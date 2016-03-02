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
	   //System.out.println(urlVal.isValid("http://www.amazon.com:65535/example"));
	   //System.out.println(urlVal.isValid("http://255.255.255.255"));
	   //System.out.println(urlVal.isValid("http://256.256.256.256"));
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
		   System.out.println("VALID URL: " + valid + ", RETURNED VALID, TEST PASSED");
		   
	   }
	   else {
		   System.out.println("VALID URL: " + valid + ", RETURNED INVALID, TEST FAILED");
	   }
	   
	   // Invalid
	   if (urlVal.isValid(invalid)) {
		   System.out.println("INVALID URL: " + invalid + ", RETURNED VALID, TEST FAILED");
		   
	   }
	   else {
		   System.out.println("INVALID URL: " + invalid + ", RETURNED INVALID, TEST PASSED");
	   }
	   
	   // Empty
	   if (urlVal.isValid(empty)) {
		   System.out.println("EMPTY PART URL: " + empty + ", RETURNED VALID, TEST PASSED");
		   
	   }
	   else {
		   System.out.println("EMPTY PART URL: " + empty + ", RETURNED INVALID, TEST FAILED");
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
		   System.out.println("VALID URL: " + valid + ", RETURNED VALID, TEST PASSED");
		   
	   }
	   else {
		   System.out.println("VALID URL: " + valid + ", RETURNED INVALID, TEST FAILED");
	   }
	   
	   // Invalid
	   if (urlVal.isValid(invalid)) {
		   System.out.println("INVALID URL: " + invalid + ", RETURNED VALID, TEST FAILED");
		   
	   }
	   else {
		   System.out.println("INVALID URL: " + invalid + ", RETURNED INVALID, TEST PASSED");
	   }
	   
	   // Empty (authority is the only part that cannot be empty)
	   if (urlVal.isValid(empty)) {
		   System.out.println("EMPTY PART URL: " + empty + ", RETURNED VALID, TEST FAILED");
		   
	   }
	   else {
		   System.out.println("EMPTY PART URL: " + empty + ", RETURNED INVALID, TEST PASSED");
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
		int schIdx, hostIdx, portIdx, pathIdx, queryIdx;
		String validUrl;
		UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		ResultPair url;
	  
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
							}

							else {
								//assertFalse(urlVal.isValid(url.item));
							}
					 	}
				 	}
			 	}
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
		   new ResultPair("", true) // this should be true, because the web doesn't necessary penalize you if you don't use a protocol.
   	};
   
   	ResultPair[] hosts = {
		   new ResultPair("127.0.0.1", true),
		   new ResultPair("127.0.1", false),
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