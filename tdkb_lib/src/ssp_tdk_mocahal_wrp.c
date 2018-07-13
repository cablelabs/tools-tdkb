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

#include <stdio.h>
#include "ssp_tdk_mocahal_wrp.h"

/*******************************************************************************************
 *
 * Function Name        : ssp_MoCAHAL_GetIfConfig
 * Description          : This function invokes MoCA hal api moca_GetIfConfig()
 * @param [in] req-     : ifIndex - index of the MoCA interface
                          pmoca_config - buffer to get the moca_config values
 * @param [out] response - filled with SUCCESS or FAILURE based on the output staus of operation
 *
 ********************************************************************************************/
int ssp_MoCAHAL_GetIfConfig(unsigned long ifIndex, moca_cfg_t *pmoca_config)
{
    printf("\n ssp_MoCAHAL_GetIfConfig----> Entry\n");
    int return_status = 0;

    return_status = moca_GetIfConfig(ifIndex, pmoca_config);
    if(return_status != SSP_SUCCESS)
    {
     printf("\nssp_MoCAHAL_GetIfConfig::Failed\n");
     return SSP_FAILURE;
    }
    else
    {
     printf("\n ssp_MoCAHAL_GetIfConfig::Success\n");
     return SSP_SUCCESS;
    }
}


/*******************************************************************************************
 *
 * Function Name        : ssp_MoCAHAL_IfGetDynamicInfo
 * Description          : This function invokes MoCA hal api moca_IfGetDynamicInfo()
 * @param [in] req-     : ifIndex - index of the MoCA interface
                          pdynamic_info - buffer to get the dynamic info
 * @param [out] response - filled with SUCCESS or FAILURE based on the output staus of operation
 *
 ********************************************************************************************/
int ssp_MoCAHAL_IfGetDynamicInfo(unsigned long ifIndex, moca_dynamic_info_t *pdynamic_info)
{
    printf("\n ssp_MoCAHAL_IfGetDynamicInfo----> Entry\n");
    int return_status = 0;

    return_status = moca_IfGetDynamicInfo(ifIndex, pdynamic_info);
    if(return_status != SSP_SUCCESS)
    {
     printf("\nssp_MoCAHAL_IfGetDynamicInfo::Failed\n");
     return SSP_FAILURE;
    }
    else
    {
     printf("\n ssp_MoCAHAL_IfGetDynamicInfo::Success\n");
     return SSP_SUCCESS;
    }

}


/*******************************************************************************************
 *
 * Function Name        : ssp_MoCAHAL_IfGetStaticInfo
 * Description          : This function invokes MoCA hal api moca_IfGetStaticInfo()
 * @param [in] req-     : ifIndex - index of the MoCA interface
                          pdynamic_info - buffer to get the static info
 * @param [out] response - filled with SUCCESS or FAILURE based on the output staus of operation
 *
 ********************************************************************************************/
int ssp_MoCAHAL_IfGetStaticInfo(unsigned long ifIndex, moca_static_info_t *pstatic_info)
{    printf("\n ssp_MoCAHAL_IfGetStaticInfo----> Entry\n");
    int return_status = 0;

    return_status = moca_IfGetStaticInfo(ifIndex, pstatic_info);
    if(return_status != SSP_SUCCESS)
    {
     printf("\nssp_MoCAHAL_IfGetStaticInfo::Failed\n");
     return SSP_FAILURE;
    }
    else
    {
     printf("\n ssp_MoCAHAL_IfGetStaticInfo::Success\n");
     return SSP_SUCCESS;
    }
}


/*******************************************************************************************
 *
 * Function Name        : ssp_MoCAHAL_IfGetStats
 * Description          : This function invokes MoCA hal api moca_IfGetStats()
 * @param [in] req-     : ifIndex - index of the MoCA interface
                          pdynamic_info - buffer to get the moca_stats
 * @param [out] response - filled with SUCCESS or FAILURE based on the output staus of operation
 *
 ********************************************************************************************/
int ssp_MoCAHAL_IfGetStats(unsigned long ifIndex, moca_stats_t *pmoca_stats)
{
    printf("\n ssp_MoCAHAL_IfGetStats----> Entry\n");
    int return_status = 0;

    return_status = moca_IfGetStats(ifIndex, pmoca_stats);
    if(return_status != SSP_SUCCESS)
    {
     printf("\nssp_MoCAHAL_IfGetStats::Failed\n");
     return SSP_FAILURE;
    }
    else
    {
     printf("\n ssp_MoCAHAL_IfGetStats::Success\n");
     return SSP_SUCCESS;
    }
}


/*******************************************************************************************
 *
 * Function Name        : ssp_MoCAHAL_GetNumAssociatedDevices
 * Description          : This function invokes MoCA hal api moca_GetNumAssociatedDevices()
 * @param [in] req-     : ifIndex - index of the MoCA interface
                          pulCount - buffer to get the associated device count
 * @param [out] response - filled with SUCCESS or FAILURE based on the output staus of operation
 *
 ********************************************************************************************/
int ssp_MoCAHAL_GetNumAssociatedDevices(unsigned long ifIndex, ULONG *pulCount)
{
    printf("\n ssp_MoCAHAL_GetNumAssociatedDevices----> Entry\n");
    int return_status = 0;

    return_status = moca_GetNumAssociatedDevices(ifIndex, pulCount);
    if(return_status != SSP_SUCCESS)
    {
     printf("\nssp_MoCAHAL_GetNumAssociatedDevices::Failed\n");
     return SSP_FAILURE;
    }
    else
    {
     printf("\n ssp_MoCAHAL_GetNumAssociatedDevices::Success\n");
     return SSP_SUCCESS;
    }
}


/*******************************************************************************************
 *
 * Function Name        : ssp_MoCAHAL_IfGetExtCounter
 * Description          : This function invokes MoCA hal api moca_IfGetExtCounter()
 * @param [in] req-     : ifIndex - index of the MoCA interface
                          pulCount - buffer to get the extCounter
 * @param [out] response - filled with SUCCESS or FAILURE based on the output staus of operation
 *
 ********************************************************************************************/
int ssp_MoCAHAL_IfGetExtCounter(unsigned long ifIndex, moca_mac_counters_t *pmoca_mac_counters)
{
    printf("\n ssp_MoCAHAL_IfGetExtCounter----> Entry\n");
    int return_status = 0;

    return_status = moca_IfGetExtCounter(ifIndex, pmoca_mac_counters);
    if(return_status != SSP_SUCCESS)
    {
     printf("\nssp_MoCAHAL_IfGetExtCounter::Failed\n");
     return SSP_FAILURE;
    }
    else
    {
     printf("\n ssp_MoCAHAL_IfGetExtCounter::Success\n");
     return SSP_SUCCESS;
    }
}

