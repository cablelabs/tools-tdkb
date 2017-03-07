package require Expect;
source proc.tcl;
source lib.tcl;
puts {
#########################################################################################################################
TESTCASEID : TC_ERTR_0135
Description  :Verify that when 5 GHz radio is disabled, corresponding SSID should not be broadcasted in Client side
##########################################################################################################################
 }
#Initializing the values to the parameters by invoking Initializer proc
#set configFile $argv;


set configFile $argv;
Initializer $configFile;

########################Logical id Check###############################


set device_param "Device.WiFi.AccessPoint.$si5.Security.ModeEnabled";
set profileType "Wireless-5GHz.xml";
set wlan_sec_type "wpawpa2-psk";
set ssidName "$ssid5";
set test_radio "5ghz";
set radio_param "Device.WiFi.Radio.$ri5.Enable";
 

puts {
################################################################################
#Step 1 :Configuring the Accesspoint with wpawpa2-psk Security mode                                                         
################################################################################
}
set response [config_wlan_sec_wpa2-psk $ClassPath $Class $oui $SNno $deviceType $device_param $test_radio $ssidName $wlan_sec_type $ri5 $si5 ];
puts "The Result of config_wlan_sec_wpawpa2-psk is $response";
if {![regexp {pass} $response] == 1} {
exit 0;
}
puts {
########################################
#step 2 :Disable the 5GHZ radio                                                         	 
########################################
} 

set response [device_set_get_param $ClassPath $Class $oui $SNno $deviceType SetParameterValue $radio_param 0 boolean];
puts "The Result of Setparameter is $response";

if {![regexp {pass} $response]} {
puts "Setparameter fails";
set result "fail";
exit 0;
}

sleep 120;
puts {
#####################################################################################################################
#step 3: :Trying to connect to WG telnet-ing to a WLAN client  and associate wirelessly for wpawpa2-psk security
#####################################################################################################################
}
spawn telnet $wlanIP $telnetPort
set timeout 100;
expect -re (.*ogin:);
send "$wlanName\r";
expect -re (.*word:);
send "$wlanPassword\r";
expect -re ".*>";
match_max 50000;
send "netsh wlan show networks\r";
expect -re ".*>";
set outpRad $expect_out(buffer);
send "exit\r"
expect -re ".*>";
#wait^M

close $spawn_id
set passFlag "";
set failFlag "";

puts "Expected: Network name \"$ssid5\" should not be broadcasted";
if { [regexp {RDKB-5} $outpRad] == 1} {
set failFlag [expr $failFlag + 1];
puts "\nObtained: Network name \"$ssid5\" is broadcasted on the network";
} else {
set passFlag [expr $passFlag + 1];
puts "\nObtained: Network name \"$ssid5\" is not broadcasted on the network";
}
puts $passFlag;
if {$passFlag == 1} {
set result "PASSED"
} else {
        if {$failFlag >0 || $passFlag <1} {
        set result "FAILED";
}
  }




puts {
########################################
#step 4 :Enable the 5GHZ radio
########################################
}

set response [device_set_get_param $ClassPath $Class $oui $SNno $deviceType SetParameterValue $radio_param 1 boolean];
puts "The Result of Setparameter is $response";
if {![regexp {pass} $response]} {
puts "Setparameter fails";
set result "fail";
exit 0;
}
sleep 60;
set passContent "Test Result : $result";
displayProc $passContent;




