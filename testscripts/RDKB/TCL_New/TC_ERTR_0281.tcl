package require Expect;
source proc.tcl;
puts {
#########################################################################################################################
#TEST CASE ID :TC_ERTR_0281                                                                                             
#Description  :Verify that Domain name in WG can be updated with a valid domain name. 
#Ensure that client has received the Comcast Domain name configuration
#########################################################################################################################
}
#Initializing the values to the parameters by invoking Initializer proc
set configFile $argv;
Initializer $configFile;


puts {
##########################################################################################################
#Step 1 :Setting a valid domain name in WG.                                                                          
##########################################################################################################
} 

set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.DHCPv4.Server.Pool.1.DomainName example.com string];
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
set output2 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.DHCPv4.Server.Pool.1.DomainName null null];
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
########################################################################################
#Step 3 :Telneting to the LAN client and obtaining the domain name from DHCP Lease file.                                                                 
########################################################################################
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
#Step 4 :Verifying the Domain name
############################################################################################
} 
if {[regexp {.*fixed-address.*option domain-name "(.*)".*} $outIp match domainName] == 1 } {

puts "Expected DomainName :bgqa3.pa.bo.comcast.net"

if {[string compare $domainName bgqa3.pa.bo.comcast.net] == 0} {
puts "Obtained DomainName: $domainName";
puts "Domain Name matching";
        set passFlag [expr $passFlag + 1];
} else {
puts "Obtained DomainName: $domainName";
puts "Domain Name not matching";
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
#Step 5 :Reverting the Domain Name back to its initial value..                                                                
##########################################################################################################
}
set output3 "";
set output3 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.DHCPv4.Server.Pool.1.DomainName bgqa3.pa.bo.comcast.net string];
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

