#ifndef ADC12_H
#define ADC12_H

#include <stdint.h>

volatile uint16_t adcResultX;
volatile uint16_t adcResultY;

/**
 * @brief Configura MEM 0 e 1 nos pinos 6.0 e 6.1 (joystick)
 */
void adc12ConfigRepSeq();

#endif  // ADC12_H
