package require Expect;
source proc.tcl;
source lib.tcl;
puts {
############################################################################################################
#TESTCASEID :TC_ERTR_0329                                                                                                    
#Description :Verify that enabling 2.4GHz radio gets successfully logged in WEBPA Log File of RDK Logger
############################################################################################################
 }
#Initializing the values to the parameters by invoking Initializer proc
set configFile $argv;
Initializer $configFile;

puts {
################################################################################
#Step Pre-req :Disable the 2.4GHz radio
################################################################################
}
set output "";
set output [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.WiFi.Radio.$ri2.Enable false boolean];
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
set fileName $webpaLogFilename
puts $deleteLogPath
#set logPath "cat /dev/null > /rdklogs/logs/WiFilog.txt.0";
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
#Step 2 : Enable the 2.4GHz radio
################################################################################

}
set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.WiFi.Radio.$ri2.Enable true boolean];
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

set soutput1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.WiFi.Radio.$ri2.Enable null null];
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
#set value "enable: 1";
#set value "WiFi radio Radio0 is set to UP";
puts "value is $value";
sleep 5;
puts {
#########################################################################################
#Step 4: Validate the 2.4GHZ SSID(Value changed in step2) value with the RDKLogger value
#########################################################################################

}

set alternateparameterName "Device.WiFi.SSID.  .Enable";
#set logFilePath "/rdklogs/logs/";
#set logFileName "WiFilog.txt.0";
set response [fetch_validate_rdklogs $CMip $CMpassword $logFilePath $backupLogfilePath $fileName $parameterName $value $alternateparameterName];
set result "PASSED";
puts "The Result of fetch_validate_rdklogs is $response";
if {![regexp {pass} $response]} {
puts "Fail to log results in WEBPA log file of rdklogger";
set result "FAILED";
#exit 0;
}
set passContent "Test Result : $result$~";
displayProc $passContent;


