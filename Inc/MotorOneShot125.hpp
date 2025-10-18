/*
 * MotorOneShot125.hpp
 *
 *  Created on: May 30, 2025
 *      Author: froilan
 */

#ifndef INC_MOTORONESHOT125_HPP_
#define INC_MOTORONESHOT125_HPP_

#define ESC_MID 1920//1830-2000
#define ESC_BACKWARD 1790
#define ESC_FORWARD 2050
#define ESC_BACKWARD_MIN 1690//3000 // Minimum PWM value for ESC
#define ESC_FORWARD_MAX 2150//3000 // Minimum PWM value for ESC
#define ESC_INC 10 // Minimum PWM value for ESC

#define ESC_START 0
#define ESC_END 4095
#define COUNTER_PERIOD_START 12500 // COUNTER_PERIOD_END / 2
#define COUNTER_PERIOD_END 25000 //

#include <cstdint>
#include <stm32f4xx_hal.h>
#include <UartSerial.hpp>

class MotorOneShot125 {
public:
    MotorOneShot125(TIM_HandleTypeDef* htim_value, unsigned int channel_value, __IO uint32_t* channel_address_value);
    uint32_t map_esc_values(uint32_t au32_IN, uint32_t au32_INmin, uint32_t au32_INmax, uint32_t au32_OUTmin, uint32_t au32_OUTmax);
    void setSpeed(uint32_t motor_speed_value);
    void disable();
private:
    TIM_HandleTypeDef* htim;
    unsigned int channel;
    __IO uint32_t* channel_address;
    uint32_t motor_speed;
    uint32_t channel_address_disable;
};


#endif /* INC_MOTORONESHOT125_HPP_ */
