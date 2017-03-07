package require Expect;
source proc.tcl;
source lib.tcl;
puts {
#####################################################################################				
TESTCASEID : TC_ERTR_0140 to TC_ERTR_0145																							    
Description  :Verify whether FTP transfer is successfull from wired to wireless clients.
Ensure that client should be able to connect to WG   
          
#####################################################################################
 }
#Initializing the values to the parameters by invoking Initializer proc
#set configFile $argv;
set script_args $argv;
puts "Script arguments are $script_args";
set no_script_args $argc;
puts "Number of Script arguments are $no_script_args";
set configFile [lindex $script_args 0];
set logical_id [lindex $script_args 1];
puts "The config file is $configFile";
puts "The logical id is $logical_id";
puts "TESTCASEID : $logical_id";
Initializer $configFile;



########################Logical id Check###############################

if {[regexp -nocase {TC_ERTR_0140} $logical_id]} {
set device_param "Device.WiFi.AccessPoint.$si2.Security.ModeEnabled";
set wlan_sec_type "open";
set profileType "Wireless-open-2.4.xml";
set ssidName "$ssid2";
set test_radio "2.4ghz";
set ri "$ri2";
set si "$si2";
} elseif {[regexp -nocase {TC_ERTR_0141} $logical_id]} {
set device_param "Device.WiFi.AccessPoint.$si5.Security.ModeEnabled";
set profileType "Wireless-open-5.xml";
set wlan_sec_type "open";
set ssidName "$ssid5";
set test_radio "5ghz";
set ri "$ri5";
set si "$si5";
} elseif {[regexp -nocase {TC_ERTR_0142} $logical_id]} {
set device_param "Device.WiFi.AccessPoint.$si2.Security.ModeEnabled";
set profileType "Wireless.xml";
set wlan_sec_type "wpa2-psk";
set ssidName "$ssid2";
set test_radio "2.4ghz";
set ri "$ri2";
set si "$si2";
} elseif {[regexp -nocase {TC_ERTR_0143} $logical_id]} {
set device_param "Device.WiFi.AccessPoint.$si5.Security.ModeEnabled";
set profileType "Wireless-5GHz.xml";
set wlan_sec_type "wpa2-psk";
set ssidName "$ssid5";
set test_radio "5ghz";
set ri "$ri5";
set si "$si5";

} elseif {[regexp -nocase {TC_ERTR_0144} $logical_id]} {
set device_param "Device.WiFi.AccessPoint.$si2.Security.ModeEnabled";
set profileType "Wireless.xml";
set wlan_sec_type "wpawpa2-psk";
set ssidName "$ssid2";
set test_radio "2.4ghz";
set ri "$ri2";
set si "$si2";

} elseif {[regexp -nocase {TC_ERTR_0145} $logical_id]} {
set device_param "Device.WiFi.AccessPoint.$si5.Security.ModeEnabled";
set profileType "Wireless-5GHz.xml";
set wlan_sec_type "wpawpa2-psk";
set ssidName "$ssid5";
set test_radio "5ghz";
set ri "$ri5";
set si "$si5";

} else {
puts "Logical Id Mismatches";
exit 0;
}
puts "The device tr69 parameter of $logical_id is $device_param";
set no [split $wlanInterfaceName "_"];
puts $no;
puts {
################################################################################
#Step 1 :Configuring the Accesspoint with $wlan_sec_type Security mode                                                 
################################################################################
}
puts "$ClassPath";
if {[regexp -nocase {open} $wlan_sec_type]} { 
#set response [device_set_get_param $ClassPath $Class $oui $SNno $deviceType SetParameterValue $device_param None string];
#puts "The Result of Setparameter is $response";

set response [config_wlan_sec_open $ClassPath $Class $oui $SNno $deviceType $device_param $test_radio $ssidName $ri $si];
puts "The Result of config_wlan_sec_open is $response";
if {![regexp {pass} $response] == 1} {
exit 0;
}
after 30000;
puts {
#########################################################################################################
#Step 2 :Trying to connect to WG telnet-ing to a WLAN client and associate wirelessly for open security                    
#########################################################################################################
}
set response [Configure_Client_open $wlanIP $telnetPort $wlanName $wlanPassword $profilePath $no $profileType $ssidName];
set wireless_pc_ip "$response";
puts "The Result of Configure client proc is $response";
set g [regexp {(\d+)\.(\d+)\.(\d+)\.(\d+)} $response m o];
puts $g;
if {![regexp {(\d+)\.(\d+)\.(\d+)\.(\d+)} $response m o] == 1} {
exit 0;
}
puts "$wireless_pc_ip";
} elseif {[regexp -nocase {wpa2-psk} $wlan_sec_type]} {
set response [config_wlan_sec_wpa2-psk $ClassPath $Class $oui $SNno $deviceType $device_param $test_radio $ssidName $wlan_sec_type $ri $si];
puts "The Result of config_wlan_sec_wpa2-psk is $response";
if {![regexp {pass} $response] == 1} {
exit 0;
}

puts {
##############################################################################################################
#Step 3 :Trying to connect to WG telnet-ing to a WLAN client and associate wirelessly for wpa2-psk security         
##############################################################################################################
}

set response [Configure_Client_open $wlanIP $telnetPort $wlanName $wlanPassword $profilePath $no $profileType $ssidName];
set wireless_pc_ip "$response";
puts "The Result of Configure client proc is $response";
if {![regexp {(\d+)\.(\d+)\.(\d+)\.(\d+)} $response m o] == 1} {
exit 0;
}
puts "$wireless_pc_ip";
} elseif {[regexp -nocase {wpawpa2-psk} $wlan_sec_type]} {
set response [config_wlan_sec_wpa2-psk $ClassPath $Class $oui $SNno $deviceType $device_param $test_radio $ssidName $wlan_sec_type $ri $si];
puts "The Result of config_wlan_sec_wpawpa2-psk is $response";
if {![regexp {pass} $response] == 1} {
exit 0;
}
puts {
#################################################################################################################
#Step 4 :Trying to connect to WG telnet-ing to a WLAN client and associate wirelessly for wpawpa2-psk security    
#################################################################################################################
} 

set response [Configure_Client_open $wlanIP $telnetPort $wlanName $wlanPassword $profilePath $no $profileType $ssidName];

set wireless_pc_ip "$response";
puts "The Result of Configure client proc is $response";
if {![regexp {(\d+)\.(\d+)\.(\d+)\.(\d+)} $response m o] == 1} {
exit 0;
}
puts "$wireless_pc_ip";
} 
puts {
###############################################################################
#step 5: Telnetting to LAN Client and get its ip address
###############################################################################
}
set response [connect_lan_pc $Telnetip $telnetPort1 $Name $password $osName1];
set wired_pc_ip "$response";
puts "The Result of connect_lan_pc is $response";  
if {![regexp {(\d+)\.(\d+)\.(\d+)\.(\d+)} $response m o] == 1} {
exit 0;
}
puts {
###################################################################################
#step 6: Send FTP traffic and validate the same 
###################################################################################
}

