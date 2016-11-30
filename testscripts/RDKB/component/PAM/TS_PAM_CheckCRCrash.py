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
  <name>TS_PAM_CheckCRCrash</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id></primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>ExecuteCmd</primitive_test_name>
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
  <script_tags />
</xml>
'''
#import statements
import tdklib;
import time;
from time import sleep;

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("sysutil","RDKB");

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_PAM_CheckCRCrash');

#Get the result of connection with test component and STB
loadmodulestatus =obj.getLoadModuleResult();
print "[LIB LOAD STATUS]  :  %s" %loadmodulestatus ;

if "SUCCESS" in loadmodulestatus.upper():
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
	obj.unloadModule("sysutil");
			
else:
        print "Failed to load the module";
        obj.setLoadModuleStatus("FAILURE");
        print "Module loading failed";
