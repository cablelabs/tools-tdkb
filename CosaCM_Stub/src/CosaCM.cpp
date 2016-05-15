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

#include "CosaCM.h"
#include "ssp_tdk_wrp.h"

/* To provide external linkage to C Functions defined in TDKB Component folder */

extern "C"
{
int ssp_register(bool);
int ssp_terminate();
int ssp_CosaDmlCMGetResetCount(int handleType, int bufferType, char *pResetType);
int ssp_CosaDmlCMGetLockedUpstreamChID(int handleType);
int ssp_CosaDmlCMSetLockedUpstreamChID(int handleType, int channelId);
int ssp_CosaDmlCMGetStartDSFrequency(int handleType);
int ssp_CosaDmlCMSetStartDSFrequency(int handleType, int frequency);
int ssp_CosaDmlCMGetProvType(int handleType, int bufferType);
int ssp_CosaDmlCMGetIPv6DHCPInfo(int handleType, int bufferType);
int ssp_cosacm_getcpelist();
int ssp_cosacm_getcertstatus();
int ssp_cosacm_getcmerrorcodewords();
int ssp_cosacm_getcert();
int ssp_cosacm_getmddipoverride();
int ssp_cosacm_setmddipoverride();
int ssp_cosacm_getmarket();
int ssp_cosacm_getmarket_memory_unalloc();
int ssp_cosacm_setmddipoverride_memory_unalloc();
int ssp_cosacm_getmddipoverride_memory_unalloc();
int ssp_cosacm_getcert_memory_unalloc();
int ssp_cosacm_getcmrrrorcodewords_invalid_arg();
int ssp_cosacm_getcertstatus_invalid_arg();
int ssp_cosacm_getcpelist_invalid_arg();
int ssp_CosaDmlCMGetStatus(int handleType, int Value);
int ssp_CosaCMGetLoopDiagnosticsStart(int handleType, int boolValue);
int ssp_CosaDmlCMGetLoopDiagnosticsDetails(int handleType, int Value);
int ssp_CosaDmlCMGetTelephonyRegistrationStatus(int handleType, int Value);
int ssp_CosaDmlCMGetTelephonyDHCPStatus(int handleType, int Value);
int ssp_CosaDmlCMGetTelephonyTftpStatus(int handleType, int Value);
int ssp_CosaDmlCMSetLoopDiagnosticsStart(int handleType, int boolValue);
int ssp_cosacm_GetDHCPInfo(int handleType, int bufferType);
int ssp_cosacm_GetDOCSISInfo(int handleType, int bufferType);
int ssp_cosacm_GetLog(int handleType, int bufferType);
int ssp_cosacm_SetLog(int handleType, int bufferType);
int ssp_cosacm_GetDocsisLog(int handleType, int bufferType);
int ssp_cosacm_GetDownstreamChannel(int handleType, int bufferType);
int ssp_cosacm_GetUpstreamChannel(int handleType, int bufferType);
int ssp_CosaCableModemCreate();
int ssp_CosaCableModemInitialize(int handleType);
int ssp_CosaCableModemRemove(int handleType);
};

/*This is a constructor function for CosaCM class*/
CosaCM::CosaCM()
{
    DEBUG_PRINT(DEBUG_LOG,"CosaCM Instance Created\n");
}

/***************************************************************************
 *Function name	: initialize
 *Description	: Initialize Function will be used for registering the wrapper method 
 *        	  	  with the agent so that wrapper function will be used in the script
 *  		  	  
 *****************************************************************************/ 

