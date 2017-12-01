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

#include "CosaMTA.h"
#include "ssp_tdk_wrp.h"

/* To provide external linkage to C Functions defined in TDKB Component folder */

extern "C"
{
    int ssp_register(bool);
    int ssp_CosaDmlMtaGetResetCount(int handleType, int bufferType, char *pResetType, unsigned long* ResetCount);
    int ssp_CosaDmlMTAGetDHCPInfo(int handleType, int bufferType, void* DHCPInfo);
    int ssp_CosaDmlMTATriggerDiagnostics();
    
    int ssp_CosaDmlMtaBatteryGetInfo(int handleType, int bufferType, char* BatteryInfo);
    int ssp_CosaDmlMtaBatteryGetStatus(int handleType, int bufferType, char* BatteryStatus);
    int ssp_CosaDmlMtaBatteryGetPowerStatus(int handleType, int bufferType, char* Power);
    int ssp_CosaDmlMtaLineTableGetNumberOfEntries(int handleType, int *Num);
    int ssp_CosaDmlMtaLineTableGetEntry(int handleType, int bufferType, unsigned long* TableEntry);
    
    int ssp_CosaDmlMTAGetServiceClass(int handleType, void* SerClass);
    int ssp_CosaDmlMTADectGetEnable(int handleType,int Value);
    int ssp_CosaDmlMTADectSetEnable(int handleType,int Value);
    int ssp_CosaDmlMTADectGetRegistrationMode(int handleType,int Value);
    int ssp_CosaDmlMTADectSetRegistrationMode(int handleType,int Value);
    
    int ssp_CosaDmlMTAGetDect(int handleType,int bufferType, void* DectInfo);
    int ssp_CosaDmlMTAGetDectPIN(int handleType,int bufferType,char *pin);
    int ssp_CosaDmlMTASetDectPIN(int handleType,int bufferType, char *pin);
    int ssp_CosaDmlMTAGetDSXLogEnable(int handleType,int Value, int *Bool);
    
    int ssp_CosaDmlMTASetDSXLogEnable(int handleType,int Value);
    int ssp_CosaDmlMTAClearDSXLog(int handleType,int Value);
    int ssp_CosaDmlMTAGetCallSignallingLogEnable(int handleType,int Value,int *Bool);
    int ssp_CosaDmlMTASetCallSignallingLogEnable(int handleType,int Value);
    int ssp_CosaDmlMTAClearCallSignallingLog(int handleType,int Value);
    int ssp_CosaDmlMtaBatteryGetNumberofCycles(int handleType, unsigned long* Num);
    int ssp_CosaDmlMtaBatteryGetRemainingTime(int handleType, unsigned long* Num);
    int ssp_CosaDmlMtaBatteryGetLife(int handleType, int bufferType, char *Life);
    int ssp_CosaDmlMtaBatteryGetCondition(int handleType, int bufferType, char *Cond);
    int ssp_terminate();
    int ssp_CosaDmlMtaInit(void);
};

/***************************************************************************
 *Function name : initialize
 *Description  : Initialize Function will be used for registering the wrapper method 
 *          with the agent so that wrapper function will be used in the script
 *             
 *****************************************************************************/ 

bool CosaMTA::initialize(IN const char* szVersion)
{
    DEBUG_PRINT(DEBUG_TRACE,"TDK::CosaMTA Initialize\n");
    return TEST_SUCCESS;
}

/***************************************************************************
 *Function name : testmodulepre_requisites
 *Description   : testmodulepre_requisites will  be used for setting the
 *                pre-requisites that are necessary for this component
 *
 *****************************************************************************/
std::string CosaMTA::testmodulepre_requisites()
{
    int returnValue;
    returnValue = ssp_register(1);

    if(0 != returnValue)
    {
        DEBUG_PRINT(DEBUG_TRACE,"\n testmodulepre_requisites: Failed to initialize \n");
        return "TEST_FAILURE";
    }

    returnValue = ssp_CosaDmlMtaInit();
    if(0 != returnValue)
    {
        DEBUG_PRINT(DEBUG_TRACE,"\n testmodulepre_requisites: Failed to initialize the COSA MTA DML\n");
        return "TEST_FAILURE";
    }

    return "SUCCESS";
}

/***************************************************************************
 *Function name : testmodulepost_requisites
 *Description    : testmodulepost_requisites will be used for resetting the
 *                pre-requisites that are set
 *
 *****************************************************************************/
bool CosaMTA::testmodulepost_requisites()
{
    return 0;
}

