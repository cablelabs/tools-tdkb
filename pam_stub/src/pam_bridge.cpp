/*
 * ============================================================================
 * COMCAST C O N F I D E N T I A L AND PROPRIETARY
 * ============================================================================
 * This file and its contents are the intellectual property of Comcast.  It may
 * not be used, copied, distributed or otherwise  disclosed in whole or in part
 * without the express written permission of Comcast.
 * ============================================================================
 * Copyright (c) 2016 Comcast. All rights reserved.
 * ============================================================================
 */

#include "pam.h"
#include "ssp_tdk_wrp.h"

/* To provide external linkage to C Functions defined in TDKB Component folder */

extern "C"
{
int ssp_register(bool);
int ssp_terminate();
int ssp_pam_Bridging_GetParamUlongValue(char* paramName,unsigned long* ulongValue);
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
    ptrAgentObj->RegisterMethod(*this,&pam::pam_bridge_GetParamBoolValue,"pam_bridge_GetParamBoolValue");

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
 * Function Name    : pam_bridge_GetParamBoolValue
 * Description      : This function is used to retrieve the value of ulong parameter
 *
 * @param [in]  req - paramName : Parameter name whose value to be retrieved
 * @param [in]  req - valueType : Value type to be fetched
 * @param [in]  req - module : keyword of the module associated with the paramName
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/

bool pam::pam_bridge_GetParamBoolValue(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n pam_bridge_GetParamBoolValue --->Entry \n");

    int returnValue = 0;
    char paramName[MAX_PARAM_SIZE];
    int valueType = 0;
    char module[MAX_PARAM_SIZE];
    unsigned long ulongValue = 0;

    /* Validate the input arguments */
    if(&req["paramName"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }
    if(&req["valueType"]==NULL)
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

    DEBUG_PRINT(DEBUG_TRACE,"\n after module validation \n");
    strcpy(paramName,req["paramName"].asCString());
    valueType = req["valueType"].asInt();
    strcpy(module,req["module"].asCString());
    if(strcmp(module,"Bridging") == 0)
    {
 	/* Invoke the wrapper function to get the value of ulong parameter */
    	 returnValue = ssp_pam_Bridging_GetParamUlongValue(paramName, &ulongValue);
         DEBUG_PRINT(DEBUG_TRACE,"\n ulongValue retrieved is:%lu\n",ulongValue);
    }

    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully retrieved the value";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to retrieve the value of ulong parameter";
        DEBUG_PRINT(DEBUG_TRACE,"\n pam_bridge_GetParamBoolValue --->Exit\n");
        return  TEST_FAILURE;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n pam_bridge_GetParamBoolValue  --->Exit\n");
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
    ptrAgentObj->UnregisterMethod("pam_bridge_GetParamBoolValue");

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

