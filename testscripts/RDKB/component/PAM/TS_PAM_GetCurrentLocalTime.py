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
  <name>TS_PAM_GetCurrentLocalTime</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id> </primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>pam_GetParameterValues</primitive_test_name>
  <!--  -->
  <primitive_test_version>1</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>This testcase checks if local time is getting updated properly</synopsis>
  <!--  -->
  <groups_id />
  <!--  -->
  <execution_time>1</execution_time>
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
#import statement
import tdklib; 
from time import sleep;

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("pam","RDKB");

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_PAM_GetCurrentLocalTime');

#Get the result of connection with test component and STB
loadmodulestatus =obj.getLoadModuleResult();
print "[LIB LOAD STATUS]  :  %s" %loadmodulestatus ;

if "SUCCESS" in loadmodulestatus.upper():
    #Set the result status of execution
    obj.setLoadModuleStatus("SUCCESS");
    tdkTestObj = obj.createTestStep('pam_GetParameterValues');
    tdkTestObj.addParameter("ParamName","Device.Time.CurrentLocalTime");
    expectedresult="SUCCESS";

    #Execute the test case in STB
    tdkTestObj.executeTestCase(expectedresult);
    actualresult = tdkTestObj.getResult();
    TimeBeforeSleep = tdkTestObj.getResultDetails();
		
    if expectedresult in actualresult:
        #Set the result status of execution
        tdkTestObj.setResultStatus("SUCCESS");
        print "TEST STEP 1: Get the current local time";
        print "EXPECTED RESULT 1: Should get the current local time";
        print "ACTUAL RESULT 1: The current local time is :%s" %TimeBeforeSleep;
        #Get the result of execution
        print "[TEST EXECUTION RESULT] : SUCCESS" 

	#sleeping for 10 seconds
	print "sleeping for 10 seconds";
	sleep (10);
	tdkTestObj = obj.createTestStep('pam_GetParameterValues');
	tdkTestObj.addParameter("ParamName","Device.Time.CurrentLocalTime");
	#Execute the test case in STB
	tdkTestObj.executeTestCase(expectedresult);
	actualresult = tdkTestObj.getResult();
	TimeAfterSleep = tdkTestObj.getResultDetails();
	if expectedresult in actualresult:
	    if TimeBeforeSleep != TimeAfterSleep:
  	        #Set the result status of execution
	        tdkTestObj.setResultStatus("SUCCESS");
       	        print "TEST STEP 2: Compare the current local time before and after sleep";
	        print "EXPECTED RESULT 2: The current local time before and after sleep should not be equal";
	        print "ACTUAL RESULT 2: The current local time after sleep is :%s" %TimeAfterSleep;
		print "The local time is updated succesfully";
	        #Get the result of execution
	        print "[TEST EXECUTION RESULT] : SUCCESS"
	    else:
		#Set the result status of execution
		tdkTestObj.setResultStatus("FAILURE");
		print "TEST STEP 2: Compare the current local time before and after sleep";
		print "EXPECTED RESULT 2: The current local time before and after sleep should not be equal";
		print "ACTUAL RESULT 2: The current local time after sleep is :%s" %TimeAfterSleep;
		print "Failed to update the current local time";
		#Get the result of execution
		print "[TEST EXECUTION RESULT] : FAILURE"
	else:
	    tdkTestObj.setResultStatus("FAILURE");
	    print "TEST STEP 1: Get the current local time after sleep";
	    print "EXPECTED RESULT 1: Should get the current local time after sleep";
	    print "ACTUAL RESULT 1: Failure in getting the current local time after sleep. Details : %s" %TimeAfterSleep;
	    print "[TEST EXECUTION RESULT] : FAILURE";
	
    else:
        tdkTestObj.setResultStatus("FAILURE");	
        print "TEST STEP 1: Get the current local time";
        print "EXPECTED RESULT 1: Should get the current local time";
        print "ACTUAL RESULT 1: Failure in getting the current local time. Details : %s" %TimeBeforeSleep;
        print "[TEST EXECUTION RESULT] : FAILURE";
    obj.unloadModule("pam");
   		 
else:   
        print "Failed to load pam module";
        obj.setLoadModuleStatus("FAILURE");
        print "Module loading failed";				
