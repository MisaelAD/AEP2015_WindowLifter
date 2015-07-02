/*============================================================================*/
/*                        Continental AEP 2015                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         dummy.c
* Instance:         RPL_1
* %version:         1.1
* %created_by:      Misael Alvarez Domínguez
* %date_created:    Wednesday, July 1, 2015
*=============================================================================*/
/* DESCRIPTION : PIT ISR                                       */
/*============================================================================*/
/* FUNCTION COMMENT : Periodic Interrupt Timer, Interrupt service Routine  */
/*                                                   */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | DD/MM/YYYY  |                               | Mr. Template     */
/* Integration under Continuus CM                                             */
/*	1.1		|	1/07/2015	|Template standard added		|Misael AD        */
/*	1.2		|	2/07/2015	|Buttons interface updated		|Misael AD        */
/*============================================================================*/

/* Includes */
/* -------- */
#include "dummy.h"
#include "typedefs.h"
#include "windowlifter.h"
#include "LED.h"

/* Functions macros, constants, types and datas         */
/* ---------------------------------------------------- */
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
extern T_SBYTE  WindowPosition;

/* WORD RAM variables */


/* LONG and STRUCTURE RAM variables */
extern TASKSTRUCT *rps_TaskPtr[];

/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Private defines */


/* Private functions prototypes */
/* ---------------------------- */

/* Exported functions prototypes */
/* ----------------------------- */
void PIT_1ms(void);

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
 *  Name                 : PIT_1ms
 *  Description          :	PIT ISR
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :  -Increments counter and triggers function 
 							if period has been reached
 							-Refreshes the LED bar window state indicator
 **************************************************************/
void PIT_1ms(void)
{
	T_UBYTE i;
	for(i=0; i<2; i++)
	{
		rps_TaskPtr[i]->ruw_Counter++;
		if(rps_TaskPtr[i]->ruw_Counter >= rps_TaskPtr[i]->ruw_TopCount)	/* Check if match */
		{
			rps_TaskPtr[i]->ruw_Counter=0;			/* Clear counter */
			rps_TaskPtr[i]->cpfu_PerFunct();		/* Call function */
		}
	}
	LED_WindowLifter(WindowPosition);
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
