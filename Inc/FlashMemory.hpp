/*
 * FlashMemory.h
 *
 *  Created on: May 24, 2025
 *      Author: froilan, prueba david
 */

//https://controllerstech.com/flash-programming-in-stm32/

#ifndef FLASHMEMORY_H_
#define FLASHMEMORY_H_

#include <stm32f4xx_hal.h>

#define FLASH_SECTOR_ADDRESS_INI_0 0x08000000
#define FLASH_SECTOR_ADDRESS_INI_1 0x08004000
#define FLASH_SECTOR_ADDRESS_INI_2 0x08008000
#define FLASH_SECTOR_ADDRESS_INI_3 0x0800C000
#define FLASH_SECTOR_ADDRESS_INI_4 0x08010000
#define FLASH_SECTOR_ADDRESS_INI_5 0x08020000
#define FLASH_SECTOR_ADDRESS_INI_6 0x08040000
#define FLASH_SECTOR_ADDRESS_INI_7 0x08060000
#define FLASH_SECTOR_ADDRESS_END   0x08080000 //END sector 7 FLASH_SECTOR_7
#define FLASH_SECTOR_ERROR 0xFFFFFFFF

class FlashMemory  {
public:
  FlashMemory();
  virtual ~FlashMemory();

  void read(uint32_t *rx_buffer, uint16_t number_of_words);
  uint32_t write(uint32_t *Data, uint16_t numberofwords);
  bool is_last_sector_free(uint32_t _etext);
  uint32_t getSector(uint32_t memory_flash_address);

private:

};

#endif /* FLASHMEMORY_H_ */
