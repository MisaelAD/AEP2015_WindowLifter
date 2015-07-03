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
/*	1.1		|	2/07/2015	|Buttons interface updated		|Misael AD        */
/*============================================================================*/

/* Includes */
/* -------- */
#include "windowlifter.h"

#include "LED.h"
#include "delay.h"

/* Functions macros, constants, types and datas		    */
/* ---------------------------------------------------- */
#define CLOSED (T_SBYTE)10			/* WindowPosition fully closed value */
#define OPENED (T_SBYTE)0			/* WindowPosition fully opened value */

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
static T_SWORD	rsw_ValidationTime;
/* WORD RAM variables */


/* LONG and STRUCTURE RAM variables */


/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Private defines */
#define WindowPtr	rps_TaskPtr[0]
#define ButtonPtr	rps_TaskPtr[1]

#define ValidationPeriod	(T_SWORD)10
#define ValidationClear		(T_SWORD)0
#define OneTouchTimeOut		(T_SWORD)500

#define WindowIdle 			states_table[0]
#define ValidateUpSignal 	states_table[1]
#define ValidateDownSignal 	states_table[2]
#define ManualMode 			states_table[3]
#define OneTouchUp 			states_table[4]
#define OneTouchDown 		states_table[5]
#define PinchOpen 			states_table[6]
#define PinchIdle 			states_table[7]
#define ButtonIdle 			states_table[8]

#define ATOMIC_ENTRY	asm(" wrteei 0")	/* Atomic code section entry */
#define ATOMIC_EXIT		asm(" wrteei 1")	/* Atomic code section exit */


/* Private functions prototypes */
/* ---------------------------- */
void Task_400ms(void);
void Valid_UP(void);
void Valid_DOWN(void);
void OneTouch_UP(void);
void OneTouch_DOWN(void);
void Idle(void);
void Valid_Pinch(void);
void SafeOpen(void);
void AntiPinch(void);
void ScanButtons(void);


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

/* Special types and datas								*/
/* ---------------------------------------------------- */
TASKSTRUCT states_table[]={		/* Task's table	 initialization */
/*Time period*/			/* States */  	  /*	Defined as:			*/
/*   1ms */		{0,   1, &Idle			},/* 0 - WindowIdle			*/
/*  10ms */		{0,   1, &Valid_UP		},/* 1 - ValidateUpSignal	*/
/*  10ms */		{0,   1, &Valid_DOWN	},/* 2 - ValidateDownSignal	*/
/* 400ms */		{0, 400, &Task_400ms	},/* 3 - ManualMode			*/
/* 400ms */		{0, 400, &OneTouch_UP	},/* 4 - OneTouchUp			*/
/* 400ms */		{0, 400, &OneTouch_DOWN	},/* 5 - OneTouchDown		*/
/* 400ms */		{0, 400, &SafeOpen		},/* 6 - PinchOpen			*/
/*   5s  */		{0,5000, &AntiPinch		},/* 7 - PinchIdle			*/
/*   1ms */		{0,	  1, &ScanButtons	} /* 8 - ButtonIdle			*/
};

TASKSTRUCT *rps_TaskPtr[]=
{
	&WindowIdle,&ButtonIdle
};

/* Private functions */
/* ----------------- */
/**************************************************************
 *  Name                 : Idle
 *  Description          :	Wait for a button press, turn off 
 								movement indicators
 *  Parameters           :	void
 *  Return               :	void
 *  Critical/explanation :	No
 **************************************************************/
void Idle(void)
{
	/* Do nothing */
}


/**************************************************************
 *  Name                 : Valid_UP
 *  Description          :	Validates that UP button has been 
 								pressed for at least 10ms
 *  Parameters           :	Void
 *  Return               :	Void
 *  Critical/explanation :  No
 **************************************************************/
void Valid_UP(void)
{
	if(Switch_UP())
	{
		rsw_ValidationTime++;
		if(rsw_ValidationTime == ValidationPeriod)
		{
			if(WindowPtr != &WindowIdle)
			{
				WindowPtr = &WindowIdle;
				while(Switch_UP())
				{
					LEDs_Off();
				}
			}
			else
			{
				WindowPtr = &OneTouchUp;
			}
		}
		else if(rsw_ValidationTime >= OneTouchTimeOut)
		{
			ButtonPtr = &WindowIdle;
			WindowPtr = &ManualMode;
			rsw_ValidationTime = ValidationClear;
		}
	}
	else
	{
		ButtonPtr = &ButtonIdle;
		rsw_ValidationTime = ValidationClear;
	}
}

