#include "hc32_ll.h"

#define LED_PORT	GPIO_PORT_B
#define LED_PIN		GPIO_PIN_14

static char *    digits       = "0123456789abcdefghijklmnopqrstuvwxyz";

const char CompileTimeStr[] __attribute__((section(".ARM.__at_0x2000"))) = __TIME__;
const char CompileDateStr[] __attribute__((section(".ARM.__at_0x200A"))) = __DATE__;
static void init_led_port( void )
{
	stc_gpio_init_t stcGpioInit;

	GPIO_StructInit( &stcGpioInit );
	stcGpioInit.u16PinState = PIN_STAT_RST;
	stcGpioInit.u16PinDir = PIN_DIR_OUT;
  stcGpioInit.u16PinAttr = PIN_ATTR_DIGITAL;
	GPIO_Init( LED_PORT, LED_PIN, &stcGpioInit );
}
/* TimerA-2-PWM2 PA1 */
static void init_PWM_port( void )
{
	stc_gpio_init_t stcGpioInit;
	stc_tmra_init_t stcTmraInit;
    stc_tmra_pwm_init_t stcPwmInit;

	
// 	GPIO_StructInit( &stcGpioInit );
// 	stcGpioInit.u16PinState = PIN_STAT_RST;
// 	stcGpioInit.u16PinDir = PIN_DIR_OUT;
//   stcGpioInit.u16PinAttr = PIN_ATTR_DIGITAL;
// 	GPIO_Init( GPIO_PORT_A, GPIO_PIN_01, &stcGpioInit );
	
	FCG_Fcg2PeriphClockCmd(FCG2_PERIPH_TMRA_2, ENABLE);

	TMRA_StructInit(&stcTmraInit);
	stcTmraInit.sw_count.u16ClockDiv = TMRA_CLK_DIV64;
	stcTmraInit.sw_count.u16CountDir = TMRA_DIR_UP;
	stcTmraInit.sw_count.u16CountMode = TMRA_MD_SAWTOOTH;
	stcTmraInit.u32PeriodValue = 2526;

	TMRA_Init(CM_TMRA_2, &stcTmraInit);

	TMRA_PWM_StructInit(&stcPwmInit);
    stcPwmInit.u32CompareValue = 500;
	stcPwmInit.u16CompareMatchPolarity = TMRA_PWM_LOW;
	stcPwmInit.u16PeriodMatchPolarity = TMRA_PWM_HIGH;
	stcPwmInit.u16StopPolarity = TMRA_PWM_HIGH;

    GPIO_SetFunc( GPIO_PORT_A, GPIO_PIN_01, GPIO_FUNC_4 );
    TMRA_PWM_Init(CM_TMRA_2, TMRA_CH2, &stcPwmInit);

    TMRA_PWM_OutputCmd(CM_TMRA_2, TMRA_CH2, ENABLE);
	TMRA_Start(CM_TMRA_2);
}

#define PHASE_A_ON() GPIO_SetPins( GPIO_PORT_A, GPIO_PIN_00 )
#define PHASE_B_ON() GPIO_SetPins( GPIO_PORT_A, GPIO_PIN_02 )
#define PHASE_C_ON() GPIO_SetPins( GPIO_PORT_A, GPIO_PIN_04 )
#define PHASE_D_ON() GPIO_SetPins( GPIO_PORT_A, GPIO_PIN_06 )

#define PHASE_A_OFF() GPIO_ResetPins( GPIO_PORT_A, GPIO_PIN_00 )
#define PHASE_B_OFF() GPIO_ResetPins( GPIO_PORT_A, GPIO_PIN_02 )
#define PHASE_C_OFF() GPIO_ResetPins( GPIO_PORT_A, GPIO_PIN_04 )
#define PHASE_D_OFF() GPIO_ResetPins( GPIO_PORT_A, GPIO_PIN_06 )

#define stepDelayMS() DDL_DelayMS(1);

