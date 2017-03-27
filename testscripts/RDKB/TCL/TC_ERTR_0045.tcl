##########################################################################
# If not stated otherwise in this file or this component's Licenses.txt
# file the following copyright and licenses apply:
#
# Copyright 2016 RDK Management
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
##########################################################################
# 

package require Expect;
source proc.tcl;
puts {
######################################################################################################################### 
#TESTCASE ID :TC_ERTR_0045 																						   
#Description  :Verify that MAC address based Access control allows 2.4GHZ SSID to connect to WG and deny access for 5GHZ SSID.
 									
#########################################################################################################################
}
#Initializing the values to the parameters by invoking Initializer proc
set configFile $argv;
Initializer $configFile;

puts {
######################################################################################################################### 
#Step 1 : Allowing access for 2.4GHZ and denying access for 5GHZ                                     					  
#########################################################################################################################
}
set output "";
set output [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.WiFi.AccessPoint.$si2.X_CISCO_COM_MACFilter.Enable true boolean];
puts $output;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
set voutput "";
set voutput [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.WiFi.AccessPoint.$si5.X_CISCO_COM_MACFilter.Enable true boolean];
puts $voutput;
if {[regexp {.*Time limit has crossed 2 minutes.*} $voutput] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 2nd parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.WiFi.AccessPoint.$si2.X_CISCO_COM_MACFilter.FilterAsBlackList false boolean];
puts $output1;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output1] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 3rd parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
set voutput1 "";
set voutput1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.WiFi.AccessPoint.$si5.X_CISCO_COM_MACFilter.FilterAsBlackList true boolean];
puts $voutput1;
if {[regexp {.*Time limit has crossed 2 minutes.*} $voutput1] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 4th parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

spawn telnet $wlanIP $telnetPort;
set timeout 100;
expect -re (.*ogin:);
send "$wlanName\r";
expect -re (.*word:);
send "$wlanPassword\r";
expect -re ".*>";
send "ipconfig /all\r";
expect -re ".*>";
set outIp $expect_out(buffer);
send "netsh wlan delete profile name=\"$ssid2\"\r";
expect -re ".*>";

send "netsh wlan delete profile name=\"$ssid2\"\r";
expect -re ".*>";
send "exit\r";
expect -re ".*>";
#wait
close $spawn_id

regexp {.*Wireless LAN.*Physical Address.*: ([0-9 A-F]{1,2}-[0-9 A-F]{1,2}-[0-9 A-F]{1,2}-[0-9 A-F]{1,2}-[0-9 A-F]{1,2}-[0-9 A-F]{1,2}).*DHCP Enabled.*Ethernet.*} $outIp match MAC1;

regsub -all {\-} $MAC1 {:} m1;



spawn telnet $AutomationServerIP;
set timeout 100;
expect -re (.*ogin:);
send "$AutomationServerName\r";
expect -re (.*word:);
send "$AutomationServerPassword\r";
expect -re ".*$";

regsub -all {\:} $SNno {} SNnoWithoutColon;
set output2 "";
set output2 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetMultipleParameterValues Device.WiFi.AccessPoint.$si2.X_CISCO_COM_MacFilterTable.DeviceName,Device.WiFi.AccessPoint.$si2.X_CISCO_COM_MacFilterTable.MACAddress $wlanName,$m1 string,string];

#expect -re ".*~]";
#set output2 $expect_out(buffer);

#Exiting Automation Server
#send "exit\r";
#expect -re ".*";

puts $output2;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output2] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 5th parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

spawn telnet $AutomationServerIP;
set timeout 100;
expect -re (.*ogin:);
send "$AutomationServerName\r";
expect -re (.*word:);
send "$AutomationServerPassword\r";
expect -re ".*$";

regsub -all {\:} $SNno {} SNnoWithoutColon;
set voutput2 "";
set voutput2 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetMultipleParameterValues Device.WiFi.AccessPoint.$si5.X_CISCO_COM_MacFilterTable.DeviceName,Device.WiFi.AccessPoint.$si5.X_CISCO_COM_MacFilterTable.MACAddress $wlanName,$m1 string,string];

#expect -re ".*~]";
#set voutput2 $expect_out(buffer);

#Exiting Automation Server
#send "exit\r";
#expect -re ".*";
puts $voutput2;
if {[regexp {.*Time limit has crossed 2 minutes.*} $voutput2] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 5th parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}



