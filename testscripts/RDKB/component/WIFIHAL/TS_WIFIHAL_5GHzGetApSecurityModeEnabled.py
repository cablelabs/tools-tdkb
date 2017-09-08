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
<?xml version='1.0' encoding='utf-8'?>
<xml>
  <id></id>
  <!-- Do not edit id. This will be auto filled while exporting. If you are adding a new script keep the id empty -->
  <version>3</version>
  <!-- Do not edit version. This will be auto incremented while updating. If you are adding a new script you can keep the vresion as 1 -->
  <name>TS_WIFIHAL_5GHzGetApSecurityModeEnabled</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id> </primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>WIFIHAL_GetOrSetParamStringValue</primitive_test_name>
  <!--  -->
  <primitive_test_version>1</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>To check the access point Security mode enabled for 5GHz radio using  wifi_getApSecurityModeEnabled HAL API and validate the same </synopsis>
  <!--  -->
  <groups_id>4</groups_id>
  <!--  -->
  <execution_time>1</execution_time>
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
    <test_case_id>TC_WIFIHAL_85</test_case_id>
    <test_objective>To check if Access point Security mode enabled for 5GHz radio using  wifi_getApSecurityModeEnabled HAL API and validate the same</test_objective>
    <test_type>Positive</test_type>
    <test_setup>XB3. XB6, Emulator, Rpi</test_setup>
    <pre_requisite>
1.Ccsp Components  should be in a running state else invoke cosa_start.sh manually that includes all the ccsp components and TDK Component
2.TDK Agent should be in running state or invoke it through StartTdk.sh script
    </pre_requisite>
    <api_or_interface_used>wifi_getApSecurityModeEnabled()</api_or_interface_used>
    <input_parameters>
methodName :   getApSecurityModeEnabled
apIndex    :   1
    </input_parameters>
    <automation_approch>
1.Configure the Function info in Test Manager GUI  which needs to be tested (WIFIHAL_GetOrSetParamStringValue  - func name - "If not exists already" WIFIHAL - module name Necessary I/P args as Mentioned in Input)
2.Python Script will be generated/overrided automatically by Test Manager with provided arguments in configure page (TS_WIFIHAL_5GHzGetApSecurityModeEnabled.py)
3.Execute the generated Script(TS_WIFIHAL_5GHzGetApSecurityModeEnabled.py) using execution page of  Test Manager GUI
4.wifihalstub which is a part of TDK Agent process, will be in listening mode to execute TDK Component function named WIFIHAL_GetOrSetParamStringValue through registered TDK wifihalstub function along with necessary Path Name as arguments
5.WIFIHAL_GetOrSetParamStringValue function will call Ccsp Base Function named "ssp_WIFIHALGetOrSetParamStringValue", that inturn will call WIFIHAL Library Function wifi_getApSecurityModeEnabled() function
6.Response(s)(printf) from TDK Component,Ccsp Library function and wifihalstub would be logged in Agent Console log based on the debug info redirected to agent console
7.wifihalstub will validate the available result (from agent console log and Pointer to instance as updated) with expected result
8.Test Manager will publish the result in GUI as SUCCESS/FAILURE based on the response from wifihalstub
    </automation_approch>
    <except_output>
CheckPoint
1:wifi_getApSecurityModeEnabled from DUT should be available in Agent Console LogCheckPoint
2:TDK agent Test Function will log the test case result as PASS based on API response CheckPoint
3:Test Manager GUI will publish the result as SUCCESS in Execution page
    </except_output>
    <priority>High</priority>
    <test_stub_interface>WIFIHAL</test_stub_interface>
    <test_script>TS_WIFIHAL_5GHzGetApSecurityModeEnabled</test_script>
    <skipped>No</skipped>
    <release_version></release_version>
    <remarks></remarks>
  </test_cases>
  <script_tags/>
</xml>
'''
# use tdklib library,which provides a wrapper for tdk testcase script
import tdklib;
from wifiUtility import *;

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("wifihal","1");

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_WIFIHAL_5GHzGetApSecurityModeEnabled');

loadmodulestatus =obj.getLoadModuleResult();
print "[LIB LOAD STATUS]  :  %s" %loadmodulestatus

if "SUCCESS" in loadmodulestatus.upper():
    obj.setLoadModuleStatus("SUCCESS");

    expectedresult="SUCCESS";
    apIndex = 1
    getMethod = "getApSecurityModeEnabled"
    primitive = 'WIFIHAL_GetOrSetParamStringValue'

    #Calling the method from wifiUtility to execute test case and set result status for the test.
    tdkTestObj, actualresult, details = ExecuteWIFIHalCallMethod(obj, primitive, apIndex, 0, getMethod)

    #List of supported security modes.
    supportedModes = ['None', 'WPA-Personal', 'WPA2-Personal', 'WPA-WPA2-Personal', 'WPA-Enterprise', 'WPA2-Enterprise', 'WPA-WPA2-Enterprise']

    if expectedresult in actualresult:
       mode = details.split(":")[1].strip()
       if mode in supportedModes:
            print "Security mode is in valid supported security modes %s"%details
	    tdkTestObj.setResultStatus("SUCCESS");
	    print "TEST STEP 1: Validate the Security mode Enabled";
	    print "EXPECTED RESULT 1: Security modes should be in ['None', 'WPA-Personal', 'WPA2-Personal', 'WPA-WPA2-Personal', 'WPA-Enterprise', 'WPA2-Enterprise', 'WPA-WPA2-Enterprise']";
	    print "ACTUAL RESULT 1: Security mode received is: %s"%mode;
            print "[TEST EXECUTION RESULT] : SUCCESS";
       else:
	    print "Security mode is NOT in valid supported security modes "%details
            tdkTestObj.setResultStatus("FAILURE");
	    print "TEST STEP 1: Validate the Security mode Enabled";
	    print "EXPECTED RESULT 1: Security modes should be in ['None', 'WPA-Personal', 'WPA2-Personal', 'WPA-WPA2-Personal', 'WPA-Enterprise', 'WPA2-Enterprise', 'WPA-WPA2-Enterprise']";
	    print "ACTUAL RESULT 1: Security mode received is: %s"%mode;
            print "[TEST EXECUTION RESULT] : FAILURE";
    else:
       print "getApSecurityModeEnabled() failed"
       tdkTestObj.setResultStatus("FAILURE");

    obj.unloadModule("wifihal");

else:
    print "Failed to load wifi module";
    obj.setLoadModuleStatus("FAILURE");
