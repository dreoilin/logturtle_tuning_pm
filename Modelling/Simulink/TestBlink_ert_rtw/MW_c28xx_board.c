#include "c2000BoardSupport.h"
#include "MW_f28004x_includes.h"
#include "rtwtypes.h"
#include "TestBlink.h"
#include "TestBlink_private.h"

void init_board (void)
{
  DisableDog();
  EALLOW;
  CpuSysRegs.PCLKCR0.bit.DMA = 1U;
  CpuSysRegs.PCLKCR6.bit.SD1 = 1U;
  CpuSysRegs.PCLKCR17.bit.CLB1 = 1U;
  CpuSysRegs.PCLKCR17.bit.CLB2 = 1U;
  CpuSysRegs.PCLKCR17.bit.CLB3 = 1U;
  CpuSysRegs.PCLKCR17.bit.CLB4 = 1U;
  EDIS;

#ifdef CPU1

  MW_InitSysPll(XTAL_OSC,10,0,0,1);

  //Turn on all peripherals
  //InitPeripheralClocks();
  EALLOW;
  CpuSysRegs.PCLKCR0.bit.CPUTIMER0 = 1U;
  CpuSysRegs.PCLKCR0.bit.CPUTIMER1 = 1U;
  CpuSysRegs.PCLKCR0.bit.CPUTIMER2 = 1U;
  CpuSysRegs.PCLKCR0.bit.HRPWM = 1U;
  EDIS;

#endif                                 // #ifdef CPU1

  EALLOW;

  /* Configure low speed peripheral clocks */
  ClkCfgRegs.LOSPCP.bit.LSPCLKDIV = 0U;
  EDIS;

  /* Disable and clear all CPU interrupts */
  DINT;
  IER = 0x0000U;
  IFR = 0x0000U;
  InitPieCtrl();
  InitPieVectTable();
  InitCpuTimers();

#ifdef CPU1
#endif                                 // #ifdef CPU1

  /* initial ePWM GPIO assignment... */
  config_ePWM_GPIO();
  EALLOW;

  /* Enable clock to ePWM */
  CpuSysRegs.PCLKCR2.bit.EPWM1 = 1U;
  CpuSysRegs.PCLKCR2.bit.EPWM2 = 1U;
  CpuSysRegs.PCLKCR2.bit.EPWM3 = 1U;

  /* Disable TBCLK within ePWM before module configuration */
  CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0U;
  EDIS;
  config_ePWMSyncSource();

  /* initial GPIO qualification settings.... */
  EALLOW;
  GpioCtrlRegs.GPAQSEL1.all = 0x0U;
  GpioCtrlRegs.GPAQSEL2.all = 0x0U;
  GpioCtrlRegs.GPBQSEL1.all = 0x0U;
  GpioCtrlRegs.GPBQSEL2.all = 0x0U;

  // Set the pin to digital mode by default
  GpioCtrlRegs.GPAAMSEL.bit.GPIO22 = 0U;
  GpioCtrlRegs.GPAAMSEL.bit.GPIO23 = 0U;
  EDIS;
}
