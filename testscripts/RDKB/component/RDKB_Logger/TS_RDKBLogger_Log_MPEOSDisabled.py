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
  <id>1441</id>
  <!-- Do not edit id. This will be auto filled while exporting. If you are adding a new script keep the id empty -->
  <version>3</version>
  <!-- Do not edit version. This will be auto incremented while updating. If you are adding a new script you can keep the vresion as 1 -->
  <name>TS_RDKBLogger_Log_MPEOSDisabled</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id> </primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>RDKBLogger_Log</primitive_test_name>
  <!--  -->
  <primitive_test_version>1</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>To check that no message is logged when MPEOS debug support is disabled.
Test Case ID: CT_RDKBLogger_37
Test Type: Negative</synopsis>
  <!--  -->
  <groups_id />
  <!--  -->
  <execution_time>5</execution_time>
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
# use tdklib library,which provides a wrapper for tdk testcase script
from tdklib import TDKScriptingLibrary;

#IP and Port of box, No need to change,
#This will be replaced with corresponding Box Ip and port while executing script
ip = <ipaddress>
port = <port>

#Test component to be tested
obj = TDKScriptingLibrary("rdklogger","RDKB");
obj.configureTestCase(ip,port,'TS_RDKBLogger_Log_MPEOSDisabled');
#Get the result of connection with test component and Gateway
result =obj.getLoadModuleResult();
print "rdklogger module loading status :%s" %result;

#Check for SUCCESS/FAILURE of rdklogger module
if "SUCCESS" in result.upper():
    #Set the module loading status
    obj.setLoadModuleStatus("SUCCESS");

    #Primitive test case which associated to this Script
    tdkTestObj = obj.createTestStep('RDKBLogger_Log_MPEOSDisabled');

    expectedRes = "SUCCESS"

    module = "TEST1"
    print "Requested module: %s"%module
    tdkTestObj.addParameter("module",module);
    level = "ERROR"
    print "Requested level: %s"%level
    tdkTestObj.addParameter("level",level);

    #Execute the test case in Gateway
    tdkTestObj.executeTestCase(expectedRes);

    #Get the result of execution
    result = tdkTestObj.getResult();
    print "[TEST EXECUTION RESULT] : %s" %result;
    details = tdkTestObj.getResultDetails();
    #Set the result status of execution
    if "SUCCESS" in result.upper():
        tdkTestObj.setResultStatus("SUCCESS");
        print "Logging failed with MPEOS Disabled as expected";
    else:
        tdkTestObj.setResultStatus("FAILURE");
        print "Logging successful with MPEOS Disabled: [%s]"%details;

    #Reset the logging to default
    obj.initiateReboot();

    #unloading rdklogger module
    obj.unloadModule("rdklogger");
else:
    print "Failed to load rdklogger module";
    #Set the module loading status
    obj.setLoadModuleStatus("FAILURE");
