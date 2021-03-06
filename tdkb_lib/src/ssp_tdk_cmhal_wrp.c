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
       long unsigned int  count = 0;
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

               int i = 0;
	       strcpy(value, "");
               for(i=0;i<count;i++)
               {
                   printf("ssp_CMHAL_GetParamCharValue: DS Frequency retreived :%s\n",pDsFreq[i].Frequency);
                   char FreqString[64] = {0};

                   strcpy(FreqString,pDsFreq[i].Frequency);
                   strcat(value, FreqString);
                   strcat(value, ",");
               }
           }

           if(pDsFreq != NULL)
           {
               free(pDsFreq);
           }
       }
    }
    else if( !(strcmp(paramName, "US_Frequency")) )
    {
        long unsigned int  count = 0;
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

                int i = 0;
                strcpy(value,"");
                for(i=0;i<count;i++)
                {
                    printf("ssp_CMHAL_GetParamCharValue: US Frequency retreived :%s\n",pUsFreq[i].Frequency);
                    char FreqString[64] = {0};
                    strcpy(FreqString,pUsFreq[i].Frequency);
                    strcat(value, FreqString);
                    strcat(value, ",");
                }
            }
            if(pUsFreq != NULL)
            {
                 free(pUsFreq);
            }
        }
    }
    else if( !(strcmp(paramName, "ModulationAndSNRLevel")) )
    {
        long unsigned int  count = 0;
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

                int i = 0;
                strcpy(value, "");
                for(i=0;i<count;i++)
                {
                    printf("ssp_CMHAL_GetParamCharValue: DS Modulation retreived :%s\n",pDsFreq[i].Modulation);
                    printf("ssp_CMHAL_GetParamCharValue: DS SNR Level retreived :%s\n",pDsFreq[i].SNRLevel);
                    char SNRString[64] = {0};
                    strcpy(SNRString,pDsFreq[i].SNRLevel);
                    strcat(value, pDsFreq[i].Modulation);
                    strcat(value, ":");
                    strcat(value, SNRString);
                    strcat(value, ",");
                }
            }
            if(pDsFreq != NULL)
            {
                 free(pDsFreq);
            }
        }
    }
    else if( !(strcmp(paramName, "LockStatusAndChannelID")) )
    {
        long unsigned int  count = 0;
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

                int i = 0;
                strcpy(value, "");
                for(i=0;i<count;i++)
                {
                    printf("ssp_CMHAL_GetParamCharValue: DS LockStatus retreived :%s\n",pDsFreq[i].LockStatus);
                    printf("ssp_CMHAL_GetParamCharValue: DS ChannelID retreived :%d\n",pDsFreq[i].ChannelID);
                    char Channelid[16] = {0};
                    sprintf(Channelid,"%d",pDsFreq[i].ChannelID);
                    strcat(value, pDsFreq[i].LockStatus);
		    strcat(value, ":");
                    strcat(value, Channelid);
                    strcat(value, ",");
                }
            }
            if(pDsFreq != NULL)
            {
                 free(pDsFreq);
            }
        }
    }
    else if( !(strcmp(paramName, "ModulationAndUSPower")) )
    {
        long unsigned int  count = 0;
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
                int i = 0;
                strcpy(value, "");
                temp_UsPower=pUsPower;
                for(i=0;i<count;i++)
                {
                    printf("ssp_CMHAL_GetParamCharValue: US Modulation retreived :%s\n",pUsPower->Modulation);
                    printf("ssp_CMHAL_GetParamCharValue: US Power Level retreived :%s\n",pUsPower->PowerLevel);
                    char PowerString[64] = {0};
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
    else if( !(strcmp(paramName, "Cert")) )
    {
        return_status = docsis_GetCert(value);
        printf("Return status of docsis_GetCert %d", return_status);
        if ( return_status != SSP_SUCCESS)
        {
            printf("ssp_CMHAL_GetCharParamValues : Failed to get Cert info\n");
            return SSP_FAILURE;
        }
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
    CMMGMT_CM_EventLogEntry_t entryArray[50];
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
    else if( !(strcmp(paramName, "CertStatus")) )
    {
        return_status = docsis_GetCertStatus(value);
        printf("Return status of docsis_GetCertStatus %d", return_status);
        if ( return_status != SSP_SUCCESS)
        {
            printf("ssp_CMHAL_GetParamUlongValue : Failed to get CertStatus\n");
            return_status =SSP_FAILURE;
        }
    }
    else if( !(strcmp(paramName, "USChannelId")) )
    {
	*value = -1;
        *value = docsis_GetUSChannelId();
        printf("ssp_CMHAL_GetParamUlongValue:US Channel id is %d", *value);

        if ( *value == -1)
        {
            printf("ssp_CMHAL_GetParamUlongValue : Failed to get the US Channel ID\n");
            return_status =SSP_FAILURE;
        }
    }
    else if( !(strcmp(paramName, "DownloadInterface")) )
    {
        return_status = cm_hal_Get_HTTP_Download_Interface(value);
        printf("Return status of cm_hal_Get_HTTP_Download_Interface %d", return_status);
        if ( return_status != SSP_SUCCESS)
        {
            printf("ssp_CMHAL_GetParamCharValue : Failed to get cm_hal_Get_HTTP_Download_Interface\n");
            return_status =SSP_FAILURE;
        }
    }
    else if( !(strcmp(paramName, "EventLogItemsCount")) )
    {
       memset(entryArray, 0, 50*sizeof(CMMGMT_CM_EventLogEntry_t));
       *value = docsis_GetDocsisEventLogItems(entryArray,50);
       if(value)
       {
           printf("ssp_CMHal_GetParamUlongValue: Number of Docsis Event log items:%d\n",value);
           return_status = SSP_SUCCESS;
       }
       else
       {
           return_status =SSP_FAILURE;
       }
    }
    else if( !(strcmp(paramName, "CableModemResetCount")) )
    {
        return_status = cm_hal_Get_CableModemResetCount(value);
        printf("Return status of cm_hal_Get_CableModemResetCount %d", return_status);
        if ( return_status != SSP_SUCCESS)
        {
            printf("ssp_CMHAL_GetParamUlongValue: Failed to get CableModemResetCount\n");
            return_status =SSP_FAILURE;
        }
    }
    else if( !(strcmp(paramName, "LocalResetCount")) )
    {
        return_status = cm_hal_Get_LocalResetCount(value);
        printf("Return status of cm_hal_Get_LocalResetCount %d", return_status);
        if ( return_status != SSP_SUCCESS)
        {
            printf("ssp_CMHAL_GetParamUlongValue: Failed to get LocalResetCount\n");
            return_status =SSP_FAILURE;
        }
    }
    else if( !(strcmp(paramName, "DocsisResetCount")) )
    {
        return_status = cm_hal_Get_DocsisResetCount(value);
        printf("Return status of cm_hal_Get_DocsisResetCount %d", return_status);
        if ( return_status != SSP_SUCCESS)
        {
            printf("ssp_CMHAL_GetParamUlongValue: Failed to get DocsisResetCount\n");
            return_status =SSP_FAILURE;
        }
    }
    else if( !(strcmp(paramName, "ErouterResetCount")) )
    {
        return_status = cm_hal_Get_ErouterResetCount(value);
        printf("Return status of cm_hal_Get_ErouterResetCount %d", return_status);
        if ( return_status != SSP_SUCCESS)
        {
            printf("ssp_CMHAL_GetParamUlongValue: Failed to get ErouterResetCount\n");
            return_status =SSP_FAILURE;
        }
    }
    else if( !(strcmp(paramName, "Reboot_Ready")) )
    {
        return_status = cm_hal_Reboot_Ready(value);
        printf("Return status of cm_hal_Reboot_Ready %d", return_status);
        if ( return_status != SSP_SUCCESS)
        {
            printf("ssp_CMHAL_GetParamUlongValue: Failed to get cm_hal_Reboot_Ready");
            return_status =SSP_FAILURE;
        }
    }
    else if(!(strcmp(paramName, "HTTP_Download_Status")))
    {
       *value = cm_hal_Get_HTTP_Download_Status();
        printf("ssp_CMHAL_GetParamUlongValue:Download status is %d", *value);
    }
    else
    {
        printf("Invalid parameter name");
        return_status =SSP_FAILURE;
    }
    return return_status;

}

/*******************************************************************************************
 *
 * Function Name        : ssp_CMHAL_GetErrorCodeWords
 * Description          : This function will invoke the hal api of CM to get the error code words
 *
 * @param [in]          :  isNegativeScenario : for executing negative scenario
                           value: returns the value of the parameter
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/

int ssp_CMHAL_GetErrorCodeWords(char *value, int isNegativeScenario)
{
    int return_status = 0;
    int i=0;
    PCMMGMT_CM_ERROR_CODEWORDS perrorcodes = NULL;
    long unsigned int  count = 0;
    printf("\nEntering ssp_CMHAL_GetErrorCodeWords function\n\n");

    if(isNegativeScenario)
    {
        printf("Executing negative scenario\n");
        return_status = docsis_GetErrorCodewords(NULL);
    }
    else
    {
        printf("Executing positive scenario\n");

        return_status = docsis_GetNumOfActiveRxChannels(&count);
        printf("Count of Active Rx channels is %d\n",count);
        if (return_status == 0)
        {
            perrorcodes = (PCMMGMT_CM_ERROR_CODEWORDS) malloc(sizeof(CMMGMT_CM_ERROR_CODEWORDS)*count);

            if(!perrorcodes)
            {
                printf("Memory has not allocated successfully \n ");
		return_status = SSP_FAILURE;
            }
            else
            {
                return_status = docsis_GetErrorCodewords(&perrorcodes);
                printf("Return status of docsis_GetErrorCodewords: %d\n",return_status);
                strcpy(value,"");
                for (i=0;i<count;i++)
                {
                    printf("UnerroredCodewords :%lu, CorrectableCodewords :%lu, UncorrectableCodewords :%lu\n",perrorcodes[i].UnerroredCodewords,perrorcodes[i].CorrectableCodewords,perrorcodes[i].UncorrectableCodewords);
                    char str[64]= {0};
                    sprintf(str,"%d,%d,%d",perrorcodes[i].UnerroredCodewords,perrorcodes[i].CorrectableCodewords,perrorcodes[i].UncorrectableCodewords);
                    strcat(value,str);
                    strcat(value," ");
                }
            }
        }
    }
    if(perrorcodes != NULL)
    {
       free(perrorcodes);
    }

    return return_status;
}
/*******************************************************************************************
 *
 * Function Name        : ssp_CMHAL_Init
 * Description          : This function will invoke the hal api of CM to init the CM
 *
 * @param [in]          :  paramName: specifies the name of the API

 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/
int ssp_CMHAL_Init(char* paramName)
{
    int return_status = 0;
    printf("\nEntering ssp_CMHAL_Init function\n\n");

    if( !(strcmp(paramName, "InitDB")) )
    {
        return_status = cm_hal_InitDB();
        printf("Return status of cm_hal_InitDB %d", return_status);
    }
    else if( !(strcmp(paramName, "InitDS")) )
    {
        return_status = docsis_InitDS();
        printf("Return status of docsis_InitDS %d", return_status);
    }
    else if( !(strcmp(paramName, "InitUS")) )
    {
        return_status = docsis_InitUS();
        printf("Return status of docsis_InitUS %d", return_status);
    }
    else if( !(strcmp(paramName, "ReinitMac")) )
    {
        return_status = cm_hal_ReinitMac();
        printf("Return status of cm_hal_ReinitMac %d", return_status);
    }
    else
    {
         printf("Invalid parameter name");
         return_status = SSP_FAILURE;
    }
    return return_status;
}

/*****************************************************************************************************************
 * Function Name : ssp_CMHAL_GetDocsisEventLogItems
 * Description   : This function will Retrieve the DocsisEventLogItems
 * @param [in]   : entryArray - to get  the event log items
 *		    len- length of array
 *		   isNegativeScenario - to execute the negative scenarios
 * @param [out]  : return status an integer value 0-success and 1-Failure
 ******************************************************************************************************************/
int ssp_CMHAL_GetDocsisEventLogItems(CMMGMT_CM_EventLogEntry_t *entryArray,int len,int isNegativeScenario)
{
       int result = RETURN_ERR;
       int count =0;
       int i =0;

       printf("Entering the ssp_CMHAL_GetDocsisEventLogItems wrapper\n");

       if(isNegativeScenario)
       {
           result = docsis_GetDocsisEventLogItems(NULL, NULL);
       }
       else
       {
          memset(entryArray, 0, len*sizeof(CMMGMT_CM_EventLogEntry_t));
          count = docsis_GetDocsisEventLogItems(entryArray,len);
          printf("Count is %d\n",count);
              for (i=0;i<count;i++)
              {
		 printf("Time: %s,EventID: %lu,EventLevel : %lu, Description:%s",ctime(&(entryArray[i].docsDevEvFirstTime.tv_sec)), entryArray[i].docsDevEvId, entryArray[i].docsDevEvLevel, entryArray[i].docsDevEvText);
                 result = RETURN_OK;
              }
        }

        if(result == RETURN_OK)
        {
           printf("ssp_CMHAL_GetDocsisEventLogItems function returns success\n");
        }
        return result;
}


/*******************************************************************************************
 *
 * Function Name        : ssp_CMHAL_SetLEDFlashStatus
 * Description          : This function will invoke the hal api of cm_hal_HTTP_LED_Flash() to enable/disable LED Flash
 *
 * @param [in]          :  LedFlash: specifies enable/disable status
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/
int ssp_CMHAL_SetLEDFlashStatus(BOOLEAN LedFlash)
{
    int return_status = 0;
    printf("\nEntering ssp_CMHAL_SetLEDFlashStatus function\n\n");

    return_status = cm_hal_HTTP_LED_Flash(LedFlash);
    if(return_status != SSP_SUCCESS)
    {
     printf("\nssp_CMHAL_SetLEDFlashStatus::Failed\n");
     return SSP_FAILURE;
    }
    else
    {
     printf("\n ssp_CMHAL_SetLEDFlashStatus::Success\n");
     return SSP_SUCCESS;
    }
}

/*****************************************************************************************************************
 * Function Name : ssp_CMHAL_ClearDocsisEventLog
 * Description   : This function will clear the docsis event log
 * @param [in]   : None
 * @param [out]  : return status an integer value 0-success and 1-Failure
 ******************************************************************************************************************/
int ssp_CMHAL_ClearDocsisEventLog(void)
{
       int result = RETURN_ERR;
       printf("Entering the ssp_CMHAL_ClearDocsisEventLog wrapper\n");
       result = docsis_ClearDocsisEventLog();
       printf("result is %d\n",result);
       if(result == RETURN_OK)
       {
          printf("ssp_CMHAL_ClearDocsisEventLog function returns success\n");
       }
       else
       {
          printf("ssp_CMHAL_ClearDocsisEventLog function returns failure\n");
       }

       return result;
}

/********************************************************************************************************************************
 *
 * Function Name        : ssp_CMHAL_GetCPEList
 * Description          : This function will invoke the hal api of cm_hal_GetCPEList to get the list of CPEs connected to the CM
 *
 * @param [in]          : InstanceNum : To save the instance number
 *			  cpeList : To save the cpeList
 *			  isNegativeScenario : To execute the negative scenario
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************************************************/
int ssp_CMHAL_GetCPEList(unsigned long int *InstanceNum, char *cpeList,int isNegativeScenario)
{
       int result = RETURN_ERR;
       int return_status = RETURN_ERR;
       PCMMGMT_DML_CPE_LIST pInfo = NULL;
       char LanMode[60] = {'\0'};
       int i =0;
       printf("Entering the ssp_CMHAL_GetCPEList wrapper\n");
       if(isNegativeScenario)
       {
           result = cm_hal_GetCPEList(NULL, NULL, NULL);
       }
       else
       {
          printf("Executing positive scenarios\n");
          result = cm_hal_GetCPEList(&pInfo,InstanceNum,&LanMode);
          printf("Result is %d, InstanceNum is :%d, LanMode is :%s\n",result,*InstanceNum,LanMode);
          if (result == RETURN_OK)
          {
              printf("cm_hal_GetCPEList returns success\n");
              if(*InstanceNum > 0)
              {
                printf("inst num is greater than zero\n");
                strcpy(cpeList,"");
                for (i=0;i<*InstanceNum;i++)
                  {
                     printf("IPaddress: %s, MACAddress: %s \n",pInfo[i].IPAddress,pInfo[i].MACAddress);
                     strcat(cpeList,pInfo[i].IPAddress);
                     strcat(cpeList,",");
                     strcat(cpeList,pInfo[i].MACAddress);
                     strcat(cpeList,"::");
                     printf("cpeList:%s\n",cpeList);
                     return_status = RETURN_OK;
                  }
              }
              else{ printf("Instance number is not greater than zero\n");}
           }
           else{ printf("cm_hal_GetCPEList returns failure\n");}
        }
        if(return_status == RETURN_OK)
        {
           printf("ssp_CMHAL_GetDocsisEventLogItems function returns success\n");
        }
        return return_status;
}

/*******************************************************************************************
 *
 * Function Name        : ssp_CMHAL_SetMddIpModeOverride
 * Description          : This function will invoke the hal api of docsis_SetMddIpModeOverride to set MddIPModeOverride
 *
 * @param [in]          :  Value : The value of MddIpModeOverride to set
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/
int ssp_CMHAL_SetMddIpModeOverride(char* Value)
{
    int return_status = 0;
    printf("\nEntering ssp_CMHAL_SetMddIpModeOverride function\n");
    return_status = docsis_SetMddIpModeOverride(Value);
    if(return_status != SSP_SUCCESS)
    {
     printf("\nssp_CMHAL_SetMddIpModeOverride::Failed\n");
     return SSP_FAILURE;
    }
    else
    {
     printf("\n ssp_CMHAL_SetMddIpModeOverride::Success\n");
     return SSP_SUCCESS;
    }
}

/*******************************************************************************************
 *
 * Function Name        : ssp_CMHAL_SetStartFreq
 * Description          : This function will invoke the cosa api of CM to set
 *                        start frequency
 *
 * @param [in]          : Value - The value to set
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/
 int ssp_CMHAL_SetStartFreq(unsigned long int Value)
{
    //Since the api is a void function, validation of this function is done inside the python scripts
    printf("\n Entering ssp_CMHAL_SetStartFreq function\n");
    docsis_SetStartFreq(Value);
    return SSP_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name        : ssp_CMHAL_SetUSChannelId
 * Description          : This function will invoke the cosa api of CM to set
 *                        USChannelId
 *
 * @param [in]          : Value - The value to set
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/
 int ssp_CMHAL_SetUSChannelId(int Value)
{
    unsigned long int usChannelId =0;
    printf(" Entering ssp_CMHAL_SetUSChannelId function\n");
    //Since the api is a void function, validation of this function is done inside the python scripts
    docsis_SetUSChannelId(Value);
    return SSP_SUCCESS;
}

/*******************************************************************************************
 *
 * Function Name        : ssp_CMHAL_SetHTTP_Download_Interface
 * Description          : This function will invoke the hal api of cm_hal_Set_HTTP_Download_Interface()
 *
 * @param [in]          : interface - The value of download interface to set
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/
int ssp_CMHAL_SetHTTP_Download_Interface(unsigned int interface)
{
    int return_status = 0;
    printf("\nEntering ssp_CMHAL_SetHTTP_Download_Interface function\n\n");

    return_status = cm_hal_Set_HTTP_Download_Interface(interface);
    printf("\n return_status of cm_hal_Set_HTTP_Download_Interface: %d",return_status);

    if(return_status != SSP_SUCCESS)
    {
     printf("\nssp_CMHAL_SetHTTP_Download_Interface::Failed\n");
     return SSP_FAILURE;
    }
    else
    {
     printf("\n ssp_CMHAL_SetHTTP_Download_Interface::Success\n");
     return SSP_SUCCESS;
    }
}

/*******************************************************************************************
 *
 * Function Name        : ssp_CMHAL_Download
 * Description          : This function will invoke the hal api of cm_hal_HTTP_Download() to start the download
 *
 * @param [in]          : None
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/
int ssp_CMHAL_Download()
{
    int return_status = 0;
    printf("\nEntering ssp_CMHAL_Download function\n\n");

    return_status = cm_hal_HTTP_Download();
    printf("return_status of cm_hal_HTTP_Download is %d",return_status);
    if(return_status != SSP_SUCCESS)
    {
     printf("\nssp_CMHAL_Download::Failed\n");
     return SSP_FAILURE;
    }
    else
    {
     printf("\n ssp_CMHAL_Download::Success\n");
     return SSP_SUCCESS;
    }
}
/*******************************************************************************************
 *
 * Function Name        : ssp_CMHAL_GetHTTP_Download_Url
 * Description          : This function will invoke the hal api of CM to get the HTTP_Download_Url
 *
 * @param [in]          : httpURL : The URL of site from which the file should download
                          filename: The name of the file which is to be download
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/
int ssp_CMHAL_GetHTTP_Download_Url(char* httpURL, char* filename)
{
    int return_status = 0;
    printf("\nEntering ssp_CMHAL_GetHTTP_Download_Url function\n\n");
    return_status = cm_hal_Get_HTTP_Download_Url(httpURL,filename);
    printf("Return status of cm_hal_Get_HTTP_Download_Url %d", return_status);
    if ( return_status != SSP_SUCCESS)
    {
        printf("ssp_CMHAL_GetHTTP_Download_Url :Failed to get the HTTP_Download_Url\n");
        return SSP_FAILURE;
    }
    return return_status;
}
/*******************************************************************************************
 *
 * Function Name        : ssp_CMHAL_SetHTTP_Download_Url
 * Description          : This function will invoke the hal api of cm_hal_Set_HTTP_Download_Url
 *
 * @param [in]          :  Value : The value of HTTP_Download_Url to set
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/
int ssp_CMHAL_SetHTTP_Download_Url(char* httpURL, char* filename)
{
    int return_status = 0;
    printf("\nEntering ssp_CMHAL_SetHTTP_Download_Url function\n");

    return_status = cm_hal_Set_HTTP_Download_Url(httpURL,filename);
    if(return_status != SSP_SUCCESS)
    {
     printf("\nssp_CMHAL_SetHTTP_Download_Url::Failed\n");
     return SSP_FAILURE;
    }
    else
    {
     printf("\n ssp_CMHAL_SetHTTP_Download_Url::Success\n");
     return SSP_SUCCESS;
    }
}
/*******************************************************************************************
 *
 * Function Name        : ssp_CMHAL_FWupdateAndFactoryReset
 * Description          : This function will invoke the hal api of cm_hal_FWupdateAndFactoryReset()
 *
 * @param [in]          : None
 * @param [out]         : return status an integer value 0-success and 1-Failure
 ********************************************************************************************/
int ssp_CMHAL_FWupdateAndFactoryReset()
{
    int return_status = 0;
    printf("\nEntering ssp_CMHAL_FWupdateAndFactoryReset function\n\n");

    return_status = cm_hal_FWupdateAndFactoryReset();
    printf("return_status of cm_hal_FWupdateAndFactoryReset is %d",return_status);
    if(return_status != SSP_SUCCESS)
    {
     printf("\n ssp_CMHAL_FWupdateAndFactoryReset::Failed\n");
     return SSP_FAILURE;
    }
    else
    {
     printf("\n ssp_CMHAL_FWupdateAndFactoryReset::Success\n");
     return SSP_SUCCESS;
    }
}
