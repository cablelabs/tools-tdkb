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
  <version>2</version>
  <name>TS_WIFIAGENT_5GHZ_ManualToAutoChannel</name>
  <primitive_test_id/>
  <primitive_test_name>WIFIAgent_Get</primitive_test_name>
  <primitive_test_version>1</primitive_test_version>
  <status>FREE</status>
  <synopsis>Test if when switching from manual to auto mode, channel value is getting changed</synopsis>
  <groups_id/>
  <execution_time>10</execution_time>
  <long_duration>false</long_duration>
  <advanced_script>false</advanced_script>
  <remarks/>
  <skip>false</skip>
  <box_types>
    <box_type>Broadband</box_type>
    <box_type>Emulator</box_type>
  </box_types>
  <rdk_versions>
    <rdk_version>RDKB</rdk_version>
  </rdk_versions>
  <test_cases>
    <test_case_id>TC_WIFIAGENT_32</test_case_id>
    <test_objective>Test if when switching from manual to auto mode, channel value is getting changed</test_objective>
    <test_type>Positive</test_type>
    <test_setup>XB3, Emulator, Rpi</test_setup>
    <pre_requisite>1.Ccsp Components in DUT should be in a running state that includes component under test Cable Modem
2.TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>WIFIAgent_Get
WIFIAgent_Set</api_or_interface_used>
    <input_parameters>Device.WiFi.Radio.2.AutoChannelEnable
Device.WiFi.Radio.2.PossibleChannels
Device.WiFi.Radio.2.Channel</input_parameters>
    <automation_approch>1. Load wifiagent module
2. Using WIFIAgent_Get, get and save Device.WiFi.Radio.2.AutoChannelEnable
3. Set Device.WiFi.Radio.2.AutoChannelEnable as false
4. Using WIFIAgent_Get, get Device.WiFi.Radio.2.PossibleChannels
5. Using WIFIAgent_Get, get and save 
 Device.WiFi.Radio.2.Channel
6. Using WIFIAgent_Set, set a value to Device.WiFi.Radio.2.Channel from possible channel list
7. Set Device.WiFi.Radio.2.AutoChannelEnable as true
8. After enabling auto mode, check if value of Device.WiFi.Radio.2.Channel is changed from the value set manually
9. Restrore values of Device.WiFi.Radio.2.AutoChannelEnable and Device.WiFi.Radio.2.Channel
10.  Unload wifiagent module
</automation_approch>
    <except_output>When switching from manual to auto mode, channel value should change from the manually set value</except_output>
    <priority>High</priority>
    <test_stub_interface>WifiAgent</test_stub_interface>
    <test_script>TS_WIFIAGENT_5GHZ_ManualToAutoChannel</test_script>
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

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("wifiagent","1");

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_WIFIAGENT_5GHZ_ManualToAutoChannel');

#Get the result of connection with test component and DUT
result =obj.getLoadModuleResult();
print "[LIB LOAD STATUS]  :  %s" %result;

#Get the result of connection with test component and DUT
loadmodulestatus =obj.getLoadModuleResult();
print "[LIB LOAD STATUS]  :  %s" %loadmodulestatus