/*******************************************************************************************
 *
 * Function Name    : CosaMTA_GetResetCount
 * Description      : This function is used to retrieve the reset count of MTAResetCount, LineResetCount
 *
 * @param [in]  req - handleType : Holds the message bus handle
 * @param [in]  req - bufferType: Holds whether buffer passed is valid or NULL
 * @param [in]  req - resetType: Holds whether reset type is MTAResetCount, LineResetCount or invalid
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/
void CosaMTA::CosaMTA_GetResetCount(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_GetResetCount --->Entry \n");

    int returnValue = 0;
    int handleType = 0;
    int bufferType = 0;
    char resetType[MAX_PARAM_SIZE];
    unsigned long ResetCount=0;
    char Details[64] = {'\0'};

    /* Validate the input arguments */
    if(&req["handleType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return;
    }
    if(&req["bufferType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return;
    }
    if(&req["resetType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return;
    }

    handleType = req["handleType"].asInt();
    bufferType = req["bufferType"].asInt();
    strcpy(resetType,req["resetType"].asCString());

    /* Invoke the wrapper function to get the reset count */
  returnValue = ssp_CosaDmlMtaGetResetCount(handleType,bufferType,resetType,&ResetCount);
    if(0 == returnValue)
    {
	sprintf(Details,"Reset count retrieved is: %lu", ResetCount);
        response["result"]="SUCCESS";
        response["details"]=Details;
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to retrieve the reset count";
        DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_GetResetCount --->Exit\n");
        return;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_GetResetCount  --->Exit\n");
    return;
}
/*******************************************************************************************
 *
 * Function Name    : CosaMTA_GetDHCPInfo
 * Description      : This function will retrieve the DHCP information
 *
 * @param [in]  req - handleType : Holds the message bus handle
 * @param [in]  req - bufferType : Holds whether buffer passed is valid or NULL
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/

void CosaMTA::CosaMTA_GetDHCPInfo(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_GetDHCPInfo --->Entry \n");

    int returnValue = 0;
    int handleType = 0;
    int bufferType = 0;
    void* DHCPInfo;
    char Details[64] = {'\0'};

    /* Validate the input arguments */
    if(&req["handleType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return;
    }

    if(&req["bufferType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return;
    }

    handleType = req["handleType"].asInt();
    bufferType = req["bufferType"].asInt();
    returnValue = ssp_CosaDmlMTAGetDHCPInfo(handleType,bufferType,DHCPInfo);
    if(0 == returnValue)
    {
	sprintf(Details,"DHCP Info retrieved is: %s", DHCPInfo);
        response["result"]="SUCCESS";
        response["details"]=Details;
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to retrieve the DHCP information";
        DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_GetDHCPInfo --->Exit\n");
        return;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_GetDHCPInfo  --->Exit\n");
    return;
}

/*******************************************************************************************
 *
 * Function Name    : CosaMTA_TriggerDiagnostics
 * Description      : This function will check the index value
 *
 * @param [in]  req - index - 0
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/

void CosaMTA::CosaMTA_Triggerdiagnostics(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_TriggerDiagnostics --->Entry \n");

    int returnValue = 0;
    returnValue = ssp_CosaDmlMTATriggerDiagnostics();
    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully checked the index value of Trigger diagnostics";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to check the index value of trigger diagnostics";
        DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_TriggerDiagnostics --->Exit\n");
        return;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_TriggerDiagnostics  --->Exit\n");
    return;
}
/*******************************************************************************************
 *
 * Function Name    : CosaMTA_BatteryGetInfo
 * Description      : This function is used to retrieve the battery info
 * @param [in]  req - handleType : Holds the message bus handle
 * @param [in]  req - bufferType: Holds whether buffer passed is valid or NULL
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/

void CosaMTA::CosaMTA_BatteryGetInfo(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_BatteryGetInfo --->Entry \n");

    int returnValue = 0;
    int handleType = 0;
    int bufferType = 0;
    char BatteryInfo[50]={'\0'};
    char Details[64] = {'\0'};


    /* Validate the input arguments */
    if(&req["handleType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return;
    }
    if(&req["bufferType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return;
    }


    handleType = req["handleType"].asInt();
    bufferType = req["bufferType"].asInt();


    returnValue = ssp_CosaDmlMtaBatteryGetInfo(handleType,bufferType,BatteryInfo);
    if(0 == returnValue)
    {
	sprintf(Details,"Battery Info is retrieved is: %s", BatteryInfo);
        response["result"]="SUCCESS";
        response["details"]=Details;
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to retrieve the Battery info";
        DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_BatteryGetInfo --->Exit\n");
        return;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_GetResetCount  --->Exit\n");
    return;
}

/*******************************************************************************************
 *
 * Function Name    : CosaMTA_BatteryGetStatus
 * Description      : This function is used to retrieve the battery status
 * @param [in]  req - handleType : Holds the message bus handle
 * @param [in]  req - bufferType: Holds whether buffer passed is valid or NULL
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/
void CosaMTA::CosaMTA_BatteryGetStatus(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_BatteryGetStatus --->Entry \n");

    int returnValue = 0;
    int handleType = 0;
    int bufferType = 0;
    char BatteryStatus[50];
    char Details[64] = {'\0'};

    // Validate the input arguments
    if(&req["handleType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return;
    }
    if(&req["bufferType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return;
    }
  
    handleType = req["handleType"].asInt();
    bufferType = req["bufferType"].asInt();
    
    returnValue = ssp_CosaDmlMtaBatteryGetStatus(handleType,bufferType,BatteryStatus);
    if(0 == returnValue)
    {
	sprintf(Details,"Battery Status retrieved is: %s", BatteryStatus);
        response["result"]="SUCCESS";
        response["details"]=Details;
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to retrieve the Battery Status";
        DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_BatteryGetStatus --->Exit\n");
        return;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_BatteryGetStatus  --->Exit\n");
    return;
}



/*******************************************************************************************
 *
 * Function Name    : CosaMTA_BatteryGetPowerStatus
 * Description      : This function is used to retrieve the battery power status
 * @param [in]  req - handleType : Holds the message bus handle
 * @param [in]  req - bufferType: Holds whether buffer passed is valid or NULL
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/

void CosaMTA::CosaMTA_BatteryGetPowerStatus(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_BatteryGetPowerStatus --->Entry \n");

    int returnValue = 0;
    int handleType = 0;
    int bufferType = 0;
    char Power[20];
    char Details[64] = {'\0'};
   

    // Validate the input arguments
    if(&req["handleType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return;
    }
    if(&req["bufferType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return;
    }
    handleType = req["handleType"].asInt();
    bufferType = req["bufferType"].asInt();
    returnValue = ssp_CosaDmlMtaBatteryGetPowerStatus(handleType,bufferType,Power);
    if(0 == returnValue)
    {
	sprintf(Details,"Power Status retrieved is: %s",Power);
        response["result"]="SUCCESS";
        response["details"]=Details;
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to retrieve the battery power status";
        DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_BatteryGetPowerStatus --->Exit\n");
        return;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_BatteryGetPowerStatus  --->Exit\n");
    return;
}

/*******************************************************************************************
 *
 * Function Name    : CosaMTA_LineTableGetNumberOfEntries
 * Description      : This function is used to retrieve the number of entries in line table
 * @param [in]  req - handleType : Holds the message bus handle
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/
void CosaMTA::CosaMTA_LineTableGetNumberOfEntries(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_LineTableGetNumberOfEntries --->Entry \n");

    int returnValue = 0;
    int handleType = 0;
    int Num=0;
    char Details[64] = {'\0'};

    // Validate the input arguments
    if(&req["handleType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return;
    }
    handleType = req["handleType"].asInt();
    returnValue = ssp_CosaDmlMtaLineTableGetNumberOfEntries(handleType, &Num);
    
    if(0 == returnValue)
    {
	sprintf(Details,"No of Line table entries retrieved is: %lu", Num);
        response["result"]="SUCCESS";
        response["details"]=Details;
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to retrieve the Line Table Entries";
        DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_LineTableGetNumberOfEntries --->Exit\n");
        return;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_LineTableGetNumberOfEntries  --->Exit\n");
    return;
}

/*******************************************************************************************
 *
 * Function Name    : CosaMTA_LineTableGetEntry
 * Description      : This function is used to retrieve the number of entries in line table
 * @param [in]  req - handleType : Holds the message bus handle
 * @param [in]  req - bufferType : Holds whether buffer passed is valid or NULL
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/

void CosaMTA::CosaMTA_LineTableGetEntry(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_LineTableGetEntry --->Entry \n");

    int returnValue = 0;
    int handleType = 0;
    int bufferType = 0;
    unsigned long TableEntry=0;
    char Details[64] = {'\0'};
    

    // Validate the input arguments
    if(&req["handleType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return;
    }
    if(&req["bufferType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return;
    }
    handleType = req["handleType"].asInt();
    bufferType = req["bufferType"].asInt();
    returnValue = ssp_CosaDmlMtaLineTableGetEntry(handleType, bufferType, &TableEntry);
    if(0 == returnValue)
    {
	sprintf(Details,"TableEntry retrieved is: %lu", TableEntry);
        response["result"]="SUCCESS";
        response["details"]=Details;
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to retrieve the Line Table Entries";
        DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_LineTableGetEntry --->Exit\n");
        return;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_LineTableGetEntry  --->Exit\n");
    return;
}

/*******************************************************************************************
 *
 * Function Name    : CosaMTA_GetServiceClass
 * Description      : This function will get the service class
 *
 * @param [in]  req - handleType : Holds the message bus handle
 * @param [in]  req - bufferType : Holds whether buffer passed is valid or NULL
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/


void CosaMTA::CosaMTA_GetServiceClass(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_GetServiceClass --->Entry \n");

    int returnValue = 0;
    int handleType = 0;
    void *SerClass;
    char Details[64] = {'\0'};

    /* Validate the input arguments */
    if(&req["handleType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return;
    }

    handleType = req["handleType"].asInt();

    returnValue = ssp_CosaDmlMTAGetServiceClass(handleType, SerClass);
    if(0 == returnValue)
    {
	sprintf(Details,"Service Class is retrieved is: %s", SerClass);
        response["result"]="SUCCESS";
        response["details"]=Details;
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to retrieve the Service class";
        DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_GetServiceClass --->Exit\n");
        return;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_GetServiceClass  --->Exit\n");
    return;
}

/*******************************************************************************************
 *
 * Function Name    : CosaMTA_DectGetEnable
 * Description      : This function will get the dect value
 *
 * @param [in]  req - handleType : Holds the message bus handle
 * @param [in]  req - boolValue : Holds whether the value is 0 or 1
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/


void CosaMTA::CosaMTA_DectGetEnable(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_DectGetEnable --->Entry \n");

    int returnValue = 0;
    int handleType = 0;
    int boolValue = 0;
    char Details[64] = {'\0'};

    /* Validate the input arguments */
    if(&req["handleType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return;
    }

    if(&req["boolValue"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return;
    }

    handleType = req["handleType"].asInt();
    boolValue = req["boolValue"].asInt();

    returnValue = ssp_CosaDmlMTADectGetEnable(handleType,boolValue);
    printf("return value is %d\n",returnValue);
    if(0 == returnValue)
    {
	sprintf(Details,"Enable value of Dect is :%d",returnValue);
        response["result"]="SUCCESS";
        response["details"]=Details;
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to retrieve the Enable value of Dect";
        DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_DectGetEnable --->Exit\n");
        return;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_DectGetEnable  --->Exit\n");
    return;
}

/*******************************************************************************************
 *
 * Function Name    : CosaMTA_DectSetEnable
 * Description      : This function will set the Dect Enable value
 *
 * @param [in]  req - handleType : Holds the message bus handle
 * @param [in]  req - boolType : Holds whether boolvalue is 0 or 1
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/


void CosaMTA::CosaMTA_DectSetEnable(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_DectSetEnable --->Entry \n");

    int returnValue = 0;
    int handleType = 0;
    int boolValue = 0;

    /* Validate the input arguments */
    if(&req["handleType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return;
    }

    if(&req["boolValue"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return;
    }

    handleType = req["handleType"].asInt();
    boolValue = req["boolValue"].asInt();

    returnValue = ssp_CosaDmlMTADectSetEnable(handleType,boolValue);
    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully set the Dect enable";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to set the Dect enable";
        DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_DectSetEnable --->Exit\n");
        return;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_DectSetEnable  --->Exit\n");
    return;
}

/*******************************************************************************************
 *
 * Function Name    : CosaMTA_DectGetRegistrationMode
 * Description      : This function will get the dect registration mode
 *
 * @param [in]  req - handleType : Holds the message bus handle
 * @param [in]  req - boolValue : Holds whether boolvalue as 0 or 1
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/


void CosaMTA::CosaMTA_DectGetRegistrationMode(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_DectGetRegistrationMode --->Entry \n");

    int returnValue = 0;
    int handleType = 0;
    int boolValue = 0;
    char Details[64]={'\0'};

    /* Validate the input arguments */
    if(&req["handleType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return;
    }

    if(&req["boolValue"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return;
    }

    handleType = req["handleType"].asInt();
    boolValue    = req["boolValue"].asInt();

    returnValue = ssp_CosaDmlMTADectGetRegistrationMode(handleType,boolValue);
    if(0 == returnValue)
    {
	sprintf(Details,"Registration mode is :%d",returnValue);
        response["result"]="SUCCESS";
        response["details"]=Details;
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to retrieve the dect registration mode";
        DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_DectGetRegistrationMode --->Exit\n");
        return;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_DectGetRegistrationMode  --->Exit\n");
    return;
}

/*******************************************************************************************
 *
 * Function Name    : CosaMTA_DectSetRegistrationMode
 * Description      : This function will set the dect registration mode
 *
 * @param [in]  req - handleType : Holds the message bus handle
 * @param [in]  req - boolValue : Holds the boolValue as 0 or 1
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/


void CosaMTA::CosaMTA_DectSetRegistrationMode(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_DectSetRegistrationMode --->Entry \n");

    int returnValue = 0;
    int handleType = 0;
    int boolValue = 0;

    /* Validate the input arguments */
    if(&req["handleType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return;
    }

    if(&req["boolValue"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return;
    }

    handleType = req["handleType"].asInt();
    boolValue = req["boolValue"].asInt();

    returnValue = ssp_CosaDmlMTADectSetRegistrationMode(handleType,boolValue);
    printf("return value is %d\n",returnValue);
    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully set the dect registration mode";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to set the dect registration mode";
        DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_DectSetRegistrationMode --->Exit\n");
        return;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_DectSetRegistrationMode  --->Exit\n");
    return;
}

/*******************************************************************************************
 *
 * Function Name    : CosaMTA_GetDect
 * Description      : This function will get the Dect value
 *
 * @param [in]  req - handleType : Holds the message bus handle
 * @param [in]  req - bufferType : Holds whether buffer passed is valid or NULL
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/


void CosaMTA::CosaMTA_GetDect(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_GetDect --->Entry \n");

    int returnValue = 0;
    int handleType = 0;
    int bufferType = 0;
    void* DectInfo;
    char Details[64] = {'\0'};

    /* Validate the input arguments */
    if(&req["handleType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return;
    }

    if(&req["bufferType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return;
    }

    handleType = req["handleType"].asInt();
    bufferType = req["bufferType"].asInt();
    printf("handleType %d\nbufferType %d\n",handleType,bufferType);

    returnValue = ssp_CosaDmlMTAGetDect(handleType,bufferType, DectInfo);
    printf("return value is %d\n",returnValue);
    if(0 == returnValue)
    {
	sprintf(Details,"Dect Info retrieved is: %s", DectInfo);
        response["result"]="SUCCESS";
        response["details"]=Details;
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to retrieve the Dect information";
        DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_GetDect --->Exit\n");
        return;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_GetDect  --->Exit\n");
    return;
}

/*******************************************************************************************
 *
 * Function Name    : CosaMTA_GetDectPIN
 * Description      : This function will get the Dect pin information
 *
 * @param [in]  req - handleType : Holds the message bus handle
 * @param [in]  req - bufferType : Holds whether buffer passed is valid or NULL
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/
void CosaMTA::CosaMTA_GetDectPIN(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_GetDectPIN --->Entry \n");

    int returnValue = 0;
    int handleType = 0;
    int bufferType = 0;
    char pin[64] = {0};
    char Details[64] = {'\0'};

    /* Validate the input arguments */
    if(&req["handleType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return;
    }

    if(&req["bufferType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return;
    }

    handleType = req["handleType"].asInt();
    bufferType = req["bufferType"].asInt();

    returnValue = ssp_CosaDmlMTAGetDectPIN(handleType,bufferType,pin);
    if(0 == returnValue)
    {
	sprintf(Details,"Dect pin retrieved is: %s",pin);
        response["result"]="SUCCESS";
        response["details"]=Details;
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to retrieve the Dect pin information";
        DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_GetDectPIN --->Exit\n");
        return;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_GetDectPIN  --->Exit\n");
    return;
}

/*******************************************************************************************
 *
 * Function Name    : CosaMTA_SetDectPIN
 * Description      : This function will set the Dect pin information
 *
 * @param [in]  req - handleType : Holds the message bus handle
 * @param [in]  req - bufferType : Holds whether buffer passed is valid or NULL
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/
void CosaMTA::CosaMTA_SetDectPIN(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_SetDectPIN --->Entry \n");

    int returnValue = 0;
    int handleType = 0;
    int bufferType = 0;
    char pin[64] = {0};

    /* Validate the input arguments */
    if(&req["handleType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return;
    }

    if(&req["bufferType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return;
    }

    if(&req["value"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return;
    }

    handleType = req["handleType"].asInt();
    bufferType = req["bufferType"].asInt();
    strcpy(pin,req["value"].asCString());

    returnValue = ssp_CosaDmlMTASetDectPIN(handleType,bufferType,pin);
    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully set the Dect pin information";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to set the Dect pin information";
        DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_SetDectPIN --->Exit\n");
        return;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_SetDectPIN  --->Exit\n");
    return;
}

/*******************************************************************************************
 *
 * Function Name    : CosaMTA_BatteryGetNumberofCycles
 * Description      : This function will retrive the number of cycles in battery
 *
 * @param [in]  req - handleType : Holds the message bus handle
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/

void CosaMTA::CosaMTA_BatteryGetNumberofCycles(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_BatteryGetNumberofCycles --->Entry \n");

    int returnValue = 0;
    int handleType = 0;
    unsigned long Num=0;
    char Details[64] = {'\0'};

    /* Validate the input arguments */
    if(&req["handleType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return;
    }


    handleType = req["handleType"].asInt();

    returnValue = ssp_CosaDmlMtaBatteryGetNumberofCycles(handleType, &Num);
    if(0 == returnValue)
    {
	sprintf(Details,"Number of cycles retrieved is: %lu", Num);
        response["result"]="SUCCESS";
        response["details"]=Details;
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to retrieve the number of cycles in battery";
        DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_BatteryGetNumberofCycles --->Exit\n");
        return;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_BatteryGetNumberofCycles  --->Exit\n");
    return;
}

/*******************************************************************************************
 *
 * Function Name    : CosaMTA_GetDSXLogEnable
 * Description      : This function will retrieve the enabled DSX log
 *
 * @param [in]  req - handleType : Holds the message bus handle
 * @param [in]  req - boolValue : Holds whether boolValue passed is 0 or 1
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/


void CosaMTA::CosaMTA_GetDSXLogEnable(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_GetDSXLogEnable --->Entry \n");

    int returnValue = 0;
    int handleType = 0;
    int boolValue = 0;
    int Bool=0;
    char Details[64] = {'\0'};

    /* Validate the input arguments */
    if(&req["handleType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return;
    }

    if(&req["boolValue"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return;
    }

    handleType = req["handleType"].asInt();
    boolValue = req["boolValue"].asInt();

    returnValue = ssp_CosaDmlMTAGetDSXLogEnable(handleType,boolValue, &Bool);
    printf("return value is %d\n",returnValue);
    if(0 == returnValue)
    {
	sprintf(Details,"DSX logs retrieved is: %d", Bool);
        response["result"]="SUCCESS";
        response["details"]=Details;
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to retrieve the enabled DSX log information";
        DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_GetDSXLogEnable --->Exit\n");
        return;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_GetDSXLogEnable  --->Exit\n");
    return;
}

/*******************************************************************************************
 *
 * Function Name    : CosaMTA_SetDSXLogEnable
 * Description      : This function will enable the DSX Log
 *
 * @param [in]  req - handleType : Holds the message bus handle
 * @param [in]  req - boolValue : Holds whether boolvalue passed is 0 or 1
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/


void CosaMTA::CosaMTA_SetDSXLogEnable(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_SetDSXLogEnable --->Entry \n");

    int returnValue = 0;
    int handleType = 0;
    int boolValue = 0;

    /* Validate the input arguments */
    if(&req["handleType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return;
    }

    if(&req["boolValue"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return;
    }

    handleType = req["handleType"].asInt();
    boolValue = req["boolValue"].asInt();

    returnValue = ssp_CosaDmlMTASetDSXLogEnable(handleType,boolValue);
    printf("return value is %d\n",returnValue);
    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully enabled the DSX Log";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to enable the DSX Log";
        DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_SetDSXLogEnable --->Exit\n");
        return;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_SetDSXLogEnable  --->Exit\n");
    return;
}

/*******************************************************************************************
 *
 * Function Name    : CosaMTA_ClearDSXLog
 * Description      : This function will clear the DSX Log
 * @param [in]  req - handleType : Holds the message bus handle
 * @param [in]  req - boolValue : Holds whether boolvalue passed is 0 or 1
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/


void CosaMTA::CosaMTA_ClearDSXLog(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_ClearDSXLog --->Entry \n");

    int returnValue = 0;
    int handleType = 0;
    int boolValue = 0;

    /* Validate the input arguments */
    if(&req["handleType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return;
    }

    if(&req["boolValue"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return;
    }

    handleType = req["handleType"].asInt();
    boolValue = req["boolValue"].asInt();

    returnValue = ssp_CosaDmlMTAClearDSXLog(handleType,boolValue);
    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully cleared the DSX Log";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to clear the DSX Log";
        DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_ClearDSXLog --->Exit\n");
        return;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_ClearDSXLog  --->Exit\n");
    return;
}

/*******************************************************************************************
 *
 * Function Name    : CosaMTA_GetCallSignallingLogEnable
 * Description      : This function will get the enable value for call signalling log
 *
 * @param [in]  req - handleType : Holds the message bus handle
 * @param [in]  req - boolValue : Holds whether boolValue passed is 0 or 1
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/


void CosaMTA::CosaMTA_GetCallSignallingLogEnable(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_GetCallSignallingLogEnable --->Entry \n");

    int returnValue = 0;
    int handleType = 0;
    int boolValue = 0;
    int Bool=0;
    char Details[64] = {'\0'};

    /* Validate the input arguments */
    if(&req["handleType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return;
    }

    if(&req["boolValue"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return;
    }

    handleType = req["handleType"].asInt();
    boolValue = req["boolValue"].asInt();

    returnValue = ssp_CosaDmlMTAGetCallSignallingLogEnable(handleType,boolValue, &Bool);
    printf("return value is %d\n",returnValue);
    if(0 == returnValue)
    {
	sprintf(Details,"Call signal log retrieved is: %d", Bool);
        response["result"]="SUCCESS";
        response["details"]=Details;
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to retrieve the enable value for call signalling log";
        DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_GetCallSignallingLogEnable --->Exit\n");
        return;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_GetCallSignallingLogEnable  --->Exit\n");
    return;
}

/*******************************************************************************************
 *
 * Function Name    : CosaMTA_SetCallSignallingLogEnable
 * Description      : This function will enable the call signalling log
 *
 * @param [in]  req - handleType : Holds the message bus handle
 * @param [in]  req - boolValue : Holds whether boolValue passed is 0 or 1
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/


void CosaMTA::CosaMTA_SetCallSignallingLogEnable(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_SetCallSignallingLogEnable --->Entry \n");

    int returnValue = 0;
    int handleType = 0;
    int boolValue = 0;

    /* Validate the input arguments */
    if(&req["handleType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return;
    }

    if(&req["Value"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return;
    }

    handleType = req["handleType"].asInt();
    boolValue = req["Value"].asInt();

    returnValue = ssp_CosaDmlMTASetCallSignallingLogEnable(handleType,boolValue);
    printf("return value is %d\n",returnValue);
    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully enabled the call signalling log";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to enable the call signalling log";
        DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_SetCallSignallingLogEnable --->Exit\n");
        return;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_SetCallSignallingLogEnable  --->Exit\n");
    return;
}

/*******************************************************************************************
 *
 * Function Name    : CosaMTA_ClearCallSignallingLog
 * Description      : This function will clear the call signalling log 
 *
 * @param [in]  req - handleType : Holds the message bus handle
 * @param [in]  req - boolvalue : Holds whether boolValue passed is 0 or 1
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/


void CosaMTA::CosaMTA_ClearCallSignallingLog(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_ClearCallSignallingLog --->Entry \n");

    int returnValue = 0;
    int handleType = 0;
    int boolValue = 0;

    /* Validate the input arguments */
    if(&req["handleType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return;
    }

    if(&req["boolValue"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return;
    }

    handleType = req["handleType"].asInt();
    boolValue = req["boolValue"].asInt();

    returnValue = ssp_CosaDmlMTAClearCallSignallingLog(handleType,boolValue);
    printf("return value is %d\n",returnValue);
    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully cleared the call signalling log";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to clear the call signalling log";
        DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_ClearCallSignallingLog --->Exit\n");
        return;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_ClearCallSignallingLog  --->Exit\n");
    return;
}


/*******************************************************************************************
 *
 * Function Name    : CosaMTA_BatteryGetRemainingTime
 * Description      : This function will get the battery Remaining time 
 *
 * @param [in]  req - handleType : Holds the message bus handle
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/

void CosaMTA::CosaMTA_BatteryGetRemainingTime(IN const Json::Value& req, OUT Json::Value& response)
{
        DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_BatteryGetRemainingTime --->Entry \n");

        int returnValue = 0;

        int handleType = 0;
	unsigned long Num=0;
	char Details[64] = {'\0'};

                    /* Validate the input arguments */

        if(&req["handleType"]==NULL)
        {
            response["result"]="FAILURE";
            response["details"]="NULL parameter as input argument";
            return;
        }


        handleType = req["handleType"].asInt();

        returnValue = ssp_CosaDmlMtaBatteryGetRemainingTime(handleType, &Num);
        if(0 == returnValue)
        {
	    sprintf(Details,"Remaining time retrieved is: %lu", Num);
            response["result"]="SUCCESS";
            response["details"]=Details;
        }
        else
        {
            response["result"]="FAILURE";
            response["details"]="Failed to retrieve the battery remaining time";
            DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_BatteryGetRemainingTime --->Exit\n");
            return;
        }
        DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_BatteryGetRemainingTime --->Exit\n");
        return;
}


/*******************************************************************************************
 *
 * Function Name    : CosaMTA_BatteryGetCondition
 * Description      : This function is used to retrieve the battery Condition
 * @param [in]  req - handleType : Holds the message bus handle
 * @param [in]  req - bufferType: Holds whether buffer passed is valid or NULL
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/

void CosaMTA::CosaMTA_BatteryGetCondition(IN const Json::Value& req, OUT Json::Value& response)
{
        DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_BatteryGetCondition --->Entry \n");

        int returnValue = 0;
        int handleType = 0;
        int bufferType = 0;
	char Cond[20];
	char Details[64] = {'\0'};

        //Validate the input arguments
            if(&req["handleType"]==NULL)
            {
                response["result"]="FAILURE";
                response["details"]="NULL parameter as input argument";
                return;
            }
        if(&req["bufferType"]==NULL)
        {
            response["result"]="FAILURE";
            response["details"]="NULL parameter as input argument";
            return;
        }

        handleType = req["handleType"].asInt();
        bufferType = req["bufferType"].asInt();

        returnValue = ssp_CosaDmlMtaBatteryGetCondition(handleType,bufferType,Cond);
        if(0 == returnValue)
        {
	    sprintf(Details,"Battery condition retrieved is: %s",Cond);
            response["result"]="SUCCESS";
            response["details"]=Details;
        }
        else
        {
            response["result"]="FAILURE";
            response["details"]="Failed to retrieve the Battery Condition";
            DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_BatteryGetCondition --->Exit\n");
            return;
        }
        DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_BatteryGetCondition  --->Exit\n");
        return;
}
                        

/*******************************************************************************************
 *
 * Function Name    : CosaMTA_BatteryGetLife
 * Description      : This function is used to retrieve the battery life
 * @param [in]  req - handleType : Holds the message bus handle
 * @param [in]  req - bufferType: Holds whether buffer passed is valid or NULL
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/

void CosaMTA::CosaMTA_BatteryGetLife(IN const Json::Value& req, OUT Json::Value& response)
{
            DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_BatteryGetLife --->Entry \n");

            int returnValue = 0;
            int handleType = 0;
            int bufferType = 0;
	    char Life[20];
	    char Details[64] = {'\0'};

          //  Validate the input arguments
                if(&req["handleType"]==NULL)
                {
                    response["result"]="FAILURE";
                    response["details"]="NULL parameter as input argument";
                    return;
                }
            if(&req["bufferType"]==NULL)
            {
                response["result"]="FAILURE";
                response["details"]="NULL parameter as input argument";
                return;
            }

            handleType = req["handleType"].asInt();
            bufferType = req["bufferType"].asInt();

           
            returnValue = ssp_CosaDmlMtaBatteryGetLife(handleType,bufferType,Life);
            if(0 == returnValue)
            {
				sprintf(Details,"Battery life retrieved is: %s",Life);
                response["result"]="SUCCESS";         
                response["details"]=Details;
            }
            else
            {                                                            
                response["result"]="FAILURE";               
                response["details"]="Failed to retrieve the Battery Life";
                DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_BatteryGetLife --->Exit\n");
                return;                  
            }               
            DEBUG_PRINT(DEBUG_TRACE,"\n CosaMTA_BatteryGetLife  --->Exit\n");
            return;                  
}



/**************************************************************************
 * Function Name    : CreateObject
 * Description : This function will be used to create a new object for the
 *          class "CosaMTA".
 *
 **************************************************************************/

extern "C" CosaMTA* CreateObject(TcpSocketServer &ptrtcpServer)
{
    return new CosaMTA(ptrtcpServer);
}

/**************************************************************************
 * Function Name : cleanup
 * Description   : This function will be used to clean the log details. 
 *
 **************************************************************************/

bool CosaMTA::cleanup(IN const char* szVersion)
{
    DEBUG_PRINT(DEBUG_LOG,"CosaMTA shutting down\n");
    return TEST_SUCCESS;
}

/**************************************************************************
 * Function Name : DestroyObject
 * Description   : This function will be used to destroy the object. 
 *
 **************************************************************************/
extern "C" void DestroyObject(CosaMTA *stubobj)
{
    DEBUG_PRINT(DEBUG_LOG,"Destroying CosaMTA object\n");
    delete stubobj;
}






