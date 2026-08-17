#ifndef SPI_REFERENCE_H
#define SPI_REFERENCE_H

#include <stdint.h>

#define SPI_REF_GPIO_DIN 52U
#define SPI_REF_GPIO_SCK 94U
#define SPI_REF_GPIO_CSLD 65U

#define LTC1661_CMD_WRITE_UPDATE_A 0x9U
#define LTC1661_CMD_WRITE_UPDATE_B 0xAU

#define SPI_REF_CHANNEL_A 0U 
#define SPI_REF_CHANNEL_B 1U 

#define LTC1661_CODE_MAX 1023U

void spiReferenceInit(void);

void spiReferenceWriteCode(uint16_t channel, uint16_t code10);

void spiReferenceSetVoltage(uint16_t channel, float volts, float vref);

#endif