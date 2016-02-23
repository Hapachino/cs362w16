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
	   UrlValidator urlVal = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
	   System.out.println("Schema Test - Allow All Schemes");
	   assertTrue(urlVal.isValid("http://www.amazon.com"));
	   assertTrue(urlVal.isValid("https://www.google.com"));
	   assertTrue(urlVal.isValid("http://ww.google.com"));
	   assertFalse(urlVal.isValid("google"));
	   assertFalse(urlVal.isValid("amazon.com"));
	   assertFalse(urlVal.isValid("http//ww.nbnbnb.com"));
	   
	   //Test valid schemas (https, http, ftp ...).
	   urlVal = new UrlValidator();
	   System.out.println("Restricted Schemas Test");
	   assertTrue(urlVal.isValid("http://www.amazon.com"));
	   assertTrue(urlVal.isValid("https://www.google.com"));
	   assertFalse(urlVal.isValid("ht://ww.google.com"));
	   assertFalse(urlVal.isValid("google"));
	   assertFalse(urlVal.isValid("amazon.com"));
	   assertFalse(urlVal.isValid("http//www.google.com.*"));
	   
	   //Test local URLs being allowed.
	   urlVal = new UrlValidator(UrlValidator.ALLOW_LOCAL_URLS);
	   System.out.println("Local URLs being allowed");
	   assertTrue(urlVal.isValid("http://127.0.0.1"));
	   assertFalse(urlVal.isValid("http://localhost")); //Should be true, possible bug

	   
	   // Test for fragments not allowed.
	   System.out.println("No Fragments Test");
	   urlVal = new UrlValidator(UrlValidator.NO_FRAGMENTS);
	   assertFalse(urlVal.isValid("http://www.bigdog/time.php")); //Should be ture, possible bug
	   assertFalse(urlVal.isValid("http://http://www.google.comwww.google.comwww.google.comwww.google.comwww.google.comwww.google.comwww.google.comwww.google.comwww.google.comwww.google.comwww.google.comwww.google.comwww.google.comwww.google.comwww.google.comwww.google.comwww.google.comwww.google.comwww.google.comwww.google.comwww.google.comwww.google.comwww.google.comwww.google.comwww.google.comwww.google.comwww.google.comwww.google.comwww.google.com"));
	    
   	   // Test for 2 slashes in paths (allowed).
	   System.out.println("Allow 2 slashes with path");
	   urlVal = new UrlValidator(UrlValidator.ALLOW_2_SLASHES);
	   assertTrue(urlVal.isValid("http://www.example.com//blog"));
	   assertTrue(urlVal.isValid("http://www.example.com//blog//index.php")); 
	    	   
   }
   
   
   public void testYourFirstPartition()
   {
	  //Test of URL Maker
	  UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	  ResultPair url = URLmaker(0,1,1,0,0);
	  System.out.println("Make URL 1: " + url.item);

	  if (url.valid) {
	   assertTrue(urlVal.isValid(url.item));
	   }
	   else {
		   assertFalse(urlVal.isValid(url.item));
	   }
	   System.out.println("Run Completed");
   }
   
   public void testYourSecondPartition(){
	 //Test of URL Maker
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   ResultPair url = URLmaker(1,1,0,0,0);
	   System.out.println("Make URL 2: " + url.item);

	   if (url.valid) {
		   assertTrue(urlVal.isValid(url.item));
	   }
	   else {
		   assertFalse(urlVal.isValid(url.item));
	   }

	   System.out.println("Run Completed");    
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
   
   // This function will make a URL and return it inside a ResultPair,
   public ResultPair URLmaker(int schema_idx, int host_idx, int port_idx, int path_idx, int query_idx)
   {
	   //Test for valid URL Index on ResultPair
	   if ((schema_idx >= testSchemas.length) || (host_idx >= testHosts.length) ||
			   (port_idx >= testPorts.length) || (path_idx >= testPaths.length) ||
			   (query_idx >= testQueries.length)) {
		   return new ResultPair("Invalid Range", false);
	   }
	   else {
		   //Make URL, if all parts true than true
		   String URLstring = testSchemas[schema_idx].item + testHosts[host_idx].item
				   + testPorts[port_idx].item + testPaths[path_idx].item +
				   testQueries[query_idx].item;
		   
		   boolean URLboolean = true;
		   
		   //Make URL, if any part false, false
		   if (!testSchemas[schema_idx].valid || !testHosts[host_idx].valid
				   || !testPorts[port_idx].valid || !testPaths[path_idx].valid
				   || !testQueries[query_idx].valid) {
			   URLboolean = false;
		   }
		   
		   ResultPair expectedURL = new ResultPair(URLstring, URLboolean);
		   return expectedURL;  
	   }
   }
   
   /* 
    * Create result pairs for portions of URL
    * to test possible test cases of URLs
    *
    */
   
	//Schemas
	ResultPair[] testSchemas = {
		   new ResultPair("http://", true),
		   new ResultPair("https://", true),
		   new ResultPair("ftp://", true),
		   new ResultPair("bob://", false),
		   new ResultPair("http:////", false),
		   new ResultPair("http//", false),
		   new ResultPair("http:/", false),
		   new ResultPair("", false) 	// Should be true
	};
	//Hosts
	ResultPair[] testHosts = {
		   new ResultPair("www.amazon.com", true),
		   new ResultPair("www.bing.com", true),
		   new ResultPair("127.0.0.1", true),
		   new ResultPair("", false),
		   new ResultPair("amazon", false),
		   new ResultPair("amazon.", false),
		   new ResultPair(".amazon", false),
		   new ResultPair("www.amazon", false),
		   new ResultPair("amazon com", false),
		   new ResultPair("127..0.1", false),
		   new ResultPair("127.1", false),
		   new ResultPair(".127.0.0.1", false),
		   new ResultPair("256.0.0.1", false),
		   new ResultPair("127", false)
	};
	//Port Numbers
	ResultPair[] testPorts = {
		   new ResultPair("", true),
		   new ResultPair(":80", true),
		   new ResultPair(":8080", true),
		   new ResultPair(":65535", true),
		   new ResultPair(":65536", false),
		   new ResultPair(":24b", false),
		   new ResultPair(":-80", false)
	};
	//Paths,  should start with slash
	ResultPair[] testPaths = {
		   new ResultPair("", true),
		   new ResultPair("/path", true),
		   new ResultPair("/path/name", true), 
		   new ResultPair("/path2/../path1", true),
		   new ResultPair("/path2/..path1", false),

	};
	//Queries 
	ResultPair[] testQueries = {
		   new ResultPair("", true),
		   new ResultPair("?lvalue=rvalue", true),
		   new ResultPair("?lvalue=rvalue&lvalue2=rvalue2", true),
		   new ResultPair("?lvalue=rvalue:lvalue2=rvalue2", false),
		   new ResultPair("?=rvalueonly", false) 
	};   
   

}
