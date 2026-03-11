#include "ne_ds.h"
#include "TX_PM_MODEL_d3b57d61_1_ds_sys_struct.h"
#include "TX_PM_MODEL_d3b57d61_1_ds_obs_all.h"
#include "TX_PM_MODEL_d3b57d61_1_ds.h"
#include "TX_PM_MODEL_d3b57d61_1_ds_externals.h"
#include "TX_PM_MODEL_d3b57d61_1_ds_external_struct.h"
#include "ssc_ml_fun.h"
int32_T TX_PM_MODEL_d3b57d61_1_ds_obs_all ( const NeDynamicSystem * sys ,
const NeDynamicSystemInput * t5 , NeDsMethodOutput * out ) { real_T CN1_i ;
real_T CN1_n_v ; real_T CN1_p_v ; real_T Controlled_Voltage_Source_i ; real_T
L_p_v ; real_T t1 ; real_T t2 ; out -> mOBS_ALL . mX [ 22UL ] = 0.0 ; CN1_i =
( - t5 -> mX . mX [ 3UL ] + t5 -> mX . mX [ 4UL ] * 1.0E-9 ) + t5 -> mX . mX
[ 0UL ] ; CN1_n_v = ( ( ( - t5 -> mX . mX [ 1UL ] + t5 -> mX . mX [ 0UL ] * -
1.0E-6 ) + t5 -> mX . mX [ 3UL ] * 2.0E-6 ) + t5 -> mX . mX [ 4UL ] * -
1.0E-15 ) + t5 -> mX . mX [ 2UL ] ; CN1_p_v = t5 -> mX . mX [ 3UL ] * 1.0E-6
+ t5 -> mX . mX [ 2UL ] ; out -> mOBS_ALL . mX [ 3UL ] = ( ( t5 -> mX . mX [
0UL ] * 1.0E-6 + t5 -> mX . mX [ 3UL ] * - 1.0E-6 ) + t5 -> mX . mX [ 4UL ] *
1.0E-15 ) + t5 -> mX . mX [ 1UL ] ; Controlled_Voltage_Source_i = - t5 -> mX
. mX [ 0UL ] + t5 -> mX . mX [ 4UL ] * - 1.0E-9 ; L_p_v = ( t5 -> mX . mX [
3UL ] * 1.0E-6 + t5 -> mX . mX [ 2UL ] ) + t5 -> mX . mX [ 4UL ] ; t1 = L_p_v
- CN1_p_v ; t2 = CN1_p_v - CN1_n_v ; out -> mOBS_ALL . mX [ 0UL ] = CN1_i ;
out -> mOBS_ALL . mX [ 1UL ] = CN1_n_v ; out -> mOBS_ALL . mX [ 2UL ] =
CN1_p_v ; out -> mOBS_ALL . mX [ 4UL ] = t5 -> mX . mX [ 1UL ] ; out ->
mOBS_ALL . mX [ 5UL ] = t5 -> mX . mX [ 3UL ] ; out -> mOBS_ALL . mX [ 6UL ]
= 0.0 ; out -> mOBS_ALL . mX [ 7UL ] = CN1_p_v ; out -> mOBS_ALL . mX [ 8UL ]
= CN1_p_v ; out -> mOBS_ALL . mX [ 9UL ] = t5 -> mX . mX [ 2UL ] ; out ->
mOBS_ALL . mX [ 10UL ] = Controlled_Voltage_Source_i ; out -> mOBS_ALL . mX [
11UL ] = 0.0 ; out -> mOBS_ALL . mX [ 12UL ] = t5 -> mU . mX [ 1UL ] ; out ->
mOBS_ALL . mX [ 13UL ] = t5 -> mU . mX [ 1UL ] ; out -> mOBS_ALL . mX [ 14UL
] = t5 -> mU . mX [ 1UL ] ; out -> mOBS_ALL . mX [ 15UL ] = -
Controlled_Voltage_Source_i ; out -> mOBS_ALL . mX [ 16UL ] = -
Controlled_Voltage_Source_i ; out -> mOBS_ALL . mX [ 17UL ] = CN1_p_v ; out
-> mOBS_ALL . mX [ 18UL ] = CN1_p_v ; out -> mOBS_ALL . mX [ 19UL ] = -
Controlled_Voltage_Source_i ; out -> mOBS_ALL . mX [ 20UL ] = 0.0 ; out ->
mOBS_ALL . mX [ 21UL ] = 0.0 ; out -> mOBS_ALL . mX [ 23UL ] = t5 -> mD . mX
[ 0UL ] ; out -> mOBS_ALL . mX [ 24UL ] = CN1_p_v ; out -> mOBS_ALL . mX [
25UL ] = L_p_v ; out -> mOBS_ALL . mX [ 26UL ] = -
Controlled_Voltage_Source_i ; out -> mOBS_ALL . mX [ 27UL ] = t5 -> mX . mX [
0UL ] ; out -> mOBS_ALL . mX [ 28UL ] = t5 -> mX . mX [ 4UL ] * t5 -> mX . mX
[ 4UL ] * 1.0000000000000002E-12 * 1000.0 ; out -> mOBS_ALL . mX [ 29UL ] =
t5 -> mX . mX [ 4UL ] ; out -> mOBS_ALL . mX [ 30UL ] = -
Controlled_Voltage_Source_i ; out -> mOBS_ALL . mX [ 31UL ] = L_p_v ; out ->
mOBS_ALL . mX [ 32UL ] = t5 -> mU . mX [ 1UL ] ; out -> mOBS_ALL . mX [ 33UL
] = Controlled_Voltage_Source_i * - 0.02 ; out -> mOBS_ALL . mX [ 34UL ] = t5
-> mU . mX [ 0UL ] ; out -> mOBS_ALL . mX [ 35UL ] = t5 -> mU . mX [ 1UL ] ;
out -> mOBS_ALL . mX [ 36UL ] = CN1_i ; out -> mOBS_ALL . mX [ 37UL ] = 0.0 ;
out -> mOBS_ALL . mX [ 38UL ] = CN1_n_v ; out -> mOBS_ALL . mX [ 39UL ] =
CN1_n_v ; out -> mOBS_ALL . mX [ 40UL ] = t5 -> mU . mX [ 0UL ] ; out ->
mOBS_ALL . mX [ 41UL ] = t1 ; out -> mOBS_ALL . mX [ 42UL ] = CN1_p_v ; out
-> mOBS_ALL . mX [ 43UL ] = L_p_v ; out -> mOBS_ALL . mX [ 44UL ] = t2 ; out
-> mOBS_ALL . mX [ 45UL ] = CN1_n_v ; out -> mOBS_ALL . mX [ 46UL ] = CN1_p_v
; out -> mOBS_ALL . mX [ 47UL ] = t2 ; out -> mOBS_ALL . mX [ 48UL ] =
CN1_n_v ; out -> mOBS_ALL . mX [ 49UL ] = 0.0 ; out -> mOBS_ALL . mX [ 50UL ]
= CN1_n_v ; out -> mOBS_ALL . mX [ 51UL ] = CN1_n_v ; out -> mOBS_ALL . mX [
52UL ] = t1 ; ( void ) sys ; ( void ) out ; return 0 ; }
