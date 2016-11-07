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
  <version>1</version>
  <!-- Do not edit version. This will be auto incremented while updating. If you are adding a new script you can keep the vresion as 1 -->
  <name>TS_PAM_DeviceUsers_SetAdminPassword</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id> </primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>pam_SetParameterValues</primitive_test_name>
  <!--  -->
  <primitive_test_version>2</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>This test case will change the admin password</synopsis>
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

					

					

					
