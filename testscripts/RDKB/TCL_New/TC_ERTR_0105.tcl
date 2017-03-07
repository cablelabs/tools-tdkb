package require Expect; 
source proc.tcl; 
source lib.tcl
puts { 
########################################################################################################################################## 
#TEST CASEID :TC_ERTR_0105
#Description  :Verify that WG allows other websites except for the sites that has been blocked using keyword (google) through Parental control (managed sites) 
########################################################################################################################################## 
}  
#Initializing the values to the parameters by invoking Initializer proc 
set configFile $argv;
Initializer $configFile; 
puts { 
################################################################################ 
#Step 1 :Enabling the managed sites and blocking a particular Keyword. 
################################################################################ 
}  
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_Comcast_com_ParentalControl.ManagedSites.Enable true boolean]; 
puts $output1; 
if {[regexp {.*Time limit has crossed 2 minutes.*} $output1] == 1 } { 
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection"; 
puts "Failed to set 1st parameter"; 
set result "FAILED"; 
set passContent "Test Result : $result$~"; 
displayProc $passContent; 
exit 0; 
}  

set voutput1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_Comcast_com_ParentalControl.ManagedSites.BlockedSite.1.BlockMethod null null]; 
puts $voutput1; 
if {[regexp {.*Time limit has crossed 2 minutes.*} $voutput1] == 1 } { 
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection"; 
puts "Failed to set 1st parameter"; 
set result "FAILED"; 
set passContent "Test Result : $result$~"; 
displayProc $passContent; 
exit 0; 
} 
 
if {[regexp {.*ManagedSites.BlockedSite.(.*).BlockMethod.*} $voutput1 match I] == 1} { 
puts "instance configured is: $I" 
}

 
set output2 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetMultipleParameterValues Device.X_Comcast_com_ParentalControl.ManagedSites.BlockedSite.$I.BlockMethod,Device.X_Comcast_com_ParentalControl.ManagedSites.BlockedSite.$I.Site,Device.X_Comcast_com_ParentalControl.ManagedSites.BlockedSite.$I.AlwaysBlock Keyword,$siteKeyword,true string,string,boolean]; 
puts $output2; 
if {[regexp {.*Time limit has crossed 2 minutes.*} $output2] == 1 } { 
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection"; 
puts "Failed to set 1st parameter"; 
set result "FAILED"; 
set passContent "Test Result : $result$~"; 
displayProc $passContent; 
exit 0; 
}  
puts {
########################################################################################################## 
#Step 2 :Get the value of parameters that have been set
########################################################################################################## 
}  
set output5 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_Comcast_com_ParentalControl.ManagedSites.Enable null null]; 
puts $output5; 
if {[regexp {.*Time limit has crossed 2 minutes.*} $output5] == 1 } { 
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection"; 
puts "Failed to set 1st parameter"; 
set result "FAILED"; 
set passContent "Test Result : $result$~"; 
displayProc $passContent; 
exit 0; 
}  
 
set output6 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_Comcast_com_ParentalControl.ManagedSites.BlockedSite.$I.BlockMethod null null]; 
puts $output6; 
if {[regexp {.*Time limit has crossed 2 minutes.*} $output6] == 1 } { 
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection"; 
puts "Failed to set 1st parameter"; 
set result "FAILED"; 
set passContent "Test Result : $result$~"; 
displayProc $passContent; 
exit 0; 
}  
set output7 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_Comcast_com_ParentalControl.ManagedSites.BlockedSite.$I.Site null null]; 
puts $output7; 
if {[regexp {.*Time limit has crossed 2 minutes.*} $output7] == 1 } { 
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection"; 
puts "Failed to set 1st parameter"; 
set result "FAILED"; 
set passContent "Test Result : $result$~"; 
displayProc $passContent; 
exit 0; 
}  
 
set output8 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_Comcast_com_ParentalControl.ManagedSites.BlockedSite.$I.AlwaysBlock null null];
puts $output8; 
if {[regexp {.*Time limit has crossed 2 minutes.*} $output8] == 1 } { 
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection"; 
puts "Failed to set 1st parameter"; 
set result "FAILED"; 
set passContent "Test Result : $result$~"; 
displayProc $passContent; 
exit 0; 
}  
set no [split $wlanInterfaceName "_"];
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
#Step 5 :Telneting to WLAN Client and trying to access the Blocked Keyword
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
if {[regexp {.*connection timed out.*} $outUrlResp match] == 1 || [regexp {.*request timed out.*} $outUrlResp match ]== 1} {
send "server 10.252.139.247\r";
expect -re ".*>";
send "$siteHttps\r";
expect -re ".*>";
set outUrlResp $expect_out(buffer);

if {[regexp {.*connection timed out.*} $outUrlResp match ] == 1 || [regexp {.*request timed out.*} $outUrlResp match ]== 1} {
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
#Step 6 :Verifying whether the Unblocked Keyword can be reached 
############################################################################################ 
} 
if {[regexp {.*200 OK.*} $outHttps match] == 1} { 
        set passFlag [expr $passFlag + 1]; 
        puts "The Unblocked Kewyord can be reached." 
                } else { 
        set failFlag [expr $failFlag + 1];  
        puts "The Unblocked Kewyord cannot be reached." 
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
#Step 7 :Reverting the blocked site parameters to initial values
################################################################################ 
}  
set output10 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.X_Comcast_com_ParentalControl.ManagedSites.Enable false boolean]; 
puts $output10; 
if {[regexp {.*Time limit has crossed 2 minutes.*} $output10] == 1 } { 
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection"; 
puts "Failed to set 1st parameter"; 
set result "FAILED"; 
set passContent "Test Result : $result$~"; 
displayProc $passContent; 
exit 0; 
}  
 
set passContent "Test Result : $result$~"; 
displayProc $passContent; 
 

