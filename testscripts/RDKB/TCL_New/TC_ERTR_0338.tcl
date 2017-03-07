package require Expect;
source proc.tcl;
source lib.tcl;
puts {
###################################################################################################################
#TESTCASEID :TC_ERTR_0338                                                                                                    
#Description : Verify that DHCPv4 server pool gateway IP can be set with Class A private IP address 10.x.x.x in WG 
#gets successfully logged in Webpa Log File of RDK logger
###################################################################################################################
 }
#Initializing the values to the parameters by invoking Initializer proc
set configFile $argv;
Initializer $configFile;

puts {
################################################################################
#Step Pre-req :Get server pool gateway IP address
################################################################################
}
set soutput "";
#set soutput [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_CISCO_COM_Security.Firewall.FirewallLevel null null];
set soutput [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_CISCO_COM_DeviceControl.LanManagementEntry.1.LanIPAddress null null];
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
#Step Pre-req :Set server pool gateway IP with private IP address 172.16.0.1
################################################################################
}
set output "";
#set output [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_CISCO_COM_Security.Firewall.FirewallLevel Low string];
set output [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_CISCO_COM_DeviceControl.LanManagementEntry.1.LanIPAddress 172.16.0.1 string];

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
########################################################################################
#Step 1 :Delete the contents of the logfile(in both logs folder and backuplogs folder)
########################################################################################

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
#Step 2 : Set server pool gateway IP with private IP address 10.0.0.1
################################################################################

}
set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_CISCO_COM_DeviceControl.LanManagementEntry.1.LanIPAddress 10.0.0.1 string ];
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
set soutput1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_CISCO_COM_DeviceControl.LanManagementEntry.1.LanIPAddress null null];
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
if {$value == "10.0.0.1"} {
set value "New Value: 10.0.0.1";
} else {
puts "Get parameter values doesnot matches with the Set parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;

}
sleep 5;
puts {
################################################################################
#Step 3 : Validate the  server pool gateway IP value change with the RDKLogger value.
################################################################################

}

set alternateparameterName "Device.X_CISCO_COM_Security.Firewall.FirewallLevel";
set response [fetch_validate_rdklogs $CMip $CMpassword $logFilePath $backupLogfilePath $fileName $parameterName $value $alternateparameterName];
set result "PASSED";
puts "The Result of fetch_validate_rdkLogs is $response";
if {![regexp {pass} $response]} {
puts "Fail to log results in Webpa Log File of rdklogger";
set result "FAILED";
#exit 0;
}

puts {
################################################################################
#Step 4:Reverting the Gateway IP to its default value
################################################################################
}
set voutput1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_CISCO_COM_DeviceControl.LanManagementEntry.1.LanIPAddress $initialValue string ];

puts $voutput1;
if {[regexp {.*Time limit has crossed 2 minutes.*} $voutput1] == 1 } {

puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

set passContent "Test Result : $result$~";
displayProc $passContent;


