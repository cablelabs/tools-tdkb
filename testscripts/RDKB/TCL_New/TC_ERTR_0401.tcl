package require Expect;
source proc.tcl;
puts {
###################################################################################################################################################
#TEST CASEID :TC_ERTR_0401
#Description  :Verify that WG supports blocking of FTP service only during specific day and time period through parental control (managed services
###################################################################################################################################################
}
#Initializing the values to the parameters by invoking Initializer proc
set configFile $argv;
Initializer $configFile;
puts {
################################################################################
#Step 1 : Get the local time configured on Wireless Gateway
################################################################################
}
set voutput "";
set voutput [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.Time.CurrentLocalTime null null];
puts $voutput;
if {[regexp {.*Time limit has crossed 2 minutes.*} $voutput] == 1 } {
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

if {[regexp {.*Device.Time.CurrentLocalTime.*VALUE:([0-9]{1,4}\-[0-9]{1,2}\-[0-9]{1,2}) .*TYPE.*} $voutput match d] == 1} {
puts "Date is: $d"
}

if {[regexp {.*Device.Time.CurrentLocalTime.*VALUE:[0-9]{1,4}\-[0-9]{1,2}\-[0-9]{1,2} ([0-9]{1,2}\:[0-9]{1,2}).*TYPE.*} $voutput match Time] == 1} {
puts "Time is: $Time"
}

spawn telnet $Telnetip $telnetPort1;
set timeout 100;
expect -re (.*ogin:);
send "$Name\r";
expect -re (.*word:);
send "$password\r";
expect -re ".*#";

puts "Starttime is $Time";
set day_of_week [clock format [clock scan $d] -format %a];
puts "Today id $day_of_week";




set Time1 [expr {([clock scan $Time]+1800)}]
set endtime [clock format $Time1 -format %H:%M];
puts "The endtime is: [clock format $Time1 -format %H:%M]";


puts {
################################################################################
#Step 2 :Enabling the managed services and blocking FTP service
################################################################################
}

set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_Comcast_com_ParentalControl.ManagedServices.Enable true boolean];
puts $output1;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output1] == 1 } {
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

set voutput1 "";
set voutput1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_Comcast_com_ParentalControl.ManagedServices.Service.1.Description null null];
puts $voutput1;
if {[regexp {.*Time limit has crossed 2 minutes.*} $voutput1] == 1 } {
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

if {[regexp {.*ManagedServices.Service.(.*).Description.*} $voutput1 match I] == 1} {
puts "instance configured is: $I"
}
 

set output2 "";
set output2 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetMultipleParameterValues Device.X_Comcast_com_ParentalControl.ManagedServices.Service.$I.Description,Device.X_Comcast_com_ParentalControl.ManagedServices.Service.$I.Protocol,Device.X_Comcast_com_ParentalControl.ManagedServices.Service.$I.StartPort,Device.X_Comcast_com_ParentalControl.ManagedServices.Service.$I.EndPort,Device.X_Comcast_com_ParentalControl.ManagedServices.Service.$I.AlwaysBlock,Device.X_Comcast_com_ParentalControl.ManagedServices.Service.$I.StartTime,Device.X_Comcast_com_ParentalControl.ManagedServices.Service.$I.EndTime,Device.X_Comcast_com_ParentalControl.ManagedServices.Service.$I.BlockDays ftp,TCP,21,21,false,$Time,$endtime,$day_of_week string,string,unsignedInt,unsignedInt,boolean,string,string,string];
puts $output2;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output2] == 1 } {
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 2nd parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
proc commented {} {
set output3 "";
set output3 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_Comcast_com_ParentalControl.ManagedServices.Service.$I.Protocol TCP string];
puts $output3;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output3] == 1 } {
  puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 3rd parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}


