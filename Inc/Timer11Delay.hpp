/*
 * Timer11Delay.hpp
 *
 *  Created on: May 30, 2025
 *      Author: froilan
 */

#ifndef INC_TIMER11DELAY_HPP_
#define INC_TIMER11DELAY_HPP_

#include <cstdint>
#include <stm32f4xx_hal.h>
#include <UartSerial.hpp>

class Timer11Delay {
public:
    Timer11Delay(TIM_HandleTypeDef* htim11_value);
    void delay(uint32_t time_ms);
    void delay2(uint32_t time_ms, UartSerial* uartSerial);
private:
    TIM_HandleTypeDef* htim11;
};


#endif /* INC_TIMER11DELAY_HPP_ */
