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
	   boolean result = urlVal.isValid("http://www.amazon.com");
	   System.out.println("testManualTest() = " + result); 
   }
   
   
   public void testYourFirstPartition() //test valid and invalid schemes
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   String baseURL = "www.google.com";
	   String testURL = "http://" + baseURL;
	   boolean result = urlVal.isValid(testURL);
	   
	   if (result) {
		   for (int i = 0; i < testSchemes.length; i++) {
			   testURL = testSchemes[i].item + baseURL;
			   result = urlVal.isValid(testURL);
			   if (result == testSchemes[i].valid) {
				   System.out.println("Passed scheme test " + (i+1) + ". The URL scheme of \"" + testSchemes[i].item + "\" was " + result + " as expected.");
			   } else {
				   System.out.println("Failed scheme test " + (i+1) + ". The URL scheme of \"" + testSchemes[i].item + "\" was " + result + " when " + testSchemes[i].valid + " was expected.");
			   }
		   }
	   } else {
		   System.out.println("The base URL of \"" + testURL + "\" was invalid so scheme testing was ignored.");
	   }
   }
   
   public void testYourSecondPartition() //test valid and invalid domains. Should allow hostname and localhost
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_LOCAL_URLS);
	   String baseURL = "http://";
	   String testURL = baseURL + "www.google.com";
	   boolean result = urlVal.isValid(testURL);
	   if (result) {
		   for (int i = 0; i < testDomains.length; i++) {
			   testURL = baseURL + testDomains[i].item;
			   result = urlVal.isValid(testURL);
			   if (result == testDomains[i].valid) {
				   System.out.println("Passed domain test " + (i+1) + ". The URL of \"" + testURL + "\" was " + result + " as expected.");
			   } else {
				   System.out.println("Failed domain test " + (i+1) + ". The URL of \"" + testURL + "\" was " + result + " when " + testDomains[i].valid + " was expected.");
			   }
		   }
	   } else {
		   System.out.println("The base URL of \"" + testURL + "\" was invalid so domain testing was ignored.");
	   }
   }
   
   public void testYourThirdPartition() //valid and invalid ports
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   String baseURL = "http://www.google.com";
	   String testURL = baseURL + ":80";
	   boolean result = urlVal.isValid(testURL);
	   if (result) {
		   for (int i = 0; i < testPorts.length; i++) {
			   testURL = baseURL + testPorts[i].item;
			   result = urlVal.isValid(testURL);
			   if (result == testPorts[i].valid) {
				   System.out.println("Passed port test " + (i+1) + ". The URL of \"" + testURL + "\" was " + result + " as expected.");
			   } else {
				   System.out.println("Failed port test " + (i+1) + ". The URL of \"" + testURL + "\" was " + result + " when " + testPorts[i].valid + " was expected.");
			   }
		   }
	   } else {
		   System.out.println("The base URL of \"" + testURL + "\" was invalid so port testing was ignored.");
	   }
   }
   
   public void testYourFourthPartition(){ //valid and invalid paths
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   String baseURL = "http://www.google.com";
	   String testURL = baseURL + "/path";
	   boolean result = urlVal.isValid(testURL);
	   if (result) {
		   for (int i = 0; i < testPaths.length; i++) {
			   testURL = baseURL + testPaths[i].item;
			   result = urlVal.isValid(testURL);
			   if (result == testPaths[i].valid) {
				   System.out.println("Passed path test " + (i+1) + ". The URL of \"" + testURL + "\" was " + result + " as expected.");
			   } else {
				   System.out.println("Failed path test " + (i+1) + ". The URL of \"" + testURL + "\" was " + result + " when " + testPaths[i].valid + " was expected.");
			   }
		   }
	   } else {
		   System.out.println("The base URL of \"" + testURL + "\" was invalid so path testing was ignored.");
	   }
   }
   
   public void testYourFifthPartition(){ //valid and invalid querys
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   String baseURL = "http://www.google.com";
	   String testURL = baseURL + "?query=answer";
	   boolean result = urlVal.isValid(testURL);
	   if (result) {
		   for (int i = 0; i < testQueries.length; i++) {
			   testURL = baseURL + testQueries[i].item;
			   result = urlVal.isValid(testURL);
			   if (result == testQueries[i].valid) {
				   System.out.println("Passed query test " + (i+1) + ". The URL of \"" + testURL + "\" was " + result + " as expected.");
			   } else {
				   System.out.println("Failed query test " + (i+1) + ". The URL of \"" + testURL + "\" was " + result + " when " + testQueries[i].valid + " was expected.");
			   }
		   }
	   } else {
		   System.out.println("The base URL of \"" + testURL + "\" was invalid so query testing was ignored.");
	   }
   }
   
   public void testYourSixthPartition(){ //valid and invalid fragments
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   String baseURL = "http://www.google.com";
	   String testURL = baseURL + "#framgent";
	   boolean result = urlVal.isValid(testURL);
	   if (result) {
		   for (int i = 0; i < testFragments.length; i++) {
			   testURL = baseURL + testFragments[i].item;
			   result = urlVal.isValid(testURL);
			   if (result == testFragments[i].valid) {
				   System.out.println("Passed fragment test " + (i+1) + ". The URL of \"" + testURL + "\" was " + result + " as expected.");
			   } else {
				   System.out.println("Failed fragment test " + (i+1) + ". The URL of \"" + testURL + "\" was " + result + " when " + testFragments[i].valid + " was expected.");
			   }
		   }
	   } else {
		   System.out.println("The base URL of \"" + testURL + "\" was invalid so fragment testing was ignored.");
	   }
   }      
   
   public void testMyIsValid() {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   String testURL = "";
	   boolean resultExpected;
	   boolean result;
	   for (int i = 0; i < testSchemes.length; i++) {
		   for (int j = 0; j < testDomains.length; j++) {
			   for (int k = 0; k < testPorts.length; k++) {
				   for (int l = 0; l < testPaths.length; l++) {
					   for (int m = 0; m < testQueries.length; m++) {
						   for (int n = 0; n < testFragments.length; n++) {
							   testURL = testSchemes[i].item + testDomains[j].item + testPorts[k].item + testPaths[l].item + testQueries[m].item + testFragments[n].item;
							   resultExpected = testSchemes[i].valid && testDomains[j].valid && testPorts[k].valid && testPaths[l].valid && testQueries[m].valid && testFragments[n].valid;
							   result = urlVal.isValid(testURL);
							   if (result == resultExpected){
								   System.out.println("Passed: The URL \"" + testURL + "\" was correctly identified by isValid() as " + result + ".");
							   } else {
								   System.out.println("Failed: The URL \"" + testURL + "\" was incorrectly identified by isValid() as " + result + ".");
							   }
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
   
   //create arrays of partitioned url components (both valid and invalid) to create and test many combinations of valid and invalid url strings
   static ResultPair[] testSchemes = {
	   new ResultPair("http://", true),
	   new ResultPair("https://", true),
	   new ResultPair("ftp://", true),
	   new ResultPair("sftp://", false),
	   new ResultPair("svn://", false),
	   new ResultPair("", false),
	   new ResultPair("http:/", false),
	   new ResultPair("http5://", false),
	   new ResultPair("60", false),
	   new ResultPair("ht®p://", false),
	   new ResultPair("://", false)
   };
   
   static ResultPair[] testDomains = {
	   new ResultPair("www.google.com", true),
	   new ResultPair("www.google", false),
	   new ResultPair("go.com", true),
	   new ResultPair("255.255.255.255", true),
	   new ResultPair("0.0.0.0", true),
	   new ResultPair("www.google.de", true),
	   new ResultPair("www.google.mz", true),
	   new ResultPair("www.google.pp", false),
	   new ResultPair("www.google.nb", false),
	   new ResultPair("", false),
	   new ResultPair("1.2.1.2", false),
	   new ResultPair("256.256.256.256", false),
	   new ResultPair("0.com", true),
	   new ResultPair("go®.com", false),
	   new ResultPair("localhost", true),
	   new ResultPair("hostname", true)
   };
   
   static ResultPair[] testPorts = { //0-1023 well-known; 1024-49151 registered; 49152-65535 dynamic/private ports
	   new ResultPair("", true),
	   new ResultPair(":0", true),
	   new ResultPair(":80", true),
	   new ResultPair(":1023", true),
	   new ResultPair(":1024", true),
	   new ResultPair(":33333", true),
	   new ResultPair(":49151", true),
	   new ResultPair(":49152", true),
	   new ResultPair(":55555", true),
	   new ResultPair(":65535", true),
	   new ResultPair(":65536", false),
	   new ResultPair(":100000", false),
	   new ResultPair(":80a", false),
	   new ResultPair(":-1", false),
	   new ResultPair(":8a0", false),
	   new ResultPair(":®", false)
   };
   
   static ResultPair[] testPaths = {
	   new ResultPair("/path", true),
	   new ResultPair("/path/", true),
	   new ResultPair("/path/path", true),
	   new ResultPair("/path/path/", true),
	   new ResultPair("/$path", true),
	   new ResultPair("/#path", false),
	   new ResultPair("", true),
	   new ResultPair("/$/path/", true),
	   new ResultPair("/../path1", false),
	   new ResultPair("/path®", false)
   };
   
   static ResultPair[] testQueries = {
	   new ResultPair("", true),
	   new ResultPair("?day=3&month=1", true),
	   new ResultPair("?action=send", true),
	   new ResultPair("?:", false),
	   new ResultPair("?answer=®", false)
   };
   
   static ResultPair[] testFragments = {
	   new ResultPair("", true),
	   new ResultPair("#apog2h5u6uh4u3672", true),
	   new ResultPair("#®aogh", false)
   };
}
