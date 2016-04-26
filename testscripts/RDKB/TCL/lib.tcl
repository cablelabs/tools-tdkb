package require Expect;
source proc.tcl;

###########
proc device_set_get_param {ClassPath Class oui SNno deviceType set_get_type parameter value dataType {rType ""}} {

set result "pass"
############Check for the mandatory args for the proc##############
if { [info exists ClassPath] && [info exists Class] && [info exists oui] && [info exists SNno] && [info exists deviceType] && [info exists set_get_type] && [info exists parameter] && [info exists value]} {
############Variable with Values for verification#################
puts "set_get_type : $set_get_type";
puts "parameter : $parameter";
puts "value : $value";
puts "datatype : $dataType";
puts "ClassPath : $ClassPath";
puts "Class : $Class";
puts "oui : $oui";
puts "SNno : $SNno";
puts "devicetype : $deviceType";
puts "returnType : $rType";
#############Check for the type of the parameter and proceed with the steps#############
if {[regexp {SetParameterValue} $set_get_type match] == 1 } {
if { [info exists dataType]} {
set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue $parameter $value $dataType];
puts "$output1";
} else {
puts "One or More Argument missing";
set result "Error";
puts "$result";
return $result;
}
} elseif {[regexp {GetParameterValue} $set_get_type match] == 1} {
if { [info exists dataType]} {
puts "argument exist";
} else {
set dataType "null";
}
set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue $parameter $value $dataType];
puts "$output1"
} elseif {[regexp {SetMultipleParameterValues} $set_get_type match] == 1} {
if { [info exists dataType]} {
set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetMultipleParameterValues $parameter $value $dataType];
puts "$output1";
} else {
puts "One or More Argument missing";
set result "Error";
puts "$result";
return $result;
}
} else  {
puts "Setparam and getparam type mismatch - not found in the list";
set result "Error";
puts "$result";
return $result;
}
 
###############Check for the Errors in Output####################
#puts "$output1";
if {[regexp {.*Time limit has crossed 2 minutes.*} $output1] == 1 } {
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set/get 1st parameter";
set result "fail";
puts "$result";
return $result;
}
} else {
puts "One or More Argument missing";
set result "Error";
puts "$result";
return $result;
}
if {[regexp {GetParameterValue} $set_get_type match] == 1} {
if {[regexp {pass} $result match]} {
if {[regexp {output} $rType match]} {
return $output1;
}
}
}

return $result;
}



####Configure_Client $profilePath $no $profileType $ssidName

