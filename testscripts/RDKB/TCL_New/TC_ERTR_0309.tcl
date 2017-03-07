package require Expect;
source proc.tcl;
puts {
########################################################################################################################################## 
#TEST CASEID :TC_ERTR_0309
#Description  :Verify that DHCP Lease time can be set with a negative integer(-1) (indicates infinite lease time)
##########################################################################################################################################
}
#Initializing the values to the parameters by invoking Initializer proc
set configFile $argv;
Initializer $configFile;

puts {
################################################################################
#Step 1 :Get the value of lease time of DHCPv4 server
################################################################################
}
set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.DHCPv4.Server.Pool.1.LeaseTime null null];
puts $output1;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output1] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}


puts {
################################################################################
#Step 2 :Set the value of lease time to -1                                                               					 
################################################################################
}

set output2 "";
set output2 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.DHCPv4.Server.Pool.1.LeaseTime -1 int];
puts $output2;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output2] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
}

after 30000;
puts {
################################################################################
#Step 3 :Get the value of lease time of DHCPv4 server
################################################################################
}


set output3 "";
set output3 [ exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.DHCPv4.Server.Pool.1.LeaseTime null null];
puts $output3;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output3] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get the value of the parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
after 45000;
puts {
###########################################################################################
#Step 3 :Telnet-ing to a LAN client and obtaining the DHCP lease time from DHCP Lease file.                                                              
###########################################################################################
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
send "ls -ltr /var/lib/dhclient/dhclient-* | grep eth$intNo\r";
after 10000;
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
#Step 4 :Verifying whether the Lease times are matching		 				   
############################################################################################
}

if {[regexp {.*fixed-address.*option dhcp-lease-time ([0-9]{1,11})\;.*} $outIp match Ipval] == 1 } {


	puts "Expected Lease : 4294967295;";
	puts "Obtained Lease : $Ipval";
	if {[regexp {4294967295} $Ipval] == 1} {
	puts "Lease time is matching";
	set passFlag [expr $passFlag + 1];
	} else {
	puts "Lease time is not matching";
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
#Step 5 :Reverting the DHCPv4 server lease time back to its initial value.                                                                               
################################################################################
}
set output2 "";
set output2 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.DHCPv4.Server.Pool.1.LeaseTime 604800 int];
puts $output2;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output2] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

set passContent "Test Result : $result$~";
displayProc $passContent;
