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
  <version>15</version>
  <!-- Do not edit version. This will be auto incremented while updating. If you are adding a new script you can keep the vresion as 1 -->
  <name>TS_MTAAGENT_SetValues_with_SetAttr</name>
  <!-- If you are adding a new script you can specify the script name. Script Name should be unique same as this file name with out .py extension -->
  <primitive_test_id> </primitive_test_id>
  <!-- Do not change primitive_test_id if you are editing an existing script. -->
  <primitive_test_name>MTA_agent_SetParameterValues</primitive_test_name>
  <!--  -->
  <primitive_test_version>1</primitive_test_version>
  <!--  -->
  <status>FREE</status>
  <!--  -->
  <synopsis>TC_MTAAGENT_8 - To Validate Set Param Values functionality with Set Parameter Attribute for 
MTA Agent</synopsis>
  <!--  -->
  <groups_id>4</groups_id>
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
import tdklib; 

#Test component to be tested
obj = tdklib.TDKScriptingLibrary("Mta_agent","RDKB");

#IP and Port of box, No need to change,
#This will be replaced with corresponding Box Ip and port while executing script
ip = <ipaddress>
port = <port>
obj.configureTestCase(ip,port,'TS_MTAAGENT_SetValues_with_SetAttr');

#Get the result of connection with test component and STB
loadmodulestatus =obj.getLoadModuleResult();
print "[LIB LOAD STATUS]  :  %s" %loadmodulestatus ;

if "SUCCESS" in loadmodulestatus.upper():
    #Set the result status of execution
    obj.setLoadModuleStatus("SUCCESS");
		
    tdkTestObj = obj.createTestStep('MTA_agent_SetParameterValues');  
    tdkTestObj.addParameter("ParamName","Device.X_CISCO_COM_MTA.EnableMTALog");

    tdkTestObj.addParameter("ParamValue","true");
    tdkTestObj.addParameter("Type","boolean");
		
    expectedresult="SUCCESS";

    #Execute the test case in STB
    tdkTestObj.executeTestCase(expectedresult);

    actualresult = tdkTestObj.getResult();
    details = tdkTestObj.getResultDetails();
		
    if expectedresult in actualresult:
        #Set the result status of execution
        tdkTestObj.setResultStatus("SUCCESS");
        
        print "Parameter value should be set as by default the access remains Anybody";		
        print "[TEST EXECUTION RESULT] : %s" %actualresult ;
	print "%s" %details;
	
	
	tdkTestObj = obj.createTestStep('MTA_agent_SetParameterAttr');
        tdkTestObj.addParameter("ParamName","Device.X_CISCO_COM_MTA.EnableMTALog");
	tdkTestObj.addParameter("AccessControl","acs");
        tdkTestObj.addParameter("Notify","active");
	
	expectedresult="SUCCESS";
	    		
	#Execute the test case in STB
        tdkTestObj.executeTestCase(expectedresult);

	actualresult = tdkTestObj.getResult();
	details = tdkTestObj.getResultDetails();
		
	if expectedresult in actualresult:
	    #Set the result status of execution
            tdkTestObj.setResultStatus("SUCCESS");
	    print "Parameter access has been changed from ANYBODY";
            print "[TEST EXECUTION RESULT] : %s" %actualresult ;
	    print "%s" %details;

            tdkTestObj = obj.createTestStep('MTA_agent_SetParameterValues');  
            tdkTestObj.addParameter("ParamName","Device.X_CISCO_COM_MTA.EnableMTALog");
    
            tdkTestObj.addParameter("ParamValue","false");
            tdkTestObj.addParameter("Type","boolean");	
	
	    expectedresult="FAILURE";
	    		
	    #Execute the test case in STB
            tdkTestObj.executeTestCase(expectedresult);

	    actualresult = tdkTestObj.getResult();
	    details = tdkTestObj.getResultDetails();
		
	    if expectedresult in actualresult:
	        #Set the result status of execution
                tdkTestObj.setResultStatus("SUCCESS");
                print "Parameter value should not be changed as access control has changed from ANYBODY";		
                print "[TEST EXECUTION RESULT] : %s" %actualresult ;
	        print "%s" %details; 
				
	        tdkTestObj = obj.createTestStep('MTA_agent_SetParameterAttr');
                tdkTestObj.addParameter("ParamName","Device.X_CISCO_COM_MTA.EnableMTALog");
	        tdkTestObj.addParameter("AccessControl","anybody");
                tdkTestObj.addParameter("Notify","active");
	
	        expectedresult="SUCCESS";
	    		
	        #Execute the test case in STB
                tdkTestObj.executeTestCase(expectedresult);

	        actualresult = tdkTestObj.getResult();
	        details = tdkTestObj.getResultDetails();
		
	        if expectedresult in actualresult:
		    #Set the result status of execution
                    tdkTestObj.setResultStatus("SUCCESS");
			
		    print "Parameter access has been changed again to ANYBODY";		
                    print "[TEST EXECUTION RESULT] : %s" %actualresult ;
	            print "%s" %details; 
					
		    tdkTestObj = obj.createTestStep('MTA_agent_SetParameterValues');  
                    tdkTestObj.addParameter("ParamName","Device.X_CISCO_COM_MTA.EnableMTALog");
  
                    tdkTestObj.addParameter("ParamValue","false");
                    tdkTestObj.addParameter("Type","boolean");	
			
		    expectedresult="SUCCESS";
	    		
	            #Execute the test case in STB
                    tdkTestObj.executeTestCase(expectedresult);

	            actualresult = tdkTestObj.getResult();
	            details = tdkTestObj.getResultDetails();
		    print "Parameter value should be set as access control is ANYBODY";	
	            if expectedresult in actualresult:
		        #Set the result status of execution
                        tdkTestObj.setResultStatus("SUCCESS");
                        	
                        print "[TEST EXECUTION RESULT] : %s" %actualresult ;
	                print "%s" %details; 
						
	            else:   
                        tdkTestObj.setResultStatus("FAILURE");
	                print "[TEST EXECUTION RESULT] : %s" %actualresult ;	
	                print "%s" %details;
						
                else:   
                    tdkTestObj.setResultStatus("FAILURE");
	            print "[TEST EXECUTION RESULT] : %s" %actualresult ;	
	            print "%s" %details;  
            else:   
                 tdkTestObj.setResultStatus("FAILURE"); 
	         print "[TEST EXECUTION RESULT] : %s" %actualresult ;	
                 print "%s" %details;

        else:   
            tdkTestObj.setResultStatus("FAILURE"); 
	    print "[TEST EXECUTION RESULT] : %s" %actualresult ;	
            print "%s" %details;
  

    else:
	
        tdkTestObj.setResultStatus("FAILURE");
        print "[TEST EXECUTION RESULT] : %s" %actualresult ;	
        print "%s" %details;
    
    obj.unloadModule("Mta_agent");
   		 
else:   
    print "Failed to load MTA module";
    obj.setLoadModuleStatus("FAILURE");
    print "Module loading failed";	
				
