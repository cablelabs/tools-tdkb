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
  <name>TS_PAM_DNSClient_ServerType</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id> </primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>pam_GetParameterValues</primitive_test_name>
  <!--  -->
  <primitive_test_version>1</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>This test case will retrieve the Server type of the DNS Client and checks whether the retrieved server type is a subset of [DHCPv4, DHCPv6, IPCP, Static or RouterAdvertisement]</synopsis>
  <!--  -->
  <groups_id />
  <!--  -->
  <execution_time>1</execution_time>
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
    <box_type>Broadband</box_type>
    <!--  -->
    <box_type>Emulator</box_type>
    <!--  -->
    <box_type>RPI</box_type>
    <!--  -->
  </box_types>
  <rdk_versions>
    <rdk_version>RDKB</rdk_version>
    <!--  -->
  </rdk_versions>
  <test_cases>
    <test_case_id></test_case_id>
    <test_objective></test_objective>
    <test_type></test_type>
    <test_setup></test_setup>
    <pre_requisite></pre_requisite>
    <api_or_interface_used></api_or_interface_used>
    <input_parameters></input_parameters>
    <automation_approch></automation_approch>
    <except_output></except_output>
    <priority></priority>
    <test_stub_interface></test_stub_interface>
    <test_script></test_script>
    <skipped></skipped>
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
pamObj.configureTestCase(ip,port,'TS_PAM_DNSClient_ServerType');

#Get the result of connection with test component and STB
loadmodulestatus =pamObj.getLoadModuleResult();

if "SUCCESS" in loadmodulestatus.upper():
    pamObj.setLoadModuleStatus("SUCCESS");
    expectedresult="SUCCESS";

    tdkTestObj = pamObj.createTestStep('pam_GetParameterNames');
    tdkTestObj.addParameter("ParamName","Device.DNS.Client.Server.");
    tdkTestObj.addParameter("ParamList","Device.DNS.Client.Server.");
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

        tdkTestObj = pamObj.createTestStep('pam_GetParameterValues');
        tdkTestObj.addParameter("ParamName","%sType" %interface);
        print "Parameter Name: %s" %interface
        tdkTestObj.executeTestCase("expectedresult");
        actualresult = tdkTestObj.getResult();
        details = tdkTestObj.getResultDetails().strip();

        serverType={'Static','DHCPv4','DHCPv6','IPCP','RouterAdvertisement'};
        if expectedresult in actualresult and details in serverType:
            tdkTestObj.setResultStatus("SUCCESS");
            print "TEST STEP 1: Retrieve the Server Type of the DNS client"
            print "EXPECTED RESULT 1: Should Retrieve the Server Type of the DNS client"
            print "ACTUAL RESULT 1: DNS Client Server Type is %s" %details;
            #Get the result of execution
            print "[TEST EXECUTION RESULT] : SUCCESS, %s" %details
        else:
            tdkTestObj.setResultStatus("FAILURE");
            print "TEST STEP 1: Retrieve the Server Type of the DNS client"
            print "EXPECTED RESULT 1: Should Retrieve the Server Type of the DNS client"
            print "ACTUAL RESULT 1: DNS Client Server Type is %s" %details;
            #Get the result of execution
            print "[TEST EXECUTION RESULT] : FAILURE, %s" %details
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

					

					

					

					

					