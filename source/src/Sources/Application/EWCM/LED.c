#include "LED.h"
#include "main.h"

void LED_ADCindicator(void);

void KITT(void);

void LED_WindowLifter(int8_t position);

uint8_t Switch_UP(void);

uint8_t Switch_DOWN(void);

uint8_t PinchSwitch(void);

void LED_UP(void);

void LED_DOWN(void);

void LEDs_Off(void);

/* LED_ADCindicator function */
/* Uses on-board LEDs to indicate ADC read value */
/* June 2015 Continental AEP */
extern uint32_t Result;			//Must declare in main
void LED_ADCindicator(void)
{
	if(Result < 200)
   	{
   		LED1 = LED_OFF;
   		LED2 = LED_OFF;
   		LED3 = LED_OFF;
   		LED4 = LED_OFF;
   	}
   	if((Result > 200) & (Result < 400))
   	{
   		LED1 = LED_ON;
   		LED2 = LED_OFF;
   		LED3 = LED_OFF;
   		LED4 = LED_OFF;
   	}
   	if((Result > 400) & (Result < 600))
   	{
   		LED1 = LED_ON;
   		LED2 = LED_ON;
   		LED3 = LED_OFF;
   		LED4 = LED_OFF;	
   	}
   	if((Result > 600) & (Result < 800))
   	{
   		LED1 = LED_ON;
   		LED2 = LED_ON;
   		LED3 = LED_ON;
   		LED4 = LED_OFF;
   	}
   	if(Result > 800)
   	{
   		LED1 = LED_ON;
   		LED2 = LED_ON;
   		LED3 = LED_ON;
   		LED4 = LED_ON;
   	}
}

/* KITT function */
/* Uses on-board LEDs as KITT routine */
/* June 2015 Continental AEP */
void KITT(void)
{
	static uint16_t KITT_state = 0;
	switch(KITT_state)
	{
	  	case 1:
	  	LED1 = LED_ON;
	  	LED2 = LED_OFF;
	  	LED3 = LED_OFF;
	  	LED4 = LED_OFF;
	  	break;
	  	case 2:
	  	LED1 = LED_OFF;
	  	LED2 = LED_ON;
	  	LED3 = LED_OFF;
	  	LED4 = LED_OFF;
	  	break;
	  	case 3:
	  	LED1 = LED_OFF;
	  	LED2 = LED_OFF;
	  	LED3 = LED_ON;
	  	LED4 = LED_OFF;
	  	break;
	  	case 4:
	  	LED1 = LED_OFF;
	  	LED2 = LED_OFF;
	  	LED3 = LED_OFF;
	  	LED4 = LED_ON;
	  	break;
	  	case 5:
	  	LED1 = LED_OFF;
	  	LED2 = LED_OFF;
	  	LED3 = LED_ON;
	  	LED4 = LED_OFF;
	  	break;
	  	case 6:
	  	LED1 = LED_OFF;
	  	LED2 = LED_ON;
	  	LED3 = LED_OFF;
	  	LED4 = LED_OFF;
	  	KITT_state = 0;
	  	break;
	  	default:
	  	/* Do Nothing */
	  	break;
	}
	KITT_state++;
}

void LED_WindowLifter(int8_t position)
{
	int8_t i;
	for(i=0 ; i<position ; i++)
	{
		SIU.GPDO[i].R = 1;
	}
	for(i=i ; i < 10 ; i++)
	{
		SIU.GPDO[i].R = 0;
	}
}

uint8_t Switch_UP(void)
{
	return !S3;
}

uint8_t Switch_DOWN(void)
{
	return !S4;
}

uint8_t PinchSwitch(void)
{
	return !S1;
}

void LED_UP(void)
{
	LEDB = 1;
}

void LED_DOWN(void)
{
	LEDG = 1;
}

void LEDs_Off(void)
{
	LEDB = 0;
	LEDG = 0;
}
