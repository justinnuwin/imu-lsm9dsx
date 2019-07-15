#include "i2c.h"

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>

extern int fd;

void writeByte(uint8_t reg, uint8_t val) {
    if (i2c_smbus_write_byte_data(fd, reg, val)) {
        perror("failed to write byte");
        exit(1);
    }
}

void writeWord(uint8_t reg, uint16_t val) {
    if (i2c_smbus_write_word_data(fd, reg, val)) {
        perror("failed to write word");
        exit(1);
    }
}

void writeBlock(uint8_t reg, uint8_t len, uint8_t * val) {
    if (i2c_smbus_write_block_data(fd, reg, len, val)) {
        perror("failed to write block");
        exit(1);
    }
}

uint8_t readByte(uint8_t reg) {
    return i2c_smbus_read_byte_data(fd, reg);
}

uint16_t readWord(uint8_t reg) {
    return i2c_smbus_read_word_data(fd, reg);
}

uint32_t readBlock(uint8_t reg) {
    uint32_t res = 0;
    uint8_t len = 0;

    if ((len = i2c_smbus_read_byte_data(fd, reg))) {
        perror("failed to read byte");
        exit(1);
    }
    return res;
}

