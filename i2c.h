#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>

void writeByte(uint8_t reg, uint8_t val);
void writeWord(uint8_t reg, uint16_t val);
void writeBlock(uint8_t reg, uint8_t len, uint8_t * val);
uint8_t readByte(uint8_t reg);
uint16_t readWord(uint8_t reg);
uint32_t readBlock(uint8_t reg);

#endif
