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
 
   
   /*******************
    * This method designed to support testing by running a test of the URL and evaluate the response, 
    * then print only to screen if failed.  Return will be a 0 for success, or 1 for failed test.
    ******************/
   public int runTest(ResultPair url, boolean display, int scheme){
	   String note = "";
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   //Allow for different rule_set usage:
	   if (scheme == 2) 
	   { 
		   urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_2_SLASHES);
		   note = " Option = ALLOW_2_SLASHES";
	   }
	   if (scheme == 3) 
	   { 
		   urlVal = new UrlValidator(null, null, UrlValidator.NO_FRAGMENTS);
		   note = " Option = NO_FRAGMENTS";
	   }
	   if (scheme == 4) 
	   { 
		   urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_LOCAL_URLS);
		   note = " Option = ALLOW_LOCAL_URLS";
	   }
	   	   
	   if(urlVal.isValid(url.item) == url.valid)
	   {
		   return 0;
	   }
	   else
	   {
		   String report = "FAIL: URL='" + url.item + "' Expected='" + url.valid + "' .isValid()='" + !url.valid + "'";
		   if (display) { System.out.println(report + note); }
		   return 1;
	   }  
   }
   
   
   /******************
    * This method will test a set of manual URL tests.  It will include some basic valid URL's and 
    * some edge cases such as null, very long/short urls, and special character URL's.  A variety of
    * combinations of scheme, authority, port, path and query paramaters.
    */
   public void testManualTest()
   {
	   //Generate a set of manual URL's and expected result values.
	   ResultPair[] testURLs = {
			   new ResultPair("http://www.google.com", true),
			   new ResultPair("www.google.com", true),
			   new ResultPair("http://125.125.125.125", true),
			   new ResultPair("www.google.com:50/directory?param=valid", true),
			   new ResultPair("httttp://www.google.com", false),
			   new ResultPair("http://www.google.com:port", false),
			   new ResultPair("", false),
			   new ResultPair("555", false),
			   new ResultPair("\n\0", false),
			   new ResultPair("www.google.com:99999", false),
			   new ResultPair("http://verylongverylongverylongabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz.gov", true),
			   new ResultPair("a.com", true) 
	   };
	   int tests = testURLs.length;
	   
	   //Run each test individually and count # of failed results.
	   int failed = 0;
	   System.out.println("\n=======================================================");	 
	   System.out.println("Running Manual Tests...");
	   System.out.println("-------------------------------------------------------");
	   for(int i = 0; i < tests; i++){
		   failed = failed + runTest(testURLs[i], true, 1);
	   }
	   System.out.println("-------------------------------------------------------");
	   System.out.println("Manual Test Complete.  " + tests + " tests run, " + failed + " tests failed.");
	   System.out.println("=======================================================\n\n");	
   }
   
   
   /******************
    * This method will test the Scheme Partition.  The range of possible (and impossible) Schemes
    * should be examined here, as well as edge and border cases.  Only the Scheme element will be
    * evaluated to ensure that Scheme selections will drive results.
    */
   public void testSchemePartition()
   {
	   //Generate a set of Scheme's to validate Scheme partition 
	   //only 3 allowed by current UrlValidator class http, https, ftp per UrlValidator.java line 179.
	   ResultPair[] testSchemes = {
			   new ResultPair("http://", true),
			   new ResultPair("https://", true),
			   new ResultPair("ftp://", true),
			   new ResultPair("", true),
			   new ResultPair("httttp://", false),
			   new ResultPair("htp://", false),
			   new ResultPair("http", false),
			   new ResultPair("http:://", false),
			   new ResultPair("http:/", false),
			   new ResultPair("http:///", false) 
	   };
	   int tests = testSchemes.length;
	   
	   //Run each test individually and count # of failed results.
	   //Running each test with otherwise valid URL, so only Scheme should drive result.
	   int failed = 0;
	   System.out.println("=======================================================");	 
	   System.out.println("Running Scheme Partition Tests...");	   
	   System.out.println("-------------------------------------------------------");
	   for(int i = 0; i < tests; i++){
		   //Generate new URL with selected Scheme, and test.
		   ResultPair this_test = new ResultPair(testSchemes[i].item + "www.google.com", testSchemes[i].valid);
		   failed = failed + runTest(this_test, true, 1);
	   }
	   System.out.println("-------------------------------------------------------");
	   System.out.println("Scheme Partition Test Complete.  " + tests + " tests run, " + failed + " tests failed.");
	   System.out.println("=======================================================\n\n");
   }
   
   
   /******************
    * This method will test the Authority Partition.  The range of possible (and impossible) Authorities
    * should be examined here, as well as edge and border cases.  Only the Authority element will be
    * evaluated to ensure that Authority selections will drive results.
    */
   public void testAuthoritiesPartition(){
	   //Generate a set of Authorities to validate Authority partition 
	   ResultPair[] testAuthorities = {
			   new ResultPair("www.google.com", true),
			   new ResultPair("google.com", true),
			   new ResultPair("google.net", true),
			   new ResultPair(".net", false),
			   new ResultPair("google.tv", true),
			   new ResultPair("google.c0m", false),
			   new ResultPair("125.125.125.125", true),
			   new ResultPair("0.0.0.0.0", false),
			   new ResultPair("255.255.255.255", true),
			   new ResultPair("256.256.256.256", false),
			   new ResultPair("255.255.255", false),
			   new ResultPair("255", false),
			   new ResultPair("", false)
	   };
	   int tests = testAuthorities.length;
	   
	   //Run each test individually and count # of failed results.
	   //Running each test with otherwise valid URL, so only Authority should drive result.
	   int failed = 0;
	   System.out.println("=======================================================");	 
	   System.out.println("Running Authority Partition Tests...");	   
	   System.out.println("-------------------------------------------------------");
	   for(int i = 0; i < tests; i++){
		   //Generate new URL with selected Authority, and test.
		   ResultPair this_test = new ResultPair("http://" + testAuthorities[i].item, testAuthorities[i].valid);
		   failed = failed + runTest(this_test, true, 1);
	   }
	   System.out.println("-------------------------------------------------------");
	   System.out.println("Authorities Partition Test Complete.  " + tests + " tests run, " + failed + " tests failed.");
	   System.out.println("=======================================================\n\n");
   }
   
   
   /******************
    * This method will test the Port Partition.  The range of possible (and impossible) Ports
    * should be examined here, as well as edge and border cases.  Only the Port element will be
    * evaluated to ensure that Port selections will drive results.
    */
   public void testPortsPartition(){
	   //Generate a set of Ports to validate Port partition 
	   ResultPair[] testPorts = {
			   new ResultPair(":10000", true),
			   new ResultPair(":1", true),
			   new ResultPair(":0", false),
			   new ResultPair(":65535", true),
			   new ResultPair(":65536", false),
			   new ResultPair(":", false),
			   new ResultPair(":port", false),
			   new ResultPair(":256.256", false),
			   new ResultPair(":500port", false),
			   new ResultPair(":999999999999999", false),
			   new ResultPair(":-100", false),
			   new ResultPair(":1", true),
			   new ResultPair(":11", true),
			   new ResultPair(":111", true),
			   new ResultPair(":1111", true),
			   new ResultPair(":11111", true)
	   };
	   int tests = testPorts.length;
	   
	   //Run each test individually and count # of failed results.
	   //Running each test with otherwise valid URL, so only Port should drive result.
	   int failed = 0;
	   System.out.println("=======================================================");	 
	   System.out.println("Running Port Partition Tests...");	   
	   System.out.println("-------------------------------------------------------");
	   for(int i = 0; i < tests; i++){
		   //Generate new URL with selected Port, and test.
		   ResultPair this_test = new ResultPair("http://www.google.com" + testPorts[i].item, testPorts[i].valid);
		   failed = failed + runTest(this_test, true, 1);
	   }
	   System.out.println("-------------------------------------------------------");
	   System.out.println("Ports Partition Test Complete.  " + tests + " tests run, " + failed + " tests failed.");
	   System.out.println("=======================================================\n\n");
   }
   

   /******************
    * This method will test the Paths Partition.  The range of possible (and impossible) Paths
    * should be examined here, as well as edge and border cases.  Only the Path element will be
    * evaluated to ensure that Path selections will drive results.
    */
   public void testPathPartition(){
	   //Generate a set of Paths to validate Path partition 
	   ResultPair[] testPaths = {
			   new ResultPair("/dir", true),
			   new ResultPair("/dir/dir", true),
			   new ResultPair("/dir/index.html", true),
			   new ResultPair("/index.html", true),
			   new ResultPair("//", false),
			   new ResultPair("/", true),
			   new ResultPair("/dir/index.html/dir", false),
			   new ResultPair("", true),
			   new ResultPair("/12345", true),
			   new ResultPair("/~!_", true)
	   };
	   int tests = testPaths.length;
	   
	   //Run each test individually and count # of failed results.
	   //Running each test with otherwise valid URL, so only Path should drive result.
	   int failed = 0;
	   System.out.println("=======================================================");	 
	   System.out.println("Running Path Partition Tests...");	   
	   System.out.println("-------------------------------------------------------");
	   for(int i = 0; i < tests; i++){
		   //Generate new URL with selected Port, and test.
		   ResultPair this_test = new ResultPair("http://www.google.com" + testPaths[i].item, testPaths[i].valid);
		   failed = failed + runTest(this_test, true, 1);
	   }
	   System.out.println("-------------------------------------------------------");
	   System.out.println("Paths Partition Test Complete.  " + tests + " tests run, " + failed + " tests failed.");
	   System.out.println("=======================================================\n\n");
   }
   
   
   /******************
    * This method will test the Queries Partition.  The range of possible (and impossible) Query
    * Parameters should be examined here, as well as edge and border cases.  Only the Query element
    * will be evaluated to ensure that Query selections will drive results.
    */
   public void testQueryPartition(){
	   //Generate a set of Paths to validate Path partition 
	   ResultPair[] testQueries = {
			   new ResultPair("?param=valid", true),
			   new ResultPair("?param=valid&param2=valid", true),
			   new ResultPair("?param=valid&param=valid&param=valid&param=valid&param=valid&param=valid&param=valid&param=valid&param=valid&param=valid", true),
			   new ResultPair("?", true),
			   new ResultPair("?param", true),
			   new ResultPair("??", false),
			   new ResultPair("?param=valid&&", false),
			   new ResultPair("?param=valid?param=valid", false),
			   new ResultPair("", true)
	   };
	   int tests = testQueries.length;
	   
	   //Run each test individually and count # of failed results.
	   //Running each test with otherwise valid URL, so only Query should drive result.
	   int failed = 0;
	   System.out.println("=======================================================");	 
	   System.out.println("Running Query Partition Tests...");	   
	   System.out.println("-------------------------------------------------------");
	   for(int i = 0; i < tests; i++){
		   //Generate new URL with selected Query, and test.
		   ResultPair this_test = new ResultPair("http://www.google.com" + testQueries[i].item, testQueries[i].valid);
		   failed = failed + runTest(this_test, true, 1);
	   }
	   System.out.println("-------------------------------------------------------");
	   System.out.println("Queries Partition Test Complete.  " + tests + " tests run, " + failed + " tests failed.");
	   System.out.println("=======================================================\n\n");
   }
   
   
   /******************
    * This method will test programatically every possible combination of Scheme/Authority/Port/Path/Query
    * identified.  This will attempt to uncover any 2-input - 5-input combination bugs that might not be
    * uncovered by the partition testing above.  Any individual invalid component will cause the expected
    * result of isValid() to return false.
    */
   public void testIsValid()
   {
	   //Define Scheme Array
	   ResultPair[] testSchemes = {
			   new ResultPair("http://", true),
			   new ResultPair("https://", true),
			   new ResultPair("ftp://", true),
			   new ResultPair("", true),
			   new ResultPair("httttp://", false),
			   new ResultPair("htp://", false),
			   new ResultPair("http", false),
			   new ResultPair("http:://", false),
			   new ResultPair("http:/", false),
			   new ResultPair("http:///", false) 
	   };
	   
	   //Define Authorities Array
	   ResultPair[] testAuthorities = {
			   new ResultPair("www.google.com", true),
			   new ResultPair("google.com", true),
			   new ResultPair("google.net", true),
			   new ResultPair(".net", false),
			   new ResultPair("google.tv", true),
			   new ResultPair("google.c0m", false),
			   new ResultPair("125.125.125.125", true),
			   new ResultPair("0.0.0.0.0", false),
			   new ResultPair("255.255.255.255", true),
			   new ResultPair("256.256.256.256", false),
			   new ResultPair("255.255.255", false),
			   new ResultPair("255", false),
			   new ResultPair("", false)
	   };
	   
	   //Define Ports Array
	   ResultPair[] testPorts = {
			   new ResultPair(":10000", true),
			   new ResultPair(":1", true),
			   new ResultPair(":0", false),
			   new ResultPair(":65535", true),
			   new ResultPair(":65536", false),
			   new ResultPair(":", false),
			   new ResultPair(":port", false),
			   new ResultPair(":256.256", false),
			   new ResultPair(":500port", false),
			   new ResultPair(":999999999999999", false),
			   new ResultPair(":-100", false),
			   new ResultPair(":1", true),
			   new ResultPair(":11", true),
			   new ResultPair(":111", true),
			   new ResultPair(":1111", true),
			   new ResultPair(":11111", true)
	   };
	   
	   //Define Paths Array
	   ResultPair[] testPaths = {
			   new ResultPair("/dir", true),
			   new ResultPair("/dir/dir", true),
			   new ResultPair("/dir/index.html", true),
			   new ResultPair("/index.html", true),
			   new ResultPair("//", false),
			   new ResultPair("/", true),
			   new ResultPair("/dir/index.html/dir", false),
			   new ResultPair("", true),
			   new ResultPair("/12345", true),
			   new ResultPair("/~!_", true)
	   };
	   
	   //Define Queries Array
	   ResultPair[] testQueries = {
			   new ResultPair("?param=valid", true),
			   new ResultPair("?param=valid&param2=valid", true),
			   new ResultPair("?param=valid&param=valid&param=valid&param=valid&param=valid&param=valid&param=valid&param=valid&param=valid&param=valid", true),
			   new ResultPair("?", true),
			   new ResultPair("?param", true),
			   new ResultPair("??", false),
			   new ResultPair("?param=valid&&", false),
			   new ResultPair("?param=valid?param=valid", false),
			   new ResultPair("", true)
	   };
	   
	   //Generate every possible combination of all 5 partitions.  For each all individual
	   //partition validity will affect expected result.  Any invalid partition, expected will also
	   //be false.
	   int failed = 0;
	   int tests = 0;
	   boolean show = true;
	   System.out.println("=======================================================");	 
	   System.out.println("Running Programatic Incremental Tests (only sample of failures displayed)...");	   
	   System.out.println("-------------------------------------------------------");
	   for (int a = 0; a < testSchemes.length; a++){
		   for (int b = 0; b < testAuthorities.length; b++){
			   for (int c = 0; c < testPorts.length; c++){
				   for (int d = 0; d < testPaths.length; d++){
					   for (int e = 0; e < testQueries.length; e++){
						   //Generate new URL with combined partitions, and test.
						   String url = testSchemes[a].item + testAuthorities[b].item + testPorts[c].item + testPaths[d].item + testQueries[e].item;
						   boolean exp = testSchemes[a].valid && testAuthorities[b].valid && testPorts[c].valid && testPaths[d].valid && testQueries[e].valid;
						   ResultPair this_test = new ResultPair(url, exp);
						   
						   //Added to limit # of failed tests printed to screen.  Sampling at 1/1000.
						   show = ((tests % 1000) == 0) ? true : false;
						   
						   failed = failed + runTest(this_test, show, 1);
						   tests++;
					   }
				   }
			   }
		   }
	   }
	   System.out.println("-------------------------------------------------------");
	   System.out.println("Programatic Incremental Test Complete.  " + tests + " tests run, " + failed + " tests failed.");
	   System.out.println("=======================================================\n\n");
   }
   
   
   /******************
    * We should perhaps consider putting in some simple bug specific testing here.
    * 1 for each of our identified bugs.  They will all fail of course, but would 
    * be inline with the course material and 'fill out' our Project Submission.
    * 
    * We should also consider some basic tests for the two other option sets,
    * 2 Slashes, Fragments, and Local URL's.
    *****************/
   public void testAnyOtherUnitTest()
   {
	   int failed = 0;
	   int tests = 0;
	   ResultPair test;
	   System.out.println("=======================================================");	 
	   System.out.println("Running Options Tests...");	   
	   System.out.println("-------------------------------------------------------");
	   //Run a few standard tests of option Allow 2 Slashes.
	   test = new ResultPair("http://www.google.com/directory//file.txt", true);
	   failed = failed + runTest(test, true, 2);
	   tests++;
	   test = new ResultPair("http://www.google.com/directory///file.txt", false);
	   failed = failed + runTest(test, true, 2);
	   tests++;
	   test = new ResultPair("http://www.google.com/directory//directory2//file.txt", true);
	   failed = failed + runTest(test, true, 2);
	   tests++;
	   //Run a few standard tests of option No Fragments.
	   test = new ResultPair("http://www.google.com/index.html#frag", false);
	   failed = failed + runTest(test, true, 3);
	   tests++;
	   test = new ResultPair("http://www.google.com/index.html##frag", false);
	   failed = failed + runTest(test, true, 3);
	   tests++;
	   test = new ResultPair("http://www.google.com/index.html", true);
	   failed = failed + runTest(test, true, 3);
	   tests++;
	   //Run a few standard tests of option Local Hosts Allowed.
	   test = new ResultPair("http://10.0.0.5", true);
	   failed = failed + runTest(test, true, 4);
	   tests++;
	   test = new ResultPair("http://localhost", true);
	   failed = failed + runTest(test, true, 4);
	   tests++;
	   test = new ResultPair("http://10.0.0.5/index.html", true);
	   failed = failed + runTest(test, true, 4);
	   tests++;
	   test = new ResultPair("http://localhost/index.html", true);
	   failed = failed + runTest(test, true, 4);
	   tests++;
	   System.out.println("-------------------------------------------------------");
	   System.out.println("Options Test Complete.  " + tests + " tests run, " + failed + " tests failed.");
	   System.out.println("=======================================================\n\n");
	   
	   
	   failed = 0;
	   tests = 0;
	   System.out.println("=======================================================");	 
	   System.out.println("Running Bug ID#001 Tests (IP > 256)...");	   
	   System.out.println("-------------------------------------------------------");
	   test = new ResultPair("http://255.255.255.255", true);
	   failed = failed + runTest(test, true, 1);
	   tests++;
	   test = new ResultPair("http://255.255.255.256", false);
	   failed = failed + runTest(test, true, 1);
	   tests++;
	   test = new ResultPair("http://255.255.256.255", false);
	   failed = failed + runTest(test, true, 1);
	   tests++;
	   test = new ResultPair("http://255.256.255.255", false);
	   failed = failed + runTest(test, true, 1);
	   tests++;
	   test = new ResultPair("http://256.255.255.255", false);
	   failed = failed + runTest(test, true, 1);
	   tests++;
	   System.out.println("-------------------------------------------------------");
	   System.out.println("Bug ID#001 Test Complete.  " + tests + " tests run, " + failed + " tests failed.");
	   System.out.println("=======================================================\n\n");
	   
	   
	   failed = 0;
	   tests = 0;
	   System.out.println("=======================================================");	 
	   System.out.println("Running Bug ID#002 Tests (query params trigger false)...");	   
	   System.out.println("-------------------------------------------------------");
	   test = new ResultPair("http://www.google.com", true);
	   failed = failed + runTest(test, true, 1);
	   tests++;
	   test = new ResultPair("http://www.google.com?param=valid", true);
	   failed = failed + runTest(test, true, 1);
	   tests++;
	   test = new ResultPair("http://www.google.com?param=valid&param2=valid", true);
	   failed = failed + runTest(test, true, 1);
	   tests++;
	   test = new ResultPair("http://www.google.com?", true);
	   failed = failed + runTest(test, true, 1);
	   tests++;
	   test = new ResultPair("http://www.google.com?param=valid&&===", false);
	   failed = failed + runTest(test, true, 1);
	   tests++;
	   System.out.println("-------------------------------------------------------");
	   System.out.println("Bug ID#002 Test Complete.  " + tests + " tests run, " + failed + " tests failed.");
	   System.out.println("=======================================================\n\n");
	   
	   
	   failed = 0;
	   tests = 0;
	   System.out.println("=======================================================");	 
	   System.out.println("Running Bug ID#003 Tests (4+ digit ports return false)...");	   
	   System.out.println("-------------------------------------------------------");
	   test = new ResultPair("http://www.google.com:1", true);
	   failed = failed + runTest(test, true, 1);
	   tests++;
	   test = new ResultPair("http://www.google.com:11", true);
	   failed = failed + runTest(test, true, 1);
	   tests++;
	   test = new ResultPair("http://www.google.com:111", true);
	   failed = failed + runTest(test, true, 1);
	   tests++;
	   test = new ResultPair("http://www.google.com:1111", true);
	   failed = failed + runTest(test, true, 1);
	   tests++;
	   test = new ResultPair("http://www.google.com:11111", true);
	   failed = failed + runTest(test, true, 1);
	   tests++;
	   test = new ResultPair("http://www.google.com:111111", false);
	   failed = failed + runTest(test, true, 1);
	   tests++;
	   test = new ResultPair("http://www.google.com:65535", true);
	   failed = failed + runTest(test, true, 1);
	   tests++;
	   test = new ResultPair("http://www.google.com:65536", false);
	   failed = failed + runTest(test, true, 1);
	   tests++;
	   System.out.println("-------------------------------------------------------");
	   System.out.println("Bug ID#003 Test Complete.  " + tests + " tests run, " + failed + " tests failed.");
	   System.out.println("=======================================================\n\n");
   }
   /**
    * Create set of tests by taking the testUrlXXX arrays and
    * running through all possible permutations of their combinations.
    *
    * @param testObjects Used to create a url.
    */
   

}
