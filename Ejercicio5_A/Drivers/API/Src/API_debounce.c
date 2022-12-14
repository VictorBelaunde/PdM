/**
 ******************************************************************************
	API para incializar, contabilizar y resetear el retardo
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/

#include "API_debounce.h"
#include "API_delay.h" //necesita de esta API para trabajar con retardos

static delay_t delay_estados;
static bool_t fallingOk = false; //variable para detectar que occurrió un flanco descendente
static debounceState_t estadoActual;

void debounceFSM_init(){
	estadoActual = BUTTON_UP;
	delayInit(&delay_estados, RETARDO);
}

void debounceFSM_update(){
	switch (estadoActual){
	case BUTTON_UP:
		if (BSP_PB_GetState(BUTTON_USER)){
			estadoActual = BUTTON_FALLING;
			delayRead(&delay_estados);
		}
		break;

	case BUTTON_FALLING:
		if (delayRead(&delay_estados)){
			if (BSP_PB_GetState(BUTTON_USER)){
				estadoActual = BUTTON_DOWN;
				fallingOk = true;

			}
			else{
				estadoActual = BUTTON_UP;
			}
		}
		break;
	case BUTTON_DOWN:
		if (!BSP_PB_GetState(BUTTON_USER)){
			estadoActual = BUTTON_RAISING;
			delayRead(&delay_estados);
		}
		break;
	case BUTTON_RAISING:
		if (delayRead(&delay_estados)){
			if (!BSP_PB_GetState(BUTTON_USER)){
				estadoActual = BUTTON_UP;

			}
			else{
				estadoActual = BUTTON_DOWN;
			}
		}
		break;

	}

}

/* La función readKey lee una variable interna del módulo y devuelve true o false
 * si la tecla fue presionada.  Si devuelve true, resetea (pone en false) el estado
 * de la variable.*/

bool_t readKey_descendente(){
	bool_t returnValue = false;
			if (fallingOk){
				fallingOk = false;
				returnValue = true;
			}
	return returnValue;
}


