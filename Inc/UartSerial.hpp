/*
 * UartSerial.h
 *
 *  Created on: May 24, 2025
 *      Author: froilan
 */

#ifndef UARTSERIAL_H_
#define UARTSERIAL_H_

#include <stm32f4xx_hal.h>
#include <string>
#include <cstdint>   // Required for uint8_t
#include <vector>
#include <UartBase.hpp>

class UartSerial : public UartBase {
public:
  UartSerial(UART_HandleTypeDef *huart, std::string menu, std::vector<std::string>* optionsValue);
  virtual ~UartSerial();
  virtual std::string receiveData(UART_HandleTypeDef *huart);
  virtual void print(std::string string_to_send);
  virtual void println(std::string string_to_send);
  virtual void buffer(std::string string_to_send);
  virtual void bufferln(std::string string_to_send);
  virtual void printBuffer();

  virtual const std::vector<std::string>* getOptionList() const;
  virtual void setOptionList(std::vector<std::string>* optionsValue);
  virtual bool isValidOption(const std::string& option) const;

private:
  #define RX_SERIAL_BUFFER_SIZE 100
  unsigned char rxBuffer[RX_SERIAL_BUFFER_SIZE];
  unsigned char rxData; // Variable para recibir un byte
  uint16_t rxIndex = 0;

  std::string menu_string;
  std::vector<std::string>* option_list = nullptr;

  std::string buffer_string;
};

#endif /* UARTSERIAL_H_ */
