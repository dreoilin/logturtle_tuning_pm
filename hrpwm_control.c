#include "hrpwm_control.h"
#include "board.h"
#include "cla_cpu_shared.h"

#define DB_COUNT_RESET          0U

static const float32_t kAuxPhaseShiftDegrees[6] =
{
    0.0f,
    0.0f,
    10.0f,
    10.0f,
    10.0f,
    10.0f
};

volatile HRPWMDeadtimeConfig gHrpwmDeadtimeConfig[6] =
{
    {0U, 0U, 0U, 0U},
    {5U, 0U, 5U, 0U},
    {5U, 0U, 5U, 0U},
    {5U, 0U, 5U, 0U},
    {5U, 0U, 5U, 0U},
    {5U, 0U, 5U, 0U}
};

volatile uint16_t gAuxInterruptLeadTicks[6] =
{
    0U,
    0U,
    2U,
    2U,
    0U,
    0U
};

static void initHRPWM1(uint32_t base, uint32_t period)
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
    HRPWM_setRisingEdgeDelay(base, DB_COUNT_RESET);
    HRPWM_setFallingEdgeDelay(base, DB_COUNT_RESET);

    EPWM_setInterruptSource(base, EPWM_INT_TBCTR_ZERO);
    EPWM_setInterruptEventCount(base, 1U);
    EPWM_clearEventTriggerInterruptFlag(base);
    EPWM_enableInterrupt(base);
}

static void initAuxiliaryHRPWM(uint32_t base, uint32_t period)
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
    HRPWM_setCounterCompareValue(base, HRPWM_COUNTER_COMPARE_B, cmpaQ8);
    HRPWM_setChannelBOutputPath(base, HRPWM_OUTPUT_ON_B_NORMAL);

    EPWM_setCounterCompareShadowLoadMode(base,
                                         EPWM_COUNTER_COMPARE_A,
                                         EPWM_COMP_LOAD_ON_CNTR_ZERO_PERIOD);
    EPWM_setCounterCompareShadowLoadMode(base,
                                         EPWM_COUNTER_COMPARE_B,
                                         EPWM_COMP_LOAD_ON_CNTR_ZERO_PERIOD);
    HRPWM_setCounterCompareShadowLoadEvent(base,
                                           HRPWM_CHANNEL_A,
                                           HRPWM_LOAD_ON_CNTR_ZERO_PERIOD);
    HRPWM_setCounterCompareShadowLoadEvent(base,
                                           HRPWM_CHANNEL_B,
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
    HRPWM_setRisingEdgeDelay(base, DB_COUNT_RESET);
    HRPWM_setFallingEdgeDelay(base, DB_COUNT_RESET);

    if(base == EPWM2_BASE)
    {
        EPWM_setInterruptSource(base, EPWM_INT_TBCTR_U_CMPB);   // Lead trigger before EPWM2A rising
        EPWM_setInterruptEventCount(base, 1U);
        EPWM_clearEventTriggerInterruptFlag(base);
        EPWM_enableInterrupt(base);
    }
    else if(base == EPWM3_BASE)
    {
        EPWM_setInterruptSource(base, EPWM_INT_TBCTR_D_CMPB);   // Lead trigger before EPWM3A falling
        EPWM_setInterruptEventCount(base, 1U);
        EPWM_clearEventTriggerInterruptFlag(base);
        EPWM_enableInterrupt(base);
    }
}

static void setHRPWMDeadtimeCounts(uint32_t base,
                                   uint16_t redCoarse,
                                   uint16_t redFine,
                                   uint16_t fedCoarse,
                                   uint16_t fedFine)
{
    uint32_t redCount;
    uint32_t fedCount;

    redCount = ((uint32_t)redCoarse << 7U) | (uint32_t)(redFine & 0x7FU);
    fedCount = ((uint32_t)fedCoarse << 7U) | (uint32_t)(fedFine & 0x7FU);

    HRPWM_setRisingEdgeDelay(base, redCount);
    HRPWM_setFallingEdgeDelay(base, fedCount);
}

