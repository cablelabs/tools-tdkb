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
        bool WIFIAgent_SetMultiple(IN const Json::Value& req, OUT Json::Value& response);
        bool WIFIHal_CallMethodForULong(IN const Json::Value& req, OUT Json::Value& response);
        bool WIFIHal_CallMethodForBool(IN const Json::Value& req, OUT Json::Value& response);
        bool WIFIHal_CallMethodForString(IN const Json::Value& req, OUT Json::Value& response);
	bool WIFIHal_CallMethodForInt(IN const Json::Value& req, OUT Json::Value& response);
};
#endif //__WIFIAGENT_STUB_H__
