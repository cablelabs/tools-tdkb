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
<?xml version='1.0' encoding='utf-8'?>
<xml>
  <id></id>
  <!-- Do not edit id. This will be auto filled while exporting. If you are adding a new script keep the id empty -->
  <version>3</version>
  <!-- Do not edit version. This will be auto incremented while updating. If you are adding a new script you can keep the vresion as 1 -->
  <name>E2E_Firewall_High_TelnetFromWlanToWan</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id> </primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>tdkb_e2e_SetMultipleParams</primitive_test_name>
  <!--  -->
  <primitive_test_version>2</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>Verify that when Firewall Config is set to High Telnet access from WLAN to WAN should be blocked</synopsis>
  <!--  -->
  <groups_id />
  <!--  -->
  <execution_time>15</execution_time>
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
    <test_case_id>TC_TDKB_E2E_69</test_case_id>
    <test_objective>Verify that when Firewall Config is set to High Telnet from WLAN to WAN should be blocked</test_objective>
    <test_type>Negative</test_type>
    <test_setup>Broadband,Emulator,RPI</test_setup>
    <pre_requisite>Ensure the client setup is up with the IP address assigned by the gateway</pre_requisite>
    <api_or_interface_used>tdkb_e2e_Set</api_or_interface_used>
    <input_parameters>Device.WiFi.Radio.1.Enable
Device.WiFi.SSID.1.SSID
Device.WiFi.AccessPoint.1.Security.KeyPassphrase
Device.X_CISCO_COM_Security.Firewall.FirewallLevel</input_parameters>
    <automation_approch>1. Load tdkb_e2e module
