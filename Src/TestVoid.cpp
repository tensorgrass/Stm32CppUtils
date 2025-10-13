#include "TestVoid.hpp"

TestVoid::TestVoid(ControllerBase* controllerBaseValue) : TestBase(controllerBaseValue) {
  // Constructor de TestVoid, inicializa el controlador y los objetos UART
}

void TestVoid::sendData() {
  timer11Delay->delay(1); // Pequeña espera para no saturar el bucle
}

void TestVoid::receiveData() {
}
