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
  <name>TS_WIFIAGENT_5GHZ_PassphraseAfterReset</name>
  <primitive_test_id/>
  <primitive_test_name>WIFIAgent_Get</primitive_test_name>
  <primitive_test_version>1</primitive_test_version>
  <status>FREE</status>
  <synopsis>Check if the passphrase changes after doing a wifi factory reset</synopsis>
  <groups_id/>
  <execution_time>10</execution_time>
  <long_duration>false</long_duration>
  <advanced_script>false</advanced_script>
  <remarks/>
  <skip>false</skip>
  <box_types>
    <box_type>Broadband</box_type>
    <box_type>Emulator</box_type>
    <box_type>RPI</box_type>
  </box_types>
  <rdk_versions>
    <rdk_version>RDKB</rdk_version>
  </rdk_versions>
  <test_cases>
    <test_case_id>TC_WIFIAGENT_39</test_case_id>
    <test_objective>Check if the passphrase changes after doing a wifi factory reset</test_objective>
    <test_type>Positive</test_type>
    <test_setup>XB3, Emulator, Rpi</test_setup>
    <pre_requisite>1.Ccsp Components in DUT should be in a running state that includes component under test Cable Modem
2.TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>WIFIAgent_Get
WIFIAgent_Set</api_or_interface_used>
    <input_parameters>Device.WiFi.AccessPoint.2.Security.KeyPassphrase
Device.WiFi.X_CISCO_COM_FactoryReset</input_parameters>
    <automation_approch>1. Load wifiagent module
2. Using WIFIAgent_Get, get and save Device.WiFi.AccessPoint.2.Security.KeyPassphrase
3. Using WIFIAgent_Set, set a temporary passphrase
4. Using Device.WiFi.X_CISCO_COM_FactoryReset do a reset of wifi component
5. After reset check if the temporary passphrase is changed or not
6. Restore the value of Device.WiFi.AccessPoint.2.Security.KeyPassphrase
7. Unload wifiagent module</automation_approch>
    <except_output> passphrase changes after doing a wifi factory reset</except_output>
    <priority>High</priority>
    <test_stub_interface>WifiAgent</test_stub_interface>
    <test_script>TS_WIFIAGENT_5GHZ_PassphraseAfterReset</test_script>
    <skipped>No</skipped>
    <release_version/>
    <remarks/>
  </test_cases>
</xml>

