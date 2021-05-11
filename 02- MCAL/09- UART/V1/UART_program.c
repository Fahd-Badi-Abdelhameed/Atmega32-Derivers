/*****************************************************************************/
/* Title        	: 	UART Driver									         */
/* File Name    	: 	UART_program.c   		                             */
/* Author       	: 	Fahd Badi                                            */
/* Version      	: 	1.0.0                                                */
/* Origin Date  	: 	04/12/2020                                           */
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

#include "UART_interface.h"
#include "UART_private.h"
#include "UART_config.h"
	
/******************************************************************************
* !comment  :  Pointer to function for callback.  							  *
******************************************************************************/

static void (*UART_TX_CallBack)(void) = NULL;	
static void (*UART_RX_CallBack)(void) = NULL;
	
	
/******************************************************************************
**************************** Function Implementation **************************
******************************************************************************/

/******************************************************************************
* Description 	: UART initialization Function.				                  *
******************************************************************************/

void UART_voidInit(void){

	uint8 Local_u8Help = 0;

	/* Set baud rate value */
	UBRRL = BAUD_RATE_VALUE;
	UBRRH =  0;
	
	/* enable RX */
	SET_BIT(UCSRB, RXEN);

	/* enable TX */
	SET_BIT(UCSRB, TXEN);

	/* Select UCSRC register */
	SET_BIT(Local_u8Help, URSEL);

	#if UART_MODE == ASYNCHRONOUS

		/* Asynchronous Mode */
		CLR_BIT(Local_u8Help, UMSEL);

	#elif UART_MODE == SYNCHRONOUS

		/* Synchronous Mode */
		SET_BIT(Local_u8Help, UMSEL);

	#else
		#error("You Chosed Wrong UART Mode!")
	#endif


	#if PARITY_MODE == DISABLE

		/* Disabl Parity Mode */
		CLR_BIT(Local_u8Help, UPM0);
		CLR_BIT(Local_u8Help, UPM1);

	#elif PARITY_MODE == EVEN_PARITY

		/* Parity Mode Even */
		CLR_BIT(Local_u8Help, UPM0);
		SET_BIT(Local_u8Help, UPM1);

	#elif PARITY_MODE == ODD_PARITY

		/* Parity Mode Odd */
		SET_BIT(Local_u8Help, UPM0);
		SET_BIT(Local_u8Help, UPM1);

	#else
		#error("You Chosed Wrong UART Parity Mode!")
	#endif


	#if STOP_BIT == ONE_BIT

		/* 1-bit stop */
		CLR_BIT(Local_u8Help, USBS);

	#elif STOP_BIT == TWO_BIT

		/* 2-bit stop */
		SET_BIT(Local_u8Help, USBS);

	#else
		#error("You Chosed Wrong UART Stop Bit Option!")
	#endif
	

	#if	DATA_SIZE == FIVE_BIT

		/* Data size 5-bit */
		CLR_BIT(Local_u8Help, UCSZ0);
		CLR_BIT(Local_u8Help, UCSZ1);
		CLR_BIT(UCSRB, UCSZ2);

	#elif	DATA_SIZE == SIX_BIT

		/* Data size 6-bit */
		SET_BIT(Local_u8Help, UCSZ0);
		CLR_BIT(Local_u8Help, UCSZ1);
		CLR_BIT(UCSRB, UCSZ2);

	#elif	DATA_SIZE == SEVEN_BIT

		/* Data size 7-bit */
		CLR_BIT(Local_u8Help, UCSZ0);
		SET_BIT(Local_u8Help, UCSZ1);
		CLR_BIT(UCSRB, UCSZ2);

	#elif	DATA_SIZE == EIGHT_BIT

		/* Data size 8-bit */
		SET_BIT(Local_u8Help, UCSZ0);
		SET_BIT(Local_u8Help, UCSZ1);
		CLR_BIT(UCSRB, UCSZ2);

	#elif	DATA_SIZE == NINE_BIT

		/* Data size 9-bit */
		SET_BIT(Local_u8Help, UCSZ0);
		SET_BIT(Local_u8Help, UCSZ1);
		SET_BIT(UCSRB, UCSZ2);

	#else
		#error("You Chosed Wrong UART data size option!")
	#endif

	UCSRC = Local_u8Help;
	
}



