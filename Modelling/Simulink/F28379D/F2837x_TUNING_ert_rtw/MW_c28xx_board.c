#include "c2000BoardSupport.h"
#include "MW_f2837xD_includes.h"
#include "rtwtypes.h"
#include "F2837x_TUNING.h"
#include "F2837x_TUNING_private.h"

void init_board_CLA ()
{

#ifdef CPU1

  EALLOW;

#ifdef MW_DAC_CHANNEL_A

  DevCfgRegs.CPUSEL14.bit.DAC_A = 0U;

#endif

#ifdef MW_DAC_CHANNEL_B

  DevCfgRegs.CPUSEL14.bit.DAC_B = 0U;

#endif

#ifdef MW_DAC_CHANNEL_C

  DevCfgRegs.CPUSEL14.bit.DAC_C = 0U;

#endif

  /* Assign SDFM modules to CPU1 */
#ifdef MW_SDFM_1

  DevCfgRegs.CPUSEL4.bit.SD1 = 0U;

#endif

#ifdef MW_SDFM_2

  DevCfgRegs.CPUSEL4.bit.SD2 = 0U;

#endif

#ifdef MW_SDFM_3

  DevCfgRegs.CPUSEL4.bit.SD3 = 0U;

#endif

#ifdef MW_SDFM_4

  DevCfgRegs.CPUSEL4.bit.SD4 = 0U;

#endif

  /* Assign used PWM modules to CPU1 */
  DevCfgRegs.CPUSEL0.bit.EPWM1 = 0U;

  /* Assign used SPI modules to CPU1 */
#ifdef MW_SPI_A

  DevCfgRegs.CPUSEL6.bit.SPI_A = 0U;

#endif

#ifdef MW_SPI_B

  DevCfgRegs.CPUSEL6.bit.SPI_B = 0U;

#endif

#ifdef MW_SPI_C

  DevCfgRegs.CPUSEL6.bit.SPI_C = 0U;

#endif

#ifdef MW_SPI_D

  DevCfgRegs.CPUSEL6.bit.SPI_D = 0U;

#endif

#if defined MW_CMPSS1_COMPH || defined MW_CMPSS1_COMPL

  DevCfgRegs.CPUSEL12.bit.CMPSS1 = 0U;

#endif

#if defined MW_CMPSS2_COMPH || defined MW_CMPSS2_COMPL

  DevCfgRegs.CPUSEL12.bit.CMPSS2 = 0U;

#endif

#if defined MW_CMPSS3_COMPH || defined MW_CMPSS3_COMPL

  DevCfgRegs.CPUSEL12.bit.CMPSS3 = 0U;

#endif

#if defined MW_CMPSS4_COMPH || defined MW_CMPSS4_COMPL

  DevCfgRegs.CPUSEL12.bit.CMPSS4 = 0U;

#endif

#if defined MW_CMPSS5_COMPH || defined MW_CMPSS5_COMPL

  DevCfgRegs.CPUSEL12.bit.CMPSS5 = 0U;

#endif

#if defined MW_CMPSS6_COMPH || defined MW_CMPSS6_COMPL

  DevCfgRegs.CPUSEL12.bit.CMPSS6 = 0U;

#endif

#if defined MW_CMPSS7_COMPH || defined MW_CMPSS7_COMPL

  DevCfgRegs.CPUSEL12.bit.CMPSS7 = 0U;

#endif

#if defined MW_CMPSS8_COMPH || defined MW_CMPSS8_COMPL

  DevCfgRegs.CPUSEL12.bit.CMPSS8 = 0U;

#endif

  EDIS;

#endif                                 // #ifdef CPU1

  /* initial ePWM GPIO assignment... */
  config_ePWM_GPIO_CLA();
  EALLOW;

  /* Enable clock to ePWM */
  CpuSysRegs.PCLKCR2.bit.EPWM1 = 1U;

  /* Disable TBCLK within ePWM before module configuration */
  CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0U;
  EDIS;
  config_ePWMSyncSource_CLA();

#ifdef CPU1

  /* initial GPIO qualification settings.... */
  EALLOW;
  GpioCtrlRegs.GPAQSEL1.all = 0x0U;
  GpioCtrlRegs.GPAQSEL2.all = 0x0U;
  GpioCtrlRegs.GPBQSEL1.all = 0x0U;
  GpioCtrlRegs.GPBQSEL2.all = 0x0U;
  GpioCtrlRegs.GPCQSEL1.all = 0x0U;
  GpioCtrlRegs.GPCQSEL2.all = 0x0U;
  GpioCtrlRegs.GPDQSEL1.all = 0x0U;
  GpioCtrlRegs.GPDQSEL2.all = 0x0U;
  GpioCtrlRegs.GPEQSEL1.all = 0x0U;
  GpioCtrlRegs.GPEQSEL2.all = 0x0U;
  GpioCtrlRegs.GPFQSEL1.all = 0x0U;
  EDIS;

#endif                                 // #ifdef CPU1

}
