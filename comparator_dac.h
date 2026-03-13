#ifndef COMPARATOR_DAC_H
#define COMPARATOR_DAC_H

#include "driverlib.h"

// Configure DACA and DACB using voltage targets in volts.
void configureComparatorDACOffsets(float32_t voltageA, float32_t voltageB);

#endif
