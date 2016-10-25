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
  <version>6</version>
  <!-- Do not edit version. This will be auto incremented while updating. If you are adding a new script you can keep the vresion as 1 -->
  <name>TS_ADVANCEDCONFIG_RuleforHTTPDownloadWithInvalidIPAddress10.0.0.1</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id> </primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>AdvancedConfig_Set</primitive_test_name>
  <!--  -->
  <primitive_test_version>1</primitive_test_version>
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
						#use tdklib library,which provides a wrapper for tdk testcase script
import tdklib;
import tdkutility

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("advancedconfig","RDKB");

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_ADVANCEDCONFIG_RuleforHTTPDownloadWithInvalidIPAddress10.0.0.1');

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
                print "Port forwarding is enabled \n"

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
                        print "Enable Port Triggering\n"
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
                                if (instance > 0):
                                    print "INSTANCE VALUE: %s" %instance
                                    # Enable Port Triggering
                                    tdkTestObj = obj.createTestStep("AdvancedConfig_Set");
                                    tdkTestObj.addParameter("paramName","Device.NAT.PortMapping.%s.Enable" %instance);
                                    tdkTestObj.addParameter("paramValue","true");
                                    tdkTestObj.addParameter("paramType","boolean");
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
                                        print "Port Triggering is Enabled \n"

                                        # Setting the protocol type
                                        tdkTestObj = obj.createTestStep("AdvancedConfig_Set");
                                        tdkTestObj.addParameter("paramName","Device.NAT.PortMapping.%s.Protocol"%instance);
                                        tdkTestObj.addParameter("paramValue","TCP");
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
                                            print "Protocol type option is set to TCP \n"

                                            #Setting the start port
                                            tdkTestObj = obj.createTestStep("AdvancedConfig_Set");
                                            tdkTestObj.addParameter("paramName","Device.NAT.PortMapping.%s.ExternalPort"%instance);
                                            tdkTestObj.addParameter("paramValue","80");
                                            tdkTestObj.addParameter("paramType","uint");
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
                                                print "Start port option is set to 80 \n"

                                                #Setting the end port
                                                tdkTestObj = obj.createTestStep("AdvancedConfig_Set");
                                                tdkTestObj.addParameter("paramName","Device.NAT.PortMapping.%s.ExternalPortEndRange"%instance);
                                                tdkTestObj.addParameter("paramValue","80");
                                                tdkTestObj.addParameter("paramType","uint");
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
                                                        print "End port option is set to 80 \n"

                                                        #Setting the ip
                                                        tdkTestObj = obj.createTestStep("AdvancedConfig_Set");
                                                        tdkTestObj.addParameter("paramName","Device.NAT.PortMapping.%s.InternalClient" %instance);
                                                        tdkTestObj.addParameter("paramValue","10.0.0.1");
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
                                                                print "IP address is set to 10.0.0.1 \n"

                                                        else:
                                                                tdkTestObj.setResultStatus("FAILURE");
                                                                details = tdkTestObj.getResultDetails();
                                                                print "ACTUAL RESULT 7: %s" %details;
                                                                print "[TEST EXECUTION RESULT] : %s" %actualresult;
                                                                print "Failure in setting the IP option\n"

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
                                        print "Failure in enabling port trigger\n"

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

					
