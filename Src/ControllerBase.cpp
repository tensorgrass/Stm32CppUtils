/*
 * ControllerBase.cpp
 *
 *  Created on: May 25, 2025
 *      Author: froilan
 */
#include <ControllerBase.hpp>
#include <cstring> // Para memcpy

ControllerBase::ControllerBase() {
  // TODO Auto-generated constructor stub
  tx_message = new StructMessage(); // Inicializar el mensaje de transmisión
  rx_message = new StructMessage(); // Inicializar el mensaje de recepción
  endTxTransaction(); // Asegurarse de que el mensaje de transmisión esté limpio
  step = 0; // Inicializa el paso
  id_counter = 0; // Inicializa el contador de ID
}

ControllerBase::~ControllerBase() {
  // TODO Auto-generated destructor stub
}

UartSerial* ControllerBase::getUartSerial() const {
  return uartSerial;
}

UartComm* ControllerBase::getUartComm() const {
  return uartComm;
}

TimerDWT* ControllerBase::getTimerDWT() const {
  return timerDWT;
}

Timer11Delay* ControllerBase::getTimer11Delay() const {
  return timer11Delay;
}

Servo* ControllerBase::getServoRight() const {
  return servo_right;
}

Servo* ControllerBase::getServoLeft() const {
  return servo_left;
}

Servo* ControllerBase::getServoCenter() const {
  return servo_center;
}

ADCBase* ControllerBase::getADC() const {
  return adc;
}

TrackerBase* ControllerBase::getTrackerLeft() const {
  return tracker_left;
}

TrackerBase* ControllerBase::getTrackerRight() const {
  return tracker_right;
}

TrackerBase* ControllerBase::getDistanceLeft() const {
  return distance_left;
}

TrackerBase* ControllerBase::getDistanceRight() const {
  return distance_right;
}

MotorOneShot125* ControllerBase::getMotorLeft() const {
  return motor_left;
}

MotorOneShot125* ControllerBase::getMotorRight() const {
  return motor_right;
}

void ControllerBase::init_gym(UartSerial* uartSerial_value, UartComm* uartComm_value,
                          TimerDWT* timerDWT_value, Timer11Delay* timer11Delay_value,
                          Servo* servoRight_value, Servo* servoLeft_value, Servo* servoCenter_value) {
  uartSerial = uartSerial_value;
  uartComm = uartComm_value;
  timerDWT = timerDWT_value;
  timer11Delay = timer11Delay_value;
  servo_right = servoRight_value;
  servo_left = servoLeft_value;
  servo_center = servoCenter_value;
}

void ControllerBase::init_fura(UartSerial* uartSerial_value, UartComm* uartComm_value,
                          TimerDWT* timerDWT_value, Timer11Delay* timer11Delay_value,
                          ADCBase* adc_value,
                          TrackerBase* tracker_left_value, TrackerBase* tracker_right_value,
                          TrackerBase* distance_left_value, TrackerBase* distance_right_value,
                          MotorOneShot125* motor_left_value, MotorOneShot125* motor_right_value) {
  uartSerial = uartSerial_value;
  uartComm = uartComm_value;
  timerDWT = timerDWT_value;
  timer11Delay = timer11Delay_value;
  adc = adc_value;
  tracker_left = tracker_left_value;
  tracker_right = tracker_right_value;
  distance_left = distance_left_value;
  distance_right = distance_right_value;
  motor_left = motor_left_value;
  motor_right = motor_right_value;
}

void ControllerBase::serialReceivedData(UART_HandleTypeDef *huart) {
  std::string selected_option = uartSerial->receiveData(huart);
  if (!selected_option.empty()) {
    setRxGroup(selected_option[0]); // Asignar grupo
    setRxSubgroup(selected_option[1]); // Asignar subgrupo
    setRxStep(0); // Reiniciar el paso al iniciar una nueva transacción
  }
}

void ControllerBase::commReceivedData(UART_HandleTypeDef *huart) {
  std::vector<uint8_t> rx_buffer_vector = uartComm->receiveData(huart);
  const uint8_t* rx_buffer = rx_buffer_vector.data();
  // Deserializar el mensaje recibido
  deserializeRxMessage(rx_buffer, RX_BUFFER_SIZE);
  
  uartSerial->buffer(std::string(1, getRxGroup()));
  uartSerial->buffer(",");
  uartSerial->buffer(std::string(1, getRxSubgroup()));
  uartSerial->buffer(",");
  uartSerial->buffer(std::to_string(getRxId()));
  uartSerial->buffer(",");
  uartSerial->bufferln(std::to_string(getRxStep()));
}

void ControllerBase::commSendData() {
  uartComm->sendData(getTxMessage());
}

void ControllerBase::commReset() {
  uartComm->commReset();
}

