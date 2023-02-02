#ifndef LCD_H
#define LCD_H

#include <stdint.h>

#define LCD_BL 0x08
#define LCD_EN 0x04
#define LCD_READ 0x02
#define LCD_WRITE 0
#define LCD_CHAR 0x01
#define LCD_INSTR 0

void lcdConfig();

void lcdWriteNib(uint8_t, uint8_t);

void lcdWriteByte(uint8_t, uint8_t);

void lcdPrint(char*);

#endif  // LCD_H
