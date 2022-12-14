/*******************************************************************************
* @file    API_uart.h
* @author  Victor Belaunde
* @brief   Modulo para incializar e imprimir por el puerto UART
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __API_UART_H
#define __API_UART_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */
#include <stdint.h>
#include <stdbool.h>
#include <string.h>  //para incluir la funcion strlen()
#include "main.h"

/*******************************************************************************
 * Defines
 ******************************************************************************/

/* Definition for USARTx Pins */
#define USARTx_TX_PIN                    GPIO_PIN_8
#define USARTx_TX_GPIO_PORT              GPIOD
#define USARTx_TX_AF                     GPIO_AF7_USART3
#define USARTx_RX_PIN                    GPIO_PIN_9
#define USARTx_RX_GPIO_PORT              GPIOD
#define USARTx_RX_AF                     GPIO_AF7_USART3

/*******************************************************************************
 * Variables y constantes
 ******************************************************************************/


typedef uint32_t tick_t;
typedef bool bool_t;

/*******************************************************************************
 * Function prototypes
 ******************************************************************************/
bool_t uartInit();
void uartSendString(uint8_t * pstring);
void uartSendStringSize(uint8_t * pstring, uint16_t size);
void uartReceiveStringSize(uint8_t * pstring, uint16_t size);



#endif /* __API_UART_H */

