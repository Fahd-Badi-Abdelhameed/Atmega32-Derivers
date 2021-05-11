/*****************************************************************************/
/* Title        	: 	SPI Driver									         */
/* File Name    	: 	SPI_program.c   		                             */
/* Author       	: 	Fahd Badi                                            */
/* Version      	: 	2.0.0                                                */
/* Origin Date  	: 	08/05/2021                                           */
/* Notes        	: 	None                                                 */
/*****************************************************************************/

/******************************************************************************
******************************* STD LIB DIRECTIVES ****************************
******************************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/******************************************************************************
********************************* DIO DIRECTIVES ******************************
******************************************************************************/
#include "DIO_interface.h"

/******************************************************************************
****************************** Component DIRECTIVES ***************************
******************************************************************************/
#include "SPI_interface.h"
#include "SPI_private.h"
#include "SPI_config.h"
	
/******************************************************************************
******************************** Global Variables ***************************** 
******************************************************************************/

SPI_ConfigStruct SPI0 = {.SPI_CallBack = NULL };

/******************************************************************************
**************************** Function Implementation **************************
******************************************************************************/

/******************************************************************************
* !comment  :  ISR Function SPI.  							 			      *   
******************************************************************************/

ISR( SPI_STC_VECT ){

	if(SPI0.SPI_CallBack != NULL){

		SPI0.SPI_CallBack();
	}

	else{ /* Return error */ }
}

	
/******************************************************************************
* Description 	: SPI Initializing Function .				                  *
******************************************************************************/

void SPI_voidInit(void){

	SPCR = 0x00;
	SPSR = 0x00;

	switch(SPI0.EnableControl){
		
		case SPI_DISABLE:	break;	
		
		case SPI_ENABLE:

			switch(SPI0.Mode){
				
				case SPI_MASTER:   SPCR |= (1<<MSTR);     break;
				case SPI_SLAVE :                          break;
		        default:                                  break;
			}
			switch(SPI0.DataOrder){
				
				case SPI_LSB:  SPCR |= (1<<DORD);   break;
				case SPI_MSB:                       break;
		        default:                            break;
			}
			switch(SPI0.InterruptState){
				
				case SPI_INTERRUPT_ENABLE :	 SPCR |= (1<<SPIE);	 break;
				case SPI_INTERRUPT_DISABLE:                      break;
		        default:                                         break;
			}
			switch(SPI0.ClockMode){
				
				case SPI_CLK_MODE0:	   	                             break;
				case SPI_CLK_MODE1:    SPCR |= (1<<CPHA);            break;
				case SPI_CLK_MODE2:	   SPCR |= (1<<CPOL);	         break;
				case SPI_CLK_MODE3:    SPCR |= (1<<CPHA)|(1<<CPOL);  break;
		        default:                                             break;
			}
			switch(SPI0.Freq){
				
				case SPI_FCPU_BY_2  :	SPSR |= (1<<SPI2X);  		    break;
				case SPI_FCPU_BY_4  :                        		    break;
				case SPI_FCPU_BY_8  :	SPCR |= (1<<SPR0 );	 		            
				                        SPSR |= (1<<SPI2X);  		    break;
				case SPI_FCPU_BY_16 :   SPCR |= (1<<SPR0 );  		    break;
				case SPI_FCPU_BY_32 :   SPCR |= (1<<SPR1 );  		              
										SPSR |= (1<<SPI2X);  		    break;
				case SPI_FCPU_BY_64 :	SPCR |= (1<<SPR1 );	            break;
				case SPI_FCPU_BY_128:   SPCR |= (1<<SPR1 )|(1<<SPR0 );  break;
		        default:                                                break;
			}
			
		/* Enable SPI */	
		SPCR |= (1<<SPE);                break;
		default:                         break;		
	}
	
}



/******************************************************************************
* Description 	: SPI Send Char Blocking Function .				              *
******************************************************************************/

void SPI_voidSendChar(uint8 Copy_u8Data){

	/* Load data in data register */
	SPDR = Copy_u8Data;

	/* Wait till transmit is complete */
	while(0 == (GET_BIT(SPSR, SPIF)));

	/* Clear SPI interrupt flag */
	SET_BIT(SPSR, SPIF);

}



/******************************************************************************
* Description 	: SPI Receive Char Blocking Function .				          *
******************************************************************************/

uint8 SPI_u8ReceiveChar(void){

	uint8 Local_u8Dummy = 0x00;
	/* Load data in data register */
	SPDR = Local_u8Dummy;
	
	/* Wait till receive is complete */
	while(0 == (GET_BIT(SPSR, SPIF)));

	/* Clear SPI interrupt flag */
	SET_BIT(SPSR, SPIF);

	/* Return data */
	return SPDR;

}


/******************************************************************************
* Description 	: SPI Exchange Data Blocking Function .				          *
******************************************************************************/

uint8 SPI_u8ExchangeDataBlocking(uint8 Copy_u8Data){
	
	/* Transmit Data Using SPI Bus */
	SPDR = Copy_u8Data;
	
	/* Check if a Write Collison Error Occurred */ 
	if((SPSR & (1<<WCOL)) != 0){
		
		SPI0.Error = SPI_WRITE_COLLISON;
	}
	
	/* Block till the End Transmition */
	while(0 == (SPSR & (1<<SPIF)));

	/* Return Rx Data From SPIN */
	return SPDR;	
	
}


/******************************************************************************
* Description 	: SPI Exchange Data Non Blocking Function .				      *
******************************************************************************/

uint8 SPI_u8ExchangeDataNonBlocking(uint8 Copy_u8Data){

	/* Transmit Data Using SPI Bus */
	SPDR = Copy_u8Data;
	
	/* Check if a Write Collison Error Occurred */ 
	if((SPSR & (1<<WCOL)) != 0){
		
		SPI0.Error = SPI_WRITE_COLLISON;
	}

	/* Return Rx Data From SPIN */
	return SPDR;	
	
}


/******************************************************************************
* Description 	: SPI Chip Select Control Function .				          *
******************************************************************************/

void SPI_voidChipSelectControl(uint8 Copy_u8State){

	switch(Copy_u8State){
	
		case 0 :    DIO_voidSetPinValue(PORT_B, PIN4, LOW );    break;
		case 1 :    DIO_voidSetPinValue(PORT_B, PIN4, HIGH);    break;
		default:                                                break;		
		
	}
}


/******************************************************************************
********************************* END OF PROGRAM ******************************
******************************************************************************/  