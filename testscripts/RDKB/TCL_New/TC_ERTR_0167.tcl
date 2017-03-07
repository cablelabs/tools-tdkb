 package require Expect;
source proc.tcl;
puts {
#########################################################################################################################
#TEST CASE ID :TC_ERTR_0167                                                                                                  
#Description  :Verify that on disconnecting a Wireless Client through 2.4 GHz radio, value of parameter 
#(Device.WiFi.AccessPoint.$si2.AssociatedDeviceNumberOfEntries) should be decremented accordingly
#########################################################################################################################
}
#Initializing the values to the parameters by invoking Initializer proc
set configFile $argv;
Initializer $configFile;
set interface_name1 [split $wlanInterfaceName "_"];
puts {
##########################################################################################################
#Step 1 :Connecting the WLAN client to WG
##########################################################################################################
}

spawn telnet $wlanIP $telnetPort;
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
after 30000;
send "exit\r";
wait
close $spawn_id;

puts {
##########################################################################################################
#Step 2 :Getting the value of number of clients connected in WLAN segment through TR-181 Parameter
##########################################################################################################
}
set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.WiFi.AccessPoint.$si2.AssociatedDeviceNumberOfEntries null null];
puts $output1;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output1] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
} 
regexp {.*VALUE:(.*) TYPE.*} $output1 match val1;

puts {
################################################################################
#Step 3 :Trying to disconnect WLAN Client from WG
################################################################################
}
spawn telnet $wlanIP $telnetPort;
set timeout 100;
expect -re (.*ogin:);
send "$wlanName\r";
expect -re (.*word:);
send "$wlanPassword\r";
expect -re ".*>";
send "netsh wlan delete profile name=\"$ssid2\"\r";
expect -re ".*>";
after 30000;
send "exit\r";
wait
close $spawn_id;
set passFlag "";
set failFlag "";
puts {
##########################################################################################################
#Step 4 :Getting the value of number of clients connected in LAN segment through 
#TR-181 Parameter after disconnecting WLAN client
##########################################################################################################
}
set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.WiFi.AccessPoint.$si2.AssociatedDeviceNumberOfEntries null null];
puts $output1;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output1] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
} 
regexp {.*VALUE:(.*) TYPE.*} $output1 match val2;

puts {
##########################################################################################################
#Step 5 :Checking whether the number of clients connected in WLAN segment has decreased after connecting 
#the wireless client.                                                                                  
##########################################################################################################
}
incr val2;
if {$val1 == $val2} {
set passFlag [expr $passFlag + 1];
puts "The number of WLAN clients has decreased."
} else {
 set failFlag [expr $failFlag + 1];
puts "The number of WLAN clients has not decreased."
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

