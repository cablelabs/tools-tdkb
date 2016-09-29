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
        sleep(1200);

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

#endif
