/*
 * ControllerBase.hpp
 *
 *  Created on: May 25, 2025
 *      Author: froilan
 */

#ifndef INC_CONTROLLERBASE_HPP_
#define INC_CONTROLLERBASE_HPP_

#include <string>
#include <message_types.hpp>
#include <vector>
#include <UartSerial.hpp>
#include <UartComm.hpp>
#include <TimerDWT.hpp>
#include <Timer11Delay.hpp>
#include <Servo.hpp>
#include <ADCBase.hpp>
#include <TrackerBase.hpp>
#include <MotorOneShot125.hpp>


class ControllerBase {
public:
  ControllerBase();
  virtual ~ControllerBase();

  virtual UartSerial* getUartSerial() const;
  virtual UartComm* getUartComm() const;
  virtual TimerDWT* getTimerDWT() const;
  virtual Timer11Delay* getTimer11Delay() const;
  virtual Servo* getServoRight() const;
  virtual Servo* getServoLeft() const;
  virtual Servo* getServoCenter() const;
  virtual ADCBase* getADC() const;
  virtual TrackerBase* getTrackerLeft() const;
  virtual TrackerBase* getTrackerRight() const;
  virtual TrackerBase* getDistanceLeft() const;
  virtual TrackerBase* getDistanceRight() const;
  virtual MotorOneShot125* getMotorLeft() const;
  virtual MotorOneShot125* getMotorRight() const;

  virtual void init_gym(UartSerial* uartSerial_value, UartComm* uartComm_value,
                    TimerDWT* timerDWTValue, Timer11Delay* timer11Delay_value,
                    Servo* servoRight_value, Servo* servoLeft_value, Servo* servoCenter_value);

  virtual void init_fura(UartSerial* uartSerial_value, UartComm* uartComm_value,
                    TimerDWT* timerDWTValue, Timer11Delay* timer11Delay_value,
                    ADCBase* adc_value,
                    TrackerBase* tracker_left_value, TrackerBase* tracker_right_value,
                    TrackerBase* distance_left_value, TrackerBase* distance_right_value,
                    MotorOneShot125* motor_left_value, MotorOneShot125* motor_right_value);

  virtual void serialReceivedData(UART_HandleTypeDef *huart);
  virtual void commReceivedData(UART_HandleTypeDef *huart);
  virtual void commSendData();
  virtual void commReset();

  virtual void setTest(char grupo, char subgrupo);
  virtual void timeoutTest(std::string step);

  // Método para indicar el final de la transacción
  virtual void endTxTransaction();

  virtual int getTxId() const;
  virtual void setTxId(int value);

  virtual char getTxGroup() const;
  virtual void setTxGroup(char value);

  virtual char getTxSubgroup() const;
  virtual void setTxSubgroup(char value);

  virtual int getTxStep() const;
  virtual void setTxStep(int value);

  virtual StructMessage* getTxMessage();
  virtual void setTxMessage(StructMessage* message);
  virtual size_t serializeTxMessage(uint8_t* buffer, size_t buffer_size);
  virtual size_t deserializeTxMessage(const uint8_t* buffer, size_t buffer_size);


  // Métodos equivalentes para Rx
  virtual void endRxTransaction();

  virtual int getRxId() const;
  virtual void setRxId(int value);

  virtual char getRxGroup() const;
  virtual void setRxGroup(char value);

  virtual char getRxSubgroup() const;
  virtual void setRxSubgroup(char value);

  virtual int getRxStep() const;
  virtual void setRxStep(int value);

  virtual StructMessage* getRxMessage() const;
  virtual void setRxMessage(StructMessage* message);
  virtual size_t serializeRxMessage(uint8_t* buffer, size_t buffer_size);
  virtual size_t deserializeRxMessage(const uint8_t* buffer, size_t buffer_size);

protected:
  UartSerial* uartSerial; // Puntero al objeto UartSerial
  UartComm* uartComm; // Puntero al objeto UartComm
  TimerDWT* timerDWT;
  Timer11Delay* timer11Delay;
  Servo* servo_right;
  Servo* servo_left;
  Servo* servo_center;
  ADCBase* adc; // Puntero al objeto ADCBase
  TrackerBase* tracker_left; // Puntero al objeto TrackerBase para el canal izquierdo
  TrackerBase* tracker_right; // Puntero al objeto TrackerBase para el canal derecho
  TrackerBase* distance_left; // Puntero al objeto TrackerBase para el canal izquierdo
  TrackerBase* distance_right; // Puntero al objeto TrackerBase para el canal derecho

  StructMessage *tx_message;          // Mensaje a transmitir
  StructMessage *rx_message;          // Mensaje recibido

  MotorOneShot125* motor_left;
  MotorOneShot125* motor_right;

  int step;

  int id_counter; // Contador de IDs para mensajes

private:


};



#endif /* INC_CONTROLLERBASE_HPP_ */
