#ifndef INC_ENCODERBASE_HPP_
#define INC_ENCODERBASE_HPP_

#include <cstdint>
#include <ADCBase.hpp>

class EncoderBase {
public:
  EncoderBase(UART_HandleTypeDef *huart);
  virtual ~EncoderBase();

  uint16_t getValue();

  // Add public methods here

protected:
  // Add protected members here

private:
  ADCBase* adc;
  uint8_t channel;
};

#endif /* INC_ENCODERBASE_HPP_ */
