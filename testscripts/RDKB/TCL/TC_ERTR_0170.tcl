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
source proc.tcl;
source lib.tcl;
puts {
#########################################################################################################################
#TESTCASEID : TC_ERTR_0170
#Description  :Verify that MAC address of 2.4 GHz radio band obtained through parameter (Device.WiFi.SSID.1.BSSID) matches 
# with the address obtained from Wireless Client.   
##########################################################################################################################
 }
#Initializing the values to the parameters by invoking Initializer proc
#set configFile $argv;


set configFile $argv;
Initializer $configFile;

########################Logical id Check###############################


set device_param "Device.WiFi.AccessPoint.$si2.Security.ModeEnabled";
set profileType "Wireless.xml";
set wlan_sec_type "wpawpa2-psk";
set ssidName "$ssid2";
set test_radio "2.4ghz";
set radio_param "Device.WiFi.Radio.$ri2.Enable"
set interface_name1 [split $wlanInterfaceName "_"];

puts {
################################################################################
#Step 1 :Configuring the Accesspoint with wpawpa2-psk Secuirty mode                                            
################################################################################
}
set response [config_wlan_sec_wpa2-psk $ClassPath $Class $oui $SNno $deviceType $device_param $test_radio $ssidName $wlan_sec_type $ri2 $si2];
puts "The Result of config_wlan_sec_wpawpa2-psk is $response";
if {![regexp {pass} $response] == 1} {
exit 0;
}
puts {
######################################################################
#step 2 :Get the value of the parameter (Device.WiFi.SSID.1.BSSID)                                      
######################################################################
} 

set response [device_set_get_param $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.WiFi.SSID.$si2.BSSID null null {rType output}];
puts "The Result of Setparameter is $response";

if {[regexp -nocase {VALUE:(.*)\s+TYPE} $response m o]} {

puts $m;
puts $o;
} else {

puts "Unable to grep expected value";
set result "fail";
exit 0;
}

sleep 30;
puts {
#####################################################################################################################
#step 3: :Trying to connect to WG telnet-ing to a WLAN client and associate wirelessly for wpawpa2-psk security 
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
send "netsh wlan connect $ssid2\r";
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

if {[regexp {There is no profile "$ssid2" assigned to the specified interface.} $outpCon match] == 1} {

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

puts {
################################################################################
#Step 4 :Validating the output and checking for WPA2-PSK security mode           
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
set hy [regexp {.*BSSID.*: (.*)Network} $outInt match opauth] ;

if {[regexp {.*BSSID.*: (.*)Network} $outInt match opauth] == 1 } {
        puts "Expected Value: $o";
  	puts "Obtained Value :  $opauth";
        set f [string trim $opauth];
set g [string tolower $o];
set g1 [string compare $f $g];
       if {$g1 == 0} {
        puts "BSSID VALUE matching";
        set passFlag [expr $passFlag + 1];
        } else {
set failFlag [expr $failFlag + 1];
puts "BSSID VALUE not matching";

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




