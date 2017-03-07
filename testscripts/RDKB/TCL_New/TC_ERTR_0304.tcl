package require Expect;
source proc.tcl;
puts {
#########################################################################################################################
#TEST CASE ID :TC_ERTR_0304                                                                                                
#Description  :Verify that when Firewall Config is set to High, ICMP message from WAN to WAN IP of WG should not be allowed
#########################################################################################################################
}
#Initializing the values to the parameters by invoking Initializer proc
set configFile $argv;
Initializer $configFile;


puts {
##########################################################################################################
#Step 1 : Set Firewall to High mode
##########################################################################################################
}
set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_CISCO_COM_Security.Firewall.FirewallLevel High string];
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
#Step 2 :Get the value of parameters that have been set.                                                                     
##########################################################################################################
} 
set output2 "";
set output2 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_CISCO_COM_Security.Firewall.FirewallLevel null null];
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
####################################################################################
#Step 3 :Telnet to WAN client and sending ICMP message to the WAN IP of the gateway                                                                 
####################################################################################
}
spawn telnet $wanIP $wanTelnetPort;
set timeout 100;
expect -re (.*ogin:);
send "$wanName\r";
expect -re (.*word:);
send "$wanPassword\r";
expect -re ".*>";
send "ping $wanIPWG\r";
expect -re ".*>";
set outPing $expect_out(buffer)
#wait
close $spawn_id
set passFlag "";
set failFlag "";
puts {
############################################################################################
#Step 4 :Verifying the reachability of the ICMP message
############################################################################################
}

if {[regexp {.*Lost.*=.*\((.*)% loss\)} $outPing match lossPercent] == 1} {
        if {$lossPercent == 0} {
        set failFlag [expr $failFlag + 1];
        puts "Ping  successful from WAN to WAN IP of gateway when firewall is set to high"
        } else {
        set passFlag [expr $passFlag + 1];
        puts "Ping not successful from WAN to WAN IP of gateway when firewall is set to high"

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
#Step 5 :Reverting the Firewall settings back to its initial value                                                    
##########################################################################################################
}
set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_CISCO_COM_Security.Firewall.FirewallLevel Low string];
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


