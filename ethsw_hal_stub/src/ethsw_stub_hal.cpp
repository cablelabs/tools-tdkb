/*
 * Copyright 2016-2017 Intel Corporation
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
#include "ethsw_stub_hal.h"

#define WAIT_TIME 5
#define MAX_BUFFER_SIZE 128
#define MAX_STRING_SIZE 64
#define MAX_BUFFER_SIZE_TO_SEND 512
#define MAXBITRATE_10    10
#define MAXBITRATE_100   100
#define MAXBITRATE_1000  1000
#define MAXBITRATE_10000 10000
#define RETURN_SUCCESS 0
#define RETURN_FAILURE 1
#define TEST_SUCCESS true
#define TEST_FAILURE false

#define CHECK_PARAM_AND_RET(x) if ((x) == NULL) \
{ \
      DEBUG_PRINT(DEBUG_ERROR,"!!!NULL Pointer!!! :: %s:%d\n", __func__, __LINE__); \
      return TEST_FAILURE; \
}

/*************************************************************************
 *Function name : ethsw_stub_hal::ethsw_stub_hal
 *Description   : Constructor for Platform class
 *@param [in]   : None
 ***************************************************************************/
ethsw_stub_hal::ethsw_stub_hal()
{
	DEBUG_PRINT(DEBUG_TRACE, "ethsw_stub_hal Initialized\n");
}

/********************************************************************************************
 *Function name : testmodulepre_requisites
 *Description   : testmodulepre_requisites will  be used for registering TDK with the CR 
 *@param [in]   : None
 *@param [out]  : Return string "SUCCESS" in case of success else return string "FAILURE"
 **********************************************************************************************/
std::string ethsw_stub_hal::testmodulepre_requisites()
{
	/*Dummy function required as it is pure virtual. No need to register with CCSP bus for HAL*/
	return "SUCCESS";

}

/**********************************************************************************************
 *Function name : testmodulepost_requisites
 *Description   : testmodulepost_requisites will be used for unregistering TDK with the CR 
 *@param [in]   : None
 *@param [out]  : Return TEST_SUCCESS or TEST_FAILURE based on the return value
 **********************************************************************************************/
bool ethsw_stub_hal::testmodulepost_requisites()
{
	/*Dummy function required as it is pure virtual. No need to register with CCSP bus for HAL*/
	return TEST_SUCCESS;
}

/***************************************************************************************
 *Function name : ethsw_stub_hal_Init
 *Description   : This function is used to register all the ethsw_stub_hal methods. 
 *param [in]    : szVersion - version, ptrAgentObj - Agent obhect
 *@param [out]  : Return TEST_SUCCESS or TEST_FAILURE
 ***************************************************************************************/
bool ethsw_stub_hal::initialize(IN const char* szVersion,IN RDKTestAgent *ptrAgentObj)
{
	DEBUG_PRINT(DEBUG_TRACE, "ethsw_stub_hal Initialize----->Entry\n");
	CHECK_PARAM_AND_RET(szVersion);
	CHECK_PARAM_AND_RET(ptrAgentObj);

	ptrAgentObj->RegisterMethod(*this,&ethsw_stub_hal::ethsw_stub_hal_Get_Port_Admin_Status,
					"ethsw_stub_hal_Get_Port_Admin_Status");
	ptrAgentObj->RegisterMethod(*this,&ethsw_stub_hal::ethsw_stub_hal_Get_Port_Cfg,
					"ethsw_stub_hal_Get_Port_Cfg");
	ptrAgentObj->RegisterMethod(*this,&ethsw_stub_hal::ethsw_stub_hal_Get_Port_Status,
					"ethsw_stub_hal_Get_Port_Status");
	ptrAgentObj->RegisterMethod(*this,&ethsw_stub_hal::ethsw_stub_hal_Init,
					"ethsw_stub_hal_Init");
	ptrAgentObj->RegisterMethod(*this,&ethsw_stub_hal::ethsw_stub_hal_LocatePort_By_MacAddress,
					"ethsw_stub_hal_LocatePort_By_MacAddress");
	ptrAgentObj->RegisterMethod(*this,&ethsw_stub_hal::ethsw_stub_hal_SetAgingSpeed,
					"ethsw_stub_hal_SetAgingSpeed");
	ptrAgentObj->RegisterMethod(*this,&ethsw_stub_hal::ethsw_stub_hal_SetPortAdminStatus,
					"ethsw_stub_hal_SetPortAdminStatus");
	ptrAgentObj->RegisterMethod(*this,&ethsw_stub_hal::ethsw_stub_hal_SetPortCfg,
					"ethsw_stub_hal_SetPortCfg");

	DEBUG_PRINT(DEBUG_TRACE, "ethsw_stub_hal Initialize----->Exit\n");

	return TEST_SUCCESS;
}

