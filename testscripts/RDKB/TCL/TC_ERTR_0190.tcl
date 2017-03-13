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
puts {
##########################################################################################################################################
#TEST CASEID :TC_ERTR_0190
#Description  :Verify that on disabling bridge mode, both Private SSIDs on 2.4 & 5 GHz should be broadcasted
##########################################################################################################################################
}
#Initializing the values to the parameters by invoking Initializer proc
set configFile $argv;
Initializer $configFile;


puts {
################################################################################
#Step 1 :Disabling the bridge mode.
################################################################################
}

set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_CISCO_COM_DeviceControl.LanManagementEntry.1.LanMode router string];
puts $output1;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output1] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
} 

sleep 100;

puts { 
################################################################################ 
#Step 2 :Telnet-ing to a WLAN client and checking the Private SSIDs
################################################################################ 
} 
spawn telnet $wlanIP $telnetPort 
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
puts "Expected: Network name \"$ssid2\" and \"$$ssid5\"  should be broadcasted";
if { [regexp "$ssid2" $outpRad] == 1 && [regexp "$ssid5" $outpRad] == 1 } { 
set passFlag [expr $passFlag + 1];       
puts "\nObtained: Network name \"$ssid2\" and \"$ssid5\" is broadcasted on the network";
} else { 
set failFlag [expr $failFlag + 1];
puts "\nObtained: Network name \"$ssid2\" and \"$ssid5\" is not broadcasted on the network";
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



