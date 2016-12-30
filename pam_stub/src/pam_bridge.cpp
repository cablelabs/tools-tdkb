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

#include "pam.h"
#include "ssp_tdk_wrp.h"

/* To provide external linkage to C Functions defined in TDKB Component folder */

extern "C"
{
int ssp_register(bool);
int ssp_terminate();
GETPARAMVALUES* ssp_getParameterValue(char* pParamName,int* pParamsize);
int ssp_setParameterValue(char *pParamName,char *pParamValue,char *pParamType, int commit);
int ssp_MTAAgentRestart();
int ssp_CRRestart();
int ssp_pam_Init();
GETPARAMNAMES *ssp_getParameterNames(char* pPathName,int recursive,int* pParamSize);
void free_Memory_Names(int size,GETPARAMNAMES *Freestruct);
void free_Memory_val(int size,GETPARAMVALUES *Freestruct);
void free_Memory_Attr(int size,GETPARAMATTR *Freestruct);
int ssp_pam_Bridging_GetParamUlongValue(char* paramName,unsigned long* ulongValue, char* module);
int ssp_DmlMlanInit();
int ssp_DmlMlanGetParamValue(char*, char*, unsigned long*);
int ssp_DmlEthGetParamValue(char*);
int ssp_DmlDiGetParamValue(char*, char*, unsigned long*);
};

/*This is a constructor function for pam class*/
pam::pam()
{
    DEBUG_PRINT(DEBUG_LOG,"pam Instance Created\n");
}

/***************************************************************************
 *Function name	: initialize
 *Description	: Initialize Function will be used for registering the wrapper method
 *        	  with the agent so that wrapper function will be used in the script
 *
 *****************************************************************************/

bool pam::initialize(IN const char* szVersion,IN RDKTestAgent *ptrAgentObj)
{
    DEBUG_PRINT(DEBUG_TRACE,"TDK::pam Initialize\n");
    /*Register stub function for callback*/
    ptrAgentObj->RegisterMethod(*this,&pam::pam_bridge_GetParamUlongValue,"pam_bridge_GetParamUlongValue");
    ptrAgentObj->RegisterMethod(*this,&pam::pam_GetParameterNames,"pam_GetParameterNames");
    ptrAgentObj->RegisterMethod(*this,&pam::pam_SetParameterValues,"pam_SetParameterValues");
    ptrAgentObj->RegisterMethod(*this,&pam::pam_GetParameterValues,"pam_GetParameterValues");
    ptrAgentObj->RegisterMethod(*this,&pam::pam_MTAAgentRestart,"pam_MTAAgentRestart");
    ptrAgentObj->RegisterMethod(*this,&pam::pam_CRRestart,"pam_CRRestart");
    ptrAgentObj->RegisterMethod(*this,&pam::pam_Init,"pam_Init");
    ptrAgentObj->RegisterMethod(*this,&pam::COSAPAM_DmlMlanGetParamValue, "COSAPAM_DmlMlanGetParamValue");
    ptrAgentObj->RegisterMethod(*this,&pam::COSAPAM_DmlEthGetParamValue, "COSAPAM_DmlEthGetParamValue");
    ptrAgentObj->RegisterMethod(*this,&pam::COSAPAM_DmlDiGetParamValue, "COSAPAM_DmlDiGetParamValue");


    return TEST_SUCCESS;
}

/***************************************************************************
 *Function name : testmodulepre_requisites
 *Description   : testmodulepre_requisites will  be used for setting the
 *                pre-requisites that are necessary for this component
 *
 *****************************************************************************/
std::string pam::testmodulepre_requisites()
{
    int returnValue;
    returnValue = ssp_register(1);

    if(0 != returnValue)
    {
        DEBUG_PRINT(DEBUG_TRACE,"\n testmodulepre_requisites: Failed to initialize \n");
        return "TEST_FAILURE";
    }

    returnValue = ssp_DmlMlanInit();
    if(0 != returnValue)
    {
        DEBUG_PRINT(DEBUG_TRACE,"\n testmodulepre_requisites: Failed to initialize the COSA PAM DML\n");
        return "TEST_FAILURE";
    }

    DEBUG_PRINT(DEBUG_TRACE,"\n testmodulepre_requisites:initialized the COSA PAM DML\n");

    return "SUCCESS";
}

/***************************************************************************
 *Function name : testmodulepost_requisites
 *Description   : testmodulepost_requisites will be used for resetting the
 *                pre-requisites that are set
 *
 *****************************************************************************/
bool pam::testmodulepost_requisites()
{
    DEBUG_PRINT(DEBUG_LOG,"testmodulepost_requisites() \n");
    return 0;
}

