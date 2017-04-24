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
  <name>TS_PAM_SetDHCPBeginIPasLANGatewayIP</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id> </primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>pam_SetParameterValues</primitive_test_name>
  <!--  -->
  <primitive_test_version>2</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>This test case will check whether setting the DHCP Begin IP address as LAN Gateway IP address is not allowed.</synopsis>
  <!--  -->
  <groups_id />
  <!--  -->
  <execution_time>2</execution_time>
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
						# import statements
import tdklib;

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("pam","RDKB");

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_PAM_SetDHCPBeginIPasLANGatewayIP');

#Get the result of connection with test component and STB
loadModuleresult =obj.getLoadModuleResult();
print "[LIB LOAD STATUS]  :  %s" %loadModuleresult;

if "SUCCESS" in loadModuleresult.upper():
        obj.setLoadModuleStatus("SUCCESS");
        
        tdkTestObj = obj.createTestStep("pam_GetParameterValues");
        tdkTestObj.addParameter("ParamName","Device.X_CISCO_COM_DeviceControl.LanManagementEntry.1.LanIPAddress");
        expectedresult = "SUCCESS";
        tdkTestObj.executeTestCase(expectedresult);
        actualresult = tdkTestObj.getResult();

        if expectedresult in actualresult:
                #Set the result status of execution
                tdkTestObj.setResultStatus("SUCCESS");
                details = tdkTestObj.getResultDetails();
		print "[TEST STEP 1]: Retrieve the current LAN IP address";
                print "[EXPECTED RESULT 1]: Should Retrieve the current LAN IP address";
                print "[ACTUAL RESULT 1]: %s" %details;
                print "[TEST EXECUTION RESULT] : %s" %actualresult;
                
                tdkTestObj = obj.createTestStep("pam_SetParameterValues");
                tdkTestObj.addParameter("ParamName","Device.DHCPv4.Server.Pool.1.MinAddress");
                tdkTestObj.addParameter("Type","string");
                tdkTestObj.addParameter("ParamValue",details);
                expectedresult = "FAILURE";
                tdkTestObj.executeTestCase(expectedresult);
                actualresult = tdkTestObj.getResult();
                if expectedresult in actualresult:
                    #Set the result status of execution
                    tdkTestObj.setResultStatus("SUCCESS");
                    details = tdkTestObj.getResultDetails();
                    print "[TEST STEP 2]: Set the DHCP Begin Address as LAN Gateway IP address";
                    print "[EXPECTED RESULT 2]: Should fail to set DHCP Begin Address as LAN Gateway IP address";
                    print "[ACTUAL RESULT 2]: %s" %details;
                    print "[TEST EXECUTION RESULT] : SUCCESS";
                else:
                    tdkTestObj.setResultStatus("FAILURE");
                    details = tdkTestObj.getResultDetails();
                    print "[TEST STEP 2]: Set the DHCP Begin Address as LAN Gateway IP address";
                    print "[EXPECTED RESULT 2]: Should fail to set DHCP Begin Address as LAN Gateway IP address";
                    print "[ACTUAL RESULT 2]: %s" %details;
                    print "[TEST EXECUTION RESULT] : FAILURE";
        else:
                tdkTestObj.setResultStatus("FAILURE");
                details = tdkTestObj.getResultDetails();
                print "[TEST STEP 1]: Retrieve the current LAN IP address";
                print "[EXPECTED RESULT 1]: Should Retrieve the current LAN IP address";
                print "[ACTUAL RESULT 1]: %s" %details;
                print "[TEST EXECUTION RESULT] : %s" %actualresult;

        obj.unloadModule("pam");
else:
        print "Failed to load pam module";
        obj.setLoadModuleStatus("FAILURE");
        print "Module loading FAILURE";

					

					