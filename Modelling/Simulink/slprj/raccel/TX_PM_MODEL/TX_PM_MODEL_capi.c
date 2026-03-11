#include "rtw_capi.h"
#ifdef HOST_CAPI_BUILD
#include "TX_PM_MODEL_capi_host.h"
#define sizeof(s) ((size_t)(0xFFFF))
#undef rt_offsetof
#define rt_offsetof(s,el) ((uint16_T)(0xFFFF))
#define TARGET_CONST
#define TARGET_STRING(s) (s)
#ifndef SS_UINT64
#define SS_UINT64 18
#endif
#ifndef SS_INT64
#define SS_INT64 19
#endif
#else
#include "builtin_typeid_types.h"
#include "TX_PM_MODEL.h"
#include "TX_PM_MODEL_capi.h"
#include "TX_PM_MODEL_private.h"
#ifdef LIGHT_WEIGHT_CAPI
#define TARGET_CONST
#define TARGET_STRING(s)               ((NULL))
#else
#define TARGET_CONST                   const
#define TARGET_STRING(s)               (s)
#endif
#endif
static const rtwCAPI_Signals rtBlockSignals [ ] = { { 0 , 1 , TARGET_STRING (
"TX_PM_MODEL/Sample and Hold" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 }
, { 1 , 0 , TARGET_STRING ( "TX_PM_MODEL/Data Type Conversion" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 2 , 0 , TARGET_STRING (
"TX_PM_MODEL/Derivative" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 2 } , { 3
, 0 , TARGET_STRING ( "TX_PM_MODEL/Gain1" ) , TARGET_STRING ( "" ) , 0 , 0 ,
0 , 0 , 1 } , { 4 , 0 , TARGET_STRING ( "TX_PM_MODEL/Gain4" ) , TARGET_STRING
( "" ) , 0 , 0 , 0 , 0 , 1 } , { 5 , 0 , TARGET_STRING (
"TX_PM_MODEL/Integrator" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 2 } , { 6
, 0 , TARGET_STRING ( "TX_PM_MODEL/Memory" ) , TARGET_STRING ( "" ) , 0 , 0 ,
0 , 0 , 1 } , { 7 , 0 , TARGET_STRING ( "TX_PM_MODEL/Relay" ) , TARGET_STRING
( "" ) , 0 , 0 , 0 , 0 , 1 } , { 8 , 0 , TARGET_STRING (
"TX_PM_MODEL/GreaterThan" ) , TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 1 } , {
9 , 0 , TARGET_STRING ( "TX_PM_MODEL/Sign1" ) , TARGET_STRING ( "" ) , 0 , 0
, 0 , 0 , 1 } , { 10 , 0 , TARGET_STRING ( "TX_PM_MODEL/Add" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 2 } , { 11 , 0 , TARGET_STRING (
"TX_PM_MODEL/Add2" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 2 } , { 12 , 0
, TARGET_STRING ( "TX_PM_MODEL/Add5" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0
, 2 } , { 13 , 0 , TARGET_STRING ( "TX_PM_MODEL/Transfer Fcn" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 2 } , { 14 , 0 , TARGET_STRING (
"TX_PM_MODEL/Transport Delay" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 2 }
, { 15 , 1 , TARGET_STRING ( "TX_PM_MODEL/Sample and Hold/In" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 16 , 0 , TARGET_STRING (
"TX_PM_MODEL/Solver Configuration/EVAL_KEY/INPUT_1_1_1" ) , TARGET_STRING (
"" ) , 0 , 0 , 1 , 0 , 2 } , { 17 , 0 , TARGET_STRING (
"TX_PM_MODEL/Solver Configuration/EVAL_KEY/INPUT_2_1_1" ) , TARGET_STRING (
"" ) , 0 , 0 , 1 , 0 , 2 } , { 18 , 0 , TARGET_STRING (
"TX_PM_MODEL/Solver Configuration/EVAL_KEY/OUTPUT_1_0" ) , TARGET_STRING ( ""
) , 0 , 0 , 1 , 0 , 2 } , { 19 , 0 , TARGET_STRING (
"TX_PM_MODEL/Solver Configuration/EVAL_KEY/STATE_1" ) , TARGET_STRING ( "" )
, 0 , 0 , 2 , 0 , 2 } , { 20 , 0 , TARGET_STRING (
"TX_PM_MODEL/Triangle Generator/Model/Constant2" ) , TARGET_STRING ( "" ) , 0
, 0 , 0 , 0 , 1 } , { 21 , 0 , TARGET_STRING (
"TX_PM_MODEL/Triangle Generator/Model/Constant3" ) , TARGET_STRING ( "" ) , 0
, 0 , 0 , 0 , 1 } , { 22 , 0 , TARGET_STRING (
"TX_PM_MODEL/Triangle Generator/Model/Constant4" ) , TARGET_STRING ( "" ) , 0
, 0 , 0 , 0 , 1 } , { 23 , 0 , TARGET_STRING (
"TX_PM_MODEL/Triangle Generator/Model/Add3" ) , TARGET_STRING ( "" ) , 0 , 0
, 0 , 0 , 2 } , { 24 , 0 , TARGET_STRING (
"TX_PM_MODEL/Triangle Generator/Model/Unit Delay" ) , TARGET_STRING ( "" ) ,
0 , 0 , 0 , 0 , 3 } , { 0 , 0 , ( NULL ) , ( NULL ) , 0 , 0 , 0 , 0 , 0 } } ;
static const rtwCAPI_BlockParameters rtBlockParameters [ ] = { { 25 ,
TARGET_STRING ( "TX_PM_MODEL/Constant3" ) , TARGET_STRING ( "Value" ) , 0 , 0
, 0 } , { 26 , TARGET_STRING ( "TX_PM_MODEL/Constant5" ) , TARGET_STRING (
"Value" ) , 0 , 0 , 0 } , { 27 , TARGET_STRING ( "TX_PM_MODEL/Gain" ) ,
TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 28 , TARGET_STRING (
"TX_PM_MODEL/Gain2" ) , TARGET_STRING ( "Gain" ) , 0 , 0 , 0 } , { 29 ,
TARGET_STRING ( "TX_PM_MODEL/Integrator" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 30 , TARGET_STRING (
"TX_PM_MODEL/Memory" ) , TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } ,
{ 31 , TARGET_STRING ( "TX_PM_MODEL/Relay" ) , TARGET_STRING (
"OnOutputValue" ) , 0 , 0 , 0 } , { 32 , TARGET_STRING ( "TX_PM_MODEL/Relay"
) , TARGET_STRING ( "OffOutputValue" ) , 0 , 0 , 0 } , { 33 , TARGET_STRING (
"TX_PM_MODEL/Transfer Fcn" ) , TARGET_STRING ( "A" ) , 0 , 0 , 0 } , { 34 ,
TARGET_STRING ( "TX_PM_MODEL/Transfer Fcn" ) , TARGET_STRING ( "C" ) , 0 , 0
, 0 } , { 35 , TARGET_STRING ( "TX_PM_MODEL/Transport Delay" ) ,
TARGET_STRING ( "DelayTime" ) , 0 , 0 , 0 } , { 36 , TARGET_STRING (
"TX_PM_MODEL/Transport Delay" ) , TARGET_STRING ( "InitialOutput" ) , 0 , 0 ,
0 } , { 37 , TARGET_STRING ( "TX_PM_MODEL/Sample and Hold/ " ) ,
TARGET_STRING ( "InitialOutput" ) , 0 , 0 , 0 } , { 38 , TARGET_STRING (
"TX_PM_MODEL/Triangle Generator/Model/Constant2" ) , TARGET_STRING ( "Value"
) , 0 , 0 , 0 } , { 39 , TARGET_STRING (
"TX_PM_MODEL/Triangle Generator/Model/Constant3" ) , TARGET_STRING ( "Value"
) , 0 , 0 , 0 } , { 40 , TARGET_STRING (
"TX_PM_MODEL/Triangle Generator/Model/Constant4" ) , TARGET_STRING ( "Value"
) , 0 , 0 , 0 } , { 41 , TARGET_STRING (
"TX_PM_MODEL/Triangle Generator/Model/1\\ib1" ) , TARGET_STRING ( "Gain" ) ,
0 , 0 , 0 } , { 42 , TARGET_STRING (
"TX_PM_MODEL/Triangle Generator/Model/1-D Lookup Table" ) , TARGET_STRING (
"Table" ) , 0 , 3 , 0 } , { 43 , TARGET_STRING (
"TX_PM_MODEL/Triangle Generator/Model/1-D Lookup Table" ) , TARGET_STRING (
"BreakpointsForDimension1" ) , 0 , 3 , 0 } , { 44 , TARGET_STRING (
"TX_PM_MODEL/Triangle Generator/Model/Unit Delay" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 0 , ( NULL ) , ( NULL ) , 0 , 0 , 0 }
} ; static int_T rt_LoggedStateIdxList [ ] = { - 1 } ; static const
rtwCAPI_Signals rtRootInputs [ ] = { { 0 , 0 , ( NULL ) , ( NULL ) , 0 , 0 ,
0 , 0 , 0 } } ; static const rtwCAPI_Signals rtRootOutputs [ ] = { { 0 , 0 ,
( NULL ) , ( NULL ) , 0 , 0 , 0 , 0 , 0 } } ; static const
rtwCAPI_ModelParameters rtModelParameters [ ] = { { 45 , TARGET_STRING ( "I0"
) , 0 , 0 , 0 } , { 46 , TARGET_STRING ( "VDD" ) , 0 , 0 , 0 } , { 47 ,
TARGET_STRING ( "VDD_DRIVE" ) , 0 , 0 , 0 } , { 48 , TARGET_STRING ( "Vh" ) ,
0 , 0 , 0 } , { 49 , TARGET_STRING ( "Vl" ) , 0 , 0 , 0 } , { 50 ,
TARGET_STRING ( "deltaVOSC" ) , 0 , 0 , 0 } , { 0 , ( NULL ) , 0 , 0 , 0 } }
;
#ifndef HOST_CAPI_BUILD
static void * rtDataAddrMap [ ] = { & rtB . hnltplbdv1 , & rtB . ckq35jkg2y ,
& rtB . h3fdkbfjnp , & rtB . pbejybptra , & rtB . or1qvnhrlo , & rtB .
mlx0mmcucs , & rtB . dke1cfa4ea , & rtB . otsbybmj2w , & rtB . fvbnvihw2k , &
rtB . htg2xosuwx , & rtB . ii304m0uao , & rtB . p4b2dhw3jt , & rtB .
catrevm5rx , & rtB . o0cqqnpekr , & rtB . iqxaw1e2wm , & rtB . hnltplbdv1 , &
rtB . pzggivk2nk [ 0 ] , & rtB . ah1knnixy1 [ 0 ] , & rtB . dzo3h1kxld [ 0 ]
, & rtB . dpnt5xseaq [ 0 ] , & rtB . bszi4f25a5 , & rtB . mlo2m0qs0q , & rtB
. h4r1sws3ty , & rtB . eqskwvzstb , & rtB . f1rw0wc1yz , & rtP .
Constant3_Value_kzpj52qcj4 , & rtP . Constant5_Value , & rtP . Gain_Gain , &
rtP . Gain2_Gain , & rtP . Integrator_IC , & rtP . Memory_InitialCondition ,
& rtP . Relay_YOn , & rtP . Relay_YOff , & rtP . TransferFcn_A , & rtP .
TransferFcn_C , & rtP . TransportDelay_Delay , & rtP .
TransportDelay_InitOutput , & rtP . _Y0 , & rtP . Constant2_Value , & rtP .
Constant3_Value , & rtP . Constant4_Value , & rtP . uib1_Gain , & rtP .
uDLookupTable_tableData [ 0 ] , & rtP . uDLookupTable_bp01Data [ 0 ] , & rtP
. UnitDelay_InitialCondition , & rtP . I0 , & rtP . VDD , & rtP . VDD_DRIVE ,
& rtP . Vh , & rtP . Vl , & rtP . deltaVOSC , } ; static int32_T *
rtVarDimsAddrMap [ ] = { ( NULL ) } ;
#endif
static TARGET_CONST rtwCAPI_DataTypeMap rtDataTypeMap [ ] = { { "double" ,
"real_T" , 0 , 0 , sizeof ( real_T ) , ( uint8_T ) SS_DOUBLE , 0 , 0 , 0 } ,
{ "unsigned char" , "boolean_T" , 0 , 0 , sizeof ( boolean_T ) , ( uint8_T )
SS_BOOLEAN , 0 , 0 , 0 } } ;
#ifdef HOST_CAPI_BUILD
#undef sizeof
#endif
static TARGET_CONST rtwCAPI_ElementMap rtElementMap [ ] = { { ( NULL ) , 0 ,
0 , 0 , 0 } , } ; static const rtwCAPI_DimensionMap rtDimensionMap [ ] = { {
rtwCAPI_SCALAR , 0 , 2 , 0 } , { rtwCAPI_VECTOR , 2 , 2 , 0 } , {
rtwCAPI_VECTOR , 4 , 2 , 0 } , { rtwCAPI_VECTOR , 6 , 2 , 0 } } ; static
const uint_T rtDimensionArray [ ] = { 1 , 1 , 4 , 1 , 12 , 1 , 1 , 3 } ;
static const real_T rtcapiStoredFloats [ ] = { 0.0 , 1.0 , 5.0E-7 , 2.5E-7 }
; static const rtwCAPI_FixPtMap rtFixPtMap [ ] = { { ( NULL ) , ( NULL ) ,
rtwCAPI_FIX_RESERVED , 0 , 0 , ( boolean_T ) 0 } , } ; static const
rtwCAPI_SampleTimeMap rtSampleTimeMap [ ] = { { ( NULL ) , ( NULL ) , - 1 , 0
} , { ( const void * ) & rtcapiStoredFloats [ 0 ] , ( const void * ) &
rtcapiStoredFloats [ 1 ] , ( int8_T ) 1 , ( uint8_T ) 0 } , { ( const void *
) & rtcapiStoredFloats [ 0 ] , ( const void * ) & rtcapiStoredFloats [ 0 ] ,
( int8_T ) 0 , ( uint8_T ) 0 } , { ( const void * ) & rtcapiStoredFloats [ 2
] , ( const void * ) & rtcapiStoredFloats [ 3 ] , ( int8_T ) 2 , ( uint8_T )
0 } } ; static rtwCAPI_ModelMappingStaticInfo mmiStatic = { { rtBlockSignals
, 25 , rtRootInputs , 0 , rtRootOutputs , 0 } , { rtBlockParameters , 20 ,
rtModelParameters , 6 } , { ( NULL ) , 0 } , { rtDataTypeMap , rtDimensionMap
, rtFixPtMap , rtElementMap , rtSampleTimeMap , rtDimensionArray } , "float"
, { 2303698878U , 2012635106U , 128554924U , 2040453846U } , ( NULL ) , 0 , (
boolean_T ) 0 , rt_LoggedStateIdxList } ; const
rtwCAPI_ModelMappingStaticInfo * TX_PM_MODEL_GetCAPIStaticMap ( void ) {
return & mmiStatic ; }
#ifndef HOST_CAPI_BUILD
void TX_PM_MODEL_InitializeDataMapInfo ( void ) { rtwCAPI_SetVersion ( ( *
rt_dataMapInfoPtr ) . mmi , 1 ) ; rtwCAPI_SetStaticMap ( ( *
rt_dataMapInfoPtr ) . mmi , & mmiStatic ) ; rtwCAPI_SetLoggingStaticMap ( ( *
rt_dataMapInfoPtr ) . mmi , ( NULL ) ) ; rtwCAPI_SetDataAddressMap ( ( *
rt_dataMapInfoPtr ) . mmi , rtDataAddrMap ) ; rtwCAPI_SetVarDimsAddressMap (
( * rt_dataMapInfoPtr ) . mmi , rtVarDimsAddrMap ) ;
rtwCAPI_SetInstanceLoggingInfo ( ( * rt_dataMapInfoPtr ) . mmi , ( NULL ) ) ;
rtwCAPI_SetChildMMIArray ( ( * rt_dataMapInfoPtr ) . mmi , ( NULL ) ) ;
rtwCAPI_SetChildMMIArrayLen ( ( * rt_dataMapInfoPtr ) . mmi , 0 ) ; }
#else
#ifdef __cplusplus
extern "C" {
#endif
void TX_PM_MODEL_host_InitializeDataMapInfo ( TX_PM_MODEL_host_DataMapInfo_T
* dataMap , const char * path ) { rtwCAPI_SetVersion ( dataMap -> mmi , 1 ) ;
rtwCAPI_SetStaticMap ( dataMap -> mmi , & mmiStatic ) ;
rtwCAPI_SetDataAddressMap ( dataMap -> mmi , ( NULL ) ) ;
rtwCAPI_SetVarDimsAddressMap ( dataMap -> mmi , ( NULL ) ) ; rtwCAPI_SetPath
( dataMap -> mmi , path ) ; rtwCAPI_SetFullPath ( dataMap -> mmi , ( NULL ) )
; rtwCAPI_SetChildMMIArray ( dataMap -> mmi , ( NULL ) ) ;
rtwCAPI_SetChildMMIArrayLen ( dataMap -> mmi , 0 ) ; }
#ifdef __cplusplus
}
#endif
#endif
