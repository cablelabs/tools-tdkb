package require Expect; 
source proc.tcl; 
puts { 
##########################################################################################################################################  
#TEST CASEID :TC_ERTR_0284
#Description  :Verify that when Firewall Config is set to High, ICMP message from LAN to WAN should be blocked
########################################################################################################################################## 
} 
#Initializing the values to the parameters by invoking Initializer proc 
set configFile $argv;
Initializer $configFile;
 

puts {
################################################################################ 
#Step 1 :Set the firewall to High
################################################################################ 
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
puts "Failed to get 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
after 20000;
puts { 
#################################################################################### 
#Step 3 :Telneting to a LAN client and sending ICMP message to a client in WAN side
#################################################################################### 
} 
spawn telnet $Telnetip $telnetPort1; 
set timeout 100; 
expect -re (.*ogin:); 
send "$Name\r";
expect -re (.*word:);  
send "$password\r"; 
expect -re ".*#";
send "service vsftpd stop\r";
expect -re ".*#";
send "service httpd stop\r";
expect -re ".*#";
send "sudo /opt/lampp/lampp start\r";
expect -re ".*#";
send "ip route add $wanIP via 10.0.0.1\r"
expect -re ".*#";
after 10000;
send "ping -c 4 $wanIP\r";
expect -re ".*#";
set outPing $expect_out(buffer);
send "ip route delete $wanIP via 10.0.0.1\r"
expect -re ".*#";
#wait 
close $spawn_id 
set passFlag "";
set failFlag "";
puts { 
############################################################################################ 
#Step 4 :Verifying the reachability of the ICMP message                                             
############################################################################################ 
} 

if {[regexp {.*4 packets transmitted.* (.*)% packet loss.*} $outPing match lossPercent] == 1} {
        if {$lossPercent == 100} {
        set passFlag [expr $passFlag + 1];
        puts "Ping not successful from LAN to WAN when firewall is set to High"
        } else {
        set failFlag [expr $failFlag + 1];
        puts "Ping successful from LAN to WAN when firewall is set to High"

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
#Step 5 :Reverting the Firewall settings to initial values.                                                                               
################################################################################ 
}
set output3 "";
set output3 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_CISCO_COM_Security.Firewall.FirewallLevel Low string];
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
