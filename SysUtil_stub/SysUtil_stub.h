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

#ifndef __SysUtil_STUB_H__
#define __SysUtil_STUB_H__

#include <json/json.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <algorithm>

#include "rdkteststubintf.h"
#include "rdktestagentintf.h"

#define IN
#define OUT

#define BUFF_LENGTH 512

#define TEST_SUCCESS true
#define TEST_FAILURE false


using namespace std;

class RDKTestAgent;
class SysUtilAgent : public RDKTestStubInterface
{
        public:
                /*Constructor*/
                SysUtilAgent();

                /*Inherited functions*/
                bool initialize(IN const char* szVersion, IN RDKTestAgent *ptrAgentObj);
                bool cleanup(const char*, RDKTestAgent*);
                std::string testmodulepre_requisites();
                bool testmodulepost_requisites();
                bool SysUtilAgent_ExecuteCmd(IN const Json::Value& req, OUT Json::Value& response);
};

extern "C" SysUtilAgent* CreateObject();
#endif