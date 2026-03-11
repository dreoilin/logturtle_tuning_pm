/*
 * File: TestBlink.h
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

#ifndef TestBlink_h_
#define TestBlink_h_
#ifndef TestBlink_COMMON_INCLUDES_
#define TestBlink_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "c2000BoardSupport.h"
#include "MW_f28004x_includes.h"
#include "IQmathLib.h"
#include "SFO_V8.h"
#endif                                 /* TestBlink_COMMON_INCLUDES_ */

#include "MW_c2000ISR.h"
#include <stddef.h>
#include "TestBlink_types.h"
#include "MW_target_hardware_resources.h"

void MW_InitSysPll(uint16_T clock_source, uint16_T imult, uint16_T fmult,
                   uint16_T odiv, uint16_T divsel);
extern void config_ePWMSyncSource(void);
extern void config_ePWM_GPIO (void);
extern void config_ePWM_TBSync (void);
extern void config_ePWM_XBAR(void);

/* Parameters (default storage) */
struct P_TestBlink_T_ {
  real_T Constant_Value;               /* Expression: 25
                                        * Referenced by: '<Root>/Constant'
                                        */
  real_T Constant1_Value;              /* Expression: 100
                                        * Referenced by: '<Root>/Constant1'
                                        */
};

/* Block parameters (default storage) */
extern P_TestBlink_T TestBlink_P;

/* Model entry point functions */
extern void TestBlink_initialize(void);
extern void TestBlink_step(void);
extern void TestBlink_terminate(void);
extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

#ifdef __cpluscplus

extern "C"
{

#endif

  interrupt void EPWM3_INT(void);
  interrupt void EPWM2_INT(void);
  void TestBlink_configure_interrupts (void);
  void TestBlink_unconfigure_interrupts (void);

#ifdef __cpluscplus

}

#endif

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'TestBlink'
 * '<S1>'   : 'TestBlink/Hardware Interrupt'
 * '<S2>'   : 'TestBlink/Hardware Interrupt1'
 * '<S3>'   : 'TestBlink/Hardware Interrupt/ECSoC'
 * '<S4>'   : 'TestBlink/Hardware Interrupt/ECSoC/ECSimCodegen'
 * '<S5>'   : 'TestBlink/Hardware Interrupt1/ECSoC'
 * '<S6>'   : 'TestBlink/Hardware Interrupt1/ECSoC/ECSimCodegen'
 */
#endif                                 /* TestBlink_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
