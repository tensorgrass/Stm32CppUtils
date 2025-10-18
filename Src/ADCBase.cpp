#include "ADCBase.hpp"

ADCBase::ADCBase(ADC_HandleTypeDef* hadc_handler_value, uint16_t* adc_values_value, uint16_t num_adc_channels_value)
    : hadc_handler(hadc_handler_value), adc_values(adc_values_value), num_adc_channels(num_adc_channels_value) {
  HAL_ADC_Start_DMA(hadc_handler, (uint32_t*)adc_values, num_adc_channels);
}

ADCBase::~ADCBase() {
  // Destructor implementation
}

// Add public method implementations here
uint16_t  ADCBase::readChannel(uint8_t channel) {
  if (channel < num_adc_channels) {
    return adc_values[channel];
  }
  return 0; // Return 0 if the channel is out of range
}
// Add protected member implementations here

// Add private member implementations here