void ControllerBase::setTest(char grupo, char subgrupo) {
  setRxGroup(grupo);
  setRxSubgroup(subgrupo);
  setRxStep(0); // Reiniciar el paso al iniciar una nueva transacción
}

void ControllerBase::timeoutTest(std::string step) {
  uartSerial->buffer("Timeout reached ");
  uartSerial->buffer(step);
  uartSerial->bufferln(", finishing step.");
  uartSerial->printBuffer();
  endRxTransaction();
}

void ControllerBase::endTxTransaction() {
  setTxGroup('\0');
  setTxSubgroup('\0');
  setTxStep(0);
}

int ControllerBase::getTxId() const {
  return static_cast<int>(tx_message->id);
}

void ControllerBase::setTxId(int value) {
  if (tx_message) {
    tx_message->id = static_cast<uint16_t>(value);
  }
}

char ControllerBase::getTxGroup() const {
  return tx_message ? tx_message->group : '\0';
}

void ControllerBase::setTxGroup(char value) {
  if (tx_message) {
    tx_message->group = value;
  }
}

char ControllerBase::getTxSubgroup() const {
  return tx_message ? tx_message->subgroup : '\0';
}

void ControllerBase::setTxSubgroup(char value) {
  if (tx_message) {
    tx_message->subgroup = value;
  }
}


int ControllerBase::getTxStep() const {
  return static_cast<int>(tx_message->step);
}

void ControllerBase::setTxStep(int value) {
  if (tx_message) {
    tx_message->step = static_cast<uint16_t>(value);
  }
}

StructMessage* ControllerBase::getTxMessage() {
  tx_message->id = id_counter++; // Asignar un ID único al mensaje
  tx_message->end = 'Z';
  return tx_message;
}

void ControllerBase::setTxMessage(StructMessage* message) {
  if (tx_message && message) {
    *tx_message = *message;
  }
}

// La serialización es simple: copiar los bytes del struct al buffer
size_t ControllerBase::serializeTxMessage(uint8_t* buffer, size_t buffer_size) {
  if (buffer_size < sizeof(StructMessage)) {
      // Buffer demasiado pequeño, manejar error
      return 0;
  }
  tx_message->id = id_counter++; // Asignar un ID único al mensaje
  tx_message->end = 'Z';
  // Copiar la estructura byte a byte al buffer
  memcpy(buffer, tx_message, sizeof(StructMessage));
  return sizeof(StructMessage);
}

size_t ControllerBase::deserializeTxMessage(const uint8_t* buffer, size_t buffer_size) {
  if (buffer_size < sizeof(StructMessage)) {
    return 0;
  }
  memcpy(tx_message, buffer, sizeof(StructMessage));
  return sizeof(StructMessage);
}


void ControllerBase::endRxTransaction() {
  setRxGroup('\0');
  setRxSubgroup('\0');
  setRxStep(0);
}

int ControllerBase::getRxId() const {
  return static_cast<int>(rx_message->id);
}

void ControllerBase::setRxId(int value) {
  if (rx_message) {
    rx_message->id = static_cast<uint16_t>(value);
  }
}

char ControllerBase::getRxGroup() const {
  return rx_message ? rx_message->group : '\0';
}

void ControllerBase::setRxGroup(char value) {
  if (rx_message) {
    rx_message->group = value;
  }
}

char ControllerBase::getRxSubgroup() const {
  return rx_message ? rx_message->subgroup : '\0';
}

void ControllerBase::setRxSubgroup(char value) {
  if (rx_message) {
    rx_message->subgroup = value;
  }
}

int ControllerBase::getRxStep() const {
  return static_cast<int>(rx_message->step);
}

void ControllerBase::setRxStep(int value) {
  if (rx_message) {
    rx_message->step = static_cast<uint16_t>(value);
  }
}

StructMessage* ControllerBase::getRxMessage() const {
  return rx_message;
}

void ControllerBase::setRxMessage(StructMessage* message) {
  if (rx_message && message) {
    *rx_message = *message;
  }
}

size_t ControllerBase::serializeRxMessage(uint8_t* buffer, size_t buffer_size) {
  if (buffer_size < sizeof(StructMessage)) {
    return 0;
  }
  rx_message->id = id_counter++; // Asignar un ID único al mensaje
  rx_message->end = 'Z';
  memcpy(buffer, rx_message, sizeof(StructMessage));
  return sizeof(StructMessage);
}

size_t ControllerBase::deserializeRxMessage(const uint8_t* buffer, size_t buffer_size) {
  if (buffer_size < sizeof(StructMessage)) {
      // Buffer demasiado pequeño, manejar error
      return 0;
  }
  // Copiar el buffer byte a byte a la estructura
  memcpy(rx_message, buffer, sizeof(StructMessage));
  return sizeof(StructMessage);
}
