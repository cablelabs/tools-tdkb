package require Expect;
source proc.tcl;
puts {
#########################################################################################################################
#TEST CASE ID :TC_ERTR_0184
#Description : Verify that on disabling Port Forwarding, HTTPs traffic should not passthrough from WAN to WLAN
#########################################################################################################################
} 

#Initializing the values to the parameters by invoking Initializer proc
set configFile $argv;
Initializer $configFile;
set interface_name1 [split $wlanInterfaceName "_"];
puts {
################################################################################
#Step 1 :Trying to connect to WG telnet-ing to a WLAN client                                                    
################################################################################
}
spawn telnet $wlanIP $telnetPort
set timeout 100;
expect -re (.*ogin:);
send "$wlanName\r";
expect -re (.*word:);
send "$wlanPassword\r";
expect -re ".*>";
send "netsh wlan add profile filename=\"$profilePath\\Wireless.xml\" interface=\"$interface_name1\"\r";
expect -re ".*>";
send "netsh wlan connect $ssid2\r";
expect -re ".*>";
set outpCon $expect_out(buffer);
after 30000
send "ipconfig\r";
expect -re ".*>";
set outIp $expect_out(buffer);
send "exit\r"
expect -re ".*>";
#wait
close $spawn_id
regexp {.*Wireless.*IPv4 Address.*:.*(10\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}).*10.0.0.1.*} $outIp match Ipval;
puts $Ipval;


puts {
##########################################################################################################
#Step 2 :Setting the firewall to Low and enabling Port Forwarding.                                                        
##########################################################################################################
}
proc commented {} {
set voutput1 "";
set voutput1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType AddObject Device.NAT.PortMapping. null null];
puts $voutput1;
if {[regexp {.*Time limit has crossed 2 minutes.*} $voutput1] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
}
set voutput2 "";
set voutput2 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.NAT.PortMapping.1.Status null null];
puts $voutput2;
if {[regexp {.*Time limit has crossed 2 minutes.*} $voutput2] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

if {[regexp {.*Device.NAT.PortMapping.(.*).Status.*} $voutput2 match P] == 1} {
puts "instance configured is: $P"
}
 
set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.NAT.X_Comcast_com_EnablePortMapping true boolean];
puts $output1;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output1] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}


set output2 "";
set output2 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_CISCO_COM_Security.Firewall.FirewallLevel Low string];
puts $output2;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output2] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}


set output3 "";
set output3 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetMultipleParameterValues  Device.NAT.PortMapping.$P.Enable,Device.NAT.PortMapping.$P.ExternalPort,Device.NAT.PortMapping.$P.ExternalPortEndRange,Device.NAT.PortMapping.$P.Protocol,Device.NAT.PortMapping.$P.InternalClient,Device.NAT.PortMapping.$P.Description true,443,443,BOTH,$Ipval,HTTPS boolean,unsignedInt,unsignedInt,string,string,string];
puts $output3;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output3] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";	
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
puts {
##########################################################################################################
#Step 3 :Get the value of parameters that have been set.                                               
##########################################################################################################
} 
set voutput "";
set voutput [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue  Device.NAT.X_Comcast_com_EnablePortMapping  null null];
puts $voutput;
if {[regexp {.*Time limit has crossed 2 minutes.*} $voutput] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

set output4 "";
set output4 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_CISCO_COM_Security.Firewall.FirewallLevel null null];
puts $output4;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output4] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 1st parameter";
set result "FAILED";	
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
} 
set output5 "";
set output5 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.NAT.PortMapping.$P.Enable null null];
puts $output2;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output5] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 2nd parameter";
set result "FAILED";	
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;

} 
 
set output6 "";
set output6 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.NAT.PortMapping.$P.ExternalPort null null];
puts $output6;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output6] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 3rd parameter";
set result "FAILED";	
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
} 
set output7 "";
set output7 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.NAT.PortMapping.$P.ExternalPortEndRange null null];
puts $output7;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output7] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 4th parameter";
set result "FAILED";	
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
} 
set output8 "";
set output8 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.NAT.PortMapping.$P.Protocol null null];
puts $output8;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output8] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 5th parameter";
set result "FAILED";	
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
} 
set output9 "";
set output9 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.NAT.PortMapping.$P.InternalClient null null];
puts $output9;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output9] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 6th parameter";
set result "FAILED";	
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
} 
set output10 "";
set output10 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.NAT.PortMapping.$P.Description null null];
puts $output10
if {[regexp {.*Time limit has crossed 2 minutes.*} $output10] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 7h parameter";
set result "FAILED";	
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
} 

after 30000;
puts {
################################################################################
#Step 4 :Telneting to a WAN client and sending HTTPs request to a WLAN Client                                             
################################################################################
} 
spawn telnet $wanIP $wanTelnetPort;
set timeout 100;
expect -re (.*ogin:);
send "$wanName\r";
expect -re (.*word:); 
send "$wanPassword\r";
expect -re ".*>"; 
send "wget --tries=1 -T 60 https://$wanIPWG/test.txt --no-check-certificate\r";
expect -re ".*>";
set outHttp $expect_out(buffer);

#wait
close $spawn_id;
set passFlag "";
set failFlag "";
puts {
############################################################################################
#Step 5 :Verifying the reachability of the HTTPs request                 
############################################################################################
}
if {[regexp {.*200 OK.*} $outHttp match] == 1} {
        set passFlag [expr $passFlag + 1];
        puts "HTTPs Request successful from WAN to WLAN when firewall is set to Low and port forwarding is enabled." 
		} else {
        set failFlag [expr $failFlag + 1];
        puts "HTTPs Request not successful.Blocked from WAN to WLAN"
} 

puts {
##########################################################################################################
#Step 6 : Disable Port Forwarding                                                			 
##########################################################################################################
}
set output12 "";
set output12 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.NAT.X_Comcast_com_EnablePortMapping false boolean];

puts $output12;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output12] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 2nd parameter";
set result "FAILED";	
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
} 

puts {
############################################################################################################
#Step 7 :Telneting to a WAN client and sending HTTPs request again after disabling Port Forwarding                
############################################################################################################
}
spawn telnet $wanIP $wanTelnetPort;
set timeout 100;
expect -re (.*ogin:);
send "$wanName\r";
expect -re (.*word:);
send "$wanPassword\r";
expect -re ".*>";
send "wget --tries=1 -T 60 http://$wanIPWG/test.txt\r";
expect -re ".*>";
set outHttp $expect_out(buffer);

#wait
close $spawn_id;
puts {
############################################################################################
#Step 8 :Verifying the reachability of the HTTPs request
############################################################################################
}
if {[regexp {.*200 OK.*} $outHttp match] == 1} {
        set failFlag [expr $failFlag + 1];
        puts "HTTPs Request successful from WAN to WLAN when firewall even after Port Forwarding is disabled"
                } else {
        set passFlag [expr $passFlag + 1];
        puts "HTTPs Request not successful.Blocked from WAN to WLAN after disabling Port Forwarding"
}

if {$passFlag == 2} {
set result "PASSED"
} else {
        if {$failFlag >0 || $passFlag <2} {
        set result "FAILED";
}
  }
set passContent "Test Result : $result$~";
displayProc $passContent;



