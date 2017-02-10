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
  <name>TS_ParentalCtrl_ManagedDevicesDisabled_AddRule</name>
  <primitive_test_id/>
  <primitive_test_name>pam_GetParameterValues</primitive_test_name>
  <primitive_test_version>1</primitive_test_version>
  <status>FREE</status>
  <synopsis>To verify whether user is able to add rule when ‘Manageddevices’ is disabled</synopsis>
  <groups_id/>
  <execution_time>2</execution_time>
  <long_duration>false</long_duration>
  <remarks/>
  <skip>false</skip>
  <box_types>
    <box_type>Broadband</box_type>
    <box_type>Emulator</box_type>
  </box_types>
  <rdk_versions>
    <rdk_version>RDKB</rdk_version>
  </rdk_versions>
  <test_cases>
    <test_case_id>TC_PAM_148</test_case_id>
    <test_objective>To verify whether user is able to add rule when Manageddevices is disabled</test_objective>
    <test_type>Negative</test_type>
    <test_setup>XB3, Emulator</test_setup>
    <pre_requisite>TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>pam_GetParameterValues
AdvancedConfig_Set
AdvancedConfig_AddObject
AdvancedConfig_DelObject</api_or_interface_used>
    <input_parameters>Device.X_Comcast_com_ParentalControl.ManagedDevices.Enable
Device.X_Comcast_com_ParentalControl.ManagedDevices.AllowAll
Device.X_Comcast_com_ParentalControl.ManagedDevices.Device.</input_parameters>
    <automation_approch>1.Function which needs to be tested will be configured in Test Manager GUI.
2.Python Script will be generated by Test Manager with provided arguments in configure page. 
3.TM will load the pamstub lib via Test agent
5.with pamstub's getparamvalue() get Device.X_Comcast_com_ParentalControl.ManagedDevices.Enable, store it and set it as true
5. With AdvancedConfig_AddObject add new blockedsite instance
8. With AdvancedConfig_DelObject delete the added instance
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
    <test_script>TS_ParentalCtrl_ManagedDevicesDisabled_AddRule</test_script>
    <skipped>No</skipped>
    <release_version/>
    <remarks/>
  </test_cases>
</xml>

