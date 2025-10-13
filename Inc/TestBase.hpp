#ifndef TESTBASE_HPP
#define TESTBASE_HPP

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
  Servo* servo_center;

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

  enum enum_step {
    STEP_WAIT_INIT,
    STEP_INIT,
    STEP_WAIT_FINISH,
    STEP_FINISH,

    STEP_WAIT_ACCELERATE,
    STEP_ACCELERATE,
    STEP_WAIT_DECELERATE,
    STEP_DECELERATE,

    STEP_WAIT_SPEED_BASE_START,
    STEP_SPEED_BASE_START,
    STEP_WAIT_SPEED_BASE_STOP,
    STEP_SPEED_BASE_STOP,

    STEP_WAIT_TRACKER_LEFT_START,
    STEP_TRACKER_LEFT_START,
    STEP_WAIT_TRACKER_LEFT_DETECTED,
    STEP_TRACKER_LEFT_DETECTED,
    STEP_WAIT_TRACKER_LEFT_RETURN,
    STEP_TRACKER_LEFT_RETURN,

    STEP_WAIT_TRACKER_RIGHT_START,
    STEP_TRACKER_RIGHT_START,
    STEP_WAIT_TRACKER_RIGHT_DETECTED,
    STEP_TRACKER_RIGHT_DETECTED,
    STEP_WAIT_TRACKER_RIGHT_RETURN,
    STEP_TRACKER_RIGHT_RETURN,

    STEP_WAIT_TRACKER_BOTH_START,
    STEP_TRACKER_BOTH_START,
    STEP_WAIT_TRACKER_BOTH_DETECTED,
    STEP_TRACKER_BOTH_DETECTED,
    STEP_WAIT_TRACKER_BOTH_RETURN,
    STEP_TRACKER_BOTH_RETURN,

    STEP_WAIT_TRACKER_MOTOR_LEFT_START,
    STEP_TRACKER_MOTOR_LEFT_START,
    STEP_WAIT_TRACKER_MOTOR_LEFT_DETECTED,
    STEP_TRACKER_MOTOR_LEFT_DETECTED,
    STEP_WAIT_TRACKER_MOTOR_LEFT_RETURN,
    STEP_TRACKER_MOTOR_LEFT_RETURN,
  };
};

#endif // TESTBASE_HPP
