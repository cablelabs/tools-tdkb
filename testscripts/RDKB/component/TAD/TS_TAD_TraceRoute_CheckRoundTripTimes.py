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
  <version>2</version>
  <name>TS_TAD_TraceRoute_CheckRoundTripTimes</name>
  <primitive_test_id/>
  <primitive_test_name>TADstub_Get</primitive_test_name>
  <primitive_test_version>3</primitive_test_version>
  <status>FREE</status>
  <synopsis>To get the round trip time in milliseconds for each hop and check whether the list not contains more than  3 items.</synopsis>
  <groups_id/>
  <execution_time>2</execution_time>
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
    <test_case_id>TC_TAD_09</test_case_id>
    <test_objective>To get the round trip time in milliseconds for each hop and check whether the list not contains more than  3 items</test_objective>
    <test_type>Positive</test_type>
    <test_setup>XB3,Emulator</test_setup>
    <pre_requisite>1.Ccsp Components  should be in a running state else invoke cosa_start.sh manually that includes all the ccsp components.
2.TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>TADstub_Get, TADstub_Set</api_or_interface_used>
    <input_parameters>Device.IP.Diagnostics.TraceRoute.Interface
Device.IP.Diagnostics.TraceRoute.Host
Device.IP.Diagnostics.TraceRoute.DiagnosticsState
Device.IP.Diagnostics.TraceRoute.RouteHopsNumberOfEntries</input_parameters>
    <automation_approch>1. Load TAD modules
2. From script invoke TADstub_Set to set all the parameters of trace route
3. if set is success, check the round trip times using TADstub_Get
4. Check if the list contains only 3 items
5. Validation of  the result is done within the python script and send the result status to Test Manager.
6.Test Manager will publish the result in GUI as PASS/FAILURE based on the response from TAD stub.</automation_approch>
    <except_output>CheckPoint 1:
 The output  should be logged in the Agent console/Component log

CheckPoint 2:
Stub function result should be success and should see corresponding log in the agent console log

CheckPoint 3:
TestManager GUI will publish the result as PASS in Execution/Console page of Test Manager</except_output>
    <priority>High</priority>
    <test_stub_interface>None</test_stub_interface>
    <test_script>TS_TAD_TraceRoute_CheckRoundTripTimes</test_script>
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
import tdkutility;

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("tad","1");

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_TAD_TraceRoute_CheckRoundTripTimes');
#Get the result of connection with test component and STB
loadmodulestatus =obj.getLoadModuleResult();
print "[LIB LOAD STATUS]  :  %s" %loadmodulestatus ;

