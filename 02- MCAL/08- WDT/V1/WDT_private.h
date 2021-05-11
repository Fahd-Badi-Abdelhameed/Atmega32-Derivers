/*****************************************************************************/
/* Title        	: 	WDT Driver					         				 */
/* File Name    	: 	WDT_private.h      	                         	     */
/* Author       	: 	Fahd Badi                                            */
/* Version      	: 	1.0.0                                                */
/* Origin Date  	: 	20/11/2020                                           */
/* Notes        	: 	None                                                 */
/*****************************************************************************/

/******************************************************************************
* Description 	: Guard to protect this File from include more 			      *
*                 than one time.                               	 	 		  *
******************************************************************************/

#ifndef WDT_PRIVATE_H
#define WDT_PRIVATE_H


/******************************************************************************
* !comment : Watchdog Timer Registers Addresses Definition.  			      *
******************************************************************************/

#define WDTCR     *((volatile uint8 *) 0x41)

/******************************************************************************
* !comment :  WDTCR Register PINS Definition.  			                      *
******************************************************************************/

#define WDP0      (uint8)0
#define WDP1      (uint8)1
#define WDP2      (uint8)2
#define WDE       (uint8)3
#define WDTOE     (uint8)4


/******************************************************************************
* !comment :  Watchdog Timer Prescale Select options:  			              *
******************************************************************************/

#define WDT_PRESCALER_16K       0
#define WDT_PRESCALER_32K       1
#define WDT_PRESCALER_64K       2
#define WDT_PRESCALER_128K      3
#define WDT_PRESCALER_256K      4
#define WDT_PRESCALER_512K      5
#define WDT_PRESCALER_1024K     6
#define WDT_PRESCALER_2048K     7


#endif 
/*** !comment : End of gaurd [WDT_PRIVATE_H] *********************************/