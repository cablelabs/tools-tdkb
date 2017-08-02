/*
 * Copyright 2016-2017 Intel Corporation
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
#ifndef __ETHSW_STUB_HAL_H__
#define __ETHSW_STUB_HAL_H__

#include "rdkteststubintf.h"
#include "rdktestagentintf.h"
#include "ssp_tdk_Ethsw_wrp.h"
/* for reference added it,(IN) indicates accepting the request from Test Manager and (OUT) 
   indicates sending the response for the request back to the Manager */
#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

using namespace std;
/* RDKTestAgent : This Class provides interface for the module to enable RPC mechanism. */
class RDKTestAgent;
/* RDKTestStubInterface : This Class provides provides interface for the modules.  */
class ethsw_stub_hal : public RDKTestStubInterface
{
	public:
		/*Constructor*/
		ethsw_stub_hal();
		bool initialize(IN const char* szVersion, IN RDKTestAgent *ptrAgentObj);
		bool cleanup(const char*, RDKTestAgent*);
		std::string testmodulepre_requisites();
		bool testmodulepost_requisites();
		bool ethsw_stub_hal_Get_Port_Admin_Status(const Json::Value&, Json::Value&);
		bool ethsw_stub_hal_Get_Port_Cfg(const Json::Value&, Json::Value&);
		bool ethsw_stub_hal_Get_Port_Status(const Json::Value&, Json::Value&);
		bool ethsw_stub_hal_Init(IN const Json::Value& req, OUT Json::Value& response);
		bool ethsw_stub_hal_LocatePort_By_MacAddress(IN const Json::Value& req, OUT Json::Value& response);
		bool ethsw_stub_hal_SetAgingSpeed(IN const Json::Value& req, OUT Json::Value& response);
		bool ethsw_stub_hal_SetPortAdminStatus(IN const Json::Value& req, OUT Json::Value& response);
		bool ethsw_stub_hal_SetPortCfg(IN const Json::Value& req, OUT Json::Value& response);
};
#endif
