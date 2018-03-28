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
#ifndef __WIFIHAL_STUB_H__
#define __WIFIHAL_STUB_H__
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
#include <jsonrpccpp/server/connectors/tcpsocketserver.h>
#define IN
#define OUT
#define TEST_SUCCESS true
#define TEST_FAILURE false

/* To provide external linkage to C Functions defined in TDKB Component folder */
extern "C"
{
    int ssp_wifi_init();
    int ssp_WIFIHALApplySettings(int radioIndex, char* methodName);
    int ssp_WIFIHALGetOrSetParamBoolValue(int radioIndex, unsigned char *output, char* method);
    int ssp_WIFIHALGetOrSetParamULongValue(int radioIndex, unsigned long *uLongVar, char* methodName);
    int ssp_WIFIHALGetOrSetParamStringValue(int radioIndex, char *output, char* methodName);
    int ssp_WIFIHALGetOrSetRadioStandard(int radioIndex, char* output, char* method, unsigned char *gOnly, unsigned char *nOnly, unsigned char *acOnly);
    int ssp_WIFIHALGetOrSetParamIntValue(int radioIndex, int *output, char* methodName);
    int ssp_WIFIHALGetOrSetParamUIntValue(int radioIndex, unsigned int *output, char* methodName);
    int ssp_WIFIHALGetIndexFromName(char* ssidName, int *output);
    int ssp_WIFIHALClearRadioResetCount();
    int ssp_WIFIHALReset();
    int ssp_WIFIHALDown();
    int ssp_WIFIHALGetOrSetSecurityRadiusServer(int radioIndex, char* IPAddress, unsigned int* port, char* RadiusSecret, char* method);
    int ssp_WIFIHALGetOrSetApBridgeInfo(int radioIndex, char* bridgeName, char* IP, char* subnet, char* method);
};

