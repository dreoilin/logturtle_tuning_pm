#include "c2000BoardSupport.h"
#include "MW_f28004x_includes.h"
#include "rtwtypes.h"
#include "TestBlink.h"
#include "TestBlink_private.h"

void config_ePWM_GPIO (void)
{
  EALLOW;

  /*-- Configure pin assignments for ePWM1 --*/
  GpioCtrlRegs.GPAGMUX1.bit.GPIO0 = 0U;
  GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1U; /* Configure GPIOGPIO0 as EPWM1A*/
  GpioCtrlRegs.GPAGMUX1.bit.GPIO1 = 0U;
  GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1U; /* Configure GPIOGPIO1 as EPWM1B*/

  /*-- Configure pin assignments for ePWM2 --*/
  GpioCtrlRegs.GPAGMUX1.bit.GPIO2 = 0U;
  GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1U; /* Configure GPIOGPIO2 as EPWM2A*/
  GpioCtrlRegs.GPAGMUX1.bit.GPIO3 = 0U;
  GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1U; /* Configure GPIOGPIO3 as EPWM2B*/

  /*-- Configure pin assignments for ePWM3 --*/
  GpioCtrlRegs.GPAGMUX1.bit.GPIO4 = 0U;
  GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1U; /* Configure GPIOGPIO4 as EPWM3A*/
  GpioCtrlRegs.GPAGMUX1.bit.GPIO5 = 0U;
  GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1U; /* Configure GPIOGPIO5 as EPWM3B*/
  EDIS;
}

void init_HRPWM ( volatile struct EPWM_REGS * EPwmRegs, uint16_T HRLOAD,
                 uint16_T CTLMODE, uint16_T EDGMODE, uint16_T CMPAHR, uint16_T
                 TBPHSHR ,uint16_T TBPRDHR,uint16_T HPREIdx,uint16_T AUTOCONV,
                 uint16_T HRUPDOWN,uint16_T HRLOADB,uint16_T CTLMODEB,uint16_T
                 EDGMODEB,uint16_T CMPBHR,uint16_T DBREDHR,uint16_T DBFEDHR,
                 uint16_T EDGMODEDB,uint16_T LOADREDMODE,uint16_T LOADFEDMODE )
{
  EALLOW;
  EPwmRegs->HRCNFG.all || 0x0U;
  EPwmRegs->HRCNFG.bit.EDGMODE = EDGMODE;
  EPwmRegs->HRCNFG.bit.CTLMODE = CTLMODE;
  EPwmRegs->HRCNFG.bit.HRLOAD = HRLOAD;
  EPwmRegs->CMPA.bit.CMPAHR = CMPAHR;
  EPwmRegs->TBPHS.bit.TBPHSHR = TBPHSHR;
  EPwmRegs->TBPRDHR = TBPRDHR;
  EPwmRegs->HRPCTL.bit.HRPE = HPREIdx;
  EPwmRegs->HRCNFG.bit.AUTOCONV = AUTOCONV;
  EPwmRegs->HRPCTL.bit.TBPHSHRLOADE = HRUPDOWN;
  EPwmRegs->HRCNFG.bit.EDGMODEB = EDGMODEB;
  EPwmRegs->HRCNFG.bit.CTLMODEB = CTLMODEB;
  EPwmRegs->HRCNFG.bit.HRLOADB = HRLOADB;
  EPwmRegs->CMPB.bit.CMPBHR = CMPBHR;
  EPwmRegs->DBREDHR.bit.DBREDHR = DBREDHR;
  EPwmRegs->DBFEDHR.bit.DBFEDHR = DBFEDHR;
  EPwmRegs->HRCNFG2.bit.EDGMODEDB = EDGMODEDB;
  EPwmRegs->HRCNFG2.bit.CTLMODEDBRED = LOADREDMODE;
  EPwmRegs->HRCNFG2.bit.CTLMODEDBFED = LOADFEDMODE;
  EDIS;
}

int_T MEP_ScaleFactor;
volatile struct EPWM_REGS *ePWM[] = { &EPwm1Regs, &EPwm2Regs, &EPwm3Regs,
  &EPwm4Regs, &EPwm5Regs, &EPwm6Regs, &EPwm7Regs, &EPwm8Regs };

void update_MepScaleFactor( void )
{
  /* MEP_ScaleFactor initialized using function SFO ()*/
  while (SFO() == 0) {
  }                /* MEP_ScaleFactor calculated by MEP Cal Module            */
}

void config_ePWM_TBSync (void)
{
  /* Enable TBCLK within the EPWM*/
  EALLOW;

  /* Enable TBCLK after the ePWM configurations */
  CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1U;
  EDIS;
}

void config_ePWMSyncSource (void)
{
  /* Configuring EXTSYNCOUT source selection */
  EALLOW;
  SyncSocRegs.SYNCSELECT.bit.SYNCOUT = 0U;

  /* Configuring ePWM Sync in source selection */
  SyncSocRegs.SYNCSELECT.bit.EPWM4SYNCIN = 7U;
  SyncSocRegs.SYNCSELECT.bit.EPWM7SYNCIN = 7U;
  SyncSocRegs.SYNCSELECT.bit.EPWM1SYNCIN = 7U;
  EDIS;
}
