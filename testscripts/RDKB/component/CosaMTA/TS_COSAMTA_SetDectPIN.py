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
  <name>TS_COSAMTA_SetDectPIN</name>
  <primitive_test_id/>
  <primitive_test_name>CosaMTA_SetDectPIN</primitive_test_name>
  <primitive_test_version>1</primitive_test_version>
  <status>FREE</status>
  <synopsis/>
  <groups_id/>
  <execution_time>2</execution_time>
  <long_duration>false</long_duration>
  <remarks/>
  <skip>false</skip>
  <box_types>
    <box_type>Emulator</box_type>
    <box_type>Broadband</box_type>
  </box_types>
  <rdk_versions>
    <rdk_version>RDKB</rdk_version>
  </rdk_versions>
  <test_cases>
    <test_case_id>TC_COSAMTA_17</test_case_id>
    <test_objective>To Validate MTA 
"CosaDmlMTASetDectPIN" API </test_objective>
    <test_type>Positive</test_type>
    <test_setup>Emulator,
XB3</test_setup>
    <pre_requisite>1.Ccsp Components  should be in a running state else invoke cosa_start.sh manually that includes all the ccsp components.
2.TDK Agent should be in running state or invoke it through StartTdk.sh script
</pre_requisite>
    <api_or_interface_used>None</api_or_interface_used>
    <input_parameters>Json Interface:

API Name:
CosaMTA_SetDectPIN

Input:
1. handleType - 0
2. bufferType - 0




</input_parameters>
    <automation_approch>1.Function which needs to be tested will be configured in Test Manager GUI.
2.Python Script will be generated by Test Manager with arguments provided in configure page. 
3.Test manager will load the COSAMTA library via Test agent
4.From python script, invoke CosaMTA_SetDectPIN() stub function to get the value of MTA reset count
5.COSAMTA stub function will call the ssp_CosaDmlMTASetDectPIN() function in TDK component which in turn will call cosa api CosaDmlMTASetDectPIN() of theMTA Agent in RDKB stack.
6.Responses from Cosa API, TDK Component and COSAMTA stub function will be logged in Agent Console log.
7.COSAMTA stub will validate the actual result with the expected result and send the result status to Test Manager.
8.Test Manager will publish the result in GUI as PASS/FAILURE based on the response from COSAMTA stub.


</automation_approch>
    <except_output>CheckPoint 1:
Values associated with the parameter specified should be logged in the Agent console/Component log and should set the dect pin successfully

CheckPoint 2:
Stub function result should be success and should see corresponding log in the agent console log

</except_output>
    <priority>High</priority>
    <test_stub_interface>None</test_stub_interface>
    <test_script>TS_COSAMTA_SetDectPIN</test_script>
    <skipped>No</skipped>
    <release_version/>
    <remarks/>
  </test_cases>
  <script_tags/>
</xml>

'''
#use tdklib library,which provides a wrapper for tdk testcase script 
import tdklib;
import time;

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("cosamta","RDKB");

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_COSAMTA_SetDectPIN');

#Get the result of connection with test component and STB
loadmodulestatus =obj.getLoadModuleResult();
print "[LIB LOAD STATUS]  :  %s" %loadmodulestatus ;

if "SUCCESS" in loadmodulestatus.upper():
        obj.setLoadModuleStatus("SUCCESS");

        #Script to load the configuration file of the component
        tdkTestObj = obj.createTestStep("CosaMTA_SetDectPIN");
        tdkTestObj.addParameter("handleType",0);
        tdkTestObj.addParameter("bufferType",0);
        expectedresult="SUCCESS";
        tdkTestObj.executeTestCase(expectedresult);
        actualresult = tdkTestObj.getResult();

        if expectedresult in actualresult:
            #Set the result status of execution
            tdkTestObj.setResultStatus("SUCCESS");
            details = tdkTestObj.getResultDetails();
            print "TEST STEP 1: Should set the Dect PIN";
            print "EXPECTED RESULT 1: Should set the Dect PIN successfully";
            print "ACTUAL RESULT 1: %s" %details;
            #Get the result of execution
            print "[TEST EXECUTION RESULT] : %s" %actualresult ; 
        else:
            tdkTestObj.setResultStatus("FAILURE");
            details = tdkTestObj.getResultDetails();
            print "TEST STEP 1: Should set the Dect PIN";
            print "EXPECTED RESULT 1: Should set the Dect PIN successfully";
            print "ACTUAL RESULT 1: %s" %details;
            print "[TEST EXECUTION RESULT] : %s" %actualresult ;              
            
        obj.unloadModule("cosamta");
else:
        print "Failed to load the module";
        obj.setLoadModuleStatus("FAILURE");
        print "Module loading failed";
