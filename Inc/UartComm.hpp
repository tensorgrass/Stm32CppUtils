/*
 * UartComm.h
 *
 *  Created on: May 24, 2025
 *      Author: froilan
 */

#ifndef UARTCOMM_H_
#define UARTCOMM_H_

#include <stm32f4xx_hal.h>
#include <string>
#include <cstdint>   // Required for uint8_t
#include <vector>
#include "UartBase.hpp"
#include "UartSerial.hpp"
#include "message_types.hpp"

#define RX_BUFFER_SIZE  sizeof(StructMessage) // El tamaño del buffer de recepción es el tamaño del struct
#define TX_BUFFER_SIZE  sizeof(StructMessage) // El tamaño del buffer de transmisión es el tamaño del struct

class UartComm : public UartBase {
public:
  UartComm(UART_HandleTypeDef *huart, UartSerial *uartSerialValue);
  virtual ~UartComm();
  virtual void sendData(StructMessage* message);
  virtual std::vector<uint8_t> receiveData(UART_HandleTypeDef *huart);
  virtual void commReset();


private:
  UartSerial *uartSerial; // Puntero al objeto UartSerial original

  uint8_t rx_buffer[RX_BUFFER_SIZE]; // Buffer para la recepción UART
  uint8_t tx_buffer[TX_BUFFER_SIZE]; // Buffer para la transmisión UART

};

#endif /* UARTCOMM_H_ */
