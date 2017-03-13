package require Expect;
source proc.tcl;
puts {
##########################################################################################################################################
#TEST CASEID :TC_ERTR_0389                                                                                                   
#Description  :Verify that WG supports blocking of websites using URL through Parental control (managed sites)
##########################################################################################################################################
} 
#Initializing the values to the parameters by invoking Initializer proc
set configFile $argv;
Initializer $configFile;

puts {
################################################################################
#Step 1 :Enabling the Managed sites and blocking a particular site.
################################################################################
} 

set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_Comcast_com_ParentalControl.ManagedSites.Enable true boolean];
puts $output1;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output1] == 1 } {
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
proc commented {} { 
set voutput2 "";
set voutput2 [exec java -cp $ClassPath $Class $oui $SNno $deviceType AddObject Device.X_Comcast_com_ParentalControl.ManagedSites.BlockedSite. null null];
puts $voutput2;
if {[regexp {.*Time limit has crossed 2 minutes.*} $voutput2] == 1 } {
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 2nd parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
}
set voutput1 "";
set voutput1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_Comcast_com_ParentalControl.ManagedSites.BlockedSite.1.BlockMethod null null];
puts $voutput1;
if {[regexp {.*Time limit has crossed 2 minutes.*} $voutput1] == 1 } {
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

if {[regexp {.*BlockedSite.(.*).BlockMethod.*} $voutput1 match I] == 1} {
puts "instance configured is: $I"
}


set output2 "";
set output2 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetMultipleParameterValues Device.X_Comcast_com_ParentalControl.ManagedSites.BlockedSite.$I.BlockMethod,Device.X_Comcast_com_ParentalControl.ManagedSites.BlockedSite.$I.Site,Device.X_Comcast_com_ParentalControl.ManagedSites.BlockedSite.$I.AlwaysBlock URL,$siteUrl,true string,string,boolean];
puts $output2;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output2] == 1 } {
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
} 

proc commented {} {
set output3 "";
set output3 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_Comcast_com_ParentalControl.ManagedSites.BlockedSite.$I.Site http://www.google.com string];
puts $output3;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output3] == 1 } {
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
 
set output4 "";
set output4 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_Comcast_com_ParentalControl.ManagedSites.BlockedSite.$I.AlwaysBlock true boolean];
puts $output4;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output4] == 1 } {
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
} 
}
puts {
##########################################################################################################
#Step 2 :Get the value of parameters that have been set.
##########################################################################################################
} 
set output5 "";
set output5 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_Comcast_com_ParentalControl.ManagedSites.Enable null null];
puts $output5;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output5] == 1 } {
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
} 
set output6 "";
set output6 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_Comcast_com_ParentalControl.ManagedSites.BlockedSite.$I.BlockMethod null null];
puts $output6;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output6] == 1 } {
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
} 

set output7 "";
set output7 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_Comcast_com_ParentalControl.ManagedSites.BlockedSite.$I.Site null null];
puts $output7;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output7] == 1 } {
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
} 

set output8 "";
set output8 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_Comcast_com_ParentalControl.ManagedSites.BlockedSite.$I.AlwaysBlock null null];
puts $output8;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output8] == 1 } {
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
} 
after 15000;
puts {
######################################################################################
#Step 3 :Telnet to Ethernet client and trying to access the blocked site                                                                  
######################################################################################
}
spawn telnet $Telnetip $telnetPort1;
set timeout 100;
expect -re (.*ogin:);
send "$Name\r";
expect -re (.*word:);
send "$password\r";
expect -re ".*#";
send "nslookup\r";
expect -re ".*>";
send "server 10.252.139.244\r";
expect -re ".*>";
send "$siteUrl\r";
expect -re ".*>";
set outUrlResp $expect_out(buffer);
if {[regexp {.*connection timed out.*} $outUrlResp match] == 1} {
send "server 10.252.139.247\r";
expect -re ".*>";
send "$siteUrl\r";
expect -re ".*>";
set outUrlResp $expect_out(buffer);

if {[regexp {.*connection timed out.*} $outUrlResp match] == 1} {
send "server 10.0.0.1\r";
expect -re ".*>";
send "$siteUrl\r";
expect -re ".*>";
set outUrlResp $expect_out(buffer);
}
}

send "exit\r";
expect -re ".*#";
regexp {.*Name.*?([0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}).*} $outUrlResp match ipFull;
regexp {(\d+\.\d+).*} $ipFull match ip;
send "ip route add $ip.0.0/16 via 10.0.0.1\r";
expect -re ".*#";
send "wget --tries=1 -T 60 http://$siteUrl\r";
expect -re ".*#";
set outHttp $expect_out(buffer);
send "ip route delete $ip.0.0/16 via 10.0.0.1\r";
expect -re ".*#";
send "exit\r";
#wait
close $spawn_id;
set passFlag "";
set failFlag "";
puts {
############################################################################################
#Step 4 :Verifying whether the blocked site can be reached
############################################################################################
}
if {[regexp {.*200 OK.*} $outHttp match] == 1} {
        set failFlag [expr $failFlag + 1];
        puts "The blocked site '$siteUrl' can be reached."
                } else {
        set passFlag [expr $passFlag + 1];
        puts "The blocked site '$siteUrl' cannot be reached."
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
#Step 5 :Reverting the blocked site parameters to initial values
################################################################################
} 
set output9 "";
set output9 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_Comcast_com_ParentalControl.ManagedSites.Enable false boolean];
puts $output9;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output9] == 1 } {
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
} 
set passContent "Test Result : $result$~";
displayProc $passContent;