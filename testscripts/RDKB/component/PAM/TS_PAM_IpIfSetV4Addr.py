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
  <name>TS_PAM_IpIfSetV4Addr</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id> </primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>pam_GetParameterValues</primitive_test_name>
  <!--  -->
  <primitive_test_version>1</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>This test will set IPV4 address</synopsis>
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

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("pam","RDKB");

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_PAM_IpIfSetV4Addr');

#Get the result of connection with test component and STB
loadmodulestatus =obj.getLoadModuleResult();
print "[LIB LOAD STATUS]  :  %s" %loadmodulestatus ;

if "SUCCESS" in loadmodulestatus.upper():
    #Set the result status of execution
    obj.setLoadModuleStatus("SUCCESS");
    tdkTestObj = obj.createTestStep('pam_GetParameterValues');
    tdkTestObj.addParameter("ParamName","Device.IP.Interface.1.IPv4Address.1.Enable");
    expectedresult="SUCCESS";

    #Execute the test case in STB
    tdkTestObj.executeTestCase(expectedresult);
    actualresult = tdkTestObj.getResult();
    details = tdkTestObj.getResultDetails();
		
    if expectedresult in actualresult:
        #Set the result status of execution
        tdkTestObj.setResultStatus("SUCCESS");
        #Get the result of execution
	print "STEP 1:Get the IPV4 address";
	print "EXPECTED RESULT: Should get the IPV4 address";
	print "ACTUAL RESULT: Successfully got the IPV4 address, %s" %details;
        print "[TEST EXECUTION RESULT] : %s" %actualresult;
	tdkTestObj = obj.createTestStep('pam_SetParameterValues');
        tdkTestObj.addParameter("ParamName","Device.IP.Interface.1.IPv4Address.1.Enable");	
	tdkTestObj.addParameter("Type","boolean");
	if "true" in details:
	    tdkTestObj.addParameter("ParamValue","false");
	    org_value = "true"
	else:
            tdkTestObj.addParameter("ParamValue","true");
            org_value = "false"
        tdkTestObj.executeTestCase(expectedresult);
        actualresult = tdkTestObj.getResult();
        details = tdkTestObj.getResultDetails();

	if expectedresult in actualresult:
	    tdkTestObj.setResultStatus("SUCCESS");
	    print "STEP 2: Set the IPV4 address";
	    print "EXPECTED RESULT: Should set the IPV4 address";
	    print "ACTUAL RESULT: Successfully set the IPV4 address, %s" %details;
	    print "[TEST EXECUTION RESULT] :%s" %actualresult;

            tdkTestObj = obj.createTestStep('pam_SetParameterValues');
            tdkTestObj.addParameter("ParamName","Device.IP.Interface.1.IPv4Address.1.Enable");
            tdkTestObj.addParameter("Type","boolean");
    	    tdkTestObj.addParameter("ParamValue",org_value);
            tdkTestObj.executeTestCase(expectedresult);
            actualresult = tdkTestObj.getResult();
            details = tdkTestObj.getResultDetails();

	    if expectedresult in actualresult:
                tdkTestObj.setResultStatus("SUCCESS");
		print "STEP 3: Set the IPV4 address to default value";
		print "EXPECTED RESULT: Should set the IPV4 address to default value";
		print "ACTUAL RESULT: Successfully set the IPV4 address to default value, %s" %details;
                print "[TEST EXECUTION RESULT] :%s" %actualresult;
	    else:
                tdkTestObj.setResultStatus("FAILURE");
		print "STEP 3: Set the IPV4 address to default value";
                print "EXPECTED RESULT: Should set the IPV4 address to default value";
                print "ACTUAL RESULT: Failed to set the IPV4 address to default value, %s" %details;
                print "[TEST EXECUTION RESULT] :%s" %actualresult;
	else:
	    tdkTestObj.setResultStatus("FAILURE");
	    print "STEP 2: Set the IPV4 address";
            print "EXPECTED RESULT: Should set the IPV4 address";
            print "ACTUAL RESULT: Failed to set the IPV4 address, %s" %details;
            print "[TEST EXECUTION RESULT] :%s" %actualresult;
    else:
        tdkTestObj.setResultStatus("FAILURE");
	print "STEP 1:Get the IPV4 address";
        print "EXPECTED RESULT: Should get the IPV4 address";
        print "ACTUAL RESULT: Failed to get the IPV4 address, %s" %details;
        print "[TEST EXECUTION RESULT] : %s" %actualresult;	
    obj.unloadModule("pam");
   		 
else:   
        print "Failed to load pam module";
        obj.setLoadModuleStatus("FAILURE");
        print "Module loading failed";				
