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

#ifndef __SSP_TDK_MBUS_WRP_H__
#define __SSP_TDK_MBUS_WRP_H__

#define SSP_MBUS_TRUE       	1

#define SSP_MBUS_SUCCESS	0

#define SSP_MBUS_FAILURE	-1

#define SSP_MBUS_EXEC_ERROR 	-2

#define  CCSP_NAME_PREFIX      	""

#if eRT
    #define CCSP_CR_NAME "eRT.com.cisco.spvtg.ccsp.CR"
    #define CCSP_CM_NAME "eRT.com.cisco.spvtg.ccsp.cm"
#else
    #define CCSP_CR_NAME "com.cisco.spvtg.ccsp.CR"
    #define CCSP_CM_NAME "com.cisco.spvtg.ccsp.cm"
#endif

#endif
