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
<?xml version='1.0' encoding='utf-8'?>
<xml>
  <id></id>
  <!-- Do not edit id. This will be auto filled while exporting. If you are adding a new script keep the id empty -->
  <version>3</version>
  <!-- Do not edit version. This will be auto incremented while updating. If you are adding a new script you can keep the vresion as 1 -->
  <name>TS_WIFIHAL_5GHzSetApSecurityReset</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id> </primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>WIFIHAL_ParamRadioIndex</primitive_test_name>
  <!--  -->
  <primitive_test_version>1</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>To invoke the api wifi_setApSecurityReset() and check whether the mode is not equal to the set mode using wifi_getRadioStandard() api for 5GHz.</synopsis>
  <!--  -->
  <groups_id />
  <!--  -->
  <execution_time>5</execution_time>
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
    <test_case_id>TC_WIFIHAL_283</test_case_id>
    <test_objective>To invoke the api wifi_setApSecurityReset() and check whether the mode is not equal to the set mode using wifi_getRadioStandard() api for 5GHz.</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Broadband</test_setup>
    <pre_requisite>1.Ccsp Components  should be in a running state else invoke cosa_start.sh manually that includes all the ccsp components and TDK Component
2.TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>wifi_setApSecurityReset()
wifi_getRadioStandard()
wifi_setRadioChannelMode()</api_or_interface_used>
    <input_parameters>methodName : setApSecurityReset
methodName : getRadioStandard
methodName : setRadioChannelMode
radioIndex : 1</input_parameters>
    <automation_approch>1.Load the module
2.Get the radio standard using wifi_getRadioStandard() api.
3.Set the channel mode to another value using wifi_setRadioChannelMode() api.
4,Invoke the  wifi_ setApSecurityReset() api and again get the mode using wifi_getRadioStandard() api.
5.The set and get values should be different.If so,return SUCCESS,else FAILURE.
6.Revert the mode back to initial mode.
7.Unload the module.</automation_approch>
    <except_output>After invoking wifi_setApSecurityReset() api mode should be changed to default value.</except_output>
    <priority>High</priority>
    <test_stub_interface>WIFIHAL</test_stub_interface>
    <test_script>TS_WIFIHAL_5GHzSetApSecurityReset</test_script>
    <skipped>No</skipped>
    <release_version>M59</release_version>
    <remarks></remarks>
  </test_cases>
  <script_tags />
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
obj.configureTestCase(ip,port,'TS_WIFIHAL_5GHzSetApSecurityReset');
#Get the result of connection with test component and DUT
loadmodulestatus =obj.getLoadModuleResult();
print "[LIB LOAD STATUS]  :  %s" %loadmodulestatus ;

def getRadioStandard():
    tdkTestObj = obj.createTestStep("WIFIHAL_GetOrSetRadioStandard");
    #Giving the method name to invoke the api wifi_getRadioStandard()
    tdkTestObj.addParameter("methodName","getRadioStandard")
    #Radio index is 0 for 2.4GHz and 1 for 5GHz
    tdkTestObj.addParameter("radioIndex",1);
    expectedresult="SUCCESS";
    tdkTestObj.executeTestCase(expectedresult);
    actualresult = tdkTestObj.getResult();
    details = tdkTestObj.getResultDetails();
    if expectedresult in actualresult:
        tdkTestObj.setResultStatus("SUCCESS");
        return (details.split(":")[1].split(" ")[0],int(details.split(":")[1].split(" ")[1].strip()),int(details.split(":")[1].split(" ")[2].strip()),int(details.split(":")[1].split(" ")[3].strip()));
    else:
        tdkTestObj.setResultStatus("FAILURE");

def setRadioChannelMode(gOnly_set,nOnly_set,acOnly_set):
    tdkTestObj = obj.createTestStep("WIFIHAL_GetOrSetRadioStandard");
    #Giving the method name to invoke the api wifi_setRadioChannelMode()
    tdkTestObj.addParameter("methodName","setRadioChannelMode")
    #Radio index is 0 for 2.4GHz and 1 for 5GHz
    tdkTestObj.addParameter("radioIndex",1);
    tdkTestObj.addParameter("param","11ACVHT80");
    tdkTestObj.addParameter("gOnly",gOnly_set);
    tdkTestObj.addParameter("nOnly",nOnly_set);
    tdkTestObj.addParameter("acOnly",acOnly_set);
    expectedresult="SUCCESS";
    tdkTestObj.executeTestCase(expectedresult);
    actualresult = tdkTestObj.getResult();
    details = tdkTestObj.getResultDetails();
    if expectedresult in actualresult:
        tdkTestObj.setResultStatus("SUCCESS");
        return 1;
    else:
       tdkTestObj.setResultStatus("FAILURE");
       return 0;

