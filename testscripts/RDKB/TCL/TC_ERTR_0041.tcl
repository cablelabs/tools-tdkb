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
#TEST CASE ID :TC_ERTR_0041																							    
#Description  :Verify that Wireless client is not able to connect to WG with SSID that is not configured in WG

#########################################################################################################################
 }
#Initializing the values to the parameters by invoking Initializer proc
set configFile $argv;
Initializer $configFile;

puts {
######################################################################################################################### 
#Step 1 :Enabling the 2.4GHz Radio.                                                                           			  
#########################################################################################################################
}

set output "";
set output [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.WiFi.Radio.$ri2.Enable true boolean];
puts $output;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output] == 1 } {

puts "\nPossible error:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st Parameter";
set result "FAILED";	
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
puts {
######################################################################################################################### 
#Step 2 :Getting the value of the parameter that has been set                                                                                               
#########################################################################################################################
}

set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.WiFi.Radio.$ri2.Enable null null];
puts $output1;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output1] == 1 } {

puts "\nPossible error:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 1st Parameter";
set result "FAILED";    
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
set interface_name1 [split $wlanInterfaceName "_"];
puts {
######################################################################################################################### 
#Step 3 :Trying to Telent to WLAN Client                                                                           			
#########################################################################################################################
}

#telnet-ing to a WLAN server
spawn telnet $wlanIP
set timeout 100;
expect -re (.*ogin:);
send "$wlanName\r"; 
expect -re (.*word:); 
send "$wlanPassword\r";
expect -re ".*>";
send "netsh wlan add profile filename=\"$profilePath\\TRAIL-2.4-g-n-def.xml\" interface=\"$interface_name1\" user=all\r";
expect -re ".*>";
send "netsh wlan connect HOME-9DFD\r";
expect -re ".*>";
set outpCon $expect_out(buffer);
after 20000;
send "ipconfig\r";
expect -re ".*>";
set outIp $expect_out(buffer);
send "exit\r"
expect -re ".*>";
#wait
close $spawn_id
set passFlag "";
set failFlag "";
puts {
######################################################################################################################### 
#Step 4 :Checking whether the CPE is able to connect to the network with the specified SSID and obtain the IP address.                                                               					  
#########################################################################################################################
}

if {[regexp {There is no profile "HOME-9DFD" assigned to the specified interface.} $outpCon match] == 1} {
	puts "Connection Failed;Please try connecting with a proper SSID";
	set passFlag [expr $passFlag + 1];
	set result "PASSED"
	set passContent "Test Result : $result$~";
	displayProc $passContent;
	exit 0;

 } 
if {$passFlag == 1} {
set result "PASSED"	
} else {
	if {$passFlag <1} {
	set result "FAILED";
} 
  }


set passContent "Test Result : $result$~";
displayProc $passContent;


