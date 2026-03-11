#include "TX_PM_MODEL.h"
#include <stddef.h>
#include <float.h>
#include "mwmathutil.h"
#include "rtwtypes.h"
#include "TX_PM_MODEL_private.h"
#include <string.h>
#include "rt_logging_mmi.h"
#include "TX_PM_MODEL_capi.h"
#include "zero_crossing_types.h"
#include "TX_PM_MODEL_dt.h"
extern void * CreateDiagnosticAsVoidPtr_wrapper ( const char * id , int nargs
, ... ) ; extern ssExecutionInfo gblExecutionInfo ; RTWExtModeInfo *
gblRTWExtModeInfo = NULL ; void raccelForceExtModeShutdown ( boolean_T
extModeStartPktReceived ) { if ( ! extModeStartPktReceived ) { boolean_T
stopRequested = false ; rtExtModeWaitForStartPkt ( gblRTWExtModeInfo , 3 , &
stopRequested ) ; } rtExtModeShutdown ( 3 ) ; }
#include "slsv_diagnostic_codegen_c_api.h"
#include "slsa_engine_exec.h"
#ifdef RSIM_WITH_SOLVER_MULTITASKING
boolean_T gbl_raccel_isMultitasking = 1 ;
#else
boolean_T gbl_raccel_isMultitasking = 0 ;
#endif
boolean_T gbl_raccel_tid01eq = 0 ; int_T gbl_raccel_NumST = 4 ; const char_T
* gbl_raccel_Version = "24.1 (R2024a) 19-Nov-2023" ; void
raccel_setup_MMIStateLog ( SimStruct * S ) {
#ifdef UseMMIDataLogging
rt_FillStateSigInfoFromMMI ( ssGetRTWLogInfo ( S ) , & ssGetErrorStatus ( S )
) ;
#else
UNUSED_PARAMETER ( S ) ;
#endif
} static DataMapInfo rt_dataMapInfo ; DataMapInfo * rt_dataMapInfoPtr = &
rt_dataMapInfo ; rtwCAPI_ModelMappingInfo * rt_modelMapInfoPtr = & (
rt_dataMapInfo . mmi ) ; int_T enableFcnCallFlag [ ] = { 1 , 1 , 1 , 1 } ;
const char * raccelLoadInputsAndAperiodicHitTimes ( SimStruct * S , const
char * inportFileName , int * matFileFormat ) { return
rt_RAccelReadInportsMatFile ( S , inportFileName , matFileFormat ) ; }
#include "simstruc.h"
#include "fixedpoint.h"
#include "slsa_engine_exec.h"
#include "simtarget/slSimTgtSLExecSimBridge.h"
B rtB ; X rtX ; DW rtDW ; PrevZCX rtPrevZCX ; static SimStruct model_S ;
SimStruct * const rtS = & model_S ;
#ifndef __RTW_UTFREE__  
extern void * utMalloc ( size_t ) ;
#endif
void * rt_TDelayCreateBuf ( int_T numBuffer , int_T bufSz , int_T elemSz ) {
return ( ( void * ) utMalloc ( numBuffer * bufSz * elemSz ) ) ; }
#ifndef __RTW_UTFREE__  
extern void * utMalloc ( size_t ) ; extern void utFree ( void * ) ;
#endif
boolean_T rt_TDelayUpdateTailOrGrowBuf ( int_T * bufSzPtr , int_T * tailPtr ,
int_T * headPtr , int_T * lastPtr , real_T tMinusDelay , real_T * * uBufPtr ,
boolean_T isfixedbuf , boolean_T istransportdelay , int_T * maxNewBufSzPtr )
{ int_T testIdx ; int_T tail = * tailPtr ; int_T bufSz = * bufSzPtr ; real_T
* tBuf = * uBufPtr + bufSz ; real_T * xBuf = ( NULL ) ; int_T numBuffer = 2 ;
if ( istransportdelay ) { numBuffer = 3 ; xBuf = * uBufPtr + 2 * bufSz ; }
testIdx = ( tail < ( bufSz - 1 ) ) ? ( tail + 1 ) : 0 ; if ( ( tMinusDelay <=
tBuf [ testIdx ] ) && ! isfixedbuf ) { int_T j ; real_T * tempT ; real_T *
tempU ; real_T * tempX = ( NULL ) ; real_T * uBuf = * uBufPtr ; int_T
newBufSz = bufSz + 1024 ; if ( newBufSz > * maxNewBufSzPtr ) { *
maxNewBufSzPtr = newBufSz ; } tempU = ( real_T * ) utMalloc ( numBuffer *
newBufSz * sizeof ( real_T ) ) ; if ( tempU == ( NULL ) ) { return ( false )
; } tempT = tempU + newBufSz ; if ( istransportdelay ) tempX = tempT +
newBufSz ; for ( j = tail ; j < bufSz ; j ++ ) { tempT [ j - tail ] = tBuf [
j ] ; tempU [ j - tail ] = uBuf [ j ] ; if ( istransportdelay ) tempX [ j -
tail ] = xBuf [ j ] ; } for ( j = 0 ; j < tail ; j ++ ) { tempT [ j + bufSz -
tail ] = tBuf [ j ] ; tempU [ j + bufSz - tail ] = uBuf [ j ] ; if (
istransportdelay ) tempX [ j + bufSz - tail ] = xBuf [ j ] ; } if ( * lastPtr
> tail ) { * lastPtr -= tail ; } else { * lastPtr += ( bufSz - tail ) ; } *
tailPtr = 0 ; * headPtr = bufSz ; utFree ( uBuf ) ; * bufSzPtr = newBufSz ; *
uBufPtr = tempU ; } else { * tailPtr = testIdx ; } return ( true ) ; } real_T
rt_TDelayInterpolate ( real_T tMinusDelay , real_T tStart , real_T * uBuf ,
int_T bufSz , int_T * lastIdx , int_T oldestIdx , int_T newIdx , real_T
initOutput , boolean_T discrete , boolean_T minorStepAndTAtLastMajorOutput )
{ int_T i ; real_T yout , t1 , t2 , u1 , u2 ; real_T * tBuf = uBuf + bufSz ;
if ( ( newIdx == 0 ) && ( oldestIdx == 0 ) && ( tMinusDelay > tStart ) )
return initOutput ; if ( tMinusDelay <= tStart ) return initOutput ; if ( (
tMinusDelay <= tBuf [ oldestIdx ] ) ) { if ( discrete ) { return ( uBuf [
oldestIdx ] ) ; } else { int_T tempIdx = oldestIdx + 1 ; if ( oldestIdx ==
bufSz - 1 ) tempIdx = 0 ; t1 = tBuf [ oldestIdx ] ; t2 = tBuf [ tempIdx ] ;
u1 = uBuf [ oldestIdx ] ; u2 = uBuf [ tempIdx ] ; if ( t2 == t1 ) { if (
tMinusDelay >= t2 ) { yout = u2 ; } else { yout = u1 ; } } else { real_T f1 =
( t2 - tMinusDelay ) / ( t2 - t1 ) ; real_T f2 = 1.0 - f1 ; yout = f1 * u1 +
f2 * u2 ; } return yout ; } } if ( minorStepAndTAtLastMajorOutput ) { if (
newIdx != 0 ) { if ( * lastIdx == newIdx ) { ( * lastIdx ) -- ; } newIdx -- ;
} else { if ( * lastIdx == newIdx ) { * lastIdx = bufSz - 1 ; } newIdx =
bufSz - 1 ; } } i = * lastIdx ; if ( tBuf [ i ] < tMinusDelay ) { while (
tBuf [ i ] < tMinusDelay ) { if ( i == newIdx ) break ; i = ( i < ( bufSz - 1
) ) ? ( i + 1 ) : 0 ; } } else { while ( tBuf [ i ] >= tMinusDelay ) { i = (
i > 0 ) ? i - 1 : ( bufSz - 1 ) ; } i = ( i < ( bufSz - 1 ) ) ? ( i + 1 ) : 0
; } * lastIdx = i ; if ( discrete ) { double tempEps = ( DBL_EPSILON ) *
128.0 ; double localEps = tempEps * muDoubleScalarAbs ( tBuf [ i ] ) ; if (
tempEps > localEps ) { localEps = tempEps ; } localEps = localEps / 2.0 ; if
( tMinusDelay >= ( tBuf [ i ] - localEps ) ) { yout = uBuf [ i ] ; } else {
if ( i == 0 ) { yout = uBuf [ bufSz - 1 ] ; } else { yout = uBuf [ i - 1 ] ;
} } } else { if ( i == 0 ) { t1 = tBuf [ bufSz - 1 ] ; u1 = uBuf [ bufSz - 1
] ; } else { t1 = tBuf [ i - 1 ] ; u1 = uBuf [ i - 1 ] ; } t2 = tBuf [ i ] ;
u2 = uBuf [ i ] ; if ( t2 == t1 ) { if ( tMinusDelay >= t2 ) { yout = u2 ; }
else { yout = u1 ; } } else { real_T f1 = ( t2 - tMinusDelay ) / ( t2 - t1 )
; real_T f2 = 1.0 - f1 ; yout = f1 * u1 + f2 * u2 ; } } return ( yout ) ; }
#ifndef __RTW_UTFREE__  
extern void utFree ( void * ) ;
#endif
void rt_TDelayFreeBuf ( void * buf ) { utFree ( buf ) ; } real_T
look1_pbinlxpw ( real_T u0 , const real_T bp0 [ ] , const real_T table [ ] ,
uint32_T prevIndex [ ] , uint32_T maxIndex ) { real_T frac ; real_T yL_0d0 ;
uint32_T bpIdx ; uint32_T found ; uint32_T iLeft ; uint32_T iRght ; if ( u0
<= bp0 [ 0U ] ) { bpIdx = 0U ; frac = ( u0 - bp0 [ 0U ] ) / ( bp0 [ 1U ] -
bp0 [ 0U ] ) ; } else if ( u0 < bp0 [ maxIndex ] ) { bpIdx = prevIndex [ 0U ]
; iLeft = 0U ; iRght = maxIndex ; found = 0U ; while ( found == 0U ) { if (
u0 < bp0 [ bpIdx ] ) { iRght = bpIdx - 1U ; bpIdx = ( ( bpIdx + iLeft ) - 1U
) >> 1U ; } else if ( u0 < bp0 [ bpIdx + 1U ] ) { found = 1U ; } else { iLeft
= bpIdx + 1U ; bpIdx = ( ( bpIdx + iRght ) + 1U ) >> 1U ; } } frac = ( u0 -
bp0 [ bpIdx ] ) / ( bp0 [ bpIdx + 1U ] - bp0 [ bpIdx ] ) ; } else { bpIdx =
maxIndex - 1U ; frac = ( u0 - bp0 [ maxIndex - 1U ] ) / ( bp0 [ maxIndex ] -
bp0 [ maxIndex - 1U ] ) ; } prevIndex [ 0U ] = bpIdx ; yL_0d0 = table [ bpIdx
] ; return ( table [ bpIdx + 1U ] - yL_0d0 ) * frac + yL_0d0 ; } void
MdlInitialize ( void ) { rtDW . j3rvz00322 = ( rtInf ) ; rtDW . mqinkjd1zs =
( rtInf ) ; rtDW . blkdexuikc = 29U ; rtX . ltjcuhbz2h = rtP . Integrator_IC
; rtDW . ogcs02to4t = rtP . Memory_InitialCondition ; rtDW . jactlik0jm = rtP
. UnitDelay_InitialCondition ; rtX . ndgviglkhd = 0.0 ; rtB . hnltplbdv1 =
rtP . _Y0 ; } void MdlStart ( void ) { CXPtMax * _rtXPerturbMax ; CXPtMin *
_rtXPerturbMin ; NeModelParameters modelParameters ; NeModelParameters
modelParameters_p ; NeslSimulationData * simulationData ; NeslSimulator * tmp
; NeuDiagnosticManager * diagnosticManager ; NeuDiagnosticTree *
diagnosticTree ; NeuDiagnosticTree * diagnosticTree_e ; NeuDiagnosticTree *
diagnosticTree_p ; char * msg ; char * msg_e ; char * msg_p ; real_T tmp_m [
8 ] ; real_T time ; real_T tmp_e ; int32_T tmp_i ; int_T tmp_g [ 3 ] ;
boolean_T tmp_p ; boolean_T val ; { bool externalInputIsInDatasetFormat =
false ; void * pISigstreamManager = rt_GetISigstreamManager ( rtS ) ;
rtwISigstreamManagerGetInputIsInDatasetFormat ( pISigstreamManager , &
externalInputIsInDatasetFormat ) ; if ( externalInputIsInDatasetFormat ) { }
} _rtXPerturbMax = ( ( CXPtMax * ) ssGetJacobianPerturbationBoundsMaxVec (
rtS ) ) ; _rtXPerturbMin = ( ( CXPtMin * )
ssGetJacobianPerturbationBoundsMinVec ( rtS ) ) ; { char_T ptrKey [ 1024 ] ;
{ real_T * pBuffer = ( real_T * ) rt_TDelayCreateBuf ( 2 , 1024 , sizeof (
real_T ) ) ; if ( pBuffer == ( NULL ) ) { ssSetErrorStatus ( rtS ,
"tdelay memory allocation error" ) ; return ; } rtDW . bqrjlrvqux . Tail = 0
; rtDW . bqrjlrvqux . Head = 0 ; rtDW . bqrjlrvqux . Last = 0 ; rtDW .
bqrjlrvqux . CircularBufSize = 1024 ; pBuffer [ 0 ] = rtP .
TransportDelay_InitOutput ; pBuffer [ 1024 ] = ssGetT ( rtS ) ; rtDW .
efhaqprcos . TUbufferPtrs [ 0 ] = ( void * ) & pBuffer [ 0 ] ; sprintf (
ptrKey , "TX_PM_MODEL/Transport\nDelay_TUbuffer%d" , 0 ) ;
slsaSaveRawMemoryForSimTargetOP ( rtS , ptrKey , ( void * * ) ( & rtDW .
efhaqprcos . TUbufferPtrs [ 0 ] ) , 2 * 1024 * sizeof ( real_T ) , ( NULL ) ,
( NULL ) ) ; } } tmp = nesl_lease_simulator (
"TX_PM_MODEL/Solver Configuration_1" , 0 , 0 ) ; rtDW . lmjogvwbmu = ( void *
) tmp ; tmp_p = pointer_is_null ( rtDW . lmjogvwbmu ) ; if ( tmp_p ) {
TX_PM_MODEL_d3b57d61_1_gateway ( ) ; tmp = nesl_lease_simulator (
"TX_PM_MODEL/Solver Configuration_1" , 0 , 0 ) ; rtDW . lmjogvwbmu = ( void *
) tmp ; } slsaSaveRawMemoryForSimTargetOP ( rtS ,
"TX_PM_MODEL/Solver Configuration_100" , ( void * * ) ( & rtDW . lmjogvwbmu )
, 0U * sizeof ( real_T ) , nesl_save_simdata , nesl_restore_simdata ) ;
simulationData = nesl_create_simulation_data ( ) ; rtDW . pw25voyhew = ( void
* ) simulationData ; diagnosticManager = rtw_create_diagnostics ( ) ; rtDW .
lwb2lbpaoe = ( void * ) diagnosticManager ; modelParameters . mSolverType =
NE_SOLVER_TYPE_DAE ; modelParameters . mSolverAbsTol = 0.001 ;
modelParameters . mSolverRelTol = 0.001 ; modelParameters .
mSolverModifyAbsTol = NE_MODIFY_ABS_TOL_MAYBE ; modelParameters . mStartTime
= 0.0 ; modelParameters . mLoadInitialState = false ; modelParameters .
mUseSimState = false ; modelParameters . mLinTrimCompile = false ;
modelParameters . mLoggingMode = SSC_LOGGING_OFF ; modelParameters .
mRTWModifiedTimeStamp = 6.89774097E+8 ; modelParameters . mZcDisabled = false
; modelParameters . mUseModelRefSolver = false ; modelParameters .
mTargetFPGAHIL = false ; tmp_e = 0.001 ; modelParameters . mSolverTolerance =
tmp_e ; tmp_e = 0.0 ; modelParameters . mFixedStepSize = tmp_e ; tmp_p = true
; modelParameters . mVariableStepSolver = tmp_p ; tmp_p = false ;
modelParameters . mIsUsingODEN = tmp_p ; tmp_p =
slIsRapidAcceleratorSimulating ( ) ; val = ssGetGlobalInitialStatesAvailable
( rtS ) ; if ( tmp_p ) { val = ( val && ssIsFirstInitCond ( rtS ) ) ; }
modelParameters . mLoadInitialState = val ; modelParameters . mZcDisabled =
false ; diagnosticManager = ( NeuDiagnosticManager * ) rtDW . lwb2lbpaoe ;
diagnosticTree = neu_diagnostic_manager_get_initial_tree ( diagnosticManager
) ; tmp_i = nesl_initialize_simulator ( ( NeslSimulator * ) rtDW . lmjogvwbmu
, & modelParameters , diagnosticManager ) ; if ( tmp_i != 0 ) { tmp_p =
error_buffer_is_empty ( ssGetErrorStatus ( rtS ) ) ; if ( tmp_p ) { msg =
rtw_diagnostics_msg ( diagnosticTree ) ; ssSetErrorStatus ( rtS , msg ) ; } }
simulationData = ( NeslSimulationData * ) rtDW . pw25voyhew ; time = ssGetT (
rtS ) ; simulationData -> mData -> mTime . mN = 1 ; simulationData -> mData
-> mTime . mX = & time ; simulationData -> mData -> mContStates . mN = 3 ;
simulationData -> mData -> mContStates . mX = & rtX . aghn3yromn [ 0 ] ;
simulationData -> mData -> mDiscStates . mN = 8 ; simulationData -> mData ->
mDiscStates . mX = & rtDW . kfu5qmkiew [ 0 ] ; simulationData -> mData ->
mModeVector . mN = 1 ; simulationData -> mData -> mModeVector . mX = & rtDW .
nwck4oizlu ; tmp_p = ( ssIsMajorTimeStep ( rtS ) && ssGetRTWSolverInfo ( rtS
) -> foundContZcEvents ) ; simulationData -> mData -> mFoundZcEvents = tmp_p
; simulationData -> mData -> mHadEvents = false ; simulationData -> mData ->
mIsMajorTimeStep = ssIsMajorTimeStep ( rtS ) ; tmp_p = ( ssGetMdlInfoPtr (
rtS ) -> mdlFlags . solverAssertCheck == 1U ) ; simulationData -> mData ->
mIsSolverAssertCheck = tmp_p ; tmp_p = ssIsSolverCheckingCIC ( rtS ) ;
simulationData -> mData -> mIsSolverCheckingCIC = tmp_p ; tmp_p =
ssIsSolverComputingJacobian ( rtS ) ; simulationData -> mData ->
mIsComputingJacobian = tmp_p ; simulationData -> mData -> mIsEvaluatingF0 = (
ssGetEvaluatingF0ForJacobian ( rtS ) != 0 ) ; tmp_p =
ssIsSolverRequestingReset ( rtS ) ; simulationData -> mData ->
mIsSolverRequestingReset = tmp_p ; simulationData -> mData ->
mIsModeUpdateTimeStep = ssIsModeUpdateTimeStep ( rtS ) ; tmp_g [ 0 ] = 0 ;
tmp_m [ 0 ] = rtB . pzggivk2nk [ 0 ] ; tmp_m [ 1 ] = rtB . pzggivk2nk [ 1 ] ;
tmp_m [ 2 ] = rtB . pzggivk2nk [ 2 ] ; tmp_m [ 3 ] = rtB . pzggivk2nk [ 3 ] ;
tmp_g [ 1 ] = 4 ; tmp_m [ 4 ] = rtB . ah1knnixy1 [ 0 ] ; tmp_m [ 5 ] = rtB .
ah1knnixy1 [ 1 ] ; tmp_m [ 6 ] = rtB . ah1knnixy1 [ 2 ] ; tmp_m [ 7 ] = rtB .
ah1knnixy1 [ 3 ] ; tmp_g [ 2 ] = 8 ; simulationData -> mData -> mInputValues
. mN = 8 ; simulationData -> mData -> mInputValues . mX = & tmp_m [ 0 ] ;
simulationData -> mData -> mInputOffsets . mN = 3 ; simulationData -> mData
-> mInputOffsets . mX = & tmp_g [ 0 ] ; simulationData -> mData ->
mNumjacDxLo . mN = 3 ; simulationData -> mData -> mNumjacDxLo . mX = &
_rtXPerturbMin -> aghn3yromn [ 0 ] ; simulationData -> mData -> mNumjacDxHi .
mN = 3 ; simulationData -> mData -> mNumjacDxHi . mX = & _rtXPerturbMax ->
aghn3yromn [ 0 ] ; diagnosticManager = ( NeuDiagnosticManager * ) rtDW .
lwb2lbpaoe ; diagnosticTree_p = neu_diagnostic_manager_get_initial_tree (
diagnosticManager ) ; tmp_i = ne_simulator_method ( ( NeslSimulator * ) rtDW
. lmjogvwbmu , NESL_SIM_NUMJAC_DX_BOUNDS , simulationData , diagnosticManager
) ; if ( tmp_i != 0 ) { tmp_p = error_buffer_is_empty ( ssGetErrorStatus (
rtS ) ) ; if ( tmp_p ) { msg_p = rtw_diagnostics_msg ( diagnosticTree_p ) ;
ssSetErrorStatus ( rtS , msg_p ) ; } } tmp = nesl_lease_simulator (
"TX_PM_MODEL/Solver Configuration_1" , 1 , 0 ) ; rtDW . acosfgneyj = ( void *
) tmp ; tmp_p = pointer_is_null ( rtDW . acosfgneyj ) ; if ( tmp_p ) {
TX_PM_MODEL_d3b57d61_1_gateway ( ) ; tmp = nesl_lease_simulator (
"TX_PM_MODEL/Solver Configuration_1" , 1 , 0 ) ; rtDW . acosfgneyj = ( void *
) tmp ; } slsaSaveRawMemoryForSimTargetOP ( rtS ,
"TX_PM_MODEL/Solver Configuration_110" , ( void * * ) ( & rtDW . acosfgneyj )
, 0U * sizeof ( real_T ) , nesl_save_simdata , nesl_restore_simdata ) ;
simulationData = nesl_create_simulation_data ( ) ; rtDW . dwoay20qkp = ( void
* ) simulationData ; diagnosticManager = rtw_create_diagnostics ( ) ; rtDW .
cuoh2x1alu = ( void * ) diagnosticManager ; modelParameters_p . mSolverType =
NE_SOLVER_TYPE_DAE ; modelParameters_p . mSolverAbsTol = 0.001 ;
modelParameters_p . mSolverRelTol = 0.001 ; modelParameters_p .
mSolverModifyAbsTol = NE_MODIFY_ABS_TOL_MAYBE ; modelParameters_p .
mStartTime = 0.0 ; modelParameters_p . mLoadInitialState = false ;
modelParameters_p . mUseSimState = false ; modelParameters_p .
mLinTrimCompile = false ; modelParameters_p . mLoggingMode = SSC_LOGGING_OFF
; modelParameters_p . mRTWModifiedTimeStamp = 6.89774097E+8 ;
modelParameters_p . mZcDisabled = false ; modelParameters_p .
mUseModelRefSolver = false ; modelParameters_p . mTargetFPGAHIL = false ;
tmp_e = 0.001 ; modelParameters_p . mSolverTolerance = tmp_e ; tmp_e = 0.0 ;
modelParameters_p . mFixedStepSize = tmp_e ; tmp_p = true ; modelParameters_p
. mVariableStepSolver = tmp_p ; tmp_p = false ; modelParameters_p .
mIsUsingODEN = tmp_p ; tmp_p = slIsRapidAcceleratorSimulating ( ) ; val =
ssGetGlobalInitialStatesAvailable ( rtS ) ; if ( tmp_p ) { val = ( val &&
ssIsFirstInitCond ( rtS ) ) ; } modelParameters_p . mLoadInitialState = val ;
modelParameters_p . mZcDisabled = false ; diagnosticManager = (
NeuDiagnosticManager * ) rtDW . cuoh2x1alu ; diagnosticTree_e =
neu_diagnostic_manager_get_initial_tree ( diagnosticManager ) ; tmp_i =
nesl_initialize_simulator ( ( NeslSimulator * ) rtDW . acosfgneyj , &
modelParameters_p , diagnosticManager ) ; if ( tmp_i != 0 ) { tmp_p =
error_buffer_is_empty ( ssGetErrorStatus ( rtS ) ) ; if ( tmp_p ) { msg_e =
rtw_diagnostics_msg ( diagnosticTree_e ) ; ssSetErrorStatus ( rtS , msg_e ) ;
} } MdlInitialize ( ) ; } void MdlOutputs ( int_T tid ) { NeslSimulationData
* simulationData ; NeuDiagnosticManager * diagnosticManager ;
NeuDiagnosticTree * diagnosticTree ; NeuDiagnosticTree * diagnosticTree_e ;
NeuDiagnosticTree * diagnosticTree_i ; NeuDiagnosticTree * diagnosticTree_p ;
ZCV * _rtZCSV ; char * msg ; char * msg_e ; char * msg_i ; char * msg_p ;
real_T tmp_f [ 20 ] ; real_T tmp_g [ 8 ] ; real_T tmp_i [ 8 ] ; real_T tmp_p
[ 8 ] ; real_T l1f1gym4n5 ; real_T time ; real_T time_e ; real_T time_g ;
real_T time_i ; real_T time_m ; real_T time_p ; real_T * lastU ; int_T tmp_c
[ 4 ] ; int_T tmp_e [ 3 ] ; int_T tmp_j [ 3 ] ; int_T tmp_m [ 3 ] ; int_T iy
; boolean_T hadEvents ; boolean_T tmp ; _rtZCSV = ( ( ZCV * )
ssGetSolverZcSignalVector ( rtS ) ) ; srClearBC ( rtDW . mxzklxqhhl ) ; {
real_T * * uBuffer = ( real_T * * ) & rtDW . efhaqprcos . TUbufferPtrs [ 0 ]
; real_T simTime = ssGetT ( rtS ) ; real_T tMinusDelay = simTime - rtP .
TransportDelay_Delay ; rtB . iqxaw1e2wm = rt_TDelayInterpolate ( tMinusDelay
, 0.0 , * uBuffer , rtDW . bqrjlrvqux . CircularBufSize , & rtDW . bqrjlrvqux
. Last , rtDW . bqrjlrvqux . Tail , rtDW . bqrjlrvqux . Head , rtP .
TransportDelay_InitOutput , 1 , ( boolean_T ) ( ssIsMinorTimeStep ( rtS ) &&
( ( * uBuffer + rtDW . bqrjlrvqux . CircularBufSize ) [ rtDW . bqrjlrvqux .
Head ] == ssGetT ( rtS ) ) ) ) ; } rtB . pzggivk2nk [ 0 ] = rtB . iqxaw1e2wm
; rtB . pzggivk2nk [ 1 ] = 0.0 ; rtB . pzggivk2nk [ 2 ] = 0.0 ; rtB .
pzggivk2nk [ 3 ] = 0.0 ; if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { rtB .
mlo2m0qs0q = rtP . Constant3_Value ; rtB . h4r1sws3ty = rtP . Constant4_Value
; } l1f1gym4n5 = look1_pbinlxpw ( muDoubleScalarRem ( ssGetT ( rtS ) + rtB .
mlo2m0qs0q , rtB . h4r1sws3ty ) * rtP . uib1_Gain , rtP .
uDLookupTable_bp01Data , rtP . uDLookupTable_tableData , & rtDW . bimuhbs2ra
, 2U ) ; if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { rtB . bszi4f25a5 = rtP .
Constant2_Value ; } rtB . eqskwvzstb = l1f1gym4n5 - rtB . bszi4f25a5 ; if ( (
rtDW . j3rvz00322 >= ssGetT ( rtS ) ) && ( rtDW . mqinkjd1zs >= ssGetT ( rtS
) ) ) { rtB . h3fdkbfjnp = 0.0 ; } else { l1f1gym4n5 = rtDW . j3rvz00322 ;
lastU = & rtDW . ei5jxspsda ; if ( rtDW . j3rvz00322 < rtDW . mqinkjd1zs ) {
if ( rtDW . mqinkjd1zs < ssGetT ( rtS ) ) { l1f1gym4n5 = rtDW . mqinkjd1zs ;
lastU = & rtDW . bis5zqcwsa ; } } else if ( rtDW . j3rvz00322 >= ssGetT ( rtS
) ) { l1f1gym4n5 = rtDW . mqinkjd1zs ; lastU = & rtDW . bis5zqcwsa ; } rtB .
h3fdkbfjnp = ( rtB . eqskwvzstb - * lastU ) / ( ssGetT ( rtS ) - l1f1gym4n5 )
; } if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { if ( rtB . h3fdkbfjnp > 0.0 ) {
rtDW . fza2m5rs4f = 1 ; } else if ( rtB . h3fdkbfjnp < 0.0 ) { rtDW .
fza2m5rs4f = - 1 ; } else { rtDW . fza2m5rs4f = 0 ; } rtB . htg2xosuwx = rtDW
. fza2m5rs4f ; rtB . or1qvnhrlo = rtP . VDD_DRIVE / 2.0 * ( rtB . htg2xosuwx
+ rtP . Constant3_Value_kzpj52qcj4 ) ; } rtB . ah1knnixy1 [ 0 ] = rtB .
or1qvnhrlo ; rtB . ah1knnixy1 [ 1 ] = 0.0 ; rtB . ah1knnixy1 [ 2 ] = 0.0 ; if
( ssIsMajorTimeStep ( rtS ) ) { rtDW . hj2m1r5qok [ 0 ] = ! ( rtB .
ah1knnixy1 [ 0 ] == rtDW . hj2m1r5qok [ 1 ] ) ; rtDW . hj2m1r5qok [ 1 ] = rtB
. ah1knnixy1 [ 0 ] ; } rtB . ah1knnixy1 [ 0 ] = rtDW . hj2m1r5qok [ 1 ] ; rtB
. ah1knnixy1 [ 3 ] = rtDW . hj2m1r5qok [ 0 ] ; simulationData = (
NeslSimulationData * ) rtDW . pw25voyhew ; hadEvents = false ; if (
ssIsMajorTimeStep ( rtS ) ) { time = ssGetT ( rtS ) ; simulationData -> mData
-> mTime . mN = 1 ; simulationData -> mData -> mTime . mX = & time ;
simulationData -> mData -> mContStates . mN = 3 ; simulationData -> mData ->
mContStates . mX = & rtX . aghn3yromn [ 0 ] ; simulationData -> mData ->
mDiscStates . mN = 8 ; simulationData -> mData -> mDiscStates . mX = & rtDW .
kfu5qmkiew [ 0 ] ; simulationData -> mData -> mModeVector . mN = 1 ;
simulationData -> mData -> mModeVector . mX = & rtDW . nwck4oizlu ; tmp = (
ssIsMajorTimeStep ( rtS ) && ssGetRTWSolverInfo ( rtS ) -> foundContZcEvents
) ; simulationData -> mData -> mFoundZcEvents = tmp ; simulationData -> mData
-> mHadEvents = false ; simulationData -> mData -> mIsMajorTimeStep =
ssIsMajorTimeStep ( rtS ) ; tmp = ( ssGetMdlInfoPtr ( rtS ) -> mdlFlags .
solverAssertCheck == 1U ) ; simulationData -> mData -> mIsSolverAssertCheck =
tmp ; tmp = ssIsSolverCheckingCIC ( rtS ) ; simulationData -> mData ->
mIsSolverCheckingCIC = tmp ; tmp = ssIsSolverComputingJacobian ( rtS ) ;
simulationData -> mData -> mIsComputingJacobian = tmp ; simulationData ->
mData -> mIsEvaluatingF0 = ( ssGetEvaluatingF0ForJacobian ( rtS ) != 0 ) ;
tmp = ssIsSolverRequestingReset ( rtS ) ; simulationData -> mData ->
mIsSolverRequestingReset = tmp ; simulationData -> mData ->
mIsModeUpdateTimeStep = ssIsModeUpdateTimeStep ( rtS ) ; tmp_e [ 0 ] = 0 ;
tmp_p [ 0 ] = rtB . pzggivk2nk [ 0 ] ; tmp_p [ 1 ] = rtB . pzggivk2nk [ 1 ] ;
tmp_p [ 2 ] = rtB . pzggivk2nk [ 2 ] ; tmp_p [ 3 ] = rtB . pzggivk2nk [ 3 ] ;
tmp_e [ 1 ] = 4 ; tmp_p [ 4 ] = rtB . ah1knnixy1 [ 0 ] ; tmp_p [ 5 ] = rtB .
ah1knnixy1 [ 1 ] ; tmp_p [ 6 ] = rtB . ah1knnixy1 [ 2 ] ; tmp_p [ 7 ] = rtB .
ah1knnixy1 [ 3 ] ; tmp_e [ 2 ] = 8 ; simulationData -> mData -> mInputValues
. mN = 8 ; simulationData -> mData -> mInputValues . mX = & tmp_p [ 0 ] ;
simulationData -> mData -> mInputOffsets . mN = 3 ; simulationData -> mData
-> mInputOffsets . mX = & tmp_e [ 0 ] ; simulationData -> mData ->
mNonSampledZCs . mN = 1 ; simulationData -> mData -> mNonSampledZCs . mX = &
_rtZCSV -> fg01sapwob ; simulationData -> mData -> mNonSampledZCs . mN = 1 ;
simulationData -> mData -> mNonSampledZCs . mX = & rtDW . ahkmninrpx ;
diagnosticManager = ( NeuDiagnosticManager * ) rtDW . lwb2lbpaoe ;
diagnosticTree = neu_diagnostic_manager_get_initial_tree ( diagnosticManager
) ; iy = ne_simulator_method ( ( NeslSimulator * ) rtDW . lmjogvwbmu ,
NESL_SIM_ZEROCROSSINGS , simulationData , diagnosticManager ) ; if ( iy != 0
) { tmp = error_buffer_is_empty ( ssGetErrorStatus ( rtS ) ) ; if ( tmp ) {
msg = rtw_diagnostics_msg ( diagnosticTree ) ; ssSetErrorStatus ( rtS , msg )
; } } memcpy ( & rtDW . lulh2dgxfx , & rtPrevZCX . jxtwnsjnx1 , 1 ) ; iy =
rt_ZCFcnRefine ( rtDW . blkdexuikc , & rtDW . lulh2dgxfx , ( rtDW .
ahkmninrpx ) ) ; hadEvents = ( iy != 0 ) ; memcpy ( & rtPrevZCX . jxtwnsjnx1
, & rtDW . lulh2dgxfx , 1 ) ; } time_p = ssGetT ( rtS ) ; simulationData ->
mData -> mTime . mN = 1 ; simulationData -> mData -> mTime . mX = & time_p ;
simulationData -> mData -> mContStates . mN = 3 ; simulationData -> mData ->
mContStates . mX = & rtX . aghn3yromn [ 0 ] ; simulationData -> mData ->
mDiscStates . mN = 8 ; simulationData -> mData -> mDiscStates . mX = & rtDW .
kfu5qmkiew [ 0 ] ; simulationData -> mData -> mModeVector . mN = 1 ;
simulationData -> mData -> mModeVector . mX = & rtDW . nwck4oizlu ; tmp = (
ssIsMajorTimeStep ( rtS ) && ssGetRTWSolverInfo ( rtS ) -> foundContZcEvents
) ; simulationData -> mData -> mFoundZcEvents = tmp ; simulationData -> mData
-> mHadEvents = false ; simulationData -> mData -> mIsMajorTimeStep =
ssIsMajorTimeStep ( rtS ) ; tmp = ( ssGetMdlInfoPtr ( rtS ) -> mdlFlags .
solverAssertCheck == 1U ) ; simulationData -> mData -> mIsSolverAssertCheck =
tmp ; tmp = ssIsSolverCheckingCIC ( rtS ) ; simulationData -> mData ->
mIsSolverCheckingCIC = tmp ; tmp = ssIsSolverComputingJacobian ( rtS ) ;
simulationData -> mData -> mIsComputingJacobian = tmp ; simulationData ->
mData -> mIsEvaluatingF0 = ( ssGetEvaluatingF0ForJacobian ( rtS ) != 0 ) ;
tmp = ssIsSolverRequestingReset ( rtS ) ; simulationData -> mData ->
mIsSolverRequestingReset = tmp ; simulationData -> mData ->
mIsModeUpdateTimeStep = ssIsModeUpdateTimeStep ( rtS ) ; tmp_m [ 0 ] = 0 ;
tmp_i [ 0 ] = rtB . pzggivk2nk [ 0 ] ; tmp_i [ 1 ] = rtB . pzggivk2nk [ 1 ] ;
tmp_i [ 2 ] = rtB . pzggivk2nk [ 2 ] ; tmp_i [ 3 ] = rtB . pzggivk2nk [ 3 ] ;
tmp_m [ 1 ] = 4 ; tmp_i [ 4 ] = rtB . ah1knnixy1 [ 0 ] ; tmp_i [ 5 ] = rtB .
ah1knnixy1 [ 1 ] ; tmp_i [ 6 ] = rtB . ah1knnixy1 [ 2 ] ; tmp_i [ 7 ] = rtB .
ah1knnixy1 [ 3 ] ; tmp_m [ 2 ] = 8 ; simulationData -> mData -> mInputValues
. mN = 8 ; simulationData -> mData -> mInputValues . mX = & tmp_i [ 0 ] ;
simulationData -> mData -> mInputOffsets . mN = 3 ; simulationData -> mData
-> mInputOffsets . mX = & tmp_m [ 0 ] ; simulationData -> mData -> mOutputs .
mN = 12 ; simulationData -> mData -> mOutputs . mX = & rtB . dpnt5xseaq [ 0 ]
; simulationData -> mData -> mTolerances . mN = 0 ; simulationData -> mData
-> mTolerances . mX = NULL ; simulationData -> mData -> mCstateHasChanged =
false ; simulationData -> mData -> mDstateHasChanged = false ; time_e =
ssGetTaskTime ( rtS , 0 ) ; simulationData -> mData -> mTime . mN = 1 ;
simulationData -> mData -> mTime . mX = & time_e ; simulationData -> mData ->
mSampleHits . mN = 0 ; simulationData -> mData -> mSampleHits . mX = NULL ;
simulationData -> mData -> mIsFundamentalSampleHit = false ; simulationData
-> mData -> mHadEvents = hadEvents ; diagnosticManager = (
NeuDiagnosticManager * ) rtDW . lwb2lbpaoe ; diagnosticTree_p =
neu_diagnostic_manager_get_initial_tree ( diagnosticManager ) ; iy =
ne_simulator_method ( ( NeslSimulator * ) rtDW . lmjogvwbmu ,
NESL_SIM_OUTPUTS , simulationData , diagnosticManager ) ; if ( iy != 0 ) {
tmp = error_buffer_is_empty ( ssGetErrorStatus ( rtS ) ) ; if ( tmp ) { msg_p
= rtw_diagnostics_msg ( diagnosticTree_p ) ; ssSetErrorStatus ( rtS , msg_p )
; } } if ( ssIsMajorTimeStep ( rtS ) && simulationData -> mData ->
mCstateHasChanged ) { ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; }
if ( ssIsMajorTimeStep ( rtS ) && ( simulationData -> mData ->
mCstateHasChanged || simulationData -> mData -> mDstateHasChanged ) ) {
time_i = ssGetT ( rtS ) ; simulationData -> mData -> mTime . mN = 1 ;
simulationData -> mData -> mTime . mX = & time_i ; simulationData -> mData ->
mContStates . mN = 3 ; simulationData -> mData -> mContStates . mX = & rtX .
aghn3yromn [ 0 ] ; simulationData -> mData -> mDiscStates . mN = 8 ;
simulationData -> mData -> mDiscStates . mX = & rtDW . kfu5qmkiew [ 0 ] ;
simulationData -> mData -> mModeVector . mN = 1 ; simulationData -> mData ->
mModeVector . mX = & rtDW . nwck4oizlu ; tmp = ( ssIsMajorTimeStep ( rtS ) &&
ssGetRTWSolverInfo ( rtS ) -> foundContZcEvents ) ; simulationData -> mData
-> mFoundZcEvents = tmp ; simulationData -> mData -> mHadEvents = false ;
simulationData -> mData -> mIsMajorTimeStep = ssIsMajorTimeStep ( rtS ) ; tmp
= ( ssGetMdlInfoPtr ( rtS ) -> mdlFlags . solverAssertCheck == 1U ) ;
simulationData -> mData -> mIsSolverAssertCheck = tmp ; tmp =
ssIsSolverCheckingCIC ( rtS ) ; simulationData -> mData ->
mIsSolverCheckingCIC = tmp ; tmp = ssIsSolverComputingJacobian ( rtS ) ;
simulationData -> mData -> mIsComputingJacobian = tmp ; simulationData ->
mData -> mIsEvaluatingF0 = ( ssGetEvaluatingF0ForJacobian ( rtS ) != 0 ) ;
tmp = ssIsSolverRequestingReset ( rtS ) ; simulationData -> mData ->
mIsSolverRequestingReset = tmp ; simulationData -> mData ->
mIsModeUpdateTimeStep = ssIsModeUpdateTimeStep ( rtS ) ; tmp_j [ 0 ] = 0 ;
tmp_g [ 0 ] = rtB . pzggivk2nk [ 0 ] ; tmp_g [ 1 ] = rtB . pzggivk2nk [ 1 ] ;
tmp_g [ 2 ] = rtB . pzggivk2nk [ 2 ] ; tmp_g [ 3 ] = rtB . pzggivk2nk [ 3 ] ;
tmp_j [ 1 ] = 4 ; tmp_g [ 4 ] = rtB . ah1knnixy1 [ 0 ] ; tmp_g [ 5 ] = rtB .
ah1knnixy1 [ 1 ] ; tmp_g [ 6 ] = rtB . ah1knnixy1 [ 2 ] ; tmp_g [ 7 ] = rtB .
ah1knnixy1 [ 3 ] ; tmp_j [ 2 ] = 8 ; simulationData -> mData -> mInputValues
. mN = 8 ; simulationData -> mData -> mInputValues . mX = & tmp_g [ 0 ] ;
simulationData -> mData -> mInputOffsets . mN = 3 ; simulationData -> mData
-> mInputOffsets . mX = & tmp_j [ 0 ] ; simulationData -> mData ->
mNonSampledZCs . mN = 1 ; simulationData -> mData -> mNonSampledZCs . mX = &
_rtZCSV -> fg01sapwob ; simulationData -> mData -> mNonSampledZCs . mN = 1 ;
simulationData -> mData -> mNonSampledZCs . mX = & rtDW . ahkmninrpx ;
diagnosticManager = ( NeuDiagnosticManager * ) rtDW . lwb2lbpaoe ;
diagnosticTree_e = neu_diagnostic_manager_get_initial_tree (
diagnosticManager ) ; iy = ne_simulator_method ( ( NeslSimulator * ) rtDW .
lmjogvwbmu , NESL_SIM_ZEROCROSSINGS , simulationData , diagnosticManager ) ;
if ( iy != 0 ) { tmp = error_buffer_is_empty ( ssGetErrorStatus ( rtS ) ) ;
if ( tmp ) { msg_e = rtw_diagnostics_msg ( diagnosticTree_e ) ;
ssSetErrorStatus ( rtS , msg_e ) ; } } rt_ZCFcnRefine ( rtDW . blkdexuikc , &
rtDW . lulh2dgxfx , ( rtDW . ahkmninrpx ) ) ; memcpy ( & rtPrevZCX .
jxtwnsjnx1 , & rtDW . lulh2dgxfx , 1 ) ; } simulationData = (
NeslSimulationData * ) rtDW . dwoay20qkp ; time_m = ssGetT ( rtS ) ;
simulationData -> mData -> mTime . mN = 1 ; simulationData -> mData -> mTime
. mX = & time_m ; simulationData -> mData -> mContStates . mN = 0 ;
simulationData -> mData -> mContStates . mX = NULL ; simulationData -> mData
-> mDiscStates . mN = 0 ; simulationData -> mData -> mDiscStates . mX = &
rtDW . jytum3zlnn ; simulationData -> mData -> mModeVector . mN = 0 ;
simulationData -> mData -> mModeVector . mX = & rtDW . epzt44w1jw ; tmp = (
ssIsMajorTimeStep ( rtS ) && ssGetRTWSolverInfo ( rtS ) -> foundContZcEvents
) ; simulationData -> mData -> mFoundZcEvents = tmp ; simulationData -> mData
-> mHadEvents = false ; simulationData -> mData -> mIsMajorTimeStep =
ssIsMajorTimeStep ( rtS ) ; tmp = ( ssGetMdlInfoPtr ( rtS ) -> mdlFlags .
solverAssertCheck == 1U ) ; simulationData -> mData -> mIsSolverAssertCheck =
tmp ; tmp = ssIsSolverCheckingCIC ( rtS ) ; simulationData -> mData ->
mIsSolverCheckingCIC = tmp ; simulationData -> mData -> mIsComputingJacobian
= false ; simulationData -> mData -> mIsEvaluatingF0 = false ; tmp =
ssIsSolverRequestingReset ( rtS ) ; simulationData -> mData ->
mIsSolverRequestingReset = tmp ; simulationData -> mData ->
mIsModeUpdateTimeStep = ssIsModeUpdateTimeStep ( rtS ) ; tmp_c [ 0 ] = 0 ;
tmp_f [ 0 ] = rtB . pzggivk2nk [ 0 ] ; tmp_f [ 1 ] = rtB . pzggivk2nk [ 1 ] ;
tmp_f [ 2 ] = rtB . pzggivk2nk [ 2 ] ; tmp_f [ 3 ] = rtB . pzggivk2nk [ 3 ] ;
tmp_c [ 1 ] = 4 ; tmp_f [ 4 ] = rtB . ah1knnixy1 [ 0 ] ; tmp_f [ 5 ] = rtB .
ah1knnixy1 [ 1 ] ; tmp_f [ 6 ] = rtB . ah1knnixy1 [ 2 ] ; tmp_f [ 7 ] = rtB .
ah1knnixy1 [ 3 ] ; tmp_c [ 2 ] = 8 ; memcpy ( & tmp_f [ 8 ] , & rtB .
dpnt5xseaq [ 0 ] , 12U * sizeof ( real_T ) ) ; tmp_c [ 3 ] = 20 ;
simulationData -> mData -> mInputValues . mN = 20 ; simulationData -> mData
-> mInputValues . mX = & tmp_f [ 0 ] ; simulationData -> mData ->
mInputOffsets . mN = 4 ; simulationData -> mData -> mInputOffsets . mX = &
tmp_c [ 0 ] ; simulationData -> mData -> mOutputs . mN = 4 ; simulationData
-> mData -> mOutputs . mX = & rtB . dzo3h1kxld [ 0 ] ; simulationData ->
mData -> mTolerances . mN = 0 ; simulationData -> mData -> mTolerances . mX =
NULL ; simulationData -> mData -> mCstateHasChanged = false ; simulationData
-> mData -> mDstateHasChanged = false ; time_g = ssGetTaskTime ( rtS , 0 ) ;
simulationData -> mData -> mTime . mN = 1 ; simulationData -> mData -> mTime
. mX = & time_g ; simulationData -> mData -> mSampleHits . mN = 0 ;
simulationData -> mData -> mSampleHits . mX = NULL ; simulationData -> mData
-> mIsFundamentalSampleHit = false ; simulationData -> mData -> mHadEvents =
false ; diagnosticManager = ( NeuDiagnosticManager * ) rtDW . cuoh2x1alu ;
diagnosticTree_i = neu_diagnostic_manager_get_initial_tree (
diagnosticManager ) ; iy = ne_simulator_method ( ( NeslSimulator * ) rtDW .
acosfgneyj , NESL_SIM_OUTPUTS , simulationData , diagnosticManager ) ; if (
iy != 0 ) { tmp = error_buffer_is_empty ( ssGetErrorStatus ( rtS ) ) ; if (
tmp ) { msg_i = rtw_diagnostics_msg ( diagnosticTree_i ) ; ssSetErrorStatus (
rtS , msg_i ) ; } } if ( ssIsMajorTimeStep ( rtS ) && simulationData -> mData
-> mCstateHasChanged ) { ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ;
} rtB . mlx0mmcucs = rtX . ltjcuhbz2h ; rtB . ii304m0uao = rtP . Gain2_Gain *
rtB . mlx0mmcucs + rtP . VDD / 2.0 ; rtB . p4b2dhw3jt = ( rtP . VDD - rtP .
deltaVOSC ) / 2.0 * rtB . eqskwvzstb + rtP . VDD / 2.0 ; if ( ssIsSampleHit (
rtS , 1 , 0 ) ) { if ( ssIsModeUpdateTimeStep ( rtS ) ) { rtDW . aez3mewd4p =
( rtB . ii304m0uao > rtB . p4b2dhw3jt ) ; } rtB . fvbnvihw2k = rtDW .
aez3mewd4p ; if ( ssIsModeUpdateTimeStep ( rtS ) ) { if ( rtB . fvbnvihw2k &&
( rtPrevZCX . j2wysauwqa != POS_ZCSIG ) ) { rtB . hnltplbdv1 = rtB .
dzo3h1kxld [ 2 ] ; rtDW . mxzklxqhhl = 4 ; } rtPrevZCX . j2wysauwqa = rtB .
fvbnvihw2k ; } } if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { rtB . ckq35jkg2y =
rtB . fvbnvihw2k ; rtB . dke1cfa4ea = rtDW . ogcs02to4t ; } if (
ssIsSampleHit ( rtS , 2 , 0 ) ) { rtB . f1rw0wc1yz = rtDW . jactlik0jm ; }
rtB . o0cqqnpekr = 0.0 ; rtB . o0cqqnpekr += rtP . TransferFcn_C * rtX .
ndgviglkhd ; rtB . catrevm5rx = rtP . VDD / 2.0 + rtB . o0cqqnpekr ; if (
ssIsModeUpdateTimeStep ( rtS ) ) { rtDW . kqserrlfnp = ( ( rtB . catrevm5rx
>= rtP . Vh ) || ( ( ! ( rtB . catrevm5rx <= rtP . Vl ) ) && rtDW .
kqserrlfnp ) ) ; } if ( rtDW . kqserrlfnp ) { rtB . otsbybmj2w = rtP .
Relay_YOn ; } else { rtB . otsbybmj2w = rtP . Relay_YOff ; } if (
ssIsSampleHit ( rtS , 1 , 0 ) ) { rtB . pbejybptra = ( rtP . Gain_Gain * rtB
. otsbybmj2w - rtP . Constant5_Value ) * rtP . I0 ; } UNUSED_PARAMETER ( tid
) ; } void MdlOutputsTID3 ( int_T tid ) { UNUSED_PARAMETER ( tid ) ; } void
MdlUpdate ( int_T tid ) { NeslSimulationData * simulationData ;
NeuDiagnosticManager * diagnosticManager ; NeuDiagnosticTree * diagnosticTree
; char * msg ; real_T tmp_p [ 8 ] ; real_T time ; real_T * lastU ; int32_T
tmp_i ; int_T tmp_e [ 3 ] ; boolean_T tmp ; { real_T * * uBuffer = ( real_T *
* ) & rtDW . efhaqprcos . TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT ( rtS
) ; rtDW . bqrjlrvqux . Head = ( ( rtDW . bqrjlrvqux . Head < ( rtDW .
bqrjlrvqux . CircularBufSize - 1 ) ) ? ( rtDW . bqrjlrvqux . Head + 1 ) : 0 )
; if ( rtDW . bqrjlrvqux . Head == rtDW . bqrjlrvqux . Tail ) { if ( !
rt_TDelayUpdateTailOrGrowBuf ( & rtDW . bqrjlrvqux . CircularBufSize , & rtDW
. bqrjlrvqux . Tail , & rtDW . bqrjlrvqux . Head , & rtDW . bqrjlrvqux . Last
, simTime - rtP . TransportDelay_Delay , uBuffer , ( boolean_T ) 0 , false ,
& rtDW . bqrjlrvqux . MaxNewBufSize ) ) { ssSetErrorStatus ( rtS ,
"tdelay memory allocation error" ) ; return ; }
slsaSaveRawMemoryForSimTargetOP ( rtS ,
"TX_PM_MODEL/Transport\nDelay_TUbuffer0" , ( void * * ) ( & uBuffer [ 0 ] ) ,
2 * rtDW . bqrjlrvqux . CircularBufSize * sizeof ( real_T ) , ( NULL ) , (
NULL ) ) ; } ( * uBuffer + rtDW . bqrjlrvqux . CircularBufSize ) [ rtDW .
bqrjlrvqux . Head ] = simTime ; ( * uBuffer ) [ rtDW . bqrjlrvqux . Head ] =
rtB . ckq35jkg2y ; } if ( rtDW . j3rvz00322 == ( rtInf ) ) { rtDW .
j3rvz00322 = ssGetT ( rtS ) ; lastU = & rtDW . ei5jxspsda ; } else if ( rtDW
. mqinkjd1zs == ( rtInf ) ) { rtDW . mqinkjd1zs = ssGetT ( rtS ) ; lastU = &
rtDW . bis5zqcwsa ; } else if ( rtDW . j3rvz00322 < rtDW . mqinkjd1zs ) {
rtDW . j3rvz00322 = ssGetT ( rtS ) ; lastU = & rtDW . ei5jxspsda ; } else {
rtDW . mqinkjd1zs = ssGetT ( rtS ) ; lastU = & rtDW . bis5zqcwsa ; } * lastU
= rtB . eqskwvzstb ; simulationData = ( NeslSimulationData * ) rtDW .
pw25voyhew ; time = ssGetT ( rtS ) ; simulationData -> mData -> mTime . mN =
1 ; simulationData -> mData -> mTime . mX = & time ; simulationData -> mData
-> mContStates . mN = 3 ; simulationData -> mData -> mContStates . mX = & rtX
. aghn3yromn [ 0 ] ; simulationData -> mData -> mDiscStates . mN = 8 ;
simulationData -> mData -> mDiscStates . mX = & rtDW . kfu5qmkiew [ 0 ] ;
simulationData -> mData -> mModeVector . mN = 1 ; simulationData -> mData ->
mModeVector . mX = & rtDW . nwck4oizlu ; tmp = ( ssIsMajorTimeStep ( rtS ) &&
ssGetRTWSolverInfo ( rtS ) -> foundContZcEvents ) ; simulationData -> mData
-> mFoundZcEvents = tmp ; simulationData -> mData -> mHadEvents = false ;
simulationData -> mData -> mIsMajorTimeStep = ssIsMajorTimeStep ( rtS ) ; tmp
= ( ssGetMdlInfoPtr ( rtS ) -> mdlFlags . solverAssertCheck == 1U ) ;
simulationData -> mData -> mIsSolverAssertCheck = tmp ; tmp =
ssIsSolverCheckingCIC ( rtS ) ; simulationData -> mData ->
mIsSolverCheckingCIC = tmp ; tmp = ssIsSolverComputingJacobian ( rtS ) ;
simulationData -> mData -> mIsComputingJacobian = tmp ; simulationData ->
mData -> mIsEvaluatingF0 = ( ssGetEvaluatingF0ForJacobian ( rtS ) != 0 ) ;
tmp = ssIsSolverRequestingReset ( rtS ) ; simulationData -> mData ->
mIsSolverRequestingReset = tmp ; simulationData -> mData ->
mIsModeUpdateTimeStep = ssIsModeUpdateTimeStep ( rtS ) ; tmp_e [ 0 ] = 0 ;
tmp_p [ 0 ] = rtB . pzggivk2nk [ 0 ] ; tmp_p [ 1 ] = rtB . pzggivk2nk [ 1 ] ;
tmp_p [ 2 ] = rtB . pzggivk2nk [ 2 ] ; tmp_p [ 3 ] = rtB . pzggivk2nk [ 3 ] ;
tmp_e [ 1 ] = 4 ; tmp_p [ 4 ] = rtB . ah1knnixy1 [ 0 ] ; tmp_p [ 5 ] = rtB .
ah1knnixy1 [ 1 ] ; tmp_p [ 6 ] = rtB . ah1knnixy1 [ 2 ] ; tmp_p [ 7 ] = rtB .
ah1knnixy1 [ 3 ] ; tmp_e [ 2 ] = 8 ; simulationData -> mData -> mInputValues
. mN = 8 ; simulationData -> mData -> mInputValues . mX = & tmp_p [ 0 ] ;
simulationData -> mData -> mInputOffsets . mN = 3 ; simulationData -> mData
-> mInputOffsets . mX = & tmp_e [ 0 ] ; diagnosticManager = (
NeuDiagnosticManager * ) rtDW . lwb2lbpaoe ; diagnosticTree =
neu_diagnostic_manager_get_initial_tree ( diagnosticManager ) ; tmp_i =
ne_simulator_method ( ( NeslSimulator * ) rtDW . lmjogvwbmu , NESL_SIM_UPDATE
, simulationData , diagnosticManager ) ; if ( tmp_i != 0 ) { tmp =
error_buffer_is_empty ( ssGetErrorStatus ( rtS ) ) ; if ( tmp ) { msg =
rtw_diagnostics_msg ( diagnosticTree ) ; ssSetErrorStatus ( rtS , msg ) ; } }
if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { rtDW . ogcs02to4t = rtB . hnltplbdv1 ;
} if ( ssIsSampleHit ( rtS , 2 , 0 ) ) { rtDW . jactlik0jm = rtB . f1rw0wc1yz
; } UNUSED_PARAMETER ( tid ) ; } void MdlUpdateTID3 ( int_T tid ) {
UNUSED_PARAMETER ( tid ) ; } void MdlDerivatives ( void ) {
NeslSimulationData * simulationData ; NeuDiagnosticManager *
diagnosticManager ; NeuDiagnosticTree * diagnosticTree ; XDot * _rtXdot ;
char * msg ; real_T tmp_p [ 8 ] ; real_T time ; int_T tmp_e [ 3 ] ; int_T is
; boolean_T tmp ; _rtXdot = ( ( XDot * ) ssGetdX ( rtS ) ) ; simulationData =
( NeslSimulationData * ) rtDW . pw25voyhew ; time = ssGetT ( rtS ) ;
simulationData -> mData -> mTime . mN = 1 ; simulationData -> mData -> mTime
. mX = & time ; simulationData -> mData -> mContStates . mN = 3 ;
simulationData -> mData -> mContStates . mX = & rtX . aghn3yromn [ 0 ] ;
simulationData -> mData -> mDiscStates . mN = 8 ; simulationData -> mData ->
mDiscStates . mX = & rtDW . kfu5qmkiew [ 0 ] ; simulationData -> mData ->
mModeVector . mN = 1 ; simulationData -> mData -> mModeVector . mX = & rtDW .
nwck4oizlu ; tmp = ( ssIsMajorTimeStep ( rtS ) && ssGetRTWSolverInfo ( rtS )
-> foundContZcEvents ) ; simulationData -> mData -> mFoundZcEvents = tmp ;
simulationData -> mData -> mHadEvents = false ; simulationData -> mData ->
mIsMajorTimeStep = ssIsMajorTimeStep ( rtS ) ; tmp = ( ssGetMdlInfoPtr ( rtS
) -> mdlFlags . solverAssertCheck == 1U ) ; simulationData -> mData ->
mIsSolverAssertCheck = tmp ; tmp = ssIsSolverCheckingCIC ( rtS ) ;
simulationData -> mData -> mIsSolverCheckingCIC = tmp ; tmp =
ssIsSolverComputingJacobian ( rtS ) ; simulationData -> mData ->
mIsComputingJacobian = tmp ; simulationData -> mData -> mIsEvaluatingF0 = (
ssGetEvaluatingF0ForJacobian ( rtS ) != 0 ) ; tmp = ssIsSolverRequestingReset
( rtS ) ; simulationData -> mData -> mIsSolverRequestingReset = tmp ;
simulationData -> mData -> mIsModeUpdateTimeStep = ssIsModeUpdateTimeStep (
rtS ) ; tmp_e [ 0 ] = 0 ; tmp_p [ 0 ] = rtB . pzggivk2nk [ 0 ] ; tmp_p [ 1 ]
= rtB . pzggivk2nk [ 1 ] ; tmp_p [ 2 ] = rtB . pzggivk2nk [ 2 ] ; tmp_p [ 3 ]
= rtB . pzggivk2nk [ 3 ] ; tmp_e [ 1 ] = 4 ; tmp_p [ 4 ] = rtB . ah1knnixy1 [
0 ] ; tmp_p [ 5 ] = rtB . ah1knnixy1 [ 1 ] ; tmp_p [ 6 ] = rtB . ah1knnixy1 [
2 ] ; tmp_p [ 7 ] = rtB . ah1knnixy1 [ 3 ] ; tmp_e [ 2 ] = 8 ; simulationData
-> mData -> mInputValues . mN = 8 ; simulationData -> mData -> mInputValues .
mX = & tmp_p [ 0 ] ; simulationData -> mData -> mInputOffsets . mN = 3 ;
simulationData -> mData -> mInputOffsets . mX = & tmp_e [ 0 ] ;
simulationData -> mData -> mDx . mN = 3 ; simulationData -> mData -> mDx . mX
= & _rtXdot -> aghn3yromn [ 0 ] ; diagnosticManager = ( NeuDiagnosticManager
* ) rtDW . lwb2lbpaoe ; diagnosticTree =
neu_diagnostic_manager_get_initial_tree ( diagnosticManager ) ; is =
ne_simulator_method ( ( NeslSimulator * ) rtDW . lmjogvwbmu ,
NESL_SIM_DERIVATIVES , simulationData , diagnosticManager ) ; if ( is != 0 )
{ tmp = error_buffer_is_empty ( ssGetErrorStatus ( rtS ) ) ; if ( tmp ) { msg
= rtw_diagnostics_msg ( diagnosticTree ) ; ssSetErrorStatus ( rtS , msg ) ; }
} _rtXdot -> ltjcuhbz2h = rtB . dke1cfa4ea ; _rtXdot -> ndgviglkhd = 0.0 ;
_rtXdot -> ndgviglkhd += rtP . TransferFcn_A * rtX . ndgviglkhd ; _rtXdot ->
ndgviglkhd += rtB . pbejybptra ; } void MdlProjection ( void ) { } void
MdlZeroCrossings ( void ) { NeslSimulationData * simulationData ;
NeuDiagnosticManager * diagnosticManager ; NeuDiagnosticTree * diagnosticTree
; ZCV * _rtZCSV ; char * msg ; real_T tmp_p [ 8 ] ; real_T time ; int32_T
tmp_i ; int_T tmp_e [ 3 ] ; boolean_T tmp ; _rtZCSV = ( ( ZCV * )
ssGetSolverZcSignalVector ( rtS ) ) ; _rtZCSV -> putxhpigxa = rtB .
h3fdkbfjnp ; simulationData = ( NeslSimulationData * ) rtDW . pw25voyhew ;
time = ssGetT ( rtS ) ; simulationData -> mData -> mTime . mN = 1 ;
simulationData -> mData -> mTime . mX = & time ; simulationData -> mData ->
mContStates . mN = 3 ; simulationData -> mData -> mContStates . mX = & rtX .
aghn3yromn [ 0 ] ; simulationData -> mData -> mDiscStates . mN = 8 ;
simulationData -> mData -> mDiscStates . mX = & rtDW . kfu5qmkiew [ 0 ] ;
simulationData -> mData -> mModeVector . mN = 1 ; simulationData -> mData ->
mModeVector . mX = & rtDW . nwck4oizlu ; tmp = ( ssIsMajorTimeStep ( rtS ) &&
ssGetRTWSolverInfo ( rtS ) -> foundContZcEvents ) ; simulationData -> mData
-> mFoundZcEvents = tmp ; simulationData -> mData -> mHadEvents = false ;
simulationData -> mData -> mIsMajorTimeStep = ssIsMajorTimeStep ( rtS ) ; tmp
= ( ssGetMdlInfoPtr ( rtS ) -> mdlFlags . solverAssertCheck == 1U ) ;
simulationData -> mData -> mIsSolverAssertCheck = tmp ; tmp =
ssIsSolverCheckingCIC ( rtS ) ; simulationData -> mData ->
mIsSolverCheckingCIC = tmp ; tmp = ssIsSolverComputingJacobian ( rtS ) ;
simulationData -> mData -> mIsComputingJacobian = tmp ; simulationData ->
mData -> mIsEvaluatingF0 = ( ssGetEvaluatingF0ForJacobian ( rtS ) != 0 ) ;
tmp = ssIsSolverRequestingReset ( rtS ) ; simulationData -> mData ->
mIsSolverRequestingReset = tmp ; simulationData -> mData ->
mIsModeUpdateTimeStep = ssIsModeUpdateTimeStep ( rtS ) ; tmp_e [ 0 ] = 0 ;
tmp_p [ 0 ] = rtB . pzggivk2nk [ 0 ] ; tmp_p [ 1 ] = rtB . pzggivk2nk [ 1 ] ;
tmp_p [ 2 ] = rtB . pzggivk2nk [ 2 ] ; tmp_p [ 3 ] = rtB . pzggivk2nk [ 3 ] ;
tmp_e [ 1 ] = 4 ; tmp_p [ 4 ] = rtB . ah1knnixy1 [ 0 ] ; tmp_p [ 5 ] = rtB .
ah1knnixy1 [ 1 ] ; tmp_p [ 6 ] = rtB . ah1knnixy1 [ 2 ] ; tmp_p [ 7 ] = rtB .
ah1knnixy1 [ 3 ] ; tmp_e [ 2 ] = 8 ; simulationData -> mData -> mInputValues
. mN = 8 ; simulationData -> mData -> mInputValues . mX = & tmp_p [ 0 ] ;
simulationData -> mData -> mInputOffsets . mN = 3 ; simulationData -> mData
-> mInputOffsets . mX = & tmp_e [ 0 ] ; simulationData -> mData ->
mNonSampledZCs . mN = 1 ; simulationData -> mData -> mNonSampledZCs . mX = &
_rtZCSV -> fg01sapwob ; diagnosticManager = ( NeuDiagnosticManager * ) rtDW .
lwb2lbpaoe ; diagnosticTree = neu_diagnostic_manager_get_initial_tree (
diagnosticManager ) ; tmp_i = ne_simulator_method ( ( NeslSimulator * ) rtDW
. lmjogvwbmu , NESL_SIM_ZEROCROSSINGS , simulationData , diagnosticManager )
; if ( tmp_i != 0 ) { tmp = error_buffer_is_empty ( ssGetErrorStatus ( rtS )
) ; if ( tmp ) { msg = rtw_diagnostics_msg ( diagnosticTree ) ;
ssSetErrorStatus ( rtS , msg ) ; } } _rtZCSV -> ecs00hjd4n = rtB . ii304m0uao
- rtB . p4b2dhw3jt ; if ( rtDW . kqserrlfnp ) { _rtZCSV -> b152gla432 = rtB .
catrevm5rx - rtP . Vl ; } else { _rtZCSV -> b152gla432 = rtB . catrevm5rx -
rtP . Vh ; } } void MdlTerminate ( void ) { rt_TDelayFreeBuf ( rtDW .
efhaqprcos . TUbufferPtrs [ 0 ] ) ; neu_destroy_diagnostic_manager ( (
NeuDiagnosticManager * ) rtDW . lwb2lbpaoe ) ; nesl_destroy_simulation_data (
( NeslSimulationData * ) rtDW . pw25voyhew ) ; nesl_erase_simulator (
"TX_PM_MODEL/Solver Configuration_1" ) ; nesl_destroy_registry ( ) ;
neu_destroy_diagnostic_manager ( ( NeuDiagnosticManager * ) rtDW . cuoh2x1alu
) ; nesl_destroy_simulation_data ( ( NeslSimulationData * ) rtDW . dwoay20qkp
) ; nesl_erase_simulator ( "TX_PM_MODEL/Solver Configuration_1" ) ;
nesl_destroy_registry ( ) ; } static void mr_TX_PM_MODEL_cacheDataAsMxArray (
mxArray * destArray , mwIndex i , int j , const void * srcData , size_t
numBytes ) ; static void mr_TX_PM_MODEL_cacheDataAsMxArray ( mxArray *
destArray , mwIndex i , int j , const void * srcData , size_t numBytes ) {
mxArray * newArray = mxCreateUninitNumericMatrix ( ( size_t ) 1 , numBytes ,
mxUINT8_CLASS , mxREAL ) ; memcpy ( ( uint8_T * ) mxGetData ( newArray ) , (
const uint8_T * ) srcData , numBytes ) ; mxSetFieldByNumber ( destArray , i ,
j , newArray ) ; } static void mr_TX_PM_MODEL_restoreDataFromMxArray ( void *
destData , const mxArray * srcArray , mwIndex i , int j , size_t numBytes ) ;
static void mr_TX_PM_MODEL_restoreDataFromMxArray ( void * destData , const
mxArray * srcArray , mwIndex i , int j , size_t numBytes ) { memcpy ( (
uint8_T * ) destData , ( const uint8_T * ) mxGetData ( mxGetFieldByNumber (
srcArray , i , j ) ) , numBytes ) ; } static void
mr_TX_PM_MODEL_cacheBitFieldToMxArray ( mxArray * destArray , mwIndex i , int
j , uint_T bitVal ) ; static void mr_TX_PM_MODEL_cacheBitFieldToMxArray (
mxArray * destArray , mwIndex i , int j , uint_T bitVal ) {
mxSetFieldByNumber ( destArray , i , j , mxCreateDoubleScalar ( ( real_T )
bitVal ) ) ; } static uint_T mr_TX_PM_MODEL_extractBitFieldFromMxArray (
const mxArray * srcArray , mwIndex i , int j , uint_T numBits ) ; static
uint_T mr_TX_PM_MODEL_extractBitFieldFromMxArray ( const mxArray * srcArray ,
mwIndex i , int j , uint_T numBits ) { const uint_T varVal = ( uint_T )
mxGetScalar ( mxGetFieldByNumber ( srcArray , i , j ) ) ; return varVal & ( (
1u << numBits ) - 1u ) ; } static void
mr_TX_PM_MODEL_cacheDataToMxArrayWithOffset ( mxArray * destArray , mwIndex i
, int j , mwIndex offset , const void * srcData , size_t numBytes ) ; static
void mr_TX_PM_MODEL_cacheDataToMxArrayWithOffset ( mxArray * destArray ,
mwIndex i , int j , mwIndex offset , const void * srcData , size_t numBytes )
{ uint8_T * varData = ( uint8_T * ) mxGetData ( mxGetFieldByNumber (
destArray , i , j ) ) ; memcpy ( ( uint8_T * ) & varData [ offset * numBytes
] , ( const uint8_T * ) srcData , numBytes ) ; } static void
mr_TX_PM_MODEL_restoreDataFromMxArrayWithOffset ( void * destData , const
mxArray * srcArray , mwIndex i , int j , mwIndex offset , size_t numBytes ) ;
static void mr_TX_PM_MODEL_restoreDataFromMxArrayWithOffset ( void * destData
, const mxArray * srcArray , mwIndex i , int j , mwIndex offset , size_t
numBytes ) { const uint8_T * varData = ( const uint8_T * ) mxGetData (
mxGetFieldByNumber ( srcArray , i , j ) ) ; memcpy ( ( uint8_T * ) destData ,
( const uint8_T * ) & varData [ offset * numBytes ] , numBytes ) ; } static
void mr_TX_PM_MODEL_cacheBitFieldToCellArrayWithOffset ( mxArray * destArray
, mwIndex i , int j , mwIndex offset , uint_T fieldVal ) ; static void
mr_TX_PM_MODEL_cacheBitFieldToCellArrayWithOffset ( mxArray * destArray ,
mwIndex i , int j , mwIndex offset , uint_T fieldVal ) { mxSetCell (
mxGetFieldByNumber ( destArray , i , j ) , offset , mxCreateDoubleScalar ( (
real_T ) fieldVal ) ) ; } static uint_T
mr_TX_PM_MODEL_extractBitFieldFromCellArrayWithOffset ( const mxArray *
srcArray , mwIndex i , int j , mwIndex offset , uint_T numBits ) ; static
uint_T mr_TX_PM_MODEL_extractBitFieldFromCellArrayWithOffset ( const mxArray
* srcArray , mwIndex i , int j , mwIndex offset , uint_T numBits ) { const
uint_T fieldVal = ( uint_T ) mxGetScalar ( mxGetCell ( mxGetFieldByNumber (
srcArray , i , j ) , offset ) ) ; return fieldVal & ( ( 1u << numBits ) - 1u
) ; } mxArray * mr_TX_PM_MODEL_GetDWork ( ) { static const char_T *
ssDWFieldNames [ 3 ] = { "rtB" , "rtDW" , "rtPrevZCX" , } ; mxArray * ssDW =
mxCreateStructMatrix ( 1 , 1 , 3 , ssDWFieldNames ) ;
mr_TX_PM_MODEL_cacheDataAsMxArray ( ssDW , 0 , 0 , ( const void * ) & ( rtB )
, sizeof ( rtB ) ) ; { static const char_T * rtdwDataFieldNames [ 27 ] = {
"rtDW.dyftahrecz" , "rtDW.hj2m1r5qok" , "rtDW.kfu5qmkiew" , "rtDW.jactlik0jm"
, "rtDW.j3rvz00322" , "rtDW.ei5jxspsda" , "rtDW.mqinkjd1zs" ,
"rtDW.bis5zqcwsa" , "rtDW.ahkmninrpx" , "rtDW.jytum3zlnn" , "rtDW.auynjau5bk"
, "rtDW.ogcs02to4t" , "rtDW.hah3mvkm3t" , "rtDW.bimuhbs2ra" ,
"rtDW.bqrjlrvqux" , "rtDW.nwck4oizlu" , "rtDW.epzt44w1jw" , "rtDW.fza2m5rs4f"
, "rtDW.mxzklxqhhl" , "rtDW.blkdexuikc" , "rtDW.lulh2dgxfx" ,
"rtDW.hw1rndtluh" , "rtDW.hrx3i5m1ae" , "rtDW.a5f52rvkkx" , "rtDW.nnenardb2c"
, "rtDW.aez3mewd4p" , "rtDW.kqserrlfnp" , } ; mxArray * rtdwData =
mxCreateStructMatrix ( 1 , 1 , 27 , rtdwDataFieldNames ) ;
mr_TX_PM_MODEL_cacheDataAsMxArray ( rtdwData , 0 , 0 , ( const void * ) & (
rtDW . dyftahrecz ) , sizeof ( rtDW . dyftahrecz ) ) ;
mr_TX_PM_MODEL_cacheDataAsMxArray ( rtdwData , 0 , 1 , ( const void * ) & (
rtDW . hj2m1r5qok ) , sizeof ( rtDW . hj2m1r5qok ) ) ;
mr_TX_PM_MODEL_cacheDataAsMxArray ( rtdwData , 0 , 2 , ( const void * ) & (
rtDW . kfu5qmkiew ) , sizeof ( rtDW . kfu5qmkiew ) ) ;
mr_TX_PM_MODEL_cacheDataAsMxArray ( rtdwData , 0 , 3 , ( const void * ) & (
rtDW . jactlik0jm ) , sizeof ( rtDW . jactlik0jm ) ) ;
mr_TX_PM_MODEL_cacheDataAsMxArray ( rtdwData , 0 , 4 , ( const void * ) & (
rtDW . j3rvz00322 ) , sizeof ( rtDW . j3rvz00322 ) ) ;
mr_TX_PM_MODEL_cacheDataAsMxArray ( rtdwData , 0 , 5 , ( const void * ) & (
rtDW . ei5jxspsda ) , sizeof ( rtDW . ei5jxspsda ) ) ;
mr_TX_PM_MODEL_cacheDataAsMxArray ( rtdwData , 0 , 6 , ( const void * ) & (
rtDW . mqinkjd1zs ) , sizeof ( rtDW . mqinkjd1zs ) ) ;
mr_TX_PM_MODEL_cacheDataAsMxArray ( rtdwData , 0 , 7 , ( const void * ) & (
rtDW . bis5zqcwsa ) , sizeof ( rtDW . bis5zqcwsa ) ) ;
mr_TX_PM_MODEL_cacheDataAsMxArray ( rtdwData , 0 , 8 , ( const void * ) & (
rtDW . ahkmninrpx ) , sizeof ( rtDW . ahkmninrpx ) ) ;
mr_TX_PM_MODEL_cacheDataAsMxArray ( rtdwData , 0 , 9 , ( const void * ) & (
rtDW . jytum3zlnn ) , sizeof ( rtDW . jytum3zlnn ) ) ;
mr_TX_PM_MODEL_cacheDataAsMxArray ( rtdwData , 0 , 10 , ( const void * ) & (
rtDW . auynjau5bk ) , sizeof ( rtDW . auynjau5bk ) ) ;
mr_TX_PM_MODEL_cacheDataAsMxArray ( rtdwData , 0 , 11 , ( const void * ) & (
rtDW . ogcs02to4t ) , sizeof ( rtDW . ogcs02to4t ) ) ;
mr_TX_PM_MODEL_cacheDataAsMxArray ( rtdwData , 0 , 12 , ( const void * ) & (
rtDW . hah3mvkm3t ) , sizeof ( rtDW . hah3mvkm3t ) ) ;
mr_TX_PM_MODEL_cacheDataAsMxArray ( rtdwData , 0 , 13 , ( const void * ) & (
rtDW . bimuhbs2ra ) , sizeof ( rtDW . bimuhbs2ra ) ) ;
mr_TX_PM_MODEL_cacheDataAsMxArray ( rtdwData , 0 , 14 , ( const void * ) & (
rtDW . bqrjlrvqux ) , sizeof ( rtDW . bqrjlrvqux ) ) ;
mr_TX_PM_MODEL_cacheDataAsMxArray ( rtdwData , 0 , 15 , ( const void * ) & (
rtDW . nwck4oizlu ) , sizeof ( rtDW . nwck4oizlu ) ) ;
mr_TX_PM_MODEL_cacheDataAsMxArray ( rtdwData , 0 , 16 , ( const void * ) & (
rtDW . epzt44w1jw ) , sizeof ( rtDW . epzt44w1jw ) ) ;
mr_TX_PM_MODEL_cacheDataAsMxArray ( rtdwData , 0 , 17 , ( const void * ) & (
rtDW . fza2m5rs4f ) , sizeof ( rtDW . fza2m5rs4f ) ) ;
mr_TX_PM_MODEL_cacheDataAsMxArray ( rtdwData , 0 , 18 , ( const void * ) & (
rtDW . mxzklxqhhl ) , sizeof ( rtDW . mxzklxqhhl ) ) ;
mr_TX_PM_MODEL_cacheDataAsMxArray ( rtdwData , 0 , 19 , ( const void * ) & (
rtDW . blkdexuikc ) , sizeof ( rtDW . blkdexuikc ) ) ;
mr_TX_PM_MODEL_cacheDataAsMxArray ( rtdwData , 0 , 20 , ( const void * ) & (
rtDW . lulh2dgxfx ) , sizeof ( rtDW . lulh2dgxfx ) ) ;
mr_TX_PM_MODEL_cacheDataAsMxArray ( rtdwData , 0 , 21 , ( const void * ) & (
rtDW . hw1rndtluh ) , sizeof ( rtDW . hw1rndtluh ) ) ;
mr_TX_PM_MODEL_cacheDataAsMxArray ( rtdwData , 0 , 22 , ( const void * ) & (
rtDW . hrx3i5m1ae ) , sizeof ( rtDW . hrx3i5m1ae ) ) ;
mr_TX_PM_MODEL_cacheDataAsMxArray ( rtdwData , 0 , 23 , ( const void * ) & (
rtDW . a5f52rvkkx ) , sizeof ( rtDW . a5f52rvkkx ) ) ;
mr_TX_PM_MODEL_cacheDataAsMxArray ( rtdwData , 0 , 24 , ( const void * ) & (
rtDW . nnenardb2c ) , sizeof ( rtDW . nnenardb2c ) ) ;
mr_TX_PM_MODEL_cacheDataAsMxArray ( rtdwData , 0 , 25 , ( const void * ) & (
rtDW . aez3mewd4p ) , sizeof ( rtDW . aez3mewd4p ) ) ;
mr_TX_PM_MODEL_cacheDataAsMxArray ( rtdwData , 0 , 26 , ( const void * ) & (
rtDW . kqserrlfnp ) , sizeof ( rtDW . kqserrlfnp ) ) ; mxSetFieldByNumber (
ssDW , 0 , 1 , rtdwData ) ; } mr_TX_PM_MODEL_cacheDataAsMxArray ( ssDW , 0 ,
2 , ( const void * ) & ( rtPrevZCX ) , sizeof ( rtPrevZCX ) ) ; return ssDW ;
} void mr_TX_PM_MODEL_SetDWork ( const mxArray * ssDW ) { ( void ) ssDW ;
mr_TX_PM_MODEL_restoreDataFromMxArray ( ( void * ) & ( rtB ) , ssDW , 0 , 0 ,
sizeof ( rtB ) ) ; { const mxArray * rtdwData = mxGetFieldByNumber ( ssDW , 0
, 1 ) ; mr_TX_PM_MODEL_restoreDataFromMxArray ( ( void * ) & ( rtDW .
dyftahrecz ) , rtdwData , 0 , 0 , sizeof ( rtDW . dyftahrecz ) ) ;
mr_TX_PM_MODEL_restoreDataFromMxArray ( ( void * ) & ( rtDW . hj2m1r5qok ) ,
rtdwData , 0 , 1 , sizeof ( rtDW . hj2m1r5qok ) ) ;
mr_TX_PM_MODEL_restoreDataFromMxArray ( ( void * ) & ( rtDW . kfu5qmkiew ) ,
rtdwData , 0 , 2 , sizeof ( rtDW . kfu5qmkiew ) ) ;
mr_TX_PM_MODEL_restoreDataFromMxArray ( ( void * ) & ( rtDW . jactlik0jm ) ,
rtdwData , 0 , 3 , sizeof ( rtDW . jactlik0jm ) ) ;
mr_TX_PM_MODEL_restoreDataFromMxArray ( ( void * ) & ( rtDW . j3rvz00322 ) ,
rtdwData , 0 , 4 , sizeof ( rtDW . j3rvz00322 ) ) ;
mr_TX_PM_MODEL_restoreDataFromMxArray ( ( void * ) & ( rtDW . ei5jxspsda ) ,
rtdwData , 0 , 5 , sizeof ( rtDW . ei5jxspsda ) ) ;
mr_TX_PM_MODEL_restoreDataFromMxArray ( ( void * ) & ( rtDW . mqinkjd1zs ) ,
rtdwData , 0 , 6 , sizeof ( rtDW . mqinkjd1zs ) ) ;
mr_TX_PM_MODEL_restoreDataFromMxArray ( ( void * ) & ( rtDW . bis5zqcwsa ) ,
rtdwData , 0 , 7 , sizeof ( rtDW . bis5zqcwsa ) ) ;
mr_TX_PM_MODEL_restoreDataFromMxArray ( ( void * ) & ( rtDW . ahkmninrpx ) ,
rtdwData , 0 , 8 , sizeof ( rtDW . ahkmninrpx ) ) ;
mr_TX_PM_MODEL_restoreDataFromMxArray ( ( void * ) & ( rtDW . jytum3zlnn ) ,
rtdwData , 0 , 9 , sizeof ( rtDW . jytum3zlnn ) ) ;
mr_TX_PM_MODEL_restoreDataFromMxArray ( ( void * ) & ( rtDW . auynjau5bk ) ,
rtdwData , 0 , 10 , sizeof ( rtDW . auynjau5bk ) ) ;
mr_TX_PM_MODEL_restoreDataFromMxArray ( ( void * ) & ( rtDW . ogcs02to4t ) ,
rtdwData , 0 , 11 , sizeof ( rtDW . ogcs02to4t ) ) ;
mr_TX_PM_MODEL_restoreDataFromMxArray ( ( void * ) & ( rtDW . hah3mvkm3t ) ,
rtdwData , 0 , 12 , sizeof ( rtDW . hah3mvkm3t ) ) ;
mr_TX_PM_MODEL_restoreDataFromMxArray ( ( void * ) & ( rtDW . bimuhbs2ra ) ,
rtdwData , 0 , 13 , sizeof ( rtDW . bimuhbs2ra ) ) ;
mr_TX_PM_MODEL_restoreDataFromMxArray ( ( void * ) & ( rtDW . bqrjlrvqux ) ,
rtdwData , 0 , 14 , sizeof ( rtDW . bqrjlrvqux ) ) ;
mr_TX_PM_MODEL_restoreDataFromMxArray ( ( void * ) & ( rtDW . nwck4oizlu ) ,
rtdwData , 0 , 15 , sizeof ( rtDW . nwck4oizlu ) ) ;
mr_TX_PM_MODEL_restoreDataFromMxArray ( ( void * ) & ( rtDW . epzt44w1jw ) ,
rtdwData , 0 , 16 , sizeof ( rtDW . epzt44w1jw ) ) ;
mr_TX_PM_MODEL_restoreDataFromMxArray ( ( void * ) & ( rtDW . fza2m5rs4f ) ,
rtdwData , 0 , 17 , sizeof ( rtDW . fza2m5rs4f ) ) ;
mr_TX_PM_MODEL_restoreDataFromMxArray ( ( void * ) & ( rtDW . mxzklxqhhl ) ,
rtdwData , 0 , 18 , sizeof ( rtDW . mxzklxqhhl ) ) ;
mr_TX_PM_MODEL_restoreDataFromMxArray ( ( void * ) & ( rtDW . blkdexuikc ) ,
rtdwData , 0 , 19 , sizeof ( rtDW . blkdexuikc ) ) ;
mr_TX_PM_MODEL_restoreDataFromMxArray ( ( void * ) & ( rtDW . lulh2dgxfx ) ,
rtdwData , 0 , 20 , sizeof ( rtDW . lulh2dgxfx ) ) ;
mr_TX_PM_MODEL_restoreDataFromMxArray ( ( void * ) & ( rtDW . hw1rndtluh ) ,
rtdwData , 0 , 21 , sizeof ( rtDW . hw1rndtluh ) ) ;
mr_TX_PM_MODEL_restoreDataFromMxArray ( ( void * ) & ( rtDW . hrx3i5m1ae ) ,
rtdwData , 0 , 22 , sizeof ( rtDW . hrx3i5m1ae ) ) ;
mr_TX_PM_MODEL_restoreDataFromMxArray ( ( void * ) & ( rtDW . a5f52rvkkx ) ,
rtdwData , 0 , 23 , sizeof ( rtDW . a5f52rvkkx ) ) ;
mr_TX_PM_MODEL_restoreDataFromMxArray ( ( void * ) & ( rtDW . nnenardb2c ) ,
rtdwData , 0 , 24 , sizeof ( rtDW . nnenardb2c ) ) ;
mr_TX_PM_MODEL_restoreDataFromMxArray ( ( void * ) & ( rtDW . aez3mewd4p ) ,
rtdwData , 0 , 25 , sizeof ( rtDW . aez3mewd4p ) ) ;
mr_TX_PM_MODEL_restoreDataFromMxArray ( ( void * ) & ( rtDW . kqserrlfnp ) ,
rtdwData , 0 , 26 , sizeof ( rtDW . kqserrlfnp ) ) ; }
mr_TX_PM_MODEL_restoreDataFromMxArray ( ( void * ) & ( rtPrevZCX ) , ssDW , 0
, 2 , sizeof ( rtPrevZCX ) ) ; } mxArray *
mr_TX_PM_MODEL_GetSimStateDisallowedBlocks ( ) { mxArray * data =
mxCreateCellMatrix ( 8 , 3 ) ; mwIndex subs [ 2 ] , offset ; { static const
char_T * blockType [ 8 ] = { "SimscapeExecutionBlock" ,
"SimscapeExecutionBlock" , "Scope" , "Scope" , "Scope" , "Scope" , "Scope" ,
"Scope" , } ; static const char_T * blockPath [ 8 ] = {
"TX_PM_MODEL/Solver Configuration/EVAL_KEY/STATE_1" ,
"TX_PM_MODEL/Solver Configuration/EVAL_KEY/OUTPUT_1_0" , "TX_PM_MODEL/Scope"
, "TX_PM_MODEL/Scope1" , "TX_PM_MODEL/Scope2" , "TX_PM_MODEL/Scope5" ,
"TX_PM_MODEL/Scope6" , "TX_PM_MODEL/Scope4" , } ; static const int reason [ 8
] = { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , } ; for ( subs [ 0 ] = 0 ; subs [ 0 ] <
8 ; ++ ( subs [ 0 ] ) ) { subs [ 1 ] = 0 ; offset = mxCalcSingleSubscript (
data , 2 , subs ) ; mxSetCell ( data , offset , mxCreateString ( blockType [
subs [ 0 ] ] ) ) ; subs [ 1 ] = 1 ; offset = mxCalcSingleSubscript ( data , 2
, subs ) ; mxSetCell ( data , offset , mxCreateString ( blockPath [ subs [ 0
] ] ) ) ; subs [ 1 ] = 2 ; offset = mxCalcSingleSubscript ( data , 2 , subs )
; mxSetCell ( data , offset , mxCreateDoubleScalar ( ( real_T ) reason [ subs
[ 0 ] ] ) ) ; } } return data ; } void MdlInitializeSizes ( void ) {
ssSetNumContStates ( rtS , 5 ) ; ssSetNumPeriodicContStates ( rtS , 0 ) ;
ssSetNumY ( rtS , 0 ) ; ssSetNumU ( rtS , 0 ) ; ssSetDirectFeedThrough ( rtS
, 0 ) ; ssSetNumSampleTimes ( rtS , 3 ) ; ssSetNumBlocks ( rtS , 65 ) ;
ssSetNumBlockIO ( rtS , 24 ) ; ssSetNumBlockParams ( rtS , 30 ) ; } void
MdlInitializeSampleTimes ( void ) { ssSetSampleTime ( rtS , 0 , 0.0 ) ;
ssSetSampleTime ( rtS , 1 , 0.0 ) ; ssSetSampleTime ( rtS , 2 , 5.0E-7 ) ;
ssSetOffsetTime ( rtS , 0 , 0.0 ) ; ssSetOffsetTime ( rtS , 1 , 1.0 ) ;
ssSetOffsetTime ( rtS , 2 , 2.5E-7 ) ; } void raccel_set_checksum ( ) {
ssSetChecksumVal ( rtS , 0 , 2303698878U ) ; ssSetChecksumVal ( rtS , 1 ,
2012635106U ) ; ssSetChecksumVal ( rtS , 2 , 128554924U ) ; ssSetChecksumVal
( rtS , 3 , 2040453846U ) ; }
#if defined(_MSC_VER)
#pragma optimize( "", off )
#endif
SimStruct * raccel_register_model ( ssExecutionInfo * executionInfo ) {
static struct _ssMdlInfo mdlInfo ; static struct _ssBlkInfo2 blkInfo2 ;
static struct _ssBlkInfoSLSize blkInfoSLSize ; rt_modelMapInfoPtr = & (
rt_dataMapInfo . mmi ) ; executionInfo -> gblObjects_ . numToFiles = 0 ;
executionInfo -> gblObjects_ . numFrFiles = 0 ; executionInfo -> gblObjects_
. numFrWksBlocks = 0 ; executionInfo -> gblObjects_ . numModelInputs = 0 ;
executionInfo -> gblObjects_ . numRootInportBlks = 0 ; executionInfo ->
gblObjects_ . inportDataTypeIdx = NULL ; executionInfo -> gblObjects_ .
inportDims = NULL ; executionInfo -> gblObjects_ . inportComplex = NULL ;
executionInfo -> gblObjects_ . inportInterpoFlag = NULL ; executionInfo ->
gblObjects_ . inportContinuous = NULL ; ( void ) memset ( ( char_T * ) rtS ,
0 , sizeof ( SimStruct ) ) ; ( void ) memset ( ( char_T * ) & mdlInfo , 0 ,
sizeof ( struct _ssMdlInfo ) ) ; ( void ) memset ( ( char_T * ) & blkInfo2 ,
0 , sizeof ( struct _ssBlkInfo2 ) ) ; ( void ) memset ( ( char_T * ) &
blkInfoSLSize , 0 , sizeof ( struct _ssBlkInfoSLSize ) ) ; ssSetBlkInfo2Ptr (
rtS , & blkInfo2 ) ; ssSetBlkInfoSLSizePtr ( rtS , & blkInfoSLSize ) ;
ssSetMdlInfoPtr ( rtS , & mdlInfo ) ; ssSetExecutionInfo ( rtS ,
executionInfo ) ; slsaAllocOPModelData ( rtS ) ; { static time_T mdlPeriod [
NSAMPLE_TIMES ] ; static time_T mdlOffset [ NSAMPLE_TIMES ] ; static time_T
mdlTaskTimes [ NSAMPLE_TIMES ] ; static int_T mdlTsMap [ NSAMPLE_TIMES ] ;
static int_T mdlSampleHits [ NSAMPLE_TIMES ] ; static boolean_T
mdlTNextWasAdjustedPtr [ NSAMPLE_TIMES ] ; static int_T mdlPerTaskSampleHits
[ NSAMPLE_TIMES * NSAMPLE_TIMES ] ; static time_T mdlTimeOfNextSampleHit [
NSAMPLE_TIMES ] ; { int_T i ; for ( i = 0 ; i < NSAMPLE_TIMES ; i ++ ) {
mdlPeriod [ i ] = 0.0 ; mdlOffset [ i ] = 0.0 ; mdlTaskTimes [ i ] = 0.0 ;
mdlTsMap [ i ] = i ; mdlSampleHits [ i ] = 1 ; } } ssSetSampleTimePtr ( rtS ,
& mdlPeriod [ 0 ] ) ; ssSetOffsetTimePtr ( rtS , & mdlOffset [ 0 ] ) ;
ssSetSampleTimeTaskIDPtr ( rtS , & mdlTsMap [ 0 ] ) ; ssSetTPtr ( rtS , &
mdlTaskTimes [ 0 ] ) ; ssSetSampleHitPtr ( rtS , & mdlSampleHits [ 0 ] ) ;
ssSetTNextWasAdjustedPtr ( rtS , & mdlTNextWasAdjustedPtr [ 0 ] ) ;
ssSetPerTaskSampleHitsPtr ( rtS , & mdlPerTaskSampleHits [ 0 ] ) ;
ssSetTimeOfNextSampleHitPtr ( rtS , & mdlTimeOfNextSampleHit [ 0 ] ) ; }
ssSetSolverMode ( rtS , SOLVER_MODE_SINGLETASKING ) ; { ssSetBlockIO ( rtS ,
( ( void * ) & rtB ) ) ; ( void ) memset ( ( ( void * ) & rtB ) , 0 , sizeof
( B ) ) ; } { real_T * x = ( real_T * ) & rtX ; ssSetContStates ( rtS , x ) ;
( void ) memset ( ( void * ) x , 0 , sizeof ( X ) ) ; } { void * dwork = (
void * ) & rtDW ; ssSetRootDWork ( rtS , dwork ) ; ( void ) memset ( dwork ,
0 , sizeof ( DW ) ) ; } { static DataTypeTransInfo dtInfo ; ( void ) memset (
( char_T * ) & dtInfo , 0 , sizeof ( dtInfo ) ) ; ssSetModelMappingInfo ( rtS
, & dtInfo ) ; dtInfo . numDataTypes = 24 ; dtInfo . dataTypeSizes = &
rtDataTypeSizes [ 0 ] ; dtInfo . dataTypeNames = & rtDataTypeNames [ 0 ] ;
dtInfo . BTransTable = & rtBTransTable ; dtInfo . PTransTable = &
rtPTransTable ; dtInfo . dataTypeInfoTable = rtDataTypeInfoTable ; }
TX_PM_MODEL_InitializeDataMapInfo ( ) ; ssSetIsRapidAcceleratorActive ( rtS ,
true ) ; ssSetRootSS ( rtS , rtS ) ; ssSetVersion ( rtS ,
SIMSTRUCT_VERSION_LEVEL2 ) ; ssSetModelName ( rtS , "TX_PM_MODEL" ) ;
ssSetPath ( rtS , "TX_PM_MODEL" ) ; ssSetTStart ( rtS , 0.0 ) ; ssSetTFinal (
rtS , 0.003 ) ; { static RTWLogInfo rt_DataLoggingInfo ; rt_DataLoggingInfo .
loggingInterval = ( NULL ) ; ssSetRTWLogInfo ( rtS , & rt_DataLoggingInfo ) ;
} { { static int_T rt_LoggedStateWidths [ ] = { 1 , 1 , 1 , 1 , 1 , 2 , 2 , 8
, 1 } ; static int_T rt_LoggedStateNumDimensions [ ] = { 1 , 1 , 1 , 1 , 1 ,
1 , 1 , 1 , 1 } ; static int_T rt_LoggedStateDimensions [ ] = { 1 , 1 , 1 , 1
, 1 , 2 , 2 , 8 , 1 } ; static boolean_T rt_LoggedStateIsVarDims [ ] = { 0 ,
0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 } ; static BuiltInDTypeId
rt_LoggedStateDataTypeIds [ ] = { SS_DOUBLE , SS_DOUBLE , SS_DOUBLE ,
SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE , SS_DOUBLE } ;
static int_T rt_LoggedStateComplexSignals [ ] = { 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
0 , 0 } ; static RTWPreprocessingFcnPtr rt_LoggingStatePreprocessingFcnPtrs [
] = { ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , ( NULL ) , (
NULL ) , ( NULL ) , ( NULL ) } ; static const char_T * rt_LoggedStateLabels [
] = { "CSTATE" , "CSTATE" , "CSTATE" , "CSTATE" , "CSTATE" , "Discrete" ,
"Discrete" , "Discrete" , "DSTATE" } ; static const char_T *
rt_LoggedStateBlockNames [ ] = { "TX_PM_MODEL/L" , "TX_PM_MODEL/CN1" ,
"TX_PM_MODEL/CN2" , "TX_PM_MODEL/Integrator" , "TX_PM_MODEL/Transfer Fcn" ,
"TX_PM_MODEL/Solver\nConfiguration/EVAL_KEY/INPUT_1_1_1" ,
"TX_PM_MODEL/Solver\nConfiguration/EVAL_KEY/INPUT_2_1_1" ,
"TX_PM_MODEL/Solver\nConfiguration/EVAL_KEY/STATE_1" ,
"TX_PM_MODEL/Triangle\nGenerator/Model/Unit Delay" } ; static const char_T *
rt_LoggedStateNames [ ] = { "TX_PM_MODEL.L.i_L" , "TX_PM_MODEL.CN1.vc" ,
"TX_PM_MODEL.CN2.vc" , "" , "" , "Discrete" , "Discrete" , "Discrete" ,
"DSTATE" } ; static boolean_T rt_LoggedStateCrossMdlRef [ ] = { 0 , 0 , 0 , 0
, 0 , 0 , 0 , 0 , 0 } ; static RTWLogDataTypeConvert rt_RTWLogDataTypeConvert
[ ] = { { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE ,
SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 ,
0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 ,
SS_DOUBLE , SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE ,
SS_DOUBLE , 0 , 0 , 0 , 1.0 , 0 , 0.0 } , { 0 , SS_DOUBLE , SS_DOUBLE , 0 , 0
, 0 , 1.0 , 0 , 0.0 } } ; static int_T rt_LoggedStateIdxList [ ] = { 0 , 1 ,
2 , 0 , 1 , 2 , 3 } ; static RTWLogSignalInfo rt_LoggedStateSignalInfo = { 9
, rt_LoggedStateWidths , rt_LoggedStateNumDimensions ,
rt_LoggedStateDimensions , rt_LoggedStateIsVarDims , ( NULL ) , ( NULL ) ,
rt_LoggedStateDataTypeIds , rt_LoggedStateComplexSignals , ( NULL ) ,
rt_LoggingStatePreprocessingFcnPtrs , { rt_LoggedStateLabels } , ( NULL ) , (
NULL ) , ( NULL ) , { rt_LoggedStateBlockNames } , { rt_LoggedStateNames } ,
rt_LoggedStateCrossMdlRef , rt_RTWLogDataTypeConvert , rt_LoggedStateIdxList
} ; static void * rt_LoggedStateSignalPtrs [ 9 ] ; rtliSetLogXSignalPtrs (
ssGetRTWLogInfo ( rtS ) , ( LogSignalPtrsType ) rt_LoggedStateSignalPtrs ) ;
rtliSetLogXSignalInfo ( ssGetRTWLogInfo ( rtS ) , & rt_LoggedStateSignalInfo
) ; rt_LoggedStateSignalPtrs [ 0 ] = ( void * ) & rtX . aghn3yromn [ 0 ] ;
rt_LoggedStateSignalPtrs [ 1 ] = ( void * ) & rtX . aghn3yromn [ 1 ] ;
rt_LoggedStateSignalPtrs [ 2 ] = ( void * ) & rtX . aghn3yromn [ 2 ] ;
rt_LoggedStateSignalPtrs [ 3 ] = ( void * ) & rtX . ltjcuhbz2h ;
rt_LoggedStateSignalPtrs [ 4 ] = ( void * ) & rtX . ndgviglkhd ;
rt_LoggedStateSignalPtrs [ 5 ] = ( void * ) rtDW . dyftahrecz ;
rt_LoggedStateSignalPtrs [ 6 ] = ( void * ) rtDW . hj2m1r5qok ;
rt_LoggedStateSignalPtrs [ 7 ] = ( void * ) rtDW . kfu5qmkiew ;
rt_LoggedStateSignalPtrs [ 8 ] = ( void * ) & rtDW . jactlik0jm ; }
rtliSetLogT ( ssGetRTWLogInfo ( rtS ) , "tout" ) ; rtliSetLogX (
ssGetRTWLogInfo ( rtS ) , "" ) ; rtliSetLogXFinal ( ssGetRTWLogInfo ( rtS ) ,
"xFinal" ) ; rtliSetLogVarNameModifier ( ssGetRTWLogInfo ( rtS ) , "none" ) ;
rtliSetLogFormat ( ssGetRTWLogInfo ( rtS ) , 4 ) ; rtliSetLogMaxRows (
ssGetRTWLogInfo ( rtS ) , 0 ) ; rtliSetLogDecimation ( ssGetRTWLogInfo ( rtS
) , 1 ) ; rtliSetLogY ( ssGetRTWLogInfo ( rtS ) , "" ) ;
rtliSetLogYSignalInfo ( ssGetRTWLogInfo ( rtS ) , ( NULL ) ) ;
rtliSetLogYSignalPtrs ( ssGetRTWLogInfo ( rtS ) , ( NULL ) ) ; } { static
struct _ssStatesInfo2 statesInfo2 ; ssSetStatesInfo2 ( rtS , & statesInfo2 )
; } { static ssPeriodicStatesInfo periodicStatesInfo ;
ssSetPeriodicStatesInfo ( rtS , & periodicStatesInfo ) ; } { static
ssJacobianPerturbationBounds jacobianPerturbationBounds ;
ssSetJacobianPerturbationBounds ( rtS , & jacobianPerturbationBounds ) ; } {
static ssSolverInfo slvrInfo ; static boolean_T contStatesDisabled [ 5 ] ;
static real_T absTol [ 5 ] = { 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 } ;
static uint8_T absTolControl [ 5 ] = { 0U , 0U , 0U , 0U , 0U } ; static
real_T contStateJacPerturbBoundMinVec [ 5 ] ; static real_T
contStateJacPerturbBoundMaxVec [ 5 ] ; static uint8_T zcAttributes [ 5 ] = {
( ZC_EVENT_ALL ) , ( 0x80 | ZC_EVENT_P2Z | ZC_EVENT_P2N | ZC_EVENT_Z2P |
ZC_EVENT_N2P ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( 0xc0 |
ZC_EVENT_ALL_UP ) } ; static ssNonContDerivSigInfo nonContDerivSigInfo [ 4 ]
= { { 1 * sizeof ( real_T ) , ( char * ) ( & rtB . pbejybptra ) , ( NULL ) }
, { 1 * sizeof ( real_T ) , ( char * ) ( & rtB . dke1cfa4ea ) , ( NULL ) } ,
{ 1 * sizeof ( real_T ) , ( char * ) ( & rtB . ckq35jkg2y ) , ( NULL ) } , {
1 * sizeof ( real_T ) , ( char * ) ( & rtB . or1qvnhrlo ) , ( NULL ) } } ; {
int i ; for ( i = 0 ; i < 5 ; ++ i ) { contStateJacPerturbBoundMinVec [ i ] =
0 ; contStateJacPerturbBoundMaxVec [ i ] = rtGetInf ( ) ; } }
ssSetSolverRelTol ( rtS , 0.001 ) ; ssSetStepSize ( rtS , 0.0 ) ;
ssSetMinStepSize ( rtS , 0.0 ) ; ssSetMaxNumMinSteps ( rtS , - 1 ) ;
ssSetMinStepViolatedError ( rtS , 0 ) ; ssSetMaxStepSize ( rtS , 1.0E-9 ) ;
ssSetSolverMaxOrder ( rtS , - 1 ) ; ssSetSolverRefineFactor ( rtS , 1 ) ;
ssSetOutputTimes ( rtS , ( NULL ) ) ; ssSetNumOutputTimes ( rtS , 0 ) ;
ssSetOutputTimesOnly ( rtS , 0 ) ; ssSetOutputTimesIndex ( rtS , 0 ) ;
ssSetZCCacheNeedsReset ( rtS , 1 ) ; ssSetDerivCacheNeedsReset ( rtS , 0 ) ;
ssSetNumNonContDerivSigInfos ( rtS , 4 ) ; ssSetNonContDerivSigInfos ( rtS ,
nonContDerivSigInfo ) ; ssSetSolverInfo ( rtS , & slvrInfo ) ;
ssSetSolverName ( rtS , "VariableStepAuto" ) ; ssSetVariableStepSolver ( rtS
, 1 ) ; ssSetSolverConsistencyChecking ( rtS , 0 ) ;
ssSetSolverAdaptiveZcDetection ( rtS , 0 ) ; ssSetSolverRobustResetMethod (
rtS , 0 ) ; _ssSetSolverUpdateJacobianAtReset ( rtS , true ) ;
ssSetAbsTolVector ( rtS , absTol ) ; ssSetAbsTolControlVector ( rtS ,
absTolControl ) ; ssSetSolverAbsTol_Obsolete ( rtS , absTol ) ;
ssSetSolverAbsTolControl_Obsolete ( rtS , absTolControl ) ;
ssSetJacobianPerturbationBoundsMinVec ( rtS , contStateJacPerturbBoundMinVec
) ; ssSetJacobianPerturbationBoundsMaxVec ( rtS ,
contStateJacPerturbBoundMaxVec ) ; ssSetSolverStateProjection ( rtS , 0 ) ;
ssSetSolverMassMatrixType ( rtS , ( ssMatrixType ) 0 ) ;
ssSetSolverMassMatrixNzMax ( rtS , 0 ) ; ssSetModelOutputs ( rtS , MdlOutputs
) ; ssSetModelUpdate ( rtS , MdlUpdate ) ; ssSetModelDerivatives ( rtS ,
MdlDerivatives ) ; ssSetSolverZcSignalAttrib ( rtS , zcAttributes ) ;
ssSetSolverNumZcSignals ( rtS , 5 ) ; ssSetModelZeroCrossings ( rtS ,
MdlZeroCrossings ) ; ssSetSolverConsecutiveZCsStepRelTol ( rtS ,
2.8421709430404007E-13 ) ; ssSetSolverMaxConsecutiveZCs ( rtS , 1000 ) ;
ssSetSolverConsecutiveZCsError ( rtS , 2 ) ; ssSetSolverMaskedZcDiagnostic (
rtS , 1 ) ; ssSetSolverIgnoredZcDiagnostic ( rtS , 1 ) ;
ssSetSolverMaxConsecutiveMinStep ( rtS , 1 ) ;
ssSetSolverShapePreserveControl ( rtS , 2 ) ; ssSetTNextTid ( rtS , INT_MIN )
; ssSetTNext ( rtS , rtMinusInf ) ; ssSetSolverNeedsReset ( rtS ) ;
ssSetNumNonsampledZCs ( rtS , 4 ) ; ssSetContStateDisabled ( rtS ,
contStatesDisabled ) ; ssSetSolverMaxConsecutiveMinStep ( rtS , 1 ) ; } {
ZCSigState * zc = ( ZCSigState * ) & rtPrevZCX ; ssSetPrevZCSigState ( rtS ,
zc ) ; } { rtPrevZCX . jxtwnsjnx1 = UNINITIALIZED_ZCSIG ; rtPrevZCX .
j2wysauwqa = POS_ZCSIG ; } ssSetChecksumVal ( rtS , 0 , 2303698878U ) ;
ssSetChecksumVal ( rtS , 1 , 2012635106U ) ; ssSetChecksumVal ( rtS , 2 ,
128554924U ) ; ssSetChecksumVal ( rtS , 3 , 2040453846U ) ; { static const
sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE ; static RTWExtModeInfo
rt_ExtModeInfo ; static const sysRanDType * systemRan [ 2 ] ;
gblRTWExtModeInfo = & rt_ExtModeInfo ; ssSetRTWExtModeInfo ( rtS , &
rt_ExtModeInfo ) ; rteiSetSubSystemActiveVectorAddresses ( & rt_ExtModeInfo ,
systemRan ) ; systemRan [ 0 ] = & rtAlwaysEnabled ; systemRan [ 1 ] = (
sysRanDType * ) & rtDW . mxzklxqhhl ; rteiSetModelMappingInfoPtr (
ssGetRTWExtModeInfo ( rtS ) , & ssGetModelMappingInfo ( rtS ) ) ;
rteiSetChecksumsPtr ( ssGetRTWExtModeInfo ( rtS ) , ssGetChecksums ( rtS ) )
; rteiSetTPtr ( ssGetRTWExtModeInfo ( rtS ) , ssGetTPtr ( rtS ) ) ; }
slsaDisallowedBlocksForSimTargetOP ( rtS ,
mr_TX_PM_MODEL_GetSimStateDisallowedBlocks ) ; slsaGetWorkFcnForSimTargetOP (
rtS , mr_TX_PM_MODEL_GetDWork ) ; slsaSetWorkFcnForSimTargetOP ( rtS ,
mr_TX_PM_MODEL_SetDWork ) ; rt_RapidReadMatFileAndUpdateParams ( rtS ) ; if (
ssGetErrorStatus ( rtS ) ) { return rtS ; } executionInfo ->
simulationOptions_ . stateSaveName_ = rtliGetLogX ( ssGetRTWLogInfo ( rtS ) )
; executionInfo -> simulationOptions_ . finalStateName_ = rtliGetLogXFinal (
ssGetRTWLogInfo ( rtS ) ) ; executionInfo -> simulationOptions_ .
outputSaveName_ = rtliGetLogY ( ssGetRTWLogInfo ( rtS ) ) ; return rtS ; }
#if defined(_MSC_VER)
#pragma optimize( "", on )
#endif
void MdlOutputsParameterSampleTime ( int_T tid ) { MdlOutputsTID3 ( tid ) ; }
