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
import java.util.UUID;
import org.junit.Test;
import java.util.Random;
//import static org.junit.Assert.*;
 

/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */


public class URLValidatorRandomTest extends TestCase {

   private boolean printStatus = false;
   private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.

   //
   char[] LetterPunct= {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t',
'u','v','w','x','y','z','-','/','[','&','#','@','!'};

   //generate random strings
   public String RandNumString()
   {
       //create string
       String randuuid = UUID.randomUUID().toString();    
       return randuuid;
   }
   //
   public String RandString(int size)
   {
	   Random rand = new Random();
	   StringBuilder sb = new StringBuilder();
	   
	   for(int i=0;i<size;i++){
		   int value = rand.nextInt(33);//length of LetterPunct  
		   sb.append(LetterPunct[value]);
		   //create string
	   }
	   String str = sb.toString();
       return str;
   }
   //address prefix
   String[] UrlPrefix= {
			  "http://",
			  "http://www.",
			  "https://www",
			  "www.",
			  "https://",
			  "https://www.",
			  "http://www.",
			  "https://",
			  "",
			  "http://www.",
			  "ftp://",
			  "ftp://www.",
			  "ftp://www",
			  "http://wwww",
			  "http://ww",
			  "http:/",
			  "http:",
			  "http:///",
			  "http//",};
   //
   String[] UrlPostfix= {
			  ".com",
			  ".net",
			  ".edu/",
			  ".eu",
			  ".edu",
			  ".gov",
			  ".us",
			  ".html",
			  ".com/mail/",
			  ".co.uk",
			  ".33",
			  ""};
   
   //IsValid tests
   @Test
   public void testRandomTest(int i)
   {
	  UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
       String randText=RandNumString();
       String testURL=UrlPrefix[i]+randText+UrlPostfix[i];
  	   boolean result;
       //URL Validation
  	   System.out.println("Testing valid URL address:"+testURL);
  	   result= urlVal.isValid(testURL);
  	   
  	   
  	   if (result)
  	   { 
  		   System.out.println("Valid URL:"+testURL+" Pass");
  	   }
  	   else {
  		   System.out.println("Valid URL:"+testURL+" Fail");
  	   }

   }
   
   
   @Test
   public void testRandomlettersTest(int i)
   {
	  UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
       String randText=RandString(10);//test 10 character strings
       String testURL=UrlPrefix[i]+randText+UrlPostfix[i];
  	   boolean result;
       //URL Validation
  	   System.out.println("Testing valid URL address random letters:"+testURL);
  	   result= urlVal.isValid(testURL);
  	   
  	   
  	   if (result)
  	   { 
  		   System.out.println("Valid URL:"+testURL+" Pass");
  	   }
  	   else {
  		   System.out.println("Valid URL:"+testURL+" Fail");
  	   }

   }
   
   //Do random tests  
   //Partition testing
   //first partition numbers and letters
   public void testYourFirstPartition()
   {
       int numTests=10;
       //call randomTests
	   for(int i = 0;i<numTests;i++)
	   {
		   testRandomTest(i);
	   }
   }
   //second partition punctuation and letters
   public void testYourSecondPartition(){
       int numTests=10;
       //call randomTests
	   for(int i = 0;i<numTests;i++)
	   {
		   testRandomlettersTest(i);
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
