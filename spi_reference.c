#include "spi_reference.h"
#include "driverlib.h"
#include "device.h"

static void spiDelay(void){
    volatile uint16_t i;
    for(i=0U; i<50U; i++){

    }
}

void spiReferenceInit(void){
    GPIO_setPinConfig(GPIO_52_GPIO52);
    GPIO_setDirectionMode(SPI_REF_GPIO_DIN, GPIO_DIR_MODE_OUT);
    GPIO_writePin(SPI_REF_GPIO_DIN, 0U);

    GPIO_setPinConfig(GPIO_94_GPIO94);
    GPIO_setDirectionMode(SPI_REF_GPIO_DIN, GPIO_DIR_MODE_OUT);
    GPIO_writePin(SPI_REF_GPIO_DIN, 0U);

    GPIO_setPinConfig(GPIO_65_GPIO65);
    GPIO_setDirectionMode(SPI_REF_GPIO_DIN, GPIO_DIR_MODE_OUT);
    GPIO_writePin(SPI_REF_GPIO_DIN, 1U); //CSLD inactive

}

static void spiSendWord16(uint16_t word){
    int16_t bitIndex;
    uint16_t bitValue;

    GPIO_writePin(SPI_REF_GPIO_CSLD, 0U);
    spiDelay();

    for(bitIndex = 15; bitIndex >= 0; bitIndex--){
        bitValue = (word >> bitIndex) & 0x1U;

        GPIO_writePin(SPI_REF_GPIO_DIN, bitValue);
        spiDelay();

        GPIO_writePin(SPI_REF_GPIO_SCK, 1U);
        spiDelay();

        GPIO_writePin(SPI_REF_GPIO_SCK, 0U);
        spiDelay();
    }

    GPIO_writePin(SPI_REF_GPIO_CSLD, 1U);
    spiDelay();
}

void spiReferenceWriteCode(uint16_t channel, uint16_t code10){
    uint16_t command;
    uint16_t code;
    uint16_t word;

    command = (channel == SPI_REF_CHANNEL_B) ? LTC1661_CMD_WRITE_UPDATE_B : LTC1661_CMD_WRITE_UPDATE_A;

    code = code10;
    if(code > LTC1661_CODE_MAX){
        code = LTC1661_CODE_MAX;
    }

    word = (uint16_t)((command<<12)|(code<<2));

    spiSendWord16(word);
}

void spiReferenceSetVoltage(uint16_t channel, float volts, float vref){
    float ratio;
    uint16_t code10;

    ratio = volts / vref;

    if(ratio < 0.0f){
        ratio = 0.0f;
    }
    else if(ratio>1.0f){
        ratio = 1.0f;
    }

    code10 = (uint16_t)(ratio * (float)LTC1661_CODE_MAX);

    spiReferenceWriteCode(channel, code10);
}