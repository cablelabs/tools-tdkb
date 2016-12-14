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
#####################################################################################################
#TEST CASEID :TC_ERTR_0270                                                                        
#Description  :Verify that subnet mask of DHCPv4 server pool cannot be set with Broadcast IP address.
#(ex.255.255.255.255). Ensure that DHCP configuration on client is not affected
#####################################################################################################

}
#Initializing the values to the parameters by invoking Initializer proc^M
set configFile $argv;
Initializer $configFile;



puts {
################################################################################
#Step 1 :Get the value of the DHCPv4 server pool subnet mask configured on WG                                 
################################################################################
}

set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.DHCPv4.Server.Pool.1.SubnetMask null null];
puts $output1;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output1] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network 

connection";
puts "Failed to get 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
puts {
##########################################################################################################
#Step 2 :Parsing the Subnet mask from Get Parameter Output                                                                              
##########################################################################################################
}
if {[regexp {.*VALUE:(.*) TYPE.*} $output1 match sub] == 1} {
puts "Subnet mask configured on device: $sub"
}


puts {
################################################################################
#Step 3 :Set the DHCPv4 server pool subnet mask with Broadcast address
################################################################################
}

set output2 "";
set output2 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.DHCPv4.Server.Pool.1.SubnetMask 255.255.255.255 string];
puts $output2;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output2] == 1 } {
puts "Failed to set the parameter."
}

set output3 "";
set output3 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.DHCPv4.Server.Pool.1.SubnetMask null null];
puts $output3;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output3] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

puts {
#######################################################################################
#Step 4 :Telnet-ing to a LAN client and obtaining the subnet mask from DHCP Lease file.
#######################################################################################
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
after 30000;
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
close $spawn_id
set passFlag "";
set failFlag "";

puts {
############################################################################################
#Step 5 :Verifying the DHCPv4 server pool Subnet mask                                                
############################################################################################
}
puts "Expected subnet mask  : $sub ";
if {[regexp {.*fixed-address.*option subnet-mask ([0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}).*} $outIp match Ipval] == 1}  {
puts "Obtained Subnet mask  : $Ipval";
if {$sub == $Ipval} {
puts "Subnet mask is matching";
set passFlag [expr $passFlag + 1];
} else {
puts "Subnet mask is not matching";
set failFlag [expr $failFlag + 1];
 }

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
#Step 6 :Reverting the subnet mask back to its default value.                                                               
################################################################################
}

set output4 "";
set output4 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.DHCPv4.Server.Pool.1.SubnetMask 255.255.255.0 string];
puts $output4;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output4] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";	
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

set passContent "Test Result : $result$~";
displayProc $passContent;


