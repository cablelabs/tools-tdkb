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
source lib.tcl;
#Initializing the values to the parameters by invoking Initializer proc
#set configFile $argv;
set configFile $argv;
Initializer $configFile;
puts {
#####################################################################################
#TESTCASEID : TC_ERTR_0197
#Description  : Verify that DNS queries fails when different DNS server is selected 
#other than Primary & Secondary Comcast DNS server.

#####################################################################################
}

puts {
#################################################################################
#step 1 : Set the DNS server other than primary and secondary server
#################################################################################
}


spawn telnet $Telnetip
set timeout 100;
expect -re (.*ogin:);
send "$Name\r";
expect -re (.*word:);
send "$password\r";
expect -re ".*#";
send -i $spawn_id "nslookup\r";
expect -re ">";
send -i $spawn_id "server 10.34.235.207\r";
expect -re ">";
send -i $spawn_id "www.google.com\r";
expect -re ">";
set clientoutput $expect_out(buffer);

close $spawn_id;


puts $clientoutput;


set regout [regexp -nocase {connection timed out; no servers could be reached} $clientoutput m out];

puts $regout;
puts $m;
puts $out;


if { $regout == 1 } {
puts "DNS query not resolved successfully";
set result "PASSED";
} else { 
puts "DNS query resolved successfully";
set result "FAILED";
}


set passContent "Test Result : $result$~";
displayProc $passContent;


