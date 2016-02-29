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
	   //System.out.println(urlVal.isValid("http://www.amazon.com:80/example?test=passed&result=true"));
   }
   
   public void testYourFirstPartition()
   {
	   String trueScheme = "http://";
	   String trueAuthority = "www.amazon.com";
	   String truePort = ":80";
	   String truePath = "/example";
	   String trueQuery = "?test=passed&result=true";
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   String falseScheme = "1h2t1p://";
	   String emptyScheme = "";
	   
	   String valid = trueScheme + trueAuthority + truePort + truePath + trueQuery;
	   String invalid = falseScheme + trueAuthority + truePort + truePath + trueQuery;
	   String empty = emptyScheme + trueAuthority + truePort + truePath + trueQuery;
	   
	   System.out.println("Testing Scheme Partition");
	   
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
   
   public void testYourSecondPartition(){
	   String trueScheme = "http://";
	   String trueAuthority = "www.amazon.com";
	   String truePort = ":80";
	   String truePath = "/example";
	   String trueQuery = "?test=passed&result=true";
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   String falseAuthority = "!@#$%^&*(_).com";
	   String emptyAuthority = "";
	   
	   String valid = trueScheme + trueAuthority + truePort + truePath + trueQuery;
	   String invalid = trueScheme + falseAuthority + truePort + truePath + trueQuery;
	   String empty = trueScheme + emptyAuthority + truePort + truePath + trueQuery;	   
	   
	   System.out.println("Testing Authority Partition");
	   
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
	   
   }
   /**
    * Create set of tests by taking the testUrlXXX arrays and
    * running through all possible permutations of their combinations.
    *
    * @param testObjects Used to create a url.
    */
   

}
