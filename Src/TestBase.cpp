#include "TestBase.hpp"

TestBase::TestBase(ControllerBase* controllerBaseValue) : 
  controller(controllerBaseValue), 
  uartSerial(controllerBaseValue->getUartSerial()), 
  uartComm(controllerBaseValue->getUartComm()), 
  timerDWT(controllerBaseValue->getTimerDWT()), 
  timer11Delay(controllerBaseValue->getTimer11Delay()),
  servo_right(controllerBaseValue->getServoRight()),
  servo_left(controllerBaseValue->getServoLeft()),
  servo_distance(controllerBaseValue->getServoDistance()) {
  // Aquí podrías inicializar otros miembros si es necesario
  // Constructor de TestBase, inicializa el controlador y los objetos UART
}

// Métodos virtuales puros, no se implementan aquí.
// void TestBase::sendData(const uint8_t* data, size_t length) {}
// void TestBase::receiveData(uint8_t* buffer, size_t length) {}

