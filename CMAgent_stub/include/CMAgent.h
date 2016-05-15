/*
* ============================================================================
* COMCAST CONFIDENTIAL AND PROPRIETARY
* ============================================================================

* This file and its contents are the intellectual property of Comcast.  It may
* not be used, copied, distributed or otherwise  disclosed in whole or in part
* without the express written permission of Comcast.

* ============================================================================
* Copyright (c) 2016 Comcast. All rights reserved.
* ============================================================================
*/
#ifndef __CMAGENT_STUB_H__
#define __CMAGENT_STUB_H__
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

class CMAgent : public RDKTestStubInterface
{
    public:
        /*Ctor*/
        CMAgent();

        /*inherited functions*/
        bool initialize(IN const char* szVersion, IN RDKTestAgent *ptrAgentObj);

        bool cleanup(IN const char* szVersion,IN RDKTestAgent *ptrAgentObj);
        std::string testmodulepre_requisites();
        bool testmodulepost_requisites();
        /*CM Agent Stub Wrapper functions*/
        bool CMAgent_Get(IN const Json::Value& req, OUT Json::Value& response);
        bool CMAgent_GetAttr(IN const Json::Value& req, OUT Json::Value& response);
        bool CMAgent_SetAttr(IN const Json::Value& req, OUT Json::Value& response);
        bool CMAgent_GetNames(IN const Json::Value& req, OUT Json::Value& response);
        bool CMAgent_Set(IN const Json::Value& req, OUT Json::Value& response);
        bool CMAgent_Set_Get(IN const Json::Value& req, OUT Json::Value& response);
        bool CMAgent_AddObject(IN const Json::Value& req, OUT Json::Value& response);
        bool CMAgent_DelObject(IN const Json::Value& req, OUT Json::Value& response);
        bool CMAgent_SetCommit(IN const Json::Value& req, OUT Json::Value& response);
        bool CMAgent_GetHealth(IN const Json::Value& req, OUT Json::Value& response);
        bool CMAgent_SetSessionId(IN const Json::Value& req, OUT Json::Value& response);

};
#endif //__CMAGENT_STUB_H__
