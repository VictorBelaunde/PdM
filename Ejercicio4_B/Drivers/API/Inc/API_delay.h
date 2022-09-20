/*
  ******************************************************************************
	Prototipos de funciones publicas para medir el retardo
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __API_DELAY_H
#define __API_DELAY_H

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */
#include <stdint.h>
#include <stdbool.h>

/* Exported functions ------------------------------------------------------- */
#define MAXDELAY 30000
typedef uint32_t tick_t;
typedef bool bool_t;
typedef struct{
   tick_t startTime;
   tick_t duration;
   bool_t running;
} delay_t;

void delayInit(delay_t *delay, tick_t duration);
bool_t delayRead(delay_t *delay );
void delayWrite(delay_t *delay, tick_t duration);


#endif /* __API_DELAY_H */

