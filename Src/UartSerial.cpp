/*
 * UartSerial.cpp
 *
 *  Created on: May 24, 2025
 *      Author: froilan
 */

#include <UartSerial.hpp>


UartSerial::UartSerial(UART_HandleTypeDef *huart, std::string menu, std::vector<std::string>* optionsValue) : UartBase(huart), menu_string(menu), option_list(optionsValue) {
  buffer_string.reserve(4096);
  buffer_string.append("\r\n---\r\n");
  HAL_UART_Receive_IT(huart, &rxData, 1);
}

UartSerial::~UartSerial() {
	// TODO Auto-generated destructor stub
}

std::string UartSerial::receiveData(UART_HandleTypeDef *huart) {
    std::string selected_option("");
    if (rxData == '\n' || rxData == '\r') // Verifica si llegó el carácter de cambio de línea
    {
      printBuffer(); // Imprime el contenido del búfer antes de procesar el mensaje
      rxBuffer[rxIndex] = '\0'; // Termina la cadena
      // Procesa el mensaje recibido en rxBuffer
      rxIndex = 0; // Reinicia el índice para el próximo mensaje
      selected_option = reinterpret_cast<const char*>(rxBuffer);
      if (!selected_option.empty()) {
        selected_option[0] = std::toupper(static_cast<unsigned char>(selected_option[0]));
      }

      if (isValidOption(selected_option)) {
        std::string texto_opcion_seleccionada = "Opcion seleccionada: " + selected_option + "\r\n";
        buffer(texto_opcion_seleccionada);
      }
      else {
        sendDataString(huart, menu_string);
      }
    }
    else if (rxData == '\177' || rxData == '\b') // Verifica si llegó el carácter de cambio de línea
    {
    	if (rxIndex > 0) {
    	  rxIndex--;
    	    std::string crlf_sequence = "\b \b";
//    	    HAL_UART_Transmit_IT(huart, reinterpret_cast<const unsigned char*>(crlf_sequence.data()), crlf_sequence.size());
    	    sendDataString(huart, crlf_sequence);
    	}
    }
    else
    {
      if (rxIndex < RX_SERIAL_BUFFER_SIZE - 1) // Evita desbordamiento del búfer
      {
        rxBuffer[rxIndex++] = rxData; // Almacena el byte recibido
      }
      HAL_UART_Transmit_IT(huart, &rxData, 1);
      sendDataChar(huart, rxData);
    }
    // Reinicia la recepción de un nuevo byte
    HAL_UART_Receive_IT(huart, &rxData, 1);
    return selected_option; // Devuelve la opción seleccionada
}

void UartSerial::print(std::string string_to_send) {
 HAL_UART_Transmit(uartHandler, reinterpret_cast<const unsigned char*>(string_to_send.data()), string_to_send.size(), HAL_MAX_DELAY);
}

void UartSerial::println(std::string string_to_send) {
 std::string string_to_send_ln(string_to_send + "\r\n");
 HAL_UART_Transmit(uartHandler, reinterpret_cast<const unsigned char*>(string_to_send_ln.data()), string_to_send_ln.size(), HAL_MAX_DELAY);
}

void UartSerial::buffer(std::string string_to_send) {
  buffer_string.append(string_to_send);
}

void UartSerial::bufferln(std::string string_to_send) {
  buffer_string.append(string_to_send);
  buffer_string.append("\r\n");
}

void UartSerial::printBuffer() {
  if (!buffer_string.empty()) {
    buffer_string.append("\r\n--fin--\r\n");
//    buffer_string = "\r\n---\r\n" + buffer_string; // Agrega un encabezado al búfer
    if (HAL_UART_Transmit(uartHandler, reinterpret_cast<const unsigned char*>(buffer_string.data()), buffer_string.size(), HAL_MAX_DELAY) == HAL_OK) {
      buffer_string.clear();
      buffer_string.append("\r\n--ok--\r\n");
    }
    else {
      buffer_string.clear();
      buffer_string.append("\r\n--error--\r\n");
    }

  }
}

const std::vector<std::string>* UartSerial::getOptionList() const {
  return option_list;
}

void UartSerial::setOptionList(std::vector<std::string>* optionsValue) {
  option_list = optionsValue;
}

bool UartSerial::isValidOption(const std::string& option) const {
  for (const auto& opt : *option_list) {
    if (opt == option) {
      return true; // Opción válida
    }
  }
  return false; // Opción no válida
}
