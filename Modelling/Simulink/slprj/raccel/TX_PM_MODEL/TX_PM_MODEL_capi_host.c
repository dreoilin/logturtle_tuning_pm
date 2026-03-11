#include "TX_PM_MODEL_capi_host.h"
static TX_PM_MODEL_host_DataMapInfo_T root;
static int initialized = 0;
rtwCAPI_ModelMappingInfo *getRootMappingInfo()
{
    if (initialized == 0) {
        initialized = 1;
        TX_PM_MODEL_host_InitializeDataMapInfo(&(root), "TX_PM_MODEL");
    }
    return &root.mmi;
}

rtwCAPI_ModelMappingInfo *mexFunction(){return(getRootMappingInfo());}
