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
#TEST CASEID :TC_ERTR_0114                                                                                                  
#Description  :Verify that WG allows allows other services for Wi-Fi Client associated using 2.4GHZ radio when only FTP service is blocked through parental control( managed services)
########################################################################################################################################## 
}  
#Initializing the values to the parameters by invoking Initializer proc 
set configFile $argv;
Initializer $configFile; 
 
puts { 
################################################################################ 
#Step 1 :Enabling the managed services and blocking a particular service. 
################################################################################ 
}

set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_Comcast_com_ParentalControl.ManagedServices.Enable true boolean]; 
puts $output1; 
if {[regexp {.*Time limit has crossed 2 minutes.*} $output1] == 1 } { 
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection"; 
puts "Failed to set 1st parameter"; 
set result "FAILED"; 
set passContent "Test Result : $result$~"; 
displayProc $passContent; 
exit 0; 
}  
set voutput1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_Comcast_com_ParentalControl.ManagedServices.Service.1.EndPort null null];
puts $voutput1; 
if {[regexp {.*Time limit has crossed 2 minutes.*} $voutput1] == 1 } { 
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection"; 
puts "Failed to set 1st parameter"; 
set result "FAILED"; 
set passContent "Test Result : $result$~"; 
displayProc $passContent; 
exit 0; 
}


if {[regexp {.*ManagedServices.Service.(.*).EndPort.*} $voutput1 match I] == 1} {
puts "instance configured is: $I"
}

set output2 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetMultipleParameterValues Device.X_Comcast_com_ParentalControl.ManagedServices.Service.$I.Description,Device.X_Comcast_com_ParentalControl.ManagedServices.Service.$I.Protocol,Device.X_Comcast_com_ParentalControl.ManagedServices.Service.$I.StartPort,Device.X_Comcast_com_ParentalControl.ManagedServices.Service.$I.EndPort,Device.X_Comcast_com_ParentalControl.ManagedServices.Service.$I.AlwaysBlock ftp,BOTH,21,21,true string,string,unsignedInt,unsignedInt,boolean]; 
puts $output2; 
if {[regexp {.*Time limit has crossed 2 minutes.*} $output2] == 1 } { 
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection"; 
puts "Failed to set 2nd parameter"; 
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
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_Comcast_com_ParentalControl.ManagedServices.Enable null null]; 
puts $output1; 
if {[regexp {.*Time limit has crossed 2 minutes.*} $output1] == 1 } { 
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection"; 
puts "Failed to get 1st parameter"; 
set result "FAILED"; 
set passContent "Test Result : $result$~"; 
displayProc $passContent; 
exit 0; 
}  
 
set output2 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_Comcast_com_ParentalControl.ManagedServices.Service.$I.Description null null]; 
puts $output2; 
if {[regexp {.*Time limit has crossed 2 minutes.*} $output2] == 1 } { 
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection"; 
puts "Failed to get 2nd parameter"; 
set result "FAILED"; 
set passContent "Test Result : $result$~"; 
displayProc $passContent; 
exit 0; 
}  
set output3 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_Comcast_com_ParentalControl.ManagedServices.Service.$I.Protocol null null]; 
puts $output3; 
if {[regexp {.*Time limit has crossed 2 minutes.*} $output3] == 1 } { 
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection"; 
puts "Failed to get 3rd parameter"; 
set result "FAILED"; 
set passContent "Test Result : $result$~"; 
displayProc $passContent; 
exit 0; 
}
set output4 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_Comcast_com_ParentalControl.ManagedServices.Service.$I.StartPort null null]; 
puts $output4; 
if {[regexp {.*Time limit has crossed 2 minutes.*} $output4] == 1 } { 
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection"; 
puts "Failed to get 4th parameter"; 
set result "FAILED"; 
set passContent "Test Result : $result$~"; 
displayProc $passContent; 
exit 0; 
}  
set output5 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_Comcast_com_ParentalControl.ManagedServices.Service.$I.EndPort null null]; 
puts $output5; 
if {[regexp {.*Time limit has crossed 2 minutes.*} $output5] == 1 } { 
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection"; 
puts "Failed to get 5th parameter"; 
set result "FAILED"; 
set passContent "Test Result : $result$~"; 
displayProc $passContent; 
exit 0; 
}  


