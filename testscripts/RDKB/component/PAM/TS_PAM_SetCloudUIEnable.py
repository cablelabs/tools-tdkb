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
  <version>5</version>
  <!-- Do not edit version. This will be auto incremented while updating. If you are adding a new script you can keep the vresion as 1 -->
  <name>TS_PAM_SetCloudUIEnable</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id> </primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>pam_SetParameterValues</primitive_test_name>
  <!--  -->
  <primitive_test_version>2</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis></synopsis>
  <!--  -->
  <groups_id />
  <!--  -->
  <execution_time>15</execution_time>
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
																								
#use tdk library											
import tdklib; 

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("pam","RDKB");

#IP and Port of box, No need to change,
#This will be replaced with corresponding Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_PAM_SetCloudUIEnable');

#Get the result of connection with test component and Gateway
loadmodulestatus =obj.getLoadModuleResult();
print "[LIB LOAD STATUS]  :  %s" %loadmodulestatus ;

if "SUCCESS" in loadmodulestatus.upper():
    #Set the result status of execution
    obj.setLoadModuleStatus("SUCCESS");	
    tdkTestObj = obj.createTestStep('pam_SetParameterValues');  
    tdkTestObj.addParameter("ParamName","Device.DeviceInfo.X_RDKCENTRAL-COM_CloudUIEnable");
    tdkTestObj.addParameter("ParamValue","true");
    tdkTestObj.addParameter("Type","boolean");
    expectedresult="SUCCESS";
    #Execute the test case in Gateway
    tdkTestObj.executeTestCase(expectedresult);
    actualresult = tdkTestObj.getResult();
    details = tdkTestObj.getResultDetails();		
    if expectedresult in actualresult:
        #Set the result status of execution
        tdkTestObj.setResultStatus("SUCCESS");
        details = tdkTestObj.getResultDetails();
        print "TEST STEP 1: Enable the Cloud UI";
        print "EXPECTED RESULT 1: Should enable the Cloud UI successfully";
        print "ACTUAL RESULT 1: %s" %details;
        tdkTestObj = obj.createTestStep('pam_SetParameterValues');  
        tdkTestObj.addParameter("ParamName","Device.DeviceInfo.X_RDKCENTRAL-COM_CloudUIEnable");
        tdkTestObj.addParameter("ParamValue","false");
        tdkTestObj.addParameter("Type","boolean");
        expectedresult="SUCCESS";
        #Execute the test case in Gateway
        tdkTestObj.executeTestCase(expectedresult);
        actualresult = tdkTestObj.getResult();
        details = tdkTestObj.getResultDetails();		
        if expectedresult in actualresult:
            #Set the result status of execution
            tdkTestObj.setResultStatus("SUCCESS");
            details = tdkTestObj.getResultDetails();
            print "TEST STEP 2: Disable the Cloud UI";
            print "EXPECTED RESULT 2: Should disable the Cloud UI successfully";
            print "ACTUAL RESULT 2: %s" %details;
        else:   
            tdkTestObj.setResultStatus("FAILURE");
            details = tdkTestObj.getResultDetails();
            print "TEST STEP 2: Disable the Cloud UI";
            print "EXPECTED RESULT 2: Should disable the Cloud UI successfully";
            print "ACTUAL RESULT 2: %s" %details;
    else:   
        tdkTestObj.setResultStatus("FAILURE");
        details = tdkTestObj.getResultDetails();
        print "TEST STEP 1: Enable the Cloud UI";
        print "EXPECTED RESULT 1: Should enable the Cloud UI successfully";
        print "ACTUAL RESULT 1: %s" %details;
	
    obj.unloadModule("pam");
   		 
else:   
        print "Failed to load pam module";
        obj.setLoadModuleStatus("FAILURE");
        print "Module loading failed";				

					

							

					

					

					

					

					

					

					