proc Configure_Client_open {wlanip wlanName wlanPassword profilePath no profileType ssidName} {

####################proc argument mandatory check###########################
if {[info exists profilePath] && [info exists no] && [info exists profileType] && [info exists wlanip]} {
set passFlag "";
spawn telnet $wlanip;
set timeout 100;
expect -re (.*ogin:);
send "$wlanName\r"; 
expect -re (.*word:); 
send "$wlanPassword\r";
expect -re ".*>";
send "netsh wlan add profile filename=\"$profilePath\\$profileType\" interface=\"$no\"\r";
expect -re ".*>";
sleep 30;
send "netsh wlan connect $ssidName\r";
expect -re ".*>";
set outpCon $expect_out(buffer);
after 30000;
send "ipconfig\r";
expect -re ".*>";
set outIp $expect_out(buffer);
send "exit\r"
expect -re ".*>";
close $spawn_id
set passFlag "";
set failFlag "";


	if {[regexp {There is no profile "$ssidName" assigned to the specified interface.} $outpCon match] == 1} {

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
        puts "Connection Successful";
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
regexp {.*Wireless LAN.*IPv4 Address.*: (.*) Sub.*Ethernet.*} $outIp match Ipval;
if {$passFlag == 3} {
puts "IP obtained: $Ipval";
return $Ipval;
} else  {
puts "Connection not successful and IP not obtained due to technical reasons"
set result "Error";
return $result;

}
} else { 
puts "Argument missing";
set result "Error";
return $result;
}
}

#################Procedure to get ip address from lan pc############################

proc connect_lan_pc {Telnetip Name password osName} {
 
if {[info exists Telnetip] && [info exists Name] && [info exists password]} {

if {[regexp -nocase {windows} $osName match] == 1} {
spawn telnet $Telnetip;
set timeout 100;
expect -re (.*ogin:);
send "$Name\r";
expect -re (.*word:);
send "$password\r";
expect -re ".*>";
#send "netsh interface set interface name=\"Wireless Network Connection 6\" admin=disabled\r";
#expect -re ".*>";
send "ipconfig\r";
expect -re ".*>";
set outConfig $expect_out(buffer);
send "exit\r";
puts "$outConfig";

#if { [regexp {.*Local Area Connection 3.*IPv4 Address.*: ([0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}).*Ethernet adapter.*} $outConfig match Ipval] == 1 } {
#puts "Obtained IP : $Ipval";
#} else {
#puts "IP has not been obtained due to technical reasons."
#set result "Error"
#return $result
#}
#if {[regexp -nocase {.*Local Area Connection 3.*IPv4 Address.*: ([0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}).*Subnet.*IPv4 Address.*:.*} $outConfig match Ipval] == 1 } {}
if { [regexp {.*IPv4 Address.*: (\d+\.\d+\.\d+\.\d+).*Subnet.*Default Gateway.*:.*10.0.0.1.*Ethernet.*} $outConfig matcn Ipval] == 1 } {
puts "Obtained IP : $Ipval";
} else {
puts "IP has not been obtained due to technical reasons."
set result "Error"
return $result
}

return $Ipval;
puts "$Ipval";
} else {
puts "$password";
spawn telnet $Telnetip; 
set timeout 100; 
expect -re (.*ogin:); 
send "$Name\r";  
expect -re (.*ssword:);  
send "$password\r"; 
expect -re ".*#";
send "service network restart\r";
expect -re ".*#";
send "ifconfig\r";
expect -re ".*#";
set outIp $expect_out(buffer);
send "exit\r"; 
#wait 
close $spawn_id; 

#if { [regexp {.*eth0.*inet addr:([0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}).*eth1.*} $outIp match Ipval] == 1 } {}
if { [regexp {.*inet addr:(\d+\.\d+\.\d+\.\d+)  Bcast:10.0.0.255.*} $outIp match Ipval] == 1 } {
puts "Obtained I P : $Ipval";
} else {
puts "IP has not been obtained due to technical reasons."
set result "Error"
return $result
}
return $Ipval;
}
}
}


################# Procedure to configure client in open security #########################


proc config_wlan_sec_open {ClassPath Class oui SNno deviceType device_param test_radio ssidName ri si} {

puts {
################################################################################
#Step 1 :Configuring the Accesspoint with Open Secuirty mode                                                                        			 
################################################################################
}


if {[regexp {2.4ghz} $test_radio]} {
set ssid_param "Device.WiFi.SSID.$si.SSID";

} elseif {[regexp {5ghz} $test_radio]} {
set ssid_param "Device.WiFi.SSID.$si.SSID";

} else {
puts "Argument to test_radio is mis-matches";
set result "fail";
return $result;
}

set result "pass";
set response [device_set_get_param $ClassPath $Class $oui $SNno $deviceType SetParameterValue $device_param None string];
puts "The Result of Setparameter is $response";
if {![regexp {pass} $response]} {
puts "Setparameter fails";
set result "fail";
exit 0;
}
set response [device_set_get_param $ClassPath $Class $oui $SNno $deviceType SetParameterValue $ssid_param $ssidName string];
puts "The Result of Setparameter is $response";
if {![regexp {pass} $response]} {
puts "Setparameter fails";
set result "fail";
exit 0;
}


puts {
################################################################################
#Step 2 :Get the values of the parameters that have been set                                                                					 
################################################################################
}
set response [device_set_get_param $ClassPath $Class $oui $SNno $deviceType GetParameterValue $device_param null null];
puts "The Result of Getparameter is $response";
if {![regexp {pass} $response]} {
puts "Setparameter fails";
set result "fail";
exit 0;
}
return $result;
}


############################### Procedure for configure wpa2-psk /wpawpa2-psk security ###################
proc config_wlan_sec_wpa2-psk {ClassPath Class oui SNno deviceType device_param test_radio ssidName sec_type ri si} {

################### Mandatory Argument Check #################################################################
if {[info exists ClassPath] && [info exists Class] && [info exists oui] && [info exists SNno] && [info exists deviceType] && [info exists device_param] && [info exists test_radio] && [info exists ssidName]} {


set result "pass";
################### set the value to varaiables based on the radio type ######################################
if {[regexp {2.4ghz} $test_radio]} {

set radio_param "Device.WiFi.Radio.$ri.Enable";
set ssid_param "Device.WiFi.SSID.$si.SSID";
set dev_param "Device.WiFi.AccessPoint.$si.Security.ModeEnabled";
#set security_param "Device.WiFi.AccessPoint.$si.Security.X_CISCO_COM_EncryptionMethod";
#set security_param1 "Device.WiFi.AccessPoint.$si.Security.ModeEnabled";
set security_param "Device.WiFi.AccessPoint.$si.Security.X_CISCO_COM_EncryptionMethod,Device.WiFi.AccessPoint.$si.Security.ModeEnabled";
set sec_key_param "Device.WiFi.AccessPoint.$si.Security.PreSharedKey";


} elseif {[regexp {5ghz} $test_radio]} {

set radio_param "Device.WiFi.Radio.$ri.Enable";
set ssid_param "Device.WiFi.SSID.$si.SSID";
#set security_param "Device.WiFi.AccessPoint.$si.Security.X_CISCO_COM_EncryptionMethod";
#set security_param1 "Device.WiFi.AccessPoint.$si.Security.ModeEnabled";
set security_param "Device.WiFi.AccessPoint.$si.Security.X_CISCO_COM_EncryptionMethod,Device.WiFi.AccessPoint.$si.Security.ModeEnabled";

set sec_key_param "Device.WiFi.AccessPoint.$si.Security.PreSharedKey";
set dev_param "Device.WiFi.AccessPoint.$si.Security.ModeEnabled";

} else {
puts "Argument to test_radio is mis-matches";
set result "fail";
return $result;
}

if {[regexp {wpawpa2-psk} $sec_type]} {
#set multi_param_value "AES+TKIP,WPA-WPA2-Personal";
set multi_param_value "AES+TKIP,WPA-WPA2-Personal";
} else {
#set multi_param_value "AES";
#set multi_param_value1 "WPA2-Personal";
set multi_param_value "AES,WPA2-Personal";
}
################### Set and Get the Parameter values and Validate the same ######################################
set response [device_set_get_param $ClassPath $Class $oui $SNno $deviceType SetParameterValue $radio_param 1 boolean];
puts "The Result of Setparameter is $response";
if {![regexp {pass} $response]} {
puts "Setparameter fails";
set result "fail";
exit 0;
}


set response [device_set_get_param $ClassPath $Class $oui $SNno $deviceType SetParameterValue $ssid_param $ssidName string];
puts "The Result of Setparameter is $response";
if {![regexp {pass} $response]} {
puts "Setparameter fails";
set result "fail";
exit 0;
}




set response [device_set_get_param $ClassPath $Class $oui $SNno $deviceType SetMultipleParameterValues $security_param $multi_param_value string,string];
puts "The Result of Setparameter is $response";
if {![regexp {pass} $response]} {
puts "Setparameter fails";
set result "fail";
exit 0;
}



set response [device_set_get_param $ClassPath $Class $oui $SNno $deviceType SetParameterValue $sec_key_param wifitest123 string];
puts "The Result of Setparameter is $response";
if {![regexp {pass} $response]} {
puts "Setparameter fails";
set result "fail";
exit 0;
}


set response [device_set_get_param $ClassPath $Class $oui $SNno $deviceType GetParameterValue $ssid_param null null];
puts "The Result of Getparameter is $response";
if {![regexp {pass} $response]} {
puts "Setparameter fails";
set result "fail";
exit 0;
}

set response [device_set_get_param $ClassPath $Class $oui $SNno $deviceType GetParameterValue $dev_param null null];
puts "The Result of Getparameter is $response";
if {![regexp {pass} $response]} {
puts "Setparameter fails";
set result "fail";
exit 0;
}



puts "$result";
return $result;
}

}


#####################Procedure to configure ethernet client############################
proc config_ethernet_client {ipaddr userName passWord osName} {
if{[regexp -nocase {windows} $osName match] == 1} {
spawn telnet $ipaddr;
set timeout 100;
expect -re (.*ogin:);
send "$userName\r";
expect -re (.*word:);
send "$passWord\r";
expect -re ".*#";
send "ifconfig\r";
expect -re ".*#";
set outConfig $expect_out(buffer);
send "exit\r";
regexp {.*eth0.*inet addr:([0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}).*eth1.*} $outConfig match Ipval;
puts "$Ipval";
} else {
spawn telnet $ipaddr;
set timeout 100;
expect -re (.*ogin:);
send "$userName\r";
expect -re (.*word:);
send "$passWord\r";
expect -re ".*>";
send "ipconfig\r";
expect -re ".*>";
set outConfig $expect_out(buffer);
send "exit\r";
regexp {.*Local Area Connection 2.*IPv4 Address.*:([0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}).*Wireless LAN.*} $outConfig match Ipval;
puts "$Ipval";
}
return $Ipval;
}


############procedure for interface  enable/disable###############################

proc config_interface_enable_disable {wlanip wlanAdminName wlanAdminPassword interface_name option} {
set result "pass";




spawn telnet $wlanip;
set timeout 100;
expect -re (.*ogin:);
send "$wlanAdminName\r";
expect -re (.*word:);
send "$wlanAdminPassword\r";
expect -re ".*>";

send "netsh interface show interface\r";
expect -re ".*>";
set output $expect_out(buffer);

send "netsh interface set interface name=\"$interface_name\" admin=$option\r";
expect -re ".*>";

send "netsh interface show interface\r";
expect -re ".*>";
#set output $expect_out(buffer);
send "exit\r";

close $spawn_id;

return $result;
}