/**************************************************************
 *  Name                 : Valid_DOWN
 *  Description          :	Validates that DOWN button has been 
 								pressed for at least 10ms
 *  Parameters           :  Void
 *  Return               :	Void
 *  Critical/explanation :	No
 **************************************************************/
void Valid_DOWN(void)
{
	if(Switch_DOWN())
	{
		rsw_ValidationTime++;
		if(rsw_ValidationTime == ValidationPeriod)
		{
			if(WindowPtr != &WindowIdle)
			{
				WindowPtr = &WindowIdle;
				while(Switch_DOWN())
				{
					LEDs_Off();
				}
			}
			else
			{
				WindowPtr = &OneTouchDown;
			}
		}
		else if(rsw_ValidationTime >= OneTouchTimeOut)
		{
			ButtonPtr = &WindowIdle;
			WindowPtr = &ManualMode;
			rsw_ValidationTime = ValidationClear;
		}
	}
	else
	{
		ButtonPtr = &ButtonIdle;
		rsw_ValidationTime = ValidationClear;
	}
}

/**************************************************************
 *  Name                 : OneTouch_UP
 *  Description          :	Activates the one-touch window 
 								function to close it
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
		WindowPtr = &WindowIdle;
	}
	else
	{
		/* Do nothing */
	}
	if(Switch_DOWN() | Switch_UP())
	{
		WindowPtr = &ManualMode;
	}
	else
	{
		/* Do nothing */
	}
	Valid_Pinch();
}

/**************************************************************
 *  Name                 : OneTouch_DOWN
 *  Description          :	Activates the one-touch window function 
 								to open it
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
		WindowPtr = &WindowIdle;
	}
	else
	{
		/* Do nothing */
	}
	if(Switch_DOWN() | Switch_UP())
	{
		WindowPtr = &ManualMode;
	}
	else
	{
		/* Do nothing */
	}
}

/**************************************************************
 *  Name                 :	Task_400ms
 *  Description          :	Modifies WindowPosition depending on 
 								the button pressed
 *  Parameters           :  Void
 *  Return               :	Void
 *  Critical/explanation :  No
 **************************************************************/
void Task_400ms(void)	/* Manual operation; transition each 400ms */
{
	LEDs_Off();
	if(Switch_Combination())
	{
		WindowPtr = &WindowIdle;
		ButtonPtr = &ButtonIdle;
		LEDs_Off();
	}
	else if(Switch_UP())
	{
		LED_UP();
		WindowPosition++;
		if(WindowPosition >= CLOSED)
		{
			LEDs_Off();
			WindowPosition = CLOSED;
			WindowPtr = &WindowIdle;
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
			WindowPtr = &WindowIdle;
		}	
	}
	else
	{
		WindowPtr = &WindowIdle;
		ButtonPtr = &ButtonIdle;
		LEDs_Off();
	}
}

/**************************************************************
 *  Name                 : Valid_Pinch
 *  Description          :	Validates that pinch button has been 
 								pressed for at least 10ms
 *  Parameters           :	Void
 *  Return               :	Void
 *  Critical/explanation :  No
 **************************************************************/
void Valid_Pinch(void)
{
	if(PinchSwitch())
	{
		ATOMIC_ENTRY;
		Delay_ms(10);
		if(PinchSwitch())
		{
			LEDs_Off();
			WindowPosition--;
			WindowPtr = &PinchOpen;
			LEDs_Off();
			LED_DOWN();
		}
		ATOMIC_EXIT;
	}
	else
	{
		/* Do nothing */
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
		WindowPtr = &PinchIdle;
		LEDs_Off();
	}
	else
	{
		/* Do nothing */
	}
}

/**************************************************************
 *  Name                 : AntiPinch
 *  Description          :	After the safe timeout of 5 seconds, 
 								goes to WindowIdle state again
 *  Parameters           :  Void
 *  Return               :	Void
 *  Critical/explanation :  No
 **************************************************************/
void AntiPinch(void)
{
	WindowPtr = &WindowIdle;
}

/**************************************************************
 *  Name                 : ScanButtons
 *  Description          :	Reads the logic state of the inputs
 *  Parameters           :  Void
 *  Return               :	Void
 *  Critical/explanation :  No
 **************************************************************/
void ScanButtons(void)
{
	if(WindowPtr != &ManualMode)
	{
		if( Switch_Combination() )
		{
			/* Do nothing */
		}
		else if(Switch_UP())
		{
			ButtonPtr = &ValidateUpSignal;
		}
		else if(Switch_DOWN())
		{
			ButtonPtr = &ValidateDownSignal;
		}
	}
	else
	{
		/* Do nothing */
	}
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
