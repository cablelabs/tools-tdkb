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

#ifndef __WIFIAGENT_STUB_H__
#define __WIFIAGENT_STUB_H__
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

class WIFIAgent : public RDKTestStubInterface
{
    public:
        /*Ctor*/
        WIFIAgent();

        /*inherited functions*/
        bool initialize(IN const char* szVersion, IN RDKTestAgent *ptrAgentObj);

        bool cleanup(IN const char* szVersion,IN RDKTestAgent *ptrAgentObj);
        std::string testmodulepre_requisites();
        bool testmodulepost_requisites();
        /*WIFI Stub Wrapper functions*/
        bool WIFIAgent_Start(IN const Json::Value& req, OUT Json::Value& response);
        bool WIFIAgent_Get(IN const Json::Value& req, OUT Json::Value& response);
        bool WIFIAgent_GetAttr(IN const Json::Value& req, OUT Json::Value& response);
        bool WIFIAgent_SetAttr(IN const Json::Value& req, OUT Json::Value& response);
        bool WIFIAgent_GetNames(IN const Json::Value& req, OUT Json::Value& response);
        bool WIFIAgent_Set(IN const Json::Value& req, OUT Json::Value& response);
        bool WIFIAgent_Set_Get(IN const Json::Value& req, OUT Json::Value& response);
        bool WIFIAgent_AddObject(IN const Json::Value& req, OUT Json::Value& response);
        bool WIFIAgent_DelObject(IN const Json::Value& req, OUT Json::Value& response);
        bool WIFIAgent_SetCommit(IN const Json::Value& req, OUT Json::Value& response);
        bool WIFIAgent_GetHealth(IN const Json::Value& req, OUT Json::Value& response);
        bool WIFIAgent_SetSessionId(IN const Json::Value& req, OUT Json::Value& response);
        bool WIFIAgent_Stop(IN const Json::Value& req, OUT Json::Value& response);

};
#endif //__WIFIAGENT_STUB_H__
