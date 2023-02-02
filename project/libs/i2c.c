#include "i2c.h"

#include <msp430.h>

uint8_t i2cSend(uint8_t addr, uint8_t data) {
  UCB0I2CSA = addr;
  UCB0CTL1 |= UCTR | UCTXSTT;
  UCB0TXBUF = data;
  while (UCB0CTL1 & UCTXSTT) {}
  UCB0CTL1 |= UCTXSTP;
  while (UCB0CTL1 & UCTXSTP) {}
  if (UCB1IFG & UCNACKIFG) {
    return 1;
  }
  return 0;
}

void i2cConfig() {
  // Master (data 3.0 | clk 3.1)
  UCB0CTL1 = UCSWRST;
  UCB0CTL0 = UCMST | UCMODE_3 | UCSYNC;
  UCB0CTL1 |= UCSSEL__SMCLK;
  UCB0BRW = 100;  // 1M / 10 = 100k
  P3SEL |= BIT0 | BIT1;
  // *** DANGER ZONE ***
  P3REN |= BIT0 | BIT1;
  P3OUT |= BIT0 | BIT1;
  // *******************
  UCB0CTL1 &= ~UCSWRST;

  // Slave (data 4.1 | clk 4.2)
  UCB1CTL1 = UCSWRST;
  UCB1CTL0 = UCMODE_3 | UCSYNC;
  P4SEL |= BIT1 | BIT2;
  // *** DANGER ZONE ***
  P4REN |= BIT1 | BIT2;
  P4OUT |= BIT1 | BIT2;
  // *******************
  UCB1I2COA = 0x34;
  UCB1CTL1 &= ~UCSWRST;
  // useless
  UCB1IE |= UCTXIE | UCRXIE;
}
/*
#pragma vector = USCI_B1_VECTOR
__interrupt void escravo() {
  switch (UCB1IV) {
    case USCI_I2C_UCRXIFG:
      rx = UCB1RXBUF;
      break;
    case USCI_I2C_UCTXIFG:
      UCB1TXBUF = rx;
      break;
    default:
      break;
  }
}
*/