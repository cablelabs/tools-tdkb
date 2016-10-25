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
#include "CCSPMBUS_Stub.h"
#include "ssp_tdk_wrp.h"
#include "ssp_tdk_mbus_wrp.h"

/* To provide external linkage to C Functions defined in TDKB Component folder */
extern "C"
{
    /* Wrapper Functions to invoke RDKB API's */
    int ssp_register(bool);
    int ssp_terminate();
    GETPARAMVALUES* ssp_getParameterValue(char *pParamName,int *paramsize);
    int ssp_setParameterValue(char *pParamName,char *pParamValue,char *pParamType, int commit);
    GETPARAMATTR* ssp_getParameterAttr(char *pParamAttr,int *pParamAttrSize);
    int ssp_setParameterAttr(char *pParamName,char *pAttrNotify,char *pAttrAccess);
    GETPARAMNAMES* ssp_getParameterNames(char *pPathName,int recursive,int *pParamSize);
    int ssp_addTableRow(char *pObjTbl,int *pInstanceNumber);
    int ssp_deleteTableRow(char *pObjTbl);
    int ssp_setCommit(char *pObjTbl);
    int ssp_setSessionId(int priority, int sessionId);
    void free_Memory_Names(int size,GETPARAMNAMES *Freestruct);
    void free_Memory_val(int size,GETPARAMVALUES *Freestruct);
    void free_Memory_Attr(int size,GETPARAMATTR *Freestruct);

    int ssp_mbus_init(char *pCfg);
    int ssp_mbus_exit();
    int ssp_mbus_register_event(char *pEvtName);
    int ssp_mbus_unregister_event(char *pEvtName);
    int ssp_mbus_loadcfg(char *pCfg);
    int ssp_mbus_load_dmlxml(char *pCmpDmXml);
    int ssp_mbus_register_path();
    int ssp_mbus_query_status();
    int ssp_mbus_get_allocmemory();
    int ssp_mbus_get_maxmemory();
    int ssp_mbus_register_capabilities();
    int ssp_mbus_unregister_namespace();
    int ssp_mbus_unregistercomponent();
    int ssp_mbus_namespace_supportedby_component();
    int ssp_mbus_component_supporting_dynamictbl();
    int ssp_mbus_get_registered_components();
    int ssp_mbus_check_namespace_datatype();
    int ssp_mbus_dump_component_registry();
    int ssp_mbus_issystem_ready();
    int ssp_mbus_bus_check();
    int ssp_mbus_inform_end_session();
    int ssp_mbus_req_sessionid();
    int ssp_mbus_register_base();
    int ssp_mbus_getHealth(char *cmpId, char*cmpPath);
    int ssp_mbus_SendsystemReadySignal(void);

    int ssp_MBUS_Stub_cosa_wifi_init();
};

/*This is a constructor function for CCSPMBUS class*/
CCSPMBUS::CCSPMBUS()
{
    DEBUG_PRINT(DEBUG_LOG,"CCSPMBUS Instance Created\n");
}

/***************************************************************************
 *Function name	: initialize
 *Description	: Initialize Function will be used for registering the wrapper method 
 *  	  	  with the agent so that wrapper function will be used in the script
 *  		  	  
 *****************************************************************************/ 

bool CCSPMBUS::initialize(IN const char* szVersion,IN RDKTestAgent *ptrAgentObj)
{
    DEBUG_PRINT(DEBUG_TRACE,"CCSPMBUS Initialize\n");
    /*Register stub function for callback*/
    ptrAgentObj->RegisterMethod(*this,&CCSPMBUS::CCSPMBUS_GetParamValues, "CCSPMBUS_GetParamValues");
    ptrAgentObj->RegisterMethod(*this,&CCSPMBUS::CCSPMBUS_SetParamValues, "CCSPMBUS_SetParamValues");

    ptrAgentObj->RegisterMethod(*this,&CCSPMBUS::CCSPMBUS_Init, "CCSPMBUS_Init");
    ptrAgentObj->RegisterMethod(*this,&CCSPMBUS::CCSPMBUS_Exit, "CCSPMBUS_Exit");
    ptrAgentObj->RegisterMethod(*this,&CCSPMBUS::CCSPMBUS_RegisterEvent, "CCSPMBUS_RegisterEvent");
    ptrAgentObj->RegisterMethod(*this,&CCSPMBUS::CCSPMBUS_UnRegisterEvent, "CCSPMBUS_UnRegisterEvent");
    ptrAgentObj->RegisterMethod(*this,&CCSPMBUS::CCSPMBUS_LoadCfg, "CCSPMBUS_LoadCfg");
    ptrAgentObj->RegisterMethod(*this,&CCSPMBUS::CCSPMBUS_LoadDmXml, "CCSPMBUS_LoadDmXml");
    ptrAgentObj->RegisterMethod(*this,&CCSPMBUS::CCSPMBUS_RegisterPath, "CCSPMBUS_RegisterPath");
    ptrAgentObj->RegisterMethod(*this,&CCSPMBUS::CCSPMBUS_QueryStatus, "CCSPMBUS_QueryStatus");
    ptrAgentObj->RegisterMethod(*this,&CCSPMBUS::CCSPMBUS_GetAllocMemory, "CCSPMBUS_GetAllocMemory");
    ptrAgentObj->RegisterMethod(*this,&CCSPMBUS::CCSPMBUS_GetMaxMemory, "CCSPMBUS_GetMaxMemory");
    ptrAgentObj->RegisterMethod(*this,&CCSPMBUS::CCSPMBUS_RegisterCapabilities, "CCSPMBUS_RegisterCapabilities");
    ptrAgentObj->RegisterMethod(*this,&CCSPMBUS::CCSPMBUS_RegisterBase, "CCSPMBUS_RegisterBase");
    ptrAgentObj->RegisterMethod(*this,&CCSPMBUS::CCSPMBUS_UnRegisterNamespace, "CCSPMBUS_UnRegisterNamespace");
    ptrAgentObj->RegisterMethod(*this,&CCSPMBUS::CCSPMBUS_UnRegisterComponent, "CCSPMBUS_UnRegisterComponent");
    ptrAgentObj->RegisterMethod(*this,&CCSPMBUS::CCSPMBUS_DiskNamespaceSupportedByComponent, "CCSPMBUS_DiskNamespaceSupportedByComponent");
    ptrAgentObj->RegisterMethod(*this,&CCSPMBUS::CCSPMBUS_DiskComponentSupportingDynamicTbl, "CCSPMBUS_DiskComponentSupportingDynamicTbl");
    ptrAgentObj->RegisterMethod(*this,&CCSPMBUS::CCSPMBUS_GetRegisteredComponents, "CCSPMBUS_GetRegisteredComponents");
    ptrAgentObj->RegisterMethod(*this,&CCSPMBUS::CCSPMBUS_GetHealth, "CCSPMBUS_GetHealth");
    ptrAgentObj->RegisterMethod(*this,&CCSPMBUS::CCSPMBUS_DumpComponentRegistry, "CCSPMBUS_DumpComponentRegistry");
    ptrAgentObj->RegisterMethod(*this,&CCSPMBUS::CCSPMBUS_IsSystemReady, "CCSPMBUS_IsSystemReady");
    ptrAgentObj->RegisterMethod(*this,&CCSPMBUS::CCSPMBUS_SendSignal, "CCSPMBUS_SendSignal");
    ptrAgentObj->RegisterMethod(*this,&CCSPMBUS::CCSPMBUS_ReqSessionId, "CCSPMBUS_ReqSessionId");
    ptrAgentObj->RegisterMethod(*this,&CCSPMBUS::CCSPMBUS_InformEndSession, "CCSPMBUS_InformEndSession");
    ptrAgentObj->RegisterMethod(*this,&CCSPMBUS::CCSPMBUS_BusCheck, "CCSPMBUS_BusCheck");
    ptrAgentObj->RegisterMethod(*this,&CCSPMBUS::CCSPMBUS_CheckNamespaceDataType, "CCSPMBUS_CheckNamespaceDataType");

    ptrAgentObj->RegisterMethod(*this,&CCSPMBUS::CCSPMBUS_CosaWifiInit, "CCSPMBUS_CosaWifiInit");
    return TEST_SUCCESS;
}

