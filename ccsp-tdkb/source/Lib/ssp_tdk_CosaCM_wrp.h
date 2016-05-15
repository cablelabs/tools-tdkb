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

#ifndef __SSP_TDK_COSACM_WRP_H__
#define __SSP_TDK_COSACM_WRP_H__


#define SSP_SUCCESS       0

#define SSP_FAILURE   	  1

int ssp_CosaDmlCMGetResetCount(int handleType, int bufferType, char *pResetType);
int ssp_CosaDmlCMGetLockedUpstreamChID(int handleType);
int ssp_CosaDmlCMSetLockedUpstreamChID(int handleType, int channelId);
int ssp_CosaDmlCMGetStartDSFrequency(int handleType);
int ssp_CosaDmlCMSetStartDSFrequency(int handleType, int frequency);
int ssp_CosaDmlCMGetProvType(int handleType, int bufferType);
int ssp_CosaDmlCMGetIPv6DHCPInfo(int handleType, int bufferType);
int ssp_CosaDmlCMGetStatus(int handleType, int Value);
int ssp_CosaCMGetLoopDiagnosticsStart(int handleType, int boolValue);
int ssp_CosaDmlCMGetLoopDiagnosticsDetails(int handleType, int Value);
int ssp_CosaDmlCMGetTelephonyRegistrationStatus(int handleType, int Value);
int ssp_CosaDmlCMGetTelephonyDHCPStatus(int handleType, int Value);
int ssp_CosaDmlCMGetTelephonyTftpStatus(int handleType, int Value);
int ssp_CosaDmlCMSetLoopDiagnosticsStart(int handleType, int boolValue);
int ssp_cosacm_GetDHCPInfo(int handleType, int bufferType);
int ssp_cosacm_GetDOCSISInfo(int handleType, int bufferType);
int ssp_cosacm_GetLog(int handleType, int bufferType);
int ssp_cosacm_SetLog(int handleType, int bufferType);
int ssp_cosacm_GetDocsisLog(int handleType, int bufferType);
int ssp_cosacm_GetDownstreamChannel(int handleType, int bufferType);
int ssp_cosacm_GetUpstreamChannel(int handleType, int bufferType);
int ssp_CosaCableModemCreate();
int ssp_CosaCableModemInitialize(int handleType);
int ssp_CosaCableModemRemove(int handleType);

#endif
