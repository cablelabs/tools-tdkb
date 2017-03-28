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
################################################################################################################################## 
#TEST CASEID :TC_ERTR_0176			
#Description  :Verify that when DHCP Server Subnet mask is set to 255.255.255.128,  Max address cannot be set greater 
#than 10.0.0.127 due to block size of 128 
##################################################################################################################################
}
#Initializing the values to the parameters by invoking Initializer proc
set configFile $argv;
Initializer $configFile;


puts {
################################################################################################
#Step 1 :Set DHCP Server Subnet mask to 255.255.255.128
################################################################################################
}

set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_CISCO_COM_DeviceControl.LanManagementEntry.1.LanIPAddress 10.0.0.1 string ];
puts $output1;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output1] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
set output2 "";
set output2 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_CISCO_COM_DeviceControl.LanManagementEntry.1.LanSubnetMask 255.255.255.128 string];
puts $output2;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output2] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

set output3 "";
set output3 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.DHCPv4.Server.Pool.1.MinAddress 10.0.0.2 string];
puts $output3;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output3] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

set output4 "";
set output4 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.DHCPv4.Server.Pool.1.MaxAddress 10.0.0.130 string];
puts $output4;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output4] == 1 } {

puts "----------------------------------------------------------------------------------------------------------------------";
puts "Failed to set Max address as 10.0.0.130 as the value is greater than block size 128";
puts "---------------------------------------------------------------------------------------------------------------------";
}
set output4 "";
set output4 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.DHCPv4.Server.Pool.1.MaxAddress 10.0.0.126 string];
puts $output4;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output4] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;

}

puts {
################################################################################
#Step 2 :Get the values of the parameters that have been set.                                         
################################################################################
}
set output5 "";
set output5 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_CISCO_COM_DeviceControl.LanManagementEntry.1.LanIPAddress null null];
puts $output5;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output5] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

set output6 "";
set output6 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_CISCO_COM_DeviceControl.LanManagementEntry.1.LanSubnetMask null null];
puts $output6;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output6] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

set output7 "";
set output7 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.DHCPv4.Server.Pool.1.MinAddress null null];
puts $output7;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output7] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

set output8 "";
set output8 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.DHCPv4.Server.Pool.1.MaxAddress null null];
puts $output8;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output8] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
set interface_name1 [split $wlanInterfaceName "_"];
after 90000;
puts {
################################################################################
#Step 3 Telnet-ing to a WLAN client and obtaining the subnet mask.                                       
################################################################################
}
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
after 30000
send "ipconfig\r";
expect -re ".*>";
set outIp $expect_out(buffer);
send "netsh wlan show interfaces\r";
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
################################################################################
#Step 4 :Verifying the 2.4GHz Wi-Fi Connectivity and cehcking Subnet mask
################################################################################
}

if {[regexp {There is no profile "$ssid2" assigned to the specified interface.} $outpCon match] == 1} {

	puts "\nMissing profile. Please ensure that you create a profile and then try connecting";
	set failFlag [expr $failFlag + 1];
	set result "FAILED";
	set passContent "Test Result : $result$~";
	displayProc $passContent;
	exit 0;

 } 
	if {[regexp {Connection request was completed successfully.} $outpCon match] == 1} {
	#set passFlag [expr $passFlag + 1];
	if { [regexp {Wireless\s*LAN\s*[^\:]*:[^\:]*:[^\:]*:\s*[\w*:]*[^\:]*:\s*[\w*:]*[^\:]*:\s*[\w*:]*[^\:]*:\s*[\w*:]*\W*\w*\s*IPv4\s*Address[^\:]*:\s*(\d+.\d+.\d+.\d+)} $outIp match ip] == 1 && [regexp {.*Wireless LAN.*Subnet Mask.*: (.*) Default.*Ethernet} $outIp match submask] == 1 } {
	#set passFlag [expr $passFlag + 1];	
	if {[regexp {169\.254\..*\..*} $ip] == 1 || [regexp {127\.0\.0\.0} $ip] == 1 } {
	puts "Test case failed; Unable to obtain IP\n";
	set failFlag [expr $failFlag + 1];
	} elseif {[regexp {255\.255\.255\.128} $submask] == 1} {
	puts "Connection Successful";
	puts "Expected Subnet mask is : 255.255.255.128";
	puts "Obtained Subnet mask is : $submask\n";
	puts "Subnet mask is matching";
	set passFlag [expr $passFlag + 1];
	} else {
	puts "Expected Subnet mask is : 255.255.255.128";
	puts "Obtained Subnet mask is : $submask\n";
	puts "Subnet mask is not matching";
	}
	
	
} else {
	 puts "\IP address not obtained";
	 set failFlag [expr $failFlag + 1];
} 	
} else {
	 puts "\Connection not successful.";
	 set failFlag [expr $failFlag + 1];
}


if {$passFlag == 1} {
set result "PASSED"	
} else {
	if {$failFlag >0 || $passFlag <1} {
	set result "FAILED";
} 
  }
puts {
################################################################################
#Step 5 :Reverting the DHCPv4 server to its default value.                                     
################################################################################
}
set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_CISCO_COM_DeviceControl.LanManagementEntry.1.LanIPAddress 10.0.0.1 string];
puts $output1;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output1] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

set output2 "";
set output2 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_CISCO_COM_DeviceControl.LanManagementEntry.1.LanSubnetMask 255.255.255.0  string];
puts $output2;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output2] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

set output3 "";
set output3 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.DHCPv4.Server.Pool.1.MinAddress 10.0.0.2 string];
puts $output3;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output3] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

set output4 "";
set output4 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.DHCPv4.Server.Pool.1.MaxAddress 10.0.0.253 string];
puts $output4;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output4] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}


set passContent "Test Result : $result$~";
displayProc $passContent;



