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
 * Function Name        : ssp_wifi_init
 * Description          : This function invokes WiFi hal's init api *
 * @param [in]  N/A
 * @param [out] N/A
 ********************************************************************************************/
int ssp_wifi_init()
{
    printf("\n ssp_wifi_init-----> Entry\n");

    int return_status=0;

#if defined(_COSA_BCM_MIPS_)
    printf("Invoking wifi_init HAL API\n");

    return_status = wifi_init();

    printf("return value from wifi_init is %d\n",return_status);

    if(return_status == SSP_SUCCESS)
    {
         printf("\nssp_wifi_init::WIFI HAL Initialization success\n");
    }
    else
    {
        printf("\nssp_wifi_init::Failed to initialize the WIFI HAL\n");
    }
#endif

    printf("\n ssp_wifi_init----> Exit\n");

    return return_status;
}

/*******************************************************************************************
 *
 * Function Name        : ssp_WIFIHALApplySettings
 * Description          : This function invokes WiFi hal api wifi_applyRadioSettings
 * @param [in] req-     : radioIndex - radio index value of wifi
			  methodName - name of the wifi hal api to be invoked
 * @param [out] response - filled with SUCCESS or FAILURE based on the output staus of operation
 *
 ********************************************************************************************/
int ssp_WIFIHALApplySettings(int radioIndex, char* methodName)
{
    printf("\n ssp_WIFIHALApplySettings-----> Entry\n");
    printf("Radio/SSID index:%d\n",radioIndex);
    printf("MethodName: %s\n", methodName);
    int return_status = 0;

    if(strstr(methodName, "setRadio")||strstr(methodName, "setAp"))
    {
        return_status = wifi_applyRadioSettings(radioIndex);
        printf("return value from wifi_applyRadioSettings is %d\n",return_status);
    }
    else if(strstr(methodName, "setSSID"))
    {
        return_status = wifi_applySSIDSettings(radioIndex);
        printf("return value from wifi_applySSIDSettings is %d\n",return_status);
    }
    if(return_status != SSP_SUCCESS)
    {
        printf("\nssp_WIFIHALApplySettings::Failed\n");
        return SSP_FAILURE;
    }
    else
    {
        printf("\nssp_WIFIHALApplySettings::Success\n");
        return return_status;
    }

    printf("\n ssp_WIFIHALApplySettings----> Exit\n");
}


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
    printf("Radio index:%d\n",radioIndex);
    printf("GetorSetParam: %d\n" , *enable);
    printf("MethodName: %s\n", method);
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
    else if(!strcmp(method, "getAutoChannelEnable"))
        return_status = wifi_getRadioAutoChannelEnable(radioIndex, enable);
    else if(!strcmp(method, "getAutoChannelSupported"))
        return_status = wifi_getRadioAutoChannelSupported(radioIndex, enable);
    else if(!strcmp(method, "getRadioStatus"))
        return_status = wifi_getRadioStatus(radioIndex, *enable);
    else if(!strcmp(method, "getApEnable"))
        return_status = wifi_getApEnable(radioIndex,enable);
    else if(!strcmp(method, "setApEnable"))
        return_status = wifi_setApEnable(radioIndex, *enable);
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
        return_status = wifi_setApWpsEnable(radioIndex,*enable);
    else if(!strcmp(method, "getRadioAMSDUEnable"))
        return_status = wifi_getRadioAMSDUEnable(radioIndex, enable);
    else if(!strcmp(method, "setRadioAMSDUEnable"))
        return_status = wifi_setRadioAMSDUEnable(radioIndex, *enable);
    else if(!strcmp(method, "getApRtsThresholdSupported"))
        return_status = wifi_getApRtsThresholdSupported(radioIndex, enable);
    else if(!strcmp(method, "pushSsidAdvertisementEnable"))
        return_status = wifi_pushSsidAdvertisementEnable(radioIndex, *enable);
    else if(!strcmp(method, "setRadioCtsProtectionEnable"))
        return_status = wifi_setRadioCtsProtectionEnable(radioIndex, *enable);
    else if(!strcmp(method, "setRadioObssCoexistenceEnable"))
        return_status = wifi_setRadioObssCoexistenceEnable(radioIndex, *enable);
    else if(!strcmp(method, "setRadioSTBCEnable"))
        return_status = wifi_setRadioSTBCEnable(radioIndex, *enable);
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
    printf("Radio index:%d\n",radioIndex);
    printf("GetorSetParam: %lu\n" , *uLongVar);
    printf("MethodName: %s\n", method);
    int return_status = 0;

    if(!strcmp(method, "getRadioChannel"))
        return_status = wifi_getRadioChannel(radioIndex, uLongVar);
    else if(!strcmp(method, "setRadioChannel"))
        return_status = wifi_setRadioChannel(radioIndex, *uLongVar);
    else if(!strcmp(method, "getAutoChannelRefreshPeriod"))
        return_status = wifi_getRadioAutoChannelRefreshPeriod(radioIndex, uLongVar);
    else if(!strcmp(method, "setAutoChannelRefreshPeriod"))
        return_status = wifi_setRadioAutoChannelRefreshPeriod(radioIndex, *uLongVar);
    else if(!strcmp(method, "getRadioNumberOfEntries"))
        return_status = wifi_getRadioNumberOfEntries(*uLongVar);
    else if(!strcmp(method, "getSSIDNumberOfEntries"))
        return_status = wifi_getSSIDNumberOfEntries(uLongVar);
    else if(!strcmp(method, "getRadioTransmitPower"))
        return_status = wifi_getRadioTransmitPower(radioIndex, uLongVar);
    else if(!strcmp(method, "setRadioTransmitPower"))
        return_status = wifi_setRadioTransmitPower(radioIndex, *uLongVar);
    else if(!strcmp(method, "getApNumDevicesAssociated"))
        return_status = wifi_getApNumDevicesAssociated(radioIndex, uLongVar);
    else if(!strcmp(method, "getApWpsDevicePIN"))
        return_status = wifi_getApWpsDevicePIN(radioIndex, uLongVar);
    else if(!strcmp(method, "setApWpsDevicePIN"))
        return_status = wifi_setApWpsDevicePIN(radioIndex, *uLongVar);
    else if(!strcmp(method, "getRadioUpTime"))
        return_status = wifi_getRadioUpTime(radioIndex, uLongVar);
    else if(!strcmp(method, "getApAssociatedDevicesHighWatermarkDate"))
        return_status = wifi_getApAssociatedDevicesHighWatermarkDate(radioIndex, uLongVar);
    else if(!strcmp(method, "getRadioResetCount"))
        return_status = wifi_getRadioResetCount(radioIndex, uLongVar);
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
    printf("Radio index:%d\n",radioIndex);
    printf("GetorSetParam: %s\n" , output);
    printf("MethodName: %s\n", method);
    int return_status = 0;

    if(!strcmp(method, "getRadioChannelsInUse"))
        return_status = wifi_getRadioChannelsInUse(radioIndex, output);
    else if(!strcmp(method, "getRadioPossibleChannels"))
        return_status = wifi_getRadioPossibleChannels(radioIndex, output);
    else if(!strcmp(method, "getChannelBandwidth"))
        return_status = wifi_getRadioOperatingChannelBandwidth(radioIndex, output);
    else if(!strcmp(method, "setChannelBandwidth"))
        return_status = wifi_setRadioOperatingChannelBandwidth(radioIndex, output);
    else if(!strcmp(method, "getRadioGuardInterval"))
        return_status = wifi_getRadioGuardInterval(radioIndex, output);
    else if(!strcmp(method, "setRadioGuardInterval"))
        return_status = wifi_setRadioGuardInterval(radioIndex, output);
    else if(!strcmp(method, "getOperationalDataTransmitRates"))
        return_status = wifi_getRadioOperationalDataTransmitRates(radioIndex, output);
    else if(!strcmp(method, "setOperationalDataTransmitRates"))
        return_status = wifi_setRadioOperationalDataTransmitRates(radioIndex, output);
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
    else if(!strcmp(method, "getSSIDStatus"))
        return_status = wifi_getSSIDStatus(radioIndex, output);
    else if(!strcmp(method, "getApBasicAuthenticationMode"))
	return_status = wifi_getApBasicAuthenticationMode(radioIndex,output);
    else if(!strcmp(method, "setApBasicAuthenticationMode"))
	return_status = wifi_setApBasicAuthenticationMode(radioIndex,output);
    else if(!strcmp(method, "getApBeaconType"))
	return_status = wifi_getApBeaconType(radioIndex,output);
    else if(!strcmp(method, "setApBeaconType"))
        return_status = wifi_setApBeaconType(radioIndex,output);
    else if(!strcmp(method, "getApSecurityModeEnabled"))
	return_status = wifi_getApSecurityModeEnabled(radioIndex,output);
    else if(!strcmp(method, "setApSecurityModeEnabled"))
	return_status = wifi_setApSecurityModeEnabled(radioIndex,output);
    else if(!strcmp(method, "getApWpaEncryptionMode"))
	return_status = wifi_getApWpaEncryptionMode(radioIndex,output);
    else if(!strcmp(method, "setApWpaEncryptionMode"))
        return_status = wifi_setApWpaEncryptionMode(radioIndex,output);
    else if(!strcmp(method, "getRadioExtChannel"))
	return_status = wifi_getRadioExtChannel(radioIndex,output);
    else if(!strcmp(method, "setRadioExtChannel"))
        return_status = wifi_setRadioExtChannel(radioIndex,output);
    else if(!strcmp(method, "getRadioBasicDataTransmitRates"))
	return_status = wifi_getRadioBasicDataTransmitRates(radioIndex,output);
    else if(!strcmp(method, "setRadioBasicDataTransmitRates"))
        return_status = wifi_setRadioBasicDataTransmitRates(radioIndex,output);
    else if(!strcmp(method, "getSSIDName"))
	return_status = wifi_getSSIDName(radioIndex,output);
    else if(!strcmp(method, "setSSIDName"))
        return_status = wifi_setSSIDName(radioIndex,output);
    else if(!strcmp(method, "getRadioDCSChannelPool"))
        return_status = wifi_getRadioDCSChannelPool(radioIndex,output);
    else if(!strcmp(method, "setRadioDCSChannelPool"))
        return_status = wifi_setRadioDCSChannelPool(radioIndex,output);
    else if(!strcmp(method, "getApStatus"))
	return_status = wifi_getApStatus(radioIndex,output);
    else if(!strcmp(method, "getApSecurityModesSupported"))
	return_status = wifi_getApSecurityModesSupported(radioIndex,output);
    else if(!strcmp(method, "getApSecurityPreSharedKey"))
	return_status = wifi_getApSecurityPreSharedKey(radioIndex,output);
    else if(!strcmp(method, "setApSecurityPreSharedKey"))
	return_status = wifi_setApSecurityPreSharedKey(radioIndex,output);
    else if(!strcmp(method, "getApSecurityKeyPassphrase"))
	return_status = wifi_getApSecurityKeyPassphrase(radioIndex,output);
    else if(!strcmp(method, "setApSecurityKeyPassphrase"))
	return_status = wifi_setApSecurityKeyPassphrase(radioIndex,output);
    else if(!strcmp(method, "getApWpsConfigMethodsSupported"))
	return_status = wifi_getApWpsConfigMethodsSupported(radioIndex,output);
    else if(!strcmp(method, "getApWpsConfigMethodsEnabled"))
	return_status = wifi_getApWpsConfigMethodsEnabled(radioIndex,output);
    else if(!strcmp(method, "setApWpsConfigMethodsEnabled"))
	return_status = wifi_setApWpsConfigMethodsEnabled(radioIndex,output);
    else if(!strcmp(method, "getRadioTransmitPowerSupported"))
        return_status = wifi_getRadioTransmitPowerSupported(radioIndex,output);
    else if(!strcmp(method, "getRadioMaxBitRate"))
        return_status = wifi_getRadioMaxBitRate(radioIndex, output);
    else if(!strcmp(method, "getRadioCountryCode"))
        return_status = wifi_getRadioCountryCode(radioIndex,output);
    else if(!strcmp(method, "setRadioCountryCode"))
        return_status = wifi_setRadioCountryCode(radioIndex,output);
    else if(!strcmp(method, "getSSIDMACAddress"))
        return_status = wifi_getSSIDMACAddress(radioIndex,output);
    else if(!strcmp(method, "getApWpsConfigurationState"))
        return_status = wifi_getApWpsConfigurationState(radioIndex,output);
    else if(!strcmp(method, "getBaseBSSID"))
        return_status = wifi_getBaseBSSID(radioIndex, output);
    else if(!strcmp(method, "getHalVersion"))
        return_status = wifi_getHalVersion(output);
    else if(!strcmp(method, "getBandSteeringApGroup"))
        return_status = wifi_getBandSteeringApGroup(output);
    else if(!strcmp(method, "setBandSteeringApGroup"))
        return_status = wifi_setBandSteeringApGroup(output);
    else if(!strcmp(method, "pushSSID"))
        return_status = wifi_pushSSID(radioIndex, output);
    else if(!strcmp(method, "getApName"))
        return_status = wifi_getApName(radioIndex, output);
    else if(!strcmp(method, "setApWpsEnrolleePin"))
        return_status = wifi_setApWpsEnrolleePin(radioIndex, output);
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
 * Function Name        : ssp_WiFiHalCallMethodForRadioStandard
 * Description          : This function invokes WiFi hal's get/set apis, when the value to be
                          get /set is a radio standard
 *
 * @param [in]          : radioIndex - WiFi radio index value
 * @param [in]          : gOnly,nOnly,acOnly - the values to be get/set
 * @param [in]          : method     - name of the wifi hal api to be invoked
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/
int ssp_WIFIHALGetOrSetRadioStandard(int radioIndex, char* output, char* method, unsigned char *gOnly, unsigned char *nOnly, unsigned char *acOnly)
{
    printf("\n ssp_WIFIHALGetOrSetParamStringValue----> Entry\n");
    printf("Radio index:%d\n",radioIndex);
    printf("GetorSetParam: %s\n" , output);
    printf("MethodName: %s\n", method);
    printf("gOnly: %d\n",*gOnly);
    printf("nOnly: %d\n",*nOnly);
    printf("acOnly: %d\n",*acOnly);

    int return_status = 0;

    if(!strcmp(method, "getRadioStandard"))
        return_status = wifi_getRadioStandard(radioIndex, output, gOnly, nOnly, acOnly);
    else if(!strcmp(method, "setRadioChannelMode"))
        return_status = wifi_setRadioChannelMode(radioIndex, output, *gOnly, *nOnly, *acOnly);
    else
    {
        return_status = SSP_FAILURE;
        printf("\n ssp_WiFiHalCallMethodForRadioStandard: Invalid methodName\n");
    }

    printf("ssp_WiFiHalCallMethodForRadioStandard: return value is %s %d %d %d\n", output, *gOnly, *nOnly, *acOnly);
    printf("\n ssp_WiFiHalCallMethodForRadioStandard--> Exit\n");
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
    printf("Radio index:%d\n",radioIndex);
    printf("GetorSetParam: %d\n" , *output);
    printf("MethodName: %s\n", method);
    int return_status = 0;
    int interval_seconds ,dwell_milliseconds;

    if(!strcmp(method, "getRadioMCS"))
        return_status = wifi_getRadioMCS(radioIndex, output);
    else if(!strcmp(method, "setRadioMCS"))
        return_status = wifi_setRadioMCS(radioIndex, *output);
    else if(!strcmp(method, "getRadioStatsReceivedSignalLevel"))
        return_status = wifi_getRadioStatsReceivedSignalLevel(radioIndex, 1, output);
    else if(!strcmp(method, "getApRadioIndex"))
        return_status = wifi_getApRadioIndex(radioIndex, output);
    else if(!strcmp(method, "setApRadioIndex"))
        return_status = wifi_setApRadioIndex(radioIndex, *output);
    else if(!strcmp(method, "getSSIDRadioIndex"))
        return_status = wifi_getSSIDRadioIndex(radioIndex, output);
    else if(!strcmp(method, "getRadioDCSScanTime"))
        return_status = wifi_getRadioDCSScanTime(radioIndex, &interval_seconds, &dwell_milliseconds);
    else if(!strcmp(method, "setRadioDCSScanTime"))
        return_status = wifi_setRadioDCSScanTime(radioIndex, interval_seconds, dwell_milliseconds);
    else if(!strcmp(method, "setApBeaconInterval"))
        return_status = wifi_setApBeaconInterval(radioIndex, *output);
    else if(!strcmp(method, "setDTIMInterval"))
        return_status = wifi_setDTIMInterval(radioIndex, *output);
    else if(!strcmp(method, "setApAuthMode"))
        return_status = wifi_setApAuthMode(radioIndex, *output);
    else if(!strcmp(method, "getApMacAddressControlMode"))
        return_status = wifi_getApMacAddressControlMode(radioIndex, output);
    else if(!strcmp(method, "setApMacAddressControlMode"))
        return_status = wifi_setApMacAddressControlMode(radioIndex, *output);
    else if(!strcmp(method, "getBandSteeringBandUtilizationThreshold"))
        return_status = wifi_getBandSteeringBandUtilizationThreshold(radioIndex, output);
    else if(!strcmp(method, "setBandSteeringBandUtilizationThreshold"))
        return_status = wifi_setBandSteeringBandUtilizationThreshold(radioIndex, *output);
    else if(!strcmp(method, "getBandSteeringRSSIThreshold"))
        return_status = wifi_getBandSteeringRSSIThreshold(radioIndex, output);
    else if(!strcmp(method, "setBandSteeringRSSIThreshold"))
        return_status = wifi_setBandSteeringRSSIThreshold(radioIndex, *output);
    else if(!strcmp(method, "getBandSteeringPhyRateThreshold"))
        return_status = wifi_getBandSteeringPhyRateThreshold(radioIndex, output);
    else if(!strcmp(method, "setBandSteeringPhyRateThreshold"))
        return_status = wifi_setBandSteeringPhyRateThreshold(radioIndex, *output);
    else if(!strcmp(method, "getApManagementFramePowerControl"))
        return_status = wifi_getApManagementFramePowerControl(radioIndex, output);
    else if(!strcmp(method, "setApManagementFramePowerControl"))
        return_status = wifi_setApManagementFramePowerControl(radioIndex, *output);
    else if(!strcmp(method, "getApVlanID"))
        return_status = wifi_getApVlanID(radioIndex, output);
    else if(!strcmp(method, "setApSecurityReset"))
        return_status = wifi_setApSecurityReset(radioIndex);
    else if(!strcmp(method, "getBandSteeringOverloadInactiveTime"))
        return_status = wifi_getBandSteeringOverloadInactiveTime(radioIndex, output);
    else if(!strcmp(method, "setBandSteeringOverloadInactiveTime"))
        return_status = wifi_setBandSteeringOverloadInactiveTime(radioIndex, *output);
    else if(!strcmp(method, "getBandSteeringIdleInactiveTime"))
        return_status = wifi_getBandSteeringIdleInactiveTime(radioIndex, output);
    else if(!strcmp(method, "setBandSteeringIdleInactiveTime"))
        return_status = wifi_setBandSteeringIdleInactiveTime(radioIndex, *output);
    else if(!strcmp(method, "getRadioTxChainMask"))
        return_status = wifi_getRadioTxChainMask(radioIndex, output);
    else if(!strcmp(method, "setRadioTxChainMask"))
        return_status = wifi_setRadioTxChainMask(radioIndex, *output);
    else if(!strcmp(method, "getRadioRxChainMask"))
        return_status = wifi_getRadioRxChainMask(radioIndex, output);
    else if(!strcmp(method, "setRadioRxChainMask"))
        return_status = wifi_setRadioRxChainMask(radioIndex, *output);
    else
    {
        return_status = SSP_FAILURE;
        printf("\n ssp_WiFiHalCallMethodForInt: Invalid methodName\n");
    }

    printf("ssp_WiFiHalCallMethodForInt: return value is %d\n", *output);
    printf("\n ssp_WiFiHalCallMethodForInt--> Exit\n");
    return return_status;
}


