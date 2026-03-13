#ifndef CLA_CPU_SHARED_H
#define CLA_CPU_SHARED_H

#include <stdint.h>

// Phase command values
#define PHASE_NONE 0U
#define PHASE_LAG  1U
#define PHASE_LEAD 2U

// Frequency mode values for CLA tuning
#define CLA_FREQ_MODE_NORMAL 0U
#define CLA_FREQ_MODE_FAST   1U
#define CLA_FREQ_MODE_SLOW   2U

// Adjustable cycle count for +/- 90 deg accumulation
#define N_PHASE_CYCLES 4U
#define PHASE_DEN      (4U * N_PHASE_CYCLES)

typedef struct
{
	uint32_t normal;
	uint32_t slow;
	uint32_t fast;
} ClaQ8Triplet;

// CPU -> CLA mailbox (CpuToCla1MsgRAM): CPU writes, CLA reads.
typedef struct
{
	uint16_t cmd_direction;
	uint16_t cmd_cycles;
	uint16_t cmd_seq;
	uint16_t reserved0;

	uint16_t epwm2_int_lead_ticks;
	uint16_t epwm3_int_lead_ticks;
	uint16_t reserved2;
	uint16_t reserved3;

	ClaQ8Triplet epwm1_period_hr_q8;
	ClaQ8Triplet epwm1_cmpa_hr_q8;
	ClaQ8Triplet aux_period_hr_q8;
	ClaQ8Triplet aux_cmpa_hr_q8;
} CpuToClaMsg;

// CLA -> CPU mailbox (Cla1ToCpuMsgRAM): CLA writes, CPU reads.
typedef struct
{
	uint16_t state_direction;
	uint16_t state_cycles_remaining;
	uint16_t state_active;
	uint16_t cmd_ack_seq;
	uint32_t done_count;

	uint16_t tuning_pin_29;
	uint16_t tuning_pin_125;
	uint16_t tuning_xnor;
	uint16_t tuning_mode;

	int16_t offset_normal;
	int16_t offset_fast;
	int16_t offset_slow;
	uint16_t reserved1;
} ClaToCpuMsg;

extern volatile CpuToClaMsg cpuToClaMsg;
extern volatile ClaToCpuMsg claToCpuMsg;

#endif
