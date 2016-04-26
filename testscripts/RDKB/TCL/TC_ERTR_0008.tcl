package require Expect;
source proc.tcl;
puts {
######################################################################################################################### 
#TEST CASE ID:TC_ERTR_0008														
#Description  :Verify that Channel number of WLAN radio(2.4GHZ) can be updated in Wireless Gateway										
#########################################################################################################################
 }
#Initializing the values to the parameters by invoking Initializer proc
set configFile $argv;
Initializer $configFile;


puts {
######################################################################################################################### 
#Step 1 :Configuring the Wireless Gateway with the specified Channel number                                            						  
#########################################################################################################################
}
puts $ri2;
set voutput "";
set voutput [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.WiFi.Radio.$ri2.AutoChannelEnable false boolean ];
puts $voutput;
if {[regexp {.*Time limit has crossed 2 minutes.*} $voutput] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";	
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

set output1 "";

set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.WiFi.Radio.$ri2.Channel 6 unsignedInt];

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
######################################################################################################################### 
#Step 2 :Get the values of the parameters that have been set                                                          
#########################################################################################################################
}

set voutput2 "";

set voutput2 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.WiFi.Radio.$ri2.AutoChannelEnable null null];
puts $voutput2;
if {[regexp {.*Time limit has crossed 2 minutes.*} $voutput2] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";	
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
set output2 "";
set output2 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.WiFi.Radio.$ri2.Channel null null];
puts $output2;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output2] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 1st parameter ";
set result "FAILED";	
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
after 60000;
set interface_name1 [split $wlanInterfaceName "_"];
puts {
######################################################################################################################### 
#Step 3 :Trying to connect to WG  Telneting to a WLAN Client                                                            
#########################################################################################################################
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
after 20000;
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
######################################################################################################################### 
#Step 4 :Checking whether the CPE is able to connect to the network with the specified SSID and obtain the IP address.                                                               					
#########################################################################################################################
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
	
	} else { 
	
	if {[regexp {10\..*\..*\..*} $ip] == 1} {
	puts "Connection Successful"
	puts "IP obtained is: $ip\n";
	set passFlag [expr $passFlag + 1];
	 
		}
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
#Step 5 :Validating the output and checking for correct channel number
################################################################################
}
if {[regexp { .*There.*Channel.*: (.*) Rec} $outInt match channel] == 1 } {
	puts "Expected Channel number : '6'"
	if {[regexp {6} $channel match] == 1} {
	puts "Obtained Channel number :  $channel."
	set passFlag [expr $passFlag + 1];	
	} else {
	puts "Obtained Channel number :  $channel."
	puts "Channel number does not match"
	set failFlag [expr $failFlag +1];
	}
 }
if {$passFlag == 4} {
set result "PASSED";	
} else {
	if {$failFlag >0 || $passFlag <4} {
	set result "FAILED";
} 
  }

puts {
################################################################################
#Step 6:Reverting the Autochannel enable to its default value.                                                               					 
################################################################################
}
set voutput1 "";

set voutput1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.WiFi.Radio.$ri2.AutoChannelEnable true boolean];
puts $voutput1;
if {[regexp {.*Time limit has crossed 2 minutes.*} $voutput1] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";	
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
set passContent "Test Result : $result$~";
displayProc $passContent;
