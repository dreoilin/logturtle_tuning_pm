#ifndef HRPWM_CONTROL_H
#define HRPWM_CONTROL_H

#include "driverlib.h"
#include <stdint.h>

typedef struct
{
    uint16_t redCoarse;
    uint16_t redFine;
    uint16_t fedCoarse;
    uint16_t fedFine;
} HRPWMDeadtimeConfig;

// Tune these live from CCS; channels 4 and 5 are derived from 2 and 3.
extern volatile HRPWMDeadtimeConfig gHrpwmDeadtimeConfig[6];
extern volatile uint16_t gAuxInterruptLeadTicks[6];

void configurePowerStageHRPWMs(uint32_t masterPeriod);
void refreshPowerStageHRPWMConfig(uint32_t masterPeriod);
void precomputePhaseShiftPeriodsForCLA(uint32_t basePeriod);

#endif
