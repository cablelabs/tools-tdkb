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
  <name>TS_SNMP_v2cGETqueryEmptyCommString</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id></primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>GetCommString</primitive_test_name>
  <!--  -->
  <primitive_test_version>1</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>Test if snmpget fails with empty community string</synopsis>
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
    <box_type>Emulator</box_type>
    <!--  -->
  </box_types>
  <rdk_versions>
    <rdk_version>RDKB</rdk_version>
    <!--  -->
  </rdk_versions>
  <test_cases>
    <test_case_id>TC_SNMP_PA_30</test_case_id>
    <test_objective>Test if snmpget fails with empty community string</test_objective>
    <test_type>Positive</test_type>
    <test_setup>XB3, Emulator</test_setup>
    <pre_requisite>1.Ccsp Components in DUT should be in a running state that includes component under test Cable Modem
2.TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>subprocess.Popen()</api_or_interface_used>
    <input_parameters>"snmpget -c \" \" -v 2c udp6:[" + ip +"] 1.3.6.1.2.1.69.1.4.5.0"</input_parameters>
    <automation_approch>1.TM will load the snmp_pa library via Test agent
2.From python script, invoke SnmpExecuteCmd function in snmplib to get the value of given OID 
3.Responses from the popen() will be logged in Script log.
6. Validation of  the result is done within the python script and send the result status to Test Manager.
7.Test Manager will publish the result in GUI as PASS/FAILURE based on the response from snmplib.</automation_approch>
    <except_output>CheckPoint 1:
  Response of snmp command should be logged in the script log

CheckPoint 2:
Stub and lib function result should be success and should see corresponding log in the script log

CheckPoint 3:
TestManager GUI will publish the result as PASS in Execution/Console page of Test Manager</except_output>
    <priority>High</priority>
    <test_stub_interface>snmp_pa</test_stub_interface>
    <test_script>TS_SNMP_v2cGETqueryEmptyCommString</test_script>
    <skipped>No</skipped>
    <release_version></release_version>
    <remarks></remarks>
  </test_cases>
  <script_tags />
</xml>
'''
												# use tdklib library,which provides a wrapper for tdk testcase script 
import tdklib; 
import subprocess;
from subprocess import Popen,PIPE,STDOUT;

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("snmp_pa","1");

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_SNMP_v2cGETqueryEmptyCommString');

#Get the result of connection with test component and STB
loadmodulestatus =obj.getLoadModuleResult();
print "[LIB LOAD STATUS]  :  %s" %loadmodulestatus;

if "SUCCESS" in loadmodulestatus.upper():
    obj.setLoadModuleStatus("SUCCESS");
    tdkTestObj = obj.createTestStep('GetCommString');
    tdkTestObj.executeTestCase("SUCCESS");

    if "." in ip:
        cmd="snmpget -OQ -Ir -v 2c -c \" \" "+ ip +" 1.3.6.1.2.1.69.1.4.5.0"
    else:
       cmd="snmpget -c \" \" -v 2c udp6:[" + ip +"] 1.3.6.1.2.1.69.1.4.5.0"
    print "cmd = ", cmd

    out=subprocess.Popen([cmd],stderr=STDOUT,stdout=PIPE,shell=True)
    actResponse = out.communicate()[0],out.returncode

    if actResponse[1] != 0:
        tdkTestObj.setResultStatus("SUCCESS");
        print "TEST STEP 1:Execute snmpget with empty community string";
        print "EXPECTED RESULT 1: snmpget should fail in get";
        print "ACTUAL RESULT 1: snmpget failed";
        #Get the result of execution
        print "[TEST EXECUTION RESULT] : %s" %actResponse[0] ;
    else:
        tdkTestObj.setResultStatus("FAILURE");
        print "TEST STEP 1:Execute snmpget with empty community string";
        print "EXPECTED RESULT 1: snmpget should fail in get";
        print "ACTUAL RESULT 1: snmpget not failed"
        print "[TEST EXECUTION RESULT] : %s" %actResponse[0] ;
    obj.unloadModule("snmp_pa");
else:
        print "FAILURE to load SNMP_PA module";
        obj.setLoadModuleStatus("FAILURE");
        print "Module loading FAILURE";


					

					