def setApSecurityReset():
    #Script to load the configuration file of the component
    tdkTestObj = obj.createTestStep("WIFIHAL_ParamRadioIndex");
    #Giving the method name to invoke the api wifi_setApSecurityReset()
    tdkTestObj.addParameter("methodName","setApSecurityReset")
    #Radio index is 0 for 2.4GHz and 1 for 5GHz
    tdkTestObj.addParameter("radioIndex",1);
    expectedresult="SUCCESS";
    tdkTestObj.executeTestCase(expectedresult);
    actualresult = tdkTestObj.getResult();
    details = tdkTestObj.getResultDetails();
    print"details",details;
    if expectedresult in actualresult:
        Currentchannel_final,gOnly_final,nOnly_final,acOnly_final = getRadioStandard();
        print"gOnly value after reset : ",gOnly_final;
        print"nOnly value after reset: ",nOnly_final;
        print"acOnly value after reset: ",acOnly_final;
        if (gOnly_final,nOnly_final,acOnly_final) == (0,0,0):
            tdkTestObj.setResultStatus("SUCCESS");
            print "TEST STEP 1: To invoke the api wifi_setApSecurityReset and check whether the mode is equal to the default values for 5GHz";
            print "EXPECTED RESULT 1: The mode should be equal to the default values for 5GHz";
            print "ACTUAL RESULT 1: The mode in equal to the default values for 5GHz";
            #Get the result of execution
            print "[TEST EXECUTION RESULT] : SUCCESS";
            #Revert the mode to initial mode
            revert = setRadioChannelMode(gOnly_initial,nOnly_initial,acOnly_initial);
            if revert == 1:
                print"Successfully reverted back to initial value";
                tdkTestObj.setResultStatus("SUCCESS");
            else:
                print"Unable to revert back to initial value";
                tdkTestObj.setResultStatus("FAILURE");
        else:
            tdkTestObj.setResultStatus("FAILURE");
            print "TEST STEP 1: To invoke the api wifi_setApSecurityReset and check whether the mode is equal to the default for 5GHz";
            print "EXPECTED RESULT 1: The mode should be equal to the default values for 5GHz";
            print "ACTUAL RESULT 1: The mode is not equal to the default values for 5GHz";
            #Get the result of execution
            print "[TEST EXECUTION RESULT] : FAILURE";
            #Revert the mode to initial mode
            revert = setRadioChannelMode(gOnly_initial,nOnly_initial,acOnly_initial);
            if revert == 1:
                print"Successfully reverted back to initial value";
                tdkTestObj.setResultStatus("SUCCESS");
            else:
                print"Unable to revert back to initial value";
                tdkTestObj.setResultStatus("FAILURE");
    else:
        tdkTestObj.setResultStatus("FAILURE");
        print "wifi_setApSecurityReset() operation failed";

if "SUCCESS" in loadmodulestatus.upper():
    obj.setLoadModuleStatus("SUCCESS");
    Currentchannel_initial,gOnly_initial,nOnly_initial,acOnly_initial = getRadioStandard();
    print"gOnly initial value : ",gOnly_initial;
    print"nOnly initial value: ",nOnly_initial;
    print"acOnly initial value: ",acOnly_initial;
    if (gOnly_initial,nOnly_initial,acOnly_initial) == (0,0,0):
        gOnly_set,nOnly_set,acOnly_set = (0,1,0);
        print"gOnly set value : ",gOnly_set;
        print"nOnly set value: ",nOnly_set;
        print"acOnly set value: ",acOnly_set;
        retvalue = setRadioChannelMode(0,1,0);
        if retvalue == 1:
            print"wifi_setRadioChannelMode() operation success";
	    setApSecurityReset()
        else:
            print"wifi_setRadioChannelMode() operation failed";
    else:
	print"Radio standard values are not same as default value 0 0 0, so calling setApSecurityReset() function";
	setApSecurityReset()

    obj.unloadModule("wifihal");
else:
    print "Failed to load the module";
    obj.setLoadModuleStatus("FAILURE");