'''
# use tdklib library,which provides a wrapper for tdk testcase script 
import tdklib; 
import time;

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("wifiagent","1");

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_WIFIAGENT_5GHZ_PassphraseAfterReset');

#Get the result of connection with test component
loadmodulestatus =obj.getLoadModuleResult();
print "[LIB LOAD STATUS]  :  %s" %loadmodulestatus ;

if "SUCCESS" in loadmodulestatus.upper():
    obj.setLoadModuleStatus("SUCCESS");

    #Get the default value of SSID
    expectedresult="SUCCESS";
    getParams = "Device.WiFi.AccessPoint.1.Security.KeyPassphrase,Device.WiFi.AccessPoint.2.Security.KeyPassphrase,Device.WiFi.SSID.1.SSID,Device.WiFi.SSID.2.SSID,Device.WiFi.AccessPoint.1.Security.ModeEnabled,Device.WiFi.AccessPoint.2.Security.ModeEnabled"
    getList = getParams.split(',');
    actualresult_get = [];
    orgValue = [];

    for index in range(len(getList)):
        tdkTestObj = obj.createTestStep("WIFIAgent_Get");
        tdkTestObj.addParameter("paramName",getList[index])
        #execute the step 
        tdkTestObj.executeTestCase(expectedresult);
        actualresult_get.append(tdkTestObj.getResult())
	details = tdkTestObj.getResultDetails();
        orgValue.append( details.split("VALUE:")[1].split(' ')[0] );

    getFlag = 1;
    for index in range(len(getList)):
	if expectedresult not in actualresult_get[index]:
	    getFlag = 0;
	    break;

    if getFlag == 1:
        tdkTestObj.setResultStatus("SUCCESS");
        print "TEST STEP 1: Get the current KeyPassphrase, SSID, security mode"
        print "EXPECTED RESULT 1: Should retrieve the current KeyPassphrase, SSID, security mode"
        print "ACTUAL RESULT 1: %s" %details;
        #Get the result of execution
        print "[TEST EXECUTION RESULT] : %s" %actualresult_get[0] ;

        tdkTestObj = obj.createTestStep("WIFIAgent_Set_Get");
        tdkTestObj.addParameter("paramName","Device.WiFi.AccessPoint.2.Security.KeyPassphrase")
        tdkTestObj.addParameter("paramValue","wifitest");
        tdkTestObj.addParameter("paramType","string");
        expectedresult="SUCCESS";
        tdkTestObj.executeTestCase(expectedresult);
        actualresult = tdkTestObj.getResult();
        details = tdkTestObj.getResultDetails();
        if expectedresult in actualresult:
            #Set the result status of execution
            tdkTestObj.setResultStatus("SUCCESS");
            print "TEST STEP 2: Set a new passphrase";
            print "EXPECTED RESULT 2: Should set the the new passphrase"
            print "ACTUAL RESULT 2: %s" %details;
            #Get the result of execution
            print "[TEST EXECUTION RESULT] : %s" %actualresult;

            #Do a factor reset of the wifi settings
            tdkTestObj = obj.createTestStep("WIFIAgent_Set");
            tdkTestObj.addParameter("paramName","Device.WiFi.X_CISCO_COM_FactoryReset");
            tdkTestObj.addParameter("paramValue","true");
            tdkTestObj.addParameter("paramType","bool");
            expectedresult="SUCCESS";
            tdkTestObj.executeTestCase(expectedresult);
            actualresult = tdkTestObj.getResult();
            if expectedresult in actualresult:
                #Set the result status of execution
                tdkTestObj.setResultStatus("SUCCESS");
                details = tdkTestObj.getResultDetails();
                print "EXPECTED RESULT 4: Should set the Factory Reset value to true";
                print "ACTUAL RESULT 4: %s" %details;
                #Get the result of execution
                print "[TEST EXECUTION RESULT] : %s" %actualresult;
                print "Factory Reset Function is SUCCESS"
                time.sleep(180);

    	        #check passphrase after reset
                tdkTestObj = obj.createTestStep('WIFIAgent_Get');
                tdkTestObj.addParameter("paramName","Device.WiFi.AccessPoint.2.Security.KeyPassphrase")
                tdkTestObj.executeTestCase("expectedresult");
                actualresult = tdkTestObj.getResult();
                details = tdkTestObj.getResultDetails();
                resetPass = details.split("VALUE:")[1].split(' ')[0];

                if expectedresult in actualresult and resetPass != "wifitest":
                    tdkTestObj.setResultStatus("SUCCESS");
                    print "TEST STEP 1: Check if passphrase got changed after reset"
                    print "EXPECTED RESULT 1: passphrase should change after reset"
                    print "ACTUAL RESULT 1: Status is %s " %details
                    #Get the result of execution
                    print "[TEST EXECUTION RESULT] : SUCCESS";
                else:
                    tdkTestObj.setResultStatus("FAILURE");
                    print "TEST STEP 1: Check if passphrase got changed after reset"
                    print "EXPECTED RESULT 1: passphrase should change after reset"
                    print "ACTUAL RESULT 1: Status is %s " %details;
                    #Get the result of execution
                    print "[TEST EXECUTION RESULT] : FAILURE";
            else:
                tdkTestObj.setResultStatus("FAILURE");
                print "EXPECTED RESULT 4: Should set the Factory Reset value to true";
                print "ACTUAL RESULT 4: %s" %details;
                #Get the result of execution
                print "[TEST EXECUTION RESULT] : %s" %actualresult;
                print "Factory Reset Function is FAILURE"

	    #change passphrase to its original value
            tdkTestObj = obj.createTestStep("WIFIAgent_SetMultiple");
            tdkTestObj.addParameter("paramList","Device.WiFi.AccessPoint.1.Security.KeyPassphrase|%s|string|Device.WiFi.AccessPoint.2.Security.KeyPassphrase|%s|string|Device.WiFi.SSID.1.SSID|%s|string|Device.WiFi.SSID.2.SSID|%s|string|Device.WiFi.AccessPoint.1.Security.ModeEnabled|%s|string|Device.WiFi.AccessPoint.2.Security.ModeEnabled|%s|string" %(orgValue[0],orgValue[1],orgValue[2],orgValue[3],orgValue[4],orgValue[5]));
            expectedresult="SUCCESS";
            tdkTestObj.executeTestCase(expectedresult);
            actualresult = tdkTestObj.getResult();
            if expectedresult in actualresult:
                #Set the result status of execution
                tdkTestObj.setResultStatus("SUCCESS");
                details = tdkTestObj.getResultDetails();
                print "EXPECTED RESULT 4: Should set the original passphrase, SSID, security mode";
                print "ACTUAL RESULT 4: %s" %details;
                #Get the result of execution
                print "[TEST EXECUTION RESULT] : %s" %actualresult;
	    else:
                tdkTestObj.setResultStatus("FAILURE");
                details = tdkTestObj.getResultDetails();
                print "EXPECTED RESULT 4: Should set the original passphrase, SSID, security mode";
                print "ACTUAL RESULT 4: %s" %details;
                #Get the result of execution
                print "[TEST EXECUTION RESULT] : %s" %actualresult;
	else:
	    tdkTestObj.setResultStatus("FAILURE");
            print "TEST STEP 2: Set a new passphrase";
            print "EXPECTED RESULT 2: Should set the the new passphrase"
            print "ACTUAL RESULT 2: %s" %details;
            #Get the result of execution
            print "[TEST EXECUTION RESULT] : %s" %actualresult;
    else:
	tdkTestObj.setResultStatus("FAILURE");
        print "TEST STEP 1: Get the current KeyPassphrase, SSID, security mode"
        print "EXPECTED RESULT 1: Should retrieve the current KeyPassphrase, SSID, security mode"
        print "ACTUAL RESULT 1: %s" %details;
        #Get the result of execution
        print "[TEST EXECUTION RESULT] : %s" %actualresult_get[0] ;

    obj.unloadModule("wifiagent");

else:
        print "Failed to load wifi module";
        obj.setLoadModuleStatus("FAILURE");
        print "Module loading failed";
