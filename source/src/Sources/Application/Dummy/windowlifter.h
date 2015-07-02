/*============================================================================*/
/*                        Continental AEP 2015                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Include:        windowlifter.h
* Instance:         RPL_1
* %version:         1.0
* %created_by:      Misael Alvarez Dom�nguez
* %date_created:    Wednesday, July 2, 2015
*=============================================================================*/
/* DESCRIPTION : Header file window lifter driver                             */
/*============================================================================*/
/* FUNCTION COMMENT : contains only symbols which are exported to internal    */
/* platform modules. This will not be delivered with the library              */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 2/07/2015  | Creation of header file       | Misael AD     	  */
/*============================================================================*/

#ifndef _WINDOWLIFTER_H        /*prevent duplicated includes*/
#define _WINDOWLIFTER_H

/* Includes */
/* -------- */
#include "typedefs.h"

/* Exported types and constants */
/* ---------------------------- */

/* Types definition */
/* typedef */
typedef struct {						/* Handling task structure definition */
		T_UWORD ruw_Counter;
		T_UWORD ruw_TopCount;
		tCallbackFunction cpfu_PerFunct; 
}TASKSTRUCT;

/*==================================================*/ 
/* Declaration of exported constants                */
/*==================================================*/ 
/* BYTE constants */


/* WORD constants */


/* LONG and STRUCTURE constants */



/*======================================================*/ 
/* Definition of RAM variables                          */
/*======================================================*/ 
/* BYTES */


/* WORDS */


/* LONGS and STRUCTURES */


/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Exported functions prototypes and macros */
/* ---------------------------------------- */

/* Functions prototypes */


/* Functions macros */


/* Exported defines */


#endif

