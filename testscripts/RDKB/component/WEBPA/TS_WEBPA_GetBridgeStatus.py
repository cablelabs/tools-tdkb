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
<?xml version='1.0' encoding='utf-8'?>
<xml>
  <id></id>
  <!-- Do not edit id. This will be auto filled while exporting. If you are adding a new script keep the id empty -->
  <version>3</version>
  <!-- Do not edit version. This will be auto incremented while updating. If you are adding a new script you can keep the vresion as 1 -->
  <name>TS_WEBPA_GetBridgeStatus</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id></primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>WEBPA_Donothing</primitive_test_name>
  <!--  -->
  <primitive_test_version>1</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>Using webpa, get the bridge status of the gateway and check if its from the list {Disabled,Enabled,Error}</synopsis>
  <!--  -->
  <groups_id />
  <!--  -->
  <execution_time>5</execution_time>
  <!--  -->
  <long_duration>false</long_duration>
  <!--  -->
  <advanced_script>false</advanced_script>
  <!-- execution_time is the time out time for test execution -->
  <remarks></remarks>
  <!-- Reason for skipping the tests if marked to skip -->
  <skip>false</skip>
  <!--  -->
  <box_types>
    <box_type>Broadband</box_type>
    <!--  -->
    <box_type>Emulator</box_type>
    <!--  -->
    <box_type>RPI</box_type>
    <!--  -->
  </box_types>
  <rdk_versions>
    <rdk_version>RDKB</rdk_version>
    <!--  -->
  </rdk_versions>
  <test_cases>
    <test_case_id>TC_WEBPA_1</test_case_id>
    <test_objective>Using webpa, get the bridge status of the gateway and check if its from the list {Disabled,Enabled,Error}</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Broadband, RPI, Emulator</test_setup>
    <pre_requisite>If SAT token is to be used, token should be created and made available in test manager. Also the config variables SAT_REQUIRED, SAT_TOKEN_FILE, SERVER_URI should be updated in webpaVariables.py</pre_requisite>
    <api_or_interface_used>webpaQuery
parseWebpaResponse</api_or_interface_used>
    <input_parameters>Device.Bridging.Bridge.1.Status</input_parameters>
    <automation_approch>1. Load sysutil module
2. Configure WEBPA server to send get request for Device.Bridging.Bridge.1.Status
3. Parse the WEBPA response
4.  If response status is 200 get operation was success otherwise failure
4. If get opeartion is success check if bridge std received is from the list  {Disabled,Enabled,Error}
5. Unload sysutil module</automation_approch>
    <except_output>Get operation status should be 200 and standard returned should be from the list  {Disabled,Enabled,Error}</except_output>
    <priority>High</priority>
    <test_stub_interface>sysutil</test_stub_interface>
    <test_script>TS_WEBPA_GetBridgeStatus</test_script>
    <skipped>No</skipped>
    <release_version>M58</release_version>
    <remarks>None</remarks>
  </test_cases>
  <script_tags />
</xml>
'''
# use tdklib library,which provides a wrapper for tdk testcase script
import tdklib;
from webpaUtility import *

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("sysutil","1");

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_WEBPA_GetBridgeStatus');

#Get the result of connection with test component and STB
result =obj.getLoadModuleResult();
print "[LIB LOAD STATUS]  :  %s" %result;

if "SUCCESS" in result.upper() :
    #Set the module loading status
    obj.setLoadModuleStatus("SUCCESS");

    bridgeStatus =  {"Disabled", "Enabled", "Error"}
    print "Expected bridge status : ", bridgeStatus
    queryParam = {"name":"Device.Bridging.Bridge.1.Status"}
    queryResponse = webpaQuery(obj, queryParam)

    parsedResponse = parseWebpaResponse(queryResponse, 1)
    tdkTestObj = obj.createTestStep('ExecuteCmd');
    tdkTestObj.executeTestCase("SUCCESS");
    if "SUCCESS" in parsedResponse[0] and parsedResponse[1] != "":
        getStatus = parsedResponse[1];
        if getStatus in bridgeStatus:
            tdkTestObj.setResultStatus("SUCCESS");
            print "Device Bridge Status::",getStatus
            print "[TEST EXECUTION RESULT] : SUCCESS"
        else:
            tdkTestObj.setResultStatus("FAILURE");
            print "[TEST EXECUTION RESULT] : FAILURE, invalid status received"
    else:
        tdkTestObj.setResultStatus("FAILURE");
        print "[TEST EXECUTION RESULT] : FAILURE"
    obj.unloadModule("sysutil");

else:
    print "FAILURE to load module";
    obj.setLoadModuleStatus("FAILURE");
    print "Module loading FAILURE";
