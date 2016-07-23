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

#ifndef __SSP_TDK_COSAMTA_WRP_H__
#define __SSP_TDK_COSAMTA_WRP_H__


#define SSP_SUCCESS       0

#define SSP_FAILURE   	  1

int ssp_CosaDmlMtaGetResetCount(int handleType, int bufferType, char *pResetType);
int ssp_CosaDmlMTAGetDHCPInfo(int handleType, int bufferType);
int ssp_CosaDmlMTATriggerDiagnostics();

int ssp_CosaDmlMtaBatteryGetInfo(int handleType, int bufferType);
int ssp_CosaDmlMtaBatteryGetStatus(int handleType, int bufferType);
int ssp_CosaDmlMtaBatteryGetPowerStatus(int handleType, int bufferType);
int ssp_CosaDmlMtaLineTableGetNumberOfEntries(int handleType);
int ssp_CosaDmlMtaLineTableGetEntry(int handleType,int bufferType);

int ssp_CosaDmlMTAGetServiceClass(int handleType);
int ssp_CosaDmlMTADectGetEnable(int handleType,int Value);
int ssp_CosaDmlMTADectSetEnable(int handleType,int Value);
int ssp_CosaDmlMTADectGetRegistrationMode(int handleType,int Value);
int ssp_CosaDmlMTADectSetRegistrationMode(int handleType,int Value);

int ssp_CosaDmlMTAGetDect(int handleType,int bufferType);
int ssp_CosaDmlMTAGetDectPIN(int handleType,int bufferType);
int ssp_CosaDmlMTASetDectPIN(int handleType,int bufferType);
int ssp_CosaDmlMTAGetCALLP(int handleType,int bufferType);
int ssp_CosaDmlMTAGetDSXLogEnable(int handleType,int Value);

int ssp_CosaDmlMTASetDSXLogEnable(int handleType,int Value);
int ssp_CosaDmlMTAClearDSXLog(int handleType,int Value);
int ssp_CosaDmlMTAGetCallSignallingLogEnable(int handleType,int Value);
int ssp_CosaDmlMTASetCallSignallingLogEnable(int handleType,int Value);
int ssp_CosaDmlMTAClearCallSignallingLog(int handleType,int Value);
int ssp_CosaDmlMtaBatteryGetNumberofCycles(int handleType);
int ssp_CosaDmlMtaBatteryGetRemainingTime(int handleType);
int ssp_CosaDmlMtaBatteryGetLife(int handleType,int bufferType);
int ssp_CosaDmlMtaBatteryGetCondition(int handleType,int bufferType);
#endif
