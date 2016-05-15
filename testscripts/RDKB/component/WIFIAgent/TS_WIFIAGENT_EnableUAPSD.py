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
  <name>TS_WIFIAGENT_EnableUAPSD</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id> </primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>WIFIAgent_Set_Get</primitive_test_name>
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
import time;
#Test component to be tested
obj = tdklib.TDKScriptingLibrary("wifiagent","RDKB");
#IP and Port of box, No need to change,
#This will be replaced with corresponding Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_WIFIAGENT_EnableUAPSD');

#Get the result of connection with test component
loadmodulestatus =obj.getLoadModuleResult();
print "[LIB LOAD STATUS]  :  %s" %loadmodulestatus ;

if "SUCCESS" in loadmodulestatus.upper():
    obj.setLoadModuleStatus("SUCCESS");
    
    #### Set and Get Values ####
    tdkTestObj = obj.createTestStep("WIFIAgent_Set_Get");
    tdkTestObj.addParameter("paramName","Device.WiFi.AccessPoint.1.UAPSDEnable");
    tdkTestObj.addParameter("paramValue","true");
    tdkTestObj.addParameter("paramType","bool");
    expectedresult="SUCCESS";
    tdkTestObj.executeTestCase(expectedresult);
    actualresult = tdkTestObj.getResult();
    if expectedresult in actualresult:
        #Set the result status of execution
        tdkTestObj.setResultStatus("SUCCESS");
        details = tdkTestObj.getResultDetails();
        print "EXPECTED RESULT 1: Should Set the Enable access point UASPD value to true";
        print "ACTUAL RESULT 1: %s" %details;
        #Get the result of execution
        print "[TEST EXECUTION RESULT] : %s" %actualresult;
        print "Enable UAPSD Function is SUCCESS"
    else:
        tdkTestObj.setResultStatus("FAILURE");
        details = tdkTestObj.getResultDetails();
        print "EXPECTED RESULT 1: Should Set the Enable access point UASPD value to true";
        print "ACTUAL RESULT 1: %s" %details;
        print "[TEST EXECUTION RESULT] : %s" %actualresult;
        print "Enable UAPSD Function is FAILURE"        
    obj.unloadModule("wifiagent");
else:
        print "FAILURE to load wifiagent module";
        obj.setLoadModuleStatus("FAILURE");
        print "Module loading FAILURE";
