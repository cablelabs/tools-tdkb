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

/*This is a constructor function for WIFIHAL class*/
WIFIHAL::WIFIHAL()
{
    DEBUG_PRINT(DEBUG_LOG,"TDK WIFIHAL Instance Created\n");
}


/***************************************************************************
 *Function name : initialize
 *Description   : Initialize Function will be used for registering the wrapper method
 *                        with the agent so that wrapper function will be used in the script
 *
 *****************************************************************************/
bool WIFIHAL::initialize(IN const char* szVersion,IN RDKTestAgent *ptrAgentObj)
{
    DEBUG_PRINT(DEBUG_TRACE,"TDK::WIFIHAL Initialize\n");
    /*Register stub function for callback*/

    ptrAgentObj->RegisterMethod(*this,&WIFIHAL::WIFIHAL_GetOrSetParamBoolValue, "WIFIHAL_GetOrSetParamBoolValue");
    ptrAgentObj->RegisterMethod(*this,&WIFIHAL::WIFIHAL_GetOrSetParamULongValue,"WIFIHAL_GetOrSetParamULongValue");
    ptrAgentObj->RegisterMethod(*this,&WIFIHAL::WIFIHAL_GetOrSetParamStringValue,"WIFIHAL_GetOrSetParamStringValue");
    ptrAgentObj->RegisterMethod(*this,&WIFIHAL::WIFIHAL_GetOrSetParamIntValue,"WIFIHAL_GetOrSetParamIntValue");
    ptrAgentObj->RegisterMethod(*this,&WIFIHAL::WIFIHAL_GetOrSetParamUIntValue,"WIFIHAL_GetOrSetParamUIntValue");
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
    return "SUCCESS";
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
bool WIFIHAL::WIFIHAL_GetOrSetParamBoolValue(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n WIFIHAL_GetOrSetParamBoolValue --->Entry\n");
    char methodName[50] = {'\0'};
    int radioIndex;
    unsigned char enable;
    int returnValue;
    char details[200] = {'\0'};
    char paramType[10] = {'\0'};

    strcpy(methodName, req["methodName"].asCString());
    radioIndex = req["radioIndex"].asInt();
    enable = req["param"].asInt();
    strcpy(paramType, req["paramType"].asCString());

    if(strstr(methodName, "set"))
    {
        returnValue = ssp_WIFIHALGetOrSetParamBoolValue(radioIndex, &enable, methodName);
        if(0 == returnValue)
        {
            sprintf(details, "%s operation success", methodName);
            response["result"]="SUCCESS";
            response["details"]=details;
            return TEST_SUCCESS;
        }
    }
    else
    {
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
            return TEST_SUCCESS;
        }
     }
     sprintf(details, "%s operation failed", methodName);
     response["result"]="FAILURE";
     response["details"]=details;
     DEBUG_PRINT(DEBUG_TRACE,"\n WiFiCallMethodForBool --->Error in execution\n");
     return  TEST_FAILURE;
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
bool WIFIHAL::WIFIHAL_GetOrSetParamULongValue(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n WIFIHAL_GetOrSetParamULongValue------>Entry\n");
    char methodName[50] = {'\0'};
    int radioIndex = 1;
    unsigned long uLongVar = 1;
    int returnValue;
    char details[200] = {'\0'};
    char paramType[10] = {'\0'};

    strcpy(methodName, req["methodName"].asCString());
    radioIndex = req["radioIndex"].asInt();
    uLongVar = (unsigned long)req["param"].asLargestUInt();
    strcpy(paramType, req["paramType"].asCString());

    if(strstr(methodName, "set"))
    {
        returnValue = ssp_WIFIHALGetOrSetParamULongValue(radioIndex, &uLongVar, methodName);
        if(0 == returnValue)
        {
            sprintf(details, "%s operation success", methodName);
            response["result"]="SUCCESS";
            response["details"]=details;
           return TEST_SUCCESS;
        }
    }
    else
    {
       //paramType is set as NULL for negative test scenarios, for NULL pointer checks
       if(strcmp(paramType, "NULL"))
           returnValue = ssp_WIFIHALGetOrSetParamULongValue(radioIndex, &uLongVar, methodName);
       else
           returnValue = ssp_WIFIHALGetOrSetParamULongValue(radioIndex, NULL, methodName);
       if(0 == returnValue)
        {
            DEBUG_PRINT(DEBUG_TRACE,"\n output: %lu\n",uLongVar);
            sprintf(details, "Value returned is :%lu", uLongVar);
            response["result"]="SUCCESS";
            response["details"]=details;
            return TEST_SUCCESS;
        }
     }
     sprintf(details, "%s operation failed", methodName);
     response["result"]="FAILURE";
     response["details"]=details;
     DEBUG_PRINT(DEBUG_TRACE,"\n WiFiCallMethodForULong --->Error in execution\n");
     return  TEST_FAILURE;
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
bool WIFIHAL::WIFIHAL_GetOrSetParamStringValue(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n WIFIHAL_GetOrSetParamStringValue----->Entry\n");
    char methodName[50] = {'\0'};
    int radioIndex = 1;
    char output[200] = {'\0'};
    int returnValue;
    char details[200] = {'\0'};
    char paramType[10] = {'\0'};

    strcpy(methodName, req["methodName"].asCString());
    radioIndex = req["radioIndex"].asInt();
    strcpy(paramType, req["paramType"].asCString());

    //paramType is set as NULL for negative test scenarios, for NULL pointer checks
    if(strcmp(paramType, "NULL"))
        returnValue = ssp_WIFIHALGetOrSetParamStringValue(radioIndex, output, methodName);
    else
        returnValue = ssp_WIFIHALGetOrSetParamStringValue(radioIndex, NULL, methodName);
    strcpy(paramType, req["paramType"].asCString());

    if(0 == returnValue)
    {
        DEBUG_PRINT(DEBUG_TRACE,"\n output: %s\n",output);
        sprintf(details, "Value returned is :%s", output);
        response["result"]="SUCCESS";
        response["details"]=details;
        return TEST_SUCCESS;
    }
    else
    {
        sprintf(details, "%s operation failed", methodName);
        response["result"]="FAILURE";
        response["details"]=details;
        DEBUG_PRINT(DEBUG_TRACE,"\n WiFiCallMethodForULong --->Error in execution\n");
        return  TEST_FAILURE;
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
bool WIFIHAL::WIFIHAL_GetOrSetParamIntValue(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n WIFIHAL_GetOrSetParamIntValue----->Entry\n");
    char methodName[50] = {'\0'};
    int radioIndex = 1;
    int intParam;
    int returnValue;
    char details[200] = {'\0'};
    char paramType[10] = {'\0'};

    strcpy(methodName, req["methodName"].asCString());
    radioIndex = req["radioIndex"].asInt();
    strcpy(paramType, req["paramType"].asCString());

    //paramType is set as NULL for negative test scenarios, for NULL pointer checks
    if(strcmp(paramType, "NULL"))
        returnValue = ssp_WIFIHALGetOrSetParamIntValue(radioIndex, &intParam, methodName);
    else
        returnValue = ssp_WIFIHALGetOrSetParamIntValue(radioIndex, NULL, methodName);

    if(0 == returnValue)
    {
        DEBUG_PRINT(DEBUG_TRACE,"\n output: %d\n",intParam);
        sprintf(details, "Value returned is :%d", intParam);
        response["result"]="SUCCESS";
        response["details"]=details;
        return TEST_SUCCESS;
    }
    else
    {
        sprintf(details, "%s operation failed", methodName);
        response["result"]="FAILURE";
        response["details"]=details;
        DEBUG_PRINT(DEBUG_TRACE,"\n WiFiCallMethodForInt --->Error in execution\n");
        return  TEST_FAILURE;
    }
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
bool WIFIHAL::WIFIHAL_GetOrSetParamUIntValue (IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n WIFIHAL_GetOrSetParamUIntValue----->Entry\n");

    char methodName[50] = {'\0'};
    int radioIndex = 1;
    unsigned int uintParam;
    int returnValue;
    char details[200] = {'\0'};
    char paramType[10] = {'\0'};

    strcpy(methodName, req["methodName"].asCString());
    radioIndex = req["radioIndex"].asInt();
    strcpy(paramType, req["paramType"].asCString());

    //paramType is set as NULL for negative test scenarios, for NULL pointer checks
    if(strcmp(paramType, "NULL"))
        returnValue = ssp_WIFIHALGetOrSetParamUIntValue(radioIndex, &uintParam, methodName);
    else
        returnValue = ssp_WIFIHALGetOrSetParamUIntValue(radioIndex, NULL, methodName);

    if(0 == returnValue)
    {
        DEBUG_PRINT(DEBUG_TRACE,"\n output: %d\n",uintParam);
        sprintf(details, "Value returned is :%d", uintParam);
        response["result"]="SUCCESS";
        response["details"]=details;
        return TEST_SUCCESS;
    }
    else
    {
        sprintf(details, "%s operation failed", methodName);
        response["result"]="FAILURE";
        response["details"]=details;
        DEBUG_PRINT(DEBUG_TRACE,"\n WiFiCallMethodForUInt --->Error in execution\n");
        return  TEST_FAILURE;
    }
}
/**************************************************************************
 * Function Name        : CreateObject
 * Description  : This function will be used to create a new object for the
 *                class "WIFIHAL".
*
 **************************************************************************/
extern "C" WIFIHAL* CreateObject()
{
    return new WIFIHAL();
}

/**************************************************************************
 * Function Name : cleanup
 * Description   : This function will be used to clean the log details.
 *
 **************************************************************************/
bool WIFIHAL::cleanup(IN const char* szVersion,IN RDKTestAgent *ptrAgentObj)
{
    DEBUG_PRINT(DEBUG_LOG,"WIFIHAL shutting down\n");
    if(ptrAgentObj==NULL)
    {
        return TEST_FAILURE;
    }
    /*unRegister stub function for callback*/
    ptrAgentObj->UnregisterMethod("WIFIHAL_GetOrSetParamBoolValue");
    ptrAgentObj->UnregisterMethod("WIFIHAL_GetOrSetParamULongValue");
    ptrAgentObj->UnregisterMethod("WIFIHAL_GetOrSetParamStringValue");
    ptrAgentObj->UnregisterMethod("WIFIHAL_GetOrSetParamIntValue");
    ptrAgentObj->UnregisterMethod("WIFIHAL_GetOrSetParamUIntValue");
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

