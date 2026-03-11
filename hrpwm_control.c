#include "driverlib.h"
#include "cla_cpu_shared.h"

// HR deadband settings: consolidated value format is (coarse << 7) | fine
#define DB_RED_COARSE_COUNT     5U
#define DB_RED_FINE_COUNT       0U
#define DB_FED_COARSE_COUNT     5U
#define DB_FED_FINE_COUNT       0U

#define DB_RED_HR_COUNT         (((uint32_t)DB_RED_COARSE_COUNT << 7U) | DB_RED_FINE_COUNT)
#define DB_FED_HR_COUNT         (((uint32_t)DB_FED_COARSE_COUNT << 7U) | DB_FED_FINE_COUNT)

void initHRPWM1(uint32_t base, uint32_t period)
{
    EPWM_setEmulationMode(base, EPWM_EMULATION_FREE_RUN);

    EPWM_setTimeBasePeriod(base, period - 1U);
    HRPWM_setTimeBasePeriod(base, ((period - 1U) << 8U));
    EPWM_setPhaseShift(base, 0U);
    EPWM_setTimeBaseCounter(base, 0U);
    EPWM_setTimeBaseCounterMode(base, EPWM_COUNTER_MODE_UP);
    EPWM_setClockPrescaler(base, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);
    EPWM_disablePhaseShiftLoad(base);

    EPWM_setSyncOutPulseMode(base, EPWM_SYNC_OUT_PULSE_ON_COUNTER_ZERO);
    HRPWM_setCounterCompareValue(base, HRPWM_COUNTER_COMPARE_A, ((period / 2U) << 8U));
    HRPWM_setChannelBOutputPath(base, HRPWM_OUTPUT_ON_B_NORMAL);
    EPWM_setCounterCompareShadowLoadMode(base,
                                         EPWM_COUNTER_COMPARE_A,
                                         EPWM_COMP_LOAD_ON_CNTR_ZERO);

    EPWM_setActionQualifierAction(base,
                                  EPWM_AQ_OUTPUT_A,
                                  EPWM_AQ_OUTPUT_HIGH,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(base,
                                  EPWM_AQ_OUTPUT_A,
                                  EPWM_AQ_OUTPUT_LOW,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);

    EPWM_setActionQualifierAction(base,
                                  EPWM_AQ_OUTPUT_B,
                                  EPWM_AQ_OUTPUT_NO_CHANGE,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(base,
                                  EPWM_AQ_OUTPUT_B,
                                  EPWM_AQ_OUTPUT_NO_CHANGE,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);

    HRPWM_setMEPEdgeSelect(base, HRPWM_CHANNEL_A, HRPWM_MEP_CTRL_FALLING_EDGE);
    HRPWM_setMEPControlMode(base, HRPWM_CHANNEL_A, HRPWM_MEP_DUTY_PERIOD_CTRL);
    HRPWM_setCounterCompareShadowLoadEvent(base, HRPWM_CHANNEL_A, HRPWM_LOAD_ON_CNTR_ZERO);

    HRPWM_enableAutoConversion(base);
    HRPWM_enablePeriodControl(base);

    HRPWM_setDeadBandDelayMode(base, EPWM_DB_RED, true);
    HRPWM_setDeadBandDelayMode(base, EPWM_DB_FED, true);
    HRPWM_setRisingEdgeDeadBandDelayInput(base, EPWM_DB_INPUT_EPWMA);
    HRPWM_setFallingEdgeDeadBandDelayInput(base, EPWM_DB_INPUT_EPWMA);

    HRPWM_setDeadBandDelayPolarity(base, EPWM_DB_RED, EPWM_DB_POLARITY_ACTIVE_HIGH);
    HRPWM_setDeadBandDelayPolarity(base, EPWM_DB_FED, EPWM_DB_POLARITY_ACTIVE_LOW);

    EPWM_setDeadBandCounterClock(base, EPWM_DB_COUNTER_CLOCK_FULL_CYCLE);

    HRPWM_setRisingEdgeDelayLoadMode(base, HRPWM_LOAD_ON_CNTR_ZERO);
    HRPWM_setFallingEdgeDelayLoadMode(base, HRPWM_LOAD_ON_CNTR_ZERO);
    HRPWM_setRisingEdgeDelay(base, DB_RED_HR_COUNT);
    HRPWM_setFallingEdgeDelay(base, DB_FED_HR_COUNT);

    EPWM_setInterruptSource(base, EPWM_INT_TBCTR_ZERO);
    EPWM_setInterruptEventCount(base, 1U);
    EPWM_clearEventTriggerInterruptFlag(base);
    EPWM_enableInterrupt(base);
}

void initAuxiliaryHRPWM(uint32_t base, uint32_t period)
{
    uint32_t auxPeriod = period >> 2U;
    uint32_t cmpaQ8;

    EPWM_setEmulationMode(base, EPWM_EMULATION_FREE_RUN);
    EPWM_setTimeBasePeriod(base, (uint16_t)auxPeriod);
    HRPWM_setTimeBasePeriod(base, auxPeriod << 8U);
    EPWM_setTimeBaseCounter(base, 0U);
    EPWM_setTimeBaseCounterMode(base, EPWM_COUNTER_MODE_UP_DOWN);
    EPWM_setClockPrescaler(base, EPWM_CLOCK_DIVIDER_1, EPWM_HSCLOCK_DIVIDER_1);

    HRPWM_setPhaseShift(base, 0U);
    EPWM_enablePhaseShiftLoad(base);
    EPWM_setCountModeAfterSync(base, EPWM_COUNT_MODE_UP_AFTER_SYNC);

    EPWM_setSyncOutPulseMode(base, EPWM_SYNC_OUT_PULSE_ON_EPWMxSYNCIN);

    cmpaQ8 = (auxPeriod << 8U) >> 1U;
    HRPWM_setCounterCompareValue(base, HRPWM_COUNTER_COMPARE_A, cmpaQ8);
    HRPWM_setChannelBOutputPath(base, HRPWM_OUTPUT_ON_B_NORMAL);

    EPWM_setCounterCompareShadowLoadMode(base,
                                         EPWM_COUNTER_COMPARE_A,
                                         EPWM_COMP_LOAD_ON_CNTR_ZERO_PERIOD);
    HRPWM_setCounterCompareShadowLoadEvent(base,
                                           HRPWM_CHANNEL_A,
                                           HRPWM_LOAD_ON_CNTR_ZERO_PERIOD);

    EPWM_setActionQualifierAction(base,
                                  EPWM_AQ_OUTPUT_A,
                                  EPWM_AQ_OUTPUT_HIGH,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPA);
    EPWM_setActionQualifierAction(base,
                                  EPWM_AQ_OUTPUT_A,
                                  EPWM_AQ_OUTPUT_LOW,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_DOWN_CMPA);

    EPWM_setActionQualifierAction(base,
                                  EPWM_AQ_OUTPUT_B,
                                  EPWM_AQ_OUTPUT_NO_CHANGE,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_ZERO);
    EPWM_setActionQualifierAction(base,
                                  EPWM_AQ_OUTPUT_B,
                                  EPWM_AQ_OUTPUT_NO_CHANGE,
                                  EPWM_AQ_OUTPUT_ON_TIMEBASE_UP_CMPB);

    HRPWM_setMEPEdgeSelect(base, HRPWM_CHANNEL_A, HRPWM_MEP_CTRL_RISING_AND_FALLING_EDGE);
    HRPWM_setMEPControlMode(base, HRPWM_CHANNEL_A, HRPWM_MEP_DUTY_PERIOD_CTRL);
    HRPWM_enableAutoConversion(base);
    HRPWM_enablePeriodControl(base);

    HRPWM_setDeadBandDelayMode(base, EPWM_DB_RED, true);
    HRPWM_setDeadBandDelayMode(base, EPWM_DB_FED, true);
    HRPWM_setRisingEdgeDeadBandDelayInput(base, EPWM_DB_INPUT_EPWMA);
    HRPWM_setFallingEdgeDeadBandDelayInput(base, EPWM_DB_INPUT_EPWMA);
    HRPWM_setDeadBandDelayPolarity(base, EPWM_DB_RED, EPWM_DB_POLARITY_ACTIVE_HIGH);
    HRPWM_setDeadBandDelayPolarity(base, EPWM_DB_FED, EPWM_DB_POLARITY_ACTIVE_LOW);
    EPWM_setDeadBandCounterClock(base, EPWM_DB_COUNTER_CLOCK_FULL_CYCLE);

    HRPWM_setDeadbandMEPEdgeSelect(base, HRPWM_DB_MEP_CTRL_RED_FED);
    HRPWM_setRisingEdgeDelayLoadMode(base, HRPWM_LOAD_ON_CNTR_ZERO_PERIOD);
    HRPWM_setFallingEdgeDelayLoadMode(base, HRPWM_LOAD_ON_CNTR_ZERO_PERIOD);
    HRPWM_setRisingEdgeDelay(base, DB_RED_HR_COUNT);
    HRPWM_setFallingEdgeDelay(base, DB_FED_HR_COUNT);
}

void setAuxiliaryHRPWMDutyCycle(uint32_t base, uint32_t period, uint16_t dutyPercent)
{
    uint32_t auxPeriod = period >> 2U;
    uint32_t cmpaQ8 = ((auxPeriod << 8U) * (100U - dutyPercent)) / 100U;

    HRPWM_setCounterCompareValue(base, HRPWM_COUNTER_COMPARE_A, cmpaQ8);
}

void precomputePhaseShiftPeriodsForCLA(uint32_t basePeriod)
{
    const float32_t cN  = (float32_t)(basePeriod - 1U);
    const float32_t den = (float32_t)PHASE_DEN;

    const float32_t cL = cN * ((den + 1.0f) / den);
    const float32_t cH = cN * ((den - 1.0f) / den);

    cpuToClaMsg.epwm1_period_hr_q8.normal = (uint32_t)(cN * 256.0f);
    cpuToClaMsg.epwm1_period_hr_q8.slow   = (uint32_t)(cL * 256.0f);
    cpuToClaMsg.epwm1_period_hr_q8.fast   = (uint32_t)(cH * 256.0f);

    cpuToClaMsg.epwm1_cmpa_hr_q8.normal = cpuToClaMsg.epwm1_period_hr_q8.normal >> 1U;
    cpuToClaMsg.epwm1_cmpa_hr_q8.slow   = cpuToClaMsg.epwm1_period_hr_q8.slow >> 1U;
    cpuToClaMsg.epwm1_cmpa_hr_q8.fast   = cpuToClaMsg.epwm1_period_hr_q8.fast >> 1U;

    cpuToClaMsg.aux_period_hr_q8.normal = cpuToClaMsg.epwm1_period_hr_q8.normal >> 2U;
    cpuToClaMsg.aux_period_hr_q8.slow   = cpuToClaMsg.epwm1_period_hr_q8.slow >> 2U;
    cpuToClaMsg.aux_period_hr_q8.fast   = cpuToClaMsg.epwm1_period_hr_q8.fast >> 2U;

    cpuToClaMsg.aux_cmpa_hr_q8.normal = cpuToClaMsg.aux_period_hr_q8.normal >> 1U;
    cpuToClaMsg.aux_cmpa_hr_q8.slow   = cpuToClaMsg.aux_period_hr_q8.slow >> 1U;
    cpuToClaMsg.aux_cmpa_hr_q8.fast   = cpuToClaMsg.aux_period_hr_q8.fast >> 1U;
}