/*******************************************************************************************
 *
 * Function Name    : pam_bridge_GetParamUlongValue
 * Description      : This function is used to retrieve the value of ulong parameter
 *
 * @param [in]  req - paramName : Parameter name whose value to be retrieved
 * @param [in]  req - module : keyword of the module associated with the paramName
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/

bool pam::pam_bridge_GetParamUlongValue(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n pam_bridge_GetParamUlongValue --->Entry \n");

    int returnValue = 0;
    char paramName[MAX_PARAM_SIZE];
    char module[MAX_PARAM_SIZE];
    char ulongDetails[64] = {'\0'};
    unsigned long ulongValue = 0;

    /* Validate the input arguments */
    if(&req["paramName"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }
    if(&req["module"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }

    strcpy(paramName,req["paramName"].asCString());
    strcpy(module,req["module"].asCString());

    /* Invoke the wrapper function to get the value of ulong parameter */
    returnValue = ssp_pam_Bridging_GetParamUlongValue(paramName, &ulongValue, module);

    if(0 == returnValue)
    {
	sprintf(ulongDetails,"UlongValue retrieved for the param name is: %lu", ulongValue);
        response["result"]="SUCCESS";
        response["details"]=ulongDetails;
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to retrieve the value of ulong parameter";
        DEBUG_PRINT(DEBUG_TRACE,"\n pam_bridge_GetParamUlongValue --->Exit\n");
        return  TEST_FAILURE;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n pam_bridge_GetParamUlongValue  --->Exit\n");
    return TEST_SUCCESS;
}

/***************************************************************************
 *Function name : pam_GetParameterNames
 *Descrption    : pam Component Get Param Name API functionality checking
 *
 * @param [in]  req - ParamName : Holds the name of the parameter
 * @param [in]  req - ParamList : Holds the List of the parameter
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *****************************************************************************/
bool pam::pam_GetParameterNames(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"Inside Fucntion GetParamNames \n");
    string ParamName=req["ParamName"].asCString();
    string ParamList=req["ParamList"].asCString();
    int size=0,i=0;
    int size_ret=0;
    GETPARAMNAMES *DataValue;
    GETPARAMNAMES *DataValue1;
    DataValue=ssp_getParameterNames(&ParamName[0],1,&size_ret);
    if(NULL==DataValue)
    {
        response["result"] = "FAILURE";
        response["details"] = "Get Param Name for Parameter returned NULL";
        return TEST_FAILURE;
    }
    DataValue1=ssp_getParameterNames(&ParamList[0],0,&size);
    if(NULL==DataValue1)
    {
        printf("Get Param Name for ParameterList returned NULL\n");	
        free_Memory_Names(size_ret,DataValue);
    }
    else
    {
        for(i=0;i<size;i++)
        {	
            if(strcmp(DataValue1[i].pParamNames,DataValue[0].pParamNames)==0)
            {
                if(DataValue[0].writable==DataValue1[i].writable)
                {
                    free_Memory_Names(size,DataValue1);
                    printf("Parameter Name has been fetched successfully and it matched with parameter List\n");
                    response["result"] = "SUCCESS";
                    response["details"] = "Parameter Name has been fetched successfully and it matched with parameter List";
                    return TEST_SUCCESS;
                }
                else
                {

                    free_Memory_Names(size,DataValue1);
                    printf("Parameter attributes does not match with the parameter List\n");
                    response["result"] = "FAILURE";
                    response["details"] = "Parameter Name and its attributes does not match with the parameter List";
                    return TEST_FAILURE;
                }
            }
        }
        free_Memory_Names(size,DataValue1);	
        response["result"] = "FAILURE";
        response["details"] = "Parameter Name does not match with the paramters in paramter list";
        return TEST_FAILURE;	
    }

}

/***************************************************************************
 *Function name : pam_GetParameterValues
 *Descrption    : pamPa Component Get Param Value API functionality checking
 *
 * @param [in]  req - ParamName : Holds the name of the parameter
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *****************************************************************************/
bool pam::pam_GetParameterValues(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"Inside Function GetParamValues \n");
    int size_ret=0;
    GETPARAMVALUES *DataParamValue;

    string ParamName=req["ParamName"].asCString();
    DataParamValue=ssp_getParameterValue(&ParamName[0],&size_ret);
    if((DataParamValue == NULL))
    {
        printf("GetParamValue funtion returns NULL as o/p\n");
    }
    else
    {
        DEBUG_PRINT(DEBUG_TRACE,"Parameter Values are as :\n");
            DEBUG_PRINT(DEBUG_TRACE,"Parameter Name is %s\n",ParamName.c_str());
            DEBUG_PRINT(DEBUG_TRACE,"Value is %s",DataParamValue[0].pParamValues);
            DEBUG_PRINT(DEBUG_TRACE," Type is %d\n",DataParamValue[0].pParamType);
            response["result"] = "SUCCESS";
            response["details"] = DataParamValue[0].pParamValues;
	    free_Memory_val(size_ret,DataParamValue);
            return TEST_SUCCESS;

    }
    response["result"] = "FAILURE";
    response["details"] = "Get Param value Failure of the function";
    return TEST_FAILURE;

}

