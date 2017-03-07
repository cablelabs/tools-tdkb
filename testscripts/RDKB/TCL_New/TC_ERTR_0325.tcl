package require Expect;
source proc.tcl;
source lib.tcl;
puts {
###########################################################################################################################
#TESTCASEID :TC_ERTR_0325                                                                                                    
#Description : Verify that changing 5GHz radio type to n only mode gets successfully logged in Webpa Log File of RDK Logger
###########################################################################################################################
 }
#Initializing the values to the parameters by invoking Initializer proc
set configFile $argv;
Initializer $configFile;
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
#Step 2 : Changing 5GHz radio type to "n" only mode
################################################################################

}

set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.WiFi.Radio.$ri5.OperatingStandards n string];
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
################################################################################
#Step 3: Get the value of the parameter that has been set
################################################################################
}
set soutput1 "";

set soutput1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.WiFi.Radio.$ri5.OperatingStandards null null];
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
proc commented {} {
if {$value == "n" } {
set value "nOnlyFlag: 1";
} else {
set value "Mode doesnt changed";
puts "Get parameter values doesnot matches with the Set parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;

}
}
puts "value is $value";

puts {
###########################################################################################
#Step 4: Validate the 5GHz radio type(Value changed in step2) value with the RDKLogger value
###########################################################################################

}

set alternateparameterName "Device.WiFi.Radio.2.OperatingStandards"
set response [fetch_validate_rdklogs $CMip $CMpassword $logFilePath $backupLogfilePath $fileName $parameterName $value $alternateparameterName];
set result "PASSED";
puts "The Result of fetch_validate_rdkLogs is $response";
if {![regexp {pass} $response]} {
puts "Fail to log results in Webpa Log File of rdklogger";
set result "FAILED";
}

puts {
################################################################################
#Step 5: Changing 5GHz radio type with the default value
################################################################################

}
set soutput1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.WiFi.Radio.$ri5.OperatingStandards a,n,ac string];

puts $soutput1;


set passContent "Test Result : $result$~";
displayProc $passContent;