class RDKTestAgent;
class WIFIHAL : public RDKTestStubInterface, public AbstractServer<WIFIHAL>
{
    public:
	 WIFIHAL(TcpSocketServer &ptrRpcServer) : AbstractServer <WIFIHAL>(ptrRpcServer)
                {
                  this->bindAndAddMethod(Procedure("WIFIHAL_GetOrSetParamBoolValue", PARAMS_BY_NAME, JSON_STRING,"methodName", JSON_STRING,"radioIndex", JSON_INTEGER,"param", JSON_INTEGER, "paramType",  JSON_STRING,NULL), &WIFIHAL::WIFIHAL_GetOrSetParamBoolValue);
		  this->bindAndAddMethod(Procedure("WIFIHAL_GetOrSetParamULongValue", PARAMS_BY_NAME, JSON_STRING,"methodName", JSON_STRING,"radioIndex", JSON_INTEGER,"param", JSON_INTEGER, "paramType",  JSON_STRING,NULL), &WIFIHAL::WIFIHAL_GetOrSetParamULongValue);
		  this->bindAndAddMethod(Procedure("WIFIHAL_GetOrSetParamStringValue", PARAMS_BY_NAME, JSON_STRING,"methodName", JSON_STRING,"radioIndex", JSON_INTEGER, "param", JSON_STRING, "paramType",  JSON_STRING,NULL), &WIFIHAL::WIFIHAL_GetOrSetParamStringValue);
		  this->bindAndAddMethod(Procedure("WIFIHAL_GetOrSetRadioStandard", PARAMS_BY_NAME, JSON_STRING,"methodName", JSON_STRING,"radioIndex", JSON_INTEGER, "param", JSON_STRING, "paramType",  JSON_STRING, "gOnly",JSON_INTEGER, "nOnly",JSON_INTEGER, "acOnly",JSON_INTEGER, NULL), &WIFIHAL::WIFIHAL_GetOrSetRadioStandard);
		  this->bindAndAddMethod(Procedure("WIFIHAL_GetOrSetParamIntValue", PARAMS_BY_NAME, JSON_STRING,"methodName", JSON_STRING,"radioIndex", JSON_INTEGER, "param", JSON_INTEGER, "paramType",  JSON_STRING,NULL), &WIFIHAL::WIFIHAL_GetOrSetParamIntValue);
	 	  this->bindAndAddMethod(Procedure("WIFIHAL_GetOrSetParamUIntValue", PARAMS_BY_NAME, JSON_STRING,"methodName", JSON_STRING,"radioIndex", JSON_INTEGER, "param", JSON_INTEGER, "paramType",  JSON_STRING,NULL), &WIFIHAL::WIFIHAL_GetOrSetParamUIntValue);
		  this->bindAndAddMethod(Procedure("WIFIHAL_GetIndexFromName", PARAMS_BY_NAME, JSON_STRING, "param", JSON_STRING,NULL), &WIFIHAL::WIFIHAL_GetIndexFromName);
		  this->bindAndAddMethod(Procedure("WIFIHAL_ClearRadioResetCount", PARAMS_BY_NAME, JSON_STRING, NULL), &WIFIHAL::WIFIHAL_ClearRadioResetCount);
                  this->bindAndAddMethod(Procedure("WIFIHAL_Reset", PARAMS_BY_NAME, JSON_STRING, NULL), &WIFIHAL::WIFIHAL_Reset);
                  this->bindAndAddMethod(Procedure("WIFIHAL_GetOrSetSecurityRadiusServer", PARAMS_BY_NAME, JSON_STRING,"methodName", JSON_STRING,"radioIndex", JSON_INTEGER, "port", JSON_INTEGER, "IPAddress", JSON_STRING, "RadiusSecret", JSON_STRING, "paramType",  JSON_STRING,NULL), &WIFIHAL::WIFIHAL_GetOrSetSecurityRadiusServer);
                  this->bindAndAddMethod(Procedure("WIFIHAL_GetOrSetApBridgeInfo", PARAMS_BY_NAME, JSON_STRING,"methodName", JSON_STRING,"radioIndex", JSON_INTEGER, "bridgeName", JSON_STRING, "IP", JSON_STRING, "subnet", JSON_STRING, "paramType",  JSON_STRING,NULL), &WIFIHAL::WIFIHAL_GetOrSetApBridgeInfo);
                  this->bindAndAddMethod(Procedure("WIFIHAL_Down", PARAMS_BY_NAME, JSON_STRING, NULL), &WIFIHAL::WIFIHAL_Down);
                  this->bindAndAddMethod(Procedure("WIFIHAL_Init", PARAMS_BY_NAME, JSON_STRING, NULL), &WIFIHAL::WIFIHAL_Init);
                }
        /*inherited functions*/
        bool initialize(IN const char* szVersion);
        bool cleanup(IN const char* szVersion);
        std::string testmodulepre_requisites();
        bool testmodulepost_requisites();

        /*WIFIHAL Stub Wrapper functions*/
        void WIFIHAL_GetOrSetParamULongValue(IN const Json::Value& req, OUT Json::Value& response);
        void WIFIHAL_GetOrSetParamBoolValue(IN const Json::Value& req, OUT Json::Value& response);
        void WIFIHAL_GetOrSetParamStringValue(IN const Json::Value& req, OUT Json::Value& response);
	void WIFIHAL_GetOrSetRadioStandard(IN const Json::Value& req, OUT Json::Value& response);
        void WIFIHAL_GetOrSetParamIntValue(IN const Json::Value& req, OUT Json::Value& response);
        void WIFIHAL_GetOrSetParamUIntValue(IN const Json::Value& req, OUT Json::Value& response);
	void WIFIHAL_GetIndexFromName(IN const Json::Value& req, OUT Json::Value& response);
	void WIFIHAL_ClearRadioResetCount(IN const Json::Value& req, OUT Json::Value& response);
	void WIFIHAL_Reset(IN const Json::Value& req, OUT Json::Value& response);
	void WIFIHAL_GetOrSetSecurityRadiusServer(IN const Json::Value& req, OUT Json::Value& response);
	void WIFIHAL_GetOrSetApBridgeInfo(IN const Json::Value& req, OUT Json::Value& response);
	void WIFIHAL_Down(IN const Json::Value& req, OUT Json::Value& response);
	void WIFIHAL_Init(IN const Json::Value& req, OUT Json::Value& response);
};
#endif //__WIFIHAL_STUB_H__

