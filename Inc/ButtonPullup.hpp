/*
 * ButtonPullup.h
 *
 *  Created on: May 24, 2025
 *      Author: froilan
 */

#ifndef BUTTONPULLUP_H_
#define BUTTONPULLUP_H_

#include <stm32f4xx_hal.h>


class ButtonPullup  {
public:
  ButtonPullup(GPIO_TypeDef* gpiox_value, uint16_t gpio_pin_value, bool reverse_value);
  virtual ~ButtonPullup();

  virtual void setEstado(uint8_t estado_valor);
  virtual uint8_t getEstado();
  virtual void actualizaEstado();
  virtual bool isButtonPressed();

private:
  GPIO_TypeDef* gpiox;
  uint16_t gpio_pin;
  uint8_t estado = 0;
  bool reverse = false;
};

#endif /* BUTTONPULLUP_H_ */
