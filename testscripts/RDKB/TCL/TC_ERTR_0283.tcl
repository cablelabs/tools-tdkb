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
########################################################################################################################################## 
#TEST CASEID :TC_ERTR_0283 			
#Description  :Verify that DHCP server configurations are updated without rebooting the client
##########################################################################################################################################
}
#Initializing the values to the parameters by invoking Initializer proc
set configFile $argv;
Initializer $configFile;

puts {
################################################################################
#Step 1 :Set the  DHCPv4 server Gateway IP and subnet mask
################################################################################
}

set output1 "";
set output1 [ exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_CISCO_COM_DeviceControl.LanManagementEntry.1.LanIPAddress 10.0.0.1 string];
puts $output1;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output1] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

set output2 "";
set output2 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_CISCO_COM_DeviceControl.LanManagementEntry.1.LanSubnetMask 255.255.255.0 string];
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
################################################################################
#Step 2 :Get the value of the parameter that has been set                                                             					 
################################################################################
}
set output3 "";
set output3 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_CISCO_COM_DeviceControl.LanManagementEntry.1.LanIPAddress null null];
puts $output3;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output3] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
set output4 "";
set output4 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_CISCO_COM_DeviceControl.LanManagementEntry.1.LanSubnetMask null null];
puts $output4;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output4] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 2nd parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}



puts {
############################################################################################
#Step 3 :Telneting to the LAN client and obtaining its subnet mask and gateway IP address                                                                 					 
############################################################################################
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
#Step 4 :Verifying the Gateway IP and Subnet mask		 				   
############################################################################################
}
if {[regexp { .*lease.* option subnet-mask ([0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}).*} $outIp match Ipval] == 1}  {



	puts "Expected subnet mask  : 255.255.255.0 ";
	puts "Obtained Subnet mask  : $Ipval";
	if {[regexp {255\..*\..*\..*} $Ipval] == 1} {
	set passFlag [expr $passFlag + 1];
	} else {
	set failFlag [expr $failFlag + 1];
		}

}

if {[regexp { .*lease.* option routers (.*) option dhcp-lease-time} $outIp match Ipval] == 1}  {



        puts "Expected IP  : 10.0.0.1 ";
        puts "Obtained IP : $Ipval";
        if {[regexp {10\..*\..*\..*} $Ipval] == 1} {
        set passFlag [expr $passFlag + 1];
        } else {
        set failFlag [expr $failFlag + 1];
                }

}


if {$passFlag == 2} {
set result "PASSED"	
} else {
	if {$failFlag >0 || $passFlag <2} {
	set result "FAILED";
} 
  }


puts {
################################################################################
#Step 5 :Reverting the DHCPv4 server Gateway IP and subnet mask
################################################################################
}
set output5 "";
set output5 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_CISCO_COM_DeviceControl.LanManagementEntry.1.LanIPAddress 10.0.0.1 string];
puts $output5;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output5] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

set output6 "";
set output6 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_CISCO_COM_DeviceControl.LanManagementEntry.1.LanSubnetMask 255.255.255.0 string];
puts $output6;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output6] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 2nd parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

set passContent "Test Result : $result$~";
displayProc $passContent;
