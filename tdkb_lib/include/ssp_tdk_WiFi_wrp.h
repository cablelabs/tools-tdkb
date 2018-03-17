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

#define SSP_SUCCESS       0
#define SSP_FAILURE       1

int ssp_wifi_init();
int ssp_WIFIHALApplySettings(int radioIndex, char* methodName);
int ssp_WIFIHALGetOrSetParamULongValue(int radioIndex, unsigned long *uLongVar, char* methodName);
int ssp_WIFIHALGetOrSetParamBoolValue(int radioIndex, unsigned char *enable, char* method);
int ssp_WIFIHALGetOrSetParamStringValue(int radioIndex, char* output, char* method);
int ssp_WIFIHALGetOrSetRadioStandard(int radioIndex, char* output, char* method, unsigned char *gOnly, unsigned char *nOnly, unsigned char *acOnly);
int ssp_WIFIHALGetOrSetParamIntValue(int radioIndex, int* output, char* method);
int ssp_WIFIHALGetIndexFromName(char* ssidName, int* output);
int ssp_WIFIHALClearRadioResetCount();
int ssp_WIFIHALReset();
int ssp_WIFIHALGetOrSetSecurityRadiusServer(int radioIndex, char* IPAddress, unsigned int* port, char* RadiusSecret, char* method);
int ssp_WIFIHALGetOrSetApBridgeInfo(int radioIndex, char* bridgeName, char* IP, char* subnet, char* method);
