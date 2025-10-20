#ifndef INC_TRACKERBASE_HPP_
#define INC_TRACKERBASE_HPP_

#include <cstdint>
#include <ADCBase.hpp>

class TrackerBase {
public:
  TrackerBase(ADCBase* adc_value, uint8_t channel_value, bool reverseValue); //reverseValue default false
  virtual ~TrackerBase();

  bool isReverse();
  uint16_t getValue();
  void setDetectionsValues(uint16_t detectInLimitValue, uint16_t detectOutLimitValue);
  bool isDetectedIn();
  bool isDetectedOut();

  // Add public methods here

protected:
  // Add protected members here

private:
  ADCBase* adc;
  uint8_t channel;
  bool reverse;
  uint16_t detectInLimit;
  uint16_t detectOutLimit;

};

#endif /* INC_TRACKERBASE_HPP_ */
