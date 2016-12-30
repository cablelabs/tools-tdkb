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
  <version>6</version>
  <!-- Do not edit version. This will be auto incremented while updating. If you are adding a new script you can keep the vresion as 1 -->
  <name>TS_COSAPAM_IpDnsGetRelayStatus</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id> </primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>pam_GetParameterValues</primitive_test_name>
  <!--  -->
  <primitive_test_version>1</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>This test case returns the status of DNS Relay</synopsis>
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
    <box_type>Emulator</box_type>
    <!--  -->
  </box_types>
  <rdk_versions>
    <rdk_version>RDKB</rdk_version>
    <!--  -->
  </rdk_versions>
  <test_cases>
    <test_case_id>TC_COSAPAM_14</test_case_id>
    <test_objective>To Validate PAM API CosaDmlIpDnsGetRelayStatus</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Emulator,Broadband</test_setup>
    <pre_requisite>1.Ccsp Components  should be in a running state else invoke cosa_start.sh manually that includes all the ccsp components.
2.TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>CosaDmlDnsGet</api_or_interface_used>
    <input_parameters>Input:
none</input_parameters>
    <automation_approch>1.Function which needs to be tested will be configured in Test Manager GUI.
2.Python Script will be generated by Test Manager with arguments provided in configure page. 
3.Test manager will load the COSAPAM library via Test agent
4.From python script, invoke COSAPAM_DnsGet() stub function to get the DNS Relay status
5.COSAPAM stub function will call the ssp_CosaDmlDnsGet function in TDK component which in turn will call cosa api CosaDmlIIpDnsGetRelayStatus() of the PAM Agent in RDKB stack.
6.Responses from Cosa API, TDK Component and COSAPAM stub function will be logged in Agent Console log.
7.COSAPAM stub will validate the actual result with the expected result and send the result status to Test Manager.
8.Test Manager will publish the result in GUI as PASS/FAILURE based on the response from COSAPAM stub.</automation_approch>
    <except_output>CheckPoint 1:
Values associated with the parameter specified should be logged in the Agent console/Component log and Should get the DNS Relay status successfully


CheckPoint 2:
Stub function result should be success and should see corresponding log in the agent console log</except_output>
    <priority>High</priority>
    <test_stub_interface>COSAPAM_DnsGet</test_stub_interface>
    <test_script>TS_COSAPAM_IpDnsGetRelayStatus</test_script>
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
obj = tdklib.TDKScriptingLibrary("pam","RDKB");

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_COSAPAM_IpDnsGetRelayStatus');

#Get the result of connection with test component and STB
loadmodulestatus =obj.getLoadModuleResult();
print "[LIB LOAD STATUS]  :  %s" %loadmodulestatus ;

if "SUCCESS" in loadmodulestatus.upper():
    #Set the result status of execution
    obj.setLoadModuleStatus("SUCCESS");
    tdkTestObj = obj.createTestStep('COSAPAM_DnsGet');
    tdkTestObj.addParameter("MethodName","DnsRelayStatus");
    expectedresult="SUCCESS";

    #Execute the test case in STB
    tdkTestObj.executeTestCase(expectedresult);
    actualresult = tdkTestObj.getResult();
    details = tdkTestObj.getResultDetails();

    if expectedresult in actualresult:
       #Set the result status of execution
       tdkTestObj.setResultStatus("SUCCESS");
       print "TEST STEP 1: Get the state of Dns relay";
       print "EXPECTED RESULT 1: Should get the state of Dns relay";
       if "0" in details:
           print "ACTUAL RESULT 1:Dns relay is enabled";
       else:
           print "ACTUAL RESULT 1:Dns relay is disabled";
       #Get the result of execution
       print "[TEST EXECUTION RESULT] : %s" %actualresult;
    else:
       tdkTestObj.setResultStatus("FAILURE");
       print "TEST STEP 1: Get the state of Dns relay";
       print "EXPECTED RESULT 1: Failure in getting the state of Dns relay";
       print "ACTUAL RESULT 1: %s" %details;
       print "[TEST EXECUTION RESULT] : %s" %actualresult;
    obj.unloadModule("pam");

else:
        print "Failed to load pam module";
        obj.setLoadModuleStatus("FAILURE");
        print "Module loading failed";
					
