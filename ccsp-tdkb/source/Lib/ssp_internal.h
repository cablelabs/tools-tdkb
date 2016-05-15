/*
* ============================================================================
* COMCAST CONFIDENTIAL AND PROPRIETARY
* ============================================================================

* This file and its contents are the intellectual property of Comcast.  It may
* not be used, copied, distributed or otherwise  disclosed in whole or in part
* without the express written permission of Comcast.

* ============================================================================
* Copyright (c) 2016 Comcast. All rights reserved.
* ============================================================================
*/

#ifndef  _SSP_INTERNAL_
#define  _SSP_INTERNAL_

#define  CCSP_COMMON_COMPONENT_HEALTH_Red                   1
#define  CCSP_COMMON_COMPONENT_HEALTH_Yellow                2
#define  CCSP_COMMON_COMPONENT_HEALTH_Green                 3

#define  CCSP_COMMON_COMPONENT_STATE_Initializing           1
#define  CCSP_COMMON_COMPONENT_STATE_Running                2
#define  CCSP_COMMON_COMPONENT_STATE_Blocked                3
#define  CCSP_COMMON_COMPONENT_STATE_Paused                 3

#define  CCSP_COMMON_COMPONENT_FREERESOURCES_PRIORITY_High  1
#define  CCSP_COMMON_COMPONENT_FREERESOURCES_PRIORITY_Low   2


extern   PCCSP_COMPONENT_CFG                        gpPnmStartCfg;

typedef  struct
_COMPONENT_COMMON_DM
{
    char*                           Name;
    ULONG                           Version;
    char*                           Author;
    ULONG                           Health;
    ULONG                           State;

    BOOL                            LogEnable;
    ULONG                           LogLevel;

    ULONG                           MemMaxUsage;
    ULONG                           MemMinUsage;
    ULONG                           MemConsumed;
}
COMPONENT_COMMON_DM,  *PCOMPONENT_COMMON_DM;

#define ComponentCommonDmInit(component_common_dm)                                          \
{                                                                                   \
    AnscZeroMemory(component_common_dm, sizeof(COMPONENT_COMMON_DM));               \
    component_common_dm->Name        = NULL;                                        \
    component_common_dm->Version     = 1;                                           \
    component_common_dm->Author      = NULL;                                        \
    component_common_dm->Health      = CCSP_COMMON_COMPONENT_HEALTH_Red;            \
    component_common_dm->State       = CCSP_COMMON_COMPONENT_STATE_Running;         \
    if(g_iTraceLevel >= CCSP_TRACE_LEVEL_EMERGENCY)                                 \
    component_common_dm->LogLevel = (ULONG) g_iTraceLevel;                     \
    component_common_dm->LogEnable   = TRUE;                                        \
    component_common_dm->MemMaxUsage = 0;                                           \
    component_common_dm->MemMinUsage = 0;                                           \
    component_common_dm->MemConsumed = 0;                                           \
}


#define  ComponentCommonDmClean(component_common_dm)                                        \
{                                                                                  \
    if ( component_common_dm->Name )                                                \
    {                                                                               \
        AnscFreeMemory(component_common_dm->Name);                                  \
    }                                                                               \
    \
    if ( component_common_dm->Author )                                              \
    {                                                                               \
        AnscFreeMemory(component_common_dm->Author);                                \
    }                                                                               \
}


#define  ComponentCommonDmFree(component_common_dm)                                         \
{                                                                                  \
    ComponentCommonDmClean(component_common_dm);                                    \
    AnscFreeMemory(component_common_dm);                                            \
}

int  cmd_dispatch(int  command);

void load_data_model();


ANSC_STATUS
ssp_create_pnm
(
 PCCSP_COMPONENT_CFG         pStartCfg
 );

ANSC_STATUS
ssp_engage_pnm
(
 PCCSP_COMPONENT_CFG         pStartCfg
 );

ANSC_STATUS
ssp_cancel_pnm
(
 PCCSP_COMPONENT_CFG         pStartCfg
 );


ANSC_STATUS 
ssp_LoadCosaPluginLibrary
(
);

ANSC_STATUS
MessageBusTaskSim
(
 ANSC_HANDLE hThisObject
 );

char*
ssp_PnmCCDmGetComponentName
(
 ANSC_HANDLE                     hThisObject
 );

ULONG
ssp_PnmCCDmGetComponentVersion
(
 ANSC_HANDLE                     hThisObject
 );

char*
ssp_PnmCCDmGetComponentAuthor
(
 ANSC_HANDLE                     hThisObject
 );

ULONG
ssp_PnmCCDmGetComponentHealth
(
 ANSC_HANDLE                     hThisObject
 );

ULONG
ssp_PnmCCDmGetComponentState
(
 ANSC_HANDLE                     hThisObject
 );

BOOL
ssp_PnmCCDmGetLoggingEnabled
(
 ANSC_HANDLE                     hThisObject
 );

ANSC_STATUS
ssp_PnmCCDmSetLoggingEnabled
(
 ANSC_HANDLE                     hThisObject,
 BOOL                            bEnabled
 );

ULONG
ssp_PnmCCDmGetLoggingLevel
(
 ANSC_HANDLE                     hThisObject
 );

ANSC_STATUS
ssp_PnmCCDmSetLoggingLevel
(
 ANSC_HANDLE                     hThisObject,
 ULONG                           LogLevel
 );

ULONG
ssp_PnmCCDmGetMemMaxUsage
(
 ANSC_HANDLE                     hThisObject
 );

ULONG
ssp_PnmCCDmGetMemMinUsage
(
 ANSC_HANDLE                     hThisObject
 );

ULONG
ssp_PnmCCDmGetMemConsumed
(
 ANSC_HANDLE                     hThisObject
 );

ANSC_STATUS
ssp_PnmCCDmApplyChanges
(
 ANSC_HANDLE                     hThisObject
 );

#endif
