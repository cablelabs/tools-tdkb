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
  <name>TS_SNMP_Get5.0SSIDWithDisableXfinityWifi</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id></primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>GetCommString</primitive_test_name>
  <!--  -->
  <primitive_test_version>1</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>To check whether the SSID name of 5GHZ is "OutOfService" when XfinityWifi is disabled</synopsis>
  <!--  -->
  <groups_id />
  <!--  -->
  <execution_time>1</execution_time>
  <!--  -->
  <long_duration>false</long_duration>
  <!--  -->
  <advanced_script>false</advanced_script>
  <!-- execution_time is the time out time for test execution -->
  <remarks>script execution is causing crash of snmp agent</remarks>
  <!-- Reason for skipping the tests if marked to skip -->
  <skip>true</skip>
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
    <test_case_id>TC_SNMP_PA_17</test_case_id>
    <test_objective>To check if SSID name for 5GHZ is "outof service" when xfinity wifi is disabled</test_objective>
    <test_type>Negative</test_type>
    <test_setup>Emulator,XB3</test_setup>
    <pre_requisite>1.Ccsp Components in DUT should be in a running state that includes component under test Cable Modem
2.TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>None</api_or_interface_used>
    <input_parameters>snmpMethod : snmpget,snmpset
snmpVersion : -v 2c
OID : 1.3.6.1.4.1.17270.50.2.13.1.1.0, .1.3.6.1.4.1.17270.50.2.2.2.1.1.3.10103</input_parameters>
    <automation_approch>1.Function which needs to be tested will be configured in Test Manager GUI.
2.Python Script will be generated by Test Manager with provided arguments in configure page. 
3.TM will load the snmp_pa library via Test agent
4.From python script, invoke SnmpExecuteCmd function in snmplib to get the value of given OID 
5. GetCommString function in the SNMP_PA stub  will be called from snmplib to get the community string. 
6.Responses from the snmplib will be logged in Script log.
7. Validation of  the result is done within the python script and send the result status to Test Manager.
8.Test Manager will publish the result in GUI as PASS/FAILURE based on the response from pam stub.</automation_approch>
    <except_output>CheckPoint 1:
  Response of snmp command should be logged in the script log

CheckPoint 2:
Stub and lib function result should be success and should see corresponding log in the script log

CheckPoint 3:
TestManager GUI will publish the result as PASS in Execution/Console page of Test Manager</except_output>
    <priority>High</priority>
    <test_stub_interface>SNMP_PA_Stub</test_stub_interface>
    <test_script>TS_SNMP_Get5.0SSIDWithDisableXfinityWifi</test_script>
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
from time import sleep;

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("snmp_pa","1");

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_SNMP_Get5.0SSIDWithDisableXfinityWifi');

#Get the result of connection with test component and STB
loadmodulestatus=obj.getLoadModuleResult();
print "[LIB LOAD STATUS]  :  %s" %loadmodulestatus;

