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
  <version>7</version>
  <!-- Do not edit version. This will be auto incremented while updating. If you are adding a new script you can keep the vresion as 1 -->
  <name>TS_ADVANCEDCONFIG_CheckAddRuleOptionsOfPortTriggering</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id> </primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>AdvancedConfig_Set</primitive_test_name>
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
#use tdklib library,which provides a wrapper for tdk testcase script 
import tdklib; 
import tdkutility;

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("advancedconfig","RDKB");

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_ADVANCEDCONFIG_CheckAddRuleOptionsOfPortTriggering');

#Get the result of connection with test component and STB
loadmodulestatus =obj.getLoadModuleResult();
print "[LIB LOAD STATUS]  :  %s" %loadmodulestatus;

if "SUCCESS" in loadmodulestatus.upper():
        obj.setLoadModuleStatus("SUCCESS");
	tdkTestObj = obj.createTestStep("AdvancedConfig_Set");
	
	#Input Parameters
	tdkTestObj.addParameter("paramName","Device.NAT.X_CISCO_COM_PortTriggers.Enable");
	tdkTestObj.addParameter("paramValue","true");
	tdkTestObj.addParameter("paramType","boolean");
	expectedresult = "SUCCESS";
	tdkTestObj.executeTestCase(expectedresult);
	actualresult = tdkTestObj.getResult();
	print "[TEST EXECUTION RESULT] : %s" %actualresult ;
	
	#### Add New Table ####
	if expectedresult in actualresult:
		#Set the result status of execution
		tdkTestObj.setResultStatus("SUCCESS");
		details = tdkTestObj.getResultDetails();
		print "ACTUAL RESULT 1: %s" %details;
		print "[TEST EXECUTION RESULT] : %s" %actualresult;
		print "Port forwarding is enabled\n"
		
		tdkTestObj = obj.createTestStep("AdvancedConfig_AddObject");
		tdkTestObj.addParameter("paramName","Device.NAT.X_CISCO_COM_PortTriggers.Trigger.");
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
                        tdkTestObj.addParameter("pathname","Device.NAT.X_CISCO_COM_PortTriggers.Trigger.");
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
                                index = 4;
                                instance = tdkutility.getInstanceNumber(details,index);
                                print "INSTANCE VALUE: %s" %instance
                                if (instance > 0):
                                    print "INSTANCE VALUE: %s" %instance
                                    tdkTestObj = obj.createTestStep("AdvancedConfig_Set");
                                    tdkTestObj.addParameter("paramName","Device.NAT.X_CISCO_COM_PortTriggers.Trigger.%s.Description" %instance);
                                    tdkTestObj.addParameter("paramValue","Myservice");
                                    tdkTestObj.addParameter("paramType","string");
                                    expectedresult="SUCCESS";
                                    tdkTestObj.executeTestCase(expectedresult);
                                    actualresult = tdkTestObj.getResult();
                                    if expectedresult in actualresult:
                                        tdkTestObj.setResultStatus("SUCCESS");
                                        details = tdkTestObj.getResultDetails();
                                        print "ACTUAL RESULT 3: %s" %details;
                                        print "[TEST EXECUTION RESULT] : %s" %actualresult;
                                        print "set descrption for Trigger\n"
                                        ## set value for Triggering Protocol ##	
                                        tdkTestObj = obj.createTestStep("AdvancedConfig_Set");
                                        tdkTestObj.addParameter("paramName","Device.NAT.X_CISCO_COM_PortTriggers.Trigger.%s.TriggerProtocol" %instance);
                                        tdkTestObj.addParameter("paramValue","TCP");
                                        tdkTestObj.addParameter("paramType","string");
                                        expectedresult="SUCCESS";
                                        tdkTestObj.executeTestCase(expectedresult);
                                        actualresult = tdkTestObj.getResult();
                                        if expectedresult in actualresult:
                                            tdkTestObj.setResultStatus("SUCCESS");
                                            details = tdkTestObj.getResultDetails();
                                            print "ACTUAL RESULT 3: %s" %details;
                                            print "[TEST EXECUTION RESULT] : %s" %actualresult;
                                            print "set value for TriggerProtocol\n"
                                    
                                            ## Set value for Trigger Start Address ##
                                            tdkTestObj = obj.createTestStep("AdvancedConfig_Set");
                                    
                                            tdkTestObj.addParameter("paramName","Device.NAT.X_CISCO_COM_PortTriggers.Trigger.%s.TriggerPortStart" %instance);
                                            tdkTestObj.addParameter("paramValue","8080");
                                            tdkTestObj.addParameter("paramType","unsignedint");
                                            expectedresult="SUCCESS";
                                            tdkTestObj.executeTestCase(expectedresult);
                                            actualresult = tdkTestObj.getResult();
                                            if expectedresult in actualresult:
                                                tdkTestObj.setResultStatus("SUCCESS");
                                                details = tdkTestObj.getResultDetails();
                                                print "ACTUAL RESULT 4: %s" %details;
                                                print "[TEST EXECUTION RESULT] : %s" %actualresult;
                                                print "Set value for Trigger Port Start \n"
			
                                                ## set value for Trigger Port End
                                                tdkTestObj = obj.createTestStep("AdvancedConfig_Set");
                                                tdkTestObj.addParameter("paramName","Device.NAT.X_CISCO_COM_PortTriggers.Trigger.%s.TriggerPortEnd" %instance);
                                                tdkTestObj.addParameter("paramValue","8090");
                                                tdkTestObj.addParameter("paramType","unsignedint");
                                                expectedresult="SUCCESS";
                                                tdkTestObj.executeTestCase(expectedresult);
                                                actualresult = tdkTestObj.getResult();
                                                if expectedresult in actualresult:
                                                    tdkTestObj.setResultStatus("SUCCESS");
                                                    details = tdkTestObj.getResultDetails();
                                                    print "ACTUAL RESULT 5: %s" %details;
                                                    print "[TEST EXECUTION RESULT] : %s" %actualresult;
                                                    print "start port option is available\n"
						
                                                    ## Enable Trigger 1 ##
                                                    tdkTestObj = obj.createTestStep("AdvancedConfig_Set");
                                                    tdkTestObj.addParameter("paramName","Device.NAT.X_CISCO_COM_PortTriggers.Trigger.%s.Enable" %instance);
                                                    tdkTestObj.addParameter("paramValue","true");
                                                    tdkTestObj.addParameter("paramType","boolean");
                                                    expectedresult="SUCCESS";
                                                    tdkTestObj.executeTestCase(expectedresult);
                                                    actualresult = tdkTestObj.getResult();
                                                    if expectedresult in actualresult:
                                                        tdkTestObj.setResultStatus("SUCCESS");
                                                        details = tdkTestObj.getResultDetails();
                                                        print "ACTUAL RESULT 6: %s" %details;
                                                        print "[TEST EXECUTION RESULT] : %s" %actualresult;
                                                        print "\n"
                                                    else:
                                                        tdkTestObj.setResultStatus("FAILURE");
                                                        details = tdkTestObj.getResultDetails();
                                                        print "ACTUAL RESULT 6: %s" %details;
                                                        print "[TEST EXECUTION RESULT] : %s" %actualresult;
                                                        print "\n"
                                                else:
                                                    tdkTestObj.setResultStatus("FAILURE");
                                                    details = tdkTestObj.getResultDetails();
                                                    print "ACTUAL RESULT 5: %s" %details;
                                                    print "[TEST EXECUTION RESULT] : %s" %actualresult;
                                                    print "Failed to Set the TriggerEndPort value \n"
                                            else:
                                                tdkTestObj.setResultStatus("FAILURE");
                                                details = tdkTestObj.getResultDetails();
                                                print "ACTUAL RESULT 4: %s" %details;
                                                print "[TEST EXECUTION RESULT] : %s" %actualresult;
                                                print "Failed to Set TriggerStartPort value \n"
                                            
                                        else:
                                            tdkTestObj.setResultStatus("FAILURE");
                                            details = tdkTestObj.getResultDetails();
                                            print "ACTUAL RESULT 3: %s" %details;
                                            print "[TEST EXECUTION RESULT] : %s" %actualresult;
                                            print "Failed to set Triggered Protocol \n"
                                    else:
                                        tdkTestObj.setResultStatus("FAILURE");
                                        details = tdkTestObj.getResultDetails();
                                        print "ACTUAL RESULT 3: %s" %details;
                                        print "[TEST EXECUTION RESULT] : %s" %actualresult;
                                        print "Failed to set Triggered description \n"
		
                                else:
                                    print "Instance value should be greater than 0 \n"
                                    print "Wrong instance value"

								
               
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
                    print "Failed to add new table \n"
        else:
            tdkTestObj.setResultStatus("FAILURE");
            details = tdkTestObj.getResultDetails();
            print "ACTUAL RESULT 1: %s" %details;
            print "[TEST EXECUTION RESULT] : %s" %actualresult;
            print "Failed to enable Port Trigger \n "

        #To delete the added table
        tdkTestObj = obj.createTestStep("AdvancedConfig_DelObject");
        tdkTestObj.addParameter("paramName","Device.NAT.X_CISCO_COM_PortTriggers.Trigger.%s." %instance);
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

					

					
