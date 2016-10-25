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
  <version>2</version>
  <!-- Do not edit version. This will be auto incremented while updating. If you are adding a new script you can keep the vresion as 1 -->
  <name>TS_PAM_GetNetworkDevicesTrafficPollingPeriod</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id> </primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>pam_GetParameterValues</primitive_test_name>
  <!--  -->
  <primitive_test_version>1</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis></synopsis>
  <!--  -->
  <groups_id />
  <!--  -->
  <execution_time>1</execution_time>
  <!--  -->
  <long_duration>false</long_duration>
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
  <script_tags />
</xml>
'''
#use tdklib library,which provides a wrapper for tdk testcase script 
import tdklib; 

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("pam","RDKB");

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
defaultPeriod = "300"
obj.configureTestCase(ip,port,'TS_PAM_GetNetworkDevicesTrafficPollingPeriod');

#Get the result of connection with test component and STB
loadmodulestatus =obj.getLoadModuleResult();
print "[LIB LOAD STATUS]  :  %s" %loadmodulestatus ;

if "SUCCESS" in loadmodulestatus.upper():
    #Set the result status of execution
    obj.setLoadModuleStatus("SUCCESS");
    tdkTestObj = obj.createTestStep('pam_GetParameterValues');
    tdkTestObj.addParameter("ParamName","Device.X_RDKCENTRAL-COM_Report.NetworkDevicesTraffic.PollingPeriod");
    expectedresult="SUCCESS";

    #Execute the test case in STB
    tdkTestObj.executeTestCase("expectedresult");

    actualresult = tdkTestObj.getResult();
    details = tdkTestObj.getResultDetails();
		
    if expectedresult in actualresult:
        #Set the result status of execution
        tdkTestObj.setResultStatus("SUCCESS");
        print "TEST STEP 1: Get the Polling period of network device traffic\n";
        print "EXPECTED RESULT 1: Should get the polling period of network device traffic\n";
        print "ACTUAL RESULT 1: Polling period of network device traffic is %s" %details;
        #Get the result of execution
        
        if defaultPeriod in details:
            print "Polling period of Network Device traffic is 300\n"
            print "[TEST EXECUTION RESULT] : SUCCESS";
        else:
            print "Polling period of Network Device traffic is wrong value, it should be 300\n"
            print "[TEST EXECUTION RESULT] : FAILURE";
    else:
        tdkTestObj.setResultStatus("FAILURE");	
        print "TEST STEP 1: Get the Polling period of network device traffic\n";
        print "EXPECTED RESULT 1: Failure in getting the Polling period of network device traffic\n";
        print "ACTUAL RESULT 1: %s" %details;
        print "[TEST EXECUTION RESULT] : FAILURE";
        

	
    obj.unloadModule("pam");
   		 
else:   
        print "Failed to load pam module";
        obj.setLoadModuleStatus("FAILURE");
        print "Module loading failed";
				
				

					
