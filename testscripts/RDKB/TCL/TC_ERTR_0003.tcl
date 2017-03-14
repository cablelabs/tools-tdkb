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
################################################################################
#TEST CASEID :TC_ERTR_0003 
Description  :Verify whether WG supports WPAWPA2-PSK (TKIP/AES)encryption security 
mechanism using valid key for 2.4GHZ SSID.  
Ensure that client should be able to connect to WG       
################################################################################
 }
#Initializing the values to the parameters by invoking Initializer proc
set configFile $argv;
Initializer $configFile;

puts {
################################################################################
#Step 1 :Configuring the Accesspoint with WPA-WPA2-PSK (TKIP/AES) encryption                                                                          			 
################################################################################
}
set voutput "";
set voutput [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetMultipleParameterValues  Device.WiFi.AccessPoint.$si2.Security.X_CISCO_COM_EncryptionMethod,Device.WiFi.AccessPoint.$si2.Security.ModeEnabled AES+TKIP,WPA-WPA2-Personal string,string];
puts $voutput;
if {[regexp {.*Time limit has crossed 2 minutes.*} $voutput] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

set output2 "";
set output2 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.WiFi.AccessPoint.$si2.Security.PreSharedKey wifitest123 string];
puts $output2;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output2] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 2nd parameter";
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

set voutput1 "";
set voutput1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.WiFi.SSID.$si2.SSID null null];
puts $voutput1;
if {[regexp {.*Time limit has crossed 2 minutes.*} $voutput1] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 1st parameter ";
set result "FAILED";	
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
set output3 "";
set output3 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.WiFi.AccessPoint.$si2.Security.ModeEnabled null null];
puts $output3;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output3] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 2nd parameter ";
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
spawn telnet $wlanIP $telnetPort
set timeout 100;
expect -re (.*ogin:);
send "$wlanName\r"; 
expect -re (.*word:); 
send "$wlanPassword\r";
expect -re ".*>";
send "netsh wlan add profile filename=\"$profilePath\\Wireless.xml\" interface=\"$interface_name1\" user=all\r";
expect -re ".*>";
send "netsh wlan connect $ssid2\r";
expect -re ".*>";
set outpCon $expect_out(buffer);
after 30000
send "ipconfig\r";
expect -re ".*>";
set outIp $expect_out(buffer);
send "netsh wlan show interfaces\r";
expect -re ".*>";
set outInt $expect_out(buffer);
send "netsh wlan delete profile name=\"$ssid2\"\r";
expect -re ".*>";
send "exit\r"
expect -re ".*>";
#wait
close $spawn_id

set passFlag "";
set failFlag "";


puts {
################################################################################
#Step 4 :Verifying the 2.4GHz Wi-Fi Connection Establishment	 		
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
#Step 5 :Validating the output and checking for WPA/WPA2 security mode		 
################################################################################
}
if {[regexp { .*There.*Channel.*: (.*) Rec} $outInt match channel] == 1 } {
	
	if { $channel >= 1 && $channel <= 11 } {
	puts "Client connected to WG successfully through channel number $channel";
	puts "Operating frequency band : 2.4GHZ"	
	} else {
	if { $channel > 11 } {
	puts "Client connected to WG successfully through channel number $channel";
	puts "Operating frequency band : 5GHZ"
		}
	}
 }

if {[regexp {.*There.*Authentication.*: (.*) Cip} $outInt match opauth] == 1 } {
	puts "Expected Mode : 'WPA2-Personal' or 'WPA-Personal'";
	if {[regexp {WPA2-Personal} $opauth match] == 1 || [regexp {WPA-Personal} $opauth match] == 1} {
	puts "Obtained Mode :  $opauth";
	puts "Authentication mode is matching";
	set passFlag [expr $passFlag + 1];
	} else {
	puts "Authentication mode not matching";
	set failFlag [expr $failFlag + 1];
		}
  }

if {$passFlag == 4} {
set result "PASSED"	
} else {
	if {$failFlag >0 || $passFlag <4} {
	set result "FAILED";
} 
  }
   	
puts {
################################################################################
#Step 6: Reverting back to its default values
################################################################################
}
set voutput "";
set voutput [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetMultipleParameterValues  Device.WiFi.AccessPoint.$si2.Security.X_CISCO_COM_EncryptionMethod,Device.WiFi.AccessPoint.$si2.Security.ModeEnabled AES+TKIP,WPA-WPA2-Personal string,string];
puts $voutput;
if {[regexp {.*Time limit has crossed 2 minutes.*} $voutput] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

set output6 "";
set output6 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.WiFi.AccessPoint.$si2.Security.PreSharedKey wifitest123 string];
puts $output6;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output6] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 2nd parameter";	
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}


set passContent "Test Result : $result";
displayProc $passContent;



