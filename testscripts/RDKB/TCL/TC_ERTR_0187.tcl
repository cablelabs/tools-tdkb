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
puts {
######################################################################################################################### 
#TESTCASE ID: TC_ERTR_0187
#Description:Verify that on disabling DMZ, HTTPs traffic should not passthrough from WAN to WLAN
#########################################################################################################################
} 
#Initializing the values to the parameters by invoking Initializer proc
set configFile $argv;
Initializer $configFile;
set interface_name1 [split $wlanInterfaceName "_"];
puts {
################################################################################
#Step 1:Trying to connect to WG telnet-ing to a WLAN client                                                         
################################################################################
}
spawn telnet $wlanIP $telnetPort
set timeout 100;
expect -re (.*ogin:);
send "$wlanName\r";
expect -re (.*word:);
send "$wlanPassword\r";
expect -re ".*>";
send "netsh wlan add profile filename=\"$profilePath\\Wireless.xml\" interface=\"$interface_name1\"\r";
expect -re ".*>";
send "netsh wlan connect $ssid2\r";
expect -re ".*>";
set outpCon $expect_out(buffer);
after 30000
send "ipconfig\r";
expect -re ".*>";
set outIp $expect_out(buffer);
send "exit\r"
expect -re ".*>";
#wait
close $spawn_id
regexp {Wireless\s*LAN\s*[^\:]*:[^\:]*:[^\:]*:\s*[\w*:]*[^\:]*:\s*[\w*:]*[^\:]*:\s*[\w*:]*[^\:]*:\s*[\w*:]*\W*\w*\s*IPv4\s*Address[^\:]*:\s*(\d+.\d+.\d+.\d+)} $outIp match Ipval;
puts $Ipval;


puts {
##########################################################################################################
#Step 2: Set Firewall to Low and Enable DMZ                                                    			 
##########################################################################################################
}
set voutput1 "";
set voutput1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_CISCO_COM_Security.Firewall.FirewallLevel Low string];
puts $voutput1;
if {[regexp {.*Time limit has crossed 2 minutes.*} $voutput1] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.NAT.X_Comcast_com_EnablePortMapping false boolean ];
puts $output1;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output1] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 2nd parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

set output2 "";
set output2 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.NAT.X_CISCO_COM_DMZ.Enable true boolean ];
puts $output2;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output2] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 3rd parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

set output3 "";
set output3 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.NAT.X_CISCO_COM_DMZ.InternalIP $Ipval string ];
puts $output3;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output3] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 4th parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

puts {
##########################################################################################################
#Step 3 :Get the value of parameters that have been set.                                             
##########################################################################################################
} 

set voutput2 "";
set voutput2 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_CISCO_COM_Security.Firewall.FirewallLevel null null ];
puts $voutput2;
if {[regexp {.*Time limit has crossed 2 minutes.*} $voutput2] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
set output4 "";
set output4 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.NAT.X_Comcast_com_EnablePortMapping null null ];
puts $output4;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output4] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to Get 2nd parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

set output5 "";
set output5 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.NAT.X_CISCO_COM_DMZ.Enable null null ];
puts $output5;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output5] == 1 } {
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 3rd parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

set output6 "";
set output6 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.NAT.X_CISCO_COM_DMZ.InternalIP null null ];
puts $output6;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output6] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 4th parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}


after 30000;

puts {
################################################################################
#Step 4 :Telneting to a WAN client and sending HTTPs Request to a WLAN Client       
################################################################################
} 
spawn telnet $wanIP $wanTelnetPort;
set timeout 100;
expect -re (.*ogin:);
send "$wanName\r";
expect -re (.*word:); 
send "$wanPassword\r";
expect -re ".*>"; 
send "wget --tries=1 -T 60 https://$wanIPWG/test.txt --no-check-certificate\r";
expect -re ".*>";
set outHttp $expect_out(buffer);

#wait
close $spawn_id;
set passFlag "";
set failFlag "";
puts {
############################################################################################
#Step 5 :Verifying the reachability of the HTTPs message                                            
############################################################################################
}
if {[regexp {.*200 OK.*} $outHttp match] == 1} {
        set passFlag [expr $passFlag + 1];
        puts "HTTPs Request successful from WAN to WLAN when firewall is set to Low and DMZ is enabled." 
		} else {
        set failFlag [expr $failFlag + 1];
        puts "HTTPs Request not successful. Blocked from WAN to WLAN"
} 
puts {
##########################################################################################################
#Step 6 :Disable DMZ                                                                      			 
##########################################################################################################
} 
set output7 "";
set output7 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.NAT.X_CISCO_COM_DMZ.Enable false boolean ];
puts $output7;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output7] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 2nd parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

after 15000;

puts {
#####################################################################################
#Step 7 :Telneting to a WAN client and sending HTTPs request again after disabling DMZ                                       
#####################################################################################
}
spawn telnet $wanIP $wanTelnetPort;
set timeout 100;
expect -re (.*ogin:);
send "$wanName\r";
expect -re (.*word:);
send "$wanPassword\r";
expect -re ".*>";
send "wget --tries=1 -T 60 https://$wanIPWG/test.txt --no-check-certificate\r";
expect -re ".*>";
set outHttp $expect_out(buffer);

#wait
close $spawn_id;
puts {
############################################################################################
#Step 8 :Verifying the reachability of the HTTPs message
############################################################################################
}
if {[regexp {.*200 OK.*} $outHttp match] == 1} {
        set failFlag [expr $failFlag + 1];
        puts "HTTPs Request successful from WAN to WLAN when firewall even after DMZ is disabled"
                } else {
        set passFlag [expr $passFlag + 1];
        puts "HTTPs Request not successful.Blocked from WAN to WLAN after disabling DMZ"
}

if {$passFlag == 2} {
set result "PASSED"
} else {
        if {$failFlag >0 || $passFlag <2} {
        set result "FAILED";
}
  }
set passContent "Test Result : $result$~";
displayProc $passContent;

