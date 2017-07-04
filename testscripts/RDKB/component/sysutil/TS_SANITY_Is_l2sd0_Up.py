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
  <version>6</version>
  <!-- Do not edit version. This will be auto incremented while updating. If you are adding a new script you can keep the vresion as 1 -->
  <name>TS_SANITY_Is_l2sd0_Up</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id></primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>ExecuteCmd</primitive_test_name>
  <!--  -->
  <primitive_test_version>1</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>Check if l2sd0.100 and l2sd0.101 interface is up and verifies whether its listed as interface of brlan0 and brlan1 respectively in brctl show</synopsis>
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
    <test_case_id>TC_SYSUTIL_4</test_case_id>
    <test_objective>Tests if l2sd0.100 and l2sd0.101 interface is up and verifies whether its listed in 'brctl  show' output</test_objective>
    <test_type>Positive</test_type>
    <test_setup>XB3</test_setup>
    <pre_requisite>TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>ExecuteCmd()</api_or_interface_used>
    <input_parameters>ifconfig | grep -w 'l2sd0.100\|l2sd0.101' | tr \"\n\" \"  \"
brctl show | grep l2sd0.100 | grep brlan0 | tr \"\n\" \"  \" | tr \"\t\" \" \"; brctl show | grep l2sd0.101 | grep brlan1 | tr \"\t\" \" \"</input_parameters>
    <automation_approch>1.Function which needs to be tested will be configured in Test Manager GUI.
2.Python Script will be generated by Test Manager with provided arguments in configure page. 
3.TM will load the sysutil library and pamstub lib via Test agent
4.From python script, invoke ExecuteCmd() stub function to get the status of  l2sd0.100 and l2sd0.101 
5. With ExecuteCmd() check output of brctl show command
5.Responses from the sysutil stub function will be logged in Agent Console log.
6.script will validate the actual result with the expected result and send the result status to Test Manager.
7.Test Manager will publish the result in GUI as PASS/FAILURE based on the response from stub.</automation_approch>
    <except_output>CheckPoint 1:
 The output  should be logged in the Agent console/Component log

CheckPoint 2:
Stub function result should be success and should see corresponding log in the agent console log

CheckPoint 3:
TestManager GUI will publish the result as PASS in Execution/Console page of Test Manager</except_output>
    <priority>High</priority>
    <test_stub_interface>sysutil</test_stub_interface>
    <test_script>TS_SANITY_Is_l2sd0_Up</test_script>
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

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
sysObj.configureTestCase(ip,port,'TS_SANITY_Is_l2sd0_Up');

#Get the result of connection with test component and STB
loadmodulestatus1 =sysObj.getLoadModuleResult();

if "SUCCESS" in loadmodulestatus1.upper():
    #Set the result status of execution
    sysObj.setLoadModuleStatus("SUCCESS");
    tdkTestObj = sysObj.createTestStep('ExecuteCmd');
    tdkTestObj.addParameter("command", "ifconfig | grep -w 'l2sd0.100\|l2sd0.101' | tr \"\n\" \"  \"");
    expectedresult="SUCCESS";

    #Execute the test case in STB
    tdkTestObj.executeTestCase(expectedresult);
    actualresult = tdkTestObj.getResult();
    details = tdkTestObj.getResultDetails().strip();

    if expectedresult in actualresult and details:
        #Set the result status of execution
        print "TEST STEP 1: Check if l2sd0.100 and l2sd0.101 is up"
        print "EXPECTED RESULT 1: l2sd0.100 and l2sd0.101 should be up";
        print "ACTUAL RESULT 1: l2sd0.100 and l2sd0.101 is up" 
        #if details == "2":
        if "l2sd0.100" in details and "l2sd0.101" in details :
            tdkTestObj.setResultStatus("SUCCESS");
            print "[TEST EXECUTION RESULT] : SUCCESS %s" %details;
        else:
            tdkTestObj.setResultStatus("FAILURE");
            print "[TEST EXECUTION RESULT] : FAILURE %s" %details;

	#checking brctl show output
        tdkTestObj.addParameter("command","brctl show | grep l2sd0.100 | grep brlan0 | tr \"\n\" \"  \" | tr \"\t\" \" \"; brctl show | grep l2sd0.101 | grep brlan1 | tr \"\t\" \" \"");
        expectedresult="SUCCESS";

        #Execute the test case in STB
        tdkTestObj.executeTestCase(expectedresult);
        actualresult = tdkTestObj.getResult();
        details = tdkTestObj.getResultDetails();

        if expectedresult in actualresult and details:
            #Set the result status of execution
            print "TEST STEP 2: Check if l2sd0.100 and l2sd0.101 is listed in brctl show";
            print "EXPECTED RESULT 2: l2sd0.100 and l2sd0.101 should be listed in brctl show"
            print "ACTUAL RESULT 2: l2sd0.100 and l2sd0.101 is listed"

            if "brlan0" in details and "brlan1" in details:
                tdkTestObj.setResultStatus("SUCCESS");
                print "[TEST EXECUTION RESULT] : SUCCESS %s" %details;
            else:
                tdkTestObj.setResultStatus("FAILURE");
                print "[TEST EXECUTION RESULT] : FAILURE %s" %details;
        else:
            tdkTestObj.setResultStatus("FAILURE");
            print "TEST STEP 2: Check if l2sd0.100 and l2sd0.101 is listed in brctl show"
            print "EXPECTED RESULT 2: l2sd0.100 and l2sd0.101 should be listed in brctl show"
            print "ACTUAL RESULT 2: l2sd0.100 and l2sd0.101 is not listed %s" %details;
            print "[TEST EXECUTION RESULT] : FAILURE";

    else:
        tdkTestObj.setResultStatus("FAILURE");
        print "TEST STEP 1: Check if l2sd0.100 and l2sd0.101 is up"
        print "EXPECTED RESULT 1: l2sd0.100 and l2sd0.101 should be up";
        print "ACTUAL RESULT 1: l2sd0.100 and l2sd0.101 is not up ";
        print "[TEST EXECUTION RESULT] : FAILURE";
    sysObj.unloadModule("sysutil");

else:
        print "Failed to load sysutil module";
        sysObj.setLoadModuleStatus("FAILURE");
        print "Module loading failed";

					
