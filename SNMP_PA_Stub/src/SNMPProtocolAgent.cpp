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

#include "SNMPProtocolAgent.h"

#define BUFFERMEMSIZE 512
static std::string Command;

/*************************************************************************
  Function name : SNMPProtocolAgent::SNMPProtocolAgent

Arguments     : NULL

Description   : Constructor for SNMPProtocolAgent class
 ***************************************************************************/

SNMPProtocolAgent::SNMPProtocolAgent()
{
	DEBUG_PRINT(DEBUG_TRACE, "SNMPProtocolAgent Initialized\n");
}

/***************************************************************************
 *Function name : testmodulepre_requisites
 *Descrption    : testmodulepre_requisites will  be used for setting the
 *                pre-requisites that are necessary for this component
 *
 *****************************************************************************/
std::string SNMPProtocolAgent::testmodulepre_requisites()
{
	return "SUCCESS";
}

/***************************************************************************
 *Function name : testmodulepost_requisites
 *Descrption    : testmodulepost_requisites will be used for resetting the
 *                pre-requisites that are set
 *
 *****************************************************************************/
bool SNMPProtocolAgent::testmodulepost_requisites()
{
	return true;
}

/**************************************************************************
Function name : SNMPProtocolAgent::initialize

Arguments     : Input arguments are Version string and SNMPProtocolAgent obj ptr

Description   : Registering all the wrapper functions with the agent for using these functions in the script
 ***************************************************************************/
bool SNMPProtocolAgent::initialize(IN const char* szVersion,IN RDKTestAgent *ptrAgentObj)
{
	DEBUG_PRINT(DEBUG_TRACE, "SNMPProtocolAgent Initialize----->Entry\n");

	ptrAgentObj->RegisterMethod(*this,&SNMPProtocolAgent::ExecuteSNMPCommand, "ExecuteSNMPCommand");
	ptrAgentObj->RegisterMethod(*this,&SNMPProtocolAgent::LogValidation, "LogValidation");
	DEBUG_PRINT(DEBUG_TRACE, "SNMPProtocolAgent Initialize----->Exit\n");

	return TEST_SUCCESS;
}

/*******************************************************************************
 *
 * Function Name      : SNMPTrigger
 * @param SnmpMethod  : This parameter contains Snmp Method - snmpget, snmpset, snmpwalk.
 * @param SnmpCommStr : This parameter contains Snmp Community String - private, public.
 * @param SnmpIP      : This parameter contains IP Address.
 * @param SnmpOID     : This parameter contains Snmp Object Identifier.
 * Description        : SNMPTrigger function will be called by ExecuteSNMPCommand
 *                 to execute Snmp command.
 *
 *******************************************************************************/
int SNMPTrigger(string SnmpMethod, string SnmpCommStr, string SnmpIP, string SnmpOID)
{
	DEBUG_PRINT(DEBUG_TRACE,"\n SNMPTrigger --->Entry\n");
	std::string Command;
	try
	{
		//concatenate strings
		Command.append(SnmpMethod);
		Command.append(" ");
		Command.append(SnmpCommStr);
		Command.append(" ");
		Command.append(SnmpIP);
		Command.append(" ");
		Command.append(SnmpOID);
		DEBUG_PRINT(DEBUG_TRACE,"\nSNMP COMMAND : %s\n", Command.c_str());

		system(Command.c_str());
		DEBUG_PRINT(DEBUG_TRACE,"\nExecuted SNMP COMMAND Successfully\n");
		return TEST_SUCCESS;
	}
	catch(...)
	{
		DEBUG_PRINT(DEBUG_TRACE,"\n SNMP COMMAND not executed\n");
		return TEST_FAILURE;
	}
	DEBUG_PRINT(DEBUG_TRACE,"\n SNMPTrigger --->Exit\n");
	return TEST_SUCCESS;
}
/**************************************************************************
 *
 * Function Name : SNMPProtocolAgent::ExecuteSNMPCommand
 * Descrption    : This command is used to execute the snmp command.
 *
 * @param [in] req- has "SnmpMethod"  which is input to ExecuteSNMPCommand
 * @param [in] req- has "SnmpCommStr" which is input to ExecuteSNMPCommand
 * @param [in] req- has "SnmpIP"      which is input to ExecuteSNMPCommand
 * @param [in] req- has "SnmpOID"     which is input to ExecuteSNMPCommand
 * @param [out] response- filled with SUCCESS or FAILURE based on the return value of SNMPCommand.
 ***************************************************************************/
bool SNMPProtocolAgent::ExecuteSNMPCommand(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n ExecuteSNMPCommand --->Entry\n");
    int retval=0;
    char *SnmpMethod;
    char *SnmpCommStr;
    char *SnmpIP;
    char *SnmpOID;
    if((&req["SnmpMethod"]==NULL) && (&req["SnmpCommStr"]==NULL) && (&req["SnmpIP"]==NULL) && (&req["SnmpOID"]==NULL))
    {
        return TEST_FAILURE;
    }

    SnmpMethod  = (char *)req["SnmpMethod"].asCString();
    SnmpCommStr = (char *)req["SnmpCommStr"].asCString();
    SnmpIP      = (char *)req["SnmpIP"].asCString();
    SnmpOID     = (char *)req["SnmpOID"].asCString();
    retval = SNMPTrigger(SnmpMethod, SnmpCommStr, SnmpIP, SnmpOID);
    if(retval == TEST_SUCCESS)
    {
		response["result"]="SUCCESS";
		response["details"]="Successfully Executed SNMP Command";
    }
    else
    {
		response["result"]="FAILURE";
		response["details"]="Invalid SNMP Command";

    }
    DEBUG_PRINT(DEBUG_TRACE,"\n ExecuteSNMPCommand --->Exit\n");
    return TEST_SUCCESS;
}

