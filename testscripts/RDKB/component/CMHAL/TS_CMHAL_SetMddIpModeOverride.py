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
<?xml version="1.0" encoding="UTF-8"?><xml>
  <id/>
  <version>2</version>
  <name>TS_CMHAL_SetMddIpModeOverride</name>
  <primitive_test_id/>
  <primitive_test_name>CMHAL_SetMddIpModeOverride</primitive_test_name>
  <primitive_test_version>1</primitive_test_version>
  <status>FREE</status>
  <synopsis>To set the MddIpModeOverride using docsis_SetMddIpModeOverride()</synopsis>
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
    <test_case_id>TC_CMHAL_55</test_case_id>
    <test_objective>To set the MddIpModeOverride using docsis_SetMddIpModeOverride()</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Broadband</test_setup>
    <pre_requisite>1.Ccsp Components  should be in a running state of DUT that includes component under test Cable Modem
2.TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>docsis_SetMddIpModeOverride()</api_or_interface_used>
    <input_parameters>None</input_parameters>
    <automation_approch>1. Load  cmhal module
2. From script invoke CMHAL_GetParamCharValue()
3. Get current MddIpOverride value
4. Set the MddIpOverride value using CMHAL_SetMddIpModeOverride()
5. Validation of  the result is done within the python script and send the result status to Test Manager.
6.Test Manager will publish the result in GUI as PASS/FAILURE based on the response from TAD stub.</automation_approch>
    <except_output>The api should set the given value of MddIpModeOverride</except_output>
    <priority>High</priority>
    <test_stub_interface>CMHAL</test_stub_interface>
    <test_script>TS_CMHAL_SetMddIpModeOverride</test_script>
    <skipped>No</skipped>
    <release_version>M62</release_version>
    <remarks>None</remarks>
  </test_cases>
  <script_tags/>
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
obj.configureTestCase(ip,port,'TS_CMHAL_SetMddIpModeOverride');

#Get the result of connection with test component and DUT
loadmodulestatus =obj.getLoadModuleResult();
print "[LIB LOAD STATUS]  :  %s" %loadmodulestatus ;

