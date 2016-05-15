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
  <version>3</version>
  <!-- Do not edit version. This will be auto incremented while updating. If you are adding a new script you can keep the vresion as 1 -->
  <name>TS_CCSPCOMMON_MBUS_Exit</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id></primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>CCSPMBUS_Exit</primitive_test_name>
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
    <box_type>Hybrid-1</box_type>
    <!--  -->
  </box_types>
  <rdk_versions>
    <rdk_version>RDKB</rdk_version>
    <!--  -->
  </rdk_versions>
</xml>
'''

#use tdklib library,which provides a wrapper for tdk testcase script
import tdklib; 

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("ccspcommon_mbus","RDKB");

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_CCSPCOMMON_MBUS_Exit');

#Get the result of connection with test component and STB
loadModuleresult =obj.getLoadModuleResult();
print "[LIB LOAD STATUS]  :  %s\n" %loadModuleresult;

loadStatusExpected = "SUCCESS"

if loadStatusExpected not in loadModuleresult.upper():
        print "[Failed To Load MBUS Agent Stub from from env TDK_PATH]"
        print "[Exiting the Script]"
        exit();

#Primitive test case which associated to this Script
tdkTestObj = obj.createTestStep('CCSPMBUS_LoadCfg');

#Input Parameters
tdkTestObj.addParameter("cmpCfgFile","/var/TDK/CcspTDKB.cfg");

expectedresult = "SUCCESS";

#Execute the test case in STB
tdkTestObj.executeTestCase(expectedresult);


#Get the result of execution
actualresult = tdkTestObj.getResult();
print "\n[TEST ACTUAL RESULT] : %s" %actualresult ;

resultDetails = tdkTestObj.getResultDetails();

if expectedresult in actualresult:
	#Set the result status of execution as success
	tdkTestObj.setResultStatus("SUCCESS");
        print "\nMessage Bus Load Config is SUCCESS"
else:
	#Set the result status of execution as failure
	tdkTestObj.setResultStatus("FAILURE");
        print "\nMessage Bus Load Config is FAILURE"
        obj.unloadModule("ccspcommon_mbus");
        exit();

print "\n[TEST EXECUTION RESULT] : %s\n" %resultDetails ;

#Primitive test case which associated to this Script
tdkTestObj = obj.createTestStep('CCSPMBUS_Init');

#Input Parameters
tdkTestObj.addParameter("cfgfileName","/tmp/ccsp_msg.cfg");

#Execute the test case in STB
tdkTestObj.executeTestCase(expectedresult);

#Get the result of execution
actualresult = tdkTestObj.getResult();
print "\n[TEST ACTUAL RESULT] : %s" %actualresult ;

resultDetails = tdkTestObj.getResultDetails();

if expectedresult in actualresult:
	#Set the result status of execution as success
	tdkTestObj.setResultStatus("SUCCESS");
        print "\nMessage Bus Initialization is SUCCESS"
else:
	#Set the result status of execution as failure
	tdkTestObj.setResultStatus("FAILURE");
        print "\nMessage Bus Initialization is FAILURE"
        obj.unloadModule("ccspcommon_mbus");
        exit();

print "\n[TEST EXECUTION RESULT] : %s\n" %resultDetails ;

#Primitive test case which associated to this Script
tdkTestObj = obj.createTestStep('CCSPMBUS_Exit');

#Input Parameters - Nil

#Execute the test case in STB
tdkTestObj.executeTestCase(expectedresult);

#Get the result of execution
actualresult = tdkTestObj.getResult();
print "\n[TEST ACTUAL RESULT] : %s" %actualresult ;

resultDetails = tdkTestObj.getResultDetails();

if expectedresult in actualresult:
	#Set the result status of execution as success
	tdkTestObj.setResultStatus("SUCCESS");
        print "\nMessage Bus De-Initialization/Exit is SUCCESS"
else:
	#Set the result status of execution as failure
	tdkTestObj.setResultStatus("FAILURE");
        print "\nMessage Bus De-Initialization/Exit is FAILURE"

print "\n[TEST EXECUTION RESULT] : %s\n" %resultDetails ;

obj.unloadModule("ccspcommon_mbus");
