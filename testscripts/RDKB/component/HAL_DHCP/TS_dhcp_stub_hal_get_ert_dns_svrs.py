#  ===========================================================================
#  Copyright 2016-2017 Intel Corporation

#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at

#http://www.apache.org/licenses/LICENSE-2.0

#Unless required by applicable law or agreed to in writing, software
#distributed under the License is distributed on an "AS IS" BASIS,
#WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#See the License for the specific language governing permissions and
#limitations under the License.
#  ===========================================================================

'''
<?xml version="1.0" encoding="UTF-8"?><xml>
  <id/>
  <version>13</version>
  <name>TS_dhcp_stub_hal_get_ert_dns_svrs</name>
  <primitive_test_id/>
  <primitive_test_name>dhcp_stub_hal_get_ert_dns_svrs</primitive_test_name>
  <primitive_test_version>1</primitive_test_version>
  <status>FREE</status>
  <synopsis>To validate HAL API dhcpv4c_get_ert_dns_svrs()</synopsis>
  <groups_id/>
  <execution_time>1</execution_time>
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
    <test_case_id>TC_HAL_DHCP_17</test_case_id>
    <test_objective>To validate Ethsw HAL API dhcpv4c_get_ert_dns_svrs()</test_objective>
    <test_type>Positive</test_type>
    <test_setup>Broadband</test_setup>
    <pre_requisite>1.Ccsp Components  should be in a running state of DUT
2.TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>dhcpv4c_get_ert_dns_svrs()</api_or_interface_used>
    <input_parameters>None</input_parameters>
    <automation_approch>1. Load  dhcp module.
2. From script invoke dhcpv4c_get_ert_dns_svrs().
3. Get the IP address of dns server
4. Validation of  the result is done within the python script and send the result status to Test Manager.
5. Test Manager will publish the result in GUI as PASS/FAILURE based on the response from HAL_DHCP stub.</automation_approch>
    <except_output>IP address should be valid.</except_output>
    <priority>High</priority>
    <test_stub_interface>HAL_DHCP</test_stub_interface>
    <test_script>TS_dhcp_stub_hal_get_ert_dns_svrs</test_script>
    <skipped>No</skipped>
    <release_version/>
    <remarks/>
  </test_cases>
  <script_tags/>
</xml>

'''
# use tdklib library,which provides a wrapper for tdk testcase script 
import tdklib;

#Test component to be tested

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
MAX_RETRY = 10;

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("dhcp","RDKB");
sysObj = tdklib.TDKScriptingLibrary("sysutil","RDKB");
obj.configureTestCase(ip,port,'TS_dhcp_stub_hal_get_ert_dns_svrs');
sysObj.configureTestCase(ip,port, 'TS_dhcp_stub_hal_get_ert_dns_svrs');

#Get the result of connection with test component and STB
loadmodulestatus1 =obj.getLoadModuleResult();
loadmodulestatus2 =sysObj.getLoadModuleResult();
print "[LIB LOAD STATUS] : %s" %loadmodulestatus1 ;
print "[LIB LOAD STATUS] : %s" %loadmodulestatus2 ;

if "SUCCESS" in loadmodulestatus1.upper() and loadmodulestatus2.upper():
        obj.setLoadModuleStatus("SUCCESS");
        sysObj.setLoadModuleStatus("SUCCESS");

        #Script to load the configuration file of the component
        tdkTestObj = obj.createTestStep("dhcp_stub_hal_get_ert_dns_svrs");
        expectedresult = "SUCCESS";
        tdkTestObj.executeTestCase(expectedresult);
        actualresult = tdkTestObj.getResult();

        details = tdkTestObj.getResultDetails();
        if expectedresult in actualresult and details:
            #Set the result status of execution
            tdkTestObj.setResultStatus("SUCCESS");
            details1 = details.split("/")[1];
            print "TEST STEP 1: Retrieve the dhcp_stub_hal_get_ert_dns_svrs";
            print "EXPECTED RESULT 1: Should retrieve the dhcp_stub_hal_get_ert_dns_svrs successfully";
            #Get the result of execution
            print "[TEST EXECUTION RESULT] : %s" %actualresult ;
            details1 = details1.upper();

            tdkTestObj = sysObj.createTestStep('ExecuteCmd');
            retryCount = 1;
            while retryCount < MAX_RETRY:
                tdkTestObj.addParameter("command", "cat /etc/resolv.conf | grep nameserver | awk 'NR==%s{print $2}'" %retryCount);
                tdkTestObj.executeTestCase(expectedresult);
                details3 = tdkTestObj.getResultDetails();
                if details1 in details3:
                    break;
                else:
                    retryCount = retryCount + 1;

            actualresult = tdkTestObj.getResult();
            #Set the result status of execution
            tdkTestObj.setResultStatus("SUCCESS");
            print "details1 = %s, details3 = %s" %(details1, details3);
            if details1 in details3:
                tdkTestObj.setResultStatus("SUCCESS");
                print "TEST STEP 2: Verify the value";
                print "EXPECTED RESULT 2: Value should be valid";
                print "ACTUAL RESULT 2: Value is valid";
                print "[TEST EXECUTION RESULT] : %s" %actualresult ;
            else:
                tdkTestObj.setResultStatus("FAILURE");
                print "TEST STEP 2: Verify the value";
                print "EXPECTED RESULT 2: Value should be valid";
                print "ACTUAL RESULT 2: Value is not valid";
                print "[TEST EXECUTION RESULT] : FAILURE";
        else:
            tdkTestObj.setResultStatus("FAILURE");
            print "TEST STEP 1: Retrieve the dhcp_stub_hal_get_ert_dns_svrs";
            print "EXPECTED RESULT 1: Should retrieve the dhcp_stub_hal_get_ert_dns_svrs successfully";
            print "ACTUAL RESULT 1: %s" %details;
            print "[TEST EXECUTION RESULT] : Failure"; 

        obj.unloadModule("dhcp");
        sysObj.unloadModule("sysutil");
else:
        print "Failed to load the module";
        obj.setLoadModuleStatus("FAILURE");
        sysObj.setLoadModuleStatus("FAILURE");
        print "Module loading failed";
