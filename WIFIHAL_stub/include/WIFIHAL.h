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

typedef struct _wifi_radius_setting_t
{
    int RadiusServerRetries;
    int RadiusServerRequestTimeout;
    int PMKLifetime;
    int PMKCaching;
    int PMKCacheInterval;
    int MaxAuthenticationAttempts;
    int BlacklistTableTimeout;
    int IdentityRequestRetryInterval;
    int QuietPeriodAfterFailedAuthentication;
}wifiRadiusSetting;

typedef struct _wifi_ssidTrafficStats2
{
    unsigned long ssid_BytesSent;
    unsigned long ssid_BytesReceived;
    unsigned long ssid_PacketsSent;
    unsigned long ssid_PacketsReceived;
    unsigned long ssid_RetransCount;
    unsigned long ssid_FailedRetransCount;
    unsigned long ssid_RetryCount;
    unsigned long ssid_MultipleRetryCount;
    unsigned long ssid_ACKFailureCount;
    unsigned long ssid_AggregatedPacketCount;
    unsigned long ssid_ErrorsSent;
    unsigned long ssid_ErrorsReceived;
    unsigned long ssid_UnicastPacketsSent;
    unsigned long ssid_DiscardedPacketsSent;
    unsigned long ssid_UnicastPacketsReceived;
    unsigned long ssid_DiscardedPacketsReceived;
    unsigned long ssid_MulticastPacketsSent;
    unsigned long ssid_MulticastPacketsReceived;
    unsigned long ssid_BroadcastPacketsSent;
    unsigned long ssid_BroadcastPacketsRecevied;
    unsigned long ssid_UnknownPacketsReceived;
}wifi_ssidTrafficStats2_t;

