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
  <version>1</version>
  <name>TS_WIFIHAL_5GHzCancelApWPS</name>
  <primitive_test_id/>
  <primitive_test_name>WIFIHAL_ParamRadioIndex</primitive_test_name>
  <primitive_test_version>1</primitive_test_version>
  <status>FREE</status>
  <synopsis>To cancel the WPS mode of 5GHz</synopsis>
  <groups_id/>
  <execution_time>10</execution_time>
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
    <test_case_id>TC_WIFIHAL_268</test_case_id>
    <test_objective>To cancel the WPS mode of 5GHz by calling wifi_cancelApWPS() and checking if it returns SUCCESS</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Broadband, Emulator, RPI</test_setup>
    <pre_requisite>1.Ccsp Components  should be in a running state else invoke cosa_start.sh manually that includes all the ccsp components and TDK Component
2.TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>wifi_cancelApWPS()</api_or_interface_used>
    <input_parameters>methodName : cancelApWPS
radioIndex : 1</input_parameters>
    <automation_approch>1.Load the module
2.Using WIFIHAL_ParamRadioIndex, call wifi_cancelApWPS() API
3. Check if the api call is success, else return FAILURE from the script
4.Unload the module.</automation_approch>
    <except_output>wifi_cancelApWPS() should return SUCCESS</except_output>
    <priority>High</priority>
    <test_stub_interface>WIFIHAL</test_stub_interface>
    <test_script>TS_WIFIHAL_5GHzCancelApWPS</test_script>
    <skipped>No</skipped>
    <release_version/>
    <remarks/>
  </test_cases>
</xml>

'''
# use tdklib library,which provides a wrapper for tdk testcase script
import tdklib;

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("wifihal","1");

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_WIFIHAL_5GHzCancelApWPS');

#Get the result of connection with test component and DUT
loadmodulestatus =obj.getLoadModuleResult();
print "[LIB LOAD STATUS]  :  %s" %loadmodulestatus

if "SUCCESS" in loadmodulestatus.upper():
    obj.setLoadModuleStatus("SUCCESS");

    #Prmitive test case which associated to this Script
    tdkTestObj = obj.createTestStep('WIFIHAL_ParamRadioIndex');
    tdkTestObj.addParameter("radioIndex", 1);
    tdkTestObj.addParameter("methodName", "cancelApWPS");
    expectedresult="SUCCESS";

    #Execute the test case in DUT
    tdkTestObj.executeTestCase(expectedresult);
    actualresult = tdkTestObj.getResult();
    details = tdkTestObj.getResultDetails();

    if expectedresult in actualresult :
	tdkTestObj.setResultStatus("SUCCESS");
        print "TEST STEP : Call the function wifi_cancelApWPS()"
        print "EXPECTED RESULT : Should return SUCCESS"
        print "ACTUAL RESULT : %s " %details
        #Get the result of execution
        print "[TEST EXECUTION RESULT] : SUCCESS";
    else:
	tdkTestObj.setResultStatus("FAILURE");
        print "TEST STEP : Call the function wifi_cancelApWPS()"
        print "EXPECTED RESULT : Should return SUCCESS"
        print "ACTUAL RESULT 1: %s " %details
        #Get the result of execution
        print "[TEST EXECUTION RESULT] : FAILURE";
    obj.unloadModule("wifihal");
else:
    print "Failed to load the module";
    obj.setLoadModuleStatus("FAILURE");
    print "Module loading failed";
