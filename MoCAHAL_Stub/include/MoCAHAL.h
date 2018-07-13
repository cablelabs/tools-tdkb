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
#ifndef __MoCAHAL_STUB_H__
#define __MoCAHAL_STUB_H__
#include <json/json.h>
#include <unistd.h>
#include <string.h>
#include <dlfcn.h>
#include <stdlib.h>
#include "rdkteststubintf.h"
#include "rdktestagentintf.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <fstream>
#include <sstream>
#include <jsonrpccpp/server/connectors/tcpsocketserver.h>
#define IN
#define OUT
#define TEST_SUCCESS true
#define TEST_FAILURE false

#define MAC_PADDING                     12

#ifndef ULONG
#define ULONG unsigned long
#endif

#ifndef BOOL
#define BOOL  unsigned char
#endif

#ifndef CHAR
#define CHAR  char
#endif

#ifndef UCHAR
#define UCHAR unsigned char
#endif

#ifndef INT
#define INT   int
#endif

#ifndef UINT
#define UINT  unsigned int
#endif

typedef enum
{
    IF_STATUS_Up               = 1,
    IF_STATUS_Down,
    IF_STATUS_Unknown,
    IF_STATUS_Dormant,
    IF_STATUS_NotPresent,
    IF_STATUS_LowerLayerDown,
    IF_STATUS_Error
} moca_if_status_t;

typedef struct {
    ULONG                           InstanceNumber;
    CHAR                            Alias[64];
    BOOL                                bEnabled;
    BOOL                                bPreferredNC;
    BOOL                                PrivacyEnabledSetting;
    UCHAR                           FreqCurrentMaskSetting[128];
    CHAR                            KeyPassphrase[18];
    INT                             TxPowerLimit;
    ULONG                           AutoPowerControlPhyRate;
    ULONG                           BeaconPowerLimit;
    ULONG                           MaxIngressBWThreshold;
    ULONG                           MaxEgressBWThreshold;
    BOOL                            Reset;
    BOOL                            MixedMode;
    BOOL                            ChannelScanning;
    BOOL                            AutoPowerControlEnable;
    BOOL                            EnableTabooBit;
    UCHAR                           NodeTabooMask[128];
    UCHAR                           ChannelScanMask[128];
} moca_cfg_t;

typedef struct {
    moca_if_status_t                Status;
    ULONG                           LastChange;
    ULONG                           MaxIngressBW;
    ULONG                           MaxEgressBW;
    CHAR                            CurrentVersion[64];
    ULONG                           NetworkCoordinator;
    ULONG                           NodeID;
    ULONG                           BackupNC;
    BOOL                            PrivacyEnabled;
    UCHAR                           FreqCurrentMask[8];
    ULONG                           CurrentOperFreq;
    ULONG                           LastOperFreq;
    ULONG                           TxBcastRate;
    BOOL                            MaxIngressBWThresholdReached;
    BOOL                            MaxEgressBWThresholdReached;
    ULONG                           NumberOfConnectedClients;
    CHAR                            NetworkCoordinatorMACAddress[18];
    ULONG                                                       LinkUpTime;

} moca_dynamic_info_t;

typedef struct {
    CHAR                            Name[64];           
    UCHAR                           MacAddress[6 + MAC_PADDING];
    CHAR                            FirmwareVersion[64];
    ULONG                           MaxBitRate;
    CHAR                            HighestVersion[64];
    UCHAR                           FreqCapabilityMask[8];
    UCHAR                           NetworkTabooMask[128];
    ULONG                           TxBcastPowerReduction;
    BOOL                            QAM256Capable;
    BOOL                           PacketAggregationCapability;
} moca_static_info_t;

typedef struct {
        /* Number of Bytes Sent & Received */
    ULONG                           BytesSent;
    ULONG                           BytesReceived;

        /* Number of Packets Sent & Received */
    ULONG                           PacketsSent;
    ULONG                           PacketsReceived;

        /* Number of Errors in Sent & Received Packets */
    ULONG                           ErrorsSent;
    ULONG                           ErrorsReceived;

        /* Number of Unicast Packets Sent & Received */
    ULONG                           UnicastPacketsSent;
    ULONG                           UnicastPacketsReceived;

        /* Number of Packets Discard (Tx & Rx side) */
    ULONG                           DiscardPacketsSent;
    ULONG                           DiscardPacketsReceived;

        /* Number of Multicast Packets Sent & Received */
    ULONG                           MulticastPacketsSent;
    ULONG                           MulticastPacketsReceived;

        /* Number of Broadcast Packets Sent & Received */
    ULONG                           BroadcastPacketsSent;
    ULONG                           BroadcastPacketsReceived;

        /* Number of Unknown Protocol Packets Received */
    ULONG                           UnknownProtoPacketsReceived;
    ULONG                           ExtAggrAverageTx;
    ULONG                           ExtAggrAverageRx;
} moca_stats_t;


