/**
 ******************************************************************************
	Programa para consumir la API de retardo no bloqueantes
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

//Define publicas
#define RETARDO 40 //Valor de retardo para utilizado para delay no bloqueante

typedef enum{
	BUTTON_UP,
	BUTTON_FALLING,
	BUTTON_DOWN,
	BUTTON_RAISING,
	} debounceState_t;

debounceState_t estadoActual;

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Initialize BSP Led for LED1 */
uint8_t led;
uint8_t led_array[2] = {LED1,LED3};
delay_t delay_estados;

/* Private function prototypes -----------------------------------------------*/

static void SystemClock_Config(void);
static void Error_Handler(void);

void debounceFSM_init();		// Cargar el estado inicial de la MEF
void debounceFSM_update();	// Lee las entradas y resuelve la lógica de transición de estados

void buttonPressed();			// Togglear el LED1
void buttonReleased();		// Togglear el LED3

/* Private functions ---------------------------------------------------------*/

void debounceFSM_init(){
	estadoActual = BUTTON_UP;
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
				buttonPressed();
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
				buttonReleased();
			}
			else{
				estadoActual = BUTTON_DOWN;
			}
		}
		break;

	}

}

void buttonPressed(){
	BSP_LED_Toggle(LED1);
}

void buttonReleased(){
	BSP_LED_Toggle(LED3);
}

/**
 * @brief  Main program
 * @param  None
 * @retval None
 */
int main(void)
{
	/* Practica para Implementar una MEF anti-rebote que permita leer el estado del pulsador
	 * de la placa NUCLEO-F429ZI y generar acciones o eventos ante un flanco descendente o ascendente,
	 * de acuerdo a un determinado diagrama
	 */

	HAL_Init();
	/* Configure the system clock to 180 MHz */
	SystemClock_Config();



	BSP_LED_Init(LED1);
	BSP_LED_Init(LED3);
	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);

	delayInit (&delay_estados, RETARDO);



	while (1) {
		debounceFSM_update();

	}


}


static void SystemClock_Config(void)
{
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_OscInitTypeDef RCC_OscInitStruct;

	/* Enable Power Control clock */
	__HAL_RCC_PWR_CLK_ENABLE();

	/* The voltage scaling allows optimizing the power consumption when the device is
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	/* Enable HSE Oscillator and activate PLL with HSE as source */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 8;
	RCC_OscInitStruct.PLL.PLLN = 360;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 7;
	if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		/* Initialization Error */
		Error_Handler();
	}

	if(HAL_PWREx_EnableOverDrive() != HAL_OK)
	{
		/* Initialization Error */
		Error_Handler();
	}

	/* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
	if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
	{
		/* Initialization Error */
		Error_Handler();
	}
}
/**
 * @brief  This function is executed in case of error occurrence.
 * @param  None
 * @retval None
 */
static void Error_Handler(void)
{
	/* Turn LED2 on */
	BSP_LED_On(LED2);
	while (1)
	{
	}
}

#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
	/* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	/* Infinite loop */
	while (1)
	{
	}
}
#endif

/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
