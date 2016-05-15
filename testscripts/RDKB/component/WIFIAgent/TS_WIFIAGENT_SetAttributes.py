# ==============================================
# COMCAST CONFIDENTIAL AND PROPRIETARY
# ==============================================

# This file and its contents are the intellectual property of Comcast.  
# It may not be used,copied,distributed or otherwise  disclosed in 
# whole or in part without the express written permission of Comcast.

# ===============================================
# Copyright (c) 2016 Comcast. All rights reserved.
# ===============================================
'''
<?xml version='1.0' encoding='utf-8'?>
<xml>
  <id></id>
  <!-- Do not edit id. This will be auto filled while exporting. If you are adding a new script keep the id empty -->
  <version>2</version>
  <!-- Do not edit version. This will be auto incremented while updating. If you are adding a new script you can keep the vresion as 1 -->
  <name>TS_WIFIAGENT_SetAttributes</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id> </primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>WIFIAgent_SetAttr</primitive_test_name>
  <!--  -->
  <primitive_test_version>1</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>Set Attributes API Validation</synopsis>
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
    <box_type>Hybrid-1</box_type>
    <!--  -->
  </box_types>
  <rdk_versions>
    <rdk_version>RDKB</rdk_version>
    <!--  -->
  </rdk_versions>
</xml>
'''

# use tdklib library,which provides a wrapper for tdk testcase script 
import tdklib; 

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("wifiagent","RDKB");

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_WIFIAGENT_SetAttributes');

#Get the result of connection with test component and STB
loadModuleresult=obj.getLoadModuleResult();
print "[LIB LOAD STATUS]  :  %s" %loadModuleresult;

loadStatusExpected = "SUCCESS";

if loadStatusExpected not in loadModuleresult.upper():
        print "[Failed To Load WIFI Agent Stub or its supporting libraries probably from /usr/lib/]"
        print "[Exiting the Script]"
        exit();

#Prmitive test case which associated to this Script
tdkTestObj = obj.createTestStep('WIFIAgent_SetAttr');

#Input Parameters
tdkTestObj.addParameter("paramname","Device.WiFi.SSIDNumberOfEntries");
tdkTestObj.addParameter("notification","passive");
tdkTestObj.addParameter("accessControlChanged","anybody");

expectedresult = "SUCCESS";

#Execute the test case in STB
tdkTestObj.executeTestCase(expectedresult);

#Get the result of execution
actualresult = tdkTestObj.getResult();
print "[TEST EXECUTION RESULT] : %s" %actualresult ;

resultDetails = tdkTestObj.getResultDetails();

if expectedresult in actualresult:
	#Set the result status of execution as success
	tdkTestObj.setResultStatus("SUCCESS");
else:
	#Set the result status of execution as failure
	tdkTestObj.setResultStatus("FAILURE");

print "[TEST EXECUTION RESULT] : %s" %resultDetails ;

obj.unloadModule("wifiagent");
