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
  <version>4</version>
  <!-- Do not edit version. This will be auto incremented while updating. If you are adding a new script you can keep the vresion as 1 -->
  <name>E2E_DHCP_SetServerLeaseTime_LessThan120</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id> </primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>tdkb_e2e_Get</primitive_test_name>
  <!--  -->
  <primitive_test_version>2</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>Verify that DHCPv4 Server lease time cannot be set less than 2 minutes (120 seconds). Ensure that DHCP configuration on client is not affected</synopsis>
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
    <test_case_id>TC_TDKB_E2E_275</test_case_id>
    <test_objective>Verify that DHCPv4 Server lease time cannot be set less than 2 minutes (120 seconds). Ensure that DHCP configuration on client is not affected</test_objective>
    <test_type>Negative</test_type>
    <test_setup>Broadband,Emulator,RPI</test_setup>
    <pre_requisite>Ensure the client setup is up with the IP address assigned by the gateway</pre_requisite>
    <api_or_interface_used>None</api_or_interface_used>
    <input_parameters>Device.X_CISCO_COM_DeviceControl.LanManagementEntry.1.LanIPAddress
Device.X_CISCO_COM_DeviceControl.LanManagementEntry.1.LanSubnetMask
Device.DHCPv4.Server.Pool.1.MinAddress
Device.DHCPv4.Server.Pool.1.MaxAddress</input_parameters>
    <automation_approch>1. Load tdkb_e2e module
