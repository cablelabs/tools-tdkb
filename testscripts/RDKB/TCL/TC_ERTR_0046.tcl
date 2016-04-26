package require Expect;
source proc.tcl;
puts {
######################################################################################################################### 
#TESTCASE ID :TC_ERTR_0046 																						   
#Description  :Verify that MAC address based Access control allows 5GHZ SSID to connect to WG and deny access for 2.4GHZ SSID.       
									
#########################################################################################################################
}
#Initializing the values to the parameters by invoking Initializer proc
set configFile $argv;
Initializer $configFile;

puts {
######################################################################################################################### 
#Step 1 : Allowing access for 5GHZ SSID and denying access for 2.4GHZ SSID                                     					  
#########################################################################################################################
}

set output "";
set output [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.WiFi.AccessPoint.$si2.X_CISCO_COM_MACFilter.Enable true boolean];
puts $output;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
set voutput "";
set voutput [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.WiFi.AccessPoint.$si5.X_CISCO_COM_MACFilter.Enable true boolean];
puts $voutput;
if {[regexp {.*Time limit has crossed 2 minutes.*} $voutput] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 2nd parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.WiFi.AccessPoint.$si2.X_CISCO_COM_MACFilter.FilterAsBlackList false boolean];
puts $output1;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output1] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 3rd parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
set voutput1 "";
set voutput1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.WiFi.AccessPoint.$si5.X_CISCO_COM_MACFilter.FilterAsBlackList true boolean];
puts $voutput1;
if {[regexp {.*Time limit has crossed 2 minutes.*} $voutput1] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 4th parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

spawn telnet $wlanIP;
set timeout 100;
expect -re (.*ogin:);
send "$wlanName\r";
expect -re (.*word:);
send "$wlanPassword\r";
expect -re ".*>";
send "ipconfig /all\r";
expect -re ".*>";
set outIp $expect_out(buffer);
send "exit\r";
expect -re ".*>";
#wait
close $spawn_id

regexp {.*Wireless LAN.*Physical Address.*: ([0-9 A-F]{1,2}-[0-9 A-F]{1,2}-[0-9 A-F]{1,2}-[0-9 A-F]{1,2}-[0-9 A-F]{1,2}-[0-9 A-F]{1,2}).*DHCP Enabled.*Ethernet.*} $outIp match MAC1;

regsub -all {\-} $MAC1 {:} m1;



set output2 "";
set output2 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.WiFi.AccessPoint.$si2.X_CISCO_COM_MACFilter.MACAddress $m1 string];
puts $output2;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output2] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 5th parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
set voutput2 "";
set voutput2 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.WiFi.AccessPoint.$si5.X_CISCO_COM_MACFilter.MACAddress $m1 string];
puts $voutput2;
if {[regexp {.*Time limit has crossed 2 minutes.*} $voutput2] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 6th parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

puts {
################################################################################
#Step 2:Get the values of the parameters that have been set.                                                                  			 
################################################################################
}
set goutput "";
set goutput [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.WiFi.AccessPoint.$si2.X_CISCO_COM_MACFilter.Enable  null null];
puts $goutput;
if {[regexp {.*Time limit has crossed 2 minutes.*} $goutput] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
set goutput1 "";
set goutput1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.WiFi.AccessPoint.$si5.X_CISCO_COM_MACFilter.Enable null null];
puts $goutput1;
if {[regexp {.*Time limit has crossed 2 minutes.*} $goutput1] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 2nd parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
set goutput2 "";
set goutput2 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.WiFi.AccessPoint.$si2.X_CISCO_COM_MACFilter.FilterAsBlackList null null];
puts $goutput2;
if {[regexp {.*Time limit has crossed 2 minutes.*} $goutput2] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 3rd parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
set goutput3 "";
set goutput3 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.WiFi.AccessPoint.$si5.X_CISCO_COM_MACFilter.FilterAsBlackList null null];
puts $goutput3;
if {[regexp {.*Time limit has crossed 2 minutes.*} $goutput3] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 4th parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
set goutput4 "";
set goutput4 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.WiFi.AccessPoint.$si2.X_CISCO_COM_MACFilter.MACAddress null null];
puts $goutput4;
if {[regexp {.*Time limit has crossed 2 minutes.*} $goutput4] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 5th parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
set goutput5 "";
set goutput5 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.WiFi.AccessPoint.$si5.X_CISCO_COM_MACFilter.MACAddress null null];
puts $goutput5;
if {[regexp {.*Time limit has crossed 2 minutes.*} $goutput5] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 6th parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

set interface_name1 [split $wlanInterfaceName "_"];
puts {
######################################################################################################################### 
#Step 3 :Telneting to a WLAN client and trying to connect to the broadcasted SSID.                                                                 					 
#########################################################################################################################
}
#telnet-ing to a WLAN server
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
after 20000
send "ipconfig\r";
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
######################################################################################################################### 
#Step 4 :Checking the connection details by validating the response.                                                               					
#########################################################################################################################
}


if {[regexp {There is no profile "$ssid2" assigned to the specified interface.} $outpCon match] == 1} {

	puts "\nMissing profile. Please ensure that you create a profile and then try connecting";
	#set passFlag [expr $passFlag +1];
	set passContent "Test Result : $result$~";
	displayProc $passContent;
	exit 0;

 } 
	if {[regexp {Connection request was completed successfully.} $outpCon match] == 1} {
	if { [regexp {.*Wireless LAN.*IPv4 Address.*: (.*) Sub.*Ethernet} $outInt match ip] == 1 } {
		
	if {[regexp {169\.254\..*\..*} $ip] == 1 || [regexp {127\.0\.0\.0} $ip] == 1 } {
	
	puts " Unable to obtain IP\n";
		
	} else { 
	
	if {[regexp {10\..*\..*\..*} $ip] == 1} {
	puts "Connection successful for 2.4GHZ SSID";
	puts "IP obtained is: $ip\n";
	
	set failFlag [expr $failFlag + 1];
	 
		}
	}

	
} else {
	 puts "\Connection not successful due to MAC Filter for 2.4GHZ SSID";
	 puts "Unable to obtain IP address"
	 set passFlag [expr $passFlag + 1];
} 	
}


puts {
######################################################################################################################### 
#Step 5 :Telneting to a WLAN client and trying to connect to the broadcasted SSID.                                                                  					 
#########################################################################################################################
}
#telnet-ing to a WLAN server
spawn telnet $wlanIP
set timeout 100;
expect -re (.*ogin:);
send "$wlanName\r"; 
expect -re (.*word:); 
send "$wlanPassword\r";
expect -re ".*>";
send "netsh wlan add profile filename=\"$profilePath\\Wireless-5GHz.xml\" interface=\"Wireless Network Connection $no\"\r";
expect -re ".*>";
send "netsh wlan connect $ssid5\r";
expect -re ".*>";
set outpCon $expect_out(buffer);
after 20000
send "ipconfig\r";
expect -re ".*>";
set outInt $expect_out(buffer);
send "netsh wlan delete profile name=\"$ssid5\"\r";
expect -re ".*>";
send "exit\r"
expect -re ".*>";
#wait
close $spawn_id

puts {
######################################################################################################################### 
#Step 6 :Checking the connection details for the MAC address by validating the response.                                          					
#########################################################################################################################
}
if {[regexp {There is no profile "$ssid5" assigned to the specified interface.} $outpCon match] == 1} {

	puts "\nMissing profile. Please ensure that you create a profile and then try connecting";
	set passContent "Test Result : $result$~";
	displayProc $passContent;
	exit 0;

 } 
	if {[regexp {Connection request was completed successfully.} $outpCon match] == 1} {
	if { [regexp {.*Wireless LAN.*IPv4 Address.*: (.*) Sub.*Ethernet} $outInt match ip] == 1 } {
	if {[regexp {169\.254\..*\..*} $ip] == 1 || [regexp {127\.0\.0\.0} $ip] == 1 } {
	
	puts "Test case failed; Unable to obtain IP\n";
	set failFlag [expr $failFlag + 1];
	
	} else { 
	
	if {[regexp {10\..*\..*\..*} $ip] == 1} {
	puts "Connection Successful for 5GHZ SSID";
	puts "IP obtained : $ip\n";
	set passFlag [expr $passFlag + 1];
	 
		}
	}

	
} else {
	 puts "\Connection not Successful due to MAC filter for 5GHZ SSID";
	 puts "Unable to Obtain IP";
	 set failFlag [expr $failFlag + 1];
} 	
}

if {$passFlag == 2} {
set result "PASSED"	
} else {
	if {$failFlag >0 || $passFlag <2} {
	set result "FAILED";
} 
  }
puts {
######################################################################################################################### 
#Step 7 :Reverting the parameters to its default value                                        					
#########################################################################################################################
}
set soutput "";
set soutput [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.WiFi.AccessPoint.$si2.X_CISCO_COM_MACFilter.Enable false boolean];
puts $soutput;
if {[regexp {.*Time limit has crossed 2 minutes.*} $soutput] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
set loutput "";
set loutput [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.WiFi.AccessPoint.$si5.X_CISCO_COM_MACFilter.Enable false boolean];
puts $loutput;
if {[regexp {.*Time limit has crossed 2 minutes.*} $loutput] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
set passContent "Test Result : $result$~";
displayProc $passContent;






