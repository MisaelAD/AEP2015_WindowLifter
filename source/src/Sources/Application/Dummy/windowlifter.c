/*******************************************************************************
*		Practice Number 2
*		Automotive Entry Program 2015
*		Misael Alvarez
********************************************************************************/

/*******************************************************************************/
/*
\file       dummy.c
\brief      Window Lifter state functions
\author     Misael AD
\version    1.0
\date       June 2015
*/

/*****************************************************************************************************
 Include files
*****************************************************************************************************/

/* Core modules */
/* Variable types and common definitions */

/* Own headers */
#include "windowlifter.h"

/* Used modules */ 
#include "LED.h"
#include "delay.h"

/*****************************************************************************************************
 Defines
*****************************************************************************************************/
#define CLOSED (T_SBYTE)10			/* WindowPosition fully closed value */
#define OPENED (T_SBYTE)0			/* WindowPosition fully opened value */

/*****************************************************************************************************
 Definition of VARIABLEs 
*****************************************************************************************************/
TASKSTRUCT states_table[]={		/* Task's table	 initialization */
/*Time period*/			/* States */  	  /*	Defined as:			*/
/*   1ms */		{0,   1, &Idle			},/* 0 - WindowIdle			*/
/*  10ms */		{0,  10, &Valid_UP		},/* 1 - ValidateUpSignal	*/
/*  10ms */		{0,  10, &Valid_DOWN	},/* 2 - ValidateDownSignal	*/
/* 400ms */		{0, 400, &Task_400ms	},/* 3 - ManualMode			*/
/* 400ms */		{0, 400, &OneTouch_UP	},/* 4 - OneTouchUp			*/
/* 400ms */		{0, 400, &OneTouch_DOWN	},/* 5 - OneTouchDown		*/
/* 400ms */		{0, 400, &SafeOpen		},/* 6 - PinchOpen			*/
/*   5s  */		{0,5000, &AntiPinch		} /* 7 - PinchIdle			*/
};

TASKSTRUCT *rps_TaskPtr = &states_table[0];	/* Pointer to state; initial: IDLE */

T_SBYTE  WindowPosition = CLOSED;			/* Initial window state: CLOSED */

/*****************************************************************************************************
 Functions 
*****************************************************************************************************/

/* Idle function 					*/
/* Window lifter state: WindowIdle 	*/
/* Reads buttons signals 			*/
/* June 2015 Continental AEP 		*/
void Idle(void)
{
	LEDs_Off();
	if(Switch_UP())
	{
		rps_TaskPtr = &ValidateUpSignal;
	}
	else if(Switch_DOWN())
	{
		rps_TaskPtr = &ValidateDownSignal;
	}
}

/* Periodic 400ms function 									*/
/* Window lifter state: ManualMode 							*/
/* Modifies WindowPosition depending on the button pressed	*/
/* June 2015 Continental AEP 								*/
void Task_400ms(void)	/* Manual operation; transition each 400ms */
{
	LEDs_Off();
	if(Switch_UP())
	{
		LED_UP();
		WindowPosition++;
		if(WindowPosition >= CLOSED)
		{
			LEDs_Off();
			WindowPosition = CLOSED;
			rps_TaskPtr = &WindowIdle;
		}
		Valid_Pinch();
	}
	else if(Switch_DOWN())
	{
		LED_DOWN();
		WindowPosition--;
		if(WindowPosition <= OPENED)
		{
			LEDs_Off();
			WindowPosition = OPENED;
			rps_TaskPtr = &WindowIdle;
		}	
	}
	else
	{
		rps_TaskPtr = &WindowIdle;
	}
}

/* Valid_UP function 											*/
/* Window lifter state: ValidateUpSignal  						*/
/* Validates that UP button has been pressed for at least 10ms	*/
/* June 2015 Continental AEP 									*/
void Valid_UP(void)
{
	if(Switch_UP())
	{
		Task_400ms();
		rps_TaskPtr = &OneTouchUp;
	}
	else
	{
		rps_TaskPtr = &WindowIdle;
	}
}

/* Valid_DOWN function 												*/
/* Window lifter state: ValidateDownSignal  						*/
/* Validates that DOWN button has been pressed for at least 10ms	*/
/* June 2015 Continental AEP 										*/
void Valid_DOWN(void)
{
	if(Switch_DOWN())
	{
		Task_400ms();
		rps_TaskPtr = &OneTouchDown;
	}
	else
	{
		rps_TaskPtr = &WindowIdle;
	}
}

/* OneTouch_UP function 								*/
/* Window lifter state: OneTouchUp  					*/
/* Activates the one-touch window function to close it	*/
/* June 2015 Continental AEP 							*/
void OneTouch_UP(void)
{
	LED_UP();
	WindowPosition++;
	if(WindowPosition >= CLOSED)
	{
		LEDs_Off();
		WindowPosition = CLOSED;
		rps_TaskPtr = &WindowIdle;
	}
	if(Switch_DOWN() | Switch_UP())
	{
		rps_TaskPtr = &ManualMode;
	}
	Valid_Pinch();
}

/* OneTouch_DOWN function 								*/
/* Window lifter state: OneTouchDown  					*/
/* Activates the one-touch window function to open it	*/
/* June 2015 Continental AEP 							*/
void OneTouch_DOWN(void)
{
	LED_DOWN();
	WindowPosition--;
	if(WindowPosition <= OPENED)
	{
		LEDs_Off();
		WindowPosition = OPENED;
		rps_TaskPtr = &WindowIdle;
	}
	if(Switch_DOWN() | Switch_UP())
	{
		rps_TaskPtr = &ManualMode;
	}
}

/* Valid_Pinch function, only when closing the window				*/
/* Validates that pinch button has been pressed for at least 10ms	*/
/* If true, it triggers anti-pinch safe mode */
/* June 2015 Continental AEP 										*/
void Valid_Pinch(void)
{
	if(PinchSwitch())
	{
		Delay_ms(10);
		if(PinchSwitch())
		{
			WindowPosition--;
			rps_TaskPtr = &PinchOpen;
			LEDs_Off();
		}
	}
}

/* SafeOpen function 						*/
/* Window lifter state: PinchOpen  			*/
/* Opens window and ignores button's signal	*/
/* June 2015 Continental AEP 				*/
void SafeOpen(void)
{
	WindowPosition--;
	if(WindowPosition <= OPENED)
	{
		WindowPosition = OPENED;
		rps_TaskPtr = &PinchIdle;
	}
}

/* AntiPinch function 													*/
/* Window lifter state: PinchIdle  										*/
/* After the safe timeout of 5 seconds, goes to WindowIdle state again	*/
/* June 2015 Continental AEP 											*/
void AntiPinch(void)
{
	rps_TaskPtr = &WindowIdle;
}
