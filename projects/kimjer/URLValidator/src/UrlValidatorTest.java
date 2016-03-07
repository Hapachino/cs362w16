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
	   //mutiple dots, http://10.10.10.999, https://google.com.; https://google.com.com
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   ////System.out.println("Value of isValid() is: ");
	   //System.out.println(urlVal.isValid("https://google.com:09"));
	   
   }
   
   
   public void partition1Bug3()
   {
	   //TEST ports 0 to 999
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   for(int i=1; i<1000; i++)
	   {
		   String URLauthority = "https://xyz.com:" + Integer.toString(i);
		   //System.out.println(i);
		   boolean res = urlVal.isValid(URLauthority);
		   assertEquals(res, true);
	   }
   }
   
   public void partition2Bug3(){
	   //test 1000 to 65535
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   for(int i=1000; i<65536; i++)
	   {
		   String URLauthority = "https://xyz.com:" + Integer.toString(i);
		   //System.out.println(i);
		   boolean res = urlVal.isValid(URLauthority);
		   assertEquals(res, true);
	   }
   }
   
   public void partition3Bug3(){
	   //test 65636 to 100000
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   for(int i=65536; i<100001; i++)
	   {
		   String URLauthority = "https://xyz.com:" + Integer.toString(i);
		   //System.out.println(i);
		   boolean res = urlVal.isValid(URLauthority);
		   assertEquals(res, false);
	   }
   }
   
   public void partition4Bug3(){
	   //test 0 padded valid ports
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
   
	   for(int i=1; i<65536; i++)
	   {
		   assertEquals(urlVal.isValid("https://xyz.com:0" +Integer.toString(i)), true);
	   }
   }
   
   public void partition5Bug3(){
	   //test 0 padded valid ports
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
   
	   for(int i=1; i<65536; i++)
	   {
		   assertEquals(urlVal.isValid("https://xyz.com:00" +Integer.toString(i)), true);
	   }
   }
   
   public void partition6Bug3(){
	   //test 0 padded valid ports
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
   
	   for(int i=1; i<65536; i++)
	   {
		   assertEquals(urlVal.isValid("https://xyz.com:000" +Integer.toString(i)), true);
	   }
   }
   
   public void partition7Bug3(){
	   //test 0 padded valid ports
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
   
	   for(int i=1; i<65536; i++)
	   {
		   assertEquals(urlVal.isValid("https://xyz.com:0000" +Integer.toString(i)), true);
	   }
   }
   
   
   public void partition8Bug3(){
	   //test 0 padded valid ports
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
   
	   for(int i=1; i<65536; i++)
	   {
		   assertEquals(urlVal.isValid("https://xyz.com:00000" +Integer.toString(i)), true);
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
