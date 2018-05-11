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

#include "WIFIHAL.h"

/***************************************************************************
 *Function name : initialize
 *Description   : Initialize Function will be used for registering the wrapper method
 *                        with the agent so that wrapper function will be used in the script
 *
 *****************************************************************************/
bool WIFIHAL::initialize(IN const char* szVersion)
{
    return TEST_SUCCESS;
}


/***************************************************************************
 *Function name : testmodulepre_requisites
 *Description   : testmodulepre_requisites will  be used for setting the
 *                pre-requisites that are necessary for this component
 *
 *****************************************************************************/
std::string WIFIHAL::testmodulepre_requisites()
{
    DEBUG_PRINT(DEBUG_TRACE,"\n WIFIHAL testmodulepre_requisites --->Entry\n");

    int return_value = 0;

    return_value = ssp_wifi_init();

    if(0 == return_value)
    {
        DEBUG_PRINT(DEBUG_TRACE,"\n testmodulepre_requisites ---> Initialize SUCCESS !!! \n");
        DEBUG_PRINT(DEBUG_TRACE,"\n WIFIHAL testmodulepre_requisites --->Exit\n");
        return "SUCCESS";
    }
    else
    {
       DEBUG_PRINT(DEBUG_TRACE,"\n testmodulepre_requisites --->Failed to initialize !!! \n");
       DEBUG_PRINT(DEBUG_TRACE,"\n WIFIHAL testmodulepre_requisites --->Exit\n");
       return "FAILURE";
    }
}


/***************************************************************************
 *Function name : testmodulepost_requisites
 *Description    : testmodulepost_requisites will be used for resetting the
 *                pre-requisites that are set
 *
 *****************************************************************************/
