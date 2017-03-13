package require Expect;
source proc.tcl;
puts {
##########################################################################################################################################
#TEST CASEID :TC_ERTR_0350
#Description  :Verify that when Firewall Config is set to Custom, HTTP access from WLAN to WAN should pass through
##########################################################################################################################################
}
#Initializing the values to the parameters by invoking Initializer proc
set configFile $argv;
Initializer $configFile;

puts {
################################################################################
#Step 1: Set the Firewall to Custom mode
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

puts {
##########################################################################################################
#Step 2 :Get the value of parameters that have been set.                                            
##########################################################################################################
}
set output3 "";
set otuput3 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_CISCO_COM_Security.Firewall.FirewallLevel  null null];
puts $output3;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output3] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
set interface_name1 [split $wlanInterfaceName "_"];
puts {
################################################################################
#Step 3 :Trying to Telnet to WLAN Client and try HTTP request
################################################################################
}
spawn telnet $wlanIP $telnetPort;
set timeout 100;
expect -re (.*ogin:);
send "$wlanAdminName\r";
expect -re (.*word:);
send "$wlanAdminPassword\r";
expect -re ".*>";
send "nslookup\r";
expect -re ".*>";
send "server 10.252.139.244\r";
expect -re ".*>";
send "$siteUrl\r";
expect -re ".*>";
set outUrlResp $expect_out(buffer);
send "exit\r";
expect -re ".*>"
regexp {.*Name.*?([0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}).*} $outUrlResp match ipFull;
regexp {(\d+\.\d+).*} $ipFull match ip;
send "route add $ip.0.0 mask 255.255.0.0 10.0.0.1\r";
expect -re ".*OK!.*>";
send "wget --tries=1 -T 60 http://$siteUrl\r";
expect -re ".*>";
set outHttp $expect_out(buffer);
send "route delete $ip.0.0\r";
expect -re ".*>";
send "exit\r";
proc commented {} {
spawn telnet $wlanIP $telnetPort
set timeout 100;
expect -re (.*ogin:);
send "$wlanAdminName\r";
expect -re (.*word:);
send "$wlanAdminPassword\r";
expect -re ".*>";
send "netsh wlan add profile filename=\"$profilePath\\Wireless.xml\" interface=\"$interface_name1\"\r";
expect -re ".*>";
send "netsh wlan connect $ssid2\r";
expect -re ".*>";
after 30000;
send "route add $wanIP mask 255.255.255.255 10.0.0.1\r";
expect -re ".*OK!.*>";

send "wget --tries=1 -T 60 http://$wanIP/test1.txt\r";
expect -re ".*>";
set outHttp $expect_out(buffer);
send "route delete $wanIP\r";
expect -re ".*OK!.*>";

send "netsh wlan delete \"$ssid2\"\r";
expect -re ".*>";
send "exit\r";
}
#wait
close $spawn_id;
set passFlag "";
set failFlag "";
puts {
############################################################################################
#Step 4 :Verifying the reachability of the HTTP Traffic
############################################################################################
}
if {[regexp {.*200 OK.*} $outHttp match] == 1} {
        set passFlag [expr $passFlag + 1];
        puts "HTTP traffic successful from WLAN to WAN when Firewall is set to Custom"
                } else {
        set failFlag [expr $failFlag + 1];
        puts "HTTP traffic not successful.Blocked from WLAN to WAN"
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
#Step 5 :Reverting the Firewall settings back to its initial value.                                                    
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


set passContent "Test Result : $result$~";
displayProc $passContent;