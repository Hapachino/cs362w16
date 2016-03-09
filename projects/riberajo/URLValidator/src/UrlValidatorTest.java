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
import java.util.Random;





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


   public void testYourFirstPartition()
   {

   }

   public void testYourSecondPartition(){

   }


   public void testIsValid()
   {
     // for random seeds
     Random random = new Random();

     // urls for true/false
     String trueTestURL = "";
     String falseTestURL = "";
     UrlValidator trueValidator = new UrlValidator(UrlValidator.ALLOW_LOCAL_URLS);
     UrlValidator falseValidator = new UrlValidator(UrlValidator.ALLOW_LOCAL_URLS);

     // counts for pass/fail tests
     int truePass = 0;
     int trueFail = 0;
     int falsePass = 0;
     int falseFail = 0;

	   for(int i = 0;i<10000;i++)
	   {
       int trueSchemeNum = random.nextInt(4);
       int falseSchemeNum = random.nextInt(5);
       int trueAuthorityNum = random.nextInt(7);
       int falseAuthorityNum = random.nextInt(12);
       int truePortNum = random.nextInt(5);
       int falsePortNum = random.nextInt(2);
       int truePathNum = random.nextInt(4);
       int falsePathNum = random.nextInt(5);
       int trueQueryNum = random.nextInt(3);

       // build url that should assert true
       trueTestURL = trueTestUrlScheme[trueSchemeNum] + trueTestUrlAuthority[trueAuthorityNum] +
       trueTestUrlPort[truePortNum] + trueTestPath[truePathNum] + trueTestUrlQuery[trueQueryNum];

       // build url that should assert false
       falseTestURL = falseTestUrlScheme[falseSchemeNum] + falseTestUrlAuthority[falseAuthorityNum] +
       falseTestUrlPort[falsePortNum] + falseTestPath[falsePathNum];

       // true validator
       trueValidator = new UrlValidator(null);
       trueValidator.isValid(trueTestURL);

       // false validator
       falseValidator = new UrlValidator(null);
       falseValidator.isValid(falseTestURL);

       // test true URLS
       System.out.println(" -- Testing True URLS -- ");
       boolean trueBugCount = trueValidator.isValid(trueTestURL);
       if(trueBugCount) {
         truePass++;
       }
       else {
         trueFail++;
       }

       if(trueFail == 0) {
          system.out.println("TEST PASS! Valid URL Count: " + truePass);
       }
       // if test fails print the count and the particular URL that failed
       else {
         system.out.println("PASS FAIL! Invalid URL Count: " + trueFail);
         system.out.println("URL Fail: " trueTestURL);
       }

       // test false URLS
       System.out.println(" -- Testing False URLS -- ");
       boolean falseBugCount = falseValidator.isValid(falseTestURL);
       if(!falseBugCount) {
         falsePass++;
       }
       else {
         falseFail++;
       }

       if(falseFail == 0) {
          system.out.println("TEST PASS! Valid URL Count: " + falsePass);
       }
       // if test fails print the count and the particular URL that failed
       else {
         system.out.println("PASS FAIL! Invalid URL Count: " + falseFail);
         system.out.println("URL Fail: "falseTestURL);
       }
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


    String[] trueTestUrlScheme = {
    		 "http://",
         "ftp://",
         "h3t://",
         ""
    };

    String[] falseTestUrlScheme = {
    		"3ht://",
        "http:/",
        "http:",
        "http/",
        "://"
    };

    String[] trueTestUrlAuthority = {
    		"www.google.com",
        "go.com",
        "go.au",
        "0.0.0.0",
        "255.255.255.255",
        "255.com",
        "go.cc"
    };

    String[] falsetestUrlAuthority = {
        "256.256.256.256",
        "1.2.3.4.5",
        "1.2.3.4.",
        "1.2.3",
        ".1.2.3.4",
        "go.a",
        "go.a1a",
        "go.1aa",
        "aaa.",
        ".aaa",
        "aaa",
        ""
    };

    String[] trueTestUrlPort = {
        ":80",
         ":65535",
         ":0",
          "",
          ":65636"
    };

    String[] falseTestUrlPort = {
        ":-1",
        ":65a"
    };

    String[] trueTestPath = {
    		"/test1",
        "/test1/",
        "",
        "/test1/file"
    };

    String[] trueTestUrlQuery = {
       "?action=view",
        "?action=edit&mode=up",
        ""
    };


}
