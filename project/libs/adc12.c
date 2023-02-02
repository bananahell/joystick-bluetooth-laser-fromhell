#include "libs/adc12.h"

#include <msp430.h>
#include <stdint.h>

void adc12ConfigRepSeq() {
  // times TA0 1.0
  TA0CTL = MC__UP | TASSEL__ACLK;
  TA0CCR0 = 128 - 1;
  TA0CCR1 = TA0CCR0 >> 1;
  TA0CCTL1 = OUTMOD_6;

  // Comeca zerado por causa do ADC12ENC
  ADC12CTL0 = 0;

  // SHT0_2 = 16 ciclos de CLK
  // ON = liga
  ADC12CTL0 = ADC12SHT0_2 | ADC12ON;

  // CSTARTADD_0 = comeca a gravar no zero
  // SHS_1 = escolhe o timer TA0 1.0
  // SHP = SAMPCON
  // SSEL_0 = MODCLK (interno)
  // CONSEQ_3 = repete e sequencia
  ADC12CTL1 =
      ADC12CSTARTADD_0 | ADC12SHS_1 | ADC12SHP | ADC12SSEL_0 | ADC12CONSEQ_3;

  // TCOFF = desliga temp
  // RES_0 = resolucao de 8 bits
  // SR = vai so ate 50 ksps
  ADC12CTL2 = ADC12TCOFF | ADC12RES_0 | ADC12SR;

  // MCTL0 = MEM 0
  // SREF_0 = tensao de VSS ate VCC
  // INCH_0 = canal de entrada no 0 (pino 6.0)
  ADC12MCTL0 = ADC12SREF_0 | ADC12INCH_0;

  // MCTL1 = MEM 1
  // SREF_0 = tensao de VSS ate VCC
  // INCH_1 = canal de entrada no 1 (pino 6.1)
  // EOS = fim da leitura
  ADC12MCTL1 = ADC12SREF_0 | ADC12INCH_1 | ADC12EOS;

  // liga interrupcao no fim da leitura para ler os dois
  ADC12IE = ADC12IE1;

  // config sel de 6.0 e 6.1
  P6SEL |= BIT0 | BIT1;

  // liga ENC pra fazer funcionar e da um flano no SC
  ADC12CTL0 |= ADC12ENC;
  ADC12CTL0 &= ~ADC12SC;
  ADC12CTL0 |= ADC12SC;
}

#pragma vector = ADC12_VECTOR
__interrupt void ADC_RESULT() {
  adcResultX = ADC12MEM0;
  adcResultY = ADC12MEM1;
}
