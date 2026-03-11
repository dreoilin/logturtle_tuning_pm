#ifndef TX_PM_MODEL_cap_host_h__
#define TX_PM_MODEL_cap_host_h__
#ifdef HOST_CAPI_BUILD
#include "rtw_capi.h"
#include "rtw_modelmap_simtarget.h"
typedef struct { rtwCAPI_ModelMappingInfo mmi ; }
TX_PM_MODEL_host_DataMapInfo_T ;
#ifdef __cplusplus
extern "C" {
#endif
void TX_PM_MODEL_host_InitializeDataMapInfo ( TX_PM_MODEL_host_DataMapInfo_T
* dataMap , const char * path ) ;
#ifdef __cplusplus
}
#endif
#endif
#endif
