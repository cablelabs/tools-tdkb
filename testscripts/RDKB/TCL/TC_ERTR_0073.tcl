##
# ============================================================================
# COMCAST CONFIDENTIAL AND PROPRIETARY
# ============================================================================
# This file and its contents are the intellectual property of Comcast.  It may
# not be used, copied, distributed or otherwise  disclosed in whole or in part
# without the express written permission of Comcast.
# ============================================================================
# Copyright (c) 2016 Comcast. All rights reserved.
# ============================================================================
##
package require Expect;
source proc.tcl;
puts {
##########################################################################################################################################
#TEST CASEID :TC_ERTR_0073                                                                                                                                                                            
#Description  :Verify that when Firewall Config is set to Low, HTTPS  access from WLAN to WAN should pass through
##########################################################################################################################################
}
#Initializing the values to the parameters by invoking Initializer proc
set configFile $argv;
Initializer $configFile;

puts {
################################################################################
#Step 1 :Setting the firewall configuration in Low mode.
################################################################################
}

set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_CISCO_COM_Security.Firewall.FirewallLevel Low string];
puts $output1;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output1] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

puts {
##########################################################################################################
#Step 2 :Get the value of parameters that have been set.                                            
##########################################################################################################
}
set output3 "";
set output3 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_CISCO_COM_Security.Firewall.FirewallLevel  null null];
puts $output3;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output3] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
set interface_name1 [split $wlanInterfaceName "_"];
puts {
################################################################################
#Step 3 :Trying to connect to WG telnet-ing to a LAN client                                                                  
################################################################################
}
spawn telnet $wlanIP
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
send "wget --tries=1 -T 60 https://68.87.16.190 --no-check-certificate\r";
expect -re ".*>";
set outHttps $expect_out(buffer);
send "netsh wlan delete \"$ssid2\"\r";
expect -re ".*>";
send "exit\r";
expect -re ".*>";


#wait
close $spawn_id;
set passFlag "";
set failFlag "";
puts {
############################################################################################
#Step 4 :Verifying the reachability of the HTTPS Traffic
############################################################################################
}
if {[regexp {.*200 OK.*} $outHttps match] == 1} {
        set passFlag [expr $passFlag + 1];
        puts "HTTPS traffic successful from WLAN to WAN when Firewall is set to Low"
                } else {
        set failFlag [expr $failFlag + 1];
        puts "HTTPS traffic not successful.Blocked from WLAN to WAN"
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
#Step 5 :Reverting the Firewall configurations back to its initial value.                                                    
##########################################################################################################
}
set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_CISCO_COM_Security.Firewall.FirewallLevel Low string];
puts $output1;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output1] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}


set passContent "Test Result : $result$~";
displayProc $passContent;