bool CosaCM::initialize(IN const char* szVersion,IN RDKTestAgent *ptrAgentObj)
{
    DEBUG_PRINT(DEBUG_TRACE,"TDK::CosaCM Initialize\n");
    /*Register stub function for callback*/
    ptrAgentObj->RegisterMethod(*this,&CosaCM::CosaCM_GetResetCount,"CosaCM_GetResetCount");
    ptrAgentObj->RegisterMethod(*this,&CosaCM::CosaCM_GetUpstreamChannelId,"CosaCM_GetUpstreamChannelId");
    ptrAgentObj->RegisterMethod(*this,&CosaCM::CosaCM_SetUpstreamChannelId,"CosaCM_SetUpstreamChannelId");
    ptrAgentObj->RegisterMethod(*this,&CosaCM::CosaCM_GetStartDSFrequency,"CosaCM_GetStartDSFrequency");
    ptrAgentObj->RegisterMethod(*this,&CosaCM::CosaCM_SetStartDSFrequency,"CosaCM_SetStartDSFrequency");
    ptrAgentObj->RegisterMethod(*this,&CosaCM::CosaCM_GetProvType,"CosaCM_GetProvType");
    ptrAgentObj->RegisterMethod(*this,&CosaCM::CosaCM_GetIPv6DHCPInfo,"CosaCM_GetIPv6DHCPInfo");

    ptrAgentObj->RegisterMethod(*this,&CosaCM::COSACM_GetMarket,"COSACM_GetMarket");
    ptrAgentObj->RegisterMethod(*this,&CosaCM::COSACM_SetMDDIPOverride,"COSACM_SetMDDIPOverride");
    ptrAgentObj->RegisterMethod(*this,&CosaCM::COSACM_GetMDDIPOverride,"COSACM_GetMDDIPOverride");
    ptrAgentObj->RegisterMethod(*this,&CosaCM::COSACM_GetCMCert,"COSACM_GetCMCert");
    ptrAgentObj->RegisterMethod(*this,&CosaCM::COSACM_GetCMErrorCodewords,"COSACM_GetCMErrorCodewords");
    ptrAgentObj->RegisterMethod(*this,&CosaCM::COSACM_GetCMCertStatus,"COSACM_GetCMCertStatus");
    ptrAgentObj->RegisterMethod(*this,&CosaCM::COSACM_GetCPEList,"COSACM_GetCPEList");

    ptrAgentObj->RegisterMethod(*this,&CosaCM::COSACM_GetMarket_ArgMemory_unalloc,"COSACM_CMGetMarket_ArgMemory_unalloc");
    ptrAgentObj->RegisterMethod(*this,&CosaCM::COSACM_SetMDDIPOverride_ArgMemory_unalloc,"COSACM_SetMDDIPOverride_ArgMemory_unalloc");
    ptrAgentObj->RegisterMethod(*this,&CosaCM::COSACM_GetMDDIPOverride_ArgMemory_unalloc,"COSACM_GetMDDIPOverride_ArgMemory_unalloc");
    ptrAgentObj->RegisterMethod(*this,&CosaCM::COSACM_GetCMCert_ArgMemory_unalloc,"COSACM_GetCMCert_ArgMemory_unalloc");
    ptrAgentObj->RegisterMethod(*this,&CosaCM::COSACM_GetCMErrorCodewords_InvalidArg,"COSACM_GetCMErrorCodewords_InvalidArg");
    ptrAgentObj->RegisterMethod(*this,&CosaCM::COSACM_GetCMCertStatus_InvalidArg,"COSACM_GetCMCertStatus_InvalidArg");
    ptrAgentObj->RegisterMethod(*this,&CosaCM::COSACM_GetCPEList_InvalidArg,"COSACM_GetCPEList_InvalidArg");

    ptrAgentObj->RegisterMethod(*this,&CosaCM::CosaCM_GetStatus,"CosaCM_GetStatus");
    ptrAgentObj->RegisterMethod(*this,&CosaCM::CosaCM_GetLoopDiagnosticsStart,"CosaCM_GetLoopDiagnosticsStart");
    ptrAgentObj->RegisterMethod(*this,&CosaCM::CosaCM_GetLoopDiagnosticsDetails,"CosaCM_GetLoopDiagnosticsDetails");
    ptrAgentObj->RegisterMethod(*this,&CosaCM::CosaCM_GetTelephonyRegistrationStatus,"CosaCM_GetTelephonyRegistrationStatus");
    ptrAgentObj->RegisterMethod(*this,&CosaCM::CosaCM_GetTelephonyDHCPStatus,"CosaCM_GetTelephonyDHCPStatus");
    ptrAgentObj->RegisterMethod(*this,&CosaCM::CosaCM_GetTelephonyTftpStatus,"CosaCM_GetTelephonyTftpStatus");
    ptrAgentObj->RegisterMethod(*this,&CosaCM::CosaCM_SetLoopDiagnosticsStart,"CosaCM_SetLoopDiagnosticsStart");
    ptrAgentObj->RegisterMethod(*this,&CosaCM::COSACM_GetDHCPInfo,"COSACM_GetDHCPInfo");
    ptrAgentObj->RegisterMethod(*this,&CosaCM::COSACM_GetDOCSISInfo,"COSACM_GetDOCSISInfo");
    ptrAgentObj->RegisterMethod(*this,&CosaCM::COSACM_GetLog,"COSACM_GetLog");
    ptrAgentObj->RegisterMethod(*this,&CosaCM::COSACM_SetLog,"COSACM_SetLog");
    ptrAgentObj->RegisterMethod(*this,&CosaCM::COSACM_GetDocsisLog,"COSACM_GetDocsisLog");
    ptrAgentObj->RegisterMethod(*this,&CosaCM::COSACM_GetDownstreamChannel,"COSACM_GetDownstreamChannel");
    ptrAgentObj->RegisterMethod(*this,&CosaCM::COSACM_GetUpstreamChannel,"COSACM_GetUpstreamChannel");
    ptrAgentObj->RegisterMethod(*this,&CosaCM::COSACM_CableModemCreate,"COSACM_CableModemCreate");
    ptrAgentObj->RegisterMethod(*this,&CosaCM::COSACM_CableModemInitialize,"COSACM_CableModemInitialize");
    ptrAgentObj->RegisterMethod(*this,&CosaCM::COSACM_CableModemRemove,"COSACM_CableModemRemove");
    return TEST_SUCCESS;
}

/***************************************************************************
 *Function name : testmodulepre_requisites
 *Description   : testmodulepre_requisites will  be used for setting the
 *                pre-requisites that are necessary for this component
 *
 *****************************************************************************/
std::string CosaCM::testmodulepre_requisites()
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
bool CosaCM::testmodulepost_requisites()
{
    int returnValue;
    returnValue = ssp_terminate();

    if(0 != returnValue)
    {
        DEBUG_PRINT(DEBUG_TRACE,"\n testmodulepost_requisites: Failed to terminate\n");
        return 1;
    }

    return 0;
}

