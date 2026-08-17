#ifndef TUNING_TARGETS_H
#define TUNING_TARGETS_H

#include <stdint.h>

typedef enum{
    TUNING_TARGET_FREQUENCY = 0,
    TUNING_TARGET_VREFA     = 1,
    TUNING_TARGET_VREFB     = 2,
    TUNING_TARGET_AUX_DUTY  = 3
} TuningTarget_e;

extern volatile TuningTarget_e gTuningTarget;

void tuningTargetsInit(void);

void tuningApplyStep(int16_t direction);

uint16_t tuningGetVrefACode(void);
uint16_t tuningGetVrefBCode(void);
int16_t  tuningGegtAuxDutyOffset(void);

#endif