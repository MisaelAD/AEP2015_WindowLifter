/*******************************************************************************/
/*
\file       windowlifter.h
\brief      
\author     Misael AD
\version    1.0
\date       June/2015
*/
/*******************************************************************************/

#ifndef _WINDOWLIFTER_H        /*prevent duplicated includes*/
#define _WINDOWLIFTER_H

/*-- Includes ----------------------------------------------------------------*/

/** Core modules */
/** Variable types and common definitions */

#include "typedefs.h"

/*-- Variables ---------------------------------------------------------------*/

/*-- Types Definitions -------------------------------------------------------*/
typedef struct {						/* Handling task structure definition */
		T_UWORD ruw_Counter;
		T_UWORD ruw_TopCount;
		tCallbackFunction cpfu_PerFunct; 
}TASKSTRUCT;
/*-- Defines -----------------------------------------------------------------*/

	/* Electronic Window Control Module States */
#define WindowIdle 			states_table[0]
#define ValidateUpSignal 	states_table[1]
#define ValidateDownSignal 	states_table[2]
#define ManualMode 			states_table[3]
#define OneTouchUp 			states_table[4]
#define OneTouchDown 		states_table[5]
#define PinchOpen 			states_table[6]
#define PinchIdle 			states_table[7]

/*-- Function Prototypes -----------------------------------------------------*/

void Task_400ms(void);
void Valid_UP(void);
void Valid_DOWN(void);
void OneTouch_UP(void);
void OneTouch_DOWN(void);
void Idle(void);
void Valid_Pinch(void);
void SafeOpen(void);
void AntiPinch(void);

#endif /* _WINDOWLIFTER_H */

/*******************************************************************************/