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
  <version>3</version>
  <!-- Do not edit version. This will be auto incremented while updating. If you are adding a new script you can keep the vresion as 1 -->
  <name>TS_TAD_SelfHeal_tr069</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id> </primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>TADstub_Get</primitive_test_name>
  <!--  -->
  <primitive_test_version>3</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>To test if by sel healing TR069 is restarted when killed</synopsis>
  <!--  -->
  <groups_id />
  <!--  -->
  <execution_time>40</execution_time>
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
    <test_case_id>TC_TAD_1</test_case_id>
    <test_objective>To test if by self healing TR069 process is restarted when killed</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Emulator,XB3,Rpi</test_setup>
    <pre_requisite>1.Ccsp Components in DUT should be in a running state that includes component under test Cable Modem
2.TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>ExecuteCmd</api_or_interface_used>
    <input_parameters>ps -ef | grep -i CcspTr069PaSsp | grep -v grep
killall -9 CcspTr069PaSsp;  ps -ef | grep CcspTr069PaSsp | grep -v grep</input_parameters>
    <automation_approch>1. Load sysutil and TAD modules
2. From script invoke ExecuteCmd to check if TR069 process is up or not
3. If TR069 is up, kill it using ExecuteCmd
4. Wait for 30 minutes for it to restart
5. Using ExecuteCmd, check if TR069 is up again 
6. Validation of  the result is done within the python script and send the result status to Test Manager.
7.Test Manager will publish the result in GUI as PASS/FAILURE based on the response from pam stub.</automation_approch>
    <except_output>TR069 process should get restarted</except_output>
    <priority>High</priority>
    <test_stub_interface>TAD
sysutil</test_stub_interface>
    <test_script>TS_TAD_SelfHeal_tr069</test_script>
    <skipped>No</skipped>
    <release_version></release_version>
    <remarks></remarks>
  </test_cases>
  <script_tags />
</xml>
'''
# use tdklib library,which provides a wrapper for tdk testcase script 
import tdklib; 
from time import sleep;

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("tad","1");
sysObj = tdklib.TDKScriptingLibrary("sysutil","RDKB");

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_TAD_SelfHeal_tr069');
sysObj.configureTestCase(ip,port,'TS_TAD_SelfHeal_tr069');

#Get the result of connection with test component and STB
loadmodulestatus1 =obj.getLoadModuleResult();
loadmodulestatus2 =sysObj.getLoadModuleResult();

print "[LIB LOAD STATUS]  :  %s" %loadmodulestatus1

if "SUCCESS" in loadmodulestatus1.upper() and "SUCCESS" in loadmodulestatus2.upper():
    obj.setLoadModuleStatus("SUCCESS");
    sysObj.setLoadModuleStatus("SUCCESS");

    tdkTestObj = sysObj.createTestStep('ExecuteCmd');
    tdkTestObj.addParameter("command", " ps | grep -i CcspTr069PaSsp | grep -v grep")
    expectedresult="SUCCESS";

    #Execute the test case in STB
    tdkTestObj.executeTestCase("expectedresult");
    actualresult = tdkTestObj.getResult();
    details = tdkTestObj.getResultDetails().strip()

    if expectedresult in actualresult and details:
        print "TEST STEP 1:Check if CcspTr069PaSsp process is running"
        print "EXPECTED RESULT 1: CcspTr069PaSsp should be running";
        print "ACTUAL RESULT 1: CcspTr069PaSsp process is running"
        tdkTestObj.setResultStatus("SUCCESS");

        tdkTestObj.addParameter("command", "killall CcspTr069PaSsp;  ps | grep CcspTr069PaSsp | grep -v grep")
        tdkTestObj.executeTestCase("expectedresult");
        actualresult = tdkTestObj.getResult();
        details = tdkTestObj.getResultDetails().strip()

        if expectedresult in actualresult :
            print "TEST STEP 1:Kill CcspTr069PaSsp process"
            print "EXPECTED RESULT 1: CcspTr069PaSsp should not be running";
            print "ACTUAL RESULT 1: CcspTr069PaSsp process is not running"
            tdkTestObj.setResultStatus("SUCCESS");
        else:
            print "TEST STEP 1:Kill CcspTr069PaSsp process"
            print "EXPECTED RESULT 1: CcspTr069PaSsp should not be running";
            print "ACTUAL RESULT 1: CcspTr069PaSsp process is running"
            tdkTestObj.setResultStatus("FAILURE");
    else:
        print "TEST STEP 1:Check if CcspTr069PaSsp process is running"
        print "EXPECTED RESULT 1: CcspTr069PaSsp should be running";
        print "ACTUAL RESULT 1: CcspTr069PaSsp process is not running"
        tdkTestObj.setResultStatus("SUCCESS");

    #wait for CcspTr069PaSsp prcs to start
    sleep(1800)
    tdkTestObj.addParameter("command", " ps | grep -i CcspTr069PaSsp | grep -v grep")
    tdkTestObj.executeTestCase("expectedresult");
    actualresult = tdkTestObj.getResult();
    details = tdkTestObj.getResultDetails().strip()

    if expectedresult in actualresult and details:
        print "TEST STEP 1:Check if CcspTr069PaSsp process is running"
        print "EXPECTED RESULT 1: CcspTr069PaSsp should be running";
        print "ACTUAL RESULT 1: CcspTr069PaSsp process is running"
        tdkTestObj.setResultStatus("SUCCESS");
    else:
        print "TEST STEP 1:Check if CcspTr069PaSsp process is running"
        print "EXPECTED RESULT 1: CcspTr069PaSsp should be running";
        print "ACTUAL RESULT 1: CcspTr069PaSsp process is not running"
        tdkTestObj.setResultStatus("FAILURE");

    sysObj.unloadModule("sysutil");
    obj.unloadModule("tad");
else:
    print "FAILURE to load TAD module";
    obj.setLoadModuleStatus("FAILURE");
    sysObj.setLoadModuleStatus("FAILURE");
    print "Module loading FAILURE";


					

					
