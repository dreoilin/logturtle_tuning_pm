#include "ne_ds.h"
#include "TX_PM_MODEL_d3b57d61_1_ds_sys_struct.h"
#include "TX_PM_MODEL_d3b57d61_1_ds_log.h"
#include "TX_PM_MODEL_d3b57d61_1_ds.h"
#include "TX_PM_MODEL_d3b57d61_1_ds_externals.h"
#include "TX_PM_MODEL_d3b57d61_1_ds_external_struct.h"
#include "ssc_ml_fun.h"
int32_T TX_PM_MODEL_d3b57d61_1_ds_log ( const NeDynamicSystem * sys , const
NeDynamicSystemInput * t5 , NeDsMethodOutput * out ) { real_T CN1_i ; real_T
CN1_n_v ; real_T CN1_p_v ; real_T Controlled_Voltage_Source_i ; real_T L_p_v
; real_T Voltage_Sensor_V ; real_T t2 ; CN1_i = ( - t5 -> mX . mX [ 3UL ] +
t5 -> mX . mX [ 4UL ] * 1.0E-9 ) + t5 -> mX . mX [ 0UL ] ; CN1_n_v = ( ( ( -
t5 -> mX . mX [ 1UL ] + t5 -> mX . mX [ 0UL ] * - 1.0E-6 ) + t5 -> mX . mX [
3UL ] * 2.0E-6 ) + t5 -> mX . mX [ 4UL ] * - 1.0E-15 ) + t5 -> mX . mX [ 2UL
] ; CN1_p_v = t5 -> mX . mX [ 3UL ] * 1.0E-6 + t5 -> mX . mX [ 2UL ] ; out ->
mLOG . mX [ 5UL ] = CN1_i * CN1_i * 1.0E-9 ; out -> mLOG . mX [ 3UL ] = ( (
t5 -> mX . mX [ 0UL ] * 1.0E-6 + t5 -> mX . mX [ 3UL ] * - 1.0E-6 ) + t5 ->
mX . mX [ 4UL ] * 1.0E-15 ) + t5 -> mX . mX [ 1UL ] ; out -> mLOG . mX [ 10UL
] = t5 -> mX . mX [ 3UL ] * t5 -> mX . mX [ 3UL ] * 1.0E-9 ;
Controlled_Voltage_Source_i = - t5 -> mX . mX [ 0UL ] + t5 -> mX . mX [ 4UL ]
* - 1.0E-9 ; L_p_v = ( t5 -> mX . mX [ 3UL ] * 1.0E-6 + t5 -> mX . mX [ 2UL ]
) + t5 -> mX . mX [ 4UL ] ; out -> mLOG . mX [ 31UL ] =
Controlled_Voltage_Source_i * Controlled_Voltage_Source_i * 0.02 ; out ->
mLOG . mX [ 37UL ] = CN1_i * CN1_n_v ; Voltage_Sensor_V = L_p_v - CN1_p_v ;
t2 = CN1_p_v - CN1_n_v ; out -> mLOG . mX [ 0UL ] = CN1_i ; out -> mLOG . mX
[ 1UL ] = CN1_n_v ; out -> mLOG . mX [ 2UL ] = CN1_p_v ; out -> mLOG . mX [
4UL ] = t5 -> mX . mX [ 1UL ] ; out -> mLOG . mX [ 6UL ] = t5 -> mX . mX [
3UL ] ; out -> mLOG . mX [ 7UL ] = CN1_p_v ; out -> mLOG . mX [ 8UL ] =
CN1_p_v ; out -> mLOG . mX [ 9UL ] = t5 -> mX . mX [ 2UL ] ; out -> mLOG . mX
[ 11UL ] = Controlled_Voltage_Source_i ; out -> mLOG . mX [ 12UL ] = t5 -> mU
. mX [ 1UL ] ; out -> mLOG . mX [ 13UL ] = t5 -> mU . mX [ 1UL ] ; out ->
mLOG . mX [ 14UL ] = t5 -> mU . mX [ 1UL ] ; out -> mLOG . mX [ 15UL ] = -
Controlled_Voltage_Source_i ; out -> mLOG . mX [ 16UL ] = -
Controlled_Voltage_Source_i ; out -> mLOG . mX [ 17UL ] = CN1_p_v ; out ->
mLOG . mX [ 18UL ] = CN1_p_v ; out -> mLOG . mX [ 19UL ] = -
Controlled_Voltage_Source_i ; out -> mLOG . mX [ 20UL ] = t5 -> mD . mX [ 0UL
] ; out -> mLOG . mX [ 21UL ] = CN1_p_v ; out -> mLOG . mX [ 22UL ] = L_p_v ;
out -> mLOG . mX [ 23UL ] = - Controlled_Voltage_Source_i ; out -> mLOG . mX
[ 24UL ] = t5 -> mX . mX [ 0UL ] ; out -> mLOG . mX [ 25UL ] = t5 -> mX . mX
[ 4UL ] * t5 -> mX . mX [ 4UL ] * 1.0000000000000002E-12 * 1000.0 ; out ->
mLOG . mX [ 26UL ] = t5 -> mX . mX [ 4UL ] ; out -> mLOG . mX [ 27UL ] = -
Controlled_Voltage_Source_i ; out -> mLOG . mX [ 28UL ] = L_p_v ; out -> mLOG
. mX [ 29UL ] = t5 -> mU . mX [ 1UL ] ; out -> mLOG . mX [ 30UL ] =
Controlled_Voltage_Source_i * - 0.02 ; out -> mLOG . mX [ 32UL ] = t5 -> mU .
mX [ 0UL ] ; out -> mLOG . mX [ 33UL ] = t5 -> mU . mX [ 1UL ] ; out -> mLOG
. mX [ 34UL ] = CN1_i ; out -> mLOG . mX [ 35UL ] = CN1_n_v ; out -> mLOG .
mX [ 36UL ] = CN1_n_v ; out -> mLOG . mX [ 38UL ] = t5 -> mU . mX [ 0UL ] ;
out -> mLOG . mX [ 39UL ] = Voltage_Sensor_V ; out -> mLOG . mX [ 40UL ] =
CN1_p_v ; out -> mLOG . mX [ 41UL ] = L_p_v ; out -> mLOG . mX [ 42UL ] = t2
; out -> mLOG . mX [ 43UL ] = CN1_n_v ; out -> mLOG . mX [ 44UL ] = CN1_p_v ;
out -> mLOG . mX [ 45UL ] = t2 ; out -> mLOG . mX [ 46UL ] = CN1_n_v ; out ->
mLOG . mX [ 47UL ] = CN1_n_v ; out -> mLOG . mX [ 48UL ] = CN1_n_v ; out ->
mLOG . mX [ 49UL ] = Voltage_Sensor_V ; ( void ) sys ; ( void ) out ; return
0 ; }