if "SUCCESS" in loadmodulestatus.upper():
    obj.setLoadModuleStatus("SUCCESS");

    #save the orginal value of AutoChannelEnable
    tdkTestObj = obj.createTestStep('WIFIAgent_Get');
    tdkTestObj.addParameter("paramName","Device.WiFi.Radio.2.AutoChannelEnable")
    expectedresult="SUCCESS";

    #Execute the test case in DUT
    tdkTestObj.executeTestCase(expectedresult);
    actualresult = tdkTestObj.getResult();
    details = tdkTestObj.getResultDetails();
    orgAuto = details.split("VALUE:")[1].split(' ')[0];

    if expectedresult in actualresult:
        #Set the result status of execution
        tdkTestObj.setResultStatus("SUCCESS");
        print "TEST STEP 1: Get the AutoChannelEnable status"
        print "EXPECTED RESULT 1: Should get the AutoChannelEnable status"
        print "ACTUAL RESULT 1: Status is %s " %details
        print "[TEST EXECUTION RESULT] : SUCCESS";

        #Disable AutoChannelEnable
        tdkTestObj = obj.createTestStep('WIFIAgent_Set');
        tdkTestObj.addParameter("paramName","Device.WiFi.Radio.2.AutoChannelEnable")
        tdkTestObj.addParameter("paramValue","false")
        tdkTestObj.addParameter("paramType","boolean")
        tdkTestObj.executeTestCase(expectedresult);
        actualresult = tdkTestObj.getResult();
        details = tdkTestObj.getResultDetails();

        if expectedresult in actualresult:
            #Set the result status of execution
            tdkTestObj.setResultStatus("SUCCESS");
            print "TEST STEP 1: Disable auto channel"
            print "EXPECTED RESULT 1: Should Disable auto channel"
            print "ACTUAL RESULT 1:  %s " %details;
            #Get the result of execution
            print "[TEST EXECUTION RESULT] : SUCCESS";

            #get the list of possible channels
            tdkTestObj = obj.createTestStep('WIFIAgent_Get');
            tdkTestObj.addParameter("paramName","Device.WiFi.Radio.2.PossibleChannels")
            tdkTestObj.executeTestCase(expectedresult);
            actualresult = tdkTestObj.getResult();
            details = tdkTestObj.getResultDetails();
            possChannels = details.split("VALUE:")[1].split(' ')[0].split(',');

            if expectedresult in actualresult :
                tdkTestObj.setResultStatus("SUCCESS");
                print "TEST STEP 1: Get the list of possible channles"
                print "EXPECTED RESULT 1: Should get the list of possible channles"
                print "ACTUAL RESULT 1: channel list is %s " %details
                #Get the result of execution
                print "[TEST EXECUTION RESULT] : SUCCESS";

                #get the current channel and save it
                tdkTestObj = obj.createTestStep('WIFIAgent_Get');
                tdkTestObj.addParameter("paramName","Device.WiFi.Radio.2.Channel")
                tdkTestObj.executeTestCase(expectedresult);
                actualresult = tdkTestObj.getResult();
                details = tdkTestObj.getResultDetails();
                currChannel = details.split("VALUE:")[1].split(' ')[0]

                if expectedresult in actualresult :
                    #Set the result status of execution
                    tdkTestObj.setResultStatus("SUCCESS");
                    print "TEST STEP 1: Get the current channel"
                    print "EXPECTED RESULT 1: Should get the current channel"
                    print "ACTUAL RESULT 1: Channel is %s " %details
                    #Get the result of execution
                    print "[TEST EXECUTION RESULT] : SUCCESS";

                    #set a new channel value manually from possible list
                    for index in range(len(possChannels)):
                        if possChannels[index] != currChannel:
                            channel = possChannels[index] ;
                            break;
                    tdkTestObj = obj.createTestStep('WIFIAgent_Set');
                    tdkTestObj.addParameter("paramName","Device.WiFi.Radio.2.Channel")
                    tdkTestObj.addParameter("paramValue",channel)
                    tdkTestObj.addParameter("paramType","unsignedint")
                    tdkTestObj.executeTestCase(expectedresult);
                    actualresult1 = tdkTestObj.getResult();
                    details = tdkTestObj.getResultDetails();

		    time.sleep(5);
		    #get the current channel and compare it the set value
                    tdkTestObj = obj.createTestStep('WIFIAgent_Get');
                    tdkTestObj.addParameter("paramName","Device.WiFi.Radio.2.Channel")
                    tdkTestObj.executeTestCase(expectedresult);
                    actualresult2 = tdkTestObj.getResult();
                    details = tdkTestObj.getResultDetails();
                    newChannel = details.split("VALUE:")[1].split(' ')[0]

                    if expectedresult in actualresult1 and expectedresult in actualresult2 and newChannel == channel :
                         #Set the result status of execution
                        tdkTestObj.setResultStatus("SUCCESS");
                        print "TEST STEP 1: Set the current channela nd verify using get"
                        print "EXPECTED RESULT 1: Should set the current channel"
                        print "ACTUAL RESULT 1: Channel is %s " %details
                        #Get the result of execution
                        print "[TEST EXECUTION RESULT] : SUCCESS";

                        #get the AutoChannelEnable status
                        tdkTestObj = obj.createTestStep('WIFIAgent_Set');
		        tdkTestObj.addParameter("paramName","Device.WiFi.Radio.2.AutoChannelEnable")
		        tdkTestObj.addParameter("paramValue","true")
		        tdkTestObj.addParameter("paramType","boolean")
                        tdkTestObj.executeTestCase(expectedresult);
                        actualresult = tdkTestObj.getResult();
                        details = tdkTestObj.getResultDetails();

                        if expectedresult in actualresult :
                            tdkTestObj.setResultStatus("SUCCESS");
                            print "TEST STEP 1: Set AutoChannelEnable as true"
                            print "EXPECTED RESULT 1: Should Set AutoChannelEnable as true"
                            print "ACTUAL RESULT 1:  %s " %details
                            #Get the result of execution
                            print "[TEST EXECUTION RESULT] : SUCCESS";

			    time.sleep(5);
                            #check if channel value got changed after enabling autochannel
	                    tdkTestObj = obj.createTestStep('WIFIAgent_Get');
        	            tdkTestObj.addParameter("paramName","Device.WiFi.Radio.2.Channel")
                            tdkTestObj.executeTestCase(expectedresult);
                            actualresult = tdkTestObj.getResult();
                            details = tdkTestObj.getResultDetails();
			    newChannel = details.split("VALUE:")[1].split(' ')[0]

                            if expectedresult in actualresult and newChannel != channel:
                                tdkTestObj.setResultStatus("SUCCESS");
                                print "TEST STEP 1: Get channel value after enabling autochannel"
                                print "EXPECTED RESULT 1: should Get channel value after enabling autochannel";
                                print "ACTUAL RESULT 1:  %s " %details
                                #Get the result of execution
                                print "[TEST EXECUTION RESULT] : SUCCESS";
                            else:
                                tdkTestObj.setResultStatus("FAILURE");
                                print "TEST STEP 1: Get channel value after enabling autochannel"
                                print "EXPECTED RESULT 1: should Get channel value after enabling autochannel";
                                print "ACTUAL RESULT 1:  %s " %details
                                #Get the result of execution
                                print "[TEST EXECUTION RESULT] : FAILURE";

			else:
                            tdkTestObj.setResultStatus("SUCCESS");
                            print "TEST STEP 1: Set AutoChannelEnable as true"
                            print "EXPECTED RESULT 1: Should Set AutoChannelEnable as true"
                            print "ACTUAL RESULT 1:  %s " %details
                            #Get the result of execution
                            print "[TEST EXECUTION RESULT] : SUCCESS";

                        #set the channel value to previous one
                        tdkTestObj = obj.createTestStep('WIFIAgent_Set');
                        tdkTestObj.addParameter("paramName","Device.WiFi.Radio.2.Channel")
                        tdkTestObj.addParameter("paramValue",currChannel)
                        tdkTestObj.addParameter("paramType","unsignedint")
                        tdkTestObj.executeTestCase(expectedresult);
                        actualresult = tdkTestObj.getResult();
                        details = tdkTestObj.getResultDetails();

                        if expectedresult in actualresult:
                            tdkTestObj.setResultStatus("SUCCESS");
                            print "TEST STEP 1: Set channel value to orginal one"
                            print "EXPECTED RESULT 1: should set channel value to orginal one"
                            print "ACTUAL RESULT 1:  %s " %details
                            #Get the result of execution
                            print "[TEST EXECUTION RESULT] : SUCCESS";
                        else:
                            tdkTestObj.setResultStatus("FAILURE");
                            print "TEST STEP 1: Set channel value to orginal one"
                            print "EXPECTED RESULT 1: should set channel value to orginal one"
                            print "ACTUAL RESULT 1:  %s " %details
                            #Get the result of execution
                            print "[TEST EXECUTION RESULT] : FAILURE";

                    else:
                        tdkTestObj.setResultStatus("FAILURE");
                        print "TEST STEP 1: Set the current channel"
                        print "EXPECTED RESULT 1: Should set the current channel"
                        print "ACTUAL RESULT 1: Channel is %s " %details
                        #Get the result of execution
                        print "[TEST EXECUTION RESULT] : FAILURE";

                else:
                    tdkTestObj.setResultStatus("FAILURE");
                    print "TEST STEP 1: Get the current channel"
                    print "EXPECTED RESULT 1: Should get the current channel"
                    print "ACTUAL RESULT 1: Channel is %s " %details
                    #Get the result of execution
                    print "[TEST EXECUTION RESULT] : FAILURE";

            else:
                tdkTestObj.setResultStatus("FAILURE");
                print "TEST STEP 1: Get the list of possible channles"
                print "EXPECTED RESULT 1: Should get the list of possible channles"
                print "ACTUAL RESULT 1: channel list is %s " %details
                #Get the result of execution
                print "[TEST EXECUTION RESULT] : FAILURE";

            #set AutoChannelEnable to its previous value
            tdkTestObj = obj.createTestStep('WIFIAgent_Set');
            tdkTestObj.addParameter("paramName","Device.WiFi.Radio.2.AutoChannelEnable")
            tdkTestObj.addParameter("paramValue",orgAuto)
            tdkTestObj.addParameter("paramType","boolean")
            tdkTestObj.executeTestCase(expectedresult);
            actualresult = tdkTestObj.getResult();
            details = tdkTestObj.getResultDetails();

            if expectedresult in actualresult:
                #Set the result status of execution
                tdkTestObj.setResultStatus("SUCCESS");
                print "TEST STEP 1: Change auto channel to its previous value"
                print "EXPECTED RESULT 1: Should Change auto channel to its previous value"
                print "ACTUAL RESULT 1:  %s " %details;
                #Get the result of execution
                print "[TEST EXECUTION RESULT] : SUCCESS";
            else:
                tdkTestObj.setResultStatus("FAILURE");
                print "TEST STEP 1: Change auto channel to its previous value"
                print "EXPECTED RESULT 1: Should Change auto channel to its previous value"
                print "ACTUAL RESULT 1:  %s " %details;
                #Get the result of execution
                print "[TEST EXECUTION RESULT] : FAILURE";
        else:
            tdkTestObj.setResultStatus("FAILURE");
            print "TEST STEP 1: Disable auto channel"
            print "EXPECTED RESULT 1: Should Disable auto channel"
            print "ACTUAL RESULT 1:  %s " %details;
            #Get the result of execution
            print "[TEST EXECUTION RESULT] : FAILURE";

    else:
        tdkTestObj.setResultStatus("FAILURE");
        print "TEST STEP 1: Get the AutoChannelEnable status"
        print "EXPECTED RESULT 1: Should get the AutoChannelEnable status"
        print "ACTUAL RESULT 1: Status is %s " %details
        #Get the result of execution
        print "[TEST EXECUTION RESULT] : FAILURE";

    obj.unloadModule("wifiagent");

else:
        print "Failed to load wifi module";
        obj.setLoadModuleStatus("FAILURE");
