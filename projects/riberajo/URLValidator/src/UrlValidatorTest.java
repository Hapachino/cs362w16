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
 private boolean printIndex = false; //print index that indicates current scheme,host,port,path, query test were using.

 public UrlValidatorTest(String testName) {
  super(testName);
 }



 public void testManualTest() {
  UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
  System.out.println(urlVal.isValid("http://www.amazon.com"));


 }


 public void testYourFirstPartition() {

 }

 public void testYourSecondPartition() {

 }


 public void testIsValid() {
  // for random seeds
  Random random = new Random();

  // urls for true/false
  String trueTestURL = "";
  String falseTestURL = "";
  UrlValidator trueValidator;
  UrlValidator falseValidator;


  for (int i = 0; i < 100000; i++) {
   int trueSchemeNum = random.nextInt(3);
   int falseSchemeNum = random.nextInt(5);
   int trueAuthorityNum = random.nextInt(7);
   int falseAuthorityNum = random.nextInt(12);
   int truePortNum = random.nextInt(5);
   int falsePortNum = random.nextInt(2);
   int truePathNum = random.nextInt(4);
   int falsePathNum = random.nextInt(2);
   int trueQueryNum = random.nextInt(3);

   // build url that should assert true
   trueTestURL = trueTestUrlScheme[trueSchemeNum] + trueTestUrlAuthority[trueAuthorityNum] +
    trueTestUrlPort[truePortNum] + trueTestPath[truePathNum] + trueTestUrlQuery[trueQueryNum];

   // build url that should assert false
   falseTestURL = falseTestUrlScheme[falseSchemeNum] + falseTestUrlAuthority[falseAuthorityNum] +
    falseTestUrlPort[falsePortNum] + falseTestPath[falsePathNum];

   //trueTestURL = "http://go.au";
   //falseTestURL = "gttp://google.com";

   // true validator
   trueValidator = new UrlValidator(null, null, UrlValidator.ALLOW_LOCAL_URLS);
   trueValidator.isValid(trueTestURL);

   // false validator
   falseValidator = new UrlValidator(null, null, UrlValidator.ALLOW_LOCAL_URLS);
   falseValidator.isValid(falseTestURL);

   // test true URLS
   System.out.println(" -- Testing True URLS -- ");
   boolean trueBugCount = trueValidator.isValid(trueTestURL);
   if (trueBugCount) {
	System.out.println(" . pass . ");
   } else {
	   // if test fails print the count and the particular URL that failed
        System.out.println("TEST FAIL!");
        System.out.println("URL Fail: " + trueTestURL);
        System.out.println("Actual: " + trueBugCount + " | Expected: true");
   }
   

   // test false URLS
   System.out.println(" -- Testing False URLS -- ");
   boolean falseBugCount = falseValidator.isValid(falseTestURL);
   if (!falseBugCount) {
    System.out.println(" . pass . ");
   } else {
    System.out.println("URL Fail: " + falseTestURL);
    //System.out.println("bool result: " + falseValidator.isValid(falseTestURL));
   }
  }
 }

 public void testAnyOtherUnitTest() {

 }


 String[] trueTestUrlScheme = {
  "http://",
  "ftp://",
  "https://"
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

 String[] falseTestUrlAuthority = {
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
 String[] falseTestPath = {
  "/..//file",
  "/test1//file"
 };

 String[] trueTestUrlQuery = {
  "?action=view",
  "?action=edit&mode=up",
  ""
 };


}