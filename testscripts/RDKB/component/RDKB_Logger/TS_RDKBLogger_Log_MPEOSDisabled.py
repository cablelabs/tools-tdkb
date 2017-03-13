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
  <id>1441</id>
  <version>4</version>
  <name>TS_RDKBLogger_Log_MPEOSDisabled</name>
  <primitive_test_id/>
  <primitive_test_name>RDKBLogger_Log</primitive_test_name>
  <primitive_test_version>1</primitive_test_version>
  <status>FREE</status>
  <synopsis>To check that no message is logged when MPEOS debug support is disabled.
Test Case ID: CT_RDKBLogger_37
Test Type: Negative</synopsis>
  <groups_id/>
  <execution_time>5</execution_time>
  <long_duration>false</long_duration>
  <remarks/>
  <skip>true</skip>
  <box_types>
    <box_type>Broadband</box_type>
    <box_type>RPI</box_type>
  </box_types>
  <rdk_versions>
    <rdk_version>RDKB</rdk_version>
  </rdk_versions>
  <test_cases>
    <test_case_id>TC_RDKLOGGER_21</test_case_id>
    <test_objective>To check that no message is logged when MPEOS debug support is disabled.</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Emulator,XB3</test_setup>
    <pre_requisite>1.Ccsp Components  should be in a running state of DUT that includes component under test Cable Modem
2.TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>None</api_or_interface_used>
    <input_parameters>Json Interface:
API Name
RDKBLogger_Log_MPEOSDisabled

Input:
module = "TEST1"
level = "ERROR"</input_parameters>
    <automation_approch>1.Function which needs to be tested will be configured in Test Manager GUI.
2.Python Script will be generated by Test Manager with provided arguments in configure page. 
3.TM will load the RDKLogger library via Test agent
4.From python script, invoke RDKBLogger_Log_MPEOSDisabled() stub function to check that no message is logged when MPEOS debug support is disabled.
5.RDKLogger stub function will call the rdk_logger_deinit(), rdk_logger_init() corresponding function of the rdk-logger component in ccsp.
6.Responses from the RDKLogger stub function will be logged in Agent Console log.
7.RDKLogger stub will validate the actual result with the expected result and send the result status to Test Manager.
8.Test Manager will publish the result in GUI as PASS/FAILURE based on the response from RDKLogger stub.</automation_approch>
    <except_output>CheckPoint 1:
No message should be logged in the Agent console/Component log

CheckPoint 2:
Stub function result should be success and should see corresponding log in the agent console log

CheckPoint 3:
TestManager GUI will publish the result as PASS in Execution/Console page of Test Manager</except_output>
    <priority>High</priority>
    <test_stub_interface>None</test_stub_interface>
    <test_script>TS_RDKBLogger_Log_MPEOSDisabled</test_script>
    <skipped>Yes</skipped>
    <release_version/>
    <remarks/>
  </test_cases>
  <script_tags/>
</xml>

'''
# use tdklib library,which provides a wrapper for tdk testcase script
from tdklib import TDKScriptingLibrary;

#IP and Port of box, No need to change,
#This will be replaced with corresponding Box Ip and port while executing script
ip = <ipaddress>
port = <port>

#Test component to be tested
obj = TDKScriptingLibrary("rdklogger","RDKB");
obj.configureTestCase(ip,port,'TS_RDKBLogger_Log_MPEOSDisabled');
#Get the result of connection with test component and Gateway
result =obj.getLoadModuleResult();
print "rdklogger module loading status :%s" %result;

#Check for SUCCESS/FAILURE of rdklogger module
if "SUCCESS" in result.upper():
    #Set the module loading status
    obj.setLoadModuleStatus("SUCCESS");

    #Primitive test case which associated to this Script
    tdkTestObj = obj.createTestStep('RDKBLogger_Log_MPEOSDisabled');

    expectedRes = "SUCCESS"

    module = "TEST1"
    print "Requested module: %s"%module
    tdkTestObj.addParameter("module",module);
    level = "ERROR"
    print "Requested level: %s"%level
    tdkTestObj.addParameter("level",level);

    #Execute the test case in Gateway
    tdkTestObj.executeTestCase(expectedRes);

    #Get the result of execution
    result = tdkTestObj.getResult();
    print "[TEST EXECUTION RESULT] : %s" %result;
    details = tdkTestObj.getResultDetails();
    #Set the result status of execution
    if "SUCCESS" in result.upper():
        tdkTestObj.setResultStatus("SUCCESS");
        print "Logging failed with MPEOS Disabled as expected";
    else:
        tdkTestObj.setResultStatus("FAILURE");
        print "Logging successful with MPEOS Disabled: [%s]"%details;

    #Reset the logging to default
    obj.initiateReboot();

    #unloading rdklogger module
    obj.unloadModule("rdklogger");
else:
    print "Failed to load rdklogger module";
    #Set the module loading status
    obj.setLoadModuleStatus("FAILURE");
