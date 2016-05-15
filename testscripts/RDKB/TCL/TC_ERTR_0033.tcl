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
##############################################################################################
#TEST CASE ID :TC_ERTR_0033													  									    
#Description  :Verify whether Network name broadcast(SSID advertisement) can be disabled in WG    								                   
##############################################################################################
 }
 #Initializing the values to the parameters by invoking Initializer proc
set configFile $argv;
Initializer $configFile
puts {
################################################################################
#Step 1 :Configuring the Accesspoint by disabling SSID advertisement                                                                  			 
################################################################################
}


set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.WiFi.AccessPoint.$si2.SSIDAdvertisementEnabled false boolean];
puts $output1;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output1] == 1 } {
puts "\nPossible error:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";	
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

puts {
################################################################################
#Step 2 :Get the values of the parameters that have been set.                                                                			 
################################################################################
}
set output2 "";
set output2 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.WiFi.AccessPoint.$si2.SSIDAdvertisementEnabled null null];
puts $output2;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output2] == 1 } {
puts "\nPossible error:\n1.Device might not be listed\n2.Wrong parameters or 
values\n3.Network connection";
puts "Failed to get 1st parameter";
set result "FAILED";	
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

puts {
################################################################################
#Step 3 :Trying to connect to WG telnet-ing to a WLAN client                                                         			 
################################################################################
}

after 60000; 
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
puts $outpRad;
send "exit\r"
expect -re ".*>";
#wait
set passFlag "";
set failFlag "";

puts {
################################################################################
#Step 4 :Checking the availability of the Network name          					 
################################################################################
}
puts "Expected: Network name $ssid2 should not be broadcasted";
if {[regexp {$ssid2} $outpRad match] == 1} {

set failFlag [expr $failFlag + 1];
puts "\nNetwork name $ssid2 is Broadcasted";
} else {
set passFlag [expr $passFlag + 1];	
puts "\nNetwork name $ssid2 is not Broadcasted"; 
}	
if {$passFlag == 1} {
set result "PASSED";	
} else {
	if {$failFlag >0 || $passFlag <1} {
	set result "FAILED";
} 
  }
 puts {
################################################################################
#Step 5 :Reverting the SSID advertisement to its initial value.                                                            					 
################################################################################
}
set output3 "";
set output3 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.WiFi.AccessPoint.$si2.SSIDAdvertisementEnabled true boolean];
puts $output3;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output3] == 1 } {
puts "\nPossible error:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter"
set result "FAILED";	
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

	
set passContent "Test Result : $result$~";
displayProc $passContent;
