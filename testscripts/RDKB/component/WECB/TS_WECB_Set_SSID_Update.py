##
# ============================================================================
# COMCAST CONFIDENTIAL AND PROPRIETARY
# ============================================================================
# This file and its contents are the intellectual property of Comcast.  It may
# not be used, copied, distributed or otherwise  disclosed in whole or in part
# without the express written permission of Comcast.
# ============================================================================
# Copyright (c) 2016 Comcast. All rights reserved.
# ============================================================================
##
'''
<?xml version='1.0' encoding='utf-8'?>
<xml>
  <id></id>
  <!-- Do not edit id. This will be auto filled while exporting. If you are adding a new script keep the id empty -->
  <version>10</version>
  <!-- Do not edit version. This will be auto incremented while updating. If you are adding a new script you can keep the vresion as 1 -->
  <name>TS_WECB_Set_SSID_Update</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id> </primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>WECB_SetParamValues</primitive_test_name>
  <!--  -->
  <primitive_test_version>2</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>TC_WECB_4 - To verify enabling/disabling of SSID update</synopsis>
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
</xml>
'''

#use tdklib library,which provides a wrapper for tdk testcase script 
import tdklib;
import time;

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("wecb","RDKB");

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_WECB_Set_SSID_Update');

#Get the result of connection with test component and STB
loadmodulestatus =obj.getLoadModuleResult();
print "[LIB LOAD STATUS]  :  %s" %loadmodulestatus ;

if "SUCCESS" in loadmodulestatus.upper():
        obj.setLoadModuleStatus("SUCCESS");

        #Enable moca interface
        tdkTestObj = obj.createTestStep("WECB_SetParamValues");
        tdkTestObj.addParameter("paramName","Device.MoCA.X_CISCO_COM_WiFi_Extender.X_CISCO_COM_SSID_Updated");
        tdkTestObj.addParameter("paramValue","true");
        tdkTestObj.addParameter("paramType","boolean");
        tdkTestObj.addParameter("commit",1);
        expectedresult="SUCCESS";
        tdkTestObj.executeTestCase(expectedresult);
        actualresult = tdkTestObj.getResult();

        if expectedresult in actualresult:
            #Set the result status of execution
            tdkTestObj.setResultStatus("SUCCESS");
            details = tdkTestObj.getResultDetails();
            print "TEST STEP 1: Enable the SSID update";
            print "EXPECTED RESULT 1: Should enable the SSID update";
            print "ACTUAL RESULT 1: %s" %details;
            #Get the result of execution
            print "[TEST EXECUTION RESULT] : %s" %actualresult ;
            
            #Disable Moca interface
            tdkTestObj = obj.createTestStep("WECB_SetParamValues");
            tdkTestObj.addParameter("paramName","Device.MoCA.X_CISCO_COM_WiFi_Extender.X_CISCO_COM_SSID_Updated");
            tdkTestObj.addParameter("paramValue","false");
            tdkTestObj.addParameter("paramType","boolean");
            tdkTestObj.addParameter("commit",1);
            expectedresult="SUCCESS";
            tdkTestObj.executeTestCase(expectedresult);
            actualresult = tdkTestObj.getResult();

            if expectedresult in actualresult:
                #Set the result status of execution
                tdkTestObj.setResultStatus("SUCCESS");
                details = tdkTestObj.getResultDetails();
                print "TEST STEP 2: Disable the SSID update";
                print "EXPECTED RESULT 2: Should SSID the radio update";
                print "ACTUAL RESULT 2: %s" %details;
                #Get the result of execution
                print "[TEST EXECUTION RESULT] : %s" %actualresult ; 
            else:
                tdkTestObj.setResultStatus("FAILURE");
                details = tdkTestObj.getResultDetails();
                print "TEST STEP 2: Disable the SSID update";
                print "EXPECTED RESULT 2: Should SSID the SSID update";
                print "ACTUAL RESULT 2: %s" %details;
                print "[TEST EXECUTION RESULT] : %s" %actualresult ;
        else:
            tdkTestObj.setResultStatus("FAILURE");
            details = tdkTestObj.getResultDetails();
            print "TEST STEP 1: Enable the SSID update";
            print "EXPECTED RESULT 1: Should enable the SSID update";
            print "ACTUAL RESULT 1: %s" %details;
            print "[TEST EXECUTION RESULT] : %s" %actualresult ;              
            
        obj.unloadModule("wecb");
else:
        print "Failed to load WECB controller module";
        obj.setLoadModuleStatus("FAILURE");
        print "Module loading failed";
