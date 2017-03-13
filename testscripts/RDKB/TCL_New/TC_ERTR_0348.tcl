package require Expect;
source proc.tcl;
puts {
#########################################################################################################################
#TEST CASE ID :TC_ERTR_0348                                                                                                  
#Description  :Verify that when Firewall Config is set to Medium, FTP access from WLAN to WAN should be allowed.
#########################################################################################################################
}
#Initializing the values to the parameters by invoking Initializer proc
set configFile $argv;
Initializer $configFile;

puts {
##########################################################################################################
#Step 1 :Set Firewall mode to Medium                                                                                 
##########################################################################################################
}
set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_CISCO_COM_Security.Firewall.FirewallLevel Medium string];
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
#Step 2 :Get the value of parameters that have been set
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

set interface_name1 [split $wlanInterfaceName "_"];
puts {
################################################################################
#Step 3 :Trying to Telnet to WLAN Client and perform FTP to WAN Client                                   
################################################################################
}
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
set outpCon $expect_out(buffer);
after 30000;
send "ipconfig\r";
expect -re ".*>";
set outIp $expect_out(buffer);
if { [regexp {.*Wireless LAN.*IPv4 Address.*: (.*) Sub.*Ethernet} $outIp match ip] == 1 } {
        if {[regexp {169\.254\..*\..*} $ip] == 1 || [regexp {127\.0\.0\.0} $ip] == 1 } {
        puts "Test case failed; Unable to obtain IP\n";
        set result "FAILED";
        set passContent "Test Result : $result$~";
        displayProc $passContent;
        exit 0;
        } else {
        if {[regexp {10\..*\..*\..*} $ip] == 1} {
        puts "Connection Successful";
        puts "IP obtained is: $ip\n";
                } else {
         puts "\IP address not obtained.";
        set result "FAILED";
        set passContent "Test Result : $result$~";
        displayProc $passContent;
        exit 0;

}
}
}


send "route add $wanIP mask 255.255.255.255 10.0.0.1\r";
expect -re ".*OK!.*>";

send "ftp $wanIP $wanFtpPort\r";
expect\
{
".*ftp:"
{
set outFtp $expect_out(buffer);
}
".*):"
{
send "$wanFtpName\r";
expect -re (.*:);
send "$wanFtpPassword\r";
expect -re (.*230);
set outFtp $expect_out(buffer);
send "bye\r";
}
}
#wait
send "route delete $wanIP\r";
expect -re ".*OK!.*>";

close $spawn_id;
set passFlag "";
set failFlag "";
puts {
################################################################################
#Step 4 :Verifying the connection to the proper SSID
################################################################################
}

if {[regexp {There is no profile "$ssid2" assigned to the specified interface.} $outpCon match] == 1} {

        puts "\nMissing profile. Please ensure that you create a profile and then try connecting";
        set failFlag [expr $failFlag + 1];
        set result "FAILED";
        set passContent "Test Result : $result$~";
        displayProc $passContent;
        exit 0;

 }
        if {[regexp {Connection request was completed successfully.} $outpCon match] == 1} {
        set passFlag [expr $passFlag + 1];
        if { [regexp {.*Wireless LAN.*IPv4 Address.*: (.*) Sub.*Ethernet} $outIp match ip] == 1 } {
        set passFlag [expr $passFlag + 1];
        if {[regexp {169\.254\..*\..*} $ip] == 1 || [regexp {127\.0\.0\.0} $ip] == 1 } {

        puts "Test case failed; Unable to obtain IP\n";
        set failFlag [expr $failFlag + 1];

        } else {

        if {[regexp {10\..*\..*\..*} $ip] == 1} {
        puts "Connection Successful";
        puts "IP obtained is: $ip\n";
        set passFlag [expr $passFlag + 1];

                }
        }


} else {
         puts "\IP address not obtained.";
         set failFlag [expr $failFlag + 1];
}
} else {
         puts "\Connection not successful.";
         set failFlag [expr $failFlag + 1];
}
puts {
############################################################################################
#Step 5 :Verifying the FTP access
############################################################################################
}
if {[regexp {.*230.*} $outFtp match] == 1} {
        set passFlag [expr $passFlag + 1];
        puts "FTP access is allowed from WLAN to WAN when firewall is set to medium"
                } else {
        set failFlag [expr $failFlag + 1];
        puts "FTP access blocked from WLAN to WAN"
}

if {$passFlag == 4} {
set result "PASSED"
} else {
        if {$failFlag >0 || $passFlag <4} {
        set result "FAILED";
}
  }

 puts {
##########################################################################################################
#Step 6 :Reverting the Firewall mode back to its initial value
##########################################################################################################
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
