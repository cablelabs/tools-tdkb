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
#TEST CASE ID :TC_ERTR_0168                                                                                                  
#Description  :Verify that on connecting a Wireless Client through 5 GHz radio, value of parameter  
#(Device.WiFi.AccessPoint.$si5.AssociatedDeviceNumberOfEntries) should be incremented accordingly
#########################################################################################################################
}
#Initializing the values to the parameters by invoking Initializer proc
set configFile $argv;
Initializer $configFile;


puts {
################################################################################
#Step 1 :Configuring the WG for wpawpa2-psk security
##############################################################################
}
set device_param "Device.WiFi.AccessPoint.$si5.Security.ModeEnabled";
set profileType "Wireless-5GHz.xm";
set wlan_sec_type "wpawpa2-psk";
set ssidName "$ssid5";
set test_radio "5ghz";
set ri "$ri5";
set si "$si5";
set response [config_wlan_sec_wpa2-psk $ClassPath $Class $oui $SNno $deviceType $device_param $test_radio $ssidName wpawpa2-psk $ri $si];
puts "The Result of config_wlan_sec_wpawpa2-psk is $response";
if {![regexp {pass} $response] == 1} {
exit 0;
}
puts {
##################################################################################
#Step 2 :Trying to connect to WLAN Client and disable the connect automatic option
##################################################################################
}
spawn telnet $wlanIP;
set timeout 100;
expect -re (.*ogin:);
send "$wlanName\r";
expect -re (.*word:);
send "$wlanPassword\r";
expect -re ".*>";
send "netsh wlan set profileparameter name=\"$ssidName\" connectionmode=manual\r";
expect -re ".*>";
send "netsh wlan set profileparameter name=$ssid5 connectionmode=manual\r";
expect -re ".*>";
send "exit\r";
wait
close $spawn_id;

puts {
##########################################################################################################
#Step 3 :Getting the value of number of clients connected in WLAN segment
##########################################################################################################
}
set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.WiFi.AccessPoint.$si5.AssociatedDeviceNumberOfEntries null null];
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
#Step 4 :Trying to connect to WG telnet-ing to a WLAN client
################################################################################
}
spawn telnet $wlanIP;
set timeout 100;
expect -re (.*ogin:);
send "$wlanName\r";
expect -re (.*word:);
send "$wlanPassword\r";
expect -re ".*>";
send "netsh wlan add profile filename=\"$profilePath\\Wireless-5GHz.xml\" interface=\"$interface_name1\"\r";
expect -re ".*>";
send "netsh wlan connect \"$ssidName\"\r";
expect -re ".*>";
after 30000;
send "exit\r";
wait
close $spawn_id;
set passFlag "";
set failFlag "";
puts {
##########################################################################################################
#Step 5 :Getting the value of number of clients connected in LAN segment after connecting WLAN client
##########################################################################################################
}
set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.WiFi.AccessPoint.$si5.AssociatedDeviceNumberOfEntries null null];
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
#Step 6 :Checking whether the number of clients connected in WLAN segment has increased after connecting 
#the wireless client  
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
#Step 7 :Reverting the WiFi client back to its initial state
##########################################################################################################
}
spawn telnet $wlanIP;
set timeout 100;
expect -re (.*ogin:);
send "$wlanName\r";
expect -re (.*word:);
send "$wlanPassword\r";
expect -re ".*>";
send "netsh wlan delete profile name=\"$ssidName\"\r";
expect -re ".*>";
after 30000;
send "exit\r";
wait
close $spawn_id;

set passContent "Test Result : $result$~";
displayProc $passContent;

