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
  <name>TS_SNMP_SetSSIDEnableWithRadioEnabled</name>
  <primitive_test_id/>
  <primitive_test_name>GetCommString</primitive_test_name>
  <primitive_test_version>1</primitive_test_version>
  <status>FREE</status>
  <synopsis>Check for SSID enable set when Radio is enabled</synopsis>
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
    <test_case_id>TC_SNMP_PA_39</test_case_id>
    <test_objective>Check for SSID enable set when Radio is enabled</test_objective>
    <test_type>Positive</test_type>
    <test_setup>XB3, Emulator</test_setup>
    <pre_requisite>1.Ccsp Components in DUT should be in a running state that includes component under test Cable Modem
2.TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>GetCommString
pam_SetParameterValues</api_or_interface_used>
    <input_parameters>Device.WiFi.Radio.1.Enable
Device.WiFi.SSID.1.Enable

"snmpget", "-v 2c", "1.3.6.1.4.1.17270.50.2.2.2.1.1.2.10001"</input_parameters>
    <automation_approch>1.TM will load the snmp_pa library via Test agent
2.From python script, invoke SnmpExecuteCmd function in snmplib to get the value of given OID 
3. GetCommString function in the SNMP_PA stub  will be called from snmplib to get the community string. 
4.With pam_SetParameterValues enable wifi.Radio
5.With pam_SetParameterValues enable wifi.SSID
5.Check with snmpget that wifi.SSID is enabled or not
6. Validation of  the result is done within the python script and send the result status to Test Manager.
7.Test Manager will publish the result in GUI as PASS/FAILURE based on the response from pam stub.</automation_approch>
    <except_output>CheckPoint 1:
  Response of snmp command should be logged in the script log

CheckPoint 2:
Stub and lib function result should be success and should see corresponding log in the script log

CheckPoint 3:
TestManager GUI will publish the result as PASS in Execution/Console page of Test Manager</except_output>
    <priority>High</priority>
    <test_stub_interface>snmp_pa
pam</test_stub_interface>
    <test_script>TS_SNMP_SetSSIDEnableWithRadioEnabled</test_script>
    <skipped>No</skipped>
    <release_version/>
    <remarks/>
  </test_cases>
</xml>

