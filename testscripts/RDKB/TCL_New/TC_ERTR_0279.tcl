package require Expect;
source proc.tcl;
puts {
########################################################################################################################################## 
#TEST CASEID :TC_ERTR_0279 							
#Description  :Verify that LAN DHCP clients receive Domain name configuration from Wireless Gateway
##########################################################################################################################################
}
#Initializing the values to the parameters by invoking Initializer proc
set configFile $argv;
Initializer $configFile;

puts {
################################################################################
#Step 1 :Get the DHCPv4 Server Pool Domain name 
################################################################################
}

set output2 "";
set output2 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.DHCPv4.Server.Pool.1.DomainName null null];

puts $output2;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output2] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get required parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

if {[regexp {.*VALUE:(.*) TYPE.*} $output2 match Dns] == 1} {
puts "Obtained DNS server address: $Dns"
}

puts {
#######################################################################################
#Step 2 :Telnet-ing to a LAN client and obtaining the domain name from DHCP Lease file.
#######################################################################################
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
close $spawn_id
set passFlag "";
set failFlag "";

puts {
############################################################################################
#Step 3 :Verifying the Domain name configured on the LAN Client
############################################################################################
}
puts "Expected Domain name  : $Dns  ";
if {[regexp {.*lease.* option domain-name "(.*)".*renew} $outIp match Ipval] == 1}  {
	
	if {[string equal $Dns $Ipval] == 1} {
	puts "Obtained Domain name  : $Ipval";
	puts "Domain names are matching";
	set passFlag [expr $passFlag + 1];
	} else {
	puts "Obtained Domain name  : $Ipval";
	puts "Domain names are not matching";
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


set passContent "Test Result : $result$~";
displayProc $passContent;
