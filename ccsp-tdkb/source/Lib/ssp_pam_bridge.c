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
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/
int ssp_pam_Bridging_GetParamUlongValue(char* paramName, unsigned long* ulongValue)
{
    int return_status = 0;
    unsigned long value = 0;
    printf("\n Entering ssp_pam_Bridging_GetParamUlongValue function\n\n");

    return_status = Bridging_GetParamUlongValue(bus_handle_client,paramName,&value);

    if ( return_status == 0)
    {
        printf("ssp_pam_Bridging_GetParamUlongValue:Failed to retrieve the ulongValue\n");
        return 1;
    }

    *ulongValue = value;
    printf("ssp_pam_Bridging_GetParamUlongValue: ulongValue:%lu\n",*ulongValue);
    return 0;
}

#endif
