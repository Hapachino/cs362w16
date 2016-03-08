/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


import java.util.Random;

import junit.framework.TestCase;





/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */
public class UrlValidatorTest extends TestCase {
    
    private boolean printStatus = false;
    private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.
    
    public UrlValidatorTest(String testName) {
        super(testName);
    }
    
    
    
    public void testManualTest()
    {
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        System.out.println(urlVal.isValid("http://www.amazon.com"));							// default URL given
        System.out.println(urlVal.isValid("http://www.google.com"));							// test typical URL
        System.out.println(urlVal.isValid(""));												// test empty URL
        System.out.println(urlVal.isValid("https://www.google.com"));						// test scheme https://
        System.out.println(urlVal.isValid("https://www.maps.google.com"));					// test subdomain
        System.out.println(urlVal.isValid("http://www.google.com:8000"));					// test port
    }
    
    
    public void testYourFirstPartition()
    {
    	int count = 1000; 
    	Random r = new Random();
    	String testString = "";
    	//can not appear in scheme
    	char[] excludedCharacters = {';', '/', '?', ':', '@', '&', '=', 
    			'$', ',', '"', '>', '<', '#', '%', '{', '}', '|', '\\', '^', 
    			'[', ']', '`', '!', '\'', '(', ')', '*', '/', '_' };
    	UrlValidator urlVal = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
    	for (int i = 1; i < count; i++)
    	{
    		boolean expected = true;
    		testString = "";
    		for (int j = 0; j <3 ; j++)
    		{
    			int t = r.nextInt(126-33) + 33;
    			//test character
    			//scheme must begin with a letter
    			if (j == 0 ){
    				//if number is not ASCII upper or lower case letter
    				//set expected result = false
    				if (!(t >= 65 && t<= 90) && !(t >= 97 && t <= 122))
    				{
    					expected &= false;
    				}
    			}
    		char[] tempChar = Character.toChars(t); 
    		if (new String(excludedCharacters).contains(Character.toString(tempChar[0])))
    		{
    			expected &= false;
    		}
    			testString += tempChar[0];
    		}

    		//append generic domain 
    		testString = testString + "://google.com";

    		boolean result = urlVal.isValid(testString);
    		System.out.print("String: " + testString + "\tExpeected: " + expected + 
    				"\tResult: " + result + "\n");
    		assertEquals(expected, result);
    		if (printStatus) {
    			if (result == expected) {
    				System.out.print('.');
    			} else {
    				System.out.print('X');
    			}
    		}
    	}
    	if (printStatus) {
    		System.out.println();
    	}

    }
    
    public void testYourSecondPartition()
    {
        
    }
    
    // A port number is a 16-bit unsigned integer that ranges from 0 - 65535. Ports 49152-65536 are never assigned.
    // source: http://tools.ietf.org/html/rfc6335
    public void testPortRange() {
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        ResultPair[] testUrlPort = {new ResultPair("", true),								// Empty port
            new ResultPair(":", false),								// If the port is omitted, the colon is as well. source: RFC 1738 Uniform Resource Locators
            new ResultPair(":-1", false),							// Negative value
            new ResultPair(":8", true),
            new ResultPair(":80", true),								// Standard HTTP port value.
            new ResultPair(":800", true),
            new ResultPair(":8000", true),
            new ResultPair(":65535", true),							// Maximum limit to port value
            new ResultPair(":65536", false)							// Exceeds maximum limit of port value
        };
        String url = "http://www.google.com";
        
        assertTrue(urlVal.isValid(url));
        System.out.println("Testing Port Number Range");
        for (int i = 0; i < testUrlPort.length; i++) {
            System.out.println(url + testUrlPort[i].item + " \nExpected: " + testUrlPort[i].valid);
            System.out.println("Actual: " + urlVal.isValid(url + testUrlPort[i].item) + "\n");
            //assertTrue(urlVal.isValid(url + testUrlPort[i].item));
        }
    }
    
    public void testYourThirdPartition()
    {
    	//testing queries
    	UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
    	String testString = "";
    	
    	ResultPair[] testQuery = {new ResultPair("?action=delete", true),
                new ResultPair("?foo=bar&bar=foo", true),
                new ResultPair("?=foo&bar=foo", false),                      
                new ResultPair("", true)
    	};
    	
    	//Test that http://www.google.com to be used with all test schemes is valid
    	System.out.println("Testing http://www.google.com \nResult: " +  urlVal.isValid("http://www.google.com"));     // test typical URL
    	
    	System.out.println("\nTesting queries...\n");
    	for (int i = 0; i < testQuery.length; i++)
    	{
    		testString = "http://www.google.com" + testQuery[i].item;
    		
    		System.out.println(testString + " \nExpected: " + testQuery[i].valid);
            System.out.println("Actual: " + urlVal.isValid(testString) + "\n");		
    	}
    	
    	
        
    }
    
    public void testIsValid()
    {
        for(int i = 0;i<10000;i++)
        {
            
        }
    }
    
