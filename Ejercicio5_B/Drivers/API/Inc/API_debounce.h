/*
 ******************************************************************************
	Prototipos de funciones publicas anti-rebote
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __API_DEBOUNCE_H
#define __API_DEBOUNCE_H

#define RETARDO 40

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */
#include <stdint.h>
#include <stdbool.h>

/* Declración de variables publicas */

typedef bool bool_t;

typedef enum{
	BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RAISING,
} debounceState_t;


bool_t readKey_descendente(); //funcion interna del módulo para devuelve si fue oresionado de forma descendente
bool_t readKey_ascendente(); //funcion interna del módulo para devuelve si se presioné de forma ascendente

/* Exported functions ------------------------------------------------------- */
void debounceFSM_init();	// Carga el estado inicial de la MEF
void debounceFSM_update();	// Lee las entradas y resuelve la lógica de transición de estados




#endif /* __API_DEBOUNCE_H */

