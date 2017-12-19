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
  <name>TS_WIFIHAL_2.4GHzGetRadioTransmitPower</name>
  <primitive_test_id/>
  <primitive_test_name>WIFIHAL_GetOrSetParamStringValue</primitive_test_name>
  <primitive_test_version>1</primitive_test_version>
  <status>FREE</status>
  <synopsis>To get the transmit power for 2.4GHz using wifi_getRadioTransmitPower and validate the same using wifi_getRadioTransmitPowerSupported</synopsis>
  <groups_id/>
  <execution_time>1</execution_time>
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
    <test_case_id>TC_WIFIHAL_107</test_case_id>
    <test_objective>To get the transmit power for 2.4GHz using wifi_getRadioTransmitPower and validate the same using wifi_getRadioTransmitPowerSupported</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Broadband</test_setup>
    <pre_requisite>1.Ccsp Components  should be in a running state else invoke cosa_start.sh manually that includes all the ccsp components and TDK Component
2.TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>wifi_getRadioTransmitPower()
wifi_getRadioTransmitPowerSupported()</api_or_interface_used>
    <input_parameters>methodName :  getRadioTransmitPower
methodName :  getRadioTransmitPowerSupported
radioIndex : 0</input_parameters>
    <automation_approch>1. Load wifihal module
2. Invoke "WIFIHAL_GetOrSetParamStringValue" to get the Supported radio transmit power for 2.4GHz
3.Invoke "WIFIHAL_GetOrSetParamStringValue" to get the current operating channel bandwidth to a different value
4.Check if the value returned is present in supported transmit powers
5. If not, return failure
6.Unload wifihal module</automation_approch>
    <except_output>Checkpoints:
1.Should successfully get the supported transmit powers
2.Should successfully get the current transmit power for 2.4GHz</except_output>
    <priority>High</priority>
    <test_stub_interface>WIFIHAL</test_stub_interface>
    <test_script>TS_WIFIHAL_2.4GHzGetRadioTransmitPower</test_script>
    <skipped>No</skipped>
    <release_version/>
    <remarks/>
  </test_cases>
</xml>

'''
# use tdklib library,which provides a wrapper for tdk testcase script 
import tdklib; 

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("wifihal","1");

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_WIFIHAL_2.4GHzGetRadioTransmitPower');

#Get the result of connection with test component and DUT
loadmodulestatus =obj.getLoadModuleResult();
print "[LIB LOAD STATUS]  :  %s" %loadmodulestatus ;

if "SUCCESS" in loadmodulestatus.upper():
    obj.setLoadModuleStatus("SUCCESS");

    #Prmitive test case which associated to this Script
    tdkTestObj = obj.createTestStep('WIFIHAL_GetOrSetParamStringValue');
    #Giving the method name to invoke the api to get transmit power supported, wifi_getRadioTransmitPowerSupported()
    tdkTestObj.addParameter("methodName","getRadioTransmitPowerSupported");
    #Radio index is 0 for 2.4GHz and 1 for 5GHz
    tdkTestObj.addParameter("radioIndex",0);
    expectedresult="SUCCESS";
    tdkTestObj.executeTestCase(expectedresult);
    actualresult = tdkTestObj.getResult();
    details = tdkTestObj.getResultDetails();
    if expectedresult in actualresult:
        #Set the result status of execution
        tdkTestObj.setResultStatus("SUCCESS");
        print "TEST STEP 1: Get the supported transmit power for 2.4GHz";
        print "EXPECTED RESULT 1: Should get the supported transmit power for 2.4GHz";
        print "ACTUAL RESULT 1: %s" %details;
        #Get the result of execution
        print "[TEST EXECUTION RESULT] : SUCCESS";
        supportedTransmitPower = [int(x) for x in details.split(":")[1].split(",")];
	supportedTransmitPower = str(supportedTransmitPower).replace(' ','');

        print "Supported transmit powers are ", supportedTransmitPower;
 
	tdkTestObj = obj.createTestStep('WIFIHAL_GetOrSetParamULongValue');
        #Giving the method name to invoke the api to get current transmit power ,wifi_getRadioTransmitPower()
        tdkTestObj.addParameter("methodName","getRadioTransmitPower");
        #Radio index is 0 for 2.4GHz and 1 for 5GHz
        tdkTestObj.addParameter("radioIndex",0);
        expectedresult="SUCCESS";
        tdkTestObj.executeTestCase(expectedresult);
        actualresult = tdkTestObj.getResult();
        details = tdkTestObj.getResultDetails();
        if expectedresult in actualresult:
	    tdkTestObj.setResultStatus("SUCCESS");
	    transmitPower = details.split(":")[1];
	    print "TEST STEP 2: Get the current transmit power for 2.4GHz"
	    print "EXPECTED RESULT 2: Should get the current transmit power for 2.4GHz";
	    print "ACTUAL RESULT 2: %s" %details;
	    if transmitPower in supportedTransmitPower:
                #Set the result status of execution
                tdkTestObj.setResultStatus("SUCCESS");
                print "TEST STEP 3: Check if the current transmit power is in supported transmit power list";
                print "EXPECTED RESULT 3: Current transmit power should be from supported transmit power list";
                print "ACTUAL RESULT 3: Current transmit power is in supported transmit power list";
                print "[TEST EXECUTION RESULT] : SUCCESS";
            else:
                tdkTestObj.setResultStatus("FAILURE");
	        print "TEST STEP 3: Check if the current transmit power is in supported transmit power list";
                print "EXPECTED RESULT 3: Current transmit power should be from supported transmit power list";
                print "ACTUAL RESULT 3: Current transmit power is in supported transmit power list";
                print "[TEST EXECUTION RESULT] : FAILURE";
        else:
            #Set the result status of execution
            tdkTestObj.setResultStatus("FAILURE");
            print "TEST STEP 2: Get the current transmit power for 2.4GHz";
            print "EXPECTED RESULT 2: Should get the current transmit power for 2.4GHz";
            print "ACTUAL RESULT 2: %s" %details;
            #Get the result of execution
            print "[TEST EXECUTION RESULT] : FAILURE";
    else:
        #Set the result status of execution
        tdkTestObj.setResultStatus("FAILURE");
        print "TEST STEP 1: Get the supported transmit power for 2.4GHz";
        print "EXPECTED RESULT 1: Should get the supported transmit power for 2.4GHz";
        print "ACTUAL RESULT 1: %s" %details;
        #Get the result of execution
        print "[TEST EXECUTION RESULT] : FAILURE";
    obj.unloadModule("wifihal");
else:
        print "Failed to load the module";
        obj.setLoadModuleStatus("FAILURE");
        print "Module loading failed";


