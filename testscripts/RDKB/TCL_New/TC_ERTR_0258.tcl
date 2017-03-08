package require Expect;
source proc.tcl;
puts {
#########################################################################################################################
#TEST CASE ID :TC_ERTR_0258                                                                                                
#Description  :Verify that Gateway IP in DHCPv4 server pool cannot be set with Multicast IP address range 
#224.x.x.x - 239.x.x.x. (ex.224.0.0.1). Ensure that DHCP configuration on client is not affected
#########################################################################################################################
}
#Initializing the values to the parameters by invoking Initializer proc
set configFile $argv;
Initializer $configFile;

set result "";
puts {
##########################################################################################################
#Step 1 :Getting the value of Gateway IP configured on WG                                                                    
##########################################################################################################
}

set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_CISCO_COM_DeviceControl.LanManagementEntry.1.LanIPAddress null null];
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
##########################################################################################################
#Step 2 :Parsing the Gateway IP from Get Parameter Output.                                                                            
##########################################################################################################
}
if {[regexp {.*VALUE:(.*) TYPE.*} $output1 match gatewayIP] == 1} {
puts "Gateway IP configured on device: $gatewayIP"
}

puts {
##########################################################################################################
#Step 3 :Setting the value of gateway IP with Multicast IP address.                                                          
##########################################################################################################
}
set output2 "";
set output2 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_CISCO_COM_DeviceControl.LanManagementEntry.1.LanIPAddress 224.0.0.1 string];
puts $output2;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output2] == 1 } {
puts "Failed to set the parameter."
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

puts {
####################################################################################
#Step 4:Telnet-ing to a LAN client and obtaining the IP address from DHCP Lease file                                                              
####################################################################################
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
set result "";
set passFlag "";
set failFlag "";
puts {
############################################################################################
#Step 5 :Verifying the Gateway IP address.                                                 
############################################################################################
}

puts "Expected Gateway IP : $gatewayIP ";
if {[regexp {.*fixed-address.*option routers ([0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}).*} $outIp match gIP] == 1}  {
puts "Obtained Gateway IP : $gIP ";
if {$gatewayIP == $gIP} {
puts "Gateway IP matching";
        set passFlag [expr $passFlag + 1];
} else {
puts "Gateway IP not matching";
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
#Step 6 :Reverting the Gateway IP back to its default value..                                                                
##########################################################################################################
}

set output4 "";
set output4 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_CISCO_COM_DeviceControl.LanManagementEntry.1.LanIPAddress 10.0.0.1 string];
puts $output4;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output4] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;

}

set passContent "Test Result : $result$~";
displayProc $passContent;


