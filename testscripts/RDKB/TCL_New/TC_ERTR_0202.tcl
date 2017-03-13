package require Expect;
source proc.tcl;
source lib.tcl;
puts {
######################################################################################################################### 
#TEST CASE ID :TC_ERTR_0202								
#Description  :Verify that when Bridge mode is enabled, ensure that the ethernet client gets the WAN IP directly
#########################################################################################################################
} 
#Initializing the values to the parameters by invoking Initializer proc
set configFile $argv;
Initializer $configFile;

puts {
#########################################################################################################################
#Step 1: Enabling the Bridge mode 
#########################################################################################################################
}
set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_CISCO_COM_DeviceControl.LanManagementEntry.1.LanMode bridge-static string];
puts $output1;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output1] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";	
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
} 

#Wait for 100 Seconds for enabling the Bridge Mode
sleep 120;


puts { 
################################################################################ 
#Step 2 :Get the value of parameters that have been set.
################################################################################ 
}

set voutput "";
set voutput [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_CISCO_COM_DeviceControl.LanManagementEntry.1.LanMode null null];
puts $voutput;
if {[regexp {.*Time limit has crossed 2 minutes.*} $voutput] == 1 } {
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 1st parameter";
set result "FAILED";	
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
} 

puts { 
################################################################################ 
#Step 3 :Get the value of Default Gateway IP Address
################################################################################ 
} 
set output2 "";
set output2 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.DHCPv4.Client.1.IPRouters null null];
puts $output2;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output2] == 1 } {
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 1st parameter";
set result "FAILED";	
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
} 


if { [regexp {.*VALUE:(\d+\.\d+\.\d+\.\d+) TYPE:.*} $output2 match Ipval] == 1 } {
puts "Obtained Default Gateway IP: $Ipval";
} else {
puts "Default Gateway IP has not been obtained due to technical reasons."
set result "Error"
return $result
}



puts {
################################################################################
#Step 4 :Telnet-ing to a LAN Client                                                                                         
################################################################################
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
send "ping -c 4 $Ipval\r";
expect -re ".*#";
set outPing $expect_out(buffer);

send "ping -c 4 10.0.0.1\r";
expect -re ".*#";
set outPing1 $expect_out(buffer);

#wait 
close $spawn_id
set passFlag ""; 
set failFlag "";

puts {
############################################################################################
#Step 5 :Verifying the reachability to Default Gateway WAN IP Address and DHCP server
############################################################################################
}

if {[regexp {.*received, (.*)% packet loss} $outPing match lossPercent] == 1} {
        if {$lossPercent == 0} {
			set passFlag [expr $passFlag + 1];
			puts "Ping successful from LAN to Default Gateway WAN IP Address"
        } else {
			set failFlag [expr $failFlag + 1];
			puts "Ping not successful from LAN to Default Gateway WAN IP Address"

        }
}

if {[regexp {.*received, (.*)% packet loss} $outPing1 match lossPercent] == 1} {
        if {$lossPercent == 0} {
			set failFlag [expr $failFlag + 1];
			puts "Ping successful from LAN to DHCP server"
        } else {
			set passFlag [expr $passFlag + 1];
			puts "Ping not successful from LAN to DHCP server"
 
        }
}
if {$passFlag == 2} {
	set result "PASSED"     
} else {
	set result "FAILED"
}

puts {
#########################################################################################################################
#Step 6: Disabling the bridge mode 
#########################################################################################################################
}
set output3 "";
set output3 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_CISCO_COM_DeviceControl.LanManagementEntry.1.LanMode router string];
puts $output3;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output3] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";	
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
} 

#Wait for 200 Seconds for Disabling the Bridge Mode
sleep 200;

set passContent "Test Result : $result$~";
displayProc $passContent;