spawn telnet $wlanIP $telnetPort;
set timeout 100;
expect -re (.*ogin:);
send "$wlanName\r";
expect -re (.*word:);
send "$wlanPassword\r";
expect -re ".*>";
send "del -r test1.txt\r";
expect -re ".*>";
send "dir test1.txt\r";
expect -re ".*>";

send "ftp $wired_pc_ip\r";
expect\
{
".*ftp:"
{
send "bye\r";
set outFtp $expect_out(buffer);
set result "FAILED";
puts "FTP access not successful between wired and wiredless clients";
}
".*ftp>"
{
send "bye\r";
set outFtp $expect_out(buffer);
set result "FAILED";
puts "FTP access not successful between wired and wireless clients";
}

".*):"
{
send "$ftpName\r";
expect -re (.*:);
send "$ftpPassword\r";
expect -re (ftp>);
send "pwd\r"
expect -re (ftp>);
send "get test1.txt\r"
expect -re (ftp>);
send "\r";

set outFtp $expect_out(buffer);
expect -re (ftp>);
send "bye\r";

expect -re ".*>";
puts $outFtp;
send "dir test1.txt\r";
expect -re ".*>";
set outFtp1 $expect_out(buffer);

puts "$outFtp1";
puts {
############################################################################################
#Step 7 :Verifying the FTP download
############################################################################################
}
if {[regexp {test1.txt} $outFtp1 match] == 1} {
        set result "PASSED";

        puts "FTP access successful between wired and wireless clients"
                } else {
        set result "FAILED";

        puts "FTP access not successful between wired and wireless clients"
}
}
}
close $spawn_id;


puts $result;

set response [config_wlan_sec_wpa2-psk $ClassPath $Class $oui $SNno $deviceType $device_param $test_radio $ssidName "wpawpa2-psk" $ri $si];
puts "The Result of config_wlan_sec_wpawpa2-psk is $response";


set passContent "Test Result : $result";
displayProc $passContent;




