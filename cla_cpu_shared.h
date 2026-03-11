#ifndef CLA_CPU_SHARED_H
#define CLA_CPU_SHARED_H

#include <stdint.h>
//#include "F2837xD_device.h" // For C2000 types

#ifndef float32_t
typedef float float32_t;
#endif

// Phase command values
#define PHASE_NONE 0U
#define PHASE_LAG  1U
#define PHASE_LEAD 2U

// Adjustable cycle count for +/- 90 deg accumulation
#define N_PHASE_CYCLES 4U
#define PHASE_DEN      (4U * N_PHASE_CYCLES)

// CPU -> CLA command mailbox
extern volatile uint16_t cla_cmd_direction;
extern volatile uint16_t cla_cmd_cycles;
extern volatile uint16_t cla_cmd_seq;

// CLA -> CPU status mailbox
extern volatile uint16_t cla_state_direction;
extern volatile uint16_t cla_state_cycles_remaining;
extern volatile uint16_t cla_state_active;
extern volatile uint16_t cla_cmd_ack_seq;
extern volatile uint32_t cla_done_count;

// CLA-owned cmpa and periods for ePWM1 (Q8 consolidated format)
extern volatile uint32_t cla_period_hr_normal_q8;
extern volatile uint32_t cla_period_hr_slow_q8;
extern volatile uint32_t cla_period_hr_fast_q8;
extern volatile uint32_t cla_cmpa_hr_normal_q8;
extern volatile uint32_t cla_cmpa_hr_slow_q8;
extern volatile uint32_t cla_cmpa_hr_fast_q8;

// CLA-owned cmpa and periods for ePWM2/3 (Q8 consolidated format)
extern volatile uint32_t cla_aux_period_hr_normal_q8;
extern volatile uint32_t cla_aux_period_hr_fast_q8;
extern volatile uint32_t cla_aux_period_hr_slow_q8;
extern volatile uint32_t cla_aux_cmpa_hr_normal_q8;
extern volatile uint32_t cla_aux_cmpa_hr_fast_q8;
extern volatile uint32_t cla_aux_cmpa_hr_slow_q8;

#endif
