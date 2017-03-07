package require Expect;
source proc.tcl;
source lib.tcl;
puts {
#############################################################################################################
#TESTCASEID :TC_ERTR_0328                                                                                                    
#Description : Verify that RDK logger successfully logs in WEBPA Log File for the WEBPA Get Parameter request
#############################################################################################################
 }
#Initializing the values to the parameters by invoking Initializer proc
set configFile $argv;
Initializer $configFile;
puts {
######################################################################################
#Step 1 :Delete the contents of the logfile(in both logs folder and backuplogs folder)
######################################################################################

}
set fileName $webpaLogFilename

puts $deleteLogPath
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
#Step 2 :Sending WEBPA get request for SSID name of 2.4GHz radio
################################################################################
}
set soutput1 "";

set soutput1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.WiFi.SSID.$si2.SSID null null];
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

puts {
###########################################################################################
#Step 3 : Validate the 2.4GHZ SSID (Value changed in step2) value with the RDKLogger value
###########################################################################################

}

set alternateparameterName "Device.WiFi.SSID.1.SSID";
set response [fetch_validate_rdklogs $CMip $CMpassword $logFilePath $backupLogfilePath $fileName $parameterName $value $alternateparameterName];
set result "PASSED";
puts "The Result of fetch_validate_rdklogs is $response";
if {![regexp {pass} $response]} {
puts "Fail to log results in WEBPA logfile of rdklogger";
set result "FAILED";
}


set passContent "Test Result : $result$~";
displayProc $passContent;


