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
  <version>2</version>
  <!-- Do not edit version. This will be auto incremented while updating. If you are adding a new script you can keep the vresion as 1 -->
  <name>TS_PAM_Get_ParentalCtrl_SitesEnable</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id> </primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>pam_GetParameterValues</primitive_test_name>
  <!--  -->
  <primitive_test_version>1</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>Check if by default Managed Sites are set as disabled</synopsis>
  <!--  -->
  <groups_id />
  <!--  -->
  <execution_time>8</execution_time>
  <!--  -->
  <long_duration>false</long_duration>
  <!-- execution_time is the time out time for test execution -->
  <remarks>box going to undefined state randomly</remarks>
  <!-- Reason for skipping the tests if marked to skip -->
  <skip>true</skip>
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
    <test_case_id>TC_PAM_125</test_case_id>
    <test_objective>Check if by default, Managed Sites are set as disabled</test_objective>
    <test_type>Positive</test_type>
    <test_setup>XB3, Emulator</test_setup>
    <pre_requisite>TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>pam_GetParameterValues

AdvancedConfig_Set</api_or_interface_used>
    <input_parameters>Device.X_Comcast_com_ParentalControl.ManagedSites.Enable

Device.X_CISCO_COM_DeviceControl.FactoryReset</input_parameters>
    <automation_approch>1.Function which needs to be tested will be configured in Test Manager GUI.
2.Python Script will be generated by Test Manager with provided arguments in configure page. 
3.TM will load the pamstub lib via Test agent
4. With AdvancedConfig_Set() do a factory reset
5.with pamstub's getparamvalue() get Device.X_Comcast_com_ParentalControl.ManagedSites.Enable
6.pam stub will validate the actual result with the expected result and send the result status to Test Manager.
7.Test Manager will publish the result in GUI as PASS/FAILURE based on the response from pam stub.</automation_approch>
    <except_output>CheckPoint 1:
 The output  should be logged in the Agent console/Component log

CheckPoint 2:
Stub function result should be success and should see corresponding log in the agent console log

CheckPoint 3:
TestManager GUI will publish the result as PASS in Execution/Console page of Test Manager</except_output>
    <priority>High</priority>
    <test_stub_interface>pam</test_stub_interface>
    <test_script>TS_PAM_Get_ParentalCtrl_SitesEnable</test_script>
    <skipped>No</skipped>
    <release_version></release_version>
    <remarks></remarks>
  </test_cases>
  <script_tags />
</xml>
'''
						# use tdklib library,which provides a wrapper for tdk testcase script 
import tdklib;
import time; 

#Test component to be tested
#pamObj = tdklib.TDKScriptingLibrary("pam","RDKB");
pamObj = tdklib.TDKScriptingLibrary("pam","RDKB");
obj = tdklib.TDKScriptingLibrary("advancedconfig","RDKB");

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
pamObj.configureTestCase(ip,port,'TS_PAM_Get_ParentalCtrl_SitesEnable');
obj.configureTestCase(ip,port,'TS_PAM_Get_ParentalCtrl_SitesEnable');

#Get the result of connection with test component and STB
pamloadmodulestatus =pamObj.getLoadModuleResult();
loadmodulestatus =obj.getLoadModuleResult();
print "[LIB LOAD STATUS]  :  %s" %loadmodulestatus ;

if "SUCCESS" in loadmodulestatus.upper() and "SUCCESS" in pamloadmodulestatus.upper():
    #Set the result status of execution
    pamObj.setLoadModuleStatus("SUCCESS");
    obj.setLoadModuleStatus("SUCCESS");
    
    expectedresult="SUCCESS";
    tdkTestObj = obj.createTestStep('AdvancedConfig_Set');
    tdkTestObj.addParameter("paramName","Device.X_CISCO_COM_DeviceControl.FactoryReset");
    tdkTestObj.addParameter("paramValue","Router");
    tdkTestObj.addParameter("paramType","string");
    tdkTestObj.executeTestCase(expectedresult);
    actualresult = tdkTestObj.getResult();
    details = tdkTestObj.getResultDetails();
    print "[TEST EXECUTION RESULT] : %s" %actualresult ;
    if expectedresult in actualresult:
        tdkTestObj.setResultStatus("SUCCESS");
        print "TEST STEP 2: set the Factory Reset value to true";
        print "EXPECTED RESULT 2: Should set the Factory Reset value to true";
        print "ACTUAL RESULT 2: %s" %details;
        #Get the result of execution
        print "[TEST EXECUTION RESULT] : SUCCESS";

	time.sleep(180);

        tdkTestObj = pamObj.createTestStep('pam_GetParameterValues');
        tdkTestObj.addParameter("ParamName","Device.X_Comcast_com_ParentalControl.ManagedSites.Enable");

        #Execute the test case in STB
        tdkTestObj.executeTestCase("expectedresult");
        actualresult = tdkTestObj.getResult();
        details = tdkTestObj.getResultDetails();
                
        if expectedresult in actualresult and "false" in details:
            #Set the result status of execution
            tdkTestObj.setResultStatus("SUCCESS");
            print "TEST STEP 1: Get ManagedSites Enable status";
            print "EXPECTED RESULT 1: Should get the status as disabled";
            print "ACTUAL RESULT 1: ManagedSites Enable status is %s" %details;
            #Get the result of execution
            print "[TEST EXECUTION RESULT] : SUCCESS";
        else:
            tdkTestObj.setResultStatus("FAILURE");  
            print "TEST STEP 1: Get ManagedSites Enable status";
            print "EXPECTED RESULT 1: Should get the status as disabled";
            print "ACTUAL RESULT 1: ManagedSites Enable status is %s" %details;
            print "[TEST EXECUTION RESULT] : FAILURE";
    else:
        tdkTestObj.setResultStatus("FAILURE");
        print "EXPECTED RESULT 4: Should set the Factory Reset value to true";
        print "ACTUAL RESULT 4: %s" %details;
        print "[TEST EXECUTION RESULT] : %s" %actualresult;
        print "Factory Reset Function is FAILURE: Value is not set to true"
    pamObj.unloadModule("pam");
    obj.unloadModule("advancedconfig");
                 
else:   
        print "Failed to load pam module";
        pamObj.setLoadModuleStatus("FAILURE");
        obj.setLoadModuleStatus("FAILURE");
        print "Module loading failed";   

					