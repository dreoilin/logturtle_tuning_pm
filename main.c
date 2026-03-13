// Included Files
#include "driverlib.h"
#include "device.h"
#include "board.h"
#include "SFO_V8.h"
#include "cla_cpu_shared.h"
#include "hrpwm_control.h"
#include "comparator_dac.h"
#include "epwm_interrupts.h"
#include "phase_triggers.h"

// Defines
#define EPWM_TIMER_TBPRD            100UL
#define COMP_DAC_OFFSET_A_VOLTS     1.500f
#define COMP_DAC_OFFSET_B_VOLTS     1.500f

// Globals

uint16_t status;

int MEP_ScaleFactor; // Global variable used by the SFO library
                     // Result can be used for all HRPWM channels
                     // This variable is also copied to HRMSTEP
                     // register by SFO() function.

// The SFO library expects this global table of EPWM base addresses.
volatile uint32_t ePWM[] =
    {0U, myEPWM1_BASE, myEPWM2_BASE, myEPWM3_BASE, myEPWM4_BASE, myEPWM5_BASE};

// CPU -> CLA mailbox (CPU writes, CLA reads)
#pragma DATA_SECTION(cpuToClaMsg, "CpuToCla1MsgRAM")
volatile CpuToClaMsg cpuToClaMsg = {0};

// CLA -> CPU mailbox (CLA writes, CPU reads)
#pragma DATA_SECTION(claToCpuMsg, "Cla1ToCpuMsgRAM")
volatile ClaToCpuMsg claToCpuMsg = {0};

static void initializePlatform(void);
static void initializeClaControl(void);
static void initializePowerStage(void);
static void initializeControlState(void);
static void runBackgroundCalibration(void);
void error(void);

// CPU-side Interrupt Service Routines for CLA End-of-Task
__interrupt void cla1Isr1(void) { Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP11); }
__interrupt void cla1Isr2(void) { Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP11); }
__interrupt void cla1Isr3(void) { Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP11); }
__interrupt void cla1Isr4(void) { Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP11); }
__interrupt void cla1Isr5(void) { Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP11); }
__interrupt void cla1Isr6(void) { Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP11); }
__interrupt void cla1Isr7(void) { Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP11); }
__interrupt void cla1Isr8(void) { Interrupt_clearACKGroup(INTERRUPT_ACK_GROUP11); }

static void initializePlatform(void)
{
    Device_init();
    Device_initGPIO();
    Interrupt_initModule();
    Interrupt_initVectorTable();
    Board_init();
}

static void initializeClaControl(void)
{
    status = SFO_INCOMPLETE;

    configureComparatorDACOffsets(COMP_DAC_OFFSET_A_VOLTS, COMP_DAC_OFFSET_B_VOLTS);
    precomputePhaseShiftPeriodsForCLA(EPWM_TIMER_TBPRD);

    CLA_setTriggerSource(CLA_TASK_1, CLA_TRIGGER_EPWM1INT);
    CLA_setTriggerSource(CLA_TASK_2, CLA_TRIGGER_EPWM2INT);
    CLA_setTriggerSource(CLA_TASK_3, CLA_TRIGGER_EPWM3INT);

    while(status == SFO_INCOMPLETE)
    {
        status = SFO();
        if(status == SFO_ERROR)
        {
            error();
        }
    }
}

static void initializePowerStage(void)
{
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
    SysCtl_setEPWMClockDivider(SYSCTL_EPWMCLK_DIV_1);

    configurePowerStageHRPWMs(EPWM_TIMER_TBPRD);

    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);
    EPWM_forceSyncPulse(myEPWM1_BASE);
    refreshPowerStageHRPWMConfig(EPWM_TIMER_TBPRD);

    configureEPWM2EPWM3Interrupts();
}

static void initializeControlState(void)
{
    cpuToClaMsg.cmd_direction = PHASE_NONE;
    cpuToClaMsg.cmd_cycles = 0U;
    cpuToClaMsg.cmd_seq = 0U;

    claToCpuMsg.state_direction = PHASE_NONE;
    claToCpuMsg.state_cycles_remaining = 0U;
    claToCpuMsg.state_active = 0U;
    claToCpuMsg.cmd_ack_seq = cpuToClaMsg.cmd_seq;
    claToCpuMsg.done_count = 0U;
    claToCpuMsg.tuning_pin_29 = 0U;
    claToCpuMsg.tuning_pin_125 = 0U;
    claToCpuMsg.tuning_xnor = 0U;
    claToCpuMsg.tuning_mode = CLA_FREQ_MODE_NORMAL;
    claToCpuMsg.offset_normal = 0;
    claToCpuMsg.offset_fast = 0;
    claToCpuMsg.offset_slow = 0;
}

static void runBackgroundCalibration(void)
{
    status = SFO();
    if(status == SFO_ERROR)
    {
        error();
    }
}


void main(void)
{
    initializePlatform();
    initializeClaControl();
    initializePowerStage();

    configureLagLeadHardwareTriggers();
    configureClaTuningTriggers();
    initializeControlState();

    EINT;
    ERTM;

    for(;;)
    {
        runBackgroundCalibration();
        refreshPowerStageHRPWMConfig(EPWM_TIMER_TBPRD);
    }
}

void error (void)
{
    ESTOP0;
}