set output6 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_Comcast_com_ParentalControl.ManagedServices.Service.$I.AlwaysBlock null null]; 
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
#Step 3 :Configuring the Accesspoint with wpawpa2-psk Secuirty mode
################################################################################
}

set device_param1 "Device.WiFi.AccessPoint.$si2.Security.ModeEnabled";
set profileType "Wireless.xml";
set wlan_sec_type "wpawpa2-psk";
set ssidName "$ssid2";
set test_radio "2.4ghz";
set radio_param "Device.WiFi.Radio.$ri2.Enable";

set response [config_wlan_sec_wpa2-psk $ClassPath $Class $oui $SNno $deviceType $device_param1 $test_radio $ssidName $wlan_sec_type $ri2 $si2];
puts "The Result of config_wlan_sec_wpawpa2-psk is $response";
if {![regexp {pass} $response] == 1} {
exit 0;
}


puts {
##########################################################################################################
#Step 4 :Telneting to the WLAN client and obtaining its IP.
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
################################################################################ 
#Step 5 :Telneting to WLAN Client and trying to access the unblocked Service
################################################################################ 
} 
spawn telnet $wlanIP $telnetPort;
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
set outUrlResp1 $expect_out(buffer);
send "$siteHttps\r";
expect -re ".*>";
set outUrlResp2 $expect_out(buffer);
send "exit\r";
expect -re ".*>";
regexp {.*Name.*?([0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}).*} $outUrlResp1 match ipFull1;
regexp {(\d+\.\d+).*} $ipFull1 match ip1;
regexp {.*Name.*?([0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}).*} $outUrlResp2 match ipFull2;
regexp {(\d+\.\d+).*} $ipFull2 match ip2;
send "route add $ip1.0.0 mask 255.255.0.0 10.0.0.1\r";
expect -re ".*OK!.*>";
send "route add $ip2.0.0 mask 255.255.0.0 10.0.0.1\r";
expect -re ".*OK!.*>";

send "wget --tries=1 -T 60 http://$siteUrl\r";
expect -re ".*>";
set outHttp $expect_out(buffer);
send "wget --tries=1 -T 60 https://$siteHttps --no-check-certificate\r";
expect -re ".*>";
set outHttps $expect_out(buffer);
send "route delete $ip1.0.0\r";
expect -re ".*>";
send "route delete $ip2.0.0\r";
expect -re ".*>";

send "exit\r";
#wait
close $spawn_id;
set passFlag "";
set failFlag "";

puts { 
############################################################################################ 
#Step 6 :Verifying whether the services other than the blocked service can be reached 
############################################################################################ 
} 
if {[regexp {.*200 OK.*} $outHttps match] == 1 && [regexp {.*200 OK.*} $outHttp match] == 1} { 
        set passFlag [expr $failFlag + 1]; 
        puts "The WG allows other services when FTP is blocked." 
                } else { 
        set failFlag [expr $failFlag + 1]; 
        puts "The WG does not allow other services when FTP is blocked." 
} 
 
if {$passFlag == 1} { 
set result "PASSED"; 
} else { 
        if {$failFlag >0 || $passFlag <1} { 
        set result "FAILED"; 
} 
  } 
 
puts { 
################################################################################ 
#Step 7 :Reverting back to its initial values.
################################################################################ 
}  
set output9 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue  Device.X_Comcast_com_ParentalControl.ManagedServices.Enable false boolean]; 
puts $output9; 
if {[regexp {.*Time limit has crossed 2 minutes.*} $output9] == 1 } { 
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection"; 
puts "Failed to set 1st parameter"; 
set result "FAILED"; 
set passContent "Test Result : $result$~"; 
displayProc $passContent; 
exit 0; 
}  
set output10 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_Comcast_com_ParentalControl.ManagedServices.Service.$I.AlwaysBlock false boolean]; 
puts $output10; 
if {[regexp {.*Time limit has crossed 2 minutes.*} $output10] == 1 } { 
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection"; 
puts "Failed to set 2nd parameter"; 
set result "FAILED"; 
set passContent "Test Result : $result$~"; 
displayProc $passContent; 
exit 0; 
}  
 
set passContent "Test Result : $result$~"; 
displayProc $passContent; 

