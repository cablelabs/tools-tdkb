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


