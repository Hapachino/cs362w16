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
	   String [] inURL = {"http://www.amazon.com"
			   			 ,"something.com"
			   			 ,"https://www.w3.org/Addressing/URL/url-spec.txt"
			   			 ,"http://www.autotrader.com/cars-for-sale/showcase.xhtml?zip=90210&Log=0&searchRadius=25"
			   			 ,"http://www.autotrader.com/cars-for-sale/Ames+IA-50014?endYear=2017"
			   			 ,"ftp://ftp.funet.fi/pub/standards/RFC/rfc959.txt"
			   			 ,"mailto:someone@example.com?Subject=Hello%20again"
			   			 ,"mailto:someone@example.com"
			   			 ,"file://alpha.hut.fi/u/lai/tik/tik76002/public_html/lerman.files/chaps"
			   			 ,"file://localhost/etc/fstab"
			   			 ,"ftp://public.ftp-servers.example.com/mydirectory/myfile.txt"
			   			 ,"http://example.com/cgi-bin/feed.cgi?feed=news&frm=rss"}; 
	   for (int i =  0; i < inURL.length; i++) {
		   System.out.println(inURL[i] + " --- " + urlVal.isValid(inURL[i]));
	   }
   }
   
   /*
    * Performs Validation Test for http.
    * http URL syntax: "http:" "//" host [ ":" port ] [ abs_path [ "?" query ]]
    */
   public void testYourFirstPartition()
   {
	   System.out.println("Testing first partition - http");
   }
   
   /*
    * Performs Validation Test for ftp.
    * ftp URL syntax: ftp://[user[:password]@]host[:port]/url-path
    * 
    */
   public void testYourSecondPartition(){
	   System.out.println("Testing second partition - ftp");
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
