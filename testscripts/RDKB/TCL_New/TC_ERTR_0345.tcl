package require Expect;
source proc.tcl;
source lib.tcl;
puts {
######################################################################################################################################
#TESTCASEID :TC_ERTR_0345                                                                                                    
#Description : Verify that Changing the Guard Interval value for 5GHz radio gets successfully logged in Webpa Log File of RDK logger
######################################################################################################################################
 }
#Initializing the values to the parameters by invoking Initializer proc
set configFile $argv;
Initializer $configFile;

puts {
################################################################################
#Step Pre-req :Get the current Guard Interval Value of 5GHz radio 
################################################################################
}
set soutput "";
set soutput [ exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.WiFi.Radio.$ri5.GuardInterval  null null];

puts $soutput;
if {[regexp {.*Time limit has crossed 2 minutes.*} $soutput] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 1st parameter ";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
regexp {.*VALUE:(.*) TYPE.*} $soutput match initialValue;

puts "value is $initialValue";

puts {
################################################################################
#Step Pre-req :Set the current Guard Interval Value of 5GHz radio to 400nsec
################################################################################
}

set output "";

set output [ exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.WiFi.Radio.$ri5.GuardInterval 400nsec string];
puts $output;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output] == 1 } {

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
#Step 2 : Set Guard Interval of 5GHz radio with its initial Value
################################################################################

}
set output1 "";
set output1 [ exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.WiFi.Radio.$ri5.GuardInterval $initialValue string];
puts $output1;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output1] == 1 } {

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
set soutput1 "";
set soutput1 [ exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.WiFi.Radio.$ri5.GuardInterval null null];

puts $soutput1;
if {[regexp {.*Time limit has crossed 2 minutes.*} $soutput1] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 1st parameter ";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
regexp {.*NAME:(.*) VALUE.*} $soutput1 match parameterName;
regexp {.*VALUE:(.*) TYPE.*} $soutput1 match value;
puts "value is $value";

sleep 5;
puts {
##########################################################################################
#Step 4 : Validate the Guard Interval value change with the RDKLogger value
##########################################################################################

}

set alternateparameterName "";
set response [fetch_validate_rdklogs $CMip $CMpassword $logFilePath $backupLogfilePath $fileName $parameterName $value $alternateparameterName];
set result "PASSED";
puts "The Result of fetch_validate_rdkLogs is $response";
if {![regexp {pass} $response]} {
puts "Fail to log results in Webpa Log File of rdklogger";
set result "FAILED";
#exit 0;
}

set passContent "Test Result : $result$~";
displayProc $passContent;


