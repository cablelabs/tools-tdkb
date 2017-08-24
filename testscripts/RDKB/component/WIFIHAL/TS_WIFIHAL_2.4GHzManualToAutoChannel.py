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
<?xml version="1.0" encoding="UTF-8"?>
<xml>
  <id/>
  <version>1</version>
  <name>TS_WIFIHAL_2.4GHzManualToAutoChannel</name>
  <primitive_test_id/>
  <primitive_test_name>WIFIHAL_GetOrSetParamBoolValue</primitive_test_name>
  <primitive_test_version>3</primitive_test_version>
  <status>FREE</status>
  <synopsis>Test if on enabling autoChannel mode using wifi_setRadioAutoChannelEnable(), the manually set channel number is getting changed for 2.4GHz</synopsis>
  <groups_id/>
  <execution_time>1</execution_time>
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
    <test_case_id>TC_WIFIHAL_35</test_case_id>
    <test_objective>Test if on enabling autoChannel mode using wifi_setRadioAutoChannelEnable(), the manually set channel number is getting changed for 2.4GHz</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Broadband,Emulator, RPI</test_setup>
    <pre_requisite>1.Ccsp Components  should be in a running state else invoke cosa_start.sh manually that includes all the ccsp components and TDK Component
2.TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>wifi_setRadioAutoChannelEnable()</api_or_interface_used>
    <input_parameters>methodName: setAutoChannelEnable
radioIndex:1</input_parameters>
    <automation_approch>1. Load wifihal module
2. Set the radio channel for 2.4GHz and enable autochannelenable
3.Check if the channel has changed or not
4. If not, return failure
5.Unload wifihal module</automation_approch>
    <except_output>The radio channel should change when auto channel is enabled</except_output>
    <priority>High</priority>
    <test_stub_interface>WIFIHAL</test_stub_interface>
    <test_script>TS_WIFIHAL_2.4GHzManualToAutoChannel</test_script>
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
obj.configureTestCase(ip,port,'TS_WIFIHAL_2.4GHzManualToAutoChannel');

#Get the result of connection with test component and DUT
loadmodulestatus =obj.getLoadModuleResult();
print "[LIB LOAD STATUS]  :  %s" %loadmodulestatus ;

