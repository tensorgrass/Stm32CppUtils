/*
 * LedBase.h
 *
 *  Created on: May 24, 2025
 *      Author: froilan
 */

#ifndef LEDBASE_H_
#define LEDBASE_H_

#include <stm32f4xx_hal.h>


class LedBase  {
public:
  LedBase(GPIO_TypeDef* gpiox_value, uint16_t gpio_pin_value, bool reverse_value);
  virtual ~LedBase();

  void turn_on();
  void turn_off();
  bool get_status();

private:
  GPIO_TypeDef* gpiox;
  uint16_t gpio_pin;
  bool led_status;
  bool reverse;
};

#endif /* LEDBASE_H_ */
