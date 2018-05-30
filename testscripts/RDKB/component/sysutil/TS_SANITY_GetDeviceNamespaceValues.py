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
  <version>5</version>
  <name>TS_SANITY_GetDeviceNamespaceValues</name>
  <primitive_test_id/>
  <primitive_test_name>ExecuteCmd</primitive_test_name>
  <primitive_test_version>1</primitive_test_version>
  <status>FREE</status>
  <synopsis>This test case will retrieve the full list of TR-181 parameter values under Device.</synopsis>
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
    <test_case_id>TC_SYSUTIL_11</test_case_id>
    <test_objective>This test case will retrieve the full list of TR-181 parameter values under Device.</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Broadband, RPI, Emulator</test_setup>
    <pre_requisite>TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>WIFIAgent_Get</api_or_interface_used>
    <input_parameters>paramName : Device.</input_parameters>
    <automation_approch>1.Function which needs to be tested will be configured in Test Manager GUI.
2.Python Script will be generated by Test Manager with provided arguments in configure page. 
3.TM will load the wifiagent lib via Test agent
4.From python script, invoke WIFIAgent_Get with param as Device.
5.Responses from the wifiagent stub function will be logged in Agent Console log.
6.Check whether all the TR-181 parameter values under Device. are listed
7.Test Manager will publish the result in GUI as PASS/FAILURE based on the response from wifiagent stub.</automation_approch>
    <except_output>All the TR-181 parameters values under Device. should be listed successfully</except_output>
    <priority>High</priority>
    <test_stub_interface>sysutil</test_stub_interface>
    <test_script>TS_SANITY_GetDeviceNamespaceValues</test_script>
    <skipped>No</skipped>
    <release_version>M59</release_version>
    <remarks/>
  </test_cases>
  <script_tags>
    <script_tag>BASIC</script_tag>
  </script_tags>
</xml>

'''
# use tdklib library,which provides a wrapper for tdk testcase script 
import tdklib;

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("wifiagent","RDKB");

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_SANITY_GetDeviceNamespaceValues');

#Get the result of connection with test component and DUT
loadmodulestatus =obj.getLoadModuleResult();

if "SUCCESS" in loadmodulestatus.upper():
    obj.setLoadModuleStatus("SUCCESS");
    expectedresult="SUCCESS";
    tdkTestObj = obj.createTestStep('WIFIAgent_Get')
    tdkTestObj.addParameter("paramName","Device.")
    tdkTestObj.executeTestCase(expectedresult);
    actualresult = tdkTestObj.getResult();
    details = tdkTestObj.getResultDetails();
    if expectedresult in actualresult and "Can't find destination component" not in details:
        #Set the result status of execution
        tdkTestObj.setResultStatus("SUCCESS");
        print "TEST STEP 1: Query the full list of namespace values under Device."
        print "EXPECTED RESULT 1: Should list the values of the namespace under Device."
        print "ACTUAL RESULT 1: Listed the values of the namespace under Device. successfully";
    else:
	#Set the result status of execution
        tdkTestObj.setResultStatus("FAILURE");
        print "TEST STEP 1: Query the full list of namespace values under Device."
        print "EXPECTED RESULT 1: Should list the values of the namespace under Device."
        print "ACTUAL RESULT 1: Failed to list the values of the namespace under Device.";
    obj.unloadModule("wifiagent");
else:
    print "Failed to load wifiagent module";
    obj.setLoadModuleStatus("FAILURE");
