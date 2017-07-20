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

#include <stdio.h>
#include "ssp_tdk_WiFi_wrp.h"
#include "wifi_hal.h"

/*******************************************************************************************
 *
 * Function Name        : ssp_WiFiHalCallMethodForBool
 * Description          : This function invokes WiFi hal's get/set apis, when the value to be 
                          get /set is Bool
 *
 * @param [in]          : radioIndex - WiFi radio index value
 * @param [in]          : enable     - the value to be get/set
 * @param [in]          : method     - name of the wifi hal api to be invoked
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/
int ssp_WiFiHalCallMethodForBool(int radioIndex, unsigned char *enable, char* method)
{
    printf("\n ssp_WiFiHalCallMethod----> Entry\n");
    int return_status = 0;

    if(!strcmp(method, "getRadioEnable"))
        return_status = wifi_getRadioEnable(radioIndex, enable);
    else if(!strcmp(method, "setRadioEnable"))
        return_status = wifi_setRadioEnable(radioIndex, *enable);
    else if(!strcmp(method, "getSSIDEnable"))
        return_status = wifi_getSSIDEnable(radioIndex, enable);
    else if(!strcmp(method, "setSSIDEnable"))
        return_status = wifi_setSSIDEnable(radioIndex, *enable);
    else if(!strcmp(method, "getRadioDCSSupported"))
        return_status = wifi_getRadioDCSSupported(radioIndex, enable);
    else if(!strcmp(method, "getRadioDCSEnable"))
        return_status = wifi_getRadioDCSEnable(radioIndex, enable);
    else if(!strcmp(method, "setRadioDCSEnable"))
        return_status = wifi_setRadioDCSEnable(radioIndex, *enable);
    else if(!strcmp(method, "getRadioDFSSupported"))
        return_status = wifi_getRadioDfsSupport(radioIndex, enable);
    else if(!strcmp(method, "getRadioDFSEnable"))
        return_status = wifi_getRadioDfsEnable(radioIndex, enable);
    else if(!strcmp(method, "setRadioDFSEnable"))
        return_status = wifi_setRadioDfsEnable(radioIndex, *enable);
    else if(!strcmp(method, "getAutoChannelRefreshPeriodSupported"))
        return_status = wifi_getRadioAutoChannelRefreshPeriodSupported(radioIndex, enable);
    else if(!strcmp(method, "setAutoChannelEnable"))
        return_status = wifi_setRadioAutoChannelEnable(radioIndex, *enable);
    else
    {
        return_status = SSP_FAILURE;
        printf("\n ssp_WiFiHalCallMethod: Invalid methodName\n");
    }

    printf("ssp_WiFiHalCallMethod:: Enable status is %d, ret:status %d\n", *enable, return_status);
    printf("\n ssp_WiFiHalCallMethod----> Exit\n");
    return return_status;
}


/*******************************************************************************************
 *
 * Function Name        : ssp_WiFiHalCallMethodForULong
 * Description          : This function invokes WiFi hal's get/set apis, when the value to be 
                          get /set is Unsigned long
 *
 * @param [in]          : radioIndex - WiFi radio index value
 * @param [in]          : enable     - the value to be get/set
 * @param [in]          : method     - name of the wifi hal api to be invoked
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/

int ssp_WiFiCallMethodForULong(int radioIndex, unsigned long *uLongVar, char* method)
{
    printf("\n ssp_WiFiCallMethodForULong-----> Entry\n");
    int return_status = 0;

    if(!strcmp(method, "getRadioChannel"))
        return_status = wifi_getRadioChannel(radioIndex, uLongVar);
    else if(!strcmp(method, "setRadioChannel"))
        return_status = wifi_setRadioChannel(radioIndex, *uLongVar);
    else if(!strcmp(method, "getAutoChannelRefreshPeriod"))
        return_status = wifi_getRadioAutoChannelRefreshPeriod(radioIndex, uLongVar);

    else
    {
        return_status = SSP_FAILURE;
        printf("\n ssp_WiFiHalCallMethodForULong: Invalid methodName\n");
    }

    printf("ssp_WiFiHalCallMethodForULong:: return value is %lu\n", *uLongVar);
    printf("\n ssp_WiFiHalCallMethodForULong---> Exit\n");
    return return_status;
}


/*******************************************************************************************
 *
 * Function Name        : ssp_WiFiHalCallMethodForString
 * Description          : This function invokes WiFi hal's get/set apis, when the value to be 
                          get /set is a string value
 *
 * @param [in]          : radioIndex - WiFi radio index value
 * @param [in]          : enable     - the value to be get/set
 * @param [in]          : method     - name of the wifi hal api to be invoked
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/
int ssp_WiFiCallMethodForString(int radioIndex, char* output, char* method)
{
    printf("\n ssp_WiFiCallMethodForString----> Entry\n");
    int return_status = 0;

    if(!strcmp(method, "getRadioChannelsInUse"))
        return_status = wifi_getRadioChannelsInUse(radioIndex, output);
    else if(!strcmp(method, "getRadioPossibleChannels"))
        return_status = wifi_getRadioPossibleChannels(radioIndex, output);
    else if(!strcmp(method, "getChannelBandwidth"))
        return_status = wifi_getRadioOperatingChannelBandwidth(radioIndex, output);
    else if(!strcmp(method, "getRadioGuardInterval"))
        return_status = wifi_getRadioGuardInterval(radioIndex, output);
    else if(!strcmp(method, "getOperationalDataTransmitRates"))
        return_status = wifi_getRadioOperationalDataTransmitRates(radioIndex, output);
    else if(!strcmp(method, "getSupportedDataTransmitRates"))
        return_status = wifi_getRadioSupportedDataTransmitRates(radioIndex, output);

    else
    {
        return_status = SSP_FAILURE;
        printf("\n ssp_WiFiHalCallMethodForString: Invalid methodName\n");
    }

    printf("ssp_WiFiHalCallMethodForString: return value is %s\n", output);
    printf("\n ssp_WiFiHalCallMethodForString--> Exit\n");
    return return_status;
}


/*******************************************************************************************
 *
 * Function Name        : ssp_WiFiHalCallMethodForInt
 * Description          : This function invokes WiFi hal's get apis, when the value to be 
                          get  is an integer value
 *
 * @param [in]          : radioIndex - WiFi radio index value
 * @param [in]          : enable     - the value to be get/set
 * @param [in]          : method     - name of the wifi hal api to be invoked
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/
int ssp_WiFiCallMethodForInt(int radioIndex, int* output, char* method)
{
    printf("\n ssp_WiFiCallMethodForInt----> Entry\n");
    int return_status = 0;

    if(!strcmp(method, "getRadioMCS"))
        return_status = wifi_getRadioMCS(radioIndex, output);

    else
    {
        return_status = SSP_FAILURE;
        printf("\n ssp_WiFiHalCallMethodForInt: Invalid methodName\n");
    }

    printf("ssp_WiFiHalCallMethodForInt: return value is %d\n", *output);
    printf("\n ssp_WiFiHalCallMethodForInt--> Exit\n");
    return return_status;
}
