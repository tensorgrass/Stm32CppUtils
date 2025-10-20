#include <TrackerBase.hpp>

TrackerBase::TrackerBase(ADCBase* adc_value, uint8_t channel_value, bool reverseValue)
    : adc(adc_value), channel(channel_value), reverse(reverseValue) {
  // Constructor implementation
  // Initialize the tracker with the ADCBase and channel
  // reverseValue default false
}

TrackerBase::~TrackerBase() {
  // Destructor implementation
}

bool TrackerBase::isReverse() {
	return reverse;
}

// Add public method implementations here
uint16_t  TrackerBase::getValue() {
  // Read the value from the ADCBase for the specified channel
  // Assuming adc->readChannel(channel) is a method that reads the ADCBase value
  return adc->readChannel(channel);
}

void TrackerBase::setDetectionsValues(uint16_t detectInLimitValue, uint16_t detectOutLimitValue) {
	detectInLimit = detectInLimitValue;
	detectOutLimit = detectOutLimitValue;
}

bool TrackerBase::isDetectedIn() {
	uint16_t current_value = adc->readChannel(channel);
	if (!reverse) {
		return current_value < detectInLimit;
	}
	else {
		return current_value > detectInLimit;
	}
}

bool TrackerBase::isDetectedOut() {
	uint16_t current_value = adc->readChannel(channel);
	if (!reverse) {
		return current_value < detectOutLimit;
	}
	else {
		return current_value > detectOutLimit;
	}
}
// Add protected member implementations here

// Add private member implementations here
