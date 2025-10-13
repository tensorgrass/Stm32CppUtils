#ifndef INC_TRACKERBASE_HPP_
#define INC_TRACKERBASE_HPP_

#include <cstdint>
#include <ADCBase.hpp>

class TrackerBase {
public:
  TrackerBase(ADCBase* adc_value, uint8_t channel_value);
  virtual ~TrackerBase();

  uint16_t getValue();

  // Add public methods here

protected:
  // Add protected members here

private:
  ADCBase* adc;
  uint8_t channel;
};

#endif /* INC_TRACKERBASE_HPP_ */
