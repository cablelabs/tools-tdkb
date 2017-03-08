 package require Expect; 
source proc.tcl; 
source lib.tcl
puts { 
########################################################################################################################################## 
#TEST CASEID :TC_ERTR_0110 
#Description  :Verify that WG supports blocking of HTTPs service only during specific day and time period through parental control (managed services) 
########################################################################################################################################## 
} 
#Initializing the values to the parameters by invoking Initializer proc 
set configFile $argv;
Initializer $configFile; 

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

set day_of_week [clock format [clock scan $d] -format %a];
set Time1 [expr {([clock scan $Time]+300)}] 
 
set endtime [clock format $Time1 -format %H:%M]; 
puts "\n\nToday is $day_of_week";
puts "Start Time: $Time";
puts "End Time:   $endtime"; 
set no [split $wlanInterfaceName "_"]; 
puts { 
################################################################################ 
#Step 1 :Enabling the managed services and blocking HTTPs service. 
################################################################################ 
} 
 
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
 
set output2 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetMultipleParameterValues Device.X_Comcast_com_ParentalControl.ManagedServices.Service.$I.Description,Device.X_Comcast_com_ParentalControl.ManagedServices.Service.$I.Protocol,Device.X_Comcast_com_ParentalControl.ManagedServices.Service.$I.StartPort,Device.X_Comcast_com_ParentalControl.ManagedServices.Service.$I.EndPort,Device.X_Comcast_com_ParentalControl.ManagedServices.Service.$I.AlwaysBlock,Device.X_Comcast_com_ParentalControl.ManagedServices.Service.$I.StartTime,Device.X_Comcast_com_ParentalControl.ManagedServices.Service.$I.EndTime,Device.X_Comcast_com_ParentalControl.ManagedServices.Service.$I.BlockDays HTTPS,TCP,443,443,false,$Time,$endtime,$day_of_week string,string,unsignedInt,unsignedInt,boolean,string,string,string]; 
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
########################################################################################################## 
#Step 2 :Get the value of parameters that have been set. 
########################################################################################################## 
} 
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
 
set output12 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_Comcast_com_ParentalControl.ManagedServices.Service.$I.Protocol null null];
puts $output12; 
if {[regexp {.*Time limit has crossed 2 minutes.*} $output12]== 1 } { 
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection"; 
puts "Failed to set 3rd parameter"; 
set result "FAILED"; 
set passContent "Test Result : $result$~"; 
displayProc $passContent; 
exit 0; 
} 
 
 
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
 
set output16 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_Comcast_com_ParentalControl.ManagedServices.Service.$I.StartTime null null]; 
puts $output16; 
if {[regexp {.*Time limit has crossed 2 minutes.*} $output16]== 1 } { 
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection"; 
puts "Failed to set 4th parameter"; 
set result "FAILED"; 
set passContent "Test Result : $result$~"; 
displayProc $passContent; 
exit 0; 
} 
 
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
#Step 3 :Configuring the Accesspoint with wpawpa2-psk Secuirty mode
################################################################################
}

set device_param1 "Device.WiFi.AccessPoint.$si2.Security.ModeEnabled";
set profileType "Wireless.xml";
set wlan_sec_type "wpawpa2-psk";
set ssidName "$ssid2";
set test_radio "2.4ghz";
set radio_param "Device.WiFi.Radio.$ri2.Enable";

set response [config_wlan_sec_wpa2-psk $ClassPath $Class $oui $SNno $deviceType $device_param1 $test_radio $ssidName $wlan_sec_type $ri2 $si2];
puts "The Result of config_wlan_sec_wpawpa2-psk is $response";
if {![regexp {pass} $response] == 1} {
exit 0;
}


puts {
##########################################################################################################
#Step 4 :Telneting to the WLAN client and obtaining its IP.
##########################################################################################################
}
set profileType "Wireless.xml";
set wlan_sec_type "wpawpa2-psk";
set ssidName "$ssid2";

set response [Configure_Client_open $wlanIP $telnetPort $wlanName $wlanPassword $profilePath $no $profileType $ssidName];

set wireless_pc_ip "$response";
puts "The Result of Configure client proc is $response";
if {![regexp {(\d+)\.(\d+)\.(\d+)\.(\d+)} $response m o] == 1} {
exit 0;
}
puts "$wireless_pc_ip";


puts { 
################################################################################ 
#Step 5 :Telneting to WLAN Client and trying to access the Blocked HTTPs Service
################################################################################ 
} 
spawn telnet $wlanIP $telnetPort;
set timeout 100;
expect -re (.*ogin:);
send "$wlanAdminName\r";
expect -re (.*word:);
send "$wlanAdminPassword\r";
expect -re ".*>";
send "nslookup\r";
expect -re ".*>";
send "server 10.252.139.244\r";
expect -re ".*>";
send "$siteHttps\r";
expect -re ".*>";
set outUrlResp $expect_out(buffer);
if {[regexp {.*connection timed out.*} $outUrlResp match] == 1} {
send "server 10.252.139.247\r";
expect -re ".*>";
send "$siteHttps\r";
expect -re ".*>";
set outUrlResp $expect_out(buffer);

if {[regexp {.*connection timed out.*} $outUrlResp match] == 1} {
send "server 10.0.0.1\r";
expect -re ".*>";
send "$siteHttps\r";
expect -re ".*>";
set outUrlResp $expect_out(buffer);
}
}

send "exit\r";
expect -re ".*>"
regexp {.*Name.*?([0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}).*} $outUrlResp match ipFull;
regexp {(\d+\.\d+).*} $ipFull match ip;
send "route add $ip.0.0 mask 255.255.0.0 10.0.0.1\r";
expect -re ".*OK!.*>";
send "wget --tries=1 -T 60 https://$siteHttps --no-check-certificate\r";
expect -re ".*>";
set outHttps $expect_out(buffer);
send "route delete $ip.0.0\r";
expect -re ".*>";
send "exit\r";
#wait
close $spawn_id;
set passFlag "";
set failFlag "";
puts { 
############################################################################################ 
#Step 6 :Verifying whether the blocked HTTPs service can be reached 
############################################################################################ 
} 
if {[regexp {.*200 OK.*} $outHttps match] == 1} { 
        set failFlag [expr $failFlag + 1]; 
        puts "The blocked service 'HTTPs' can be reached." 
                } else { 
        set passFlag [expr $passFlag + 1]; 
        puts "The blocked service 'HTTPs' cannot be reached." 
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
#Step 7 :Reverting back to its initial values.
################################################################################ 
}  
set output9 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue  Device.X_Comcast_com_ParentalControl.ManagedServices.Enable false boolean]; 
puts $output9; 
if {[regexp {.*Time limit has crossed 2 minutes.*} $output9] == 1 } { 
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection"; 
puts "Failed to set 1st parameter"; 
set result "FAILED"; 
set passContent "Test Result : $result$~"; 
displayProc $passContent; 
exit 0; 
}  
set output10 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_Comcast_com_ParentalControl.ManagedServices.Service.$I.AlwaysBlock false boolean]; 
puts $output10; 
if {[regexp {.*Time limit has crossed 2 minutes.*} $output10] == 1 } { 
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection"; 
puts "Failed to set 2nd parameter"; 
set result "FAILED"; 
set passContent "Test Result : $result$~"; 
displayProc $passContent; 
exit 0; 
}  
set passContent "Test Result : $result$~"; 
displayProc $passContent; 

