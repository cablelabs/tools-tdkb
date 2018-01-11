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
  <name>E2E_BridgeMode_CheckSSIDBroadcast</name>
  <primitive_test_id/>
  <primitive_test_name>tdkb_e2e_Set</primitive_test_name>
  <primitive_test_version>2</primitive_test_version>
  <status>FREE</status>
  <synopsis>Verify that on enabling bridge mode both Private SSIDs on 2.4 and 5 GHz should not be broadcasted</synopsis>
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
    <test_case_id>TC_TDKB_E2E_189</test_case_id>
    <test_objective>Verify that on enabling bridge mode both Private SSIDs on 2.4 and 5 GHz should not be broadcasted</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Broadband,Emulator,RPI</test_setup>
    <pre_requisite>Ensure the client setup is up with the IP address assigned by the gateway</pre_requisite>
    <api_or_interface_used>None</api_or_interface_used>
    <input_parameters>Device.WiFi.SSID.2.SSID
Device.WiFi.AccessPoint.2.Security.KeyPassphrase
Device.X_CISCO_COM_DeviceControl.LanManagementEntry.1.LanMode</input_parameters>
    <automation_approch>1. Load tdkb_e2e module
2. Using tdkb_e2e_Get, get and save lanMode
4. Set lanMode as bridge-static
5.  Connect to the WIFI client and check whether the ssid is getting listed
6.Unload tdkb_e2e module</automation_approch>
    <except_output>The SSID should not get listed lanMode is bridge-static</except_output>
    <priority>High</priority>
    <test_stub_interface>tdkb_e2e</test_stub_interface>
    <test_script>E2E_BridgeMode_CheckSSIDBroadcast</test_script>
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
obj.configureTestCase(ip,port,'E2E_BridgeMode_CheckSSIDBroadcast');

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
        ssidName_5ghz = "Device.WiFi.SSID.%s.SSID" %tdkbE2EUtility.ssid_5ghz_index
        lanMode = "Device.X_CISCO_COM_DeviceControl.LanManagementEntry.1.LanMode"

        #Get the value of the wifi parameters that are currently set.
        paramList=[ssidName_2ghz,ssidName_5ghz,lanMode]
        tdkTestObj,status,orgValue = getMultipleParameterValues(obj,paramList)

        if expectedresult in status:
            tdkTestObj.setResultStatus("SUCCESS");
            print "TEST STEP 1: Get the current ssid for 2ghz and 5ghz and lanMode"
            print "EXPECTED RESULT 1: Should retrieve the current ssid for 2ghz and 5ghz and lanMode"
            print "ACTUAL RESULT 1: %s" %orgValue;
            print "[TEST EXECUTION RESULT] : SUCCESS";

            # Set securityMode and radioEnable for 2.4ghz"
            setValuesList = [tdkbE2EUtility.ssid_2ghz_name,tdkbE2EUtility.ssid_5ghz_name,'bridge-static'];
            print "WIFI parameter values that are set: %s" %setValuesList

            list1 = [ssidName_2ghz,tdkbE2EUtility.ssid_2ghz_name,'string']
            list2 = [ssidName_5ghz,tdkbE2EUtility.ssid_5ghz_name,'string']

	    lanModeValue="%s|bridge-static|string" %lanMode

            #Concatenate the lists with the elements separated by pipe
            setParamList = list1 + list2
            setParamList = "|".join(map(str, setParamList))

            tdkTestObj,actualresult,details = setMultipleParameterValues(obj,setParamList)
            tdkTestObj,actualresult1,details = setMultipleParameterValues(obj,lanModeValue)
            if expectedresult in actualresult and expectedresult in actualresult1:
                tdkTestObj.setResultStatus("SUCCESS");
                print "TEST STEP 2: Set the ssid for 2ghz and 5ghz and lanMode"
                print "EXPECTED RESULT 2: Should set the ssid for 2ghz and 5ghz and lanMode";
                print "ACTUAL RESULT 2: %s" %details;
                print "[TEST EXECUTION RESULT] : SUCCESS";

                #Retrieve the values after set and compare
                newParamList=[ssidName_2ghz,ssidName_5ghz,lanMode]
                tdkTestObj,status,newValues = getMultipleParameterValues(obj,newParamList)

                if expectedresult in status and setValuesList == newValues:
                    tdkTestObj.setResultStatus("SUCCESS");
                    print "TEST STEP 3: Get the current ssid for 2ghz and 5ghz and lanMode"
                    print "EXPECTED RESULT 3: Should retrieve the current ssid for 2ghz and 5ghz and lanMode"
                    print "ACTUAL RESULT 3: %s" %newValues;
                    print "[TEST EXECUTION RESULT] : SUCCESS";

                    #Wait for the changes to reflect in client device
                    time.sleep(60);

                    #Check if the SSID name is listed in wifi client
                    print "TEST STEP 4: Check if the SSID name is listed in wifi client"
                    status_2ghz = wlanIsSSIDAvailable(tdkbE2EUtility.ssid_2ghz_name);
		    status_5ghz = wlanIsSSIDAvailable(tdkbE2EUtility.ssid_5ghz_name);
                    if expectedresult not in status_2ghz and expectedresult not in status_5ghz:
                        tdkTestObj.setResultStatus("SUCCESS");
                        print "Network names",tdkbE2EUtility.ssid_2ghz_name,"and",tdkbE2EUtility.ssid_5ghz_name,"are not broadcasted on the network";
                        finalStatus = "SUCCESS"
                    else:
                        tdkTestObj.setResultStatus("FAILURE");
			print "Network names",tdkbE2EUtility.ssid_2ghz_name,"and",tdkbE2EUtility.ssid_5ghz_name,"are broadcasted on the network";

                else:
                    tdkTestObj.setResultStatus("FAILURE");
                    print "TEST STEP 3: Get the current ssid for 2ghz and 5ghz and lanMode"
                    print "EXPECTED RESULT 3: Should retrieve the current ssid for 2ghz and 5ghz and lanMode"
                    print "ACTUAL RESULT 3: %s" %newValues;
                    print "[TEST EXECUTION RESULT] : FAILURE";
            else:
                tdkTestObj.setResultStatus("FAILURE");
                print "TEST STEP 2: Set the ssid for 2ghz and 5ghz and lanMode"
                print "EXPECTED RESULT 2: Should set the ssid for 2ghz and 5ghz and lanMode";
                print "ACTUAL RESULT 2: %s" %details;
                print "[TEST EXECUTION RESULT] : FAILURE";

            #Prepare the list of parameter values to be reverted
            list1 = [ssidName_2ghz,orgValue[0],'string']
            list2 = [ssidName_5ghz,orgValue[1],'string']

            #Concatenate the lists with the elements separated by pipe
            revertParamList = list1 + list2
            revertParamList = "|".join(map(str, revertParamList))

 	    revertlanModeValue = "%s|%s|string" %(lanMode,orgValue[2])

            #Revert the values to original
            tdkTestObj,actualresult,details = setMultipleParameterValues(obj,revertParamList)
            tdkTestObj,actualresult1,details = setMultipleParameterValues(obj,revertlanModeValue)
            if expectedresult in actualresult and expectedresult in actualresult1 and expectedresult in finalStatus:
                tdkTestObj.setResultStatus("SUCCESS");
                print "EXPECTED RESULT 15: Should set the original ssid for 2ghz and 5ghz and lanMode";
                print "ACTUAL RESULT 15: %s" %details;
                print "[TEST EXECUTION RESULT] : SUCCESS";
            else:
                tdkTestObj.setResultStatus("FAILURE");
                details = tdkTestObj.getResultDetails();
                print "EXPECTED RESULT 15: Should set the original ssid for 2ghz and 5ghz and lanMode";
                print "ACTUAL RESULT 15: %s" %details;
                print "[TEST EXECUTION RESULT] : FAILURE";
        else:
            tdkTestObj.setResultStatus("FAILURE");
            print "TEST STEP 1: Get the current ssid for 2ghz and 5ghz and lanMode"
            print "EXPECTED RESULT 1: Should retrieve the current ssid for 2ghz and 5ghz and lanMode"
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
