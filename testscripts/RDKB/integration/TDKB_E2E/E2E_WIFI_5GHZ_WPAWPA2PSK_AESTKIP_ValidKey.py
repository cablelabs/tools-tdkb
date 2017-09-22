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
<?xml version="1.0" encoding="UTF-8"?><xml>
  <id/>
  <version>2</version>
  <name>E2E_WIFI_5GHZ_WPAWPA2PSK_AESTKIP_ValidKey</name>
  <primitive_test_id/>
  <primitive_test_name>tdkb_e2e_Get</primitive_test_name>
  <primitive_test_version>2</primitive_test_version>
  <status>FREE</status>
  <synopsis>Verify whether WG supports WPAWPA2-PSK (TKIP/AES)á encryption security mechanism using valid key for 5GHZ SSID. Ensure that client should be able to connect to WG</synopsis>
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
    <test_case_id>TC_TDKB_E2E_17</test_case_id>
    <test_objective>Verify whether WG supports WPAWPA2-PSK (TKIP/AES)Ã&#131;Â¡ encryption security mechanism using valid key for 5GHZ SSID. Ensure that client should be able to connect to WG</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Broadband,Emulator,RPI</test_setup>
    <pre_requisite>Ensure the WIFI client setup is ready and WIFI client is listing the SSIDs properly.</pre_requisite>
    <api_or_interface_used>None</api_or_interface_used>
    <input_parameters>Device.WiFi.Radio.2.Enable
Device.WiFi.AccessPoint.2.Security.X_CISCO_COM_EncryptionMethod
Device.WiFi.AccessPoint.2.Security.ModeEnabled
Device.WiFi.AccessPoint.2.Security.KeyPassphrase</input_parameters>
    <automation_approch>1. Load tdkb_e2e module
2. Using tdkb_e2e_Get, get and save encryption method and security mode
3. Set encryption method and security mode to AES+TKIP and WPA-WPA2-Personal using tdkb_e2e_SetMultipleParams
3. Try to connect to Wifi client and check whether the wifi client is connected to the DUT using AES+TKIP and WPA-WPA2-Personal and valid wifi password
4. Revert the values of encryption method and security mode</automation_approch>
    <except_output>WIFI client should be able to connect to the DUT with the using AES+TKIP encryption method and WPA-WPA2-Personal security mode and valid wifi password</except_output>
    <priority>High</priority>
    <test_stub_interface>tdkb_e2e</test_stub_interface>
    <test_script>E2E_WIFI_5GHZ_WPAWPA2PSK_AESTKIP_ValidKey</test_script>
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