/*******************************************************************************************
 *
 * Function Name        : ssp_WIFIHALGetOrSetParamUIntValue
 * Description          : This function invokes WiFi hal's get apis, when the value to be
                          get  is an unsigned integer value
 *
 * @param [in]          : radioIndex - WiFi radio index value
 * @param [in]          : enable     - the value to be get/set
 * @param [in]          : method     - name of the wifi hal api to be invoked
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/
int ssp_WIFIHALGetOrSetParamUIntValue(int radioIndex, unsigned int* output, char* method)
{
    printf("\n ssp_WIFIHALGetOrSetParamUIntValue----> Entry\n");
    printf("Radio index:%d\n",radioIndex);
    printf("GetorSetParam: %u\n" , *output);
    printf("MethodName: %s\n", method);
    int return_status = 0;

    if(!strcmp(method, "getRadioBeaconPeriod"))
        return_status = wifi_getRadioBeaconPeriod(radioIndex, output);
    else if(!strcmp(method, "setRadioBeaconPeriod"))
        return_status = wifi_setRadioBeaconPeriod(radioIndex, *output);
    else if(!strcmp(method, "getApAclDeviceNum"))
        return_status = wifi_getApAclDeviceNum(radioIndex, output);
    else if(!strcmp(method, "getApRetryLimit"))
        return_status = wifi_getApRetryLimit(radioIndex, output);
    else if(!strcmp(method, "setApRetryLimit"))
        return_status = wifi_setApRetryLimit(radioIndex, *output);
    else if(!strcmp(method, "getApMaxAssociatedDevices"))
        return_status = wifi_getApMaxAssociatedDevices(radioIndex, output);
    else if(!strcmp(method, "getApAssociatedDevicesHighWatermarkThreshold"))
        return_status = wifi_getApAssociatedDevicesHighWatermarkThreshold(radioIndex, output);
    else if(!strcmp(method, "setApAssociatedDevicesHighWatermarkThreshold"))
        return_status = wifi_setApAssociatedDevicesHighWatermarkThreshold(radioIndex, *output);
    else if(!strcmp(method, "getApAssociatedDevicesHighWatermark"))
        return_status = wifi_getApAssociatedDevicesHighWatermark(radioIndex, output);
    else if(!strcmp(method, "setApRtsThreshold"))
        return_status = wifi_setApRtsThreshold(radioIndex, *output);
    else if(!strcmp(method, "pushChannel"))
        return_status = wifi_pushChannel(radioIndex, *output);
    else
    {
        return_status = SSP_FAILURE;
        printf("\n ssp_WiFiHalCallMethodForUInt: Invalid methodName\n");
    }

    printf("ssp_WiFiHalCallMethodForUInt: return value is %d\n", *output);
    printf("\n ssp_WiFiHalCallMethodForUInt--> Exit\n");
    return return_status;
}


/*******************************************************************************************
 *
 * Function Name        : WIFIHAL_GetIndexFromName
 * Description          : This function invokes WiFi hal api wifi_getIndexFromName()

 * @param [in]          : param     - the ssid name to be passed
 * @param [out]         : return status an integer value 0-success and 1-Failure
 *
 ********************************************************************************************/
