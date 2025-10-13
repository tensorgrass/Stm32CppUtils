/*
 * MotorOneShot125.cpp
 *
 *  Created on: May 30, 2025
 *      Author: froilan
 */

#include "MotorOneShot125.hpp"

MotorOneShot125::MotorOneShot125(TIM_HandleTypeDef* htim_value, unsigned int channel_value, __IO uint32_t* channel_address_value) : htim(htim_value), channel(channel_value), channel_address(channel_address_value) {
    HAL_TIM_PWM_Start(htim, channel);
}

uint32_t MotorOneShot125::map_esc_values(uint32_t au32_IN, uint32_t au32_INmin, uint32_t au32_INmax, uint32_t au32_OUTmin, uint32_t au32_OUTmax)
{
    return ((((au32_IN - au32_INmin)*(au32_OUTmax - au32_OUTmin))/(au32_INmax - au32_INmin)) + au32_OUTmin);
}

void MotorOneShot125::setSpeed(uint32_t motor_speed_value)
{
    motor_speed = motor_speed_value;
    uint32_t esc_speed = map_esc_values(motor_speed, ESC_START, ESC_END, COUNTER_PERIOD_START, COUNTER_PERIOD_END);
    *channel_address = esc_speed;
}

