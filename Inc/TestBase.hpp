#ifndef TESTBASE_HPP
#define TESTBASE_HPP

#include <enum_step.hpp>
#include "UartSerial.hpp"
#include "UartComm.hpp"
#include "ControllerBase.hpp"
#include <TimerDWT.hpp>
#include <Timer11Delay.hpp>
#include <Servo.hpp>


class TestBase {
public:
  TestBase(ControllerBase* controllerBaseValue);
  virtual ~TestBase() = default;

  virtual char getGroup() const = 0;
  virtual void sendData() = 0;
  virtual void receiveData() = 0;

protected:
  ControllerBase* controller; // Puntero al controlador base
  UartSerial* uartSerial; // Puntero al objeto UartSerial
  UartComm* uartComm; // Puntero al objeto UartComm
  TimerDWT* timerDWT;
  Timer11Delay* timer11Delay;
  Servo* servo_right;
  Servo* servo_left;
  Servo* servo_distance;

  int timeout;

  enum enum_subgroup {
    SUBGRUPO_0,
    SUBGRUPO_1,
    SUBGRUPO_2,
    SUBGRUPO_3,
    SUBGRUPO_4,
    SUBGRUPO_5,
    SUBGRUPO_6,
    SUBGRUPO_7,
    SUBGRUPO_8,
    SUBGRUPO_9
  };


};

#endif // TESTBASE_HPP
