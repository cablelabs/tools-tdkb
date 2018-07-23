/*
 *If not stated otherwise in this file or this component's Licenses.txt file the
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

#include "CMHAL.h"

/***************************************************************************
 *Function name : initialize
 *Description   : Initialize Function will be used for registering the wrapper method
 *                        with the agent so that wrapper function will be used in the script
 *
 *****************************************************************************/

bool CMHAL::initialize(IN const char* szVersion)
{
    return TEST_SUCCESS;
}

/***************************************************************************
 *Function name : testmodulepre_requisites
 *Description   : testmodulepre_requisites will  be used for setting the
 *                pre-requisites that are necessary for this component
 *
 *****************************************************************************/
std::string CMHAL::testmodulepre_requisites()
{
    return "SUCCESS";
}


/***************************************************************************
 *Function name : testmodulepost_requisites
 *Description   : testmodulepost_requisites will be used for resetting the
 *                pre-requisites that are set
 *
 *****************************************************************************/
bool CMHAL::testmodulepost_requisites()
{
    DEBUG_PRINT(DEBUG_LOG,"DBG:CMHAL:testmodulepost_requisites() \n");
    return 0;
}


/*******************************************************************************************
 *
 * Function Name    : CMHAL_GetParamCharValue
 * Description      : This will get the char values
 *

 * @param [in]  req - paramName : Holds the name of api
                      paramType : Holds NULL in the case of negative scenario and empty otherwise
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/

void CMHAL::CMHAL_GetParamCharValue(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CMHAL_GetParamCharValue  --->Entry \n");

    int returnValue = 0;
    char paramName[100];
    char Details[800] = {'\0'};
    char value[700];
    char paramType[10] = {'\0'};

    /* Validate the input arguments */
    if(&req["paramName"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
	return;
    }
    strcpy(paramName,req["paramName"].asCString());
    strcpy(paramType, req["paramType"].asCString());

    //For negative scenario, "NULL" will be passed as the paramType argument
    if(strcmp(paramType, "NULL"))
        returnValue = ssp_CMHAL_GetParamCharValue(paramName,value);
    else
       returnValue = ssp_CMHAL_GetParamCharValue(paramName,NULL);
    if(0 == returnValue)
    {
       sprintf(Details,"%s", value);
       response["result"]="SUCCESS";
       response["details"]=Details;
    }
    else
    {
       response["result"]="FAILURE";
       response["details"]="Failed to get the value";
       DEBUG_PRINT(DEBUG_TRACE,"\n CMHAL_GetParamCharValue --->Exit\n");
	return;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CMHAL_GetParamCharValue --->Exit\n");
    return;
}

/*******************************************************************************************
 *
 * Function Name    : CMHAL_GetParamUlongValue
 * Description      : This will get the Ulong values
 * @param [in]  req - paramName : Holds the name of api
  		      paramType  :Holds NULL in the case of negative scenario and empty otherwise
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
*
 *******************************************************************************************/
void CMHAL::CMHAL_GetParamUlongValue(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CMHAL_GetParamUlongValue  --->Entry \n");
    int returnValue = 0;
    char paramName[100];
    char Details[64] = {'\0'};
    unsigned long value = 0;
    char paramType[10] = {'\0'};

    /* Validate the input arguments */
    if(&req["paramName"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
	return;
    }
    strcpy(paramName,req["paramName"].asCString());
    strcpy(paramType, req["paramType"].asCString());

     //For negative scenario, "NULL" will be passed as the paramType argument
    if(strcmp(paramType, "NULL"))
        returnValue = ssp_CMHAL_GetParamUlongValue(paramName,&value);
    else
       returnValue = ssp_CMHAL_GetParamUlongValue(paramName,NULL);

    if(0 == returnValue)
    {
        sprintf(Details,"%d", value);
        response["result"]="SUCCESS";
        response["details"]=Details;
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to get the value";
        DEBUG_PRINT(DEBUG_TRACE,"\n CMHAL_GetParamUlongValue --->Exit\n");
	return;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CMHAL_GetParamUlongValue --->Exit\n");
    return;
}

/*******************************************************************************************
 *
 * Function Name        : CMHAL_GetErrorCodeWords
 * Description          :This function will invoke the SSP  HAL wrapper to get the ErrorCodeWords
 *
 * @param [in] req-    : flag: To handle negative scenario
 * @param [out] response - filled with SUCCESS or FAILURE based on the output staus of operation
 *
 ********************************************************************************************/
void CMHAL::CMHAL_GetErrorCodeWords(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"Inside Function CMHAL_GetErrorCodeWords stub\n");
    int isNegativeScenario = 0;
    char details[800] = {'\0'};
    char value[800] = {'\0'};

    if(&req["flag"])
    {
        isNegativeScenario = req["flag"].asInt();
    }

    if(ssp_CMHAL_GetErrorCodeWords(value,isNegativeScenario) == 0)
        {
                sprintf(details, "Value returned successfully\n");
                DEBUG_PRINT(DEBUG_TRACE, "Successfully retrieved the ErrorCodeWords status\n");
                response["result"] = "SUCCESS";
                response["details"] = details;
                return;
        }
        else
        {
                response["result"] = "FAILURE";
                response["details"] = "CMHAL_GetErrorCodeWords function has failed.Please check logs";
                return;
        }
}

/*******************************************************************************************
 *
 * Function Name        : CMHAL_Init
 * Description          :This function will invoke the SSP  HAL wrapper to init the CM
 *
 * @param [in] req-     :ParamName : Name of the api
 * @param [out] response - filled with SUCCESS or FAILURE based on the output staus of operation
 *
 ********************************************************************************************/
void CMHAL::CMHAL_Init(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"Inside Function CMHAL_Init stub\n");
    char details[64] = {'\0'};
    char paramName[64] = {'\0'};

    strcpy(paramName,req["paramName"].asCString());

    if(ssp_CMHAL_Init(paramName) == 0)
        {
                sprintf(details, "CM  has initiated successfully\n");
                DEBUG_PRINT(DEBUG_TRACE, "Successfully initiated the CM \n");
                response["result"] = "SUCCESS";
                response["details"] = details;
                return;
        }
        else
        {
                response["result"] = "FAILURE";
                response["details"] = "CMHAL_Init function has failed.Please check logs";
                return;
        }
}

/*******************************************************************************************
 *
 * Function Name        : CMHAL_GetDocsisEventLogItems
 * Description          :This function will invoke the SSP  HAL wrapper to get the DocsisEventLogItems
 *
 * @param [in] req-    :flag- to execute negative scenarios
 * @param [out] response - filled with SUCCESS or FAILURE based on the output staus of operation
 *
 ********************************************************************************************/
void CMHAL::CMHAL_GetDocsisEventLogItems(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"Inside Function CMHAL_GetDocsisEventLogItems stub\n");
    int isNegativeScenario = 0;
    char details[120] = {'\0'};
    CMMGMT_CM_EventLogEntry_t entries[DOCSIS_EVENT_LOG_SIZE];

    if(&req["flag"])
    {
        isNegativeScenario = req["flag"].asInt();
    }

    if(ssp_CMHAL_GetDocsisEventLogItems(entries, DOCSIS_EVENT_LOG_SIZE,isNegativeScenario) == 0)
    {
        sprintf(details, "Retrieved the event log items  successfully");
        DEBUG_PRINT(DEBUG_TRACE, "Successfully retrieved the event log items\n");
        response["result"] = "SUCCESS";
        response["details"] = details;
        return;
    }
    else
    {
        response["result"] = "FAILURE";
        response["details"] = "CMHAL_GetDocsisEventLogItems function has failed.Please check logs";
        return;
    }
}


