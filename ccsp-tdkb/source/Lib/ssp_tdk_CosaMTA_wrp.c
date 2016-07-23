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


#ifndef __SSP_COSAMTA_WRP_C__
#define __SSP_COSAMTA_WRP_C__

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
#include "ssp_tdk_CosaMTA_wrp.h"
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


#include "cosa_x_cisco_com_mta_apis.h"
//#if !defined(CCSP_INC_no_asm_sigcontext_h)^M
  //  #include <asm/sigcontext.h>
//#endif
// for PC build with gcc 4.4.3 on Ubuntu 10.4 Lucid,^M
// <asm/sigcontext.h> will redefine some definitions from <bits/sigcontext.h>^M
#endif
/*******************************************************************************************
 *
 * Function Name        : ssp_CosaDmlMtaGetResetCount
 * Description          : This function will invoke the cosa api of MTA to retrieve the reset count
 *                        value for the specified reset type.
 *
 * @param [in]          : handleType - message bus handle
 * @param [in]          : bufferType - Valid or NULL pointer
 * @param [in]          : pResetType - reset type can be MTAResetcount, LineResetCount or invalid
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/
int ssp_CosaDmlMtaGetResetCount(int handleType, int bufferType, char *pResetType)
{
    int return_status = 0;
    ANSC_HANDLE mta_handle = NULL;
    MTA_RESET_TYPE resetType = 0;
    ULONG resetCount = 0;

    printf("\n Entering ssp_CosaDmlMtaGetResetCount function\n\n");

    if(handleType == 0)
    {
        mta_handle = bus_handle_client;
    }

    if((strcmp(pResetType,"MTAResetCount")==0))
    {
        resetType = MTA_RESET;
    }
    else if((strcmp(pResetType,"LineResetCount")==0))
    {
        resetType = LINE_RESET;
    }

    printf("ssp_CosaDmlMtaGetResetCount: Reset Type:%d\n",resetType);

    if(bufferType == 0)
    {
        return_status = CosaDmlMtaGetResetCount(mta_handle,resetType,&resetCount);
    }
    else
    {
        return_status = CosaDmlMtaGetResetCount(mta_handle,resetType,NULL);
    }

    printf("ssp_CosaDmlMtaGetResetCount: ResetCount retrieved:%d\n",resetCount);

    if ( return_status != SSP_SUCCESS)
    {
        printf("ssp_CosaDmlMtaGetResetCount:Failed to retrieve the reset count\n");
        return SSP_FAILURE;
    }
    return SSP_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name        : ssp_CosaDmlMTAGetDHCPInfo
 * Description          : This function will invoke the cosa api of MTA to retrieve the DHCP
 *                        information
 *
 * @param [in]          : handleType - Message bus handle
 * @param [in]          : bufferType - Invalid or NULL pointer
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/

int ssp_CosaDmlMTAGetDHCPInfo(int handleType, int bufferType)
{
    int return_status = 0;
    ANSC_HANDLE mta_handle = NULL;
    PCOSA_MTA_DHCP_INFO *dhcp = NULL;

    printf("\n Entering ssp_CosaDmlMTAGetDHCPInfo function\n\n");

    if(handleType == 0)
    {
        mta_handle = bus_handle_client;
        dhcp = ((PCOSA_MTA_DHCP_INFO *) malloc(704));
        return_status = CosaDmlMTAGetDHCPInfo(mta_handle,dhcp);

    }
    else
    {
        return_status = CosaDmlMTAGetDHCPInfo(mta_handle,NULL);
    }    


    printf("ssp_CosaDmlMTAGetDHCPInfo: DHCP Info:%s\n",dhcp);

    if ( return_status != SSP_SUCCESS)
    {
        printf("ssp_CosaDmlMTAGetDHCPInfo:Failed to retrieve the DHCP information \n");
        return SSP_FAILURE;
    }

    return SSP_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name        : ssp_CosaDmlMTATriggerDiagnostics
 * Description          : This function will invoke the cosa api of MTA to check the index value
 *
 * @param [in]          : index - 0
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/

int ssp_CosaDmlMTATriggerDiagnostics()
{
    int return_status = 0;
    ULONG index = 0;

    printf("\n Entering ssp_CosaDmlMTATriggerDiagnostics function\n\n");
    return_status = CosaDmlMTATriggerDiagnostics(index);
    printf("Valid index value\n");

    if ( return_status != SSP_SUCCESS)
    {
        printf("ssp_CosaDmlMTATriggerDiagnostics:Index value is invalid  \n");
        return SSP_FAILURE;
    }

    return SSP_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name        : ssp_CosaDmlMtaBatteryGetInfo
 * Description          : This function will invoke the cosa api of MTA to retrieve the Battery
 *                        information
 *
 * @param [in]          : handleType - Message bus handle
 * @param [in]          : bufferType - Invalid or NULL pointer
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/
int ssp_CosaDmlMtaBatteryGetInfo(int handleType, int bufferType)
{
    int return_status = 0;
    ANSC_HANDLE mta_handle = NULL;
    PCOSA_DML_BATTERY_INFO *battery = NULL;

    printf("\n Entering ssp_CosaDmlMtaBatteryGetInfo function\n\n");

    if(handleType == 0)
    {
        mta_handle = bus_handle_client;
    }

    if(bufferType == 0)
    {
        battery  = ((PCOSA_DML_BATTERY_INFO *) malloc(130));
    }

    return_status = CosaDmlMtaBatteryGetInfo(mta_handle,battery);

    printf("ssp_CosaDmlMtaBatteryGetInfo: BATTERY Info:%s\n",battery);

    if ( return_status != SSP_SUCCESS)
    {
        printf("ssp_CosaDmlMtaBatteryGetInfo:Failed to retrieve the BATTERY information \n");
        return SSP_FAILURE;
    }

    return SSP_SUCCESS;
}

/********************************************************************************************
 *Parameter Name        : ssp_CosaDmlMtaBatteryGetStatus
 * Description          : This function will invoke the cosa api of MTA which will get the 
 *                        battery status
 * @param [in]          : handleType - Message bus handle
 * @param [in]          : bufferType - Invalid or NULL pointer
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/
int ssp_CosaDmlMtaBatteryGetStatus(int handleType, int bufferType)
{
    int return_status = 0;
    ANSC_HANDLE mta_handle = NULL;
    char* value = NULL;
    int* size = NULL;

    printf("\n Entering ssp_CosaDmlMtaBatteryGetStatus function\n\n");

    if(handleType == 0)
    {
        mta_handle = bus_handle_client;
    }

    if(bufferType == 0)
    {
        value  = ((PCHAR *) malloc(20));
    }

    return_status = CosaDmlMtaBatteryGetStatus(mta_handle,value,&size);

    printf("ssp_CosaDmlMtaBatteryGetStatus: BATTERY Info:%s\n",value);

    if ( return_status != SSP_SUCCESS)
    {
        printf("ssp_CosaDmlMtaBatteryGetStatus:Failed to retrieve the BATTERY information \n");
        return SSP_FAILURE;
    }

    return SSP_SUCCESS;
}

/********************************************************************************************
 *Parameter Name        : ssp_CosaDmlMtaBatteryGetPowerStatus
 * Description          : This function will invoke the cosa api of MTA to retrieve the battery 
 *                        power status
 *
 * @param [in]          : handleType - Message bus handle
 * @param [in]          : bufferType - Invalid or NULL pointer
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/
int ssp_CosaDmlMtaBatteryGetPowerStatus(int handleType, int bufferType)
{
    int return_status = 0;
    ANSC_HANDLE mta_handle = NULL;
    char* value = NULL;
    int* size = NULL;

    printf("\n Entering ssp_CosaDmlMtaBatteryGetPowerStatus function\n\n");

    if(handleType == 0)
    {
        mta_handle = bus_handle_client;
    }

    if(bufferType == 0)
    {
        value  = ((char *) malloc(8));
    }

    return_status = CosaDmlMtaBatteryGetPowerStatus(mta_handle,value,&size);

    printf("ssp_CosaDmlMtaBatteryGetPowerStatus: BATTERY Info:%s\n",value);

    if ( return_status != SSP_SUCCESS)
    {
        printf("ssp_CosaDmlMtaBatteryGetPowerStatus:Failed to retrieve the BATTERY information \n");
        return SSP_FAILURE;
    }

    return SSP_SUCCESS;
}

/********************************************************************************************
 *Parameter Name        : ssp_CosaDmlMtaLineTableGetNumberOfEntries
 * Description          : This function will invoke the cosa api of MTA to retrieve the Line
 *                        table number of entries
 *
 * @param [in]          : handleType - Message bus handle
 * @param [in]          : bufferType - Invalid or NULL pointer
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/
int ssp_CosaDmlMtaLineTableGetNumberOfEntries(int handleType)
{
    int return_status = 0;
    ANSC_HANDLE mta_handle = NULL;
    if(handleType == 0)
    {
        mta_handle = bus_handle_client;

        return_status = CosaDmlMTALineTableGetNumberOfEntries(mta_handle);
    }
    printf("ssp_CosaDmlMtaLineTableGetNumberOfEntries info:%d\n",return_status);

    if ( return_status != SSP_SUCCESS)
    {
        printf("ssp_CosaDmlMtaLineTableGetNumberOfEntries:Failed to retrieve the Line Table information \n");
        return SSP_FAILURE;
    }

    return SSP_SUCCESS;
}
/********************************************************************************************
 * Parameter Name       : ssp_CosaDmlMtaLineTableGetEntry
 * Description          : This function will invoke the cosa api of MTA to retrieve the Line 
 *                        table get entry
 *
 * @param [in]          : handleType - Message bus handle
 * @param [in]          : Value - 0
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/
int ssp_CosaDmlMtaLineTableGetEntry(int handleType,int bufferType)
{
    int return_status = 0;
    ANSC_HANDLE mta_handle = NULL;
    int value = 0;
    PCOSA_MTA_LINETABLE_INFO* entry = NULL;

    if(handleType == 0)
    {
        mta_handle = bus_handle_client;

    }
    if(bufferType == 0)
    {
        entry  = ((PCOSA_MTA_LINETABLE_INFO *) malloc(1863));
    }
    return_status = CosaDmlMTALineTableGetEntry(mta_handle,value,entry);
    printf("ssp_CosaDmlMtaLineTableGetEntry: Line Table Info:%s\n",entry);
    printf("return status:%d\n",return_status);

    if ( return_status != SSP_SUCCESS)
    {
        printf("ssp_CosaDmlMTALineTableGetEntry:Failed to retrieve the Line Table information \n");
        return SSP_FAILURE;
    }

    return SSP_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name        : ssp_CosaDmlMTAGetServiceClass
 * Description          : This function will invoke the cosa api of MTA to retrieve the 
 *                        Service class
 *
 * @param [in]          : handleType - Message bus handle
 * @param [in]          : bufferType - Invalid or NULL pointer
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/

int ssp_CosaDmlMTAGetServiceClass(int handleType)
{
    int return_status = 0;
    ANSC_HANDLE mta_handle = NULL;
    int *Count=NULL;
    PCOSA_MTA_SERVICE_CLASS *pfg = NULL;
    mta_handle = bus_handle_client;

    printf("\n Entering ssp_CosaDmlMTAGetServiceClass function\n\n");

    if(handleType == 0)
    {
        Count=(int*)malloc(20*sizeof(int));
        return_status = CosaDmlMTAGetServiceClass(mta_handle,&Count,pfg);
    }

    printf("ssp_CosaDmlMTAGetServiceClass: %s\n",pfg);

    if ( return_status != SSP_SUCCESS)
    {
        printf("ssp_CosaDmlMTAGetServiceClass:Failed to retrieve the Service class \n");
        return SSP_FAILURE;
    }

    return SSP_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name        : ssp_CosaDmlMTADectGetEnable
 * Description          : This function will invoke the cosa api of MTA to retrieve the 
 *                        enable value of Dect
 *
 * @param [in]          : handleType - Message bus handle
 * @param [in]          : Value - 0
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/

int ssp_CosaDmlMTADectGetEnable(int handleType, int Value)
{
    int return_status = 0;
    ANSC_HANDLE mta_handle = NULL;
    char *bValue = NULL;

    printf("\n Entering ssp_CosaDmlMTADectGetEnable function\n\n");

    if(handleType == 0)
    {
        mta_handle = bus_handle_client;
    }
    if(Value == 0)
    {
        bValue = ((char *) malloc(100));
    }
    return_status = CosaDmlMTADectGetEnable(mta_handle,bValue);
    if ( return_status != SSP_SUCCESS)
    {
        printf("ssp_CosaDmlMTADectGetEnable: Failed to retrieve the Dect enable value\n");
        return SSP_FAILURE;
    }

    return SSP_SUCCESS;

}
/*******************************************************************************************
 *
 * Function Name        : ssp_CosaDmlMTADectSetEnable
 * Description          : This function will invoke the cosa api of MTA to retrieve the 
 *                        Set Enable of Dect
 *
 * @param [in]          : handleType - Message bus handle
 * @param [in]          : Value - 0
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/

int ssp_CosaDmlMTADectSetEnable(int handleType, int Value)
{
    int return_status = 0;
    ANSC_HANDLE mta_handle = NULL;
    char bValue = NULL;
    printf("\n Entering ssp_CosaDmlMTADectSetEnable function\n\n");

    if(handleType == 0)
    {
        mta_handle = bus_handle_client;

    }
    if (Value == 0)
    {
        bValue = ((char *) malloc(100));
    }


    return_status = CosaDmlMTADectSetEnable(mta_handle,bValue);
    if ( return_status != SSP_SUCCESS)
    {
        printf("ssp_CosaDmlMTADectSetEnable:Failed to retrieve the Dect enable\n");
        return SSP_FAILURE;
    }

    return SSP_SUCCESS;


}
/*******************************************************************************************
 *
 * Function Name        : ssp_CosaDmlMTADectGetRegistrationMode
 * Description          : This function will invoke the cosa api of MTA to retrieve the 
 *                        Dect registration mode
 *
 * @param [in]          : handleType - Message bus handle
 * @param [in]          : bufferType - Invalid or NULL pointer
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/

int ssp_CosaDmlMTADectGetRegistrationMode(int handleType, int Value)
{
    int return_status = 0;
    ANSC_HANDLE mta_handle = NULL;
    char *bValue = NULL; 
    printf("\n Entering ssp_CosaDmlMTADectGetRegistrationMode function\n\n");

    if(handleType == 0)
    {
        mta_handle = bus_handle_client;

    }
    if (Value == 0)
    {
        bValue = ((char *) malloc(100));
    }
    return_status = CosaDmlMTADectGetRegistrationMode(mta_handle,bValue);
    if ( return_status != SSP_SUCCESS)
    {
        printf("ssp_CosaDmlMTADectGetRegistrationMode:Failed to retrieve the Dect registration mode\n");
        return SSP_FAILURE;
    }

    return SSP_SUCCESS;


}
/*******************************************************************************************
 *
 * Function Name        : ssp_CosaDmlMTADectSetRegistrationMode
 * Description          : This function will invoke the cosa api of MTA to set the 
 *                        dect registration mode
 *
 * @param [in]          : handleType - Message bus handle
 * @param [in]          : bufferType - Invalid or NULL pointer
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/

 int ssp_CosaDmlMTADectSetRegistrationMode(int handleType, int Value)
{
    int return_status = 0;
    ANSC_HANDLE mta_handle = NULL;
    char *bValue = NULL;
    printf("\n Entering ssp_CosaDmlMTADectSetRegistrationMode function\n\n");

    if(handleType == 0)
    {
        mta_handle = bus_handle_client;

    }

    if (Value == 0)
    {
        bValue = ((char *) malloc(100));
    }
    return_status = CosaDmlMTADectSetRegistrationMode(mta_handle,bValue);
    if ( return_status != SSP_SUCCESS)
    {
        printf("ssp_CosaDmlMTADectSetRegistrationMode:Failed to set the dect registration mode\n");
        return SSP_FAILURE;
    }

    return SSP_SUCCESS;

}
/*******************************************************************************************
 *
 * Function Name        : ssp_CosaDmlMTAGetDect
 * Description          : This function will invoke the cosa api of MTA to retrieve the dect
 *                        information
 *
 * @param [in]          : handleType - Message bus handle
 * @param [in]          : bufferType - Invalid or NULL pointer
 * @param [out]         : return status an integer value 0-success and 1-Failure
********************************************************************************************/

