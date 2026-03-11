/*
 * File: F2837x_TUNING.h
 *
 * Code generated for Simulink model 'F2837x_TUNING'.
 *
 * Model version                  : 1.0
 * Simulink Coder version         : 24.1 (R2024a) 19-Nov-2023
 * C/C++ source code generated on : Thu Mar  5 14:31:47 2026
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Texas Instruments->C2000
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef F2837x_TUNING_h_
#define F2837x_TUNING_h_
#ifndef F2837x_TUNING_COMMON_INCLUDES_
#define F2837x_TUNING_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "c2000BoardSupport.h"
#include "MW_f2837xD_includes.h"
#include "IQmathLib.h"
#endif                                 /* F2837x_TUNING_COMMON_INCLUDES_ */

#include <stddef.h>
#include "F2837x_TUNING_types.h"
#include "MW_target_hardware_resources.h"

extern void config_ePWMSyncSource_CLA(void);
extern void config_ePWM_GPIO_CLA (void);
extern void config_ePWM_TBSync_CLA (void);
extern void config_ePWM_XBAR(void);

/* Parameters (default storage) */
struct P_F2837x_TUNING_T_ {
  real_T Constant_Value;               /* Expression: 200
                                        * Referenced by: '<Root>/Constant'
                                        */
  real_T Constant1_Value;              /* Expression: 2
                                        * Referenced by: '<Root>/Constant1'
                                        */
};

/* Block parameters (default storage) */
extern P_F2837x_TUNING_T F2837x_TUNING_P;

/* Model entry point functions */
extern void F2837x_TUNING_initialize(void);
extern void F2837x_TUNING_step(void);
extern void F2837x_TUNING_terminate(void);
extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

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
 * '<Root>' : 'F2837x_TUNING'
 */
#endif                                 /* F2837x_TUNING_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