if "SUCCESS" in loadmodulestatus.upper():
    obj.setLoadModuleStatus("SUCCESS");

    tdkTestObj = obj.createTestStep("CMHAL_GetParamCharValue");
    tdkTestObj.addParameter("paramName","MddIpModeOverride");
    expectedresult="SUCCESS";
    tdkTestObj.executeTestCase(expectedresult);
    actualresult = tdkTestObj.getResult();
    MddIpValue = tdkTestObj.getResultDetails();

    if expectedresult in actualresult:
        #Set the result status of execution
        tdkTestObj.setResultStatus("SUCCESS");
        print "TEST STEP 1: Get the MddIpModeOverride";
        print "EXPECTED RESULT 1: Should get the MddIpModeOverride successfully";
        print "ACTUAL RESULT 1: MddIpModeOverride is %s" %MddIpValue;
        #Get the result of execution
        print "[TEST EXECUTION RESULT] : SUCCESS";

	List =["IPV4","IPV6","HONOR"];
	if MddIpValue.upper() in List:
	    for i in List:
    	        #Script to load the configuration file of the component
    	        tdkTestObj = obj.createTestStep("CMHAL_SetMddIpModeOverride");
    	        tdkTestObj.addParameter("value",i);
    	        expectedresult="SUCCESS";
    	        tdkTestObj.executeTestCase(expectedresult);
    	        actualresult = tdkTestObj.getResult();
    	        details = tdkTestObj.getResultDetails();

    	        if expectedresult in actualresult :
    	            #Set the result status of execution
    	            tdkTestObj.setResultStatus("SUCCESS");
    	            print "TEST STEP 2: Set MddIpModeOverride as ",i;
    	            print "EXPECTED RESULT 2: Should Set MddIpModeOverride as", i;
    	            print "ACTUAL RESULT 2:  ",details;
    	            #Get the result of execution
    	            print "[TEST EXECUTION RESULT] : SUCCESS";

	            #validate set function using get
	            tdkTestObj = obj.createTestStep("CMHAL_GetParamCharValue");
    	            tdkTestObj.addParameter("paramName","MddIpModeOverride");
    	            expectedresult="SUCCESS";
    	            tdkTestObj.executeTestCase(expectedresult);
    	            actualresult = tdkTestObj.getResult();
    	            MddIpValue1 = tdkTestObj.getResultDetails();

    	            if expectedresult in actualresult and MddIpValue1 == i:
    	                #Set the result status of execution
    	                tdkTestObj.setResultStatus("SUCCESS");
    	                print "TEST STEP 3: Get the MddIpModeOverride";
    	                print "EXPECTED RESULT 3: Should get the MddIpModeOverride as ",i,"successfully";
    	                print "ACTUAL RESULT 3: MddIpModeOverride is %s" %MddIpValue1;
    	                #Get the result of execution
    	                print "[TEST EXECUTION RESULT] : SUCCESS";
	            else:
	    	        #Set the result status of execution
                        tdkTestObj.setResultStatus("FAILURE");
                        print "TEST STEP 3: Get the MddIpModeOverride";
                        print "EXPECTED RESULT 3: Should get the MddIpModeOverride as ",i,"successfully";
                        print "ACTUAL RESULT 3: MddIpModeOverride is %s" %MddIpValue1;
                        #Get the result of execution
                        print "[TEST EXECUTION RESULT] : FAILURE";
		else:
                    #Set the result status of execution
                    tdkTestObj.setResultStatus("FAILURE");
                    print "TEST STEP 2: Set MddIpModeOverride";
                    print "EXPECTED RESULT 2: Should Set MddIpModeOverride";
                    print "ACTUAL RESULT 2:  ",details;
                    #Get the result of execution
                    print "[TEST EXECUTION RESULT] : FAILURE";
	    #Revert the value of MddIpModeOverride
            tdkTestObj = obj.createTestStep("CMHAL_SetMddIpModeOverride");
            tdkTestObj.addParameter("value",MddIpValue);
            expectedresult="SUCCESS";
            tdkTestObj.executeTestCase(expectedresult);
            actualresult = tdkTestObj.getResult();
            details = tdkTestObj.getResultDetails();

            if expectedresult in actualresult :
                #Set the result status of execution
                tdkTestObj.setResultStatus("SUCCESS");
                print "TEST STEP : Set MddIpModeOverride";
                print "EXPECTED RESULT : Should Set MddIpModeOverride";
                print "ACTUAL RESULT :  ",details;
                #Get the result of execution
                print "[TEST EXECUTION RESULT] : SUCCESS";
	    else:
	        #Set the result status of execution
                tdkTestObj.setResultStatus("FAILURE");
                print "TEST STEP : Set MddIpModeOverride";
                print "EXPECTED RESULT : Should Set MddIpModeOverride";
                print "ACTUAL RESULT :  ",details;
                #Get the result of execution
                print "[TEST EXECUTION RESULT] : FAILURE";
	else:
	    tdkTestObj.setResultStatus("FAILURE");
	    print "The value obtained for MddIpModeOverride is not a subset of {UNDEFINED,IPV4,IPV6,HONOR}"
	    print "[TEST EXECUTION RESULT] : FAILURE";
    else:
	#Set the result status of execution
        tdkTestObj.setResultStatus("FAILURE");
        print "TEST STEP 1: Get the MddIpModeOverride";
        print "EXPECTED RESULT 1: Should get the MddIpModeOverride successfully";
        print "ACTUAL RESULT 1: MddIpModeOverride is %s" %MddIpValue;
        #Get the result of execution
        print "[TEST EXECUTION RESULT] : FAILURE";
    obj.unloadModule("cmhal");
else:
        print "Failed to load the module";
        obj.setLoadModuleStatus("FAILURE");
        print "Module loading failed";
