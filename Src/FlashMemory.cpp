/*
 * FlashMemory.cpp
 *
 *  Created on: May 24, 2025
 *      Author: froilan
 */

#include <FlashMemory.hpp>


FlashMemory::FlashMemory() {

}

FlashMemory::~FlashMemory() {
	// TODO Auto-generated destructor stub
}


void FlashMemory::read(uint32_t *rx_buffer, uint16_t number_of_words) {
  uint32_t start_sector_address = FLASH_SECTOR_ADDRESS_INI_7;
  while (number_of_words > 0) {
    *rx_buffer = *(__IO uint32_t *)start_sector_address;
    start_sector_address += 4;
    rx_buffer++;
    number_of_words--;
  }
}

uint32_t FlashMemory::write(uint32_t *data, uint16_t number_of_words) {
  /* Erase the user Flash area */
  /* Get the number of sector to erase from 1st sector */
  FLASH_EraseInitTypeDef erase_init_struct;
  uint32_t sector_error = 0;
  uint32_t start_sector_address = FLASH_SECTOR_ADDRESS_INI_7;

//  uint32_t start_sector = getSector(start_sector_address);
//  uint32_t end_sector_address = start_sector_address + (number_of_words * 4);
//  uint32_t end_sector = getSector(end_sector_address);
//  uint32_t num_sectors = end_sector - start_sector + 1;

  uint32_t start_sector = FLASH_SECTOR_7;
  uint32_t num_sectors = 1;

  /* Unlock the Flash to enable the flash control register access *************/
  HAL_FLASH_Unlock();

  /* Fill EraseInit structure*/
  erase_init_struct.TypeErase     = FLASH_TYPEERASE_SECTORS;
  erase_init_struct.VoltageRange  = FLASH_VOLTAGE_RANGE_3;
  erase_init_struct.Sector        = start_sector;
  erase_init_struct.NbSectors     = num_sectors; //Borramos todo el sector 7, que es el ultimo y con el cual estamos trabajando

  /* Note: If an erase operation in Flash memory also concerns data in the data or instruction cache,
     you have to make sure that these data are rewritten before they are accessed during code
     execution. If this cannot be done safely, it is recommended to flush the caches by setting the
     DCRST and ICRST bits in the FLASH_CR register. */
  if (HAL_FLASHEx_Erase(&erase_init_struct, &sector_error) != HAL_OK) {
    return HAL_FLASH_GetError();
  }

  /* Program the user Flash area word by word
    (area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR) ***********/

  for(int num_word = 0; num_word < number_of_words; num_word++) {
    if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, start_sector_address, data[num_word]) == HAL_OK) {
      start_sector_address += 4;  // use StartPageAddress += 2 for half word and 8 for double word
    }
    else {
      /* Error occurred while writing data in Flash memory*/
      return HAL_FLASH_GetError();
    }
  }

  /* Lock the Flash to disable the flash control register access (recommended
     to protect the FLASH memory against possible unwanted operation) *********/
  HAL_FLASH_Lock();

  return 0;
}

/**
 * @brief Calcula la dirección del primer sector de Flash libre después del programa.
 * @retval La dirección de inicio del sector a usar.
 * Poner en el main.c en el aparatdo el siguiente codigo: USER CODE BEGIN PV
 * extern uint32_t _etext; // Símbolo que marca el final del código en Flash
 */
bool FlashMemory::is_last_sector_free(uint32_t _etext) {
  uint32_t program_sector_end = getSector(_etext);
  if (program_sector_end < FLASH_SECTOR_7 && program_sector_end != FLASH_SECTOR_ERROR){
    return true;
  }
  // Si el programa es tan grande que no cabe, devuelve 0 (o maneja el error)
  return false;
}

/**
 * @brief Obtiene el número de sector de la Flash para una dirección de memoria dada.
 * @note  Esta función es necesaria para la serie STM32F4, que no incluye HAL_FLASHEx_GetSector.
 * @param Address: La dirección de memoria a comprobar.
 * @retval El número de sector (ej. FLASH_SECTOR_0) o 0xFFFFFFFF si la dirección es inválida.
 */
uint32_t FlashMemory::getSector(uint32_t memory_flash_address)
{
  uint32_t sector = 0;

  if((memory_flash_address >= FLASH_SECTOR_ADDRESS_INI_0) && (memory_flash_address < FLASH_SECTOR_ADDRESS_INI_1)) {
    sector = FLASH_SECTOR_0;
  }
  else if((memory_flash_address >= FLASH_SECTOR_ADDRESS_INI_1) && (memory_flash_address < FLASH_SECTOR_ADDRESS_INI_2)) {
    sector = FLASH_SECTOR_1;
  }
  else if((memory_flash_address >= FLASH_SECTOR_ADDRESS_INI_2) && (memory_flash_address < FLASH_SECTOR_ADDRESS_INI_3)) {
    sector = FLASH_SECTOR_2;
  }
  else if((memory_flash_address >= FLASH_SECTOR_ADDRESS_INI_3) && (memory_flash_address < FLASH_SECTOR_ADDRESS_INI_4)) {
    sector = FLASH_SECTOR_3;
  }
  else if((memory_flash_address >= FLASH_SECTOR_ADDRESS_INI_4) && (memory_flash_address < FLASH_SECTOR_ADDRESS_INI_5)) {
    sector = FLASH_SECTOR_4;
  }
  else if((memory_flash_address >= FLASH_SECTOR_ADDRESS_INI_5) && (memory_flash_address < FLASH_SECTOR_ADDRESS_INI_6)) {
    sector = FLASH_SECTOR_5;
  }
  else if((memory_flash_address >= FLASH_SECTOR_ADDRESS_INI_6) && (memory_flash_address < FLASH_SECTOR_ADDRESS_INI_7)) {
    sector = FLASH_SECTOR_6;
  }
  else if((memory_flash_address >= FLASH_SECTOR_ADDRESS_INI_7) && (memory_flash_address < FLASH_SECTOR_ADDRESS_END)) {
    sector = FLASH_SECTOR_7;
  }
  else {
    sector = FLASH_SECTOR_ERROR; // Dirección inválida
  }

  return sector;
}
