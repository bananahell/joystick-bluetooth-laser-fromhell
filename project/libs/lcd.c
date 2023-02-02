#include "lcd.h"

#include <msp430.h>

#include "i2c.h"

void lcdConfig() {
  lcdWriteNib(0x3, LCD_INSTR);
  lcdWriteNib(0x3, LCD_INSTR);
  lcdWriteNib(0x3, LCD_INSTR);
  lcdWriteNib(0x2, LCD_INSTR);
  lcdWriteByte(0x28, LCD_INSTR);
  lcdWriteByte(0x0F, LCD_INSTR);
  lcdWriteByte(0x01, LCD_INSTR);
}

void lcdWriteNib(uint8_t nib, uint8_t isChar) {
  nib = nib << 4;
  i2cSend(0x27, nib | LCD_BL | LCD_WRITE | isChar);
  i2cSend(0x27, nib | LCD_BL | LCD_EN | LCD_WRITE | isChar);
  i2cSend(0x27, nib | LCD_BL | LCD_WRITE | isChar);
}

void lcdWriteByte(uint8_t byte, uint8_t isChar) {
  lcdWriteNib(byte >> 4, isChar);
  lcdWriteNib(byte & 0x0F, isChar);
}

void lcdPrint(char* str) {
  while (*str) {
    lcdWriteByte(*str++, LCD_CHAR);
  }
}
