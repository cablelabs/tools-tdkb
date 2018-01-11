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
  <name>E2E_DHCP_2.4GHZ_GetWlanIPAddress_OnActiveLease_WiFiReconnection</name>
  <primitive_test_id/>
  <primitive_test_name>tdkb_e2e_Set</primitive_test_name>
  <primitive_test_version>2</primitive_test_version>
  <status>FREE</status>
  <synopsis>Verify that Wi-Fi client retains the same IP address when disconnected and reconnected when the Lease period is active</synopsis>
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
    <test_case_id>TC_TDKB_E2E_177</test_case_id>
    <test_objective>Verify that Wi-Fi client retains the same IP address when disconnected and reconnected when the Lease period is active</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Broadband,Emulator,RPI</test_setup>
    <pre_requisite>Ensure the client setup is up with the IP address assigned by the gateway</pre_requisite>
    <api_or_interface_used>None</api_or_interface_used>
    <input_parameters>Device.WiFi.SSID.1.SSID
Device.WiFi.AccessPoint.1.Security.KeyPassphrase
Device.X_CISCO_COM_DeviceControl.LanManagementEntry.1.LanIPAddress
Device.X_CISCO_COM_DeviceControl.LanManagementEntry.1.LanSubnetMask
Device.DHCPv4.Server.Pool.1.MinAddress
Device.DHCPv4.Server.Pool.1.MaxAddress
Device.DHCPv4.Server.Pool.1.LeaseTime</input_parameters>
    <automation_approch>1. Load tdkb_e2e module