bool WIFIHAL::testmodulepost_requisites()
{
    return TEST_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name        : WIFIHAL_GetOrSetParamBoolValue
 * Description          : This function invokes WiFi hal's get/set apis, when the value to be
                          get /set is BOOL
 *
 * @param [in] req-    : methodName - identifier for the hal api name
 			  radioIndex - radio index value of wifi
                          enable     - the bool value to be get/set
                          paramType  - To indicate negative test scenario. it is set as NULL for negative sceanario, otherwise empty
 * @param [out] response - filled with SUCCESS or FAILURE based on the output staus of operation
 *
 ********************************************************************************************/
void WIFIHAL::WIFIHAL_GetOrSetParamBoolValue(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n WIFIHAL_GetOrSetParamBoolValue --->Entry\n");
    char methodName[50] = {'\0'};
    int radioIndex;
    unsigned char enable;
    int returnValue;
    int retValue;
    char details[200] = {'\0'};
    char paramType[10] = {'\0'};

    strcpy(methodName, req["methodName"].asCString());
    radioIndex = req["radioIndex"].asInt();
    enable = req["param"].asInt();
    strcpy(paramType, req["paramType"].asCString());

    if(!(strncmp(methodName, "set",3)&&strncmp(methodName, "push",4)))
    {
	printf("wifi_set operation to be done\n");
        returnValue = ssp_WIFIHALGetOrSetParamBoolValue(radioIndex, &enable, methodName);
        if(0 == returnValue)
        {
            sprintf(details, "%s operation success", methodName);
            response["result"]="SUCCESS";
            response["details"]=details;
        
            if(strstr(methodName, "Radio")||strstr(methodName, "SSID")||strstr(methodName, "Ap")||strstr(methodName, "BandSteering"))
            {
                retValue = ssp_WIFIHALApplySettings(radioIndex,methodName);
                if(0 == retValue)
                {
                    printf("applyRadioSettings operation success\n");
                    return;
                }
                else
                {
                    printf("applyRadioSettings operation failed\n");
                    return;
                }
            }
	    else
		return;
        }
    }
    else
    {
        printf("wifi_get operation to be done\n");
        //paramType is set as NULL for negative test scenarios, for NULL pointer checks
        if(strcmp(paramType, "NULL"))
            returnValue = ssp_WIFIHALGetOrSetParamBoolValue(radioIndex, &enable, methodName);
        else
            returnValue = ssp_WIFIHALGetOrSetParamBoolValue(radioIndex, NULL, methodName);
        if(0 == returnValue)
        {
            DEBUG_PRINT(DEBUG_TRACE,"\n output: %d\n",enable);
            sprintf(details, "Enable state : %s", int(enable)? "Enabled" : "Disabled");
            response["result"]="SUCCESS";
            response["details"]=details;
	    return;
        }
     }
     sprintf(details, "%s operation failed", methodName);
     response["result"]="FAILURE";
     response["details"]=details;
     DEBUG_PRINT(DEBUG_TRACE,"\n WiFiCallMethodForBool --->Error in execution\n");
     return;
}


/*******************************************************************************************
 *
 * Function Name        : WIFIHAL_GetOrSetParamULongValue
 * Description          : This function invokes WiFi hal's get/set apis, when the value to be
                          get /set is Unsigned long
 *
 * @param [in] req-    : methodName - identifier for the hal api name
			 radioIndex - radio index value of wifi
                         param     - the ulong value to be get/set
                         paramType  - To indicate negative test scenario. it is set as NULL for negative sceanario, otherwise empty
 * @param [out] response - filled with SUCCESS or FAILURE based on the output staus of operation
 *
 ********************************************************************************************/
void WIFIHAL::WIFIHAL_GetOrSetParamULongValue(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n WIFIHAL_GetOrSetParamULongValue------>Entry\n");
    char methodName[50] = {'\0'};
    int radioIndex = 1;
    unsigned long uLongVar = 1;
    unsigned long nullValue = NULL;
    int returnValue;
    int retValue;
    char details[200] = {'\0'};
    char paramType[10] = {'\0'};

    strcpy(methodName, req["methodName"].asCString());
    radioIndex = req["radioIndex"].asInt();
    uLongVar = (unsigned long)req["param"].asLargestUInt();
    strcpy(paramType, req["paramType"].asCString());

    if(!strncmp(methodName, "set",3))
    {
	printf("wifi_set operation to be done\n");
        returnValue = ssp_WIFIHALGetOrSetParamULongValue(radioIndex, &uLongVar, methodName);
        if(0 == returnValue)
        {
            sprintf(details, "%s operation success", methodName);
            response["result"]="SUCCESS";
            response["details"]=details;
        
            if(strstr(methodName, "Radio")||strstr(methodName, "SSID")||strstr(methodName, "Ap"))
            {
                retValue = ssp_WIFIHALApplySettings(radioIndex,methodName);
                if(0 == retValue)
                {
                    printf("applyRadioSettings operation success\n");
                    return;
                }
                else
                {
                    printf("applyRadioSettings operation failed\n");
                    return;
                }
            }
	    else
		return;
        }
    }
    else
    {
       printf("wifi_get operation to be done\n");
       //paramType is set as NULL for negative test scenarios, for NULL pointer checks
       if(strcmp(paramType, "NULL"))
           returnValue = ssp_WIFIHALGetOrSetParamULongValue(radioIndex, &uLongVar, methodName);
       else
           returnValue = ssp_WIFIHALGetOrSetParamULongValue(radioIndex, &nullValue, methodName);
       if(0 == returnValue)
        {
            DEBUG_PRINT(DEBUG_TRACE,"\n output: %lu\n",uLongVar);
            sprintf(details, "Value returned is :%lu", uLongVar);
            response["result"]="SUCCESS";
            response["details"]=details;
	    return;
        }
     }
     sprintf(details, "%s operation failed", methodName);
     response["result"]="FAILURE";
     response["details"]=details;
     DEBUG_PRINT(DEBUG_TRACE,"\n WiFiCallMethodForULong --->Error in execution\n");
     return;

}


/*******************************************************************************************
 *
 * Function Name        : WIFIHAL_GetOrSetParamStringValue
 * Description          : This function invokes WiFi hal's get/set apis, when the value to be
                          get /set is a string
 *
 * @param [in] req-    : methodName - identifier for the hal api name
 			  radioIndex - radio index value of wifi
                          param     - the string value to be get
                          paramType  - To indicate negative test scenario. it is set as NULL for negative sceanario, otherwise empty
 * @param [out] response - filled with SUCCESS or FAILURE based on the output staus of operation
 *
 ********************************************************************************************/
void WIFIHAL::WIFIHAL_GetOrSetParamStringValue(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n WIFIHAL_GetOrSetParamStringValue  ----->Entry\n");
    char methodName[50] = {'\0'};
    int radioIndex = 1;
    char output[1000] = {'\0'};
    int returnValue;
    int retValue;
    char details[200] = {'\0'};
    char paramType[10] = {'\0'};
    char param[200] = {'\0'}; 

    strcpy(methodName, req["methodName"].asCString());
    radioIndex = req["radioIndex"].asInt();
    strcpy(paramType, req["paramType"].asCString());
    strcpy(param, req["param"].asCString());

    if(!(strncmp(methodName, "set",3)&&strncmp(methodName, "push",4)))
    {
	printf("wifi_set operation to be done\n");
        returnValue = ssp_WIFIHALGetOrSetParamStringValue(radioIndex, param, methodName);
        if(0 == returnValue)
        {
            sprintf(details, "%s operation success", methodName);
            response["result"]="SUCCESS";
            response["details"]=details;
        
            if(strstr(methodName, "Radio")||strstr(methodName, "SSID")||strstr(methodName, "Ap"))
            {
                retValue = ssp_WIFIHALApplySettings(radioIndex,methodName);
                if(0 == retValue)
                {
                    printf("applyRadioSettings operation success\n");
                    return;
                }
                else
                {
                    printf("applyRadioSettings operation failed\n");
                    return;
                }
            }
	    else
		return;
        }
        else
        {
            sprintf(details, "%s operation failed", methodName);
            response["result"]="FAILURE";
            response["details"]=details;
            DEBUG_PRINT(DEBUG_TRACE,"\n WiFiCallMethodForString --->Error in execution\n");
            return;
        }
    }
    else
    {
        printf("wifi_get operation to be done\n");
        //paramType is set as NULL for negative test scenarios, for NULL pointer checks
        if(strcmp(paramType, "NULL"))
            returnValue = ssp_WIFIHALGetOrSetParamStringValue(radioIndex, output, methodName);
        else
            returnValue = ssp_WIFIHALGetOrSetParamStringValue(radioIndex, NULL, methodName);

        if(0 == returnValue)
        {
            DEBUG_PRINT(DEBUG_TRACE,"\n output: %s\n",output);
            sprintf(details, "Value returned is :%s", output);
            response["result"]="SUCCESS";
            response["details"]=details;
            return;
        }
        else
        {
            sprintf(details, "%s operation failed", methodName);
            response["result"]="FAILURE";
            response["details"]=details;
            DEBUG_PRINT(DEBUG_TRACE,"\n WiFiCallMethodForString --->Error in execution\n");
            return;
        }
    }
}

/*******************************************************************************************
 *
 * Function Name        : WIFIHAL_GetOrSetRadioStandard
 * Description          : This function invokes WiFi hal's get/set apis, when the value to be
                          get /set is a string
 *
 * @param [in] req-    : methodName - identifier for the hal api name
                          radioIndex - radio index value of wifi
                          param     - the string value to be get
                          paramType  - To indicate negative test scenario. it is set as NULL for negative sceanario, otherwise empty
			  gOnly, nOnly, acOnly - the bool values to be set/get
 * @param [out] response - filled with SUCCESS or FAILURE based on the output staus of operation
 *
 ********************************************************************************************/
void WIFIHAL::WIFIHAL_GetOrSetRadioStandard(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n WIFIHAL_GetOrSetParamRadioStandard ----->Entry\n");
    char methodName[50] = {'\0'};
    int radioIndex = 1;
    char output[1000] = {'\0'};
    int returnValue;
    int retValue;
    char details[200] = {'\0'};
    char paramType[10] = {'\0'};
    char param[200] = {'\0'};
    unsigned char gOnly, nOnly, acOnly;

    strcpy(methodName, req["methodName"].asCString());
    radioIndex = req["radioIndex"].asInt();
    strcpy(paramType, req["paramType"].asCString());
    strcpy(param, req["param"].asCString());
    gOnly = req["gOnly"].asInt();
    nOnly = req["nOnly"].asInt();
    acOnly = req["acOnly"].asInt();

    if(!strncmp(methodName, "set",3))
    {
        printf("wifi_set operation to be done\n");
        returnValue = ssp_WIFIHALGetOrSetRadioStandard(radioIndex, param, methodName, &gOnly, &nOnly, &acOnly);
        if(0 == returnValue)
        {
            sprintf(details, "%s operation success", methodName);
            response["result"]="SUCCESS";
            response["details"]=details;

            if(strstr(methodName, "Radio")||strstr(methodName, "SSID")||strstr(methodName, "Ap"))
            {
                retValue = ssp_WIFIHALApplySettings(radioIndex,methodName);
                if(0 == retValue)
                {
                    printf("applyRadioSettings operation success\n");
                    return;
                }
                else
                {
                    printf("applyRadioSettings operation failed\n");
                    return;
                }
            }
            else
                return;
        }
        else
        {
            sprintf(details, "%s operation failed", methodName);
            response["result"]="FAILURE";
            response["details"]=details;
            DEBUG_PRINT(DEBUG_TRACE,"\n WiFiCallMethodForRadioStandard --->Error in execution\n");
            return;
        }
    }
    else
    {
        printf("wifi_get operation to be done\n");
        //paramType is set as NULL for negative test scenarios, for NULL pointer checks
        if(strcmp(paramType, "NULL"))
            returnValue = ssp_WIFIHALGetOrSetRadioStandard(radioIndex, output, methodName, &gOnly, &nOnly, &acOnly);
        else
            returnValue = ssp_WIFIHALGetOrSetRadioStandard(radioIndex, NULL, methodName, &gOnly, &nOnly, &acOnly);

        if(0 == returnValue)
        {
            DEBUG_PRINT(DEBUG_TRACE,"\n output: %s\n",output);
            sprintf(details, "Value returned is :%s %d %d %d", output,gOnly,nOnly,acOnly);
            response["result"]="SUCCESS";
            response["details"]=details;
            return;
        }
        else
        {
            sprintf(details, "%s operation failed", methodName);
            response["result"]="FAILURE";
            response["details"]=details;
            DEBUG_PRINT(DEBUG_TRACE,"\n WiFiCallMethodForRadioStandard --->Error in execution\n");
            return;
        }
    }
}


/*******************************************************************************************
 *
 * Function Name        : WIFIHAL_GetOrSetParamIntValue
 * Description          : This function invokes WiFi hal's get apis, when the value to be
                          get  is an integer
 *
 * @param [in] req-    : methodName - identifier for the hal api name
 			  radioIndex - radio index value of wifi
                          param     - the int value to be get
                          paramType  - To indicate negative test scenario. it is set as NULL for negative sceanario, otherwise empty
 * @param [out] response - filled with SUCCESS or FAILURE based on the output staus of operation
 *
 ********************************************************************************************/
void WIFIHAL::WIFIHAL_GetOrSetParamIntValue(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n WIFIHAL_GetOrSetParamIntValue----->Entry\n");
    char methodName[50] = {'\0'};
    int radioIndex = 1;
    int intParam = 1;
    int returnValue;
    int retValue;
    char details[200] = {'\0'};
    char paramType[10] = {'\0'};

    strcpy(methodName, req["methodName"].asCString());
    intParam = req["param"].asInt();
    radioIndex = req["radioIndex"].asInt();
    strcpy(paramType, req["paramType"].asCString());

    if(!strncmp(methodName, "set",3))
    {
	printf("wifi_set operation to be done\n");
        printf("MethodName : %s\n",methodName);
        returnValue = ssp_WIFIHALGetOrSetParamIntValue(radioIndex, &intParam, methodName);
        if(0 == returnValue)
        {
            sprintf(details, "%s operation success", methodName);
            response["result"]="SUCCESS";
            response["details"]=details;
        
            if(strstr(methodName, "Radio")||strstr(methodName, "SSID")||strstr(methodName, "Ap"))
            {
                retValue = ssp_WIFIHALApplySettings(radioIndex,methodName);
                if(0 == retValue)
                {
                    printf("applyRadioSettings operation success\n");
                    return;
                }
                else
                {
                    printf("applyRadioSettings operation failed\n");
                    return;
                }
            }
	    else
		return;
        }
    }
    else
    {
        printf("wifi_get operation to be done\n");
        printf("MethodName : %s\n",methodName);
        //paramType is set as NULL for negative test scenarios, for NULL pointer checks
        if(strcmp(paramType, "NULL"))
            //When the paramType is not equal to NULL
            returnValue = ssp_WIFIHALGetOrSetParamIntValue(radioIndex, &intParam, methodName);
        else
            //When the paramType is NULL i.e., negative scenario
            returnValue = ssp_WIFIHALGetOrSetParamIntValue(radioIndex, NULL, methodName);
        if(0 == returnValue)
        {
            DEBUG_PRINT(DEBUG_TRACE,"\n output: %d\n",intParam);
            sprintf(details, "Value returned is :%d", intParam);
            response["result"]="SUCCESS";
            response["details"]=details;
            return;
        }
     }
     sprintf(details, "%s operation failed", methodName);
     response["result"]="FAILURE";
     response["details"]=details;
     DEBUG_PRINT(DEBUG_TRACE,"\n WiFiCallMethodForInt --->Error in execution\n");
     return;
}

/*******************************************************************************************
 *
 * Function Name        : WIFIHAL_GetOrSetParamUIntValue
 * Description          : This function invokes WiFi hal's get apis, when the value to be
                          get  is an unsigned integer
 *
 * @param [in] req-    : methodName - identifier for the hal api name
 			  radioIndex - radio index value of wifi
                          param     - the int value to be get
                          paramType  - To indicate negative test scenario. it is set as NULL for negative sceanario, otherwise empty
 * @param [out] response - filled with SUCCESS or FAILURE based on the output staus of operation
 *
 ********************************************************************************************/
void WIFIHAL::WIFIHAL_GetOrSetParamUIntValue (IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n WIFIHAL_GetOrSetParamUIntValue----->Entry\n");

    char methodName[50] = {'\0'};
    int radioIndex = 1;
    unsigned int uintParam = 1;
    int returnValue;
    int retValue;
    char details[200] = {'\0'};
    char paramType[10] = {'\0'};

    strcpy(methodName, req["methodName"].asCString());
    uintParam = req["param"].asInt();
    radioIndex = req["radioIndex"].asInt();
    strcpy(paramType, req["paramType"].asCString());

    if(!strncmp(methodName, "set",3))
    {
	printf("wifi_set operation to be done\n");
        printf("MethodName : %s\n",methodName);
        returnValue = ssp_WIFIHALGetOrSetParamUIntValue(radioIndex, &uintParam, methodName);
        if(0 == returnValue)
        {
            sprintf(details, "%s operation success", methodName);
            response["result"]="SUCCESS";
            response["details"]=details;
        
            if(strstr(methodName, "Radio")||strstr(methodName, "SSID")||strstr(methodName, "Ap"))
            {
                retValue = ssp_WIFIHALApplySettings(radioIndex,methodName);
                if(0 == retValue)
                {
                    printf("applyRadioSettings operation success\n");
                    return;
                }
                else
                {
                    printf("applyRadioSettings operation failed\n");
                    return;
                }
            }
	    else
		return;
        }
    }
    else
    {
        printf("wifi_get operation to be done\n");
        printf("MethodName : %s\n",methodName);
        //paramType is set as NULL for negative test scenarios, for NULL pointer checks
        if(strcmp(paramType, "NULL"))
            //When the paramType is not equal to NULL
            returnValue = ssp_WIFIHALGetOrSetParamUIntValue(radioIndex, &uintParam, methodName);
        else
            //When the paramType is NULL i.e., negative scenario
            returnValue = ssp_WIFIHALGetOrSetParamUIntValue(radioIndex, NULL, methodName);
        if(0 == returnValue)
        {
            DEBUG_PRINT(DEBUG_TRACE,"\n output: %u\n",uintParam);
            sprintf(details, "Value returned is :%u", uintParam);
            response["result"]="SUCCESS";
            response["details"]=details;
            return;
        }
     }
     sprintf(details, "%s operation failed", methodName);
     response["result"]="FAILURE";
     response["details"]=details;
     DEBUG_PRINT(DEBUG_TRACE,"\n WiFiCallMethodForUInt --->Error in execution\n");
     return;
}
/*******************************************************************************************
 *
 * Function Name        : WIFIHAL_GetIndexFromName
 * Description          : This function invokes WiFi hal api wifi_getIndexFromName()

 * @param [in] req-     : param     - the ssid name to be passed
 * @param [out] response - filled with SUCCESS or FAILURE based on the output staus of operation
 *
 ********************************************************************************************/
void WIFIHAL::WIFIHAL_GetIndexFromName (IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n WIFIHAL_GetIndexFromName ----->Entry\n");

    int returnValue;
    int output = 1;
    char ssidName[10] = {'\0'};
    char details[200] = {'\0'};

    strcpy(ssidName, req["param"].asCString());

    returnValue = ssp_WIFIHALGetIndexFromName(ssidName, &output);
    if(0 == returnValue)
       {
            DEBUG_PRINT(DEBUG_TRACE,"\n output: %d\n",output);
            sprintf(details, "Value returned is :%d", output);
            response["result"]="SUCCESS";
            response["details"]=details;
            return;
       }
    else
       {
            sprintf(details, "GetIndexFromName operation failed");
            response["result"]="FAILURE";
            response["details"]=details;
            return;
       }
    DEBUG_PRINT(DEBUG_TRACE,"\n WIFIHAL_GetIndexFromName  --->Exit\n");
}
/*******************************************************************************************
 *
 * Function Name        : WIFIHAL_ClearRadioResetCount
 * Description          : This function invokes WiFi hal api wifi_clearRadioResetCount()

 * @param [in] req-     : NIL
 * @param [out] response - filled with SUCCESS or FAILURE based on the output status of operation
 *
 ********************************************************************************************/
void WIFIHAL::WIFIHAL_ClearRadioResetCount (IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n WIFIHAL_ClearRadioResetCount ----->Entry\n");

    int returnValue;
    char details[200] = {'\0'};

    returnValue = ssp_WIFIHALClearRadioResetCount();
    if(0 == returnValue)
       {
            sprintf(details, "ClearRadioResetCount operation success");
            response["result"]="SUCCESS";
            response["details"]=details;
            return;
       }
    else
       {
            sprintf(details, "ClearRadioResetCount operation failed");
            response["result"]="FAILURE";
            response["details"]=details;
            return;
       }
    DEBUG_PRINT(DEBUG_TRACE,"\n WIFIHAL_ClearRadioResetCount  --->Exit\n");
}
/*******************************************************************************************
 *
 * Function Name        : WIFIHAL_Reset
 * Description          : This function invokes WiFi hal api wifi_reset()

 * @param [in] req-     : NIL
 * @param [out] response - filled with SUCCESS or FAILURE based on the output status of operation
 *
 ********************************************************************************************/
void WIFIHAL::WIFIHAL_Reset (IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n WIFIHAL_Reset ----->Entry\n");

    int returnValue;
    char details[200] = {'\0'};

    returnValue = ssp_WIFIHALReset();
    if(0 == returnValue)
       {
            sprintf(details, "wifi_reset operation success");
            response["result"]="SUCCESS";
            response["details"]=details;
            return;
       }
    else
       {
            sprintf(details, "wifi_reset operation failed");
            response["result"]="FAILURE";
            response["details"]=details;
            return;
       }
    DEBUG_PRINT(DEBUG_TRACE,"\n WIFIHAL_Reset --->Exit\n");
}
/*******************************************************************************************
 *
 * Function Name        : WIFIHAL_GetOrSetSecurityRadiusServer
 * Description          : This function invokes WiFi hal's get/set api's which are
                          related to SecurityRadiusServer
 *
 * @param [in] req-    :  methodName - identifier for the hal api name
                          radioIndex - radio index value of wifi
                          IPAddress - IP Address of the RADIUS server used for WLAN security
			  port - port  number of the RADIUS server used for WLAN security
			  RadiusSecret - RadiusSecret of the RADIUS server used for WLAN security
                          paramType  - To indicate negative test scenario. it is set as NULL for negative sceanario, otherwise empty
 * @param [out] response - filled with SUCCESS or FAILURE based on the output status of operation
 *
 ********************************************************************************************/
void WIFIHAL::WIFIHAL_GetOrSetSecurityRadiusServer(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n WIFIHAL_GetOrSetSecurityRadiusServer----->Entry\n");
    char methodName[50] = {'\0'};
    int radioIndex = 1;
    int returnValue;
    char details[200] = {'\0'};
    char paramType[10] = {'\0'};
    unsigned int port = 1;
    char IPAddress[50] = {'\0'};
    char RadiusSecret[100] = {'\0'};

    strcpy(methodName, req["methodName"].asCString());
    radioIndex = req["radioIndex"].asInt();
    port = req["port"].asInt();
    strcpy(IPAddress, req["IPAddress"].asCString());
    strcpy(RadiusSecret, req["RadiusSecret"].asCString());
    strcpy(paramType, req["paramType"].asCString());

    if(!strncmp(methodName, "set",3))
    {
        DEBUG_PRINT(DEBUG_TRACE,"\n Set operation requested\n");
        printf("MethodName : %s\n",methodName);
        returnValue = ssp_WIFIHALGetOrSetSecurityRadiusServer(radioIndex, IPAddress, &port, RadiusSecret, methodName);
        if(0 == returnValue)
        {
            sprintf(details, "%s operation success", methodName);
            response["result"]="SUCCESS";
            response["details"]=details;
            return;
        }
    }
    else
    {
        DEBUG_PRINT(DEBUG_TRACE,"\n Get operation requested\n");
        printf("MethodName : %s\n",methodName);
        //paramType is set as NULL for negative test scenarios, for NULL pointer checks
        if(strcmp(paramType, "NULL"))
            //When the paramType is not equal to NULL
            returnValue = ssp_WIFIHALGetOrSetSecurityRadiusServer(radioIndex, IPAddress, &port, RadiusSecret, methodName);
        else
            //When the paramType is NULL i.e., negative scenario
            returnValue = ssp_WIFIHALGetOrSetSecurityRadiusServer(radioIndex, NULL, NULL, NULL, methodName);
        if(0 == returnValue)
        {
            DEBUG_PRINT(DEBUG_TRACE,"\n output: %s\n%d\n%s\n",IPAddress,port,RadiusSecret);
            sprintf(details, "Value returned is :IPAddress=%s,Port=%d,RadiusSecret=%s",IPAddress, port, RadiusSecret);
            response["result"]="SUCCESS";
            response["details"]=details;
            return;
        }
     }
     sprintf(details, "%s operation failed", methodName);
     response["result"]="FAILURE";
     response["details"]=details;
     DEBUG_PRINT(DEBUG_TRACE,"\n WIFIHAL_GetOrSetSecurityRadiusServer ---->Error in execution\n");
     return;
}
/*******************************************************************************************
 *
 * Function Name        : WIFIHAL_GetOrSetApBridgeInfo
 * Description          : This function invokes WiFi hal's get/set apis, when the value to be
                          get /set is related to ApBridgeInfo
 *
 * @param [in] req-    : methodName - identifier for the hal api name
                          radioIndex - radio index value of wifi
                          bridgeName,IP,subnet - the string value to be get/set
                          paramType  - To indicate negative test scenario. it is set as NULL for negative sceanario, otherwise empty
 * @param [out] response - filled with SUCCESS or FAILURE based on the output status of operation
 *
 ********************************************************************************************/
void WIFIHAL::WIFIHAL_GetOrSetApBridgeInfo(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n WIFIHAL_GetOrSetApBridgeInfo  ----->Entry\n");
    char methodName[50] = {'\0'};
    int radioIndex = 1;
    char output[1000] = {'\0'};
    int returnValue;
    int retValue;
    char details[200] = {'\0'};
    char paramType[10] = {'\0'};
    char bridgeName[32] = {'\0'};
    char IP[20] = {'\0'};
    char subnet[50] = {'\0'};

    strcpy(methodName, req["methodName"].asCString());
    radioIndex = req["radioIndex"].asInt();
    strcpy(paramType, req["paramType"].asCString());
    strcpy(bridgeName, req["bridgeName"].asCString());
    strcpy(IP, req["IP"].asCString());
    strcpy(subnet, req["subnet"].asCString());

    if(!strncmp(methodName, "set",3))
    {
        printf("wifi_set operation to be done\n");
        returnValue = ssp_WIFIHALGetOrSetApBridgeInfo(radioIndex, bridgeName, IP, subnet, methodName);
        if(0 == returnValue)
        {
            sprintf(details, "%s operation success", methodName);
            response["result"]="SUCCESS";
            response["details"]=details;

            retValue = ssp_WIFIHALApplySettings(radioIndex,methodName);
            if(0 == retValue)
            {
                printf("applyRadioSettings operation success\n");
                return;
            }
            else
            {
                printf("applyRadioSettings operation failed\n");
                return;
            }
        }
        else
        {
            sprintf(details, "%s operation failed", methodName);
            response["result"]="FAILURE";
            response["details"]=details;
            DEBUG_PRINT(DEBUG_TRACE,"\n WiFiCallMethodForApBridgeInfo --->Error in execution\n");
            return;
        }
    }
    else
    {
        printf("wifi_get operation to be done\n");
        //paramType is set as NULL for negative test scenarios, for NULL pointer checks
        if(strcmp(paramType, "NULL"))
            returnValue = ssp_WIFIHALGetOrSetApBridgeInfo(radioIndex, bridgeName, IP, subnet, methodName);
        else
            returnValue = ssp_WIFIHALGetOrSetApBridgeInfo(radioIndex, NULL, NULL, NULL, methodName);

        if(0 == returnValue)
        {
            DEBUG_PRINT(DEBUG_TRACE,"\n output: %s\n%s\n%s\n",bridgeName,IP,subnet);
            sprintf(details, "Value returned is :bridgeName=%s,IP=%s,subnet=%s",bridgeName,IP,subnet);
            response["result"]="SUCCESS";
            response["details"]=details;
            return;
        }
        else
        {
            sprintf(details, "%s operation failed", methodName);
            response["result"]="FAILURE";
            response["details"]=details;
            DEBUG_PRINT(DEBUG_TRACE,"\n WiFiCallMethodForApBridgeInfo --->Error in execution\n");
            return;
	}
    }
}
/*******************************************************************************************
 *
 * Function Name        : WIFIHAL_GetOrSetRadioDCSScanTime
 * Description          : This function invokes WiFi hal's get/set apis, when the value to be
                          get /set is related to RadioDCSScanTime
 *
 * @param [in] req-    : methodName - identifier for the hal api name
                         radioIndex - radio index value of wifi
                         output_interval_seconds,output_dwell_milliseconds - the integer value to be get/set
                         paramType  - To indicate negative test scenario. it is set as NULL for negative sceanario, otherwise empty
 * @param [out] response - filled with SUCCESS or FAILURE based on the output status of operation
 *
 ********************************************************************************************/
void WIFIHAL::WIFIHAL_GetOrSetRadioDCSScanTime(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n WIFIHAL_GetOrSetRadioDCSScanTime----->Entry\n");
    char methodName[50] = {'\0'};
    int radioIndex = 1;
    char output[1000] = {'\0'};
    int returnValue;
    int retValue;
    char details[200] = {'\0'};
    char paramType[10] = {'\0'};
    int output_interval_seconds = 1;
    int output_dwell_milliseconds = 1;

    strcpy(methodName, req["methodName"].asCString());
    radioIndex = req["radioIndex"].asInt();
    strcpy(paramType, req["paramType"].asCString());
    output_interval_seconds = req["output_interval_seconds"].asInt();
    output_dwell_milliseconds = req["output_dwell_milliseconds"].asInt();

    if(!strncmp(methodName, "set",3))
    {
        printf("wifi_set operation to be done\n");
        returnValue = ssp_WIFIHALGetOrSetRadioDCSScanTime(radioIndex, &output_interval_seconds, &output_dwell_milliseconds, methodName);
        if(0 == returnValue)
        {
            sprintf(details, "%s operation success", methodName);
            response["result"]="SUCCESS";
            response["details"]=details;

            retValue = ssp_WIFIHALApplySettings(radioIndex,methodName);
            if(0 == retValue)
            {
                printf("applyRadioSettings operation success\n");
                return;
            }
            else
            {
                printf("applyRadioSettings operation failed\n");
                return;
            }
        }
        else
        {
            sprintf(details, "%s operation failed", methodName);
            response["result"]="FAILURE";
            response["details"]=details;
            DEBUG_PRINT(DEBUG_TRACE,"\n WiFiCallMethodForRadioDCSScanTime --->Error in execution\n");
            return;
        }
    }
    else
    {
        printf("wifi_get operation to be done\n");
        //paramType is set as NULL for negative test scenarios, for NULL pointer checks
        if(strcmp(paramType, "NULL"))
            returnValue = ssp_WIFIHALGetOrSetRadioDCSScanTime(radioIndex, &output_interval_seconds, &output_dwell_milliseconds, methodName);
        else
            returnValue = ssp_WIFIHALGetOrSetRadioDCSScanTime(radioIndex, NULL, NULL, methodName);

        if(0 == returnValue)
        {
            DEBUG_PRINT(DEBUG_TRACE,"\n output: %d\n%d\n",output_interval_seconds,output_dwell_milliseconds);
            sprintf(details, "Value returned is :output_interval_seconds=%d,output_dwell_milliseconds=%d",output_interval_seconds,output_dwell_milliseconds);
            response["result"]="SUCCESS";
            response["details"]=details;
            return;
        }
        else
        {
            sprintf(details, "%s operation failed", methodName);
            response["result"]="FAILURE";
            response["details"]=details;
            DEBUG_PRINT(DEBUG_TRACE,"\n WiFiCallMethodForRadioDCSScanTime --->Error in execution\n");
            return;
        }
    }
}
/*******************************************************************************************
 *
 * Function Name        : WIFIHAL_AddorDelApAclDevice
 * Description          : This function invokes WiFi hal's add/delete apis, when the value to be
                          added/deleted is related to ApAclDevice
 *
 * @param [in] req-    : methodName - identifier for the hal api name
                          apIndex - ap index value of wifi
                          DeviceMacAddress - the MacAddress(string)of the device to be added/deleted
 * @param [out] response - filled with SUCCESS or FAILURE based on the output status of operation
 *
 ********************************************************************************************/
void WIFIHAL::WIFIHAL_AddorDelApAclDevice(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n WIFIHAL_AddorDelApAclDevice------>Entry\n");
    char methodName[50] = {'\0'};
    int apIndex = 1;
    char output[1000] = {'\0'};
    int returnValue;
    char details[200] = {'\0'};
    char DeviceMacAddress[64] = {'\0'};
    strcpy(methodName, req["methodName"].asCString());
    apIndex = req["apIndex"].asInt();
    strcpy(DeviceMacAddress, req["DeviceMacAddress"].asCString());
    if(!strncmp(methodName, "add",3))
    {
        printf("wifi_add operation to be done\n");
        returnValue = ssp_WIFIHALAddorDelApAclDevice(apIndex, DeviceMacAddress, methodName);
        if(0 == returnValue)
        {
            sprintf(details, "%s operation success", methodName);
            response["result"]="SUCCESS";
            response["details"]=details;
            return;
        }
        else
        {
            sprintf(details, "%s operation failed", methodName);
            response["result"]="FAILURE";
            response["details"]=details;
            DEBUG_PRINT(DEBUG_TRACE,"\n WiFiCallMethodForAddApAclDevice --->Error in execution\n");
            return;
        }
    }
    else
    {
        printf("wifi_delete operation to be done\n");
	returnValue = ssp_WIFIHALAddorDelApAclDevice(apIndex, DeviceMacAddress, methodName);
        if(0 == returnValue)
        {
            sprintf(details, "%s operation success", methodName);
            response["result"]="SUCCESS";
            response["details"]=details;
            return;
        }
        else
        {
            sprintf(details, "%s operation failed", methodName);
            response["result"]="FAILURE";
            response["details"]=details;
            DEBUG_PRINT(DEBUG_TRACE,"\n WiFiCallMethodForDelApAclDevice --->Error in execution\n");
            return;
	}
    }
}
/*******************************************************************************************
 *
 * Function Name        : WIFIHAL_IfConfigUporDown
 * Description          : This function invokes WiFi hal api's wifi_ifConfigDown() or wifi_ifConfigUp()

 * @param [in] req-     :  apIndex - ap Index value of wifi
                           methodName - identifier for the hal api name
 * @param [out] response - filled with SUCCESS or FAILURE based on the output status of operation
 *
 ********************************************************************************************/
void WIFIHAL::WIFIHAL_IfConfigUporDown(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n WIFIHAL_IfConfigUporDown------>Entry\n");
    char methodName[50] = {'\0'};
    int apIndex = 1;
    char output[1000] = {'\0'};
    int returnValue;
    char details[200] = {'\0'};
    strcpy(methodName, req["methodName"].asCString());
    apIndex = req["apIndex"].asInt();
    if(!strcmp(methodName, "ifConfigUp"))
    {
        printf("wifi_IfConfigUp operation to be done\n");
        returnValue = ssp_WIFIHALIfConfigUporDown(apIndex, methodName);
        if(0 == returnValue)
        {
            sprintf(details, "%s operation success", methodName);
            response["result"]="SUCCESS";
            response["details"]=details;
	    return;
        }
        else
        {
            sprintf(details, "%s operation failed", methodName);
            response["result"]="FAILURE";
            response["details"]=details;
            DEBUG_PRINT(DEBUG_TRACE,"\n WiFiCallMethodForIfConfigUp --->Error in execution\n");
            return;
        }
    }
    else
    {
        printf("wifi_IfConfigDown operation to be done\n");
	returnValue = ssp_WIFIHALIfConfigUporDown(apIndex, methodName);
        if(0 == returnValue)
        {
            sprintf(details, "%s operation success", methodName);
            response["result"]="SUCCESS";
            response["details"]=details;
            return;
        }
        else
        {
            sprintf(details, "%s operation failed", methodName);
            response["result"]="FAILURE";
            response["details"]=details;
            DEBUG_PRINT(DEBUG_TRACE,"\n WiFiCallMethodForIfConfigDown --->Error in execution\n");
            return;
	}
    }
}
/*******************************************************************************************
 *
 * Function Name        : WIFIHAL_ParamRadioIndex
 * Description          : This function invokes WiFi hal api's which require radioIndex as input
 * @param [in] req-     :  radioIndex - radio Index value of wifi
                           methodName - identifier for the hal api name
 * @param [out] response - filled with SUCCESS or FAILURE based on the output status of operation
 *
 ********************************************************************************************/
void WIFIHAL::WIFIHAL_ParamRadioIndex(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n WIFIHAL_ParamRadioIndex------>Entry\n");
    char methodName[50] = {'\0'};
    int radioIndex = 1;
    char output[1000] = {'\0'};
    int returnValue;
    char details[200] = {'\0'};
    strcpy(methodName, req["methodName"].asCString());
    radioIndex = req["radioIndex"].asInt();
    if(strstr(methodName, "cancel")||strstr(methodName, "set")||strstr(methodName, "reset")||strstr(methodName, "disable")||strstr(methodName, "remove")||strstr(methodName, "init")||strstr(methodName, "factoryReset"))
    {
        returnValue = ssp_WIFIHALParamRadioIndex(radioIndex, methodName);
	if(0 == returnValue)
        {
            sprintf(details, "%s operation success", methodName);
            response["result"]="SUCCESS";
            response["details"]=details;
            return;
        }
        else
        {
            sprintf(details, "%s operation failed", methodName);
            response["result"]="FAILURE";
            response["details"]=details;
            DEBUG_PRINT(DEBUG_TRACE,"\n WiFiCallMethodForParamRadioIndex --->Error in execution\n");
            return;
	}
    }
    else
        return;
    DEBUG_PRINT(DEBUG_TRACE,"\n WIFIHAL_ParamRadioIndex --->Exit\n");
}
/*******************************************************************************************
 *
 * Function Name        : WIFIHAL_StartorStopHostApd
 * Description          : This function invokes WiFi hal api's wifi_startHostApd() and wifi_stopHostApd()
 * @param [in] req-     : methodName - identifier for the hal api name
 * @param [out] response - filled with SUCCESS or FAILURE based on the output status of operation
 *
 ********************************************************************************************/
void WIFIHAL::WIFIHAL_StartorStopHostApd(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n WIFIHAL_StartorStopHostApd ----->Entry\n");
    int returnValue;
    char details[200] = {'\0'};
    char output[1000] = {'\0'};
    char methodName[50] = {'\0'};
    strcpy(methodName, req["methodName"].asCString());
    if(strstr(methodName, "start")||strstr(methodName, "stop"))
    {
        returnValue = ssp_WIFIHALStartorStopHostApd(methodName);
	if(0 == returnValue)
        {
            sprintf(details, "%s operation success", methodName);
            response["result"]="SUCCESS";
            response["details"]=details;
            return;
        }
        else
        {
            sprintf(details, "%s operation failed", methodName);
            response["result"]="FAILURE";
            response["details"]=details;
            DEBUG_PRINT(DEBUG_TRACE,"\n WiFiCallMethodForStartorStopHostApd --->Error in execution\n");
            return;
	}
    }
    else
        return;
    DEBUG_PRINT(DEBUG_TRACE,"\n WIFIHAL_StartorStopHostApd --->Exit\n");
}
/*******************************************************************************************
 *
 * Function Name        : WIFIHAL_FactoryReset
 * Description          : This function invokes WiFi hal api's wifi_factoryResetRadios() and wifi_factoryReset()
 * @param [in] req-     : methodName - identifier for the hal api name
 * @param [out] response - filled with SUCCESS or FAILURE based on the output status of operation
 *
 ********************************************************************************************/
void WIFIHAL::WIFIHAL_FactoryReset(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n WIFIHAL_FactoryReset ----->Entry\n");
    int returnValue;
    char details[200] = {'\0'};
    char output[1000] = {'\0'};
    char methodName[50] = {'\0'};
    strcpy(methodName, req["methodName"].asCString());
    if(strstr(methodName, "Reset")||strstr(methodName, "ResetRadios"))
    {
        returnValue = ssp_WIFIHALFactoryReset(methodName);
	if(0 == returnValue)
        {
            sprintf(details, "%s operation success", methodName);
            response["result"]="SUCCESS";
            response["details"]=details;
            return;
        }
        else
        {
            sprintf(details, "%s operation failed", methodName);
            response["result"]="FAILURE";
            response["details"]=details;
            DEBUG_PRINT(DEBUG_TRACE,"\n WiFiCallMethodForFactoryReset --->Error in execution\n");
            return;
	}
    }
    else
        return;
    DEBUG_PRINT(DEBUG_TRACE,"\n WIFIHAL_FactoryReset --->Exit\n");
}
/*******************************************************************************************
 *
 * Function Name        : WIFIHAL_GetOrSetSecurityRadiusSettings
 * Description          : This function invokes WiFi hal get/set api's which are
                          related to SecurityRadiusSettings()

 * @param [in] req-     : radioIndex - radio Index value of wifi
                          methodName - identifier for the hal api name
			  RadiusServerRetries - Number of retries for Radius requests
			  RadiusServerRequestTimeout - Radius request timeout in seconds after which the request must be retransmitted for the # of 
                                                       retries available
			  PMKLifetime - Default time in seconds after which a Wi-Fi client is forced to ReAuthenticate (def 8 hrs)
			  PMKCaching - Time interval in seconds after which the PMKSA (Pairwise Master Key Security Association)cache is purged (def 5min)
			  MaxAuthenticationAttempts - Indicates the # of time, a client can attempt to login with incorrect credentials.
                                                      When this limit is reached, the client is blacklisted and not allowed to attempt loging
                                                      into the network. Settings this parameter to 0 (zero) disables the blacklisting feature.
			  BlacklistTableTimeout - Time interval in seconds for which a client will continue to be blacklisted once it is marked so
			  IdentityRequestRetryInterval - Time Interval in seconds between identity requests retries. A value of 0 (zero) disables it
			  QuietPeriodAfterFailedAuthentication - The enforced quiet period (time interval) in seconds following failed authentication.
                                                                 A value of 0 (zero) disables it
 * @param [out] response - filled with SUCCESS or FAILURE based on the output status of operation
 *
 ********************************************************************************************/
void WIFIHAL::WIFIHAL_GetOrSetSecurityRadiusSettings (IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n WIFIHAL_GetOrSetSecurityRadiusSettings ----->Entry\n");

    wifiRadiusSetting radiusSetting;
    char methodName[50] = {'\0'};
    int radioIndex = 1;
    int returnValue;
    char details[500] = {'\0'};

    strcpy(methodName, req["methodName"].asCString());
    radioIndex = req["radioIndex"].asInt();
    radiusSetting.RadiusServerRetries = req["RadiusServerRetries"].asInt();
    radiusSetting.RadiusServerRequestTimeout = req["RadiusServerRequestTimeout"].asInt();
    radiusSetting.PMKLifetime = req["PMKLifetime"].asInt();
    radiusSetting.PMKCaching = req["PMKCaching"].asInt();
    radiusSetting.PMKCacheInterval = req["PMKCacheInterval"].asInt();
    radiusSetting.MaxAuthenticationAttempts = req["MaxAuthenticationAttempts"].asInt();
    radiusSetting.BlacklistTableTimeout = req["BlacklistTableTimeout"].asInt();
    radiusSetting.IdentityRequestRetryInterval = req["IdentityRequestRetryInterval"].asInt();
    radiusSetting.QuietPeriodAfterFailedAuthentication = req["QuietPeriodAfterFailedAuthentication"].asInt();

    if(!strncmp(methodName, "set",3))
    {
        DEBUG_PRINT(DEBUG_TRACE,"\n Set operation requested\n");
        printf("MethodName : %s\n",methodName);
        returnValue = ssp_WIFIHALGetOrSetSecurityRadiusSettings(radioIndex, &radiusSetting, methodName);
        if(0 == returnValue)
        {
            sprintf(details, "%s operation success", methodName);
            response["result"]="SUCCESS";
            response["details"]=details;
            return;
        }
    }
    else
    {
        DEBUG_PRINT(DEBUG_TRACE,"\n Get operation requested\n");
        printf("MethodName : %s\n",methodName);
        returnValue = ssp_WIFIHALGetOrSetSecurityRadiusSettings(radioIndex, &radiusSetting, methodName);
        if(0 == returnValue)
        {
            DEBUG_PRINT(DEBUG_TRACE,"\n output: ");
            sprintf(details, "Value returned is :RadiusServerRetries=%d,RadiusServerRequestTimeout=%d,PMKLifetime=%d,PMKCaching=%d,PMKCacheInterval=%d,MaxAuthenticationAttempts=%d,BlacklistTableTimeout=%d,IdentityRequestRetryInterval=%d,QuietPeriodAfterFailedAuthentication=%d",radiusSetting.RadiusServerRetries,radiusSetting.RadiusServerRequestTimeout,radiusSetting.PMKLifetime,radiusSetting.PMKCaching,radiusSetting.PMKCacheInterval,radiusSetting.MaxAuthenticationAttempts,radiusSetting.BlacklistTableTimeout,radiusSetting.IdentityRequestRetryInterval,radiusSetting.QuietPeriodAfterFailedAuthentication);
            response["result"]="SUCCESS";
            response["details"]=details;
            return;
        }
     }
     sprintf(details, "%s operation failed", methodName);
     response["result"]="FAILURE";
     response["details"]=details;
     DEBUG_PRINT(DEBUG_TRACE,"\n WIFIHAL_GetOrSetSecurityRadiusSettings ---->Error in execution\n");
     return;
}
/*******************************************************************************************
 *
 * Function Name        : WIFIHAL_GetSSIDTrafficStats2
 * Description          : This function invokes WiFi hal api wifi_getSSIDTrafficStats2

 * @param [in] req-     : radioIndex - radio index of the wifi
 * @param [out] response - filled with SUCCESS or FAILURE based on the output status of operation
 *
 ********************************************************************************************/
void WIFIHAL::WIFIHAL_GetSSIDTrafficStats2(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n WIFIHAL_GetSSIDTrafficStats2 ----->Entry\n");

    wifi_ssidTrafficStats2_t ssidTrafficStats2;
    int radioIndex = 1;
    int returnValue;
    char details[1000] = {'\0'};

    radioIndex = req["radioIndex"].asInt();

    returnValue = ssp_WIFIHALGetSSIDTrafficStats2(radioIndex, &ssidTrafficStats2);
    if(0 == returnValue)
    {
        sprintf(details, "Value returned is :ssid_BytesSent=%d,ssid_BytesReceived=%d,ssid_PacketsSent=%d,ssid_PacketsReceived=%d,ssid_RetransCount=%d,ssid_FailedRetransCount=%d,ssid_RetryCount=%d,ssid_MultipleRetryCount=%d,ssid_ACKFailureCount=%d,ssid_AggregatedPacketCount=%d,ssid_ErrorsSent=%d,ssid_ErrorsReceived=%d,ssid_UnicastPacketsSent=%d,ssid_UnicastPacketsReceived=%d,ssid_DiscardedPacketsSent=%d,ssid_UnicastPacketsReceived=%d,ssid_DiscardedPacketsSent%d,ssid_DiscardedPacketsReceived=%d,ssid_MulticastPacketsSent=%d,ssid_MulticastPacketsReceived=%d,ssid_BroadcastPacketsSent=%d,ssid_BroadcastPacketsRecevied=%d,ssid_UnknownPacketsReceived=%d\n",ssidTrafficStats2.ssid_BytesSent,ssidTrafficStats2.ssid_BytesReceived,ssidTrafficStats2.ssid_PacketsSent,ssidTrafficStats2.ssid_PacketsReceived,ssidTrafficStats2.ssid_RetransCount,ssidTrafficStats2.ssid_FailedRetransCount,ssidTrafficStats2.ssid_RetryCount,ssidTrafficStats2.ssid_MultipleRetryCount,ssidTrafficStats2.ssid_ACKFailureCount,ssidTrafficStats2.ssid_AggregatedPacketCount,ssidTrafficStats2.ssid_ErrorsSent,ssidTrafficStats2.ssid_ErrorsReceived,ssidTrafficStats2.ssid_UnicastPacketsSent,ssidTrafficStats2.ssid_UnicastPacketsReceived,ssidTrafficStats2.ssid_DiscardedPacketsSent,ssidTrafficStats2.ssid_UnicastPacketsReceived,ssidTrafficStats2.ssid_DiscardedPacketsSent,ssidTrafficStats2.ssid_DiscardedPacketsReceived,ssidTrafficStats2.ssid_MulticastPacketsSent,ssidTrafficStats2.ssid_MulticastPacketsReceived,ssidTrafficStats2.ssid_BroadcastPacketsSent,ssidTrafficStats2.ssid_BroadcastPacketsRecevied,ssidTrafficStats2.ssid_UnknownPacketsReceived);
        response["result"]="SUCCESS";
        response["details"]=details;
        return;
    }
    else
    {
        sprintf(details, "wifi_getSSIDTrafficStats2 operation failed");
        response["result"]="FAILURE";
        response["details"]=details;
        DEBUG_PRINT(DEBUG_TRACE,"\n WIFIHAL_GetSSIDTrafficStats2 ---->Error in execution\n");
        return;
    }
}
/*******************************************************************************************
 *
 * Function Name        : WIFIHAL_GetRadioTrafficStats2
 * Description          : This function invokes WiFi hal get api which are
                          related to wifi_getRadioTrafficStats2()

 * @param [in] req-     : NIL
 * @param [out] response - filled with SUCCESS or FAILURE based on the output status of operation
 *
 ********************************************************************************************/
void WIFIHAL::WIFIHAL_GetRadioTrafficStats2 (IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n WIFIHAL_WIFIHAL_GetRadioTrafficStats2 ----->Entry\n");
    GetRadioTrafficStats2 TrafficStats2;
    int radioIndex = 1;
    int returnValue;
    char details[1000] = {'\0'};
    radioIndex = req["radioIndex"].asInt();
    DEBUG_PRINT(DEBUG_TRACE,"\n Get operation requested\n");
    returnValue = ssp_WIFIHAL_GetRadioTrafficStats2(radioIndex, &TrafficStats2);
    if(0 == returnValue)
    {
        sprintf(details, "Value returned is :radio_BytesSent=%d,radio_BytesReceived=%d,radio_PacketsSent=%d,radio_ErrorsSent=%d,radio_PacketsReceived=%d,radio_ErrorsReceived=%d,radio_DiscardPacketsSent=%d,radio_DiscardPacketsReceived=%d,radio_PLCPErrorCount=%d,radio_FCSErrorCount=%d,radio_InvalidMACCount=%d,radio_PacketsOtherReceived=%d,radio_NoiseFloor=%d,radio_ChannelUtilization=%d,radio_ActivityFactor=%d,radio_CarrierSenseThreshold_Exceeded=%d,radio_RetransmissionMetirc=%d,radio_MaximumNoiseFloorOnChannel=%d,radio_MinimumNoiseFloorOnChannel=%d,radio_MedianNoiseFloorOnChannel=%d,radio_StatisticsStartTime=%d",TrafficStats2.radio_BytesSent,TrafficStats2.radio_BytesReceived,TrafficStats2.radio_PacketsSent,TrafficStats2.radio_ErrorsSent,TrafficStats2.radio_PacketsReceived,TrafficStats2.radio_ErrorsReceived,TrafficStats2.radio_DiscardPacketsSent,TrafficStats2.radio_DiscardPacketsReceived,TrafficStats2.radio_PLCPErrorCount,TrafficStats2.radio_FCSErrorCount,TrafficStats2.radio_InvalidMACCount,TrafficStats2.radio_PacketsOtherReceived,TrafficStats2.radio_NoiseFloor,TrafficStats2.radio_ChannelUtilization,TrafficStats2.radio_ActivityFactor,TrafficStats2.radio_CarrierSenseThreshold_Exceeded,TrafficStats2.radio_RetransmissionMetirc,TrafficStats2.radio_MaximumNoiseFloorOnChannel,TrafficStats2.radio_MinimumNoiseFloorOnChannel,TrafficStats2.radio_MedianNoiseFloorOnChannel,TrafficStats2.radio_StatisticsStartTime);
        response["result"]="SUCCESS";
        response["details"]=details;
	return;
    }
    else
    {
        sprintf(details, "wifi_getRadioTrafficStats2 operation failed");
        response["result"]="FAILURE";
        response["details"]=details;
        DEBUG_PRINT(DEBUG_TRACE,"\n WiFiCallMethodForGetRadioTrafficStats2  --->Error in execution\n");
        return;
    }
}
/*******************************************************************************************
 *
 * Function Name        : WIFIHAL_Down
 * Description          : This function invokes WiFi hal api wifi_down()

 * @param [in] req-     : NIL
 * @param [out] response - filled with SUCCESS or FAILURE based on the output status of operation
 *
 ********************************************************************************************/
void WIFIHAL::WIFIHAL_Down (IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n WIFIHAL_Down ----->Entry\n");

    int returnValue;
    char details[200] = {'\0'};
    int retValue;
    int radioIndex;
    returnValue = ssp_WIFIHALDown();
    if(0 == returnValue)
       {
            sprintf(details, "wifi_down operation success");
            response["result"]="SUCCESS";
            response["details"]=details;
            retValue = ssp_WIFIHALApplySettings(radioIndex,"wifi_down");
            if(0 == retValue)
            {
                printf("applyRadioSettings operation success\n");
                return;
            }
            else
            {
                printf("applyRadioSettings operation failed\n");
                return;
            }
       }
    else
       {
            sprintf(details, "wifi_down operation failed");
            response["result"]="FAILURE";
            response["details"]=details;
            return;
       }
    DEBUG_PRINT(DEBUG_TRACE,"\n WIFIHAL_Down --->Exit\n");
}

/*******************************************************************************************
 *
 * Function Name        : WIFIHAL_Init
 * Description          : This function invokes WiFi hal api wifi_init()

 * @param [in] req-     : NIL
 * @param [out] response - filled with SUCCESS or FAILURE based on the output status of operation
 *
 ********************************************************************************************/
void WIFIHAL::WIFIHAL_Init (IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n WIFIHAL_Init ----->Entry\n");

    int returnValue;
    char details[200] = {'\0'};

    returnValue = ssp_wifi_init();
    if(0 == returnValue)
       {
            sprintf(details, "wifi_init operation success");
            response["result"]="SUCCESS";
            response["details"]=details;
            return;
       }
    else
       {
            sprintf(details, "wifi_init operation failed");
            response["result"]="FAILURE";
            response["details"]=details;
            return;
       }
    DEBUG_PRINT(DEBUG_TRACE,"\n WIFIHAL_Init --->Exit\n");
}

/**************************************************************************
 * Function Name        : CreateObject
 * Description  : This function will be used to create a new object for the
 *                class "WIFIHAL".
*
 **************************************************************************/
extern "C" WIFIHAL* CreateObject(TcpSocketServer &ptrtcpServer)
{
    return new WIFIHAL(ptrtcpServer);
}

/**************************************************************************
 * Function Name : cleanup
 * Description   : This function will be used to clean the log details.
 *
 **************************************************************************/
bool WIFIHAL::cleanup(IN const char* szVersion)
{
    DEBUG_PRINT(DEBUG_LOG,"WIFIHAL shutting down\n");
    return TEST_SUCCESS;
}

/**************************************************************************
 * Function Name : DestroyObject
 * Description   : This function will be used to destroy the object.
 *
 **************************************************************************/
extern "C" void DestroyObject(WIFIHAL *stubobj)
{
    DEBUG_PRINT(DEBUG_LOG,"Destroying WIFIHAL object\n");
    delete stubobj;
}

