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
  <version>12</version>
  <!-- Do not edit version. This will be auto incremented while updating. If you are adding a new script you can keep the vresion as 1 -->
  <name>TS_COSACM_SetMDDIPOverride</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id> </primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>COSACM_SetMDDIPOverride</primitive_test_name>
  <!--  -->
  <primitive_test_version>2</primitive_test_version>
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
																																																
import tdklib;
import time;

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("cosacm","RDKB");

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_COSACM_SetMDDIPOverride');

#Get the result of connection with test component and STB
loadmodulestatus =obj.getLoadModuleResult();
print "[LIB LOAD STATUS]  :  %s" %loadmodulestatus ;

if "SUCCESS" in loadmodulestatus.upper():
        obj.setLoadModuleStatus("SUCCESS");

        #Script to load the configuration file of the component
        tdkTestObj = obj.createTestStep("CosaCM_SetMDDIPOverride");
        tdkTestObj.addParameter("value","IPv4");
        expectedresult="SUCCESS";
        tdkTestObj.executeTestCase(expectedresult);
        actualresult = tdkTestObj.getResult();

        if expectedresult in actualresult:
            #Set the result status of execution
            tdkTestObj.setResultStatus("SUCCESS");
            details = tdkTestObj.getResultDetails();
            print "TEST STEP 1: Set the MDDIP Override value to IPv4";
            print "EXPECTED RESULT 1: Should successfully set the value to IPv4";
            print "ACTUAL RESULT 1: %s" %details;
            #Script to load the configuration file of the component
            tdkTestObj = obj.createTestStep("COSACM_GetMDDIPOverride");
            expectedresult="SUCCESS";
            tdkTestObj.executeTestCase(expectedresult);
            actualresult = tdkTestObj.getResult();

            if expectedresult in actualresult:
                #Set the result status of execution
                tdkTestObj.setResultStatus("SUCCESS");
                details = tdkTestObj.getResultDetails();
                print "TEST STEP 2: Retrieve the MDD IP Override Status";
                print "EXPECTED RESULT 2: Should retrieve the MDD IP Override Status successfully";
                print "ACTUAL RESULT 2: %s" %details;
                #Get the result of execution
                print "[TEST EXECUTION RESULT] : %s" %actualresult ;
                tdkTestObj = obj.createTestStep("CosaCM_SetMDDIPOverride");
                tdkTestObj.addParameter("value","IPv6");
                expectedresult="SUCCESS";
                tdkTestObj.executeTestCase(expectedresult);
                actualresult = tdkTestObj.getResult();

                if expectedresult in actualresult:
                    #Set the result status of execution
                    tdkTestObj.setResultStatus("SUCCESS");
                    details = tdkTestObj.getResultDetails();
                    print "TEST STEP 3: Set the MDDIP Override value to IPv6";
                    print "EXPECTED RESULT 3: Should successfully set the value to IPv6";
                    print "ACTUAL RESULT 3: %s" %details;
                    #Get the result of execution
                    print "[TEST EXECUTION RESULT] : %s" %actualresult ;
                    tdkTestObj = obj.createTestStep("COSACM_GetMDDIPOverride");
                    expectedresult="SUCCESS";
                    tdkTestObj.executeTestCase(expectedresult);
                    actualresult = tdkTestObj.getResult();

                    if expectedresult in actualresult:
                        #Set the result status of execution
                        tdkTestObj.setResultStatus("SUCCESS");
                        details = tdkTestObj.getResultDetails();
                        print "TEST STEP 4: Retrieve the MDD IP Override Status";
                        print "EXPECTED RESULT 4: Should retrieve the MDD IP Override Status successfully";
                        print "ACTUAL RESULT 4: %s" %details;
                        #Get the result of execution
                        print "[TEST EXECUTION RESULT] : %s" %actualresult ;
                        tdkTestObj = obj.createTestStep("CosaCM_SetMDDIPOverride");
                        tdkTestObj.addParameter("value","Honor");
                        expectedresult="SUCCESS";
                        tdkTestObj.executeTestCase(expectedresult);
                        actualresult = tdkTestObj.getResult();

                        if expectedresult in actualresult:
                            #Set the result status of execution
                            tdkTestObj.setResultStatus("SUCCESS");
                            details = tdkTestObj.getResultDetails();
                            print "TEST STEP 5: Set the MDDIP Override value to Honor";
                            print "EXPECTED RESULT 5: Should successfully set the value to Honor";
                            print "ACTUAL RESULT 5: %s" %details;
                            #Get the result of execution
                            print "[TEST EXECUTION RESULT] : %s" %actualresult ;
                            tdkTestObj = obj.createTestStep("COSACM_GetMDDIPOverride");
                            expectedresult="SUCCESS";
                            tdkTestObj.executeTestCase(expectedresult);
                            actualresult = tdkTestObj.getResult();

                            if expectedresult in actualresult:
                                #Set the result status of execution
                                tdkTestObj.setResultStatus("SUCCESS");
                                details = tdkTestObj.getResultDetails();
                                print "TEST STEP 6: Retrieve the MDD IP Override Status";
                                print "EXPECTED RESULT 6: Should retrieve the MDD IP Override Status successfully";
                                print "ACTUAL RESULT 6: %s" %details;
                                #Get the result of execution
                                print "[TEST EXECUTION RESULT] : %s" %actualresult ; 
                            else:
                                tdkTestObj.setResultStatus("FAILURE");
                                details = tdkTestObj.getResultDetails();
                                print "TEST STEP 6: Retrieve the MDD IP Override Status";
                                print "EXPECTED RESULT 6: Should retrieve the MDD IP Override Status successfully";
                                print "ACTUAL RESULT 6: %s" %details;
                                print "[TEST EXECUTION RESULT] : %s" %actualresult ;
                        else:
                            tdkTestObj.setResultStatus("FAILURE");
                            details = tdkTestObj.getResultDetails();
                            print "TEST STEP 5: Set the MDDIP Override value to Honor";
                            print "EXPECTED RESULT 5: Should successfully set the value to Honor";
                            print "ACTUAL RESULT 5: %s" %details;
                            print "[TEST EXECUTION RESULT] : %s" %actualresult ;
                    else:
                        tdkTestObj.setResultStatus("FAILURE");
                        details = tdkTestObj.getResultDetails();
                        print "TEST STEP 4: Retrieve the MDD IP Override Status";
                        print "EXPECTED RESULT 4: Should retrieve the MDD IP Override Status successfully";
                        print "ACTUAL RESULT 4: %s" %details;
                        print "[TEST EXECUTION RESULT] : %s" %actualresult ;
                else:
                    tdkTestObj.setResultStatus("FAILURE");
                    details = tdkTestObj.getResultDetails();
                    print "TEST STEP 3: Set the MDDIP Override value to IPv6";
                    print "EXPECTED RESULT 3: Should successfully set the value to IPv6";
                    print "ACTUAL RESULT 3: %s" %details;
                    print "[TEST EXECUTION RESULT] : %s" %actualresult ;
                    tdkTestObj = obj.createTestStep("CosaCM_SetMDDIPOverride");
                    tdkTestObj.addParameter("value","Honor");
                    expectedresult="SUCCESS";
                    tdkTestObj.executeTestCase(expectedresult);
            else:
                tdkTestObj.setResultStatus("FAILURE");
                details = tdkTestObj.getResultDetails();
                print "TEST STEP 2: Retrieve the MDD IP Override Status";
                print "EXPECTED RESULT 2: Should retrieve the MDD IP Override Status successfully";
                print "ACTUAL RESULT 2: %s" %details;
                print "[TEST EXECUTION RESULT] : %s" %actualresult ;
                #Get the result of execution
                print "[TEST EXECUTION RESULT] : %s" %actualresult ;
        else:
            tdkTestObj.setResultStatus("FAILURE");
            details = tdkTestObj.getResultDetails();
            print "TEST STEP 1: Set the MDDIP Override value to IPv4";
            print "EXPECTED RESULT 1: Should successfully set the value to IPv4";
            print "ACTUAL RESULT 1: %s" %details;
            print "[TEST EXECUTION RESULT] : %s" %actualresult ;
            tdkTestObj = obj.createTestStep("CosaCM_SetMDDIPOverride");
            tdkTestObj.addParameter("value","Honor");
            expectedresult="SUCCESS";
            tdkTestObj.executeTestCase(expectedresult);
            
        obj.unloadModule("cosacm");
else:
        print "Failed to load the module";
        obj.setLoadModuleStatus("FAILURE");
        print "Module loading failed";

					

					

					

					

					

					

					

					