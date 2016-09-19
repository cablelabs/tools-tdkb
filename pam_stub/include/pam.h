/*
 * ============================================================================
 * COMCAST C O N F I D E N T I A L AND PROPRIETARY
 * ============================================================================
 * This file (and its contents) are the intellectual property of Comcast.  It may
 * not be used, copied, distributed or otherwise  disclosed in whole or in part
 * without the express written permission of Comcast.
 * ============================================================================
 * Copyright (c) 2016 Comcast. All rights reserved.
 * ============================================================================
 */

#ifndef __PAM_H__
#define __PAM_H__
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

class pam : public RDKTestStubInterface
{
	public:
        /*Ctor*/
	pam ();

	/*inherited functions*/
	bool initialize(IN const char* szVersion, IN RDKTestAgent *ptrAgentObj);

	bool cleanup(IN const char* szVersion,IN RDKTestAgent *ptrAgentObj);
	std::string testmodulepre_requisites();
        bool testmodulepost_requisites();
        /*pam Stub Wrapper functions*/
	bool pam_bridge_GetParamBoolValue(IN const Json::Value& req, OUT Json::Value& response);
};
#endif //__PAM_STUB_H__
