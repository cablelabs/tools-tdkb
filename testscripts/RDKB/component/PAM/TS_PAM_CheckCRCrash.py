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
  <version>2</version>
  <!-- Do not edit version. This will be auto incremented while updating. If you are adding a new script you can keep the vresion as 1 -->
  <name>TS_PAM_CheckCRCrash</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id> </primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>pam_GetParameterValues</primitive_test_name>
  <!--  -->
  <primitive_test_version>1</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>This test case is to kill the CR process and check if the CR process is restarted</synopsis>
  <!--  -->
  <groups_id />
  <!--  -->
  <execution_time>30</execution_time>
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
  </box_types>
  <rdk_versions>
    <rdk_version>RDKB</rdk_version>
    <!--  -->
  </rdk_versions>
  <test_cases>
    <test_case_id>TC_PAM_41</test_case_id>
    <test_objective>To kill the CR and check if the box reboots.</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Emulator,XB3</test_setup>
    <pre_requisite>1.Ccsp Components  should be in a running state else invoke cosa_start.sh manually that includes all the ccsp components.
2.TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>None</api_or_interface_used>
    <input_parameters>Json Interface:
API Name
pam_CRRestart</input_parameters>
    <automation_approch>1.Function which needs to be tested will be configured in Test Manager GUI.
2.Python Script will be generated by Test Manager with provided arguments in configure page.
3.TM will load the PAM library via Test agent
4.From python script, invoke pam_CRRestart() stub function to Kill the CR and check if the box boots.
5.pam stub function will call the ssp_CRRestart() function of tdk component.
6.Responses from the pam stub function will be logged in Agent Console log.
7.pam stub will validate the actual result with the expected result and send the result status to Test Manager.
8.Test Manager will publish the result in GUI as PASS/FAILURE based on the response from pam stub.</automation_approch>
    <except_output>CheckPoint 1:
CR should be killed and the box should be restarted successfully, the status of it should be logged in the Agent console/Component log

CheckPoint 2:
Stub function result should be success and should see corresponding log in the agent console log

CheckPoint 3:
TestManager GUI will publish the result as PASS in Execution/Console page of Test Manager</except_output>
    <priority>High</priority>
    <test_stub_interface>None</test_stub_interface>
    <test_script>TS_PAM_CheckCRCrash</test_script>
    <skipped>No</skipped>
    <release_version></release_version>
    <remarks></remarks>
  </test_cases>
  <script_tags />
</xml>
'''
						#import statements
import tdklib;
import time;
from time import sleep;

#Test component to be tested
pamObj = tdklib.TDKScriptingLibrary("pam","RDKB");
obj = tdklib.TDKScriptingLibrary("sysutil","RDKB");

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_PAM_CheckCRCrash');
pamObj.configureTestCase(ip,port,'TS_PAM_CheckCRCrash');

#Get the result of connection with test component and STB
loadmodulestatus =obj.getLoadModuleResult();
pamloadmodulestatus =pamObj.getLoadModuleResult();
print "[LIB LOAD STATUS]  :  %s" %loadmodulestatus ;

if "SUCCESS" in loadmodulestatus.upper() and "SUCCESS" in pamloadmodulestatus.upper():
        obj.setLoadModuleStatus("SUCCESS");
        #To check whether CR process is running or not
        tdkTestObj = obj.createTestStep("ExecuteCmd");
        cmnd = "pidof CcspCrSsp"
        tdkTestObj.addParameter("command", cmnd);
        expectedresult="SUCCESS";
        tdkTestObj.executeTestCase(expectedresult);
        #Get the result of execution
        actualresult = tdkTestObj.getResult();
        details = tdkTestObj.getResultDetails();
        if details:
            tdkTestObj.setResultStatus("SUCCESS");
            print "TEST STEP 1:Check whether CR process is running or not"
            print "EXPECTED RESULT 1:CR process should be running"
            print "ACTUAL RESULT 1: Process is running. PID is %s" %details;
            print "[TEST EXECUTION RESULT]: %s" %actualresult;

            #Going to kill CR process
            tdkTestObj = obj.createTestStep("ExecuteCmd");
            print "Killing CR process"
            cmnd ="kill -9 `pidof CcspCrSsp`"
            tdkTestObj.addParameter("command", cmnd);
            expectedresult="SUCCESS";
            tdkTestObj.executeTestCase(expectedresult);
            #Get the result of execution
            actualresult = tdkTestObj.getResult();
            details = tdkTestObj.getResultDetails();
            if expectedresult in actualresult:
                tdkTestObj.setResultStatus("SUCCESS");
                print "TEST STEP 2: Kill the CR process"
                print "EXPECTED RESULT 2: Should kill the CR process"
                print "ACTUAL RESULT 2: CR process is killed"
                print "[TEST EXECUTION RESULT]: %s" %actualresult;
                #Sleeping for 15 minutes
                sleep(900)
                #checking process after sleep
                tdkTestObj = obj.createTestStep("ExecuteCmd");
                cmnd = "pidof CcspCrSsp"
                tdkTestObj.addParameter("command", cmnd);
                expectedresult="SUCCESS";
                tdkTestObj.executeTestCase(expectedresult);
                #Get the result of execution
                actualresult = tdkTestObj.getResult();
                details = tdkTestObj.getResultDetails();
                if details:
                    tdkTestObj.setResultStatus("SUCCESS");
                    print "TEST STEP 3:Check whether CR process is running or not after killing the process and waiting"
                    print "EXPECTED RESULT 3:CR process should be running"
                    print "ACTUAL RESULT 3: Process is running after killing and waiting .PID is %s" %details;
                    print "[TEST EXECUTION RESULT]: %s" %actualresult;
                else:
                    tdkTestObj.setResultStatus("FAILURE");
                    print "TEST STEP 3:Check whether CR process is running or not after killing the process and waiting"
                    print "EXPECTED RESULT 3:CR process should be running"
                    print "ACTUAL RESULT 3: Process is not running after killing and waiting"
                    print "[TEST EXECUTION RESULT]: FAILURE"
                    obj.initiateReboot();
		    pamObj.resetConnectionAfterReboot();
            else:
                tdkTestObj.setResultStatus("FAILURE");
                print "TEST STEP 2: Kill the CR process"
                print "EXPECTED RESULT 2: Should kill the CR process"
                print "ACTUAL RESULT 2: CR process is not killed"
                print "[TEST EXECUTION RESULT]: %s" %actualresult
        else:
            tdkTestObj.setResultStatus("FAILURE");
            print "TEST STEP 1:Check whether CR process is running or not"
            print "EXPECTED RESULT 1:CR process should be running"
            print "ACTUAL RESULT 1: CR process is not running"
            print "[TEST EXECUTION RESULT]: FAILURE"
            obj.initiateReboot();
	    pamObj.resetConnectionAfterReboot();
        obj.unloadModule("sysutil");
	pamObj.unloadModule("pam");


else:
        print "Failed to load the module";
        obj.setLoadModuleStatus("FAILURE");
        pamObj.setLoadModuleStatus("FAILURE");
        print "Module loading failed";

					
