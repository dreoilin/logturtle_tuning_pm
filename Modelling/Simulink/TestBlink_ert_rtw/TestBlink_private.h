/*
 * File: TestBlink_private.h
 *
 * Code generated for Simulink model 'TestBlink'.
 *
 * Model version                  : 1.10
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Wed Mar  4 21:17:29 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Texas Instruments->C2000
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef TestBlink_private_h_
#define TestBlink_private_h_
#include "rtwtypes.h"
#include "TestBlink_types.h"
#include "TestBlink.h"

extern void init_HRPWM ( volatile struct EPWM_REGS * EPwmRegs, uint16_T HRLOAD,
  uint16_T CTLMODE, uint16_T EDGMODE, uint16_T CMPAHR, uint16_T TBPHSHR,
  uint16_T TBPRDHR,
  uint16_T HPREIdx,uint16_T AUTOCONV,uint16_T HRUPDOWN,uint16_T HRLOADB,uint16_T
  CTLMODEB,
  uint16_T EDGMODEB,uint16_T CMPBHR,uint16_T DBREDHR,uint16_T DBFEDHR,uint16_T
  EDGMODEDB,uint16_T LOADREDMODE,uint16_T LOADFEDMODE);
extern void update_MepScaleFactor(void);

#endif                                 /* TestBlink_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
