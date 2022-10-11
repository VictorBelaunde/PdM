# PdM
Repositorio presentar el Trabajo final de la materia Programación de Microcontroladores

Alumno: Victor Belaunde

Se desarrollará una solución que tome como referencia una variable global que contiene el resultado de un sensor de temperatura (en esta instancia del proyecto será hard-codeado por terminal serie) y que llame a varias funciones para controlar un ambiente climatizado para mantener un rango determinado de ºC a través de activación de ventiladores (refrigeración) o turbinas de resistencia (calefacción) según sea conveniente. Este sistema tiene como fin controlar la temperatura de un ambiente adaptado para el cultivo de plantas medicinales.
Si el valor sensado (llega la información por UART) rompe con el umbral superior se activa el mecanismo identificado para reducir ese valor. En cambio si lo hace sobre el umbral inferior se activa el mecanismo opuesto para aumentar el valor.

Periféricos: UART y GPIO.

La MEF tendrá cuatro estados.
typedef enum{
CALIBRACIÓN,
FRÍO,
CÁLIDO,
REPOSO,
} ClimaState_t

Se trabajaron con cinco modulos:
API_activadores: Para controlar la activación y desactivación de los motores que impulsan la calefacción o refrigeración.
API_clima: Para manejar una MEF con estados del clima.
API_delay: Para obtener un delay no bloqueante y permita tomar mediciones de temperatura cada 5seg.
API_toma_temp: Para abstraernos del medio o sensor que obtiene los ºC del ambiente.
API_uart: Para comunicarnos vía monitor serie e ingresar la temperatura sensada en modo hardcode. Convierte char a número.


 
