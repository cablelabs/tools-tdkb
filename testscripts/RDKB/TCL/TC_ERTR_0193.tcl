#
# ============================================================================
# COMCAST CONFIDENTIAL AND PROPRIETARY
# ============================================================================
# This file and its contents are the intellectual property of Comcast.  It may
# not be used, copied, distributed or otherwise  disclosed in whole or in part
# without the express written permission of Comcast.
# ============================================================================
# Copyright (c) 2016 Comcast. All rights reserved.
# ============================================================================
#

package require Expect;
source proc.tcl;
puts {
######################################################################################################################### 
#TEST CASEID :TC_ERTR_0193 					
#Description  :Verify that DHCPv4 server pool can be set with Class B private IP address range 172.16.x.x - 172.31.255.255. Ensure that ethernet client obtains IP within the range
#########################################################################################################################
}
#Initializing the values to the parameters by invoking Initializer proc
set configFile $argv;
Initializer $configFile;

puts {
################################################################################
#Step 1 :Set server pool and gateway IP with class B private IP address
################################################################################
}
set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_CISCO_COM_DeviceControl.LanManagementEntry.1.LanIPAddress 172.16.0.1 string];
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
set output2 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_CISCO_COM_DeviceControl.LanManagementEntry.1.LanSubnetMask 255.255.255.0  string];
puts $output2;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output2] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

set output3 "";
set output3 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.DHCPv4.Server.Pool.1.MinAddress 172.16.0.2 string];
puts $output3;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output3] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

set output4 "";
set output4 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.DHCPv4.Server.Pool.1.MaxAddress 172.16.0.253 string];
puts $output4;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output4] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}


puts {
################################################################################
#Step 2 :Get the values of the parameters that have been set.                                         
################################################################################
}


set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_CISCO_COM_DeviceControl.LanManagementEntry.1.LanIPAddress null null];
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
set output2 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_CISCO_COM_DeviceControl.LanManagementEntry.1.LanSubnetMask null null];
puts $output2;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output2] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

set output3 "";
set output3 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.DHCPv4.Server.Pool.1.MinAddress null null];
puts $output3;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output3] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

set output4 "";
set output4 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.DHCPv4.Server.Pool.1.MaxAddress null null];
puts $output4;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output4] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

after 120000;
puts {
################################################################################
#Step 3 Telnet-ing to a LAN client and obtaining the IP address
################################################################################
}
spawn telnet $Telnetip;
set timeout 100;
expect -re (.*ogin:);
send "$Name\r";
expect -re (.*word:);
send "$password\r";
expect -re ".*#";
send "service network restart\r"
expect -re ".*#";
after 10000;
send "ifconfig\r";
expect -re ".*#";
set outIPadd $expect_out(buffer);
#send "cat $leaseCommand\r";
#expect -re ".*#";
#set outIp $expect_out(buffer);
#wait
close $spawn_id
set passFlag "";
set failFlag "";


puts {
############################################################################################
#Step 4 :Verifying whether the Ethernet Client has got IP in Class B Private range	 				   
############################################################################################
}
if {[regexp {.*eth.*inet addr:([0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}).*Bcast:.*.0.255.*} $outIPadd match gIp] == 1 } {
        puts "Expected Value : '172.16.0.2 - 172.16.0.253'";
	if {[regexp {172\.16\..*\..*} $gIp match] == 1} {	
	puts "Obtained Value :  $gIp";
	puts "IP address obtained within the correct DHCP range for Ethernet Client";
	set passFlag [expr $passFlag + 1];
	} else {
	puts "Obtained Value :  $gIp";
	puts "IP address not obtained within the correct DHCP range for Ethernet Client";
	set failFlag [expr $failFlag + 1];
		}

} else {
puts "IP address not obtained";
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
#Step 5 :Reverting the DHCPv4 server to its initial value.                                        
################################################################################
}

set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_CISCO_COM_DeviceControl.LanManagementEntry.1.LanIPAddress 10.0.0.1 string];
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
set output2 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_CISCO_COM_DeviceControl.LanManagementEntry.1.LanSubnetMask 255.255.255.0  string];
puts $output2;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output2] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

set output3 "";
set output3 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.DHCPv4.Server.Pool.1.MinAddress 10.0.0.2 string];
puts $output3;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output3] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

set output4 "";
set output4 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.DHCPv4.Server.Pool.1.MaxAddress 10.0.0.253 string];
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
