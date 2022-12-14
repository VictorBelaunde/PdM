/**
 ******************************************************************************
	API para incializar, contabilizar y resetear el retardo
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/

#include "API_delay.h"


// Inicializa el retardo con la duracion como parametro

void delayInit( delay_t *delay, tick_t duration){
	if (delay != 0 && duration > 0 && duration < MAXDELAY){
		delay->duration = duration;
		delay->running = false;
	}
	else {
		while (1);
	}
}


// Funcion para determinar que finalizó el retardo,
// devolviendo verdadero en estarlo

bool_t delayRead( delay_t *delay ){
	bool_t finish = false;
	uint32_t duracion_actual;
	uint32_t cuenta_duracion;

	if (delay->running == false){
		delay->running = true;
		delay->startTime = HAL_GetTick(); //Funcion para obtener una marca de tiempo
	}
	else {
		duracion_actual = HAL_GetTick();
		cuenta_duracion = duracion_actual - delay->startTime;
		if (cuenta_duracion > delay->duration){
			finish = true;
			delay->running = false;

		}
	}
	return finish;
}

//Funcion para redefinir el retardo

void delayWrite( delay_t *delay, tick_t duration ){
	delay->duration = duration;
}
