package require Expect;
source proc.tcl;
puts {
###################################################################################################
#TEST CASEID :TC_ERTR_0275                                                                         
            
#Description  :Verify that DHCPv4 Server lease time cannot be set less than 2 minutes (120 seconds).
#Ensure that DHCP configuration on client is not affected
##################################################################################################
}
#Initializing the values to the parameters by invoking Initializer proc^M
set configFile $argv;
Initializer $configFile;



puts {
################################################################################
#Step 1 :Get the value of the DHCPv4 server lease time                                        
################################################################################
}

set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.DHCPv4.Server.Pool.1.LeaseTime null null];
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

if {[regexp {.*VALUE:(.*)TYPE.*} $output1 match lease] == 1} {
puts "Lease time configured on device: $lease"
}


puts {
################################################################################
#Step 2 :Set the DHCPv4 server pool lease time with value less than 120sec
################################################################################
}

set output2 "";
set output2 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.DHCPv4.Server.Pool.1.LeaseTime 60 int];
puts $output2;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output2] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network 

connection";
puts "Failed to set 1st parameter";

}
puts {
################################################################################
#Step 3 :Get the value of the DHCPv4 server pool lease time                       
################################################################################
}
set output3 "";
set output3 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.DHCPv4.Server.Pool.1.LeaseTime null null];
puts $output3;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output3] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network 

connection";
puts "Failed to get the value of parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}


puts {
###########################################################################################
#Step 4 :Telnet-ing to a LAN client and obtaining the DHCP lease time from DHCP Lease file.
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
#Step 5 :Verifying the DHCPv4 server pool Lease Time                                           
############################################################################################
}
puts "Expected Lease Time : $lease ";
if {[regexp {.*fixed-address.*option dhcp-lease-time ([0-9]{1,8})\;.*} $outIp match Lval] == 1}  { 
        puts "Obtained Lease Time : $Lval ";
        if { $lease == $Lval } {
        puts "Lease Time is matching";
        set passFlag [expr $passFlag + 1];
        } else {
        puts "Lease Time is not matching";
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
#Step 6 :Reverting the Lease time back to its default value.                                                                          			 
################################################################################
}

set voutput "";
set voutput [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValu Device.DHCPv4.Server.Pool.1.LeaseTime 604800 int];
puts $voutput;
if {[regexp {.*Time limit has crossed 2 minutes.*} $voutput] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";	
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

set passContent "Test Result : $result$~";
displayProc $passContent;


