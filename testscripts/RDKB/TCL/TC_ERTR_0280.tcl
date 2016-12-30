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
package require Expect;
source proc.tcl;
puts {
#########################################################################################################################
#TEST CASE ID :TC_ERTR_0280                                                                                             
#Description  :Verify that DNS server details can be updated with a valid global DNS server in WG (ex.4.4.4.4).
#Ensure that Client receives Comcast DNS server Configurations
#########################################################################################################################
}
#Initializing the values to the parameters by invoking Initializer proc
set configFile $argv;
Initializer $configFile;


puts {
##########################################################################################################
#Step 1 :Setting a valid global DNS server in WG.                                                                          
##########################################################################################################
} 

set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.DHCPv4.Server.Pool.1.DNSServers 4.4.4.4 string];
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
#Step 2 :Getting the value of parameters that have been set.                                                                          
##########################################################################################################
} 
set output2 "";
set output2 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.DHCPv4.Server.Pool.1.DNSServers null null];
puts $output2;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output2] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
} 


puts {
##############################################################################################
#Step 3 :Telneting to the LAN client and obtaining the DNS server address from DHCP Lease file                                                              
##############################################################################################
} 
spawn telnet $Telnetip;
set timeout 100;
expect -re (.*ogin:);
send "$Name\r";
expect -re (.*word:);
send "$password\r";
expect -re ".*#";
send "service network restart\r";
expect -re ".*#";
send "ls -ltr /var/lib/dhclient/dhclient-* | grep eth$intNo\r";
expect -re ".*#";
set outInt $expect_out(buffer);
set b [split $outInt "\n"];
puts $b;
set l [llength $b];
puts $l;
set l [expr $l - 2];
puts $l;
set g [lindex $b $l];
puts $g;
set h [regexp -nocase ".*(\/var.*)" $g match output];
puts $h;
puts $output;
send "cat $output\r";
expect -re ".*#";
set outIp $expect_out(buffer);
#wait
close $spawn_id;
set passFlag "";
set failFlag "";
puts {
############################################################################################
#Step 4 :Verifying the DNS Server address.                                                 
############################################################################################
} 
puts "Expected DNS server: $DnsServerIp"
if {[regexp {.*fixed-address.*option domain-name-servers ([0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}).*} $outIp match dnsAddr] == 1 } {


if {[string compare $dnsAddr $DnsServerIp] == 0} {
puts "Obtained DNS server: $dnsAddr";
puts "DNS Address matching";
        set passFlag [expr $passFlag + 1];
} else {
puts "Obtained DNS server: $dnsAddr";
puts "DNS Address not matching";
        set failFlag [expr $failFlag + 1];
}
} 

if {$passFlag == 1} {
set result "PASSED";
} else {
        if {$failFlag >0 || $passFlag <1} {
        set result "FAILED";
}
 }

 puts {
##########################################################################################################
#Step 5 :Reverting the DNS Server back to its initial value..                                                                
##########################################################################################################
}
set output3 "";
set output3 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.DHCPv4.Server.Pool.1.DNSServers $DnsServerIp string];
puts $output3;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output3] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
} 
set passContent "Test Result : $result$~";
displayProc $passContent;

