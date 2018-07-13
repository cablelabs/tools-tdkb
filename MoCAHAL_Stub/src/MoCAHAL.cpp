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

#include "MoCAHAL.h"

/***************************************************************************
 *Function name : initialize
 *Description   : Initialize Function will be used for registering the wrapper method
 *                        with the agent so that wrapper function will be used in the script
 *
 *****************************************************************************/
bool MoCAHAL::initialize(IN const char* szVersion)
{
    return TEST_SUCCESS;
}


/***************************************************************************
 *Function name : testmodulepre_requisites
 *Description   : testmodulepre_requisites will  be used for setting the
 *                pre-requisites that are necessary for this component
 *
 *****************************************************************************/
std::string MoCAHAL::testmodulepre_requisites()
{
    DEBUG_PRINT(DEBUG_TRACE,"\n MoCAHAL testmodulepre_requisites --->Entry\n");
    return "SUCCESS";

}


/***************************************************************************
 *Function name : testmodulepost_requisites
 *Description    : testmodulepost_requisites will be used for resetting the
 *                pre-requisites that are set
 *
 *****************************************************************************/
bool MoCAHAL::testmodulepost_requisites()
{
    return TEST_SUCCESS;
}


/**************************************************************************
 * Function Name        : CreateObject
 * Description  : This function will be used to create a new object for the
 *                class "MoCAHAL".
*
 **************************************************************************/
extern "C" MoCAHAL* CreateObject(TcpSocketServer &ptrtcpServer)
{
    return new MoCAHAL(ptrtcpServer);
}


/*******************************************************************************************
 *
 * Function Name        : MoCAHAL_GetIfConfig
 * Description          : This function gets the MoCA Configuration Parameters that were previously set
 *
 * @param [in] req-    : ifIndex - index of the MoCA interface
 * @param [out] response - filled with SUCCESS or FAILURE based on the output staus of operation
 *
 ********************************************************************************************/
void MoCAHAL::MoCAHAL_GetIfConfig(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n MoCAHAL_GetIfConfig --->Entry\n");
    int ifIndex;
    int returnValue;
    char details[1000] = {'\0'};
    moca_cfg_t moca_config;

    ifIndex = req["ifIndex"].asInt();

    returnValue = ssp_MoCAHAL_GetIfConfig(ifIndex, &moca_config);
    if(0 == returnValue)
    {
	sprintf(details, "Value returned is :InstanceNumber=%lu, Alias=%s, bEnabled=%d, bPreferredNC=%d,  PrivacyEnabledSetting=%d, FreqCurrentMaskSetting=%s, KeyPassphrase=%s, TxPowerLimit=%d, AutoPowerControlPhyRate=%lu, BeaconPowerLimit=%lu, MaxIngressBWThreshold=%lu, MaxEgressBWThreshold=%lu, Reset=%d, MixedMode=%d, ChannelScanning=%d, AutoPowerControlEnable=%d, EnableTabooBit=%d, NodeTabooMask=%s, ChannelScanMask=%s",moca_config.InstanceNumber, moca_config.Alias, moca_config.bEnabled, moca_config.bPreferredNC, moca_config.PrivacyEnabledSetting, moca_config.FreqCurrentMaskSetting, moca_config.KeyPassphrase, moca_config.TxPowerLimit, moca_config.AutoPowerControlPhyRate, moca_config.BeaconPowerLimit, moca_config.MaxIngressBWThreshold, moca_config.MaxEgressBWThreshold, moca_config.Reset, moca_config.MixedMode, moca_config.ChannelScanning, moca_config.AutoPowerControlEnable, moca_config.EnableTabooBit, moca_config.NodeTabooMask, moca_config.ChannelScanMask);
        response["result"]="SUCCESS";
        response["details"]=details;
	DEBUG_PRINT(DEBUG_TRACE,"\n MoCAHAL_GetIfConfig ---->Execution success\n");
        return;
    }
    else
    {
        sprintf(details, "MoCAHAL_GetIfConfig operation failed");
        response["result"]="FAILURE";
        response["details"]=details;
        DEBUG_PRINT(DEBUG_TRACE,"\n MoCAHAL_GetIfConfig ---->Error in execution\n");
        return;
    }
}


/*******************************************************************************************
 *
 * Function Name        : MoCAHAL_IfGetDynamicInfo
 * Description          : This function gets the Dynamic Status information on the interface & its associated network.
 *
 * @param [in] req-    : ifIndex - index of the MoCA interface
 * @param [out] response - filled with SUCCESS or FAILURE based on the output staus of operation
 *
 ********************************************************************************************/

