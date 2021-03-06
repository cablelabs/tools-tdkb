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
  <name>TS_CMHAL_GetDSFrequency</name>
  <primitive_test_id/>
  <primitive_test_name>CMHAL_GetParamCharValue</primitive_test_name>
  <primitive_test_version>1</primitive_test_version>
  <status>FREE</status>
  <synopsis>To get the downstream channel frequency and check whether it is in valid range or not</synopsis>
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
    <test_case_id>TC_CMHAL_20</test_case_id>
    <test_objective>To get the downstream channel frequency and check whether it is in valid range or not</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Broadband</test_setup>
    <pre_requisite>1.Ccsp Components  should be in a running state of DUT that includes component under test Cable Modem
2.TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>docsis_GetDSChannel</api_or_interface_used>
    <input_parameters>paramName : "DS_Frequency"</input_parameters>
    <automation_approch>1. Load  cmhal module
2. From script invoke CMHAL_GetParamCharValue() 
3. Get all the downstream frequencies and validate it
4. Validation of  the result is done within the stub and send the result status to Test Manager.
5.Test Manager will publish the result in GUI as PASS/FAILURE based on the response from TAD stub.</automation_approch>
    <except_output>All downstream frequencies should be within the range of 108Mhz to 1.002Ghz</except_output>
    <priority>High</priority>
    <test_stub_interface>CosaCM</test_stub_interface>
    <test_script>TS_CMHAL_GetDSFrequency</test_script>
    <skipped>No</skipped>
    <release_version/>
    <remarks/>
  </test_cases>
</xml>

'''
# use tdklib library,which provides a wrapper for tdk testcase script 
import tdklib; 

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("cmhal","1");

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_CMHAL_GetDSFrequency');

#Get the result of connection with test component and DUT 
loadmodulestatus =obj.getLoadModuleResult();
print "[LIB LOAD STATUS]  :  %s" %loadmodulestatus ;

if "SUCCESS" in loadmodulestatus.upper():
    obj.setLoadModuleStatus("SUCCESS");

    #Script to load the configuration file of the component
    tdkTestObj = obj.createTestStep("CMHAL_GetParamCharValue");
    tdkTestObj.addParameter("paramName","DS_Frequency");
    expectedresult="SUCCESS";
    tdkTestObj.executeTestCase(expectedresult);
    actualresult = tdkTestObj.getResult();
    Details = tdkTestObj.getResultDetails();
    DS_freq = Details.split(",");
    print DS_freq;
    maxFreq = 1002.00;
    minFreq = 108.00;
    for item in DS_freq:
	if minFreq <= float(item) <= maxFreq:
	    status = "Success";
	else:
	    status = "Failure";
	    break;
    if expectedresult in actualresult and "Success" in status:
        #Set the result status of execution
        tdkTestObj.setResultStatus("SUCCESS");
        print "TEST STEP 1: Get and validate the DownStream Frequency";
        print "EXPECTED RESULT 1: Downstream Frequencies should be within the range of 108Mhz to 1.002Ghz";
        print "ACTUAL RESULT 1: Successfully validated the DownStream Frequency";
        #Get the result of execution
        print "[TEST EXECUTION RESULT] : SUCCESS";
    else:
        tdkTestObj.setResultStatus("FAILURE");
        print "TEST STEP 1: Get and validate the DownStream Frequency";
        print "EXPECTED RESULT 1: Downstream Frequencies should be within the range of 108Mhz to 1.002Ghz";
        print "ACTUAL RESULT 1: Validation of DownStream Frequency is failed";
        print "[TEST EXECUTION RESULT] : FAILURE";

    obj.unloadModule("cmhal");
else:
        print "Failed to load the module";
        obj.setLoadModuleStatus("FAILURE");
        print "Module loading failed";
