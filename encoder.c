#include "encoder.h"
#include "driverlib.h"
#include "cla_cpu_shared.h"
#include "tuning_targets.h"

static volatile uint32_t gEncoderFreqHz = ENCODER_FREQ_NOM_HZ;

static uint16_t gLastChannelA = 1U;

void configureEncoderPins(void){
    GPIO_setPinConfig(GPIO_40_GPIO40);
    GPIO_setDirectionMode(ENCODER_GPIO_A, GPIO_DIR_MODE_IN);
    GPIO_setPadConfig(ENCODER_GPIO_A, GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(ENCODER_GPIO_A, GPIO_QUAL_6SAMPLE);

    //GPIO_setInterruptPin(ENCODER_GPIO_A, GPIO_INT_XINT3);
    //GPIO_setInterruptType(GPIO_INT_XINT3,GPIO_INT_TYPE_RISING_EDGE);
    //GPIO_enableInterrupt(GPIO_INT_XINT3);

    //Interrupt_register(INT_XINT3, &encoderChAIsr);
    //Interrupt_enable(INT_XINT3);

    GPIO_setPinConfig(GPIO_41_GPIO41);
    GPIO_setDirectionMode(ENCODER_GPIO_B, GPIO_DIR_MODE_IN);
    GPIO_setPadConfig(ENCODER_GPIO_B, GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(ENCODER_GPIO_B, GPIO_QUAL_6SAMPLE);  

    gLastChannelA = GPIO_readPin(ENCODER_GPIO_A);
}

void encoderPollUpdate(void){
    uint16_t currentChannelA;
    uint16_t channelB;

    currentChannelA = GPIO_readPin(ENCODER_GPIO_A);

    if((currentChannelA != gLastChannelA)){
        channelB = GPIO_readPin(ENCODER_GPIO_B);

        if(currentChannelA != channelB){
            tuningApplyStep(1);
        }
        else{
            tuningApplyStep(-1);
        }

        gLastChannelA = currentChannelA;
    }
}

void encoderStepFrequency(int16_t direction){
    uint32_t currentFreq = gEncoderFreqHz;

    if(direction > 0){
        if(currentFreq <= (ENCODER_FREQ_MAX_HZ - ENCODER_FREQ_STEP_HZ)){
            currentFreq += ENCODER_FREQ_STEP_HZ;
        }
        else{
            currentFreq = ENCODER_FREQ_MAX_HZ;
        }
    }
    else{
        if(currentFreq >= (ENCODER_FREQ_MIN_HZ + ENCODER_FREQ_STEP_HZ)){
            currentFreq -= ENCODER_FREQ_STEP_HZ;
        }
        else{
            currentFreq = ENCODER_FREQ_MIN_HZ;
        }
    }
    gEncoderFreqHz = currentFreq;
}

uint32_t encoderGetCurrentPeriod(void){
    return ENCODER_F_SYSCLK_HZ / gEncoderFreqHz;
}

uint32_t encoderGetCurrentFreqHz(void){
    return gEncoderFreqHz;
}
