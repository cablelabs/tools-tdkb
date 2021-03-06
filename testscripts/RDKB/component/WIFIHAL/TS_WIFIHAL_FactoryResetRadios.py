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
<?xml version='1.0' encoding='utf-8'?>
<xml>
  <id></id>
  <!-- Do not edit id. This will be auto filled while exporting. If you are adding a new script keep the id empty -->
  <version>4</version>
  <!-- Do not edit version. This will be auto incremented while updating. If you are adding a new script you can keep the vresion as 1 -->
  <name>TS_WIFIHAL_FactoryResetRadios</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id> </primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>WIFIHAL_FactoryReset</primitive_test_name>
  <!--  -->
  <primitive_test_version>1</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>To invoke the api wifi_factoryResetRadios()  and check whether the set and get values are different after doing factory reset radios for both 2.4GHz and 5GHz.</synopsis>
  <!--  -->
  <groups_id />
  <!--  -->
  <execution_time>5</execution_time>
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
  </box_types>
  <rdk_versions>
    <rdk_version>RDKB</rdk_version>
    <!--  -->
  </rdk_versions>
  <test_cases>
    <test_case_id>TC_WIFIHAL_289</test_case_id>
    <test_objective>To invoke the api wifi_factoryResetRadios() and check whether the set and get values are different after factory reset radios for both 2.4GHz and 5GHz.</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Broadband</test_setup>
    <pre_requisite>1.Ccsp Components  should be in a running state else invoke cosa_start.sh manually that includes all the ccsp components and TDK Component
2.TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>wifi_getChannelBandwidth()
wifi_getRadioGuardInterval()
wifi_getRadioChannel()
wifi_setChannelBandwidth()
wifi_setRadioGuardInterval()
wifi_setRadioChannel()
wifi_factoryResetRadios()</api_or_interface_used>
    <input_parameters>methodName : getChannelBandwidth
methodName : getRadioGuardInterval
methodName : getRadioChannel
methodName : setChannelBandwidth
methodName : setRadioGuardInterval
methodName : setRadioChannel
methodName : factoryResetRadio
radioIndex : 0
radioIndex : 1</input_parameters>
    <automation_approch>1.Load the module.
2.Get the channel bandwidth,radio guard interval and radio channel using wifi_getChannelBandwidth() wifi_getRadioGuardInterval()
wifi_getRadioChannel() apis respectively for both 2.4GHz and 5GHz.
3.Set these three values to other values using wifi_setChannelBandwidth()
wifi_setRadioGuardInterval()
wifi_setRadioChannel() apis respectively for both 2.4GHz and 5GHz.
4.Invoke the wifi_factoryResetRadio() api.
5.Get the values and compare with the set values for both 2.4GHz and 5GHz.
6.Get  and set values should be different.If they are different,return SUCCESS,else FAILURE.
7.Revert the values back to the initial values.
8.Unload the module.</automation_approch>
    <except_output>The set and get values should be different doing  after factory reset radios by invoking wifi_factoryResetRadios() for both 2.4GHz and 5GHz.</except_output>
    <priority>High</priority>
    <test_stub_interface>WIFIHAL</test_stub_interface>
    <test_script>TS_WIFIHAL_FactoryResetRadios</test_script>
    <skipped>No</skipped>
    <release_version>M59</release_version>
    <remarks></remarks>
  </test_cases>
  <script_tags />
