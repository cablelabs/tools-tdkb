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

#ifndef __CosaCM_STUB_H__
#define __CosaCM_STUB_H__
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

class CosaCM : public RDKTestStubInterface
{
	public:
		
        /*Ctor*/
		CosaCM ();

		/*inherited functions*/
		bool initialize(IN const char* szVersion, IN RDKTestAgent *ptrAgentObj);

		bool cleanup(IN const char* szVersion,IN RDKTestAgent *ptrAgentObj);
		std::string testmodulepre_requisites();
        bool testmodulepost_requisites();
		
        /*CosaCM Stub Wrapper functions*/
		bool CosaCM_GetResetCount(IN const Json::Value& req, OUT Json::Value& response);	
		bool CosaCM_GetUpstreamChannelId(IN const Json::Value& req, OUT Json::Value& response);	
		bool CosaCM_SetUpstreamChannelId(IN const Json::Value& req, OUT Json::Value& response);	
		bool CosaCM_GetStartDSFrequency(IN const Json::Value& req, OUT Json::Value& response);
        bool CosaCM_SetStartDSFrequency(IN const Json::Value& req, OUT Json::Value& response);	
		bool CosaCM_GetProvType(IN const Json::Value& req, OUT Json::Value& response);	
        bool CosaCM_GetIPv6DHCPInfo(IN const Json::Value& req, OUT Json::Value& response);
        bool CosaCM_GetStatus(IN const Json::Value& req, OUT Json::Value& response);
        bool CosaCM_GetLoopDiagnosticsStart(IN const Json::Value& req, OUT Json::Value& response);
        bool CosaCM_GetLoopDiagnosticsDetails(IN const Json::Value& req, OUT Json::Value& response);
        bool CosaCM_GetTelephonyRegistrationStatus(IN const Json::Value& req, OUT Json::Value& response);
        bool CosaCM_GetTelephonyTftpStatus(IN const Json::Value& req, OUT Json::Value& response);
        bool CosaCM_GetTelephonyDHCPStatus(IN const Json::Value& req, OUT Json::Value& response);
        bool CosaCM_SetLoopDiagnosticsStart(IN const Json::Value& req, OUT Json::Value& response);
        bool COSACM_GetDHCPInfo(IN const Json::Value& req, OUT Json::Value& response);
        bool COSACM_GetDOCSISInfo(IN const Json::Value& req, OUT Json::Value& response);
        bool COSACM_GetLog(IN const Json::Value& req, OUT Json::Value& response);
        bool COSACM_SetLog(IN const Json::Value& req, OUT Json::Value& response);
        bool COSACM_GetDocsisLog(IN const Json::Value& req, OUT Json::Value& response);
        bool COSACM_GetDownstreamChannel(IN const Json::Value& req, OUT Json::Value& response);
        bool COSACM_GetUpstreamChannel(IN const Json::Value& req, OUT Json::Value& response);
        bool COSACM_CableModemCreate(IN const Json::Value& req, OUT Json::Value& response);
        bool COSACM_CableModemInitialize(IN const Json::Value& req, OUT Json::Value& response);
        bool COSACM_CableModemRemove(IN const Json::Value& req, OUT Json::Value& response);
        bool COSACM_GetMarket_ArgMemory_unalloc(IN const Json::Value& req, OUT Json::Value& response);  
        bool COSACM_SetMDDIPOverride_ArgMemory_unalloc(IN const Json::Value& req, OUT Json::Value& response);   
        bool COSACM_GetMDDIPOverride_ArgMemory_unalloc(IN const Json::Value& req, OUT Json::Value& response);   
        bool COSACM_GetCMCert_ArgMemory_unalloc(IN const Json::Value& req, OUT Json::Value& response);
        bool COSACM_GetCMErrorCodewords_InvalidArg(IN const Json::Value& req, OUT Json::Value& response);   
        bool COSACM_GetCMCertStatus_InvalidArg(IN const Json::Value& req, OUT Json::Value& response);   
        bool COSACM_GetCPEList_InvalidArg(IN const Json::Value& req, OUT Json::Value& response);
        bool COSACM_GetMarket(IN const Json::Value& req, OUT Json::Value& response);    
        bool COSACM_SetMDDIPOverride(IN const Json::Value& req, OUT Json::Value& response); 
        bool COSACM_GetMDDIPOverride(IN const Json::Value& req, OUT Json::Value& response); 
        bool COSACM_GetCMCert(IN const Json::Value& req, OUT Json::Value& response);
        bool COSACM_GetCMErrorCodewords(IN const Json::Value& req, OUT Json::Value& response);  
        bool COSACM_GetCMCertStatus(IN const Json::Value& req, OUT Json::Value& response);  
        bool COSACM_GetCPEList(IN const Json::Value& req, OUT Json::Value& response);

};
#endif //__CosaCM_STUB_H__