void MoCAHAL::MoCAHAL_IfGetDynamicInfo(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n MoCAHAL_IfGetDynamicInfo --->Entry\n");
    int ifIndex;
    int returnValue;
    char details[1500] = {'\0'};
    moca_dynamic_info_t dynamic_info;

    ifIndex = req["ifIndex"].asInt();

    returnValue = ssp_MoCAHAL_IfGetDynamicInfo(ifIndex, &dynamic_info);
    if(0 == returnValue)
    {
        sprintf(details, "Value returned is :Status=%d, LastChange=%lu, MaxIngressBW=%lu, MaxEgressBW=%lu, CurrentVersion=%s, NetworkCoordinator=%lu, NodeID=%lu, BackupNC=%lu, PrivacyEnabled=%d, FreqCurrentMask=%s, CurrentOperFreq=%lu, LastOperFreq=%lu, TxBcastRate=%lu, MaxIngressBWThresholdReached=%d, MaxEgressBWThresholdReached=%d, NumberOfConnectedClients=%lu, NetworkCoordinatorMACAddress=%s, LinkUpTime=%lu", dynamic_info.Status, dynamic_info.LastChange, dynamic_info.MaxIngressBW, dynamic_info.MaxEgressBW, dynamic_info.CurrentVersion, dynamic_info.NetworkCoordinator, dynamic_info.NodeID, dynamic_info.BackupNC, dynamic_info.PrivacyEnabled, dynamic_info.FreqCurrentMask, dynamic_info.CurrentOperFreq, dynamic_info.LastOperFreq, dynamic_info.TxBcastRate, dynamic_info.MaxIngressBWThresholdReached, dynamic_info.MaxEgressBWThresholdReached, dynamic_info.NumberOfConnectedClients, dynamic_info.NetworkCoordinatorMACAddress, dynamic_info.LinkUpTime);
        response["result"]="SUCCESS";
        response["details"]=details;
        DEBUG_PRINT(DEBUG_TRACE,"\n MoCAHAL_IfGetDynamicInfo--->Execution success\n");
        return;
    }
    else
    {
        sprintf(details, "MoCAHAL_IfGetDynamicInfo operation failed");
        response["result"]="FAILURE";
        response["details"]=details;
        DEBUG_PRINT(DEBUG_TRACE,"\n MoCAHAL_IfGetDynamicInfo ---->Error in execution\n");
        return;
    }
}


/*******************************************************************************************
 *
 * Function Name        : MoCAHAL_IfGetStaticInfo
 * Description          : This function gets the Static Information from the Local Node
 *
 * @param [in] req-    : ifIndex - index of the MoCA interface
 * @param [out] response - filled with SUCCESS or FAILURE based on the output staus of operation
 *
 ********************************************************************************************/
void MoCAHAL::MoCAHAL_IfGetStaticInfo(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n MoCAHAL_IfGetStaticInfo --->Entry\n");
    int ifIndex;
    int returnValue;
    char details[1000] = {'\0'};
    moca_static_info_t static_info;

    ifIndex = req["ifIndex"].asInt();

    returnValue = ssp_MoCAHAL_IfGetStaticInfo(ifIndex, &static_info);
    if(0 == returnValue)
    {
        sprintf(details, "Value returned is :Name=%s, MacAddress=%s, FirmwareVersion=%s, MaxBitRate=%lu, HighestVersion=%s, FreqCapabilityMask=%s, NetworkTabooMask=%s, TxBcastPowerReduction=%lu, QAM256Capable=%d, PacketAggregationCapability=%d", static_info.Name, static_info.MacAddress, static_info.FirmwareVersion, static_info.MaxBitRate, static_info.HighestVersion, static_info.FreqCapabilityMask, static_info.NetworkTabooMask, static_info.TxBcastPowerReduction, static_info.QAM256Capable, static_info.PacketAggregationCapability);
        response["result"]="SUCCESS";
        response["details"]=details;
        DEBUG_PRINT(DEBUG_TRACE,"\n MoCAHAL_IfGetStaticInfo--->Execution success\n");
        return;
    }
    else
    {
        sprintf(details, "MoCAHAL_IfGetStaticInfo operation failed");
        response["result"]="FAILURE";
        response["details"]=details;
        DEBUG_PRINT(DEBUG_TRACE,"\n MoCAHAL_IfGetStaticInfo ---->Error in execution\n");
        return;
    }
}


/*******************************************************************************************
 *
 * Function Name        : MoCAHAL_IfGetStats
 * Description          : This function Gets the Statistics on the Interface at Network Layer
 *
 * @param [in] req-    : ifIndex - index of the MoCA interface
 * @param [out] response - filled with SUCCESS or FAILURE based on the output staus of operation
 *
 ********************************************************************************************/
