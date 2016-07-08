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

#ifndef __SNMP_STUB_H__
#define __SNMP_STUB_H__

#include <json/json.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <errno.h>

#include "rdkteststubintf.h"
#include "rdktestagentintf.h"

#define IN
#define OUT

#define TEST_SUCCESS true
#define TEST_FAILURE false


using namespace std;

class RDKTestAgent;
class SNMPProtocolAgent : public RDKTestStubInterface
{
        public:
		/*Constructor*/
		SNMPProtocolAgent();

		/*Inherited functions*/
		bool initialize(IN const char* szVersion, IN RDKTestAgent *ptrAgentObj);
		bool cleanup(const char*, RDKTestAgent*);
		std::string testmodulepre_requisites();
		bool testmodulepost_requisites();

		/*Execute snmp command */
		bool ExecuteSNMPCommand(IN const Json::Value& req, OUT Json::Value& response);
		/*Verify SNMP Logs*/
		bool LogValidation(IN const Json::Value& req, OUT Json::Value& response);
};

extern "C" SNMPProtocolAgent* CreateObject();
#endif

