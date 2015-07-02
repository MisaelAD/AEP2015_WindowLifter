/*******************************************************************************
*		Practice Number 2
*		Automotive Entry Program 2015
*		Kevin Castellanos
*		Misael Alvarez
********************************************************************************/

#include "MCU_derivative.h"

/* GPIO funtion prototypes  */
#include    "PIT.h"
#include    "dummy.h"
#include	"init.h"

/*****************************************************************************************************
* Definition of module wide VARIABLEs 
*****************************************************************************************************/

/****************************************************************************************************
* Declaration of module wide FUNCTIONs 
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of global wide MACROs / #DEFINE-CONSTANTs
*****************************************************************************************************/

/*****************************************************************************************************
* Declaration of module wide TYPEs 
*****************************************************************************************************/

/******************************************************************************************************
* Definition of module wide VARIABLEs 
******************************************************************************************************/

/******************************************************************************************************
* Code of module wide FUNCTIONS
******************************************************************************************************/

/*~~~~~~~ Main Code ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int main(void) 

{
	initModesAndClock();
	
	/* Disable Watchdog */
	disableWatchdog();
	
	/*Initialize LEDs on TRK-MPC560xB board */
	init_OnBoardLEDs();
	init_OnBoardPushButtons();
	
	/* Initialize Window LED bar */
	init_LEDBar();
		
	/*Initialize Interrupts */
	INTC_InitINTCInterrupts();
	/*Initialize Exception Handlers */
	EXCEP_InitExceptionHandlers();
	
	PIT_device_init();
    PIT_channel_configure(PIT_CHANNEL_0 , PIT_1ms);	
    PIT_channel_start(PIT_CHANNEL_0);
    
    /* Enable External Interrupts*/
    enableIrq();
	
	/* Infinite loop */
	for (;;) 
	{
		/* Do nothing, work using PIT ISR */
	}
}

/*~~~~~~~ End of Main Code ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
