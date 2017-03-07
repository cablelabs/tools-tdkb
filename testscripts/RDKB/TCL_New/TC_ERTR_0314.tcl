package require Expect;
source proc.tcl;
source lib.tcl;
puts {
#################################################################################################################################################
#TESTCASEID :TC_ERTR_0314                                                                                                    
#Description :Verify that changing the security mode of 2.4GHz radio to WPA2-Personal  gets successfully logged in  Wi-Fi Log File of RDK logger
##################################################################################################################################################
}
#Initializing the values to the parameters by invoking Initializer proc
set configFile $argv;
Initializer $configFile;
puts {
#####################################################################################
#Step 1 :Delete the contents of the logfile(in both logs folder and backuplogs folder)
#####################################################################################

}
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
#Step 2 : Change the security mode of 2.4GHZ Radio to WPA2-Personal.
################################################################################

}
set SSID_index_2 "$si2";

set voutput "";

set voutput [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetMultipleParameterValues  Device.WiFi.AccessPoint.$si2.Security.X_CISCO_COM_EncryptionMethod,Device.WiFi.AccessPoint.$SSID_index_2.Security.ModeEnabled AES,WPA2-Personal string,string];
puts $voutput;
if {[regexp {.*Time limit has crossed 2 minutes.*} $voutput] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 2nd parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}


set output2 "";
set output2 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.WiFi.AccessPoint.$si2.Security.PreSharedKey wifitest123 string];
puts $output2;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output2] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 4th parameter";
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

set soutput1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.WiFi.AccessPoint.$si2.Security.ModeEnabled null null];
puts $soutput1;
if {[regexp {.*Time limit has crossed 2 minutes.*} $soutput1] == 1 } {
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
regexp {.*NAME:(.*) VALUE.*} $soutput1 match parameterName;
regexp {.*VALUE:(.*) TYPE.*} $soutput1 match value;
puts "value is $value";

puts {
################################################################################
#Step 4: Validate the Wi-Fi security mode changes logged in RDKLogger
################################################################################
}

set alternateparameterName "Device.WiFi.AccessPoint.1.Security.ModeEnabled";
set response [fetch_validate_rdklogs $CMip $CMpassword $logFilePath $backupLogfilePath $wifiLogFilename $parameterName $value $alternateparameterName];
set result "PASSED";
puts "The Result of fetch_validate_rdkLogs is $response";
if {![regexp {pass} $response]} {
puts "Fail to log results in  Wi-Fi Log File of rdklogger";
set result "FAILED";
}

puts {
################################################################################
#Step 5: Reverting the ModeEnabled and PreSharedKey back to their default value.
################################################################################
}
set voutput "";

set voutput  [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetMultipleParameterValues  Device.WiFi.AccessPoint.$si2.Security.X_CISCO_COM_EncryptionMethod,Device.WiFi.AccessPoint.$si2.Security.ModeEnabled AES+TKIP,WPA-WPA2-Personal string,string];
puts $voutput;
if {[regexp {.*Time limit has crossed 2 minutes.*} $voutput] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 2nd parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

set output6 "";

set output6 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.WiFi.AccessPoint.$si2.Security.PreSharedKey wifitest123 string];
puts $output6;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output6] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 2nd parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}


set passContent "Test Result : $result$~";
displayProc $passContent;


