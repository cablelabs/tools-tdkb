package require Expect;
source proc.tcl;
puts {
################################################################################################################################
#TEST CASEID :TC_ERTR_0277                                                                                                                                   #Description  :Verify that the client reuses the same ip address when disconnected and reconnected when the lease period expires
################################################################################################################################
}
#Initializing the values to the parameters by invoking Initializer proc
set configFile $argv;
Initializer $configFile;


puts {
################################################################################
#Step 1 :Setting the value of lease time for DHCP server.
################################################################################
}

set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.DHCPv4.Server.Pool.1.LeaseTime 120 int];
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
################################################################################
#Step 2 :Get the values of the parameters that have been set                                                              
################################################################################
}
set output3 "";
set output3 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.DHCPv4.Server.Pool.1.LeaseTime null null];
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
################################################################################
#Step 3 :Telneting to the LAN client and disconnecting and reconnecting it                                                   
################################################################################
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
send "ifconfig\r";
expect -re ".*#";
set outIp1 $expect_out(buffer);
send "ifconfig eth$intNo down\r";
expect -re ".*#";
after 120000;
send "ifconfig eth$intNo up\r";
expect -re ".*#";
after 40000;
send "service network restart\r";
expect -re ".*#";
send "ifconfig\r";
expect -re ".*#";
set outIp2 $expect_out(buffer);
#wait
close $spawn_id
set passFlag "";
set failFlag "";

puts {
############################################################################################
#Step 4 :Checking whether the IP addresses obtained prior to and after restarting are equal.                                                
############################################################################################
}

if {[regexp {.*inet addr:([0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3})  Bcast:(.*).*0.255.*} $outIp1 match Ipval1] == 1 && [regexp {.*inet addr:([0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3})  Bcast:(.*).*0.255.*} $outIp2 match Ipval2] == 1  } {


        puts "IP prior to restarting the ethernet port: $Ipval1";
        puts "IP after restarting the ethernet port: $Ipval2";
        if {[string equal $Ipval1 $Ipval2] == 1} {
        puts "IP addresses are matching";
		set passFlag [expr $passFlag + 1];
        } else {
	puts "IP addresses are not matching";
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

