#include "ne_ds.h"
#include "TX_PM_MODEL_d3b57d61_1_ds_sys_struct.h"
#include "TX_PM_MODEL_d3b57d61_1_ds_obs_exp.h"
#include "TX_PM_MODEL_d3b57d61_1_ds.h"
#include "TX_PM_MODEL_d3b57d61_1_ds_externals.h"
#include "TX_PM_MODEL_d3b57d61_1_ds_external_struct.h"
#include "ssc_ml_fun.h"
int32_T TX_PM_MODEL_d3b57d61_1_ds_obs_exp ( const NeDynamicSystem * sys ,
const NeDynamicSystemInput * t1 , NeDsMethodOutput * out ) { ( void ) t1 ;
out -> mOBS_EXP . mX [ 0 ] = 0.0 ; out -> mOBS_EXP . mX [ 1 ] = 0.0 ; out ->
mOBS_EXP . mX [ 2 ] = 0.0 ; out -> mOBS_EXP . mX [ 3 ] = 0.0 ; out ->
mOBS_EXP . mX [ 4 ] = 0.0 ; out -> mOBS_EXP . mX [ 5 ] = 0.0 ; out ->
mOBS_EXP . mX [ 6 ] = 0.0 ; out -> mOBS_EXP . mX [ 7 ] = 0.0 ; out ->
mOBS_EXP . mX [ 8 ] = 0.0 ; out -> mOBS_EXP . mX [ 9 ] = 0.0 ; out ->
mOBS_EXP . mX [ 10 ] = 0.0 ; out -> mOBS_EXP . mX [ 11 ] = 0.0 ; out ->
mOBS_EXP . mX [ 12 ] = 0.0 ; out -> mOBS_EXP . mX [ 13 ] = 0.0 ; out ->
mOBS_EXP . mX [ 14 ] = 0.0 ; out -> mOBS_EXP . mX [ 15 ] = 0.0 ; out ->
mOBS_EXP . mX [ 16 ] = 0.0 ; out -> mOBS_EXP . mX [ 17 ] = 0.0 ; out ->
mOBS_EXP . mX [ 18 ] = 0.0 ; out -> mOBS_EXP . mX [ 19 ] = 0.0 ; out ->
mOBS_EXP . mX [ 20 ] = 0.0 ; out -> mOBS_EXP . mX [ 21 ] = 0.0 ; out ->
mOBS_EXP . mX [ 22 ] = 0.0 ; out -> mOBS_EXP . mX [ 23 ] = 0.0 ; out ->
mOBS_EXP . mX [ 24 ] = 0.0 ; out -> mOBS_EXP . mX [ 25 ] = 0.0 ; out ->
mOBS_EXP . mX [ 26 ] = 0.0 ; out -> mOBS_EXP . mX [ 27 ] = 0.0 ; out ->
mOBS_EXP . mX [ 28 ] = 0.0 ; out -> mOBS_EXP . mX [ 29 ] = 0.0 ; out ->
mOBS_EXP . mX [ 30 ] = 0.0 ; out -> mOBS_EXP . mX [ 31 ] = 0.0 ; out ->
mOBS_EXP . mX [ 32 ] = 0.0 ; out -> mOBS_EXP . mX [ 33 ] = 0.0 ; out ->
mOBS_EXP . mX [ 34 ] = 0.0 ; out -> mOBS_EXP . mX [ 35 ] = 0.0 ; out ->
mOBS_EXP . mX [ 36 ] = 0.0 ; out -> mOBS_EXP . mX [ 37 ] = 0.0 ; out ->
mOBS_EXP . mX [ 38 ] = 0.0 ; out -> mOBS_EXP . mX [ 39 ] = 0.0 ; out ->
mOBS_EXP . mX [ 40 ] = 0.0 ; out -> mOBS_EXP . mX [ 41 ] = 0.0 ; out ->
mOBS_EXP . mX [ 42 ] = 0.0 ; out -> mOBS_EXP . mX [ 43 ] = 0.0 ; out ->
mOBS_EXP . mX [ 44 ] = 0.0 ; out -> mOBS_EXP . mX [ 45 ] = 0.0 ; out ->
mOBS_EXP . mX [ 46 ] = 0.0 ; out -> mOBS_EXP . mX [ 47 ] = 0.0 ; out ->
mOBS_EXP . mX [ 48 ] = 0.0 ; out -> mOBS_EXP . mX [ 49 ] = 0.0 ; out ->
mOBS_EXP . mX [ 50 ] = 0.0 ; out -> mOBS_EXP . mX [ 51 ] = 0.0 ; out ->
mOBS_EXP . mX [ 52 ] = 0.0 ; ( void ) sys ; ( void ) out ; return 0 ; }
