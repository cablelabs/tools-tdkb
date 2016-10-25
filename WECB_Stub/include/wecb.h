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

#ifndef __WECB_STUB_H__
#define __WECB_STUB_H__
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

class WECB : public RDKTestStubInterface
{
    public:
        /*Constructor*/
        WECB();

        /*inherited functions*/
        bool initialize(IN const char* szVersion, IN RDKTestAgent *ptrAgentObj);
        bool cleanup(IN const char* szVersion,IN RDKTestAgent *ptrAgentObj);
        std::string testmodulepre_requisites();
        bool testmodulepost_requisites();

        /*WECB Wrapper functions*/
        bool WECB_GetParamNames(IN const Json::Value& req, OUT Json::Value& response);
        bool WECB_GetParamValues(IN const Json::Value& req, OUT Json::Value& response);
        bool WECB_GetParamAttributes(IN const Json::Value& req, OUT Json::Value& response);
        bool WECB_SetParamValues(IN const Json::Value& req, OUT Json::Value& response);
        bool WECB_SetParamAttribute(IN const Json::Value& req, OUT Json::Value& response);
        bool WECB_SetSessionId(IN const Json::Value& req, OUT Json::Value& response);
        bool WECB_AddObject(IN const Json::Value& req, OUT Json::Value& response);
        bool WECB_DelObject(IN const Json::Value& req, OUT Json::Value& response);
        bool WECB_SetCommit(IN const Json::Value& req, OUT Json::Value& response);

};
#endif //__WECB_STUB_H__