/*****************************************************************************************************
 *Function name : ethsw_stub_hal_Get_Port_Admin_Status
 *Description   : This function will invoke the SSP  HAL wrapper to get the ethsw port admin status
 *@param [in]   : req - It will give port id (port number) and flag(for negative scenario)
 *@param [out]  : response - filled with SUCCESS or FAILURE based on the return value
 *******************************************************************************************************/
bool ethsw_stub_hal::ethsw_stub_hal_Get_Port_Admin_Status(IN const Json::Value& req, OUT Json::Value& response)
{
	int portID = 0;
	char getAdminStatus[MAX_STRING_SIZE] = {0};
	int isNegativeScenario = 0;

	DEBUG_PRINT(DEBUG_TRACE,"Inside Function ethsw_stub_hal_Get_Port_Admin_Status stub\n");
	if(&req["PortID"] == NULL)
	{
		response["result"] = "FAILURE";
		response["details"] = "NULL parameter as input argument";
		return TEST_FAILURE;
	}
	portID = req["PortID"].asInt();

	if(&req["flag"])
	{
		isNegativeScenario = req["flag"].asInt();
	}

	if(ssp_ethsw_stub_hal_GetAdminPortStatus(portID, getAdminStatus, isNegativeScenario) == RETURN_SUCCESS)
	{
		DEBUG_PRINT(DEBUG_TRACE, "Successfully retrieved the admin status\n");
		response["result"] = "SUCCESS";
		response["details"] = getAdminStatus;
		return TEST_SUCCESS;
	}
	else
	{
		response["result"] = "FAILURE";
		response["details"] = "ethsw_stub_hal_Get_Port_Admin_Status function has failed.Please check logs";
		return TEST_FAILURE;
	}
}


/*********************************************************************************************
 *Function name : ethsw_stub_hal_Get_Port_Cfg
 *Description   : This function will invoke the SSP  HAL wrapper to get the ethsw port cfg
 *@param [in]   : req - It will give port id (port number) and flag(for negative scenario)
 *@param [out]  : response - filled with SUCCESS or FAILURE based on the return value
 ************************************************************************************************/
bool ethsw_stub_hal::ethsw_stub_hal_Get_Port_Cfg(IN const Json::Value& req, OUT Json::Value& response)
{
	int portID = 0;
	char duplexMode[MAX_STRING_SIZE] = {0};
	int maxBitRate = 0;
	char resultDetails[MAX_BUFFER_SIZE_TO_SEND] = {0};
	int  isNegativeScenario = 0;

	DEBUG_PRINT(DEBUG_TRACE,"Inside Function ethsw_stub_hal_Get_Port_Cfg stub \n");
	if(&req["PortID"] == NULL)
	{
		response["result"] = "FAILURE";
		response["details"] = "NULL parameter as input argument";
		return TEST_FAILURE;
	}
	portID = req["PortID"].asInt();
	if(&req["flag"])
	{
		isNegativeScenario = req["flag"].asInt();
	}

	if(ssp_ethsw_stub_hal_GetPortCfg(portID, duplexMode, &maxBitRate, isNegativeScenario) == RETURN_SUCCESS)
	{
		snprintf(resultDetails, MAX_BUFFER_SIZE_TO_SEND, "/%d/%s/", maxBitRate, duplexMode);
		response["result"] = "SUCCESS";
		response["details"] = resultDetails;
		return TEST_SUCCESS;
	}
	else
	{
		response["result"] = "FAILURE";
		response["details"] = "ethsw_stub_hal_Get_Port_Cfg function has failed.Please check logs";
		return TEST_FAILURE;
	}
}


