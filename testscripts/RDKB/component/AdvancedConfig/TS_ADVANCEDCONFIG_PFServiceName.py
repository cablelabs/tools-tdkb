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
  <version>16</version>
  <name>TS_ADVANCEDCONFIG_PFServiceName</name>
  <primitive_test_id/>
  <primitive_test_name>AdvancedConfig_Set</primitive_test_name>
  <primitive_test_version>1</primitive_test_version>
  <status>FREE</status>
  <synopsis/>
  <groups_id/>
  <execution_time>1</execution_time>
  <long_duration>false</long_duration>
  <remarks/>
  <skip>false</skip>
  <box_types>
    <box_type>Emulator</box_type>
    <box_type>Broadband</box_type>
  </box_types>
  <rdk_versions>
    <rdk_version>RDKB</rdk_version>
  </rdk_versions>
  <test_cases>
    <test_case_id>TC_ADVANCEDCONFIG_4</test_case_id>
    <test_objective>To Validate "Parental Control &gt; Service name option for port forwarding rule" functionality</test_objective>
    <test_type>Possitive</test_type>
    <test_setup>Emulator,
XB3</test_setup>
    <pre_requisite>1.Ccsp Components  should be in a running state else invoke cosa_start.sh manually that includes all the ccsp components and TDK Component
2.TDK Agent should be in running state or invoke it through StartTdk.sh script</pre_requisite>
    <api_or_interface_used>None</api_or_interface_used>
    <input_parameters>Json Interface:
API Name
AdvancedConfig_Set
AdvancedConfig_AddObject
AdvancedConfig_GetNames

Input
1.PathName ("paramName")
( eg: "Device.NAT.X_Comcast_com_EnablePortMapping" )
Type: bool, Value: true

2.PathName ("paramName")
( eg: "Device.NAT.PortMapping." )

3. PathName ("paramName")
( eg: "Device.NAT.PortMapping.1.Alias" )
Type: string, Value: new service

4. PathName ("paramName")
( eg: "Device.NAT.PortMapping.1.Protocol" )
Type: string Value: UDP

5. PathName ("paramName")
( eg: "Device.NAT.PortMapping.1.ExternalPort" )
Type: unsignedint Value : 21

6. PathName ("paramName")
( eg: "Device.NAT.PortMapping.1.ExternalPortEndRange" )
Type: unsignedint Value : 21

7. PathName ("paramName")
( eg: "Device.NAT.PortMapping.1.InternalClient" )
Type: string Value : 192.168.22.22</input_parameters>
    <automation_approch>1.Configure the Function info in Test Manager GUI  which needs to be tested  
(AdvancedConfig_Set,AdvancedConfig_AddObject, AdvancedConfig_GetNames - func name - "If not exists already"
 advancedconfig - module name
 Necessary I/P args as Mentioned in Input)
2.Python Script will be generated/overrided automically by Test Manager with provided arguments in configure page (TS_ADVANCEDCONFIG_PFServiceName.py)
3.Execute the generated Script(TS_ADVANCEDCONFIG_PFServiceName.py) using execution page of  Test Manager GUI
4.advancedconfigstub which is a part of TDK Agent process, will be in listening mode to execute TDK Component function named AdvancedConfig_Set, AdvancedConfig_AddObject through registered TDK advancedconfigstub function along with necessary Entry Values as arguments
5.AdvancedConfig_Set function will call ssp_setParameterValue,that inturn will call CCSP Base Interface Function named CcspBaseIf_setParameterValues.
6. AdvancedConfig_AddObject function will call ssp_addTableRow, that inturn will call CCSP Base Interface Function named CcspBaseIf_AddTblRow and AdvancedConfig_GetNames Will find the instance number of the row added and will process the function for the instance number generated.
7.Responses(printf) from TDK Component,Ccsp Library function and advancedcongifstub would be logged in Agent Console log based on the debug info redirected to agent console   
8.advancedconfigstub will validate the available result (from ssp_setParameterValue as zero) with expected result (zero) and the result is updated in agent console log and json output variable
9.TestManager will publish the result in GUI as SUCCESS/FAILURE based on the response from AdvancedConfig_Set and AdvancedConfig_AddObject function.</automation_approch>
    <except_output>Checkpoint 1:
