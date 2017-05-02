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
  <version>4</version>
  <!-- Do not edit version. This will be auto incremented while updating. If you are adding a new script you can keep the vresion as 1 -->
  <name>TS_TAD_API_Ping_SetCfg</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id> </primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>TADstub_SetCfg</primitive_test_name>
  <!--  -->
  <primitive_test_version>1</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>To verify the functionality of diag_setcfg() api</synopsis>
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
  </box_types>
  <rdk_versions>
    <rdk_version>RDKB</rdk_version>
    <!--  -->
  </rdk_versions>
  <test_cases>
    <test_case_id>TC_TAD_50</test_case_id>
    <test_objective>To verify the functionality of diag_setcfg() api</test_objective>
    <test_type>Positive</test_type>
    <test_setup>xb3, emulator</test_setup>
    <pre_requisite>1.Ccsp Components  should be in a running state else invoke cosa_start.sh manually that includes all the ccsp components.
2.TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>diag_setcfg</api_or_interface_used>
    <input_parameters>mode
host</input_parameters>
    <automation_approch>1. Load  TAD modules
2. From script invoke TADstub_SetCfg() with mode as ping and a host name
3. Invoke TADstub_GetCfg() to check for the set values
4. check whether set and get values are same
5. Validation of  the result is done within the python script and send the result status to Test Manager.
6.Test Manager will publish the result in GUI as PASS/FAILURE based on the response from TAD stub.</automation_approch>
    <except_output>Value retreived by TADstub_GetCfg() should be same as that set by TADstub_SetCfg()</except_output>
    <priority>High</priority>
    <test_stub_interface>TAD</test_stub_interface>
    <test_script>TS_TAD_API_Ping_SetCfg</test_script>
    <skipped>No</skipped>
    <release_version></release_version>
    <remarks></remarks>
  </test_cases>
  <script_tags />
</xml>
'''
						# use tdklib library,which provides a wrapper for tdk testcase script 
import tdklib; 

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("tad","1");

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_TAD_API_Ping_SetCfg');

loadmodulestatus =obj.getLoadModuleResult();
print "[LIB LOAD STATUS]  :  %s" %loadmodulestatus ;

if "SUCCESS" in loadmodulestatus.upper():
    obj.setLoadModuleStatus("SUCCESS");
    #Prmitive test case which associated to this Script
    tdkTestObj = obj.createTestStep('TADstub_Init');
    expectedresult="SUCCESS";

    #Execute the test case in STB
    tdkTestObj.executeTestCase(expectedresult);
    actualresult = tdkTestObj.getResult();
    details = tdkTestObj.getResultDetails();
    if expectedresult in actualresult:
        #Set the result status of execution
        tdkTestObj.setResultStatus("SUCCESS");
        print "TEST STEP 1: Set diagnostics init"
        print "EXPECTED RESULT 1: Should set diagnostics init";
        print "ACTUAL RESULT 1:  %s" %details;
        #Get the result of execution
        print "[TEST EXECUTION RESULT] : SUCCESS";
    else:
        tdkTestObj.setResultStatus("FAILURE");
        print "TEST STEP 1: Set diagnostics init"
        print "EXPECTED RESULT 1: Should set diagnostics init";
        print "ACTUAL RESULT 1:  %s" %details;
        #Get the result of execution
        print "[TEST EXECUTION RESULT] : FAILURE, exiting script";
	exit();

    tdkTestObj = obj.createTestStep('TADstub_SetCfg');

    #setting mode 0 for ping
    tdkTestObj.addParameter("mode",1);
    tdkTestObj.addParameter("host","google.com");

    #Execute the test case in STB
    tdkTestObj.executeTestCase(expectedresult);
    actualresult = tdkTestObj.getResult();
    details = tdkTestObj.getResultDetails();
    if expectedresult in actualresult:
        #Set the result status of execution
        tdkTestObj.setResultStatus("SUCCESS");
        print "TEST STEP 1: Set ping config values"
        print "EXPECTED RESULT 1: Should set the ping config";
        print "ACTUAL RESULT 1:  %s" %details;
        #Get the result of execution
        print "[TEST EXECUTION RESULT] : SUCCESS";

	#verify using getCfg()
	tdkTestObj = obj.createTestStep('TADstub_GetCfg');
        #setting mode 0 for ping
        tdkTestObj.addParameter("mode",0);

        tdkTestObj.executeTestCase(expectedresult);
        actualresult = tdkTestObj.getResult();
        details = tdkTestObj.getResultDetails();
        if expectedresult in actualresult and "host" in details:
            #Set the result status of execution
            tdkTestObj.setResultStatus("SUCCESS");
            print "TEST STEP 1: Get ping config values"
            print "EXPECTED RESULT 1: Should get the ping config";
            print "ACTUAL RESULT 1:  %s" %details;
            #Get the result of execution
            print "[TEST EXECUTION RESULT] : SUCCESS";
	else:
            tdkTestObj.setResultStatus("FAILURE");
            print "TEST STEP 1: Get ping config values"
            print "EXPECTED RESULT 1: Should get the ping config";
            print "ACTUAL RESULT 1:  %s" %details;
            #Get the result of execution
            print "[TEST EXECUTION RESULT] : FAILURE";

    else:
        #Set the result status of execution
        tdkTestObj.setResultStatus("FAILURE");
        print "TEST STEP 1: Set ping config values"
        print "EXPECTED RESULT 1: Should set the ping config"
        print "ACTUAL RESULT 1:  %s" %details;
        #Get the result of execution
        print "[TEST EXECUTION RESULT] : FAILURE";

obj.unloadModule("tad");

					