puts {
################################################################################
#Step 2:Get the values of the parameters that have been set.                                                                  			 
################################################################################
}
set goutput "";
set goutput [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.WiFi.AccessPoint.$si2.X_CISCO_COM_MACFilter.Enable  null null];
puts $goutput;
if {[regexp {.*Time limit has crossed 2 minutes.*} $goutput] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
set goutput1 "";
set goutput1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.WiFi.AccessPoint.$si5.X_CISCO_COM_MACFilter.Enable null null];
puts $goutput1;
if {[regexp {.*Time limit has crossed 2 minutes.*} $goutput1] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 2nd parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
set goutput2 "";
set goutput2 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.WiFi.AccessPoint.$si2.X_CISCO_COM_MACFilter.FilterAsBlackList null null];
puts $goutput2;
if {[regexp {.*Time limit has crossed 2 minutes.*} $goutput2] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 3rd parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
set goutput3 "";
set goutput3 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.WiFi.AccessPoint.$si5.X_CISCO_COM_MACFilter.FilterAsBlackList null null];
puts $goutput3;
if {[regexp {.*Time limit has crossed 2 minutes.*} $goutput3] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 4th parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

set interface_name1 [split $wlanInterfaceName "_"];
puts {
######################################################################################################################### 
#Step 3 :Telneting to a WLAN client                                                                   					 
#########################################################################################################################
}
#telnet-ing to a WLAN server
spawn telnet $wlanIP $telnetPort
set timeout 100;
expect -re (.*ogin:);
send "$wlanName\r"; 
expect -re (.*word:); 
send "$wlanPassword\r";
expect -re ".*>";
send "netsh wlan add profile filename=\"$profilePath\\Wireless.xml\" interface=\"$interface_name1\"\r";
expect -re ".*>";
send "netsh wlan connect $ssid2\r";
expect -re ".*>";
set outpCon $expect_out(buffer);
after 20000
send "ipconfig\r";
expect -re ".*>";
set outInt $expect_out(buffer);
send "netsh wlan delete profile name=\"$ssid2\"\r";
expect -re ".*>";
send "exit\r"
expect -re ".*>";
#wait
close $spawn_id

set passFlag "";
set failFlag "";


puts {
######################################################################################################################### 
#Step 4 :Checking the connection details by validating the response.                                                               					
#########################################################################################################################
}


if {[regexp {There is no profile "$ssid2" assigned to the specified interface.} $outpCon match] == 1} {

	puts "\nMissing profile. Please ensure that you create a profile and then try connecting";
	#set passFlag [expr $passFlag +1];
	set passContent "Test Result : $result$~";
	displayProc $passContent;
	exit 0;

 } 
	if {[regexp {Connection request was completed successfully.} $outpCon match] == 1} {
	if { [regexp {Wireless\s*LAN\s*[^\:]*:[^\:]*:[^\:]*:\s*[\w*:]*[^\:]*:\s*[\w*:]*[^\:]*:\s*[\w*:]*[^\:]*:\s*[\w*:]*\W*\w*\s*IPv4\s*Address[^\:]*:\s*(\d+.\d+.\d+.\d+)} $outInt match ip] == 1 } {
		
	if {[regexp {169\.254\..*\..*} $ip] == 1 || [regexp {127\.0\.0\.0} $ip] == 1 } {
	
	puts " Unable to obtain IP\n";
		
	} elseif {[regexp {10\.0\.0\..*} $ip] == 1} {
        puts "Connection Successful";
        puts "IP obtained is: $ip\n";
        puts "IP address obtained within the Default DHCP server range";
        set passFlag [expr $passFlag + 1];
        } else {
        puts "IP obtained is: $ip\n";
        puts "IP address not obtained within the Default DHCP server range";
        }

	
} else {
	 puts "Unable to obtain IP address"
	 set failFlag [expr $failFlag + 1];
} 	
}  else {
         puts "\Connection not successful due to MAC Filter for 2.4GHZ SSID";
         set failFlag [expr $failFlag + 1];
}    

set interface_name1 [split $wlanInterfaceName "_"];
puts {
######################################################################################################################### 
#Step 5 :Telneting to a WLAN client.                                                                  					 
#########################################################################################################################
}
spawn telnet $wlanIP $telnetPort
set timeout 100;
expect -re (.*ogin:);
send "$wlanName\r"; 
expect -re (.*word:); 
send "$wlanPassword\r";
expect -re ".*>";
send "netsh wlan add profile filename=\"$profilePath\\Wireless-5GHz.xml\" interface=\"$interface_name1\"\r";
expect -re ".*>";
send "netsh wlan connect $ssid5\r";
expect -re ".*>";
set outpCon $expect_out(buffer);
after 20000
send "ipconfig\r";
expect -re ".*>";
set outInt $expect_out(buffer);
send "netsh wlan delete profile name=\"$ssid5\"\r";
expect -re ".*>";
send "exit\r"
expect -re ".*>";
#wait
close $spawn_id

puts {
######################################################################################################################### 
#Step 6 :Checking the connection details for the MAC address by validating the response.                                          					
#########################################################################################################################
}
if {[regexp {There is no profile "$ssid5" assigned to the specified interface.} $outpCon match] == 1} {

	puts "\nMissing profile. Please ensure that you create a profile and then try connecting";
	set passContent "Test Result : $result$~";
	displayProc $passContent;
	exit 0;

 } 
	if {[regexp {Connection request was completed successfully.} $outpCon match] == 1} {
	if { [regexp {Wireless\s*LAN\s*[^\:]*:[^\:]*:[^\:]*:\s*[\w*:]*[^\:]*:\s*[\w*:]*[^\:]*:\s*[\w*:]*[^\:]*:\s*[\w*:]*\W*\w*\s*IPv4\s*Address[^\:]*:\s*(\d+.\d+.\d+.\d+)} $outInt match ip] == 1 } {
	if {[regexp {169\.254\..*\..*} $ip] == 1 || [regexp {127\.0\.0\.0} $ip] == 1 } {
	
	puts "Test case failed; Unable to obtain IP\n";
	set failFlag [expr $failFlag + 1];
	
	} else { 
	
	if {[regexp {10\..*\..*\..*} $ip] == 1} {
	puts "Connection Successful for 5GHZ SSID";
	puts "IP obtained : $ip\n";
	set failFlag [expr $failFlag + 1];
	 
		}
	}

	
} else {
	 puts "\Connection not Successful due to MAC filter for 5GHZ SSID";
	 puts "Unable to Obtain IP";
	 set passFlag [expr $passFlag + 1];
} 	
}

if {$passFlag == 2} {
set result "PASSED"	
} else {
	if {$failFlag >0 || $passFlag <2} {
	set result "FAILED";
} 
  }

puts {
######################################################################################################################### 
#Step 7 :Reverting the parameters to its default value                                        					
#########################################################################################################################
}
set soutput "";
set soutput [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.WiFi.AccessPoint.$si2.X_CISCO_COM_MACFilter.Enable false boolean];
puts $soutput;
if {[regexp {.*Time limit has crossed 2 minutes.*} $soutput] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
set loutput "";
set loutput [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.WiFi.AccessPoint.$si5.X_CISCO_COM_MACFilter.Enable false boolean];
puts $loutput;
if {[regexp {.*Time limit has crossed 2 minutes.*} $loutput] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

set voutput2 "";
set voutput2 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.WiFi.AccessPoint.$si5.X_CISCO_COM_MACFilter.FilterAsBlackList false boolean];
puts $voutput2;
if {[regexp {.*Time limit has crossed 2 minutes.*} $voutput2] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 4th parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}


spawn telnet $AutomationServerIP;
set timeout 100;
expect -re (.*ogin:);
send "$AutomationServerName\r";
expect -re (.*word:);
send "$AutomationServerPassword\r";
expect -re ".*$";

regsub -all {\:} $SNno {} SNnoWithoutColon;
set soutput "";
set soutput [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetMultipleParameterValues Device.WiFi.AccessPoint.$si5.X_CISCO_COM_MacFilterTable.DeviceName,Device.WiFi.AccessPoint.$si5.X_CISCO_COM_MacFilterTable.MACAddress $wlanName,00:00:00:00:00:00 string,string];

#expect -re ".*~]";
#set soutput $expect_out(buffer);
#after 5000;

set soutput1 "";
set soutput1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetMultipleParameterValues Device.WiFi.AccessPoint.$si5.X_CISCO_COM_MacFilterTable.DeviceName,Device.WiFi.AccessPoint.$si5.X_CISCO_COM_MacFilterTable.MACAddress $wlanName,00:00:00:00:00:00 string,string];

#expect -re ".*~]";
#set soutput1 $expect_out(buffer);
#after 5000;

#Exiting Automation Server
#send "exit\r";
#expect -re ".*";

puts $soutput;
if {[regexp {.*Time limit has crossed 2 minutes.*} $soutput] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 3rd parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

puts $soutput1;
if {[regexp {.*Time limit has crossed 2 minutes.*} $soutput1] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 3rd parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}


set passContent "Test Result : $result$~";
displayProc $passContent;



