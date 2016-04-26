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

#ifndef __ADVANCEDCONFIG_STUB_H__
#define __ADVANCEDCONFIG_STUB_H__

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

class AdvancedConfig : public RDKTestStubInterface
{
	public:
		/*Ctor*/
		AdvancedConfig();

		/*inherited functions*/
		bool initialize(IN const char* szVersion, IN RDKTestAgent *ptrAgentObj);
        bool cleanup(IN const char* szVersion,IN RDKTestAgent *ptrAgentObj);
		std::string testmodulepre_requisites();
        bool testmodulepost_requisites();
		/*CM Agent Stub Wrapper functions*/
		bool AdvancedConfig_Start(IN const Json::Value& req, OUT Json::Value& response);
		bool AdvancedConfig_Get(IN const Json::Value& req, OUT Json::Value& response);
		bool AdvancedConfig_GetAttr(IN const Json::Value& req, OUT Json::Value& response);
		bool AdvancedConfig_SetAttr(IN const Json::Value& req, OUT Json::Value& response);
		bool AdvancedConfig_GetNames(IN const Json::Value& req, OUT Json::Value& response);
		bool AdvancedConfig_Set(IN const Json::Value& req, OUT Json::Value& response);
		bool AdvancedConfig_Set_Get(IN const Json::Value& req, OUT Json::Value& response);
		bool AdvancedConfig_AddObject(IN const Json::Value& req, OUT Json::Value& response);
		bool AdvancedConfig_DelObject(IN const Json::Value& req, OUT Json::Value& response);
		bool AdvancedConfig_SetCommit(IN const Json::Value& req, OUT Json::Value& response);
		bool AdvancedConfig_GetHealth(IN const Json::Value& req, OUT Json::Value& response);
		bool AdvancedConfig_SetSessionId(IN const Json::Value& req, OUT Json::Value& response);
		bool AdvancedConfig_Stop(IN const Json::Value& req, OUT Json::Value& response);

};
extern "C" AdvancedConfig* CreateObject();
#endif //