/***************************************************************************
 *Function name : pam_SetParameterValues
 *Descrption    : pamPa Component Set Param Value API functionality checking
 * @param [in]  req - ParamName : Holds the name of the parameter
 * @param [in]  req - ParamValue : Holds the value of the parameter
 * @param [in]  req - Type : Holds the Type of the parameter
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *****************************************************************************/
bool pam::pam_SetParameterValues(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"Inside Function SetParamValues \n");

    int size_ret=0,i=0,setResult=0;

    string ParamName=req["ParamName"].asCString();    
    string ParamValue=req["ParamValue"].asCString();
    string Type=req["Type"].asCString();

    GETPARAMVALUES *DataParamValue1;

    setResult=ssp_setParameterValue(&ParamName[0],&ParamValue[0],&Type[0],1);
    if(setResult==0)
    {
        DEBUG_PRINT(DEBUG_TRACE,"Parameter Values have been set.Needs to cross be checked with Get Parameter Names\n");
        DataParamValue1=ssp_getParameterValue(&ParamName[0],&size_ret);
    }
    else
    {
        response["result"] = "FAILURE";
        response["details"] = "FAILURE : Parameter value is not SET. Set returns failure";
        return TEST_FAILURE;
    }

    if((DataParamValue1== NULL))
    {
        printf("GetParamValue funtion returns NULL as output\n");
    }
    else
    {
        if(strcmp(&ParamValue[0],&DataParamValue1[i].pParamValues[0])==0)
        {
            printf("Set has been validated successfully\n");
            free_Memory_val(size_ret,DataParamValue1);
            response["result"] = "SUCCESS";
            response["details"] = "Set has been validated successfully";
            return TEST_SUCCESS;
        }
        else
        {	
            free_Memory_val(size_ret,DataParamValue1);
            printf("Parameter Value has not changed after a proper Set\n");

        }
    }

    response["result"] = "FAILURE";
    response["details"] = "FAILURE : Parameter Value has not changed after a proper Set";
    return TEST_FAILURE;
}

