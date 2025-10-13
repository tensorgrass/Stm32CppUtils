#ifndef TIMER_DWT_HPP
#define TIMER_DWT_HPP

#include <cstdint>

class TimerDWT {
public:
    TimerDWT();
    ~TimerDWT();

    void start();
    uint32_t getElapsedTime(); // Returns elapsed time in microseconds

    uint32_t start_cycles;
    uint32_t end_cycles;
    uint32_t elapsed_cycles;
    uint32_t elapsed_microseconds;
private:
    // Función para convertir ciclos a microsegundos
    uint32_t cycles_to_microseconds(uint32_t cycles);
};

#endif // TIMER_DWT_HPP