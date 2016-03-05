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
    
    
    public void testIsValid()
    {
        for(int i = 0;i<10000;i++)
        {
            
        }
    }
    
    public void testAnyOtherUnitTest()
    {
        
    }
    /**
     * Create set of tests by taking the testUrlXXX arrays and
     * running through all possible permutations of their combinations.
     *
     * @param testObjects Used to create a url.
     */
    
    
}
