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
puts {
#########################################################################################################################
#TEST CASE ID :TC_ERTR_0191                                                                                                  
#Description  :Verify whether the Operational status of Wireless Gateway got through 
#TR-181 Parameter (Device.X_CISCO_COM_CableModem.CMStatus) matches with the actual status of WG. (OPERATIONAL)
#########################################################################################################################
}
#Initializing the values to the parameters by invoking Initializer proc
set configFile $argv;
Initializer $configFile;
puts {
#########################################################################################################
#Step 1 :Getting the value of operational status of the Wireless Gateway through TR-181 Parameter.                 
##########################################################################################################
}
set output1 "";

set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_CISCO_COM_CableModem.CMStatus null null];
puts $output1;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output1] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
} 
regexp {.*VALUE:(.*) .*TYPE} $output1 match val;

puts $val;


puts {
##########################################################################################################
#Step 2 :Checking whether the LAN client is able to ping to the Gateway, when it is in operational status           
##########################################################################################################
}
if {[string compare $val "OPERATIONAL"] == 0} {
spawn telnet $Telnetip;
set timeout 100;
expect -re (.*ogin:);
send "$Name\r";
expect -re (.*word:);
send "$password\r";
expect -re ".*#";
send "ping -c 4 10.0.0.1\r";
expect -re ".*#";
set outPing $expect_out(buffer);
#wait
close $spawn_id
set passFlag "";
set failFlag "";
} else {
puts "Gateway status is not operational"
}

if {[regexp {.*4 packets transmitted.* (.*)% packet loss.*} $outPing match lossPercent] == 1} {
        if {$lossPercent == 0} {
        set passFlag [expr $passFlag + 1];
        puts "Ping successful from LAN client to Gateway when Gateway is operational"
        } else {
        set failFlag [expr $failFlag + 1];
        puts "Ping not successful.Blocked from LAN client to Gateway"

        }
}

if {$passFlag == 1} {
set result "PASSED"
} else {
        if {$failFlag >0 || $passFlag <1} {
        set result "FAILED";
}
  }

  
set passContent "Test Result : $result$~";
displayProc $passContent;


