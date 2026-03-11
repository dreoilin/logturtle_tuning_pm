#ifndef TX_PM_MODEL_h_
#define TX_PM_MODEL_h_
#ifndef TX_PM_MODEL_COMMON_INCLUDES_
#define TX_PM_MODEL_COMMON_INCLUDES_
#include <stdio.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "sigstream_rtw.h"
#include "simtarget/slSimTgtSigstreamRTW.h"
#include "simtarget/slSimTgtSlioCoreRTW.h"
#include "simtarget/slSimTgtSlioClientsRTW.h"
#include "simtarget/slSimTgtSlioSdiRTW.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "raccel.h"
#include "slsv_diagnostic_codegen_c_api.h"
#include "rt_logging_simtarget.h"
#include "rt_nonfinite.h"
#include "math.h"
#include "dt_info.h"
#include "ext_work.h"
#include "nesl_rtw.h"
#include "TX_PM_MODEL_d3b57d61_1_gateway.h"
#endif
#include "TX_PM_MODEL_types.h"
#include <stddef.h>
#include <string.h>
#include "rt_zcfcnRefine.h"
#include "rtGetInf.h"
#include "rtw_modelmap_simtarget.h"
#include "rt_defines.h"
#include "zero_crossing_types.h"
#define MODEL_NAME TX_PM_MODEL
#define NSAMPLE_TIMES (4) 
#define NINPUTS (0)       
#define NOUTPUTS (0)     
#define NBLOCKIO (24) 
#define NUM_ZC_EVENTS (2) 
#ifndef NCSTATES
#define NCSTATES (5)   
#elif NCSTATES != 5
#error Invalid specification of NCSTATES defined in compiler command
#endif
#ifndef rtmGetDataMapInfo
#define rtmGetDataMapInfo(rtm) (*rt_dataMapInfoPtr)
#endif
#ifndef rtmSetDataMapInfo
#define rtmSetDataMapInfo(rtm, val) (rt_dataMapInfoPtr = &val)
#endif
#ifndef IN_RACCEL_MAIN
#endif
typedef struct { real_T iqxaw1e2wm ; real_T pzggivk2nk [ 4 ] ; real_T
mlo2m0qs0q ; real_T h4r1sws3ty ; real_T bszi4f25a5 ; real_T eqskwvzstb ;
real_T h3fdkbfjnp ; real_T htg2xosuwx ; real_T or1qvnhrlo ; real_T ah1knnixy1
[ 4 ] ; real_T dpnt5xseaq [ 12 ] ; real_T dzo3h1kxld [ 4 ] ; real_T
mlx0mmcucs ; real_T ii304m0uao ; real_T p4b2dhw3jt ; real_T ckq35jkg2y ;
real_T dke1cfa4ea ; real_T f1rw0wc1yz ; real_T o0cqqnpekr ; real_T catrevm5rx
; real_T otsbybmj2w ; real_T pbejybptra ; real_T hnltplbdv1 ; boolean_T
fvbnvihw2k ; } B ; typedef struct { real_T dyftahrecz [ 2 ] ; real_T
hj2m1r5qok [ 2 ] ; real_T kfu5qmkiew [ 8 ] ; real_T jactlik0jm ; real_T
j3rvz00322 ; real_T ei5jxspsda ; real_T mqinkjd1zs ; real_T bis5zqcwsa ;
real_T ahkmninrpx ; real_T jytum3zlnn ; real_T auynjau5bk ; real_T ogcs02to4t
; struct { real_T modelTStart ; } hah3mvkm3t ; struct { void * TUbufferPtrs [
2 ] ; } efhaqprcos ; void * lmjogvwbmu ; void * pw25voyhew ; void *
lwb2lbpaoe ; void * hgiopsej4q ; void * cry0wwc30p ; void * acosfgneyj ; void
* dwoay20qkp ; void * cuoh2x1alu ; void * hxuru1ea5n ; void * cvtdhhhk2k ;
struct { void * LoggedData [ 4 ] ; } eor52yxnta ; struct { void * LoggedData
[ 2 ] ; } ctf4tkw1zy ; struct { void * LoggedData [ 4 ] ; } dxpqylue1z ;
struct { void * LoggedData [ 3 ] ; } htjwqeoktr ; struct { void * LoggedData
; } dhzmjggnk2 ; struct { void * LoggedData [ 2 ] ; } nhylb4j3vq ; uint32_T
bimuhbs2ra ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T
CircularBufSize ; int_T MaxNewBufSize ; } bqrjlrvqux ; int_T nwck4oizlu ;
int_T epzt44w1jw ; int_T fza2m5rs4f ; int8_T mxzklxqhhl ; uint8_T blkdexuikc
; uint8_T lulh2dgxfx ; uint8_T hw1rndtluh ; uint8_T hrx3i5m1ae ; boolean_T
a5f52rvkkx ; boolean_T nnenardb2c ; boolean_T aez3mewd4p ; boolean_T
kqserrlfnp ; } DW ; typedef struct { real_T aghn3yromn [ 3 ] ; real_T
ltjcuhbz2h ; real_T ndgviglkhd ; } X ; typedef struct { real_T aghn3yromn [ 3
] ; real_T ltjcuhbz2h ; real_T ndgviglkhd ; } XDot ; typedef struct {
boolean_T aghn3yromn [ 3 ] ; boolean_T ltjcuhbz2h ; boolean_T ndgviglkhd ; }
XDis ; typedef struct { real_T aghn3yromn [ 3 ] ; real_T ltjcuhbz2h ; real_T
ndgviglkhd ; } CStateAbsTol ; typedef struct { real_T aghn3yromn [ 3 ] ;
real_T ltjcuhbz2h ; real_T ndgviglkhd ; } CXPtMin ; typedef struct { real_T
aghn3yromn [ 3 ] ; real_T ltjcuhbz2h ; real_T ndgviglkhd ; } CXPtMax ;
typedef struct { real_T putxhpigxa ; real_T fg01sapwob ; real_T ecs00hjd4n ;
real_T b152gla432 ; real_T hpzu352yhi ; } ZCV ; typedef struct { ZCSigState
jxtwnsjnx1 ; ZCSigState j2wysauwqa ; } PrevZCX ; typedef struct {
rtwCAPI_ModelMappingInfo mmi ; } DataMapInfo ; struct P_ { real_T I0 ; real_T
VDD ; real_T VDD_DRIVE ; real_T Vh ; real_T Vl ; real_T deltaVOSC ; real_T
_Y0 ; real_T TransportDelay_Delay ; real_T TransportDelay_InitOutput ; real_T
Constant3_Value ; real_T Constant4_Value ; real_T uib1_Gain ; real_T
uDLookupTable_tableData [ 3 ] ; real_T uDLookupTable_bp01Data [ 3 ] ; real_T
Constant2_Value ; real_T Integrator_IC ; real_T Gain2_Gain ; real_T
Memory_InitialCondition ; real_T UnitDelay_InitialCondition ; real_T
TransferFcn_A ; real_T TransferFcn_C ; real_T Relay_YOn ; real_T Relay_YOff ;
real_T Gain_Gain ; real_T Constant3_Value_kzpj52qcj4 ; real_T Constant5_Value
; } ; extern const char_T * RT_MEMORY_ALLOCATION_ERROR ; extern B rtB ;
extern X rtX ; extern DW rtDW ; extern PrevZCX rtPrevZCX ; extern P rtP ;
extern mxArray * mr_TX_PM_MODEL_GetDWork ( ) ; extern void
mr_TX_PM_MODEL_SetDWork ( const mxArray * ssDW ) ; extern mxArray *
mr_TX_PM_MODEL_GetSimStateDisallowedBlocks ( ) ; extern const
rtwCAPI_ModelMappingStaticInfo * TX_PM_MODEL_GetCAPIStaticMap ( void ) ;
extern SimStruct * const rtS ; extern DataMapInfo * rt_dataMapInfoPtr ;
extern rtwCAPI_ModelMappingInfo * rt_modelMapInfoPtr ; void MdlOutputs (
int_T tid ) ; void MdlOutputsParameterSampleTime ( int_T tid ) ; void
MdlUpdate ( int_T tid ) ; void MdlTerminate ( void ) ; void
MdlInitializeSizes ( void ) ; void MdlInitializeSampleTimes ( void ) ;
SimStruct * raccel_register_model ( ssExecutionInfo * executionInfo ) ;
#endif