int ssp_WIFIHALGetIndexFromName(char* ssidName, int *output)
{
    printf("\n ssp_WIFIHALGetIndexFromName ----> Entry\n");
    printf("ssidName: %s\n", ssidName);
    int return_status = 0;

    return_status = wifi_getIndexFromName(ssidName, output);
    printf("return value from ssp_WIFIHALGetIndexFromName is %d\n",return_status);
    if(return_status != SSP_SUCCESS)
    {
     printf("\nssp_WIFIHALGetIndexFromName::Failed\n");
     return SSP_FAILURE;
    }
    else
    {
     printf("\nssp_WIFIHALGetIndexFromName::Success\n");
     return return_status;
    }
    printf("\n ssp_WIFIHALGetIndexFromName ----> Exit\n");
}

/*******************************************************************************************
 *
 * Function Name        : WIFIHAL_ClearRadioResetCount
 * Description          : This function invokes WiFi hal api wifi_clearRadioResetCount()

 * @param [in]          : NIL
 * @param [out]         : return status an integer value 0-success and 1-Failure
 *
 ********************************************************************************************/
int ssp_WIFIHALClearRadioResetCount()
{
    printf("\n ssp_WIFIHALClearRadioResetCount ----> Entry\n");
    int return_status = 0;

    return_status = wifi_clearRadioResetCount();
    printf("return value from ssp_WIFIHALClearRadioResetCount is %d\n",return_status);
    if(return_status != SSP_SUCCESS)
    {
     printf("\nssp_WIFIHALClearRadioResetCount::Failed\n");
     return SSP_FAILURE;
    }
    else
    {
     printf("\nssp_WIFIHALClearRadioResetCount::Success\n");
     return return_status;
    }
    printf("\n ssp_WIFIHALClearRadioResetCount ----> Exit\n");
}