/*******************************************************************************************
 *
 * Function Name        : CMHAL_SetLEDFlashStatus
 * Description          :This function will invoke the SSP  HAL wrapper to set the LEDFlashStatus
 *
 * @param [in] req-    :LEDFlash - to enable LEDFlash status
 * @param [out] response - filled with SUCCESS or FAILURE based on the output staus of operation
 *
 ********************************************************************************************/
void CMHAL::CMHAL_SetLEDFlashStatus(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CMHAL_SetLEDFlashStatus --->Entry \n");
    int returnValue = 0;
    unsigned char* LEDFlash;
    char Details[64] = {'\0'};

    LEDFlash=(unsigned char*)req["LEDFlash"].asCString();
    returnValue = ssp_CMHAL_SetLEDFlashStatus(*LEDFlash);
    if(0 == returnValue)
    {
        sprintf(Details,"CMHAL_SetLEDFlashStatus enabled successfully");
        response["result"]="SUCCESS";
        response["details"]=Details;
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to set enable status";
        DEBUG_PRINT(DEBUG_TRACE,"\n CMHAL_SetLEDFlashStatus failed--->Exit\n");
        return;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CMHAL_SetLEDFlashStatus --->Exit\n");
    return;
}


/**************************************************************************
 * Function Name        : CreateObject
* Description  : This function will be used to create a new object for the
 *                      class "CMHAL".
*
+ **************************************************************************/

extern "C" CMHAL* CreateObject(TcpSocketServer &ptrtcpServer)
{
    return new CMHAL(ptrtcpServer);
}

/**************************************************************************
 * Function Name : cleanup
 * Description   : This function will be used to clean the log details.
 *
 **************************************************************************/

bool CMHAL::cleanup(IN const char* szVersion)
{
    DEBUG_PRINT(DEBUG_LOG,"CMHAL shutting down\n");
    return TEST_SUCCESS;
}

/**************************************************************************
 * Function Name : DestroyObject
 * Description   : This function will be used to destroy the object
 *
 **************************************************************************/
extern "C" void DestroyObject(CMHAL *stubobj)
{
    DEBUG_PRINT(DEBUG_LOG,"Destroying CMHAL object\n");
    delete stubobj;
}