    public void testAnyOtherUnitTest()
    {
    	
    	UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
    	String testString = "";
    	int iterationNumber = 1;
    	  	
        /**
         * Create set of tests by taking the testUrlXXX arrays and
         * running through all possible permutations of their combinations.
         *
         * @param testObjects Used to create a url.
         */
    	
    	ResultPair[] testScheme = {new ResultPair("http://", true),
                new ResultPair("ftp://", true),
                new ResultPair("mailto://", true),
                new ResultPair("ht4://", false),
                new ResultPair("http:/", false),
                new ResultPair("http:", false),
                new ResultPair("http/", false),
                new ResultPair("://", false),
                new ResultPair("https://", true),
                new ResultPair("", true)};
    		
    	ResultPair[] testAuthority = {new ResultPair("www.google.com", true),
                new ResultPair("wikipedia.org", true),
                new ResultPair("amazon.com", true),
                new ResultPair("0.0.0.0", true),
                new ResultPair("255.255.255.255", true),
                new ResultPair("256.256.256.256", false),
                new ResultPair("255.com", true),
                new ResultPair("1.2.3.4.5", false),
                new ResultPair("1.2.3.4.", false),
                new ResultPair("1.2.3", false),
                new ResultPair(".1.2.3.4", false),
                new ResultPair("abcde.", false),
                new ResultPair(".abc", false),
                new ResultPair("abcde", false),
                new ResultPair("", false)
    	};
    	ResultPair[] testPort = {new ResultPair("", true),               //empty port
    			new ResultPair(":", false),								// If the port is omitted, the colon is as well. source: RFC 1738 Uniform Resource Locators
                new ResultPair(":-1", false),							// Negative value
                new ResultPair(":8", true),
                new ResultPair(":80", true),								// Standard HTTP port value.
                new ResultPair(":800", true),
                new ResultPair(":8000", true),
                new ResultPair(":65535", true),							// Maximum limit to port value
                new ResultPair(":65536", false)							// Exceeds maximum limit of port value
    	};
    	ResultPair[] testPath = {new ResultPair("/test1", true),
    	        new ResultPair("/foo123", true),
    	        new ResultPair("/$17", true),
    	        new ResultPair("/..", false),
    	        new ResultPair("/../", false),
    	        new ResultPair("/foo/", true),
    	        new ResultPair("", true),
    	        new ResultPair("/foo/bar", true),
    	        new ResultPair("/test1//file", false)
    	};
    	
    	
    	ResultPair[] testQuery = {new ResultPair("?action=delete", true),
                new ResultPair("?foo=bar&bar=foo", true),
                new ResultPair("?=foo&bar=foo", false),                      
                new ResultPair("", true)
    	};
    	
    	
    	 /*
    	   A complete URL is composed of a scheme+authority+port+path+query,
    	   all of which must be individually valid for the entire URL to be considered
    	   valid.
    	 */
    	System.out.println("Testing complete URLs...");
    	
    	for (int schemeIndex = 0; schemeIndex < testScheme.length; schemeIndex++)
    	{
    		for (int authorityIndex = 0; authorityIndex < testAuthority.length; authorityIndex++)
        	{
    			for (int portIndex = 0; portIndex < testPort.length; portIndex++)
            	{
    				for (int pathIndex = 0; pathIndex < testPath.length; pathIndex++)
                	{
    					for (int queryIndex = 0; queryIndex < testQuery.length; queryIndex++)
                    	{
    						//build the URL to test
    						testString = testScheme[schemeIndex].item + testAuthority[authorityIndex].item + testPort[portIndex].item + testPath[pathIndex].item + testQuery[queryIndex].item;
    						
    						boolean expected = true;
    						
    						//set the expected result
    						if(!testScheme[schemeIndex].valid  || !testAuthority[authorityIndex].valid  || !testPort[portIndex].valid  || !testPath[pathIndex].valid  || !testQuery[queryIndex].valid)
    						{
    							expected = false;
    						}
    						
    						//run isValid()
    						boolean result = urlVal.isValid(testString);
    						
    						
    						if (expected != result)
    						{
    							
    							System.out.println("Test#" + iterationNumber + "\n===========================");
    							System.out.println(testString + " \nExpected: " + expected);
        			            System.out.println("Actual: " + result + "\n");
        			            
        			            //try to hone in on the problem by pairing each part with other valid parts
        			            System.out.println("Scheme: "+ testScheme[schemeIndex].item + ", " + testScheme[schemeIndex].valid);
        			            System.out.println("Authority: " + testAuthority[authorityIndex].item + ", " + testAuthority[authorityIndex].valid);
        			            System.out.println("Port: " + testPort[portIndex].item + ", " + testPort[portIndex].valid);
        			            System.out.println("Path: " + testPath[pathIndex].item + ", " + testPath[pathIndex].valid);
        			            System.out.println("Query: " + testQuery[queryIndex].item + ", " + testQuery[queryIndex].valid);
        			            System.out.println("\n");
        			               
    						}
    						
    			            //assertEquals(expected, result);
    						iterationNumber++;
                    	}
                	}
            	}
        	}
    	}//end all for loops
    	
        
    }

    
    
    
}
