#include <msp430.h>
#include <stdint.h>

#include "libs/adc12.h"
#include "libs/i2c.h"
#include "libs/lcd.h"

void initConfig() {
  // P1.0 = LED1 (vermelho)
  P1REN &= ~BIT0;
  P1DIR |= BIT0;

  // P4.7 = LED2 (verde)
  P4REN &= ~BIT7;
  P4DIR |= BIT7;

  // Timer A0 com mode up e Aclk
  TA0CTL = TASSEL__ACLK | MC__UP | TACLR;

  TA0CCR0 = 0x80 - 1;
  TA0CCR3 = (TA0CCR0 >> 4) - 1;
}

int main() {
  WDTCTL = WDTPW | WDTHOLD;  // stop watchdog timer

  adc12ConfigRepSeq();

  __enable_interrupt();

  while (1) {
    __low_power_mode_0();
  }
}