static void setAuxiliaryInterruptLeadTicks(uint32_t base, uint32_t masterPeriod, uint16_t leadTicks)
{
    uint32_t cmpaQ8;
    uint32_t cmpbQ8;
    uint32_t leadQ8;
    uint32_t prdQ8;

    cmpaQ8 = HRPWM_getCounterCompareValue(base, HRPWM_COUNTER_COMPARE_A);
    leadQ8 = ((uint32_t)leadTicks << 8U);
    prdQ8 = ((masterPeriod >> 2U) << 8U);

    if(base == EPWM2_BASE)
    {
        cmpbQ8 = (cmpaQ8 > leadQ8) ? (cmpaQ8 - leadQ8) : 0U;
    }
    else if(base == EPWM3_BASE)
    {
        cmpbQ8 = cmpaQ8 + leadQ8;
        if(cmpbQ8 >= prdQ8)
        {
            cmpbQ8 = (prdQ8 > 0U) ? (prdQ8 - 1U) : 0U;
        }
    }
    else
    {
        cmpbQ8 = cmpaQ8;
    }

    HRPWM_setCounterCompareValue(base, HRPWM_COUNTER_COMPARE_B, cmpbQ8);
}

static void setAuxiliaryHRPWMPhaseDegrees(uint32_t base,
                                          uint32_t masterPeriod,
                                          float32_t phaseDegrees)
{
    float32_t auxPeriod;
    float32_t phaseAbsDeg;
    uint32_t phaseQ8;

    auxPeriod = (float32_t)(masterPeriod >> 2U);
    phaseAbsDeg = (phaseDegrees >= 0.0f) ? phaseDegrees : -phaseDegrees;

    if(phaseAbsDeg > 180.0f)
    {
        phaseAbsDeg = 180.0f;
    }

    phaseQ8 = (uint32_t)(((phaseAbsDeg * (2.0f * auxPeriod) * 256.0f) / 360.0f) + 0.5f);

    if(phaseDegrees >= 0.0f)
    {
        EPWM_setCountModeAfterSync(base, EPWM_COUNT_MODE_UP_AFTER_SYNC);
    }
    else
    {
        EPWM_setCountModeAfterSync(base, EPWM_COUNT_MODE_DOWN_AFTER_SYNC);
    }

    EPWM_enablePhaseShiftLoad(base);
    HRPWM_enablePhaseShiftLoad(base);
    HRPWM_setPhaseShift(base, phaseQ8);
}

static void configureAuxiliaryFollowerLinks(void)
{
    // ePWM4 mirrors ePWM2 compare updates.
    EPWM_setupEPWMLinks(EPWM4_BASE, EPWM_LINK_WITH_EPWM_2, EPWM_LINK_TBPRD);
    EPWM_setupEPWMLinks(EPWM4_BASE, EPWM_LINK_WITH_EPWM_2, EPWM_LINK_COMP_A);
    EPWM_setupEPWMLinks(EPWM4_BASE, EPWM_LINK_WITH_EPWM_2, EPWM_LINK_COMP_B);

    // ePWM5 mirrors ePWM3 compare updates.
    EPWM_setupEPWMLinks(EPWM5_BASE, EPWM_LINK_WITH_EPWM_3, EPWM_LINK_TBPRD);
    EPWM_setupEPWMLinks(EPWM5_BASE, EPWM_LINK_WITH_EPWM_3, EPWM_LINK_COMP_A);
    EPWM_setupEPWMLinks(EPWM5_BASE, EPWM_LINK_WITH_EPWM_3, EPWM_LINK_COMP_B);
}

static void syncFollowerRuntimeConfig(void)
{
    gHrpwmDeadtimeConfig[4].redCoarse = gHrpwmDeadtimeConfig[2].redCoarse;
    gHrpwmDeadtimeConfig[4].redFine = gHrpwmDeadtimeConfig[2].redFine;
    gHrpwmDeadtimeConfig[4].fedCoarse = gHrpwmDeadtimeConfig[2].fedCoarse;
    gHrpwmDeadtimeConfig[4].fedFine = gHrpwmDeadtimeConfig[2].fedFine;

    gHrpwmDeadtimeConfig[5].redCoarse = gHrpwmDeadtimeConfig[3].redCoarse;
    gHrpwmDeadtimeConfig[5].redFine = gHrpwmDeadtimeConfig[3].redFine;
    gHrpwmDeadtimeConfig[5].fedCoarse = gHrpwmDeadtimeConfig[3].fedCoarse;
    gHrpwmDeadtimeConfig[5].fedFine = gHrpwmDeadtimeConfig[3].fedFine;
}

