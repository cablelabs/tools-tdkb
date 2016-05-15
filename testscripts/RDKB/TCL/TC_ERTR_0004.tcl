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
######################################################################################
#TEST CASEID :TC_ERTR_0004 
Description  :Verify whether WG supports WPAWPA2-PSK (TKIP/AES) encryption security 
mechanism using invalid key for 2.4GHZ SSID. 
Ensure that client should not be able to connect to WG             
######################################################################################
}
#Initializing the values to the parameters by invoking Initializer proc
set configFile $argv;
Initializer $configFile;

puts {
##########################################################################################################
#Step 1 :Configuring the Accesspoint with WPA-WPA2-PSK(TKIP/AES) encryption and setting the preshared key                                                                        			 
##########################################################################################################
}

set voutput "";
set voutput [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetMultipleParameterValues  Device.WiFi.AccessPoint.$si2.Security.X_CISCO_COM_EncryptionMethod,Device.WiFi.AccessPoint.$si2.Security.ModeEnabled AES+TKIP,WPA-WPA2-Personal string,string];
puts $voutput;
if {[regexp {.*Time limit has crossed 2 minutes.*} $voutput] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 2nd parameter";
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
#Step 2 :Get the values of the parameters that have been set                                                             					 
################################################################################
}

set output3 "";
set output3 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.WiFi.AccessPoint.$si2.Security.ModeEnabled null null];
puts $output3;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output3] == 1 } {

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
#################################################################
#Step 3 :Trying to connect to WG by telnet-ing to the WLAN client                                                                           			
#################################################################
}
spawn telnet $wlanIP
set timeout 100;
expect -re (.*ogin:);
send "$wlanName\r"; 
expect -re (.*word:); 
send "$wlanPassword\r";
expect -re ".*>";
send "netsh wlan add profile filename=\"$profilePath\\Wireless-invalid.xml\" interface=\"$interface_name1\"\r";
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
send "exit\r"
expect -re ".*>";
#wait
close $spawn_id
set passFlag "";
set failFlag "";
puts {
#################################################################################################################
#Step 4 :Checking whether the CPE is able to connect to the network with the specified SSID and obtain the IP address                                                         					  
#################################################################################################################
}
if {[regexp {There is no profile "$ssid2" assigned to the specified interface.} $outpCon match] == 1} {

	puts "\nMissing profile. Please ensure that you create a profile and then try connecting";
	set result "FAILED";
	set passContent "Test Result : $result$~";
	displayProc $passContent;
	exit 0;

 } 
	if {[regexp {Connection request was completed successfully.} $outpCon match] == 1} {
	if { [regexp {.*Wireless LAN.*IPv4 Address.*: (.*) Sub.*Ethernet} $outIp match ip] == 1 } {
		
	if {[regexp {169\.254\..*\..*} $ip] == 1 || [regexp {127\.0\.0\.0} $ip] == 1 } {
	
	puts " Unable to obtain IP\n";
		
	} else { 
	
	if {[regexp {2001\:.*\:.*\:.*\:.*\:.*\:.*\:.*} $ip] == 1} {
	puts "IP obtained is: $ip\n";
	puts "Failed : Client should not connect successfully"
	set failFlag [expr $failFlag + 1];
	 
		}
	}

	
} else {
	 puts "\Connection not successful due to invalid key";
	 puts "Passed: Unable to obtain IP address"
	 set passFlag [expr $passFlag + 1];
} 	
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
#Step 5 :Reverting the ModeEnabled and PreSharedKey back to their initial value                                                              					 
################################################################################
}
set voutput "";
set voutput [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetMultipleParameterValues  Device.WiFi.AccessPoint.$si2.Security.X_CISCO_COM_EncryptionMethod,Device.WiFi.AccessPoint.$si2.Security.ModeEnabled AES+TKIP,WPA-WPA2-Personal string,string];
puts $voutput;
if {[regexp {.*Time limit has crossed 2 minutes.*} $voutput] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 2nd parameter";
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

set passContent "Test Result : $result$~";
displayProc $passContent;

                                                                        
