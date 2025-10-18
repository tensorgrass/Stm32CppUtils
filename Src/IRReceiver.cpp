/*
 * IRReceiver.cpp
 *
 *  Created on: May 24, 2025
 *      Author: froilan
 */

#include <IRReceiver.hpp>


IRReceiver::IRReceiver(TIM_HandleTypeDef* htim_value, uint32_t channel_value) : htim(htim_value), channel(channel_value) {
  is_data_ready = false;
  decoded_data = 0;
  HAL_TIM_IC_Start_IT(htim, channel);
}

IRReceiver::~IRReceiver() {
	// TODO Auto-generated destructor stub
}

void IRReceiver::adquireData() {
  uint32_t ir_current_value_ms = 0;
  uint32_t ir_diference_ms = 0;
  ir_current_value_ms = HAL_TIM_ReadCapturedValue(htim, channel);
  ir_diference_ms = ir_current_value_ms - ir_previous_value_ms;
  ir_previous_value_ms = ir_current_value_ms;

  if (ir_diference_ms > PULSE_BETWEEN_COMM_MIN) {
    __HAL_TIM_SET_COUNTER(htim, 0);
    ir_previous_value_ms = 0;
    ir_step = START_PULSE_BRUST;
  }
  else {
    switch(ir_step){
    case (START_PULSE_BRUST):
      if (START_PULSE_BRUST_MIN_MS < ir_diference_ms && ir_diference_ms < START_PULSE_BRUST_MAX_MS) { //9 ms
        ir_step = SPACE_SELECTOR;
      }
      else {
        ir_step = ERROR_VALUE;
        is_valid_value = false;
      }
      break;
    case (SPACE_SELECTOR):
      if (SPACE_SELECTOR_FULL_VALUE_MIN_MS < ir_diference_ms && ir_diference_ms < SPACE_SELECTOR_FULL_VALUE_MAX_MS) {// 4.5ms full value
        ir_step = FULL_VALUE_PULSE_BRUST;
        ir_value_position = 0;
        decoded_data_tmp = 0;
        value_repetitions = 0;
      }
      else if (SPACE_SELECTOR_REPEAT_VALUE_MIN_MS < ir_diference_ms && ir_diference_ms < SPACE_SELECTOR_REPEAT_VALUE_MAX_MS) {// 2.25ms repeat code
        if (is_valid_value) {
          ir_step = REPETITION_VALUE_PULSE_BRUST;
        }
        else {
          ir_step = ERROR_VALUE;
          is_valid_value = false;
        }
      }
      else {
        ir_step = ERROR_VALUE;
        is_valid_value = false;
      }
      break;
    case (FULL_VALUE_PULSE_BRUST):
      if (FULL_VALUE_PULSE_BRUST_MIN_MS < ir_diference_ms && ir_diference_ms < FULL_VALUE_PULSE_BRUST_MAX_MS) { // 0.5625ms
        if (ir_value_position == NUM_BITS_VALUE){
          ir_step = END_FULL_VALUE;
          decoded_data = decoded_data_tmp;
          is_valid_value = true;
        }
        else {
          ir_step = FULL_VALUE;
        }
      }
      else {
        ir_step = ERROR_VALUE;
        is_valid_value = false;
      }
      break;
    case (FULL_VALUE):
      if (FULL_VALUE_ONE_MIN_MS < ir_diference_ms && ir_diference_ms < FULL_VALUE_ONE_MAX_MS) { //1.6875ms para los 1
        decoded_data_tmp |= (1UL << (NUM_BITS_VALUE - ir_value_position - 1) );
        ir_value_position++;
        ir_step = FULL_VALUE_PULSE_BRUST;
      }
      else if (FULL_VALUE_ZERO_MIN_MS < ir_diference_ms && ir_diference_ms < FULL_VALUE_ZERO_MAX_MS) { //0.5625ms para los 0
        ir_value_position++;
        ir_step = FULL_VALUE_PULSE_BRUST;
        //no hace falta poner el valor ya que está a cero
      }
      else {
        ir_step = ERROR_VALUE;
        is_valid_value = false;
      }
      break;
    case (REPETITION_VALUE_PULSE_BRUST):
      if (REPETITION_VALUE_PULSE_BRUST_MIN_MS < ir_diference_ms && ir_diference_ms < REPETITION_VALUE_PULSE_BRUST_MAX_MS) { // 0.5625ms
        ir_step = END_REPETITION_VALUE;  //envia un solo pulso y no hace nada mas
        value_repetitions++;
      }
      else {
        ir_step = ERROR_VALUE;
        is_valid_value = false;
      }
      break;
    case (END_FULL_VALUE): //si llega al final y hay mas datos es que hay algun error
    case (END_REPETITION_VALUE):
    default:
      ir_step = ERROR_VALUE;
      is_valid_value = false;
      break;
    }
  }

//  if (ir_step == END_FULL_VALUE || ir_step == END_REPETITION_VALUE) // Si ya capturamos todos los bits
  if (ir_step == END_FULL_VALUE) // Si ya capturamos todos los bits
  {
    is_data_ready = true;
    HAL_TIM_IC_Stop_IT(htim, channel); // Detenemos para procesar
  }
}

bool IRReceiver::isDataReady() {
  return is_data_ready;
}

uint32_t IRReceiver::getValue() {
  is_data_ready = false;
  HAL_TIM_IC_Start_IT(htim, channel);
  return decoded_data;
}