/*********************************************************************************************
 *Function name : ethsw_stub_hal_Get_Port_Status
 *Description   : This function will invoke the SSP  HAL wrapper to get the ethsw port status
 *@param [in]   : req - It will give port id (port number) and flag(for negative scenario)
 *@param [out]  : response - filled with SUCCESS or FAILURE based on the return value
 ************************************************************************************************/
bool ethsw_stub_hal::ethsw_stub_hal_Get_Port_Status(IN const Json::Value& req, OUT Json::Value& response)
{
	int portID = 0;
	char linkStatus[MAX_STRING_SIZE] = {0};
	int bitRate = 0;
	char resultDetails[MAX_BUFFER_SIZE_TO_SEND] = {0};
	int isNegativeScenario = 0;

	DEBUG_PRINT(DEBUG_TRACE,"Inside Function ethsw_stub_hal_Get_Port_Status stub \n");

	if(&req["PortID"] == NULL)
	{
		response["result"] = "FAILURE";
		response["details"] = "NULL parameter as input argument";
		return TEST_FAILURE;
	}
	portID = req["PortID"].asInt();

	if(&req["flag"])
	{
		isNegativeScenario = req["flag"].asInt();
	}

	if(ssp_ethsw_stub_hal_GetPort_Status(portID, linkStatus, &bitRate, isNegativeScenario) == RETURN_SUCCESS)
	{
		snprintf(resultDetails, MAX_BUFFER_SIZE_TO_SEND, "/%d/%s/", bitRate, linkStatus);
		response["result"] = "SUCCESS";
		response["details"] = resultDetails;
		return TEST_SUCCESS;
	}
	else
	{
		response["result"] = "FAILURE";
		response["details"] = "ethsw_stub_hal_Get_Port_Status function has failed.Please check logs";
		return TEST_FAILURE;
	}
}

/********************************************************************************************************
 *Function name : ethsw_stub_hal_Init
 *Description   : This function will invoke the SSP  HAL wrapper to intialize the ethsw_stub_hal HAL
 *@param [in]   : req - request sent by Test Manager
 *@param [out]  : response - filled with SUCCESS or FAILURE based on the return value
 ************************************************************************************************************/
bool ethsw_stub_hal::ethsw_stub_hal_Init(IN const Json::Value& req, OUT Json::Value& response)
{
	DEBUG_PRINT(DEBUG_TRACE,"Inside Function ethsw_stub_hal_Init stub\n");
	if(ssp_ethsw_stub_hal_Init() == RETURN_SUCCESS)
	{
		response["result"] = "SUCCESS";
		response["details"] = "ethsw_stub_hal_Init function has been intailized successfully";
		return TEST_SUCCESS;
	}
	else
	{
		response["result"] = "FAILURE";
		response["details"] = "ethsw_stub_hal_Init function has failed.Please check logs";
		return TEST_FAILURE;
	}
}


/****************************************************************************************************************
 *Function name : ethsw_stub_hal_LocatePort_By_MacAddress
 *Description   : This function will invoke the SSP  HAL wrapper to Locate Port By MacAddress
 *@param [in]   : req - It will give MAC Address(MAC of associated device) and flag(for negative scenario)
 *@param [out]  : response - filled with SUCCESS or FAILURE based on the return value
 ****************************************************************************************************************/
bool ethsw_stub_hal::ethsw_stub_hal_LocatePort_By_MacAddress(IN const Json::Value& req, OUT Json::Value& response)
{
	char macID[MAX_STRING_SIZE] = {0};
	int portId = 0;
	char resultDetails[MAX_BUFFER_SIZE_TO_SEND] = {0};
	int isNegativeScenario = 0;

	DEBUG_PRINT(DEBUG_TRACE,"Inside Function ethsw_stub_hal_LocatePort_By_MacAddress stub\n");

	if(macID == NULL)
	{
		response["result"] = "FAILURE";
		response["details"] = "NULL parameter as input argument";
		return TEST_FAILURE;
	}
	strncpy(macID,req["macID"].asCString(), MAX_STRING_SIZE);
	if(&req["flag"])
	{
		isNegativeScenario = req["flag"].asInt();
	}

	if(ssp_ethsw_stub_hal_LocatePort_By_MacAddress(macID, &portId, isNegativeScenario) == RETURN_SUCCESS)
	{
		snprintf(resultDetails, MAX_BUFFER_SIZE_TO_SEND, "%d", portId);
		response["result"] = "SUCCESS";
		response["details"] = resultDetails;
		return TEST_SUCCESS;
	}
	else
	{
		response["result"] = "FAILURE";
		response["details"] = "ethsw_stub_hal_LocatePort_By_MacAddress function has failed.Please check logs";
		return TEST_FAILURE;
	}
}

