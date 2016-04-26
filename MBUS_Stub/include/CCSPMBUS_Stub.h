/*
 * ============================================================================
 * COMCAST C O N F I D E N T I A L AND PROPRIETARY
 * ============================================================================
 * This file (and its contents) are the intellectual property of Comcast.  It may
 * not be used, copied, distributed or otherwise  disclosed in whole or in part
 * without the express written permission of Comcast.
 * ============================================================================
 * Copyright (c) 2014 Comcast. All rights reserved.
 * ============================================================================
 */

#ifndef __CCSPMBUSSTUB_STUB_H__
#define __CCSPMBUSSTUB_STUB_H__
#include <json/json.h>
#include <unistd.h>
#include <string.h>
#include <dlfcn.h>
#include <stdlib.h>
#include "rdkteststubintf.h"
#include "rdktestagentintf.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <fstream>
#include <sstream>
#define IN
#define OUT

#define TEST_SUCCESS true
#define TEST_FAILURE false
#define MAX_PARAM_SIZE	100
#define MAX_PARAM_NAMES_ARRAY	1000

class RDKTestAgent;

class CCSPMBUS : public RDKTestStubInterface
{
    public:
        /*Constructor*/
        CCSPMBUS();

        /*inherited functions*/
        bool initialize(IN const char* szVersion, IN RDKTestAgent *ptrAgentObj);
        bool cleanup(IN const char* szVersion,IN RDKTestAgent *ptrAgentObj);
        std::string testmodulepre_requisites();
        bool testmodulepost_requisites();

        bool CCSPMBUS_GetParamValues(IN const Json::Value& req, OUT Json::Value& response);
        bool CCSPMBUS_SetParamValues(IN const Json::Value& req, OUT Json::Value& response);
        bool CCSPMBUS_Init(IN const Json::Value& req, OUT Json::Value& response);
        bool CCSPMBUS_Exit(IN const Json::Value& req, OUT Json::Value& response);
        bool CCSPMBUS_RegisterEvent(IN const Json::Value& req, OUT Json::Value& response);
        bool CCSPMBUS_UnRegisterEvent(IN const Json::Value& req, OUT Json::Value& response);
        bool CCSPMBUS_LoadCfg(IN const Json::Value& req, OUT Json::Value& response);
        bool CCSPMBUS_LoadDmXml(IN const Json::Value& req, OUT Json::Value& response);
        bool CCSPMBUS_RegisterPath(IN const Json::Value& req, OUT Json::Value& response);
        bool CCSPMBUS_QueryStatus(IN const Json::Value& req, OUT Json::Value& response);
        bool CCSPMBUS_GetAllocMemory(IN const Json::Value& req, OUT Json::Value& response);
        bool CCSPMBUS_GetMaxMemory(IN const Json::Value& req, OUT Json::Value& response);
        bool CCSPMBUS_RegisterCapabilities(IN const Json::Value& req, OUT Json::Value& response);
        bool CCSPMBUS_UnRegisterNamespace(IN const Json::Value& req, OUT Json::Value& response);
        bool CCSPMBUS_UnRegisterComponent(IN const Json::Value& req, OUT Json::Value& response);
        bool CCSPMBUS_DiskNamespaceSupportedByComponent(IN const Json::Value& req, OUT Json::Value& response);
        bool CCSPMBUS_DiskComponentSupportingDynamicTbl(IN const Json::Value& req, OUT Json::Value& response);
        bool CCSPMBUS_GetRegisteredComponents(IN const Json::Value& req, OUT Json::Value& response);
        bool CCSPMBUS_GetHealth(IN const Json::Value& req, OUT Json::Value& response);
        bool CCSPMBUS_DumpComponentRegistry(IN const Json::Value& req, OUT Json::Value& response);
        bool CCSPMBUS_IsSystemReady(IN const Json::Value& req, OUT Json::Value& response);
        bool CCSPMBUS_SendSignal(IN const Json::Value& req, OUT Json::Value& response);
        bool CCSPMBUS_ReqSessionId(const Json::Value&, Json::Value&);
        bool CCSPMBUS_InformEndSession(const Json::Value&, Json::Value&);
        bool CCSPMBUS_BusCheck(const Json::Value&, Json::Value&);
        bool CCSPMBUS_CheckNamespaceDataType(const Json::Value&, Json::Value&);
        bool CCSPMBUS_RegisterBase(IN const Json::Value& req, OUT Json::Value& response);
        bool CCSPMBUS_CosaWifiInit(IN const Json::Value& req, OUT Json::Value& response);
};
#endif //__CCSPMBUS_STUB_H__
