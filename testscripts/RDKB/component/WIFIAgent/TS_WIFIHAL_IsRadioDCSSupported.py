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
  <version>4</version>
  <!-- Do not edit version. This will be auto incremented while updating. If you are adding a new script you can keep the vresion as 1 -->
  <name>TS_WIFIHAL_IsRadioDCSSupported</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id> </primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>WIFIHal_CallMethodForBool</primitive_test_name>
  <!--  -->
  <primitive_test_version>1</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>Check if dynamic channel selection(DCS) is supported, using wifi_getRadioDCSSupported(). If so get DCS enable status using wifi_getRadioDCSEnable()</synopsis>
  <!--  -->
  <groups_id />
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
    <test_case_id>TC_WIFIAGENT_50</test_case_id>
    <test_objective>Check if dynamic channel selection(DCS) is supported, using wifi_getRadioDCSSupported(). If so get DCS enable status using wifi_getRadioDCSEnable()</test_objective>
    <test_type>Positive</test_type>
    <test_setup>XB3. XB6, Emulator, Rpi</test_setup>
    <pre_requisite>1.Ccsp Components  should be in a running state else invoke cosa_start.sh manually that includes all the ccsp components and TDK Component
2.TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>wifi_getRadioDCSEnable()
wifi_getRadioDCSSupported()</api_or_interface_used>
    <input_parameters>methodName : getRadioDCSSupported
methodName : getRadioDCSEnable
radioIndex     :    1</input_parameters>
    <automation_approch>1. Load wifiagent module
2. Invoke wifi_getRadioDCSSupported()  to to check if DCS is supported or not 
3.If supported, get the DCS enable status using wifi_getRadioDCSEnable()
4. If not supported, return failure
5. Unload wifiagent module</automation_approch>
    <except_output>DCS should be supported</except_output>
    <priority>High</priority>
    <test_stub_interface>WiFiAgent</test_stub_interface>
    <test_script>TS_WIFIHAL_IsRadioDCSSupported</test_script>
    <skipped>No</skipped>
    <release_version></release_version>
    <remarks></remarks>
  </test_cases>
  <script_tags />
</xml>
'''
# use tdklib library,which provides a wrapper for tdk testcase script 
import tdklib; 
from wifiUtility import *

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("wifiagent","1");

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_WIFIHAL_IsRadioDCSSupported');

loadmodulestatus =obj.getLoadModuleResult();
print "[LIB LOAD STATUS]  :  %s" %loadmodulestatus

if "SUCCESS" in loadmodulestatus.upper():
    obj.setLoadModuleStatus("SUCCESS");

    expectedresult="SUCCESS";
    radioIndex = 1
    getMethod = "getRadioDCSSupported"
    primitive = 'WIFIHal_CallMethodForBool'
    tdkTestObj, actualresult, details = ExecuteWIFIHalCallMethod(obj, primitive, radioIndex, 0, getMethod)

    if expectedresult in actualresult :
        enable = details.split(":")[1].strip()
        if "Enabled" in enable:
	    print "RadioDCS is Supported"
	    tdkTestObj.setResultStatus("SUCCESS");

	    getMethod = "getRadioDCSEnable"
	    tdkTestObj, actualresult, details = ExecuteWIFIHalCallMethod(obj, primitive, radioIndex, 0, getMethod)

	    if expectedresult in actualresult :
	        enable = details.split(":")[1].strip()
        	if "Enabled" in enable:
                    print "RadioDCS is Enabled"
		else:
		    print "RadioDCS is Disabled"
	    else:
		print "getRadioDCSEnable() failed"
	else:
            print "RadioDCS is not Supported"
            tdkTestObj.setResultStatus("FAILURE");
    else:
	print "getRadioDCSSupported() failed"

    obj.unloadModule("wifiagent");

else:
    print "Failed to load wifi module";
    obj.setLoadModuleStatus("FAILURE");

