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
  <name>TS_PAM_DeviceUsers_SetAdminPassword</name>
  <primitive_test_id/>
  <primitive_test_name>pam_SetParameterValues</primitive_test_name>
  <primitive_test_version>2</primitive_test_version>
  <status>FREE</status>
  <synopsis>This test case will change the admin password</synopsis>
  <groups_id/>
  <execution_time>1</execution_time>
  <long_duration>false</long_duration>
  <remarks/>
  <skip>false</skip>
  <box_types>
    <box_type>RPI</box_type>
    <box_type>Emulator</box_type>
    <box_type>Broadband</box_type>
  </box_types>
  <rdk_versions>
    <rdk_version>RDKB</rdk_version>
  </rdk_versions>
  <test_cases>
    <test_case_id>TC_PAM_67</test_case_id>
    <test_objective>To change the admin password</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Emulator,XB3</test_setup>
    <pre_requisite>1.Ccsp Components in DUT should be in a running state that includes component under test Cable Modem
2.TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>None</api_or_interface_used>
    <input_parameters>Json Interface:
API Name
pam_SetParameterValues

Input:
ParamName - Device.Users.User.3.X_CISCO_COM_Password</input_parameters>
    <automation_approch>1.Function which needs to be tested will be configured in Test Manager GUI.
2.Python Script will be generated by Test Manager with provided arguments in configure page. 
3.TM will load the PAM library via Test agent
4.From python script, invoke pam_SetParameterValues() stub function to set the admin password.
5.pam stub function will call the ssp_setParameterValue() function of tdk component. 
6.Responses from the pam stub function will be logged in Agent Console log.
7.pam stub will validate the actual result with the expected result and send the result status to Test Manager.
8.Test Manager will publish the result in GUI as PASS/FAILURE based on the response from pam stub.</automation_approch>
    <except_output>CheckPoint 1:
 Password changing verification log should be logged in the Agent console/Component log

CheckPoint 2:
Stub function result should be success and should see corresponding log in the agent console log

CheckPoint 3:
TestManager GUI will publish the result as PASS in Execution/Console page of Test Manager</except_output>
    <priority>High</priority>
    <test_stub_interface>None</test_stub_interface>
    <test_script>TS_PAM_DeviceUsers_SetAdminPassword</test_script>
    <skipped>No</skipped>
    <release_version/>
    <remarks/>
  </test_cases>
</xml>

'''
#import statement
import tdklib; 

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("pam","RDKB");

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_PAM_DeviceUsers_SetAdminPassword');

#Get the result of connection with test component and STB
loadmodulestatus =obj.getLoadModuleResult();
print "[LIB LOAD STATUS]  :  %s" %loadmodulestatus ;

if "SUCCESS" in loadmodulestatus.upper():
    #Set the result status of execution
    obj.setLoadModuleStatus("SUCCESS");
    tdkTestObj = obj.createTestStep('pam_GetParameterValues');
    tdkTestObj.addParameter("ParamName","Device.Users.User.3.X_CISCO_COM_Password");
    expectedresult="SUCCESS";

    #Execute the test case in STB
    tdkTestObj.executeTestCase(expectedresult);
    actualresult = tdkTestObj.getResult();
    details = tdkTestObj.getResultDetails();
    org_value = details;
		
    if expectedresult in actualresult:
        #Set the result status of execution
        tdkTestObj.setResultStatus("SUCCESS");
        #Get the result of execution
	print "STEP 1: Get the admin password";
        print "EXPECTED RESULT : Should get the admin password";
        print "ACTUAL RESULT: Successfully get the password, %s" %details;
        print "[TEST EXECUTION RESULT] :%s" %actualresult;
        test_password = "TestPassword"
        expectedresult="FAILURE";
	tdkTestObj = obj.createTestStep('pam_SetParameterValues');
        tdkTestObj.addParameter("ParamName","Device.Users.User.3.Password");	
	tdkTestObj.addParameter("Type","string");
	tdkTestObj.addParameter("ParamValue",test_password);

        tdkTestObj.executeTestCase(expectedresult);
        actualresult = tdkTestObj.getResult();
        details = tdkTestObj.getResultDetails();

	if expectedresult in actualresult:
	    tdkTestObj.setResultStatus("SUCCESS");
	    print "STEP 2: Set the admin password";
	    print "EXPECTED RESULT : Should not change the admin password";
	    print "ACTUAL RESULT: Admin password is not changed, %s" %details;
	    print "[TEST EXECUTION RESULT] :%s" %actualresult;
	    tdkTestObj = obj.createTestStep('pam_GetParameterValues');
            tdkTestObj.addParameter("ParamName","Device.Users.User.3.X_CISCO_COM_Password");
            expectedresult="SUCCESS";

            #Execute the test case in STB
            tdkTestObj.executeTestCase(expectedresult);
            actualresult = tdkTestObj.getResult();
            details = tdkTestObj.getResultDetails();
                        
            if expectedresult in actualresult and test_password in details:
                #Set the result status of execution
                tdkTestObj.setResultStatus("SUCCESS");
                #Get the result of execution
		print "STEP 3: Get the admin password";
	        print "EXPECTED RESULT : Should get the admin password";
        	print "ACTUAL RESULT: Successfully get the password, %s" %details;
	        print "[TEST EXECUTION RESULT] :%s" %actualresult;

                tdkTestObj = obj.createTestStep('pam_SetParameterValues');
                tdkTestObj.addParameter("ParamName","Device.Users.User.3.Password");
                tdkTestObj.addParameter("Type","string");
                tdkTestObj.addParameter("ParamValue",org_value);
                expectedresult="FAILURE";
                tdkTestObj.executeTestCase(expectedresult);
                actualresult = tdkTestObj.getResult();
                details = tdkTestObj.getResultDetails();

                if expectedresult in actualresult:
                    tdkTestObj.setResultStatus("SUCCESS");
		    print "STEP 4: Set the admin password";
	            print "EXPECTED RESULT : Should not change the admin password";
        	    print "ACTUAL RESULT: Admin password is not changed, %s" %details;
	            print "[TEST EXECUTION RESULT] :%s" %actualresult;
                else:
                    tdkTestObj.setResultStatus("FAILURE");
		    print "STEP 4: Set the admin password";
                    print "EXPECTED RESULT : Should not change the admin password";
                    print "ACTUAL RESULT: Admin password is changed, %s" %details;
                    print "[TEST EXECUTION RESULT] :%s" %actualresult;
            else:
                tdkTestObj.setResultStatus("FAILURE");
		print "STEP 3: Get the admin password";
                print "EXPECTED RESULT : Should get the admin password";
                print "ACTUAL RESULT: Failed to get the password, %s" %details;
                print "[TEST EXECUTION RESULT] :%s" %actualresult;
	else:
	    tdkTestObj.setResultStatus("FAILURE");
	    print "STEP 2: Set the admin password";
            print "EXPECTED RESULT : Should not change the admin password";
            print "ACTUAL RESULT: Admin password is changed, %s" %details;
            print "[TEST EXECUTION RESULT] :%s" %actualresult;
    else:
        tdkTestObj.setResultStatus("FAILURE");
	print "STEP 1: Get the admin password";
        print "EXPECTED RESULT : Should get the admin password";
        print "ACTUAL RESULT: Failed to get the password, %s" %details;
        print "[TEST EXECUTION RESULT] :%s" %actualresult;	
    obj.unloadModule("pam");
   		 
else:   
        print "Failed to load pam module";
        obj.setLoadModuleStatus("FAILURE");
        print "Module loading failed";				

					

					

					