int ssp_CosaDmlMTAGetDect(int handleType, int bufferType)
{
    int return_status = 0;
    ANSC_HANDLE mta_handle = NULL;
    PCOSA_MTA_DECT *dect = NULL;

    printf("\n Entering ssp_CosaDmlMTAGetDect function\n\n");

    if(handleType == 0)
    {
        mta_handle = bus_handle_client;
        dect = ((PCOSA_MTA_DECT *) malloc(20));
        return_status = CosaDmlMTAGetDect(mta_handle,dect);

    }
    else
    {
        return_status = CosaDmlMTAGetDect(mta_handle,NULL);
    }

    printf("ssp_CosaDmlMTAGetDect: Dect Info:%s\n",dect);

    if ( return_status != SSP_SUCCESS)
    
    {
        printf("ssp_CosaDmlMTAGetDect:Failed to retrieve the Dect information \n");
        return SSP_FAILURE;
    }

    return SSP_SUCCESS;
}
/*******************************************************************************************
 *
 * Function Name        : ssp_CosaDmlMTAGetDectPIN
 * Description          : This function will invoke the cosa api of MTA to retrieve the Dect
 *                        information
 *
 * @param [in]          : handleType - Message bus handle
 * @param [in]          : bufferType - Invalid or NULL pointer
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/



int ssp_CosaDmlMTAGetDectPIN(int handleType, int bufferType)
{
    int return_status = 0;
    ANSC_HANDLE mta_handle = NULL;
    char *pinstring = NULL;

    printf("\n Entering ssp_CosaDmlMTAGetDectPIN function\n\n");

    if(handleType == 0)
    {
        mta_handle = bus_handle_client;

    }
    
    if (bufferType == 0)
    {
        pinstring = ((char *) malloc(20));
    }

    return_status =     CosaDmlMTAGetDectPIN(mta_handle, &pinstring);

    if ( return_status != SSP_SUCCESS)
    {
        printf("ssp_CosaDmlMTAGetDectPIN:Failed to retrieve the Dect pin information \n");
        return SSP_FAILURE;
    }

    return SSP_SUCCESS;
}


/*******************************************************************************************
 *
 * Function Name        : ssp_CosaDmlMTASetDectPIN
 * Description          : This function will invoke the cosa api of MTA to retrieve the 
 *                        dect pin
 *
 * @param [in]          : handleType - Message bus handle
 * @param [in]          : bufferType - Invalid or NULL pointer
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/

int ssp_CosaDmlMTASetDectPIN(int handleType, int bufferType)
{
    int return_status = 0;
    ANSC_HANDLE mta_handle = NULL;
    char *pinstring = NULL;

    printf("\n Entering ssp_CosaDmlMTASetDectPIN function\n\n");

    if(handleType == 0)
    {
        mta_handle = bus_handle_client;

    }

    if (bufferType == 0)
    {
        pinstring = ((char *) malloc(20));
    }

    return_status =     CosaDmlMTASetDectPIN(mta_handle, &pinstring);

    if ( return_status != SSP_SUCCESS)
    {
        printf("ssp_CosaDmlMTASetDectPIN:Failed to retrieve the Dect pin information \n");
        return SSP_FAILURE;
    }

    return SSP_SUCCESS;
}





/*******************************************************************************************
 *
 * Function Name        : ssp_CosaDmlMTAGetDSXLogEnable
 * Description          : This function will invoke the cosa api of MTA to retrieve the DSX Log 
 *                        enable
 *
 * @param [in]          : handleType - Message bus handle
 * @param [in]          : bufferType - Invalid or NULL pointer
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/

int ssp_CosaDmlMTAGetDSXLogEnable(int handleType, int Value)
{
    int return_status = 0;
    ANSC_HANDLE mta_handle = NULL;
    char *bValue = NULL;
    printf("\n Entering ssp_CosaDmlMTAGetDSXLogEnable function\n\n");
 
    if(handleType == 0)
    {
        mta_handle = bus_handle_client;

    }
    
    if (Value == 0)
    {
        bValue = ((char *) malloc(100));
    }
    return_status = CosaDmlMTAGetDSXLogEnable(mta_handle,bValue);

    if ( return_status != SSP_SUCCESS)
    {
        printf("ssp_CosaDmlMTAGetDSXLogEnable:Failed to retrieve the dsx log enable\n");
        return SSP_FAILURE;
    }

    return SSP_SUCCESS;

}

/*******************************************************************************************
 *
 * Function Name        : ssp_CosaDmlMTASetDSXLogEnable
 * Description          : This function will invoke the cosa api of MTA to set the
 *                        DSX log enable 
 *
 * @param [in]          : handleType - Message bus handle
 * @param [in]          : Value - 0
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/

int ssp_CosaDmlMTASetDSXLogEnable(int handleType, int Value)
{
    int return_status = 0;
    ANSC_HANDLE mta_handle = NULL;
    char bValue = NULL;
    printf("\n Entering ssp_CosaDmlMTASetDSXLogEnable function\n\n");

    if(handleType == 0)
    {
        mta_handle = bus_handle_client;

    }
    if (Value == 0)
    {
        bValue = ((char *) malloc(100));
    }


    return_status = CosaDmlMTASetDSXLogEnable(mta_handle,bValue);
    if ( return_status != SSP_SUCCESS)
    {
        printf("ssp_CosaDmlMTASetDSXLogEnable:Failed to set the DSX log enable\n");
        return SSP_FAILURE;
    }

    return SSP_SUCCESS;



}


/*******************************************************************************************
 *
 * Function Name        : ssp_CosaDmlMTAClearDSXLog
 * Description          : This function will invoke the cosa api of MTA to clear the DSX log
 *
 * @param [in]          : handleType - Message bus handle
 * @param [in]          : Value - 0
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/

int ssp_CosaDmlMTAClearDSXLog(int handleType, int Value)
{
    int return_status = 0;
    ANSC_HANDLE mta_handle = NULL;
    char bValue = NULL;
    printf("\n Entering ssp_CosaDmlMTAClearDSXLog function\n\n");

    if(handleType == 0)
    {
        mta_handle = bus_handle_client;

    }
    if (Value == 0)
    {
        bValue = ((char *) malloc(100));
    }


    return_status = CosaDmlMTAClearDSXLog(mta_handle,bValue);
    if ( return_status != SSP_SUCCESS)
    {
        printf("ssp_CosaDmlMTAClearDSXLog:Failed to clear the DSX log\n");
        return SSP_FAILURE;
    }

    return SSP_SUCCESS;


}
/*******************************************************************************************
 *
 * Function Name        : ssp_CosaDmlMTAGetCallSignallingLogEnable
 * Description          : This function will invoke the cosa api of MTA to retrieve the 
 *                        Call signalling log
 *
 * @param [in]          : handleType - Message bus handle
 * @param [in]          : Value - 0
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/

int ssp_CosaDmlMTAGetCallSignallingLogEnable(int handleType, int Value)
{
    int return_status = 0;
    ANSC_HANDLE mta_handle = NULL;
    char *bValue = NULL;
    printf("\n Entering ssp_CosaDmlMTAGetCallSignallingLogEnable function\n\n");

    if(handleType == 0)
    {
        mta_handle = bus_handle_client;

    }

    if (Value == 0)
    {
        bValue = ((char *) malloc(100));
    }
    return_status = CosaDmlMTAGetCallSignallingLogEnable(mta_handle,bValue);

    if ( return_status != SSP_SUCCESS)
    {
        printf("ssp_CosaDmlMTAGetCallSignallingLogEnable:Failed to retrieve the call signalling log\n");
        return SSP_FAILURE;
    }

    return SSP_SUCCESS;


}


/*******************************************************************************************
 *
 * Function Name        : ssp_CosaDmlMTASetCallSignallingLogEnable
 * Description          : This function will invoke the cosa api of MTA to
 *                        set the call signalling log
 *
 * @param [in]          : handleType - Message bus handle
 * @param [in]          : Value - 0
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/

int ssp_CosaDmlMTASetCallSignallingLogEnable(int handleType, int Value)
{
    int return_status = 0;
    ANSC_HANDLE mta_handle = NULL;
    char bValue = NULL;
    printf("\n Entering ssp_CosaDmlMTASetCallSignallingLogEnable function\n\n");

    if(handleType == 0)
    {
        mta_handle = bus_handle_client;

    }
    if (Value == 0)
    {
        bValue = ((char *) malloc(100));
    }


    return_status = CosaDmlMTASetCallSignallingLogEnable(mta_handle,bValue);

    if ( return_status != SSP_SUCCESS)
    {
        printf("ssp_CosaDmlMTASetCallSignallingLogEnable:Failed to  set the call signalling log\n");
        return SSP_FAILURE;
    }

    return SSP_SUCCESS;



}

/*******************************************************************************************
 *
 * Function Name        : ssp_CosaDmlMTAClearCallSignallingLog
 * Description          : This function will invoke the cosa api of MTA to clear the
 *                        call signalling log
 *
 * @param [in]          : handleType - Message bus handle
 * @param [in]          : bufferType - Value - 0
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/

int ssp_CosaDmlMTAClearCallSignallingLog(int handleType, int Value)
{

    int return_status = 0;
    ANSC_HANDLE mta_handle = NULL;
    char bValue = NULL;
    printf("\n Entering ssp_CosaDmlMTAClearCallSignallingLog function\n\n");

    if(handleType == 0)
    {
        mta_handle = bus_handle_client;

    }
    if (Value == 0)
    {
        bValue = ((char *) malloc(100));
    }


    return_status = CosaDmlMTAClearCallSignallingLog(mta_handle,bValue);
    if ( return_status != SSP_SUCCESS)
    {
        printf("ssp_CosaDmlMTAClearCallSignallingLog:Failed to clear the call signalling log\n");
        return SSP_FAILURE;
    }

    return SSP_SUCCESS;


}


/*******************************************************************************************
 *
 * Function Name        : ssp_CosaDmlMtaBatteryGetNumberofCycles
 * Description          : This function will invoke the cosa api of MTA to retrieve
 *                        the number of battery cycles
 *
 * @param [in]          : handleType - Message bus handle
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/

int ssp_CosaDmlMtaBatteryGetNumberofCycles(int handleType)
{
    int return_status = 0;
    ANSC_HANDLE mta_handle = NULL;
    ULONG *pval  = NULL;

    printf("\n Entering ssp_CosaDmlMtaBatteryGetNumberofCycles function\n\n");

    if(handleType == 0)
    {
        mta_handle = bus_handle_client;
    }

    return_status = CosaDmlMtaBatteryGetNumberofCycles(mta_handle,&pval);

    printf("ssp_CosaDmlMtaBatteryGetNumberofCycles: Number of cycles retrieved:%d\n",pval);

    if ( return_status != SSP_SUCCESS)
    {
        printf("ssp_CosaDmlMtaBatteryGetNumberofCycles:Failed to retrieve the number of cycles\n");
        return SSP_FAILURE;
    }

    return SSP_SUCCESS;

}


/*******************************************************************************************
 *
 * Function Name        : ssp_CosaDmlMtaBatteryGetLife
 * Description          : This function will invoke the cosa api of MTA to retrieve
 *                        the Battery Life
 *
 * @param [in]          : handleType - Message bus handle
 * @param [in]          : bufferType - Value - 0
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/

int ssp_CosaDmlMtaBatteryGetLife(int handleType, int bufferType)
{
    int return_status = 0;
    ANSC_HANDLE mta_handle = NULL;
    char* value = NULL;
    int* size = NULL;

    printf("\n Entering ssp_CosaDmlMtaBatteryGetLife function\n\n");

    if(handleType == 0)
    {
        mta_handle = bus_handle_client;
    }

    if(bufferType == 0)
    {
        value  = ((PCHAR *) malloc(20));
    }

    return_status = CosaDmlMtaBatteryGetLife(mta_handle,value,&size);

    printf("ssp_CosaDmlMtaBatteryGetLife: BATTERY Info:%s\n",value);

    if ( return_status != SSP_SUCCESS)
    {
        printf("ssp_CosaDmlMtaBatteryGetLife:Failed to retrieve the BATTERY information \n");
        return SSP_FAILURE;
    }

    return SSP_SUCCESS;
}


/*******************************************************************************************
 *
 * Function Name        : ssp_CosaDmlMtaBatteryGetCondition
 * Description          : This function will invoke the cosa api of MTA to retrieve
 *                        the Battery Condition
 *
 * @param [in]          : handleType - Message bus handle
 * @param [in]          : bufferType - Value - 0
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/

int ssp_CosaDmlMtaBatteryGetCondition(int handleType, int bufferType)
{
    int return_status = 0;
    ANSC_HANDLE mta_handle = NULL;
    char* value = NULL;
    int* size = NULL;

    printf("\n Entering ssp_CosaDmlMtaBatteryGetCondition function\n\n");

    if(handleType == 0)
    {
        mta_handle = bus_handle_client;
    }

    if(bufferType == 0)
    {
        value  = ((PCHAR *) malloc(20));
    }

    return_status = CosaDmlMtaBatteryGetCondition(mta_handle,value,&size);

    printf("ssp_CosaDmlMtaBatteryGetCondition: BATTERY Info:%s\n",value);

    if ( return_status != SSP_SUCCESS)
    {
        printf("ssp_CosaDmlMtaBatteryGetCondition:Failed to retrieve the BATTERY information \n");
        return SSP_FAILURE;
    }

    return SSP_SUCCESS;
}


/*******************************************************************************************
 *
 * Function Name        : ssp_CosaDmlMtaBatteryGetRemainingTime
 * Description          : This function will invoke the cosa api of MTA to retrieve
 *                        the Battery Condition
 *
 * @param [in]          : handleType - Message bus handle
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/

int ssp_CosaDmlMtaBatteryGetRemainingTime(int handleType)
{
    int return_status = 0;
    ANSC_HANDLE mta_handle = NULL;
    ULONG *pval  = NULL;

    printf("\n Entering ssp_CosaDmlMtaBatteryGetRemainingTime function\n\n");

    if(handleType == 0)
    {
        mta_handle = bus_handle_client;
    }

    return_status = CosaDmlMtaBatteryGetRemainingTime(mta_handle,&pval);

    printf("ssp_CosaDmlMtaBatteryGetRemainingTime: Remaining Time retrieved:%d\n",pval);

    if ( return_status != SSP_SUCCESS)
    {
        printf("ssp_CosaDmlMtaBatteryGetRemainingTime:Failed to retrieve the Battery Remaining Time\n");
        return SSP_FAILURE;
    }

    return SSP_SUCCESS;

}

