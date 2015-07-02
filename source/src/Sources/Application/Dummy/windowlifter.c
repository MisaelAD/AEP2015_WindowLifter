/*============================================================================*/
/*                        Continental AEP 2015                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         windowlifter.c
* Instance:         RPL_1
* %version:         1.0
* %created_by:      Misael Alvarez Domínguez
* %date_created:    Wednesday, July 1, 2015
*=============================================================================*/
/* DESCRIPTION : Window Lifter state functions                                      */
/*============================================================================*/
/* FUNCTION COMMENT : This file describes the C source template according to  */
/* the new software platform                                                  */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | DD/MM/YYYY  |                               | Mr. Template     */
/* Integration under Continuus CM                                             */
/*============================================================================*/

/* Includes */
/* -------- */
#include "windowlifter.h"

#include "LED.h"
#include "delay.h"

/* Functions macros, constants, types and datas         */
/* ---------------------------------------------------- */
#define CLOSED (T_SBYTE)10			/* WindowPosition fully closed value */
#define OPENED (T_SBYTE)0			/* WindowPosition fully opened value */

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
/* Functions macros */

/*==================================================*/ 
/* Definition of constants                          */
/*==================================================*/ 
/* BYTE constants */


/* WORD constants */


/* LONG and STRUCTURE constants */



/*======================================================*/ 
/* Definition of RAM variables                          */
/*======================================================*/ 
/* BYTE RAM variables */
T_SBYTE  WindowPosition = CLOSED;			/* Initial window state: CLOSED */

/* WORD RAM variables */


/* LONG and STRUCTURE RAM variables */


/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Private defines */

#define WindowIdle 			states_table[0]
#define ValidateUpSignal 	states_table[1]
#define ValidateDownSignal 	states_table[2]
#define ManualMode 			states_table[3]
#define OneTouchUp 			states_table[4]
#define OneTouchDown 		states_table[5]
#define PinchOpen 			states_table[6]
#define PinchIdle 			states_table[7]

/* Private functions prototypes */
/* ---------------------------- */


/* Exported functions prototypes */
/* ----------------------------- */

/* Inline functions */
/* ---------------- */
/**************************************************************
 *  Name                 : inline_func	2
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/


/* Private functions */
/* ----------------- */
/**************************************************************
 *  Name                 : Idle
 *  Description          :	Wait for a button press, turn off movement indicators
 *  Parameters           :	void
 *  Return               :	void
 *  Critical/explanation :	No
 **************************************************************/
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

/**************************************************************
 *  Name                 : Valid_UP
 *  Description          :	Validates that UP button has been pressed for at least 10ms
 *  Parameters           :	Void
 *  Return               :	Void
 *  Critical/explanation :  No
 **************************************************************/
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

/**************************************************************
 *  Name                 : Valid_DOWN
 *  Description          :	Validates that DOWN button has been pressed for at least 10ms
 *  Parameters           :  Void
 *  Return               :	Void
 *  Critical/explanation :	No
 **************************************************************/
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

/**************************************************************
 *  Name                 : OneTouch_UP
 *  Description          :	Activates the one-touch window function to close it
 *  Parameters           :	Void
 *  Return               :	Void
 *  Critical/explanation :	No
 **************************************************************/
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

/**************************************************************
 *  Name                 : OneTouch_DOWN
 *  Description          :	Activates the one-touch window function to open it
 *  Parameters           :	Void
 *  Return               :	Void
 *  Critical/explanation :	No
 **************************************************************/
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

/**************************************************************
 *  Name                 :	Task_400ms
 *  Description          :	Modifies WindowPosition depending on the button pressed
 *  Parameters           :  Void
 *  Return               :	Void
 *  Critical/explanation :  No
 **************************************************************/
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

/**************************************************************
 *  Name                 : Valid_Pinch
 *  Description          :	Validates that pinch button has been pressed for at least 10ms
 *  Parameters           :	Void
 *  Return               :	Void
 *  Critical/explanation :  No
 **************************************************************/
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

/**************************************************************
 *  Name                 : SafeOpen
 *  Description          :	Opens window and ignores button's signal
 *  Parameters           :  Void
 *  Return               :	Void
 *  Critical/explanation :  No
 **************************************************************/
void SafeOpen(void)
{
	WindowPosition--;
	if(WindowPosition <= OPENED)
	{
		WindowPosition = OPENED;
		rps_TaskPtr = &PinchIdle;
	}
}

/**************************************************************
 *  Name                 : AntiPinch
 *  Description          :	After the safe timeout of 5 seconds, goes to WindowIdle state again
 *  Parameters           :  Void
 *  Return               :	Void
 *  Critical/explanation :  No
 **************************************************************/
void AntiPinch(void)
{
	rps_TaskPtr = &WindowIdle;
}

/* Exported functions */
/* ------------------ */
/**************************************************************
 *  Name                 :	export_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/
