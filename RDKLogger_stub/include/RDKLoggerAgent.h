/*
 * ============================================================================
 * COMCAST C O N F I D E N T I A L AND PROPRIETARY
 * ============================================================================
 * This file and its contents are the intellectual property of Comcast.  It may
 * not be used, copied, distributed or otherwise  disclosed in whole or in part
 * without the express written permission of Comcast.
 * ============================================================================
 * Copyright (c) 2016 Comcast. All rights reserved.
 * ============================================================================
 */
#ifndef __RDKLOGGER_STUB_H__
#define __RDKLOGGER_STUB_H__
#include <json/json.h>
#include <string.h>
#include <stdlib.h>
#include "rdkteststubintf.h"
#include "rdktestagentintf.h"
#include "rdk_debug.h"
#include "rdk_utils.h"
#include <fstream>
#define IN
#define OUT
#define TEST_SUCCESS true
#define TEST_FAILURE false
#define TDKAGENT_LOG		"AgentConsole.log"
#define RDKLOGGER_LOG           "TESTLog.txt.0"
#define PRE_REQUISITE_FILE      "scripts/Rdklogger_pre-requisite.sh"
#define POST_REQUISITE_FILE     "scripts/Rdklogger_post-requisite.sh"
#define DEBUG_CONF		"debug.ini"
#define SIZE    		256
using namespace std;
class RDKTestAgent;
class RDKBLoggerAgent : public RDKTestStubInterface
{
        public:
                //Constructor
                RDKBLoggerAgent();
                //Inherited functions
                bool initialize(IN const char* szVersion, IN RDKTestAgent *ptrAgentObj);
                bool cleanup(const char*, RDKTestAgent*);
		std::string testmodulepre_requisites();
                bool testmodulepost_requisites();
                //RDKBLoggerAgent Wrapper functions
		bool RDKBLoggerAgent_Init(IN const Json::Value& req, OUT Json::Value& response);
		bool RDKBLoggerAgent_Log(IN const Json::Value& req, OUT Json::Value& response);
		bool RDKBLoggerAgent_Dbg_Enabled_Status(IN const Json::Value& req, OUT Json::Value& response);
		bool RDKBLoggerAgent_EnvGet(IN const Json::Value& req, OUT Json::Value& response);
		bool RDKBLoggerAgent_EnvGetNum(IN const Json::Value& req, OUT Json::Value& response);
		bool RDKBLoggerAgent_EnvGetValueFromNum(IN const Json::Value& req, OUT Json::Value& response);
		bool RDKBLoggerAgent_EnvGetModFromNum(IN const Json::Value& req, OUT Json::Value& response);
		bool RDKBLoggerAgent_CheckMPELogEnabled(IN const Json::Value& req, OUT Json::Value& response);
		bool RDKBLoggerAgent_Log_All(IN const Json::Value& req, OUT Json::Value& response);
		bool RDKBLoggerAgent_Log_None(IN const Json::Value& req, OUT Json::Value& response);
		bool RDKBLoggerAgent_Log_Trace(IN const Json::Value& req, OUT Json::Value& response);
		bool RDKBLoggerAgent_Log_InverseTrace(IN const Json::Value& req, OUT Json::Value& response);
		bool RDKBLoggerAgent_Log_Msg(IN const Json::Value& req, OUT Json::Value& response);
		bool RDKBLoggerAgent_SetLogLevel(IN const Json::Value& req, OUT Json::Value& response);
		bool RDKBLoggerAgent_GetLogLevel(IN const Json::Value& req, OUT Json::Value& response);
                bool RDKBLoggerAgent_Log_MPEOSDisabled(IN const Json::Value& req, OUT Json::Value& response);
};
        extern "C" RDKBLoggerAgent* CreateObject();
#endif //__RDKLOGGER_STUB_H__
