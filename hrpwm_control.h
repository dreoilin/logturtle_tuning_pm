#ifndef HRPWM_CONTROL_H
#define HRPWM_CONTROL_H

#include <stdint.h>

void initHRPWM1(uint32_t base, uint32_t period);
void initAuxiliaryHRPWM(uint32_t base, uint32_t period);
void setAuxiliaryHRPWMDutyCycle(uint32_t base, uint32_t period, uint16_t dutyPercent);
void precomputePhaseShiftPeriodsForCLA(uint32_t basePeriod);

#endif
