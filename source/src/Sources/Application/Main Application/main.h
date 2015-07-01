/* main.h file                        */
/* Simplified registers tags          */
/* June 2015 Automotive Entry Program */

//#include "typedefs.h"
//#include "MPC5606B.h"

#include "MCU_derivative.h"

#define Output (uint16_t)0x200	//PCR_GPIO_OutputConfiguration
#define Input  (uint16_t)0x100	//PCR_GPIO_InputConfiguration
#define Analog (uint16_t)0x2000	//PCR_AnalogConfiguration

/* Push buttons */
#define PortE0 SIU.PCR[64].R
#define PortE1 SIU.PCR[65].R 
#define PortE2 SIU.PCR[66].R 
#define PortE3 SIU.PCR[67].R

/* LEDs */   
#define PortE4 SIU.PCR[68].R 
#define PortE5 SIU.PCR[69].R 
#define PortE6 SIU.PCR[70].R 
#define PortE7 SIU.PCR[71].R

/* ADC Pins */
#define PortB4 SIU.PCR[20].R	//ADC0_P0 

/* Push buttons pins */
#define S1 SIU.GPDI[64].R
#define S2 SIU.GPDI[65].R
#define S3 SIU.GPDI[66].R
#define S4 SIU.GPDI[67].R

/* LED pins */
#define LED1 SIU.GPDO[68].R
#define LED2 SIU.GPDO[69].R
#define LED3 SIU.GPDO[70].R
#define LED4 SIU.GPDO[71].R
#define LEDB SIU.GPDO[10].R
#define LEDG SIU.GPDO[11].R

/* LED states */
#define LED_ON  0
#define LED_OFF 1

/* ADC registers */
#define ANP0_Valid ADC_0.CDR[0].B.VALID		//Precision channel 0 valid conversion flag
#define ANP0_Data  ADC_0.CDR[0].B.CDATA		//Precision channel 0 converted data