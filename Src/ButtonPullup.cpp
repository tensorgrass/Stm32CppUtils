/*
 * ButtonPullup.cpp
 *
 *  Created on: May 24, 2025
 *      Author: froilan
 */

#include <ButtonPullup.hpp>


ButtonPullup::ButtonPullup(GPIO_TypeDef* gpiox_value, uint16_t gpio_pin_value, bool reverse_value) : gpiox(gpiox_value), gpio_pin(gpio_pin_value), reverse(reverse_value) {
  if (reverse_value) {
	estado = 1;
  }
  else {
	estado = 0;
  }
}

ButtonPullup::~ButtonPullup() {
	// TODO Auto-generated destructor stub
}


void ButtonPullup::setEstado(uint8_t estado_valor) {
  estado = estado_valor;
}

uint8_t ButtonPullup::getEstado() {
  return estado;
}

void ButtonPullup::actualizaEstado() {
  estado = HAL_GPIO_ReadPin(gpiox, gpio_pin);
}

bool ButtonPullup::isButtonPressed() {
  if (reverse) {
	  return estado == 0;
  }
  else {
	  return estado == 1;
  }
}