/***************************************************************************************
 *Function name : ethsw_stub_hal_SetAgingSpeed
 *Description   : This function will invoke the SSP  HAL wrapper to Set Aging Speed
 *@param [in]   : req - It will give port id and aging speed to be set
 *@param [out]  : response - filled with SUCCESS or FAILURE based on the return value
 ******************************************************************************************/
bool ethsw_stub_hal::ethsw_stub_hal_SetAgingSpeed(IN const Json::Value& req, OUT Json::Value& response)
{
	int portID = 0;
	int agingSpeed = 0;

	DEBUG_PRINT(DEBUG_TRACE,"Inside Function ethsw_stub_hal_SetAgingSpeed stub\n");

	if(&req["PortID"] == NULL)
	{
		response["result"] = "FAILURE";
		response["details"] = "NULL parameter as input argument";
		return TEST_FAILURE;
	}
	if(&req["AgingSpeed"] == NULL)
	{
		response["result"] = "FAILURE";
		response["details"] = "NULL parameter as input argument";
		return TEST_FAILURE;
	}

	portID = req["PortID"].asInt();
	agingSpeed = req["AgingSpeed"].asInt();

	DEBUG_PRINT(DEBUG_TRACE, "PortID = %d, AgingSpeed = %d\n", portID, agingSpeed);

	if(ssp_ethsw_stub_hal_SetAgingSpeed(portID, agingSpeed) == RETURN_SUCCESS)
	{
		response["result"] = "SUCCESS";
		response["details"] = "ethsw_stub_hal_SetAgingSpeed function has passed";
		return TEST_SUCCESS;
	}
	else
	{
		response["result"] = "FAILURE";
		response["details"] = "ethsw_stub_hal_SetAgingSpeed function has failed.Please check logs";
		return TEST_FAILURE;
	}
}

/******************************************************************************************
 *Function name : ethsw_stub_hal_SetPortAdminStatus
 *Description   : This function will invoke the SSP  HAL wrapper to Set Port Admin Status
 *@param [in]   : req - It will give port id and admin status to be set
 *@param [out]  : response - filled with SUCCESS or FAILURE based on the return value
 *******************************************************************************************/
bool ethsw_stub_hal::ethsw_stub_hal_SetPortAdminStatus(IN const Json::Value& req, OUT Json::Value& response)
{
	int portID = 0;
	char adminStatus[MAX_STRING_SIZE] = {0};

	DEBUG_PRINT(DEBUG_TRACE,"Inside Function ethsw_stub_hal_SetPortAdminStatus stub\n");

	if(&req["PortID"] == NULL)
	{
		response["result"] = "FAILURE";
		response["details"] = "NULL parameter as input argument";
		return TEST_FAILURE;
	}

	if(&req["adminstatus"] == NULL)
	{
		response["result"] = "FAILURE";
		response["details"] = "NULL parameter as input argument";
		return TEST_FAILURE;
	}

	portID = req["PortID"].asInt();
	strncpy(adminStatus, req["adminstatus"].asCString(), MAX_STRING_SIZE);

	if(ssp_ethsw_stub_hal_SetPortAdminStatus(portID, adminStatus) == RETURN_SUCCESS)
	{
		response["result"] = "SUCCESS";
		response["details"] = "ethsw_stub_hal_SetPortAdminStatus function has been executed successfully";
		return TEST_SUCCESS;
	}
	else
	{
		response["result"] = "FAILURE";
		response["details"] = "ethsw_stub_hal_SetPortAdminStatus function has been failed";
		return TEST_FAILURE;
	}
}

