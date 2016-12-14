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
  package require Expect;
source proc.tcl;
source lib.tcl;
#Initializing the values to the parameters by invoking Initializer proc
#set configFile $argv;
set script_args $argv;
puts "Script arguments are $script_args";
set no_script_args $argc;
puts "Number of Script arguments are $no_script_args";
set configFile [lindex $script_args 0];
set logical_id [lindex $script_args 1];
puts "The config file is $configFile";
Initializer $configFile;
puts {
#####################################################################################
TESTCASEID : TC_ERTR_0383
Description  :Verify that telnet traffic between WLAN to LAN should be denied, when 
wifi client assocation in wpa2-psk authentication for 5GHZ and Radio interface 
parameter for 5GHZ [Device.WiFi.Radio.2.Enable] is disabled.
#####################################################################################
}
set device_param "Device.WiFi.AccessPoint.$si5.Security.ModeEnabled";
set profileType "Wireless-5GHz.xml";
set wlan_sec_type "wpa2-psk";
set ssidName "$ssid5";
set test_radio "5ghz";
set no [split $wlanInterfaceName "_"];
puts {
################################################################################
#Step 1 :Configuring the Accesspoint with wpa2-psk Secuirty mode
################################################################################
}
set response [config_wlan_sec_wpa2-psk $ClassPath $Class $oui $SNno $deviceType $device_param $test_radio $ssidName $wlan_sec_type $ri5 $si5];
puts "The Result of config_wlan_sec_wpa2-psk is $response";
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
set wlan_sec_type "wpa2-psk";
set ssidName "$ssid5";

set response [Configure_Client_open $wlanIP $wlanName $wlanPassword $profilePath $no $profileType $ssidName];

set wireless_pc_ip "$response";
puts "The Result of Configure client proc is $response";
if {![regexp {(\d+)\.(\d+)\.(\d+)\.(\d+)} $response m o] == 1} {
exit 0;
}
puts "$wireless_pc_ip";


puts {
##########################################################################################################
#Step 3 :Telneting to the LAN client and obtaining its IP.
##########################################################################################################
}

spawn telnet $Telnetip;
set timeout 100;
expect -re (.*ogin:);
send "$Name\r";
expect -re (.*word:);
send "$password\r";
expect -re ".*#";
send "service network restart\r";
expect -re ".*#";
send "ifconfig\r";
expect -re ".*#";
set outConfig $expect_out(buffer);
send "exit\r";
regexp {.*inet addr:([0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}).*Bcast:10.0.0.255.*} $outConfig match Ipval;
puts "$Ipval";

puts {
##########################################################################################################
#Step 4 :Disabling the 5GHz SSID interface of the WG
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

set passFlag "";
set failFlag "";
after 15000;

puts {
###################################################################################
#step 5: Send Telnet traffic from LAN to WLAN - traffic  should fail
###################################################################################
}

spawn telnet $Telnetip;
set timeout 100;
expect -re (.*ogin:);
send "$Name\r";
expect -re (.*word:);
send "$password\r";
expect -re ".*#";
send "telnet $wireless_pc_ip\r";
set timeout 100;
expect\
{
".*#"
{
set outTelnet $expect_out(buffer);
}
".*ogin:"
{

set result "FAILED";
set failFlag [expr $failFlag + 1];
puts "Telnet Request successful between WLAN and LAN"
}
}

#wait
close $spawn_id;

puts {
############################################################################################
#Step 6:Verifying the reachability of the Telnet Traffic
############################################################################################
}
if {[regexp {.*No route to host.*} $outTelnet match] == 1 } {
        set passFlag [expr $passFlag + 1];
        puts "Telnet Request not successful between WLAN and LAN"
                } else {
if {[regexp {.*Unable to connect to remote host.*} $outTelnet match] == 1 } {
        set passFlag [expr $passFlag + 1];
        puts "Telnet Request not successful between WLAN and LAN"
        } else {
        set failFlag [expr $failFlag + 1];
        puts "Telnet Request successful between WLAN and LAN"
        }
 }



if {$passFlag == 1} {
set result "PASSED"
} else {
        if {$failFlag >0 || $passFlag <1} {
        set result "FAILED";
}
  }


puts {
############################################################################################
#Step 7:Reverting the interface status back to its initial value.
############################################################################################
}
set response [config_wlan_sec_wpa2-psk $ClassPath $Class $oui $SNno $deviceType $device_param $test_radio $ssidName "wpawpa2-psk" $ri5 $si5];
puts "The Result of config_wlan_sec_wpawpa2-psk is $response";



set device_param "Device.WiFi.Radio.$ri5.Enable";
set value "true";
set dataType "boolean";

set response [device_set_get_param $ClassPath $Class $oui $SNno $deviceType SetParameterValue $device_param $value $dataType];
puts "The Result of Setparameter is $response";


set passContent "Test Result : $result$~";
displayProc $passContent;


