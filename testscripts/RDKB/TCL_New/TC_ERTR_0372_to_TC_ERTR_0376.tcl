package require Expect;
source proc.tcl;
source lib.tcl;
puts {
#####################################################################################				
#TESTCASEID :TC_ERTR_0372 to TC_ERTR_0376
#Description  :Verify that Telnet traffic between WLAN to LAN should be succesfull, 
#when wifi client assocation is done.      
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
Initializer $configFile;


########################Logical id Check###############################

if {[regexp -nocase {TC_ERTR_0372} $logical_id]} {
set device_param "Device.WiFi.AccessPoint.$si2.Security.ModeEnabled";
set wlan_sec_type "open";
set profileType "Wireless-open-2.4.xml";
set ssidName "$ssid2";
set test_radio "2.4ghz";
set ri "$ri2";
set si "$si2";
} elseif {[regexp -nocase {TC_ERTR_0373} $logical_id]} {
set device_param "Device.WiFi.AccessPoint.$si5.Security.ModeEnabled";
set profileType "Wireless-open-5.xml";
set wlan_sec_type "open";
set ssidName "$ssid5";
set test_radio "5ghz";
set ri "$ri5";
set si "$si5";
} elseif {[regexp -nocase {TC_ERTR_0374} $logical_id]} {
set device_param "Device.WiFi.AccessPoint.$si2.Security.ModeEnabled";
set profileType "Wireless.xml";
set wlan_sec_type "wpa2-psk";
set ssidName "$ssid2";
set test_radio "2.4ghz";
set ri "$ri2";
set si "$si2";
} elseif {[regexp -nocase {TC_ERTR_0375} $logical_id]} {
set device_param "Device.WiFi.AccessPoint.$si5.Security.ModeEnabled";
set profileType "Wireless-5GHz.xml";
set wlan_sec_type "wpa2-psk";
set ssidName "$ssid5";
set test_radio "5ghz";
set ri "$ri5";
set si "$si5";
}  elseif {[regexp -nocase {TC_ERTR_0376} $logical_id]} {
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
puts {
################################################################################
#Step 1 :Configuring the Accesspoint with $wlan_sec_type Secuirty mode                           
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
puts {
#########################################################################################################
#Step 2 :Telnet to WLAN Client and associate wirelessly for open security mode       
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
#Step 3 :Telnet to WLAN Client and associate wirelessly for wpa2-psk security mode
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
#Step 4 :Telnet to  WLAN Client and associate wirelessly for wpawpa2-psk security mode
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

###############################################################################
#step 5: Telnetting to LAN Client and get its IP address
###############################################################################
set response [connect_lan_pc $Telnetip $telnetPort1 $Name $password $osName1];
set wired_pc_ip "$response";
puts "The Result of connect_lan_pc is $response";  
if {![regexp {(\d+)\.(\d+)\.(\d+)\.(\d+)} $response m o] == 1} {
exit 0;
}

puts {
###################################################################################
#step 6: Send Telnet traffic between Wired and Wireless Client
###################################################################################
}
spawn telnet $Telnetip $telnetPort1;
set timeout 100;
expect -re (.*ogin:);
send "$Name\r";
expect -re (.*word:);
send "$password\r";
expect -re ".*#";

send "telnet $wireless_pc_ip\r";
set timeout 100;

after 2000;


expect -re (.*ogin:);
#set out $expect_out(buffer);
#puts $out;

#expect -re (.*ogin:.*);
after 10000;
send "$wlanName\r";
expect -re (.*word:);
send "$wlanPassword\r";
expect -re ".*>";
set outTelnet $expect_out(buffer);

send "exit\r";
expect -re ".*#";

#wait
close $spawn_id;
set passFlag "";
set failFlag "";
puts {
############################################################################################
#Step 7 :Verifying the reachability of the Telnet Traffic
############################################################################################
}
if {[regexp {.*Connection refused.*} $outTelnet match] == 1 } {
        set failFlag [expr $failFlag + 1];
        puts "Telnet Request not successful between wired and wireless clients"
                } else {
if {[regexp {.*Trying.*....*} $outTelnet match] == 1 } {
        set failFlag [expr $failFlag + 1];
        puts "Telnet Request not successful between wired and wireless clients"
        } else {
        set passFlag [expr $passFlag + 1];
        puts "Telnet Request successful between wired and wireless clients"
        }
 }


puts {
##############################################################################################
#Step 8: Revert to default security mode
##############################################################################################
}

set response [config_wlan_sec_wpa2-psk $ClassPath $Class $oui $SNno $deviceType $device_param $test_radio $ssidName $wlan_sec_type $ri $si];
puts "The Result of config_wlan_sec_wpawpa2-psk is $response";
if {![regexp {pass} $response] == 1} {
exit 0;
}

if {$passFlag == 1} {
set result "PASSED"
} else {
        if {$failFlag >0 || $passFlag <1} {
        set result "FAILED";
}
  }
puts "$passFlag";
puts $result;

set passContent "Test Result : $result";
displayProc $passContent;




