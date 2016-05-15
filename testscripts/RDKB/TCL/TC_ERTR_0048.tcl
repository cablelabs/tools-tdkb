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
######################################################################################################################### 
#TEST CASE ID :TC_ERTR_0048																							    
#Description  :Verify that signal strength at wireless client machine changes according to transmit power settings ( Device.WiFi.Radio.$ri2.TransmitPower)  in WG

#########################################################################################################################
 }
#Initializing the values to the parameters by invoking Initializer proc
set configFile $argv;
Initializer $configFile;
puts {
################################################################################
#Step 1 :Reverting the Transmit Power for 2.4GHz to its initial value.                                                                                      
################################################################################
}

set output3 "";
set output3 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.WiFi.Radio.$ri2.TransmitPower 100 int];
puts $output3;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output3] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
puts {
######################################################################################################################### 
#Step 2 :Get the value of Transmit Power for 2.4GHz radio.                                                                         			 
#########################################################################################################################
}

set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.WiFi.Radio.$ri2.TransmitPower null null];
puts $output1;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output1] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 1st parameter ";
set result "FAILED";	
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
set interface_name1 [split $wlanInterfaceName "_"];
after 45000;

puts { 
######################################################################################################################### 
#Step 3 :Trying to connect to WG telnet-ing to a WLAN client                                                              					
#########################################################################################################################
}
spawn telnet $wlanIP
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
after 20000
send "ipconfig\r";
expect -re ".*>";
set outIp $expect_out(buffer);
send "netsh wlan show interfaces\r";
expect -re ".*>";
set outInt $expect_out(buffer);
send "netsh wlan delete profile name=\"$ssid2\"\r";
expect -re ".*>";
#wait
close $spawn_id;
set passFlag1 "";
set failFlag1 "";
puts {
######################################################################################################################### 
#Step 4 :Checking whether the CPE is able to connect to the network with the specified SSID and obtain the IP address.                                                               					 
#########################################################################################################################
}
if {[regexp {There is no profile "$ssid2" assigned to the specified interface.} $outpCon match] == 1} {

	puts "\nMissing profile. Please ensure that you create a profile and then try connecting";
	set failFlag1 [expr $failFlag1 + 1];
	set passContent "Test Result : $result$~";
	displayProc $passContent;
	exit 0;
	
	} 
	if {[regexp {Connection request was completed successfully.} $outpCon match] == 1} {
	set passFlag1 [expr $passFlag1 + 1];
	if { [regexp {.*Wireless LAN.*IPv4 Address.*: (.*) Sub.*Ethernet} $outIp match ip] == 1 } {
	set passFlag1 [expr $passFlag1 + 1];	
	if {[regexp {169\.254\..*\..*} $ip] == 1 || [regexp {127\.0\.0\.0} $ip] == 1 } {
	
	puts "Test case failed; Unable to obtain IP\n";
	set failFlag1 [expr $failFlag1 + 1];
	
	} else { 
	
	if {[regexp {10\..*\..*\..*} $ip] == 1} {
	puts "Connection Successful";
	puts "Obtained IP obtained is: $ip\n";
	set passFlag1 [expr $passFlag1 + 1];
	 
		}
	}

	
} else {
	 puts "\Connection not Successful";
	 set failFlag1 [expr $failFlag1 + 1];
} 	
}

puts {
######################################################################################################################### 
#Step 5 :Getting the value of the signal strength in a variable.                                                              					 
#########################################################################################################################
}
if {$passFlag1 == 3} {
regexp {.*There.*Signal.*: ([0-9]{1,3}).*Pro} $outInt match signal1;
puts "Signal Strength: $signal1"
}
puts {
######################################################################################################################### 
#Step 6 :Setting the Transmit Power for 2.4GHz Radio to 25                                                             					 
#########################################################################################################################
}

set output2 "";
set output2 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.WiFi.Radio.$ri2.TransmitPower 25 int];
puts $output2;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output2] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";	
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
after 45000;
puts { 
######################################################################################################################### 
#Step 7 :Trying to connect to CM telnet-ing to a WLAN server                                                              					 
#########################################################################################################################
}
spawn telnet $wlanIP
set timeout 100;
expect -re (.*ogin:);
send "$wlanName\r"; 
expect -re (.*word:); 
send "$wlanPassword\r";
expect -re ".*>";
send "netsh wlan add profile filename=\"$profilePath\\Wireless.xml\" interface=\"Wireless Network Connection $no\" user=all\r";
expect -re ".*>";
send "netsh wlan connect $ssid2\r";
expect -re ".*>";
set outpCon $expect_out(buffer);
after 20000
send "ipconfig\r";
expect -re ".*>";
set outIp $expect_out(buffer);
send "netsh wlan show interfaces\r";
expect -re ".*>";
set outInt $expect_out(buffer);
send "netsh wlan delete profile name=\"$ssid2\"\r";
expect -re ".*>";
#wait
close $spawn_id;
set passFlag2 "";
set failFlag2 "";
puts {
######################################################################################################################### 
#Step 8 :Checking whether the CPE is able to connect to the network with the specified SSID and obtain the IP address.                                                               					
#########################################################################################################################
}
if {[regexp {There is no profile "$ssid2" assigned to the specified interface.} $outpCon match] == 1} {

	puts "\nMissing profile. Please ensure that you create a profile and then try connecting";
	set failFlag2 [expr $failFlag2 + 1];
	set passContent "Test Result : $result$~";
	displayProc $passContent;
	exit 0;
	
	} 
	if {[regexp {Connection request was completed successfully.} $outpCon match] == 1} {
	set passFlag2 [expr $passFlag2 + 1];
	if { [regexp {.*Wireless LAN.*IPv4 Address.*: (.*) Sub.*Ethernet} $outIp match ip] == 1 } {
	set passFlag2 [expr $passFlag2 + 1];	
	if {[regexp {169\.254\..*\..*} $ip] == 1 || [regexp {127\.0\.0\.0} $ip] == 1 } {
	
	puts "Test case failed; Unable to obtain IP\n";
	set failFlag2 [expr $failFlag2 + 1];
	
	} else { 
	
	if {[regexp {10\..*\..*\..*} $ip] == 1} {
	puts "Connection Successful";
	puts "Obtained IP obtained is: $ip\n";
	set passFlag2 [expr $passFlag2 + 1];
	 
		}
	}

	
} else {
	 puts "\Connection not Successful";
	 set failFlag2 [expr $failFlag2 + 1];
} 	
}

puts {
######################################################################################################################### 
#Step 9 :Getting the value of the signal strength in a variable.                                                              					 
#########################################################################################################################
}
if {$passFlag2 == 3} {
regexp {.*There.*Signal.*: ([0-9]{1,3}).*Pro} $outInt match signal2;
puts "Signal Strength: $signal2"
}
puts {
######################################################################################################################### 
#Step 10 :Checking whether the signal strength has reduced by reducing the transmitting power.                                                              					 
#########################################################################################################################
}
set passFlag3 "";
puts "Initial Signal Strength: $signal1";
puts "Final Signal Strength: $signal2"
if {[expr $signal2 < $signal1] == 1} {
	set passFlag3 [expr $passFlag3 + 1];	
	puts "Signal Strength is varying"
} else {
	puts "Signal Strength is not varying"
} 
if {$passFlag3 == 1} {
set result "PASSED";	
} else {
set result "FAILED";	
}
puts {
################################################################################
#Step 11 :Reverting the Transmit Power for 2.4GHz to its initial value.                                                               					 
################################################################################
}

set output3 "";
set output3 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.WiFi.Radio.$ri2.TransmitPower 100 int];
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
