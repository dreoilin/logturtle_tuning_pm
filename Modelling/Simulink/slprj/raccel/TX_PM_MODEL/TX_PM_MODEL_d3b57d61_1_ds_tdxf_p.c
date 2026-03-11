#include "ne_ds.h"
#include "TX_PM_MODEL_d3b57d61_1_ds_sys_struct.h"
#include "TX_PM_MODEL_d3b57d61_1_ds_tdxf_p.h"
#include "TX_PM_MODEL_d3b57d61_1_ds.h"
#include "TX_PM_MODEL_d3b57d61_1_ds_externals.h"
#include "TX_PM_MODEL_d3b57d61_1_ds_external_struct.h"
#include "ssc_ml_fun.h"
int32_T TX_PM_MODEL_d3b57d61_1_ds_tdxf_p ( const NeDynamicSystem * sys ,
const NeDynamicSystemInput * t1 , NeDsMethodOutput * out ) { static int32_T
_cg_const_2 [ 17 ] = { 0 , 2 , 3 , 4 , 0 , 4 , 1 , 3 , 4 , 0 , 1 , 3 , 4 , 0
, 2 , 3 , 4 } ; static int32_T _cg_const_1 [ 6 ] = { 0 , 4 , 6 , 9 , 13 , 17
} ; ( void ) t1 ; out -> mTDXF_P . mNumCol = 5UL ; out -> mTDXF_P . mNumRow =
5UL ; out -> mTDXF_P . mJc [ 0 ] = _cg_const_1 [ 0 ] ; out -> mTDXF_P . mJc [
1 ] = _cg_const_1 [ 1 ] ; out -> mTDXF_P . mJc [ 2 ] = _cg_const_1 [ 2 ] ;
out -> mTDXF_P . mJc [ 3 ] = _cg_const_1 [ 3 ] ; out -> mTDXF_P . mJc [ 4 ] =
_cg_const_1 [ 4 ] ; out -> mTDXF_P . mJc [ 5 ] = _cg_const_1 [ 5 ] ; out ->
mTDXF_P . mIr [ 0 ] = _cg_const_2 [ 0 ] ; out -> mTDXF_P . mIr [ 1 ] =
_cg_const_2 [ 1 ] ; out -> mTDXF_P . mIr [ 2 ] = _cg_const_2 [ 2 ] ; out ->
mTDXF_P . mIr [ 3 ] = _cg_const_2 [ 3 ] ; out -> mTDXF_P . mIr [ 4 ] =
_cg_const_2 [ 4 ] ; out -> mTDXF_P . mIr [ 5 ] = _cg_const_2 [ 5 ] ; out ->
mTDXF_P . mIr [ 6 ] = _cg_const_2 [ 6 ] ; out -> mTDXF_P . mIr [ 7 ] =
_cg_const_2 [ 7 ] ; out -> mTDXF_P . mIr [ 8 ] = _cg_const_2 [ 8 ] ; out ->
mTDXF_P . mIr [ 9 ] = _cg_const_2 [ 9 ] ; out -> mTDXF_P . mIr [ 10 ] =
_cg_const_2 [ 10 ] ; out -> mTDXF_P . mIr [ 11 ] = _cg_const_2 [ 11 ] ; out
-> mTDXF_P . mIr [ 12 ] = _cg_const_2 [ 12 ] ; out -> mTDXF_P . mIr [ 13 ] =
_cg_const_2 [ 13 ] ; out -> mTDXF_P . mIr [ 14 ] = _cg_const_2 [ 14 ] ; out
-> mTDXF_P . mIr [ 15 ] = _cg_const_2 [ 15 ] ; out -> mTDXF_P . mIr [ 16 ] =
_cg_const_2 [ 16 ] ; ( void ) sys ; ( void ) out ; return 0 ; }
