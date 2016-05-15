##
# ============================================================================
# COMCAST CONFIDENTIAL AND PROPRIETARY
# ============================================================================
# This file and its contents are the intellectual property of Comcast.  It may
# not be used, copied, distributed or otherwise  disclosed in whole or in part
# without the express written permission of Comcast.
# ============================================================================
# Copyright (c) 2016 Comcast. All rights reserved.
# ============================================================================
##

'''
<?xml version='1.0' encoding='utf-8'?>
<xml>
<id></id>
<!-- Do not edit id. This will be auto filled while exporting. If you are adding a new script keep the id empty -->
<version>2</version>
<!-- Do not edit version. This will be auto incremented while updating. If you are adding a new script you can keep the vresion as 1 -->
<name>TS_ADVANCEDCONFIG_DuplicatePortTriggeringRulesNotAllowed</name>
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
<box_type>Hybrid-1</box_type>
<!--  -->
</box_types>
<rdk_versions>
<rdk_version>RDKB</rdk_version>
<!--  -->
</rdk_versions>
</xml>
'''

# use tdklib library,which provides a wrapper for tdk testcase script 
import tdklib; 

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("advancedconfig","1");

#IP and Port of box, No need to change,
#This will be replaced with correspoing Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_ADVANCEDCONFIG_DuplicatePortTriggeringRulesNotAllowed');
#Get the result of connection with test component
loadmodulestatus =obj.getLoadModuleResult();
print "[LIB LOAD STATUS]  :  %s" %loadmodulestatus;
if "SUCCESS" in loadmodulestatus.upper():
	obj.setLoadModuleStatus("SUCCESS");

## Enable Port Trigger ##
	tdkTestObj = obj.createTestStep("AdvancedConfig_Set");
	tdkTestObj.addParameter("paramName","Device.NAT.X_CISCO_COM_PortTriggers.Enable");
	tdkTestObj.addParameter("paramValue","true");
	tdkTestObj.addParameter("paramType","boolean");
	expectedresult = "SUCCESS";
	tdkTestObj.executeTestCase(expectedresult);
	actualresult = tdkTestObj.getResult();
	print "[TEST EXECUTION RESULT] : %s" %actualresult ;  
	if expectedresult in actualresult:
		tdkTestObj.setResultStatus("SUCCESS");
		details = tdkTestObj.getResultDetails();
		print "ACTUAL RESULT 1: %s" %details;
		print "[TEST EXECUTION RESULT] : %s" %actualresult;
		print "Port trigger is enabled\n"

## Add Table for Port Trigger ##
		tdkTestObj = obj.createTestStep("AdvancedConfig_AddObject");
		tdkTestObj.addParameter("paramName","Device.NAT.X_CISCO_COM_PortTriggers.Trigger.");
		expectedresult="SUCCESS";
		tdkTestObj.executeTestCase(expectedresult);
		actualresult = tdkTestObj.getResult();
		if expectedresult in actualresult:
			tdkTestObj.setResultStatus("SUCCESS");
			details = tdkTestObj.getResultDetails();
			print "ACTUAL RESULT 2: %s" %details;
			print "[TEST EXECUTION RESULT] : %s" %actualresult;
			print "Added new Table for Port Trigger\n"

## Set values for Trigger Port Start ##
			tdkTestObj = obj.createTestStep("AdvancedConfig_Set");
			tdkTestObj.addParameter("paramName","Device.NAT.X_CISCO_COM_PortTriggers.Trigger.1.TriggerPortStart");
			tdkTestObj.addParameter("paramValue","8089");
			tdkTestObj.addParameter("paramType","unsignedint");
			expectedresult="SUCCESS";
			tdkTestObj.executeTestCase(expectedresult);
			actualresult = tdkTestObj.getResult();
			if expectedresult in actualresult:
				tdkTestObj.setResultStatus("SUCCESS");
				details = tdkTestObj.getResultDetails();
				print "ACTUAL RESULT 3: %s" %details;
				print "[TEST EXECUTION RESULT] : %s" %actualresult;
				print "Port trigger is enabled\n"
	
## Add New Table ##
				tdkTestObj = obj.createTestStep("AdvancedConfig_AddObject");
				tdkTestObj.addParameter("paramName","Device.NAT.X_CISCO_COM_PortTriggers.Trigger.");
				expectedresult="SUCCESS";
				tdkTestObj.executeTestCase(expectedresult);
				actualresult = tdkTestObj.getResult();
				if expectedresult in actualresult:
					tdkTestObj.setResultStatus("SUCCESS");
					details = tdkTestObj.getResultDetails();
					print "ACTUAL RESULT 4: %s" %details;
					print "[TEST EXECUTION RESULT] : %s" %actualresult;
					print "Protocol option is available\n"
					tdkTestObj = obj.createTestStep("AdvancedConfig_Set");
					tdkTestObj.addParameter("paramName","Device.NAT.X_CISCO_COM_PortTriggers.Trigger.2.TriggerPortStart");
					tdkTestObj.addParameter("paramValue","8089");
					tdkTestObj.addParameter("paramType","unsignedint");
					expectedresult="FAILURE";
					tdkTestObj.executeTestCase(expectedresult);
					actualresult = tdkTestObj.getResult();
					print "Different rules with same port numbers must not be allowed"
					if expectedresult in actualresult:
						tdkTestObj.setResultStatus("SUCCESS");
						details = tdkTestObj.getResultDetails();
						print "ACTUAL RESULT 5: %s" %details;
						print "[TEST EXECUTION RESULT] : %s" %actualresult;
						print "Protocol option is available\n"
					else:
						tdkTestObj.setResultStatus("FAILURE");
						details = tdkTestObj.getResultDetails();
						print "ACTUAL RESULT 5: %s" %details;
						print "[TEST EXECUTION RESULT] : %s" %actualresult;
						print "Failed to set Trigger Port Start Address  \n"

				else:
					tdkTestObj.setResultStatus("FAILURE");
					details = tdkTestObj.getResultDetails();
					print "ACTUAL RESULT 4: %s" %details;
					print "[TEST EXECUTION RESULT] : %s" %actualresult;
					print "Failed to add table \n"
			else:
				tdkTestObj.setResultStatus("FAILURE");
				details = tdkTestObj.getResultDetails();
				print "ACTUAL RESULT 3: %s" %details;
				print "[TEST EXECUTION RESULT] : %s" %actualresult;
				print "Failed to set Trigger Port Start Address \n"
		else:
			tdkTestObj.setResultStatus("FAILURE");
			details = tdkTestObj.getResultDetails();
			print "ACTUAL RESULT 2: %s" %details;
			print "[TEST EXECUTION RESULT] : %s" %actualresult;
			print "Failed to add table \n"
	else:
		tdkTestObj.setResultStatus("FAILURE");
		details = tdkTestObj.getResultDetails();
		print "ACTUAL RESULT 1: %s" %details;
		print "[TEST EXECUTION RESULT] : %s" %actualresult;
		print "Failed to enable port trigger \n "
	obj.unloadModule("advancedconfig");
else:
	print "FAILURE to load Advancedconfig module";
	obj.setLoadModuleStatus("FAILURE");
	print "Module loading FAILURE";		
