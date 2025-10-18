#ifndef INC_ENCODER_HPP_
#define INC_ENCODER_HPP_

#include <cstdint>
#include <stm32f4xx_hal.h>

class Encoder {
public:
  Encoder(TIM_HandleTypeDef *htim_value);
  virtual ~Encoder();

  void init();
  uint32_t getValue();
  int32_t getDifferenceSigned(uint32_t previous_value);
  uint32_t getDifferenceUnsigned(uint32_t previous_value);


  // Add public methods here

protected:
  // Add protected members here

private:
  TIM_HandleTypeDef *htim;
  const uint32_t MODULE = 65553;
};

#endif /* INC_ENCODER_HPP_ */
