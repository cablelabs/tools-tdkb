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
##########################################################################################################################################
#TEST CASEID :TC_ERTR_0189
#Description  :Verify that on enabling bridge mode, both Private SSIDs on 2.4 & 5 GHz should not be broadcasted
##########################################################################################################################################
}
#Initializing the values to the parameters by invoking Initializer proc
set configFile $argv;
Initializer $configFile;


puts {
################################################################################
#Step 1 :Enabling the bridge mode.
################################################################################
}

set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_CISCO_COM_DeviceControl.LanManagementEntry.1.LanMode bridge-static string];
puts $output1;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output1] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
} 

set output2 "";
set output2 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_CISCO_COM_DeviceControl.LanManagementEntry.1.LanMode null null];
puts $output2;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output2] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

sleep 120;

puts { 
################################################################################## 
#Step 2 :Telnet-ing to a WLAN client and checking the Private SSIDs                                                      
################################################################################## 
} 

spawn telnet $wlanIP 
set timeout 100; 
expect -re (.*ogin:); 
send "$wlanName\r";  
expect -re (.*word:);  
send "$wlanPassword\r"; 
expect -re ".*>";
match_max 50000;
send "netsh wlan show networks\r";
expect -re ".*>";
set outpRad $expect_out(buffer);
send "exit\r"
expect -re ".*>";
#wait 

close $spawn_id
set passFlag ""; 
set failFlag "";

puts {
################################################################################ 
#Step 3 :Checking the availability of the Network names                                                    
################################################################################
} 
puts "Expected: Network name \"RDKB-2.4\" and \"RDKB-5\"  should not be broadcasted";
if { [regexp {RDKB-2.4} $outpRad] == 1 && [regexp {RDKB-5} $outpRad] == 1 } { 
set failFlag [expr $failFlag + 1];       
puts "\nObtained: Network name \"RDKB-2.4\" and \"RDKB-5\" is broadcasted on the network";
} else { 
set passFlag [expr $passFlag + 1];
puts "\nObtained: Network name \"RDKB-2.4\" and \"RDKB-5\" is not broadcasted on the network";
}         

if {$passFlag == 1} { 
set result "PASSED"      
} else { 
        if {$failFlag >0 || $passFlag <1} { 
        set result "FAILED"; 
} 
}  


puts {
################################################################################
#Step 4 :Reverting the the bridge mode to its default value.
################################################################################
}

set output2 "";
set output2 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_CISCO_COM_DeviceControl.LanManagementEntry.1.LanMode router string];
puts $output2;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output2] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

sleep 100;

set passContent "Test Result : $result$~";
displayProc $passContent;



