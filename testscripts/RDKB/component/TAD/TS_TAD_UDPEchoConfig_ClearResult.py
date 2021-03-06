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
  <name>TS_TAD_UDPEchoConfig_ClearResult</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id> </primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>TADstub_Set</primitive_test_name>
  <!--  -->
  <primitive_test_version>1</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>To check if the result details are getting cleared when UDPEchoConfig is enabled</synopsis>
  <!--  -->
  <groups_id />
  <!--  -->
  <execution_time>3</execution_time>
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
  </box_types>
  <rdk_versions>
    <rdk_version>RDKB</rdk_version>
    <!--  -->
  </rdk_versions>
  <test_cases>
    <test_case_id>TC_TAD_44</test_case_id>
    <test_objective>To check if the result details are getting cleared when UDPEchoConfig is enabled</test_objective>
    <test_type>Positive</test_type>
    <test_setup>XB3,Emulator</test_setup>
    <pre_requisite>1.Ccsp Components  should be in a running state else invoke cosa_start.sh manually that includes all the ccsp components.
2.TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>TADstub_Set,TADstub_Get</api_or_interface_used>
    <input_parameters>Device.IP.Diagnostics.UDPEchoConfig.SourceIPAddress
Device.IP.Diagnostics.UDPEchoConfig.Interface
Device.IP.Diagnostics.UDPEchoConfig.UDPPort
Device.IP.Diagnostics.UDPEchoConfig.Enable
Device.IP.Diagnostics.UDPEchoConfig.BytesReceived</input_parameters>
    <automation_approch>1. Load  TAD modules
2. From script invoke TADstub_Set to set all the UDPEchoConfig parameters
3. Enable the UDPEchoConfig
4. Send UDP echo request with source ip address
5. Check whether packets are received or not
6. Disable and enable UDPEchoConfig 
7. verify that all the result details are cleared
8. Validation of  the result is done within the python script and send the result status to Test Manager.
9.Test Manager will publish the result in GUI as PASS/FAILURE based on the response from TAD stub.</automation_approch>
    <except_output>CheckPoint 1:
 The output  should be logged in the Agent console/Component log

CheckPoint 2:
Stub function result should be success and should see corresponding log in the agent console log

CheckPoint 3:
TestManager GUI will publish the result as PASS in Execution/Console page of Test Manager</except_output>
    <priority>High</priority>
    <test_stub_interface>None</test_stub_interface>
    <test_script>TS_TAD_UDPEchoConfig_ClearResult</test_script>
    <skipped>No</skipped>
    <release_version></release_version>
    <remarks></remarks>
  </test_cases>
  <script_tags />
