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


#ifndef __SSP_PAM_BRIDGE_C__
#define __SSP_PAM_BRIDGE_C__

#include "ssp_global.h"
#include "ccsp_dm_api.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "pthread.h"
#include "ssp_tdk_wrp.h"
#include <pthread.h>
#include <ccsp_message_bus.h>
#include <ccsp_base_api.h>
#include <sys/time.h>
#include <time.h>
#include <signal.h>
#include "ccsp_memory.h"
#include <ccsp_custom.h>
#include <dslh_definitions_database.h>
#include <sys/ucontext.h>


#include "cosa_bridging_dml.h"

/*******************************************************************************************
 *
 * Function Name        : ssp_pam_Bridging_GetParamUlongValue
 * Description          : This function will retrieve the values of ulong params
 *
 * @param [in]          : paramName - parameter name whose values to be retrieved
 * @param [out]         : ulongValue - Holds the value of the parameter
 * @param [out]         : module - Holds the module function to be invoked
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/
int ssp_pam_Bridging_GetParamUlongValue(char* paramName, unsigned long* ulongValue, char *module)
{
    int return_status = 0;
    unsigned long value = 0;
    printf("\n Entering ssp_pam_Bridging_GetParamUlongValue function\n\n");

    if(strcmp(module,"Bridging") == 0)
    {
    	return_status = Bridging_GetParamUlongValue(bus_handle_client,paramName,&value);
    }
    else if(strcmp(module,"Bridge") == 0)
    {
	return_status = Bridge_GetParamUlongValue(bus_handle_client,paramName,&value);
    }
    else if(strcmp(module,"Port") == 0)
    {
	return_status = Port_GetParamUlongValue(bus_handle_client,paramName,&value);
    }
    else if(strcmp(module,"PortStats") == 0)
    {
        return_status = PortStats_GetParamUlongValue(bus_handle_client,paramName,&value);
    }
    else if(strcmp(module,"Filter") == 0)
    {
        return_status = Filter_GetParamUlongValue(bus_handle_client,paramName,&value);
    }
    else
    {
	printf("Invalid module type received\n");
	return 1;
    }

    if ( return_status == 0)
    {
        printf("ssp_pam_Bridging_GetParamUlongValue:Failed to retrieve the ulongValue\n");
        return 1;
    }

    *ulongValue = value;
    printf("ssp_pam_Bridging_GetParamUlongValue: ulongValue:%lu\n",*ulongValue);
    return 0;
}

/*******************************************************************************************
 *
 * Function Name        : ssp_MTAAgentRestart
 * Description          : This function will kill the CMAgent process which is running by default
 *                        and check if the process has restarted after kill.
 *
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/

int ssp_MTAAgentRestart()
{
    printf("\n Entering ssp_MTAAgentRestart function\n\n");

    if(0 == system("pidof CcspMtaAgentSsp > /dev/null"))  {
        printf("\nMTAAgent process is running\n");
        printf("\nGoing to kill MTAAgent process\n");
        system ("kill -9 `pidof CcspMtaAgentSsp`");
        sleep(1500);

        if(0 == system("pidof CcspMtaAgentSsp > /dev/null"))   {
            printf("\nMTAAgent process has restarted \n");
            return 0;

        }

        else
        {
            printf ("\nMTAAgent process is not restarted after kill\n");
            return 1;
        }
    }

    else {

        printf ("\nMTAAgent process is not running\n");
        return 1;
    }
    printf("\n Exiting ssp_MTAAgentRestart function\n\n");
}

/*******************************************************************************************
 *
 * Function Name        : ssp_CRRestart
 * Description          : This function will kill the CR process which is running by default
 *                        and check if the system has rebooted after kill.
 *
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/

int ssp_CRRestart()
{
    printf("\n Entering ssp_CRRestart function\n\n");

    if(0 == system("pidof CcspCrSsp > /dev/null"))  {
        printf("\nCR is running\n");
        printf("\nGoing to kill CR process\n");
        system ("kill -9 `pidof CcspCrSsp`");
        sleep(1800);

        if(0 == system("pidof CcspCrSsp > /dev/null"))   {
            printf("\nCcspCrSsp process has restarted \n");
            return 0;

        }

        else
        {
            printf ("\nCcspCrSsp process is not restarted after kill\n");
            return 1;
        }
    }

    else {

        printf ("\nCcspCrSsp process is not running\n");
        return 1;
    }
    printf("\n Exiting ssp_CRRestart function\n\n");
}

/*******************************************************************************************
 *
 * Function Name        : ssp_pam_Init()
 * Description          : This function will check if the pam module is getting initialised 
                          or not
 * @param [out]         : return status an integer value 0-success and 1-Failure 
 ********************************************************************************************/
int ssp_pam_Init()
{
    int return_status = 0;
    unsigned long value = 0;
    printf("\n Entering ssp_pam_Init function\n\n");
       return_status = CosaDmlDiInit(NULL,NULL);

    if ( return_status == 0)
    {
        printf("ssp_pam_Init: success\n");
        return 0;
    }

    else
       {
    printf("ssp_pam_Init:Failed to initialise\n");
    return 1;
       }
}


#endif