</xml>
'''
# use tdklib library,which provides a wrapper for tdk testcase script
import tdklib;
from wifiUtility import *;
import time;

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("wifihal","1");

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_WIFIHAL_FactoryResetRadios');
#Get the result of connection with test component and DUT
loadmodulestatus =obj.getLoadModuleResult();
print "[LIB LOAD STATUS]  :  %s" %loadmodulestatus ;
def InvokeGetSetMethod(primitive,radioIndex,Value,MethodName):
    expectedresult="SUCCESS";
    tdkTestObj, actualresult, details = ExecuteWIFIHalCallMethod(obj, primitive, radioIndex, Value, MethodName)
    if expectedresult in actualresult:
        tdkTestObj.setResultStatus("SUCCESS");
        return details;
    else:
	tdkTestObj.setResultStatus("FAILURE");

if "SUCCESS" in loadmodulestatus.upper():
    obj.setLoadModuleStatus("SUCCESS");
    details_BW0 = InvokeGetSetMethod('WIFIHAL_GetOrSetParamStringValue',0,"0","getChannelBandwidth");
    OperatingChannelBandwidth_initial0 = details_BW0.split(":")[1].strip(" ");
    details_BW1 = InvokeGetSetMethod('WIFIHAL_GetOrSetParamStringValue',1,"0","getChannelBandwidth");
    OperatingChannelBandwidth_initial1 = details_BW1.split(":")[1].strip(" ");
    details_interval0 = InvokeGetSetMethod('WIFIHAL_GetOrSetParamStringValue',0,"0","getRadioGuardInterval");
    GuardInterval_initial0 = details_interval0.split(":")[1].strip(" ");
    details_interval1 = InvokeGetSetMethod('WIFIHAL_GetOrSetParamStringValue',1,"0","getRadioGuardInterval");
    GuardInterval_initial1 = details_interval1.split(":")[1].strip(" ");
    details_channel0 = InvokeGetSetMethod('WIFIHAL_GetOrSetParamULongValue',0,0,"getRadioChannel");
    RadioChannel_initial0 = int((details_channel0.split(":")[1].strip(" ")));
    details_channel1 = InvokeGetSetMethod('WIFIHAL_GetOrSetParamULongValue',1,0,"getRadioChannel");
    RadioChannel_initial1 = int((details_channel1.split(":")[1].strip(" ")));
    InvokeGetSetMethod('WIFIHAL_GetOrSetParamStringValue',0,"20MHz","setChannelBandwidth");
    InvokeGetSetMethod('WIFIHAL_GetOrSetParamStringValue',1,"20MHz","setChannelBandwidth");
    InvokeGetSetMethod('WIFIHAL_GetOrSetParamStringValue',0,"800nsec","setRadioGuardInterval");
    InvokeGetSetMethod('WIFIHAL_GetOrSetParamStringValue',1,"800nsec","setRadioGuardInterval");
    InvokeGetSetMethod('WIFIHAL_GetOrSetParamULongValue',0,int(9),"setRadioChannel");
    InvokeGetSetMethod('WIFIHAL_GetOrSetParamULongValue',1,int(36),"setRadioChannel");
    time.sleep(5);
    InvokeGetSetMethod('WIFIHAL_GetOrSetParamStringValue',0,"0","getChannelBandwidth");
    InvokeGetSetMethod('WIFIHAL_GetOrSetParamStringValue',1,"0","getChannelBandwidth");
    InvokeGetSetMethod('WIFIHAL_GetOrSetParamStringValue',0,"0","getRadioGuardInterval");
    InvokeGetSetMethod('WIFIHAL_GetOrSetParamStringValue',1,"0","getRadioGuardInterval");
    InvokeGetSetMethod('WIFIHAL_GetOrSetParamULongValue',0,0,"getRadioChannel");
    InvokeGetSetMethod('WIFIHAL_GetOrSetParamULongValue',1,0,"getRadioChannel");
    #call the factory reset radio api
    #Primitive test case which associated to this Script
    tdkTestObj = obj.createTestStep('WIFIHAL_FactoryReset');
    #Giving the method name to invoke the api wifi_factoryResetRadios()
    tdkTestObj.addParameter("methodName","factoryResetRadios");
    expectedresult="SUCCESS";
    tdkTestObj.executeTestCase(expectedresult);
    actualresult = tdkTestObj.getResult();
    details = tdkTestObj.getResultDetails();
    if expectedresult in actualresult:
	tdkTestObj.setResultStatus("SUCCESS");
	time.sleep(5);
	details_channel0_reset = InvokeGetSetMethod('WIFIHAL_GetOrSetParamULongValue',0,0,"getRadioChannel");
        RadioChannel0 = int((details_channel0_reset.split(":")[1].strip(" ")));
        details_channel1_reset = InvokeGetSetMethod('WIFIHAL_GetOrSetParamULongValue',1,0,"getRadioChannel");
        RadioChannel1 = int((details_channel1_reset.split(":")[1].strip(" ")));
	if RadioChannel0 != int(9) and RadioChannel1 != int(36):
	    tdkTestObj.setResultStatus("SUCCESS");
            print"TEST STEP1:To invoke wifi_factoryResetRadio() api and check whether the RadioChannel is not equal to the set value for both 2.4GHz and 5GHz";
	    print"EXPECTED RESULT1:RadioChannel should not be equal to the set value for both 2.4GHz and 5GHz";
	    print"ACTUAL RESULT1:RadioChannel is not equal to set value for both 2.4GHz and 5GHz";
	    print"{TEST EXECUTION RESULT1]:SUCCESS";
        else:
            tdkTestObj.setResultStatus("FAILURE");
            print"TEST STEP1:To invoke wifi_factoryResetRadio() api and check whether RadioChannel is not equal to the set value for both 2.4GHz and 5GHz";
	    print"EXPECTED RESULT1::RadioChannel should not be equal to the set value for both 2.4GHz and 5GHz";
	    print"ACTUAL RESULT1:RadioChannel is equal to set value for both 2.4GHz and 5GHz";
	    print"{TEST EXECUTION RESULT1]:FAILURE";
	    #Reverting the values back to initial values
	    InvokeGetSetMethod('WIFIHAL_GetOrSetParamULongValue',0,RadioChannel_initial0,"setRadioChannel");
            InvokeGetSetMethod('WIFIHAL_GetOrSetParamULongValue',1,RadioChannel_initial1,"setRadioChannel");
        details_BW0_reset = InvokeGetSetMethod('WIFIHAL_GetOrSetParamStringValue',0,"0","getChannelBandwidth");
        OperatingChannelBandwidth0 = details_BW0_reset.split(":")[1].strip(" ");
        details_BW1_reset = InvokeGetSetMethod('WIFIHAL_GetOrSetParamStringValue',1,"0","getChannelBandwidth");
        OperatingChannelBandwidth1 = details_BW1_reset.split(":")[1].strip(" ");
        if OperatingChannelBandwidth0 != "20MHz" and OperatingChannelBandwidth1 !="20MHz":
            tdkTestObj.setResultStatus("SUCCESS");
            print"TEST STEP2:To invoke wifi_factoryResetRadio() api and check whether the OperatingChannelBandwidth is not equal to the set value for both 2.4GHz and 5GHz";
	    print"EXPECTED RESULT2:OperatingChannelBandwidth should not be equal to the set value for both 2.4GHz and 5GHz";
	    print"ACTUAL RESULT2:OperatingChannelBandwidth is not equal to the set value for both 2.4GHz and 5GHz";
	    print"[TEST EXECUTION RESULT2]:SUCCESS";
        else:
            tdkTestObj.setResultStatus("FAILURE");
            print"TEST STEP2:To invoke wifi_factoryResetRadio() api and check whether the OperatingChannelBandwidth is not equal to the set value for both 2.4GHz and 5GHz";
	    print"EXPECTED RESULT2:OperatingChannelBandwidth should not be equal to the set value for both 2.4GHz and 5GHz";
	    print"ACTUAL RESULT2:OperatingChannelBandwidth is equal to the set value for both 2.4GHz and 5GHz";
	    print"[TEST EXECUTION RESULT2]:FAILURE";
	    #Reverting the values back to initial values
	    InvokeGetSetMethod('WIFIHAL_GetOrSetParamStringValue',0,OperatingChannelBandwidth_initial0,"setChannelBandwidth");
            InvokeGetSetMethod('WIFIHAL_GetOrSetParamStringValue',1,OperatingChannelBandwidth_initial1,"setChannelBandwidth");
        details_interval0_reset = InvokeGetSetMethod('WIFIHAL_GetOrSetParamStringValue',0,"0","getRadioGuardInterval");
        GuardInterval0 = details_interval0_reset.split(":")[1].strip(" ");
        details_interval1_reset = InvokeGetSetMethod('WIFIHAL_GetOrSetParamStringValue',1,"0","getRadioGuardInterval");
        GuardInterval1 = details_interval1_reset.split(":")[1].strip(" ");
        if GuardInterval0 != "800nsec" and GuardInterval1 != "800nsec" :
            tdkTestObj.setResultStatus("SUCCESS");
            print"TEST STEP3:To invoke wifi_factoryResetRadio() api and check whether the GuardInterval value is not equal to the set value for both 2.4GHz and 5GHz";
	    print"EXPECTED RESULT3:GuardInterval value should not be equal to the set value for both 2.4GHz and 5GHz";
	    print"ACTUAL RESULT3:GuardInterval value is not equal to the set value for both 2.4GHz and 5GHz";
	    print"[TEST EXECUTION RESULT3]:SUCCESS";
        else:
            tdkTestObj.setResultStatus("FAILURE");
            print"TEST STEP3:To invoke wifi_factoryResetRadio() api and check whether the GuardInterval value is not equal to the set value for both 2.4GHz and 5GHz";
	    print"EXPECTED RESULT3:GuardInterval value should not be equal to the set value for both 2.4GHz and 5GHz";
	    print"ACTUAL RESULT3:GuardInterval value is equal to the set value for both 2.4GHz and 5GHz";
	    print"[TEST EXECUTION RESULT3]:FAILURE";
	    #Reverting the values back to initial values
	    InvokeGetSetMethod('WIFIHAL_GetOrSetParamStringValue',0,GuardInterval_initial0,"setRadioGuardInterval");
            InvokeGetSetMethod('WIFIHAL_GetOrSetParamStringValue',1,GuardInterval_initial1,"setRadioGuardInterval");
    else:
        tdkTestObj.setResultStatus("FAILURE");
        print"wifi_factoryResetRadios() operation";
    obj.unloadModule("wifihal");
else:
    print "Failed to load wifi module";
    obj.setLoadModuleStatus("FAILURE");