typedef struct {
        /* Number of MAP packets */
    ULONG                           Map;
        /* Number of Reservation Request Packets */
    ULONG                           Rsrv;
        /* Number of Link Control Packets */
    ULONG                           Lc;
        /* Number of Admission Request Packets */
    ULONG                           Adm;
        /* Number of Probes */
    ULONG                           Probe;
        /* Number of Beacons */
    ULONG                           Async;
} moca_mac_counters_t;


typedef struct {
        /* Aggregate Tx Payload Data Units (Not MoCA Control Packets). */
    ULONG                           Tx;
        /* Aggregate Rx Payload Data Units (Not MoCA Control Packets). */
    ULONG                           Rx;
} moca_aggregate_counters_t;

/* To provide external linkage to C Functions defined in TDKB Component folder */
extern "C"
{
    int ssp_MoCAHAL_GetIfConfig(unsigned long ifIndex, moca_cfg_t *pmoca_config);
    int ssp_MoCAHAL_IfGetDynamicInfo(unsigned long ifIndex, moca_dynamic_info_t *pdynamic_info);
    int ssp_MoCAHAL_IfGetStaticInfo(unsigned long ifIndex, moca_static_info_t *pstatic_info);
    int ssp_MoCAHAL_IfGetStats(unsigned long ifIndex, moca_stats_t *pmoca_stats);
    int ssp_MoCAHAL_GetNumAssociatedDevices(unsigned long ifIndex, unsigned long *pulCount);
    int ssp_MoCAHAL_IfGetExtCounter(unsigned long ifIndex, moca_mac_counters_t *pmoca_mac_counters);
};


class RDKTestAgent;
class MoCAHAL : public RDKTestStubInterface, public AbstractServer<MoCAHAL>
{
    public:
         MoCAHAL(TcpSocketServer &ptrRpcServer) : AbstractServer <MoCAHAL>(ptrRpcServer)
                {
                  this->bindAndAddMethod(Procedure("MoCAHAL_GetIfConfig", PARAMS_BY_NAME, JSON_STRING,"ifIndex", JSON_INTEGER, NULL), &MoCAHAL::MoCAHAL_GetIfConfig);
                  this->bindAndAddMethod(Procedure("MoCAHAL_IfGetDynamicInfo", PARAMS_BY_NAME, JSON_STRING,"ifIndex", JSON_INTEGER, NULL), &MoCAHAL::MoCAHAL_IfGetDynamicInfo);
                  this->bindAndAddMethod(Procedure("MoCAHAL_IfGetStaticInfo", PARAMS_BY_NAME, JSON_STRING,"ifIndex", JSON_INTEGER, NULL), &MoCAHAL::MoCAHAL_IfGetStaticInfo);
                  this->bindAndAddMethod(Procedure("MoCAHAL_IfGetStats", PARAMS_BY_NAME, JSON_STRING,"ifIndex", JSON_INTEGER, NULL), &MoCAHAL::MoCAHAL_IfGetStats);
                  this->bindAndAddMethod(Procedure("MoCAHAL_GetNumAssociatedDevices", PARAMS_BY_NAME, JSON_STRING,"ifIndex", JSON_INTEGER, NULL), &MoCAHAL::MoCAHAL_GetNumAssociatedDevices);
                  this->bindAndAddMethod(Procedure("MoCAHAL_IfGetExtCounter", PARAMS_BY_NAME, JSON_STRING,"ifIndex", JSON_INTEGER, NULL), &MoCAHAL::MoCAHAL_IfGetExtCounter);
		}

        /*inherited functions*/
        bool initialize(IN const char* szVersion);
        bool cleanup(IN const char* szVersion);
        std::string testmodulepre_requisites();
        bool testmodulepost_requisites();

        /*MoCAHAL Stub Wrapper functions*/
        void MoCAHAL_GetIfConfig(IN const Json::Value& req, OUT Json::Value& response);
        void MoCAHAL_IfGetStaticInfo(IN const Json::Value& req, OUT Json::Value& response);
        void MoCAHAL_IfGetDynamicInfo(IN const Json::Value& req, OUT Json::Value& response);
        void MoCAHAL_IfGetStats(IN const Json::Value& req, OUT Json::Value& response);
        void MoCAHAL_GetNumAssociatedDevices(IN const Json::Value& req, OUT Json::Value& response);
        void MoCAHAL_IfGetExtCounter(IN const Json::Value& req, OUT Json::Value& response);
};
#endif //__MoCAHAL_STUB_H__