'''
# use tdklib library,which provides a wrapper for tdk testcase script 
import tdklib; 
import snmplib;
from time import sleep;

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("snmp_pa","1");
pamObj = tdklib.TDKScriptingLibrary("pam","RDKB");

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_SNMP_SetSSIDEnableWithRadioEnabled');
pamObj.configureTestCase(ip,port,'TS_SNMP_SetSSIDEnableWithRadioEnabled');

#Get the result of connection with test component and STB
loadmodulestatus=obj.getLoadModuleResult();
pamloadmodulestatus =pamObj.getLoadModuleResult();
print "[LIB LOAD STATUS]  :  %s" %loadmodulestatus;

if "SUCCESS" in loadmodulestatus.upper() and "SUCCESS" in pamloadmodulestatus.upper():
    obj.setLoadModuleStatus("SUCCESS");
    pamObj.setLoadModuleStatus("SUCCESS");

    tdkTestObj = pamObj.createTestStep('pam_GetParameterValues');
    tdkTestObj.addParameter("ParamName","Device.WiFi.Radio.1.Enable");
    expectedresult="SUCCESS";
    tdkTestObj.executeTestCase("expectedresult");
    actualresult = tdkTestObj.getResult();
    orgRadio = tdkTestObj.getResultDetails();

    if expectedresult in actualresult:
        tdkTestObj.setResultStatus("SUCCESS");
        print "ACTUAL RESULT 1: Radio status get SUCCESS";

        tdkTestObj.addParameter("ParamName","Device.WiFi.SSID.1.Enable");
        tdkTestObj.executeTestCase("expectedresult");
        actualresult = tdkTestObj.getResult();
        orgSsid = tdkTestObj.getResultDetails();

        if expectedresult in actualresult:
            tdkTestObj.setResultStatus("SUCCESS");
            print "ACTUAL RESULT 1: SSID status get SUCCESS";

            #Disable Radio
            tdkTestObj = obj.createTestStep('pam_SetParameterValues');
            tdkTestObj.addParameter("ParamName","Device.WiFi.Radio.1.Enable");
            tdkTestObj.addParameter("ParamValue","true");
            tdkTestObj.addParameter("Type","boolean");
            expectedresult="SUCCESS";

            #Execute the test case in Gateway
            tdkTestObj.executeTestCase(expectedresult);
            actualresult = tdkTestObj.getResult();
            details = tdkTestObj.getResultDetails();
            if expectedresult in actualresult:
                #Set the result status of execution
                tdkTestObj.setResultStatus("SUCCESS");
                print "TEST STEP 1:Disable WiFi.Radio";
                print "EXPECTED RESULT 1: Should Disable WiFi.Radio";
                print "ACTUAL RESULT 1: SUCCESS, Disabled";

                #Enable Wifi.SSID
                tdkTestObj.addParameter("ParamName","Device.WiFi.SSID.1.Enable");
                tdkTestObj.addParameter("ParamValue","true");
                tdkTestObj.addParameter("Type","boolean");
                expectedresult="SUCCESS";

                tdkTestObj.executeTestCase(expectedresult);
                actualresult = tdkTestObj.getResult();
                details = tdkTestObj.getResultDetails();
                if expectedresult in actualresult:
                    sleep(30)
                    tdkTestObj.setResultStatus("SUCCESS");
                    print "TEST STEP 1:Enable Wifi.SSID";
                    print "EXPECTED RESULT 1: Should ENable wifi.SSID";
                    print "ACTUAL RESULT 1: SUCCESS, enabled";

                    ##Cross check with snmpget of Wifi.SSID
                    tdkTestObj = obj.createTestStep('GetCommString');
                    get_details =snmplib.SnmpExecuteCmd(tdkTestObj, "snmpget", "-v 2c", "1.3.6.1.4.1.17270.50.2.2.2.1.1.2.10001", ip);
                    print "TEST STEP 1:get Wifi.SSID with snmpget";
                    print "EXPECTED RESULT 1: Should get the value as enabled"
                    if "=" in get_details:
                        snmpStatus = get_details.rsplit(None, 1)[-1].strip('"');
                        if snmpStatus == '1':
                            print "ACTUAL RESULT 1: SUCCESS, enabled ", snmpStatus;
                            tdkTestObj.setResultStatus("SUCCESS");
                        else:
                            print "ACTUAL RESULT 1: FAILURE, not enabled", snmpStatus;
                            tdkTestObj.setResultStatus("FAILURE");
                    else:
                        tdkTestObj.setResultStatus("FAILURE");
                        print "ACTUAL RESULT 1: FAILURE, snmpget failed"

                    #restore previous state of wifi.SSID
                    tdkTestObj = obj.createTestStep('pam_SetParameterValues');
                    tdkTestObj.addParameter("ParamName","Device.WiFi.SSID.1.Enable");
                    tdkTestObj.addParameter("ParamValue",orgSsid);
                    tdkTestObj.addParameter("Type","boolean");
                    expectedresult="SUCCESS";
                    tdkTestObj.executeTestCase(expectedresult);
                    actualresult = tdkTestObj.getResult();
                    details = tdkTestObj.getResultDetails();
                    if expectedresult in actualresult:
                        tdkTestObj.setResultStatus("SUCCESS");
                        print "ACTUAL RESULT 1: SUCCESS, WiFi.SSID restored"
                    else:
                        tdkTestObj.setResultStatus("FAILURE");
                        print "ACTUAL RESULT 1: FAILURE, WiFi.SSID not restored"
                else:
                    #Set the result status of execution
                    tdkTestObj.setResultStatus("FAILURE");
                    print "TEST STEP 1:Enable Wifi.SSID";
                    print "EXPECTED RESULT 1: Should ENable Wifi.SSID";
                    print "ACTUAL RESULT 1: FAILURE, not enabled";

                #Restore WiFi.Radio
                tdkTestObj = obj.createTestStep('pam_SetParameterValues');
                tdkTestObj.addParameter("ParamName","Device.WiFi.Radio.1.Enable");
                tdkTestObj.addParameter("ParamValue",orgRadio);
                tdkTestObj.addParameter("Type","boolean");
                expectedresult="SUCCESS";

                tdkTestObj.executeTestCase(expectedresult);
                actualresult = tdkTestObj.getResult();
                details = tdkTestObj.getResultDetails();
                if expectedresult in actualresult:
                    #Set the result status of execution
                    tdkTestObj.setResultStatus("SUCCESS");
                    print "ACTUAL RESULT 1: SUCCESS, WiFi.Radio restored"
                else:
                    tdkTestObj.setResultStatus("FAILURE");
                    print "ACTUAL RESULT 1: FAILURE, WiFi.Radio not restored"
            else:
                tdkTestObj.setResultStatus("FAILURE");
                print "TEST STEP 1:Disable WiFi.Radio";
                print "EXPECTED RESULT 1: Should Disable WiFi.Radio";
                print "ACTUAL RESULT 1: FAILURE, not Disabled";
        else:
            tdkTestObj.setResultStatus("FAILURE");
            print "ACTUAL RESULT 1: SSID status get FAILED";
    else:
        tdkTestObj.setResultStatus("FAILURE");
        print "ACTUAL RESULT 1: Radio status get FAILED";
    obj.unloadModule("snmp_pa");
    pamObj.unloadModule("pam");
else:
    print "FAILURE to load SNMP_PA module";
    obj.setLoadModuleStatus("FAILURE");
    print "Module loading FAILURE";
