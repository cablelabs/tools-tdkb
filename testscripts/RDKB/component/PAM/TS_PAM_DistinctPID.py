##########################################################################
# If not stated otherwise in this file or this component's Licenses.txt
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
  <version>5</version>
  <!-- Do not edit version. This will be auto incremented while updating. If you are adding a new script you can keep the vresion as 1 -->
  <name>TS_PAM_DistinctPID</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id> </primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>pam_GetParameterValues</primitive_test_name>
  <!--  -->
  <primitive_test_version>1</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>Tests if Process table has no two entries with same pid values</synopsis>
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
#import statement
import tdklib; 

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("sysutil","RDKB");

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_PAM_DistinctPID');

#Get the result of connection with test component and STB
loadmodulestatus =obj.getLoadModuleResult();
print "[LIB LOAD STATUS]  :  %s" %loadmodulestatus ;

if "SUCCESS" in loadmodulestatus.upper():
    #Set the result status of execution
    obj.setLoadModuleStatus("SUCCESS");

    #Check the box type
    imagename = tdklib.getImageName (ip, port)
    print imagename;
    pattern = "TG1682_"
    if pattern in imagename:
	#box type is xb3
	print "DUT is XB3."
	prefix = "eRT"
    else:
	prefix = "simu"

    #select a random PID from process table
    tdkTestObj = obj.createTestStep('ExecuteCmd');
    tdkTestObj.addParameter("command", "/fss/gw/usr/ccsp/ccsp_bus_client_tool %s getvalues Device.DeviceInfo.ProcessStatus.Process. | grep -A 1 PID | head -n 100 | tail -3 | cut -f3 -d ':' | head -n 1 | tr \"\n\" \" \"" %prefix);
    expectedresult="SUCCESS";

    #Execute the test case in STB
    tdkTestObj.executeTestCase("expectedresult");
    actualresult = tdkTestObj.getResult();
    details = tdkTestObj.getResultDetails();
		
    if expectedresult in actualresult and details:
	pid = details;
        #Set the result status of execution
        tdkTestObj.setResultStatus("SUCCESS");
        print "TEST STEP 1: Get a random PID";
        print "EXPECTED RESULT 1: Should get a random PID";
        print "ACTUAL RESULT 1: ProcessId is %s" %details;
        #Get the result of execution
        print "[TEST EXECUTION RESULT] : SUCCESS";

	#check for the no: of occurences of that pid in process table
	tdkTestObj = obj.createTestStep('ExecuteCmd');
	tdkTestObj.addParameter("command", "/fss/gw/usr/ccsp/ccsp_bus_client_tool %s getvalues Device.DeviceInfo.ProcessStatus.Process. | grep -A 1 PID | cut -f3 -d ':' | grep -w %s | wc -l | tr \"\n\" \" \"" %(prefix, pid));
	expectedresult="SUCCESS";

        #Execute the test case in STB
        tdkTestObj.executeTestCase("expectedresult");
        actualresult = tdkTestObj.getResult();
        details = tdkTestObj.getResultDetails().strip();
                
        if expectedresult in actualresult and details == "1":
            pid = details;
            #Set the result status of execution
            tdkTestObj.setResultStatus("SUCCESS");
            print "TEST STEP 2: Get no: of occurence of PID";
            print "EXPECTED RESULT 2: Should get no: of occurence of PID as one";
            print "ACTUAL RESULT 2: no: of occurence is %s" %details;
            #Get the result of execution
            print "[TEST EXECUTION RESULT] : SUCCESS";
        else:
            tdkTestObj.setResultStatus("FAILURE");  
            print "TEST STEP 2: Get no: of occurence of PID";
            print "EXPECTED RESULT 2: Should get no: of occurence of PID as one";
            print "ACTUAL RESULT 2: no: of occurence is %s" %details;
            print "[TEST EXECUTION RESULT] : FAILURE";

    else:
        tdkTestObj.setResultStatus("FAILURE");	
        print "TEST STEP 1: Get a random PID";
        print "EXPECTED RESULT 1: Should get a random PID";
        print "ACTUAL RESULT 1: ProcessId is %s" %details;
        print "[TEST EXECUTION RESULT] : FAILURE";
    obj.unloadModule("sysutil");
   		 
else:   
        print "Failed to load sysutil module";
        obj.setLoadModuleStatus("FAILURE");
        print "Module loading failed";				
