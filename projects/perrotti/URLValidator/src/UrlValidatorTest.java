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
	   //Test Allow All Schemes
	   //This is one way we could approach testing manually
	   UrlValidator urlVal = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
	   System.out.println("Schema Test - Allow All Schemes");
	   assertTrue(urlVal.isValid("http://www.amazon.com"));
	   assertTrue(urlVal.isValid("https://www.google.com"));
	   assertTrue(urlVal.isValid("http://ww.google.com"));
	   assertFalse(urlVal.isValid("google"));
	   assertFalse(urlVal.isValid("amazon.com"));
	   assertTrue(urlVal.isValid("http://google.com"));
	   
	   //Using arrays like this is easier. Feel free to add more valid URLs to either.
	   String[] validUrls = {"", 
			   "http://www.amazon.com", 
			   "https://www.google.com", 
			   "http://ww.google.com",
			   "ftp://127.0.0.1", 
			   "https://oregonstate.instructure.com/courses/1568425", 
			   "http://eecs.oregonstate.edu/current%20students",
			   "http://localhost/", 
			   "http://www.amazon.com:80",
			   "https://mail.google.com/mail/u/0/?hl=en&shva=1#inbox",
			   "http://blog.yourwebsite.com"};
	   
	   String[] invalidUrls = {"amazon.com",
			   "google",
			   "http://www.google.com:123r",
			   "htp://google.com",
			   "https:///www.google.com",
			   "http//www.oregonstate.edu",
			   "http:\\www.amazon.com"};
	   
	   int i;
	   boolean isValid;
	   
	   for(i = 0; i < validUrls.length; i++)
	   {
		   System.out.println("Testing URL: " + validUrls[i]);
		   isValid = urlVal.isValid(validUrls[i]);
		   if (isValid)
		   {
			   System.out.println("TEST PASSED");
		   }
		   else
		   {
			   System.out.println("TEST FAILED");
		   }
	   }
	   
	   System.out.println();
	   
	   for(i = 0; i < invalidUrls.length; i++)
	   {
		   System.out.println("Testing invalid URL: " + invalidUrls[i]);
		   isValid = urlVal.isValid(invalidUrls[i]);
		   if (!isValid)
		   {
			   System.out.println("TEST PASSED");
		   }
		   else
		   {
			   System.out.println("TEST FAILED");
		   }
	   }
   }
   
   /******************************************
    * Part 2: Input Partitioning
    ******************************************/
   
   public void testYourFirstPartition()
   {
	   //Testing Schemes
	   
	   UrlValidator urlVal = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   boolean passed = true;
	   
	   String validOne = "http://";
	   String validTwo = "https://";
	   String validThree = "ftp://";
	   
	   String invalidOne = "h3pp://";
	   
	   String urlBig = "www.google.com";
	   
	   String validUrl = validOne + urlBig;
	   String invalidUrl = invalidOne + urlBig;
	   
	   System.out.println("");
	   System.out.println("Testing Schemes");
	   
	   if(!urlVal.isValid(validUrl))
	   {
		   System.out.println("TEST FAILED. Expected valid for URL: " + validUrl);
		   passed = false;
	   }
	   
	   validUrl = validTwo + urlBig;
	   
	   if(!urlVal.isValid(validUrl))
	   {
		   System.out.println("TEST FAILED. Expected valid for URL: " + validUrl);
		   passed = false;
	   }
	   
	   validUrl = validThree + urlBig;
	   
	   if(!urlVal.isValid(validUrl))
	   {
		   System.out.println("TEST FAILED. Expected valid for URL: " + validUrl);
		   passed = false;
	   }
	   
	   if(urlVal.isValid(invalidUrl))
	   {
		   System.out.println("TEST FAILED. Expected invalid for URL: " + invalidUrl);
		   passed = false;
	   }
	   
	   if(passed)
	   {
		   System.out.println("Scheme Test Passed");
	   }
	   else
	   {
		   System.out.println("Scheme Test Failed");
	   }
   }
   
   public void testYourSecondPartition()
   {
	   UrlValidator urlVal = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   System.out.println("");
	   System.out.println("Testing Authority");
	   
	   boolean passed = true;
	   
	   String validOne = "www.google.com";
	   String validTwo = "amazon.com";
	   String validThree = "127.0.0.1";
	   
	   String invalidOne = "google";
	   String invalidTwo = ".google.com";
	   
	   String urlBig = "http://";
	   
	   String validUrl = urlBig + validOne;
	   String invalidUrl = urlBig + invalidOne;
	   
	   if(!urlVal.isValid(validUrl))
	   {
		   System.out.println("TEST FAILED. Expected valid for URL: " + validUrl);
		   passed = false;
	   }
	   
	   validUrl = urlBig + validTwo;
	   
	   if(!urlVal.isValid(validUrl))
	   {
		   System.out.println("TEST FAILED. Expected valid for URL: " + validUrl);
		   passed = false;
	   }
	   
	   validUrl = urlBig + validThree;
	   
	   if(!urlVal.isValid(validUrl))
	   {
		   System.out.println("TEST FAILED. Expected valid for URL: " + validUrl);
		   passed = false;
	   }
	   
	   if(urlVal.isValid(invalidUrl))
	   {
		   System.out.println("TEST FAILED. Expected invalid for URL: " + invalidUrl);
		   passed = false;
	   }
	   
	   invalidUrl = urlBig + invalidTwo;
	   
	   if(urlVal.isValid(invalidUrl))
	   {
		   System.out.println("TEST FAILED. Expected invalid for URL: " + invalidUrl);
		   passed = false;
	   }
	   
	   if(passed)
	   {
		   System.out.println("Authority Test Passed");
	   }
	   else
	   {
		   System.out.println("Authority Test Failed");
	   }
   }
   
   public void testYourThirdPartition()
   {
	   UrlValidator urlVal = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   System.out.println("");
	   System.out.println("Testing Path");
	   
	   boolean passed = true;
	   
	   String validOne = "/test1";
	   String validTwo = "/test1/pics";
	   
	   String invalidOne = "/..";

	   String urlBig = "http://www.google.com";
	   
	   String validUrl = urlBig + validOne;
	   String invalidUrl = urlBig + invalidOne;
	   
	   if(!urlVal.isValid(validUrl))
	   {
		   System.out.println("TEST FAILED. Expected valid for URL: " + validUrl);
		   passed = false;
	   }
	   
	   validUrl = urlBig + validTwo;
	   
	   if(!urlVal.isValid(validUrl))
	   {
		   System.out.println("TEST FAILED. Expected valid for URL: " + validUrl);
		   passed = false;
	   }
	   
	   if(urlVal.isValid(invalidUrl))
	   {
		   System.out.println("TEST FAILED. Expected invalid for URL: " + invalidUrl);
		   passed = false;
	   }
	   
	   if(passed)
	   {
		   System.out.println("Path Test Passed");
	   }
	   else
	   {
		   System.out.println("Path Test Failed");
	   }
   }
   
   public void testYourFourthPartition()
   {
	   UrlValidator urlVal = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   System.out.println("");
	   System.out.println("Testing Query");
	   
	   boolean passed = true;
	   
	   String validOne = "?action=view";
	   String validTwo = "?action=edit&mode=up";

	   String urlBig = "http://www.google.com";
	   
	   String validUrl = urlBig + validOne;
	   
	   if(!urlVal.isValid(validUrl))
	   {
		   System.out.println("TEST FAILED. Expected valid for URL: " + validUrl);
		   passed = false;
	   }
	   
	   validUrl = urlBig + validTwo;
	   
	   if(!urlVal.isValid(validUrl))
	   {
		   System.out.println("TEST FAILED. Expected valid for URL: " + validUrl);
		   passed = false;
	   }
	   
	   if(passed)
	   {
		   System.out.println("Path Test Passed");
	   }
	   else
	   {
		   System.out.println("Query Test Failed");
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
