##########################################################################
# If not stated otherwise in this file or this component's Licenses.txt
# file the following copyright and licenses apply:
#
# Copyright 2016 RDK Management
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
  <name>TS_WIFIHAL_2.4GHzIsRadioEnabled</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id> </primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>WIFIHAL_GetOrSetParamBoolValue</primitive_test_name>
  <!--  -->
  <primitive_test_version>1</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>To check enable Status of 2.4Ghz Radio using wifi_getRadioEnable() HAL API </synopsis>
  <!--  -->
  <groups_id>4</groups_id>
  <!--  -->
  <execution_time>1</execution_time>
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
     <box_type>Emulator</box_type>
     <box_type>RPI</box_type>
  </box_types>
  <rdk_versions>
    <rdk_version>RDKB</rdk_version>
    <!--  -->
  </rdk_versions>
  <test_cases>
    <test_case_id>TC_WIFIHAL_51</test_case_id>
    <test_objective>To check enable Status of 2.4Ghz Radio using wifi_getRadioEnable() HAL API </test_objective>
    <test_type>Positive</test_type>
    <test_setup>XB3. XB6, Emulator, Rpi</test_setup>
    <pre_requisite>1.Ccsp Components  should be in a running state else invoke cosa_start.sh manually that includes all the ccsp components and TDK Component
2.TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>wifi_getRadioEnable()
wifi_getRadioEnable()</api_or_interface_used>
    <input_parameters>
methodName : getRadioEnable
methodName : setRadioEnable
radioIndex : 0
    </input_parameters>
    <automation_approch>
1.Configure the Function info in Test Manager GUI  which needs to be tested  
(WIFIHAL_GetOrSetParamBoolValue  - func name - "If not exists already"
 WIFIHAL - module name
 Necessary I/P args as Mentioned in Input)
2.Python Script will be generated/overrided automatically by Test Manager with provided arguments in configure page (TS_WIFIHAL_2.4GHzIsRadioEnabled.py)
3.Execute the generated Script(TS_WIFIHAL_2.4GHzIsRadioEnabled.py) using execution page of  Test Manager GUI
4.wifihalstub which is a part of TDK Agent process, will be in listening mode to execute TDK Component function named WIFIHAL_GetOrSetParamBoolValue through registered TDK wifihalstub function along with necessary arguments
5.WIFIHAL_GetOrSetParamBoolValue function will call Ccsp Base Function named "ssp_WIFIHALGetOrSetParamBoolValue", that inturn will call WIFIHAL Library Functions 
wifi_getRadioEnable() and wifi_setRadioEnable()
6.Response(s)(printf) from TDK Component,Ccsp Library function and wifihalstub would be logged in Agent Console log based on the debug info redirected to agent console
7.wifihalstub will validate the available result (from agent console log and Pointer to instance as updated) with expected result
8.Test Manager will publish the result in GUI as SUCCESS/FAILURE based on the response from wifihalstub
    </automation_approch>
    <except_output>set operation using wifi_getRadioEnable() should be success</except_output>
    <priority>High</priority>
    <test_stub_interface>wifihal</test_stub_interface>
    <test_script>TS_WIFIHAL_2.4GHzIsRadioEnabled</test_script>
    <skipped>No</skipped>
    <release_version></release_version>
    <remarks></remarks>
  </test_cases>
  <script_tags />
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
obj.configureTestCase(ip,port,'TS_WIFIHAL_2.4GHzIsRadioEnabled');

loadmodulestatus =obj.getLoadModuleResult();
print "[LIB LOAD STATUS]  :  %s" %loadmodulestatus

if "SUCCESS" in loadmodulestatus.upper():
    obj.setLoadModuleStatus("SUCCESS");

    expectedresult="SUCCESS";
    radioIndex = 0
    getMethod = "getRadioEnable"
    primitive = 'WIFIHAL_GetOrSetParamBoolValue'
    #Getting the default enable mode
    tdkTestObj, actualresult, details = ExecuteWIFIHalCallMethod(obj, primitive, radioIndex, 0, getMethod)

    if expectedresult in actualresult :
        tdkTestObj.setResultStatus("SUCCESS");
        enable = details.split(":")[1].strip()
        if "Enabled" in enable:
            print "Radio 2.4GHz is Enabled"
	    oldEnable = 1
            newEnable = 0
        else:
            print "Radio 2.4GHz is Disabled"
	    oldEnable = 0
            newEnable = 1

        setMethod = "setRadioEnable"
        #Toggle the enable status using set
        tdkTestObj, actualresult, details = ExecuteWIFIHalCallMethod(obj, primitive, radioIndex, newEnable, setMethod)

        if expectedresult in actualresult :
            print "Enable state toggled using set"
            #Get the New enable status
            tdkTestObj, actualresult, details = ExecuteWIFIHalCallMethod(obj, primitive, radioIndex, 0, getMethod)

            if expectedresult in actualresult and enable not in details.split(":")[1].strip():
                print "getEnable Success, verified along with setEnable() api"
                #Revert back to original Enable status
                tdkTestObj, actualresult, details = ExecuteWIFIHalCallMethod(obj, primitive, radioIndex, oldEnable, setMethod)

                if expectedresult in actualresult :
                    print "Enable status reverted back";
                else:
                    print "Couldn't revert enable status"
                    tdkTestObj.setResultStatus("FAILURE");
            else:
                print "getRadioEnable() failed"
		tdkTestObj.setResultStatus("FAILURE");
        else:
            print "setRadioEnable() failed"
            tdkTestObj.setResultStatus("FAILURE");	
    else:
        print "getRadioEnable() failed" 
        tdkTestObj.setResultStatus("FAILURE");

    obj.unloadModule("wifihal");

else:
    print "Failed to load wifi module";
    obj.setLoadModuleStatus("FAILURE");

