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
import java.util.*;





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
	   System.out.println(urlVal.isValid("http://www.amazon.com"));
	   
	   
   }
   
   //create valid and invalid components for partitioning input by url component
   //0 for valid input, 1 for invalid.
   public static String createPartition(int schemeN, int authN, int portN, int pathN, int queryN)
   {
	   //scheme inputs
	   List<String> scheme = new ArrayList<String>();
	   scheme.add("http://");
	   scheme.add("http:");
	   //authority inputs
	   List<String> auth = new ArrayList<String>();
	   auth.add("www.google.com");
	   auth.add("go.a:");
	   //port inputs
	   List<String> port = new ArrayList<String>();
	   port.add(":80");
	   port.add(":65a");
	   //path inputs
	   List<String> path = new ArrayList<String>();
	   path.add("/t1/");
	   path.add("/..");
	   //query inputs
	   List<String> query = new ArrayList<String>();
	   query.add("?action=view");
	   query.add("?action=)view");
	   
	   String urlParts = scheme.get(schemeN) + auth.get(authN) + port.get(portN) + path.get(pathN) + query.get(queryN);
	   
	   return urlParts;
   }
	   
   
   //partitioning input by url component
   public void testPartitions()
   {
		System.out.println("----------Testing input partitions---------- \n");
		
		UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		boolean failFlag;
		
		//invalid scheme
		String testScheme = createPartition(1, 0, 0, 0, 0);
		failFlag = urlVal.isValid(testScheme);
		if(failFlag)
			System.out.println("FAILED - Invalid scheme: " + testScheme + " passed.\n");
		else
			System.out.println("PASSED - Invalid scheme: " + testScheme + " failed.\n");
		
		//invalid authority
		String testAuth = createPartition(0, 1, 0, 0, 0);
		failFlag = urlVal.isValid(testAuth);
		if(failFlag)
			System.out.println("FAILED - Invalid authority: " + testAuth + " passed.\n");
		else
			System.out.println("PASSED - Invalid authority: " + testAuth + " failed.\n");
		
		//invalid port
		String testPort = createPartition(0, 0, 1, 0, 0);
		failFlag = urlVal.isValid(testPort);
		if(failFlag)
			System.out.println("FAILED - Invalid port: " + testPort + " passed.\n");
		else
			System.out.println("PASSED - Invalid port: " + testPort + " failed.\n");
		
		//invalid path
		String testPath = createPartition(0, 0, 0, 1, 0);
		failFlag = urlVal.isValid(testPath);
		if(failFlag)
			System.out.println("FAILED - Invalid path: " + testPath + " passed.\n");
		else
			System.out.println("PASSED - Invalid path: " + testPath + " failed.\n");
		
		//invalid query
		String testQuery = createPartition(0, 0, 0, 0, 1);
		failFlag = urlVal.isValid(testQuery);
		if(failFlag)
			System.out.println("FAILED - Invalid query: " + testQuery + " passed.\n");
		else
			System.out.println("PASSED - Invalid query: " + testQuery + " failed.\n");
		
		System.out.println("----------Testing of input partitions complete---------- \n");
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
