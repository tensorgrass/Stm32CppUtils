/*
 * UartComm.cpp
 *
 *  Created on: May 24, 2025
 *      Author: froilan
 */

#include <UartComm.hpp>


UartComm::UartComm(UART_HandleTypeDef *huart, UartSerial *uartSerialValue) : UartBase(huart), uartSerial(uartSerialValue) {
  uint8_t dummy_byte;
  while (HAL_UART_Receive(uartHandler, &dummy_byte, 1, 10) == HAL_OK) { // Timeout de 10ms
      // El bucle seguirá leyendo mientras haya datos y se reciban OK
      uartSerial->bufferln("Limpiando uartComm"); // Para depuración
  }

  HAL_UART_Receive_IT(uartHandler, rx_buffer, RX_BUFFER_SIZE);
}

UartComm::~UartComm() {
  // TODO Auto-generated destructor stub
}

void UartComm::sendData(StructMessage* message){
  // Copiar la estructura byte a byte al buffer
  memcpy(tx_buffer, message, sizeof(StructMessage));


  uartSerial->buffer("Send:");
  uartSerial->bufferln(std::string(reinterpret_cast<char*>(tx_buffer), TX_BUFFER_SIZE));

  // Enviar el primer mensaje (bloqueante para asegurar que salga primero)
//  HAL_UART_Transmit(uartHandler, tx_buffer, TX_BUFFER_SIZE, HAL_MAX_DELAY);
  HAL_UART_Transmit(uartHandler, tx_buffer, TX_BUFFER_SIZE, 1);
  // HAL_Delay(1); // Pequeña espera para que el otro nodo reciba y procese
}

std::vector<uint8_t> UartComm::receiveData(UART_HandleTypeDef *huart){
  uartSerial->buffer("Rcv: ");
  uartSerial->bufferln(std::string(reinterpret_cast<char*>(rx_buffer), RX_BUFFER_SIZE));

  HAL_UART_Receive_IT(huart, rx_buffer, RX_BUFFER_SIZE);

  size_t arr_size = sizeof(rx_buffer) / sizeof(rx_buffer[0]);
  std::vector<uint8_t> rx_buffer_vector(rx_buffer, rx_buffer + arr_size);
  return rx_buffer_vector;
}

void UartComm::commReset() {
  HAL_UART_AbortReceive(uartHandler);
  HAL_UART_Receive_IT(uartHandler, rx_buffer, RX_BUFFER_SIZE);
}
