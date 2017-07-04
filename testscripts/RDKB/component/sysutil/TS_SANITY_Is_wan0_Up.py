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
  <version>5</version>
  <!-- Do not edit version. This will be auto incremented while updating. If you are adding a new script you can keep the vresion as 1 -->
  <name>TS_SANITY_Is_wan0_Up</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id></primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>ExecuteCmd</primitive_test_name>
  <!--  -->
  <primitive_test_version>1</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>Check if wan0 interface is up and verifies whether its ip retrieved from ifconfig is same as the ip from tr181 param</synopsis>
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
  </box_types>
  <rdk_versions>
    <rdk_version>RDKB</rdk_version>
    <!--  -->
  </rdk_versions>
  <test_cases>
    <test_case_id>TC_SYSUTIL_3</test_case_id>
    <test_objective>Tests if wan0 interface is up and verifies whether its ip retrieved from ifconfig is same as the ip from tr181 param</test_objective>
    <test_type>Positive</test_type>
    <test_setup>XB3</test_setup>
    <pre_requisite>TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>ExecuteCmd() pam_GetParameterValues()</api_or_interface_used>
    <input_parameters>For getparamvalue() - ifconfig | grep -A 2 \"wan0\" | grep \"inet6 addr\" | tail -1 | cut -f13 -d ' ' |  cut -f1 -d '/' | tr \"\n\" \" \"

pam_GetParameterValues() - Device.X_CISCO_COM_CableModem.IPv6Address</input_parameters>
    <automation_approch>1.Function which needs to be tested will be configured in Test Manager GUI.
2.Python Script will be generated by Test Manager with provided arguments in configure page. 
3.TM will load the sysutil library and pamstub lib via Test agent
4.From python script, invoke ExecuteCmd() stub function to get the wan0 ip
5.with pamstub's getparamvalue() get Device.X_CISCO_COM_CableModem.IPv6Address and compare with above ip
5.Responses from the sysutil stub function will be logged in Agent Console log.
6.pam stub will validate the actual result with the expected result and send the result status to Test Manager.
7.Test Manager will publish the result in GUI as PASS/FAILURE based on the response from pam stub.</automation_approch>
    <except_output>CheckPoint 1:
 The output  should be logged in the Agent console/Component log

CheckPoint 2:
Stub function result should be success and should see corresponding log in the agent console log

CheckPoint 3:
TestManager GUI will publish the result as PASS in Execution/Console page of Test Manager</except_output>
    <priority>High</priority>
    <test_stub_interface>sysutil</test_stub_interface>
    <test_script>TS_SANITY_Is_wan0_Up</test_script>
    <skipped>No</skipped>
    <release_version></release_version>
    <remarks></remarks>
  </test_cases>
  <script_tags />
</xml>
'''

import tdklib; 
#Test component to be tested
sysObj = tdklib.TDKScriptingLibrary("sysutil","RDKB");
pamObj = tdklib.TDKScriptingLibrary("pam","RDKB");

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
sysObj.configureTestCase(ip,port,'TS_SANITY_Is_wan0_Up');
pamObj.configureTestCase(ip,port,'TS_SANITY_Is_wan0_Up');

#Get the result of connection with test component and STB
loadmodulestatus1 =sysObj.getLoadModuleResult();
loadmodulestatus2 =pamObj.getLoadModuleResult();

if "SUCCESS" in loadmodulestatus1.upper() and loadmodulestatus2.upper:
    #Set the result status of execution
    sysObj.setLoadModuleStatus("SUCCESS");
    pamObj.setLoadModuleStatus("SUCCESS");
    tdkTestObj = sysObj.createTestStep('ExecuteCmd');
    tdkTestObj.addParameter("command", "ifconfig | grep -A 2 wan0 | grep \"Scope:Global\" | cut -f13 -d ' ' |  cut -f1 -d '/' | tr \"\n\" \" \"");
    expectedresult="SUCCESS";

    #Execute the test case in STB
    tdkTestObj.executeTestCase(expectedresult);
    actualresult = tdkTestObj.getResult();
    details = tdkTestObj.getResultDetails().strip();

    if expectedresult in actualresult and details:
        ip = details;
        #Set the result status of execution
        tdkTestObj.setResultStatus("SUCCESS");
        print "TEST STEP 1: Check if wan0 is up"
        print "EXPECTED RESULT 1: wan0 should be up";
        print "ACTUAL RESULT 1: wan0 is up with ip %s" %ip;
        #Get the result of execution
        print "[TEST EXECUTION RESULT] : SUCCESS";

        #check if the ip obtained from tr181 param is same as above
        tdkTestObj = pamObj.createTestStep('pam_GetParameterValues');
        tdkTestObj.addParameter("ParamName","Device.X_CISCO_COM_CableModem.IPv6Address")
        expectedresult="SUCCESS";

        #Execute the test case in STB
        tdkTestObj.executeTestCase(expectedresult);
        actualresult = tdkTestObj.getResult();
        details = tdkTestObj.getResultDetails();

        if expectedresult in actualresult and details:
            tr_ip = details;
            #Set the result status of execution
            print "TEST STEP 2: Get ip value using tr181 param"
            print "EXPECTED RESULT 2: ip value received should be same as the ip from STEP1"
            print "ACTUAL RESULT 2: ip values retrieved is %s" %tr_ip;

            if ip == tr_ip:
                tdkTestObj.setResultStatus("SUCCESS");
                print "[TEST EXECUTION RESULT] : SUCCESS, both ip values are same";
            else:
                tdkTestObj.setResultStatus("FAILURE");
                print "[TEST EXECUTION RESULT] : FAILURE, both ip values are not the same";
        else:
            tdkTestObj.setResultStatus("FAILURE");
            print "TEST STEP 2: Get ip value using tr181 param"
            print "EXPECTED RESULT 2: should get the ip value";
            print "ACTUAL RESULT 2: failed to get ip value %s" %details;
            print "[TEST EXECUTION RESULT] : FAILURE";

    else:
        tdkTestObj.setResultStatus("FAILURE");
        print "TEST STEP 1: Check if wan0 is up"
        print "EXPECTED RESULT 1: wan0 should be up";
        print "ACTUAL RESULT 1: wan0 is not up ";
        print "[TEST EXECUTION RESULT] : FAILURE";
    sysObj.unloadModule("sysutil");
    pamObj.unloadModule("pam");

else:
        print "Failed to load sysutil module";
        sysObj.setLoadModuleStatus("FAILURE");
        print "Module loading failed";

					
