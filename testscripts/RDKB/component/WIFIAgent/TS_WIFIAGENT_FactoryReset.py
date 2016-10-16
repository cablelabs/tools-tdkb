#  ============================================================================
#  COMCAST C O N F I D E N T I A L AND PROPRIETARY
#  ============================================================================
#  This file (and its contents) are the intellectual property of Comcast.  It may
#  not be used, copied, distributed or otherwise  disclosed in whole or in part
#  without the express written permission of Comcast.
#  ============================================================================
#  Copyright (c) 2014 Comcast. All rights reserved.
#  ===========================================================================
'''
<?xml version='1.0' encoding='utf-8'?>
<xml>
  <id></id>
  <!-- Do not edit id. This will be auto filled while exporting. If you are adding a new script keep the id empty -->
  <version>14</version>
  <!-- Do not edit version. This will be auto incremented while updating. If you are adding a new script you can keep the vresion as 1 -->
  <name>TS_WIFIAGENT_FactoryReset</name>
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
  <execution_time>4</execution_time>
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
import time;
#Test component to be tested
obj = tdklib.TDKScriptingLibrary("wifiagent","RDKB");
#IP and Port of box, No need to change,
#This will be replaced with corresponding Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_WIFIAGENT_FactoryReset');

#Get the result of connection with test component
loadmodulestatus =obj.getLoadModuleResult();
print "[LIB LOAD STATUS]  :  %s" %loadmodulestatus ;

if "SUCCESS" in loadmodulestatus.upper():
    obj.setLoadModuleStatus("SUCCESS");
    
    #### Set and Get Values ####
    tdkTestObj = obj.createTestStep("WIFIAgent_Set");
    tdkTestObj.addParameter("paramName","Device.WiFi.SSID.1.SSID");
    tdkTestObj.addParameter("paramValue","TDKB");
    tdkTestObj.addParameter("paramType","string");
    expectedresult="SUCCESS";
    tdkTestObj.executeTestCase(expectedresult);
    actualresult = tdkTestObj.getResult();
    if expectedresult in actualresult:
        #Set the result status of execution
        tdkTestObj.setResultStatus("SUCCESS");
        details = tdkTestObj.getResultDetails();
        print "TEST STEP 1: Set the SSID name as TDKB";
        print "EXPECTED RESULT 1: Should set the SSID name as TDKB";
        print "ACTUAL RESULT 1: %s" %details;
        #Get the result of execution
        print "[TEST EXECUTION RESULT] : %s" %actualresult;
        
        tdkTestObj = obj.createTestStep("WIFIAgent_Get");
        tdkTestObj.addParameter("paramName","Device.WiFi.SSID.1.SSID");
        expectedresult="SUCCESS";
        tdkTestObj.executeTestCase(expectedresult);
        actualresult = tdkTestObj.getResult();
        #Script to get the parameter values of wifi
        tdkTestObj = obj.createTestStep("WIFIAgent_Get");
        tdkTestObj.addParameter("paramName","Device.WiFi.SSID.1.SSID");
        expectedresult="SUCCESS";
        tdkTestObj.executeTestCase(expectedresult);
        actualresult = tdkTestObj.getResult();

        if expectedresult in actualresult:
            #Set the result status of execution
            tdkTestObj.setResultStatus("SUCCESS");
            details1 = tdkTestObj.getResultDetails();
            print "TEST STEP 2: Get the current SSID name";
            print "EXPECTED RESULT 2: Should retrieve the SSID name";
            print "ACTUAL RESULT 2: %s" %details1;
            #Get the result of execution
            print "[TEST EXECUTION RESULT] : %s" %actualresult ;

            #Do a factor reset of the wifi settings
            tdkTestObj = obj.createTestStep("WIFIAgent_Set");
            tdkTestObj.addParameter("paramName","Device.WiFi.X_CISCO_COM_FactoryReset");
            tdkTestObj.addParameter("paramValue","true");
            tdkTestObj.addParameter("paramType","bool");
            expectedresult="SUCCESS";
            tdkTestObj.executeTestCase(expectedresult);
            actualresult = tdkTestObj.getResult();
            if expectedresult in actualresult:
                #Set the result status of execution
                tdkTestObj.setResultStatus("SUCCESS");
                details2 = tdkTestObj.getResultDetails();
                print "EXPECTED RESULT 3: Should set the Factory Reset value to true";
                print "ACTUAL RESULT 3: %s" %details2;
                #Get the result of execution
                print "[TEST EXECUTION RESULT] : %s" %actualresult;
                print "Factory Reset Function is SUCCESS: Value set to true and validated"
                time.sleep(180);
                
                tdkTestObj = obj.createTestStep("WIFIAgent_Get");
                tdkTestObj.addParameter("paramName","Device.WiFi.SSID.1.SSID");
                expectedresult="SUCCESS";
                tdkTestObj.executeTestCase(expectedresult);
                actualresult = tdkTestObj.getResult();

                if expectedresult in actualresult:
                    #Set the result status of execution
                    tdkTestObj.setResultStatus("SUCCESS");
                    details3 = tdkTestObj.getResultDetails();
                    print "TEST STEP 4: Get the SSID Name after factory reset";
                    print "EXPECTED RESULT 4: Should retrieve the SSID Name";
                    print "ACTUAL RESULT 4: %s" %details3;
                    #Get the result of execution
                    print "[TEST EXECUTION RESULT] : %s" %actualresult ;
                    if details1 in details3:
                        print "SSID Name retrieved is matching with the name before Wifi factory reset";
                        tdkTestObj.setResultStatus("FAILURE");
                    else:
                        print "SSID Name retrieved is not matching with the name before Wifi factory reset";
                        tdkTestObj.setResultStatus("SUCCESS");
                else:
                    tdkTestObj.setResultStatus("FAILURE");
                    details3 = tdkTestObj.getResultDetails();
                    print "TEST STEP 4: Get the SSID Name after factory reset";
                    print "EXPECTED RESULT 4: hould retrieve the SSID Name";
                    print "ACTUAL RESULT 4: %s" %details3;
                    print "[TEST EXECUTION RESULT] : %s" %actualresult ;
            else:
                tdkTestObj.setResultStatus("FAILURE");
                details2 = tdkTestObj.getResultDetails();
                print "EXPECTED RESULT 3: Should set the Factory Reset value to true";
                print "ACTUAL RESULT 3: %s" %details2;
                print "[TEST EXECUTION RESULT] : %s" %actualresult;
                print "Factory Reset Function is FAILURE: Value is not set to true"
        else:
                tdkTestObj.setResultStatus("FAILURE");
                details1 = tdkTestObj.getResultDetails();
                print "TEST STEP 2: Get the current SSID name";
                print "EXPECTED RESULT 2: Should retrieve the SSID name";
                print "ACTUAL RESULT 2: %s" %details1;
                print "[TEST EXECUTION RESULT] : %s" %actualresult ;            
    else:
        tdkTestObj.setResultStatus("FAILURE");
        details = tdkTestObj.getResultDetails();
        print "TEST STEP 1: Set the SSID name as TDKB";
        print "EXPECTED RESULT 1: Should set the SSID name as TDKB";
        print "ACTUAL RESULT 1: %s" %details;
        print "[TEST EXECUTION RESULT] : %s" %actualresult ;
        
            
    obj.unloadModule("wifiagent");
else:
        print "FAILURE to load wifiagent module";
        obj.setLoadModuleStatus("FAILURE");
        print "Module loading FAILURE";

					

					

					

					

					

					

					

					