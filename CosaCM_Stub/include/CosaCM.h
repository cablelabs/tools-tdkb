/*
 * ============================================================================
 * COMCAST C O N F I D E N T I A L AND PROPRIETARY
 * ============================================================================
 * This file (and its contents) are the intellectual property of Comcast.  It may
 * not be used, copied, distributed or otherwise  disclosed in whole or in part
 * without the express written permission of Comcast.
 * ============================================================================
 * Copyright (c) 2016 Comcast. All rights reserved.
 * ============================================================================
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
