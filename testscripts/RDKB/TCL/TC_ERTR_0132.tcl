##########################################################################
# If not stated otherwise in this file or this component's Licenses.txt
# file the following copyright and licenses apply:
#
# Copyright 2016 RDK Management
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
##########################################################################
#

package require Expect; 
source proc.tcl; 
source lib.tcl
puts { 
########################################################################################################################################## 
#TEST CASEID :TC_ERTR_0132                                                                                                 
#Description  :Verify that WG supports blocking of specific clients based on MACaddress through parental control (managed devices) 
########################################################################################################################################## 
}  
#Initializing the values to the parameters by invoking Initializer proc 
set configFile $argv;
Initializer $configFile; 
 
 
puts { 
################################################################################ 
#Step 1 :Enabling the managed devices and blocking a particular device. 
################################################################################ 
}  
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_Comcast_com_ParentalControl.ManagedDevices.Enable true boolean]; 
puts $output1; 
if {[regexp {.*Time limit has crossed 2 minutes.*} $output1] == 1 } { 
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection"; 
puts "Failed to set 1st parameter"; 
set result "FAILED"; 
set passContent "Test Result : $result$~"; 
displayProc $passContent; 
exit 0; 
}  
 
 
set output2 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_Comcast_com_ParentalControl.ManagedDevices.AllowAll false boolean]; 
puts $output2; 
if {[regexp {.*Time limit has crossed 2 minutes.*} $output2] == 1 } { 
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection"; 
puts "Failed to set 2nd parameter"; 
set result "FAILED"; 
set passContent "Test Result : $result$~"; 
displayProc $passContent; 
exit 0; 
}  
proc commented {} { 
set voutput3 [exec java -cp $ClassPath $Class $oui $SNno $deviceType AddObject Device.X_Comcast_com_ParentalControl.ManagedDevices.Device. null null]; 
puts $voutput3; 
if {[regexp {.*Time limit has crossed 2 minutes.*} $voutput3] == 1 } { 
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection"; 
puts "Failed to set 3rd parameter"; 
set result "FAILED"; 
set passContent "Test Result : $result$~"; 
displayProc $passContent; 
exit 0; 
} 
} 

 
 
set output3 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_Comcast_com_ParentalControl.ManagedDevices.Device.1.Type Block string]; 
puts $output3; 
if {[regexp {.*Time limit has crossed 2 minutes.*} $output3] == 1 } { 
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection"; 
puts "Failed to set 3rd parameter"; 
set result "FAILED"; 
set passContent "Test Result : $result$~"; 
displayProc $passContent; 
exit 0; 
}  
 
set output4 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_Comcast_com_ParentalControl.ManagedDevices.Device.1.Description rootNAT string]; 
puts $output4; 
if {[regexp {.*Time limit has crossed 2 minutes.*} $output4] == 1 } { 
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection"; 
puts "Failed to set 4th parameter"; 
set result "FAILED"; 
set passContent "Test Result : $result$~"; 
displayProc $passContent; 
exit 0; 
}  
 
spawn telnet $Telnetip; 
set timeout 100; 
expect -re (.*ogin:); 
send "$Name\r"; 
expect -re (.*word:); 
send "$password\r"; 
expect -re ".*#"; 
send "ifconfig\r"; 
expect -re ".*#"; 
set outIp $expect_out(buffer); 
#wait 
close $spawn_id 
 
regexp {.*HWaddr.* ([0-9 A-F]{1,2}:[0-9 A-F]{1,2}:[0-9 A-F]{1,2}:[0-9 A-F]{1,2}:[0-9 A-F]{1,2}:[0-9 A-F]{1,2}).*inet addr:10.0.*} $outIp match MAC1; 
puts $MAC1;
 
 
 
 
set output5 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_Comcast_com_ParentalControl.ManagedDevices.Device.1.MACAddress $MAC1 string]; 
puts $output5; 
if {[regexp {.*Time limit has crossed 2 minutes.*} $output5] == 1 } { 
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection"; 
puts "Failed to set 5th parameter"; 
set result "FAILED"; 
set passContent "Test Result : $result$~"; 
displayProc $passContent; 
exit 0; 
}  
 
set output6 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_Comcast_com_ParentalControl.ManagedDevices.Device.1.AlwaysBlock true boolean]; 
puts $output6; 
if {[regexp {.*Time limit has crossed 2 minutes.*} $output6] == 1 } { 
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection"; 
puts "Failed to set 6th parameter"; 
set result "FAILED"; 
set passContent "Test Result : $result$~"; 
displayProc $passContent; 
exit 0; 
}  
puts { 
########################################################################################################## 
#Step 2 :Get the value of parameters that have been set. 
########################################################################################################## 
}  
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_Comcast_com_ParentalControl.ManagedDevices.Enable null null]; 
puts $output1; 
if {[regexp {.*Time limit has crossed 2 minutes.*} $output1] == 1 } { 
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection"; 
puts "Failed to get 1st parameter"; 
set result "FAILED"; 
set passContent "Test Result : $result$~"; 
displayProc $passContent; 
exit 0; 
}  
 
 
set output2 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_Comcast_com_ParentalControl.ManagedDevices.AllowAll null null]; 
puts $output2; 
if {[regexp {.*Time limit has crossed 2 minutes.*} $output2] == 1 } { 
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection"; 
puts "Failed to get 2nd parameter"; 
set result "FAILED"; 
set passContent "Test Result : $result$~"; 
displayProc $passContent; 
exit 0; 
}  
 
