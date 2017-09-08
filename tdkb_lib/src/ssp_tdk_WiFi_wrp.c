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
 * Function Name        : ssp_WIFIHALGetOrSetParamBoolValue
 * Description          : This function invokes WiFi hal's get/set apis, when the value to be 
                          get /set is Bool
 *
 * @param [in]          : radioIndex - WiFi radio index value
 * @param [in]          : enable     - the value to be get/set
 * @param [in]          : method     - name of the wifi hal api to be invoked
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/
int ssp_WIFIHALGetOrSetParamBoolValue(int radioIndex, unsigned char *enable, char* method)
{
    printf("\n ssp_WIFIHALGetOrSetParamBoolValue----> Entry\n");
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
    else if(!strcmp(method, "getRadioStatus"))
        return_status = wifi_getRadioStatus(radioIndex, *enable);
    else if(!strcmp(method, "getApEnable"))
        return_status = wifi_getApEnable(radioIndex,enable);
    else if(!strcmp(method, "getApIsolationEnable"))
        return_status = wifi_getApIsolationEnable(radioIndex,enable);
    else if(!strcmp(method, "setApIsolationEnable"))
        return_status = wifi_setApIsolationEnable(radioIndex, *enable);
    else if(!strcmp(method, "getRadioIEEE80211hSupported"))
        return_status = wifi_getRadioIEEE80211hSupported(radioIndex,enable);
    else if(!strcmp(method, "getRadioIEEE80211hEnabled"))
        return_status = wifi_getRadioIEEE80211hEnabled(radioIndex,enable);
    else if(!strcmp(method, "setRadioIEEE80211hEnabled"))
        return_status = wifi_setRadioIEEE80211hEnabled(radioIndex, *enable);
    else if(!strcmp(method, "getBandSteeringCapability"))
        return_status = wifi_getBandSteeringCapability(enable);
    else if(!strcmp(method, "getBandSteeringEnable"))
        return_status = wifi_getBandSteeringEnable(enable);
    else if(!strcmp(method, "setBandSteeringEnable"))
        return_status = wifi_setBandSteeringEnable(*enable);
    else if(!strcmp(method, "getRadioReverseDirectionGrantSupported"))
        return_status = wifi_getRadioReverseDirectionGrantSupported(radioIndex,enable);
    else if(!strcmp(method, "getRadioReverseDirectionGrantEnable"))
        return_status = wifi_getRadioReverseDirectionGrantEnable(radioIndex,enable);
    else if(!strcmp(method, "setRadioReverseDirectionGrantEnable"))
        return_status = wifi_setRadioReverseDirectionGrantEnable(radioIndex, *enable);
    else if(!strcmp(method, "getRadioDeclineBARequestEnable"))
        return_status = wifi_getRadioDeclineBARequestEnable(radioIndex, enable);
    else if(!strcmp(method, "setRadioDeclineBARequestEnable"))
        return_status = wifi_setRadioDeclineBARequestEnable(radioIndex,*enable);
    else if(!strcmp(method, "getRadioAutoBlockAckEnable"))
        return_status = wifi_getRadioAutoBlockAckEnable(radioIndex,enable);
    else if(!strcmp(method, "setRadioAutoBlockAckEnable"))
        return_status = wifi_setRadioAutoBlockAckEnable(radioIndex, *enable);
    else if(!strcmp(method, "getRadio11nGreenfieldSupported"))
        return_status = wifi_getRadio11nGreenfieldSupported(radioIndex,enable);
    else if(!strcmp(method, "getRadio11nGreenfieldEnable"))
        return_status = wifi_getRadio11nGreenfieldEnable(radioIndex,enable);
    else if(!strcmp(method, "setRadio11nGreenfieldEnable"))
        return_status = wifi_setRadio11nGreenfieldEnable(radioIndex, *enable);
    else if(!strcmp(method, "getRadioIGMPSnoopingEnable"))
        return_status = wifi_getRadioIGMPSnoopingEnable(radioIndex,enable);
    else if(!strcmp(method, "setRadioIGMPSnoopingEnable"))
        return_status = wifi_setRadioIGMPSnoopingEnable(radioIndex,*enable);
    else if(!strcmp(method, "getApRtsThresholdSupported"))
        return_status = wifi_getApRtsThresholdSupported(radioIndex,enable);
    else if(!strcmp(method, "getApSsidAdvertisementEnable"))
        return_status = wifi_getApSsidAdvertisementEnable(radioIndex,enable);
    else if(!strcmp(method, "setApSsidAdvertisementEnable"))
        return_status = wifi_setApSsidAdvertisementEnable(radioIndex, *enable);
    else if(!strcmp(method, "getApWMMCapability"))
        return_status = wifi_getApWMMCapability(radioIndex,enable);
    else if(!strcmp(method, "getApUAPSDCapability"))
        return_status = wifi_getApUAPSDCapability(radioIndex,enable);
    else if(!strcmp(method, "getApWmmEnable"))
        return_status = wifi_getApWmmEnable(radioIndex,enable);
    else if(!strcmp(method, "setApWmmEnable"))
        return_status = wifi_setApWmmEnable(radioIndex, *enable);
    else if(!strcmp(method, "getApWmmUapsdEnable"))
        return_status = wifi_getApWmmUapsdEnable(radioIndex,enable);
    else if(!strcmp(method, "setApWmmUapsdEnable"))
        return_status = wifi_setApWmmUapsdEnable(radioIndex, *enable);
    else if(!strcmp(method, "getApWpsEnable"))
        return_status = wifi_getApWpsEnable(radioIndex,enable);
    else if(!strcmp(method, "setApWpsEnable"))
        return_status = wifi_setApWpsEnable(radioIndex,enable);
    else
    {
        return_status = SSP_FAILURE;
        printf("\n ssp_WIFIHALGetOrSetParamBoolValue: Invalid methodName\n");
    }

    printf("ssp_WIFIHALGetOrSetParamBoolValue: Enable status is %d, ret:status %d\n", *enable, return_status);
    printf("\n ssp_WIFIHALGetOrSetParamBoolValue----> Exit\n");
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

int ssp_WIFIHALGetOrSetParamULongValue(int radioIndex, unsigned long *uLongVar, char* method)
{
    printf("\n ssp_WIFIHALGetOrSetParamULongValue-----> Entry\n");
    int return_status = 0;

    if(!strcmp(method, "getRadioChannel"))
        return_status = wifi_getRadioChannel(radioIndex, uLongVar);
    else if(!strcmp(method, "setRadioChannel"))
        return_status = wifi_setRadioChannel(radioIndex, *uLongVar);
    else if(!strcmp(method, "getAutoChannelRefreshPeriod"))
        return_status = wifi_getRadioAutoChannelRefreshPeriod(radioIndex, uLongVar);
    else if(!strcmp(method, "getRadioNumberOfEntries"))
        return_status = wifi_getRadioNumberOfEntries(uLongVar);

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
int ssp_WIFIHALGetOrSetParamStringValue(int radioIndex, char* output, char* method)
{
    printf("\n ssp_WIFIHALGetOrSetParamStringValue----> Entry\n");
    int return_status = 0;
    unsigned char gOnly,nOnly,acOnly;

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
    else if(!strcmp(method, "getRadioSupportedFrequencyBands"))
        return_status = wifi_getRadioSupportedFrequencyBands(radioIndex, output);
    else if(!strcmp(method, "getRadioOperatingFrequencyBand"))
        return_status = wifi_getRadioOperatingFrequencyBand(radioIndex, output);
    else if(!strcmp(method, "getRadioSupportedStandards"))
        return_status = wifi_getRadioSupportedStandards(radioIndex, output);
    else if(!strcmp(method, "getRadioIfName"))
        return_status = wifi_getRadioIfName(radioIndex, output);
    else if(!strcmp(method, "getRadioStandard"))
        return_status = wifi_getRadioStandard(radioIndex, output, &gOnly, &nOnly, &acOnly);
    else if(!strcmp(method, "getSSIDStatus"))
        return_status = wifi_getSSIDStatus(radioIndex, output);

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
int ssp_WIFIHALGetOrSetParamIntValue(int radioIndex, int* output, char* method)
{
    printf("\n ssp_WIFIHALGetOrSetParamIntValue----> Entry\n");
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
