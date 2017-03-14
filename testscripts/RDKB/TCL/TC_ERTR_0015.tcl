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
#TEST CASE ID :TC_ERTR_0015																							    
#Description  :Verify whether WG supports WPA2-PSK with AES encryption security 
#mechanism using valid key for 5GHZ SSID. 
#Ensure that client should be able to connect to WG
                
################################################################################
 }
#Initializing the values to the parameters by invoking Initializer proc
set configFile $argv;
Initializer $configFile;


puts {
################################################################################
#Step 1 :Configuring the Accesspoint with WPA2-PSK with AES encryption                                                                          			 
################################################################################
}


set Radio_index_2 "$ri5";
set SSID_index_2 "$si5";
set radio "";

set radio [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.WiFi.Radio.$ri5.Enable 1 boolean];

puts $radio;
if {[regexp {.*Time limit has crossed 2 minutes.*} $radio] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";	
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
set soutput "";
set soutput [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.WiFi.SSID.$si5.SSID $ssid5 string];

puts $soutput;
if {[regexp {.*Time limit has crossed 2 minutes.*} $soutput] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 2nd parameter";
set result "FAILED";	
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
set voutput "";

set voutput [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetMultipleParameterValues  Device.WiFi.AccessPoint.$si5.Security.X_CISCO_COM_EncryptionMethod,Device.WiFi.AccessPoint.$si5.Security.ModeEnabled AES,WPA2-Personal string,string];

puts $voutput;
if {[regexp {.*Time limit has crossed 2 minutes.*} $voutput] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 3rd parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

set output2 "";

set output2 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.WiFi.AccessPoint.$si5.Security.PreSharedKey wifitest123 string];

puts $output2;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output2] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 4th parameter";
set result "FAILED";	
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;


}
puts {
################################################################################
#Step 2 :Get the values of the parameters that have been set                                                                					 
################################################################################
}
set soutput1 "";
set soutput1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.WiFi.SSID.$si5.SSID null null];

puts $soutput1;
if {[regexp {.*Time limit has crossed 2 minutes.*} $soutput1] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 1st parameter ";
set result "FAILED";	
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
set output3 "";

set output3 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.WiFi.AccessPoint.$si5.Security.ModeEnabled null null];

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
after 30000;
puts {
################################################################################
#Step 3 : Trying to Telnet to WLAN Client
################################################################################
}
spawn telnet $wlanIP $telnetPort
set timeout 100;
expect -re (.*ogin:);
send "$wlanName\r"; 
expect -re (.*word:); 
send "$wlanPassword\r";
expect -re ".*>";
send "netsh wlan add profile filename=\"$profilePath\\Wireless-5GHz.xml\" interface=\"$interface_name1\"\r";
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
send "netsh wlan delete profile name=\"$ssid5\"\r";
expect -re ".*>";
send "exit\r"
expect -re ".*>";
#wait
close $spawn_id

set passFlag "";
set failFlag "";


puts {
################################################################################
#Step 4 :Verifying the 5GHz Wi-Fi Connection Establishment
################################################################################
}

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
#Step 5 :Validating the output and checking for WPA2-PSK security mode		 
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
  
proc commented {} {  
puts {
################################################################################
#Step 6 :Reverting the ModeEnabled and PreSharedKey back to their initial value.                                                               					 
################################################################################
}
set voutput "";
after 30000 {
catch { exec java -cp $ClassPath $Class $oui $SNno $deviceType SetMultipleParameterValues  Device.WiFi.AccessPoint.$si5.Security.X_CISCO_COM_EncryptionMethod,Device.WiFi.AccessPoint.$si5.Security.ModeEnabled AES+TKIP,WPA-WPA2-Personal string,string

} voutput;
}
vwait voutput;
puts $voutput;
if {[regexp {.*Time limit has crossed 2 minutes.*} $voutput] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st  parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
set output6 "";
after 30000 {
catch { exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.WiFi.AccessPoint.$si5.Security.PreSharedKey wifitest123 string } output6;
}
vwait output6;
puts $output6;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output6] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 2nd parameter";	
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
}
set passContent "Test Result : $result";
displayProc $passContent;
