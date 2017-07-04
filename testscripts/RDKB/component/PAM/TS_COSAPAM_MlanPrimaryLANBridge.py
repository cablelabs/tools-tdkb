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
  <version>5</version>
  <name>TS_COSAPAM_MlanPrimaryLANBridge</name>
  <primitive_test_id/>
  <primitive_test_name>pam_GetParameterValues</primitive_test_name>
  <primitive_test_version>1</primitive_test_version>
  <status>FREE</status>
  <synopsis>This test will get the PrimaryLANBridge of the CPE</synopsis>
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
    <test_case_id>TC_PAM_108</test_case_id>
    <test_objective>To get the PrimaryLANBridge</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Emulator,XB3</test_setup>
    <pre_requisite>1.Ccsp Components in DUT should be in a running state that includes component under test Cable Modem
2.TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>None</api_or_interface_used>
    <input_parameters>Json Interface:
API Name
pam_GetParameterValues

Input:
ParamName - Device.DeviceInfo.PrimaryLANBridge</input_parameters>
    <automation_approch>1.Function which needs to be tested will be configured in Test Manager GUI.
2.Python Script will be generated by Test Manager with provided arguments in configure page. 
3.TM will load the PAM library via Test agent
4.From python script, invoke pam_GetParameterValues() stub function to get the PrimaryLANBridge. 
5.pam stub function will call the ssp_getParameterValue() function of tdk component.
6.Responses from the pam stub function will be logged in Agent Console log.
7.pam stub will validate the actual result with the expected result and send the result status to Test Manager.
8.Test Manager will publish the result in GUI as PASS/FAILURE based on the response from pam stub.</automation_approch>
    <except_output>CheckPoint 1:
 The PrimaryLANBridge should be logged in the Agent console/Component log

CheckPoint 2:
Stub function result should be success and should see corresponding log in the agent console log

CheckPoint 3:
TestManager GUI will publish the result as PASS in Execution/Console page of Test Manager</except_output>
    <priority>High</priority>
    <test_stub_interface>None</test_stub_interface>
    <test_script>TS_COSAPAM_MlanPrimaryLANBridge</test_script>
    <skipped>No</skipped>
    <release_version/>
    <remarks/>
  </test_cases>
  <script_tags/>
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
obj.configureTestCase(ip,port,'TS_COSAPAM_MlanPrimaryLANBridge');

#Get the result of connection with test component and STB
loadmodulestatus =obj.getLoadModuleResult();
print "[LIB LOAD STATUS]  :  %s" %loadmodulestatus ;

if "SUCCESS" in loadmodulestatus.upper():
    #Set the result status of execution
    obj.setLoadModuleStatus("SUCCESS");
    tdkTestObj = obj.createTestStep('pam_GetParameterValues');
#    tdkTestObj.addParameter("ParamName","Device.IP.Interface.4.");
    tdkTestObj.addParameter("ParamName","Device.X_CISCO_COM_MultiLAN.PrimaryLANBridge");
    expectedresult="SUCCESS";

    #Execute the test case in STB
    tdkTestObj.executeTestCase(expectedresult);
    actualresult = tdkTestObj.getResult();
    details = tdkTestObj.getResultDetails();
		
    if expectedresult in actualresult:

        #Set the result status of execution
        tdkTestObj.setResultStatus("SUCCESS");
        print "TEST STEP 1: Get the PrimaryLANBridge object";
        print "EXPECTED RESULT 1: Should get the PrimaryLANBridge object";
        print "ACTUAL RESULT 1: PrimaryLANBridge object is %s" %details;
        #Get the result of execution
        print "[TEST EXECUTION RESULT] : SUCCESS, %s" %details;

#	param = details.split(':')[2].split(' ')[0];
#        print param
#	param = param.split(' ').[0];
	param = details+'.'; 
#	print param
#	tdkTestObj.addParameter("ParamName","Device.Bridging.Bridge.2");
	#tdkTestObj = obj.createTestStep('pam_GetParameterValues');
	tdkTestObj.addParameter("ParamName", param);
	tdkTestObj.executeTestCase(expectedresult);
        actualresult = tdkTestObj.getResult();
        details = tdkTestObj.getResultDetails();

        if expectedresult in actualresult:

            #Set the result status of execution
            tdkTestObj.setResultStatus("SUCCESS");
            print "TEST STEP 1: Get the PrimaryLANBridge";
            print "EXPECTED RESULT 1: Should get the PrimaryLANBridge";
            print "ACTUAL RESULT 1: PrimaryLANBridge is %s" %details;
            #Get the result of execution
            print "[TEST EXECUTION RESULT] : SUCCESS, %s" %details;
        else:
            tdkTestObj.setResultStatus("FAILURE");
            print "TEST STEP 1: Get the PrimaryLANBridge";
            print "EXPECTED RESULT 1: Should get the PrimaryLANBridge";
            print "ACTUAL RESULT 1: Failure in getting the PrimaryLANBridge. Details : %s" %details;
            print "[TEST EXECUTION RESULT] : FAILURE";
    else:
        tdkTestObj.setResultStatus("FAILURE");	
        print "TEST STEP 1: Get the PrimaryLANBridge object";
        print "EXPECTED RESULT 1: Should get the PrimaryLANBridge object";
        print "ACTUAL RESULT 1: Failure in getting the PrimaryLANBridge object. Details : %s" %details;
        print "[TEST EXECUTION RESULT] : FAILURE";
    obj.unloadModule("pam");
   		 
else:   
        print "Failed to load pam module";
        obj.setLoadModuleStatus("FAILURE");
        print "Module loading failed";				