/***************************************************************************
 *Function name : testmodulepre_requisites
 *Description   : testmodulepre_requisites will  be used for setting the
 *                pre-requisites that are necessary for this component
 *
 *****************************************************************************/
std::string CCSPMBUS::testmodulepre_requisites()
{

    return "SUCCESS";
}

/***************************************************************************
 *Function name : testmodulepost_requisites
 *Description    : testmodulepost_requisites will be used for resetting the
 *                pre-requisites that are set
 *
 *****************************************************************************/
bool CCSPMBUS::testmodulepost_requisites()
{

    return TEST_SUCCESS;
}


/*******************************************************************************************
 *
 * Function Name        : CCSPMBUS_GetParamValues
 * Description          : This function will retrieve the list of parameter values 
 *                        associated with the specified namespace
 *
 * @param [in] req      : paramName - Specific parameter name for which value to be retrieved
 *
 * @param [out] response - SUCCESS - All parameter values are retrieved
 *                         FAILURE - Failed to retrieve the parameter values
 ********************************************************************************************/
bool CCSPMBUS::CCSPMBUS_GetParamValues(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_GetParamValues --->Entry\n");

    char paramName[MAX_PARAM_SIZE];
    int paramSize = 0;
    int loop = 0;
    GETPARAMVALUES *paramValue;

    /* Validate the input arguments */
    if(&req["paramName"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }

    /* Copy the input arguments to the local variables */
    strcpy(paramName,req["paramName"].asCString());

    DEBUG_PRINT(DEBUG_TRACE,"\n Input parameter is %s",paramName);	

    int returnVal=0;

    DEBUG_PRINT(DEBUG_TRACE,"Initiate to register with Component register\n");

    returnVal=ssp_register(1);
    if(returnVal == 0)
    {
        DEBUG_PRINT(DEBUG_TRACE,"CCSPMBUS stub registered with CR\n");
    }
    else
    {
        DEBUG_PRINT(DEBUG_TRACE,"Failed to register with CR\n");
        return "FAILURE";
    }

    /* Retrieve the specified parameter value */
    paramValue = ssp_getParameterValue(&paramName[0],&paramSize);
    if(paramValue == NULL)
    {
        response["result"]="FAILURE";
        response["details"]="Failed to retrieve the value of parameter name"; 		
    }
    else
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully retrieved the value of parameter name";

        for(loop = 0; loop < paramSize; loop++)
        {
            DEBUG_PRINT(DEBUG_TRACE,"Parameter Id is %d\n",loop);
            DEBUG_PRINT(DEBUG_TRACE,"Parameter Name is %s\n",paramValue[loop].pParamNames);
            DEBUG_PRINT(DEBUG_TRACE,"Parameter Value is %s",paramValue[loop].pParamValues);
            DEBUG_PRINT(DEBUG_TRACE,"Parameter Type is %d\n",paramValue[loop].pParamType);
        }

        /* Free the memory */
        free_Memory_val(paramSize,paramValue);	
    }

    DEBUG_PRINT(DEBUG_TRACE,"Initiate to unregistered from Component register\n");

    returnVal=ssp_terminate();
    if(returnVal == 0)
    {
        DEBUG_PRINT(DEBUG_TRACE,"CCSPMBUS stub unregistered from CR \n");
    }
    else
    {
        DEBUG_PRINT(DEBUG_TRACE,"Failed to unregistered from CR\n");
        return TEST_FAILURE;
    }

    DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_GetParamValues --->Exit\n");

    return TEST_SUCCESS;
}


