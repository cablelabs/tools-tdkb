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
##########################################################################################################################################
#TEST CASEID :TC_ERTR_0078                                                                                                                                                                            
#Description  :Verify that when Firewall Config is set to Medium, HTTPS access from WLAN to WAN should pass through
##########################################################################################################################################
}
#Initializing the values to the parameters by invoking Initializer proc
set configFile $argv;
Initializer $configFile;

puts {
################################################################################
#Step 1 :Setting the firewall configuration in Medium mode.
################################################################################
}

set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_CISCO_COM_Security.Firewall.FirewallLevel Medium string];
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
##########################################################################################################
#Step 2 :Get the value of parameters that have been set.                                            
##########################################################################################################
}
set output3 "";
set output3 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_CISCO_COM_Security.Firewall.FirewallLevel  null null];
puts $output3;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output3] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
set interface_name1 [split $wlanInterfaceName "_"];
puts {
################################################################################
#Step 3 :Trying to connect to CM telnet-ing to a WLAN server                                                                  
################################################################################
}
spawn telnet $wlanIP $telnetPort;
set timeout 100;
expect -re (.*ogin:);
send "$wlanAdminName\r";
expect -re (.*word:);
send "$wlanAdminPassword\r";
expect -re ".*>";
send "netsh wlan add profile filename=\"$profilePath\\Wireless.xml\" interface=\"$interface_name1\"\r";
expect -re ".*>";
send "netsh wlan connect $ssid2\r";
expect -re ".*>";
after 30000;
send "ipconfig\r";
expect -re ".*>";
set outIp $expect_out(buffer);
if { [regexp {Wireless\s*LAN\s*[^\:]*:[^\:]*:[^\:]*:\s*[\w*:]*[^\:]*:\s*[\w*:]*[^\:]*:\s*[\w*:]*[^\:]*:\s*[\w*:]*\W*\w*\s*IPv4\s*Address[^\:]*:\s*(\d+.\d+.\d+.\d+)} $outIp match ip] == 1} {
        if {[regexp {169\.254\..*\..*} $ip] == 1 || [regexp {127\.0\.0\.0} $ip] == 1 } {
        puts "Test case failed; Unable to obtain IP\n";
        set result "FAILED";
        set passContent "Test Result : $result$~";
        displayProc $passContent;
        exit 0;
        } else {
        if {[regexp {10\..*\..*\..*} $ip] == 1} {
        puts "Connection Successful";
        puts "IP obtained is: $ip\n";
                } else {
         puts "\IP address not obtained.";
        set result "FAILED";
        set passContent "Test Result : $result$~";
        displayProc $passContent;
        exit 0;

}
}
}
send "nslookup\r";
expect -re ".*>";
send "server $DnsServerIp\r";
expect -re ".*>";
send "$siteHttps\r";
expect -re ".*>";
set outUrlResp $expect_out(buffer);
send "exit\r";
expect -re ".*>"
regexp {.*Name.*?([0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}).*} $outUrlResp match ipFull;
regexp {(\d+\.\d+).*} $ipFull match ip;
send "route add $ip.0.0 mask 255.255.0.0 10.0.0.1\r";
expect -re ".*OK!.*>";
send "wget --tries=1 -T 60 https://$siteHttps --no-check-certificate\r";
expect -re ".*>";
set outHttps $expect_out(buffer);
send "route delete $ip.0.0\r";
expect -re ".*>";
send "exit\r";
expect -re ".*>";
close $spawn_id;
set passFlag "";
set failFlag "";

puts {
############################################################################################
#Step 4 :Verifying the reachability of the HTTPS Traffic
############################################################################################
}

if {[regexp {.*200 OK.*} $outHttps match] == 1} {
        set passFlag [expr $passFlag + 1];
        puts "HTTPS traffic successful from WLAN to WAN when Firewall is set to Medium"
                } else {
        set failFlag [expr $failFlag + 1];
        puts "HTTPS traffic not successful.Blocked from WLAN to WAN"
}

if {$passFlag == 1} {
set result "PASSED"
} else {
        if {$failFlag >0 || $passFlag <1} {
        set result "FAILED";
}
  }
  
     puts {
##########################################################################################################
#Step 5 :Reverting the Firewall configurations back to its initial value.                                                    
##########################################################################################################
}
set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_CISCO_COM_Security.Firewall.FirewallLevel Low string];
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
