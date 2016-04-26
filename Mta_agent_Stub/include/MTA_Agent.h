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

#ifndef __MTA_agent_STUB_H__
#define __MTA_agent_STUB_H__

#include <json/json.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <net/if.h>


#include "rdkteststubintf.h"
#include "rdktestagentintf.h"

#define IN
#define OUT

#define TEST_SUCCESS true
#define TEST_FAILURE false


using namespace std;

class RDKTestAgent;
class MTA_Agent : public RDKTestStubInterface
{
    public:
        /*Constructor*/
        MTA_Agent();

        /*Inherited functions*/
        bool initialize(IN const char* szVersion, IN RDKTestAgent *ptrAgentObj);
        bool cleanup(const char*, RDKTestAgent*);
        std::string testmodulepre_requisites();
        bool testmodulepost_requisites();

        bool MTA_agent_Init(IN const Json::Value& req, OUT Json::Value& response);
        bool MTA_agent_Terminate(IN const Json::Value& req, OUT Json::Value& response);
        bool MTA_agent_GetParameterNames(IN const Json::Value& req, OUT Json::Value& response);
        bool MTA_agent_SetParameterValues(IN const Json::Value& req, OUT Json::Value& response);
        bool MTA_agent_GetParameterValues(IN const Json::Value& req, OUT Json::Value& response);
        bool MTA_agent_GetParameterAttr(IN const Json::Value& req, OUT Json::Value& response);
        bool MTA_agent_SetParameterAttr(IN const Json::Value& req, OUT Json::Value& response);		
        bool MTA_agent_Commit(IN const Json::Value& req, OUT Json::Value& response);
        bool MTA_agent_GetParameterNames_NextLevel(IN const Json::Value& req, OUT Json::Value& response);
        bool MTA_agent_AddTbl(IN const Json::Value& req, OUT Json::Value& response);
        bool MTA_agent_DelTble(IN const Json::Value& req, OUT Json::Value& response);
        bool MTA_agent_SetSessionId(IN const Json::Value& req, OUT Json::Value& response);
        bool MTA_agent_GetHealth(IN const Json::Value& req, OUT Json::Value& response);	

};

//extern "C" MTA_Agent* CreateObject();
#endif 
