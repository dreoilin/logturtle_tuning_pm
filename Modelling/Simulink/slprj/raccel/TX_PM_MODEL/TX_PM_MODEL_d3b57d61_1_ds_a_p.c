#include "ne_ds.h"
#include "TX_PM_MODEL_d3b57d61_1_ds_sys_struct.h"
#include "TX_PM_MODEL_d3b57d61_1_ds_a_p.h"
#include "TX_PM_MODEL_d3b57d61_1_ds.h"
#include "TX_PM_MODEL_d3b57d61_1_ds_externals.h"
#include "TX_PM_MODEL_d3b57d61_1_ds_external_struct.h"
#include "ssc_ml_fun.h"
int32_T TX_PM_MODEL_d3b57d61_1_ds_a_p ( const NeDynamicSystem * sys , const
NeDynamicSystemInput * t1 , NeDsMethodOutput * out ) { static int32_T
_cg_const_2 [ 12 ] = { 0 , 2 , 3 , 0 , 1 , 3 , 0 , 1 , 3 , 0 , 2 , 3 } ;
static int32_T _cg_const_1 [ 6 ] = { 0 , 3 , 4 , 6 , 9 , 12 } ; ( void ) t1 ;
out -> mA_P . mNumCol = 5UL ; out -> mA_P . mNumRow = 5UL ; out -> mA_P . mJc
[ 0 ] = _cg_const_1 [ 0 ] ; out -> mA_P . mJc [ 1 ] = _cg_const_1 [ 1 ] ; out
-> mA_P . mJc [ 2 ] = _cg_const_1 [ 2 ] ; out -> mA_P . mJc [ 3 ] =
_cg_const_1 [ 3 ] ; out -> mA_P . mJc [ 4 ] = _cg_const_1 [ 4 ] ; out -> mA_P
. mJc [ 5 ] = _cg_const_1 [ 5 ] ; out -> mA_P . mIr [ 0 ] = _cg_const_2 [ 0 ]
; out -> mA_P . mIr [ 1 ] = _cg_const_2 [ 1 ] ; out -> mA_P . mIr [ 2 ] =
_cg_const_2 [ 2 ] ; out -> mA_P . mIr [ 3 ] = _cg_const_2 [ 3 ] ; out -> mA_P
. mIr [ 4 ] = _cg_const_2 [ 4 ] ; out -> mA_P . mIr [ 5 ] = _cg_const_2 [ 5 ]
; out -> mA_P . mIr [ 6 ] = _cg_const_2 [ 6 ] ; out -> mA_P . mIr [ 7 ] =
_cg_const_2 [ 7 ] ; out -> mA_P . mIr [ 8 ] = _cg_const_2 [ 8 ] ; out -> mA_P
. mIr [ 9 ] = _cg_const_2 [ 9 ] ; out -> mA_P . mIr [ 10 ] = _cg_const_2 [ 10
] ; out -> mA_P . mIr [ 11 ] = _cg_const_2 [ 11 ] ; ( void ) sys ; ( void )
out ; return 0 ; }
