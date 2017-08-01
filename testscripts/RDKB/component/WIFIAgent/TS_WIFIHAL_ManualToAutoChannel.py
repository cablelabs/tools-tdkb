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
<?xml version="1.0" encoding="UTF-8"?><xml>
  <id/>
  <version>1</version>
  <name>TS_WIFIHAL_ManualToAutoChannel</name>
  <primitive_test_id/>
  <primitive_test_name>WIFIHal_CallMethodForULong</primitive_test_name>
  <primitive_test_version>1</primitive_test_version>
  <status>FREE</status>
  <synopsis/>
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
    <test_case_id>TC_WIFIAGENT_51</test_case_id>
    <test_objective>Test if on enabling autoChannel mode using wifi_setRadioAutoChannelEnable(), the manually set channel number is getting changed</test_objective>
    <test_type>Positive</test_type>
    <test_setup>XB3. XB6, Emulator, Rpi</test_setup>
    <pre_requisite>1.Ccsp Components  should be in a running state else invoke cosa_start.sh manually that includes all the ccsp components and TDK Component
2.TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>wifi_setRadioAutoChannelEnable()
wifi_setRadioChannel()
wifi_getRadioChannel()</api_or_interface_used>
    <input_parameters>methodName : getRadioChannel
methodName : eetRadioChannel
methodName : getRadioPossibleChannels
methodName : setAutoChannelEnable
radioIndex     :    1</input_parameters>
    <automation_approch>1. Load wifiagent module
2. Using wifi_getRadioChannel() get and save current channel
3. Set a new channel from possible channel list using wifi_setRadioChannel()
4. Enable autochannel mode using wifi_setRadioAutoChannelEnable()
5. Using wifi_getRadioChannel() get the current channel number and check if if it has changed from the manually set value
6. If not, return failure
6. Revert back to the previous channel value
5. Unload wifiagent module</automation_approch>
    <except_output>On enabling autoChannel mode using wifi_setRadioAutoChannelEnable(), the manually set channel number should get changed</except_output>
    <priority>High</priority>
    <test_stub_interface>WiFiAgent</test_stub_interface>
    <test_script>TS_WIFIHAL_ManualToAutoChannel</test_script>
    <skipped>No</skipped>
    <release_version/>
    <remarks/>
  </test_cases>
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
obj.configureTestCase(ip,port,'TS_WIFIHAL_ManualToAutoChannel');

loadmodulestatus =obj.getLoadModuleResult();
print "[LIB LOAD STATUS]  :  %s" %loadmodulestatus

if "SUCCESS" in loadmodulestatus.upper():
    obj.setLoadModuleStatus("SUCCESS");

    #get the current cahnnel number
    expectedresult="SUCCESS";
    radioIndex = 1
    getMethod = "getRadioChannel"
    param = 0
    primitive = 'WIFIHal_CallMethodForULong'
    tdkTestObj, actualresult, details = ExecuteWIFIHalCallMethod(obj, primitive, radioIndex, 0, getMethod)

    if expectedresult in actualresult :
        currChannel = int(details.split(":")[1].strip())

        #get the possible channel list
        getMethod = "getRadioPossibleChannels"
        primitive = 'WIFIHal_CallMethodForString'
        tdkTestObj, actualresult, details = ExecuteWIFIHalCallMethod(obj, primitive, radioIndex, 0, getMethod)

        if expectedresult in actualresult :
            possibleCh = details.split(":")[1].strip().split(',')
            #from possible channel list, select a channel != current channel num:, to do set operation
            for index in range(len(possibleCh)):
                if int(possibleCh[index]) != currChannel:
                    channel = int(possibleCh[index]) ;
                    break;

            #setchannel with the above selected channel number
            setMethod = "setRadioChannel"
            primitive = 'WIFIHal_CallMethodForULong'

            tdkTestObj, actualresult, details = ExecuteWIFIHalCallMethod(obj, primitive, radioIndex, channel, setMethod)
            if expectedresult in actualresult :
                print "Radio channel set"

		setMethod = "setAutoChannelEnable"
		primitive = "WIFIHal_CallMethodForBool"
		tdkTestObj, actualresult, details = ExecuteWIFIHalCallMethod(obj, primitive, radioIndex, 1, setMethod)

		primitive = 'WIFIHal_CallMethodForULong'
		if expectedresult in actualresult :
   		    getMethod = "getRadioChannel"
		    tdkTestObj, actualresult, details = ExecuteWIFIHalCallMethod(obj, primitive, radioIndex, 0, getMethod)
 		    channelAfterAuto = int(details.split(":")[1].strip())
		    if channelAfterAuto != channel :
			print "Channel number changed on enabling autocahannel mode"
		    else:
			tdkTestObj.setResultStatus("FAILURE");
			print "Channel number not changed on enabling autocahannel mode"

		#Reverting channel back
		setMethod = "setRadioChannel"
                tdkTestObj, actualresult, details = ExecuteWIFIHalCallMethod(obj, primitive, radioIndex, currChannel, setMethod)

                if expectedresult in actualresult :
                    print "Radio channel reverted back";
                else:
                    print "Couldn't revert channel num"
		    tdkTestObj.setResultStatus("FAILURE");

    obj.unloadModule("wifiagent");

else:
    print "Failed to load wifi module";
    obj.setLoadModuleStatus("FAILURE");
