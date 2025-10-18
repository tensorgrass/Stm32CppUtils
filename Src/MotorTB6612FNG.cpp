/*
 * MotorTB6612FNG.cpp
 *
 *  Created on: Jun 9, 2025
 *      Author: froilan
 */
#include "MotorTB6612FNG.hpp"

MotorTB6612FNG::MotorTB6612FNG(TIM_HandleTypeDef *htim_value, uint32_t channel_value,
		                       GPIO_TypeDef* gpio_peripheral_in1_value, uint16_t gpio_pin_in1_value,
							   GPIO_TypeDef* gpio_peripheral_in2_value, uint16_t gpio_pin_in2_value) {
  htim = htim_value;
  channel = channel_value;
  gpio_peripheral_in1 = gpio_peripheral_in1_value;
  gpio_pin_in1 = gpio_pin_in1_value;
  gpio_peripheral_in2 = gpio_peripheral_in2_value;
  gpio_pin_in2 = gpio_pin_in2_value;
  HAL_TIM_PWM_Start(htim_value, channel_value); // MotorTB6612FNG 1 (PA0)
}

void MotorTB6612FNG::setSpeed(int16_t speed) {

  if (speed > 0) // Hacia adelante
  {
	HAL_GPIO_WritePin(gpio_peripheral_in1, gpio_pin_in1, GPIO_PIN_SET);   // AIN1 HIGH
	HAL_GPIO_WritePin(gpio_peripheral_in2, gpio_pin_in2, GPIO_PIN_RESET); // AIN2 LOW
  }
  else if (speed < 0) // Marcha atrás
  {
	HAL_GPIO_WritePin(gpio_peripheral_in1, gpio_pin_in1, GPIO_PIN_RESET); // AIN1 LOW
	HAL_GPIO_WritePin(gpio_peripheral_in2, gpio_pin_in2, GPIO_PIN_SET);   // AIN2 HIGH
  }
  else // Frenar
  {
	HAL_GPIO_WritePin(gpio_peripheral_in1, gpio_pin_in1, GPIO_PIN_SET);   // AIN1 HIGH
	HAL_GPIO_WritePin(gpio_peripheral_in2, gpio_pin_in2, GPIO_PIN_SET);   // AIN2 HIGH
  }

  uint32_t pulse_us = map_motor_values(abs(speed), 0, 100, MIN_FREQ_US, MAX_FREQ_US);
  if (pulse_us < MIN_FREQ_US) pulse_us = MIN_FREQ_US;
  if (pulse_us > MAX_FREQ_US) pulse_us = MAX_FREQ_US;
  __HAL_TIM_SET_COMPARE(htim, channel, pulse_us);

}

uint32_t MotorTB6612FNG::map_motor_values(uint32_t speed, uint32_t min_speed, uint32_t max_speed, uint32_t min_frequence_us, uint32_t max_frequence_us){
	return ((((speed - min_speed)*(max_frequence_us - min_frequence_us))/(max_speed - min_speed)) + min_frequence_us);
}

void MotorTB6612FNG::disable() {
	setSpeed(0);
}



