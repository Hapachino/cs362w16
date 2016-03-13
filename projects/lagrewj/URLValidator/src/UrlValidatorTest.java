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
		ResultPair[] manualUrls = {
			new ResultPair("http://www.reddit.com/r/osuonlinecs/", true),
			new ResultPair("http://www.reddit.com/osuonlinecs/", true),
			new ResultPair("http://github.com", true),
			new ResultPair("h3tp:/\\something.wlel.wakyyy", false),
			new ResultPair("ftp://127.0.0.1", true),
			new ResultPair("https://///127.0.0.1", false),
			new ResultPair("hppt://www.kpcc.com", false),
			new ResultPair("sftp://student@access.engr.oregon.edu", false),
			new ResultPair("http://www.yahoo.com", true),
			new ResultPair("htt:/\\www.yahoo.com", false),
			new ResultPair("http://www.oregonstate.edu", true),
			new ResultPair("http://www.amazon123.com", true),
			new ResultPair("http:///www.google.com", false),
			new ResultPair("httpz://www.amazon.com", false),
			new ResultPair("http://vww.amazon.com", false),
			new ResultPair("http://www.amazon.notacountry", false),
			new ResultPair("httP://www.cnn.com", true),
			new ResultPair("https://www.codecademy.com/learn", true),
			new ResultPair("http://www.realclearpolitics.com/", true),
			new ResultPair("https://www.google.com/webhp?hl=en", true),
			new ResultPair("ftp://ftp.funet.fi/pub/standards/RFC/rfc959.txt", true),
			new ResultPair("https://piazza.com/class/iip31fywxe72b0", true),
			new ResultPair("https://piazza.com/class/iip31fywxe72b0?cid=135", true),
			new ResultPair("http://www.tutorialspoint.com/execute_python_online.php", true),
			new ResultPair("https://secure.engr.oregonstate.edu:8000/teach.php?type=want_auth", true),
			new ResultPair("https://travel.state.gov/content/passports/en/passports/renew.html", true),
			new ResultPair("https://github.com/amchristi/cs362w16/commit/a75865dcf7d44615a9f61e4d7fc578283d5c74ea#diff-c593563edcbbbb47bab9b4f1d748176e", true),
			new ResultPair("http://www.amazon.co.jp/", true),
			new ResultPair("http://www.visualgo.net/", true),
			new ResultPair("http://www.123.com", true)
	    	};

	   	int manIdx;
	   	boolean e, a;
	   	String expected, actual;

	   	UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   	
	   	System.out.println("\nManual Testing");

	   	for (manIdx = 0; manIdx < manualUrls.length; manIdx++) {
		   
		   // Value in ResultPair
		   e = manualUrls[manIdx].valid;
		   expected = (e) ? "VALID" : "INVALID";
		   
		   // Value returned from isValid()
		   a = urlVal.isValid(manualUrls[manIdx].item);
		   actual = (a) ? "VALID" : "INVALID";
		   
		   	// Test failed
		   	if (!expected.equals(actual)) {
				System.out.println("Testing " + expected + " url: " + manualUrls[manIdx].item);
				System.out.println("- TEST FAILED, expected " + expected + " but returned " + actual);
			   
		   	}
		   	// Test passed
		   	else {
				System.out.println("Testing " + expected + " url: " + manualUrls[manIdx].item);
		   	}
	   	}
   	}
   
   	public void testYourFirstPartition()
   	{
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   // Valid parts
	   String trueScheme = "http://";
	   String trueAuthority = "www.amazon.com";
	   String truePort = ":80";
	   String truePath = "/example";
	   String trueQuery = "?test=passed&result=true";
	   
	   // Parts to test
	   String falseScheme = "1h2t1p://";
	   String emptyScheme = "";
	   
	   // Construct urls
	   String valid = trueScheme + trueAuthority + truePort + truePath + trueQuery;
	   String invalid = falseScheme + trueAuthority + truePort + truePath + trueQuery;
	   String empty = emptyScheme + trueAuthority + truePort + truePath + trueQuery;
	   
	   System.out.println("\nTesting Scheme Partition");
	   
	   // Valid
	   if (urlVal.isValid(valid)) {
		   System.out.println("Testing VALID url: " + valid);
		   
	   }
	   else {
		   System.out.println("Testing VALID url: " + valid);
		   System.out.println("- TEST FAILED, expected VALID but returned INVALID");
	   }
	   
	   // Invalid
	   if (urlVal.isValid(invalid)) {
		   System.out.println("Testing INVALID url: " + invalid);
		   System.out.println("- TEST FAILED, expected INVALID but returned VALID");
		   
	   }
	   else {
		   System.out.println("Testing INVALID url: " + invalid);
	   }
	   
	   // Empty
	   if (urlVal.isValid(empty)) {
		   System.out.println("Testing VALID URL: " + empty);
		   
	   }
	   else {
		   System.out.println("Testing VALID URL: " + empty);
		   System.out.println("- TEST FAILED, expected VALID but returned INVALID");
	   }
   	}
   
   	public void testYourSecondPartition()
   	{
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   // Valid parts
	   String trueScheme = "http://";
	   String trueAuthority = "www.amazon.com";
	   String truePort = ":80";
	   String truePath = "/example";
	   String trueQuery = "?test=passed&result=true";
	   
	   // Parts to test
	   String falseAuthority = "!@#$%^&*(_).com";
	   String emptyAuthority = "";
	   
	   // Construct urls
	   String valid = trueScheme + trueAuthority + truePort + truePath + trueQuery;
	   String invalid = trueScheme + falseAuthority + truePort + truePath + trueQuery;
	   String empty = trueScheme + emptyAuthority + truePort + truePath + trueQuery;	   
	   
	   System.out.println("\nTesting Authority Partition");
	   
	   // Valid
	   if (urlVal.isValid(valid)) {
		   System.out.println("Testing VALID url: " + valid);
		   
	   }
	   else {
		   System.out.println("Testing VALID url: " + valid);
		   System.out.println("- TEST FAILED, expected VALID but returned INVALID");
	   }
	   
	   // Invalid
	   if (urlVal.isValid(invalid)) {
		   System.out.println("Testing INVALID url: " + invalid);
		   System.out.println("- TEST FAILED, expected INVALID but returned VALID");
		   
	   }
	   else {
		   System.out.println("Testing INVALID url: " + invalid);
	   }
	   
	   // Empty (authority is the only part that cannot be empty)
	   if (urlVal.isValid(empty)) {
		   System.out.println("Testing INVALID url: " + empty);
		   System.out.println("- TEST FAILED, expected INVALID but returned VALID");
		   
	   }
	   else {
		   System.out.println("Testing INVALID url: " + empty);
	   }
   	}

    public void testYourThirdPartition()
   	{
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   // Valid parts
	   String trueScheme = "http://";
	   String trueAuthority = "www.amazon.com";
	   String truePort = ":80";
	   String truePath = "/example";
	   String trueQuery = "?test=passed&result=true";
	   
	   // Parts to test
	   String falsePort = ":-100abc000~";
	   String emptyPort = "";
	   
	   // Construct urls
	   String valid = trueScheme + trueAuthority + truePort + truePath + trueQuery;
	   String invalid = trueScheme + trueAuthority + falsePort + truePath + trueQuery;
	   String empty = trueScheme + trueAuthority + emptyPort + truePath + trueQuery;
	   
	   System.out.println("\nTesting Port Partition");
	   
	   // Valid
	   if (urlVal.isValid(valid)) {
		   System.out.println("Testing VALID url: " + valid);
		   
	   }
	   else {
		   System.out.println("Testing VALID url: " + valid);
		   System.out.println("- TEST FAILED, expected VALID but returned INVALID");
	   }
	   
	   // Invalid
	   if (urlVal.isValid(invalid)) {
		   System.out.println("Testing INVALID url: " + invalid);
		   System.out.println("- TEST FAILED, expected INVALID but returned VALID");
		   
	   }
	   else {
		   System.out.println("Testing INVALID url: " + invalid);
	   }
	   
	   // Empty
	   if (urlVal.isValid(empty)) {
		   System.out.println("Testing VALID URL: " + empty);
		   
	   }
	   else {
		   System.out.println("Testing VALID URL: " + empty);
		   System.out.println("- TEST FAILED, expected VALID but returned INVALID");
	   }
   	}

   	public void testYourFourthPartition()
   	{
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   // Valid parts
	   String trueScheme = "http://";
	   String trueAuthority = "www.amazon.com";
	   String truePort = ":80";
	   String truePath = "/example";
	   String trueQuery = "?test=passed&result=true";
	   
	   // Parts to test
	   String falsePath = "/..//...\\";
	   String emptyPath = "";
	   
	   // Construct urls
	   String valid = trueScheme + trueAuthority + truePort + truePath + trueQuery;
	   String invalid = trueScheme + trueAuthority + truePort + falsePath + trueQuery;
	   String empty = trueScheme + trueAuthority + truePort + emptyPath + trueQuery;
	   
	   System.out.println("\nTesting Path Partition");
	   
	   // Valid
	   if (urlVal.isValid(valid)) {
		   System.out.println("Testing VALID url: " + valid);
		   
	   }
	   else {
		   System.out.println("Testing VALID url: " + valid);
		   System.out.println("- TEST FAILED, expected VALID but returned INVALID");
	   }
	   
	   // Invalid
	   if (urlVal.isValid(invalid)) {
		   System.out.println("Testing INVALID url: " + invalid);
		   System.out.println("- TEST FAILED, expected INVALID but returned VALID");
		   
	   }
	   else {
		   System.out.println("Testing INVALID url: " + invalid);
	   }
	   
	   // Empty
	   if (urlVal.isValid(empty)) {
		   System.out.println("Testing VALID URL: " + empty);
		   
	   }
	   else {
		   System.out.println("Testing VALID URL: " + empty);
		   System.out.println("- TEST FAILED, expected VALID but returned INVALID");
	   }
   	}

   	public void testYourFifthPartition()
   	{
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   // Valid parts
	   String trueScheme = "http://";
	   String trueAuthority = "www.amazon.com";
	   String truePort = ":80";
	   String truePath = "/example";
	   String trueQuery = "?test=passed&result=true";
	   
	   // Parts to test
	   String falseQuery = "querystringwithnoquestionmark";
	   String emptyQuery = "";
	   
	   // Construct urls
	   String valid = trueScheme + trueAuthority + truePort + truePath + trueQuery;
	   String invalid = trueScheme + trueAuthority + truePort + truePath + falseQuery;
	   String empty = trueScheme + trueAuthority + truePort + truePath + emptyQuery;
	   
	   System.out.println("\nTesting Query Partition");
	   
	   // Valid
	   if (urlVal.isValid(valid)) {
		   System.out.println("Testing VALID url: " + valid);
		   
	   }
	   else {
		   System.out.println("Testing VALID url: " + valid);
		   System.out.println("- TEST FAILED, expected VALID but returned INVALID");
	   }
	   
	   // Invalid
	   if (urlVal.isValid(invalid)) {
		   System.out.println("Testing INVALID url: " + invalid);
		   System.out.println("- TEST FAILED, expected INVALID but returned VALID");
		   
	   }
	   else {
		   System.out.println("Testing INVALID url: " + invalid);
	   }
	   
	   // Empty
	   if (urlVal.isValid(empty)) {
		   System.out.println("Testing VALID URL: " + empty);
		   
	   }
	   else {
		   System.out.println("Testing VALID URL: " + empty);
		   System.out.println("- TEST FAILED, expected VALID but returned INVALID");
	   }
   	}
   
   	public void testIsValid()
   	{
		int schIdx, hostIdx, portIdx, pathIdx, queryIdx;
		String validUrl;
		UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		ResultPair url;
		
		System.out.println("\nProgramming based testing");
	  
		for (schIdx = 0; schIdx < schemes.length; schIdx++)
		{
			for (hostIdx = 0; hostIdx < hosts.length; hostIdx++)
			{
				for (portIdx = 0; portIdx < ports.length; portIdx++)
				{
					for (pathIdx = 0; pathIdx < paths.length; pathIdx++)
					{
						for (queryIdx = 0; queryIdx < queries.length; queryIdx++)
						{
							url = URLBuilder(schIdx, hostIdx, portIdx, pathIdx, queryIdx);
							validUrl = (url.valid) ? "VALID" : "INVALID"; // ternary operators make life easier

							System.out.println("Testing " + validUrl + " URL: " + url.item);

							if (url.valid) {
								//assertTrue(urlVal.isValid(url.item));
								if (!urlVal.isValid(url.item)) {
									System.out.println("- TEST FAILED, expected VALID but returned INVALID");
								}
							}

							else {
								//assertFalse(urlVal.isValid(url.item));
								if (urlVal.isValid(url.item)) {
									System.out.println("- TEST FAILED, expected INVALID but returned VALID");
								}								
							}
					 	}
				 	}
			 	}
		 	}
		}
   	}
   
   	public void testAnyOtherUnitTest()
   	{
   		// UrlValidator();
   		ResultPair[] otherUrls1 = {
				new ResultPair("http://www.google.com/path/", true),
				new ResultPair("http://www.google.com/path//", false),
				new ResultPair("http://somesite.com/html/top.html", true),
				new ResultPair("http://somesite.com/html/top.html#section_2", true),
				new ResultPair("http://localhost/", false),
				new ResultPair("http://machine/", false)
		};

		// UrlValidator(null, null, UrlValidator.ALLOW_2_SLASHES);
		ResultPair[] otherUrls2 = {
				new ResultPair("http://www.google.com/path/", true),
				new ResultPair("http://www.google.com/path//", true),
				new ResultPair("http://somesite.com/html/top.html", true),
				new ResultPair("http://somesite.com/html/top.html#section_2", true),
				new ResultPair("http://localhost/", false),
				new ResultPair("http://machine/", false)
		};

		// UrlValidator(null, null, UrlValidator.ALLOW_LOCAL_URLS);
		ResultPair[] otherUrls3 = {
				new ResultPair("http://www.google.com/path/", true),
				new ResultPair("http://www.google.com/path//", false),
				new ResultPair("http://somesite.com/html/top.html", true),
				new ResultPair("http://somesite.com/html/top.html#section_2", true),
				new ResultPair("http://localhost/", true),
				new ResultPair("http://machine/", true)
		};

		// UrlValidator(null, null, UrlValidator.NO_FRAGMENTS);
		ResultPair[] otherUrls4 = {
				new ResultPair("http://www.google.com/path/", true),
				new ResultPair("http://www.google.com/path//", false),
				new ResultPair("http://somesite.com/html/top.html", true),
				new ResultPair("http://somesite.com/html/top.html#section_2", false),
				new ResultPair("http://localhost/", false),
				new ResultPair("http://machine/", false)
		};

		int otherIdx;
	   	boolean e, a;
	   	String expected, actual;

	   	UrlValidator urlVal1 = new UrlValidator();
   		UrlValidator urlVal2 = new UrlValidator(null, null, UrlValidator.ALLOW_2_SLASHES);
   		UrlValidator urlVal3 = new UrlValidator(null, null, UrlValidator.ALLOW_LOCAL_URLS);
   		UrlValidator urlVal4 = new UrlValidator(null, null, UrlValidator.NO_FRAGMENTS);
	   	
	   	System.out.println("\nOther Unit Tests");
   		
   		System.out.println("\nDefault schemes: http, https, ftp");
   		for (otherIdx = 0; otherIdx < otherUrls1.length; otherIdx++) {
		   
		   // Value in ResultPair
		   e = otherUrls1[otherIdx].valid;
		   expected = (e) ? "VALID" : "INVALID";
		   
		   // Value returned from isValid()
		   a = urlVal1.isValid(otherUrls1[otherIdx].item);
		   actual = (a) ? "VALID" : "INVALID";
		   
		   	// Test failed
		   	if (!expected.equals(actual)) {
				System.out.println("Testing " + expected + " url: " + otherUrls1[otherIdx].item);
				System.out.println("- TEST FAILED, expected " + expected + " but returned " + actual);
			   
		   	}
		   	// Test passed
		   	else {
				System.out.println("Testing " + expected + " url: " + otherUrls1[otherIdx].item);
		   	}
	   	}
	   	
	   	System.out.println("\nALLOW_2_SLASHES");
	   	for (otherIdx = 0; otherIdx < otherUrls2.length; otherIdx++) {
		   
		   // Value in ResultPair
		   e = otherUrls2[otherIdx].valid;
		   expected = (e) ? "VALID" : "INVALID";
		   
		   // Value returned from isValid()
		   a = urlVal2.isValid(otherUrls2[otherIdx].item);
		   actual = (a) ? "VALID" : "INVALID";
		   
		   	// Test failed
		   	if (!expected.equals(actual)) {
				System.out.println("Testing " + expected + " url: " + otherUrls2[otherIdx].item);
				System.out.println("- TEST FAILED, expected " + expected + " but returned " + actual);
			   
		   	}
		   	// Test passed
		   	else {
				System.out.println("Testing " + expected + " url: " + otherUrls2[otherIdx].item);
		   	}
	   	}

	   	System.out.println("\nALLOW_LOCAL_URLS");
	   	for (otherIdx = 0; otherIdx < otherUrls3.length; otherIdx++) {
		   
		   // Value in ResultPair
		   e = otherUrls3[otherIdx].valid;
		   expected = (e) ? "VALID" : "INVALID";
		   
		   // Value returned from isValid()
		   a = urlVal3.isValid(otherUrls3[otherIdx].item);
		   actual = (a) ? "VALID" : "INVALID";
		   
		   	// Test failed
		   	if (!expected.equals(actual)) {
				System.out.println("Testing " + expected + " url: " + otherUrls3[otherIdx].item);
				System.out.println("- TEST FAILED, expected " + expected + " but returned " + actual);
			   
		   	}
		   	// Test passed
		   	else {
				System.out.println("Testing " + expected + " url: " + otherUrls3[otherIdx].item);
		   	}
	   	}

	   	System.out.println("\nNO_FRAGMENTS");
	   	for (otherIdx = 0; otherIdx < otherUrls4.length; otherIdx++) {
		   
		   // Value in ResultPair
		   e = otherUrls4[otherIdx].valid;
		   expected = (e) ? "VALID" : "INVALID";
		   
		   // Value returned from isValid()
		   a = urlVal4.isValid(otherUrls4[otherIdx].item);
		   actual = (a) ? "VALID" : "INVALID";
		   
		   	// Test failed
		   	if (!expected.equals(actual)) {
				System.out.println("Testing " + expected + " url: " + otherUrls4[otherIdx].item);
				System.out.println("- TEST FAILED, expected " + expected + " but returned " + actual);
			   
		   	}
		   	// Test passed
		   	else {
				System.out.println("Testing " + expected + " url: " + otherUrls4[otherIdx].item);
		   	}
	   	}
	}
	
   /**
    * Create set of tests by taking the testUrlXXX arrays and
    * running through all possible permutations of their combinations.
    *
    * @param testObjects Used to create a url.
    */
   
	ResultPair[] schemes = {
		new ResultPair("http://", true),
		new ResultPair("https://", true),
		new ResultPair("ftp://", true),
		new ResultPair("sftp://", true),
		new ResultPair("http:///", false),
		new ResultPair("foo://", false),
		new ResultPair("bar://", false),
		new ResultPair("1http://", false),
		new ResultPair("h1ttp://", false),
		new ResultPair("http:/", false),
		new ResultPair("http//", false),
		new ResultPair("", true) // this should be true, because the web doesn't necessary penalize you if you don't use a protocol.
	};
   
	ResultPair[] hosts = {
		new ResultPair("127.0.0.1", true),
		new ResultPair("127.0.1", false),
		new ResultPair("255.255.255.255", true),
		new ResultPair("256.256.256.256", false),
		new ResultPair("www.yahoo.com", true),
		new ResultPair("www.amazon.com", true),
		new ResultPair("www.bing.com", true),
		new ResultPair("yahoo", false),
		new ResultPair("amazon", false),
		new ResultPair("bing", false),
		new ResultPair("baidu", false),
		new ResultPair("oregonstate.edu", true),
		new ResultPair("", false)
	};
   
	ResultPair[] ports = {
		new ResultPair(":80", true),
		new ResultPair(":8080", true),
		new ResultPair(":65535", true),
		new ResultPair(":65536", false),
		new ResultPair(":23a", false),
		new ResultPair(":-80", false),
		new ResultPair("", true)
	};
		   
	ResultPair[] paths = {
		new ResultPair("/path", true),
		new ResultPair("/path/", true),
		new ResultPair("/path2/../path1", true),
		new ResultPair("/path2/..path1", false),
		new ResultPair("noslashes", false),
		new ResultPair("/path/name", true),
		new ResultPair("", true)
	};
	
	ResultPair[] queries = {
		new ResultPair("?lvalue=rvalue", true),
		new ResultPair("?lvalue=rvalue&lvalue2=rvalue2", true),
		new ResultPair("?lvalue=rvalue;lvalue2=rvalue2", true),
		new ResultPair("?lvalue=rvalue:lvalue2=rvalue2", false),
		new ResultPair("?=rvalueonly", false),
		new ResultPair("", true)
	};
		   
	public ResultPair URLBuilder(int schIdx, int hostIdx, int portIdx, int pathIdx, int queryIdx)
	{
		boolean urlValidity;
		
		if ((schIdx >= schemes.length) || (hostIdx >= hosts.length) || (portIdx >= ports.length) || ( pathIdx >= paths.length)|| (queryIdx >= queries.length))
		{
			return new ResultPair("Out of range", false);
		}
		
		else 
		{
			String urlString = schemes[schIdx].item + hosts[hostIdx].item + ports[portIdx].item + paths[pathIdx].item + queries[queryIdx].item;
	
			urlValidity = true;

			if(!schemes[schIdx].valid || !hosts[hostIdx].valid || !ports[portIdx].valid || !paths[pathIdx].valid || !queries[queryIdx].valid)
			{
				urlValidity = false;
			}
		
			ResultPair builtURL = new ResultPair(urlString, urlValidity);
	
			return builtURL;
		}
	}
}
