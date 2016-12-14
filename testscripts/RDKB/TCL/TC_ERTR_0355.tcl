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
puts {
###################################################################################################################################################
#TESTCASEID : TC_ERTR_0355															
#Description  :Verify that MAC address of 5 GHz radio band obtained through parameter (Device.WiFi.AccessPoint.$si5.AssociatedDevice.1.MACAddress) 
#matches with the address obtained from Wireless Client.             
######################################################################################################################################################
 }
#Initializing the values to the parameters by invoking Initializer proc
#set configFile $argv;
set configFile $argv;
Initializer $configFile;

########################Logical id Check###############################
set device_param "Device.WiFi.AccessPoint.$si5.Security.ModeEnabled";
set profileType "Wireless-5GHz.xml";
set wlan_sec_type "wpawpa2-psk";
set ssidName "$ssid5";
set test_radio "5ghz";
set radio_param "Device.WiFi.Radio.$si5.Enable";
set interface_name1 [split $wlanInterfaceName "_"];

puts {
################################################################################
#Step 1 :Configuring the Accesspoint with wpawpa2-psk Security mode                                                                        
################################################################################
}
set response [config_wlan_sec_wpa2-psk $ClassPath $Class $oui $SNno $deviceType $device_param $test_radio $ssidName $wlan_sec_type $ri5 $si5];
puts "The Result of config_wlan_sec_wpawpa2-psk is $response";
if {![regexp {pass} $response] == 1} {
exit 0;
}

sleep 30;
puts {
#####################################################################################################################
#step 2: :Telnrt to WLAN Client and connect to the SSID
#####################################################################################################################
}
spawn telnet $wlanIP;
set timeout 100;
expect -re (.*ogin:);
send "$wlanName\r";
expect -re (.*word:);
send "$wlanPassword\r";
expect -re ".*>";
send "netsh wlan add profile filename=\"$profilePath\\$profileType\" interface=\"$interface_name1\"\r";
expect -re ".*>";
send "netsh wlan connect $ssid5\r";
expect -re ".*>";
set outpCon $expect_out(buffer);
after 30000;
send "ipconfig\r";
expect -re ".*>";
set outIp $expect_out(buffer);
send "netsh wlan show interfaces\r";
expect -re ".*>";
set outInt $expect_out(buffer);

send "exit\r"
expect -re ".*>";
close $spawn_id
puts $outpCon;
puts $outIp;
set passFlag "";
set failFlag "";

if {[regexp {There is no profile "$ssid5" assigned to the specified interface.} $outpCon match] == 1} {

        puts "\nMissing profile. Please ensure that you create a profile and then try connecting";
        set failFlag [expr $failFlag + 1];
        set result "FAILED";
        set passContent "Test Result : $result$~";
        displayProc $passContent;
        exit 0;

 } 
        if {[regexp {Connection request was completed successfully.} $outpCon match] == 1} {
        set passFlag [expr $passFlag + 1];
        if { [regexp {.*Wireless LAN.*IPv4 Address.*: (.*) Sub.*Ethernet} $outIp match ip] == 1 } {
        set passFlag [expr $passFlag + 1];      
        if {[regexp {169\.254\..*\..*} $ip] == 1 || [regexp {127\.0\.0\.0} $ip] == 1 } {
        
        puts "Test case failed; Unable to obtain IP\n";
        set failFlag [expr $failFlag + 1];
        
        } else { 
        
        if {[regexp {10\..*\..*\..*} $ip] == 1} {
        puts "Connection Successful";
        puts "IP obtained is: $ip\n";
        set passFlag [expr $passFlag + 1];
         
                }
        }

        }       
} else {
         puts "\Connection not successful.";
         set failFlag [expr $failFlag + 1];
}

puts $passFlag; 
puts {
################################################################################
#Step 3 :Validating the output and checking for WPA2-PSK security mode           
################################################################################
}
if {[regexp { .*There.*Channel.*: (.*) Rec} $outInt match channel] == 1 } {
        if { $channel >= 1 && $channel <= 11 } {
        puts "Client connected to CM successfully through channel number $channel";
        puts "Operating frequency band : 2.4GHZ"        
        } else {
        if { $channel > 11 } {
        puts "Client connected to CM successfully through channel number $channel";
        puts "Operating frequency band : 5GHZ"
                }
        }
 }
if {[regexp {.*There.*Authentication.*: (.*) Cip} $outInt match opauth] == 1 } {
        puts "Expected Mode : 'WPA2-Personal'";
        if {[regexp {WPA2-Personal} $opauth match] == 1} {
        puts "Obtained Mode :  $opauth";
        puts "Authentication mode matching";
        set passFlag [expr $passFlag + 1];
        } else {
        puts "Obtained Mode :  $opauth";
        puts "Authentication mode not matching";
        set failFlag [expr $failFlag + 1];
                }
  }




puts {
###########################################################################################################
#step 4 :Get the valus of the parameter (Device.WiFi.AccessPoint.10001.AssociatedDevice.1.MACAddress)                                                        
###########################################################################################################
}

set response [device_set_get_param $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.WiFi.AccessPoint.$si5.AssociatedDevice.1.MACAddress null null {rType output}];
puts "The Result of Setparameter is $response";
if {[regexp -nocase {VALUE:(.*)\s+TYPE} $response m o]} {
#puts $m;
#puts $o;
} else {
puts "Unable to grep expected value";
set result "fail";
exit 0;
}

puts $passFlag;
set hy [regexp {.*Physical address.*: (.*)State} $outInt match opauth] ;
#puts $hy;
#puts $match;
#puts $opauth;

if {[regexp {.*Physical address.*: (.*)State} $outInt match opauth] == 1 } {
        puts "Expected Value: $o";
  	puts "Obtained Value :  $opauth";
        set f [string trim $opauth];
#puts $f;
set g [string tolower $o];
set g1 [string compare $f $g];

       if {$g1 == 0} {
        puts "MAC Addresses are matching";
        set passFlag [expr $passFlag + 1];
        } else {
set failFlag [expr $failFlag + 1];
puts "MAC Addresses are not matching";

        }
} 


if {$passFlag == 5} {
set result "PASSED"
} else {
        if {$failFlag >0 || $passFlag <5} {
        set result "FAILED";
}
}

puts $result;
set passContent "Test Result : $result";
displayProc $passContent;




