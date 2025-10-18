/*
 * IRReceiver.h
 *
 *  Created on: May 24, 2025
 *      Author: froilan
 */

#ifndef IRRECEIVER_H_
#define IRRECEIVER_H_

#include <stm32f4xx_hal.h>


#define PULSE_BETWEEN_COMM_MIN 10000
#define START_PULSE_BRUST_MIN_MS 8500
#define START_PULSE_BRUST_MAX_MS 9250
#define SPACE_SELECTOR_FULL_VALUE_MIN_MS 4250
#define SPACE_SELECTOR_FULL_VALUE_MAX_MS 4750
#define SPACE_SELECTOR_REPEAT_VALUE_MIN_MS 2000
#define SPACE_SELECTOR_REPEAT_VALUE_MAX_MS 2500
#define FULL_VALUE_PULSE_BRUST_MIN_MS 320
#define FULL_VALUE_PULSE_BRUST_MAX_MS 812
#define FULL_VALUE_ONE_MIN_MS 1437
#define FULL_VALUE_ONE_MAX_MS 1937
#define FULL_VALUE_ZERO_MIN_MS 312
#define FULL_VALUE_ZERO_MAX_MS 812
#define REPETITION_VALUE_PULSE_BRUST_MIN_MS 320
#define REPETITION_VALUE_PULSE_BRUST_MAX_MS 812
#define NUM_BITS_VALUE 32

class IRReceiver  {
public:
  IRReceiver(TIM_HandleTypeDef* htim_value, uint32_t channel_value);
  virtual ~IRReceiver();

  virtual void adquireData();
  virtual bool isDataReady();
  virtual uint32_t getValue();


private:
  TIM_HandleTypeDef *htim;
  uint32_t channel;

  bool is_data_ready;
  uint32_t decoded_data;

  enum enum_ir_protocol {
     START_PULSE_BRUST,
     SPACE_SELECTOR,
     FULL_VALUE_PULSE_BRUST,
     FULL_VALUE,
     REPETITION_VALUE_PULSE_BRUST,
     END_FULL_VALUE,
     END_REPETITION_VALUE,
     ERROR_VALUE
  };

  enum_ir_protocol ir_step;
  uint32_t ir_previous_value_ms;
  bool is_valid_value;
  uint8_t ir_value_position;
  uint32_t decoded_data_tmp;
  uint32_t value_repetitions;

};

#endif /* IRRECEIVER_H_ */
