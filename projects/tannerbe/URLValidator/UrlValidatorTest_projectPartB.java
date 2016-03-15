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
import java.security.SecureRandom;




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
	   int RandomNumber;
	   Random random = new Random();
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   System.out.println(urlVal.isValid("http://www.amazon.com"));
	   System.out.println(urlVal.isValid("http://https://www.amazon.com"));
	   System.out.println(urlVal.isValid("http://www.ama/zon.com"));
	   System.out.println(urlVal.isValid("http://wwww.amazon.com:523"));
	   System.out.println(urlVal.isValid("http://wwww.amazon.com:999"));
	   System.out.println(urlVal.isValid("http://wwww.amazon.com:1000"));
	   System.out.println(urlVal.isValid("http://wwww.amazon.com:8695"));
	   System.out.println(urlVal.isValid("http://amazon.org"));
	   System.out.println(urlVal.isValid("http://www.a?mazon.com"));
	   System.out.println(urlVal.isValid("http://www.amazon.com"));
	   System.out.println(urlVal.isValid("http://2.255.2.3"));
	   System.out.println(urlVal.isValid("http://2.256.2.3"));
	   System.out.println(urlVal.isValid("http://2.999.2.3"));
	   	System.out.println(urlVal.isValid("http://www.amazon.com"));
	   	System.out.println(urlVal.isValid("http://www.amazon.com?x=1"));
	   	System.out.println(urlVal.isValid("http://www.amazon.com?xxx"));
	   	System.out.println(urlVal.isValid("http://www.amazon.com?x"));
	   	System.out.println(urlVal.isValid("http://www.amazon.com?x\n"));
	   	System.out.println(urlVal.isValid("http://www.amazon.com?x\r"));
	   	System.out.println(urlVal.isValid("http://www.amazon.com?x\0"));
	   	System.out.println(urlVal.isValid("http://www.amazon.com?x\0" + " " + Character.toString ((char) 1)));
	   System.out.println(urlVal.isValid("http://www.amazon.com:1"));
	   	System.out.println(urlVal.isValid("http://www.amazon.com:12"));
	   	System.out.println(urlVal.isValid("http://www.amazon.com:123"));
	   	System.out.println(urlVal.isValid("http://www.amazon.com:1234"));
	   	System.out.println(urlVal.isValid("http://www.amazon.com:12345"));
	   	System.out.println(urlVal.isValid("http://www.amazon.com:123456"));
	   	System.out.println(urlVal.isValid("http://www.amazon.com:123456"));
	   	System.out.println(urlVal.isValid("http://www.amazon.com:65535"));
	   	System.out.println(urlVal.isValid("http://www.amazon.com:65536"));
	   	System.out.println(urlVal.isValid("http://www.amazon.com"));
	   	System.out.println(urlVal.isValid("http://www.amazon.com:12a"));
	   	System.out.println(urlVal.isValid("http://www.amazon.com:b34"));
	   	System.out.println(urlVal.isValid("http://www.amazon.com:abc"));
	   
   }
   
   
   public void testYourFirstPartition()
   {
		//partitions based on port length
	   	System.out.println("Testing second Partition!");
	   	UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   	System.out.println(urlVal.isValid("http://www.amazon.com:1"));
	   	System.out.println(urlVal.isValid("http://www.amazon.com:12"));
	   	System.out.println(urlVal.isValid("http://www.amazon.com:123"));
	   	System.out.println(urlVal.isValid("http://www.amazon.com:1234"));
	   	System.out.println(urlVal.isValid("http://www.amazon.com:12345"));
	   	System.out.println(urlVal.isValid("http://www.amazon.com:123456"));
	   	System.out.println(urlVal.isValid("http://www.amazon.com:123456"));
	   	System.out.println(urlVal.isValid("http://www.amazon.com:65535"));
	   	System.out.println(urlVal.isValid("http://www.amazon.com:65536"));
	   	System.out.println(urlVal.isValid("http://www.amazon.com"));
	   	System.out.println(urlVal.isValid("http://www.amazon.com:12a"));
	   	System.out.println(urlVal.isValid("http://www.amazon.com:b34"));
	   	System.out.println(urlVal.isValid("http://www.amazon.com:abc"));
	   	System.out.println("End Testing second Partition!");
	      

   }
   
   public void testYourSecondPartition(){
	   	//partition based on query string in URL
	   	System.out.println("Testing first Partition!");
	   	UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   	System.out.println(urlVal.isValid("http://www.amazon.com"));
	   	System.out.println(urlVal.isValid("http://www.amazon.com?x=1"));
	   	System.out.println(urlVal.isValid("http://www.amazon.com?xxx"));
	   	System.out.println(urlVal.isValid("http://www.amazon.com?x"));
	   	System.out.println(urlVal.isValid("http://www.amazon.com?x\n"));
	   	System.out.println(urlVal.isValid("http://www.amazon.com?x\r"));
	   	System.out.println(urlVal.isValid("http://www.amazon.com?x\0"));
	   	System.out.println(urlVal.isValid("http://www.amazon.com?x\0" + " " + Character.toString ((char) 1)));
	   	System.out.println("Testing end Partition!");
   }

   
   public void testIsValid()
   {

	   	//Programmatically checking for a functioning query string
	   	System.out.println("Testing Iteratively!");
	   	Random ran = new Random();
	   	UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   	String RandomString = "";
	   	String RandomString2;
	   	char letter = ' ';
	   	int RandomNumber;
	   	for(int i = 0;i<1000;i++)
	   	{
	   		RandomNumber = ran.nextInt(10) + 1;
	   		for (int b=0; b<=RandomNumber; b++) {
	   			letter = (char)(ran.nextInt(127));
	   			RandomString= letter + RandomString;
	   		 }
	   	    
	   		// RandomString = new BigInteger(RandomNumber, random).toString(32);
	   	   // RandomString = new BigInteger(RandomNumber, random).toString(32);
	   		//RandomString2 = new BigInteger(RandomNumber, random).toString(32);
	   		System.out.println(urlVal.isValid("http://www.google.com?" + RandomString + "=" + RandomString)) ;
	   		RandomString = "";
	   	}
	   	System.out.println("End Testing Iteratively!");

   }
   
   public void testAnyOtherUnitTest()
   {
	     //Programmatically checking for a functioning URL port   
	   	System.out.println("Testing Iteratively!");
	   	SecureRandom random = new SecureRandom();
	   	UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   	int RandomNumber;
	   	for(int i = 0;i<10000;i++)
	   	{
	   		RandomNumber = random.nextInt(10000) + 1;
	   		System.out.println(urlVal.isValid("http://www.google.com:"+ RandomNumber )) ;
	   	}
	   	System.out.println("End Testing Iteratively!");
   }
   /**
    * Create set of tests by taking the testUrlXXX arrays and
    * running through all possible permutations of their combinations.
    *
    * @param testObjects Used to create a url.
    */
   

}