</xml>
'''
# use tdklib library,which provides a wrapper for tdk testcase script
import tdklib;
import time;

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("tad","1");
sysObj = tdklib.TDKScriptingLibrary("sysutil","RDKB");

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_TAD_UDPEchoConfig_ClearResult');
sysObj.configureTestCase(ip,port,'TS_TAD_UDPEchoConfig_ClearResult');

#Get the result of connection with test component and DUT
loadmodulestatus =obj.getLoadModuleResult();
sysloadmodulestatus=sysObj.getLoadModuleResult();
print "[LIB LOAD STATUS]  :  %s" %loadmodulestatus ;
if "SUCCESS" in loadmodulestatus.upper() and sysloadmodulestatus.upper():
    #Set the result status of execution
    obj.setLoadModuleStatus("SUCCESS");
    tdkTestObj = obj.createTestStep('TADstub_Set');
    tdkTestObj.addParameter("ParamName","Device.IP.Diagnostics.UDPEchoConfig.Interface");
    tdkTestObj.addParameter("ParamValue","");
    tdkTestObj.addParameter("Type","string");
    expectedresult="SUCCESS";
    tdkTestObj.executeTestCase(expectedresult);
    actualresult = tdkTestObj.getResult();
    details = tdkTestObj.getResultDetails();
    if expectedresult in actualresult:
        #Set the result status of execution
        tdkTestObj.setResultStatus("SUCCESS");
        print "TEST STEP 1: Set the interface of UDPEchoConfig";
        print "EXPECTED RESULT 1: Should set the interface of UDPEchoConfig";
        print "ACTUAL RESULT 1: %s" %details;
        #Get the result of execution
        print "[TEST EXECUTION RESULT] : SUCCESS";

        tdkTestObj = obj.createTestStep('TADstub_Set');
        tdkTestObj.addParameter("ParamName","Device.IP.Diagnostics.UDPEchoConfig.SourceIPAddress");
        tdkTestObj.addParameter("ParamValue",ip);
        tdkTestObj.addParameter("Type","string");
        expectedresult="SUCCESS";
        tdkTestObj.executeTestCase(expectedresult);
        actualresult = tdkTestObj.getResult();
        details = tdkTestObj.getResultDetails();
        if expectedresult in actualresult:
            #Set the result status of execution
            tdkTestObj.setResultStatus("SUCCESS");
            print "TEST STEP 2: Set the source IP of UDPEchoconfig";
            print "EXPECTED RESULT 2: Should set the source IP of UDPEchoConfig";
            print "ACTUAL RESULT 2: %s" %details;
            #Get the result of execution
            print "[TEST EXECUTION RESULT] : SUCCESS";
            tdkTestObj = obj.createTestStep('TADstub_Set');
            tdkTestObj.addParameter("ParamName","Device.IP.Diagnostics.UDPEchoConfig.UDPPort");
            tdkTestObj.addParameter("ParamValue","7");
            tdkTestObj.addParameter("Type","unsignedint");
            expectedresult="SUCCESS";
            tdkTestObj.executeTestCase(expectedresult);
            actualresult = tdkTestObj.getResult();
            details = tdkTestObj.getResultDetails();
            if expectedresult in actualresult:
                #Set the result status of execution
                tdkTestObj.setResultStatus("SUCCESS");
                print "TEST STEP 3: Set the port of UDPEchoconfig";
                print "EXPECTED RESULT 3: Should set the port of UDPEchoConfig";
                print "ACTUAL RESULT 3: %s" %details;
                #Get the result of execution
                print "[TEST EXECUTION RESULT] : SUCCESS";

                tdkTestObj = obj.createTestStep('TADstub_Set');
                tdkTestObj.addParameter("ParamName","Device.IP.Diagnostics.UDPEchoConfig.Enable");
                tdkTestObj.addParameter("ParamValue","true");
                tdkTestObj.addParameter("Type","boolean");
                expectedresult="SUCCESS";
                tdkTestObj.executeTestCase(expectedresult);
                actualresult = tdkTestObj.getResult();
                details = tdkTestObj.getResultDetails();
                if expectedresult in actualresult:
                    #Set the result status of execution
                    tdkTestObj.setResultStatus("SUCCESS");
                    print "TEST STEP 4: Set UDPEchoConfig  as Enabled";
                    print "EXPECTED RESULT 4: Should set  UDPEchoConfig  as Enabled";
                    print "ACTUAL RESULT 4: %s" %details;
                    #Get the result of execution
                    print "[TEST EXECUTION RESULT] : SUCCESS";
                    tdkTestObj = sysObj.createTestStep('ExecuteCmd');
                    command = "echo UDPEchoTest > /dev/udp/"+ip+"/7";
                    print command;
                    tdkTestObj.addParameter("command",command);
                    expectedresult="SUCCESS";

                    #Execute the test case in STB
                    tdkTestObj.executeTestCase(expectedresult);
                    actualresult = tdkTestObj.getResult();
                    details = tdkTestObj.getResultDetails().strip();

                    if expectedresult in actualresult:
                        #Set the result status of execution
                        tdkTestObj.setResultStatus("SUCCESS");
                        print "TEST STEP 5: Send a valid UDP request";
                        print "EXPECTED RESULT 5: Should send UDP request";
                        print "ACTUAL RESULT 5:UDP request has sent";
                        #Get the result of execution
                        print "[TEST EXECUTION RESULT] : SUCCESS";
                        tdkTestObj = obj.createTestStep('TADstub_Get');
                        tdkTestObj.addParameter("paramName","Device.IP.Diagnostics.UDPEchoConfig.BytesReceived");
                        expectedresult="SUCCESS";
                        tdkTestObj.executeTestCase(expectedresult);
                        actualresult = tdkTestObj.getResult();
                        pkts_rcvd = tdkTestObj.getResultDetails();
                        if expectedresult in actualresult and int(pkts_rcvd)>0:
                            #Set the result status of execution
                            tdkTestObj.setResultStatus("SUCCESS");
                            print "TEST STEP 6: Check if the bytes received is greater than zero";
                            print "EXPECTED RESULT 6: Should get the bytes received greater than zero";
                            print "ACTUAL RESULT 6: %s" %pkts_rcvd;
                            #Get the result of execution
                            print "[TEST EXECUTION RESULT] : SUCCESS";
                            #disable UDPEcho config
                            tdkTestObj = obj.createTestStep('TADstub_Set');
                            tdkTestObj.addParameter("ParamName","Device.IP.Diagnostics.UDPEchoConfig.Enable");
                            tdkTestObj.addParameter("ParamValue","false");
                            tdkTestObj.addParameter("Type","boolean");
                            expectedresult="SUCCESS";
                            tdkTestObj.executeTestCase(expectedresult);
                            actualresult = tdkTestObj.getResult();
                            details = tdkTestObj.getResultDetails();
                            if expectedresult in actualresult:
                                #Set the result status of execution
                                tdkTestObj.setResultStatus("SUCCESS");
                                print "TEST STEP 7: Set UDPEchoConfig  as Disabled";
                                print "EXPECTED RESULT 7: Should set  UDPEchoConfig  as Disabled";
                                print "ACTUAL RESULT 7: %s" %details;
                                #Get the result of execution
                                print "[TEST EXECUTION RESULT] : SUCCESS";
				time.sleep(10);
				tdkTestObj = obj.createTestStep('TADstub_Set');
                		tdkTestObj.addParameter("ParamName","Device.IP.Diagnostics.UDPEchoConfig.Enable");
                		tdkTestObj.addParameter("ParamValue","true");
                		tdkTestObj.addParameter("Type","boolean");
                		expectedresult="SUCCESS";
                		tdkTestObj.executeTestCase(expectedresult);
                		actualresult = tdkTestObj.getResult();
                		details = tdkTestObj.getResultDetails();
                		if expectedresult in actualresult:
                		    #Set the result status of execution
                		    tdkTestObj.setResultStatus("SUCCESS");
                		    print "TEST STEP 8: Set UDPEchoConfig  as Enabled";
                		    print "EXPECTED RESULT 8: Should set  UDPEchoConfig  as Enabled";
                		    print "ACTUAL RESULT 8: %s" %details;
                		    #Get the result of execution
                		    print "[TEST EXECUTION RESULT] : SUCCESS";
				    time.sleep(10);
				    tdkTestObj = obj.createTestStep('TADstub_Get');
                        	    tdkTestObj.addParameter("paramName","Device.IP.Diagnostics.UDPEchoConfig.BytesReceived");
                        	    expectedresult="SUCCESS";
                        	    tdkTestObj.executeTestCase(expectedresult);
                        	    actualresult = tdkTestObj.getResult();
                        	    pkts_rcvd = tdkTestObj.getResultDetails();
                        	    if expectedresult in actualresult and int(pkts_rcvd)==0:
                        	        #Set the result status of execution
                        	        tdkTestObj.setResultStatus("SUCCESS");
                        	        print "TEST STEP 9: Check if the bytes received is equal to zero";
                        	        print "EXPECTED RESULT 9: Should get the bytes received is equal to zero";
                        	        print "ACTUAL RESULT 9: %s" %pkts_rcvd;
                        	        #Get the result of execution
                        	        print "[TEST EXECUTION RESULT] : SUCCESS";
				    else:
					#Set the result status of execution
                                        tdkTestObj.setResultStatus("FAILURE");
                                        print "TEST STEP 9: Check if the bytes received is equal to zero";
                                        print "EXPECTED RESULT 9: Should get the bytes received is equal to zero";
                                        print "ACTUAL RESULT 9: %s" %pkts_rcvd;
                                        #Get the result of execution
                                        print "[TEST EXECUTION RESULT] : FAILURE";
				else:
				    #Set the result status of execution
                                    tdkTestObj.setResultStatus("FAILURE");
                                    print "TEST STEP 8: Set UDPEchoConfig  as Enabled";
                                    print "EXPECTED RESULT 8: Should set  UDPEchoConfig  as Enabled";
                                    print "ACTUAL RESULT 8: %s" %details;
                                    #Get the result of execution
                                    print "[TEST EXECUTION RESULT] : FAILURE";
			    else:
				#Set the result status of execution
                                tdkTestObj.setResultStatus("FAILURE");
                                print "TEST STEP 7: Set UDPEchoConfig  as Disabled";
                                print "EXPECTED RESULT 7: Should set  UDPEchoConfig  as Disabled";
                                print "ACTUAL RESULT 7: %s" %details;
                                #Get the result of execution
                                print "[TEST EXECUTION RESULT] : FAILURE";
			else:
			    #Set the result status of execution
                            tdkTestObj.setResultStatus("FAILURE");
                            print "TEST STEP 6: Check if the bytes received is greater than zero";
                            print "EXPECTED RESULT 6: Should get the bytes received greater than zero";
                            print "ACTUAL RESULT 6: %s" %pkts_rcvd;
                            #Get the result of execution
                            print "[TEST EXECUTION RESULT] : FAILURE";
		    else:
			#Set the result status of execution
                        tdkTestObj.setResultStatus("FAILURE");
                        print "TEST STEP 5: Send a valid UDP request";
                        print "EXPECTED RESULT 5: Should send UDP request";
                        print "ACTUAL RESULT 5:UDP request has sent";
                        #Get the result of execution
                        print "[TEST EXECUTION RESULT] : FAILURE";
		    #disable UDPEcho config
                    tdkTestObj = obj.createTestStep('TADstub_Set');
                    tdkTestObj.addParameter("ParamName","Device.IP.Diagnostics.UDPEchoConfig.Enable");
                    tdkTestObj.addParameter("ParamValue","false");
                    tdkTestObj.addParameter("Type","boolean");
                    expectedresult="SUCCESS";
                    tdkTestObj.executeTestCase(expectedresult);
                    actualresult = tdkTestObj.getResult();
                    details = tdkTestObj.getResultDetails();
                    if expectedresult in actualresult:
                        #Set the result status of execution
                        tdkTestObj.setResultStatus("SUCCESS");
                        print "TEST STEP : Set UDPEchoConfig  as Disabled";
                        print "EXPECTED RESULT : Should set  UDPEchoConfig  as Disabled";
                        print "ACTUAL RESULT : %s" %details;
                       #Get the result of execution
                        print "[TEST EXECUTION RESULT] : SUCCESS";
                    else:
                        #Set the result status of execution
                        tdkTestObj.setResultStatus("FAILURE");
                        print "TEST STEP : Set UDPEchoConfig  as Disabled";
                        print "EXPECTED RESULT : Should set  UDPEchoConfig  as Disabled";
                        print "ACTUAL RESULT : %s" %details;
                        #Get the result of execution
                        print "[TEST EXECUTION RESULT] : FAILURE";
		else:
		    #Set the result status of execution
                    tdkTestObj.setResultStatus("FAILURE");
                    print "TEST STEP 4: Set UDPEchoConfig  as Enabled";
                    print "EXPECTED RESULT 4: Should set  UDPEchoConfig  as Enabled";
                    print "ACTUAL RESULT 4: %s" %details;
                    #Get the result of execution
                    print "[TEST EXECUTION RESULT] : FAILURE";
	    else:
		#Set the result status of execution
                tdkTestObj.setResultStatus("FAILURE");
                print "TEST STEP 3: Set the port of UDPEchoconfig";
                print "EXPECTED RESULT 3: Should set the port of UDPEchoConfig";
                print "ACTUAL RESULT 3: %s" %details;
                #Get the result of execution
                print "[TEST EXECUTION RESULT] : FAILURE";
	else:
	    #Set the result status of execution
            tdkTestObj.setResultStatus("FAILURE");
            print "TEST STEP 2: Set the source IP of UDPEchoconfig";
            print "EXPECTED RESULT 2: Should set the source IP of UDPEchoConfig";
            print "ACTUAL RESULT 2: %s" %details;
            #Get the result of execution
            print "[TEST EXECUTION RESULT] : FAILURE";
    else:
	#Set the result status of execution
        tdkTestObj.setResultStatus("FAILURE");
        print "TEST STEP 1: Set the interface of UDPEchoConfig";
        print "EXPECTED RESULT 1: Should set the interface of UDPEchoConfig";
        print "ACTUAL RESULT 1: %s" %details;
        #Get the result of execution
        print "[TEST EXECUTION RESULT] : FAILURE";
    sysObj.unloadModule("sysutil");
    obj.unloadModule("tad");

else:
        print "Failed to load tad module";
        obj.setLoadModuleStatus("FAILURE");
