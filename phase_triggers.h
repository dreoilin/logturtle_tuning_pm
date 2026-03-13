#ifndef PHASE_TRIGGERS_H
#define PHASE_TRIGGERS_H

void configureLagLeadHardwareTriggers(void);
void configureClaTuningTriggers(void);
__interrupt void xintLeadIsr(void);
__interrupt void xintLagIsr(void);

#endif
