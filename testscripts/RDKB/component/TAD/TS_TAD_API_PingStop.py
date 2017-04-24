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
  <version>1</version>
  <name>TS_TAD_API_PingStop</name>
  <primitive_test_id/>
  <primitive_test_name>TADstub_Stop</primitive_test_name>
  <primitive_test_version>1</primitive_test_version>
  <status>FREE</status>
  <synopsis>Script for checking the functionality of ping_stop api</synopsis>
  <groups_id/>
  <execution_time>1</execution_time>
  <long_duration>false</long_duration>
  <advanced_script>false</advanced_script>
  <remarks/>
  <skip>false</skip>
  <box_types>
    <box_type>Broadband</box_type>
  </box_types>
  <rdk_versions>
    <rdk_version>RDKB</rdk_version>
  </rdk_versions>
  <test_cases>
    <test_case_id>TC_TAD_35</test_case_id>
    <test_objective>To verify the functionality of diag_stop() api</test_objective>
    <test_type>Positive</test_type>
    <test_setup>xb3, emulator</test_setup>
    <pre_requisite>1.Ccsp Components  should be in a running state else invoke cosa_start.sh manually that includes all the ccsp components.
2.TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>diag_stop</api_or_interface_used>
    <input_parameters>mode</input_parameters>
    <automation_approch>1. Load  TAD modules
2. From script invoke TADstub_SetCfg() with mode as ping and a host name
3. Invoke TADstub_Start() to start the ping operation
4. Invoke TADstub_Stop() to stop the ping operation
4. check whether set , start and stop returned success
5. Validation of  the result is done within the python script and send the result status to Test Manager.
6.Test Manager will publish the result in GUI as PASS/FAILURE based on the response from TAD stub.</automation_approch>
    <except_output>Check for return values of diag_start(), diag_stop() and diag_setcfg()</except_output>
    <priority>High</priority>
    <test_stub_interface>TAD</test_stub_interface>
    <test_script>TS_TAD_API_PingStop</test_script>
    <skipped>No</skipped>
    <release_version/>
    <remarks/>
  </test_cases>
</xml>

'''
# use tdklib library,which provides a wrapper for tdk testcase script 
import tdklib; 
from time import sleep;

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("tad","1");

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_TAD_API_PingStop');

#Get the result of connection with test component and STB
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
    expectedresult="SUCCESS";
    #setting mode 1 for ping
    tdkTestObj.addParameter("mode",0);
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

        #invoke ping start
        tdkTestObj = obj.createTestStep('TADstub_Start');
        #setting mode 1 for ping
        tdkTestObj.addParameter("mode",0);
        expectedresult="SUCCESS";
        #Execute the test case in STB
        tdkTestObj.executeTestCase(expectedresult);
        actualresult = tdkTestObj.getResult();
        details = tdkTestObj.getResultDetails();
        if expectedresult in actualresult:
            #Set the result status of execution
            tdkTestObj.setResultStatus("SUCCESS");
            print "TEST STEP 1: Start the IP ping";
            print "EXPECTED RESULT 1: Should Start the IP ping";
            print "ACTUAL RESULT 1:  %s" %details;
            #Get the result of execution
            print "[TEST EXECUTION RESULT] : SUCCESS";
	    sleep(20);

            ##Staring ping_stop sequence
     	    tdkTestObj = obj.createTestStep('TADstub_Stop');
	    tdkTestObj.addParameter("mode",0);
            tdkTestObj.executeTestCase(expectedresult);
            actualresult = tdkTestObj.getResult();
            details = tdkTestObj.getResultDetails();
            if expectedresult in actualresult:
                #Set the result status of execution
                tdkTestObj.setResultStatus("SUCCESS");
                print "TEST STEP 1: Stop the IP ping";
                print "EXPECTED RESULT 1: Should Stop the IP ping";
                print "ACTUAL RESULT 1:  %s" %details;
                #Get the result of execution
                print "[TEST EXECUTION RESULT] : SUCCESS";
            else:
                #Set the result status of execution
                tdkTestObj.setResultStatus("FAILURE");
                print "TEST STEP 1: Stop the IP ping";
                print "EXPECTED RESULT 1: Should Stop the IP ping";
                print "ACTUAL RESULT 1:  %s" %details;
                #Get the result of execution
                print "[TEST EXECUTION RESULT] : FAILURE";
        else:
            #Set the result status of execution
            tdkTestObj.setResultStatus("FAILURE");
            print "TEST STEP 1: Start the IP ping";
            print "EXPECTED RESULT 1: Should Start the IP ping";
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

else:
        print "Failed to load tad module";
        obj.setLoadModuleStatus("FAILURE");
        print "Module loading failed";
