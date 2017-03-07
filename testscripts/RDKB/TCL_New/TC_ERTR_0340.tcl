package require Expect;
source proc.tcl;
source lib.tcl;
puts {
#####################################################################################################################
#TESTCASEID :TC_ERTR_0340                                                                                                    
#Description : Verify that configuring the DHCP Server pool range as 10.0.0.10 - 10.0.0.15 in WG 
#gets successfully logged in Webpa Log File of RDK logger
######################################################################################################################
 }
#Initializing the values to the parameters by invoking Initializer proc
set configFile $argv;
Initializer $configFile;

puts {
################################################################################
#Step Pre-req :Get the initial maximun and minimum server pool IP Address
################################################################################
}
set soutput "";
set soutput [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.DHCPv4.Server.Pool.1.MinAddress null null];
puts $soutput;
if {[regexp {.*Time limit has crossed 2 minutes.*} $soutput] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 1st parameter ";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
regexp {.*VALUE:(.*) TYPE.*} $soutput match initialValue1;

puts "value is $initialValue1";

set soutput2 "";
set soutput2 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.DHCPv4.Server.Pool.1.MaxAddress null null];
puts $soutput2;
if {[regexp {.*Time limit has crossed 2 minutes.*} $soutput2] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 1st parameter ";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
regexp {.*VALUE:(.*) TYPE.*} $soutput2 match initialValue2;

puts "value is $initialValue2";

puts {
################################################################################
#Step Pre-req :Set the DHCPv4 Server Pool Minimum and Maximum address
################################################################################
}
set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.DHCPv4.Server.Pool.1.MinAddress 10.0.0.20 string];
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
set output2 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.DHCPv4.Server.Pool.1.MaxAddress 10.0.0.25 string];
puts $output2;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output2] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 2nd parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}


puts {
######################################################################################
#Step 1 :Delete the contents of the logfile(in both logs folder and backuplogs folder)
######################################################################################

}
puts $deleteLogPath
set fileName $webpaLogFilename

set response [delete_rdklogs $CMip $CMpassword $deleteLogPath $deleteBackupLogPath $fileName];
puts "The Result of Delete rdkLogs is $response";
if {![regexp {pass} $response]} {
puts "Deleting rdkLogs fails";
set result "FAILED";
exit 0;
}

sleep 5;
puts {
################################################################################
#Step 2 : Set DHCPv4 Server Pool Minimum and Maximum address with its initial Value
################################################################################

}
set voutput1 "";
set voutput1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.DHCPv4.Server.Pool.1.MinAddress $initialValue1 string];
puts $voutput1;
if {[regexp {.*Time limit has crossed 2 minutes.*} $voutput1] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

set voutput2 "";
set voutput2 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.DHCPv4.Server.Pool.1.MaxAddress $initialValue2 string];
puts $voutput2;
if {[regexp {.*Time limit has crossed 2 minutes.*} $voutput2] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 2nd parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}




puts {
################################################################################
#Step 3: Get the value of the parameter that has been set
################################################################################
}
set soutput3 "";
set soutput3 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.DHCPv4.Server.Pool.1.MinAddress null null];

puts $soutput3;
if {[regexp {.*Time limit has crossed 2 minutes.*} $soutput3] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 1st parameter ";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
regexp {.*NAME:(.*) VALUE.*} $soutput3 match parameterName;
regexp {.*VALUE:(.*) TYPE.*} $soutput3 match value;
puts "value is $value";
if {$value == $initialValue1} {
set value1 "$initialValue1";
} else {
puts "Get parameter values doesnot matches with the Set parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;

}

set soutput4 "";
set soutput4 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.DHCPv4.Server.Pool.1.MaxAddress null null];

puts $soutput4;
if {[regexp {.*Time limit has crossed 2 minutes.*} $soutput4] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 1st parameter ";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
regexp {.*NAME:(.*) VALUE.*} $soutput4 match parameterName;
regexp {.*VALUE:(.*) TYPE.*} $soutput4 match value;
puts "value is $value";
if {$value == "$initialValue2"} {
set value2 "New Value: $initialValue2";
} else {
puts "Get parameter values doesnot matches with the Set parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;

}

sleep 5;
puts {
###########################################################################################################
#Step 4 : Validate the DHCPv4 Server Pool Minimum and Maximum address value change with the RDKLogger value
###########################################################################################################

}
set alternateparameterName "";
set response1 [fetch_validate_rdklogs $CMip $CMpassword $logFilePath $backupLogfilePath $fileName $parameterName $value1 $alternateparameterName];
set result "PASSED";
puts "The Result of fetch_validate_rdkLogs is $response1";
sleep 5;
set response2 [fetch_validate_rdklogs $CMip $CMpassword $logFilePath $backupLogfilePath $fileName $parameterName $value2 $alternateparameterName];
puts "The Result of fetch_validate_rdkLogs is $response2";


if {![regexp {pass} $response1] && ![regexp {pass} $response2]} {
puts "Fail to log results in Webpa Log File of rdklogger";
set result "FAILED";
#exit 0;
} else {
puts "The Server Pool Minimum address : $initialValue1  and The Server Pool Maximum address : $initialValue2 found in the Webpa Log File of rdklogger"
}

set passContent "Test Result : $result$~";
displayProc $passContent;


