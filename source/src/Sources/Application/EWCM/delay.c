/*============================================================================*/
/*                        Continental AEP 2015                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         delay.c
* Instance:         RPL_1
* %version:         1.0
* %created_by:      Misael Alvarez Domínguez
* %date_created:    Wednesday, July 2, 2015
*=============================================================================*/
/* DESCRIPTION : C source delay functions                                       */
/*============================================================================*/
/* FUNCTION COMMENT : Delay functions based on software routines  */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 2/07/2015  |                               | Misael AD     */
/*============================================================================*/

/* Includes */
/* -------- */
#include "typedefs.h"

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


/* WORD RAM variables */


/* LONG and STRUCTURE RAM variables */


/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Private defines */
#define CoreClock	(uint32_t)16000000

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
 *  Name                 : Delay_ms
 *  Description          :	Delay routine made by software
 *  Parameters           :  [Input:Time in ms]
 *  Return               :	void
 *  Critical/explanation :  No
 **************************************************************/
void Delay_ms(uint32_t TimeOut)
{
	TimeOut*=(CoreClock/1000);
	for(TimeOut=TimeOut; TimeOut != 0; TimeOut--)
	{
		
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
