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
source lib.tcl;
#Initializing the values to the parameters by invoking Initializer proc
#set configFile $argv;
set configFile $argv;
Initializer $configFile;
puts {
###############################################################################################################
TESTCASEID : TC_ERTR_0234
Description  : Verify that tcp traffic between wireless and wired clients should be denied when SSID parameter 
               for 5GHZ [Device.WiFi.SSID.2.Enable] is disabled.
###############################################################################################################
}

set device_param "Device.WiFi.AccessPoint.$si5.Security.ModeEnabled";
set profileType "Wireless-5GHz.xml";
set wlan_sec_type "wpawpa2-psk";
set ssidName "$ssid5";
set test_radio "5ghz";
set radio_param "Device.WiFi.Radio.$ri5.Enable";
set no [split $wlanInterfaceName "_"];

puts {
################################################################################
#Step 1 :Configuring the Accesspoint with wpawpa2-psk Secuirty mode
################################################################################
}
set response [config_wlan_sec_wpa2-psk $ClassPath $Class $oui $SNno $deviceType $device_param $test_radio $ssidName $wlan_sec_type $ri5 $si5];
puts "The Result of config_wlan_sec_wpawpa2-psk is $response";
if {![regexp {pass} $response] == 1} {
exit 0;
}
set device_param "Device.WiFi.Radio.$ri5.Enable";
set value "true";
set dataType "boolean";

set response [device_set_get_param $ClassPath $Class $oui $SNno $deviceType SetParameterValue $device_param $value $dataType];
puts "The Result of Setparameter is $response";
if {[string compare $response "pass"] != 0} {
puts "Setparameter fails"
exit 0;
}
set device_param "Device.WiFi.SSID.$si5.Enable";
set value "true";
set dataType "boolean";

set response [device_set_get_param $ClassPath $Class $oui $SNno $deviceType SetParameterValue $device_param $value $dataType];
puts "The Result of Setparameter is $response";
if {[string compare $response "pass"] != 0} {
puts "Setparameter fails"
exit 0;
}


puts {
##########################################################################################################
#Step 2 :Telneting to the WLAN client and obtaining its IP.
##########################################################################################################
} 
set profileType "Wireless-5GHz.xml";
set wlan_sec_type "wpawpa2-psk";
set ssidName "$ssid5";

set response [Configure_Client_open $wlanIP $wlanName $wlanPassword $profilePath $no $profileType $ssidName];

set wireless_pc_ip "$response";
puts "The Result of Configure client proc is $response";
if {![regexp {(\d+)\.(\d+)\.(\d+)\.(\d+)} $response m o] == 1} {
exit 0;
}
puts "$wireless_pc_ip";


puts {
###############################################################################
#step 3: Telnetting to LAN Clinet and get its ip address
###############################################################################
}
set response [connect_lan_pc $Telnetip $Name $password $osName1];
set wired_pc_ip "$response";
puts "The Result of connect_lan_pc is $response";
if {![regexp {(\d+)\.(\d+)\.(\d+)\.(\d+)} $response m o] == 1} {
exit 0;
}



puts {
##########################################################################################################
#Step 4 :Disabling 5ghz SSID interface of the device.
##########################################################################################################
}
set device_param "Device.WiFi.SSID.$si5.Enable";
set value "false";
set dataType "boolean";

set response [device_set_get_param $ClassPath $Class $oui $SNno $deviceType SetParameterValue $device_param $value $dataType];
puts "The Result of Setparameter is $response";
if {[string compare $response "pass"] != 0} {
puts "Setparameter fails"
exit 0;
}
after 15000;
puts {
################################################################################
#Step 5 :Initializing LAN PC as server using iperf
################################################################################
}

spawn telnet $Telnetip
set timeout 100;
expect -re (.*ogin:);
send "$Name\r";
expect -re (.*word:);
send "$password\r";
expect -re ".*#";
#send -i $spawn_id "iperf -s --remove\r";
#expect -re ".*#";
send -i $spawn_id "iperf -s --remove\r";
expect -re ".*Server";
#send "ps-ef | grep iperf\r";
send "\003";
expect -re ".*#";
send -i $spawn_id "iperf -s > output123.txt & \r";
expect -re ".*#";
close $spawn_id;

puts {
################################################################################
#Step 6 :Sending TCP packets from WLAN using iperf
################################################################################
}

spawn telnet $wlanIP
set timeout 100;
expect -re (.*ogin:);
send "$wlanName\r";
expect -re (.*word:);
send "$wlanPassword\r";
expect -re ".*>";
#send "iperf -s --remove\r";
#expect -re ".*>";
#expect -re ".*>";
send "iperf -s --remove\r";
expect -re ".*Server";
#send "ps-ef | grep iperf\r";
send "\003";
expect -re ".*>";
send "iperf -c $wired_pc_ip\r";
expect -re ".*>";
set clientoutput $expect_out(buffer)
close $spawn_id


puts {
################################################################################
#Step 7 :Validating the client Output
################################################################################
}
if { [ regexp {connect failed: Connection timed out.} $clientoutput match] == 1 } {

puts "CLIENT CONNECTION FAILED";
set result "PASSED";

} else { set result "FAILED";
}



puts {
############################################################################################
#Step 8 :Reverting the interface status back to its initial value.
############################################################################################
}
set device_param "Device.WiFi.SSID.$si5.Enable";
set value "true";
set dataType "boolean";

set response [device_set_get_param $ClassPath $Class $oui $SNno $deviceType SetParameterValue $device_param $value $dataType];
puts "The Result of Setparameter is $response";
if {[string compare $response "pass"] != 0} {
puts "Setparameter fails"
exit 0;
}
set passContent "Test Result : $result$~";
displayProc $passContent;

