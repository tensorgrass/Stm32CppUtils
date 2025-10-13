#include "ADCBase.hpp"

ADCBase::ADCBase(ADC_HandleTypeDef* hadc_handler_value)
    : hadc_handler(hadc_handler_value) {
  HAL_ADC_Start_DMA(hadc_handler, (uint32_t*)adc_values, NUM_ADC_CHANNELS);
}

ADCBase::~ADCBase() {
  // Destructor implementation
}

// Add public method implementations here
uint16_t  ADCBase::readChannel(uint8_t channel) {
  if (channel < NUM_ADC_CHANNELS) {
    return adc_values[channel];
  }
  return 0; // Return 0 if the channel is out of range
}
// Add protected member implementations here

// Add private member implementations here