2. Using tdkb_e2e_Get, get and save LanIP,SubnetMask,Lease time, Maximum and minimum Address range
3. Set LanIP,SubnetMask,Lease Time, Maximum and minimum Address range using tdkb_e2e_SetMultipleParams
4. Connect to the WIFI client and check whether the IP obtained is in valid range
5. Disconnect from wifi ssid and reconnect to the same ssid. 
6.Check whether the IP obtained is same as the ip obtained previously
6. Revert the values to original value
7.Unload tdkb_e2e module</automation_approch>
    <except_output>Wi-Fi client should retain the same IP address when disconnected and reconnected when the Lease period is active</except_output>
    <priority>High</priority>
    <test_stub_interface>tdkb_e2e</test_stub_interface>
    <test_script>E2E_DHCP_2.4GHZ_GetWlanIPAddress_OnActiveLease_WiFiReconnection</test_script>
    <skipped>No</skipped>
    <release_version>M55</release_version>
    <remarks>WLAN</remarks>
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
obj.configureTestCase(ip,port,'E2E_DHCP_2.4GHZ_GetWlanIPAddress_OnActiveLease_WiFiReconnection');

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
        lanIPAddress = "Device.X_CISCO_COM_DeviceControl.LanManagementEntry.1.LanIPAddress"
        lanSubnetMask = "Device.X_CISCO_COM_DeviceControl.LanManagementEntry.1.LanSubnetMask"
        minAddress = "Device.DHCPv4.Server.Pool.1.MinAddress"
        maxAddress = "Device.DHCPv4.Server.Pool.1.MaxAddress"
	leaseTime = "Device.DHCPv4.Server.Pool.1.LeaseTime"

        #Get the value of the wifi parameters that are currently set.
        paramList=[ssidName,keyPassPhrase,lanIPAddress,lanSubnetMask,minAddress,maxAddress,leaseTime]
        tdkTestObj,status,orgValue = getMultipleParameterValues(obj,paramList)

        if expectedresult in status:
            tdkTestObj.setResultStatus("SUCCESS");
            print "TEST STEP 1: Get the current ssid,keypassphrase,lanIPAddress,lanSubnetMask,minAddress,maxAddress and leaseTime"
            print "EXPECTED RESULT 1: Should retrieve the current ssid,keypassphrase,lanIPAddress,lanSubnetMask,minAddress maxAddress and leaseTime"
            print "ACTUAL RESULT 1: %s" %orgValue;
            print "[TEST EXECUTION RESULT] : SUCCESS";

            # Set the SSID name,password,lanIPAddress,lanSubnetMask,minAddress and maxAddress"
            setValuesList = [tdkbE2EUtility.ssid_2ghz_name,tdkbE2EUtility.ssid_2ghz_pwd,'10.0.0.1','255.255.255.0','10.0.0.2','10.0.0.253','300'];
            print "Parameter values that are set: %s" %setValuesList

            list1 = [ssidName,tdkbE2EUtility.ssid_2ghz_name,'string']
            list2 = [keyPassPhrase,tdkbE2EUtility.ssid_2ghz_pwd,'string']

            list3 = [lanIPAddress,'10.0.0.1','string']
            list4 = [lanSubnetMask,'255.255.255.0','string']
            list5 = [minAddress,'10.0.0.2','string']
            list6 = [maxAddress,'10.0.0.253','string']
            list7 = [leaseTime,'300','int']

            #Concatenate the lists with the elements separated by pipe
            setParamList = list1 + list2
            setParamList = "|".join(map(str, setParamList))
            setParamList1= list3 + list4 + list5 + list6 + list7
            setParamList1 = "|".join(map(str, setParamList1))

            tdkTestObj,actualresult,details = setMultipleParameterValues(obj,setParamList)
            tdkTestObj,actualresult1,details = setMultipleParameterValues(obj,setParamList1)
            if expectedresult in actualresult and expectedresult in actualresult1:
                tdkTestObj.setResultStatus("SUCCESS");
                print "TEST STEP 2: Set the ssid,keypassphrase,lanIPAddress,lanSubnetMask,minAddress,maxAddress and leaseTime"
                print "EXPECTED RESULT 2: Should set the ssid,keypassphrase,lanIPAddress,lanSubnetMask,minAddress,maxAddress and leaseTime";
                print "ACTUAL RESULT 2: %s" %details;
                print "[TEST EXECUTION RESULT] : SUCCESS";

                #Retrieve the values after set and compare
                newParamList=[ssidName,keyPassPhrase,lanIPAddress,lanSubnetMask,minAddress,maxAddress,leaseTime]
                tdkTestObj,status,newValues = getMultipleParameterValues(obj,newParamList)

                if expectedresult in status and setValuesList == newValues:
                    tdkTestObj.setResultStatus("SUCCESS");
                    print "TEST STEP 3: Get the current ssid,keypassphrase,lanIPAddress,lanSubnetMask,minAddress,maxAddress and leaseTime"
                    print "EXPECTED RESULT 3: Should retrieve the current ssid,keypassphrase,lanIPAddress,lanSubnetMask,minAddress,maxAddress and leaseTime"
                    print "ACTUAL RESULT 3: %s" %newValues;
                    print "[TEST EXECUTION RESULT] : SUCCESS";

                    #Wait for the changes to reflect in client device
                    time.sleep(60);

                    #Connect to the wifi ssid from wlan client
                    print "TEST STEP 4: From wlan client, Connect to the wifi ssid"
                    status = wlanConnectWifiSsid(tdkbE2EUtility.ssid_2ghz_name,tdkbE2EUtility.ssid_2ghz_pwd,tdkbE2EUtility.wlan_2ghz_interface);
                    if expectedresult in status:
                        tdkTestObj.setResultStatus("SUCCESS");
                        print "wlanConnectWifiSsid: SUCCESS"

                        print "TEST STEP 5: Get the IP address of the wlan client after connecting to wifi"
                        wlanIP = getWlanIPAddress(tdkbE2EUtility.wlan_2ghz_interface);
                        if wlanIP:
                            tdkTestObj.setResultStatus("SUCCESS");
                            print "getWlanIPAddress: SUCCESS"
			
			    print "TEST STEP 6: Check whether wlan ip address is in same DHCP range"
                            status = "SUCCESS"
                            LanIP = newValues[2];
                            status = checkIpRange(LanIP,wlanIP);
                            if expectedresult in status:
                                tdkTestObj.setResultStatus("SUCCESS");
                                print "checkIpRange: SUCCESS"

                                print "TEST STEP 7: From wlan client, Disconnect from the wifi ssid"
                                status = wlanDisconnectWifiSsid(tdkbE2EUtility.wlan_2ghz_interface);
                                if expectedresult in status:
                                    tdkTestObj.setResultStatus("SUCCESS");
                                    finalStatus = "SUCCESS";
                                    print "Disconnect from WIFI SSID: SUCCESS"
			
				    time.sleep(60);	
				    print "TEST STEP 8: Reconnecting to the wifi ssid"
				    status = wlanConnectWifiSsid(tdkbE2EUtility.ssid_2ghz_name,tdkbE2EUtility.ssid_2ghz_pwd,tdkbE2EUtility.wlan_2ghz_interface);
                    		    if expectedresult in status:
                    		        tdkTestObj.setResultStatus("SUCCESS");
                    		        print "wlanConnectWifiSsid: SUCCESS"

                    		        print "TEST STEP 9: Get the IP address of the wlan client after connecting to wifi"
                    		        wlanIP1 = getWlanIPAddress(tdkbE2EUtility.wlan_2ghz_interface);
                    		        if wlanIP1:
                    		            tdkTestObj.setResultStatus("SUCCESS");
                    		            print "getWlanIPAddress: SUCCESS"

                    		            print "TEST STEP 10: Check whether wlan ip address is in same DHCP range"
                    		            status = "SUCCESS"
                    		            LanIP = newValues[2];
                    		            status = checkIpRange(LanIP,wlanIP1);
                    		            if expectedresult in status:
                    		                tdkTestObj.setResultStatus("SUCCESS");
                    		                print "checkIpRange: SUCCESS"

					        print "TEST STEP 11: From wlan client, Disconnect from the wifi ssid"
                                		status = wlanDisconnectWifiSsid(tdkbE2EUtility.wlan_2ghz_interface);
                                		if expectedresult in status:
                                		    tdkTestObj.setResultStatus("SUCCESS");
                                		    finalStatus = "SUCCESS";
                                		    print "Disconnect from WIFI SSID: SUCCESS"
						   
						    print "TEST STEP 12: Checking whether Wi-Fi Client retains the same IP address when disconnected and reconnected when the Lease period is active"
						    if wlanIP == wlanIP1:
							tdkTestObj.setResultStatus("SUCCESS");
							print "Wi-Fi Client retains the same IP address when disconnected and reconnected when the Lease period is active"
						    else:
							tdkTestObj.setResultStatus("FAILURE");
							print "Wi-Fi Client did not retain the same IP address when disconnected and reconnected when the Lease period is active"
						else:
						    tdkTestObj.setResultStatus("FAILURE");
						    print "TEST STEP 11:Disconnect from WIFI SSID: FAILED"
					    else:
						tdkTestObj.setResultStatus("FAILURE");
						print "TEST STEP 10:WLAN Client IP address is not in the same Gateway DHCP range"
					else:
					    tdkTestObj.setResultStatus("FAILURE");
					    print "TEST STEP 9:Failed to get the WLAN Client IP address"
				    else:
					tdkTestObj.setResultStatus("FAILURE");
					print "TEST STEP 8:Failed to reconnect to WIFI SSID"
                                else:
                                    tdkTestObj.setResultStatus("FAILURE");
                                    print "TEST STEP 7:Disconnect from WIFI SSID: FAILED"
                            else:
                                tdkTestObj.setResultStatus("FAILURE");
                                print "TEST STEP 6:WLAN Client IP address is not in the same Gateway DHCP range"
                        else:
                            tdkTestObj.setResultStatus("FAILURE");
                            print "TEST STEP 5:Failed to get the WLAN Client IP address"
                    else:
                        tdkTestObj.setResultStatus("FAILURE");
                        print "TEST STEP 4:Failed to connect to WIFI SSID"
                else:
                    tdkTestObj.setResultStatus("FAILURE");
                    print "TEST STEP 3: Get the current ssid,keypassphrase,lanIPAddress,lanSubnetMask,minAddress,maxAddress and leaseTime"
                    print "EXPECTED RESULT 3: Should retrieve the current ssid,keypassphrase,lanIPAddress,lanSubnetMask,minAddress,maxAddress and leaseTime"
                    print "ACTUAL RESULT 3: %s" %newValues;
                    print "[TEST EXECUTION RESULT] : FAILURE";
            else:
                tdkTestObj.setResultStatus("FAILURE");
                details = tdkTestObj.getResultDetails();
                print "TEST STEP 2: Set the ssid,keypassphrase,lanIPAddress,lanSubnetMask,minAddress,maxAddress and leaseTime"
                print "EXPECTED RESULT 2: Should set the ssid,keypassphrase,lanIPAddress,lanSubnetMask,minAddress,maxAddress and leaseTime";
                print "ACTUAL RESULT 2: %s" %details;
                print "[TEST EXECUTION RESULT] : FAILURE";

            #Prepare the list of parameter values to be reverted
            list1 = [ssidName,orgValue[0],'string']
            list2 = [keyPassPhrase,orgValue[1],'string']

            list3 = [lanIPAddress,orgValue[2],'string']
            list4 = [lanSubnetMask,orgValue[3],'string']
            list5 = [minAddress,orgValue[4],'string']
            list6 = [maxAddress,orgValue[5],'string']
            list7 = [leaseTime,orgValue[6],'int']

            #Concatenate the lists with the elements separated by pipe
            revertParamList = list1 + list2
            revertParamList = "|".join(map(str, revertParamList))

            revertParamList1 = list3 + list4 + list5 + list6 + list7
            revertParamList1 = "|".join(map(str, revertParamList1))


            #Revert the values to original
            tdkTestObj,actualresult,details = setMultipleParameterValues(obj,revertParamList)
            tdkTestObj,actualresult1,details = setMultipleParameterValues(obj,revertParamList1)
            if expectedresult in actualresult and expectedresult in actualresult1 and expectedresult in finalStatus:
                tdkTestObj.setResultStatus("SUCCESS");
                print "EXPECTED RESULT 8: Should set the original ssid,keypassphrase,lanIPAddress,lanSubnetMask,minAddress,maxAddress and leaseTime";
                print "ACTUAL RESULT 8: %s" %details;
                print "[TEST EXECUTION RESULT] : SUCCESS";
            else:
                tdkTestObj.setResultStatus("FAILURE");
                details = tdkTestObj.getResultDetails();
                print "EXPECTED RESULT 8: Should set the original ssid,keypassphrase,lanIPAddress,lanSubnetMask,minAddress,maxAddress and leaseTime";
                print "ACTUAL RESULT 8: %s" %details;
                print "[TEST EXECUTION RESULT] : FAILURE";
        else:
            tdkTestObj.setResultStatus("FAILURE");
            print "TEST STEP 1: Get the current ssid,keypassphrase,lanIPAddress,lanSubnetMask,minAddress,maxAddress and leaseTime"
            print "EXPECTED RESULT 1: Should retrieve the current ssid,keypassphrase,lanIPAddress,lanSubnetMask,minAddress,maxAddress and leaseTime"
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