Check if the service name option for port forwarding rule is success. 
CheckPoint 2:
Success log should be available in Agent Console Log
CheckPoint 3:
TDK agent Test Function will log the test case result as SUCCESS based on API response 
CheckPoint 4:
TestManager GUI will publish the result as SUCCESS in Execution page</except_output>
    <priority>High</priority>
    <test_stub_interface>none</test_stub_interface>
    <test_script>TS_ADVANCEDCONFIG_PFServiceName</test_script>
    <skipped>No</skipped>
    <release_version/>
    <remarks/>
  </test_cases>
  <script_tags/>
</xml>

'''
						#use tdklib library,which provides a wrapper for tdk testcase script
import tdklib;
import tdkutility;

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("advancedconfig","RDKB");

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_ADVANCEDCONFIG_PFServiceName');

#Get the result of connection with test component and STB
loadModuleresult =obj.getLoadModuleResult();
print "[LIB LOAD STATUS]  :  %s" %loadModuleresult;

if "SUCCESS" in loadModuleresult.upper():
        obj.setLoadModuleStatus("SUCCESS");

        #Enabling port forwarding - setting the port mapping as true
        tdkTestObj = obj.createTestStep("AdvancedConfig_Set");
        tdkTestObj.addParameter("paramName","Device.NAT.X_Comcast_com_EnablePortMapping");
        tdkTestObj.addParameter("paramValue","true");
        tdkTestObj.addParameter("paramType","boolean");
        expectedresult = "SUCCESS";
        tdkTestObj.executeTestCase(expectedresult);
        actualresult = tdkTestObj.getResult();
        print "[TEST EXECUTION RESULT] : %s" %actualresult ;
        if expectedresult in actualresult:
                #Set the result status of execution
                tdkTestObj.setResultStatus("SUCCESS");
                details = tdkTestObj.getResultDetails();
                print "ACTUAL RESULT 1: %s" %details;
                print "[TEST EXECUTION RESULT] : %s" %actualresult;
                print "Port forwarding is enabled\n"

                # Adding a new row to the port forwarding table
                tdkTestObj = obj.createTestStep("AdvancedConfig_AddObject");
                tdkTestObj.addParameter("paramName","Device.NAT.PortMapping.");
                expectedresult="SUCCESS";
                tdkTestObj.executeTestCase(expectedresult);
                actualresult = tdkTestObj.getResult();
                if expectedresult in actualresult:
                #Set the result status of execution
                        tdkTestObj.setResultStatus("SUCCESS");
			details = tdkTestObj.getResultDetails();
                        print "ACTUAL RESULT 2: %s" %details;
                        #Get the result of execution
                        print "[TEST EXECUTION RESULT] : %s" %actualresult;
                        print "Add service option is selected and a new table is created\n"
			tdkTestObj = obj.createTestStep("AdvancedConfig_GetNames");
                        tdkTestObj.addParameter("pathname","Device.NAT.PortMapping.");
                        tdkTestObj.addParameter("brecursive",1);
                        expectedresult = "SUCCESS";
                        tdkTestObj.executeTestCase(expectedresult);
                        actualresult = tdkTestObj.getResult();
                        print "[TEST EXECUTION RESULT] : %s" %actualresult ;
                        if expectedresult in actualresult:
                                #Set the result status of execution
                                tdkTestObj.setResultStatus("SUCCESS");
                                details = tdkTestObj.getResultDetails();
                                print "ACTUAL RESULT 1: %s" %details;
                                print "[TEST EXECUTION RESULT] : %s" %actualresult;
                                index = 3;
                                instance = tdkutility.getInstanceNumber(details,index);
                                print "INSTANCE VALUE: %s" %instance
                                if (instance>0):
                                    print "INSTANCE VALUE: %s" %instance
                                    # Setting the service name
                                    tdkTestObj = obj.createTestStep("AdvancedConfig_Set");
                                    tdkTestObj.addParameter("paramName","Device.NAT.PortMapping.%s.Alias" %instance);
                                    tdkTestObj.addParameter("paramValue","new service");
                                    tdkTestObj.addParameter("paramType","string");
                                    expectedresult="SUCCESS";
                                    tdkTestObj.executeTestCase(expectedresult);
                                    actualresult = tdkTestObj.getResult();
                                    if expectedresult in actualresult:
                                        #Set the result status of execution
                                        tdkTestObj.setResultStatus("SUCCESS");
                                        details = tdkTestObj.getResultDetails();
                                        print "ACTUAL RESULT 3: %s" %details;
                                        #Get the result of execution
                                        print "[TEST EXECUTION RESULT] : %s" %actualresult;
                                        print "Service name is set\n"

                                        # Setting the protocol type
                                        tdkTestObj = obj.createTestStep("AdvancedConfig_Set");
                                        tdkTestObj.addParameter("paramName","Device.NAT.PortMapping.%s.Protocol" %instance);
                                        tdkTestObj.addParameter("paramValue","UDP");
                                        tdkTestObj.addParameter("paramType","string");
                                        expectedresult="SUCCESS";
                                        tdkTestObj.executeTestCase(expectedresult);
                                        actualresult = tdkTestObj.getResult();
                                        if expectedresult in actualresult:
                                            #Set the result status of execution
                                            tdkTestObj.setResultStatus("SUCCESS");
                                            details = tdkTestObj.getResultDetails();
                                            print "ACTUAL RESULT 4: %s" %details;
                                            #Get the result of execution
                                            print "[TEST EXECUTION RESULT] : %s" %actualresult;
                                            print "Protocol type is set\n"

                                            #setting the start port
                                            tdkTestObj = obj.createTestStep("AdvancedConfig_Set");
                                            tdkTestObj.addParameter("paramName","Device.NAT.PortMapping.%s.ExternalPort" %instance);
                                            tdkTestObj.addParameter("paramValue","21");
                                            tdkTestObj.addParameter("paramType","unsignedint");										   
                                            expectedresult="SUCCESS";
                                            tdkTestObj.executeTestCase(expectedresult);
                                            actualresult = tdkTestObj.getResult();
                                            if expectedresult in actualresult:
                                                #Set the result status of execution
                                                tdkTestObj.setResultStatus("SUCCESS");
                                                details = tdkTestObj.getResultDetails();
                                                print "ACTUAL RESULT 5: %s" %details;
                                                #Get the result of execution
                                                print "[TEST EXECUTION RESULT] : %s" %actualresult;
                                                print "Start port is set\n"

                                                #setting the end port
                                                tdkTestObj = obj.createTestStep("AdvancedConfig_Set");
                                                tdkTestObj.addParameter("paramName","Device.NAT.PortMapping.%s.ExternalPortEndRange" %instance);
                                                tdkTestObj.addParameter("paramValue","21");
                                                tdkTestObj.addParameter("paramType","unsignedint");
                                                expectedresult="SUCCESS";
                                                tdkTestObj.executeTestCase(expectedresult);
                                                actualresult = tdkTestObj.getResult();
                                                if expectedresult in actualresult:
                                                        #Set the result status of execution
                                                        tdkTestObj.setResultStatus("SUCCESS");
                                                        details = tdkTestObj.getResultDetails();
                                                        print "ACTUAL RESULT 6: %s" %details;
                                                        #Get the result of execution
                                                        print "[TEST EXECUTION RESULT] : %s" %actualresult;
                                                        print "End port is set\n"

                                                        #setting the ip
                                                        tdkTestObj = obj.createTestStep("AdvancedConfig_Set");
                                                        tdkTestObj.addParameter("paramName","Device.NAT.PortMapping.%s.InternalClient" %instance);
                                                        tdkTestObj.addParameter("paramValue","192.168.22.22");
                                                        tdkTestObj.addParameter("paramType","string");
                                                        expectedresult="SUCCESS";
                                                        tdkTestObj.executeTestCase(expectedresult);
                                                        actualresult = tdkTestObj.getResult();
                                                        if expectedresult in actualresult:
								#Set the result status of execution
                                                                tdkTestObj.setResultStatus("SUCCESS");
                                                                details = tdkTestObj.getResultDetails();
                                                                print "ACTUAL RESULT 7: %s" %details;
                                                                #Get the result of execution
                                                                print "[TEST EXECUTION RESULT] : %s" %actualresult;
                                                                print "IP is set\n"

                                                        else:
                                                                tdkTestObj.setResultStatus("FAILURE");
                                                                details = tdkTestObj.getResultDetails();
                                                                print "ACTUAL RESULT 7: %s" %details;
                                                                print "[TEST EXECUTION RESULT] : %s" %actualresult;
                                                                print "Failure in setting the IP\n"

                                                else:
                                                        tdkTestObj.setResultStatus("FAILURE");
                                                        details = tdkTestObj.getResultDetails();
                                                        print "ACTUAL RESULT 6: %s" %details;
                                                        print "[TEST EXECUTION RESULT] : %s" %actualresult;
                                                        print "Failure in setting the end port\n"
                                            else:
                                                tdkTestObj.setResultStatus("FAILURE");
                                                details = tdkTestObj.getResultDetails();
                                                print "ACTUAL RESULT 5: %s" %details;
                                                print "[TEST EXECUTION RESULT] : %s" %actualresult;
                                                print "Failure in setting the start port\n"
                                        else:
                                            tdkTestObj.setResultStatus("FAILURE");
                                            details = tdkTestObj.getResultDetails();
                                            print "ACTUAL RESULT 4: %s" %details;
                                            print "[TEST EXECUTION RESULT] : %s" %actualresult;
                                            print "Failure in setting the protocol type\n"
                                    else:
                                        tdkTestObj.setResultStatus("FAILURE");
                                        details = tdkTestObj.getResultDetails();
                                        print "ACTUAL RESULT 3: %s" %details;
                                        print "[TEST EXECUTION RESULT] : %s" %actualresult;
                                        print "Failure in setting the service name\n"

                                else:
                                    print "Instance value should be greater than 0\n"
                                    print "Wrong instance value\n"
               
                        else:
                                tdkTestObj.setResultStatus("FAILURE");
                                details = tdkTestObj.getResultDetails();
                                print "ACTUAL RESULT 1: %s" %details;
                                print "[TEST EXECUTION RESULT] : %s" %actualresult;
                                print "Failed to getnames\n "

                        
		else:
                        tdkTestObj.setResultStatus("FAILURE");
                        details = tdkTestObj.getResultDetails();
                        print "ACTUAL RESULT 2: %s" %details;
                        print "[TEST EXECUTION RESULT] : %s" %actualresult;
                        print "Failure in adding the new port forwarding row\n"
        else:
                tdkTestObj.setResultStatus("FAILURE");
                details = tdkTestObj.getResultDetails();
                print "ACTUAL RESULT 1: %s" %details;
                print "[TEST EXECUTION RESULT] : %s" %actualresult;
                print "Failure in setting the port forwarding as true\n "

        #To delete the added table
        tdkTestObj = obj.createTestStep("AdvancedConfig_DelObject");
        tdkTestObj.addParameter("paramName","Device.NAT.PortMapping.%s." %instance);
        expectedresult = "SUCCESS";
        tdkTestObj.executeTestCase(expectedresult);
        actualresult = tdkTestObj.getResult();
        print "[TEST EXECUTION RESULT] : %s" %actualresult ;
        if expectedresult in actualresult:
            #Set the result status of execution
            tdkTestObj.setResultStatus("SUCCESS");
            details = tdkTestObj.getResultDetails();
            print "ACTUAL RESULT: %s" %details;
            print "[TEST EXECUTION RESULT] : %s" %actualresult;
            print "Added table is deleted successfully\n"
        else:
            print "Added table could not be deleted\n"                

        obj.unloadModule("advancedconfig");
else:
        print "FAILURE to load Advancedconfig module";
        obj.setLoadModuleStatus("FAILURE");
        print "Module loading FAILURE";

					
