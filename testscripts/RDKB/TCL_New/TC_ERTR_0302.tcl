package require Expect;
source proc.tcl;
puts {
##########################################################################################################################################
#TEST CASEID :TC_ERTR_0302                                                                                                                                   
#Description  :Verify that when Firewall Config is set to Custom, Telnet access from LAN to WAN  should be allowed
##########################################################################################################################################
}
#Initializing the values to the parameters by invoking Initializer proc
set configFile $argv;
Initializer $configFile;

puts {
################################################################################
#Step 1 :Enabling the firewall to Custom mode
################################################################################
}

set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_CISCO_COM_Security.Firewall.FirewallLevel Custom string];
puts $output1;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output1] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
after 10000;

puts {
##########################################################################################################
#Step 2 :Get the value of parameters that have been set.                                            
##########################################################################################################
}
set output3 "";
set output3 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_CISCO_COM_Security.Firewall.FirewallLevel null null];
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
#Step 3 :Telnet-int to LAN Client and trying to telnet to client in WAN side                                                               
################################################################################
}
spawn telnet $Telnetip $telnetPort1;
set timeout 100;
expect -re (.*ogin:);
send "$Name\r";
expect -re (.*word:);
send "$password\r";
expect -re ".*#";
send "ip route add $wanIP via 10.0.0.1\r";
expect -re ".*#";
send "telnet $wanIP $wanTelnetPort\r";
set timeout 100;
expect\
{
".*#"
{
set outTelnet $expect_out(buffer);
}
".*ogin:"
{
set outTelnet $expect_out(buffer);
send "$wanName\r";
expect -re (.*word:);
send "$wanPassword\r";
expect -re ".*>";
set outTelnet1 $expect_out(buffer);
send "exit\r";
}
}
expect -re ".*#";
send "ip route delete $wanIP via 10.0.0.1\r";
expect -re ".*#";
#wait
close $spawn_id;
set passFlag "";
set failFlag "";


puts {
############################################################################################
#Step 4 :Verifying the reachability of the Telnet Traffic
############################################################################################
}
proc commented {} {
if {[regexp {.*Connection refused.*} $outTelnet match] == 1 } {
        set passFlag [expr $passFlag + 1];
        puts "Telnet Request not successful.Blocked from LAN to WAN"
                } else {
if {[regexp {.*Trying.*....*} $outTelnet match] == 1 } {
        set failFlag [expr $failFlag + 1];
        puts "Telnet Request not successful as connection timed out"
        } else {
        set failFlag [expr $failFlag + 1];
        puts "Telnet Request successful from LAN to WAN when firewall is set to high"
        }
 }
}

if {[regexp {.*Microsoft.*} $outTelnet1 match] == 1 } {
        set passFlag [expr $passFlag + 1];
         puts "Telnet Request successful from LAN to WAN when firewall is set to Custom";
                } else {
if {[regexp {.*Trying.*....*} $outTelnet match] == 1 } {
        set failFlag [expr $failFlag + 1];
        puts "Telnet Request not successful as connection timed out"
        } else {
        set failFlag [expr $failFlag + 1];
        puts "Telnet Request not successful.Blocked from LAN to WAN"

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
##########################################################################################################
#Step 5 :Reverting the Firewall configurations back to its initial value.                                                    
##########################################################################################################
}
set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_CISCO_COM_Security.Firewall.FirewallLevel Custom string];
puts $output1;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output1] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}


set passContent "Test Result : $result$~";
displayProc $passContent;