/*******************************************************************************************
 *
 * Function Name    : CosaCM_GetResetCount
 * Description      : This function is used to retrieve the reset count of docsis, erouter
 *                    cable modem and local reset count
 *
 * @param [in]  req - handleType : Holds the message bus handle
 * @param [in]  req - bufferType: Holds whether buffer passed is valid or NULL
 * @param [in]  req - resetType: Holds whether reset type is docsis, cable modem, erouter
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/

bool CosaCM::CosaCM_GetResetCount(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaCM_GetResetCount --->Entry \n");

    int returnValue = 0;
    int handleType = 0;
    int bufferType = 0;
    char resetType[MAX_PARAM_SIZE];

    /* Validate the input arguments */
    if(&req["handleType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }
    if(&req["bufferType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }
    if(&req["resetType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }

    handleType = req["handleType"].asInt();
    bufferType = req["bufferType"].asInt();
    strcpy(resetType,req["resetType"].asCString());

    /* Invoke the wrapper function to get the reset count */
    returnValue = ssp_CosaDmlCMGetResetCount(handleType,bufferType,resetType);
    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully retrieved the reset count";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to retrieve the reset count";
        DEBUG_PRINT(DEBUG_TRACE,"\n CosaCM_GetResetCount --->Exit\n");
        return  TEST_FAILURE;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaCM_GetResetCount  --->Exit\n");
    return TEST_SUCCESS;
}


/*******************************************************************************************
 *
 * Function Name    : CosaCM_GetUpstreamChannelId 
 * Description      : This function will retrieve the currently locked upstream channel Id
 *
 * @param [in]  req - handleType : Holds the message bus handle
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/

bool CosaCM::CosaCM_GetUpstreamChannelId(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaCM_GetUpstreamChannelId --->Entry \n");

    int returnValue = 0;
    int handleType = 0;
    
    /* Validate the input arguments */
    if(&req["handleType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }
    
    handleType = req["handleType"].asInt();
    
    returnValue = ssp_CosaDmlCMGetLockedUpstreamChID(handleType);
    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully retrieved the upstream channel Id";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to retrieve the upstream channel Id";
        DEBUG_PRINT(DEBUG_TRACE,"\n CosaCM_GetUpstreamChannelId --->Exit\n");
        return  TEST_FAILURE;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaCM_GetUpstreamChannelId  --->Exit\n");
    return TEST_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name    : CosaCM_SetUpstreamChannelId
 * Description      : This function will lock channel for the specified upstream channel Id.
 *
 * @param [in]  req - handleType : Holds the message bus handle
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/

bool CosaCM::CosaCM_SetUpstreamChannelId(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaCM_SetUpstreamChannelId --->Entry \n");

    int returnValue = 0;
    int handleType = 0;
    int channelId = 0;
    
    /* Validate the input arguments */
    if(&req["handleType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }

    if(&req["channelId"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }
    
    handleType = req["handleType"].asInt();
    channelId = req["channelId"].asInt();
    
    returnValue = ssp_CosaDmlCMSetLockedUpstreamChID(handleType,channelId);
    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully locked the channel for the upstream channel Id";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to lock channel for the upstream channel Id";
        DEBUG_PRINT(DEBUG_TRACE,"\n CosaCM_SetUpstreamChannelId --->Exit\n");
        return  TEST_FAILURE;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaCM_SetUpstreamChannelId  --->Exit\n");
    return TEST_SUCCESS;
}


/*******************************************************************************************
 *
 * Function Name    : CosaCM_GetStartDSFrequency
 * Description      : This function will retrieve the current downstream frequency
 *
 * @param [in]  req - handleType : Holds the message bus handle
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/

bool CosaCM::CosaCM_GetStartDSFrequency(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaCM_GetStartDSFrequency --->Entry \n");

    int returnValue = 0;
    int handleType = 0;
    
    /* Validate the input arguments */
    if(&req["handleType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }
    
    handleType = req["handleType"].asInt();
    
    returnValue = ssp_CosaDmlCMGetStartDSFrequency(handleType);
    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully retrieved the downstream frequency";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to retrieve the downstream ferquency";
        DEBUG_PRINT(DEBUG_TRACE,"\n CosaCM_GetStartDSFrequency --->Exit\n");
        return  TEST_FAILURE;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaCM_GetStartDSFrequency  --->Exit\n");
    return TEST_SUCCESS;
}


/*******************************************************************************************
 *
 * Function Name    : CosaCM_SetStartDSFrequency
 * Description      : This function will set the specified downstream frequency
 *
 * @param [in]  req - handleType : Holds the message bus handl
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/

bool CosaCM::CosaCM_SetStartDSFrequency(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaCM_SetStartDSFrequency --->Entry \n");

    int returnValue = 0;
    int handleType = 0;
    int frequency = 0;
    
    /* Validate the input arguments */
    if(&req["handleType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }

    if(&req["frequency"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }
    
    handleType = req["handleType"].asInt();
    frequency = req["frequency"].asInt();

    returnValue = ssp_CosaDmlCMSetStartDSFrequency(handleType,frequency);
    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully set the downstream frequency";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to set the downstream frequency";
        DEBUG_PRINT(DEBUG_TRACE,"\n CosaCM_SetStartDSFrequency --->Exit\n");
        return  TEST_FAILURE;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaCM_SetStartDSFrequency  --->Exit\n");
    return TEST_SUCCESS;
}


/*******************************************************************************************
 *
 * Function Name    : CosaCM_GetProvType
 * Description      : This function will retrieve the provisioning type
 *
 * @param [in]  req - handleType : Holds the message bus handle
 * @param [in]  req - bufferType : Holds whether buffer passed is valid or NULL
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/

bool CosaCM::CosaCM_GetProvType(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaCM_GetProvType --->Entry \n");

    int returnValue = 0;
    int handleType = 0;
    int bufferType = 0;
    
    /* Validate the input arguments */
    if(&req["handleType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }
    
    if(&req["bufferType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }
    
    handleType = req["handleType"].asInt();
    bufferType = req["bufferType"].asInt();
    
    returnValue = ssp_CosaDmlCMGetProvType(handleType,bufferType);
    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully retrieved the provisioning type";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to retrieve the provisioning type";
        DEBUG_PRINT(DEBUG_TRACE,"\n CosaCM_GetProvType --->Exit\n");
        return  TEST_FAILURE;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaCM_GetProvType  --->Exit\n");
    return TEST_SUCCESS;
}

/*******************************************************************************************
*
* Function Name    : CosaCM_GetIPv6DHCPInfo
* Description      : This function will retrieve the DHCP information of IPv6
*
* @param [in]  req - handleType : Holds the message bus handle
* @param [in]  req - bufferType : Holds whether buffer passed is valid or NULL
* @param [out] response - filled with SUCCESS or FAILURE based on the return value
*
*******************************************************************************************/

bool CosaCM::CosaCM_GetIPv6DHCPInfo(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaCM_GetIPv6DHCPInfo --->Entry \n");

    int returnValue = 0;
    int handleType = 0;
    int bufferType = 0;

    /* Validate the input arguments */
    if(&req["handleType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }

    if(&req["bufferType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }

    handleType = req["handleType"].asInt();
    bufferType = req["bufferType"].asInt();

    returnValue = ssp_CosaDmlCMGetIPv6DHCPInfo(handleType,bufferType);
    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully retrieved the DHCP information of IPv6";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to retrieve the DHCP information of IPv6";
        DEBUG_PRINT(DEBUG_TRACE,"\n CosaCM_GetIPv6DHCPInfo --->Exit\n");
        return  TEST_FAILURE;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaCM_GetIPv6DHCPInfo  --->Exit\n");
    return TEST_SUCCESS;
}


/*******************************************************************************************
*
* Function Name    : COSACM_GetMarket 
* Description      : This function will invoke COSACM_GetMarket API Function and obtain
*                    its response
* @param [in]  req - Nil
* @param [out] response - filled with SUCCESS or FAILURE based on the return value
*
*******************************************************************************************/

bool CosaCM::COSACM_GetMarket(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_GetMarket--->Entry \n");

    int returnValue = 0;

    returnValue = ssp_cosacm_getmarket();

    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully retrieved the DUT Market Information";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to retrieve the DUT Market Information";
        DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_GetMarket --->Exit\n");
        return  TEST_FAILURE;
    }

    DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_GetMarket --->Exit\n");

    return TEST_SUCCESS;
}

/*******************************************************************************************
*
* Function Name    : CosaDmlCMSetMDDIPOverride 
* Description      : This function will invoke the CosaDmlCMSetMDDIPOverride API Function
*                    and obtain its response
* @param [in]  req - Nil
* @param [out] response - filled with SUCCESS or FAILURE based on the return value
*
*******************************************************************************************/

bool CosaCM::COSACM_SetMDDIPOverride(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_SetMDDIPOverride --->Entry \n");

    int returnValue = 0;

    returnValue = ssp_cosacm_setmddipoverride();

    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully Set the MDD IP Override Function";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to Set the MDD IP Override Function";
        DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_SetMDDIPOverride --->Exit\n");
        return  TEST_FAILURE;
    }

    DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_SetMDDIPOverride --->Exit\n");

    return TEST_SUCCESS;
}

/*******************************************************************************************
*
* Function Name    : COSACM_GetMDDIPOverride 
* Description      : This function will invoke the COSACM_GetMDDIPOverride API Function
*                    and obtain its response
* @param [in]  req - Nil
* @param [out] response - filled with SUCCESS or FAILURE based on the return value
*
*******************************************************************************************/

bool CosaCM::COSACM_GetMDDIPOverride(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_GetMDDIPOverride --->Entry \n");

    int returnValue = 0;

    returnValue = ssp_cosacm_getmddipoverride();

    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully Get the MDD IP Override Function";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to Get the MDD IP Override Function";
        DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_GetMDDIPOverride --->Exit\n");
        return  TEST_FAILURE;
    }

    DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_GetMDDIPOverride --->Exit\n");

    return TEST_SUCCESS;
}

/*******************************************************************************************
*
* Function Name    : COSACM_GetCMCert 
* Description      : This function will invoke the COSACM_GetCMCert API Function
*                    and obtain its response
* @param [in]  req - Nil
* @param [out] response - filled with SUCCESS or FAILURE based on the return value
*
*******************************************************************************************/

bool CosaCM::COSACM_GetCMCert(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_GetCMCert --->Entry \n");

    int returnValue = 0;

    returnValue = ssp_cosacm_getcert();

    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully Executed and Get the CM Certificate";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to Get the CM Certificate";
        DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_GetCMCert --->Exit\n");
        return  TEST_FAILURE;
    }

    DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_GetCMCert --->Exit\n");

    return TEST_SUCCESS;
}

/*******************************************************************************************
*
* Function Name    : COSACM_GetCMCertStatus 
* Description      : This function will invoke the COSACM_GetCMCertStatus API Function
*                    and obtain its response
* @param [in]  req - Nil
* @param [out] response - filled with SUCCESS or FAILURE based on the return value
*
*******************************************************************************************/

bool CosaCM::COSACM_GetCMCertStatus(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_GetCMCertStatus --->Entry \n");

    int returnValue = 0;

    returnValue = ssp_cosacm_getcertstatus();

    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully Executed and Get the CM Certificate Status Info";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to Get the CM Certificate Status Information";
        DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_GetCMCertStatus --->Exit\n");
        return  TEST_FAILURE;
    }

    DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_GetCMCertStatus --->Exit\n");

    return TEST_SUCCESS;
}

/*******************************************************************************************
*
* Function Name    : COSACM_GetCMErrorCodewords 
* Description      : This function will invoke the COSACM_GetCMErrorCodewords API Function
*                    and obtain its response
* @param [in]  req - Nil
* @param [out] response - filled with SUCCESS or FAILURE based on the return value
*
*******************************************************************************************/

bool CosaCM::COSACM_GetCMErrorCodewords(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_GetCMErrorCodewords --->Entry \n");

    int returnValue = 0;

    returnValue = ssp_cosacm_getcmerrorcodewords();

    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully Get the CM Error Code Words Info";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to Get the CM Error Code Words Info";
        DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_GetCMErrorCodewords --->Exit\n");
        return  TEST_FAILURE;
    }

    DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_GetCMErrorCodewords --->Exit\n");

    return TEST_SUCCESS;
}


/*******************************************************************************************
*
* Function Name    : COSACM_GetCPEList 
* Description      : This function will invoke the COSACM_GetCPEList API Function
*                    and obtain its response
* @param [in]  req - Nil
* @param [out] response - filled with SUCCESS or FAILURE based on the return value
*
*******************************************************************************************/

bool CosaCM::COSACM_GetCPEList(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_GetCPEList --->Entry \n");

    int returnValue = 0;

    returnValue = ssp_cosacm_getcpelist();

    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully Get the CPE List information";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to Get the CPE List Information";
        DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_GetCPEList --->Exit\n");
        return  TEST_FAILURE;
    }

    DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_GetCPEList --->Exit\n");

    return TEST_SUCCESS;
}



/*******************************************************************************************
*
* Function Name    : COSACM_GetMarket_ArgMemory_unalloc 
* Description      : This function will invoke COSACM_GetMarket API Function and obtain
*                    its response
* @param [in]  req - Nil
* @param [out] response - filled with SUCCESS or FAILURE based on the return value
*
*******************************************************************************************/

bool CosaCM::COSACM_GetMarket_ArgMemory_unalloc(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_GetMarket_ArgMemory_unalloc --->Entry \n");

    int returnValue = 0;

    returnValue = ssp_cosacm_getmarket_memory_unalloc();

    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully handled the input memory unallocated case";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to handle the input memory unallocated case";
        DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_GetMarket_ArgMemory_unalloc --->Exit\n");
        return  TEST_FAILURE;
    }

    DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_GetMarket_ArgMemory_unalloc --->Exit\n");

    return TEST_SUCCESS;
}

/*******************************************************************************************
*
* Function Name    : COSACM_SetMDDIPOverride_ArgMemory_unalloc
* Description      : This function will invoke the COSACM_SetMDDIPOverride API Function
*                    and obtain its response
* @param [in]  req - Nil
* @param [out] response - filled with SUCCESS or FAILURE based on the return value
*
*******************************************************************************************/

bool CosaCM::COSACM_SetMDDIPOverride_ArgMemory_unalloc(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_SetMDDIPOverride_ArgMemory_unalloc --->Entry \n");

    int returnValue = 0;

    returnValue = ssp_cosacm_setmddipoverride_memory_unalloc();

    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully handled the input memory unallocated case";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to handle the input memory unallocated case";
        DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_SetMDDIPOverride_ArgMemory_unalloc --->Exit\n");
        return  TEST_FAILURE;
    }

    DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_SetMDDIPOverride_ArgMemory_unalloc --->Exit\n");

    return TEST_SUCCESS;
}

/*******************************************************************************************
*
* Function Name    : COSACM_GetMDDIPOverride_ArgMemory_unalloc 
* Description      : This function will invoke the COSACM_GetMDDIPOverride API Function
*                    and obtain its response
* @param [in]  req - Nil
* @param [out] response - filled with SUCCESS or FAILURE based on the return value
*
*******************************************************************************************/

bool CosaCM::COSACM_GetMDDIPOverride_ArgMemory_unalloc(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_GetMDDIPOverride --->Entry \n");

    int returnValue = 0;

    returnValue = ssp_cosacm_getmddipoverride_memory_unalloc();

    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully handled the input memory unallocated case";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to handle the input memory unallocated case";
        DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_GetMDDIPOverride_ArgMemory_unalloc --->Exit\n");
        return  TEST_FAILURE;
    }

    DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_GetMDDIPOverride_ArgMemory_unalloc --->Exit\n");

    return TEST_SUCCESS;
}

/*******************************************************************************************
*
* Function Name    : COSACM_GetCMCert_ArgMemory_unalloc 
* Description      : This function will invoke the COSACM_GetCMCert API Function
*                    and obtain its response
* @param [in]  req - Nil
* @param [out] response - filled with SUCCESS or FAILURE based on the return value
*
*******************************************************************************************/

bool CosaCM::COSACM_GetCMCert_ArgMemory_unalloc(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_GetCMCert_ArgMemory_unalloc --->Entry \n");

    int returnValue = 0;

    returnValue = ssp_cosacm_getcert_memory_unalloc();

    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully handled the input memory unallocated case";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to handle the input memory unallocated case";
        DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_GetCMCert_ArgMemory_unalloc --->Exit\n");
        return  TEST_FAILURE;
    }

    DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_GetCMCert_ArgMemory_unalloc --->Exit\n");

    return TEST_SUCCESS;
}

/*******************************************************************************************
*
* Function Name    : COSACM_GetCMCertStatus_InvalidArg 
* Description      : This function will invoke the COSACM_GetCMCertStatus API Function
*                    and obtain its response
* @param [in]  req - Nil
* @param [out] response - filled with SUCCESS or FAILURE based on the return value
*
*******************************************************************************************/

bool CosaCM::COSACM_GetCMCertStatus_InvalidArg(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_GetCMCertStatus_InvalidArg--->Entry \n");

    int returnValue = 0;

    returnValue = ssp_cosacm_getcertstatus_invalid_arg();

    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully handled the invalid input argument";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to handle the invalid input argument";
        DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_GetCMCertStatus_InvalidArg --->Exit\n");
        return  TEST_FAILURE;
    }

    DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_GetCMCertStatus_InvalidArg--->Exit\n");

    return TEST_SUCCESS;
}

/*******************************************************************************************
*
* Function Name    : COSACM_GetCMErrorCodewords_InvalidArg 
* Description      : This function will invoke the COSACM_GetCMErrorCodewords API Function
*                    and obtain its response
* @param [in]  req - Nil
* @param [out] response - filled with SUCCESS or FAILURE based on the return value
*
*******************************************************************************************/

bool CosaCM::COSACM_GetCMErrorCodewords_InvalidArg(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_GetCMErrorCodewords_InvalidArg --->Entry \n");

    int returnValue = 0;

    returnValue = ssp_cosacm_getcmrrrorcodewords_invalid_arg();

    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully handled the invalid input argument";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to handle the invalid input argument";
        DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_GetCMErrorCodewords_InvalidArg --->Exit\n");
        return  TEST_FAILURE;
    }

    DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_GetCMErrorCodewords_InvalidArg --->Exit\n");

    return TEST_SUCCESS;
}


/*******************************************************************************************
*
* Function Name    : COSACM_GetCPEList_InvalidArg 
* Description      : This function will invoke the COSACM_GetCPEList API Function
*                    and obtain its response
* @param [in]  req - Nil
* @param [out] response - filled with SUCCESS or FAILURE based on the return value
*
*******************************************************************************************/

bool CosaCM::COSACM_GetCPEList_InvalidArg(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_GetCPEList_InvalidArg --->Entry \n");

    int returnValue = 0;

    returnValue = ssp_cosacm_getcpelist_invalid_arg();

    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully handled the invalid input argument";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to handle the invalid input argument";
        DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_GetCPEList_InvalidArg --->Exit\n");
        return  TEST_FAILURE;
    }

    DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_GetCPEList_InvalidArg --->Exit\n");

    return TEST_SUCCESS;
}

/*******************************************************************************************
*
* Function Name    : CosaCM_GetStatus
* Description      : This function will retrieve the DHCP information of IPv6
*
* @param [in]  req - handleType : Holds the message bus handle
* @param [in]  req - bufferType : Holds whether buffer passed is valid or NULL
* @param [out] response - filled with SUCCESS or FAILURE based on the return value
*
*******************************************************************************************/

bool CosaCM::CosaCM_GetStatus(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaCM_GetStatus --->Entry \n");

    int returnValue = 0;
    int handleType = 0;
    int Value = 0;

    /* Validate the input arguments */
    if(&req["handleType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }

    if(&req["Value"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }

    handleType = req["handleType"].asInt();
    Value = req["Value"].asInt();

    returnValue =ssp_CosaDmlCMGetStatus(handleType,Value);
    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully got CM Status";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to get CM Status";
        DEBUG_PRINT(DEBUG_TRACE,"\n CosaCM_GetStatus --->Exit\n");
        return  TEST_FAILURE;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaCM_GetStatus  --->Exit\n");
    return TEST_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name    : CosaCM_GetLoopDiagnosticsStart
 * Description      : This function will get the Loop Diagnostics Start
 * @param [in]  req - handleType : Holds the message bus handle
 * @param [in]  req - boolValue : Holds whether buffer passed is valid or NULL
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/

bool CosaCM::CosaCM_GetLoopDiagnosticsStart(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaCM_GetLoopDiagnosticsStart --->Entry \n");

    int returnValue = 0;
    int handleType = 0;
    int boolValue = 0;

    /* Validate the input arguments */
    if(&req["handleType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }

    if(&req["boolValue"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }

    handleType = req["handleType"].asInt();
    boolValue = req["boolValue"].asInt();

    returnValue =ssp_CosaCMGetLoopDiagnosticsStart(handleType,boolValue);
    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully got the Loop Diagnostics Start";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to get the Loop Diagnostics Start";
        DEBUG_PRINT(DEBUG_TRACE,"\n CosaCM_GetLoopDiagnosticsStart --->Exit\n");
        return  TEST_FAILURE;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaCM_GetLoopDiagnosticsStart  --->Exit\n");
    return TEST_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name    : CosaCM_GetLoopDiagnosticsDetails
 * Description      : This function will get the Loop Diagnostics Details
 * @param [in]  req - handleType : Holds the message bus handle
 * @param [in]  req - bufferType : Holds whether buffer passed is valid or NULL
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/

bool CosaCM::CosaCM_GetLoopDiagnosticsDetails(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaCM_GetLoopDiagnosticsDetails --->Entry \n");

    int returnValue = 0;
    int handleType = 0;
    int bufferType = 0;

    /* Validate the input arguments */
    if(&req["handleType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }
    if(&req["bufferType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }

    handleType = req["handleType"].asInt();
    bufferType = req["bufferType"].asInt();

    returnValue =ssp_CosaDmlCMGetLoopDiagnosticsDetails(handleType,bufferType);
    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully got the Loop Diagnostics Details";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to get the Loop Diagnostics Details";
        DEBUG_PRINT(DEBUG_TRACE,"\n CosaCM_GetLoopDiagnosticsDetails --->Exit\n");
        return  TEST_FAILURE;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaCM_GetLoopDiagnosticsDetails  --->Exit\n");
    return TEST_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name    : CosaCM_GetTelephonyRegistrationStatus
 * Description      : This function will get Telephony Registration Status.
 * @param [in]  req - handleType : Holds the message bus handle
 * @param [in]  req - bufferType : Holds whether buffer passed is valid or NULL
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/

bool CosaCM::CosaCM_GetTelephonyRegistrationStatus(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaCM_GetTelephonyRegistrationStatus --->Entry \n");

    int returnValue = 0;
    int handleType = 0;
    int bufferType = 0;

    /* Validate the input arguments */
    if(&req["handleType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }
    if(&req["bufferType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }

    handleType = req["handleType"].asInt();
    bufferType = req["bufferType"].asInt();

    returnValue =ssp_CosaDmlCMGetTelephonyRegistrationStatus(handleType,bufferType);
    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully got Telephony Registration Status";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to get Telephony Registration Status";
        DEBUG_PRINT(DEBUG_TRACE,"\n CosaCM_GetTelephonyRegistrationStatus --->Exit\n");
        return  TEST_FAILURE;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaCM_GetTelephonyRegistrationStatus  --->Exit\n");
    return TEST_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name    : CosaCM_GetTelephonyTftpStatus
 * Description      : This function will get Telephony Tftp Status.
 * @param [in]  req - handleType : Holds the message bus handle
 * @param [in]  req - bufferType : Holds whether buffer passed is valid or NULL
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/

bool CosaCM::CosaCM_GetTelephonyTftpStatus(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaCM_GetTelephonyTftpStatus --->Entry \n");

    int returnValue = 0;
    int handleType = 0;
    int bufferType = 0;

    /* Validate the input arguments */
    if(&req["handleType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }
    if(&req["bufferType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }

    handleType = req["handleType"].asInt();
    bufferType = req["bufferType"].asInt();

    returnValue =ssp_CosaDmlCMGetTelephonyTftpStatus(handleType,bufferType);
    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully got Telephony Tftp Status";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to get Telephony Tftp Status";
        DEBUG_PRINT(DEBUG_TRACE,"\n CosaCM_GetTelephonyTftpStatus --->Exit\n");
        return  TEST_FAILURE;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaCM_GetTelephonyTftpStatus  --->Exit\n");
    return TEST_SUCCESS;
}

/*******************************************************************************************
 * Function Name    : CosaCM_GetTelephonyDHCPStatus
 * Description      : This function will get Telephony DHCP Status.
 * @param [in]  req - handleType : Holds the message bus handle
 * @param [in]  req - bufferType : Holds whether buffer passed is valid or NULL
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/

bool CosaCM::CosaCM_GetTelephonyDHCPStatus(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaCM_GetTelephonyDHCPStatus --->Entry \n");

    int returnValue = 0;
    int handleType = 0;
    int bufferType = 0;

    /* Validate the input arguments */
    if(&req["handleType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }
    if(&req["bufferType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }

    handleType = req["handleType"].asInt();
    bufferType = req["bufferType"].asInt();

    returnValue =ssp_CosaDmlCMGetTelephonyDHCPStatus(handleType,bufferType);
    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully got Telephony DHCP Status";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to get Telephony DHCP Status";
        DEBUG_PRINT(DEBUG_TRACE,"\n CosaCM_GetTelephonyDHCPStatus --->Exit\n");
        return  TEST_FAILURE;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaCM_GetTelephonyDHCPStatus  --->Exit\n");
    return TEST_SUCCESS;
}

/*******************************************************************************************
 * Function Name    : CosaCM_SetLoopDiagnosticsStart
 * Description      : This function will set Loop Diagnostics Start.
 * @param [in]  req - handleType : Holds the message bus handle
 * @param [in]  req - boolValue : 
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/

bool CosaCM::CosaCM_SetLoopDiagnosticsStart(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaCM_SetLoopDiagnosticsStart --->Entry \n");

    int returnValue = 0;
    int handleType = 0;
    int boolValue = 0;

    /* Validate the input arguments */
    if(&req["handleType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }
    if(&req["boolValue"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }

    handleType = req["handleType"].asInt();
    boolValue = req["boolValue"].asInt();

    returnValue =ssp_CosaDmlCMSetLoopDiagnosticsStart(handleType,boolValue);
    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully Set Loop Diagnostics Start value";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to Set Loop Diagnostics Start value";
        DEBUG_PRINT(DEBUG_TRACE,"\n CosaCM_SetLoopDiagnosticsStart --->Exit\n");
        return  TEST_FAILURE;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n CosaCM_SetLoopDiagnosticsStart  --->Exit\n");
    return TEST_SUCCESS;
}

/*******************************************************************************************
*
* Function Name    : COSACM_GetDHCPInfo
* Description      : This function will retrieve the DHCP information
*
* @param [in]  req - handleType : Holds the message bus handle
* @param [in]  req - bufferType : Holds whether buffer passed is valid or NULL
* @param [out] response - filled with SUCCESS or FAILURE based on the return value
*
*******************************************************************************************/

bool CosaCM::COSACM_GetDHCPInfo(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_GetDHCPInfo --->Entry \n");

    int returnValue = 0;
    int handleType = 0;
    int bufferType = 0;

    /* Validate the input arguments */
    if(&req["handleType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }

    if(&req["bufferType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }

    handleType = req["handleType"].asInt();
    bufferType = req["bufferType"].asInt();
    returnValue = ssp_cosacm_GetDHCPInfo(handleType,bufferType);
    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully retrieved the DHCP information";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to retrieve the DHCP information";
        DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_GetDHCPInfo --->Exit\n");
        return  TEST_FAILURE;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_GetDHCPInfo  --->Exit\n");
    return TEST_SUCCESS;
}

/*******************************************************************************************
*
* Function Name    : COSACM_GetDOCSISInfo
* Description      : This function will retrieve the DOCSIS information
*
* @param [in]  req - handleType : Holds the message bus handle
* @param [in]  req - bufferType : Holds whether buffer passed is valid or NULL
* @param [out] response - filled with SUCCESS or FAILURE based on the return value
*
*******************************************************************************************/

bool CosaCM::COSACM_GetDOCSISInfo(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_GetDOCSISInfo --->Entry \n");

    int returnValue = 0;
    int handleType = 0;
    int bufferType = 0;

    /* Validate the input arguments */
    if(&req["handleType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }

    if(&req["bufferType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }

    handleType = req["handleType"].asInt();
    bufferType = req["bufferType"].asInt();

    returnValue = ssp_cosacm_GetDOCSISInfo(handleType,bufferType);
    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully retrieved the DOCSIS information";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to retrieve the DOCSIS information";
        DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_GetDOCSISInfo --->Exit\n");
        return  TEST_FAILURE;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_GetDOCSISInfo  --->Exit\n");
    return TEST_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name    : COSACM_GetLog
 * Description      : This function will retrieve the Log information
 *
 * @param [in]  req - handleType : Holds the message bus handle
 * @param [in]  req - bufferType : Holds whether buffer passed is valid or NULL
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/

bool CosaCM::COSACM_GetLog(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_GetLog --->Entry \n");

    int returnValue = 0;
    int handleType = 0;
    int bufferType = 0;

    /* Validate the input arguments */
    if(&req["handleType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }

    if(&req["bufferType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }

    handleType = req["handleType"].asInt();
    bufferType = req["bufferType"].asInt();
    returnValue = ssp_cosacm_GetLog(handleType,bufferType);
    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully retrieved the Log information";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to retrieve the Log information";
        DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_GetLog --->Exit\n");
        return  TEST_FAILURE;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_GetLog  --->Exit\n");
    return TEST_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name    : COSACM_SetLog
 * Description      : This function will set the log information
 *
 * @param [in]  req - handleType : Holds the message bus handle
 * @param [in]  req - bufferType : Holds whether buffer passed is valid or NULL
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/

bool CosaCM::COSACM_SetLog(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_SetLog --->Entry \n");

    int returnValue = 0;
    int handleType = 0;
    int bufferType = 0;

    /* Validate the input arguments */
    if(&req["handleType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }

    if(&req["bufferType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }

    handleType = req["handleType"].asInt();
    bufferType = req["bufferType"].asInt();

    returnValue = ssp_cosacm_SetLog(handleType,bufferType);
    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully set the log information";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to set the log information";
        DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_SetLog --->Exit\n");
        return  TEST_FAILURE;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_SetLog  --->Exit\n");
    return TEST_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name    : COSACM_GetDocsisLog
 * Description      : This function will get the DOCSIS log information
 *
 * @param [in]  req - handleType : Holds the message bus handle
 * @param [in]  req - bufferType : Holds whether buffer passed is valid or NULL
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/

bool CosaCM::COSACM_GetDocsisLog(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_GetDocsisLog --->Entry \n");

    int returnValue = 0;
    int handleType = 0;
    int bufferType = 0;
    /* Validate the input arguments */
    if(&req["handleType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }

    if(&req["bufferType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }

    handleType = req["handleType"].asInt();
    bufferType = req["bufferType"].asInt();

    returnValue = ssp_cosacm_GetDocsisLog(handleType,bufferType);
    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully retrieved the DOCSIS Log information";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to retrieve the DOCSIS Log information";
        DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_GetDocsisLog --->Exit\n");
        return  TEST_FAILURE;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_GetDocsisLog  --->Exit\n");
    return TEST_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name    : COSACM_GetDownstreamChannel
 * Description      : This function will get the Downstream channel information
 *
 * @param [in]  req - handleType : Holds the message bus handle
 * @param [in]  req - bufferType : Holds whether buffer passed is valid or NULL
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/

bool CosaCM::COSACM_GetDownstreamChannel(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_GetDownstreamChannel --->Entry \n");

    int returnValue = 0;
    int handleType = 0;
    int bufferType = 0;

    /* Validate the input arguments */
    if(&req["handleType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }

    if(&req["bufferType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }

    handleType = req["handleType"].asInt();
    bufferType = req["bufferType"].asInt();
    printf("handleType %d\nbufferType %d\n",handleType,bufferType);

    returnValue = ssp_cosacm_GetDownstreamChannel(handleType,bufferType);
    printf("return value is %d\n",returnValue);
    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully retrieved the Downstream channel information";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to retrieve the Downstream channel information";
        DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_GetDownstreamChannel --->Exit\n");
        return  TEST_FAILURE;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_GetDownstreamChannel  --->Exit\n");
    return TEST_SUCCESS;
}
/*******************************************************************************************
 *
 * Function Name    : COSACM_GetUpstreamChannel
 * Description      : This function will get the Upstream channel information
 *
 * @param [in]  req - handleType : Holds the message bus handle
 * @param [in]  req - bufferType : Holds whether buffer passed is valid or NULL
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/
bool CosaCM::COSACM_GetUpstreamChannel(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_GetUpstreamChannel --->Entry \n");

    int returnValue = 0;
    int handleType = 0;
    int bufferType = 0;

    /* Validate the input arguments */
    if(&req["handleType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }

    if(&req["bufferType"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL parameter as input argument";
        return TEST_FAILURE;
    }

    handleType = req["handleType"].asInt();
    bufferType = req["bufferType"].asInt();

    returnValue = ssp_cosacm_GetUpstreamChannel(handleType,bufferType);
    if(0 == returnValue)
    {
        printf("Successfully retrieved the Upstream channel information\n");
        response["result"]="SUCCESS";
        response["details"]="Successfully retrieved the Upstream channel information";
    }
    else
    {
        printf("Failed to retrieve the Upstream channel information\n");
        response["result"]="FAILURE";
        response["details"]="Failed to retrieve the Upstream channel information";
        DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_GetUpstreamChannel --->Exit\n");
        return  TEST_FAILURE;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_GetUpstreamChannel  --->Exit\n");
    return TEST_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name    : COSACM_CableModemCreate
 * Description      : This function will execute cable modem create 
 *
 * @param [in]  req - handleType : Holds the message bus handle
 * @param [in]  req - bufferType : Holds whether buffer passed is valid or NULL
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/
 
bool CosaCM::COSACM_CableModemCreate(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_CableModemCreate --->Entry \n");

    int returnValue = 0; 
    returnValue = ssp_CosaCableModemCreate();
    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully executed Cable Modem Create";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to execute Cable Modem Create";
        DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_CableModemCreate --->Exit\n");
        return  TEST_FAILURE;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_CableModemCreate  --->Exit\n");
    return TEST_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name    : CosaCableModemInitialize
 * Description      : This function will execute the cable modem initialize 

 * @param [in]  req - handleType : Holds the message bus handle
 * @param [in]  req - bufferType : Holds whether buffer passed is valid or NULL
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/
 
bool CosaCM::COSACM_CableModemInitialize(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_CableModemInitialize --->Entry \n");

    int returnValue = 0;
    int handleType = 0;
    handleType = req["handleType"].asInt();
    printf("\nhandleType is %d\n",handleType);
    returnValue = ssp_CosaCableModemInitialize(handleType);
    printf("\nreturnValue is %d\n",returnValue);
    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully executed Cable Modem Initialize";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to execute Cable Modem Initialize";
        DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_CableModemInitialize --->Exit\n");
        return  TEST_FAILURE;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_CableModemInitialize  --->Exit\n");
    return TEST_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name    : COSACM_CableModemRemove
 * Description      : This will execute cable modem remove
 *
 * @param [in]  req - handleType : Holds the message bus handle
 * @param [in]  req - bufferType : Holds whether buffer passed is valid or NULL
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value
 *
 *******************************************************************************************/
 
bool CosaCM::COSACM_CableModemRemove(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_CableModemRemove  --->Entry \n");

    int returnValue = 0;
    int handleType = 0;
    handleType = req["handleType"].asInt();
    
    returnValue = ssp_CosaCableModemRemove(handleType);
    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="Successfully executed Cable Modem Remove";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="Failed to execute Cable Modem Remove";
        DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_CableModemRemove --->Exit\n");
        return  TEST_FAILURE;
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n COSACM_CableModemRemove --->Exit\n");
    return TEST_SUCCESS;
}

/**************************************************************************
 * Function Name	: CreateObject
 * Description	: This function will be used to create a new object for the
 *	                class "CosaCM".
 *
 **************************************************************************/

extern "C" CosaCM* CreateObject()
{
    return new CosaCM();
}

/**************************************************************************
 * Function Name : cleanup
 * Description   : This function will be used to clean the log details. 
 *
 **************************************************************************/

bool CosaCM::cleanup(IN const char* szVersion,IN RDKTestAgent *ptrAgentObj)
{
    DEBUG_PRINT(DEBUG_LOG,"CosaCM shutting down\n");
    if(ptrAgentObj==NULL)
    {
        return TEST_FAILURE;
    }
    /*unRegister stub function for callback*/

    ptrAgentObj->UnregisterMethod("CosaCM_GetResetCount");
    ptrAgentObj->UnregisterMethod("CosaCM_GetUpstreamChannelId");
    ptrAgentObj->UnregisterMethod("CosaCM_SetUpstreamChannelId");
    ptrAgentObj->UnregisterMethod("CosaCM_GetStartDSFrequency");
    ptrAgentObj->UnregisterMethod("CosaCM_SetStartDSFrequency");
    ptrAgentObj->UnregisterMethod("CosaCM_GetProvType"); 
    ptrAgentObj->UnregisterMethod("CosaCM_GetIPv6DHCPInfo");

    ptrAgentObj->UnregisterMethod("COSACM_GetMarket");
    ptrAgentObj->UnregisterMethod("COSACM_SetMDDIPOverride");
    ptrAgentObj->UnregisterMethod("COSACM_GetMDDIPOverride");
    ptrAgentObj->UnregisterMethod("COSACM_GetCMCert");
    ptrAgentObj->UnregisterMethod("COSACM_GetCMErrorCodewords");
    ptrAgentObj->UnregisterMethod("COSACM_GetCMCertStatus");
    ptrAgentObj->UnregisterMethod("COSACM_GetCPEList");

    ptrAgentObj->UnregisterMethod("COSACM_GetMarket_ArgMemory_unalloc");
    ptrAgentObj->UnregisterMethod("COSACM_SetMDDIPOverride_ArgMemory_unalloc");
    ptrAgentObj->UnregisterMethod("COSACM_GetMDDIPOverride_ArgMemory_unalloc");
    ptrAgentObj->UnregisterMethod("COSACM_GetCMCert_ArgMemory_unalloc");
    ptrAgentObj->UnregisterMethod("COSACM_GetCMErrorCodewords_InvalidArg");
    ptrAgentObj->UnregisterMethod("COSACM_GetCMCertStatus_InvalidArg");
    ptrAgentObj->UnregisterMethod("COSACM_GetCPEList_InvalidArg");

    ptrAgentObj->UnregisterMethod("CosaCM_GetStatus");
    ptrAgentObj->UnregisterMethod("CosaCM_GetLoopDiagnosticsStart");
    ptrAgentObj->UnregisterMethod("CosaCM_GetLoopDiagnosticsDetails");
    ptrAgentObj->UnregisterMethod("CosaCM_GetTelephonyTftpStatus");
    ptrAgentObj->UnregisterMethod("CosaCM_GetTelephonyRegistrationStatus");
    ptrAgentObj->UnregisterMethod("CosaCM_GetTelephonyDHCPStatus");
    ptrAgentObj->UnregisterMethod("CosaCM_SetLoopDiagnosticsStart");
    ptrAgentObj->UnregisterMethod("COSACM_GetDHCPInfo");
    ptrAgentObj->UnregisterMethod("COSACM_GetDOCSISInfo");
    ptrAgentObj->UnregisterMethod("COSACM_GetLog");
    ptrAgentObj->UnregisterMethod("COSACM_SetLog");
    ptrAgentObj->UnregisterMethod("COSACM_GetDocsisLog");
    ptrAgentObj->UnregisterMethod("COSACM_GetDownstreamChannel");
    ptrAgentObj->UnregisterMethod("COSACM_GetUpstreamChannel");
    ptrAgentObj->UnregisterMethod("COSACM_CableModemCreate");
    ptrAgentObj->UnregisterMethod("COSACM_CableModemInitialize");
    ptrAgentObj->UnregisterMethod("COSACM_CableModemRemove");
    return TEST_SUCCESS;
}

/**************************************************************************
 * Function Name : DestroyObject
 * Description   : This function will be used to destroy the object. 
 *
 **************************************************************************/
extern "C" void DestroyObject(CosaCM *stubobj)
{
    DEBUG_PRINT(DEBUG_LOG,"Destroying CosaCM object\n");
    delete stubobj;
}

