##########################################################################
# If not stated otherwise in this file or this component's Licenses.txt
# file the following copyright and licenses apply:
#
# Copyright 2018 RDK Management
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
  <version>4</version>
  <name>TS_WIFIHAL_5GHzWifiDown</name>
  <primitive_test_id/>
  <primitive_test_name>WIFIHAL_GetOrSetParamStringValue</primitive_test_name>
  <primitive_test_version>1</primitive_test_version>
  <status>FREE</status>
  <synopsis>To call the wifi down for 5GHz radio using wifi_down HAL API and validate the same</synopsis>
  <groups_id>4</groups_id>
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
    <test_case_id>TC_WIFIHAL_234</test_case_id>
    <test_objective>To set the wifi down for 5GHz radio using wifi_down HAL API and validate the same</test_objective>
    <test_type>Positive</test_type>
    <test_setup>XB6</test_setup>
    <pre_requisite>1.Ccsp Components  should be in a running state else invoke cosa_start.sh manually that includes all the ccsp components and TDK Component
2.TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>wifi_down()</api_or_interface_used>
    <input_parameters>methodName   :   wifiDown
apIndex   :    0</input_parameters>
    <automation_approch>1.Configure the Function info in Test Manager GUI  which needs to be tested (WIFIHAL_GetOrSetParamStringValue  - func name - "If not exists already" WIFIHAL - module name Necessary I/P args as Mentioned in Input)
2.Python Script will be generated/overrided automatically by Test Manager with provided arguments in configure page (TS_WIFIHAL_5GHzWifiDown.py)
3.Execute the generated Script(TS_WIFIHAL_5GHzWifiDown.py) using execution page of  Test Manager GUI
4.wifihalstub which is a part of TDK Agent process, will be in listening mode to execute TDK Component function named WIFIHAL_GetOrSetParamStringValue through registered TDK wifihalstub function along with necessary Path Name as arguments
5.WIFIHAL_Down (stub function) will call  Ccsp Base Function named "ssp_WIFIHALDown" that inturn will call WIFIHAL Library Function wifi_down() function
6.Response(s)(printf) from TDK Component,Ccsp Library function and wifihalstub would be logged in Agent Console log based on the debug info redirected to agent console
7.wifihalstub will validate the available result (from agent console log and Pointer to instance as updated) with expected result
8.Test Manager will publish the result in GUI as SUCCESS/FAILURE based on the response from wifihalstub</automation_approch>
    <except_output>"""CheckPoint
1:wifi_down() from DUT should be available in Agent Console LogCheckPoint
2:TDK agent Test Function will log the test case result as PASS based on API response CheckPoint
3:Test Manager GUI will publish the result as SUCCESS in Execution page"""</except_output>
    <priority>High</priority>
    <test_stub_interface>WIFIHAL</test_stub_interface>
    <test_script>TS_WIFIHAL_5GHzWifiDown</test_script>
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
from wifiUtility import *;

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("wifihal","1");

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_WIFIHAL_5GHzWifiDown');

