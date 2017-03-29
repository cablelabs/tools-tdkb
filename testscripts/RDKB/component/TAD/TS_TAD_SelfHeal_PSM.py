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
<?xml version="1.0" encoding="UTF-8"?><xml>
  <id/>
  <version>1</version>
  <name>TS_TAD_SelfHeal_PSM</name>
  <primitive_test_id/>
  <primitive_test_name>TADstub_Get</primitive_test_name>
  <primitive_test_version>3</primitive_test_version>
  <status>FREE</status>
  <synopsis>To test if by self healing CcspPSM is restarted when killed</synopsis>
  <groups_id/>
  <execution_time>40</execution_time>
  <long_duration>false</long_duration>
  <advanced_script>false</advanced_script>
  <remarks/>
  <skip>false</skip>
  <box_types>
    <box_type>Broadband</box_type>
  </box_types>
  <rdk_versions>
    <rdk_version>RDKB</rdk_version>
  </rdk_versions>
  <test_cases>
    <test_case_id>TC_TAD_17</test_case_id>
    <test_objective>To test if by self healing CcspPSM is restarted when killed</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Emulator,XB3,Rpi</test_setup>
    <pre_requisite>1.Ccsp Components in DUT should be in a running state that includes component under test Cable Modem
2.TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>ExecuteCmd</api_or_interface_used>
    <input_parameters> ps -ef | grep -i PsmSsp | grep -v grep
killall PsmSsp;  ps -ef | grep PsmSsp | grep -v grep</input_parameters>
    <automation_approch>1. Load sysutil and TAD modules
2. From script invoke ExecuteCmd to check if PSM process is up or not
3. If CcspPSM is up, kill it using ExecuteCmd
4. Wait for 30 minutes for it to restart
5. Using ExecuteCmd, check if PSM is up again 
6. Validation of  the result is done within the python script and send the result status to Test Manager.
7.Test Manager will publish the result in GUI as PASS/FAILURE based on the response from pam stub.</automation_approch>
    <except_output>CcspPSMSsp process should get restarted</except_output>
    <priority>High</priority>
    <test_stub_interface>TAD
sysutil</test_stub_interface>
    <test_script>TS_TAD_SelfHeal_PSM</test_script>
    <skipped>No</skipped>
    <release_version/>
    <remarks/>
  </test_cases>
</xml>

'''
# use tdklib library,which provides a wrapper for tdk testcase script 
import tdklib; 
from time import sleep;

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("tad","1");
sysObj = tdklib.TDKScriptingLibrary("sysutil","RDKB")

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_TAD_SelfHeal_PSM');
sysObj.configureTestCase(ip,port,'TS_TAD_SelfHeal_PSM');

#Get the result of connection with test component and STB
loadmodulestatus1 =obj.getLoadModuleResult();
loadmodulestatus2 =sysObj.getLoadModuleResult();

print "[LIB LOAD STATUS]  :  %s" %loadmodulestatus1

if "SUCCESS" in loadmodulestatus1.upper() and "SUCCESS" in loadmodulestatus2.upper():
    obj.setLoadModuleStatus("SUCCESS");
    sysObj.setLoadModuleStatus("SUCCESS");

    tdkTestObj = sysObj.createTestStep('ExecuteCmd');
    tdkTestObj.addParameter("command", " ps -ef | grep -i PsmSsp | grep -v grep")
    expectedresult="SUCCESS";

    #Execute the test case in STB
    tdkTestObj.executeTestCase("SUCCESS");
    actualresult = tdkTestObj.getResult();
    details = tdkTestObj.getResultDetails().strip()

    if expectedresult in actualresult and details:
        print "TEST STEP 1:Check if PsmSsp process is running"
        print "EXPECTED RESULT 1: PsmSsp should be running";
        print "ACTUAL RESULT 1: PsmSsp process is running"
        tdkTestObj.setResultStatus("SUCCESS");

        tdkTestObj.addParameter("command", "killall PsmSsp;  ps -ef | grep PsmSsp | grep -v grep")
        tdkTestObj.executeTestCase("SUCCESS");
        actualresult = tdkTestObj.getResult();
        details = tdkTestObj.getResultDetails().strip()
        if expectedresult in actualresult :
            print "TEST STEP 1:Kill PsmSsp process"
            print "EXPECTED RESULT 1: PsmSsp should not be running";
            print "ACTUAL RESULT 1: PsmSsp process is not running"
            tdkTestObj.setResultStatus("SUCCESS");
        else:
            print "TEST STEP 1:Kill PsmSsp process"
            print "EXPECTED RESULT 1: PsmSsp should not be running";
            print "ACTUAL RESULT 1: PsmSsp process is running"
            tdkTestObj.setResultStatus("FAILURE");
    else:
        print "TEST STEP 1:Check if PsmSsp process is running"
        print "EXPECTED RESULT 1: PsmSsp should be running";
        print "ACTUAL RESULT 1: PsmSsp process is not running"
        tdkTestObj.setResultStatus("SUCCESS");

    #wait for PsmSsp prcs to start
    sleep(1800)
    tdkTestObj = sysObj.createTestStep('ExecuteCmd');
    tdkTestObj.addParameter("command", " ps -ef | grep -i PsmSsp | grep -v grep")
    tdkTestObj.executeTestCase("SUCCESS");
    actualresult = tdkTestObj.getResult();
    details = tdkTestObj.getResultDetails().strip()

    if expectedresult in actualresult and details:
        print "TEST STEP 1:Check if PsmSsp process is running"
        print "EXPECTED RESULT 1: PsmSsp should be running";
        print "ACTUAL RESULT 1: PsmSsp process is running"
        tdkTestObj.setResultStatus("SUCCESS");
    else:
        print "TEST STEP 1:Check if PsmSsp process is running"
        print "EXPECTED RESULT 1: PsmSsp should be running";
        print "ACTUAL RESULT 1: PsmSsp process is not running"
        tdkTestObj.setResultStatus("FAILURE");

    sysObj.unloadModule("sysutil");
    obj.unloadModule("tad");
else:
    print "FAILURE to load TAD module";
    obj.setLoadModuleStatus("FAILURE");
    sysObj.setLoadModuleStatus("FAILURE");
    print "Module loading FAILURE";