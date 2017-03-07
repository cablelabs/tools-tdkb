package require Expect;
source proc.tcl;
puts {
##########################################################################################################################################
#TEST CASEID :TC_ERTR_0353                                                                                                   
#Description  :Verify that MAC address of the device connected via WIFI can be verified from WG
#(Device.WiFi.AccessPoint.$si2.AssociatedDevice.1.MACAddress)
##########################################################################################################################################
}
#Initializing the values to the parameters by invoking Initializer proc
set configFile $argv;
Initializer $configFile;
puts {
################################################################################
#Step 1 :Getting the value of the MAC address of the associated device to the WG
################################################################################
}
set output1 "";
set output1 [exec java -cp $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.WiFi.AccessPoint.$si2.AssociatedDevice.1.MACAddress null null];
puts $output1;
if {[regexp {.*Time limit has crossed 2 minutes.*} $output1] == 1 } {
puts "\nPossible errors:\n1.Device might not be listed\n2.Wrong parameters or values\n3.Network connection";
puts "Failed to get 1st parameter";
set result "FAILED";
set passContent "Test Result : $result$~";
displayProc $passContent;
exit 0;
}

regexp {.*VALUE:([0-9 A-F]{1,2}:[0-9 A-F]{1,2}:[0-9 A-F]{1,2}:[0-9 A-F]{1,2}:[0-9 A-F]{1,2}:[0-9 A-F]{1,2}) TYPE.*} $output1 match MAC1;


set m1 [regexp -all -inline {[0-9 A-F]{1,2}} $MAC1];

set interface_name1 [split $wlanInterfaceName "_"];

puts {
################################################################################
#Step 2: Trying to Telnet to WLAN Client and get the MAC address                                                     
################################################################################
}
spawn telnet $wlanIP $telnetPort
set timeout 100;
expect -re (.*ogin:);
send "$wlanName\r";
expect -re (.*word:);
send "$wlanPassword\r";
expect -re ".*>";
send "netsh wlan add profile filename=\"$profilePath\\Wireless.xml\" interface=\"$interface_name1\"\r";
expect -re ".*>";
send "netsh wlan connect $ssid2\r";
expect -re ".*>";
set outpCon $expect_out(buffer);
after 20000;
send "ipconfig /all\r";
expect -re ".*>";
set outIp $expect_out(buffer);
send "netsh wlan show interfaces\r";
expect -re ".*>";
set outInt $expect_out(buffer);
send "netsh wlan delete profile name=\"$ssid2\"\r";
expect -re ".*>";
send "exit\r"
expect -re ".*>";
#wait
close $spawn_id
set passFlag "";
set failFlag "";


if {[regexp {.*Physical address.*: (.*)State} $outInt match MAC2] == 1 } {
        puts "Expected Value: $MAC1";
        puts "Obtained Value :  $MAC2";
        set f [string trim $MAC2];
puts $f;
set g [string tolower $MAC1];
puts $f;
puts $g;
set g1 [string compare $f $g];
puts $g1;
       if {$g1 == 0} {
        puts "MAC ADDRESS VALUE matching";
        set passFlag [expr $passFlag + 1];
        } else {
		spawn telnet $wlanIP $telnetPort2
		set timeout 100;
		expect -re (.*ogin:);
		send "$wlanName2\r";
		expect -re (.*word:);
		send "$wlanPassword2\r";
		expect -re ".*>";
		send "netsh wlan add profile filename=\"$profilePath1\\Wireless.xml\" interface=\"$wlanInterfaceName2\"\r";
		expect -re ".*>";
		send "netsh wlan connect $ssid2\r";
		expect -re ".*>";
		set outpCon $expect_out(buffer);
		after 20000;
		send "ipconfig /all\r";
		expect -re ".*>";
		set outIp $expect_out(buffer);
		send "netsh wlan show interfaces\r";
		expect -re ".*>";
		set outInt $expect_out(buffer);
		send "netsh wlan delete profile name=\"$ssid2\"\r";
		expect -re ".*>";
		send "exit\r"
		expect -re ".*>";
		#wait
		close $spawn_id
		set passFlag "";
		set failFlag "";


		if {[regexp {.*Physical address.*: (.*)State} $outInt match MAC2] == 1 } {
				puts "Expected Value: $MAC1";
				puts "Obtained Value :  $MAC2";
				set f [string trim $MAC2];
		set g [string tolower $MAC1];
		set g1 [string compare $f $g];
			   if {$g1 == 0} {
				puts "MAC ADDRESS VALUE matching";
				set passFlag [expr $passFlag + 1];
				} else {
		set failFlag [expr $failFlag + 1];
		puts "MAC ADDRESS VALUE not matching";
				}
set failFlag [expr $failFlag + 1];
puts "MAC ADDRESS VALUE not matching";

        }
}
}
puts $passFlag;



puts {
################################################################################
#Step 3 :Validating whether the MAC address on the WG and WLAN Server are same
################################################################################
}
puts "MAC Address on WG: $MAC1";
puts "MAC Address on Associated Device: $MAC2";


 if {$passFlag == 1} {
set result "PASSED"
} else {
        if {$failFlag >0 || $passFlag <1} {
        set result "FAILED";
}
 }

set passContent "Test Result : $result$~";
displayProc $passContent;


