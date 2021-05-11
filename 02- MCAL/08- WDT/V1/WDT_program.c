/*****************************************************************************/
/* Title        	: 	WDT Driver									         */
/* File Name    	: 	WDT_program.c   		                             */
/* Author       	: 	Fahd Badi                                            */
/* Version      	: 	1.0.0                                                */
/* Origin Date  	: 	20/11/2020                                           */
/* Notes        	: 	None                                                 */
/*****************************************************************************/

/******************************************************************************
******************************* STD LIB DIRECTIVES ****************************
******************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

/******************************************************************************
****************************** Component DIRECTIVES ***************************
******************************************************************************/

#include "WDT_interface.h"
#include "WDT_private.h"
#include "WDT_config.h"


/******************************************************************************
**************************** Function Implementation **************************
******************************************************************************/


/******************************************************************************
* Description : Watchdog Timer Initialization Function.			              *
******************************************************************************/

void WDT_voidInit(void){

	#if   TIME_OUT == WDT_PRESCALER_16K
	
		/* Watchdog Timer Prescale 16k */
		
		CLR_BIT(WDTCR, WDP0);	/* Clear WDP0 bit */
	    CLR_BIT(WDTCR, WDP1);	/* Clear WDP1 bit */
	    CLR_BIT(WDTCR, WDP2);	/* Clear WDP2 bit */
		
	#elif TIME_OUT == WDT_PRESCALER_32K
	
		/* Watchdog Timer Prescale 32k */
		
		SET_BIT(WDTCR, WDP0);	/* Set   WDP0 bit */
	    CLR_BIT(WDTCR, WDP1);	/* Clear WDP1 bit */
	    CLR_BIT(WDTCR, WDP2);	/* Clear WDP2 bit */

	#elif TIME_OUT == WDT_PRESCALER_64K
	
		/* Watchdog Timer Prescale 64k */
		
		CLR_BIT(WDTCR, WDP0);	/* Clear WDP0 bit */
	    SET_BIT(WDTCR, WDP1);	/* Set   WDP1 bit */
	    CLR_BIT(WDTCR, WDP2);	/* Clear WDP2 bit */

	#elif TIME_OUT == WDT_PRESCALER_128K
	
		/* Watchdog Timer Prescale 128k */
		
		SET_BIT(WDTCR, WDP0);	/* Set   WDP0 bit */
	    SET_BIT(WDTCR, WDP1);	/* Set   WDP1 bit */
	    CLR_BIT(WDTCR, WDP2);	/* Clear WDP2 bit */

	#elif TIME_OUT == WDT_PRESCALER_256K
	
		/* Watchdog Timer Prescale 256k */
		
		CLR_BIT(WDTCR, WDP0);	/* Clear WDP0 bit */
		CLR_BIT(WDTCR, WDP1);	/* Clear WDP1 bit */
		SET_BIT(WDTCR, WDP2);	/* Set   WDP2 bit */

	#elif TIME_OUT == WDT_PRESCALER_512K
	
		/* Watchdog Timer Prescale 512k */
		
		SET_BIT(WDTCR, WDP0);	/* Set   WDP0 bit */
		CLR_BIT(WDTCR, WDP1);	/* Clear WDP1 bit */
		SET_BIT(WDTCR, WDP2);	/* Set   WDP2 bit */
		
	#elif TIME_OUT == WDT_PRESCALER_1024K
	
		/* Watchdog Timer Prescale 1024k */
		
		CLR_BIT(WDTCR, WDP0);	/* Clear WDP0 bit */
		SET_BIT(WDTCR, WDP1);	/* Set   WDP1 bit */
		SET_BIT(WDTCR, WDP2);	/* Set   WDP2 bit */
		
	#elif TIME_OUT == WDT_PRESCALER_2048K
	
		/* Watchdog Timer Prescale 2048k */
		
		SET_BIT(WDTCR, WDP0);	/* Set   WDP0 bit */
		SET_BIT(WDTCR, WDP1);	/* Set   WDP1 bit */
		SET_BIT(WDTCR, WDP2);	/* Set   WDP2 bit */
	
	#else
		#error("You Chosed Wrong Watchdog Timer Prescale Select!")
	#endif
	
}


/******************************************************************************
* Description : Watchdog Timer Enable Function.			                      *
******************************************************************************/

void WDT_voidEnable(void){

	/* Enable Watchdog Timer */
	SET_BIT(WDTCR, WDE);
	
}


/******************************************************************************
* Description : Watchdog Timer Disable Function.			                  *
******************************************************************************/

void WDT_voidDisable(void){

	/* Set bit WDTOE and bit WDE */
	WDTCR = (( 1 << WDE )|( 1 << WDTOE ));
	
	/* Turn off WDT */
	WDTCR = 0x00;
	
}


/******************************************************************************
* Description : Watchdog Timer Refresh Function.			                  *
******************************************************************************/
void WDT_voidRefresh(void){
	
	asm("WDR");
	
}


/******************************************************************************
********************************* END OF PROGRAM ******************************
******************************************************************************/
