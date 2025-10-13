#include "TimerDWT.hpp"

#include <stm32f4xx_hal.h>

#define DWT_CONTROL (*(volatile uint32_t*)0xE0001000)
#define DWT_CYCCNT (*(volatile uint32_t*)0xE0001004)
#define DEMCR (*(volatile uint32_t*)0xE000EDFC)
#define DEMCR_TRCENA (1 << 24)

TimerDWT::TimerDWT()
    : start_cycles(0), end_cycles(0), elapsed_cycles(0), elapsed_microseconds(0) {
    // Enable TRCENA in DEMCR (Debug Exception and Monitor Control Register)
    DEMCR |= DEMCR_TRCENA;
    // Reset cycle counter
    DWT_CYCCNT = 0;
    // Enable the cycle counter
    DWT_CONTROL |= 1;
}

TimerDWT::~TimerDWT() {
}

void TimerDWT::start() {
    start_cycles = DWT->CYCCNT;
}

uint32_t TimerDWT::getElapsedTime() {
    end_cycles = DWT->CYCCNT;

    // Calcular tiempo transcurrido
    elapsed_cycles = end_cycles - start_cycles;
    elapsed_microseconds = cycles_to_microseconds(elapsed_cycles);
    return elapsed_microseconds;
}

// Función para convertir ciclos a microsegundos
uint32_t TimerDWT::cycles_to_microseconds(uint32_t cycles) {
    // STM32F411 típicamente corre a 100MHz, ajusta si es diferente
    return cycles / (SystemCoreClock / 1000000);
}