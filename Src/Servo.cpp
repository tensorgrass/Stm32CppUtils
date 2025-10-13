/*
 * Servo.cpp
 *
 *  Created on: Jun 9, 2025
 *      Author: froilan
 */
#include "Servo.hpp"

Servo::Servo(TIM_HandleTypeDef *timer_handle_value, uint32_t channel_value) {
  timer_handle = timer_handle_value;
  channel = channel_value;
  //  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1); // Servo 1 (PA0)
  HAL_TIM_PWM_Start(timer_handle_value, channel_value); // Servo 1 (PA0)
  // HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_3 | TIM_CHANNEL_4); // Encoder 1 (PB10, PB11)
//  HAL_TIM_Encoder_Start(timer_handle_value, channel_value); // Encoder 1 (PB10, PB11)
}

/**
  * @brief  Establece el ángulo de un servo.
  * @param  timer_handle: Puntero al manejador del timer (ej. &htim2)
  * @param  channel: Canal del timer (ej. TIM_CHANNEL_1)
  * @param  angle: Ángulo en grados (0 a 180)
  * @retval None
  */
void Servo::setPosition(uint16_t angle) {
    // Mapea el ángulo (0-180) al ancho de pulso en microsegundos.
    // Los valores de 500us a 2500us (0.5ms a 2.5ms) son comunes para 0-180 grados.
    // Ajusta si tu servo tiene un rango diferente.
    // Aquí usamos un rango típico de 1000us a 2000us para 0-180 grados.
    uint32_t pulse_us = 500 + (angle * 2000 / 180);

    // Asegurarse de que el pulso esté dentro de límites seguros para el servo.
    if (pulse_us < 500) pulse_us = 500;
    if (pulse_us > 2500) pulse_us = 2500;

    __HAL_TIM_SET_COMPARE(timer_handle, channel, pulse_us);
}


