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
TESTCASEID : TC_ERTR_0253
Description  : Verify that ftp traffic between WLan to LAN should be denied, 
when wifi client assocation in open authentication for 2.4GHZ and SSID interface 
parameter for 2.4GHZ [Device.WiFi.SSID.1.Enable] is disabled.
#####################################################################################
}
set device_param "Device.WiFi.AccessPoint.$si2.Security.ModeEnabled"
set profileType "Wireless-open-2.4.xml";
set wlan_sec_type "open";
set ssidName "$ssid2";
set test_radio "2.4ghz";
set no [split $wlanInterfaceName "_"];
puts {
################################################################################
#Step 1 :Configuring the Accesspoint with wpawpa2-psk Secuirty mode
################################################################################
}
set response [config_wlan_sec_open $ClassPath $Class $oui $SNno $deviceType $device_param $test_radio $ssidName $ri2 $si2];
puts "The Result of config_wlan_sec_open is $response";
if {![regexp {pass} $response] == 1} {
exit 0;
}

set device_param "Device.WiFi.Radio.$ri2.Enable";
set value "true";
set dataType "boolean";

set response [device_set_get_param $ClassPath $Class $oui $SNno $deviceType SetParameterValue $device_param $value $dataType];
puts "The Result of Setparameter is $response";
if {[string compare $response "pass"] != 0} {
puts "Setparameter fails"
exit 0;
}

set device_param "Device.WiFi.SSID.$si2.Enable";
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
set profileType "Wireless-open-2.4.xml";
set wlan_sec_type "open";
set ssidName "$ssid2";

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
send "ifconfig\r";
expect -re ".*#";
set outConfig $expect_out(buffer);
send "exit\r";
regexp {.*inet addr:([0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}).*Bcast:10.0.0.255.*} $outConfig match Ipval;
puts "$Ipval";


puts {
##########################################################################################################
#Step 5 :Disabling SSID interface of the device.
##########################################################################################################
}
set device_param "Device.WiFi.SSID.$si2.Enable";
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
#Step 6 :Trying to connect to CM telnet-ing to a LAN Client
################################################################################
}
spawn telnet $Telnetip $telnetPort1;
set timeout 100;
expect -re (.*ogin:);
send "$Name\r";
expect -re (.*word:);
send "$password\r";
expect -re ".*#";
send "ftp $wireless_pc_ip\r";
expect\
{
".*ftp:"
{
set outFtp $expect_out(buffer);
}
".*):"
{
send "$wanFtpName\r";
expect -re (.*:);
send "$wanFtpPassword\r";
expect -re (.*230);
set outFtp $expect_out(buffer);
send "bye\r";
}
}
#wait
close $spawn_id;
set passFlag "";
set failFlag "";



puts {
############################################################################################
#Step 7 :Verifying the reachability of the FTP Traffic
############################################################################################
}
if {[regexp {.*230.*} $outFtp match] == 1} {
        set failFlag [expr $failFlag + 1];
        puts "FTP traffic successful between wired and wireless clients"
                } else {
        set passFlag [expr $passFlag + 1];
        puts "FTP traffic not successful between wired and wireless clients"
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
#Step 8 :Deleting the created profile.
############################################################################################
}
spawn telnet $wlanIP $telnetPort
set timeout 100;
expect -re (.*ogin:);
send "$wlanName\r";
expect -re (.*word:);
send "$wlanPassword\r";
expect -re ".*>";
send "netsh wlan delete profile name=\"$ssid2\"\r";
expect -re ".*>";
send "exit\r"
expect -re ".*>";
#wait
close $spawn_id
  
puts {
############################################################################################
#Step 9 :Reverting the interface status back to its initial value.
############################################################################################
}

set response [config_wlan_sec_wpa2-psk $ClassPath $Class $oui $SNno $deviceType $device_param $test_radio $ssidName "wpawpa2-psk" $ri2 $si2];
puts "The Result of config_wlan_sec_wpawpa2-psk is $response";


set device_param "Device.WiFi.SSID.$si2.Enable";
set value "true";
set dataType "boolean";

set response [device_set_get_param $ClassPath $Class $oui $SNno $deviceType SetParameterValue $device_param $value $dataType];
puts "The Result of Setparameter is $response";
if {[string compare $response "pass"] != 0} {
puts "Setparameter fails"
exit 0;
}
set passContent "Test Result : $result$~";
displayProc $passContent;

