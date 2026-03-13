#include "phase_triggers.h"
#include "driverlib.h"
#include "cla_cpu_shared.h"

void configureLagLeadHardwareTriggers(void)
{
    Interrupt_register(INT_XINT1, &xintLeadIsr);
    Interrupt_register(INT_XINT2, &xintLagIsr);

    GPIO_setDirectionMode(16U, GPIO_DIR_MODE_IN);
    GPIO_setDirectionMode(24U, GPIO_DIR_MODE_IN);
    GPIO_setPadConfig(16U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setPadConfig(24U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(16U, GPIO_QUAL_6SAMPLE);
    GPIO_setQualificationMode(24U, GPIO_QUAL_6SAMPLE);

    GPIO_setInterruptPin(16U, GPIO_INT_XINT1);
    GPIO_setInterruptType(GPIO_INT_XINT1, GPIO_INT_TYPE_RISING_EDGE);
    GPIO_enableInterrupt(GPIO_INT_XINT1);

    GPIO_setInterruptPin(24U, GPIO_INT_XINT2);
    GPIO_setInterruptType(GPIO_INT_XINT2, GPIO_INT_TYPE_RISING_EDGE);
    GPIO_enableInterrupt(GPIO_INT_XINT2);

    Interrupt_enable(INT_XINT1);
    Interrupt_enable(INT_XINT2);
}

void configureClaTuningTriggers(void)
{
    // Configure GPIO125
    GPIO_setDirectionMode(125U, GPIO_DIR_MODE_IN);
    GPIO_setPadConfig(125U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(125U, GPIO_QUAL_SYNC);

    // Configure GPIO29
    GPIO_setDirectionMode(29U, GPIO_DIR_MODE_IN);
    GPIO_setPadConfig(29U, GPIO_PIN_TYPE_PULLUP);
    GPIO_setQualificationMode(29U, GPIO_QUAL_SYNC);

}

__interrupt void xintLeadIsr(void)
{
    if(claToCpuMsg.state_active == 0U)
    {
        cpuToClaMsg.cmd_direction = PHASE_LEAD;
        cpuToClaMsg.cmd_cycles    = N_PHASE_CYCLES;
        cpuToClaMsg.cmd_seq++;
    }

    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}

__interrupt void xintLagIsr(void)
{
    if(claToCpuMsg.state_active == 0U)
    {
        cpuToClaMsg.cmd_direction = PHASE_LAG;
        cpuToClaMsg.cmd_cycles    = N_PHASE_CYCLES;
        cpuToClaMsg.cmd_seq++;
    }

    Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP1);
}
