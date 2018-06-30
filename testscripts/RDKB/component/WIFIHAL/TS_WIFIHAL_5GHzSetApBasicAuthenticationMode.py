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
  <name>TS_WIFIHAL_5GHzSetApBasicAuthenticationMode</name>
  <primitive_test_id/>
  <primitive_test_name>WIFIHAL_GetOrSetParamStringValue</primitive_test_name>
  <primitive_test_version>8</primitive_test_version>
  <status>FREE</status>
  <synopsis>To set and get ApBasicAuthenticationMode for 5GHz</synopsis>
  <groups_id/>
  <execution_time>10</execution_time>
  <long_duration>false</long_duration>
  <advanced_script>false</advanced_script>
  <remarks/>
  <skip>false</skip>
  <box_types>
    <box_type>Broadband</box_type>
  </box_types>
  <rdk_versions>
    <rdk_version>RDKB</rdk_version>
  </rdk_versions>
  <test_cases>
    <test_case_id>TC_WIFIHAL_134</test_case_id>
    <test_objective>To set and get the BasicAuthenticationMode for 5GHz</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Broadband, RPI</test_setup>
    <pre_requisite>1.Ccsp Components  should be in a running state else invoke cosa_start.sh manually that includes all the ccsp components and TDK Component
2.TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>wifi_getApBasicAuthenticationMode()
wifi_setApBasicAuthenticationMode()</api_or_interface_used>
    <input_parameters>methodName : getApBasicAuthenticationMode()
methodName : setApBasicAuthenticationMode()
ApIndex : 1</input_parameters>
    <automation_approch>1. Load wifihal module
2. Using WIFIHAL_GetOrSetParamStringValue invoke wifi_getApBasicAuthenticationMode() and save the get value
3. Choose a BasicAuthenticationMode from supported BasicAuthenticationMode  list and using  WIFIHAL_GetOrSetParamStringValue invoke wifi_setApBasicAuthenticationMode()
4. Invoke wifi_getApBasicAuthenticationMode() to get the previously set value.
5. Compare the above two results. If the two values  are same return SUCCESS else return FAILURE
6. Revert the AuthenticationMode back to initial value
7. Unload wifihal module</automation_approch>
    <except_output>Set and get values of AuthenticationMode should be the same</except_output>
    <priority>High</priority>
    <test_stub_interface>WIFIHAL</test_stub_interface>
    <test_script>TS_WIFIHAL_5GHzSetApBasicAuthenticationMode</test_script>
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
obj.configureTestCase(ip,port,'TS_WIFIHAL_5GHzSetApBasicAuthenticationMode');

def setApBeaconType(obj):
    expectedresult="SUCCESS";
    apIndex = 1
    getMethod = "getApBeaconType"
    primitive = 'WIFIHAL_GetOrSetParamStringValue'

    #Calling the method to execute wifi_getApBeaconType()
    tdkTestObj, actualresult, details = ExecuteWIFIHalCallMethod(obj, primitive, apIndex, "0", getMethod)
    if expectedresult in actualresult:
        initialBeaconType = details.split(":")[1].strip()
        tdkTestObj.setResultStatus("SUCCESS");
        expectedresult = "SUCCESS";
        apIndex = 1
        setMethod = "setApBeaconType"
        setBeaconType = 'None'
        primitive = 'WIFIHAL_GetOrSetParamStringValue'

        #Calling the method to execute wifi_setApBeaconType()
        tdkTestObj, actualresult, details = ExecuteWIFIHalCallMethod(obj, primitive, apIndex, setBeaconType, setMethod)
        if expectedresult in actualresult:
            expectedresult="SUCCESS";
            apIndex = 1
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
            else:
                print "wifi_getApBeaconType() call failed"
                tdkTestObj.setResultStatus("FAILURE");
        else:
            print "wifi_setApBeaconType() call failed"
            tdkTestObj.setResultStatus("FAILURE");
    return (initialBeaconType);

#Get the result of connection with test component and DUT
loadmodulestatus =obj.getLoadModuleResult();
print "[LIB LOAD STATUS]  :  %s" %loadmodulestatus ;

