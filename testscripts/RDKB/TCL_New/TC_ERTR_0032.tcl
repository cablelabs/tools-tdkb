package require Expect;
source proc.tcl;
puts {
################################################################################
#TEST CASE ID :TC_ERTR_0032
														    
#Description  :Verify whether Network name broadcast (SSID advertisement) is 
enabled by default in WG                
################################################################################
 }
 #Initializing the values to the parameters by invoking Initializer proc
set configFile $argv;
Initializer $configFile;
puts {
################################################################################
#Step 1 :Verifying the value of SSID advertisement                                                               			 
################################################################################
}

set output2 "";
set output2 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.WiFi.AccessPoint.$si2.SSIDAdvertisementEnabled null null];
puts $output2;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output2] == 1 } {
puts "\nPossible error:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 1st parameter";
set result "FAILED";	
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

puts {
################################################################################
#Step 2 :Trying to Telnet to WLAN Client                                                          					 
################################################################################
}
spawn telnet $wlanIP $telnetPort
set timeout 100;
expect -re (.*ogin:);
send "$wlanName\r"; 
expect -re (.*word:); 
send "$wlanPassword\r";
expect -re ".*>";
match_max 50000;
send "netsh wlan show networks\r";
expect -re ".*>";
set outpRad $expect_out(buffer);
send "exit\r"
expect -re ".*>";
#wait

close $spawn_id
set passFlag "";
set failFlag "";
puts {
################################################################################
#Step 3 :Checking the availability of the Network name          					 
################################################################################
}
puts "Expected: Network name \"$ssid2\" should be broadcasted"; 
if { [regexp {RDKB-2.4} $outpRad] == 1} {
set passFlag [expr $passFlag + 1];	
puts "\nObtained: Network name \"$ssid2\" is broadcasted on the network";
} else {
set failFlag [expr $failFlag + 1];
puts "\nObtained: Network name \"$ssid2\" is not broadcasted on the network";
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
#Step 4 : Reverting the SSID advertisement to its default value                                                               			 
################################################################################
}
set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType SetParameterValue Device.WiFi.AccessPoint.$si2.SSIDAdvertisementEnabled true boolean];
puts $output1;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output1] == 1 } {
puts "\nPossible error:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to set 1st parameter"
set result "FAILED";
	
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}
set passContent "Test Result : $result$~";
displayProc $passContent;

  
			
 
