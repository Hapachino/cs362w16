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

/*
What is the failure?
How did you find it?
What is the cause of that failure? Explain what part of code is causing it?
You can use any methodology that your learn during the class to test it. To stay 
consistent let us do it this way.

First just do manual testing. Call the valid method of URLValidator with different 
possible valid/invalid inputs and see if you find a failure. (2 points)

Second, come up with good input partitioning. Try to provide a varying set of 
inputs that partition the overall input set well. Did you find any failures? 
You can call valid method once or more for each partition. (3 points)

Third, do programming based testing. Write few unit test cases. You can have 
some sort of loop in your unit test and test different url with each instance 
of loop. Something very similar to testIsValid() but your own logic and idea. 
Even a single test will be sufficient if you write it like testIsValid() method. 
Did you find any failures? Submit your test files and test cases as part of your
 work under your onid/URLValidator folder.   (5 points)

When you find out any failure, debug using Eclipse debugger and try to localize 
its cause.    Provide at what line/lines in what file the failure manifested 
itself. Did you use any of Agan’s principle in debugging URLValidator?  (5 points)

Provide a report called URLValidator.pdf/URLValidator.txt (5 points). 
You need to provide following details in the report. Clearly mention 
your methodology of testing. For manual testing, provide some of your 
(not all) urls. 

For partitioning, mention your partitions with reasons. 
For unit tests/random tests, submit your unit tests using svn under 
URLValidator folder. In report files mention the name of your tests. 
Also mention, how did you work in the team? How did you divide your work? 
How did you collaborate? 

Write bug report for each of the bugs you found. 
Bug report should follow all the standard bug reporting principle, 
Use apache commons validator issue tracking system issues as standard to 
write bug report. Please mention in the bug report, file name and line number 
where bug manifested itself. Provide your debugging details for each bugs. 
You don't need to report bugs using svn, just dump your bug report in the 
URLValidator.pdf/.txt file. 
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
	   System.out.println(urlVal.isValid("http://amaz.com:10000"));
	   
	   
   }
   
   
   public void testYourFirstPartition()
   {
  	   //test valid full url inputs
  	   System.out.println("Testing first partition: valid full url inputs");
  	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
  	   System.out.println(urlVal.isValid("http://google.com"));
  	   System.out.println(urlVal.isValid("http://go.com:80"));
  	   System.out.println(urlVal.isValid("http://255.com"));
  	   System.out.println(urlVal.isValid("http://yahoo.com"));
   }
     
   public void testYourSecondPartition(){
	   //test invalid full url inputs
	   System.out.println("Testing second partition: invalid full url inputs");
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   System.out.println(urlVal.isValid("http:/google.com"));
	   System.out.println(urlVal.isValid("http://google/com"));
	   System.out.println(urlVal.isValid("http://google.bad"));
	   System.out.println(urlVal.isValid("://go.com:80"));
	   System.out.println(urlVal.isValid("http://go..com:80"));
	   System.out.println(urlVal.isValid("http://go.com:-1"));
	   System.out.println(urlVal.isValid("htttp://255.com"));
	   System.out.println(urlVal.isValid("http://255/com"));
	   System.out.println(urlVal.isValid("http://255.ccc"));
	   System.out.println(urlVal.isValid("yahoo..com"));
	   System.out.println(urlVal.isValid("http:yahoo.abc"));
   }
 
   public void testYourThirdPartition(){
	   System.out.println("Testing third partition: (partially) empty url inputs");
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   System.out.println(urlVal.isValid("http://..com"));
	   System.out.println(urlVal.isValid("google.com"));
	   System.out.println(urlVal.isValid("http://www.google"));
	   System.out.println(urlVal.isValid("go.com:80"));
	   System.out.println(urlVal.isValid("http://go"));
	   System.out.println(urlVal.isValid("255.com"));
	   System.out.println(urlVal.isValid("http://255"));
	   System.out.println(urlVal.isValid("yahoo.com"));
	   System.out.println(urlVal.isValid("http://www.yahoo"));
   }
   
 
   
   /**
    * Create set of tests by taking the testUrlXXX arrays and
    * running through all possible permutations of their combinations.
    *
    * @param testObjects Used to create a url.
    */
   
   //Input for testUrlQuery
   ResultPair[] testUrlQuery = {
	//throws error
	new ResultPair("?action=view", true),
	//throws error
           new ResultPair("?action=edit&mode=up", true),
           new ResultPair("?action=edit/mode=up", false),
           new ResultPair("??==?", false),
           new ResultPair("", true)
   };
   
   public void testUrlQuery()
   {
	   UrlValidator urlVal = new UrlValidator();
	   String partUrl = "https://www.google.com/path";
	   assertTrue(urlVal.isValid(partUrl));
	   String testUrl;
	   	   
	   //Loop through and try different options for testUrlQuery
	   for(int i = 0;i<testUrlQuery.length;i++)
	   {
		   //Put together URL for test
		   testUrl = partUrl + testUrlQuery[i].item;
		   System.out.println(testUrl);
		   
		   //Output success or failure
		   if(urlVal.isValid(testUrl) == testUrlQuery[i].valid){
			   System.out.println("Test works as expected");	   
		   }else {
		    	   System.out.println("ERROR: Test does not work as expected");
		    }
	   }
   }
   
   //Input for testPath
   ResultPair[] testPath = {
		   new ResultPair("/test1", true),
           new ResultPair("/t123", true),
           new ResultPair("/$23", true),
           new ResultPair("/..", false),
           new ResultPair("/../", false),
           new ResultPair("/test../", false),
           new ResultPair("/../../", false),
           new ResultPair("/test1/", true),
           new ResultPair("", true),
           new ResultPair("/test1/file", true),
           new ResultPair("/..//file", false),
           new ResultPair("/test1//file", false)
   };
   
   public void testUrlPath()
   {
	   UrlValidator urlVal = new UrlValidator();
	   String partUrl = "http://www.amazon.com";
	   String partQuery = "";
	   //System.out.println(partUrl + partQuery);
	   assertTrue(urlVal.isValid(partUrl + partQuery));
	   String testUrl;
	   	   
	   //Loop through and try different options for testPath
	   for(int i = 0;i<testPath.length;i++)
	   {
		   //Put together URL for test
		   testUrl = partUrl + testPath[i].item + partQuery;
		   System.out.println(testUrl);
		   
		   //Output success or failure
		   if(urlVal.isValid(testUrl) == testPath[i].valid){
			   System.out.println("Test works as expected");	   
		   }else {
		       System.out.println("ERROR: Test does not work as expected");
		    }
	   }
   }

   //Input for testUrlAuthority
   ResultPair[] testUrlAuthority = {
		   new ResultPair("www.google.com", true),
           new ResultPair("go.com", true),
           new ResultPair("go.au", true),
           new ResultPair("0.0.0.0", true),
           new ResultPair("255.255.255.255", true),
	
	//appears to be bug
           new ResultPair("256.256.256.256", false),
           new ResultPair("255.com", true),
           new ResultPair("1.2.3.4.5", false),
           new ResultPair("1.2.3.4.", false),
           new ResultPair("1.2.3", false),
           new ResultPair(".1.2.3.4", false),
           new ResultPair("go.a", false),
           new ResultPair("go.a1a", false),
           new ResultPair("go.cc", true),
           new ResultPair("go.1aa", false),
           new ResultPair("aaa.", false),
           new ResultPair(".aaa", false),
           new ResultPair("aaa", false),
           new ResultPair("", false)   
   };

   public void testUrlAuthority()
   {
	   UrlValidator urlVal = new UrlValidator();
	   String partUrl = "http://";
	   String goodAuthority = "www.google.com";
	   String partEnd = ":30/test";
	   System.out.println(partUrl + goodAuthority + partEnd);
	   assertTrue(urlVal.isValid(partUrl + goodAuthority + partEnd));
	   String testUrl;
	   	   
	   //Loop through and try different options for testPath
	   for(int i = 0;i<testUrlAuthority.length;i++)
	   {
		   //Put together URL for test
		   testUrl = partUrl + testUrlAuthority[i].item + partEnd;
		   System.out.println(testUrl);
		   
		   //Output success or failure
		   if(urlVal.isValid(testUrl) == testUrlAuthority[i].valid){
			   System.out.println("Test works as expected");	   
		   }else {
		       System.out.println("ERROR: Test does not work as expected");
		    }
	   }
   }
}
