package require Expect;
source proc.tcl;
source lib.tcl;
#Initializing the values to the parameters by invoking Initializer proc
#set configFile $argv;
set script_args $argv;
puts "Script arguments are $script_args";
set no_script_args $argc;
puts "Number of Script arguments are $no_script_args";
set configFile [lindex $script_args 0];
set logical_id [lindex $script_args 1];
puts "The config file is $configFile";
Initializer $configFile;
puts {
#####################################################################################
TESTCASEID : TC_ERTR_0250
Description  :Verify that http traffic between WLan to LAN should be denied, when 
wifi client assocation in open authentication for 5GHZ and SSID interface parameter 
for 5GHZ [Device.WiFi.SSID.2.Enable] is disabled
#####################################################################################
}
set device_param "Device.WiFi.AccessPoint.$si5.Security.ModeEnabled";
set profileType "Wireless-open-5GHz.xml";
set wlan_sec_type "open";
set ssidName "$ssid5";
set test_radio "5ghz";
set no [split $wlanInterfaceName "_"];
puts {
################################################################################
#Step 1 :Configuring the Accesspoint with wpawpa2-psk Secuirty mode
################################################################################
}
set response [config_wlan_sec_open $ClassPath $Class $oui $SNno $deviceType $device_param $test_radio $ssidName $ri5 $si5];
puts "The Result of config_wlan_sec_open is $response";
if {![regexp {pass} $response] == 1} {
exit 0;
}

set device_param "Device.WiFi.Radio.$ri5.Enable";
set value "true";
set dataType "boolean";

set response [device_set_get_param $ClassPath $Class $oui $SNno $deviceType SetParameterValue $device_param $value $dataType];
puts "The Result of Setparameter is $response";
if {[string compare $response "pass"] != 0} {
puts "Setparameter fails"
exit 0;
}
set device_param "Device.WiFi.SSID.$si5.Enable";
set value "true";
set dataType "boolean";

set response [device_set_get_param $ClassPath $Class $oui $SNno $deviceType SetParameterValue $device_param $value $dataType];
puts "The Result of Setparameter is $response";
if {[string compare $response "pass"] != 0} {
puts "Setparameter fails"
exit 0;
}

puts {
##########################################################################################################
#Step 3 :Telneting to the WLAN client and obtaining its IP.
##########################################################################################################
}
set profileType "Wireless-open-5.xml";
set wlan_sec_type "wpawpa2-psk";
set ssidName "$ssid5";

set response [Configure_Client_open $wlanIP $telnetPort $wlanName $wlanPassword $profilePath $no $profileType $ssidName];

set wireless_pc_ip "$response";
puts "The Result of Configure client proc is $response";
if {![regexp {(\d+)\.(\d+)\.(\d+)\.(\d+)} $response m o] == 1} {
exit 0;
}
puts "$wireless_pc_ip";


puts {
##########################################################################################################
#Step 4 :Telneting to the LAN client and obtaining its IP.
##########################################################################################################
}

spawn telnet $Telnetip $telnetPort1;
set timeout 100;
expect -re (.*ogin:);
send "$Name\r";
expect -re (.*word:);
send "$password\r";
expect -re ".*#";
send "service network restart\r";
expect -re ".*#";
send "ifconfig\r";
expect -re ".*#";
set outConfig $expect_out(buffer);
send "exit\r";
regexp {.*inet addr:([0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}).*Bcast:10.0.0.255.*} $outConfig match Ipval;
puts "$Ipval";

puts {
##########################################################################################################
#Step 5 :Disabling radio interface of the device.
##########################################################################################################
}
set device_param "Device.WiFi.SSID.$si5.Enable";
set value "false";
set dataType "boolean";

set response [device_set_get_param $ClassPath $Class $oui $SNno $deviceType SetParameterValue $device_param $value $dataType];
puts "The Result of Setparameter is $response";
if {[string compare $response "pass"] != 0} {
puts "Setparameter fails"
exit 0;
}
after 10000;
puts {
################################################################################
#Step 6 :Trying to connect to CM telnet-ing to a WLAN Client
################################################################################
}
spawn telnet $wlanIP $telnetPort;
set timeout 100;
expect -re (.*ogin:);
send "$wlanName\r";
expect -re (.*word:);
send "$wlanPassword\r";
expect -re ".*>";
send "wget http://$Ipval/test1\r";
expect -re ".*>";
set outHttp $expect_out(buffer);
#wait
close $spawn_id;


set passFlag "";
set failFlag "";
puts {
############################################################################################
#Step 7 :Verifying the reachability of the HTTP Traffic
############################################################################################
}
if {[regexp {.*200 OK.*} $outHttp match] == 1} {
        set failFlag [expr $failFlag + 1];
        puts "HTTP traffic successful between wired and wireless clients"
                } else {
        set passFlag [expr $passFlag + 1];
        puts "HTTP traffic not successful between wired and wireless clients"
}

if {$passFlag == 1} {
set result "PASSED"
} else {
        if {$failFlag >0 || $passFlag <1} {
        set result "FAILED";
}
  }
  

  puts {
############################################################################################
#Step 8 :Reverting the interface status back to its initial value.
############################################################################################
}
set response [config_wlan_sec_wpa2-psk $ClassPath $Class $oui $SNno $deviceType $device_param $test_radio $ssidName "wpawpa2-psk" $ri5 $si5];
puts "The Result of config_wlan_sec_wpawpa2-psk is $response";

set device_param "Device.WiFi.SSID.$si5.Enable";
set value "true";
set dataType "boolean";

set response [device_set_get_param $ClassPath $Class $oui $SNno $deviceType SetParameterValue $device_param $value $dataType];
puts "The Result of Setparameter is $response";

set passContent "Test Result : $result$~";
displayProc $passContent;

