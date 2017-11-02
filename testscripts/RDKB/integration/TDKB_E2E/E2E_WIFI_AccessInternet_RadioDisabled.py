##########################################################################
# If not stated otherwise in this file or this component's Licenses.txt
# file the following copyright and licenses apply:
#
# Copyright 2017 RDK Management
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
<?xml version="1.0" encoding="UTF-8"?>
<xml>
  <id/>
  <version>2</version>
  <name>E2E_WIFI_AccessInternet_RadioDisabled</name>
  <primitive_test_id/>
  <primitive_test_name>tdkb_e2e_Set</primitive_test_name>
  <primitive_test_version>2</primitive_test_version>
  <status>FREE</status>
  <synopsis>Verify that when both WIFI Radios are disabled in WG wireless client should not be able to connect to WG and access internet</synopsis>
  <groups_id/>
  <execution_time>15</execution_time>
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
    <test_case_id>TC_TDKB_E2E_36</test_case_id>
    <test_objective>Verify that when both WIFI Radios are disabled in WG wireless client should not be able to connect to WG and access internet</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Broadband,Emulator,RPI</test_setup>
    <pre_requisite>1.Ccsp Components in DUT should be in a running state that includes component under test Cable Modem
2.TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>None</api_or_interface_used>
    <input_parameters>Device.WiFi.Radio.1.Enable : false
Device.WiFi.Radio.2.Enable : false</input_parameters>
    <automation_approch>1. Load tdkb_e2e module
2. Using tdkb_e2e_Get, get and save Radio enable status of 2.4GHz and 5GHz
3. Set Radio.1.Enable to falseand Radio.2.Enable to false using tdkb_e2e_SetMultipleParams
3. Try to connect to 2.4GHZ and 5GHz from WIFI client 
4. Revert the values of Radio enable</automation_approch>
    <except_output>Wifi client should not be able to connect to 2.4Ghz or 5GHZ since radio interface is disabled</except_output>
    <priority>High</priority>
    <test_stub_interface>tdkb_e2e</test_stub_interface>
    <test_script>E2E_WIFI_AccessInternet_RadioDisabled</test_script>
    <skipped>No</skipped>
    <release_version/>
    <remarks/>
  </test_cases>
  <script_tags/>
</xml>