'''
# use tdklib library,which provides a wrapper for tdk testcase script 
import tdklib; 
#Test component to be tested
pamObj = tdklib.TDKScriptingLibrary("pam","RDKB");
obj = tdklib.TDKScriptingLibrary("advancedconfig","RDKB");

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_ParentalCtrl_ManagedDevicesDisabled_AddRule');
pamObj.configureTestCase(ip,port,'TS_ParentalCtrl_ManagedDevicesDisabled_AddRule');

#Get the result of connection with test component and STB
loadmodulestatus =obj.getLoadModuleResult();
pamloadmodulestatus =pamObj.getLoadModuleResult();
print "[LIB LOAD STATUS]  :  %s" %loadmodulestatus ;

if "SUCCESS" in loadmodulestatus.upper() and "SUCCESS" in pamloadmodulestatus.upper():
    #get the orinal status and store it
    obj.setLoadModuleStatus("SUCCESS");
    pamObj.setLoadModuleStatus("SUCCESS");
    tdkTestObj = obj.createTestStep('pam_GetParameterValues');
    tdkTestObj.addParameter("ParamName","Device.X_Comcast_com_ParentalControl.ManagedDevices.Enable");
    expectedresult="SUCCESS";
    #Execute the test case in STB
    tdkTestObj.executeTestCase(expectedresult);
    actualresult = tdkTestObj.getResult();
    details = tdkTestObj.getResultDetails();
    if expectedresult in actualresult:
        tdkTestObj.setResultStatus("SUCCESS");
        org_status = details;
        print "TEST STEP 1: Get ManagedDevice Enable status";
        print "EXPECTED RESULT 1: Should get the Enable status";
        print "ACTUAL RESULT 1: ManagedDevice Enable status is %s" %details;
        #Get the result of execution
        print "[TEST EXECUTION RESULT] : SUCCESS";
        tdkTestObj = obj.createTestStep('pam_GetParameterValues');
        tdkTestObj.addParameter("ParamName","Device.X_Comcast_com_ParentalControl.ManagedDevices.AllowAll");
        expectedresult="SUCCESS";
        #Execute the test case in STB
        tdkTestObj.executeTestCase(expectedresult);
        actualresult = tdkTestObj.getResult();
        details = tdkTestObj.getResultDetails();
        if expectedresult in actualresult:
            tdkTestObj.setResultStatus("SUCCESS");
            org_access = details;
            print "TEST STEP 2: Get ManagedDevice Access type";
            print "EXPECTED RESULT 2: Should get the Access type";
            print "ACTUAL RESULT 2: ManagedDevice Access type is %s" %details;
            #Get the result of execution
            print "[TEST EXECUTION RESULT] : SUCCESS";
            #set enable as true
            tdkTestObj = obj.createTestStep('AdvancedConfig_Set');
            tdkTestObj.addParameter("paramName","Device.X_Comcast_com_ParentalControl.ManagedDevices.Enable");
            tdkTestObj.addParameter("paramValue","false");
            tdkTestObj.addParameter("paramType","boolean");
            tdkTestObj.executeTestCase(expectedresult);
            actualresult = tdkTestObj.getResult();
            details = tdkTestObj.getResultDetails();
            print "[TEST EXECUTION RESULT] : %s" %actualresult ;
            if expectedresult in actualresult:
                tdkTestObj.setResultStatus("SUCCESS");
                print "TEST STEP 3: Set ManagedDevices Enable status as false";
                print "EXPECTED RESULT 3: Should set the Enable status as false";
                print "ACTUAL RESULT 3: ManagedDevices Enable status is %s" %details;
                #Get the result of execution
                print "[TEST EXECUTION RESULT] : SUCCESS";
                tdkTestObj = obj.createTestStep('AdvancedConfig_Set');
                tdkTestObj.addParameter("paramName","Device.X_Comcast_com_ParentalControl.ManagedDevices.AllowAll");
                tdkTestObj.addParameter("paramValue","true");
                tdkTestObj.addParameter("paramType","boolean");
                tdkTestObj.executeTestCase(expectedresult);
                actualresult = tdkTestObj.getResult();
                details = tdkTestObj.getResultDetails();
                print "[TEST EXECUTION RESULT] : %s" %actualresult ;
                if expectedresult in actualresult:
                    tdkTestObj.setResultStatus("SUCCESS");
                    print "TEST STEP 4: Set Access Type to AllowAll";
                    print "EXPECTED RESULT 4: Should set Access Type to AllowAll";
                    print "ACTUAL RESULT 4: %s" %details;
                    #Get the result of execution
                    print "[TEST EXECUTION RESULT] : SUCCESS";
                    #add a new device to be blocked
                    tdkTestObj = obj.createTestStep("AdvancedConfig_AddObject");
                    tdkTestObj.addParameter("paramName","Device.X_Comcast_com_ParentalControl.ManagedDevices.Device.");
		    expectedresult="SUCCESS";
                    tdkTestObj.executeTestCase(expectedresult);
                    actualresult = tdkTestObj.getResult();
                    details = tdkTestObj.getResultDetails();
                    if expectedresult in actualresult:
                        #Set the result status of execution
                        tdkTestObj.setResultStatus("SUCCESS");
                        print "[TEST STEP 5]: Adding new rule for device blocking";
                        print "[EXPECTED RESULT 5]: Should add new rule";
                        print "[ACTUAL RESULT 5]:  %s" %details;
                        print "[TEST EXECUTION RESULT] : %s" %actualresult;
                        temp = details.split(':');
                        instance1 = temp[1];
                        if (instance1 > 0):
                            print "INSTANCE VALUE: %s" %instance1
			    tdkTestObj = obj.createTestStep("AdvancedConfig_SetMultiple");
                            tdkTestObj.addParameter("paramList","Device.X_Comcast_com_ParentalControl.ManagedDevices.Device.%s.Type|Allow|string|Device.X_Comcast_com_ParentalControl.ManagedDevices.Device.%s.Description|Comcast|string|Device.X_Comcast_com_ParentalControl.ManagedDevices.Device.%s.MACAddress|BC:30:5B:BF:98:23|string|Device.X_Comcast_com_ParentalControl.ManagedDevices.Device.%s.AlwaysBlock|false|bool" %(instance1, instance1, instance1, instance1));
			    expectedresult="FAILURE";
                            tdkTestObj.executeTestCase(expectedresult);
                            actualresult = tdkTestObj.getResult();
                            details = tdkTestObj.getResultDetails();
                            if expectedresult in actualresult:
                                tdkTestObj.setResultStatus("SUCCESS");
                                print "[TEST STEP 6]: Setting a valid device as device to be blocked"
                                print "[EXPECTED RESULT 6]: Should not set the device"
                                print "[ACTUAL RESULT 6]: SUCCESS: %s" %details;
                                print "[TEST EXECUTION RESULT] : %s" %actualresult;
			    else:
                                tdkTestObj.setResultStatus("FAILURE");
                                print "[TEST STEP 6]: Setting a valid device as device to be blocked"
                                print "[EXPECTED RESULT 6]: Should not set the device"
                                print "[ACTUAL RESULT 6]: SUCCESS: %s" %details;
                                print "[TEST EXECUTION RESULT] : %s" %actualresult;

                            #Delete the created table entry
                            tdkTestObj = obj.createTestStep("AdvancedConfig_DelObject");
                            tdkTestObj.addParameter("paramName","Device.X_Comcast_com_ParentalControl.ManagedDevices.Device.%s." %instance1);
                            expectedresult = "SUCCESS";
                            tdkTestObj.executeTestCase(expectedresult);
                            actualresult = tdkTestObj.getResult();
                            print "[TEST EXECUTION RESULT] : %s" %actualresult ;
                            details = tdkTestObj.getResultDetails();
                            if expectedresult in actualresult:
                                #Set the result status of execution
                                tdkTestObj.setResultStatus("SUCCESS");
                                print "[TEST STEP ]: Deleting the added rule";
                                print "[EXPECTED RESULT ]: Should delete the added rule";
                                print "[ACTUAL RESULT]: %s" %details;
                                print "[TEST EXECUTION RESULT] : %s" %actualresult;
                                print "Added table is deleted successfully\n"
                            else:
                                tdkTestObj.setResultStatus("FAILURE");
                                print "[TEST STEP ]: Deleting the added rule";
                                print "[EXPECTED RESULT ]: Should delete the added rule";
                                print "[ACTUAL RESULT]: %s" %details;
                                print "[TEST EXECUTION RESULT] : %s" %actualresult;
                                print "Added table could not be deleted\n"
			else:
                            print "Wrong instance number";
                    else:
                        #Set the result status of execution
                        tdkTestObj.setResultStatus("FAILURE");
                        print "[TEST STEP 5]: Adding new rule for site blocking";
                        print "[EXPECTED RESULT 5]: Should add new rule";
                        print "[ACTUAL RESULT 5]: %s" %details;
                        print "[TEST EXECUTION RESULT] : %s" %actualresult;


                    #set enable status to its original value
                    tdkTestObj = obj.createTestStep('AdvancedConfig_Set');
                    tdkTestObj.addParameter("paramName","Device.X_Comcast_com_ParentalControl.ManagedDevices.AllowAll");
                    tdkTestObj.addParameter("paramValue",org_access.strip());
                    tdkTestObj.addParameter("paramType","boolean");
                    tdkTestObj.executeTestCase(expectedresult);
                    actualresult = tdkTestObj.getResult();
                    details = tdkTestObj.getResultDetails();
                    print "[TEST EXECUTION RESULT] : %s" %actualresult ;
                    if expectedresult in actualresult:
                        tdkTestObj.setResultStatus("SUCCESS");
                        print "TEST STEP : Set ManagedDevices access type as its initial value";
                        print "EXPECTED RESULT : Should set the access type as its initial value";
                        print "ACTUAL RESULT : ManagedDevice access type set success"
                        #Get the result of execution
                        print "[TEST EXECUTION RESULT] : SUCCESS";
                    else:
                        tdkTestObj.setResultStatus("FAILURE");
                        print "TEST STEP : Set ManagedDevices access type as its initial value";
                        print "EXPECTED RESULT : Should set the access type as its initial value";
                        print "ACTUAL RESULT : ManagedDevice access type set failed";
                        #Get the result of execution
                        print "[TEST EXECUTION RESULT] : FAILURE";
                else:
                    tdkTestObj.setResultStatus("FAILURE");
                    print "TEST STEP 4: Set ManagedDevices access type as AllowAll";
                    print "EXPECTED RESULT 4: Should set the access type as AllowAll ";
                    print "ACTUAL RESULT 4: ManagedDevices access type set failed";
                    print "[TEST EXECUTION RESULT] : FAILURE";
                #set enable status to its original value
                tdkTestObj = obj.createTestStep('AdvancedConfig_Set');
                tdkTestObj.addParameter("paramName","Device.X_Comcast_com_ParentalControl.ManagedDevices.Enable");
                tdkTestObj.addParameter("paramValue",org_status.strip());
                tdkTestObj.addParameter("paramType","boolean");
                tdkTestObj.executeTestCase(expectedresult);
                actualresult = tdkTestObj.getResult();
                details = tdkTestObj.getResultDetails();
                print "[TEST EXECUTION RESULT] : %s" %actualresult ;
                if expectedresult in actualresult:
                    tdkTestObj.setResultStatus("SUCCESS");
                    print "TEST STEP : Set ManagedDevice Enable status as its initial value";
                    print "EXPECTED RESULT : Should set the Enable status as its initial value";
                    print "ACTUAL RESULT : ManagedDevice Enable status set success"
                    #Get the result of execution
                    print "[TEST EXECUTION RESULT] : SUCCESS";
                else:
                    tdkTestObj.setResultStatus("FAILURE");
                    print "TEST STEP : Set ManagedDevice Enable status as its initial value";
                    print "EXPECTED RESULT : Should set the Enable status as its initial value";
                    print "ACTUAL RESULT : ManagedDevice Enable status set failed";
                    #Get the result of execution
                    print "[TEST EXECUTION RESULT] : FAILURE";
            else:
                tdkTestObj.setResultStatus("FAILURE");
                print "TEST STEP 3: Set Manageddevice Enable status as true";
                print "EXPECTED RESULT 3: Should set the Enable status as true";
                print "ACTUAL RESULT 3: ManagedDevice Enable status set failed";
                print "[TEST EXECUTION RESULT] : FAILURE";
        else:
            tdkTestObj.setResultStatus("FAILURE");
            print "TEST STEP 2: Get ManagedDevice access type";
            print "EXPECTED RESULT 2: Should get the access type";
            print "ACTUAL RESULT 2: ManagedDevice access type is %s" %details;
            print "[TEST EXECUTION RESULT] : FAILURE";
    else:
        tdkTestObj.setResultStatus("FAILURE");
        print "TEST STEP 1: Get ManagedDevice Enable status";
        print "EXPECTED RESULT 1: Should get the status";
        print "ACTUAL RESULT 1: Manageddevice Enable status is %s" %details;
        print "[TEST EXECUTION RESULT] : FAILURE";
    obj.unloadModule("advancedconfig");
    pamObj.unloadModule("pam");

else:
        print "Failed to load pam module";
        obj.setLoadModuleStatus("FAILURE");
        pamObj.setLoadModuleStatus("FAILURE");
        print "Module loading failed";
