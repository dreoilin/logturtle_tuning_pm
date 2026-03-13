#include "comparator_dac.h"
#include "device.h"

#define COMP_DAC_REFERENCE_VOLTS 3.0f
#define COMP_DAC_MAX_CODE        4095U

static inline uint16_t voltageToDacCode(float32_t voltage)
{
    float32_t normalized;
    float32_t scaled;

    if(voltage <= 0.0f)
    {
        return 0U;
    }

    if(voltage >= COMP_DAC_REFERENCE_VOLTS)
    {
        return COMP_DAC_MAX_CODE;
    }

    normalized = voltage / COMP_DAC_REFERENCE_VOLTS;
    scaled = (normalized * (float32_t)COMP_DAC_MAX_CODE) + 0.5f;
    return (uint16_t)scaled;
}

void configureComparatorDACOffsets(float32_t voltageA, float32_t voltageB)
{
    uint16_t dacCodeA;
    uint16_t dacCodeB;

    dacCodeA = voltageToDacCode(voltageA);
    dacCodeB = voltageToDacCode(voltageB);

    DAC_setReferenceVoltage(DACA_BASE, DAC_REF_ADC_VREFHI);
    DAC_setReferenceVoltage(DACB_BASE, DAC_REF_ADC_VREFHI);

    DAC_setLoadMode(DACA_BASE, DAC_LOAD_SYSCLK);
    DAC_setLoadMode(DACB_BASE, DAC_LOAD_SYSCLK);

    DAC_enableOutput(DACA_BASE);
    DAC_enableOutput(DACB_BASE);

    DAC_setShadowValue(DACA_BASE, dacCodeA);
    DAC_setShadowValue(DACB_BASE, dacCodeB);

    DEVICE_DELAY_US(10);
}
