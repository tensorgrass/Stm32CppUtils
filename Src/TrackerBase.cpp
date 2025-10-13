#include <TrackerBase.hpp>

TrackerBase::TrackerBase(ADCBase* adc_value, uint8_t channel_value) 
    : adc(adc_value), channel(channel_value) {
  // Constructor implementation
  // Initialize the tracker with the ADCBase and channel
}

TrackerBase::~TrackerBase() {
  // Destructor implementation
}

// Add public method implementations here
uint16_t  TrackerBase::getValue() {
  // Read the value from the ADCBase for the specified channel
  // Assuming adc->readChannel(channel) is a method that reads the ADCBase value
  return adc->readChannel(channel);
}
// Add protected member implementations here

// Add private member implementations here
