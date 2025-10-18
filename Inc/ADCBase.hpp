#ifndef INC_ADC_HPP_
#define INC_ADC_HPP_

#include <stm32f4xx_hal.h>
#include <cstdint>

// #define NUM_ADC_CHANNELS    6 // Número de canales ADC que estamos leyendo (PA1, PA5, P0, P7, P4, P6)

class ADCBase {
  // This class is responsible for handling analog to digital conversion
  // and may include methods for reading analog values, converting them,
  // and possibly interfacing with hardware components.
public:
  ADCBase(ADC_HandleTypeDef* hadc_handler_value, uint16_t* adc_values_value, uint16_t num_adc_channels_value);
  virtual ~ADCBase();

  // Add public methods here
  uint16_t readChannel(uint8_t channel);
protected:
  // Add protected members here

private:
  ADC_HandleTypeDef *hadc_handler;
//  uint16_t adc_values[NUM_ADC_CHANNELS];
  uint16_t* adc_values;
  uint16_t num_adc_channels;
};

#endif /* INC_ADC_HPP_ */
