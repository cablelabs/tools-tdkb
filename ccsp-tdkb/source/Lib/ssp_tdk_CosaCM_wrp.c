/*
* ============================================================================
* COMCAST CONFIDENTIAL AND PROPRIETARY
* ============================================================================

* This file and its contents are the intellectual property of Comcast.  It may
* not be used, copied, distributed or otherwise  disclosed in whole or in part
* without the express written permission of Comcast.

* ============================================================================
* Copyright (c) 2016 Comcast. All rights reserved.
* ============================================================================
*/

#ifndef __SSP_COSACM_WRP_C__
#define __SSP_COSACM_WRP_C__

#include "ssp_global.h"
#include "ccsp_dm_api.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pthread.h"
#include "ssp_tdk_wrp.h"
#include "ssp_tdk_CosaCM_wrp.h"
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
#include "cosa_x_cisco_com_cablemodem_apis.h"

ANSC_HANDLE cm_handle = NULL;    
/*******************************************************************************************
 *
 * Function Name        : ssp_CosaDmlCMGetResetCount
 * Description          : This function will invoke the cosa api of CM to retrieve the reset count
 *                        value for the specified reset type.
 *
 * @param [in]          : handleType - message bus handle
 * @param [in]          : bufferType - Valid or NULL pointer
 * @param [in]          : pResetType - reset type can be CM, Docsis, Erouter or local
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/

int ssp_CosaDmlCMGetResetCount(int handleType, int bufferType, char *pResetType)
{
    int return_status = 0;
    ANSC_HANDLE cm_handle = NULL;
    CM_RESET_TYPE resetType = 0;
    ULONG resetCount = 0;

    printf("\n Entering ssp_CosaDmlCMGetResetCount function\n\n");

    if(handleType == 0)
    {
        cm_handle = bus_handle_client;
    }

    if((strcmp(pResetType,"CMResetCount")==0))
    {
        resetType = CABLE_MODEM_RESET;
    }
    else if((strcmp(pResetType,"LocalResetCount")==0))
    {
        resetType = LOCAL_RESET;
    }
    else if((strcmp(pResetType,"DocsisResetCount")==0))
    {
        resetType = DOCSIS_RESET;
    }
    else if((strcmp(pResetType,"ErouterResetCount")==0))
    {
        resetType = EROUTER_RESET;
    }

    printf("ssp_CosaDmlCMGetResetCount: Reset Type:%d\n",resetType);

    if(bufferType == 0)
    {
        return_status = CosaDmlCMGetResetCount(cm_handle,resetType,&resetCount);
    }
    else
    {
        return_status = CosaDmlCMGetResetCount(cm_handle,resetType,NULL);
    }

    printf("ssp_CosaDmlCMGetResetCount: ResetCount retrieved:%d\n",resetCount);

    if ( return_status != SSP_SUCCESS)
    {
        printf("ssp_CosaDmlCMGetResetCount:Failed to retrieve the reset count\n");
        return SSP_FAILURE;
    }
    return SSP_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name        : ssp_CosaDmlCMGetLockedUpstreamChID
 * Description          : This function will invoke the cosa api of CM to retrieve the currently
 *                        locked upstream channel Id
 *
 * @param [in]          : handleType - Message Bus handle
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/

int ssp_CosaDmlCMGetLockedUpstreamChID(int handleType)
{
    int return_status = 0;
    ANSC_HANDLE cm_handle = NULL;
    ULONG *pChannelId  = NULL;

    printf("\n Entering ssp_CosaDmlCMGetLockedUpstreamChID function\n\n");

    if(handleType == 0)
    {
        cm_handle = bus_handle_client;
    }

    return_status = CosaDmlCMGetLockedUpstreamChID(NULL,pChannelId);

    if ( return_status != SSP_SUCCESS)
    {
        printf("ssp_CosaDmlCMGetLockedUpstreamChID: Failed to retrieve the upstream channel Id\n");
        return SSP_FAILURE;
    }

    return SSP_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name        : ssp_CosaDmlCMSetLockedUpstreamChID
 * Description          : This function will invoke the cosa api of CM to lock upstream channel
 *                        Id for the specified value. 
 *
 * @param [in]          : handleType - Message bus handle
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/

int ssp_CosaDmlCMSetLockedUpstreamChID(int handleType, int channelId)
{
    int return_status = 0;
    ANSC_HANDLE cm_handle = NULL;
    ULONG channelValue = (ULONG)channelId;

    printf("\n Entering ssp_CosaDmlCMSetLockedUpstreamChID function\n\n");

    if(handleType == 0)
    {
        cm_handle = bus_handle_client;
    }

    printf("ssp_CosaDmlCMSetLockedUpstreamChID: Upstream Channel Id to be set:%d\n",channelValue);   
    return_status = CosaDmlCMSetLockedUpstreamChID(cm_handle,&channelValue);

    if ( return_status != SSP_SUCCESS)
    {
        printf("ssp_CosaDmlCMSetLockedUpstreamChID:Failed to lock the upstream channel Id\n");
        return SSP_FAILURE;
    }

    return SSP_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name        : ssp_CosaDmlCMGetStartDSFrequency
 * Description          : This function will invoke the cosa api of CM to retrieve the Downstream
 *                        frequency
 *
 * @param [in]          : handleType - Message bus handle
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/

int ssp_CosaDmlCMGetStartDSFrequency(int handleType)
{
    int return_status = 0;
    ANSC_HANDLE cm_handle = NULL;
    ULONG *pFrequency  = NULL;

    printf("\n Entering ssp_CosaDmlCMGetStartDSFrequency function\n\n");

    if(handleType == 0)
    {
        cm_handle = bus_handle_client;
    }

    return_status = CosaDmlCMGetStartDSFrequency(cm_handle,&pFrequency);

    printf("ssp_CosaDmlCMGetStartDSFrequency: Downstream Frequency retrieved:%d\n",pFrequency);

    if ( return_status != SSP_SUCCESS)
    {
        printf("ssp_CosaDmlCMGetStartDSFrequency:Failed to retrieve the downstream channel\n");
        return SSP_FAILURE;
    }

    return SSP_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name        : ssp_CosaDmlCMSetStartDSFrequency
 * Description          : This function will invoke the cosa api of CM to set the downstream
 *                        frequency
 * @param [in]          : handleType - Message Bus handle
 * @param [in]          : frequency - Downstream frequency to be set
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/

int ssp_CosaDmlCMSetStartDSFrequency(int handleType, int frequency)
{
    int return_status = 0;
    ANSC_HANDLE cm_handle = NULL;
    ULONG frequencyValue = (ULONG)frequency;

    printf("\n Entering ssp_CosaDmlCMSetStartDSFrequency function\n\n");

    if(handleType == 0)
    {
        cm_handle = bus_handle_client;
    }

    printf("ssp_CosaDmlCMSetStartDSFrequency: Downstream frequency to be set:%d\n",(int)frequencyValue);    
    return_status = CosaDmlCMSetStartDSFrequency(cm_handle,frequencyValue);

    if ( return_status != SSP_SUCCESS)
    {
        printf("ssp_CosaDmlCMSetStartDSFrequency:Failed to set the downstream frequency\n");
        return SSP_FAILURE;
    }

    return SSP_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name        : ssp_CosaDmlCMGetProvType
 * Description          : This function will invoke the cosa api of CM to get the cable modem
 *                        provisioning type.
 *
 * @param [in]          : handleType - Message bus handle
 * @param [in]          : bufferType - Invalid or NULL pointer
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/

int ssp_CosaDmlCMGetProvType(int handleType, int bufferType)
{
    int return_status = 0;
    ANSC_HANDLE cm_handle = NULL;
    char *provType = NULL;

    printf("\n Entering ssp_CosaDmlCMGetProvType function\n\n");

    if(handleType == 0)
    {
        cm_handle = bus_handle_client;
    }

    if(bufferType == 0)
    {
        provType = ((char *) malloc(20));
    }

    return_status = CosaDmlCMGetProvType(cm_handle,&provType);
    printf("ssp_CosaDmlCMGetProvType: Provisioning type retrieved:%s\n",provType);

    if ( return_status != SSP_SUCCESS)
    {
        printf("ssp_CosaDmlCMGetProvType:Failed to retrieve the provisioning type of cable modem\n");
        return SSP_FAILURE;
    }

    return SSP_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name        : ssp_CosaDmlCMGetIPv6DHCPInfo
 * Description          : This function will invoke the cosa api of CM to retrieve the DHCP
 *                        information of IPv6
 *
 * @param [in]          : handleType - Message bus handle
 * @param [in]          : bufferType - Invalid or NULL pointer
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/

int ssp_CosaDmlCMGetIPv6DHCPInfo(int handleType, int bufferType)
{
    int return_status = 0;
    ANSC_HANDLE cm_handle = NULL;
    PCOSA_CM_IPV6DHCP_INFO *dhcpIpv6 = NULL;

    printf("\n Entering ssp_CosaDmlCMGetIPv6DHCPInfo function\n\n");

    if(handleType == 0)
    {
        cm_handle = bus_handle_client;
    }

    if(bufferType == 0)
    {
        dhcpIpv6 = ((PCOSA_CM_IPV6DHCP_INFO *) malloc(450));
    }

    return_status = CosaDmlCMGetIPv6DHCPInfo(cm_handle,dhcpIpv6);

    printf("ssp_CosaDmlCMGetIPv6DHCPInfo: IPv6 DHCP Info:%s\n",dhcpIpv6);

    if ( return_status != SSP_SUCCESS)
    {
        printf("ssp_CosaDmlCMGetIPv6DHCPInfo:Failed to retrieve the DHCP information of IPv6 \n");
        return SSP_FAILURE;
    }

    return SSP_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name        : ssp_CosaDmlCMGetStatus
 * Description          : This function will get CM Status.
 * @param [in]          : Value - Get CM Status value
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/

int ssp_CosaDmlCMGetStatus(int handleType, int Value)
{
    int return_status = 0;
    ANSC_HANDLE cm_handle = NULL;
    char *pValue = NULL;

    printf("Entering ssp_CosaDmlCMGetStatus");
    if(handleType == 0)
    {
        cm_handle = bus_handle_client;
    }
    if(Value == 0)
    {
        pValue = ((char *) malloc(100));
    }
    return_status = CosaDmlCMGetStatus(cm_handle,pValue);
    printf("Return status of CosaDmlCMGetStatus is %d \n", return_status);  
    if(return_status == SSP_SUCCESS)
    {
        printf("\n ssp_CosaDmlCMGetStatus :: CosaDmlCMGetStatus function is success with return status %d",return_status);
        return_status = SSP_SUCCESS;
    }
    else
    {
        printf("\n ssp_CosaDmlCMGetStatus :: CosaDmlCMGetStatus function is failure and return status %d",return_status);
        return_status = SSP_FAILURE;
    }
    return return_status;
}

/*******************************************************************************************
 *
 * Function Name        : ssp_CosaCMGetLoopDiagnosticsStart
 * Description          : This function will get Loop Diagnostics start details
 * @param [in]          : Value -
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/

int ssp_CosaCMGetLoopDiagnosticsStart(int handleType, int Value)
{
    int return_status = 0;
    ANSC_HANDLE cm_handle = NULL;
    char *bValue = NULL;
    printf("Entering ssp_CosaCMGetLoopDiagnosticsStart");
    if(handleType == 0)
    {
        cm_handle = bus_handle_client;
    }
    if(Value == 0)
    {
        bValue = ((char *) malloc(100));
    }

    return_status = CosaDmlCMGetLoopDiagnosticsStart(cm_handle,bValue);
    if(return_status == SSP_SUCCESS)
    {
        printf("\n ssp_CosaCMGetLoopDiagnosticsStart :: CosaCMGetLoopDiagnosticsStart function is success with return status %d",return_status);
        return_status = SSP_SUCCESS;
    }
    else
    {
        printf("\n ssp_CosaCMGetLoopDiagnosticsStart :: CosaCMGetLoopDiagnosticsStart function is failure and return status %d",return_status);
        return_status = SSP_FAILURE;
    }
    return return_status;
}

/*******************************************************************************************
 *
 * Function Name        : ssp_CosaDmlCMGetLoopDiagnosticsDetails
 * Description          : This function will get Loop Diagnostics details
 * @param [in]          : boolValue -
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/

int ssp_CosaDmlCMGetLoopDiagnosticsDetails(int handleType, int Value)
{
    int return_status = 0;
    ANSC_HANDLE cm_handle = NULL;
    char *pValue = NULL;
    printf("Entering ssp_CosaDmlCMGetLoopDiagnosticsDetails");
    if(handleType == 0)
    {
        cm_handle = bus_handle_client;
    }
    if(Value == 0)
    {
        pValue = ((char *) malloc(100));
    }
    return_status = CosaDmlCMGetLoopDiagnosticsDetails(cm_handle,pValue);
    if(return_status == SSP_SUCCESS)
    {
        printf("\n ssp_CosaDmlCMGetLoopDiagnosticsDetails :: CosaDmlCMGetLoopDiagnosticsDetails function is success with return status %d",return_status);
        return_status = SSP_SUCCESS;
    }
    else
    {
        printf("\n ssp_CosaDmlCMGetLoopDiagnosticsDetails:: CosaDmlCMGetLoopDiagnosticsDetails function is failure and return status %d",return_status);
        return_status = SSP_FAILURE;
    }
    return return_status;
}

/*******************************************************************************************
 * Function Name        : ssp_CosaDmlCMSetLoopDiagnosticsStart
 * Description          : This function will get 
 * @param [in]          : boolValue -
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/
int ssp_CosaDmlCMGetTelephonyRegistrationStatus(int handleType, int Value)
{
    int return_status = 0;
    ANSC_HANDLE cm_handle = NULL;
    char *pValue = NULL;
    printf("Entering ssp_CosaDmlCMGetTelephonyRegistrationStatus");
    if(handleType == 0)
    {
        cm_handle = bus_handle_client;
    }
    if(Value == 0)
    {
        pValue = ((char *) malloc(100));
    }
    return_status = CosaDmlCMGetTelephonyRegistrationStatus(cm_handle,pValue);
    if(return_status == SSP_SUCCESS)
    {
        printf("\n ssp_CosaDmlCMGetTelephonyRegistrationStatus :: CosaDmlCMGetTelephonyRegistrationStatus function is success with return status %d",return_status);
        return_status = SSP_SUCCESS;
    }
    else
    {
        printf("\n ssp_CosaDmlCMGetTelephonyRegistrationStatus :: CosaDmlCMGetTelephonyRegistrationStatus function is failure and return status %d",return_status);
        return_status = SSP_FAILURE;
    }
    return return_status;
}

/*******************************************************************************************
 * Function Name        : ssp_CosaDmlCMGetTelephonyDHCPStatus
 * Description          : This function will get 
 * @param [in]          : boolValue -
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/
int ssp_CosaDmlCMGetTelephonyDHCPStatus(int handleType, int Value)
{
    int return_status = 0;
    ANSC_HANDLE cm_handle = NULL;
    char *pValue = NULL;
    printf("Entering ssp_CosaDmlCMGetTelephonyDHCPStatus");
    if(handleType == 0)
    {
        cm_handle = bus_handle_client;
    }
    if(Value == 0)
    {
        pValue = ((char *) malloc(20));
    }
    return_status = CosaDmlCMGetTelephonyDHCPStatus(cm_handle,pValue);
    if(return_status == SSP_SUCCESS)
    {
        printf("\n ssp_CosaDmlCMGetTelephonyDHCPStatus :: CosaDmlCMGetTelephonyDHCPStatus function is success with return status %d",return_status);
        return_status = SSP_SUCCESS;
    }
    else
    {
        printf("\n ssp_CosaDmlCMGetTelephonyDHCPStatus :: CosaDmlCMGetTelephonyDHCPStatus function is failure and return status %d",return_status);
        return_status = SSP_FAILURE;
    }
    return return_status;
}

/*******************************************************************************************
 * Function Name        : ssp_CosaDmlCMGetTelephonyTftpStatus
 * Description          : This function will get 
 * @param [in]          : boolValue -
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/
int ssp_CosaDmlCMGetTelephonyTftpStatus(int handleType, int Value)
{
    int return_status = 0;
    ANSC_HANDLE cm_handle = NULL;
    char *pValue = NULL;
    printf("Entering ssp_CosaDmlCMGetTelephonyTftpStatus");
    if(handleType == 0)
    {
        cm_handle = bus_handle_client;
    }
    if(Value == 0)
    {
        pValue = ((char *) malloc(20));
    }
    return_status = CosaDmlCMGetTelephonyTftpStatus(cm_handle,pValue);
    if(return_status == SSP_SUCCESS)
    {
        printf("\n ssp_CosaDmlCMGetTelephonyTftpStatus :: CosaDmlCMGetTelephonyTftpStatus function is success with return status %d",return_status);
        return_status = SSP_SUCCESS;
    }
    else
    {
        printf("\n ssp_CosaDmlCMGetTelephonyTftpStatus :: CosaDmlCMGetTelephonyTftpStatus function is failure and return status %d",return_status);
        return_status = SSP_FAILURE;
    }
    return return_status;
}

/*******************************************************************************************
 * Function Name        : ssp_CosaDmlCMSetLoopDiagnosticsStart
 * Description          : This function will set Loop Diagnostics Start
 * @param [in]          : boolValue -
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/
int ssp_CosaDmlCMSetLoopDiagnosticsStart(int handleType, int Value)
{
    int return_status = 0;
    ANSC_HANDLE cm_handle = NULL;
    printf("Entering ssp_CosaDmlCMSetLoopDiagnosticsStart");
    if(handleType == 0)
    {
        cm_handle = bus_handle_client;
    }
    return_status = CosaDmlCMSetLoopDiagnosticsStart(cm_handle,Value);
    if(return_status == SSP_SUCCESS)
    {
        printf("\n ssp_CosaDmlCMSetLoopDiagnosticsStart :: CosaDmlCMSetLoopDiagnosticsStart function is success with return status %d",return_status);
        return_status = SSP_SUCCESS;
    }
    else
    {
        printf("\n ssp_CosaDmlCMSetLoopDiagnosticsStart :: CosaDmlCMSetLoopDiagnosticsStart function is failure and return status %d",return_status);
        return_status = SSP_FAILURE;
    }
    return return_status;
}
/*******************************************************************************************
 *
 * Function Name        : ssp_cosacm_GetDHCPInfo
 * Description          : This function will invoke the cosa api of CM to retrieve the DHCP
 *                        information
 *
 * @param [in]          : handleType - Message bus handle
 * @param [in]          : bufferType - Invalid or NULL pointer
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/

int ssp_cosacm_GetDHCPInfo(int handleType, int bufferType)
{
    int return_status = 0;
    ANSC_HANDLE cm_handle = NULL;
    PCOSA_CM_DHCP_INFO *dhcp = NULL;

    printf("\n Entering ssp_cosacm_GetDHCPInfo function\n\n");

    if(handleType == 0)
    {
        cm_handle = bus_handle_client;
    }

    if(bufferType == 0)
    {
        dhcp = ((PCOSA_CM_DHCP_INFO *) malloc(450));
        return_status = CosaDmlCMGetDHCPInfo(cm_handle, dhcp);
    }
    else
    {
        return_status = CosaDmlCMGetDHCPInfo(cm_handle, NULL);
    }

    printf("ssp_cosacm_GetDHCPInfo: DHCP Info:%s\n",dhcp);

    if ( return_status != SSP_SUCCESS)
    {
        printf("ssp_cosacm_GetDHCPInfo:Failed to retrieve the DHCP information \n");
        return SSP_FAILURE;
    }

    return SSP_SUCCESS;
}
/*******************************************************************************************
 *
 * Function Name        : ssp_cosacm_GetDOCSISInfo
 * Description          : This function will invoke the cosa api of CM to retrieve the DOCSIS
 *                        information
 *
 * @param [in]          : handleType - Message bus handle
 * @param [in]          : bufferType - Invalid or NULL pointer
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/

int ssp_cosacm_GetDOCSISInfo(int handleType, int bufferType)
{
    int return_status = 0;
    ANSC_HANDLE cm_handle = NULL;
    PCOSA_CM_DOCSIS_INFO *docsis = 0;

    printf("\n Entering ssp_cosacm_GetDOCSISInfo function\n\n");

    if(handleType == 0)
    {
        cm_handle = bus_handle_client;
    }
    
    if(bufferType == 0)
    {
        docsis=((PCOSA_CM_DOCSIS_INFO*)malloc(20));
        return_status = CosaDmlCMGetDOCSISInfo(cm_handle,docsis);
    }
    else
    {
        return_status = CosaDmlCMGetDOCSISInfo(cm_handle,NULL);

    }
    
    printf("Return status of CosaDmlCMGetDOCSISInfo %d ",return_status);
    printf("ssp_cosacm_GetDOCSISInfo: DOCSIS Info:%s\n",docsis);

    if ( return_status != SSP_SUCCESS)
    {
        printf("ssp_cosacm_GetDOCSISInfo:Failed to retrieve the DOCSIS information \n");
        return SSP_FAILURE;
    }

    return SSP_SUCCESS;
}
/*******************************************************************************************
 *
 * Function Name        : ssp_cosacm_GetLog
 * Description          : This function will invoke the cosa api of CM to retrieve the Log
 *                        information
 *
 * @param [in]          : handleType - Message bus handle
 * @param [in]          : bufferType - Invalid or NULL pointer
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/

int ssp_cosacm_GetLog(int handleType, int bufferType)
{
    int return_status = 0;
    ANSC_HANDLE cm_handle = NULL;
    PCOSA_DML_CM_LOG *log = NULL;

    printf("\n Entering ssp_cosacm_GetLog function\n\n");

    if(handleType == 0)
    {
        cm_handle = bus_handle_client;
    }
    if(bufferType == 0)
    {
        log = ((PCOSA_DML_CM_LOG *) malloc(20));
    }  

    return_status = CosaDmlCmGetLog(cm_handle,log);

    printf("ssp_cosacm_GetLog: Log Info:%s\n",log);

    if ( return_status != SSP_SUCCESS)
    {
        printf("ssp_cosacm_GetLog:Failed to retrieve the Log information \n");
        return SSP_FAILURE;
    }

    return SSP_SUCCESS;
}


/*******************************************************************************************
 *
 * Function Name        : ssp_cosacm_SetLog
 * Description          : This function will invoke the cosa api of CM to set the log information
 *
 * @param [in]          : handleType - Message bus handle
 * @param [in]          : bufferType - Invalid or NULL pointer
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/

int ssp_cosacm_SetLog(int handleType, int bufferType)
{
    int return_status = 0;
    ANSC_HANDLE cm_handle = NULL;
    PCOSA_DML_CM_LOG *log = NULL;

    printf("\n Entering ssp_cosacm_SetLog function\n\n");

    if(handleType == 0)
    {
        cm_handle = bus_handle_client;
    }
    if(bufferType == 0)
    {
        log = ((PCOSA_DML_CM_LOG *) malloc(20));

    }

    return_status = CosaDmlCmSetLog(cm_handle,log);

    printf("ssp_cosacm_SetLog: Log Info:%s\n",log);

    if ( return_status != SSP_SUCCESS)
    {
        printf("ssp_cosacm_SetLog:Failed to set the log information \n");
        return SSP_FAILURE;
    }

    return SSP_SUCCESS;
}
/*******************************************************************************************
 *
 * Function Name        : ssp_cosacm_GetDocsisLog
 * Description          : This function will invoke the cosa api of CM to set the DOCSIS log information
 *
 * @param [in]          : handleType - Message bus handle
 * @param [in]          : bufferType - Invalid or NULL pointer
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/
int ssp_cosacm_GetDocsisLog(int handleType, int bufferType)
{
    int return_status = 0;
    ANSC_HANDLE cm_handle = NULL;
    int *count = NULL;
    PCOSA_DML_DOCSISLOG_FULL *ppConf = NULL;
    
    printf("\n Entering ssp_cosacm_GetDocsisLog function\n\n");

    if(handleType == 0)
    {
	cm_handle = bus_handle_client;
    }
    if(bufferType == 0) 
    {
        count=(int*)malloc(20*sizeof(int));
        return_status = CosaDmlCmGetDocsisLog(cm_handle,&count,&ppConf);
    }
    else
    {    

        return_status = CosaDmlCmGetDocsisLog(cm_handle,NULL,&ppConf);
    }   
    printf("ssp_cosacm_GetDocsisLog: DOCSIS Log Info:%s\n",ppConf);

    if ( return_status != SSP_SUCCESS)
    {
        printf("ssp_cosacm_GetDocsisLog:Failed to retrieve the DOCSIS Log information \n");
        return SSP_FAILURE;
    }

    return SSP_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name        : ssp_cosacm_GetDownstreamChannel
 * Description          : This function will invoke the cosa api of CM to set the Downstream channel information
 *
 * @param [in]          : handleType - Message bus handle
 * @param [in]          : bufferType - Invalid or NULL pointer
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/

int ssp_cosacm_GetDownstreamChannel(int handleType, int bufferType)
{
    int return_status = 0;
    ANSC_HANDLE cm_handle = NULL;
    int     *Count=NULL;
    PCOSA_CM_DS_CHANNEL *pcfg = NULL;
    
    printf("\n Entering ssp_cosacm_GetDownstreamChannel function\n\n");

    if(handleType == 0)
    {
	cm_handle = bus_handle_client;
    }
    if(bufferType == 0)
    {
        Count=(int*)malloc(20*sizeof(int));
        return_status = CosaDmlCmGetDownstreamChannel(cm_handle,&Count,&pcfg);
    }
    else
    {
        return_status = CosaDmlCmGetDownstreamChannel(cm_handle,NULL,&pcfg);
    }

    printf("ssp_cosacm_GetUpstreamChannel: Downstream channel Info:%s\n",pcfg);

    if ( return_status != SSP_SUCCESS)
    {
        printf("ssp_cosacm_GetDownstreamChannel:Failed to retrieve the Downstream channel information \n");
        return SSP_FAILURE;
    }

    return SSP_SUCCESS;
}
/*******************************************************************************************
 *
 * Function Name        : ssp_cosacm_GetUpstreamChannel
 * Description          : This function will invoke the cosa api of CM to set the Upstream channel information
 *
 * @param [in]          : handleType - Message bus handle
 * @param [in]          : bufferType - Invalid or NULL pointer
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/

int ssp_cosacm_GetUpstreamChannel(int handleType, int bufferType)
{
    int return_status = 0;
    ANSC_HANDLE cm_handle = NULL;
    int     *Count=NULL;
    PCOSA_CM_US_CHANNEL *pcfg = NULL;

    printf("\n Entering ssp_cosacm_GetUpstreamChannel function\n\n");

    if(handleType == 0)
    {
	cm_handle = bus_handle_client;
    }
    if(bufferType == 0)
    {
        Count=(int*)malloc(20*sizeof(int));
        return_status = CosaDmlCmGetUpstreamChannel(cm_handle,&Count,&pcfg);
    }
    else
    {
        return_status = CosaDmlCmGetUpstreamChannel(cm_handle,NULL,&pcfg);
    }

    printf("ssp_cosacm_GetUpstreamChannel: Upstream channel Info:%s\n",pcfg);

    if ( return_status != SSP_SUCCESS)
    {
        free(Count);
        printf("ssp_cosacm_GetUpstreamChannel:Failed to retrieve the Upstream channel information \n");
        return SSP_FAILURE;
    }


    return SSP_SUCCESS;
}

/*******************************************************************************************
 * Function Name        : ssp_CosaCableModemCreate 
 * Description          : This function will create cabel Modem. 
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/
int ssp_CosaCableModemCreate()
{
    int return_status = 0;
    printf("Entering ssp_CosaCableModemCreate");
    ANSC_HANDLE cm_handle = NULL;
    cm_handle = CosaCableModemCreate();
    if(cm_handle !=NULL)
    {
        printf("\n ssp_CosaCableModemCreate :: CosaCableModemCreate function is success with return status %d",return_status);
        return_status = SSP_SUCCESS;
    }
    else
    {
        printf("\n ssp_CosaCableModemCreate :: CosaCableModemCreate function is failure and return status %d",return_status);
        return_status = SSP_FAILURE;
    }
    return return_status;
}

/*******************************************************************************************
 * Function Name        : ssp_CosaCableModemInitialize
 * Description          : This function will initialize Cable Modem  
 * @param [in]          : Value - pointer
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/
int ssp_CosaCableModemInitialize(int Value)
{
    int return_status = 0;
    ANSC_HANDLE cm_handle = NULL;
    printf("Entering ssp_CosaCableModemInitialize");
    if(Value == 0)
    {
        printf("\nNULL handle passed\n");
        return_status = CosaCableModemInitialize(NULL);
        if(return_status == SSP_SUCCESS)
        {
            printf("\n ssp_CosaCableModemInitialize :: CosaCableModemInitialize function fails to handle NULL scenarios %d",return_status);
            return 1;
        }
        else
        {
            printf("\n ssp_CosaCableModemInitialize :: CosaCableModemInitialize function handles NULL scenarios and return status %d",return_status);
            return 0;
        }

    }
    else if (Value == 1)
    {
        printf("\nvalid handle passed\n");
        cm_handle = CosaCableModemCreate();
        return_status = CosaCableModemInitialize(cm_handle);

        if(return_status == SSP_SUCCESS)
        {
            printf("\n ssp_CosaCableModemInitialize :: CosaCableModemInitialize function is success with return status %d",return_status);
            return 0;
        }
        else
        {
            printf("\n ssp_CosaCableModemInitialize :: CosaCableModemInitialize function is failure and return status %d",return_status);
            return 1;
        }
    }
    else
    {
        printf("\nNo Handle type is passed\n");
        return return_status;
    }    
}
/*******************************************************************************************
 * Function Name        : ssp_CosaCableModemRemove 
 * Description          : This function will Remove Cable modem
 * @param [in]          : pObject - pointer
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/
int ssp_CosaCableModemRemove(int Value)
{
    int return_status = 0;
    ANSC_HANDLE cm_handle = NULL;
    printf("Entering ssp_CosaCableModemRemove");
    if(Value == 0)
    {
        return_status = CosaCableModemRemove(NULL);
        if(return_status == SSP_SUCCESS)
        {
            printf("\n ssp_CosaCableModemRemove :: CosaCableModemRemove function does not handle NULL sceanrios with return status %d",return_status);
            return 1;
        }
        else
        {
            printf("\n ssp_CosaCableModemRemove :: CosaCableModemRemove function handles failure scenarios and return status %d",return_status);
            return 0;
        }

    }
    else if (Value == 1)
    {   
        cm_handle = CosaCableModemCreate();
        return_status = CosaCableModemRemove(cm_handle);
        if(return_status == SSP_SUCCESS)
        {
            printf("\n ssp_CosaCableModemRemove :: CosaCableModemRemove function is success with return status %d",return_status);
            return 0;
        }
        else
        {
            printf("\n ssp_CosaCableModemRemove :: CosaCableModemRemove function is failure and return status %d",return_status);
            return 1;
        }
    }
    else
    {    
        printf("\nNo value paseed\n");
        return return_status;
    }
}    
/*******************************************************************************************
 *
 * Function Name        : ssp_cosacm_getmarket
 * Description          : This function will invoke the cosa api of CM to get Market in which
 *                        this particular DUT can be used
 *
 * @param [in]          : N/A
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/

int ssp_cosacm_getmarket()
{

    int return_status = 0;
    char *value = NULL;

    printf("\n Entering ssp_cosacm_getmarket function\n\n");

    value = ((char *) malloc(20));

    if(value == NULL)
    {
        printf("\n ssp_cosacm_getmarket :: Get Value Memory alloc error \n");
        return SSP_FAILURE;
    }
    return_status = CosaDmlCMGetMarket(bus_handle_client,value);
    if ( return_status != SSP_SUCCESS)
    {
        printf("\n ssp_cosacm_getmarket:Failed to get the DUT Market Info \n");
        return SSP_FAILURE;
    }
    if(value != NULL)
    {
        free(value);
    }   
    return SSP_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name        : ssp_cosacm_setmddipoverride 
 * Description          : This function will invoke the cosa api of CM to set MDD IP Override
 *                        Function
 *
 * @param [in]          : N/A
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/

int ssp_cosacm_setmddipoverride()
{
    int return_status = 0;
    char *value = NULL;

    printf("\n Entering ssp_cosacm_setmddipoverride function\n\n");

    value = ((char *) malloc(20));

    if(value == NULL)
    {
        printf("\n ssp_cosacm_getmarket :: Get Value Memory alloc error \n");
        return SSP_FAILURE;
    }

    strcpy(value,"MDD IP Override");

    return_status = CosaDmlCMSetMDDIPOverride(bus_handle_client,value);

    if ( return_status != SSP_SUCCESS)
    {
        printf("\n ssp_cosacm_setmddipoverride :Failed to set the MDDIPOverride \n");
        return SSP_FAILURE;
    }

    if(value != NULL)
    {
        free(value);                                                                                             }

    return SSP_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name        : ssp_cosacm_getmddipoverride
 * Description          : This function will invoke the cosa api of CM to get MDD IP Override
 *                        Function current Configuration
 *
 * @param [in]          : N/A
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/

int ssp_cosacm_getmddipoverride()
{

    int return_status = 0;
    char *value = NULL;

    printf("\n Entering ssp_cosacm_getmddipoverride function\n\n");

    value = ((char *) malloc(20));

    if(value == NULL)
    {
        printf("\n ssp_cosacm_getmddipoverride :: Get Value Memory alloc error \n");
        return SSP_FAILURE;
    }

    return_status = CosaDmlCMGetMDDIPOverride(bus_handle_client,value);

    if ( return_status != SSP_SUCCESS)
    {
        printf("\n ssp_cosacm_getmddipoverride:Failed to get the MDDIPOverride \n");
        return SSP_FAILURE;
    }

    if(value != NULL)
    {
        free(value);
    }

    return SSP_SUCCESS;


}
/*******************************************************************************************
 *
 * Function Name        : ssp_cosacm_getcert
 * Description          : This function will invoke the cosa api of CM to get certificate
 *                        access information
 *
 * @param [in]          : N/A
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/

int ssp_cosacm_getcert()
{

    int return_status = 0;
    char *value = NULL;
    int*     pBool;

    printf("\n Entering ssp_cosacm_getcert function\n\n");

    value = ((char *) malloc(20));

    if(value == NULL)
    {
        printf("\n ssp_cosacm_getcert :: Get Value Memory alloc error \n");
        return SSP_FAILURE;
    }

    return_status = CosaDmlCmGetCMCert(bus_handle_client,value);

    if ( return_status != SSP_SUCCESS)
    {
        printf("\n ssp_cosacm_getcert:Failed\n");
        return SSP_FAILURE;
    }

    if(value != NULL)
    {
        free(value);
    }

    return SSP_SUCCESS;

}


/*******************************************************************************************
 *
 * Function Name        : ssp_cosacm_getcmerrorcodewords
 * Description          : This function will invoke the cosa api of CM to get Error Code
 *                        Words Information. It contains channel coding related information
 *
 * @param [in]          : N/A
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/

int ssp_cosacm_getcmerrorcodewords()
{
    int return_status = 0;
    ULONG count = 0;
    PCOSA_DML_CMERRORCODEWORDS_FULL **pCfg  = NULL;

    printf("\n Entering ssp_cosacm_getcmerrorcodewords function\n\n");

    return_status = CosaDmlCmGetCMErrorCodewords(bus_handle_client,&count,&pCfg);

    if ( return_status != SSP_SUCCESS)
    {
        printf("\n ssp_cosacm_getcmerrorcodewords:Failed to retrieve the error code words\n");
        return SSP_FAILURE;
    }

    return SSP_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name        : ssp_cosacm_getcertstatus 
 * Description          : This function will invoke the cosa api of CM to certificate availability
 *                        status
 *
 * @param [in]          : N/A
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/

int ssp_cosacm_getcertstatus()
{

    int return_status = 0;
    bool bValue;

    printf("\n Entering ssp_cosacm_getcertstatus function\n\n");

    return_status = CosaDmlCmGetCMCertStatus(bus_handle_client,&bValue);

    if ( return_status != SSP_SUCCESS)
    {
        printf("\n ssp_cosacm_getcertstatus:Failed to get the Certificate Status info \n");
        return SSP_FAILURE;
    }

    return SSP_SUCCESS;

}

/*******************************************************************************************
 *
 * Function Name        : ssp_cosacm_getcpelist 
 * Description          : This function will invoke the cosa api of CM to Wireless/Wired Clients
 *                        connected with this DUT
 *
 * @param [in]          : N/A
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/

int ssp_cosacm_getcpelist()
{

    int return_status = 0;
    char *value = NULL;
    int   ulInstanceNumber=0;
    ANSC_HANDLE cm_handle = NULL;
    PCOSA_DML_CPE_LIST *pCPEList = NULL;

    printf("\nEntering ssp_cosacm_getcpelist function\n\n");

    return_status = CosaDmlCmGetCPEList(NULL,&ulInstanceNumber,pCPEList);
    printf("Return status of CosaDmlCmGetCPEList is %d \n", return_status);

    if ( return_status != SSP_SUCCESS)
    {
        printf("ssp_cosacm_getcpelist :Failed to get the CPE List Info \n");
        return SSP_FAILURE;
    }

    if(pCPEList != NULL)
    {
        printf("\nCosaDmlCmGetCPEList return instance number as %l with info \n",ulInstanceNumber);

        puts(pCPEList);
        free(pCPEList);

    }

    return SSP_SUCCESS;

}


/*******************************************************************************************
 *
 * Function Name        : ssp_cosacm_getmarket_memory_unalloc
 * Description          : This function will invoke the cosa api of CM to get Market in which
 *                        this particular DUT can be used
 *
 * @param [in]          : N/A
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/

int ssp_cosacm_getmarket_memory_unalloc()
{

    int return_status = 0;
    char *value = NULL;

    printf("\n Entering ssp_cosacm_getmarket_memory_unalloc function\n\n");


    return_status = CosaDmlCMGetMarket(bus_handle_client,value);

    if ( return_status != SSP_SUCCESS)
    {
        printf("\n ssp_cosacm_getmarket_memory_unalloc:Failed to get the DUT Market Info \n");
        return SSP_FAILURE;
    }

    if(value != NULL)
    {
        free(value);
    }

    return SSP_SUCCESS;

}


/*******************************************************************************************
 *
 * Function Name        : ssp_cosacm_setmddipoverride_memory_unalloc
 * Description          : This function will invoke the cosa api of CM to set MDD IP Override
 *                        Function
 *
 * @param [in]          : N/A
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/

int ssp_cosacm_setmddipoverride_memory_unalloc()
{
    int return_status = 0;
    char *value = NULL;

    printf("\n Entering ssp_cosacm_setmddipoverride function\n\n");


    return_status = CosaDmlCMSetMDDIPOverride(bus_handle_client,value);

    if ( return_status != SSP_SUCCESS)
    {
        printf("\n ssp_cosacm_setmddipoverride_memory_unalloc :Failed to set the MDDIPOverride \n");
        return SSP_FAILURE;
    }

    if(value != NULL)
    {
        free(value);
    }

    return SSP_SUCCESS;
}


/*******************************************************************************************
 *
 * Function Name        : ssp_cosacm_getmddipoverride_memory_unalloc
 * Description          : This function will invoke the cosa api of CM to get MDD IP Override
 *                        Function current Configuration
 *
 * @param [in]          : N/A
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/

int ssp_cosacm_getmddipoverride_memory_unalloc()
{

    int return_status = 0;
    char *value = NULL;

    printf("\n Entering ssp_cosacm_getmddipoverride_memory_unalloc function\n\n");

    return_status = CosaDmlCMGetMDDIPOverride(bus_handle_client,value);
    
    printf("Return status of CosaDmlCMGetMDDIPOverride %d ",return_status);

    if ( return_status != SSP_SUCCESS)
    {
        printf("\n ssp_cosacm_get_mddipoverride_memory_unalloc:Failed to get the MDDIPOverride \n");
        return SSP_FAILURE;
    }

    if(value != NULL)
    {
        free(value);
    }

    return SSP_SUCCESS;


}


/*******************************************************************************************
 *
 * Function Name        : ssp_cosacm_getcert_memory_unalloc
 * Description          : This function will invoke the cosa api of CM to get certificate
 *                        access information
 *
 * @param [in]          : N/A
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/

int ssp_cosacm_getcert_memory_unalloc()
{

    int return_status = 0;
    char *value = NULL;

    printf("\n Entering ssp_cosacm_getcert_memory_unalloc function\n\n");


    return_status = CosaDmlCmGetCMCert(bus_handle_client,value);

    if ( return_status != SSP_SUCCESS)
    {
        printf("\n ssp_cosacm_getcert_memory_unalloc:Failed to get the MDDIPOverride \n");
        return SSP_FAILURE;
    }

    if(value != NULL)
    {
        free(value);
    }

    return SSP_SUCCESS;

}


/*******************************************************************************************
 *
 * Function Name        : ssp_cosacm_getcmerrorcodewords_invalid_arg
 * Description          : This function will invoke the cosa api of CM to get Error Code
 *                        Words Information. It contains channel coding related information
 *
 * @param [in]          : N/A
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/

int ssp_cosacm_getcmerrorcodewords_invalid_arg()
{
    int return_status = 0;
    ULONG count = 0;
    int **pCfg = NULL;

    printf("\n Entering ssp_cosacm_getcmerrorcodewords_invalid_arg function\n\n");

    return_status = CosaDmlCmGetCMErrorCodewords(bus_handle_client,&count,&pCfg);
    
    printf("Return status of CosaDmlCmGetCMErrorCodewords %d ",return_status);

    if ( return_status != SSP_SUCCESS)
    {
        printf("\n ssp_cosacm_getcmerrorcodewords_invalid_arg:Failed to retrieve the error code words\n");
        return SSP_FAILURE;
    }

    return SSP_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name        : ssp_cosacm_getcertstatus_invalid_arg
 * Description          : This function will invoke the cosa api of CM to certificate availability
 *                        status
 *
 * @param [in]          : N/A
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/

int ssp_cosacm_getcertstatus_invalid_arg()
{

    int return_status = 0;
    int *bValue=NULL;

    printf("\n Entering ssp_cosacm_getcertstatus_invalid_arg function\n\n");

    return_status = CosaDmlCmGetCMCertStatus(bus_handle_client,bValue);

    printf("Return status of CosaDmlCmGetCMCertStatus %d ", return_status);

    if ( return_status != SSP_SUCCESS)
    {
        printf("\n ssp_cosacm_getcertstatus_invalid_arg:Failed to get the Certificate Status info \n");
        return SSP_FAILURE;
    }

    return SSP_SUCCESS;

}

/*******************************************************************************************
 *
 * Function Name        : ssp_cosacm_getcpelist_invalid_arg
 * Description          : This function will invoke the cosa api of CM to Wireless/Wired Clients
 *                        connected with this DUT
 *
 * @param [in]          : N/A
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/

int ssp_cosacm_getcpelist_invalid_arg()
{

    int return_status = 0;
    char *value = NULL;
    ULONG   ulInstanceNumber=0;
    int *pCPEList = NULL;

    printf("\nEntering ssp_cosacm_getcpelist_invalid_arg function\n\n");

    return_status = CosaDmlCmGetCPEList(bus_handle_client,&ulInstanceNumber,pCPEList);

    printf("Return status of CosaDmlCmGetCPEList %d " , return_status);

    if ( return_status != SSP_SUCCESS)
    {
        printf("ssp_cosacm_getcpelist_invalid_arg :Failed to get the CPE List Info \n");
        return SSP_FAILURE;
    }

    if(pCPEList != NULL)
    {
        printf("\nCosaDmlCmGetCPEList return instance number as %l with info \n",ulInstanceNumber);

        if(pCPEList != NULL)
        {
            puts(pCPEList);
            free(pCPEList);
        }
    }

    return SSP_SUCCESS;

}

#endif
