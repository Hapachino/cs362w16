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

import java.util.UUID;
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

   //IsValid tests
   public void testManualTest()
   {
	  	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
  	   boolean result;
         //URL Validation
  	   System.out.println("Testing valid URL address www.amazon.com");
  	   result= urlVal.isValid("http://www.amazon.com");
  	   if (result)
  	   { 
  		   System.out.println("Valid URL...Pass");
  	   }
  	   else {
  		   System.out.println("Valid URL...Fail");
  	   }
 	   System.out.println("****Manual Tests Completed****");
   }

   //generate random strings
    public static String RandString()
    {
        //create string
        String randuuid = UUID.randomUUID().toString();    
        return randuuid;
    }

   //Randomized Testing   
   public class RandomUrlValidatorTest extends TestCase {
   private boolean printStatus = false;
   private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.

   public UrlValidatorTest(String testName) {
      super(testName);
   }

   //IsValid tests
   public void testRandomTest(int i)
   {
	  UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
       testURL=new RandString();
  	   boolean result;
       //URL Validation
  	   System.out.println("Testing valid URL address:"+testURL);
  	   result= urlVal.isValid(testURL);
  	   if (result)
  	   { 
  		   System.out.println("Valid URL...Pass");
  	   }
  	   else {
  		   System.out.println("Valid URL...Fail");
  	   }
 	   System.out.println("Test Completed);
   }

   }

   //Partition testing
   public void testYourFirstPartition()
   {
	   
   }
   
   public void testYourSecondPartition(){
	   
   }
   
   
   public void testIsValid()
   {
       int numTests=2000
       //call manual tests
       UrlValidatorTest;
       //call randomTests
	   for(int i = 0;i<numTests;i++)
	   {
		   testRandomTest;
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
