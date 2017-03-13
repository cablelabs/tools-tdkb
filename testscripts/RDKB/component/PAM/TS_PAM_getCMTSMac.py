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
'''
<?xml version="1.0" encoding="UTF-8"?><xml>
  <id/>
  <version>2</version>
  <name>TS_PAM_getCMTSMac</name>
  <primitive_test_id/>
  <primitive_test_name>pam_GetParameterValues</primitive_test_name>
  <primitive_test_version>1</primitive_test_version>
  <status>FREE</status>
  <synopsis>Test to get CMTS MAC</synopsis>
  <groups_id/>
  <execution_time>1</execution_time>
  <long_duration>false</long_duration>
  <remarks/>
  <skip>false</skip>
  <box_types>
    <box_type>RPI</box_type>
    <box_type>Broadband</box_type>
  </box_types>
  <rdk_versions>
    <rdk_version>RDKB</rdk_version>
  </rdk_versions>
  <test_cases>
    <test_case_id>TC_PAM_122</test_case_id>
    <test_objective>To get the CMTS MAC</test_objective>
    <test_type>Positive</test_type>
    <test_setup>XB3</test_setup>
    <pre_requisite>TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>pam_GetParameterValues()</api_or_interface_used>
    <input_parameters>Device.DeviceInfo.X_RDKCENTRAL-COM_CMTS_MAC</input_parameters>
    <automation_approch>1.Function which needs to be tested will be configured in Test Manager GUI.
2.Python Script will be generated by Test Manager with provided arguments in configure page. 
3.TM will load the pamstub lib via Test agent
5.with pamstub's getparamvalue() get Device.DeviceInfo.X_RDKCENTRAL-COM_CMTS_MAC
6.pam stub will validate the actual result with the expected result and send the result status to Test Manager.
7.Test Manager will publish the result in GUI as PASS/FAILURE based on the response from pam stub.</automation_approch>
    <except_output>CheckPoint 1:
 The output  should be logged in the Agent console/Component log

CheckPoint 2:
Stub function result should be success and should see corresponding log in the agent console log

CheckPoint 3:
TestManager GUI will publish the result as PASS in Execution/Console page of Test Manager</except_output>
    <priority>High</priority>
    <test_stub_interface>pam</test_stub_interface>
    <test_script>TS_PAM_getCMTSMac</test_script>
    <skipped>No</skipped>
    <release_version/>
    <remarks/>
  </test_cases>
  <script_tags/>
</xml>

'''
						# use tdklib library,which provides a wrapper for tdk testcase script 
import tdklib; 

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("pam","1");

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_PAM_getCMTSMac');

#Get the loadmodulestatus of execution
loadmodulestatus = obj.getLoadModuleResult();
print "[TEST EXECUTION RESULT] : %s" %loadmodulestatus;

if "SUCCESS" in loadmodulestatus.upper():
        obj.setLoadModuleStatus("SUCCESS");

        #Script to load the configuration file of the component
        tdkTestObj = obj.createTestStep("pam_GetParameterValues");
        tdkTestObj.addParameter("ParamName","Device.DeviceInfo.X_RDKCENTRAL-COM_CMTS_MAC");
        expectedresult="SUCCESS";
        tdkTestObj.executeTestCase(expectedresult);
        actualresult = tdkTestObj.getResult();

        if expectedresult in actualresult:
            #Set the result status of execution
            tdkTestObj.setResultStatus("SUCCESS");
            details = tdkTestObj.getResultDetails();
            print "TEST STEP 1: Retrieve the CMTS MAC detail";
            print "EXPECTED RESULT 1: Should retrieve the CMTS MAC detail successfully";
            print "ACTUAL RESULT 1: %s" %details;
            #Get the result of execution
            print "[TEST EXECUTION RESULT] : %s" %actualresult ;
        else:
            tdkTestObj.setResultStatus("FAILURE");
            details = tdkTestObj.getResultDetails();
            print "TEST STEP 1: Retrieve the CMTS MAC detail";
            print "EXPECTED RESULT 1: Should retrieve CMTS MAC detail successfully";
            print "ACTUAL RESULT 1: %s" %details;
            print "[TEST EXECUTION RESULT] : %s" %actualresult ;

        obj.unloadModule("pam");
else:
        print "Failed to load the module";
        obj.setLoadModuleStatus("FAILURE");
        print "Module loading failed";