set output4 "";
set output4 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_Comcast_com_ParentalControl.ManagedServices.Service.$I.StartPort 21 unsignedInt];
puts $output4;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output4] == 1 } {
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 3rd parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

set output5 "";
set output5 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_Comcast_com_ParentalControl.ManagedServices.Service.$I.EndPort 21 unsignedInt];
puts $output5;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output5] == 1 } {
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 3rd parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
set output6 "";
set output6 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_Comcast_com_ParentalControl.ManagedServices.Service.$I.AlwaysBlock false boolean];
puts $output6;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output6] == 1 } {
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 3rd parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}



set output7 "";
set output7 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_Comcast_com_ParentalControl.ManagedServices.Service.$I.StartTime $Time1 string];
puts $output7;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output7] == 1 } {
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 4th parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

set output8 "";
set output8 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_Comcast_com_ParentalControl.ManagedServices.Service.$I.EndTime $endtime string];
puts $output8;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output8] == 1 } {
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 5th parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

set output9 "";
set output9 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_Comcast_com_ParentalControl.ManagedServices.Service.$I.BlockDays $day_of_week string];
puts $output9;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output9] == 1 } {
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 6th parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
}
puts {
##########################################################################################################
#Step 3 :Get the value of parameters that have been set.
##########################################################################################################
}
set output10 "";
set output10 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_Comcast_com_ParentalControl.ManagedServices.Enable null null];
puts $output10;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output10] == 1 } {
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

set output11 "";
set output11 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_Comcast_com_ParentalControl.ManagedServices.Service.$I.Description null null];
puts $output11;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output11] == 1 } {
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 2nd parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

set output12 "";
set output12 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_Comcast_com_ParentalControl.ManagedServices.Service.$I.Protocol null null];
puts $output12;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output12] == 1 } {
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 3rd parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
set output13 "";
set output13 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_Comcast_com_ParentalControl.ManagedServices.Service.$I.StartPort null null];
puts $output13;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output13] == 1 } {
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 3rd parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

set output14 "";
set output14 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_Comcast_com_ParentalControl.ManagedServices.Service.$I.EndPort null null];
puts $output14;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output14] == 1 } {
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 3rd parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

set output15 "";
set output15 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_Comcast_com_ParentalControl.ManagedServices.Service.$I.AlwaysBlock null null];
puts $output15;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output15] == 1 } {
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 3rd parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

set output16 "";
set output16 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_Comcast_com_ParentalControl.ManagedServices.Service.$I.StartTime null null];
puts $output16;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output16] == 1 } {
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 4th parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

set output17 "";
set output17 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_Comcast_com_ParentalControl.ManagedServices.Service.$I.EndTime null null];
puts $output17;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output17] == 1 } {
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 5th parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
set output18 "";
set output18 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_Comcast_com_ParentalControl.ManagedServices.Service.$I.BlockDays null null];
puts $output18;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output18] == 1 } {
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 6th parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}


puts {
################################################################################
#Step 4 :Telnet to Ethernet Client and trying to access the FTP service
##############################################################################
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
after 10000;
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
expect -re (.*>);
set outFtp $expect_out(buffer);
send "bye\r";
}
}
send "ip route delete $wanIP via 10.0.0.1\r";
expect -re ".*#";
#wait
close $spawn_id

set passFlag "";
set failFlag "";
puts {
############################################################################################
#Step 5 :Verifying whether the blocked service can be reached
############################################################################################
}
if {[regexp {.*230.*} $outFtp match] == 1} {
        set failFlag [expr $failFlag + 1];
        puts "The blocked service 'FTP' can be reached."
                } else {
        set passFlag [expr $passFlag + 1];
        puts "The blocked service 'FTP' is blocked on $day_of_week from $Time to $Time1."
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
#Step 6 :Reverting the blocked service parameters to initial values.                                                         
################################################################################
}
set voutput9 "";
set voutput9 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue  Device.X_Comcast_com_ParentalControl.ManagedServices.Enable false boolean];
puts $voutput9;
if {[regexp {.*Time limit has crossed 2 minutes.*} $voutput9] == 1 } {
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

set passContent "Test Result : $result$~";
displayProc $passContent;
                                                                            
