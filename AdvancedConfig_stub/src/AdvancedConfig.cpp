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

#include "AdvancedConfig.h"
#include "ssp_tdk_wrp.h"

/* To provide external linkage to C Functions defined in TDKB Component folder */


extern "C"
{
    int ssp_register(bool);
    GETPARAMVALUES* ssp_getParameterValue(char *pParamName,int *pParamsize);
    int ssp_setParameterValue(char *pParamName,char *pParamValue,char *pParamType);
    GETPARAMATTR* ssp_getParameterAttr(char *pParamAttr,int *pParamAttrSize);
    int ssp_setParameterAttr(char *pParamName,char *pAttrNotify,char *pAttrAccess);
    GETPARAMNAMES* ssp_getParameterNames(char *pPathName,int recursive,int *pParamSize);
    int ssp_addTableRow(char *pObjTbl,int *pInstanceNumber);
    int ssp_deleteTableRow(char *pObjTbl);
    int ssp_setCommit(char *pObjTbl);
    int ssp_getHealth(char *pComponentName);
    int ssp_setSessionId(int priority, int sessionId);
};

/*This is a constructor function for AdvancedConfig class*/
AdvancedConfig::AdvancedConfig()
{
	DEBUG_PRINT(DEBUG_LOG,"TDK AdvancedConfig Instance Created\n");
}


/***************************************************************************
 *Function name	: initialize
 *Description	: Initialize Function will be used for registering the wrapper method 
 *  	  	  with the agent so that wrapper function will be used in the script
 *  		  	  
 *****************************************************************************/ 

bool AdvancedConfig::initialize(IN const char* szVersion,IN RDKTestAgent *ptrAgentObj)
{
	DEBUG_PRINT(DEBUG_TRACE,"TDK::AdvancedConfig Initialize\n");
	/*Register stub function for callback*/
	ptrAgentObj->RegisterMethod(*this,&AdvancedConfig::AdvancedConfig_Start, "AdvancedConfig_Start");
	ptrAgentObj->RegisterMethod(*this,&AdvancedConfig::AdvancedConfig_Get, "AdvancedConfig_Get");
	ptrAgentObj->RegisterMethod(*this,&AdvancedConfig::AdvancedConfig_GetAttr, "AdvancedConfig_GetAttr");
	ptrAgentObj->RegisterMethod(*this,&AdvancedConfig::AdvancedConfig_GetNames, "AdvancedConfig_GetNames");
	ptrAgentObj->RegisterMethod(*this,&AdvancedConfig::AdvancedConfig_SetAttr, "AdvancedConfig_SetAttr");
	ptrAgentObj->RegisterMethod(*this,&AdvancedConfig::AdvancedConfig_Set, "AdvancedConfig_Set");
	ptrAgentObj->RegisterMethod(*this,&AdvancedConfig::AdvancedConfig_AddObject, "AdvancedConfig_AddObject");
	ptrAgentObj->RegisterMethod(*this,&AdvancedConfig::AdvancedConfig_DelObject, "AdvancedConfig_DelObject");
	ptrAgentObj->RegisterMethod(*this,&AdvancedConfig::AdvancedConfig_SetCommit, "AdvancedConfig_SetCommit");
	ptrAgentObj->RegisterMethod(*this,&AdvancedConfig::AdvancedConfig_GetHealth, "AdvancedConfig_GetHealth");
	ptrAgentObj->RegisterMethod(*this,&AdvancedConfig::AdvancedConfig_SetSessionId, "AdvancedConfig_SetSessionId");
	ptrAgentObj->RegisterMethod(*this,&AdvancedConfig::AdvancedConfig_Set_Get, "AdvancedConfig_Set_Get");
	ptrAgentObj->RegisterMethod(*this,&AdvancedConfig::AdvancedConfig_Stop, "AdvancedConfig_Stop");
		
	return TEST_SUCCESS;

}

/***************************************************************************
 *Function name : testmodulepre_requisites
 *Description   : testmodulepre_requisites will  be used for setting the
 *                pre-requisites that are necessary for this component
 *
 *****************************************************************************/