if "SUCCESS" in loadmodulestatus.upper():
    obj.setLoadModuleStatus("SUCCESS");
    ########## Script to Execute the snmp command ###########
    tdkTestObj = obj.createTestStep('GetCommString');
    actResponse =snmplib.SnmpExecuteCmd(tdkTestObj, "snmpget", "-v 2c", "1.3.6.1.4.1.17270.50.2.13.1.1.0", ip);

    if "=" in actResponse :
        #Set the result status of execution
        tdkTestObj.setResultStatus("SUCCESS");
        print "TEST STEP 1: snmpget request to get xfinity wifi status";
        print "EXPECTED RESULT 1: Command should return xfinity wifi status";
        print "ACTUAL RESULT 1: %s" %actResponse;
        #Get the result of execution
        print "[TEST EXECUTION RESULT] : SUCCESS"
        org_value = actResponse.rsplit(None, 1)[-1];
        print "Current Status is %s " %org_value;
	if org_value != "2":
  	    actResponse =snmplib.SnmpExecuteCmd(tdkTestObj, "snmpset", "-v 2c", "1.3.6.1.4.1.17270.50.2.13.1.1.0 i 2", ip);
	    sleep(5);
	    actResponse =snmplib.SnmpExecuteCmd(tdkTestObj, "snmpget", "-v 2c", "1.3.6.1.4.1.17270.50.2.13.1.1.0", ip);
	    status = actResponse.rsplit(None, 1)[-1];
	    if status and "2" in status:
                #Set the result status of execution
                tdkTestObj.setResultStatus("SUCCESS");
                print "TEST STEP 2:Disable Xfinity Wifi";
                print "EXPECTED RESULT 2: Should disable Xfinity Wifi successfully";
                print "ACTUAL RESULT 2: %s" %actResponse;
	    else:
		#Set the result status of execution
                tdkTestObj.setResultStatus("FAILURE");
                print "TEST STEP 2:Disable Xfinity Wifi";
                print "EXPECTED RESULT 2: Should disable Xfinity Wifi successfully";
                print "ACTUAL RESULT 2: %s" %actResponse;
   	        obj.unloadModule("snmp_pa");
	actResponse =snmplib.SnmpExecuteCmd(tdkTestObj, "snmpget", "-v 2c", ".1.3.6.1.4.1.17270.50.2.2.2.1.1.3.10103", ip);
	if "OutOfService" in actResponse or "No Such" in actResponse:
	    tdkTestObj.setResultStatus("SUCCESS");
	    print "TEST STEP 2: snmpget request to get the SSID";
	    print "EXPECTED RESULT 2: Command should not return any SSID since Xfinity Wifi is disabled";
            print "ACTUAL RESULT 2: %s" %actResponse;
            #Get the result of execution
	    print "[TEST EXECUTION RESULT] : SUCCESS"
	else:
	    tdkTestObj.setResultStatus("FAILURE");
	    print "TEST STEP 2: snmpget request to get the SSID";
            print "EXPECTED RESULT 2: Command should not return any SSID since Xfinity Wifi is disabled";
            print "ACTUAL RESULT 2: %s" %actResponse;
            #Get the result of execution
            print "[TEST EXECUTION RESULT] : FAILURE";
	if org_value != "2":
	    actResponse =snmplib.SnmpExecuteCmd(tdkTestObj, "snmpset", "-v 2c", "1.3.6.1.4.1.17270.50.2.13.1.1.0 i %s" %org_value, ip);
	    sleep(5);
	    actResponse =snmplib.SnmpExecuteCmd(tdkTestObj, "snmpget", "-v 2c", "1.3.6.1.4.1.17270.50.2.13.1.1.0", ip);
	    status = actResponse.rsplit(None, 1)[-1];
	    if status and org_value in status:
                #Set the result status of execution
                tdkTestObj.setResultStatus("SUCCESS");
                print "TEST STEP 2:Disable Xfinity Wifi";
                print "EXPECTED RESULT 2: Should enable Xfinity Wifi successfully";
                print "ACTUAL RESULT 2: %s" %actResponse;
            else:
                #Set the result status of execution
                tdkTestObj.setResultStatus("FAILURE");
                print "TEST STEP 2:Disable Xfinity Wifi";
                print "EXPECTED RESULT 2: Should enable Xfinity Wifi successfully";
                print "ACTUAL RESULT 2: %s" %actResponse;
    else:
	tdkTestObj.setResultStatus("FAILURE");
	print "TEST STEP 1: snmpget request to get xfinity wifi status";
        print "EXPECTED RESULT 1: Command should return xfinity wifi status";
        print "ACTUAL RESULT 1: %s" %actResponse;
        #Get the result of execution
        print "[TEST EXECUTION RESULT] : FAILURE";
    obj.unloadModule("snmp_pa");
else:
        print "FAILURE to load SNMP_PA module";
        obj.setLoadModuleStatus("FAILURE");
        print "Module loading FAILURE";

					

					
