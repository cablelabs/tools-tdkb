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
  <name>TS_SNMP_GetSysDescrBootR</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id></primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>GetCommString</primitive_test_name>
  <!--  -->
  <primitive_test_version>1</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>With snmpget retrieve the device bootloader version</synopsis>
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
  <test_cases>
    <test_case_id>TC_SNMP_PA_23</test_case_id>
    <test_objective>With snmpget retrieve the Device Bootloader</test_objective>
    <test_type>Positive</test_type>
    <test_setup>XB3</test_setup>
    <pre_requisite>1.Ccsp Components in DUT should be in a running state that includes component under test Cable Modem
2.TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>GetCommString
pam_GetParameterValues</api_or_interface_used>
    <input_parameters>SnmpMethod : snmpget
SnmpVersion : v2c
OID : 1.3.6.1.2.1.1.1.0

Device.DeviceInfo.X_CISCO_COM_BootloaderVersion</input_parameters>
    <automation_approch>1.TM will load the snmp_pa and pam library via Test agent
2.From python script, invoke SnmpExecuteCmd function in snmplib to get the value of given OID 
3. GetCommString function in the SNMP_PA stub  will be called from snmplib to get the community string. 
4. Get bootr using getparams()and compare with snmpget output
4.Responses from the snmplib and getparams() will be logged in Script log.
6. Validation of  the result is done within the python script and send the result status to Test Manager.
7.Test Manager will publish the result in GUI as PASS/FAILURE based on the response from pam stub.</automation_approch>
    <except_output>CheckPoint 1:
  Response of snmp command should be logged in the script log

CheckPoint 2:
Stub and lib function result should be success and should see corresponding log in the script log

CheckPoint 3:
TestManager GUI will publish the result as PASS in Execution/Console page of Test Manager</except_output>
    <priority>High</priority>
    <test_stub_interface>snmp_pa, pam</test_stub_interface>
    <test_script>TS_SNMP_GetSysDescrBootR</test_script>
    <skipped>No</skipped>
    <release_version></release_version>
    <remarks></remarks>
  </test_cases>
  <script_tags />
</xml>
'''
																		# use tdklib library,which provides a wrapper for tdk testcase script 
import tdklib; 
import snmplib;

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("snmp_pa","1");
pamObj = tdklib.TDKScriptingLibrary("pam","RDKB");

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_SNMP_GetSysDescrBootR');
pamObj.configureTestCase(ip,port,'TS_SNMP_GetSysDescrBootR');

#Get the result of connection with test component and STB
loadmodulestatus1 =obj.getLoadModuleResult();
loadmodulestatus2 =pamObj.getLoadModuleResult();
print "[LIB LOAD STATUS]  :  %s" %loadmodulestatus1

if "SUCCESS" in loadmodulestatus1.upper() and "SUCCESS" in loadmodulestatus2.upper():
    obj.setLoadModuleStatus("SUCCESS");
    tdkTestObj = obj.createTestStep('GetCommString');
    actResponse =snmplib.SnmpExecuteCmd(tdkTestObj, "snmpget", "-v 2c", "1.3.6.1.2.1.1.1.0", ip);

    if "SNMPv2-MIB" in actResponse:
        bootr = actResponse.split("BOOTR:")[1].split(';')[0].strip()
        tdkTestObj.setResultStatus("SUCCESS");
        print "TEST STEP 1:Execute snmpget for BOOTR in system description";
        print "EXPECTED RESULT 1: snmpget should get the BOOTR system description values";
        print "ACTUAL RESULT 1: BOOTR is %s" %bootr;
        #Get the result of execution
        print "[TEST EXECUTION RESULT] : %s" %bootr ;

        tdkTestObj = pamObj.createTestStep('pam_GetParameterValues');
        tdkTestObj.addParameter("ParamName","Device.DeviceInfo.X_CISCO_COM_BootloaderVersion");
        expectedresult="SUCCESS";

        #Execute the test case in STB
        tdkTestObj.executeTestCase("expectedresult");
        actualresult = tdkTestObj.getResult();
        details = tdkTestObj.getResultDetails();

        if expectedresult in actualresult:
            #Set the result status of execution
            print "TEST STEP 1: Get the BOOTR using getparams";
            print "EXPECTED RESULT 1: Should get the same BOOTR as snmpget";
            if bootr==details:
                 tdkTestObj.setResultStatus("SUCCESS");
                 print "ACTUAL RESULT 1: BOOTR from getparams same as snmpget";
            else:
                 tdkTestObj.setResultStatus("FAILURE");
                 print "ACTUAL RESULT 1: BOOTR from getparams not same as snmpget";
            #Get the result of execution
            print "[TEST EXECUTION RESULT] : %s" %details
        else:
            print "TEST STEP 1: Get the BOOTR using getparams";
            print "EXPECTED RESULT 1: Should get the same BOOTR as snmpget";
            print "ACTUAL RESULT 1: Couldn't get BOOTR from getparams"
            tdkTestObj.setResultStatus("FAILURE");

    else:
        tdkTestObj.setResultStatus("FAILURE");
        details = tdkTestObj.getResultDetails();
        print "TEST STEP 1:Execute snmpget for BOOTR in system description";
        print "EXPECTED RESULT 1: snmpget should get the BOOTR system description values";
        print "ACTUAL RESULT 1: %s" %actResponse;
        print "[TEST EXECUTION RESULT] : %s" %actResponse ;
    obj.unloadModule("snmp_pa");
    pamObj.unloadModule("pam");
else:
        print "FAILURE to load SNMP_PA module";
        obj.setLoadModuleStatus("FAILURE");
	pamObj.setLoadModuleStatus("FAILURE");
        print "Module loading FAILURE";

					

					

					