/*
 * ControllerBase.hpp
 *
 *  Created on: May 25, 2025
 *      Author: froilan
 */

#ifndef INC_CONTROLLERBASE_HPP_
#define INC_CONTROLLERBASE_HPP_

#include <ADCBase.hpp>
#include <ButtonPullup.hpp>
#include <Encoder.hpp>
#include <FlashMemory.hpp>
#include <IRReceiver.hpp>
#include <LedBase.hpp>
#include <MotorOneShot125.hpp>
#include <MotorTB6612FNG.hpp>
#include <Servo.hpp>
#include <Timer11Delay.hpp>
#include <TimerDWT.hpp>
#include <TrackerBase.hpp>
#include <UartComm.hpp>
#include <UartSerial.hpp>
#include <message_types.hpp>
#include <string>
#include <vector>

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
  virtual Servo* getServoDistance() const;
  virtual ADCBase* getADC() const;
  virtual TrackerBase* getTrackerLeft() const;
  virtual LedBase* getLedTrackerLeft() const;
  virtual TrackerBase* getTrackerRight() const;
  virtual LedBase* getLedTrackerRight() const;
  virtual TrackerBase* getDistanceLeft() const;
  virtual LedBase* getLedDistanceLeft() const;
  virtual TrackerBase* getDistanceRight() const;
  virtual LedBase* getLedDistanceRight() const;
  virtual TrackerBase* getDistanceLateralLeft() const;
  virtual LedBase* getLedDistanceLateralLeft() const;
  virtual TrackerBase* getDistanceLateralRight() const;
  virtual LedBase* getLedDistanceLateralRight() const;
  virtual TrackerBase* getDistanceCentral() const;
  virtual LedBase* getLedDistanceCentral() const;
  virtual MotorOneShot125* getMotorLeft() const;
  virtual MotorOneShot125* getMotorRight() const;
  virtual MotorTB6612FNG* getMotorDriverLeft() const;
  virtual MotorTB6612FNG* getMotorDriverRight() const;
  virtual Encoder* getEncoderLeft() const;
  virtual Encoder* getEncoderRight() const;
  virtual ButtonPullup* getButtonStart() const;
  virtual ButtonPullup* getSensorTilting() const;
  virtual LedBase* getLedStart() const;
  virtual IRReceiver* getIRReceiver() const;
  virtual FlashMemory* getFlashMemory() const;

  virtual void init_gym_mode_gym(UartSerial* uartSerial_value, UartComm* uartComm_value,
                                 TimerDWT* timerDWTValue, Timer11Delay* timer11Delay_value,
                                 Servo* servo_left_value, Servo* servo_right_value, Servo* servo_distance_value,
                                 Encoder* encoder_left_value, Encoder* encoder_right_value);

  virtual void init_gym_mode_fura(UartSerial* uartSerial_value, UartComm* uartComm_value,
                                  TimerDWT* timerDWTValue, Timer11Delay* timer11Delay_value,
                                  ADCBase* adc_value,
                                  TrackerBase* tracker_left_value, TrackerBase* tracker_right_value,
                                  TrackerBase* distance_left_value, TrackerBase* distance_right_value,
                                  MotorOneShot125* motor_left_value, MotorOneShot125* motor_right_value,
                                  ButtonPullup* button_start_value, LedBase* led_start_value);

  virtual void init_fura_mode_gym(Servo* servo_left_value, Servo* servo_right_value, Servo* servo_distance_value,
                                  Encoder* encoder_left_value, Encoder* encoder_right_value,
                                  LedBase* led_start_value);
  virtual void init_fura_mode_fura(ADCBase* adc_value,
                                   TrackerBase* tracker_left_value, LedBase* led_tracker_left_value,
                                   TrackerBase* tracker_right_value, LedBase* led_tracker_right_value,
                                   TrackerBase* distance_left_value, LedBase* led_distance_left_value,
                                   TrackerBase* distance_right_value, LedBase* led_distance_right_value,
                                   TrackerBase* distance_lateral_left_value, LedBase* led_distance_lateral_left_value,
                                   TrackerBase* distance_lateral_right_value, LedBase* led_distance_lateral_right_value,
                                   TrackerBase* distance_central_value, LedBase* led_distance_central_value,
                                   MotorOneShot125* motor_left_value, MotorOneShot125* motor_right_value,
                                   ButtonPullup* button_start_value, IRReceiver* ir_receiver, LedBase* led_start_value,
                                   ButtonPullup* sensor_tilting_value,
                                   FlashMemory* flash_memory_value);

  virtual void init_fura_mode_sumaker(ADCBase* adc_value,
                                      TrackerBase* tracker_left_value, TrackerBase* tracker_right_value,
                                      MotorTB6612FNG* motor_driver_left_value, MotorTB6612FNG* motor_driver_right_value,
                                      ButtonPullup* button_start_value, IRReceiver* ir_receiver_value, LedBase* led_start_value);

  virtual void serialReceivedData(UART_HandleTypeDef* huart);
  virtual void commReceivedData(UART_HandleTypeDef* huart);
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
  UartSerial* uartSerial;  // Puntero al objeto UartSerial
  UartComm* uartComm;      // Puntero al objeto UartComm
  TimerDWT* timerDWT;
  Timer11Delay* timer11Delay;
  Servo* servo_right;
  Servo* servo_left;
  Servo* servo_distance;
  ADCBase* adc;               // Puntero al objeto ADCBase
  TrackerBase* tracker_left;  // Puntero al objeto TrackerBase para el canal izquierdo
  LedBase* led_tracker_left;
  TrackerBase* tracker_right;  // Puntero al objeto TrackerBase para el canal derecho
  LedBase* led_tracker_right;
  TrackerBase* distance_left;  // Puntero al objeto TrackerBase para el canal izquierdo
  LedBase* led_distance_left;
  TrackerBase* distance_right;  // Puntero al objeto TrackerBase para el canal derecho
  LedBase* led_distance_right;
  TrackerBase* distance_lateral_left;  // Puntero al objeto TrackerBase para el canal izquierdo
  LedBase* led_distance_lateral_left;
  TrackerBase* distance_lateral_right;  // Puntero al objeto TrackerBase para el canal derecho
  LedBase* led_distance_lateral_right;
  TrackerBase* distance_central;  // Puntero al objeto TrackerBase para el canal central
  LedBase* led_distance_central;

  StructMessage* tx_message;  // Mensaje a transmitir
  StructMessage* rx_message;  // Mensaje recibido

  MotorOneShot125* motor_left;
  MotorOneShot125* motor_right;
  MotorTB6612FNG* motor_driver_left;
  MotorTB6612FNG* motor_driver_right;

  Encoder* encoder_left;
  Encoder* encoder_right;

  ButtonPullup* button_start;
  ButtonPullup* sensor_tilting;

  LedBase* led_start;

  IRReceiver* ir_receiver;

  FlashMemory* flash_memory;

  int step;

  int id_counter;  // Contador de IDs para mensajes

 private:
};

#endif /* INC_CONTROLLERBASE_HPP_ */
