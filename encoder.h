#ifndef ENCODER_H
#define ENCODER_H

#include <stdint.h>

#define ENCODER_GPIO_A 40U
#define ENCODER_GPIO_B 41U

#define ENCODER_F_SYSCLK_HZ 200000000UL //200 MHz

#define ENCODER_FREQ_STEP_HZ 5000UL

#define ENCODER_FREQ_MIN_HZ 800000UL
#define ENCODER_FREQ_MAX_HZ 1200000UL
#define ENCODER_FREQ_NOM_HZ 1000000UL

void configureEncoderPins(void);
void encoderPollUpdate(void);
uint32_t encoderGetCurrentPeriod(void);
uint32_t encoderGetCurrentFreqHz(void);

void encoderStepFrequency(int16_t direction);

#endif
