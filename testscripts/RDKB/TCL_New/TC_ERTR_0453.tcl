package require Expect;
source proc.tcl;
source lib.tcl;

#Initializing the values to the parameters by invoking Initializer proc
set configFile $argv;
Initializer $configFile;

puts {
#####################################################################################

TESTCASEID : TC_ERTR_0453                                                                                    
Description : Verify that TCP Traffic should be successfull with destination as
              wired client and source as wireless client  where client association 
              in wpawpa2-psk security wlan on 5ghz band with firewall set to None.

#####################################################################################
 }

set device_param "Device.WiFi.AccessPoint.$si5.Security.ModeEnabled";
set profileType "Wireless-5GHz.xml";
set wlan_sec_type "wpawpa2-psk";
set ssidName "$ssid5";
set test_radio "5ghz";
set ri "$ri5";
set si "$si5";


puts {
################################################################################
#Step  : Configuring the firewall to None
################################################################################
}


set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_CISCO_COM_Security.Firewall.FirewallLevel None string];
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
################################################################################
#Step 1 :Configuring the Accesspoint with $wlan_sec_type Secuirty mode                                                                        
################################################################################
}
puts "$ClassPath";
set response [config_wlan_sec_wpa2-psk $ClassPath $Class $oui $SNno $deviceType $device_param $test_radio $ssidName $wlan_sec_type $ri $si];
puts "The Result of config_wlan_sec_wpawpa2-psk is $response";
if {![regexp {pass} $response] == 1} {
exit 0;
}
puts {
#################################################################################################################
#Step 2 :Trying to telnet to WLAN Client and associate wirelessly for wpawpa2-psk security                                    
#################################################################################################################
} 

set response [Configure_Client_open $wlanIP $telnetPort $wlanName $wlanPassword $profilePath $no $profileType $ssidName];

set wireless_pc_ip "$response";
puts "The Result of Configure client proc is $response";
if {![regexp {(\d+)\.(\d+)\.(\d+)\.(\d+)} $response m o] == 1} {
exit 0;
}
puts "$wireless_pc_ip";
 

###############################################################################
#step 3: Telnet to LAN Client and obtain its IP address
###############################################################################
set response [connect_lan_pc $Telnetip $telnetPort1 $Name $password $osName1];
set wired_pc_ip "$response";
puts "The Result of connect_lan_pc is $response";  
if {![regexp {(\d+)\.(\d+)\.(\d+)\.(\d+)} $response m o] == 1} {
exit 0;
}


puts {
################################################################################
#Step 4 : Initializing LAN Client as server using iperf
################################################################################
}

spawn telnet $Telnetip $telnetPort1
set timeout 100;
expect -re (.*ogin:);
send "$Name\r";
expect -re (.*word:);
send "$password\r";
expect -re ".*#";

send -i $spawn_id "iperf -s --remove\r";
expect -re ".*Server";

send "\003";
expect -re ".*#";
send -i $spawn_id "iperf -s > output123.txt & \r";
expect -re ".*#";
close $spawn_id;

puts {
################################################################################
#Step 5 :Sending TCP packets from WLAN Client using iperf
################################################################################
}
spawn telnet $wlanIP $telnetPort
set timeout 100;
expect -re (.*ogin:);
send "$wlanName\r";
expect -re (.*word:);
send "$wlanPassword\r";
expect -re ".*>";

send "iperf -s --remove\r";
expect -re ".*Server";

send "\003";
expect -re ".*>";
send "iperf -c $wired_pc_ip\r";
expect -re ".*>";
set clientoutput $expect_out(buffer);
close $spawn_id;



puts {
################################################################################
#Step 6 :Validating the Client Output                                                                                      
################################################################################
}
if { [ regexp {.*Client .* MBytes\s(.*)} $clientoutput match cbandwidth] == 1 } {
puts "Client bandwidth is $cbandwidth";
set result "PASSED";

} else { set result "FAILED";
}


puts {
################################################################################
#Step 7 :Validating the Server Output                                                                                      
################################################################################
}
spawn telnet $Telnetip $telnetPort1
set timeout 100;
expect -re (.*ogin:);
send "$Name\r";
expect -re (.*word:);
send "$password\r";
expect -re ".*#";
send -i $spawn_id "cat output123.txt\r";
expect -re ".*#";
set serverOutput "$expect_out(buffer)";
if { [ regexp {.*Server .* MBytes\s(.*)} $serverOutput match sbandwidth] == 1 } {

puts "Server side bandwidth is $sbandwidth";
set result "PASSED";


} else { set result "FAILED";
}
if { $sbandwidth >= $cbandwidth } {
set result "PASSED";
} else { set result "FAILED";
}


puts $result;


set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_CISCO_COM_Security.Firewall.FirewallLevel Custom string];
puts $output1;


#set response [config_wlan_sec_wpa2-psk $ClassPath $Class $oui $SNno $deviceType $device_param $test_radio $ssidName "wpawpa2-psk" $ri $si];
#puts "The Result of config_wlan_sec_wpawpa2-psk is $response";


set passContent "Test Result : $result";
displayProc $passContent;




