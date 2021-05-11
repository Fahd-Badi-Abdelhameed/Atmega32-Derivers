/*****************************************************************************/
/* Title        	: 	WDT Driver		        						     */
/* File Name    	: 	WDT_config.h      		                             */
/* Author       	: 	Fahd Badi                                            */
/* Version      	: 	1.0.0                                                */
/* Origin Date  	: 	20/11/2020                                           */
/* Notes        	: 	None                                                 */
/*****************************************************************************/

/******************************************************************************
* Description 	: Guard to protect this File from include more 			      *
*                 than one time.                               	 	 		  *
******************************************************************************/

#ifndef WDT_CONFIG_H
#define WDT_CONFIG_H


/* Watchdog Timer Prescale Select :
   Typical Time-out at    VCC = 5.0V , VCC = 3.0V
   
    * WDT_PRESCALER_16K    = 16.3 ms , 17.1 ms *
	* WDT_PRESCALER_32K    = 32.5 ms , 34.3 ms *
	* WDT_PRESCALER_64K    = 65   ms , 68.5 ms *
	* WDT_PRESCALER_128K   = 0.13 s  , 0.14 s  *
	* WDT_PRESCALER_256K   = 0.26 s  , 0.27 s  *
	* WDT_PRESCALER_512K   = 0.52 s  , 0.55 s  *
	* WDT_PRESCALER_1024K  = 1.0  s  , 1.1  s  *
	* WDT_PRESCALER_2048K  = 2.1  s  , 2.2  s  *
*/

#define TIME_OUT     WDT_PRESCALER_1024K



#endif 
/*** !comment : End of gaurd [WDT_CONFIG_H] **********************************/