if "SUCCESS" in loadmodulestatus.upper():
    obj.setLoadModuleStatus("SUCCESS");

    supportedModes = ['None', 'EAPAuthentication', 'SharedAuthentication', 'PSKAuthentication']

    expectedresult="SUCCESS";
    apIndex = 1
    getMethod = "getApBasicAuthenticationMode"
    primitive = 'WIFIHAL_GetOrSetParamStringValue'

    #Calling the method to execute wifi_getApBasicAuthenticationMode()
    tdkTestObj, actualresult, details = ExecuteWIFIHalCallMethod(obj, primitive, apIndex, "0", getMethod)
    initialMode = details.split(":")[1].strip()

    if expectedresult in actualresult and initialMode in supportedModes:
        tdkTestObj.setResultStatus("SUCCESS");

        for setMode in supportedModes:
            if initialMode == setMode:
                continue;
            else:
	        if (setMode == 'None'):
		    #Calling the function to perform the settings and getting and verification of becon type to be none.
		    initialBeaconType = setApBeaconType(obj);

                expectedresult = "SUCCESS";
                apIndex = 1
                setMethod = "setApBasicAuthenticationMode"
                primitive = 'WIFIHAL_GetOrSetParamStringValue'


                #Calling the method to execute wifi_setApBasicAuthenticationMode()
                tdkTestObj, actualresult, details = ExecuteWIFIHalCallMethod(obj, primitive, apIndex, setMode, setMethod)

                if expectedresult in actualresult:
                    expectedresult="SUCCESS";
                    apIndex = 1
                    getMethod = "getApBasicAuthenticationMode"
                    primitive = 'WIFIHAL_GetOrSetParamStringValue'

                    #Calling the method to execute wifi_getApBasicAuthenticationMode()
                    tdkTestObj, actualresult, details = ExecuteWIFIHalCallMethod(obj, primitive, apIndex, "0", getMethod)
                    finalMode = details.split(":")[1].strip()

                    if expectedresult in actualresult:
                        if finalMode == setMode:
                            tdkTestObj.setResultStatus("SUCCESS");
                            print "TEST STEP: Compare the set and get values of ApBasicAuthenticationMode"
                            print "EXPECTED RESULT: Set and get values of ApBasicAuthenticationMode should be same"
                            print "ACTUAL RESULT: Set and get values of ApBasicAuthenticationMode are the same"
                            print "setBasicAuthenticationMode = ",setMode
                            print "getBasicAuthenticationMode = ",finalMode
                            print "TEST EXECUTION RESULT : SUCCESS"
                        elif finalMode == "PSKAuthentication" and setMode == "SharedAuthentication":
                            tdkTestObj.setResultStatus("SUCCESS");
                            #To handle the basic authentication mode in xf3 where setMode is equal to "SharedAuthentication"
                            print "TEST STEP: Compare the set and get values of ApBasicAuthenticationMode"
                            print "EXPECTED RESULT: Set and get values of ApBasicAuthenticationMode should be same(SharedAuthentication is same as PSKAuthentication)"
                            print "ACTUAL RESULT: Set and get values of ApBasicAuthenticationMode are the same"
                            print "setBasicAuthenticationMode = ",setMode
                            print "getBasicAuthenticationMode = ",finalMode
                            print "TEST EXECUTION RESULT : SUCCESS"
                        else:
                            tdkTestObj.setResultStatus("FAILURE");
                            print "TEST STEP: Compare the set and get values of ApBasicAuthenticationMode"
                            print "EXPECTED RESULT: Set and get values of ApBasicAuthenticationMode should be same"
                            print "ACTUAL RESULT: Set and get values of ApBasicAuthenticationMode are NOT the same"
                            print "setBasicAuthenticationMode = ",setMode
                            print "getBasicAuthenticationMode = ",finalMode
                            print "TEST EXECUTION RESULT : FAILURE"

                        #Revert the BasicAuthenticationMode back to initial value
                        setMethod = "setApBasicAuthenticationMode"
                        primitive = 'WIFIHAL_GetOrSetParamStringValue'
                        tdkTestObj, actualresult, details = ExecuteWIFIHalCallMethod(obj, primitive, apIndex, initialMode, setMethod)
                        if expectedresult in actualresult:
                            print "Successfully reverted the BasicAuthenticationMode to initial value"
			    tdkTestObj.setResultStatus("SUCCESS");
                        else:
                            print "Unable to revert the BasicAuthenticationMode"
			    tdkTestObj.setResultStatus("FAILURE");
                    else:
                        print "wifi_getApBasicAuthenticationMode() call failed"
			tdkTestObj.setResultStatus("FAILURE");
                else:
                    print "wifi_setApBasicAuthenticationMode() call failed"
		    tdkTestObj.setResultStatus("FAILURE");
                if (setMode == 'None'):
                    expectedresult="SUCCESS";
                    apIndex = 1
                    setMethod = "setApBeaconType"
                    primitive = 'WIFIHAL_GetOrSetParamStringValue'
                    #Revert the BeaconType back to initial value
                    tdkTestObj, actualresult, details = ExecuteWIFIHalCallMethod(obj, primitive, apIndex, initialBeaconType, setMethod)
                    if expectedresult in actualresult:
                        print "Successfully reverted the BeaconType to initial value"
	                tdkTestObj.setResultStatus("SUCCESS");
                    else:
                        print "Unable to revert the BeaconType"
	                tdkTestObj.setResultStatus("FAILURE");
                break;
    else:
        tdkTestObj.setResultStatus("FAILURE");

    obj.unloadModule("wifihal");
else:
        print "Failed to load the module";
        obj.setLoadModuleStatus("FAILURE");
        print "Module loading failed";