obj.configureTestCase(ip,port,'E2E_WIFI_5GHZ_WPAWPA2PSK_AESTKIP_ValidKey');

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
        ssidName = "Device.WiFi.SSID.%s.SSID" %tdkbE2EUtility.ssid_5ghz_index
        keyPassPhrase = "Device.WiFi.AccessPoint.%s.Security.KeyPassphrase" %tdkbE2EUtility.ssid_5ghz_index
        radioEnable = "Device.WiFi.Radio.%s.Enable" %tdkbE2EUtility.radio_5ghz_index
        encryptionMethod = "Device.WiFi.AccessPoint.%s.Security.X_CISCO_COM_EncryptionMethod" %tdkbE2EUtility.ssid_5ghz_index
        securityMode = "Device.WiFi.AccessPoint.%s.Security.ModeEnabled" %tdkbE2EUtility.ssid_5ghz_index
        
        #Get the value of the wifi parameters that are currently set.
        paramList=[ssidName,keyPassPhrase,radioEnable,encryptionMethod,securityMode]
        tdkTestObj,status,orgValue = getMultipleParameterValues(obj,paramList)

        if expectedresult in status:
            tdkTestObj.setResultStatus("SUCCESS");
            print "TEST STEP 1: Get the current SSID, KeyPassphrase, Radio status, encryption method, security mode"
            print "EXPECTED RESULT 1: Should retrieve the current SSID, KeyPassphrase, Radio status, encryption method, security mode"
            print "ACTUAL RESULT 1: %s" %orgValue;
            print "[TEST EXECUTION RESULT] : %s" %status;

            # Set the security mode as WPA-WPA2-PSK and encryption method as "AES+TKIP"
            setValuesList = ['true',tdkbE2EUtility.ssid_5ghz_name,'AES+TKIP','WPA-WPA2-Personal',tdkbE2EUtility.ssid_5ghz_pwd];
            print "WIFI parameter values that are set: %s" %setValuesList

            list1 = [radioEnable,'true','boolean']
            list2 = [ssidName,tdkbE2EUtility.ssid_5ghz_name,'string']
            list3 = [encryptionMethod,'AES+TKIP','string']
            list4 = [securityMode,'WPA-WPA2-Personal','string']
            list5 = [keyPassPhrase,tdkbE2EUtility.ssid_5ghz_pwd,'string']

            #Concatenate the lists with the elements separated by pipe
            setParamList = list1 + list2 + list3 + list4 + list5
            setParamList = "|".join(map(str, setParamList))
            
            tdkTestObj,actualresult,details = setMultipleParameterValues(obj,setParamList)
            if expectedresult in actualresult:
                tdkTestObj.setResultStatus("SUCCESS");
                print "TEST STEP 2: Set the SSID, KeyPassphrase, Radio status, encryption method, security mode"
                print "EXPECTED RESULT 2: Should set the SSID, KeyPassphrase, Radio status, encryption method, security mode";
                print "ACTUAL RESULT 2: %s" %details;
                print "[TEST EXECUTION RESULT] : %s" %actualresult;

                #Retrieve the values after set and compare
                newParamList=[radioEnable,ssidName,encryptionMethod,securityMode,keyPassPhrase]
                tdkTestObj,status,newValues = getMultipleParameterValues(obj,newParamList)
                
                if expectedresult in status and setValuesList == newValues:
                    tdkTestObj.setResultStatus("SUCCESS");
                    print "TEST STEP 3: Get the current SSID, KeyPassphrase, Radio status, encryption method, security mode"
                    print "EXPECTED RESULT 3: Should retrieve the current SSID, KeyPassphrase, Radio status, encryption method, security mode"
                    print "ACTUAL RESULT 3: %s" %newValues;
                    print "[TEST EXECUTION RESULT] : %s" %status;

                    #Wait for the changes to reflect in client device
                    time.sleep(60);

                    #Connect to the wifi ssid from wlan client
                    print "TEST STEP 4: From wlan client, Connect to the wifi ssid"
                    status = wlanConnectWifiSsid(tdkbE2EUtility.ssid_5ghz_name,tdkbE2EUtility.ssid_5ghz_pwd,tdkbE2EUtility.wlan_5ghz_interface);
                    if expectedresult in status:
                        tdkTestObj.setResultStatus("SUCCESS");

                        print "TEST STEP 5: Get the IP address of the wlan client after connecting to wifi"
                        wlanIP = getWlanIPAddress(tdkbE2EUtility.wlan_5ghz_interface);
                        if wlanIP:
                            tdkTestObj.setResultStatus("SUCCESS");

                            print "TEST STEP 6: Get the current LAN IP address DHCP range"
                            param = "Device.X_CISCO_COM_DeviceControl.LanManagementEntry.1.LanIPAddress"
                            tdkTestObj,status,curIPAddress = getParameterValue(obj,param)
                            print "LAN IP Address: %s" %curIPAddress;
                            
                            if expectedresult in status and curIPAddress:
                                tdkTestObj.setResultStatus("SUCCESS");
                                
                                print "TEST STEP 7: Check whether wlan ip address is in same DHCP range"
                                status = "SUCCESS"
                                status = checkIpRange(curIPAddress,wlanIP);
                                if expectedresult in status:
                                    tdkTestObj.setResultStatus("SUCCESS");

                                    print "TEST STEP 8: Check whether wlan client connected with WPA2-Personal or WPA-Personal"
                                    security_mode = getSecurityMode(tdkbE2EUtility.ssid_5ghz_name);
                                    security_mode_list = ['WPA2-Personal','WPA-Personal']
                                    if security_mode in security_mode_list:
                                        tdkTestObj.setResultStatus("SUCCESS");

                                        print "TEST STEP 9: From wlan client, Disconnect from the wifi ssid"
                                        status = wlanDisconnectWifiSsid(tdkbE2EUtility.wlan_5ghz_interface);
                                        if expectedresult in status:
                                            tdkTestObj.setResultStatus("SUCCESS");
                                            finalStatus = "SUCCESS"
                                        else:
                                            tdkTestObj.setResultStatus("FAILURE");
                                    else:
                                        tdkTestObj.setResultStatus("FAILURE");
                                else:
                                        tdkTestObj.setResultStatus("FAILURE");
                            else:
                                tdkTestObj.setResultStatus("FAILURE");
                        else:
                            tdkTestObj.setResultStatus("FAILURE");
                    else:
                        tdkTestObj.setResultStatus("FAILURE");           
                else:
                    tdkTestObj.setResultStatus("FAILURE");
                    print "TEST STEP 3: Get the current SSID, KeyPassphrase, Radio status, encryption method, security mode"
                    print "EXPECTED RESULT 3: Should retrieve the current SSID, KeyPassphrase, Radio status, encryption method, security mode"
                    print "ACTUAL RESULT 3: %s" %newValues;
                    print "[TEST EXECUTION RESULT] : %s" %status;
            else:
                tdkTestObj.setResultStatus("FAILURE");
                details = tdkTestObj.getResultDetails();
                print "TEST STEP 2: Set the SSID, KeyPassphrase, Radio status, encryption method, security mode"
                print "EXPECTED RESULT 2: Should set the SSID, KeyPassphrase, Radio status, encryption method, security mode";
                print "ACTUAL RESULT 2: %s" %details;
                print "[TEST EXECUTION RESULT] : %s" %actualresult;

            #Prepare the list of parameter values to be reverted
            list1 = [ssidName,orgValue[0],'string']
            list2 = [keyPassPhrase,orgValue[1],'string']
            list3 = [radioEnable,orgValue[2],'boolean']
            list4 = [encryptionMethod,orgValue[3],'string']
            list5 = [securityMode,orgValue[4],'string']

            #Concatenate the lists with the elements separated by pipe
            revertParamList = list1 + list2 + list3 + list4 + list5
            revertParamList = "|".join(map(str, revertParamList))

            #Revert the values to original
            tdkTestObj,actualresult,details = setMultipleParameterValues(obj,revertParamList)
            if expectedresult in actualresult and expectedresult in finalStatus:
                tdkTestObj.setResultStatus("SUCCESS");
                print "EXPECTED RESULT 10: Should set the original SSID, KeyPassphrase, Radio status, encryption method, security mode";
                print "ACTUAL RESULT 10: %s" %details;
                print "[TEST EXECUTION RESULT] : %s" %actualresult;
            else:
                tdkTestObj.setResultStatus("FAILURE");
                details = tdkTestObj.getResultDetails();
                print "EXPECTED RESULT 10: Should set the original SSID, KeyPassphrase, Radio status, encryption method, security mode";
                print "ACTUAL RESULT 10: %s" %details;
                print "[TEST EXECUTION RESULT] : %s" %actualresult;
        else:
            tdkTestObj.setResultStatus("FAILURE");
            print "TEST STEP 1: Get the current SSID, KeyPassphrase, Radio status, encryption method, security mode"
            print "EXPECTED RESULT 1: Should retrieve the current SSID, KeyPassphrase, Radio status, encryption method, security mode"
            print "ACTUAL RESULT 1: %s" %orgValue;
            print "[TEST EXECUTION RESULT] : %s" %status;
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
