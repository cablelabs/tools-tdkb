package require Expect;
source proc.tcl;
source lib.tcl;
puts {
############################################################################################################
#TESTCASEID :TC_ERTR_0311                                                                                                    
#Description  :Verify that enabling 5GHz radio gets successfully logged in Wi-Fi Log File of  RDK logger
############################################################################################################
 }
#Initializing the values to the parameters by invoking Initializer proc
set configFile $argv;
Initializer $configFile;

puts {
################################################################################
#Step Pre-req :Disable the 5GHz radio
################################################################################
}
set output "";
set output [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.WiFi.Radio.$ri5.Enable false boolean];
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
#set logPath "cat /dev/null > /rdklogs/logs/WiFilog.txt.0";
set response [delete_rdklogs $CMip $CMpassword $deleteLogPath $deleteBackupLogPath $wifiLogFilename];
puts "The Result of Delete rdkLogs is $response";
if {![regexp {pass} $response]} {
puts "Deleting rdkLogs fails";
set result "FAILED";
exit 0;
}

sleep 5;
puts {
################################################################################
#Step 2 : Enable the 5GHz radio
################################################################################

}
set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.WiFi.Radio.$ri5.Enable true boolean];
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
set soutput1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.WiFi.Radio.$ri5.Enable null null];
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
if {$value == "true"} {
#set value "enable: 1";
set value "WiFi radio Radio1 is set to UP";
} else {
set value "WiFi radio Radio1 is set to DOWN";
puts "Get parameter values doesnot matches with the Set parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;

}
puts "value is $value";
sleep 5;
puts {
################################################################################
#Step 4: Validate that enabling the 5GHz radio get logged into RDKLogger
################################################################################
}
set alternateparameterName "Device.WiFi.SSID.  .Enable";
#set logFilePath "/rdklogs/logs/";
#set logFileName "WiFilog.txt.0";
set response [fetch_validate_rdklogs $CMip $CMpassword $logFilePath $backupLogfilePath $wifiLogFilename $parameterName $value $alternateparameterName];
set result "PASSED";
puts "The Result of fetch_validate_rdkLogs is $response";
if {![regexp {pass} $response]} {
puts "Fail to log results in Wi-Fi Log File of rdklogger";
set result "FAILED";
#exit 0;
}

set passContent "Test Result : $result$~";
displayProc $passContent;


