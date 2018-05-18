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
  <version>2</version>
  <!-- Do not edit version. This will be auto incremented while updating. If you are adding a new script you can keep the vresion as 1 -->
  <name>TS_WIFIAGENT_IsWiFiNameSpaces_Available</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id></primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>WIFIAgent_Get</primitive_test_name>
  <!--  -->
  <primitive_test_version>1</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>To check if all the namespaces under Device.WiFi. are available in the image.</synopsis>
  <!--  -->
  <groups_id />
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
    <test_case_id>TC_WIFIAGENT_62</test_case_id>
    <test_objective>To check if all the namespaces under Device.WiFi. are available in the image.</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Broadband, Emulator, RPI</test_setup>
    <pre_requisite>1.Ccsp Components in DUT should be in a running state that includes component under test Cable Modem
2.TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>None</api_or_interface_used>
    <input_parameters>None</input_parameters>
    <automation_approch>1. Load wifiagent module
2. Using ExecuteCmd(), try to get the value of com.cisco.spvtg.ccsp.wifi.
3. Check if its value is valid or not
4. Validation of  the result is done within the python script and send the result status to Test Manager.
5. Test Manager will publish the result in GUI as PASS/FAILURE</automation_approch>
    <except_output>The wifi namespaces should be available in the device</except_output>
    <priority>High</priority>
    <test_stub_interface>wifiagent</test_stub_interface>
    <test_script>TS_WIFIAGENT_IsWiFiNameSpaces_Available</test_script>
    <skipped>No</skipped>
    <release_version>M59</release_version>
    <remarks></remarks>
  </test_cases>
  <script_tags>
    <script_tag>BASIC</script_tag>
    <!--  -->
  </script_tags>
</xml>
'''
# use tdklib library,which provides a wrapper for tdk testcase script 
import tdklib; 

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("wifiagent","1");
sysObj = tdklib.TDKScriptingLibrary("sysutil","RDKB");

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_WIFIAGENT_IsWiFiNameSpaces_Available');
sysObj.configureTestCase(ip,port,'TS_WIFIAGENT_IsWiFiNameSpaces_Available');

#Get the result of connection with test component and STB
loadmodulestatus1 =obj.getLoadModuleResult();
loadmodulestatus2 =sysObj.getLoadModuleResult();

if "SUCCESS" in loadmodulestatus1.upper() and "SUCCESS" in loadmodulestatus2.upper():
    obj.setLoadModuleStatus("SUCCESS");

    expectedresult="SUCCESS";
    tdkTestObj = obj.createTestStep('WIFIAgent_Get')
    tdkTestObj.addParameter("paramName","Device.WiFi.")
    tdkTestObj.executeTestCase(expectedresult);
    actualresult = tdkTestObj.getResult();
    details = tdkTestObj.getResultDetails();

    if expectedresult in actualresult and "Can't find destination component" not in details:
        #Set the result status of execution
        tdkTestObj.setResultStatus("SUCCESS");
        print "TEST STEP 1: Check if wifi namespaces are available or not"
        print "EXPECTED RESULT 1: WiFi namespaces should be available"
        print "ACTUAL RESULT 1: SUCCESS";
    else:
	#Set the result status of execution
        tdkTestObj.setResultStatus("FAILURE");
        print "TEST STEP 1: Check if wifi namespaces are available or not"
        print "EXPECTED RESULT 1: WiFi namespaces should be available"
        print "ACTUAL RESULT 1: FAILURE";
    obj.unloadModule("wifiagent");
    sysObj.unloadModule("sysutil");
else:
    print "Failed to load sysutil module";
    obj.setLoadModuleStatus("FAILURE");