if "SUCCESS" in loadmodulestatus.upper():
    obj.setLoadModuleStatus("SUCCESS");

    #Script to load the configuration file of the component
    tdkTestObj = obj.createTestStep("WIFIHAL_GetOrSetParamULongValue");
    #Giving the method name to invoke the api for getting Radio channel. ie,wifi_getRadioChannel()
    tdkTestObj.addParameter("methodName","getRadioChannel");
    #Radio index is 1 or 5 for 2.4GHz and 2 or 6 for 5GHz
    tdkTestObj.addParameter("radioIndex",1);
    expectedresult="SUCCESS";
    tdkTestObj.executeTestCase(expectedresult);
    actualresult = tdkTestObj.getResult();
    details = tdkTestObj.getResultDetails();
    currentChannel = details.split(":")[1];
    if expectedresult in actualresult:
        #Set the result status of execution
        tdkTestObj.setResultStatus("SUCCESS");
        print "TEST STEP 1: Get the Radio channel for 2.4GHz";
        print "EXPECTED RESULT 1: Should get the Radio channel for 2.4GHz";
        print "ACTUAL RESULT 1: %s" %details;
        #Get the result of execution
        print "[TEST EXECUTION RESULT] : SUCCESS";
	
	tdkTestObj = obj.createTestStep("WIFIHAL_GetOrSetParamStringValue");
    	#Giving the method name to invoke the api for getting possible Radio Channel. ie,wifi_getRadioPossibleChannels()
    	tdkTestObj.addParameter("methodName","getRadioPossibleChannels");
    	#Radio index is 0 for 2.4GHz and 1 for 5GHz
    	tdkTestObj.addParameter("radioIndex",0);
    	expectedresult="SUCCESS";
    	tdkTestObj.executeTestCase(expectedresult);
    	actualresult = tdkTestObj.getResult();
    	details = tdkTestObj.getResultDetails();
    	if expectedresult in actualresult:
    	    #Set the result status of execution
    	    tdkTestObj.setResultStatus("SUCCESS");
    	    print "TEST STEP 2: Get the possible Radio Channels for 2.4GHz";
    	    print "EXPECTED RESULT 2: Should get the possible Radio Channels for 2.4GHz";
    	    print "ACTUAL RESULT 2: %s" %details;
    	    #Get the result of execution
    	    print "[TEST EXECUTION RESULT] : SUCCESS";
   	    #if possible channels are given as a range eg: 1-11
	    if "-" in details:
            	#get the possible channels as a list of integers
            	PossibleChannelRange = [int(x) for x in details.split(":")[1].split("-")];
            	PossibleChannels = range(PossibleChannelRange[0],PossibleChannelRange[1]+1);
            	print "Possible channels are ", PossibleChannels;
            #if possible channels are given as values eg:1,2,3,4,5
            else:
        	#get the possible channels as a list of integers
        	PossibleChannels = [int(x) for x in details.split(",")];
        	print "Possible channels are ", PossibleChannels;
	    #select a channel from possible channels which is not the current channel
	    for i in PossibleChannels:
	        if i != int(currentChannel):
	            newChannel= i;
		    break;
	    print "New channel to set is ", newChannel;
	    
	    tdkTestObj = obj.createTestStep("WIFIHAL_GetOrSetParamULongValue");
            #Giving the method name to invoke the api for getting Radio Channel. ie,wifi_getRadioChannel()
            tdkTestObj.addParameter("methodName","setRadioChannel");
            #Radio index is 1 or 5 for 2.4GHz and 2 or 6 for 5GHz
            tdkTestObj.addParameter("radioIndex",1);
            tdkTestObj.addParameter("param",newChannel);
            expectedresult="SUCCESS";
            tdkTestObj.executeTestCase(expectedresult);
            actualresult = tdkTestObj.getResult();
            details = tdkTestObj.getResultDetails();
            if expectedresult in actualresult:
                #Set the result status of execution
                tdkTestObj.setResultStatus("SUCCESS");
                print "TEST STEP 3: Set new Radio channel for 2.4GHz";
                print "EXPECTED RESULT 3: Should  set the new Radio channel for 2.4GHz";
                print "ACTUAL RESULT 3: %s" %details;
                #Get the result of execution
                print "[TEST EXECUTION RESULT] : SUCCESS";
		
		tdkTestObj = obj.createTestStep("WIFIHAL_GetOrSetParamBoolValue");
	        #Giving the method name to invoke the api to set auto channel enable. ie,wifi_setRadioAutoChannelEnable()
		tdkTestObj.addParameter("methodName","setAutoChannelEnable");
        	#Radio index is 1 or 5 for 2.4GHz and 2 or 6 for 5GHz
        	tdkTestObj.addParameter("radioIndex",1);
        	tdkTestObj.addParameter("param",2);
        	expectedresult="SUCCESS";
        	tdkTestObj.executeTestCase(expectedresult);
        	actualresult = tdkTestObj.getResult();
        	details = tdkTestObj.getResultDetails();
        	if expectedresult in actualresult:
        	    #Set the result status of execution
        	    tdkTestObj.setResultStatus("SUCCESS");
        	    print "TEST STEP 4: Set the auto channel enable for 2.4GHz as true";
        	    print "EXPECTED RESULT 4: Should Set auto channel enable for 2.4GHz as true";
        	    print "ACTUAL RESULT 4: %s" %details;
        	    #Get the result of execution
        	    print "[TEST EXECUTION RESULT] : SUCCESS";
		   
		    tdkTestObj = obj.createTestStep("WIFIHAL_GetOrSetParamULongValue");
    		    #Giving the method name to invoke the api for getting Radio channel. ie,wifi_getRadioChannel()
    		    tdkTestObj.addParameter("methodName","getRadioChannel");
    		    #Radio index is 1 or 5 for 2.4GHz and 2 or 6 for 5GHz
    		    tdkTestObj.addParameter("radioIndex",1);
    		    expectedresult="SUCCESS";
    		    tdkTestObj.executeTestCase(expectedresult);
    		    actualresult = tdkTestObj.getResult();
    		    details = tdkTestObj.getResultDetails();
    		    ChannelAfterAuto = details.split(":")[1];
    		    if expectedresult in actualresult and int(ChannelAfterAuto) != newChannel:
    		        #Set the result status of execution
    		        tdkTestObj.setResultStatus("SUCCESS");
    		        print "TEST STEP 5: Get the Radio channel for 2.4GHz";
    		        print "EXPECTED RESULT 5: Should get the Radio channel for 2.4GHz";
    		        print "ACTUAL RESULT 5: %s" %details;
    		        #Get the result of execution
    		        print "[TEST EXECUTION RESULT] : SUCCESS";
		    else:
			#Set the result status of execution
                        tdkTestObj.setResultStatus("FAILURE");
                        print "TEST STEP 5: Get the Radio channel for 2.4GHz";
                        print "EXPECTED RESULT 5: Should get the Radio channel for 2.4GHz";
                        print "ACTUAL RESULT 5: %s" %details;
                        #Get the result of execution
                        print "[TEST EXECUTION RESULT] : FAILURE";
		else:
		    #Set the result status of execution
                    tdkTestObj.setResultStatus("FAILURE");
                    print "TEST STEP 4: Set the auto channel enable for 2.4GHz as true";
                    print "EXPECTED RESULT 4: Should Set auto channel enable for 2.4GHz as true";
                    print "ACTUAL RESULT 4: %s" %details;
                    #Get the result of execution
                    print "[TEST EXECUTION RESULT] : FAILURE";
	    else:
		#Set the result status of execution
                tdkTestObj.setResultStatus("FAILURE");
                print "TEST STEP 3: Set new Radio channel for 2.4GHz";
                print "EXPECTED RESULT 3: Should  set the new Radio channel for 2.4GHz";
                print "ACTUAL RESULT 3: %s" %details;
                #Get the result of execution
                print "[TEST EXECUTION RESULT] : FAILURE";
	    #set channel back
	    #Giving the method name to invoke the api for getting Radio Channel. ie,wifi_getRadioChannel()
            tdkTestObj.addParameter("methodName","setRadioChannel");
            #Radio index is 1 or 5 for 2.4GHz and 2 or 6 for 5GHz
            tdkTestObj.addParameter("radioIndex",1);
            tdkTestObj.addParameter("param",currentChannel);
            expectedresult="SUCCESS";
            tdkTestObj.executeTestCase(expectedresult);
            actualresult = tdkTestObj.getResult();
            details = tdkTestObj.getResultDetails();
            if expectedresult in actualresult:
                #Set the result status of execution
                tdkTestObj.setResultStatus("SUCCESS");
                print "TEST STEP : Set Radio channel for 2.4GHz";
                print "EXPECTED RESULT : Should set Radio channel for 2.4GHz";
                print "ACTUAL RESULT : %s" %details;
                #Get the result of execution
                print "[TEST EXECUTION RESULT] : SUCCESS";
	    else:
		#Set the result status of execution
                tdkTestObj.setResultStatus("FAILURE");
                print "TEST STEP : Set Radio channel for 2.4GHz";
                print "EXPECTED RESULT : Should set Radio channel for 2.4GHz";
                print "ACTUAL RESULT : %s" %details;
                #Get the result of execution
                print "[TEST EXECUTION RESULT] : FAILURE";
	else:
	    #Set the result status of execution
            tdkTestObj.setResultStatus("FAILURE");
            print "TEST STEP 2: Get the possible Radio Channels for 2.4GHz";
            print "EXPECTED RESULT 2: Should get the possible Radio Channels for 2.4GHz";
            print "ACTUAL RESULT 2: %s" %details;
            #Get the result of execution
            print "[TEST EXECUTION RESULT] : FAILURE";
    else:
	#Set the result status of execution
        tdkTestObj.setResultStatus("FAILURE");
        print "TEST STEP 1: Get the Radio channel for 2.4GHz";
        print "EXPECTED RESULT 1: Should get the Radio channel for 2.4GHz";
        print "ACTUAL RESULT 1: %s" %details;
        #Get the result of execution
        print "[TEST EXECUTION RESULT] : FAILURE";
    obj.unloadModule("wifihal");
else:
        print "Failed to load the module";
        obj.setLoadModuleStatus("FAILURE");
