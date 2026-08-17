#include "driverlib.h"
#include "board.h"
#include "epwm_interrupts.h"

static __interrupt void epwm2Isr(void)
{
    EPWM_clearEventTriggerInterruptFlag(myEPWM2_BASE);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP3);
}

static __interrupt void epwm3Isr(void)
{
    EPWM_clearEventTriggerInterruptFlag(myEPWM3_BASE);
    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP3);
}

void configureEPWM2EPWM3Interrupts(void)
{
    Interrupt_register(INT_EPWM2, &epwm2Isr);
    Interrupt_register(INT_EPWM3, &epwm3Isr);

    EPWM_clearEventTriggerInterruptFlag(myEPWM2_BASE);
    EPWM_clearEventTriggerInterruptFlag(myEPWM3_BASE);

    Interrupt_enable(INT_EPWM2);
    Interrupt_enable(INT_EPWM3);
}