def wifidown ():
    #Calling the method from wifiUtility to execute wifidown test case and set result status for the test
    expectedresult = "SUCCESS";
    tdkTestObj = obj.createTestStep("WIFIHAL_Down");
    tdkTestObj.executeTestCase(expectedresult);
    actualresult = tdkTestObj.getResult();
    details = tdkTestObj.getResultDetails();
    if expectedresult in actualresult:
        tdkTestObj.setResultStatus("SUCCESS");
        print "TEST STEP: Validate the wifi_down Function";
        print "EXPECTED RESULT: wifi_down should return SUCCESS";
        print "ACTUAL RESULT : wifi_down operation returned SUCCESS";
        print "Actual result is :",details;
        print "[TEST EXECUTION RESULT] : SUCCESS";
        time.sleep(10)

        #Get the Transmit power
        getMethod = "getRadioTransmitPower"
        radioIndex = 1
        primitive = 'WIFIHAL_GetOrSetParamULongValue'
        tdkTestObj, actualresult, details = ExecuteWIFIHalCallMethod(obj, primitive, radioIndex, 0, getMethod)
        expectedresult = "SUCCESS";
        if expectedresult in actualresult:
            details1 = details.split(":")[1].strip()
            if details1 == "0":
                tdkTestObj.setResultStatus("SUCCESS");
                print "TEST STEP:Get the transmit power after wifidown operation";
                print "EXPECTED RESULT: Transmit power should be '0' ";
                print "ACTUAL RESULT:Transmit power is :",details1;
                print "[TEST EXECUTION RESULT] : SUCCESS";
            else:
                tdkTestObj.setResultStatus("FAILURE");
                print "TEST STEP:Get the transmit power after wifidown operation";
                print "EXPECTED RESULT: Transmit power should be '0' ";
                print "ACTUAL RESULT:Transmit power is :",details1;
                print "[TEST EXECUTION RESULT] : FAILED";
        else:
            tdkTestObj.setResultStatus("FAILURE");
            print "TEST STEP:Get the transmit power after wifidown operation";
            print "EXPECTED RESULT: Should get the Transmit power";
            print "ACTUAL RESULT:Faled to get the Transmit power";
            print "[TEST EXECUTION RESULT] : FAILED";

        #Initializes the down radios
        expectedresult="SUCCESS"
        primitive = "WIFIHAL_Init"
        tdkTestObj = obj.createTestStep("WIFIHAL_Init");
        tdkTestObj.executeTestCase(expectedresult);
        actualresult = tdkTestObj.getResult();
        details = tdkTestObj.getResultDetails();
        if expectedresult in actualresult:
            tdkTestObj.setResultStatus("SUCCESS");
            print "TEST STEP:INITIALIZES the wifi Radio";
            print "EXPECTED RESULT:Should INITIALIZE the wifi Radio 2.4 & 5 GHz";
            print "ACTUAL RESULT: Successfully initializes the wifi Radio 2.4 & 5 GHz"
        else:
            tdkTestObj.setResultStatus("FAILURE");
            print "TEST STEP:INITIALIZES the wifi Radio";
            print "EXPECTED RESULT:Should INITIALIZE the wifi Radio 2.4 & 5 GHz";
            print "ACTUAL RESULT: FAILED to INITIALIZE the wifi Radio 2.4GHz & 5GHz"

        #Revert back to initial value
        setMethod = "setRadioTransmitPower"
        primitive = 'WIFIHAL_GetOrSetParamULongValue'
        setValue = int(initGetValue)
        tdkTestObj, actualresult, details = ExecuteWIFIHalCallMethod(obj, primitive, radioIndex, setValue, setMethod)
        if expectedresult in actualresult:
            tdkTestObj.setResultStatus("SUCCESS");
            print "TEST STEP:Revert back the RadioTransmitPower to initial value";
            print "EXPECTED RESULT:Should Revert back the RadioTransmitPower to initial value for 2.4 & 5 GHz";
            print "ACTUAL RESULT: Successfully Reverted back to the initial value for  2.4 & 5 GHz"
        else:
            tdkTestObj.setResultStatus("FAILURE");
            print "TEST STEP:Revert back the RadioTransmitPower to initial value";
            print "EXPECTED RESULT:Should Revert back the RadioTransmitPower to initial value for 2.4 & 5 GHz";
            print "ACTUAL RESULT: Failed to Revert to the initial value for  2.4 & 5 GHz"

loadmodulestatus =obj.getLoadModuleResult();
print "[LIB LOAD STATUS]  :  %s" %loadmodulestatus