void MoCAHAL::MoCAHAL_IfGetStats(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n MoCAHAL_IfGetStats --->Entry\n");
    int ifIndex;
    int returnValue;
    char details[1000] = {'\0'};
    moca_stats_t stats;

    ifIndex = req["ifIndex"].asInt();

    returnValue = ssp_MoCAHAL_IfGetStats(ifIndex, &stats);
    if(0 == returnValue)
    {
        sprintf(details, "Value returned is :BytesSent=%lu, BytesReceived=%lu, PacketsSent=%lu, PacketsReceived=%lu, ErrorsSent=%lu, ErrorsReceived=%lu, UnicastPacketsSent=%lu, UnicastPacketsReceived=%lu, DiscardPacketsSent=%lu, DiscardPacketsReceived=%lu, MulticastPacketsSent=%lu, MulticastPacketsReceived=%lu, BroadcastPacketsSent=%lu, BroadcastPacketsReceived=%lu, UnknownProtoPacketsReceived=%lu, ExtAggrAverageTx=%lu, ExtAggrAverageTx=%lu", stats.BytesSent, stats.BytesReceived, stats.PacketsSent, stats.PacketsReceived, stats.ErrorsSent, stats.ErrorsReceived, stats.UnicastPacketsSent, stats.UnicastPacketsReceived, stats.DiscardPacketsSent, stats.DiscardPacketsReceived, stats.MulticastPacketsSent, stats.MulticastPacketsReceived, stats.BroadcastPacketsSent, stats.BroadcastPacketsReceived, stats.UnknownProtoPacketsReceived, stats.ExtAggrAverageTx, stats.ExtAggrAverageTx);
        response["result"]="SUCCESS";
        response["details"]=details;
        DEBUG_PRINT(DEBUG_TRACE,"\n MoCAHAL_IfGetStats--->Execution success\n");
        return;
    }
    else
    {
        sprintf(details, "MoCAHAL_IfGetStats operation failed");
        response["result"]="FAILURE";
        response["details"]=details;
        DEBUG_PRINT(DEBUG_TRACE,"\n MoCAHAL_IfGetStats ---->Error in execution\n");
        return;
    }
}


/*******************************************************************************************
 *
 * Function Name        : MoCAHAL_GetNumAssociatedDevices
 * Description          : This function Gets the Number of Nodes on the MoCA network.
 *
 * @param [in] req-    : ifIndex - index of the MoCA interface
 * @param [out] response - filled with SUCCESS or FAILURE based on the output staus of operation
 *
 ********************************************************************************************/
void MoCAHAL::MoCAHAL_GetNumAssociatedDevices(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n MoCAHAL_GetNumAssociatedDevices --->Entry\n");
    int ifIndex;
    int returnValue;
    char details[1000] = {'\0'};
    ULONG devCount;

    ifIndex = req["ifIndex"].asInt();

    returnValue = ssp_MoCAHAL_GetNumAssociatedDevices(ifIndex, &devCount);
    if(0 == returnValue)
    {
        sprintf(details, "Value returned is : %lu",devCount);
        response["result"]="SUCCESS";
        response["details"]=details;
        DEBUG_PRINT(DEBUG_TRACE,"\n MoCAHAL_GetNumAssociatedDevices--->Execution success\n");
        return;
    }
    else
    {
        sprintf(details, "MoCAHAL_GetNumAssociatedDevices operation failed");
        response["result"]="FAILURE";
        response["details"]=details;
        DEBUG_PRINT(DEBUG_TRACE,"\n MoCAHAL_GetNumAssociatedDevices ---->Error in execution\n");
        return;
    }
}


/*******************************************************************************************
 *
 * Function Name        : MoCAHAL_IfGetExtCounter
 * Description          : This function Gets the Statistics on the Interface at MoCA MAC Layer.
 *
 * @param [in] req-    : ifIndex - index of the MoCA interface
 * @param [out] response - filled with SUCCESS or FAILURE based on the output staus of operation
 *
 ********************************************************************************************/
void MoCAHAL::MoCAHAL_IfGetExtCounter(IN const Json::Value& req, OUT Json::Value& response)
{
    DEBUG_PRINT(DEBUG_TRACE,"\n MoCAHAL_IfGetExtCounter---->Entry\n");
    int ifIndex;
    int returnValue;
    char details[1000] = {'\0'};
    moca_mac_counters_t mac_counters;

    ifIndex = req["ifIndex"].asInt();

    returnValue = ssp_MoCAHAL_IfGetExtCounter(ifIndex, &mac_counters);
    if(0 == returnValue)
    {
        sprintf(details, "Value returned is :Map=%lu, Rsrv=%lu, Lc=%lu, Adm=%lu, Probe=%lu, Async=%lu", mac_counters.Map, mac_counters.Rsrv, mac_counters.Lc, mac_counters.Adm, mac_counters.Probe, mac_counters.Async);
        response["result"]="SUCCESS";
        response["details"]=details;
        DEBUG_PRINT(DEBUG_TRACE,"\n MoCAHAL_IfGetExtCounter--->Execution success\n");
        return;
    }
    else
    {
        sprintf(details, "MoCAHAL_IfGetExtCounter operation failed");
        response["result"]="FAILURE";
        response["details"]=details;
        DEBUG_PRINT(DEBUG_TRACE,"\n MoCAHAL_IfGetExtCounter---->Error in execution\n");
        return;
    }
}

/**************************************************************************
 * Function Name : cleanup
 * Description   : This function will be used to clean the log details.
 *
 **************************************************************************/
bool MoCAHAL::cleanup(IN const char* szVersion)
{
    DEBUG_PRINT(DEBUG_LOG,"MoCAHAL shutting down\n");
    return TEST_SUCCESS;
}

/**************************************************************************
 * Function Name : DestroyObject
 * Description   : This function will be used to destroy the object.
 *
 **************************************************************************/
extern "C" void DestroyObject(MoCAHAL *stubobj)
{
    DEBUG_PRINT(DEBUG_LOG,"Destroying MoCAHAL object\n");
    delete stubobj;
}

