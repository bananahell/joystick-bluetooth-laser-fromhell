#include <msp430.h>
#include <stdint.h>

#include "libs/adc12.h"
#include "libs/i2c.h"
#include "libs/lcd.h"

#define CLK_FREQ 1048576
#define CLK_HALF_MSEC 525
#define CLK_TWOHALF_MSEC 2621

void initConfig() {
  // P2.4 <-- Timer A2 canal 1 (rotor horizontal)
  P2REN &= ~BIT4;
  P2DIR |= BIT4;
  P2SEL |= BIT4;
  // P2.5 <-- Timer A2 canal 2 (rotor vertical)
  P2REN &= ~BIT5;
  P2DIR |= BIT5;
  P2SEL |= BIT5;

  // Timer A2 com mode up e SMclk
  TA2CTL = TASSEL__SMCLK | MC__UP | TACLR;
  TA2CCTL1 = OUTMOD_6;
  TA2CCTL2 = OUTMOD_6;

  // CCR0 arbitrario grandao e comeca em 0 graus (0.5 ms)
  TA2CCR0 = CLK_TWOHALF_MSEC;
  TA2CCR1 = CLK_HALF_MSEC - 1;
  TA2CCR2 = CLK_HALF_MSEC - 1;
}

int main() {
  WDTCTL = WDTPW | WDTHOLD;  // stop watchdog timer

  adcResultX = 0;
  adcResultY = 0;

  adc12ConfigRepSeq();
  initConfig();

  __enable_interrupt();

  while (1) {
    if (adcResultX < 0) {
      TA2CCR1 = CLK_HALF_MSEC;
    } else if (adcResultX > 255) {
      TA2CCR1 = CLK_TWOHALF_MSEC;
    } else {
      TA2CCR1 = (adcResultX << 3) + CLK_HALF_MSEC;
    }
    if (adcResultY < 0) {
      TA2CCR2 = CLK_HALF_MSEC;
    } else if (adcResultY > 255) {
      TA2CCR2 = CLK_TWOHALF_MSEC;
    } else {
      TA2CCR2 = (adcResultY << 3) + CLK_HALF_MSEC;
    }
  }
}
