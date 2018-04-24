##########################################################################
# If not stated otherwise in this file or this component's Licenses.txt
# file the following copyright and licenses apply:
#
# Copyright 2018 RDK Management
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
'''
<?xml version="1.0" encoding="UTF-8"?><xml>
  <id/>
  <version>2</version>
  <name>TS_WIFIHAL_5GHzSetRadioFragmentationThreshold</name>
  <primitive_test_id/>
  <primitive_test_name>WIFIHAL_GetOrSetParamUIntValue</primitive_test_name>
  <primitive_test_version>3</primitive_test_version>
  <status>FREE</status>
  <synopsis>To set the radio fragmentation threshold using wifi_setRadioFragmentationThreshold() API for 5GHz.</synopsis>
  <groups_id/>
  <execution_time>5</execution_time>
  <long_duration>false</long_duration>
  <advanced_script>false</advanced_script>
  <remarks/>
  <skip>false</skip>
  <box_types>
    <box_type>Broadband</box_type>
    <box_type>Emulator</box_type>
    <box_type>RPI</box_type>
  </box_types>
  <rdk_versions>
    <rdk_version>RDKB</rdk_version>
  </rdk_versions>
  <test_cases>
    <test_case_id>TC_WIFIHAL_242</test_case_id>
    <test_objective>To set the Radio Fragmentation Threshold using wifi_setRadioFragmentationThreshold API for 5GHz.</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Broadband,Emulator,RPI</test_setup>
    <pre_requisite>1.Ccsp Components  should be in a running state else invoke cosa_start.sh manually that includes all the ccsp components and TDK Component
2.TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>wifi_setRadioFragmentationThreshold()</api_or_interface_used>
    <input_parameters>methodName : setRadioFragmentationThreshold
ApIndex : 1</input_parameters>
    <automation_approch>1.Load the module.
2.Set the Radio Fragmentation Threshold using wifi_setRadioFragmentationThreshold() API
3.Return SUCCESS if set operation is successful,else FAILURE.
4.Unload the module</automation_approch>
    <except_output>To set the Radio Fragmentation Threshold for 5GHz.</except_output>
    <priority>High</priority>
    <test_stub_interface>WIFIHAL</test_stub_interface>
    <test_script>TS_WIFIHAL_5GHzSetRadioFragmentationThreshold</test_script>
    <skipped>No</skipped>
    <release_version/>
    <remarks/>
  </test_cases>
  <script_tags/>
</xml>

'''
# use tdklib library,which provides a wrapper for tdk testcase script
import tdklib;
from wifiUtility import *;
import random;
#Test component to be tested
obj = tdklib.TDKScriptingLibrary("wifihal","1");

#IP and Port of box, No need to change
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_WIFIHAL_5GHzSetRadioFragmentationThreshold');

loadmodulestatus =obj.getLoadModuleResult();
print "[LIB LOAD STATUS]  :  %s" %loadmodulestatus

if "SUCCESS" in loadmodulestatus.upper():
    obj.setLoadModuleStatus("SUCCESS");

    expectedresult="SUCCESS";
    radioIndex = 1
    setMethod = "setRadioFragmentationThreshold"
    primitive = 'WIFIHAL_GetOrSetParamUIntValue'
    setThreshold = random.randint(0,64);
    #Calling the method from wifiUtility to execute test case and set result status for the test.
    tdkTestObj, actualresult, details = ExecuteWIFIHalCallMethod(obj, primitive, radioIndex, setThreshold, setMethod)

    if expectedresult in actualresult:
        print "setRadioFragmentationThreshold function successful: %s"%details
        tdkTestObj.setResultStatus("SUCCESS");
        print "TEST STEP 1: Set the Radio Fragmentation Threshold value for 5GHz";
        print "EXPECTED RESULT 1: Function Should set a Radio Fragmentation Threshold value";
        print "ACTUAL RESULT 1: Radio Fragmentation Threshold value set Successfully: %d"%setThreshold;
        print "[TEST EXECUTION RESULT] : SUCCESS";
    else:
        print "setRadioFragmentationThreshold function failed: %s"%details
        tdkTestObj.setResultStatus("FAILURE");
        print "TEST STEP 1: Set the Radio Fragmentation Threshold value for 5GHz";
        print "EXPECTED RESULT 1: Function Should set a Radio Fragmentation Threshold value";
        print "ACTUAL RESULT 1: Failed to set Radio Fragmentation Threshold value: %d"%setThreshold;
        print "[TEST EXECUTION RESULT] : FAILURE";
    obj.unloadModule("wifihal");
else:
    print "Failed to load wifi module";
    obj.setLoadModuleStatus("FAILURE");
