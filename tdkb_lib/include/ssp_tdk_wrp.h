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

#ifndef __SSP_TDK_WRP_H__
#define __SSP_TDK_WRP_H__

#define	MAX_ATTRIBUTE_SIZE	100
#define MAX_PARAM_SIZE		200
#define MAX_PARAMS_COMP		100
#define MAX_COMP_ARRAY		20
#define MAX_PARAM_NAMES_ARRAY   1000

#define SSP_TDK_SUCCESS     0
#define SSP_TDK_FAILURE     -1
#define SSP_SUCCESS       0
#define SSP_FAILURE       1

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
typedef struct _Config
{
        unsigned long InstanceNumber;
        char Alias[20];
        int bEnabled;
        char Interface[20];
        int PassthroughEnable;
        char PassthroughDHCPPool;
}CFG;

typedef struct _Info
{
         unsigned long Status;
         unsigned long DHCPStatus;
         char IPAddress;
         char SubnetMask;
         int NumIPRouters;
         int NumDnsServers;
}INFO;

typedef struct _Poolcfg
{
       unsigned long InstanceNumber;
       char Alias[20];
       int bEnabled;
       char Interface[20];
       int Order;
       int VendorClassIDExclude;
       int ClientIDExclude;
       int ChaddrExclude;
       int UserClassIDExclude;
       int DNSServersEnabled;
       int LeaseTime;
}POOLCFG;

typedef struct _Dns
{
        unsigned long InstanceNumber;
        char Alias[20];
        int bEnabled;
        char Interface[20];
}DNS;

#endif
