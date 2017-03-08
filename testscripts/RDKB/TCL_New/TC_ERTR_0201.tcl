
package require Expect;
source proc.tcl;
puts {
##########################################################################################################################################
#TEST CASEID :TC_ERTR_0201                                                                                               
#Description  :Verify that when remote access management via HTTPS is disabled for all computer, none should able to remote access to the WG
##########################################################################################################################################
}
#Initializing the values to the parameters by invoking Initializer proc
set configFile $argv;
Initializer $configFile;
puts {
###################################################################################################
#Step 1 :Enabling the Remote access via HTTPs and disabling access for any computer
###################################################################################################
}
set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.UserInterface.X_CISCO_COM_RemoteAccess.HttpsEnable true boolean];
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
set output2 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.UserInterface.X_CISCO_COM_RemoteAccess.FromAnyIP false boolean];
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
###################################################################################################
#Step 2 :Get the value of parameters that have been set..
###################################################################################################
} 
set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.UserInterface.X_CISCO_COM_RemoteAccess.HttpEnable null null];
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
set output2 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.UserInterface.X_CISCO_COM_RemoteAccess.FromAnyIP null null];
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
######################################################################################
#Step 3 :Telneting to a WAN PC and trying to access the WG by sending an HTTPs request
######################################################################################
}

spawn telnet $wanIP $wanTelnetPort
set timeout 100;
expect -re (.*ogin:);
send "$wanName\r";
expect -re (.*word:);
send "$wanPassword\r";
expect -re ".*>";
send "wget --tries=1 -T 60 https://$wanIPWG:8181 --no-check-certificate\r";
expect -re ".*>";
set outHttps $expect_out(buffer);
#wait
close $spawn_id
set passFlag "";
set failFlag "";
puts {
################################################################################
#Step 4 :Checking whether the remote management request was successful
################################################################################
}
if {[regexp {.*200 OK.*} $outHttps match] == 1} {
        set failFlag [expr $failFlag + 1];
        puts "Remote management request via HTTPs successful from WAN Client through WAN IP of gateway"
                } else {
        set passFlag [expr $passFlag + 1];
        puts "Remote management request via HTTPs not successful from WAN Client through WAN IP of gateway"
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
#Step 5 :Reverting the Remote Management configurations back to its initial value.                           
##########################################################################################################
}
set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.UserInterface.X_CISCO_COM_RemoteAccess.HttpsEnable false boolean];
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
set output2 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.UserInterface.X_CISCO_COM_RemoteAccess.FromAnyIP true boolean];
puts $output2;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output2] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}


set passContent "Test Result : $result$~";
displayProc $passContent;