/*******************************************************************************************
 *
 * Function Name        : CCSPMBUS_SetParamValues
 * Description          : This function will set the specified value to the parameter name
 *
 * @param [in] req      : paramName - parameter name for which the value to be set
 *                        paramValue - value to be set for the parameter name
 *                        paramType - type of the parameter value
 *
 * @param [out] response - SUCCESS - Value for the parameter name is set
 *                         FAILURE - Failed to set the value to the parameter name
 ********************************************************************************************/
bool CCSPMBUS::CCSPMBUS_SetParamValues(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_SetParamValues --->Entry\n");

    int returnValue = 0;
    char paramName[MAX_PARAM_SIZE];
    char paramValue[MAX_PARAM_SIZE];
    char paramType[MAX_PARAM_SIZE];
    int paramSize = 0;
    int commit = 0;
    GETPARAMVALUES *getParamValue;
    int returnVal=0;

    /* Validate the input arguments */
    if(&req["paramName"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }

    if(&req["paramValue"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }

    if(&req["paramType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }

    if(&req["commit"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }

    /* Copy the input arguments to the local variables */
    strcpy(paramName,req["paramName"].asCString());
    strcpy(paramValue,req["paramValue"].asCString());
    strcpy(paramType,req["paramType"].asCString());
    commit = req["commit"].asInt();

    DEBUG_PRINT(DEBUG_TRACE,"\nCCSPMBUS_SetParamValues:: ParamName input is %s",paramName);
    DEBUG_PRINT(DEBUG_TRACE,"\nCCSPMBUS_SetParamValues:: ParamValue input is %s",paramValue);
    DEBUG_PRINT(DEBUG_TRACE,"\nCCSPMBUS_SetParamValues:: ParamType input is %s",paramType);
    DEBUG_PRINT(DEBUG_TRACE,"\nCCSPMBUS_SetParamValues:: Commit input is %d",commit);

    DEBUG_PRINT(DEBUG_TRACE,"Initiate to register with Component register\n");

    returnVal=ssp_register(1);
    if(returnVal == 0)
    {
        DEBUG_PRINT(DEBUG_TRACE,"CCSPMBUS stub registered with CR\n");
    }
    else
    {
        DEBUG_PRINT(DEBUG_TRACE,"Failed to register with CR\n");
        return "FAILURE";
    }

    /* Set the value for the specified parameter name */
    returnValue = ssp_setParameterValue(&paramName[0],&paramValue[0],&paramType[0],commit);
    if(0 == returnValue)
    {
        /* Retrieve the specified parameter value */
        getParamValue = ssp_getParameterValue(&paramName[0],&paramSize);
        if(getParamValue == NULL)
        {
            response["result"]="FAILURE";
            response["details"]="Failed to retrieve the value of parameter name"; 		
        }
        else
        {
            DEBUG_PRINT(DEBUG_TRACE,"Parameter Name is %s\n",paramName);
            DEBUG_PRINT(DEBUG_TRACE,"Parameter Value is %s",getParamValue[0].pParamValues);
            DEBUG_PRINT(DEBUG_TRACE,"Parameter Type is %d\n",getParamValue[0].pParamType);

            /* Check whether set and get values are same */
            if(strcmp(&paramValue[0],&getParamValue[0].pParamValues[0])==0)
            {
                /* Free the memory */
                free_Memory_val(paramSize,getParamValue);	

                /* Set the result details */
                response["result"]="SUCCESS";
                response["details"]="Successfully set the value for the specified parameter";
            }
            else
            {
                /* Free the memory */
                free_Memory_val(paramSize,getParamValue);	

                /* Set the result details */
                response["result"]="FAILURE";
                response["details"]="Validation Failed - Set and Get values are not matching";
            }
        }
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to set the value for the specified parameter";
    }


    returnVal=ssp_terminate();
    if(returnVal == 0)
    {
        DEBUG_PRINT(DEBUG_TRACE,"CCSPMBUS stub unregistered from CR \n");
    }
    else
    {
        DEBUG_PRINT(DEBUG_TRACE,"Failed to unregistered from CR\n");
        return TEST_FAILURE;
    }

    DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_GetParamValues --->Exit\n");

    DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_SetParamValues --->Exit\n");
    return TEST_SUCCESS;
}



/*******************************************************************************************
 *
 * Function Name	: CCSPMBUS_Init
 * Description		: This function will invoke Message bus init that will init dbus 
 * 	        		  functions and interface calls
 *
 * @param [in]  req- 
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value of 
 * 			               ssp_mbus_init
 ********************************************************************************************/

bool CCSPMBUS::CCSPMBUS_Init(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_Init --->Entry \n");

    int returnValue = 0;
    char configFile[MAX_PARAM_SIZE];

    strcpy(configFile,req["cfgfileName"].asCString());

    printf("\n CCSPMBUS_Init :: Input msg config file is %s",configFile);

    returnValue = ssp_mbus_init(configFile);

    printf("\n CCSPMBUS_Init :: Status of Bus Init %s",returnValue);

    if(SSP_MBUS_SUCCESS == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="CCSPMBUS_Init :: Message Bus Initialization Success";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="CCSPMBUS_Init :: Message Bus Initialization Failure";
        DEBUG_PRINT(DEBUG_TRACE,"\n tdk_mbus_init Error --->Exit\n");
        return	TEST_FAILURE;
    }

    DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_Init --->Exit\n");
    return TEST_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name	: CCSPMBUS_Exit
 * Description		: This function is called through TM RPC which will invoke Message bus 
 *                    Exit function
 * @param [in] req- 
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value of 
 * 			               ssp_mbus_exit
 ********************************************************************************************/

bool CCSPMBUS::CCSPMBUS_Exit(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_Exit --->Entry\n");

    int returnValue = SSP_MBUS_FAILURE;


    returnValue = ssp_mbus_exit();

    if( SSP_MBUS_SUCCESS == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="CCSPMBUS_Exit :: MBUS DE-INITIALIZTION SUCCESS";
    }
    else
    {
        response["result"]="FAILURE";

        if( returnValue == SSP_MBUS_EXEC_ERROR )
        {
            response["details"]="CCSPMBUS_Exit :: Message Bus EXIT INVOKE ERROR / Is INIT CALLED?";
        }
        else
        {
            response["details"]="CCSPMBUS_Exit :: MBUS DE-INITIALIZTION FAILURE";
        }

        DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_Exit --->Error in  execution \n");
        return	TEST_FAILURE;
    }

    DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_Exit --->Exit\n");
    return TEST_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name	: CCSPMBUS_RegisterEvent
 * Description		: This function is called through TM RPC which will invoke Message bus 
 *                    Exit function
 * @param [in] req- 
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value of 
 * 			               ssp_mbus_exit
 ********************************************************************************************/

bool CCSPMBUS::CCSPMBUS_RegisterEvent(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_RegisterEvent --->Entry \n");

    int returnValue = SSP_MBUS_FAILURE;
    char eventName[MAX_PARAM_SIZE];

    strcpy(eventName,req["eventName"].asCString());

    returnValue = ssp_mbus_register_event(eventName);

    if(SSP_MBUS_SUCCESS == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="CCSPMBUS_RegisterEvent :: MBUS Register Event Success";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="CCSPMBUS_RegisterEvent :: MBUS Register Event Failure";
        DEBUG_PRINT(DEBUG_TRACE,"\n ssp_mbus_register_event Error --->Exit\n");
        return  TEST_FAILURE;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_RegisterEvent --->Exit\n");

    return TEST_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name	: CCSPMBUS_UnRegisterEvent
 * Description		: This function is called through TM RPC which will invoke Message bus 
 *                    Exit function
 * @param [in] req- 
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value of 
 * 			               ssp_mbus_exit
 ********************************************************************************************/

bool CCSPMBUS::CCSPMBUS_UnRegisterEvent(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_UnRegisterEvent --->Entry \n");

    int returnValue = SSP_MBUS_FAILURE;
    char eventName[MAX_PARAM_SIZE];

    strcpy(eventName,req["eventName"].asCString());

    returnValue = ssp_mbus_unregister_event(eventName);

    if(SSP_MBUS_SUCCESS == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="CCSPMBUS_UnRegisterEvent :: MBUS UnRegister Event Success";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="CCSPMBUS_UnRegisterEvent :: MBUS UnRegister Event Failure";
        DEBUG_PRINT(DEBUG_TRACE,"\n tdk_mbus_unregister_event Error --->Exit\n");
        return  TEST_FAILURE;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_UnRegisterEvent --->Exit\n");

    return TEST_SUCCESS;
}


/*******************************************************************************************
 *
 * Function Name	: CCSPMBUS_LoadCfg
 * Description		: This function will invoke ssp function that inturn will
 * 	        		  call ccsp base functions to load component specific config file
 *
 * @param [in]  req- 
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value of 
 * 			               ssp_mbus_loadcfg
 ********************************************************************************************/

bool CCSPMBUS::CCSPMBUS_LoadCfg(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_LoadCfg --->Entry \n");

    int returnValue = SSP_MBUS_FAILURE;
    char configFile[MAX_PARAM_SIZE];	

    strcpy(configFile,req["cmpCfgFile"].asCString());

    returnValue = ssp_mbus_loadcfg(configFile);

    if(SSP_MBUS_SUCCESS == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="CCSPMBUS_LoadCfg :: Component Config file loading SUCCESS";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="CCSPMBUS_LoadCfg :: Component Config file loading FAILURE";
        DEBUG_PRINT(DEBUG_TRACE,"\n tdk_mbus_loadcfg Error --->Exit\n");
        return	TEST_FAILURE;
    }

    DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_LoadCfg --->Exit \n");
    return TEST_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name	: CCSPMBUS_LoadDmXml
 * Description		: This function will invoke ssp function that inturn will
 * 	        		  call ccsp base functions to load component specific data model
 *                    xml file
 *
 * @param [in]  req- 
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value of 
 * 			               ssp_mbus_load_dmlxml
 ********************************************************************************************/

bool CCSPMBUS::CCSPMBUS_LoadDmXml(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_LoadDmXml --->Entry \n");

    int returnValue = SSP_MBUS_FAILURE;
    char dmlxml[MAX_PARAM_SIZE];	

    strcpy(dmlxml,req["xmlfileName"].asCString());

    returnValue = ssp_mbus_load_dmlxml(dmlxml);

    if(SSP_MBUS_SUCCESS == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="CCSPMBUS_LoadDmXml :: Component data model xml file loading SUCCESS";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="CCSPMBUS_LoadDmXml :: Component data model xml file loading FAILURE";
        DEBUG_PRINT(DEBUG_TRACE,"\n tdk_mbus_load_dmlxml Error --->Exit\n");
        return	TEST_FAILURE;
    }

    DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_LoadDmXml --->Exit \n");
    return TEST_SUCCESS;
}


/*******************************************************************************************
 *
 * Function Name	: CCSPMBUS_RegisterPath
 * Description		: This function will invoke ssp function that inturn will
 * 	        		  call ccsp base functions to load component specific data model
 *                    xml file
 *
 * @param [in]  req- 
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value of 
 * 			               ssp_mbus_register_path
 ********************************************************************************************/

bool CCSPMBUS::CCSPMBUS_RegisterPath(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_RegisterPath --->Entry \n");

    int returnValue = SSP_MBUS_FAILURE;

    returnValue = ssp_mbus_register_path();

    if(SSP_MBUS_SUCCESS == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="CCSPMBUS_RegisterPath :: MBUS Register Path Success";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="CCSPMBUS_RegisterPath :: MBUS Register Path Failure";
        DEBUG_PRINT(DEBUG_TRACE,"\n tdk_mbus_register_path Error --->Exit\n");
        return  TEST_FAILURE;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_RegisterPath --->Exit\n");

    return TEST_SUCCESS;
}


/*******************************************************************************************
 *
 * Function Name	: CCSPMBUS_QueryStatus
 * Description		: This function will invoke ssp function that inturn will
 * 	        		  call ccsp base functions to load component specific data model
 *                    xml file
 *
 * @param [in]  req- 
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value of 
 * 			               ssp_mbus_load_dmlxml
 ********************************************************************************************/

bool CCSPMBUS::CCSPMBUS_QueryStatus(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_QueryStatus --->Entry \n");

    int returnValue = 0;

    returnValue = ssp_mbus_query_status();

    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="CCSPMBUS_QueryStatus :: MBUS Query Status Success";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="CCSPMBUS_QueryStatus :: MBUS Query Status Failure";
        DEBUG_PRINT(DEBUG_TRACE,"\n tdk_mbus_query_status Error --->Exit\n");
        return  TEST_FAILURE;
    }

    DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_QueryStatus --->Exit\n");

    return TEST_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name	: CCSPMBUS_GetAllocMemory
 * Description		: This function will invoke ssp function that inturn will
 * 	        		  call ccsp base functions to load component specific data model
 *                    xml file
 *
 * @param [in]  req- 
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value of 
 * 			               ssp_mbus_load_dmlxml
 ********************************************************************************************/

bool CCSPMBUS::CCSPMBUS_GetAllocMemory(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_GetAllocMemory --->Entry \n");

    int returnValue = SSP_MBUS_FAILURE;

    returnValue = ssp_mbus_get_allocmemory();

    if(SSP_MBUS_SUCCESS == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="Mbus_GetAllocMemory:: CCSPMBUS Get allocated Memory Success";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Mbus_GetAllocMemory:: CCSPMBUS Get Allocated Memory Failure";
        DEBUG_PRINT(DEBUG_TRACE,"\n tdk_mbus_get_alloc_memory--->Exit\n");
        return  TEST_FAILURE;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_GetAllocMemory--->Exit\n");

    return TEST_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name	: CCSPMBUS_GetMaxMemory
 * Description		: This function will invoke ssp function that inturn will
 * 	        		  call ccsp base functions to load component specific data model
 *                    xml file
 *
 * @param [in]  req- 
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value of 
 * 			               ssp_mbus_load_dmlxml
 ********************************************************************************************/

bool CCSPMBUS::CCSPMBUS_GetMaxMemory(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_GetMaxMemory --->Entry \n");

    int returnValue = SSP_MBUS_FAILURE;

    returnValue = ssp_mbus_get_maxmemory();

    if(SSP_MBUS_SUCCESS == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="CCSPMBUS_GetMaxMemory:: Mbus Get Max Memory Success";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="CCSPMBUS_GetMaxMemory:: Mbus Get Max Memory Failure";
        DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_GetMaxMemory --->Exit\n");
        return  TEST_FAILURE;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_GetMaxMemory --->Exit\n");

    return TEST_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name	: CCSPMBUS_RegisterCapabilities
 * Description		: This function will invoke ssp function that inturn will
 * 	        		  call ccsp base functions to load component specific data model
 *                    xml file
 *
 * @param [in]  req- 
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value of 
 * 			               ssp_mbus_load_dmlxml
 ********************************************************************************************/

bool CCSPMBUS::CCSPMBUS_RegisterCapabilities(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_RegisterCapabilities --->Entry \n");

    int returnValue = SSP_MBUS_FAILURE;

    returnValue = ssp_mbus_register_capabilities();

    if(SSP_MBUS_SUCCESS == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="CCSPMBUS_RegisterCapabilities :: Mbus Register Capabilities Success";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="CCSPMBUS_RegisterCapabilities ::Mbus Register Capabilities Failure";
        DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_RegisterCapabilities --->Exit\n");
        return  TEST_FAILURE;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_RegisterCapabilities --->Exit\n");

    return TEST_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name	: CCSPMBUS_UnRegisterNamespace
 * Description		: This function will invoke ssp function that inturn will
 * 	        		  call ccsp base functions to load component specific data model
 *                    xml file
 *
 * @param [in]  req- 
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value of 
 * 			               ssp_mbus_load_dmlxml
 ********************************************************************************************/

bool CCSPMBUS::CCSPMBUS_UnRegisterNamespace(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_UnRegisterNamespace --->Entry \n");

    int returnValue = SSP_MBUS_FAILURE;

    returnValue = ssp_mbus_unregister_namespace();

    if(SSP_MBUS_SUCCESS == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="CCSPMBUS_UnRegisterNamespace :: UnRegister Namespace Success";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="CCSPMBUS_UnRegisterNamespace :: UnRegister Namespace Failure";
        DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_UnRegisterNamespace --->Exit\n");
        return  TEST_FAILURE;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_UnRegisterNamespace -->Exit\n");

    return TEST_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name	: CCSPMBUS_UnRegisterComponent
 * Description		: This function will invoke ssp function that inturn will
 * 	        		  call ccsp base functions to load component specific data model
 *                    xml file
 *
 * @param [in]  req- 
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value of 
 * 			               ssp_mbus_load_dmlxml
 ********************************************************************************************/

bool CCSPMBUS::CCSPMBUS_UnRegisterComponent(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_UnRegisterComponent --->Entry \n");

    int returnValue = SSP_MBUS_FAILURE;

    returnValue = ssp_mbus_unregistercomponent();

    if(SSP_MBUS_SUCCESS == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="CCSPMBUS_UnRegisterComponent :: UnRegister Component Success";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="CCSPMBUS_UnRegisterComponent :: MBUS UnRegister Component Failure";
        DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_UnRegisterComponent ERROR --->Exit\n");
        return  TEST_FAILURE;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_UnRegisterComponent --->Exit\n");

    return TEST_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name	: CCSPMBUS_DiskNamespaceSupportedByComponent
 * Description		: This function will invoke ssp function that inturn will
 * 	        		  call ccsp base functions to load component specific data model
 *                    xml file
 *
 * @param [in]  req- 
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value of 
 * 			               ssp_mbus_load_dmlxml
 ********************************************************************************************/

bool CCSPMBUS::CCSPMBUS_DiskNamespaceSupportedByComponent(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_DiskNamespaceSupportedByComponent --->Entry \n");

    int returnValue = SSP_MBUS_FAILURE;

    returnValue = ssp_mbus_namespace_supportedby_component();

    if(SSP_MBUS_SUCCESS == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="CCSPMBUS_DiskNamespaceSupportedByComponent :: DiskNamespace Supported By Component Success";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="CCSPMBUS_DiskNamespaceSupportedByComponent :: DiskNamespace Supported By Component Failure";
        DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_DiskNamespaceSupportedByComponent Error --->Exit\n");
        return  TEST_FAILURE;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_DiskNamespaceSupportedByComponent --->Exit\n");

    return TEST_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name	: CCSPMBUS_DiskComponentSupportingDynamicTbl
 * Description		: This function will invoke ssp function that inturn will
 * 	        		  call ccsp base functions to load component specific data model
 *                    xml file
 *
 * @param [in]  req- 
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value of 
 * 			               ssp_mbus_load_dmlxml
 ********************************************************************************************/

bool CCSPMBUS::CCSPMBUS_DiskComponentSupportingDynamicTbl(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_DiskComponentSupportingDynamicTbl --->Entry \n");

    int returnValue = SSP_MBUS_FAILURE;

    returnValue = ssp_mbus_component_supporting_dynamictbl();

    if(SSP_MBUS_SUCCESS == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="CCSPMBUS_DiskComponentSupportingDynamicTbl :: Disk Component Supporting Dynamic Tbl Success";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="CCSPMBUS_DiskComponentSupportingDynamicTbl :: Disk Component Supporting Dynamic Tbl Failure";
        DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_DiskComponentSupportingDynamicTbl --->Exit\n");
        return  TEST_FAILURE;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_DiskComponentSupportingDynamicTbl --->Exit\n");

    return TEST_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name	: CCSPMBUS_GetRegisteredComponents
 * Description		: This function will invoke ssp function that inturn will
 * 	        		  call ccsp base functions to load component specific data model
 *                    xml file
 *
 * @param [in]  req- 
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value of 
 * 			               ssp_mbus_load_dmlxml
 ********************************************************************************************/

bool CCSPMBUS::CCSPMBUS_GetRegisteredComponents(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_GetRegisteredComponents --->Entry \n");

    int returnValue = 0;

    returnValue = ssp_mbus_get_registered_components();

    if(SSP_MBUS_SUCCESS == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="CCSPMBUS_GetRegisteredComponents :: Get Registered Components Success";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="CCSPMBUS_GetRegisteredComponents :: Get Registered Components Failure";
        DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_GetRegisteredComponents Error --->Exit\n");
        return  TEST_FAILURE;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_GetRegisteredComponents --->Exit\n");

    return TEST_SUCCESS;
}


/*******************************************************************************************
 *
 * Function Name	: CCSPMBUS_GetHealth
 * Description		: This function will invoke ssp function that inturn will
 * 	        		  call ccsp base functions to load component specific data model
 *                    xml file
 *
 * @param [in]  req- 
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value of 
 * 			               ssp_mbus_load_dmlxml
 ********************************************************************************************/

bool CCSPMBUS::CCSPMBUS_GetHealth(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_GetHealth --->Entry \n");

    int returnValue = SSP_MBUS_FAILURE;
    char cmpId[MAX_PARAM_SIZE];
    char cmpPath[MAX_PARAM_SIZE];

    strcpy(cmpId,req["cmpId"].asCString());
    strcpy(cmpPath,req["cmpPath"].asCString());

    returnValue = ssp_mbus_getHealth(cmpId,cmpPath);

    if(SSP_MBUS_SUCCESS == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="CCSPMBUS_GetHealth :: Retrieved the component health";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="CCSPMBUS_GetHealth :: Failed to retrievd the component health";
        return  TEST_FAILURE;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_GetHealth --->Exit\n");

    return TEST_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name	: CCSPMBUS_DumpComponentRegistry 
 * Description		: This function will invoke ssp function that inturn will
 * 	        		  call ccsp base functions to load component specific data model
 *                    xml file
 *
 * @param [in]  req- 
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value of 
 * 			               ssp_mbus_load_dmlxml
 ********************************************************************************************/

bool CCSPMBUS::CCSPMBUS_DumpComponentRegistry(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_DumpComponentRegistry --->Entry \n");

    int returnValue = SSP_MBUS_FAILURE;

    returnValue = ssp_mbus_dump_component_registry();

    if(SSP_MBUS_SUCCESS == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="CCSPMBUS_DumpComponentRegistry :: Dump Component Registry Success";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="CCSPMBUS_DumpComponentRegistry :: Dump Component Registry Failure";
        return  TEST_FAILURE;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n tdk_mbus_DumpComponentRegistry --->Exit\n");

    return TEST_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name	: CCSPMBUS_IsSystemReady 
 * Description		: This function will invoke ssp function that inturn will
 * 	        		  call ccsp base functions to load component specific data model
 *                    xml file
 *
 * @param [in]  req- 
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value of 
 * 			               ssp_mbus_load_dmlxml
 ********************************************************************************************/

bool CCSPMBUS::CCSPMBUS_IsSystemReady(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_IsSystemReady --->Entry \n");

    int returnValue = SSP_MBUS_FAILURE;

    returnValue = ssp_mbus_issystem_ready();

    if(SSP_MBUS_SUCCESS == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="CCSPMBUS_IsSystemReady :: IsSystem Ready Success";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="CCSPMBUS_IsSystemReady :: IsSystem Ready Failure";
        return  TEST_FAILURE;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_IsSystemReady --->Exit\n");

    return TEST_SUCCESS;
}


/*******************************************************************************************
 *
 * Function Name	: CCSPMBUS_SendSignal 
 * Description		: This function will invoke ssp function that inturn will
 * 	        		  call ccsp base functions to load component specific data model
 *                    xml file
 *
 * @param [in]  req- 
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value of 
 * 			               ssp_mbus_load_dmlxml
 ********************************************************************************************/

bool CCSPMBUS::CCSPMBUS_SendSignal(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_SendSignal --->Entry \n");

    int returnValue = SSP_MBUS_FAILURE;

    returnValue = ssp_mbus_SendsystemReadySignal();

    if(SSP_MBUS_SUCCESS == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="CCSPMBUS_SendSignal :: Successfully send the event signal";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="CCSPMBUS_SendSignal :: Failed to send the event signal";
        return  TEST_FAILURE;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_SendSignal --->Exit\n");

    return TEST_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name	: CCSPMBUS_RegisterBase
 * Description		: This function will invoke ssp function that inturn will
 * 	        		  call ccsp base functions to load component specific data model
 *                    xml file
 *
 * @param [in]  req- 
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value of 
 * 			               ssp_mbus_load_dmlxml
 ********************************************************************************************/

bool CCSPMBUS::CCSPMBUS_RegisterBase(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_RegisterBase--->Entry \n");

    int returnValue = SSP_MBUS_FAILURE;

    returnValue = ssp_mbus_register_base();

    if(SSP_MBUS_SUCCESS == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="CCSPMBUS_RegisterBase :: Register Base Success";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="CCSPMBUS_RegisterBase :: Register Base Failure";
        DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_RegisterBase Error --->Exit\n");
        return  TEST_FAILURE;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_RegisterBase --->Exit\n");

    return TEST_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name        : CCSPMBUS_ReqSessionId
 * Description          : This function will invoke ssp function that inturn will
 *                                call ccsp base functions to request session ID from CR
 *
 *
 * @param [in]  req-
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value of
 *                                     ssp_mbus_req_sessionid
 ********************************************************************************************/

bool CCSPMBUS::CCSPMBUS_ReqSessionId(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_ReqSessionId --->Entry \n");

    int returnValue = SSP_MBUS_FAILURE;

    returnValue = ssp_mbus_req_sessionid();

    if(SSP_MBUS_SUCCESS == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="CCSPMBUS_ReqSessionId :: MBUS ReqSession Id Success";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="CCSPMBUS_ReqSessionId :: MBUS ReqSession Id Failure";
        DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_ReqSessionId  Error --->Exit\n");
        return  TEST_FAILURE;
    }

    DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_ReqSessionId --->Exit\n");

    return TEST_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name        : CCSPMBUS_InformEndSession
 * Description          : This function will invoke ssp function that inturn will
 *                                call ccsp base functions to close/inform end of session to the CR
 *
 *
 * @param [in]  req-
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value of
 *                                     ssp_mbus_inform_end_session
 ********************************************************************************************/
bool CCSPMBUS::CCSPMBUS_InformEndSession(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_InformEndSession --->Entry \n");

    int returnValue = SSP_MBUS_FAILURE;

    returnValue = ssp_mbus_inform_end_session();

    if(SSP_MBUS_SUCCESS == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="CCSPMBUS_InformEndOfSession :: MBus Inform End Of Session Success";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="CCSPMBUS_InformEndOfSession :: MBus Inform End Of Session Failure";
        DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_InformEndSession Error --->Exit\n");
        return  TEST_FAILURE;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_InformEndSession --->Exit\n");

    return TEST_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name        : CCSPMBUS_BusCheck
 * Description          : This function will invoke ssp function that inturn will
 *                                call ccsp base functions to check the bus status of a component
 *                    from CR
 *
 * @param [in]  req-
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value of
 *                                     ssp_mbus_bus_check
 ********************************************************************************************/
bool CCSPMBUS::CCSPMBUS_BusCheck(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_BusCheck --->Entry \n");

    int returnValue = SSP_MBUS_FAILURE;


    returnValue = ssp_mbus_bus_check();

    if(SSP_MBUS_SUCCESS == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="CCSPMBUS_BusCheck :: MBus BusCheck Success";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="CCSPMBUS_BusCheck :: MBus BusCheck Failure";
        DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_BusCheck --->Exit\n");
        return  TEST_FAILURE;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_BusCheck --->Exit\n");

    return TEST_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name	: CCSPMBUS_CosaWifiInit
 * Description		: This function will invoke Cosa init that will init wifi
 * 	        		  dml init function
 *
 * @param [in]  req- 
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value of 
 * 			               ssp_mbus_init
 ********************************************************************************************/

bool CCSPMBUS::CCSPMBUS_CosaWifiInit(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_CosaWifiInit --->Entry \n");

    int returnValue = 0;

    ssp_register(1);
#if 1
    returnValue = ssp_MBUS_Stub_cosa_wifi_init();

    printf("\n CCSPMBUS_CosaWifiInit :: Status of WIFI DML Init %s",returnValue);

    if(SSP_TDK_SUCCESS == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="CCSPMBUS_CosaWifiInit:: Cosa DML WIFI Initialization Success";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="CCSPMBUS_CosaWifiInit:: Cosa DML WIFI Initialization Failure";
        DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_CosaWifiInit Error --->Exit\n");
        return	TEST_FAILURE;
    }
    ssp_terminate();
#endif
    return TEST_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name        : CCSPMBUS_CheckNamespaceDataType
 * Description          : This function will invoke ssp function that inturn will
 *                                call ccsp base functions to get/check datatype of a given
 *                    namespace
 *
 * @param [in]  req-
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value of
 *                                     ssp_mbus_check_namespace_datatype
 ********************************************************************************************/

bool CCSPMBUS::CCSPMBUS_CheckNamespaceDataType(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n  CCSPMBUS_CheckNamespaceDataType --->Entry \n");

    int returnValue = SSP_MBUS_FAILURE;


    returnValue = ssp_mbus_check_namespace_datatype();

    if(SSP_MBUS_SUCCESS == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="CCSPMBUS_CheckNamespaceDataType :: MBus Check Namespace DataType Success";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="CCSPMBUS_CheckNamespaceDataType :: MBus Check Namespace DataType Failure";
        DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_CheckNamespaceDataType Error --->Exit\n");
        return  TEST_FAILURE;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CCSPMBUS_CheckNamespaceDataType --->Exit\n");

    return TEST_SUCCESS;
}

/**************************************************************************
 * Function Name	: CreateObject
 * Description	    : This function will be used to create a new object for the
 *		              class "CCSPMBUS".
 *
 **************************************************************************/
extern "C" CCSPMBUS* CreateObject()
{
    return new CCSPMBUS();
}

/**************************************************************************
 * Function Name : cleanup
 * Description   : This function will be used to clean the log details. 
 *
 **************************************************************************/
bool CCSPMBUS::cleanup(IN const char* szVersion,IN RDKTestAgent *ptrAgentObj)
{

    DEBUG_PRINT(DEBUG_LOG,"CCSPMBUS cleanup --> Entry \n");

    if(ptrAgentObj==NULL)
    {
        return TEST_FAILURE;
    }

    /*unRegister stub function for callback*/
    ptrAgentObj->UnregisterMethod("CCSPMBUS_GetParamValues");
    ptrAgentObj->UnregisterMethod("CCSPMBUS_SetParamValues");

    ptrAgentObj->UnregisterMethod("CCSPMBUS_Init");
    ptrAgentObj->UnregisterMethod("CCSPMBUS_Exit");	
    ptrAgentObj->UnregisterMethod("CCSPMBUS_LoadCfg");
    ptrAgentObj->UnregisterMethod("CCSPMBUS_LoadDmXml");
    ptrAgentObj->UnregisterMethod("CCSPMBUS_UnRegisterComponent");
    ptrAgentObj->UnregisterMethod("CCSPMBUS_GetRegisteredComponents");
    ptrAgentObj->UnregisterMethod("CCSPMBUS_GetHealth");
    ptrAgentObj->UnregisterMethod("CCSPMBUS_IsSystemReady");
    ptrAgentObj->UnregisterMethod("CCSPMBUS_SendSignal");
    ptrAgentObj->UnregisterMethod("CCSPMBUS_RegisterEvent");
    ptrAgentObj->UnregisterMethod("CCSPMBUS_UnRegisterEvent");
    ptrAgentObj->UnregisterMethod("CCSPMBUS_LoadCfg");
    ptrAgentObj->UnregisterMethod("CCSPMBUS_LoadDmXml");
    ptrAgentObj->UnregisterMethod("CCSPMBUS_RegisterPath");
    ptrAgentObj->UnregisterMethod("CCSPMBUS_QueryStatus");
    ptrAgentObj->UnregisterMethod("CCSPMBUS_GetAllocMemory");
    ptrAgentObj->UnregisterMethod("CCSPMBUS_GetMaxMemory");
    ptrAgentObj->UnregisterMethod("CCSPMBUS_RegisterCapabilities");
    ptrAgentObj->UnregisterMethod("CCSPMBUS_RegisterBase");
    ptrAgentObj->UnregisterMethod("CCSPMBUS_UnRegisterNamespace");
    ptrAgentObj->UnregisterMethod("CCSPMBUS_DiskNamespaceSupportedByComponent");
    ptrAgentObj->UnregisterMethod("CCSPMBUS_DiskComponentSupportingDynamicTbl");
    ptrAgentObj->UnregisterMethod("CCSPMBUS_DumpComponentRegistry");
    ptrAgentObj->UnregisterMethod("CCSPMBUS_ReqSessionId");
    ptrAgentObj->UnregisterMethod("CCSPMBUS_InformEndSession");
    ptrAgentObj->UnregisterMethod("CCSPMBUS_BusCheck");
    ptrAgentObj->UnregisterMethod("CCSPMBUS_CheckNamespaceDataType");

    ptrAgentObj->UnregisterMethod("CCSPMBUS_CosaWifiInit");

    DEBUG_PRINT(DEBUG_LOG,"CCSPMBUS cleanup --> Exit \n");

    return TEST_SUCCESS;
}

/**************************************************************************
 * Function Name : DestroyObject
 * Description   : This function will be used to destroy the object. 
 *
 **************************************************************************/
extern "C" void DestroyObject(CCSPMBUS *stubobj)
{
    DEBUG_PRINT(DEBUG_LOG,"Destroying CCSPMBUS object\n");
    delete stubobj;
}