/*******************************************************************************************
 *
 * Function Name    : pam_CMAgentRestart
 * Description      : This function will kill the CMAgent process which is running by default
 *                    and check if the process has restarted after kill.
 *
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/

bool pam::pam_MTAAgentRestart(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n pam_MTAAgentRestart --->Entry \n");

    int returnValue = 0;

    returnValue = ssp_MTAAgentRestart();
    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully restarted the MTAAgent after killing\n";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to restart the MTAAgent after being killed\n";
        DEBUG_PRINT(DEBUG_TRACE,"\n pam_MTAAgentRestart --->Exit\n");
        return  TEST_FAILURE;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n pam_MTAAgentRestart  --->Exit\n");
    return TEST_SUCCESS;

}

/*******************************************************************************************
 *
 * Function Name    : pam_CRRestart
 * Description      : This function will kill the CR process which is running by default
 *                    and check if the system has restarted after kill.
 *
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/

bool pam::pam_CRRestart(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n pam_CRRestart --->Entry \n");

    int returnValue = 0;

    returnValue = ssp_CRRestart();
    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully rebooted the system after CR is killed\n";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to reboot the system after CR being killed\n";
        DEBUG_PRINT(DEBUG_TRACE,"\n pam_CRRestart --->Exit\n");
        return  TEST_FAILURE;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n pam_CRRestart  --->Exit\n");
    return TEST_SUCCESS;

}

/***************************************************************************
 *Function name : COSAPAM_DmlMlanGetParamValue
 *Descrption    : Invokes the get APIs of multi lan
 * @param [in]  req - MethodName : Holds the name of the get api
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *****************************************************************************/
bool pam::COSAPAM_DmlMlanGetParamValue(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n pam_GetPrimaryLanIpIf --->Entry \n");

    int returnValue = 0;
    char pValue[100] = {'\0'};
    char paramName[100] = {'\0'};
    unsigned long size = sizeof(pValue);
    char details[100] = {'\0'};

    if(&req["MethodName"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }

    strcpy(paramName,req["MethodName"].asCString());
    printf("paramName received as %s\n", paramName);
    returnValue = ssp_DmlMlanGetParamValue(paramName, pValue, &size);
    if(0 == returnValue)
    {
       sprintf(details, "value: %s size: %lu", pValue, size);
        response["result"]="SUCCESS";
        response["details"]=details;
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to get value";
        DEBUG_PRINT(DEBUG_TRACE,"\n pam_GetParamValue --->Exit\n");
        return  TEST_FAILURE;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n pam_GetParamValue ---->Exit\n");
    return TEST_SUCCESS;
}

/***************************************************************************
 *Function name : COSAPAM_DmlEthGetParamValue
 *Descrption    : Invokes the get APIs of ethernet port's attributes
 * @param [in]  req - MethodName : Holds the name of the get api
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *****************************************************************************/
bool pam::COSAPAM_DmlEthGetParamValue(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n pam_GetPrimaryLanIpIf --->Entry \n");

    int returnValue = 0;
    char paramName[100] = {'\0'};

    if(&req["MethodName"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }

    strcpy(paramName,req["MethodName"].asCString());
    printf("paramName received as %s\n", paramName);
    returnValue = ssp_DmlEthGetParamValue(paramName);
    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="successfully received";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to get value";
        DEBUG_PRINT(DEBUG_TRACE,"\n pam_GetParamValue --->Exit\n");
        return  TEST_FAILURE;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n pam_GetParamValue ---->Exit\n");
    return TEST_SUCCESS;
}


/***************************************************************************
 *Function name : COSAPAM_DmlDiGetParamValue
 *Descrption    : Invokes the get APIs of device info attributes
 * @param [in]  req - MethodName : Holds the name of the get api
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *****************************************************************************/
bool pam::COSAPAM_DmlDiGetParamValue(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n pam_GetPrimaryLanIpIf --->Entry \n");

    int returnValue = 0;
    char pValue[100] = {'\0'};
    char paramName[100] = {'\0'};
    unsigned long size = 0;
    char details[100] = {'\0'};

    if(&req["MethodName"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }

    strcpy(paramName,req["MethodName"].asCString());
    printf("paramName received as %s\n", paramName);
    returnValue = ssp_DmlDiGetParamValue(paramName, pValue, &size);
    if(0 == returnValue)
    {
       sprintf(details, "value: %s size: %lu", pValue, size);
        response["result"]="SUCCESS";
        response["details"]=details;
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to get value";
        DEBUG_PRINT(DEBUG_TRACE,"\n pam_GetParamValue --->Exit\n");
        return  TEST_FAILURE;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n pam_GetParamValue ---->Exit\n");
    return TEST_SUCCESS;
}

/**************************************************************************
 * Function Name	: CreateObject
 * Description	: This function will be used to create a new object for the
 *	                class "pam".
 *
 **************************************************************************/

extern "C" pam* CreateObject()
{
    return new pam();
}

/**************************************************************************
 * Function Name : cleanup
 * Description   : This function will be used to clean the log details.
 *
 **************************************************************************/

bool pam::cleanup(IN const char* szVersion,IN RDKTestAgent *ptrAgentObj)
{
    DEBUG_PRINT(DEBUG_LOG,"pam shutting down\n");
    if(ptrAgentObj==NULL)
    {
        return TEST_FAILURE;
    }

    /*unRegister stub function for callback*/
    ptrAgentObj->UnregisterMethod("pam_bridge_GetParamUlongValue");
    ptrAgentObj->UnregisterMethod("pam_SetParameterValues");
    ptrAgentObj->UnregisterMethod("pam_GetParameterValues");
    ptrAgentObj->UnregisterMethod("pam_MTAAgentRestart");
    ptrAgentObj->UnregisterMethod("pam_CRRestart");
    ptrAgentObj->UnregisterMethod("pam_GetParameterNames");
    ptrAgentObj->UnregisterMethod("pam_Init");
    ptrAgentObj->UnregisterMethod("COSAPAM_DmlMlanGetParamValue");
    ptrAgentObj->UnregisterMethod("COSAPAM_DmlEthGetParamValue");
    ptrAgentObj->UnregisterMethod("COSAPAM_DmlDiGetParamValue");

    return TEST_SUCCESS;
}

/**************************************************************************
 * Function Name : DestroyObject
 * Description   : This function will be used to destroy the object.
 *
 **************************************************************************/
extern "C" void DestroyObject(pam *stubobj)
{
    DEBUG_PRINT(DEBUG_LOG,"Destroying pam object\n");
    delete stubobj;
}

/*******************************************************************************************
 *
 * Function Name    : pam_Init()
 * Description      : This function will initialise pam
 *
 *
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/

bool pam::pam_Init(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n pam_Init --->Entry \n");

    int returnValue = 0;
    returnValue = ssp_pam_Init();
    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully initiated pam module\n";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to initialise pam module\n";
        DEBUG_PRINT(DEBUG_TRACE,"\n pam_Init --->Exit\n");
        return  TEST_FAILURE;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n pam_Init  --->Exit\n");
    return TEST_SUCCESS;

}

