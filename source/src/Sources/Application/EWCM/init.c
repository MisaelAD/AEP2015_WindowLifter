/* init.c file                        */
/* Init functions                     */
/* June 2015 Automotive Entry Program */

#include "init.h"
//#include "typedefs.h"
#include "main.h"
//#include "MPC5604B.h"

void disableWatchdog(void);
void init_OnBoardLEDs(void);
void init_OnBoardPushButtons(void);
void init_ADC0_P0(void);
void init_LEDBar(void);

void disableWatchdog(void) 
{
  SWT.SR.R = 0x0000c520;     /* Write keys to clear soft lock bit */
  SWT.SR.R = 0x0000d928; 
  SWT.CR.R = 0x8000010A;     /* Clear watchdog enable (WEN) */
}

void init_OnBoardLEDs(void)
{
	/* Set on-board LED pins as outputs */
  PortE4 = Output;	//LED 1
  PortE5 = Output;	//LED 2
  PortE6 = Output;	//LED 3
  PortE7 = Output;	//LED 4
  		/* Initial LEDs state: OFF */
  LED1 = LED_OFF;
  LED2 = LED_OFF;
  LED3 = LED_OFF;
  LED4 = LED_OFF;
}

void init_OnBoardPushButtons(void)
{
	/* Set on-board push-buttons as inputs */
  PortE0 = Input;	//S1
  PortE1 = Input;	//S2
  PortE2 = Input;	//S3
  PortE3 = Input;	//S4	
}

void init_ADC0_P0(void)
{
  PortB4 = Analog;				/* Initialize PB[4] as ADC0_P0 */
  ADC_0.MCR.R = 0x20000000;   	/* Initialize ADC0 for scan mode */
  ADC_0.NCMR0.R = 1;            /* Select ADC0_P0 input for conversion */
  ADC_0.CTR0.R = 0x00008606;    /* Conversion times for 32MHz ADClock */
  ADC_0.MCR.B.NSTART = 1;       /* Trigger normal conversions for ADC0 */	
}

/* PortA 0 - 9 */
void init_LEDBar(void)
{
	uint8_t pin;
	for(pin=0 ; pin<12 ; pin++)
	{
		SIU.PCR[pin].R = Output;
	}
}
