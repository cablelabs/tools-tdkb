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
  <version>7</version>
  <!-- Do not edit version. This will be auto incremented while updating. If you are adding a new script you can keep the vresion as 1 -->
  <name>TS_PAM_IpIfGetV6AddressOrigin</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id> </primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>pam_GetParameterValues</primitive_test_name>
  <!--  -->
  <primitive_test_version>1</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>This test case will get the Origin type of the IPv6 Address</synopsis>
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
    <box_type>RPI</box_type>
    <box_type>Broadband</box_type>
    <!--  -->
  </box_types>
  <rdk_versions>
    <rdk_version>RDKB</rdk_version>
    <!--  -->
  </rdk_versions>
  <test_cases>
    <test_case_id>TC_PAM_75</test_case_id>
    <test_objective>To get the Origin type of the IPv6 Address</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Emulator,XB3</test_setup>
    <pre_requisite>1.Ccsp Components in DUT should be in a running state that includes component under test Cable Modem
2.TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>None</api_or_interface_used>
    <input_parameters>Json Interface:
API Name
pam_GetParameterValues

Input:
ParamName - Device.IP.Interface.1.IPv6Address.1.Origin</input_parameters>
    <automation_approch>1.Function which needs to be tested will be configured in Test Manager GUI.
2.Python Script will be generated by Test Manager with provided arguments in configure page. 
3.TM will load the PAM library via Test agent
4.From python script, invoke pam_GetParameterValues() stub function to get the origin type of IPV6 address.
5.pam stub function will call the ssp_getParameterValue() function of tdk component.
6.Responses from the pam stub function will be logged in Agent Console log.
7.pam stub will validate the actual result with the expected result and send the result status to Test Manager.
8.Test Manager will publish the result in GUI as PASS/FAILURE based on the response from pam stub.</automation_approch>
    <except_output>CheckPoint 1:
 The Origin type of the IPv6 Address should be logged in the Agent console/Component log

CheckPoint 2:
Stub function result should be success and should see corresponding log in the agent console log

CheckPoint 3:
TestManager GUI will publish the result as PASS in Execution/Console page of Test Manager</except_output>
    <priority>High</priority>
    <test_stub_interface>None</test_stub_interface>
    <test_script>TS_PAM_IpIfGetV6AddressOrigin</test_script>
    <skipped>No</skipped>
    <release_version></release_version>
    <remarks></remarks>
  </test_cases>
  <script_tags />
</xml>
'''
						#import statement
import tdklib; 

#Test component to be tested
pamObj = tdklib.TDKScriptingLibrary("pam","RDKB");

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
pamObj.configureTestCase(ip,port,'TS_PAM_IpIfGetV6AddressOrigin');

#Get the result of connection with test component and STB
loadmodulestatus =pamObj.getLoadModuleResult();

if "SUCCESS" in loadmodulestatus.upper():
    pamObj.setLoadModuleStatus("SUCCESS");
    expectedresult="SUCCESS";

    tdkTestObj = pamObj.createTestStep('pam_GetParameterNames');
    tdkTestObj.addParameter("ParamName","Device.IP.Interface.");
    tdkTestObj.addParameter("ParamList","Device.IP.Interface.");
    tdkTestObj.executeTestCase(expectedresult);
    actualresult = tdkTestObj.getResult();
    interface = tdkTestObj.getResultDetails().strip();
    if expectedresult in actualresult:
        #Set the result status of execution
        tdkTestObj.setResultStatus("SUCCESS");
        print "TEST STEP 1: Get an IP Interface"
        print "EXPECTED RESULT 1: Should get an IP Interface"
        print "ACTUAL RESULT 1: Interface is %s" %interface;
        #Get the result of execution
        print "[TEST EXECUTION RESULT] : SUCCESS, %s" %interface;

	tdkTestObj = pamObj.createTestStep('pam_GetParameterNames');
	tdkTestObj.addParameter("ParamName","%sIPv6Address." %interface);
	tdkTestObj.addParameter("ParamList","%sIPv6Address." %interface);
        tdkTestObj.executeTestCase(expectedresult);
        actualresult = tdkTestObj.getResult();
        addrInstance = tdkTestObj.getResultDetails().strip();

	if expectedresult in actualresult:
            #Set the result status of execution
            tdkTestObj.setResultStatus("SUCCESS");
            print "TEST STEP 1: Get an IPv6address instance"
            print "EXPECTED RESULT 1: Should get an IPv6address instance"
            print "ACTUAL RESULT 1: Instance is %s" %addrInstance;
            #Get the result of execution
            print "[TEST EXECUTION RESULT] : SUCCESS, %s" %addrInstance

	    tdkTestObj = pamObj.createTestStep('pam_GetParameterValues');
            tdkTestObj.addParameter("ParamName","%sOrigin" %addrInstance);
	    print "Parameter Name: %sOrigin" %addrInstance
            tdkTestObj.executeTestCase("expectedresult");
            actualresult = tdkTestObj.getResult();
            details = tdkTestObj.getResultDetails().strip();

	    if expectedresult in actualresult:
                tdkTestObj.setResultStatus("SUCCESS");
                print "TEST STEP 1: Get IPv6address Origin Type"
                print "EXPECTED RESULT 1: Should get IPv6address Origin Type"
                print "ACTUAL RESULT 1: IPv6address is %s" %details;
                #Get the result of execution
                print "[TEST EXECUTION RESULT] : SUCCESS, %s" %details
	    else:
                tdkTestObj.setResultStatus("FAILURE");
                print "TEST STEP 1: Get IPv6address Origin Type"
                print "EXPECTED RESULT 1: Should get IPv6address Origin Type"
                print "ACTUAL RESULT 1: IPv6address is %s" %details;
                #Get the result of execution
                print "[TEST EXECUTION RESULT] : FAILURE, %s" %details
	else:
            tdkTestObj.setResultStatus("FAILURE");
            print "TEST STEP 1: Get an IPv6address instance"
            print "EXPECTED RESULT 1: Should get an IPv6address instance"
            print "ACTUAL RESULT 1: Instance is %s" %addrInstancee;
            #Get the result of execution
            print "[TEST EXECUTION RESULT] : FAILURE, %s" %addrInstance

    else:
        tdkTestObj.setResultStatus("FAILURE");	
        print "TEST STEP 1: Get an IP Interface"
        print "EXPECTED RESULT 1: Should get an IP Interface"
        print "ACTUAL RESULT 1: Failure in getting the Interface. Details : %s" %interface;
        print "[TEST EXECUTION RESULT] : FAILURE";
    pamObj.unloadModule("pam");
   		 
else:   
        print "Failed to load pam module";
        pamObj.setLoadModuleStatus("FAILURE");
        print "Module loading failed";

					
