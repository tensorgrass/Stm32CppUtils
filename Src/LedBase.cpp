/*
 * LedBase.cpp
 *
 *  Created on: May 24, 2025
 *      Author: froilan
 */

#include <LedBase.hpp>


LedBase::LedBase(GPIO_TypeDef* gpiox_value, uint16_t gpio_pin_value, bool reverse_value) : gpiox(gpiox_value), gpio_pin(gpio_pin_value), reverse(reverse_value) {
  turn_off();
}

LedBase::~LedBase() {
	// TODO Auto-generated destructor stub
}


void LedBase::turn_on() {
  led_status = 1;
  if (!reverse) {
    HAL_GPIO_WritePin(gpiox, gpio_pin, GPIO_PIN_SET);
  }
  else {
    HAL_GPIO_WritePin(gpiox, gpio_pin, GPIO_PIN_RESET);
  }

}

void LedBase::turn_off() {
  led_status = 0;
  if (!reverse) {
    HAL_GPIO_WritePin(gpiox, gpio_pin, GPIO_PIN_RESET);
  }
  else {
    HAL_GPIO_WritePin(gpiox, gpio_pin, GPIO_PIN_SET);
  }
}

bool LedBase::get_status() {
  return led_status;
}
