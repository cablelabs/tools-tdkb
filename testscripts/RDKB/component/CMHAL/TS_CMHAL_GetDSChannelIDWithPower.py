##########################################################################
#If not stated otherwise in this file or this component's Licenses.txt
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
  <version>1</version>
  <!-- Do not edit version. This will be auto incremented while updating. If you are adding a new script you can keep the vresion as 1 -->
  <name>TS_CMHAL_GetDSChannelIDWithPower</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id> </primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>CMHAL_GetParamCharValue</primitive_test_name>
  <!--  -->
  <primitive_test_version>1</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>To get the channel ID and power of downstream channel. If the channel ID is zero,power should be empty. Otherwise it should not be empty</synopsis>
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
  </box_types>
  <rdk_versions>
    <rdk_version>RDKB</rdk_version>
    <!--  -->
  </rdk_versions>
  <test_cases>
    <test_case_id>TC_CMHAL_19</test_case_id>
    <test_objective>To get the channel ID and power of downstream channel. If the channel ID is zero,power should be empty. Otherwise it should not be empty</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Broadband</test_setup>
    <pre_requisite>1.Ccsp Components  should be in a running state of DUT that includes component under test Cable Modem
2.TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>docsis_GetDSChannel</api_or_interface_used>
    <input_parameters>paramName : "DSChannelIDAndPower"</input_parameters>
    <automation_approch>1. Load  cmhal module
2. Invoke docsis_GetDSChannel to get the channel ID and power of downstream channel
3. If the channel id is non zero and power is within acceptable range, it is success
4. Else if channel id is zero and power is empty , it is success
4. The test should return FAILURE otherwise
5. Unload cmhal module</automation_approch>
    <except_output>If the channel id is non zero, downstream channel power should not be empty</except_output>
    <priority>High</priority>
    <test_stub_interface>CMHAL</test_stub_interface>
    <test_script>TS_CMHAL_GetDSChannelIDWithPower</test_script>
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
obj.configureTestCase(ip,port,'TS_CMHAL_GetDSChannelIDWithPower');

#Get the result of connection with test component and DUT
loadmodulestatus =obj.getLoadModuleResult();
print "[LIB LOAD STATUS]  :  %s" %loadmodulestatus ;

if "SUCCESS" in loadmodulestatus.upper():
    obj.setLoadModuleStatus("SUCCESS");

    #This method invokes the HAL API docsis_GetDSChannel to get the downstream channel id and power
    tdkTestObj = obj.createTestStep("CMHAL_GetParamCharValue");
    tdkTestObj.addParameter("paramName","DSChannelIDAndPower");
    expectedresult="SUCCESS";
    tdkTestObj.executeTestCase(expectedresult);
    actualresult = tdkTestObj.getResult();
    Power = tdkTestObj.getResultDetails();
    minPower = -15.00;
    maxPower = 15.00;
    List = Power.split(",");
    print "%s" %List;
    for item in List:
	#Data[0] is Channel ID and Data[1] is Power
        Data = item.split(":");
        print "%s" %Data;
        
        if  int(Data[0]) != 0 and "dBmV" in Data[1]:
           
           if  minPower<=float(Data[1].split(" ")[0])<=maxPower:
            status = "Success";
           else:
            status = "Failure";
            break;
        elif int(Data[0]) != 0 and "dBmV" not in Data[1] :
             
        
             if  minPower<=float(Data[1])<=maxPower:
               status = "Success";
             else:
               status = "Failure";
               break;

             
        elif int(Data[0])==0 and "" in Data[1]:
            status = "Success";
        else:
            status = "Failure";
            break;
        
    if expectedresult in actualresult and "Success" in status:
        #Set the result status of execution
        tdkTestObj.setResultStatus("SUCCESS");
        print "TEST STEP 1: Get and validate the DownStream power and ChannelID";
        print "EXPECTED RESULT 1: Should get power if channelID not zero";
        print "ACTUAL RESULT 1: Successfully validated the ChannelID with power" ;
        #Get the result of execution
        print "[TEST EXECUTION RESULT] : SUCCESS";
    else:
        tdkTestObj.setResultStatus("FAILURE");
        print "TEST STEP 1: Get and validate the DownStream power and ChannelID";
        print "EXPECTED RESULT 1: Should get power if channelID not zero";
        print "ACTUAL RESULT 1: Validation of ChannelID and power failed";
        print "[TEST EXECUTION RESULT] : FAILURE";

    obj.unloadModule("cmhal");
else:
        print "Failed to load the module";
        obj.setLoadModuleStatus("FAILURE");
        print "Module loading failed";
				

