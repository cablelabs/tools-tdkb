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
puts {
#####################################################################################				
TESTCASEID :TC_ERTR_0158 to TC_ERTR_0163																							    
Description  :Verify whether WG supports Open Security mode for 2.4GHZ frequency band.
Ensure that client should be able to connect to WG   
          
#####################################################################################
 }
#Initializing the values to the parameters by invoking Initializer proc
#set configFile $argv;
set script_args $argv;
puts "Script arguments are $script_args";
set no_script_args $argc;
puts "Number of Script arguments are $no_script_args";
set configFile [lindex $script_args 0];
set logical_id [lindex $script_args 1];
puts "The config file is $configFile";
puts "The logical id is $logical_id";
Initializer $configFile;


########################Logical id Check###############################

if {[regexp -nocase {TC_ERTR_0158} $logical_id]} {
set device_param "Device.WiFi.AccessPoint.$si2.Security.ModeEnabled";
set wlan_sec_type "open";
set profileType "Wireless-open-2.4.xml";
set ssidName "$ssid2";
set test_radio "2.4ghz";
set ri "$ri2";
set si "$si2";
} elseif {[regexp -nocase {TC_ERTR_0159} $logical_id]} {
set device_param "Device.WiFi.AccessPoint.$si5.Security.ModeEnabled";
set profileType "Wireless-open-5.xml";
set wlan_sec_type "open";
set ssidName "$ssid5";
set test_radio "5ghz";
set ri "$ri5";
set si "$si5";
} elseif {[regexp -nocase {TC_ERTR_0160} $logical_id]} {
set device_param "Device.WiFi.AccessPoint.$si2.Security.ModeEnabled";
set profileType "Wireless.xml";
set wlan_sec_type "wpa2-psk";
set ssidName "$ssid2";
set test_radio "2.4ghz";
set ri "$ri2";
set si "$si2";
} elseif {[regexp -nocase {TC_ERTR_0161} $logical_id]} {
set device_param "Device.WiFi.AccessPoint.$si5.Security.ModeEnabled";
set profileType "Wireless-5GHz.xml";
set wlan_sec_type "wpa2-psk";
set ssidName "$ssid5";
set test_radio "5ghz";
set ri "$ri5";
set si "$si5";
} elseif {[regexp -nocase {TC_ERTR_0162} $logical_id]} {
set device_param "Device.WiFi.AccessPoint.$si2.Security.ModeEnabled";
set profileType "Wireless.xml";
set wlan_sec_type "wpawpa2-psk";
set ssidName "$ssid2";
set test_radio "2.4ghz";
set ri "$ri2";
set si "$si2";
} elseif {[regexp -nocase {TC_ERTR_0163} $logical_id]} {
set device_param "Device.WiFi.AccessPoint.$si5.Security.ModeEnabled";
set profileType "Wireless-5GHz.xml";
set wlan_sec_type "wpawpa2-psk";
set ssidName "$ssid5";
set test_radio "5ghz";
set ri "$ri5";
set si "$si5";
} else {
puts "Logical Id Mismatches";
exit 0;
}
puts "The device tr69 parameter of $logical_id is $device_param";
set no [split $wlanInterfaceName "_"];
puts {
################################################################################
#Step 1 :Configuring the Accesspoint with $wlan_sec_type Security mode                                     
################################################################################
}
puts "$ClassPath";
if {[regexp -nocase {open} $wlan_sec_type]} { 
#set response [device_set_get_param $ClassPath $Class $oui $SNno $deviceType SetParameterValue $device_param None string];
#puts "The Result of Setparameter is $response";

set response [config_wlan_sec_open $ClassPath $Class $oui $SNno $deviceType $device_param $test_radio $ssidName $ri $si];
puts "The Result of config_wlan_sec_open is $response";
if {![regexp {pass} $response] == 1} {
exit 0;
}
puts {
#########################################################################################################
#Step 2 :Trying to connect to WG telnet-ing to a WLAN client and associate wirelessly for open security  
#########################################################################################################
}
set response [Configure_Client_open $wlanIP $wlanName $wlanPassword $profilePath $no $profileType $ssidName];
set wireless_pc_ip "$response";
puts "The Result of Configure client proc is $response";
set g [regexp {(\d+)\.(\d+)\.(\d+)\.(\d+)} $response m o];
puts $g;
if {![regexp {(\d+)\.(\d+)\.(\d+)\.(\d+)} $response m o] == 1} {
exit 0;
}
puts "$wireless_pc_ip";
} elseif {[regexp -nocase {wpa2-psk} $wlan_sec_type]} {
set response [config_wlan_sec_wpa2-psk $ClassPath $Class $oui $SNno $deviceType $device_param $test_radio $ssidName $wlan_sec_type $ri $si];
puts "The Result of config_wlan_sec_wpa2-psk is $response";
if {![regexp {pass} $response] == 1} {
exit 0;
}

puts {
##############################################################################################################
#Step 3 :Trying to connect to WG telnet-ing to a WLAN client and associate wirelessly for wpa2-psk security       
##############################################################################################################
}

set response [Configure_Client_open $wlanIP $wlanName $wlanPassword $profilePath $no $profileType $ssidName];
set wireless_pc_ip "$response";
puts "The Result of Configure client proc is $response";
if {![regexp {(\d+)\.(\d+)\.(\d+)\.(\d+)} $response m o] == 1} {
exit 0;
}
puts "$wireless_pc_ip";
} elseif {[regexp -nocase {wpawpa2-psk} $wlan_sec_type]} {
set response [config_wlan_sec_wpa2-psk $ClassPath $Class $oui $SNno $deviceType $device_param $test_radio $ssidName $wlan_sec_type $ri $si];
puts "The Result of config_wlan_sec_wpawpa2-psk is $response";
if {![regexp {pass} $response] == 1} {
exit 0;
}
puts {
#################################################################################################################
#Step 4 :Trying to connect to WG telnet-ing to a WLAN client  and associate wirelessly for wpawpa2-psk security            
#################################################################################################################
} 

set response [Configure_Client_open $wlanIP $wlanName $wlanPassword $profilePath $no $profileType $ssidName];

set wireless_pc_ip "$response";
puts "The Result of Configure client proc is $response";
if {![regexp {(\d+)\.(\d+)\.(\d+)\.(\d+)} $response m o] == 1} {
exit 0;
}
puts "$wireless_pc_ip";
} 
puts {
###############################################################################
#step 5: Telnetting to lan pc and get its ip address
###############################################################################
}
set response [connect_lan_pc $Telnetip $Name $password $osName1];
set wired_pc_ip "response";
puts "The Result of connect_lan_pc is $response";  
if {![regexp {(\d+)\.(\d+)\.(\d+)\.(\d+)} $response m o] == 1} {
exit 0;
}