/******************************************************************************************
 *Function name : ethsw_stub_hal_SetPortCfg
 *Description   : This function will invoke the SSP  HAL wrapper to Set Port Cfg
 *@param [in]   : req - It will give port id, linkrate and duplex mode to be set
 *@param [out]  : response - filled with SUCCESS or FAILURE based on the return value
 ********************************************************************************************/
bool ethsw_stub_hal::ethsw_stub_hal_SetPortCfg(IN const Json::Value& req, OUT Json::Value& response)
{
	int portID = 0;
	int linkRate = 0;
	char duplexMode[MAX_STRING_SIZE] = {0};

	DEBUG_PRINT(DEBUG_TRACE,"Inside Function ethsw_stub_hal_SetPortCfg stub\n");

	if(&req["PortID"] == NULL)
	{
		response["result"] = "FAILURE";
		response["details"] = "NULL parameter as input argument";
		return TEST_FAILURE;
	}
	if(&req["linkrate"] == NULL)
	{
		response["result"] = "FAILURE";
		response["details"] = "NULL parameter as input argument";
		return TEST_FAILURE;
	}
	if(&req["mode"] == NULL)
	{
		response["result"] = "FAILURE";
		response["details"] = "NULL parameter as input argument";
		return TEST_FAILURE;
	}

	portID = req["PortID"].asInt();
	linkRate = req["linkrate"].asInt();
	strncpy(duplexMode, req["mode"].asCString(), MAX_STRING_SIZE);

	if(ssp_ethsw_stub_hal_SetPortCfg(portID, linkRate, duplexMode) == RETURN_SUCCESS)
	{
		response["result"] = "SUCCESS";
		response["details"] = "ethsw_stub_hal_SetPortCfg function has been executed successfully";
		return TEST_SUCCESS;
	}
	else
	{
		response["result"] = "FAILURE";
		response["details"] = "ethsw_stub_hal_SetPortCfg function has been failed";
		return TEST_FAILURE;
	}
}


/***************************************************************************************************
 *Function Name   : CreateObject
 *Description     : This function is used to create a new object of the class "ethsw_stub_hal".
 *@param [in]     : None
 ***************************************************************************************************/
extern "C" ethsw_stub_hal* CreateObject()
{
	return new ethsw_stub_hal();
}

/*************************************************************************************
 *Function Name : cleanup
 *Description   : This function will be used to the close things cleanly.
 *@param [in]   : szVersion - version, ptrAgentObj - Agent object
 *@param [out]  : response - filled with SUCCESS or FAILURE based on the return value
 **************************************************************************************/
bool ethsw_stub_hal::cleanup(IN const char* szVersion, IN RDKTestAgent *ptrAgentObj)
{
	DEBUG_PRINT(DEBUG_TRACE, "cleaning up\n");

	CHECK_PARAM_AND_RET(szVersion);
	CHECK_PARAM_AND_RET(ptrAgentObj);

	ptrAgentObj->UnregisterMethod("ethsw_stub_hal_Get_Port_Admin_Status");
	ptrAgentObj->UnregisterMethod("ethsw_stub_hal_Get_Port_Cfg");
	ptrAgentObj->UnregisterMethod("ethsw_stub_hal_Get_Port_Status");
	ptrAgentObj->UnregisterMethod("ethsw_stub_hal_Init");
	ptrAgentObj->UnregisterMethod("ethsw_stub_hal_LocatePort_By_MacAddress");
	ptrAgentObj->UnregisterMethod("ethsw_stub_hal_SetAgingSpeed");
	ptrAgentObj->UnregisterMethod("ethsw_stub_hal_SetPortAdminStatus");
	ptrAgentObj->UnregisterMethod("ethsw_stub_hal_SetPortCfg");

	return TEST_SUCCESS;
}

/**********************************************************************************
 *Function Name : DestroyObject
 *Description   : This function will be used to destroy the ethsw_stub_hal object.
 *@param [in]   : Input argument is ethsw_stub_hal Object
 **********************************************************************************/
extern "C" void DestroyObject(ethsw_stub_hal *stubobj)
{
	DEBUG_PRINT(DEBUG_TRACE, "Destroying ethsw_stub_hal object\n");
	delete stubobj;
}
