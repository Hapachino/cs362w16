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
        System.out.println("\nRunning manual tests...");
        System.out.println("\nTesting http://www.google.com \nResult: " +  urlVal.isValid("http://www.google.com"));    // test typical URL
        System.out.println("\nTesting http://www.amazon.com \nResult: " +  urlVal.isValid("http://www.amazon.com"));    // default URL given
        System.out.println("\nTesting empty URL \nResult: " +  urlVal.isValid(""));                                     // test empty URL
        System.out.println("\nTesting https://www.google.com \nResult: " +  urlVal.isValid("https://www.google.com"));    // test scheme https://
        System.out.println("\nTesting https://www.maps.google.com \nResult: " +  urlVal.isValid("https://www.maps.google.com"));    //test subdomain
        System.out.println("\nTesting http://www.google.com:8000 \nResult: " +  urlVal.isValid("http://www.google.com:8000"));    //test port
      
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
    		//System.out.print("String: " + testString + "\tExpeected: " + expected + 
    		//		"\tResult: " + result + "\n");
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
    
    public void testYourSecondPartition(){
 	   
 	   //Project Version
 	   
 	   /*******************************
 	    * WE're going to cut this into pieces.
 	    * We're going to instantiate an instance of UrlValidator
 	    * Then we're going to test traditional alphanumeric authorities.
 	    * Then we'll test numeric, dotted decimal IP addresses.
 	    * 
 	    * 
 	    * ********************************/
 	   
 	   int count = 10000;
 	   Random r = new Random();
 	   String scheme[] = { "http:", "ftp:", "smtp:", "mailto:", "file:", 
 			   "news:", "telnet:"};
 	  
 	   String connector[] = {"//" } ;
 	   String terminator[] = {"/", ""};
 	   String domain[] = {".edu", ".gov", ".org", ".com", ".mil"};

 	   String testURL = "";
 	   
 	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
 	   try {
 		   assertTrue(urlVal.isValid("http://www.google.com"));
 		   assertTrue(urlVal.isValid("http://www.google.com/"));
 	   } catch (AssertionError ex) {
 		   System.out.println("Assertions failed.\n");
 		   System.exit(1);
 	   }
 	   
 	   System.out.print("Test Domains\n");
 	   for (int i = 0; i < count; i++)
 	   {
 		   
 		   //let's test a set of good addresses
 		   String host[] = { "google", "ibm", "amazon", "apple","dell", "oracle",
 				   "cisco", "toshiba", "lg", "samsung", "belkin", "microsoft"};
 		   
 		   	testURL = "http://" + host[i % host.length] + ".com";
 		   	boolean expected = true;
 		   	
 		   	boolean result = urlVal.isValid(testURL);
 		   	assertEquals(result, expected);
 	   		if (result == expected) 
 	   		{
 	   			System.out.print(".");
 	   			if ((i % 72) == 0)
 	   				System.out.print("\n");
 	   		}
 	   		else {
 	   			System.out.print("X");
 	   		}
 		   }
 	   
 	   System.out.print("Dotted Decimal IP\n");
 	   	for (int i = 0; i < count; i++)
 	   	{
 	   		
 	   		int octet[] = {0, 0, 0, 0};
 	   		
 	   		for (int j = 0; j < 4; j++)
 	   			octet[j] = r.nextInt(255);
 	   		
 	   		String host = Integer.toString(octet[0]) + "." + 
 	   				Integer.toString(octet[1]) + "." +
 	   				Integer.toString(octet[2]) + "." +
 	   				Integer.toString(octet[3]);
 	   		
 		   	testURL = "http://" + host;
 		   	boolean expected = true;
 		   	
 		   	boolean result = urlVal.isValid(testURL);
 		   	//System.out.print("String: " + testURL + "\tExpected: " + expected +
 		   	//		"\tResult: " + result + "\n");
 	   		assertEquals(expected, result);
 	   		if (result == expected) 
 	   		{
 	   			System.out.print(".");
 	   			if ((i % 72) == 0)
 	   				System.out.print("\n");
 	   		}
 	   		else {
 	   			System.out.print("X");
 	   		}
 	   	}
 		   
 		   //Random authority string
 	   	System.out.print("\nRandom authority String\n");
 	   	for (int i = 0; i < 1000; i++){
 	   		
 	   		String host = "";
 	   		
 	   		for (int j = 0; j < 10; j++)
 	   		{
 	   			//generate and validate random character
 	   			while (true)
 	   			{
 	   				int asciiNumber = r.nextInt(123 - 48) + 48;
 	   				if (j == 0) //make sure that the first character is a letter
 	   				{
 	   					if (((asciiNumber >=65) && (asciiNumber <= 90)) ||
 	   							((asciiNumber >= 97) && (asciiNumber <= 122)))
 	   					{
 	   						host = Character.toString((char) asciiNumber);
 	   						break;
 	   					}
 	   				}
 	   				else if (((asciiNumber >=65) && (asciiNumber <= 90)) ||
 	   							((asciiNumber >= 97) && (asciiNumber <= 122))
 	   							|| ((asciiNumber >= 48) && (asciiNumber <= 57))) 
 	   				 
 	   				{
 	   					host = host + Character.toString((char) asciiNumber);
 	   					break;
 	   				}
 	   			}
 	   		}
 		   	testURL = "http://" + host + ".com";
 		   	boolean expected = true;
 		   	
 		   	boolean result = urlVal.isValid(testURL);
 		   	//System.out.print("String: " + testURL + "\tExpected: " + expected +
 		   	//		"\tResult: " + result + "\n");
 	   		assertEquals(expected, result);
 	   		if (result == expected) 
 	   		{
 	   			System.out.print(".");
 	   			if ((i % 72) == 0)
 	   				System.out.print("\n");
 	   		}
 	   		else {
 	   			System.out.print("X");
 	   		}
 	   		
 	   		/******************************
 	   		 * After we run a basic alphanumeric test of the authority space,
 	   		 * we're going to run a test that tests the authority with different
 	   		 * schemes and connectors
 	   		 * 
 	   		 * We're going to use the same randomized host that we just tested in
 	   		 * this i loop.  And we're going to alternate the connections
 	   		 */
 	   		
 	   		int schemeNo = r.nextInt(scheme.length);
 	   		int connectorNo = r.nextInt(connector.length);
 	   		int terminatorNo = r.nextInt(terminator.length);
 	   		int domainNo = r.nextInt(domain.length);
 	   		
 	   		testURL = scheme[schemeNo];
 	   		testURL = testURL + connector[connectorNo];
 	   		testURL = testURL + host;
 	   		testURL = testURL + domain[domainNo];
 	   		testURL = testURL + terminator[terminatorNo];
 	   
 		   	result = urlVal.isValid(testURL);
 		   	//System.out.print("String: " + testURL + "\tExpected: " + expected +
 		   	//		"\tResult: " + result + "\n");
 	   		assertEquals(expected, result);
 	   		if (result == expected) 
 	   		{
 	   			System.out.print(".");
 	   			if ((i % 72) == 0)
 	   				System.out.print("\n");
 	   		}
 	   		else {
 	   			System.out.print("X");
 	   		}
 		   
 	   }
    
    //Random string length
 	System.out.print("\nRandom string length\n");
 	for (int i = 0; i < 1000; i++){
 		
 		String host = "";
 		
 		for (int j = 0; j < r.nextInt(255 - 11) + 1; j++)
 		{
 			//generate and validate random character
 			while (true)
 			{
 				int asciiNumber = r.nextInt(123 - 48) + 48;
 				if (j == 0) //make sure that the first character is a letter
 				{
 					if (((asciiNumber >=65) && (asciiNumber <= 90)) ||
 							((asciiNumber >= 97) && (asciiNumber <= 122)))
 					{
 						host = Character.toString((char) asciiNumber);
 						break;
 					}
 				}
 				else if (((asciiNumber >=65) && (asciiNumber <= 90)) ||
 							((asciiNumber >= 97) && (asciiNumber <= 122))
 							|| ((asciiNumber >= 48) && (asciiNumber <= 57))) 
 				 
 				{
 					host = host + Character.toString((char) asciiNumber);
 					break;
 				}
 			}
 		}
    	testURL = "http://" + host + ".com";
    	boolean expected = true;
    	
    	boolean result = urlVal.isValid(testURL);
    	//System.out.print("String: " + testURL + "\tExpected: " + expected +
    	//		"\tResult: " + result + "\n");
 		assertEquals(expected, result);
 		if (result == expected) 
 		{
 			System.out.print(".");
 			if ((i % 72) == 0)
 				System.out.print("\n");
 		}
 		else {
 			System.out.print("X");
 		}   
 	}
 	

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
       testIsNull();
       testASCII_PATTERN();
       testUrlMatcher();
       testIsValidQuery();
       testIsValidPath();
       testIsValidFragment();
       
    }
    
    public void testUrlMatcher()
    {
    	
    	/***************************************
    	 * okay, this one's going to be fun.  
    	 * We've got to test this mama-jamma regex string:
    	 * ^(([^:/?#]+):)?(//([^/?#]*))?([^?#]*)(\\?([^#]*))?(#(.*))?
    	 * Parsing this thing is a bear, and I don't know that I can
    	 * spend the time digging into every nook and cranny of this expression.
    	 * 
    	 * So, I'm going to try to start simple.  Just some basic tests, to check
    	 * basic functionality and add to our code coverage.
    	 * 
    	 * I'm going to fuzz this.  Starting with a valid string and injecting 
    	 * different characters into the test string. 
    	 * 
    	 * I'm pretty sure that there's not a bug in here.  But just to be sure,
    	 * I'm going to write this function in the correct version then copy it 
    	 * over here. -waddelto
    	 *********************************************/
    	
    		UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
    		String testString = "http://www.amazon.com";
    		
    		boolean expected = true;
    		
    		boolean result = urlVal.isValid(testString);
    		assertEquals(expected, result);
    		
    		StringBuilder fuzzedString = new StringBuilder(testString);
    		fuzzedString.setCharAt(3, '#');
    		
    		/*********************************
    		 * We could do more work on this fuzzer, modifying different 
    		 * components of the URL.
    		 * 
    		 **************************************/
    		
    		expected = false;
    		result = urlVal.isValid(fuzzedString.toString());
    		assertEquals(expected, result);
    	
    }

    
    public void testASCII_PATTERN()
    {
    	UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
    	String nonASCIIString = "";
    	
    	//we're going to try building some invalid escape characters into a string
    	//java compiler errors on string = "\x01\x02...."
    	//So we're building the string a character at a time.
    	for (int i = 0; i < 5; i++){
    		nonASCIIString = nonASCIIString + "\\";
    		nonASCIIString = nonASCIIString + "x";
    		nonASCIIString = nonASCIIString + "0";
    		nonASCIIString = nonASCIIString + Integer.toString(i);

    	}
    	
    	boolean expected = false;
    	
    	boolean result = urlVal.isValid(nonASCIIString);
    	
    	assertEquals(expected, result);
    	if (result != expected)
    	{
    		System.out.println("\nASCII check failed.");
    	}
    	else
    	{
    		System.out.println("\nASCII check passed.");
    	}
    		
    }
    
    public void testIsNull()
    {
    	UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
    	String nullString = "";
    	
    	boolean expected = false;
    	
    	boolean result = urlVal.isValid(nullString);
    	//System.out.print("String: " + testURL + "\tExpected: " + expected +
    			//"\tResult: " + result + "\n");
 		assertEquals(expected, result);
 		if (result != expected)
 		{
 			System.out.println("\nNull check failed");
 		}
 		else
 		{
 			System.out.println("\nNull check passed");
 		}
 			
    }
    
    public void testIsValidQuery()
    {
    	//testing queries
    	UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
    	String testString = "";
    	
    	ResultPair[] testQuery = {new ResultPair("?action=delete", true),
                new ResultPair("?foo=bar&bar=foo", true),
                new ResultPair("?=foo&bar=foo", false),                      
                new ResultPair("", true)                         //should return true for null queries
    	};
    	
    	System.out.println("\nTesting queries...\n");
    	//Test that http://www.google.com to be used with all test queries is valid
    	System.out.println("First testing that http://www.google.com \nResult: " +  urlVal.isValid("http://www.google.com"));     // test typical URL
    	
    	
    	for (int i = 0; i < testQuery.length; i++)
    	{
    		testString = "http://www.google.com" + testQuery[i].item;
    		
    		System.out.println(testString + " \nExpected: " + testQuery[i].valid);
            System.out.println("Actual: " + urlVal.isValid(testString) + "\n");		
    	}
    	      
    }
    
    public void testIsValidPath()
    {
    	//testing path
    	UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
    	String testString = "";
    	
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
    	
    	System.out.println("\nTesting paths...\n");
    	//Test that http://www.google.com to be used with all test paths is valid
    	System.out.println("First testing that http://www.google.com \nResult: " +  urlVal.isValid("http://www.google.com") + "\n");     // test typical URL
    	
    	for (int i = 0; i < testPath.length; i++)
    	{
    		testString = "http://www.google.com" + testPath[i].item;
    		
    		System.out.println(testString + " \nExpected: " + testPath[i].valid);
            System.out.println("Actual: " + urlVal.isValid(testString) + "\n");		
    	}
    	
    }
    
    public void testIsValidFragment()
    {
    	String testFragmentString = "";
    	
    	ResultPair[] testFragment = {new ResultPair("test", true),
                new ResultPair("1", true),
                new ResultPair("*", true),
                new ResultPair("//", true),
                new ResultPair("http:/", true),
                new ResultPair("http:", true),
                new ResultPair("http/", true),
                new ResultPair(".", true),
                new ResultPair("abc", true),
                new ResultPair("foo", true),
                new ResultPair("", true)};
    	
    	ResultPair[] testNullFragment = {
                new ResultPair(null, true)};
    	
    	System.out.println("\nTesting fragments with default NO_FRAGMENTS option set to off...\n");
    	
    	UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
    	
    	for (int i = 0; i < testFragment.length; i++)
    	{   		
    		testFragmentString = testFragment[i].item;
    		//run isValidFragment
    		boolean result = urlVal.isValidFragment(testFragmentString);
    		
    		System.out.println("\nTesting \"" + testFragment[i].item + "\" \nExpected: " + testFragment[i].valid);
            System.out.println("Actual: " + result + "\n");		
    	}
    	
    	//test null fragment
    	System.out.println("\nTesting \"" + testNullFragment[0].item + "\" \nExpected: " + testNullFragment[0].valid);
        System.out.println("Actual: " + urlVal.isValidFragment(testNullFragment[0].item) + "\n");
    	
    	
    	System.out.println("\nTesting fragments with NO_FRAGMENTS option set to on...\n");
    	
    	UrlValidator urlVal2 = new UrlValidator(null, null, UrlValidator.NO_FRAGMENTS);
    	
    	for (int i = 0; i < testFragment.length; i++)
    	{   		
    		testFragmentString = testFragment[i].item;
    		//run isValidFragment
    		boolean result = urlVal2.isValidFragment(testFragmentString);
    		
    		System.out.println("\nTesting \"" + testFragment[i].item + "\" \nExpected: " + !testFragment[i].valid); //expected value will be false since no fragments are allowed
            System.out.println("Actual: " + result + "\n");		
    	}
    	
    	//test null fragment
    	System.out.println("\nTesting \"" + testNullFragment[0].item + "\" \nExpected: " + testNullFragment[0].valid);
        System.out.println("Actual: " + urlVal2.isValidFragment(testNullFragment[0].item) + "\n");
    		
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