#define GPIO_PORT_TX		GPIO_PORT_A
#define GPIO_PIN_TX			GPIO_PIN_09

#define GPIO_PORT_RX		GPIO_PORT_A
#define GPIO_PIN_RX			GPIO_PIN_08



#define TX_GPIO_FUNC		GPIO_FUNC_36
#define RX_GPIO_FUNC		GPIO_FUNC_37


#define RI_INT_SRC		INT_SRC_USART2_RI
#define RI_IRQ_NUM		INT081_IRQn

#define EI_INT_SRC		INT_SRC_USART2_EI
#define EI_IRQ_NUM		INT082_IRQn

#define USART_UNIT					( CM_USART2 )
#define USART_FCG_ENABLE()			( FCG_Fcg1PeriphClockCmd( FCG1_PERIPH_USART2, ENABLE ) )

extern int
ee_printf(const char *fmt, ...);

void usart_init()
{
	stc_usart_uart_init_t stcUartInit;
	stc_gpio_init_t stcGpioInit;

	GPIO_SetFunc( GPIO_PORT_RX, GPIO_PIN_RX, RX_GPIO_FUNC );
	GPIO_SetFunc( GPIO_PORT_TX, GPIO_PIN_TX, TX_GPIO_FUNC );

	USART_FCG_ENABLE();

	USART_UART_StructInit( &stcUartInit );
	stcUartInit.u32ClockDiv = USART_CLK_DIV16;
	stcUartInit.u32Baudrate = 9600UL;				/*  */
	stcUartInit.u32OverSampleBit = USART_OVER_SAMPLE_8BIT;
	stcUartInit.u32Parity = USART_PARITY_NONE;
	USART_UART_Init( USART_UNIT, &stcUartInit, NULL );

	USART_FuncCmd( USART_UNIT, ( USART_RX | USART_INT_RX | USART_TX ), ENABLE );
}



void step_nonreverse()
{
	PHASE_A_ON();
	PHASE_B_OFF();
	PHASE_C_OFF();
	PHASE_D_OFF();
	stepDelayMS();
	PHASE_A_ON();
	PHASE_B_ON();
	PHASE_C_OFF();
	PHASE_D_OFF();
	stepDelayMS();
	PHASE_A_OFF();
	PHASE_B_ON();
	PHASE_C_OFF();
	PHASE_D_OFF();
	stepDelayMS();
	PHASE_A_OFF();
	PHASE_B_ON();
	PHASE_C_ON();
	PHASE_D_OFF();
	stepDelayMS();
	PHASE_A_OFF();
	PHASE_B_OFF();
	PHASE_C_ON();
	PHASE_D_OFF();
	stepDelayMS();
	PHASE_A_OFF();
	PHASE_B_OFF();
	PHASE_C_ON();
	PHASE_D_ON();
	stepDelayMS();
	PHASE_A_OFF();
	PHASE_B_OFF();
	PHASE_C_OFF();
	PHASE_D_ON();
	stepDelayMS();
	PHASE_A_ON();
	PHASE_B_OFF();
	PHASE_C_OFF();
	PHASE_D_ON();
	stepDelayMS();
}

static void usart_send_string( char * pchar )
{
	while( *pchar != '\0' )
	{
		
	USART_WriteData( USART_UNIT, *pchar );
		pchar++;
		DDL_DelayMS(2);
	}
}
int main(void)
{
	LL_PERIPH_WE( LL_PERIPH_ALL );	//Unlock FCG Register.
	
	init_led_port();
	init_PWM_port();
	usart_init();

	LL_PERIPH_WP( LL_PERIPH_ALL );	//Unlock FCG Register.
	while(1)
	{
		// step_nonreverse();
//		GPIO_TogglePins(GPIO_PORT_B,GPIO_PIN_14);
//		ee_printf("this is a demo %d %d\r", 22, 33 );
//		usart_send_string( "This is a demo!\r\n" );
//		usart_send_string(digits);
//		usart_send_string("\r");
		DDL_DelayMS(500);
	}
	return 0;
}