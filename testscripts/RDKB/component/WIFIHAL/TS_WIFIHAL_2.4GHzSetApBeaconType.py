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
  <version>1</version>
  <name>TS_WIFIHAL_2.4GHzSetApBeaconType</name>
  <primitive_test_id/>
  <primitive_test_name>WIFIHAL_GetOrSetParamStringValue</primitive_test_name>
  <primitive_test_version>8</primitive_test_version>
  <status>FREE</status>
  <synopsis>To set and get beacon type using the api's wifi_setApBeaconType() and wifi_getApBeaconType()</synopsis>
  <groups_id/>
  <execution_time>1</execution_time>
  <long_duration>false</long_duration>
  <advanced_script>false</advanced_script>
  <remarks/>
  <skip>false</skip>
  <box_types>
    <box_type>Broadband</box_type>
    <box_type>RPI</box_type>
  </box_types>
  <rdk_versions>
    <rdk_version>RDKB</rdk_version>
  </rdk_versions>
  <test_cases>
    <test_case_id>TC_WIFIHAL_132</test_case_id>
    <test_objective>To set and get the BeaconType for 2.4GHz</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Broadband, RPI</test_setup>
    <pre_requisite>1.Ccsp Components  should be in a running state else invoke cosa_start.sh manually that includes all the ccsp components and TDK Component
2.TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>wifi_getApBeaconType()
wifi_setApBeaconType()</api_or_interface_used>
    <input_parameters>methodName : getApBeaconType
methodName : setApBeaconType
ApIndex : 0</input_parameters>
    <automation_approch>1. Load wifihal module
2. Using WIFIHAL_GetOrSetParamStringValue invoke wifi_getApBeaconType() and save the get value
3. Choose a BeaconType from supported Beacon Type list and using  WIFIHAL_GetOrSetParamStringValue invoke wifi_setApBeaconType()
4. Invoke wifi_getApBeaconType() to get the previously set value. 
5. Compare the above two results. If the two values  are same return SUCCESS else return FAILURE
6. Revert the BeaconType back to initial value
7. Unload wifihal module</automation_approch>
    <except_output>Set and get values of BeaconType should be the same</except_output>
    <priority>High</priority>
    <test_stub_interface>WIFIHAL</test_stub_interface>
    <test_script>TS_WIFIHAL_2.4GHzSetApBeaconType</test_script>
    <skipped>No</skipped>
    <release_version/>
    <remarks/>
  </test_cases>
</xml>

'''
# use tdklib library,which provides a wrapper for tdk testcase script 
import tdklib; 
from wifiUtility import *;

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("wifihal","1");

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_WIFIHAL_2.4GHzSetApBeaconType');

#Get the result of connection with test component and DUT
loadmodulestatus =obj.getLoadModuleResult();
print "[LIB LOAD STATUS]  :  %s" %loadmodulestatus ;

if "SUCCESS" in loadmodulestatus.upper():
    obj.setLoadModuleStatus("SUCCESS");

    beaconTypes = ['None', 'Basic', 'WPA', '11i', 'WPAand11i']

    expectedresult="SUCCESS";
    apIndex = 0
    getMethod = "getApBeaconType"
    primitive = 'WIFIHAL_GetOrSetParamStringValue'

    #Calling the method to execute wifi_getApBeaconType()
    tdkTestObj, actualresult, details = ExecuteWIFIHalCallMethod(obj, primitive, apIndex, "0", getMethod)
    initialBeaconType = details.split(":")[1].strip()

    if expectedresult in actualresult and initialBeaconType in beaconTypes:
        tdkTestObj.setResultStatus("SUCCESS");

        for setBeaconType in beaconTypes:
            if initialBeaconType == setBeaconType:
                continue;
            else:
                expectedresult = "SUCCESS";
                apIndex = 0
                setMethod = "setApBeaconType"
                primitive = 'WIFIHAL_GetOrSetParamStringValue'


                #Calling the method to execute wifi_setApBeaconType()
                tdkTestObj, actualresult, details = ExecuteWIFIHalCallMethod(obj, primitive, apIndex, setBeaconType, setMethod)

                if expectedresult in actualresult:
                    expectedresult="SUCCESS";
                    apIndex = 0
                    getMethod = "getApBeaconType"
                    primitive = 'WIFIHAL_GetOrSetParamStringValue'

                    #Calling the method to execute wifi_getApBeaconType()
                    tdkTestObj, actualresult, details = ExecuteWIFIHalCallMethod(obj, primitive, apIndex, "0", getMethod)
                    finalBeaconType = details.split(":")[1].strip()

                    if expectedresult in actualresult:
                        if finalBeaconType == setBeaconType:
                            tdkTestObj.setResultStatus("SUCCESS");
                            print "TEST STEP: Compare the set and get values of ApBeaconType"
                            print "EXPECTED RESULT: Set and get values of ApBeaconType should be same"
                            print "ACTUAL RESULT: Set and get values of ApBeaconType are the same"
                            print "setBeaconType = ",setBeaconType
                            print "getBeaconType = ",finalBeaconType
                            print "TEST EXECUTION RESULT : SUCCESS"
                        else:
                            tdkTestObj.setResultStatus("FAILURE");
                            print "TEST STEP: Compare the set and get values of ApBeaconType"
                            print "EXPECTED RESULT: Set and get values of ApBeaconType should be same"
                            print "ACTUAL RESULT: Set and get values of ApBeaconType are NOT the same"
                            print "setBeaconType = ",setBeaconType
                            print "getBeaconType = ",finalBeaconType
                            print "TEST EXECUTION RESULT : FAILURE"

                        #Revert the BeaconType back to initial value
                        tdkTestObj, actualresult, details = ExecuteWIFIHalCallMethod(obj, primitive, apIndex, initialBeaconType, setMethod)
                        if expectedresult in actualresult:
                            print "Successfully reverted the BeaconType to initial value"
			    tdkTestObj.setResultStatus("SUCCESS");
                        else:
                            print "Unable to revert the BeaconType"
			    tdkTestObj.setResultStatus("FAILURE");
                    else:
                        print "wifi_getApBeaconType() call failed"
			tdkTestObj.setResultStatus("FAILURE");
                else:
                    print "wifi_setApBeaconType() call failed"
		    tdkTestObj.setResultStatus("FAILURE");
                break;
    else:
        tdkTestObj.setResultStatus("FAILURE");

    obj.unloadModule("wifihal");
else:
        print "Failed to load the module";
        obj.setLoadModuleStatus("FAILURE");
        print "Module loading failed";