static void seedAuxiliaryCompareBaseline(void)
{
    HWREG(myEPWM2_BASE + HRPWM_O_CMPA) = (cpuToClaMsg.aux_cmpa_hr_q8.normal << 8U);
    HWREG(myEPWM3_BASE + HRPWM_O_CMPA) = (cpuToClaMsg.aux_cmpa_hr_q8.normal << 8U);
}

void configurePowerStageHRPWMs(uint32_t masterPeriod)
{
    syncFollowerRuntimeConfig();

    initHRPWM1(myEPWM1_BASE, masterPeriod);
    initAuxiliaryHRPWM(myEPWM2_BASE, masterPeriod);
    initAuxiliaryHRPWM(myEPWM3_BASE, masterPeriod);
    initAuxiliaryHRPWM(myEPWM4_BASE, masterPeriod);
    initAuxiliaryHRPWM(myEPWM5_BASE, masterPeriod);

    setAuxiliaryHRPWMPhaseDegrees(myEPWM2_BASE, masterPeriod, kAuxPhaseShiftDegrees[2]);
    setAuxiliaryHRPWMPhaseDegrees(myEPWM3_BASE, masterPeriod, kAuxPhaseShiftDegrees[3]);
    setAuxiliaryHRPWMPhaseDegrees(myEPWM4_BASE, masterPeriod, kAuxPhaseShiftDegrees[4]);
    setAuxiliaryHRPWMPhaseDegrees(myEPWM5_BASE, masterPeriod, kAuxPhaseShiftDegrees[5]);

    configureAuxiliaryFollowerLinks();
    seedAuxiliaryCompareBaseline();
    refreshPowerStageHRPWMConfig(masterPeriod);
}

void refreshPowerStageHRPWMConfig(uint32_t masterPeriod)
{
    static HRPWMDeadtimeConfig appliedDeadtime[6];
    static uint16_t appliedLeadTicks[6];
    static uint16_t isInitialized = 0U;
    static const uint32_t pwmBaseByChannel[6] =
    {
        0U,
        myEPWM1_BASE,
        myEPWM2_BASE,
        myEPWM3_BASE,
        myEPWM4_BASE,
        myEPWM5_BASE
    };
    uint16_t channel;

    syncFollowerRuntimeConfig();

    for(channel = 1U; channel <= 5U; channel++)
    {
        HRPWMDeadtimeConfig requestedDeadtime;

        requestedDeadtime.redCoarse = gHrpwmDeadtimeConfig[channel].redCoarse;
        requestedDeadtime.redFine = gHrpwmDeadtimeConfig[channel].redFine;
        requestedDeadtime.fedCoarse = gHrpwmDeadtimeConfig[channel].fedCoarse;
        requestedDeadtime.fedFine = gHrpwmDeadtimeConfig[channel].fedFine;

        if((isInitialized == 0U) ||
           (appliedDeadtime[channel].redCoarse != requestedDeadtime.redCoarse) ||
           (appliedDeadtime[channel].redFine != requestedDeadtime.redFine) ||
           (appliedDeadtime[channel].fedCoarse != requestedDeadtime.fedCoarse) ||
           (appliedDeadtime[channel].fedFine != requestedDeadtime.fedFine))
        {
            setHRPWMDeadtimeCounts(pwmBaseByChannel[channel],
                                   requestedDeadtime.redCoarse,
                                   requestedDeadtime.redFine,
                                   requestedDeadtime.fedCoarse,
                                   requestedDeadtime.fedFine);
            appliedDeadtime[channel] = requestedDeadtime;
        }
    }

    cpuToClaMsg.epwm2_int_lead_ticks = gAuxInterruptLeadTicks[2];
    cpuToClaMsg.epwm3_int_lead_ticks = gAuxInterruptLeadTicks[3];

    if((isInitialized == 0U) || (appliedLeadTicks[2] != gAuxInterruptLeadTicks[2]))
    {
        setAuxiliaryInterruptLeadTicks(myEPWM2_BASE, masterPeriod, gAuxInterruptLeadTicks[2]);
        appliedLeadTicks[2] = gAuxInterruptLeadTicks[2];
    }

    if((isInitialized == 0U) || (appliedLeadTicks[3] != gAuxInterruptLeadTicks[3]))
    {
        setAuxiliaryInterruptLeadTicks(myEPWM3_BASE, masterPeriod, gAuxInterruptLeadTicks[3]);
        appliedLeadTicks[3] = gAuxInterruptLeadTicks[3];
    }

    isInitialized = 1U;
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
