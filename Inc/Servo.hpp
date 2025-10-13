/*
 * Servo.hpp
 *
 *  Created on: Jun 9, 2025
 *      Author: froilan
 */

#ifndef INC_SERVO_HPP_
#define INC_SERVO_HPP_

#include <cstdint>
#include <stm32f4xx_hal.h>

class Servo {
public:
  Servo(TIM_HandleTypeDef *timer_handle, uint32_t channel);
  ~Servo() = default;

  void setPosition(uint16_t angle);
protected:
  TIM_HandleTypeDef *timer_handle;
  uint32_t channel;
};


#endif /* INC_SERVO_HPP_ */
