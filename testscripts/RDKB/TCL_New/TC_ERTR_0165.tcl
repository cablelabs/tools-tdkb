package require Expect;
source proc.tcl;
source lib.tcl
puts {
#########################################################################################################################
#TEST CASE ID :TC_ERTR_0165
#Description  :Verify that on disconnecting a LAN client, Parameter value (Device.Hosts.X_CISCO_COM_ConnectedDeviceNumber) 
#should be decremented accordingly.
#########################################################################################################################
}
#Initializing the values to the parameters by invoking Initializer proc
set configFile $argv;
Initializer $configFile;
set device_param "Device.WiFi.AccessPoint.$si2.Security.ModeEnabled";
set profileType "Wireless.xml";
set wlan_sec_type "wpawpa2-psk";
set ssidName "$ssid2";
set test_radio "2.4ghz";
set no [split $wlanInterfaceName "_"];
puts {
################################################################################
#Step 1 :Configuring the Accesspoint with wpawpa2-psk Security mode
################################################################################
}
set response [config_wlan_sec_wpa2-psk $ClassPath $Class $oui $SNno $deviceType $device_param $test_radio $ssidName $wlan_sec_type $ri2 $si2];
puts "The Result of config_wlan_sec_wpawpa2-psk is $response";
if {![regexp {pass} $response] == 1} {
exit 0;
}
puts {
##########################################################################################################
#Step 2 :Telneting to the WLAN client and obtaining its IP.
##########################################################################################################
}
set profileType "Wireless.xml";
set wlan_sec_type "wpawpa2-psk";
set ssidName "$ssid2";

set response [Configure_Client_open $wlanIP $telnetPort $wlanName $wlanPassword $profilePath $no $profileType $ssidName];

set wireless_pc_ip "$response";
puts "The Result of Configure client proc is $response";
if {![regexp {(\d+)\.(\d+)\.(\d+)\.(\d+)} $response m o] == 1} {
exit 0;
}
puts "$wireless_pc_ip";

puts {
###################################################################################
#Step 3 :Trying to connect to WLAN Client and disable the connect automatic option
###################################################################################
}
spawn telnet $wlanIP $telnetPort;
set timeout 100;
expect -re (.*ogin:);
send "$wlanName\r";
expect -re (.*word:);
send "$wlanPassword\r";
expect -re ".*>";
send "netsh wlan set profileparameter name=$ssidName connectionmode=manual\r";
expect -re ".*>";
send "netsh wlan set profileparameter name=$ssid5 connectionmode=manual\r";
expect -re ".*>";
send "exit\r";
wait
close $spawn_id;

puts {
##########################################################################################################
#Step 4 :Getting the value of number of clients connected in LAN segment through
#TR-181 Parameter.
##########################################################################################################
}
set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.Hosts.X_CISCO_COM_ConnectedDeviceNumber null null];
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
##########################################################################################################
#Step 5 :Disconnecting a WLAN client from the WG
##########################################################################################################
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

after 60000;
#sleep 120;
puts {
#############################################################################################################
#Step 6 :Getting the value of number of clients connected in LAN segment after disconnecting the WLAN Client
#############################################################################################################
}
set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.Hosts.X_CISCO_COM_ConnectedDeviceNumber null null];
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
#Step 7:Checking whether the number of clients connected in LAN segment has decreased after disconnecting
#the WLAN client.
##########################################################################################################
}
incr val2;
if {$val1 == $val2} {
set passFlag [expr $passFlag + 1];
puts "The number of LAN clients has decreased."
} else {
 set failFlag [expr $failFlag + 1];
puts "The number of LAN clients has not decreased."
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