std::string AdvancedConfig::testmodulepre_requisites()
{
	int returnValue;
	int bStart = 1;
	returnValue = ssp_register(bStart);

	if(0 != returnValue)
	{
	    DEBUG_PRINT(DEBUG_TRACE,"\n testmodulepre_requisites --->Error invoking Advanced config in DUT !!! \n");
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
bool AdvancedConfig::testmodulepost_requisites()
{
        return TEST_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name	: AdvancedConfig_Start
 * Description		: This function will invoke TDK Component that will attach to 
 * 			  CCSP Component Registrar (CR)
 *
 * @param [in]  req- 
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value of 
 * 			   ssp_register
********************************************************************************************/

bool AdvancedConfig::AdvancedConfig_Start(IN const Json::Value& req, OUT Json::Value& response)
{
	DEBUG_PRINT(DEBUG_TRACE,"\n AdvancedConfig_start --->Entry \n");

	bool bStart = 1;
	int returnValue = 0;

	returnValue = ssp_register(bStart);

	if(0 == returnValue)
	{
		response["result"]="SUCCESS";
        response["details"]="NULL";
	}
	else
	{

		response["result"]="FAILURE";
        response["details"]="NULL";
	}
	
	DEBUG_PRINT(DEBUG_TRACE,"\n AdvancedConfig_start --->Exit\n");
	return TEST_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name	: AdvancedConfig_Get
 * Description		: This function will invoke TDK Component GET Value wrapper 
         * 			  function to get parameter value
 *
 * @param [in] req- This holds Path name for Parameter
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value of 
 * 			   ssp_getParameterValue
********************************************************************************************/

bool AdvancedConfig::AdvancedConfig_Get(IN const Json::Value& req, OUT Json::Value& response)
{
	DEBUG_PRINT(DEBUG_TRACE,"\n AdvancedConfig_get --->Entry\n");

	char ParamNames[MAX_PARAM_SIZE];
	GETPARAMVALUES *resultDetails;
	int	paramsize=0;
	
	strcpy(ParamNames,req["paramName"].asCString());

	DEBUG_PRINT(DEBUG_TRACE,"\n ParamNames input is %s",ParamNames);	

	resultDetails = ssp_getParameterValue(&ParamNames[0],&paramsize);

	if(resultDetails == NULL)
	{
	    response["result"]="FAILURE";
	    response["details"]="Get Parameter Value API Validation Failure"; 		
	}
	else
	{
	    response["result"]="SUCCESS";
        response["details"]="Get Parameter Value API Validation is Succeeded";

	    for(int i=0; i < paramsize; i++)
	    {
		free(resultDetails[i].pParamValues);
	    }
	}
	
	DEBUG_PRINT(DEBUG_TRACE,"\n AdvancedConfig_get --->Exit\n");

	return TEST_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name	: AdvancedConfig_Set
 * Description		: This function will invoke TDK Component SET Value wrapper 
         * 			  function 
 *
 * @param [in] req-        This hods Path name, Value to set and its type
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value of 
 * 		            	   ssp_setParameterValue
********************************************************************************************/

bool AdvancedConfig::AdvancedConfig_Set(IN const Json::Value& req, OUT Json::Value& response)
{
	DEBUG_PRINT(DEBUG_TRACE,"\n AdvancedConfig_set --->Entry\n");

	int returnValue = 0;
    char ParamName[MAX_PARAM_SIZE];
    char ParamValue[MAX_PARAM_SIZE];
	char ParamType[MAX_PARAM_SIZE];

    strcpy(ParamName,req["paramName"].asCString());
    strcpy(ParamValue,req["paramValue"].asCString());
    strcpy(ParamType,req["paramType"].asCString());
	
    DEBUG_PRINT(DEBUG_TRACE,"\nAdvancedConfig_Set:: ParamName input is %s",ParamName);
    DEBUG_PRINT(DEBUG_TRACE,"\nAdvancedConfig_Set:: ParamValue input is %s",ParamValue);
    DEBUG_PRINT(DEBUG_TRACE,"\nAdvancedConfig_Set:: ParamType input is %s",ParamType);

	returnValue = ssp_setParameterValue(&ParamName[0],&ParamValue[0],&ParamType[0]);
	
	if(0 == returnValue)
	{
		response["result"]="SUCCESS";
	    response["details"]="SET API Validation is Success";
	}
	else
	{
		response["result"]="FAILURE";
	    response["details"]="AdvancedConfigStub::SET API Validation is Failure";
	    DEBUG_PRINT(DEBUG_TRACE,"\n AdvancedConfig_set --->Error in Set API Validation of Advanced config in DUT !!! \n");
	}

	DEBUG_PRINT(DEBUG_TRACE,"\n tdk_AdvancedConfig_set --->Exit\n");
	return TEST_SUCCESS;
}


/*******************************************************************************************
 *
 * Function Name	: AdvancedConfig_Set_Get
 * Description		: This function will invoke TDK Component SET and GET Value wrapper 
 *      			  function for functional Validation
 *
 * @param [in] req-        This hods Path name, Value to set and its type
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value of 
 * 			               ssp_setParameterValue and ssp_getParameterValue
********************************************************************************************/

bool AdvancedConfig::AdvancedConfig_Set_Get(IN const Json::Value& req, OUT Json::Value& response)
{
	DEBUG_PRINT(DEBUG_TRACE,"\n AdvancedConfig_set_get --->Entry\n");

    //Set Param
    int returnValue = 0;
    char ParamName[MAX_PARAM_SIZE];
    char ParamValue[MAX_PARAM_SIZE];
    char ParamType[MAX_PARAM_SIZE];

    //Get Param
    char ParamNames[MAX_PARAM_SIZE];
    GETPARAMVALUES *resultDetails;
    int	paramsize=0;

    //Set Param
    strcpy(ParamName,req["paramName"].asCString());
    strcpy(ParamValue,req["paramValue"].asCString());
    strcpy(ParamType,req["paramType"].asCString());

    //Get param
    strcpy(ParamNames,req["paramName"].asCString());

    DEBUG_PRINT(DEBUG_TRACE,"\nAdvancedConfig_Set_Get:: ParamName input is %s",ParamName);
    DEBUG_PRINT(DEBUG_TRACE,"\nAdvancedConfig_Set_Get:: ParamValue input is %s",ParamValue);
    DEBUG_PRINT(DEBUG_TRACE,"\nAdvancedConfig_Set_Get:: ParamType input is %s",ParamType);



	returnValue = ssp_setParameterValue(&ParamName[0],&ParamValue[0],&ParamType[0]);
	
	if(0 != returnValue)
	{
        response["result"]="FAILURE";
        response["details"]="AdvancedConfigStub::SET API Validation is Failure";
        DEBUG_PRINT(DEBUG_TRACE,"\n AdvancedConfig_set_get --->Error in Set API Validation of Advanced config in DUT !!! \n");
        return	TEST_FAILURE;
	}


	resultDetails = ssp_getParameterValue(&ParamNames[0],&paramsize);

	if(resultDetails == NULL)
	{
	    response["result"]="FAILURE";
	    response["details"]="Get Parameter Value API Validation Failure"; 		
	    DEBUG_PRINT(DEBUG_TRACE,"\n AdvancedConfig_set_get --->Error in Get API Validation of Advanced config in DUT !!! \n");
	    return TEST_FAILURE;
	}

	if((strcmp(resultDetails[0].pParamValues,&ParamValue[0])) == 0)
	{
        response["result"]="SUCCESS";
        response["details"]="Set Get Functional Validation is Succeeded";
	}
	else
	{

	    response["result"]="FAILURE";
	    response["details"]="Set Get Functional Validation Failure"; 		
	    DEBUG_PRINT(DEBUG_TRACE,"\n AdvancedConfig_set_get --->Error in Functional Validation of Advanced config in DUT !!! \n");
	}

	if(resultDetails != NULL)
	{

	    for(int i=0; i < paramsize; i++)
	    {
		free(resultDetails[i].pParamValues);
	    }
	}
	DEBUG_PRINT(DEBUG_TRACE,"\n AdvancedConfig_set_get --->Exit\n");
	return TEST_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name	: AdvancedConfig_GetAttr
 * Description		: This function is called through RPC which will invoke TDK 
 *       			  Wrapper Get attribute function
 *
 * @param [in] req- 	   This holds Attribute path name 
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value of 
 * 		            	   ssp_getParameterAttr
********************************************************************************************/

bool AdvancedConfig::AdvancedConfig_GetAttr(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n AdvancedConfig_getattr --->Entry\n");
    int attrCnt=0;
    int retParamAttrSize = 0;
    char ParamAttr[MAX_PARAM_SIZE];
    GETPARAMATTR *resultDetails;

    strcpy(ParamAttr,req["paramname"].asCString());

    DEBUG_PRINT(DEBUG_TRACE,"\n Input path name is %s\n",ParamAttr);


    resultDetails = ssp_getParameterAttr(&ParamAttr[0],&retParamAttrSize);

    if(resultDetails == NULL)
    {
        response["result"]="FAILURE";
        response["details"]="AdvancedConfigStub::GET Parameter Attribute API Validation is Failure";
    }
    else
    {
        for(attrCnt=0; attrCnt < retParamAttrSize; attrCnt++)
        {
            free(resultDetails[attrCnt].pParamAccess);
            free(resultDetails[attrCnt].pParamNotify);
        }
        response["result"]="SUCCESS";
        response["details"]="GET Parameter Attribute API Validation is Success";
    }

    DEBUG_PRINT(DEBUG_TRACE,"\n AdvancedConfig_getattr --->Exit\n");
    return TEST_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name	: AdvancedConfig_SetAttr
 * Description		: This function is called through TM RPC which will invoke TDK 
 * 			  Wrapper Set Attribute Function
 *
 * @param [in] req- 	  This holds attribute path name and it attributes values to be set
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value of 
             * 			   ssp_setParameterAttr
********************************************************************************************/

bool AdvancedConfig::AdvancedConfig_SetAttr(IN const Json::Value& req, OUT Json::Value& response)
{

	DEBUG_PRINT(DEBUG_TRACE,"\n AdvancedConfig_setattr --->Entry\n");

	int returnValue = 0;
	char AttrNotify[MAX_PARAM_SIZE];
	char AttrAccess[MAX_PARAM_SIZE];
	char ParamName[MAX_PARAM_SIZE];
	
	strcpy(ParamName,req["paramname"].asCString());

	strcpy(AttrNotify,req["notification"].asCString());

	strcpy(AttrAccess,req["accessControlChanged"].asCString());

	DEBUG_PRINT(DEBUG_TRACE,"\n Input path name is %s\n",ParamName);
	DEBUG_PRINT(DEBUG_TRACE,"\n Input notification is %s\n",AttrNotify);
	DEBUG_PRINT(DEBUG_TRACE,"\n Input access control is %s\n",AttrAccess);


	returnValue = ssp_setParameterAttr(&ParamName[0],&AttrNotify[0],&AttrAccess[0]);

	if(returnValue!=0)
	{
	   response["result"]="FAILURE";
	   response["details"]="AdvancedConfigStub::SET Parameter Attribute API Validation Failure";
	}
	else
	{
	   response["result"]="SUCCESS";
	   response["details"]="SET Parameter Attribute API Validation is Success";
	}

	DEBUG_PRINT(DEBUG_TRACE,"\n AdvancedConfig_setattr --->Exit\n");
	return TEST_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name	: AdvancedConfig_GetNames
 * Description		: This function is called through TM RPC which will invoke TDK 
 *       			  Wrapper function to get Parameter names of given component path
 *
 * @param [in] req- 	  This holds path name
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value of 
 * 		            	   ssp_getParameterNames
********************************************************************************************/

bool AdvancedConfig::AdvancedConfig_GetNames(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n AdvancedConfig_getnames --->Entry\n");
    int retParamNameSize = 0;
    char PathName[MAX_PARAM_SIZE];
    GETPARAMNAMES *resultDetails;
    int  recursive=0;

    strcpy(PathName,req["pathname"].asCString());

    DEBUG_PRINT(DEBUG_TRACE,"\n Input path name is %s \n",PathName);

    recursive = req["brecursive"].asInt();

    DEBUG_PRINT(DEBUG_TRACE,"\n Input path name is %s and recursive is %d\n",PathName,recursive);


    resultDetails = ssp_getParameterNames(&PathName[0],recursive,&retParamNameSize);

    if(resultDetails == NULL)
    {
        response["result"]="FAILURE";
        response["details"]="ADVANCEDCONFIG::Get Param Name API Validation Fail";	
    }
    else
    {
        response["result"]="SUCCESS";
        response["details"]=resultDetails[0].pParamNames;

        for(int nameCnt=0; nameCnt < retParamNameSize; nameCnt++)
        {
            free(resultDetails[nameCnt].pParamNames);
        }
    }

    DEBUG_PRINT(DEBUG_TRACE,"\n AdvancedConfig_getnames --->Exit\n");
    return TEST_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name        : AdvancedConfig_AddObject
 * Description          : Add a row to the table object
 *
 * @param [in] req-
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value of 
 * 			   ssp_addTableRow
********************************************************************************************/

bool AdvancedConfig::AdvancedConfig_AddObject(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n AdvancedConfig_AddObject --->Entry\n");

    int returnValue = 0;
    char paramName[MAX_PARAM_SIZE];
    int instanceNumber = 0;

    if(&req["paramName"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL";
        return TEST_FAILURE;
    }

    strcpy(paramName,req["paramName"].asCString());

    DEBUG_PRINT(DEBUG_TRACE,"\nAdvancedConfig_AddObject:: ParamName input is %s",paramName);


    returnValue = ssp_addTableRow(&paramName[0],&instanceNumber);


    if(0 == returnValue)
    {
        DEBUG_PRINT(DEBUG_TRACE,"\nAdvancedConfig_AddObject::instance added is %d",instanceNumber);
        response["result"]="SUCCESS";
        response["details"]="ADD OBJECT API Validation is Success";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="AdvancedConfig::ADD OBJECT API Validation is Failure";
        DEBUG_PRINT(DEBUG_TRACE,"\n AdvancedConfig_AddObject --->Error in adding object !!! \n");
    }

    DEBUG_PRINT(DEBUG_TRACE,"\n AdvancedConfig_AddObject --->Exit\n");
    return TEST_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name        : AdvancedConfig_DelObject
 * Description          : Delete a row from the table object
 *
 * @param [in] req-	This holds parameter path name
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value of 
 * 			   ssp_deleteTableRow
********************************************************************************************/

bool AdvancedConfig::AdvancedConfig_DelObject(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n AdvancedConfig_DelObject --->Entry\n");

    int returnValue = 0;
    char paramName[MAX_PARAM_SIZE];

    int instanceNumber=0;
    int apitest=0;
    std::ostringstream sin;

    if(&req["paramName"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL";
        return TEST_FAILURE;
    }

    strcpy(paramName,req["paramName"].asCString());
    apitest = req["apiTest"].asInt();

    DEBUG_PRINT(DEBUG_TRACE,"\nAdvancedConfig_DelObject:: ParamName input is %s",paramName);
    DEBUG_PRINT(DEBUG_TRACE,"\nAdvancedConfig_DelObject:: apiTest input is %d",apitest);

    if(apitest != 0)
    {

        returnValue = ssp_addTableRow(&paramName[0],&instanceNumber);

        if(returnValue == 0)
        {
            DEBUG_PRINT(DEBUG_TRACE,"\nAdvancedConfig_AddObject::Object added with instance %d",instanceNumber);
            sin << instanceNumber;
            std::string val = sin.str();
            strcat(paramName,val.c_str());
            strcat(paramName,".");
        }
    }

    DEBUG_PRINT(DEBUG_TRACE,"\nAdvancedConfig_DelObject:: Modified ParamName input is %s",paramName);

    returnValue = ssp_deleteTableRow(&paramName[0]);

    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="DELETE OBJECT API Validation is Success";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="AdvancedConfigStub::Delete Object API Validation is Failure";
        DEBUG_PRINT(DEBUG_TRACE,"\n AdvancedConfig_DelObject --->Error in deleting object !!! \n");
    }

    DEBUG_PRINT(DEBUG_TRACE,"\n AdvancedConfig_DelObject --->Exit\n");
    return TEST_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name        : AdvancedConfig_SetCommit
 * Description          : Commit the changes in the table object
 *
 * @param [in] req-
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value of 
 * 			   ssp_setCommit
********************************************************************************************/

bool AdvancedConfig::AdvancedConfig_SetCommit(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n AdvancedConfig_SetCommit --->Entry\n");

    int returnValue = 0;
    char paramName[MAX_PARAM_SIZE];

    if(&req["paramName"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL";
        return TEST_FAILURE;
    }

    strcpy(paramName,req["paramName"].asCString());

    DEBUG_PRINT(DEBUG_TRACE,"\nAdvancedConfig_SetCommit:: ParamName input is %s",paramName);


    returnValue = ssp_setCommit(&paramName[0]);

    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="COMMIT API Validation is Success";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="AdvancedConfigStub::Commit API Validation is Failure";
        DEBUG_PRINT(DEBUG_TRACE,"\n AdvancedConfig_SetCommit --->Error in committing the changes !!! \n");
    }

    DEBUG_PRINT(DEBUG_TRACE,"\n AdvancedConfig_SetCommit --->Exit\n");
    return TEST_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name        : AdvancedConfig_GetHealth
 * Description          : Get the health  of the component
 *
 * @param [in] req-
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value of 
 * 			   ssp_getHealth
********************************************************************************************/

bool AdvancedConfig::AdvancedConfig_GetHealth(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n AdvancedConfig_GetHealth --->Entry\n");

    int returnValue = 0;
    char paramName[MAX_PARAM_SIZE];

    if(&req["paramName"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="AdvancedConfigStub::Error Invoking TDK Component";
        return TEST_FAILURE;
    }

    strcpy(paramName,req["paramName"].asCString());

    DEBUG_PRINT(DEBUG_TRACE,"\nAdvancedConfig_GetHealth:: ParamName input is %s",paramName);


    returnValue = ssp_getHealth(&paramName[0]);

    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="GET HEALTH API Validation is Success";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="AdvancedConfigStub::GET HEALTH API Validation is Failure";
        DEBUG_PRINT(DEBUG_TRACE,"\n AdvancedConfig_GetHealth --->Error in retrieving the component !!! \n");
    }

    DEBUG_PRINT(DEBUG_TRACE,"\n AdvancedConfig_GetHealth --->Exit\n");
    return TEST_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name        : AdvancedConfig_SetSessionId
 * Description          : Set the session Id
 *
 * @param [in] req-
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value of 
 *          			   ssp_setSessionId
********************************************************************************************/

bool AdvancedConfig::AdvancedConfig_SetSessionId(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n AdvancedConfig_SetSessionId --->Entry\n");

    int returnValue = 0;
    int priority = 0;
    int sessionId = 0;

    if(&req["priority"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL";
        return TEST_FAILURE;
    }

    if(&req["sessionId"]==NULL)
    {
        response["result"]="FAILURE";
        response["details"]="NULL";
        return TEST_FAILURE;
    }

    priority = req["priority"].asInt();
    sessionId = req["sessionId"].asInt();

    DEBUG_PRINT(DEBUG_TRACE,"\nAdvancedConfig_SetSessionId:: priority is %d",priority);
    DEBUG_PRINT(DEBUG_TRACE,"\nAdvancedConfig_SetSessionId:: sessionId is %d",sessionId);


    returnValue = ssp_setSessionId(priority,sessionId);

    if(0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="SET SESSION ID API Validation is Success";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="AdvancedConfig_Stub::SET SESSION ID API Validation is Failure";
        DEBUG_PRINT(DEBUG_TRACE,"\n AdvancedConfig_SetSessionId --->Error in setting the session Id !!! \n");
    }

    DEBUG_PRINT(DEBUG_TRACE,"\n AdvancedConfig_SetSessionId --->Exit\n");
    return TEST_SUCCESS;
}



/*******************************************************************************************
 *
 * Function Name	: AdvancedConfig_Stop
 * Description		: This function is called through TM RPC which will invoke TDK
 *	        		  Wrapper Stop function
 *
 * @param [in] req- 
 * @param [out] response - filled with SUCCESS or FAILURE based on the return value of 
 * 			               ssp_register
********************************************************************************************/

bool AdvancedConfig::AdvancedConfig_Stop(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n AdvancedConfig_stop --->Entry\n");
    int returnValue;
    char *resultDetails;
    bool bStart = 0;
    resultDetails=(char *)malloc(sizeof(char)*16);
    memset(resultDetails , '\0', (sizeof(char)*16));


    returnValue = ssp_register(bStart);

    if( 0 == returnValue)
    {
        response["result"]="SUCCESS";
        response["details"]="NULL";
    }
    else
    {
        response["result"]="FAILURE";
        response["details"]="NULL";
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n AdvancedConfig_stop --->Called and exected \n");

    free(resultDetails);

    DEBUG_PRINT(DEBUG_TRACE,"\n AdvancedConfig_stop --->Exit\n");
    return TEST_SUCCESS;
}

/**************************************************************************
 * Function Name	: CreateObject
 * Description	: This function will be used to create a new object for the
 *		  class "AdvancedConfig".
 *
 **************************************************************************/

extern "C" AdvancedConfig* CreateObject()
{
	return new AdvancedConfig();
}

/**************************************************************************
 * Function Name : cleanup
 * Description   : This function will be used to clean the log details. 
 *
 **************************************************************************/

bool AdvancedConfig::cleanup(IN const char* szVersion,IN RDKTestAgent *ptrAgentObj)
{
    DEBUG_PRINT(DEBUG_LOG,"AdvancedConfig shutting down\n");
    if(ptrAgentObj==NULL)
    {
        return TEST_FAILURE;
    }
    /*unRegister stub function for callback*/

    ptrAgentObj->UnregisterMethod("AdvancedConfig_Start");
    ptrAgentObj->UnregisterMethod("AdvancedConfig_Get");
    ptrAgentObj->UnregisterMethod("AdvancedConfig_GetAttr");
    ptrAgentObj->UnregisterMethod("AdvancedConfig_GetNames");
    ptrAgentObj->UnregisterMethod("AdvancedConfig_SetAttr");
    ptrAgentObj->UnregisterMethod("AdvancedConfig_Set");
    ptrAgentObj->UnregisterMethod("AdvancedConfig_Set_Get");

    ptrAgentObj->UnregisterMethod("AdvancedConfig_AddObject");
    ptrAgentObj->UnregisterMethod("AdvancedConfig_DelObject");
    ptrAgentObj->UnregisterMethod("AdvancedConfig_SetCommit");
    ptrAgentObj->UnregisterMethod("AdvancedConfig_GetHealth");
    ptrAgentObj->UnregisterMethod("AdvancedConfig_SetSessionId");

    ptrAgentObj->UnregisterMethod("AdvancedConfig_Stop");	
    return TEST_SUCCESS;
}


/**************************************************************************
 * Function Name : DestroyObject
 * Description   : This function will be used to destroy the object. 
 *
 **************************************************************************/
extern "C" void DestroyObject(AdvancedConfig *stubobj)
{
        DEBUG_PRINT(DEBUG_LOG,"Destroying Advanced config object\n");
        delete stubobj;
}