/**************************************************************************************
 *
 * Function Name : ValidateSNMPLog
 * @param FindStr: This parameter contains find string in log file.
 * Description   : ValidateSNMPLog function will be called by LogValidation function
 *                 to execute verify snmp logs.
 *
 **************************************************************************************/

int ValidateSNMPLog(char *FindStr)
{
	try
        {
		DEBUG_PRINT(DEBUG_TRACE,"Entering ValidateSNMPLog function ------> Entry");
		const char *LogFile = "/opt/TDK/logs/AgentConsole.log";
		FILE *fp;
		char tempBuf[512];
		int line_num = 1;
		int find_result = 0;
		fp = fopen("/opt/TDK/logs/AgentConsole.log","r");
		DEBUG_PRINT(DEBUG_TRACE,"\n Log file Name :: %s", LogFile);
		if(NULL == fp)
		{
			DEBUG_PRINT(DEBUG_TRACE,"\n Error opening files!\n");
			DEBUG_PRINT(DEBUG_TRACE,"\n Exiting from SNMP Log Validation on Failure------->exit\n");
			return TEST_FAILURE;
		}
		while(fgets(tempBuf, BUFFERMEMSIZE, fp) != NULL) {
			if((strstr(tempBuf, FindStr)) != NULL) {
				DEBUG_PRINT(DEBUG_TRACE,"A match found on line: %d\n", line_num);
				find_result ++;
			}
			line_num++;
		}

		if(find_result == 0) {
			DEBUG_PRINT(DEBUG_TRACE,"\nSorry, couldn't find a match.\n");
			return TEST_FAILURE;
		}
		//Close the file if still open.
	        if(fp) {
        	      fclose(fp);
	        }
		DEBUG_PRINT(DEBUG_TRACE,"\n Log Validation performed successfully \n");
                return TEST_SUCCESS;
	}
	catch(...)
        {
			DEBUG_PRINT(DEBUG_TRACE,"\n Log Validation not performed \n");
			return TEST_FAILURE;
        }
        DEBUG_PRINT(DEBUG_TRACE,"ValidateSNMPLog ------> Exit");
	return TEST_SUCCESS;
}

/**************************************************************************
 * Function Name : LogValidation
 * Descrption    : This function is used to validate the SNMP log
 *
 * @param [in] req- has "FindStr"  which is input to LogValidation
 * @param [out] response- filled with SUCCESS or FAILURE based on the return value of LogValidation.
 ***************************************************************************/
bool SNMPProtocolAgent::LogValidation(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n  --->Entry\n");
    int retval=0;
    char *FindStr;
    if(&req["FindStr"]==NULL)
    {
        return TEST_FAILURE;
    }
    FindStr = (char *)req["FindStr"].asCString();;

    retval = ValidateSNMPLog(FindStr);
    DEBUG_PRINT(DEBUG_TRACE,"\n retval ===================== %d\n", retval);
    if(retval != TEST_SUCCESS)
    {
        response["result"]="FAILURE";
        response["details"]="Failed to find the expected string in log file";
    }
    else
    {
        response["result"]="SUCCESS";
        response["details"]="Found the expected string in the log file";
    }
    DEBUG_PRINT(DEBUG_TRACE,"\n LogValidation --->Exit\n");
    return TEST_SUCCESS;
}

/**************************************************************************
Function Name   : CreateObject

Arguments       : NULL

Description     : This function is used to create a new object of the class "SNMPProtocolAgent".
 **************************************************************************/

extern "C" SNMPProtocolAgent* CreateObject()
{
	DEBUG_PRINT(DEBUG_TRACE, "Creating SNMP Protocol Agent Object\n");

	return new SNMPProtocolAgent();
}

/**************************************************************************
Function Name   : cleanup

Arguments       : NULL

Description     : This function will be used to the close things cleanly.
 **************************************************************************/
bool SNMPProtocolAgent::cleanup(IN const char* szVersion, IN RDKTestAgent *ptrAgentObj)
{
	DEBUG_PRINT(DEBUG_TRACE, "cleaningup\n");

	if(NULL == ptrAgentObj)
	{
		return TEST_FAILURE;
	}

	ptrAgentObj->UnregisterMethod("ExecuteSNMPCommand");
	ptrAgentObj->UnregisterMethod("LogValidation");

	DEBUG_PRINT(DEBUG_TRACE, "cleaningup done\n");

	return TEST_SUCCESS;
}

/**************************************************************************
Function Name : DestroyObject

Arguments     : Input argument is SNMPProtocolAgent Object

Description   : This function will be used to destory the SNMPProtocolAgent object.
 **************************************************************************/
extern "C" void DestroyObject(SNMPProtocolAgent *stubobj)
{
	DEBUG_PRINT(DEBUG_TRACE, "Destroying SNMPProtocolAgent object\n");
	delete stubobj;
}