set output3 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_Comcast_com_ParentalControl.ManagedDevices.Device.1.Type null null]; 
puts $output3; 
if {[regexp {.*Time limit has crossed 2 minutes.*} $output3] == 1 } { 
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection"; 
puts "Failed to get 3rd parameter"; 
set result "FAILED"; 
set passContent "Test Result : $result$~"; 
displayProc $passContent; 
exit 0; 
}  
 
set output4 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_Comcast_com_ParentalControl.ManagedDevices.Device.1.Description null null]; 
puts $output4; 
if {[regexp {.*Time limit has crossed 2 minutes.*} $output4] == 1 } { 
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection"; 
puts "Failed to get 4th parameter"; 
set result "FAILED"; 
set passContent "Test Result : $result$~"; 
displayProc $passContent; 
exit 0; 
}  
 
set output5 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_Comcast_com_ParentalControl.ManagedDevices.Device.1.MACAddress null null]; 
puts $output5; 
if {[regexp {.*Time limit has crossed 2 minutes.*} $output5] == 1 } { 
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection"; 
puts "Failed to get 5th parameter"; 
set result "FAILED"; 
set passContent "Test Result : $result$~"; 
displayProc $passContent; 
exit 0; 
}  
 
set output6 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_Comcast_com_ParentalControl.ManagedDevices.Device.1.AlwaysBlock null null]; 
puts $output6; 
if {[regexp {.*Time limit has crossed 2 minutes.*} $output6] == 1 } { 
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection"; 
puts "Failed to get 6th parameter"; 
set result "FAILED"; 
set passContent "Test Result : $result$~"; 
displayProc $passContent; 
exit 0; 
}  
set no [split $wlanInterfaceName "_"]; 
puts {
################################################################################
#Step 3:Configuring the Accesspoint with wpawpa2-psk Secuirty mode
################################################################################
}

set device_param1 "Device.WiFi.AccessPoint.$si5.Security.ModeEnabled";
set profileType "Wireless-5GHz.xml";
set wlan_sec_type "wpawpa2-psk";
set ssidName "$ssid5";
set test_radio "5ghz";
set radio_param "Device.WiFi.Radio.$ri5.Enable";

set response [config_wlan_sec_wpa2-psk $ClassPath $Class $oui $SNno $deviceType $device_param1 $test_radio $ssidName $wlan_sec_type $ri5 $si5];
puts "The Result of config_wlan_sec_wpawpa2-psk is $response";
if {![regexp {pass} $response] == 1} {
exit 0;
}


puts {
##########################################################################################################
#Step 4 :Telneting to the WLAN client and obtaining its IP.
##########################################################################################################
}
set profileType "Wireless-5GHz.xml";
set wlan_sec_type "wpawpa2-psk";
set ssidName "$ssid5";

set response [Configure_Client_open $wlanIP $wlanName $wlanPassword $profilePath $no $profileType $ssidName];

set wireless_pc_ip "$response";
puts "The Result of Configure client proc is $response";
if {![regexp {(\d+)\.(\d+)\.(\d+)\.(\d+)} $response m o] == 1} {
exit 0;
}
puts "$wireless_pc_ip";

puts { 
####################################################################################### 
#Step 5 :Telneting to WLAN client and trying to access Internet from blocked device                                          ####################################################################################### 
} 
spawn telnet $wlanIP;
set timeout 100;
expect -re (.*ogin:);
send "$wlanAdminName\r";
expect -re (.*word:);
send "$wlanAdminPassword\r";
expect -re ".*>";
send "nslookup\r";
expect -re ".*>";
send "server $DnsServerIp\r";
expect -re ".*>";
send "$siteUrl\r";
expect -re ".*>";
set outUrlResp $expect_out(buffer);
send "exit\r";
expect -re ".*>"
regexp {.*Name.*?([0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}).*} $outUrlResp match ipFull;
regexp {(\d+\.\d+).*} $ipFull match ip;
send "route add $ip.0.0 mask 255.255.0.0 10.0.0.1\r";
expect -re ".*OK!.*>";
send "wget --tries=1 -T 60 http://$siteUrl\r";
expect -re ".*>";
set outHttp $expect_out(buffer);
send "route delete $ip.0.0\r";
expect -re ".*>";
send "exit\r";
#wait
close $spawn_id;
set passFlag "";
set failFlag "";
puts { 
############################################################################################ 
#Step 6 :Verifying whether the blocked device can access Internet 
############################################################################################ 
} 
if {[regexp {.*200 OK.*} $outHttp match] == 1} { 
        set failFlag [expr $failFlag + 1]; 
        puts "The blocked device can access the Internet" 
                } else { 
        set passFlag [expr $passFlag + 1]; 
        puts "The blocked device cannot access the Internet" 
} 
 
if {$passFlag == 1} { 
set result "PASSED" 
} else { 
        if {$failFlag >0 || $passFlag <1} { 
        set result "FAILED"; 
} 
  } 
 
  puts { 
################################################################################ 
#Step 7 :Reverting the blocked device parameters to initial values
################################################################################ 
}  
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_Comcast_com_ParentalControl.ManagedDevices.Enable false boolean]; 
puts $output1; 
if {[regexp {.*Time limit has crossed 2 minutes.*} $output1] == 1 } { 
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection"; 
puts "Failed to set 1st parameter"; 
set result "FAILED"; 
set passContent "Test Result : $result$~"; 
displayProc $passContent; 
exit 0; 
} 
 
set passContent "Test Result : $result$~"; 
displayProc $passContent; 
  

