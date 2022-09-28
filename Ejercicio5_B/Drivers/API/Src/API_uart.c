/*******************************************************************************
 * @file    API_uart.c
 * @author  Victor Belaunde
 * @brief   Modulo para incializar e imprimir por el puerto UART
 *******************************************************************************/


/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "API_uart.h"

/*******************************************************************************
 * Function prototypes
 ******************************************************************************/


/*******************************************************************************
 * Private global variables
 ******************************************************************************/
static UART_HandleTypeDef UartHandle;
uint16_t tamaño_maximo_mensaje = 500; //Configuro el tamaño maximo del mensaje que imprime por UART
const uint32_t tiempo_max_espera = 1000; //Se define el tiempo antes de timeOut


/**
 * @brief	funcion que inicializa la UART
 * @param	none
 * @return	verdadero si inicio correctamente
 */
bool_t uartInit(){
	/* UART configured as follows:
	      - Word Length = 8 Bits (7 data bit + 1 parity bit) :
		                  BE CAREFUL : Program 7 data bits + 1 parity bit in PC HyperTerminal
	      - Stop Bit    = One Stop bit
	      - Parity      = ODD parity
	      - BaudRate    = 9600 baud
	      - Hardware flow control disabled (RTS and CTS signals) */
	UartHandle.Instance        = USARTx;
	UartHandle.Init.BaudRate   = 9600;
	UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	UartHandle.Init.StopBits   = UART_STOPBITS_1;
	UartHandle.Init.Parity     = UART_PARITY_ODD;
	UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
	UartHandle.Init.Mode       = UART_MODE_TX_RX;
	UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;
	bool_t init_uart_ok = false;

	if (HAL_UART_Init(&UartHandle) == HAL_OK)
	{
		init_uart_ok = true;
		printf("Inicializacion exitosa");

	}

	return init_uart_ok;
}


/**
 * @brief	funcion que transmite un mensaje por UART
 * @param	puntero a la cadena que envia
 * @return	none
 */
void uartSendString(uint8_t * pstring){

	if (pstring != NULL){
		uint16_t tamaño_mensaje = (uint16_t) strlen((char *) pstring); //Calcula el tamaño del mensaje

		HAL_UART_Transmit(&UartHandle, pstring, tamaño_mensaje, tiempo_max_espera);
	}

}

/**
 * @brief	funcion que transmite un mensaje por UART acotado por una cantidad de caracteres
 * @param	puntero a la cadena que envia y cantidad de caracteres
 * @return	none
 */
void uartSendStringSize(uint8_t * pstring, uint16_t size){

	if (pstring!= NULL){
		uint16_t tamaño_mensaje = (uint16_t) strlen((char *) pstring); //Calcula el tamaño del mensaje
		if (size > tamaño_mensaje){
			size = tamaño_mensaje;
		}
		if (size > tamaño_maximo_mensaje){
			size = tamaño_maximo_mensaje;
		}
		HAL_UART_Transmit(&UartHandle, pstring, size, tiempo_max_espera);
	}

}

void uartReceiveStringSize(uint8_t * pstring, uint16_t size){

	HAL_UART_Receive(&UartHandle, pstring, size, tiempo_max_espera);

}