/*******************************************************************************************
 *
 * Function Name        : WIFIHAL_Reset
 * Description          : This function invokes WiFi hal api wifi_reset()

 * @param [in]          : NIL
 * @param [out]         : return status an integer value 0-success and 1-Failure
 *
 ********************************************************************************************/
int ssp_WIFIHALReset()
{
    printf("\n ssp_WIFIHALReset ----> Entry\n");
    int return_status = 0;

    return_status = wifi_reset();
    printf("return value from ssp_WIFIHALReset is %d\n",return_status);
    if(return_status != SSP_SUCCESS)
    {
     printf("\nssp_WIFIHALReset::Failed\n");
     return SSP_FAILURE;
    }
    else
    {
     printf("\nssp_WIFIHALReset::Success\n");
     return return_status;
    }
    printf("\n ssp_WIFIHALReset ----> Exit\n");
}

/*******************************************************************************************
 *
 * Function Name        : ssp_WIFIHALGetOrSetSecurityRadiusServer
 * Description          : This function invokes WiFi hal's get/set api's which are
                          related to SecurityRadiusServer
 *
 * @param [in]          : radioIndex - WiFi radio index value
 * @param [in]          : method     - name of the wifi hal api to be invoked
 * @param [in]          : IPAddress - IP Address of the RADIUS server used for WLAN security
 * @param [in]          : port - port  number of the RADIUS server used for WLAN security
 * @param [in]          : RadiusSecret - RadiusSecret of the RADIUS server used for WLAN security
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/
int ssp_WIFIHALGetOrSetSecurityRadiusServer(int radioIndex, char* IPAddress, unsigned int* port, char* RadiusSecret, char* method)
{
    printf("\n ssp_WIFIHALGetOrSetSecurityRadiusServer ----> Entry\n");
    printf("Radio index:%d\n",radioIndex);
    printf("IPAddress : %s\n",IPAddress);
    printf("Port : %u\n" ,*port);
    printf("RadiusSecret : %s\n",RadiusSecret);
    printf("MethodName: %s\n", method);
    int return_status = 0;

    if(!strcmp(method, "getApSecurityRadiusServer"))
        return_status = wifi_getApSecurityRadiusServer(radioIndex, IPAddress, port, RadiusSecret);
    else if(!strcmp(method, "setApSecurityRadiusServer"))
        return_status = wifi_setApSecurityRadiusServer(radioIndex, IPAddress, *port, RadiusSecret);
    else if(!strcmp(method, "getApSecuritySecondaryRadiusServer"))
        return_status = wifi_getApSecuritySecondaryRadiusServer(radioIndex, IPAddress, port, RadiusSecret);
    else if(!strcmp(method, "setApSecuritySecondaryRadiusServer"))
        return_status = wifi_setApSecuritySecondaryRadiusServer(radioIndex, IPAddress, *port, RadiusSecret);
    else
    {
        return_status = SSP_FAILURE;
        printf("\n ssp_WiFiHalCallMethodForSecurityRadiusServer: Invalid methodName\n");
    }
    printf("\n ssp_WiFiHalCallMethodForSecurityRadiusServer--> Exit\n");
    return return_status;
}

/*******************************************************************************************
 *
 * Function Name        : ssp_WIFIHAL_GetOrSetApBridgeInfo
 * Description          : This function invokes WiFi hal's get/set api's which are
                          related to ApBridgeInfo
 *
 * @param [in]          : radioIndex - WiFi radio index value
 * @param [in]          : method     - name of the wifi hal api to be invoked
 * @param [in]          : bridgeName 
 * @param [in]          : IP 
 * @param [in]          : subnet
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/
int ssp_WIFIHALGetOrSetApBridgeInfo(int radioIndex, char* bridgeName, char* IP, char* subnet, char* method)
{
    printf("\n ssp_WIFIHALGetOrSetApBridgeInfo ----> Entry\n");
    printf("Radio index:%d\n",radioIndex);
    printf("IPAddress : %s\n",IP);
    printf("bridgeName : %s\n" ,bridgeName);
    printf("subnet : %s\n",subnet);
    printf("MethodName: %s\n", method);
    int return_status = 0;

    if(!strcmp(method, "getApBridgeInfo"))
        return_status = wifi_getApBridgeInfo(radioIndex, bridgeName, IP, subnet);
    else if(!strcmp(method, "setApBridgeInfo"))
        return_status = wifi_setApBridgeInfo(radioIndex, bridgeName, IP, subnet);
    else
    {
        return_status = SSP_FAILURE;
        printf("\n ssp_WiFiHalCallMethodForApBridgeInfo: Invalid methodName\n");
    }
    printf("\n ssp_WiFiHalCallMethodForApBridgeInfo--> Exit\n");
    return return_status;
}

/*******************************************************************************************
 *
 * Function Name        : WIFIHAL_Down
 * Description          : This function invokes WiFi hal api wifi_down()

 * @param [in]          : NIL
 * @param [out]         : return status as integer value 0-success and 1-Failure
 *
 ********************************************************************************************/
int ssp_WIFIHALDown()
{
    printf("\n ssp_WIFIHALDown ----> Entry\n");
    int return_status = 0;

    return_status = wifi_down();
    printf("return value from ssp_WIFIHALDown is %d\n",return_status);
    if(return_status != SSP_SUCCESS)
    {
     printf("\nssp_WIFIHALDown::Failed\n");
     return SSP_FAILURE;
    }
    else
    {
     printf("\nssp_WIFIHALDown::Success\n");
     return return_status;
    }
    printf("\n ssp_WIFIHALDown ----> Exit\n");
}

