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
<?xml version="1.0" encoding="UTF-8"?><xml>
  <id/>
  <version>1</version>
  <name>TS_platform_stub_hal_SetFanSpeed</name>
  <primitive_test_id/>
  <primitive_test_name>platform_stub_hal_SetFanSpeed</primitive_test_name>
  <primitive_test_version>2</primitive_test_version>
  <status>FREE</status>
  <synopsis>To set the Fan Speed using platform_hal_SetFanSpeed() api and validate</synopsis>
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
    <test_case_id>TC_HAL_Platform_32</test_case_id>
    <test_objective>To set the Fan Speed using platform_hal_SetFanSpeed() api and validate</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Broadband</test_setup>
    <pre_requisite>1.Ccsp Components  should be in a running state of DUT
2.TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>platform_hal_SetFanSpeed()</api_or_interface_used>
    <input_parameters>None</input_parameters>
    <automation_approch>1. Load  platform module.
2. From script invoke platform_hal_GetFanSpeed() and save the value
3. Set the fan speed to another value and validate
4. Validation of  the result is done within the python script and send the result status to Test Manager.
5. Test Manager will publish the result in GUI as PASS/FAILURE based on the response from HAL_Platform stub.</automation_approch>
    <except_output>Should be able to set the fan speed</except_output>
    <priority>High</priority>
    <test_stub_interface>HAL_Platform</test_stub_interface>
    <test_script>TS_platform_stub_hal_SetFanSpeed</test_script>
    <skipped>No</skipped>
    <release_version>M61</release_version>
    <remarks>None</remarks>
  </test_cases>
</xml>

'''
# use tdklib library,which provides a wrapper for tdk testcase script 
import tdklib; 

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("halplatform","1");

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_platform_stub_hal_SetFanSpeed');

#Get the result of connection with test component and STB
loadmodulestatus =obj.getLoadModuleResult();
print "[LIB LOAD STATUS]  :  %s" %loadmodulestatus;

if "SUCCESS" in loadmodulestatus.upper():
        obj.setLoadModuleStatus("SUCCESS");
        #Script to load the configuration file of the component
        tdkTestObj = obj.createTestStep("platform_stub_hal_GetFanSpeed");
        expectedresult="SUCCESS";
        tdkTestObj.executeTestCase(expectedresult);
        actualresult = tdkTestObj.getResult();
        actualValue = tdkTestObj.getResultDetails();
        if expectedresult in actualresult and int (actualValue) > 0:
            tdkTestObj.setResultStatus("SUCCESS");
            print "TEST STEP 1: Get value from Platform_GetFanSpeed";
            print "EXPECTED RESULT 1: Should get the value from Platform_GetFanSpeed successfully";
            print "ACTUAL RESULT 1: %s" %actualValue;
            print "[TEST EXECUTION RESULT] : %s" %actualresult;

	    testFanSpeed = int(actualValue) + 100;
	    print "testFanSpeed", testFanSpeed
            #Verify SET operation
            tdkTestObj = obj.createTestStep("platform_stub_hal_SetFanSpeed");
            tdkTestObj.addParameter("index",testFanSpeed);
            expectedresult="SUCCESS";
            tdkTestObj.executeTestCase(expectedresult);
            actualresult = tdkTestObj.getResult();
            details = tdkTestObj.getResultDetails();
            if expectedresult in actualresult:
                tdkTestObj.setResultStatus("SUCCESS");
                print "TEST STEP 2: Set value using Platform_SetFanSpeed";
                print "EXPECTED RESULT 2: Should set the value from Platform_SetFanSpeed successfully";
                print "ACTUAL RESULT 2: %s" %details;
                print "[TEST EXECUTION RESULT] : %s" %actualresult;

                #get value after SET operation to cross verify
                tdkTestObj = obj.createTestStep("platform_stub_hal_GetFanSpeed");
                expectedresult="SUCCESS";
                tdkTestObj.executeTestCase(expectedresult);
                actualresult = tdkTestObj.getResult();
                valueAfterSet = tdkTestObj.getResultDetails();
                if expectedresult in actualresult and int (valueAfterSet) > 0:
                    tdkTestObj.setResultStatus("SUCCESS");
                    print "TEST STEP 3: Get value from Platform_GetFanSpeed";
                    print "EXPECTED RESULT 3: Should get the value from Platform_GetFanSpeed successfully";
                    print "ACTUAL RESULT 3: value = %s" %valueAfterSet;
                    print "[TEST EXECUTION RESULT] : %s" %actualresult;

                    if int (valueAfterSet) == testFanSpeed:
			tdkTestObj.setResultStatus("SUCCESS");
                        print "TEST STEP 4: Cross verifing the value";
                        print "EXPECTED RESULT 4: Value should match";
                        print "ACTUAL RESULT 4: Value is set successfully";
                        print "[TEST EXECUTION RESULT] : %s" %actualresult;
		    else:
			tdkTestObj.setResultStatus("FAILURE");
                        print "TEST STEP 4: Cross verifing the value";
                        print "EXPECTED RESULT 4: Value should match";
                        print "ACTUAL RESULT 4: Value is set successfully";
                        print "[TEST EXECUTION RESULT] : FAILURE";
		else:
		    tdkTestObj.setResultStatus("FAILURE");
                    print "TEST STEP 3: Get value from Platform_GetFanSpeed";
                    print "EXPECTED RESULT 3: Should get the value from Platform_GetFanSpeed successfully";
                    print "ACTUAL RESULT 3: value = %s" %valueAfterSet;
                    print "[TEST EXECUTION RESULT] : FAILURE"
		#Reverting the values
		tdkTestObj = obj.createTestStep("platform_stub_hal_SetFanSpeed");
                tdkTestObj.addParameter("index", int(actualValue));
                expectedresult="SUCCESS";
                tdkTestObj.executeTestCase(expectedresult);
                actualresult = tdkTestObj.getResult();
                details = tdkTestObj.getResultDetails();
                if expectedresult in actualresult:
                    tdkTestObj.setResultStatus("SUCCESS");
                    print "TEST STEP 5: Set value from Platform_SetFanSpeed";
                    print "EXPECTED RESULT 5: Should set the value from Platform_SetFanSpeed successfully";
                    print "ACTUAL RESULT 5: %s" %details;
                    print "[TEST EXECUTION RESULT] : %s" %actualresult;
                else:
                    tdkTestObj.setResultStatus("FAILURE");
                    print "TEST STEP 5: Set value from Platform_SetFanSpeed";
                    print "EXPECTED RESULT 5: Should set the value from Platform_SetFanSpeed successfully";
                    print "ACTUAL RESULT 5: %s" %details;
                    print "[TEST EXECUTION RESULT] : %s" %actualresult;
	    else:
		tdkTestObj.setResultStatus("FAILURE");
                print "TEST STEP 2: Set value using Platform_SetFanSpeed";
                print "EXPECTED RESULT 2: Should set the value from Platform_SetFanSpeed successfully";
                print "ACTUAL RESULT 2: %s" %details;
                print "[TEST EXECUTION RESULT] : FAILURE";
	else:
	    tdkTestObj.setResultStatus("FAILURE");
            print "TEST STEP 1: Get value from Platform_GetFanSpeed";
            print "EXPECTED RESULT 1: Should get the value from Platform_GetFanSpeed successfully";
            print "ACTUAL RESULT 1: %s" %actualValue;
            print "[TEST EXECUTION RESULT] : FAILURE";
        obj.unloadModule("halplatform");
else:
        print "Failed to load the module";
        obj.setLoadModuleStatus("FAILURE");
        print "Module loading failed";