2. Using tdkb_e2e_Get, get and save firewall level
3. Set the firewall level to High using tdkb_e2e_SetMultipleParams
4. Connect to Wifi client to GW SSID and check whether it is assigned a valid ip by the GW
5. From the wlan client, do TELNET to the WAN client and check whether telnet is blocked when the firewall level is set to High
6. Revert the firewall level to original value
7.Unload tdkb_e2e module</automation_approch>
    <except_output>Telnet from WLAN to WAN should fail</except_output>
    <priority>High</priority>
    <test_stub_interface>tdkb_e2e</test_stub_interface>
    <test_script>E2E_Firewall_High_TelnetFromWlanToWan</test_script>
    <skipped>No</skipped>
    <release_version>M54</release_version>
    <remarks>WAN,WLAN</remarks>
  </test_cases>
  <script_tags />
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
obj.configureTestCase(ip,port,'E2E_Firewall_High_TelnetFromWlanToWan');

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
        ssidName = "Device.WiFi.SSID.%s.SSID" %tdkbE2EUtility.ssid_2ghz_index
        keyPassPhrase = "Device.WiFi.AccessPoint.%s.Security.KeyPassphrase" %tdkbE2EUtility.ssid_2ghz_index
        radioEnable = "Device.WiFi.Radio.%s.Enable" %tdkbE2EUtility.ssid_2ghz_index
        firewallLevel = "Device.X_CISCO_COM_Security.Firewall.FirewallLevel"

        #Get the value of the wifi parameters that are currently set.
        paramList=[ssidName,keyPassPhrase,radioEnable]
        tdkTestObj,status,orgValue = getMultipleParameterValues(obj,paramList)
        tdkTestObj1,retStatus,firewallValue = getParameterValue(obj,firewallLevel)
        print "Firewall Level: %s" %firewallValue;

        if expectedresult in status and expectedresult in retStatus:
            tdkTestObj.setResultStatus("SUCCESS");
            print "TEST STEP 1: Get the current ssid,keypassphrase,Radio enable status,firewall level"
            print "EXPECTED RESULT 1: Should retrieve the current ssid,keypassphrase,Radio enable status,firewall level"
            print "ACTUAL RESULT 1: %s %s" %(orgValue,firewallValue);
            print "[TEST EXECUTION RESULT] : SUCCESS";

            # Set the SSID name,password,Radio enable status and firewall level"
            setValuesList = [tdkbE2EUtility.ssid_2ghz_name,tdkbE2EUtility.ssid_2ghz_pwd,'true'];
            print "Parameter values that are set: %s" %setValuesList

            list1 = [ssidName,tdkbE2EUtility.ssid_2ghz_name,'string']
            list2 = [keyPassPhrase,tdkbE2EUtility.ssid_2ghz_pwd,'string']
            list3 = [radioEnable,'true','bool']

            firewallParam = "%s|High|string" %firewallLevel

            #Concatenate the lists with the elements separated by pipe
            setParamList = list1 + list2 + list3
            setParamList = "|".join(map(str, setParamList))

            tdkTestObj,actualresult,details = setMultipleParameterValues(obj,setParamList)
            tdkTestObj,firewallResult,details = setMultipleParameterValues(obj,firewallParam)
            if expectedresult in actualresult and expectedresult in firewallResult:
                tdkTestObj.setResultStatus("SUCCESS");
                print "TEST STEP 2: Set the ssid,keypassphrase,Radio enable status,firewall level"
                print "EXPECTED RESULT 2: Should set the ssid,keypassphrase,Radio enable status,firewall level";
                print "ACTUAL RESULT 2: %s" %details;
                print "[TEST EXECUTION RESULT] : SUCCESS";

                #Retrieve the values after set and compare
                newParamList=[ssidName,keyPassPhrase,radioEnable]
                tdkTestObj,status,newValues = getMultipleParameterValues(obj,newParamList)

                tdkTestObj1,retStatus,newFirewallValue = getParameterValue(obj,firewallLevel)
                print "Firewall Level: %s" %newFirewallValue;

                if expectedresult in status and expectedresult in retStatus and setValuesList == newValues and newFirewallValue == "High":
                    tdkTestObj.setResultStatus("SUCCESS");
                    print "TEST STEP 3: Get the current ssid,keypassphrase,Radio enable status,firewall level"
                    print "EXPECTED RESULT 3: Should retrieve the current ssid,keypassphrase,Radio enable status,firewall level"
                    print "ACTUAL RESULT 3: %s %s" %(newValues,newFirewallValue);
                    print "[TEST EXECUTION RESULT] : SUCCESS";

                    #Wait for the changes to reflect in client device
                    time.sleep(60);

                    #Connect to the wifi ssid from wlan client
                    print "TEST STEP 4: From wlan client, Connect to the wifi ssid"
                    status = wlanConnectWifiSsid(tdkbE2EUtility.ssid_2ghz_name,tdkbE2EUtility.ssid_2ghz_pwd,tdkbE2EUtility.wlan_2ghz_interface);
                    if expectedresult in status:
                        tdkTestObj.setResultStatus("SUCCESS");

                        print "TEST STEP 5: Get the IP address of the wlan client after connecting to wifi"
                        wlanIP = getWlanIPAddress(tdkbE2EUtility.wlan_2ghz_interface);
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
		   		    print "wlan ip address is in same DHCP range"

				    #set new static route to wan client
				    status = addStaticRoute(tdkbE2EUtility.wan_ip, curIPAddress,tdkbE2EUtility.wlan_2ghz_interface);
		                    if expectedresult in status:
					    print "TEST STEP 8:Static route add success"

                        	            tdkTestObj.setResultStatus("SUCCESS");
                                            print "TEST STEP 10:Check the Telnet from WLAN to LAN"
                                            status = telnetToClient("WAN",tdkbE2EUtility.wan_ip,"WLAN");	    
                                            if expectedresult not in status:
                                                tdkTestObj.setResultStatus("SUCCESS");
                                                print "SUCCESS: Telnet from WLAN to LAN is blocked"

                                            else:
                                                tdkTestObj.setResultStatus("FAILURE");
                                                print "TEST STEP 10: failed, Telnet from WLAN to LAN not blocked"

                                            print "TEST STEP 11: From wlan client, Disconnect from the wifi ssid"
                                            status = wlanDisconnectWifiSsid(tdkbE2EUtility.wlan_2ghz_interface);
                                            if expectedresult in status:
                                                    tdkTestObj.setResultStatus("SUCCESS");
                                                    finalStatus = "SUCCESS";
                                                    print "Disconnect from WIFI SSID: SUCCESS"
                                            else:
                                                    tdkTestObj.setResultStatus("FAILURE");
                                                    print "TEST STEP 11:Disconnect from WIFI SSID: FAILED"
				    else:
					tdkTestObj.setResultStatus("FAILURE");
					print "TEST STEP 8:Static route add failed"
                                else:
                                     tdkTestObj.setResultStatus("FAILURE");
                                     print "TEST STEP 9:WLAN Client IP address is not in the same Gateway DHCP range"
                            else:
                                  tdkTestObj.setResultStatus("FAILURE");
                                  print "TEST STEP 8:Failed to get the WLAN Client IP address"
                        else:
                                    tdkTestObj.setResultStatus("FAILURE");
                                    print "TEST STEP 7:Failed to connect to WIFI SSID"
                    else:
                        tdkTestObj.setResultStatus("FAILURE");
                        print "TEST STEP 4:Failed to get the Gateway IP address"
                else:
                    tdkTestObj.setResultStatus("FAILURE");
                    print "TEST STEP 3: Get the current ssid,keypassphrase,Radio enable status,firewall level"
                    print "EXPECTED RESULT 3: Should retrieve the current ssid,keypassphrase,Radio enable status,firewall level"
                    print "ACTUAL RESULT 3: %s %s" %(newValues,newFirewallValue);
                    print "[TEST EXECUTION RESULT] : FAILURE";
            else:
                tdkTestObj.setResultStatus("FAILURE");
                details = tdkTestObj.getResultDetails();
                print "TEST STEP 2: Set the ssid,keypassphrase,Radio enable status,firewall level"
                print "EXPECTED RESULT 2: Should set the ssid,keypassphrase,Radio enable status,firewall level";
                print "ACTUAL RESULT 2: %s" %details;
                print "[TEST EXECUTION RESULT] : FAILURE";

            #Prepare the list of parameter values to be reverted
            list1 = [ssidName,orgValue[0],'string']
            list2 = [keyPassPhrase,orgValue[1],'string']
            list3 = [radioEnable,orgValue[2],'bool']

            #Concatenate the lists with the elements separated by pipe
            revertParamList = list1 + list2 + list3
            revertParamList = "|".join(map(str, revertParamList))

            firewallParam = "%s|%s|string" %(firewallLevel,firewallValue)

            #Revert the values to original
            tdkTestObj,actualresult,details = setMultipleParameterValues(obj,revertParamList)
            tdkTestObj,firewallResult,details = setMultipleParameterValues(obj,firewallParam)
            if expectedresult in actualresult and expectedresult in firewallResult and expectedresult in finalStatus:
                tdkTestObj.setResultStatus("SUCCESS");
                print "EXPECTED RESULT 12: Should set the original ssid,keypassphrase,Radio enable status,firewall level";
                print "ACTUAL RESULT 12: %s" %details;
                print "[TEST EXECUTION RESULT] : SUCCESS";
            else:
                tdkTestObj.setResultStatus("FAILURE");
                details = tdkTestObj.getResultDetails();
                print "EXPECTED RESULT 12: Should set the original ssid,keypassphrase,Radio enable status,firewall level";
                print "ACTUAL RESULT 12: %s" %details;
                print "[TEST EXECUTION RESULT] : FAILURE";
        else:
            tdkTestObj.setResultStatus("FAILURE");
            print "TEST STEP 1: Get the current ssid,keypassphrase,Radio enable status,firewall level"
            print "EXPECTED RESULT 1: Should retrieve the current ssid,keypassphrase,Radio enable status,firewall level"
            print "ACTUAL RESULT 1: %s %s" %(orgValue,firewallValue);
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
