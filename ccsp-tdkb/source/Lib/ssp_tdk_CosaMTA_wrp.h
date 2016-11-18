/*
 * If not stated otherwise in this file or this component's Licenses.txt file the
 * following copyright and licenses apply:
 *
 * Copyright 2016 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

#ifndef __SSP_TDK_COSAMTA_WRP_H__
#define __SSP_TDK_COSAMTA_WRP_H__


#define SSP_SUCCESS       0

#define SSP_FAILURE   	  1

int ssp_CosaDmlMtaGetResetCount(int handleType, int bufferType, char *pResetType, unsigned long* ResetCount);
int ssp_CosaDmlMTAGetDHCPInfo(int handleType, int bufferType, void* DHCPInfo);
int ssp_CosaDmlMTATriggerDiagnostics();

int ssp_CosaDmlMtaBatteryGetInfo(int handleType, int bufferType, char* BatteryInfo);
int ssp_CosaDmlMtaBatteryGetStatus(int handleType, int bufferType, char* BatteryStatus);
int ssp_CosaDmlMtaBatteryGetPowerStatus(int handleType, int bufferType, char* Power);
int ssp_CosaDmlMtaLineTableGetNumberOfEntries(int handleType, int* Num);
int ssp_CosaDmlMtaLineTableGetEntry(int handleType,int bufferType, unsigned long* TableEntry);

int ssp_CosaDmlMTAGetServiceClass(int handleType, void* SerClass);
int ssp_CosaDmlMTADectGetEnable(int handleType,int Value);
int ssp_CosaDmlMTADectSetEnable(int handleType,int Value);
int ssp_CosaDmlMTADectGetRegistrationMode(int handleType,int Value);
int ssp_CosaDmlMTADectSetRegistrationMode(int handleType,int Value);

int ssp_CosaDmlMTAGetDect(int handleType,int bufferType, void* DectInfo);
int ssp_CosaDmlMTAGetDectPIN(int handleType,int bufferType,char *pin);
int ssp_CosaDmlMTASetDectPIN(int handleType,int bufferType);
int ssp_CosaDmlMTAGetCALLP(int handleType,int bufferType);
int ssp_CosaDmlMTAGetDSXLogEnable(int handleType,int Value,int *Bool);

int ssp_CosaDmlMTASetDSXLogEnable(int handleType,int Value);
int ssp_CosaDmlMTAClearDSXLog(int handleType,int Value);
int ssp_CosaDmlMTAGetCallSignallingLogEnable(int handleType,int Value, int *Bool);
int ssp_CosaDmlMTASetCallSignallingLogEnable(int handleType,int Value);
int ssp_CosaDmlMTAClearCallSignallingLog(int handleType,int Value);
int ssp_CosaDmlMtaBatteryGetNumberofCycles(int handleType, unsigned long* Num);
int ssp_CosaDmlMtaBatteryGetRemainingTime(int handleType,unsigned long* Num);
int ssp_CosaDmlMtaBatteryGetLife(int handleType,int bufferType,char *Life);
int ssp_CosaDmlMtaBatteryGetCondition(int handleType,int bufferType, char *Cond);
#endif
