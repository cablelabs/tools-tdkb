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
#include "ssp_tdk_cmhal_wrp.h"
#include "cm_hal.h"


/*******************************************************************************************
 *
 * Function Name        : ssp_CMHAL_GetParamCharValue
 * Description          : This function will invoke the hal api of CM to get the char values
 *
 * @param [in]          : paramName: specifies the name of the API
			  value: returns the value of the parameter
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/

int ssp_CMHAL_GetParamCharValue(char* paramName, char* value)
{
    int return_status = 0;
    CMMGMT_CM_DOCSIS_INFO docsisinfo;
    CMMGMT_CM_IPV6DHCP_INFO v6dhcpinfo;
    CMMGMT_CM_DHCP_INFO v4dhcpinfo;
    PCMMGMT_CM_DS_CHANNEL pDsFreq,temp_DsFreq;
    PCMMGMT_CM_US_CHANNEL pUsFreq,temp_UsFreq;
    PCMMGMT_CM_US_CHANNEL pUsPower,temp_UsPower;
    PCMMGMT_CM_DS_CHANNEL pDsPower,temp_DsPower;
    printf("\nEntering ssp_CMHAL_GetParamCharValues function\n\n");
    if( !(strcmp(paramName, "CMStatus")) )
    {
        return_status = docsis_getCMStatus(value);
        printf("Return status of docsis_getCMStatus %d", return_status);

        if ( return_status != SSP_SUCCESS)
        {
            printf("ssp_CMHAL_GetCharParamValues : Failed to get the CM status\n");
            return SSP_FAILURE;
        }
    }
    else if( !(strcmp(paramName, "MddIpModeOverride")) )
    {
        return_status = docsis_GetMddIpModeOverride(value);
        printf("Return status of docsis_GetMddIpModeOverride %d", return_status);
        if ( return_status != SSP_SUCCESS)
        {
            printf("ssp_CMHAL_GetParamCharValues : Failed to get MddIpModeOverride\n");
            return SSP_FAILURE;
        }
    }
    else if( !(strcmp(paramName, "ProvIpType")) )
    {
        return_status = docsis_GetProvIpType(value);
        printf("Return status of docsis_GetProvIpType %d", return_status);
        if ( return_status != SSP_SUCCESS)
        {
            printf("ssp_CMHAL_GetParamCharValues : Failed to get IPType\n");
            return SSP_FAILURE;
        }
    }
    else if( !(strcmp(paramName, "MarketInfo")) )
    {
        return_status = cm_hal_GetMarket(value);
        printf("Return status of cm_hal_GetMarket %d", return_status);
        if ( return_status != SSP_SUCCESS)
        {
            printf("ssp_CMHAL_GetCharParamValues : Failed to get Market info\n");
            return SSP_FAILURE;
        }
    }
    else if( !(strcmp(paramName, "version")) )
    {
       if(value)
       {
           return_status = docsis_GetDOCSISInfo(&docsisinfo);
           printf("ssp_CMHAL_GetParamCharValue: Version retreived :%s\n",docsisinfo.DOCSISVersion);
           strcpy(value, docsisinfo.DOCSISVersion);
       }
       else
           return_status = docsis_GetDOCSISInfo(value);
    }
    else if( !(strcmp(paramName, "Ipv6DhcpBootFileName")) )
    {
        if(value)
        {
           strcpy(value, " ");
            return_status = cm_hal_GetIPv6DHCPInfo(&v6dhcpinfo);
           printf("ssp_CMHAL_GetParamCharValue: BootFileName retreived :%s\n",v6dhcpinfo.IPv6BootFileName);
            strcpy(value, v6dhcpinfo.IPv6BootFileName);
        }
        else
            return_status = cm_hal_GetIPv6DHCPInfo(value);
    }
    else if( !(strcmp(paramName, "Ipv4DhcpBootFileName")) )
    {
        if(value)
        {
            strcpy(value, " ");
            return_status = cm_hal_GetDHCPInfo(&v4dhcpinfo);
           printf("ssp_CMHAL_GetParamCharValue: BootFileName retreived :%s\n",v4dhcpinfo.BootFileName);
            strcpy(value, v4dhcpinfo.BootFileName);
        }
        else
            return_status = cm_hal_GetDHCPInfo(value);
    }
    else if( !(strcmp(paramName, "Ipv6DhcpIPAddress")) )
    {
        if(value)
        {
            strcpy(value, " ");
            return_status = cm_hal_GetIPv6DHCPInfo(&v6dhcpinfo);
            printf("ssp_CMHAL_GetParamCharValue: IPAddress retreived :%s\n",v6dhcpinfo.IPv6Address);
            strcpy(value, v6dhcpinfo.IPv6Address);
	 }
        else
            return_status = cm_hal_GetIPv6DHCPInfo(value);
    }
    else if( !(strcmp(paramName, "ConfigFileName")) )
    {
        if(value)
        {
            strcpy(value, " ");
            return_status = docsis_GetDOCSISInfo(&docsisinfo);
           printf("ssp_CMHAL_GetParamCharValue: ConfigFileName retreived :%s\n",docsisinfo.DOCSISConfigFileName);
            strcpy(value, docsisinfo.DOCSISConfigFileName);
        }
        else
            return_status = docsis_GetDOCSISInfo(value);
    }
    else if( !(strcmp(paramName, "DS_DataRate")) )
    {
        if(value)
        {
            return_status = docsis_GetDOCSISInfo(&docsisinfo);
            printf("ssp_CMHAL_GetParamCharValue: DownstreamDataRate retreived :%s\n",docsisinfo.DOCSISDownstreamDataRate);
            strcpy(value, docsisinfo.DOCSISDownstreamDataRate);
        }
        else
            return_status = docsis_GetDOCSISInfo(value);
    }
    else if( !(strcmp(paramName, "US_DataRate")) )
    {
        if(value)
        {
            return_status = docsis_GetDOCSISInfo(&docsisinfo);
            printf("ssp_CMHAL_GetParamCharValue: UpstreamDataRate retreived :%s\n",docsisinfo.DOCSISUpstreamDataRate);
            strcpy(value, docsisinfo.DOCSISUpstreamDataRate);
        }
        else
            return_status = docsis_GetDOCSISInfo(value);
    }
    else if( !(strcmp(paramName, "DS_Frequency")) )
    {
       long unsigned int  count;
       return_status = docsis_GetNumOfActiveRxChannels(&count);
       printf("Count of Active Rx channels is %d\n",count);
       if (return_status == 0)
       {
           pDsFreq = (PCMMGMT_CM_DS_CHANNEL) malloc(sizeof(CMMGMT_CM_DS_CHANNEL)*count);
           if(!pDsFreq)
           {
               printf("Memory has not allocated successfully \n ");
           }
           else
           {
               return_status = docsis_GetDSChannel(&pDsFreq);
               int i;
	       strcpy(value, "");
               for(i=0;i<count;i++)
               {
                   printf("ssp_CMHAL_GetParamCharValue: DS Frequency retreived :%s\n",pDsFreq->Frequency);
                   char FreqString[64];

                   strcpy(FreqString,pDsFreq->Frequency);
                   FreqString[strlen(FreqString)- 4]  = '\0';
                   strcat(value, FreqString);
                   strcat(value, ",");
                   pDsFreq++;
               }
           }
           free(pDsFreq);
       }
    }
    else if( !(strcmp(paramName, "US_Frequency")) )
    {
        long unsigned int  count;
       return_status = docsis_GetNumOfActiveTxChannels(&count);
        printf("Count of Active Tx channels is %d\n",count);
        if (return_status == 0)
        {
            pUsFreq = (PCMMGMT_CM_US_CHANNEL) malloc(sizeof(CMMGMT_CM_US_CHANNEL)*count);
            if(!pUsFreq)
            {
                printf("Memory has not allocated successfully \n ");
            }
            else
            {
                return_status = docsis_GetUSChannel(&pUsFreq);
                int i;
                strcpy(value,"");
                for(i=0;i<count;i++)
                {
                    printf("ssp_CMHAL_GetParamCharValue: US Frequency retreived :%s\n",pUsFreq->Frequency);
                    char FreqString[64];
                    strcpy(FreqString,pUsFreq->Frequency);
                    FreqString[strlen(FreqString)- 4]  = '\0';
                    strcat(value, FreqString);
                    strcat(value, ",");
                    pUsFreq++;
                }
            }
            free(pUsFreq);
        }
    }
    else if( !(strcmp(paramName, "ModulationAndSNRLevel")) )
    {
        long unsigned int  count;
        return_status = docsis_GetNumOfActiveRxChannels(&count);
        printf("Count of Active Rx channels is %d\n",count);
	if (return_status == 0)
        {
            pDsFreq = (PCMMGMT_CM_DS_CHANNEL) malloc(sizeof(CMMGMT_CM_DS_CHANNEL)*count);
            if(!pDsFreq)
            {
                printf("Memory has not allocated successfully \n ");
            }
            else
            {
                return_status = docsis_GetDSChannel(&pDsFreq);
                int i;
                strcpy(value, "");
                for(i=0;i<count;i++)
                {
                    printf("ssp_CMHAL_GetParamCharValue: DS Modulation retreived :%s\n",pDsFreq->Modulation);
                    printf("ssp_CMHAL_GetParamCharValue: DS SNR Level retreived :%s\n",pDsFreq->SNRLevel);
                    char SNRString[64];
                    strcpy(SNRString,pDsFreq->SNRLevel);
                    SNRString[strlen(SNRString)- 3]  = '\0';
                    strcat(value, pDsFreq->Modulation);
                    strcat(value, ":");
                    strcat(value, SNRString);
                    strcat(value, ",");
                    pDsFreq++;
                }
            }
            free(pDsFreq);
        }
    }
    else if( !(strcmp(paramName, "LockStatusAndChannelID")) )
    {
        long unsigned int  count;
        return_status = docsis_GetNumOfActiveRxChannels(&count);
        printf("Count of Active Rx channels is %d\n",count);
        if (return_status == 0)
        {
            pDsFreq = (PCMMGMT_CM_DS_CHANNEL) malloc(sizeof(CMMGMT_CM_DS_CHANNEL)*count);
            if(!pDsFreq)
            {
                printf("Memory has not allocated successfully \n ");
            }
            else
            {
                return_status = docsis_GetDSChannel(&pDsFreq);
                int i;
                strcpy(value, "");
                for(i=0;i<count;i++)
                {
                    printf("ssp_CMHAL_GetParamCharValue: DS LockStatus retreived :%s\n",pDsFreq->LockStatus);
                    printf("ssp_CMHAL_GetParamCharValue: DS ChannelID retreived :%d\n",pDsFreq->ChannelID);
                    char Channelid[16];
                    sprintf(Channelid,"%d",pDsFreq->ChannelID);
                    strcat(value, pDsFreq->LockStatus);
		    strcat(value, ":");
                    strcat(value, Channelid);
                    strcat(value, ",");
                    pDsFreq++;
                }
            }
            free(pDsFreq);
        }
    }
    else if( !(strcmp(paramName, "ModulationAndUSPower")) )
    {
        long unsigned int  count;
        return_status = docsis_GetNumOfActiveTxChannels(&count);
        printf("Count of Active Tx channels is %d\n",count);
        if (return_status == 0)
        {
            pUsPower = (PCMMGMT_CM_US_CHANNEL) malloc(sizeof(CMMGMT_CM_US_CHANNEL)*count);
            if(!pUsPower)
            {
                printf("Memory has not allocated successfully \n ");
            }
            else
            {
                return_status =  docsis_GetUSChannel(&pUsPower);
                int i;
                strcpy(value, "");
                temp_UsPower=pUsPower;
                for(i=0;i<count;i++)
                {
                    printf("ssp_CMHAL_GetParamCharValue: US Modulation retreived :%s\n",pUsPower->Modulation);
                    printf("ssp_CMHAL_GetParamCharValue: US Power Level retreived :%s\n",pUsPower->PowerLevel);
                    char PowerString[64];
                    strcpy(PowerString,pUsPower->PowerLevel);
                    strcat(value, pUsPower->Modulation);
                    strcat(value, ":");
                    strcat(value, PowerString);
                    strcat(value, ",");
                    temp_UsPower++;
                }
            }
            free(pUsPower);
        }
    }
    else if( !(strcmp(paramName, "DS_Power")) )
    {
       long unsigned int  count;
       return_status = docsis_GetNumOfActiveRxChannels(&count);
       printf("Count of Active Rx channels is %d\n",count);
       if (return_status == 0)
       {
           pDsPower = (PCMMGMT_CM_DS_CHANNEL) malloc(sizeof(CMMGMT_CM_DS_CHANNEL)*count);
           if(!pDsPower)
           {
               printf("Memory has not allocated successfully \n ");
	   }
           else
           {
               return_status = docsis_GetDSChannel(&pDsPower);
               int i;
               strcpy(value, "");
               temp_DsPower=pDsPower;
               for(i=0;i<count;i++)
               {
                   printf("ssp_CMHAL_GetParamCharValue: DS Power retreived :%s\n",pDsPower->PowerLevel);
                   char PowerString[128];
                   strcpy(PowerString,pDsPower->PowerLevel);
                   strcat(value, PowerString);
                   strcat(value, ",");
                   temp_DsPower++;
               }
           }
           free(pDsPower);
       }
    }
     else if( !(strcmp(paramName, "TimeServer")) )
    {
        if(value)
        {
            strcpy(value, " ");
            return_status = cm_hal_GetIPv6DHCPInfo(&v6dhcpinfo);
           printf("ssp_CMHAL_GetParamCharValue: TimeServer retreived :%s\n",v6dhcpinfo.IPv6TimeServer);
            strcpy(value,v6dhcpinfo.IPv6TimeServer);
        }
        else
            return_status = cm_hal_GetIPv6DHCPInfo(value);
    }
    else if( !(strcmp(paramName, "USChannelIDAndFrequency")) )
    {
        long unsigned int  count;
        return_status = docsis_GetNumOfActiveTxChannels(&count);
        printf("Count of Active Tx channels is %d\n",count);
        if (return_status == 0)
        {
            pUsFreq = (PCMMGMT_CM_US_CHANNEL) malloc(sizeof(CMMGMT_CM_US_CHANNEL)*count);
            if(!pUsFreq)
            {
                printf("Memory has not allocated successfully \n ");
            }
            else
            {
                return_status =  docsis_GetUSChannel(&pUsFreq);
                int i;
                strcpy(value, "");
                temp_UsFreq=pUsFreq;
                for(i=0;i<count;i++)
                {
                    printf("ssp_CMHAL_GetParamCharValue: US Channel ID retreived :%d\n",pUsFreq->ChannelID);
                    printf("ssp_CMHAL_GetParamCharValue: US Frequency retreived :%s\n",pUsFreq->Frequency);
                    char FreqString[64];
		    char Channelid[16];
                    sprintf(Channelid,"%d",pUsFreq->ChannelID);
                    strcpy(FreqString,pUsFreq->Frequency);
                    strcat(value, Channelid);
                    strcat(value, ":");
                    strcat(value, FreqString);
                    strcat(value, ",");
                    temp_UsFreq++;
                }
            }
            free(pUsFreq);
        }
    }
    else if( !(strcmp(paramName, "USSymbolRate")) )
    {
        long unsigned int  count;
       return_status = docsis_GetNumOfActiveTxChannels(&count);
        printf("Count of Active Tx channels is %d\n",count);
        if (return_status == 0)
        {
            pUsFreq = (PCMMGMT_CM_US_CHANNEL) malloc(sizeof(CMMGMT_CM_US_CHANNEL)*count);
            if(!pUsFreq)
            {
                printf("Memory has not allocated successfully \n ");
            }
            else
            {
                return_status = docsis_GetUSChannel(&pUsFreq);
                int i;
                strcpy(value,"");
                temp_UsFreq=pUsFreq;
                for(i=0;i<count;i++)
                {
                    printf("ssp_CMHAL_GetParamCharValue: US symbol retreived :%s\n",pUsFreq->SymbolRate);
                    char FreqString[64];
                    strcpy(FreqString,pUsFreq->SymbolRate);
                    strcat(value, FreqString);
                    strcat(value, ",");
                    temp_UsFreq++;
                }
            }
            free(pUsFreq);
        }
    }
    else if( !(strcmp(paramName, "DSChannelIDAndFrequency")) )
    {
        long unsigned int  count;
        return_status = docsis_GetNumOfActiveRxChannels(&count);
        printf("Count of Active Rx channels is %d\n",count);
        if (return_status == 0)
        {
            pDsFreq = (PCMMGMT_CM_DS_CHANNEL) malloc(sizeof(CMMGMT_CM_DS_CHANNEL)*count);
	    if(!pDsFreq)
            {
                printf("Memory has not allocated successfully \n ");
            }
            else
            {
                return_status =  docsis_GetDSChannel(&pDsFreq);
                int i;
                strcpy(value, "");
                temp_DsFreq=pDsFreq;
                for(i=0;i<count;i++)
                {
                    printf("ssp_CMHAL_GetParamCharValue: DS Channel ID retreived :%d\n",pDsFreq->ChannelID);
                    printf("ssp_CMHAL_GetParamCharValue: DS Frequency retreived :%s\n",pDsFreq->Frequency);
                    char FreqString[64];
                    char Channelid[16];
                    sprintf(Channelid,"%d",pDsFreq->ChannelID);
                    strcpy(FreqString,pDsFreq->Frequency);
                    strcat(value, Channelid);
                    strcat(value, ":");
                    strcat(value, FreqString);
                    strcat(value, ",");
                    temp_DsFreq++;
                }
            }
            free(pDsFreq);
        }
    }
    else if( !(strcmp(paramName, "DownstreamScanning")) )
    {
        if(value)
        {
            strcpy(value, " ");
            return_status = docsis_GetDOCSISInfo(&docsisinfo);
           printf("ssp_CMHAL_GetParamCharValue: Downstream Scanning retreived :%s\n",docsisinfo.DOCSISDownstreamScanning);
            strcpy(value, docsisinfo.DOCSISDownstreamScanning);
        }
        else
            return_status = docsis_GetDOCSISInfo(value);
    }
    else if( !(strcmp(paramName, "DSLockStatusAndFrequency")) )
    {
        long unsigned int  count;
        return_status = docsis_GetNumOfActiveRxChannels(&count);
        printf("Count of Active Rx channels is %d\n",count);
        if (return_status == 0)
        {
            pDsFreq = (PCMMGMT_CM_DS_CHANNEL) malloc(sizeof(CMMGMT_CM_DS_CHANNEL)*count);
            if(!pDsFreq)
            {
                printf("Memory has not allocated successfully \n ");
            }
            else
            {
                return_status =  docsis_GetDSChannel(&pDsFreq);
                int i;
                strcpy(value, "");
                temp_DsFreq=pDsFreq;
                for(i=0;i<count;i++)
                {
                    printf("ssp_CMHAL_GetParamCharValue: DS LockStatus retreived :%s\n",pDsFreq->LockStatus);
                    printf("ssp_CMHAL_GetParamCharValues: DS Frequency retreived :%s\n",pDsFreq->Frequency);
                    char FreqString[64];
                    strcpy(FreqString,pDsFreq->Frequency);
                    FreqString[strlen(FreqString)- 4]  = '\0';
                    strcat(value, pDsFreq->LockStatus);
                    strcat(value, ":");
                    strcat(value, FreqString);
                    strcat(value, ",");
                    temp_DsFreq++;
                }
            }
            free(pDsFreq);
        }
    }
    else if( !(strcmp(paramName, "UpstreamRanging")) )
    {
        if(value)
        {
            strcpy(value, " ");
            return_status = docsis_GetDOCSISInfo(&docsisinfo);
           printf("ssp_CMHal_GetStructValues: Upstream Ranging Ranging retreived :%s\n",docsisinfo.DOCSISUpstreamRanging);
            strcpy(value, docsisinfo.DOCSISUpstreamRanging);
        }
        else
            return_status = docsis_GetDOCSISInfo(value);
    }
    else if( !(strcmp(paramName, "ToDStatus")) )
    {
        if(value)
        {
            strcpy(value, " ");
            return_status = docsis_GetDOCSISInfo(&docsisinfo);
           printf("ssp_CMHal_GetStructValues: ToD Status retreived :%s\n",docsisinfo.ToDStatus);
            strcpy(value, docsisinfo.ToDStatus);
        }
        else
            return_status = docsis_GetDOCSISInfo(value);
    }
    else if( !(strcmp(paramName, "Ipv6DhcpPrefix")) )
    {
        if(value)
        {
            strcpy(value, " ");
            return_status = cm_hal_GetIPv6DHCPInfo(&v6dhcpinfo);
           printf("ssp_CMHal_GetParamCharValue: IPv6 Prefix retreived :%s\n",v6dhcpinfo.IPv6Prefix);
            strcpy(value, v6dhcpinfo.IPv6Prefix);
        }
        else
            return_status = cm_hal_GetIPv6DHCPInfo(value);
    }
     else if( !(strcmp(paramName, "USLockStatusAndModulation")) )
    {
        long unsigned int  count;
        return_status = docsis_GetNumOfActiveTxChannels(&count);
        printf("Count of Active Tx channels is %d\n",count);
        if (return_status == 0)
        {
            pUsFreq = (PCMMGMT_CM_US_CHANNEL) malloc(sizeof(CMMGMT_CM_US_CHANNEL)*count);
            if(!pUsFreq)
            {
                printf("Memory has not allocated successfully \n ");
            }
            else
            {
                return_status =  docsis_GetUSChannel(&pUsFreq);
                int i;
                strcpy(value, "");
                temp_UsFreq=pUsFreq;
                for(i=0;i<count;i++)
                {
                    printf("ssp_CMHAL_GetParamCharValue: US LockStatus retreived :%s\n",pUsFreq->LockStatus);
                    printf("ssp_CMHAL_GetParamCharValue: US Modulation retreived :%s\n",pUsFreq->Modulation);

                    strcat(value, pUsFreq->LockStatus);
                    strcat(value, ":");
                    strcat(value, pUsFreq->Modulation);
                    strcat(value, ",");
                    temp_UsFreq++;
                }
            }
            free(pUsFreq);
        }
    }
    else if( !(strcmp(paramName, "DSLockStatusAndModulation")) )
    {
        long unsigned int  count;
        return_status = docsis_GetNumOfActiveRxChannels(&count);
        printf("Count of Active Rx channels is %d\n",count);
        if (return_status == 0)
        {
            pDsFreq = (PCMMGMT_CM_DS_CHANNEL) malloc(sizeof(CMMGMT_CM_DS_CHANNEL)*count);
            if(!pDsFreq)
            {
                printf("Memory has not allocated successfully \n ");
            }
            else
            {
                return_status =  docsis_GetDSChannel(&pDsFreq);
                int i;
                strcpy(value, "");
                temp_DsFreq=pDsFreq;
                for(i=0;i<count;i++)
                {
                    printf("ssp_CMHAL_GetParamCharValue: DS LockStatus retreived :%s\n",pDsFreq->LockStatus);
                    printf("ssp_CMHAL_GetParamCharValue: DS Modulation retreived :%s\n",pDsFreq->Modulation);
                    strcat(value, pDsFreq->LockStatus);
                    strcat(value, ":");
                    strcat(value, pDsFreq->Modulation);
                    strcat(value, ",");
                    temp_DsFreq++;
                }
            }
            free(pDsFreq);
        }
    }
     else if( !(strcmp(paramName, "USChannelIDAndType")) )
    {
        long unsigned int  count;
        return_status = docsis_GetNumOfActiveTxChannels(&count);
        printf("Count of Active Tx channels is %d\n",count);
        if (return_status == 0)
        {
            pUsFreq = (PCMMGMT_CM_US_CHANNEL) malloc(sizeof(CMMGMT_CM_US_CHANNEL)*count);
            if(!pUsFreq)
            {
                printf("Memory has not allocated successfully \n ");
            }
            else
            {
                return_status =  docsis_GetUSChannel(&pUsFreq);
                int i;
                strcpy(value, "");
                temp_UsFreq=pUsFreq;
                for(i=0;i<count;i++)
                {
                    printf("ssp_CMHAL_GetParamCharValue: US Channel ID retreived :%d\n",pUsFreq->ChannelID);
                    printf("ssp_CMHAL_GetParamCharValue: US Frequency retreived :%s\n",pUsFreq->ChannelType);
                    char FreqString[64];
                    char Channelid[16];
                    sprintf(Channelid,"%d",pUsFreq->ChannelID);
                    strcpy(FreqString,pUsFreq->ChannelType);
                    strcat(value, Channelid);
                    strcat(value, ":");
                    strcat(value, FreqString);
                    strcat(value, ",");
                    temp_UsFreq++;
                }
            }
            free(pUsFreq);
        }
    }
    else if( !(strcmp(paramName, "DSChannelIDAndPower")) )
    {
        long unsigned int  count;
        return_status = docsis_GetNumOfActiveRxChannels(&count);
        printf("Count of Active Rx channels is %d\n",count);
        if (return_status == 0)
        {
            pDsFreq = (PCMMGMT_CM_DS_CHANNEL) malloc(sizeof(CMMGMT_CM_DS_CHANNEL)*count);
            if(!pDsFreq)
            {
                printf("Memory has not allocated successfully \n ");
            }
            else
            {
                return_status =  docsis_GetDSChannel(&pDsFreq);
                int i;
                strcpy(value, "");
                temp_DsFreq=pDsFreq;
                for(i=0;i<count;i++)
                {
                    printf("ssp_CMHAL_GetParamCharValue: DS Channel ID retreived :%d\n",pDsFreq->ChannelID);
                    printf("ssp_CMHAL_GetParamCharValue: DS Power retreived :%s\n",pDsFreq->PowerLevel);
                    char PowerString[64];
                    char Channelid[16];
                    sprintf(Channelid,"%d",pDsFreq->ChannelID);
                    strcpy(PowerString,pDsFreq->PowerLevel);
                    strcat(value, Channelid);
                    strcat(value, ":");
                    strcat(value, PowerString);
                    strcat(value, ",");
                    temp_DsFreq++;
                }
            }
            free(pDsFreq);
        }
    }
    else if( !(strcmp(paramName, "USChannelIDAndPower")) )
    {
        long unsigned int  count;
        return_status = docsis_GetNumOfActiveTxChannels(&count);
        printf("Count of Active Tx channels is %d\n",count);
        if (return_status == 0)
        {
            pUsFreq = (PCMMGMT_CM_US_CHANNEL) malloc(sizeof(CMMGMT_CM_US_CHANNEL)*count);
            if(!pUsFreq)
            {
                printf("Memory has not allocated successfully \n ");
            }
            else
            {
                return_status =  docsis_GetUSChannel(&pUsFreq);
                int i;
                strcpy(value, "");
                temp_UsFreq=pUsFreq;
                for(i=0;i<count;i++)
                {
                    printf("ssp_CMHAL_GetParamCharValue: US Channel ID retreived :%d\n",pUsFreq->ChannelID);
                    printf("ssp_CMHAL_GetParamCharValue: US Power retreived :%s\n",pUsFreq->PowerLevel);
                    char PowerString[64];
                    char Channelid[16];
                    sprintf(Channelid,"%d",pUsFreq->ChannelID);
                    strcpy(PowerString,pUsFreq->PowerLevel);
                    strcat(value, Channelid);
                    strcat(value, ":");
                    strcat(value, PowerString);
                    strcat(value, ",");
                    temp_UsFreq++;
                }
            }
            free(pUsFreq);
        }
    }
    else if( !(strcmp(paramName, "DOCSISDataRegComplete")) )
    {
        if(value)
        {
            strcpy(value, " ");
            return_status = docsis_GetDOCSISInfo(&docsisinfo);
           printf("ssp_CMHAL_GetParamCharValue: DHCP Status  retreived :%s\n",docsisinfo.DOCSISDataRegComplete);
            strcpy(value, docsisinfo.DOCSISDataRegComplete);
        }
        else
            return_status = docsis_GetDOCSISInfo(value);
    }
    else if( !(strcmp(paramName, "DownstreamRanging")) )
    {
        if(value)
        {
            strcpy(value, " ");
            return_status = docsis_GetDOCSISInfo(&docsisinfo);
           printf("ssp_CMHAL_GetParamCharValue: Downstream Ranging retreived :%s\n",docsisinfo.DOCSISDownstreamRanging);
            strcpy(value, docsisinfo.DOCSISDownstreamRanging);
        }
        else
            return_status = docsis_GetDOCSISInfo(value);
    }

    else
    {
         printf("Invalid parameter name");
	 return_status = SSP_FAILURE;
    }
    return return_status;

}


/*******************************************************************************************
 *
 * Function Name        : ssp_CMHAL_GetParamUlongValue
 * Description          : This function will invoke the hal api of CM to get the ulong values
 *
 * @param [in]          :  paramName: specifies the name of the API
                           value: returns the value of the parameter
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/

int ssp_CMHAL_GetParamUlongValue(char* paramName, unsigned long* value)
{
    int return_status = 0;
    CMMGMT_CM_DHCP_INFO v4dhcpinfo;
    printf("\nEntering ssp_CMHAL_GetParamUlongValue function\n\n");
    if( !(strcmp(paramName, "DownFreq")) )
    {
        *value = docsis_GetDownFreq();
        printf("ssp_CMHAL_GetParamUlongValue:DownFreq is %d", *value);

        if ( *value == 0)
        {
            printf("ssp_CMHAL_GetParamUlongValue : Failed to get the Down Frequency\n");
            return_status =SSP_FAILURE;
        }
    }
    else if( !(strcmp(paramName, "NumberofActiveRxChannels")) )
    {
        return_status = docsis_GetNumOfActiveRxChannels(value);
        printf("Return status of docsis_GetNumOfActiveRxChannels %d", return_status);
        if ( return_status != SSP_SUCCESS)
        {
            printf("ssp_CMHAL_GetParamCharValue : Failed to get NumberofActiveRxChannels\n");
            return_status =SSP_FAILURE;
        }
    }
    else if( !(strcmp(paramName, "NumberofActiveTxChannels")) )
    {
        return_status = docsis_GetNumOfActiveTxChannels(value);
        printf("Return status of docsis_GetNumOfActiveTxChannels %d", return_status);
        if ( return_status != SSP_SUCCESS)
        {
            printf("ssp_CMHAL_GetCharValue : Failed to get NumberofActiveRxChannels\n");
            return_status =SSP_FAILURE;
        }
    }
    else if( !(strcmp(paramName, "Ipv4DhcpIPAddress")) )
    {
        if(value)
        {
            return_status = cm_hal_GetDHCPInfo(&v4dhcpinfo);
	     printf("ssp_CMHal_GetParamUlongValue: IPAddress retreived :%lu\n",v4dhcpinfo.IPAddress);
            *value = v4dhcpinfo.IPAddress.Value;
        }
        else
            return_status = cm_hal_GetDHCPInfo(value);
    }
    else
    {
        printf("Invalid parameter name");
        return_status =SSP_FAILURE;
    }
    return return_status;

}



