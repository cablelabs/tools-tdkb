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
######################################################################################################################### 
#TEST CASE ID :TC_ERTR_0054																							    
#Description  :Verify that when Firewall Config is set to High, Telnet access from LAN to LAN  should be allowed

#########################################################################################################################
} 
#Initializing the values to the parameters by invoking Initializer proc
set configFile $argv;
Initializer $configFile;

puts {
##########################################################################################################
#Step 1 :Setting the firewall in high mode.                                                                       			 
##########################################################################################################
}
set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_CISCO_COM_Security.Firewall.FirewallLevel High string];
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
set output2 "";
set output2 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_CISCO_COM_Security.Firewall.FirewallLevel null null];
puts $output2;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output2] == 1 } {

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
#Step 3 :Trying to Telnet to WLAN Client
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
set outpCon $expect_out(buffer); 
after 30000;
send "ipconfig\r";
expect -re ".*>";
set outIp $expect_out(buffer);
regexp {.*Wireless LAN.*IPv4 Address.*: ([0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}).*Subnet.*Ethernet.*} $outIp match Ipval;
send "exit\r";
puts "$Ipval";
#wait 
close $spawn_id
 
set passFlag ""; 
set failFlag "";



puts { 
################################################################################ 
#Step 4 :Verifying the connection to the proper SSID                                                
################################################################################ 
} 
 
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
         
	} elseif {[regexp {10\.0\.0\..*} $ip] == 1} {
        puts "Connection Successful";
        puts "IP obtained is: $ip\n";
        puts "IP address obtained within the Default DHCP server range";
        set passFlag [expr $passFlag + 1];
        } else {
        puts "IP obtained is: $ip\n";
        puts "IP address not obtained within the Default DHCP server range";
        }
 
         
} else { 
         puts "\IP address not obtained."; 
         set failFlag [expr $failFlag + 1]; 
}        
} else { 
         puts "\Connection not successful."; 
         set failFlag [expr $failFlag + 1]; 
}  




puts {
################################################################################
#Step 5 :Trying to Telnet to LAN Client                                                                                
################################################################################
} 
spawn telnet $Telnetip;
set timeout 100;
expect -re (.*ogin:);
send "$Name\r";
expect -re (.*word:);
send "$password\r";
expect -re ".*#";
send "telnet $Ipval\r";
set timeout 100;
expect -re (.*ogin:);
send "$wlanName\r";
expect -re (.*word:);
send "$wlanPassword\r";
expect -re ".*>";
set outTelnet $expect_out(buffer);
send "exit\r";
expect -re ".*#";
send "telnet $wlanIP\r";
set timeout 100;
expect -re (.*ogin:);
send "$wlanName\r";
expect -re (.*word:);
send "$wlanPassword\r";
expect -re ".*>";
send "netsh wlan delete profile name=\"$ssid2\"\r";
expect -re ".*>";
send "exit\r";


 

#wait
close $spawn_id;
set passFlag "";
set failFlag "";




puts {
############################################################################################
#Step 6 :Verifying the telnet access from LAN to LAN                                            
############################################################################################
}

if {[regexp {.*Microsoft.*} $outTelnet match] == 1 } {
        set passFlag [expr $passFlag + 1];
        puts "Telnet Request successful from LAN to LAN when Firewall is set to High" 
		} else { 


set failFlag [expr $failFlag + 1];
        puts "Telnet Request not successful from LAN to LAN when firewall is set to High"
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
#Step 7 :Reverting the Firewall configurations back to its initial value.                                                                        			 
##########################################################################################################
}

set output3 "";
set output3 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_CISCO_COM_Security.Firewall.FirewallLevel Low string];
puts $output3;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output3] == 1 } {
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";	
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}  
set passContent "Test Result : $result$~";
displayProc $passContent;
