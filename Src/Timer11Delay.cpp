/*
 * Timer11Delay.cpp
 *
 *  Created on: May 30, 2025
 *      Author: froilan
 */

#include "Timer11Delay.hpp"

Timer11Delay::Timer11Delay(TIM_HandleTypeDef *htim3_value) : htim11(htim3_value) {
  HAL_TIM_Base_Start(htim11);
}

void Timer11Delay::delay(uint32_t time_ms) {
  // Asegurarse de que el contador esté en 0 antes de empezar
  __HAL_TIM_SET_COUNTER(htim11, 0);

  // Iniciar el contador (si no está ya activo)
  // Es buena práctica iniciar el timer base al principio del programa y dejarlo corriendo.
  // Si ya lo iniciaste en MX_TIM2_Init(), no necesitas hacerlo aquí.
//  HAL_TIM_Base_Start(htim11);

  // int max_time_ms = 65535; // Valor máximo para un uint16_t
  uint16_t num_max_value = 0;
  uint16_t time_ms16 = 0;
  time_ms *= 1000;
  if (time_ms > UINT16_MAX) {
    num_max_value = static_cast<uint16_t>(time_ms / UINT16_MAX); // Número de veces que el valor máximo cabe en el tiempo
    time_ms16 = static_cast<uint16_t>(time_ms % UINT16_MAX); // Resto del tiempo que no cabe en el valor máximo
  } else {
    time_ms16 = static_cast<uint16_t>(time_ms); // Si el tiempo es menor o igual al valor máximo, lo convertimos directamente
  }


  uint16_t counter = static_cast<uint16_t>(__HAL_TIM_GET_COUNTER(htim11));
  uint16_t counter_previous = 0;
  while (num_max_value > 0) {
    while (counter_previous <= counter) {
      counter_previous = counter;
      counter = static_cast<uint16_t>(__HAL_TIM_GET_COUNTER(htim11));
    }
    num_max_value--;
    counter_previous = counter;
  }

  // Esperar hasta que el contador alcance el valor deseado
  while (static_cast<uint16_t>(__HAL_TIM_GET_COUNTER(htim11)) < time_ms16)
  {

  }

  // El contador sigue funcionando después de salir del bucle.
  // Si quieres detenerlo para ahorrar energía o reutilizarlo:
  //  HAL_TIM_Base_Stop(htim11);
}

void Timer11Delay::delay2(uint32_t time_ms, UartSerial* uartSerial) {
    // Asegurarse de que el contador esté en 0 antes de empezar
    __HAL_TIM_SET_COUNTER(htim11, 0);

    // Iniciar el contador (si no está ya activo)
    // Es buena práctica iniciar el timer base al principio del programa y dejarlo corriendo.
    // Si ya lo iniciaste en MX_TIM2_Init(), no necesitas hacerlo aquí.
    HAL_TIM_Base_Start(htim11);

    // int max_time_ms = 65535; // Valor máximo para un uint16_t
    uint16_t num_max_value = 0;
    uint16_t time_ms16 = 0;
    time_ms *= 1000;
    if (time_ms > UINT16_MAX) {
      num_max_value = static_cast<uint16_t>(time_ms / UINT16_MAX); // Número de veces que el valor máximo cabe en el tiempo
      time_ms16 = static_cast<uint16_t>(time_ms % UINT16_MAX); // Resto del tiempo que no cabe en el valor máximo
    } else {
      time_ms16 = static_cast<uint16_t>(time_ms); // Si el tiempo es menor o igual al valor máximo, lo convertimos directamente
    }


    uint16_t counter = static_cast<uint16_t>(__HAL_TIM_GET_COUNTER(htim11));
    uint16_t counter_previous = 0;
    while (num_max_value > 0) {
      while (counter_previous <= counter) {
        uartSerial->bufferln(std::to_string(counter));
        counter_previous = counter;
        counter = static_cast<uint16_t>(__HAL_TIM_GET_COUNTER(htim11));
      }
      num_max_value--;
      counter_previous = counter;
    }
    // Esperar hasta que el contador alcance el valor deseado
    while (counter < time_ms16)
    {
      counter = static_cast<uint16_t>(__HAL_TIM_GET_COUNTER(htim11));
      uartSerial->bufferln(std::to_string(counter));
    }

    // El contador sigue funcionando después de salir del bucle.
    // Si quieres detenerlo para ahorrar energía o reutilizarlo:
    HAL_TIM_Base_Stop(htim11);
}
