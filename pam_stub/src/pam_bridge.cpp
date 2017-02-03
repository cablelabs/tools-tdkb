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
int ssp_CosaDmlUpnpInit();
int ssp_CosaDmlDhcpInit();
int ssp_CosaDmlDnsInit();
int ssp_CosaDmlUpnpEnable(char*, int);
int ssp_CosaDmlUpnpGetState(char*);
int ssp_CosaDmlDhcpGet(char*, void*);
int ssp_CosaDmlDhcpsEnable(int);
int ssp_CosaDmlDnsGet(char*, void*);
int ssp_CosaDmlDnsEnable(char*, int);
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
    ptrAgentObj->RegisterMethod(*this,&pam::COSAPAM_UpnpEnable,"COSAPAM_UpnpEnable");
    ptrAgentObj->RegisterMethod(*this,&pam::COSAPAM_UpnpGetState,"COSAPAM_UpnpGetState");
    ptrAgentObj->RegisterMethod(*this,&pam::COSAPAM_DhcpGet,"COSAPAM_DhcpGet");
    ptrAgentObj->RegisterMethod(*this,&pam::COSAPAM_DhcpsEnable,"COSAPAM_DhcpsEnable");
    ptrAgentObj->RegisterMethod(*this,&pam::COSAPAM_DnsGet,"COSAPAM_DnsGet");
    ptrAgentObj->RegisterMethod(*this,&pam::COSAPAM_DnsEnable,"COSAPAM_DnsEnable");



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
     returnValue = ssp_CosaDmlUpnpInit();
     if(0 != returnValue)
     {
         DEBUG_PRINT(DEBUG_TRACE,"\n testmodulepre_requisites: Failed to initialize the COSA UPNP DML\n");
         return "TEST_FAILURE";
     }
     returnValue = ssp_CosaDmlDhcpInit();
     if(0 != returnValue)
     {
         DEBUG_PRINT(DEBUG_TRACE,"\n testmodulepre_requisites: Failed to initialize the COSA DHCP DML\n");
         return "TEST_FAILURE";
     }
     returnValue = ssp_CosaDmlDnsInit();
     if(0 != returnValue)
     {
         DEBUG_PRINT(DEBUG_TRACE,"\n testmodulepre_requisites: Failed to initialize the COSA DNS DML\n");
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
		    response["details"] = DataValue[0].pParamNames;
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
/*******************************************************************************************
 *
 * Function Name    : COSAPAM_UpnpEnable
 * Description      : This function will set the Upnp Enable value
 *
 * @param [in]  req - methodName :  Holds the name of the api
 * @param [in]  req - boolType : Holds whether boolvalue is 0 or 1
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/


bool pam::COSAPAM_UpnpEnable(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n COSAPAM_UpnpEnable --->Entry \n");
    int returnValue = 0;
    int boolValue = 0;
    char paramName[100] = {'\0'};

    /* Validate the input arguments */

    if(&req["Value"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }
    if(&req["MethodName"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }

    boolValue = req["Value"].asInt();
    strcpy(paramName,req["MethodName"].asCString());
    printf("paramName received as %s %d\n", paramName,boolValue);
    returnValue = ssp_CosaDmlUpnpEnable(paramName,boolValue);
    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully set the Upnp enable";
    }
    else
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully set the Upnp disable";
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n COSAPAM_UpnpEnable  --->Exit\n");
    return TEST_SUCCESS;
}
/*******************************************************************************************
 *
 * Function Name    : COSAPAM_UpnpGetState
 * Description      : This function will get the upnp state
 *
 * @param [in]  req - MethodName : Holds the names of api
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/


bool pam::COSAPAM_UpnpGetState(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n COSAPAM_UpnpDevGetIgdState --->Entry \n");

    int returnValue = 0;
    char paramName[100] = {'\0'};
    char Details[100] = {'\0'};

    /* Validate the input arguments*/
    if(&req["MethodName"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }

    strcpy(paramName,req["MethodName"].asCString());
    printf("paramName received as %s\n", paramName);

    returnValue = ssp_CosaDmlUpnpGetState(paramName);
    printf("return value is %d\n",returnValue);
    if(0 == returnValue)
    {
        sprintf(Details,"Upnp state is enabled" );
        response["result"]="SUCCESS";
        response["details"]=Details;
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Upnp state is disabled";
        DEBUG_PRINT(DEBUG_TRACE,"\n COSAPAM_UpnpGetState --->Exit\n");
        return  TEST_FAILURE;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n COSAPAM_UpnpGetState  --->Exit\n");
    return TEST_SUCCESS;
}
/*******************************************************************************************
 *
 * Function Name    : COSAPAM_DhcpGet
 * Description      : This function is used to retrieve value of DHCP get apis
 *
 * @param [in]  req - MethodName : Holds the name of api
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/
bool pam::COSAPAM_DhcpGet(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n COSAPAM_DhcpGet --->Entry \n");

    int returnValue = 0;
    CFG cf = {0};
    INFO retInfo = {0};
    int value = 0;
    char Details[200]= {'\0'};
    char paramName[100] = {'\0'};

    if(&req["MethodName"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }

    strcpy(paramName,req["MethodName"].asCString());
    printf("paramName received as %s\n", paramName);

    /* Invoke the wrapper function to get the config */
    if( !(strcmp(paramName, "DhcpcConf")) )
    {
        returnValue = ssp_CosaDmlDhcpGet(paramName,&cf);
        if(0 == returnValue)
        {
        sprintf(Details,"Interface is:%s Passthrough enable :%d Inst num retrieved is:%d Alias retrieved is: %s  Enabled or not:%d",cf.Interface,cf.PassthroughEnable,cf.InstanceNumber,cf.Alias,cf.bEnabled);
        response["result"]="SUCCESS";
        response["details"]=Details;
        }
    }
    else if( !(strcmp(paramName, "DhcpcInfo")) )
    {
        returnValue = ssp_CosaDmlDhcpGet(paramName,&retInfo);
       if(0 == returnValue)
        {
        sprintf(Details,"Status is:%d, DHCP Status:%d, Num of IPRouters:%d, Num of Dns Serves:%d\n",retInfo.Status,retInfo.DHCPStatus,retInfo.NumIPRouters,retInfo.NumDnsServers);
        response["result"]="SUCCESS";
        response["details"]=Details;
        }
    }
    else
    {
        returnValue = ssp_CosaDmlDhcpGet(paramName,&value);
       if(0 == returnValue)
        {
        sprintf(Details,"The value retrieved is: %lu", value);
        response["result"]="SUCCESS";
        response["details"]=Details;
        }
    }

    if (0 != returnValue)
    {
        response["result"]="FAILURE";
        response["details"]="Failed to retrieve the value";
        DEBUG_PRINT(DEBUG_TRACE,"\n COSAPAM_DhcpGet --->Exit\n");
        return  TEST_FAILURE;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n COSAPAM_DhcpGet --->Exit\n");
    return TEST_SUCCESS;
}
/*******************************************************************************************
 *
 * Function Name    : COSAPAM_DhcpsEnable
 * Description      : This function will set the DHCP server Enable value
 *
 * @param [in]  req - boolType : Holds whether boolvalue is 0 or 1
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/


bool pam::COSAPAM_DhcpsEnable(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n COSAPAM_DhcpsEnable --->Entry \n");
    int returnValue = 0;
    int  boolValue =0;
     /* Validate the input arguments */
    if(&req["Value"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }

    boolValue = req["Value"].asInt();

    returnValue = ssp_CosaDmlDhcpsEnable(boolValue);
    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully set the DHCP server enable";
    }
    else
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully set the DHCP server disable";
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n COSAPAM_DhcpsEnable  --->Exit\n");
    return TEST_SUCCESS;
}
/*******************************************************************************************
 *
 * Function Name    : COSAPAM_DnsGet
 * Description      : This function is used to retrieve the number of DnsClientServers in the system
 * @param [in]  req - handleType : Holds the message bus handle
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/
bool pam::COSAPAM_DnsGet(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n COSAPAM_DnsGet --->Entry \n");

    int returnValue = 0;
    int value=0;
       DNS cfg = {0};
    char Details[64] = {'\0'};
       char paramName[100] = {'\0'};
       if(&req["MethodName"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }
    strcpy(paramName,req["MethodName"].asCString());
    printf("paramName received as %s\n", paramName);

    if( !(strcmp(paramName, "DnsClientServerCfg")) )
       {
        returnValue = ssp_CosaDmlDnsGet(paramName,&cfg);
               if(0 == returnValue)
        {
        DEBUG_PRINT(DEBUG_TRACE,"\n print\n");
        sprintf(Details,"Interface is:%s Inst num retrieved is:%d Alias retrieved is: %s  Enabled or not:%d",cfg.Interface,cfg.InstanceNumber,cfg.Alias,cfg.bEnabled);
        response["result"]="SUCCESS";
        response["details"]=Details;
        }

       }
       else
       {
               returnValue = ssp_CosaDmlDnsGet(paramName,&value);
               if(0 == returnValue)
        {
        sprintf(Details,"The value retrieved is: %d", value);
        response["result"]="SUCCESS";
        response["details"]=Details;
        }

       }


     if (0 != returnValue)
    {
        response["result"]="FAILURE";
        response["details"]="Failed to retrieve the value";
        DEBUG_PRINT(DEBUG_TRACE,"\n COSAPAM_DnsGet --->Exit\n");
        return  TEST_FAILURE;
    }

    DEBUG_PRINT(DEBUG_TRACE,"\n COSAPAM_DnsGet  --->Exit\n");
    return TEST_SUCCESS;
}
/*******************************************************************************************
 *
 * Function Name    : COSAPAM_DnsEnable
 * Description      : This function will set the Dns client Enable value
 *
 * @param [in]  req - handleType : Holds the message bus handle
 * @param [in]  req - boolType : Holds whether boolvalue is 0 or 1
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/


bool pam::COSAPAM_DnsEnable(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n COSAPAM_DnsEnableClient --->Entry \n");
    int returnValue = 0;
    int boolValue = 0;
       char paramName[100] = {'\0'};

    /* Validate the input arguments */

    if(&req["Value"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }
       if(&req["MethodName"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }

    boolValue = req["Value"].asInt();
       strcpy(paramName,req["MethodName"].asCString());
    printf("paramName received as %s %d\n", paramName,boolValue);
    returnValue = ssp_CosaDmlDnsEnable(paramName,boolValue);
    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully set the Dns enable";
    }
    else
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully set the Dns disable";
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n COSAPAM_DnsEnable --->Exit\n");
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
    ptrAgentObj->UnregisterMethod("COSAPAM_UpnpEnable");
    ptrAgentObj->UnregisterMethod("COSAPAM_UpnpGetState");
    ptrAgentObj->UnregisterMethod("COSAPAM_DhcpGet");
    ptrAgentObj->UnregisterMethod("COSAPAM_DhcpsEnable");
    ptrAgentObj->UnregisterMethod("COSAPAM_DnsGet");
    ptrAgentObj->UnregisterMethod("COSAPAM_DnsEnable");

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