puts {
###################################################################################
#step 6: Send ICMP traffic and validate the same with different size ping packets
###################################################################################
}
spawn telnet $Telnetip;
set timeout 100;
expect -re (.*ogin:);
send "$Name\r";
expect -re (.*word:);
send "$password\r";
expect -re ".*#";
send "ip route add $wireless_pc_ip via 10.0.0.1\r";
expect -re ".*#";
send "ping -c 4 -s 500 $wireless_pc_ip\r";
expect -re ".*#";
set outPing $expect_out(buffer);
expect -re ".*#";
send "\n";
expect -re ".*#";
send "ping -c 4 -s 1000 $wireless_pc_ip\r";
expect -re ".*#";
set outPing1 $expect_out(buffer);
expect -re ".*#";
send "\n";
expect -re ".*#";
send "ping -c 4 -s 1500 $wireless_pc_ip\r";
expect -re ".*#";
set outPing2 $expect_out(buffer);
expect -re ".*#";
send "ip route delete $wireless_pc_ip via 10.0.0.1\r";
expect -re ".*#";

#wait
close $spawn_id;
set passFlag "";
set failFlag "";

puts {
############################################################################################
#Step 7 :Verifying the reachability of the ICMP message
############################################################################################
}

if {[regexp {.*4 packets transmitted.* (.*)% packet loss.*} $outPing match lossPercent] == 1} {
        if {$lossPercent == 0} {
        set passFlag [expr $passFlag + 1];
        puts "Ping successful from wired to wireless with packet size 500";
        } else {
        set failFlag [expr $failFlag + 1];
        puts "Ping not successful.Blocked from wired to wireless with packet size 500"

        }
}
puts "check 1000 bytes";
puts "$outPing1";
puts "$outPing2";

if {[regexp {.*4 packets transmitted.* (.*)% packet loss.*} $outPing1 match lossPercent] == 1} {
        if {$lossPercent == 0} {
        set passFlag [expr $passFlag + 1];
        puts "Ping successful from wired to wireless with packet size 1000"
        } else {
        set failFlag [expr $failFlag + 1];
        puts "Ping not successful.Blocked from wired to wireless with packet size 1000"

        }
}
if {[regexp {.*4 packets transmitted.* (.*)% packet loss.*} $outPing2 match lossPercent] == 1} {
        if {$lossPercent == 0} {
        set passFlag [expr $passFlag + 1];
        puts "Ping successful from wired to wireless with packet size 1500"
        } else {
        set failFlag [expr $failFlag + 1];
        puts "Ping not successful.Blocked from wired to wireless with packet size 1500"

        }
}

if {$passFlag >= 1} {
set result "PASSED"
} else {
  set result "FAILED"
}

puts $result;

set response [config_wlan_sec_wpa2-psk $ClassPath $Class $oui $SNno $deviceType $device_param $test_radio $ssidName "wpawpa2-psk" $ri $si];
puts "The Result of config_wlan_sec_wpawpa2-psk is $response";

set passContent "Test Result : $result";
displayProc $passContent;




