#
# ============================================================================
# COMCAST CONFIDENTIAL AND PROPRIETARY
# ============================================================================
# This file and its contents are the intellectual property of Comcast.  It may
# not be used, copied, distributed or otherwise  disclosed in whole or in part
# without the express written permission of Comcast.
# ============================================================================
# Copyright (c) 2016 Comcast. All rights reserved.
# ============================================================================
#

package require Expect;
#Procedure initialize values from Config.txt
proc Initializer {configFile} {   
puts "$configFile";
	set handle [open "$configFile" r];

	if { $handle == ""} {

		puts "No Data in Config file\n";
		exit 0;

   	}
	puts "Reading from Config file\n";

	while {[gets $handle entry] > -1} {

		scan $entry "%s %s" Vname Vvalue;

		if { ![string compare $Vname "telnetIP"] } {
			global Telnetip "";
			set Telnetip $Vvalue;

	   	}


		if { ![string compare $Vname "UserName"] } {
			global Name "";
			set Name $Vvalue;

   		}

		if { ![string compare $Vname "Password"] } {
			global password "";
			set password $Vvalue;

   		}

		 if { ![string compare $Vname "OsName1"] } {
                        global osName1 "";
                        set osName1 $Vvalue;

                }
 
		if { ![string compare $Vname "telnetIP2"] } {
                        global Telnetip2 "";
                        set Telnetip2 $Vvalue;

                }


                if { ![string compare $Vname "UserName2"] } {
                        global Name2 "";
                        set Name2 $Vvalue;

                }

                if { ![string compare $Vname "Password2"] } {
                        global password2 "";
                        set password2 $Vvalue;

                }

		if { ![string compare $Vname "OsName2"] } {
                        global osName2 "";
                        set osName2 $Vvalue;

                }

		

		if { ![string compare $Vname "Interfaceport"] } {
			global port "";
			set port $Vvalue;

   		}

		if { ![string compare $Vname "cmIP"] } {
			global CMip "";
			set CMip $Vvalue;

   		}

                if { ![string compare $Vname "cmPassword"] } {
                        global CMpassword "";
                        set CMpassword $Vvalue;
                }


		if { ![string compare $Vname "DHCPleaseTime"] } {
			global dhcpLeaseTime "";
			set dhcpLeaseTime $Vvalue;

 		}

		if { ![string compare $Vname "LeaseMiB"] } {
			global  leaseMiB "";
			set leaseMComcast.2014iB $Vvalue;

   		}

		if { ![string compare $Vname "DHCPstartRange"] } {
			global dhcpStartRange "";
			set dhcpStartRange $Vvalue;

   		}
		if { ![string compare $Vname "StartRangeMiB"] } {
			global startRangeMiB "";
			set startRangeMiB $Vvalue;

   		}


		if { ![string compare $Vname "DHCPendRange"] } {
			global dhcpEndRange "";
			set dhcpEndRange $Vvalue;

   		}

		if { ![string compare $Vname "EndRangeMiB"] } {
			global endRangeMiB "";
			set endRangeMiB $Vvalue;

   		}

		if { ![string compare $Vname "BlockURL"] } {
			global blockURL "";
			set blockURL $Vvalue;

   		}

		if { ![string compare $Vname "BlockURLMiB"] } {
			global blockURLMiB "";
			set blockURLMiB $Vvalue;

   		}

		if { ![string compare $Vname "classPath"] } {

			global ClassPath "";
			set ClassPath $Vvalue;

			
   		}
		
		if { ![string compare $Vname "class"] } {
			
			global Class "";
			set Class $Vvalue;

			
   		}
		

		if { ![string compare $Vname "OUI"] } {
			global oui "";
			set oui $Vvalue;

   		}
		
		if { ![string compare $Vname "SerialNo"] } {
			global SNno "";
			set SNno $Vvalue;

   		}
		

		if { ![string compare $Vname "DeviceType"] } {
			global deviceType "";
			set deviceType $Vvalue;

   		}
		
		if { ![string compare $Vname "RPCtype"] } {
			global rpcType "";
			set rpcType $Vvalue;

   		}

		if { ![string compare $Vname "RPC"] } {
			global rpc "";
			set rpc $Vvalue;

   		}

		if { ![string compare $Vname "ValueType"] } {
			global Valtype "";
			set Valtype $Vvalue;

   		}

		if { ![string compare $Vname "Value"] } {
			global Val "";
			set Val $Vvalue;

   		}
		
		if { ![string compare $Vname "SSID"] } {
			global ssid "";
			set ssid $Vvalue;

   		}

		if { ![string compare $Vname "WlanIP"] } {
			global wlanIP "";
			set wlanIP $Vvalue;

   		}

		if { ![string compare $Vname "WlanName"] } {
			global wlanName "";
			set wlanName $Vvalue;

   		}

		if { ![string compare $Vname "WlanPassword"] } {
			global wlanPassword "";
			set wlanPassword $Vvalue;

   		}

		if { ![string compare $Vname "WlanInterfaceName"] } {
                        global wlanInterfaceName "";
                        set wlanInterfaceName $Vvalue;

                }


                if { ![string compare $Vname "WlanAdminName"] } {
                        global wlanAdminName "";
                        set wlanAdminName $Vvalue;

                }

                if { ![string compare $Vname "WlanAdminPassword"] } {
                        global wlanAdminPassword "";
                        set wlanAdminPassword $Vvalue;

                }

		
		if { ![string compare $Vname "WlanIP2"] } {
			global wlanIP2 "";
			set wlanIP2 $Vvalue;

   		}

		if { ![string compare $Vname "WlanName2"] } {
			global wlanName2 "";
			set wlanName2 $Vvalue;

   		}

		if { ![string compare $Vname "WlanPassword2"] } {
			global wlanPassword2 "";
			set wlanPassword2 $Vvalue;

   		}

                if { ![string compare $Vname "WlanInterfaceName2"] } {
                        global wlanInterfaceName2 "";
                        set wlanInterfaceName2 $Vvalue;

                }

		if { ![string compare $Vname "WanIP"] } {
			global wanIP "";
			set wanIP $Vvalue;

   		}

		if { ![string compare $Vname "WanName"] } {
			global wanName "";
			set wanName $Vvalue;

   		}

		if { ![string compare $Vname "WanPassword"] } {
			global wanPassword "";
			set wanPassword $Vvalue;

   		} 
		
		if { ![string compare $Vname "WanIPWG"] } {
			global wanIPWG "";
			set wanIPWG $Vvalue;

   		} 
		
		if { ![string compare $Vname "WanIPv6WG"] } {
                        global wanIPv6WG "";
                        set wanIPv6WG $Vvalue;

                }

		
		if { ![string compare $Vname "FtpIP"] } {
			global ftpIP "";
			set ftpIP $Vvalue;

   		}

		if { ![string compare $Vname "FtpName"] } {
			global ftpName "";
			set ftpName $Vvalue;

   		}

		if { ![string compare $Vname "FtpPassword"] } {
			global ftpPassword "";
			set ftpPassword $Vvalue;

   		}

                 if { ![string compare $Vname "FtpAudiofile"] } {
                        global FtpAudiofile "";
                        set FtpAudiofile $Vvalue;

                }
 
                if { ![string compare $Vname "FtpVideofile"] } {
                        global FtpVideofile "";
                        set FtpVideofile $Vvalue;

                }

		if { ![string compare $Vname "WanFtpIP"] } {
			global wanFtpIP "";
			set wanFtpIP $Vvalue;

   		}

		if { ![string compare $Vname "WanFtpName"] } {
			global wanFtpName "";
			set wanFtpName $Vvalue;

   		}

		if { ![string compare $Vname "WanFtpPassword"] } {
			global wanFtpPassword "";
			set wanFtpPassword $Vvalue;

   		} 
		
		
		
		if { ![string compare $Vname "TestWanIPv4"] } {
			global wanIpInWeb "";
			set wanIpInWeb $Vvalue;

   		} 

		
		if { ![string compare $Vname "ProfilePath"] } {
			global profilePath "";
			set profilePath $Vvalue;

   		}	
                  

                 if { ![string compare $Vname "ProfilePath1"] } {
                        global profilePath1 "";
                        set profilePath1 $Vvalue;

                }
	
		
		if { ![string compare $Vname "Interface"] } {
			global no "";
			set no $Vvalue;

   		}

		if { ![string compare $Vname "SiteKeyword"] } {
                        global siteKeyword "";
                        set siteKeyword $Vvalue;

                }

		if { ![string compare $Vname "SiteUrl"] } {
                        global siteUrl "";
                        set siteUrl $Vvalue;

                }
		if { ![string compare $Vname "SiteHttps"] } {
                        global siteHttps "";
                        set siteHttps $Vvalue;

                }
		if { ![string compare $Vname "SiteKeywordIPv6"] } {
                        global siteKeywordIPv6 "";
                        set siteKeywordIPv6 $Vvalue;

                }
		
		if { ![string compare $Vname "SiteUrlIPv6"] } {
                        global siteUrlIPv6 "";
                        set siteUrlIPv6 $Vvalue;

                }
                
		if { ![string compare $Vname "SiteHttpsIPv6"] } {
                        global siteHttpsIPv6 "";
                        set siteHttpsIPv6 $Vvalue;

                }

		if { ![string compare $Vname "FtpIPv6"] } {
                        global ftpIPv6 "";
                        set ftpIPv6 $Vvalue;

                }

		if { ![string compare $Vname "IntNo"] } {
                        global intNo "";
                        set intNo $Vvalue;

                }
		 
		if { ![string compare $Vname "LeaseCommand"] } {
                        global leaseCommand "";
                        set leaseCommand $Vvalue;

                }

		if { ![string compare $Vname "EthInterface"] } {
                        global ethInterface "";
                        set ethInterface $Vvalue;

                }



		if { ![string compare $Vname "Interface2"] } {
                        global no2 "";
                        set no2 $Vvalue;

                }

		
		if { ![string compare $Vname "MAClist"] } {
			global macList "";
			set macList $Vvalue;

   		}
			
     		if { ![string compare $Vname "SSID2"] } {
			global ssid2 "";
			set ssid2 $Vvalue;

   		}
		
		
		if { ![string compare $Vname "SSID5"] } {
			global ssid5 "";
			set ssid5 $Vvalue;

   		}
                if { ![string compare $Vname "RadioIndex2"] } {
                        global ri2 "";
                        set ri2 $Vvalue;

                }
                if { ![string compare $Vname "SSIDIndex2"] } {
                        global si2 "";
                        set si2 $Vvalue;

                }
                if { ![string compare $Vname "RadioIndex5"] } {
                        global ri5 "";
                        set ri5 $Vvalue;

                }
                if { ![string compare $Vname "SSIDIndex5"] } {
                        global si5 "";
                        set si5 $Vvalue;

                }
                if { ![string compare $Vname "AutomationServerIP"] } {
                        global AutomationServerIP "";
                        set AutomationServerIP $Vvalue;

                }

               if { ![string compare $Vname "AutomationServerName"] } {
                        global AutomationServerName "";
                        set AutomationServerName $Vvalue;

                }
               if { ![string compare $Vname "AutomationServerPassword"] } {
                        global AutomationServerPassword "";
                        set AutomationServerPassword $Vvalue;

                }
		if { ![string compare $Vname "DeleteLogPath"] } {
                        global deleteLogPath "";
                        set deleteLogPath $Vvalue;

                }
		if { ![string compare $Vname "DeleteBackupLogPath"] } {
                        global deleteBackupLogPath "";
                        set deleteBackupLogPath $Vvalue;

                }
		if { ![string compare $Vname "LogfilePath"] } {
                        global logFilePath "";
                        set logFilePath $Vvalue;
                }
		if { ![string compare $Vname "BackupLogfilePath"] } {
                        global backupLogfilePath "";
                        set backupLogfilePath $Vvalue;
                }
		if { ![string compare $Vname "WifiLogFilename"] } {
                        global wifiLogFilename "";
                        set wifiLogFilename $Vvalue;
                }
		if { ![string compare $Vname "WebpaLogFilename"] } {
                        global webpaLogFilename "";
                        set webpaLogFilename $Vvalue;
                }


		if { ![string compare $Vname "exejar"] } {
                        global EXEJAR "";
                        set EXEJAR $Vvalue;
		
                }
               if { ![string compare $Vname "DefaultSSID2"] } {
                        global defaultssid2 "";
                        set defaultssid2 $Vvalue;

                }


                if { ![string compare $Vname "DefaultSSID5"] } {
                        global defaultssid5 "";
                        set defaultssid5 $Vvalue;

                }
                
	 	if { ![string compare $Vname "WlanMAC"] } {
                        global wlanMAC "";
                        set wlanMAC $Vvalue;

                }

		if { ![string compare $Vname "serverPort"] } {
                        global serverPort "";
                        set serverPort $Vvalue;

                }

	 }
close $handle;
}

#Procedure to display a formated information about the ongoing process
proc displayProc {dispContent} {

	puts "\r######################################################################"
	puts "#$dispContent"
	puts "######################################################################\n"

}




