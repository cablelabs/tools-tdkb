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

#ifndef __CosaMTA_STUB_H__
#define __CosaMTA_STUB_H__
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

class CosaMTA : public RDKTestStubInterface
{
	public:
		
        /*Ctor*/
		CosaMTA ();

		/*inherited functions*/
		bool initialize(IN const char* szVersion, IN RDKTestAgent *ptrAgentObj);

		bool cleanup(IN const char* szVersion,IN RDKTestAgent *ptrAgentObj);
		std::string testmodulepre_requisites();
        bool testmodulepost_requisites();
		
        /*CosaMTA Stub Wrapper functions*/
        bool CosaMTA_GetResetCount(IN const Json::Value& req, OUT Json::Value& response);	
        bool CosaMTA_GetDHCPInfo(IN const Json::Value& req, OUT Json::Value& response);
        bool CosaMTA_Triggerdiagnostics(IN const Json::Value& req, OUT Json::Value& response);
        bool CosaMTA_BatteryGetInfo(IN const Json::Value& req, OUT Json::Value& response);
        bool CosaMTA_BatteryGetStatus(IN const Json::Value& req, OUT Json::Value& response);
        bool CosaMTA_BatteryGetPowerStatus(IN const Json::Value& req, OUT Json::Value& response);
        bool CosaMTA_LineTableGetNumberOfEntries(IN const Json::Value& req, OUT Json::Value& response);
        bool CosaMTA_LineTableGetEntry(IN const Json::Value& req, OUT Json::Value& response);

        bool CosaMTA_GetServiceClass(IN const Json::Value& req, OUT Json::Value& response);
        bool CosaMTA_DectGetEnable(IN const Json::Value& req, OUT Json::Value& response);
        bool CosaMTA_DectSetEnable(IN const Json::Value& req, OUT Json::Value& response);
        bool CosaMTA_DectGetRegistrationMode(IN const Json::Value& req, OUT Json::Value& response);
        bool CosaMTA_DectSetRegistrationMode(IN const Json::Value& req, OUT Json::Value& response);

        bool CosaMTA_GetDect(IN const Json::Value& req, OUT Json::Value& response);
        bool CosaMTA_GetDectPIN(IN const Json::Value& req, OUT Json::Value& response);
        bool CosaMTA_SetDectPIN(IN const Json::Value& req, OUT Json::Value& response);
        bool CosaMTA_GetDSXLogEnable(IN const Json::Value& req, OUT Json::Value& response);

        bool CosaMTA_SetDSXLogEnable(IN const Json::Value& req, OUT Json::Value& response);
        bool CosaMTA_ClearDSXLog(IN const Json::Value& req, OUT Json::Value& response);
        bool CosaMTA_GetCallSignallingLogEnable(IN const Json::Value& req, OUT Json::Value& response);
        bool CosaMTA_SetCallSignallingLogEnable(IN const Json::Value& req, OUT Json::Value& response);
 
        bool CosaMTA_ClearCallSignallingLog(IN const Json::Value& req, OUT Json::Value& response);
        bool CosaMTA_BatteryGetNumberofCycles(IN const Json::Value& req, OUT Json::Value& response);
        bool CosaMTA_BatteryGetRemainingTime(IN const Json::Value& req, OUT Json::Value& response);
        bool CosaMTA_BatteryGetLife(IN const Json::Value& req, OUT Json::Value& response);
        bool CosaMTA_BatteryGetCondition(IN const Json::Value& req, OUT Json::Value& response);
};
#endif //__CosaMTA_STUB_H__
