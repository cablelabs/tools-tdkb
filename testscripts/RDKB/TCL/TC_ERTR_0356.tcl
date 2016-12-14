##########################################################################
# If not stated otherwise in this file or this component's Licenses.txt
# file the following copyright and licenses apply:
#
# Copyright 2016 RDK Management
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
##########################################################################
package require Expect;
source proc.tcl;
source lib.tcl;
puts {
####################################################################################################################################################                                                                                                  
#TESTCASEID : TC_ERTR_0356
#Description  : Verify that CM IP address of WG obtained through parameter (Device.X_CISCO_COM_CableModem.IPAddress)matches with the actual value
######################################################################################################################################################
 }
#Initializing the values to the parameters by invoking Initializer proc
#set configFile $argv;

set configFile $argv;
Initializer $configFile;

puts {
###########################################################################################################
#step 1 :Get the valus of the parameter (Device.X_CISCO_COM_CableModem.IPAddress)
###########################################################################################################
}

set response [device_set_get_param $ClassPath $Class $oui $SNno $deviceType GetParameterValue Device.X_CISCO_COM_CableModem.IPAddress null null {rType output}];
puts "The Result of Setparameter is $response";

if {[regexp -nocase {VALUE:(.*)\s+TYPE} $response m o]} {

#puts $m;
#puts $o;
} else {

puts "Unable to grep expected value";
set result "fail";
exit 0;
}

set passFlag "";
set failFlag "";

puts $CMip;

set g1 [string compare $CMip $o];

       if {$g1 == 0} {
        puts "CM IP VALUE matching";
        set passFlag [expr $passFlag + 1];
        } else {
set failFlag [expr $failFlag + 1];
puts "CM IP VALUE not matching";

        }



if {$passFlag == 1} {
set result "PASSED"
} else {
        if {$failFlag >0 || $passFlag <1} {
        set result "FAILED";
}
}


puts $result;

set passContent "Test Result : $result";
displayProc $passContent;

