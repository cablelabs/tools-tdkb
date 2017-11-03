/****************************************************************************
  Copyright 2016-2017 Intel Corporation

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*******************************************************************************/

#ifndef __DHCP_STUB_HAL_STUB_H__
#define __DHCP_STUB_HAL_STUB_H__
#include "rdkteststubintf.h"
#include "rdktestagentintf.h"
#include "ssp_tdk_dhcp_hal_wrp.h"

/* for reference added it,(IN) indicates accepting the request from Test Manager 
   and (OUT) indicates sending the response for the request back to the Manager
*/
#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

using namespace std;
/* RDKTestAgent : This Class provides interface for the module to enable RPC mechanism. */
class RDKTestAgent;
/* RDKTestStubInterface : This Class provides provides interface for the modules. */
class dhcp_stub_hal : public RDKTestStubInterface
{
	public:
		dhcp_stub_hal();
		bool initialize(IN const char* szVersion, IN RDKTestAgent *ptrAgentObj);
		bool cleanup(const char*, RDKTestAgent*);
		std::string testmodulepre_requisites();
		bool testmodulepost_requisites();
		bool dhcp_stub_hal_get_ecm_config_attempts(IN const Json::Value& req, OUT Json::Value& response);
		bool dhcp_stub_hal_get_ecm_dhcp_svr(IN const Json::Value& req, OUT Json::Value& response);
		bool dhcp_stub_hal_get_ecm_dns_svrs(IN const Json::Value& req, OUT Json::Value& response);
		bool dhcp_stub_hal_get_ecm_fsm_state(IN const Json::Value& req, OUT Json::Value& response);
		bool dhcp_stub_hal_get_ecm_gw(IN const Json::Value& req, OUT Json::Value& response);
		bool dhcp_stub_hal_get_ecm_ifname(IN const Json::Value& req, OUT Json::Value& response);
		bool dhcp_stub_hal_get_ecm_ip_addr(IN const Json::Value& req, OUT Json::Value& response);
		bool dhcp_stub_hal_get_ecm_lease_time(IN const Json::Value& req, OUT Json::Value& response);
		bool dhcp_stub_hal_get_ecm_mask(IN const Json::Value& req, OUT Json::Value& response);
		bool dhcp_stub_hal_get_ecm_remain_lease_time(IN const Json::Value& req, OUT Json::Value& response);
		bool dhcp_stub_hal_get_ecm_remain_rebind_time(IN const Json::Value& req, OUT Json::Value& response);
		bool dhcp_stub_hal_get_ecm_remain_renew_time(IN const Json::Value& req, OUT Json::Value& response);
		bool dhcp_stub_hal_get_emta_remain_lease_time(IN const Json::Value& req, OUT Json::Value& response);
		bool dhcp_stub_hal_get_emta_remain_rebind_time(IN const Json::Value& req, OUT Json::Value& response);
		bool dhcp_stub_hal_get_emta_remain_renew_time(IN const Json::Value& req, OUT Json::Value& response);
		bool dhcp_stub_hal_get_ert_config_attempts(IN const Json::Value& req, OUT Json::Value& response);
		bool dhcp_stub_hal_get_ert_dhcp_svr(IN const Json::Value& req, OUT Json::Value& response);
		bool dhcp_stub_hal_get_ert_dns_svrs(IN const Json::Value& req, OUT Json::Value& response);
		bool dhcp_stub_hal_get_ert_fsm_state(IN const Json::Value& req, OUT Json::Value& response);
		bool dhcp_stub_hal_get_ert_gw(IN const Json::Value& req, OUT Json::Value& response);
		bool dhcp_stub_hal_get_ert_ifname(IN const Json::Value& req, OUT Json::Value& response);
		bool dhcp_stub_hal_get_ert_ip_addr(IN const Json::Value& req, OUT Json::Value& response);
		bool dhcp_stub_hal_get_ert_lease_time(IN const Json::Value& req, OUT Json::Value& response);
		bool dhcp_stub_hal_get_ert_mask(IN const Json::Value& req, OUT Json::Value& response);
		bool dhcp_stub_hal_get_ert_remain_lease_time(IN const Json::Value& req, OUT Json::Value& response);
		bool dhcp_stub_hal_get_ert_remain_rebind_time(IN const Json::Value& req, OUT Json::Value& response);
		bool dhcp_stub_hal_get_ert_remain_renew_time(IN const Json::Value& req, OUT Json::Value& response);
		bool erouter_ip_stub_GetIpAddress(IN const Json::Value& req, OUT Json::Value& response);
};
#endif
