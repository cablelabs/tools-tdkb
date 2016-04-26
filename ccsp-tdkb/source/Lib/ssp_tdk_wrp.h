/*
 * ============================================================================
 * COMCAST C O N F I D E N T I A L AND PROPRIETARY
 * ============================================================================
 * This file and its contents are the intellectual property of Comcast.  It may
 * not be used, copied, distributed or otherwise  disclosed in whole or in part
 * without the express written permission of Comcast.
 * ============================================================================
 * Copyright (c) 2014 Comcast. All rights reserved.
 * ============================================================================
 */

#ifndef __SSP_TDK_WRP_H__
#define __SSP_TDK_WRP_H__

#define	MAX_ATTRIBUTE_SIZE	100
#define MAX_PARAM_SIZE		200
#define MAX_PARAMS_COMP		100
#define MAX_COMP_ARRAY		20
#define MAX_PARAM_NAMES_ARRAY   1000

#define SSP_TDK_SUCCESS     0
#define SSP_TDK_FAILURE     -1

enum
{
    SSP_STOP = 0,
    SSP_START
};

typedef struct GetNames_Struct
{
    char *pParamNames;
    bool writable;
}GETPARAMNAMES;

typedef struct GetValues_Struct
{
    char *pParamNames;
    char *pParamValues;
    int pParamType;
}GETPARAMVALUES;

typedef struct GetAttr_Struct
{
    char *pParamNames;
    char *pParamAccess;
    char *pParamNotify;

}GETPARAMATTR;

#endif