if "SUCCESS" in loadmodulestatus.upper():
    obj.setLoadModuleStatus("SUCCESS");

    #Get the Transmit power
    getMethod = "getRadioTransmitPower"
    radioIndex = 1
    primitive = 'WIFIHAL_GetOrSetParamULongValue'
    tdkTestObj, actualresult, details = ExecuteWIFIHalCallMethod(obj, primitive, radioIndex, 0, getMethod)
    expectedresult = "SUCCESS";
    if expectedresult in actualresult:
        initGetValue = details.split(":")[1].strip()
        if initGetValue == "0":
            tdkTestObj.setResultStatus("SUCCESS");
            print "TEST STEP: Get the current transmit power for 5 GHz";
            print "EXPECTED RESULT:should get the current transmit power for 5 GHz";
            print "ACTUAL RESULT:Get operation success and value returned is:",initGetValue;
            print "[TEST EXECUTION RESULT] : SUCCESS";
            #Prmitive test case which associated to this Script
            tdkTestObj = obj.createTestStep('WIFIHAL_GetOrSetParamStringValue');
            #Giving the method name to invoke the api to get transmit power supported, wifi_getRadioTransmitPowerSupported()
            tdkTestObj.addParameter("methodName","getRadioTransmitPowerSupported");
            #Radio index is 0 for 2.4GHz and 1 for 5GHz
            tdkTestObj.addParameter("radioIndex",1);
            expectedresult="SUCCESS";
            tdkTestObj.executeTestCase(expectedresult);
            actualresult = tdkTestObj.getResult();
            details = tdkTestObj.getResultDetails();
            if expectedresult in actualresult:
                #Set the result status of execution
                tdkTestObj.setResultStatus("SUCCESS");
                print "TEST STEP: Get the supported transmit power for 5 GHz";
                print "EXPECTED RESULT: Should get the supported transmit power for 5 GHz";
                print "ACTUAL RESULT: %s" %details;
                #Get the result of execution
                print "[TEST EXECUTION RESULT] : SUCCESS";
                supportedTransmitPower = [int(x) for x in details.split(":")[1].split(",")];
                print "Supported transmit powers are ", supportedTransmitPower;
                for i in supportedTransmitPower:
                    if i > 0:
                        break
                    else:
                        pass
                setValue = i;
                setMethod = "setRadioTransmitPower"
                primitive = 'WIFIHAL_GetOrSetParamULongValue'
                tdkTestObj, actualresult, details = ExecuteWIFIHalCallMethod(obj, primitive, radioIndex, setValue, setMethod)
                if expectedresult in actualresult:
                    tdkTestObj.setResultStatus("SUCCESS");
                    print "TEST STEP: Set the transmit power for 5 GHz to a supported value";
                    print "EXPECTED RESULT:Should set the transmit power for 5 GHz to :",setValue;
                    print "ACTUAL RESULT:Set operation success";
                    print "[TEST EXECUTION RESULT] : SUCCESS";
                    #call getRadioTransmitPower to get newly set radio transmit power
                    getMethod = "getRadioTransmitPower"
                    radioIndex = 1
                    primitive = 'WIFIHAL_GetOrSetParamULongValue'
                    tdkTestObj, actualresult, details = ExecuteWIFIHalCallMethod(obj, primitive, radioIndex, 0, getMethod)
                    expectedresult = "SUCCESS";
                    if expectedresult in actualresult:
                        NewlySetTransmitpowerValue = details.split(":")[1].strip()
                        tdkTestObj.setResultStatus("SUCCESS");
                        print "TEST STEP: Get the newly set transmit power for 5 GHz";
                        print "EXPECTED RESULT:Should get the transmit power for 5 GHz as :",setValue;
                        print "ACTUAL RESULT:Get operation success";
                        print "Newly Set transmit power value is :",NewlySetTransmitpowerValue;
                        if NewlySetTransmitpowerValue == setValue:
                            tdkTestObj.setResultStatus("SUCCESS");
                            print "'wifi_setRadioTransmitPower' api returns true SUCCESS"
                            print "[TEST EXECUTION RESULT] : SUCCESS";
                            #call wifidown () function to execute wifi radio power down
                            wifidown ()
                        else:
                            tdkTestObj.setResultStatus("FAILURE");
                            print "'wifi_setRadioTransmitPower' api returns false SUCCESS"
                            print "[TEST EXECUTION RESULT] : FAILURE";
                            obj.unloadModule("wifihal");
                    else:
                        tdkTestObj.setResultStatus("FAILURE");
                        print "TEST STEP: Get the newly set transmit power for 5 GHz";
                        print "EXPECTED RESULT:Should get the transmit power for 5 GHz as :",setValue;
                        print "ACTUAL RESULT:Get operation Failed"
                else:
                    tdkTestObj.setResultStatus("FAILURE");
                    print "TEST STEP: Set the transmit power for 5 GHz to a supported value";
                    print "EXPECTED RESULT:Should set the transmit power for 5 GHz";
                    print "ACTUAL RESULT:Set operation failed";
                    print "[TEST EXECUTION RESULT] : FAILED";
        else:
            print "Initial transmit power value is:",initGetValue
            #call wifidown () function to execute wifi radio power down
            wifidown ()
    else:
        print "getRadioTransmitPower operation returns failure no need to execute further";
    obj.unloadModule("wifihal");
else:
    print "Failed to load wifi module";
    obj.setLoadModuleStatus("FAILURE");