'''
# use tdklib library,which provides a wrapper for tdk testcase script 
import tdklib; 
import time;
import tdkbE2EUtility
from tdkbE2EUtility import *;

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("tdkb_e2e","1");

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'E2E_WIFI_AccessInternet_RadioDisabled');

#Get the result of connection with test component
loadmodulestatus =obj.getLoadModuleResult();
print "[LIB LOAD STATUS]  :  %s" %loadmodulestatus ;

if "SUCCESS" in loadmodulestatus.upper():
    obj.setLoadModuleStatus("SUCCESS");
    expectedresult = "SUCCESS"
    finalStatus = "FAILURE"

    #Parse the device configuration file
    status = parseDeviceConfig(obj);
    if expectedresult in status:
        obj.setLoadModuleStatus("SUCCESS");
        print "Parsed the device configuration file successfully"

        #Assign the WIFI parameters names to a variable
        ssidName_2ghz = "Device.WiFi.SSID.%s.SSID" %tdkbE2EUtility.ssid_2ghz_index
        keyPassPhrase_2ghz = "Device.WiFi.AccessPoint.%s.Security.KeyPassphrase" %tdkbE2EUtility.ssid_2ghz_index
	RadioEnable_2ghz = "Device.WiFi.Radio.%s.Enable" %tdkbE2EUtility.ssid_2ghz_index
        ssidName_5ghz = "Device.WiFi.SSID.%s.SSID" %tdkbE2EUtility.ssid_5ghz_index
        keyPassPhrase_5ghz = "Device.WiFi.AccessPoint.%s.Security.KeyPassphrase" %tdkbE2EUtility.ssid_5ghz_index
        RadioEnable_5ghz = "Device.WiFi.Radio.%s.Enable" %tdkbE2EUtility.ssid_5ghz_index

        #Get the value of the wifi parameters that are currently set.
        paramList=[ssidName_2ghz,keyPassPhrase_2ghz,RadioEnable_2ghz,ssidName_5ghz,keyPassPhrase_5ghz,RadioEnable_5ghz]
        tdkTestObj,status,orgValue = getMultipleParameterValues(obj,paramList)
        if expectedresult in status:
            tdkTestObj.setResultStatus("SUCCESS");
            print "TEST STEP 1: Get the current ssid,keypassphrase,Radio enable status for 2ghz and 5ghz"
            print "EXPECTED RESULT 1: Should retrieve the current ssid,keypassphrase,Radio enable status for 2ghz and 5ghz"
            print "ACTUAL RESULT 1: %s" %orgValue;
            print "[TEST EXECUTION RESULT] : SUCCESS";

            # Set the SSID name,password,Radio enable status for 2ghz and 5ghz"
            setValuesList = [tdkbE2EUtility.ssid_2ghz_name,tdkbE2EUtility.ssid_2ghz_pwd,'false',tdkbE2EUtility.ssid_5ghz_name,tdkbE2EUtility.ssid_5ghz_pwd,'false'];
            print "WIFI parameter values that are set: %s" %setValuesList

            list1 = [ssidName_2ghz,tdkbE2EUtility.ssid_2ghz_name,'string']
            list2 = [keyPassPhrase_2ghz,tdkbE2EUtility.ssid_2ghz_pwd,'string']
	    list3 = [RadioEnable_2ghz,'false','bool']
	    list4 = [ssidName_5ghz,tdkbE2EUtility.ssid_5ghz_name,'string']
            list5 = [keyPassPhrase_5ghz,tdkbE2EUtility.ssid_5ghz_pwd,'string']
            list6 = [RadioEnable_5ghz,'false','bool']

            #Concatenate the lists with the elements separated by pipe
            setParamList = list1 + list2 + list3 + list4 + list5 + list6
            setParamList = "|".join(map(str, setParamList))

            tdkTestObj,actualresult,details = setMultipleParameterValues(obj,setParamList)
            if expectedresult in actualresult:
                tdkTestObj.setResultStatus("SUCCESS");
                print "TEST STEP 2: Set the ssid,keypassphrase,Radio enable status for 2ghz and 5ghz"
                print "EXPECTED RESULT 2: Should set the ssid,keypassphrase,Radio enable status for 2ghz and 5ghz";
                print "ACTUAL RESULT 2: %s" %details;
                print "[TEST EXECUTION RESULT] : SUCCESS";

                #Retrieve the values after set and compare
                newParamList=[ssidName_2ghz,keyPassPhrase_2ghz,RadioEnable_2ghz,ssidName_5ghz,keyPassPhrase_5ghz,RadioEnable_5ghz]
                tdkTestObj,status,newValues = getMultipleParameterValues(obj,newParamList)
                if expectedresult in status and setValuesList == newValues:
                    tdkTestObj.setResultStatus("SUCCESS");
                    print "TEST STEP 3: Get the current ssid,keypassphrase,Radio enable status for 2ghz and 5ghz"
                    print "EXPECTED RESULT 3: Should retrieve the current ssid,keypassphrase,Radio enable status for 2ghz and 5ghz"
                    print "ACTUAL RESULT 3: %s" %newValues;
                    print "[TEST EXECUTION RESULT] : SUCCESS";

                    #Wait for the changes to reflect in client device
                    time.sleep(60);

                    #Connect to the wifi ssid from wlan client
                    print "TEST STEP 4: From wlan client, Connect to the wifi ssid for 2.4ghz"
                    status = wlanConnectWifiSsid(tdkbE2EUtility.ssid_2ghz_name,tdkbE2EUtility.ssid_2ghz_pwd,tdkbE2EUtility.wlan_2ghz_interface);
                    if "SUCCESS" not in status:
                        tdkTestObj.setResultStatus("SUCCESS");

			print "TEST STEP 5: From wlan client, Connect to the wifi ssid for 5ghz"
                    	status = wlanConnectWifiSsid(tdkbE2EUtility.ssid_5ghz_name,tdkbE2EUtility.ssid_5ghz_pwd,tdkbE2EUtility.wlan_5ghz_interface);
                    	if "SUCCESS" not in status:
			    tdkTestObj.setResultStatus("SUCCESS");
                            finalStatus = "SUCCESS"
			else:
			    tdkTestObj.setResultStatus("FAILURE");
			    print "Connected to wifi ssid for 5ghz when radio.2 is disabled";
                    else:
                        tdkTestObj.setResultStatus("FAILURE");
			print "Connected to wifi ssid for 2.4ghz when radio.1 is disabled";
		    
                else:
                    tdkTestObj.setResultStatus("FAILURE");
                    print "TEST STEP 3: Get the current ssid,keypassphrase,Radio enable status for 2ghz and 5ghz"
                    print "EXPECTED RESULT 3: Should retrieve the current ssid,keypassphrase,Radio enable status for 2ghz and 5ghz"
                    print "ACTUAL RESULT 3: %s" %newValues;
                    print "[TEST EXECUTION RESULT] : FAILURE";
            else:
                tdkTestObj.setResultStatus("FAILURE");
                details = tdkTestObj.getResultDetails();
                print "TEST STEP 2: Set the ssid,keypassphrase,Radio enable status for 2ghz and 5ghz"
                print "EXPECTED RESULT 2: Should set the ssid,keypassphrase,Radio enable status for 2ghz and 5ghz";
                print "ACTUAL RESULT 2: %s" %details;
                print "[TEST EXECUTION RESULT] : FAILURE";

            #Prepare the list of parameter values to be reverted
            list1 = [ssidName_2ghz,orgValue[0],'string']
            list2 = [keyPassPhrase_2ghz,orgValue[1],'string']
            list3 = [RadioEnable_2ghz,orgValue[2],'bool']
	    list4 = [ssidName_5ghz,orgValue[3],'string']
            list5 = [keyPassPhrase_5ghz,orgValue[4],'string']
            list6 = [RadioEnable_5ghz,orgValue[5],'bool']

            #Concatenate the lists with the elements separated by pipe
            revertParamList = list1 + list2 + list3 + list4 + list5 + list6
            revertParamList = "|".join(map(str, revertParamList))

            #Revert the values to original
            tdkTestObj,actualresult,details = setMultipleParameterValues(obj,revertParamList)
            if expectedresult in actualresult and expectedresult in finalStatus:
                tdkTestObj.setResultStatus("SUCCESS");
                print "EXPECTED RESULT 6: Should set the original ssid,keypassphrase,Radio enable status for 2ghz and 5ghz";
                print "ACTUAL RESULT 6: %s" %details;
                print "[TEST EXECUTION RESULT] : SUCCESS";
            else:
                tdkTestObj.setResultStatus("FAILURE");
                details = tdkTestObj.getResultDetails();
                print "EXPECTED RESULT 6: Should set the original ssid,keypassphrase,Radio enable status for 2ghz and 5ghz";
                print "ACTUAL RESULT 6: %s" %details;
                print "[TEST EXECUTION RESULT] : FAILURE";
        else:
            tdkTestObj.setResultStatus("FAILURE");
            print "TEST STEP 1: Get the current ssid,keypassphrase,Radio enable status for 2ghz and 5ghz"
            print "EXPECTED RESULT 1: Should retrieve the current ssid,keypassphrase,Radio enable status for 2ghz and 5ghz"
            print "ACTUAL RESULT 1: %s" %orgValue;
            print "[TEST EXECUTION RESULT] : FAILURE";
    else:
        obj.setLoadModuleStatus("FAILURE");
        print "Failed to parse the device configuration file"

    #Handle any post execution cleanup required
    postExecutionCleanup();
    obj.unloadModule("tdkb_e2e");

else:
        print "Failed to load tdkb_e2e module";
        obj.setLoadModuleStatus("FAILURE");
        print "Module loading failed";