if "SUCCESS" in loadmodulestatus.upper():
    #Set the result status of execution
    obj.setLoadModuleStatus("SUCCESS");
    host = tdkutility.readtdkbConfigFile(obj);
    tdkTestObj = obj.createTestStep('TADstub_Get');
    tdkTestObj.addParameter("paramName","Device.IP.Diagnostics.TraceRoute.Host");
    expectedresult="SUCCESS";
    tdkTestObj.executeTestCase(expectedresult);
    if host == "NULL":
        tdkTestObj.setResultStatus("FAILURE");
        print "Host name not available in tdkb config file"
    else:
        tdkTestObj = obj.createTestStep('TADstub_Set');
        tdkTestObj.addParameter("ParamName","Device.IP.Diagnostics.TraceRoute.Interface");
        tdkTestObj.addParameter("ParamValue","Interface_erouter0");
        tdkTestObj.addParameter("Type","string");
        expectedresult="SUCCESS";
        tdkTestObj.executeTestCase(expectedresult);
        actualresult = tdkTestObj.getResult();
        details = tdkTestObj.getResultDetails();
        if expectedresult in actualresult:
            #Set the result status of execution
            tdkTestObj.setResultStatus("SUCCESS");
            print "TEST STEP 1: Set the interface of TraceRoute";
            print "EXPECTED RESULT 1: Should set the interface of TraceRoute";
            print "ACTUAL RESULT 1: %s" %details;
            #Get the result of execution
            print "[TEST EXECUTION RESULT] : SUCCESS";

            tdkTestObj = obj.createTestStep('TADstub_Set');
            tdkTestObj.addParameter("ParamName","Device.IP.Diagnostics.TraceRoute.Host");
            tdkTestObj.addParameter("ParamValue",host);
            tdkTestObj.addParameter("Type","string");
            expectedresult="SUCCESS";
            tdkTestObj.executeTestCase(expectedresult);
            actualresult = tdkTestObj.getResult();
            details = tdkTestObj.getResultDetails();
            if expectedresult in actualresult:
                #Set the result status of execution
                tdkTestObj.setResultStatus("SUCCESS");
                print "TEST STEP 2: Set the host of TraceRoute";
                print "EXPECTED RESULT 2: Should set the host of TraceRoute";
                print "ACTUAL RESULT 2: %s" %details;
                #Get the result of execution
                print "[TEST EXECUTION RESULT] : SUCCESS";

                tdkTestObj = obj.createTestStep('TADstub_Set');
                tdkTestObj.addParameter("ParamName","Device.IP.Diagnostics.TraceRoute.DiagnosticsState");
                tdkTestObj.addParameter("ParamValue","Requested");
                tdkTestObj.addParameter("Type","string");
                expectedresult="SUCCESS";
                tdkTestObj.executeTestCase(expectedresult);
                actualresult = tdkTestObj.getResult();
                details = tdkTestObj.getResultDetails();
                if expectedresult in actualresult:
                    #Set the result status of execution
                    tdkTestObj.setResultStatus("SUCCESS");
                    print "TEST STEP 3: Set DiagnosticsState of TraceRoute as Requested";
                    print "EXPECTED RESULT 3: Should set DiagnosticsState of TraceRoute as Requested";
                    print "ACTUAL RESULT 3: %s" %details;
                    #Get the result of execution
                    print "[TEST EXECUTION RESULT] : SUCCESS";
                    time.sleep(50);
                    tdkTestObj = obj.createTestStep('TADstub_Get');
                    tdkTestObj.addParameter("paramName","Device.IP.Diagnostics.TraceRoute.RouteHopsNumberOfEntries");
                    expectedresult="SUCCESS";
                    tdkTestObj.executeTestCase(expectedresult);
                    actualresult = tdkTestObj.getResult();
                    details = tdkTestObj.getResultDetails();
                    if expectedresult in actualresult and int(details)>0:
                        #Set the result status of execution
                        tdkTestObj.setResultStatus("SUCCESS");
                        print "TEST STEP 4: Check if the request is set successfully";
                        print "EXPECTED RESULT 4: Should get the routehops greater than zero";
                        print "ACTUAL RESULT 4: Route hops count is :%s" %details;
                        #Get the result of execution
                        print "[TEST EXECUTION RESULT] : SUCCESS";

            	        tdkTestObj = obj.createTestStep('TADstub_Get');
                        tdkTestObj.addParameter("paramName","Device.IP.Diagnostics.TraceRoute.RouteHops.1.RTTimes");
                        expectedresult="SUCCESS";
                        tdkTestObj.executeTestCase(expectedresult);
                        actualresult = tdkTestObj.getResult();
                        details = tdkTestObj.getResultDetails();
            	        Time_list=details.split(',');
            	        NumberofItems= len(Time_list);
                        if expectedresult in actualresult and NumberofItems <=3:
            		    #Set the result status of execution
                            tdkTestObj.setResultStatus("SUCCESS");
                            print "TEST STEP 5: Check if the list conatains more than 3 items";
                            print "EXPECTED RESULT 5: The list should contain less than  or equal to 3 items";
                            print "ACTUAL RESULT 5: The number of items in the list :%s" %NumberofItems;
                            #Get the result of execution
                            print "[TEST EXECUTION RESULT] : SUCCESS";
            	        else:
            		    #Set the result status of execution
                            tdkTestObj.setResultStatus("FAILURE");
                            print "TEST STEP 5: Check if the list conatains more than 3 items";
                            print "EXPECTED RESULT 5: The list should contain less than  or equal to 3 items";
                            print "ACTUAL RESULT 5: The number of items in the list :%s" %NumberofItems;
                            #Get the result of execution
                            print "[TEST EXECUTION RESULT] : FAILURE";
                    else:
                        #Set the result status of execution
                        tdkTestObj.setResultStatus("FAILURE");
                        print "TEST STEP 4: Check if the request is set successfully";
                        print "EXPECTED RESULT 4: Should get the routehops greater than zero";
                        print "ACTUAL RESULT 4: Route hops count is :%s" %details;
                        #Get the result of execution
                        print "[TEST EXECUTION RESULT] : FAILURE";
                else:
                    #Set the result status of execution
                    tdkTestObj.setResultStatus("FAILURE");
                    print "TEST STEP 3: Set DiagnosticsState of TraceRoute as Requested";
                    print "EXPECTED RESULT 3: Should set DiagnosticsState of TraceRoute as Requested";
                    print "ACTUAL RESULT 3: %s" %details;
                    #Get the result of execution
                    print "[TEST EXECUTION RESULT] : FAILURE";
            else:
                #Set the result status of execution
                tdkTestObj.setResultStatus("FAILURE");
                print "TEST STEP 2: Set the host of TraceRoute";
                print "EXPECTED RESULT 2: Should set the host of TraceRoute";
                print "ACTUAL RESULT 2: %s" %details;
                #Get the result of execution
                print "[TEST EXECUTION RESULT] : FAILURE";
        else:
            #Set the result status of execution
            tdkTestObj.setResultStatus("FAILURE");
            print "TEST STEP 1: Set the interface of TraceRoute";
            print "EXPECTED RESULT 1: Should set the interface of TraceRoute";
            print "ACTUAL RESULT 1: %s" %details;
            #Get the result of execution
            print "[TEST EXECUTION RESULT] : FAILURE";
    obj.unloadModule("tad");

else:
        print "Failed to load tad module";
        obj.setLoadModuleStatus("FAILURE");
        print "Module loading failed";

					