2. Using tdkb_e2e_Get, get and save LanIP,SubnetMask,Maximum and minimum Address range
3. Set LanIP,SubnetMask,Maximum and minimum Address range as ClassA using tdkb_e2e_SetMultipleParams
4. Set leasetime as less than 120 seconds using tdkb_e2e_SetMultipleParams 
5.  Connect to the LAN client and check whether the leasetime is changed or not
5. Revert the values to original value
6.Unload tdkb_e2e module</automation_approch>
    <except_output>Lease time on client should not change to the invalid value used  in set</except_output>
    <priority>High</priority>
    <test_stub_interface>tdkb_e2e</test_stub_interface>
    <test_script>E2E_DHCP_SetServerLeaseTime_LessThan120</test_script>
    <skipped>No</skipped>
    <release_version>M55</release_version>
    <remarks>LAN</remarks>
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
obj.configureTestCase(ip,port,'E2E_DHCP_SetServerLeaseTime_LessThan120');

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
        lanIPAddress = "Device.X_CISCO_COM_DeviceControl.LanManagementEntry.1.LanIPAddress"
        lanSubnetMask = "Device.X_CISCO_COM_DeviceControl.LanManagementEntry.1.LanSubnetMask"
        minAddress = "Device.DHCPv4.Server.Pool.1.MinAddress"
        maxAddress = "Device.DHCPv4.Server.Pool.1.MaxAddress"
        leaseTime = "Device.DHCPv4.Server.Pool.1.LeaseTime"

        #Get the value of the wifi parameters that are currently set.
        paramList=[lanIPAddress,lanSubnetMask,minAddress,maxAddress,leaseTime]
        tdkTestObj,status,orgValue = getMultipleParameterValues(obj,paramList)

        if expectedresult in status:
            tdkTestObj.setResultStatus("SUCCESS");
            print "TEST STEP 1: Get the current lanIPAddress,lanSubnetMask,minAddress,maxAddress and leaseTime"
            print "EXPECTED RESULT 1: Should retrieve the current lanIPAddress,lanSubnetMask,minAddress maxAddress and leaseTime"
            print "ACTUAL RESULT 1: %s" %orgValue;
            print "[TEST EXECUTION RESULT] : SUCCESS";

            # Set the SSID name,password,lanIPAddress,lanSubnetMask,minAddress and maxAddress"
            setValuesList = ['10.0.0.1','255.255.255.0','10.0.0.2','10.0.0.253','120'];
            print "Parameter values that are set: %s" %setValuesList

            list1 = [lanIPAddress,'10.0.0.1','string']
            list2 = [lanSubnetMask,'255.255.255.0','string']
            list3 = [minAddress,'10.0.0.2','string']
            list4 = [maxAddress,'10.0.0.253','string']
            list5 = [leaseTime,'120','int']

            #Concatenate the lists with the elements separated by pipe
            setParamList = list1 + list2
            setParamList = "|".join(map(str, setParamList))
            setParamList1= list3 + list4 + list5 
            setParamList1 = "|".join(map(str, setParamList1))

            tdkTestObj,actualresult,details = setMultipleParameterValues(obj,setParamList)
            tdkTestObj,actualresult1,details = setMultipleParameterValues(obj,setParamList1)
            if expectedresult in actualresult and expectedresult in actualresult1:
                tdkTestObj.setResultStatus("SUCCESS");
                print "TEST STEP 2: Set the lanIPAddress,lanSubnetMask,minAddress,maxAddress and leaseTime"
                print "EXPECTED RESULT 2: Should set the lanIPAddress,lanSubnetMask,minAddress,maxAddress and leaseTime";
                print "ACTUAL RESULT 2: %s" %details;
                print "[TEST EXECUTION RESULT] : SUCCESS";

                #Retrieve the values after set and compare
                newParamList=[lanIPAddress,lanSubnetMask,minAddress,maxAddress,leaseTime]
                tdkTestObj,status,newValues = getMultipleParameterValues(obj,newParamList)

                if expectedresult in status and setValuesList == newValues:
                    tdkTestObj.setResultStatus("SUCCESS");
                    print "TEST STEP 3: Get the current lanIPAddress,lanSubnetMask,minAddress,maxAddress and leaseTime"
                    print "EXPECTED RESULT 3: Should retrieve the current lanIPAddress,lanSubnetMask,minAddress,maxAddress and leaseTime"
                    print "ACTUAL RESULT 3: %s" %newValues;
                    print "[TEST EXECUTION RESULT] : SUCCESS";

                    #Wait for the changes to reflect in client device
                    time.sleep(60);

                    # Set the lease time as less than 120 seconds
                    newLease = "%s|60|int" %leaseTime

                    tdkTestObj,status,details = setMultipleParameterValues(obj,newLease)
                    if expectedresult not in status:
                        tdkTestObj.setResultStatus("SUCCESS");
                        print "TEST STEP 4: Set the leasetime as less than 120seconds"
                        print "EXPECTED RESULT 4: Should not set the leasetime as less than 120seconds"
                        print "ACTUAL RESULT 4: %s" %details;
                        print "[TEST EXECUTION RESULT] : SUCCESS";

                        #Retrieve the values after set and compare
                        tdkTestObj,retStatus,newLeaseTime = getParameterValue(obj,leaseTime)
                        print "Leasetime: %s" %newLeaseTime;

                        if expectedresult in retStatus and newLeaseTime != 60:
                            tdkTestObj.setResultStatus("SUCCESS");
                            print "TEST STEP 5: Get the current leasetime"
                            print "EXPECTED RESULT 5: Should retrieve the current leasetime"
                            print "ACTUAL RESULT 5: %s " %newLeaseTime;
                            print "[TEST EXECUTION RESULT] : SUCCESS";


                            #Connect to Lan Client and get the IP address
                            print "TEST STEP 6:Connect to LAN Client and get the IP address after network refresh"
                            lanIP = getLanIPAddress(tdkbE2EUtility.lan_interface);

                            if lanIP:
                                tdkTestObj.setResultStatus("SUCCESS");
                                print "getlanIPAddress: SUCCESS"

                                print "TEST STEP 7: Check whether lan ip address is in same DHCP range"
                                status = "SUCCESS"
                                LanIP = newValues[0];
                                status = checkIpRange(LanIP,lanIP);
                                if expectedresult in status:
                                    tdkTestObj.setResultStatus("SUCCESS");
                                    print "checkIpRange: SUCCESS"

                                    print "TEST STEP 8: Get the DHCP server lease time of LAN client"
                                    leaseTimeInClient = getLanDhcpDetails(tdkbE2EUtility.lan_lease_time);
                                    if leaseTimeInClient:
                                                tdkTestObj.setResultStatus("SUCCESS");
                                                print "getDhcpLeaseTime SUCCESS"

                                                print "TEST STEP 9: Check whether lease time configuration in client is not affected"
                                                if leaseTimeInClient != 60:
                                                    tdkTestObj.setResultStatus("SUCCESS");
                                                    print "Lease time from client is not affected"
			            		    finalStatus = "SUCCESS";
                                                else:
                                                    tdkTestObj.setResultStatus("FAILURE");
                                                    print "lease time from client has changed to invalid value"
                                    else:
                                                tdkTestObj.setResultStatus("FAILURE");
                                                print "TEST STEP 8:Failed to get the DHCP server lease time of LAN client"
                                else:
                                     tdkTestObj.setResultStatus("FAILURE");
                                     print "TEST STEP 7:LAN Client IP address is not in the same Gateway DHCP range"
                            else:
                                tdkTestObj.setResultStatus("FAILURE");
                                print "TEST STEP 6:Failed to get the LAN Client IP address"
			else:
                            tdkTestObj.setResultStatus("FAILURE");
                            print "TEST STEP 5: Get the current leasetime"
                            print "EXPECTED RESULT 5: Should retrieve the current leasetime"
                            print "ACTUAL RESULT 5: %s " %newLeaseTime;
                            print "[TEST EXECUTION RESULT] : SUCCESS";
                    else:
                        tdkTestObj.setResultStatus("SUCCESS");
                        print "TEST STEP 4: Set the leasetime as less than 120seconds"
                        print "EXPECTED RESULT 4: Should not set the leasetime as less than 120seconds"
                        print "ACTUAL RESULT 4: %s" %details;
                        print "[TEST EXECUTION RESULT] : SUCCESS";
                else:
                    tdkTestObj.setResultStatus("FAILURE");
                    print "TEST STEP 3: Get the current lanIPAddress,lanSubnetMask,minAddress,maxAddress and leaseTime"
                    print "EXPECTED RESULT 3: Should retrieve the current lanIPAddress,lanSubnetMask,minAddress,maxAddress and leaseTime"
                    print "ACTUAL RESULT 3: %s" %newValues;
                    print "[TEST EXECUTION RESULT] : FAILURE";
            else:
                tdkTestObj.setResultStatus("FAILURE");
                details = tdkTestObj.getResultDetails();
                print "TEST STEP 2: Set the lanIPAddress,lanSubnetMask,minAddress,maxAddress and leaseTime"
                print "EXPECTED RESULT 2: Should set the lanIPAddress,lanSubnetMask,minAddress,maxAddress and leaseTime";
                print "ACTUAL RESULT 2: %s" %details;
                print "[TEST EXECUTION RESULT] : FAILURE";

            #Prepare the list of parameter values to be reverted
            list1 = [lanIPAddress,orgValue[0],'string']
            list2 = [lanSubnetMask,orgValue[1],'string']
            list3 = [minAddress,orgValue[2],'string']
            list4 = [maxAddress,orgValue[3],'string']
            list5 = [leaseTime,orgValue[4],'int']

            #Concatenate the lists with the elements separated by pipe
            revertParamList = list1 + list2
            revertParamList = "|".join(map(str, revertParamList))

            revertParamList1 = list3 + list4 + list5 
            revertParamList1 = "|".join(map(str, revertParamList1))


            #Revert the values to original
            tdkTestObj,actualresult,details = setMultipleParameterValues(obj,revertParamList)
            tdkTestObj,actualresult1,details = setMultipleParameterValues(obj,revertParamList1)
            if expectedresult in actualresult and expectedresult in actualresult1 and expectedresult in finalStatus:
                tdkTestObj.setResultStatus("SUCCESS");
                print "EXPECTED RESULT 10: Should set the original lanIPAddress,lanSubnetMask,minAddress,maxAddress and leaseTime";
                print "ACTUAL RESULT 10: %s" %details;
                print "[TEST EXECUTION RESULT] : SUCCESS";
            else:
                tdkTestObj.setResultStatus("FAILURE");
                details = tdkTestObj.getResultDetails();
                print "EXPECTED RESULT 10: Should set the original lanIPAddress,lanSubnetMask,minAddress,maxAddress and leaseTime";
                print "ACTUAL RESULT 10: %s" %details;
                print "[TEST EXECUTION RESULT] : FAILURE";
        else:
            tdkTestObj.setResultStatus("FAILURE");
            print "TEST STEP 1: Get the current lanIPAddress,lanSubnetMask,minAddress,maxAddress and leaseTime"
            print "EXPECTED RESULT 1: Should retrieve the current lanIPAddress,lanSubnetMask,minAddress,maxAddress and leaseTime"
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