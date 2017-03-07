package require Expect;
source proc.tcl;
source lib.tcl;
#Initializing the values to the parameters by invoking Initializer proc
#set configFile $argv;
set configFile $argv;
Initializer $configFile;
puts {
#####################################################################################
#TESTCASEID : TC_ERTR_0195
#Description  : Verify that the Primary DNS server (IPv4) of WG successfully 
#resolves the DNS queries (Device.DNS.Client.Server.1.DNSServer)
#####################################################################################
}

puts {
#################################################################################
#step 1 :Get the values of the parameter (Device.DNS.Client.Server.1.DNSServer)                               
#################################################################################
}

set response [device_set_get_param $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.DNS.Client.Server.1.DNSServer null null {rType output}];
puts "The Result of Setparameter is $response";

if {[regexp -nocase {VALUE:(.*)\s+TYPE} $response m o]} {

puts $m;
puts $o;
} else {

puts "Unable to grep expected value";
set result "fail";
exit 0;
}


spawn telnet $Telnetip $telnetPort1
set timeout 100;
expect -re (.*ogin:);
send "$Name\r";
expect -re (.*word:);
send "$password\r";
expect -re ".*#";
send -i $spawn_id "nslookup\r";
expect -re ">";
send -i $spawn_id "server $o\r";
expect -re ">";
send -i $spawn_id "www.google.com\r";
expect -re ">";
set clientoutput $expect_out(buffer);

close $spawn_id;


puts $clientoutput;

if {![regexp -nocase {connection timed out; no servers could be reached} $clientoutput]} {
if {[regexp -nocase {Non-authoritative answer:.*Name:.*Address:\s+(\d+.\d+.\d+.\d+)} $clientoutput m out]} {
puts "DNS Primary Server successfully resolves the DNS query";
set result "PASSED";
} else {
puts "DNS Primary Server doesn't resolve the DNS query";
set result "FAILED";
}
}  else {
puts "DNS Primary Server doesn't resolve the DNS query";
set result "FAILED";
}

set passContent "Test Result : $result$~";
displayProc $passContent;


