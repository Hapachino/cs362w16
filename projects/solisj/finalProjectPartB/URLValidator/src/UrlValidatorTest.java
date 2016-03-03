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
