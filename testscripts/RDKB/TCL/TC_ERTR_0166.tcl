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
#TEST CASE ID :TC_ERTR_0166                                                                                                  
#Description  :Verify that on connecting a Wireless Client through 2.4 GHz radio, value of parameter 
#(Device.WiFi.AccessPoint.$si2.AssociatedDeviceNumberOfEntries) should be incremented accordingly
#########################################################################################################################
}
#Initializing the values to the parameters by invoking Initializer proc
set configFile $argv;
Initializer $configFile;
puts {
##########################################################################################################
#Step 1 :Getting the value of number of clients connected in WLAN segment through TR-181 Parameter
##########################################################################################################
}
set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.WiFi.AccessPoint.$si2.AssociatedDeviceNumberOfEntries null null];
puts $output1;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output1] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
} 
regexp {.*VALUE:(.*) TYPE.*} $output1 match val1;
set interface_name1 [split $wlanInterfaceName "_"];
puts {
################################################################################
#Step 2 :Trying to connect to WG telnet-ing to a WLAN client
################################################################################
}
spawn telnet $wlanIP $telnetPort;
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
after 30000;
send "exit\r";
wait
close $spawn_id;
set passFlag "";
set failFlag "";
puts {
##########################################################################################################
#Step 3 :Getting the value of number of clients connected in LAN segment through 
#TR-181 Parameter after connecting WLAN client.                          
##########################################################################################################
}
set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.WiFi.AccessPoint.$si2.AssociatedDeviceNumberOfEntries null null];
puts $output1;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output1] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
} 
regexp {.*VALUE:(.*) TYPE.*} $output1 match val2;

puts {
##########################################################################################################
#Step 4 :Checking whether the number of clients connected in WLAN segment has increased after connecting 
#the wireless client.                                                                                  
##########################################################################################################
}
incr val1;
if {$val1 == $val2} {
set passFlag [expr $passFlag + 1];
puts "The number of WLAN clients has increased."
} else {
 set failFlag [expr $failFlag + 1];
puts "The number of WLAN clients has not increased."
}

if {$passFlag == 1} {
set result "PASSED"
} else {
        if {$failFlag >0 || $passFlag <1} {
        set result "FAILED";
}
  }

puts {
##########################################################################################################
#Step 5 :Reverting the WiFi client back to its initial state
##########################################################################################################
}
spawn telnet $wlanIP $telnetPort;
set timeout 100;
expect -re (.*ogin:);
send "$wlanName\r";
expect -re (.*word:);
send "$wlanPassword\r";
expect -re ".*>";
send "netsh wlan delete profile name=\"$ssid2\"\r";
expect -re ".*>";
after 30000;
send "exit\r";
wait
close $spawn_id;

set passContent "Test Result : $result$~";
displayProc $passContent;