typedef struct _wifi_radioTrafficStats2_t
{
    unsigned long radio_BytesSent;
    unsigned long radio_BytesReceived;
    unsigned long radio_PacketsSent;
    unsigned long radio_ErrorsSent;
    unsigned long radio_PacketsReceived;
    unsigned long radio_ErrorsReceived;
    unsigned long radio_DiscardPacketsSent;
    unsigned long radio_DiscardPacketsReceived;
    unsigned long radio_PLCPErrorCount;
    unsigned long radio_FCSErrorCount;
    unsigned long radio_InvalidMACCount;
    unsigned long radio_PacketsOtherReceived;
    unsigned long radio_NoiseFloor;
    unsigned long radio_ChannelUtilization;
    unsigned long radio_ActivityFactor;
    unsigned long radio_CarrierSenseThreshold_Exceeded;
    unsigned long radio_RetransmissionMetirc;
    unsigned long radio_MaximumNoiseFloorOnChannel;
    unsigned long radio_MinimumNoiseFloorOnChannel;
    unsigned long radio_MedianNoiseFloorOnChannel;
    unsigned long radio_StatisticsStartTime;
}GetRadioTrafficStats2;

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
    int ssp_WIFIHALGetOrSetRadioDCSScanTime(int radioIndex, int* output_interval_seconds,int* output_dwell_milliseconds, char* methodName);
    int ssp_WIFIHALAddorDelApAclDevice(int apIndex, char* DeviceMacAddress, char* method);
    int ssp_WIFIHALIfConfigUporDown(int apIndex, char* method);
    int ssp_WIFIHALParamRadioIndex(int radioIndex, char* method);
    int ssp_WIFIHALStartorStopHostApd(char* method);
    int ssp_WIFIHALFactoryReset(char* method);
    int ssp_WIFIHALGetOrSetSecurityRadiusSettings(int radioIndex, wifiRadiusSetting *radiusSetting, char* method);
    int ssp_WIFIHALGetSSIDTrafficStats2(int radioIndex,  wifi_ssidTrafficStats2_t *ssidTrafficStats2);
    int ssp_WIFIHAL_GetRadioTrafficStats2(int radioIndex, GetRadioTrafficStats2 *TrafficStats2);
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
                  this->bindAndAddMethod(Procedure("WIFIHAL_GetOrSetRadioDCSScanTime", PARAMS_BY_NAME, JSON_STRING,"methodName", JSON_STRING,"radioIndex", JSON_INTEGER, "output_interval_seconds", JSON_INTEGER, "output_dwell_milliseconds", JSON_INTEGER, "paramType",  JSON_STRING,NULL), &WIFIHAL::WIFIHAL_GetOrSetRadioDCSScanTime);
                  this->bindAndAddMethod(Procedure("WIFIHAL_AddorDelApAclDevice", PARAMS_BY_NAME, JSON_STRING,"methodName", JSON_STRING,"apIndex", JSON_INTEGER, "DeviceMacAddress", JSON_STRING,NULL), &WIFIHAL::WIFIHAL_AddorDelApAclDevice);
                  this->bindAndAddMethod(Procedure("WIFIHAL_IfConfigUporDown", PARAMS_BY_NAME, JSON_STRING,"methodName", JSON_STRING,"apIndex", JSON_INTEGER,NULL), &WIFIHAL::WIFIHAL_IfConfigUporDown);
                  this->bindAndAddMethod(Procedure("WIFIHAL_ParamRadioIndex", PARAMS_BY_NAME, JSON_STRING,"methodName", JSON_STRING,"radioIndex", JSON_INTEGER,NULL), &WIFIHAL::WIFIHAL_ParamRadioIndex);
                  this->bindAndAddMethod(Procedure("WIFIHAL_StartorStopHostApd", PARAMS_BY_NAME, JSON_STRING,"methodName", JSON_STRING,NULL), &WIFIHAL::WIFIHAL_StartorStopHostApd);
                  this->bindAndAddMethod(Procedure("WIFIHAL_FactoryReset", PARAMS_BY_NAME, JSON_STRING,"methodName", JSON_STRING,NULL), &WIFIHAL::WIFIHAL_FactoryReset);
                  this->bindAndAddMethod(Procedure("WIFIHAL_GetOrSetSecurityRadiusSettings",PARAMS_BY_NAME, JSON_STRING, "methodName", JSON_STRING,"radioIndex", JSON_INTEGER, "RadiusServerRetries", JSON_INTEGER, "RadiusServerRequestTimeout", JSON_INTEGER, "PMKLifetime", JSON_INTEGER, "PMKCaching", JSON_INTEGER, "PMKCacheInterval", JSON_INTEGER, "MaxAuthenticationAttempts", JSON_INTEGER, "BlacklistTableTimeout", JSON_INTEGER, "IdentityRequestRetryInterval", JSON_INTEGER, "QuietPeriodAfterFailedAuthentication", JSON_INTEGER, NULL), &WIFIHAL::WIFIHAL_GetOrSetSecurityRadiusSettings);
		  this->bindAndAddMethod(Procedure("WIFIHAL_GetSSIDTrafficStats2",PARAMS_BY_NAME, JSON_STRING, "radioIndex",JSON_INTEGER,NULL), &WIFIHAL::WIFIHAL_GetSSIDTrafficStats2);
                  this->bindAndAddMethod(Procedure("WIFIHAL_GetRadioTrafficStats2",PARAMS_BY_NAME, JSON_STRING, "radioIndex",JSON_INTEGER,NULL), &WIFIHAL::WIFIHAL_GetRadioTrafficStats2);
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
        void WIFIHAL_GetOrSetRadioDCSScanTime(IN const Json::Value& req, OUT Json::Value& response);
        void WIFIHAL_AddorDelApAclDevice(IN const Json::Value& req, OUT Json::Value& response);
        void WIFIHAL_IfConfigUporDown(IN const Json::Value& req, OUT Json::Value& response);
        void WIFIHAL_ParamRadioIndex(IN const Json::Value& req, OUT Json::Value& response);
        void WIFIHAL_StartorStopHostApd(IN const Json::Value& req, OUT Json::Value& response);
        void WIFIHAL_FactoryReset(IN const Json::Value& req, OUT Json::Value& response);
        void WIFIHAL_GetOrSetSecurityRadiusSettings(IN const Json::Value& req, OUT Json::Value& response);
	void WIFIHAL_GetSSIDTrafficStats2(IN const Json::Value& req, OUT Json::Value& response);
        void WIFIHAL_GetRadioTrafficStats2(IN const Json::Value& req, OUT Json::Value& response);
	void WIFIHAL_Down(IN const Json::Value& req, OUT Json::Value& response);
	void WIFIHAL_Init(IN const Json::Value& req, OUT Json::Value& response);
};
#endif //__WIFIHAL_STUB_H__

