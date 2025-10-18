/*
 * MotorTB6612FNG.hpp
 *
 *  Created on: Jun 9, 2025
 *      Author: froilan
 */

#ifndef INT_MOTORTB6612FNG_HPP_
#define INT_MOTORTB6612FNG_HPP_

#define MIN_FREQ_US 500
#define MAX_FREQ_US 20000

#include <cstdint>
#include <stm32f4xx_hal.h>
#include <cmath>

class MotorTB6612FNG {
public:
  MotorTB6612FNG(TIM_HandleTypeDef *htim_value, uint32_t channel_value,
		         GPIO_TypeDef* gpio_peripheral_in1_value, uint16_t gpio_pin_in1_value,
				 GPIO_TypeDef* gpio_peripheral_in2_value, uint16_t gpio_pin_in2_value);
  ~MotorTB6612FNG() = default;

  void setSpeed(int16_t speed); //speed = 0 - 100
  uint32_t map_motor_values(uint32_t speed, uint32_t min_speed, uint32_t max_speed, uint32_t min_frequence_us, uint32_t max_frequence_us);
  void disable(); //speed = 0 - 100
protected:
  TIM_HandleTypeDef *htim;
  uint32_t channel;
  GPIO_TypeDef* gpio_peripheral_in1;
  uint16_t gpio_pin_in1;
  GPIO_TypeDef* gpio_peripheral_in2;
  uint16_t gpio_pin_in2;

};


#endif /* INT_MOTORTB6612FNG_HPP_ */