/******************************************************************************
* Description 	: UART Send Char Blocking Function.		                      *
******************************************************************************/

void UART_voidSendChar(uint8 Copy_u8Data){

	while('\0' != Copy_u8Data){

		/* Load data in data register */
		UDR = Copy_u8Data;

		/* wait till transmit is complete */
		while(0 == (GET_BIT(UCSRA, TXC)));
	}

}

/******************************************************************************
* Description 	: UART Receive char Blocking Function.		                  *
******************************************************************************/
	
uint8 UART_u8Receive(void){

	uint16 Local_u16TimeOut = 0;
	uint8  Local_u8ReceivedData = 0;

	/* wait till receive is complete */
	while(0 == (GET_BIT(UCSRA, RXC))){

		Local_u16TimeOut ++;

		if(10000 == Local_u16TimeOut){

			Local_u8ReceivedData = 255;
			break;
		}
	}
	
	if(0 == Local_u8ReceivedData){

		 Local_u8ReceivedData = UDR;
	}

	/* Clear flag */
	SET_BIT(UCSRA, RXC);
	
	/* return data */
	return (Local_u8ReceivedData);
	
}


/******************************************************************************
* Description 	: UART Transmit String Blocking Function.                     *
******************************************************************************/

void UART_voidTransmit(uint8 Copy_u8Arr[]){

	uint8 Local_u8Counter = 0;
	
	while('\0' != Copy_u8Arr[Local_u8Counter]){
	
		UDR = Copy_u8Arr[Local_u8Counter];
		
		/* wait till transmit is complete */
		while(0 == (GET_BIT(UCSRA, TXC)));

		Local_u8Counter ++;
	}
	
}


/******************************************************************************
* Description 	: UART Send Byte Function, Used using interrupt.              *
******************************************************************************/

void UART_voidSendByteNoBlock(uint8 Copy_u8Data){

	UDR = Copy_u8Data;
}


/******************************************************************************
* Description 	: UART Receive Byte Function, Used using interrupt.           *
******************************************************************************/

uint8 UART_u8ReceiveByteNoBlock(void){

	return UDR;
}


/******************************************************************************
* Description 	: UART RX Interrupt Enable Function.			              *
******************************************************************************/

void UART_voidEnableInterrupt_RX(void){

	SET_BIT(UCSRB, RXCIE);
}


/******************************************************************************
* Description 	: UART RX Interrupt Disable Function.			              *
******************************************************************************/

void UART_voidDisableInterrupt_RX(void){

	CLR_BIT(UCSRB, RXCIE);
}


/******************************************************************************
* Description 	: UART TX Interrupt Enable Function.			              *
******************************************************************************/

void UART_voidEnableInterrupt_TX(void){

	SET_BIT(UCSRB, TXCIE);
}


/******************************************************************************
* Description 	: UART TX Interrupt Disable Function.			              *
******************************************************************************/

void UART_voidDisableInterrupt_TX(void){

	CLR_BIT(UCSRB, TXCIE);
}


/******************************************************************************
* Description 	: This function used to	communicate with the function in App  *
*                 Layer(The Callback function UART TX) -                      *
*		          [ Layer Architecture Problem Solved ].                      *
******************************************************************************/

void UART_voidSetCallBack_TX(void(*Local_ptr)(void)){

	UART_TX_CallBack = Local_ptr;

}


/******************************************************************************
* Description 	: This function used to	communicate with the function in App  *
*                 Layer(The Callback function UART RX) -                      *
*		          [ Layer Architecture Problem Solved ].                      *
******************************************************************************/

void UART_voidSetCallBack_RX(void(*Local_ptr)(void)){

	UART_RX_CallBack = Local_ptr;

}


/******************************************************************************
* !comment  :  ISR Function UART TX interrupt.  						      *
******************************************************************************/

ISR( USART_TX_VECTOR ){

	if(UART_TX_CallBack != NULL){

		UART_TX_CallBack();
	}

	else{/* Return error */}
}


/******************************************************************************
* !comment  :  ISR Function UART RX interrupt.  						      *
******************************************************************************/

ISR( USART_RX_VECTOR ){

	if(UART_RX_CallBack != NULL){

		UART_RX_CallBack();
	}

	else{/* Return error */}
}


/******************************************************************************
********************************* END OF PROGRAM ******************************
******************************************************************************/

