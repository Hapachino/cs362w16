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


import java.util.Random;
import java.util.regex.Pattern;

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

   
   /************************************************
    *       PART 1: MANUAL TESTING
    ************************************************/
   
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
	   assertFalse(urlVal.isValid("http://www.bigdog/time.php")); //Should be true, possible bug
	   assertFalse(urlVal.isValid("http://http://www.google.comwww.google.comwww.google.comwww.google.comwww.google.comwww.google.comwww.google.comwww.google.comwww.google.comwww.google.comwww.google.comwww.google.comwww.google.comwww.google.comwww.google.comwww.google.comwww.google.comwww.google.comwww.google.comwww.google.comwww.google.comwww.google.comwww.google.comwww.google.comwww.google.comwww.google.comwww.google.comwww.google.comwww.google.com"));
	    
   	   // Test for 2 slashes in paths (allowed).
	   System.out.println("Allow 2 slashes with path");
	   urlVal = new UrlValidator(UrlValidator.ALLOW_2_SLASHES);
	   assertTrue(urlVal.isValid("http://www.example.com//blog"));
	   assertTrue(urlVal.isValid("http://www.example.com//blog//index.php")); 
	
	   // Test basic URLs with hostname
	   System.out.println("Basic URL Test");
	   urlVal = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
	   assertTrue(urlVal.isValid("https://www.google.com"));
	   assertFalse(urlVal.isValid("https://www.google.&(@*$A@(')"));
	   assertTrue(urlVal.isValid("https://www.amazon.com"));
	   assertFalse(urlVal.isValid("http://www.amazon.rocks"));	//Should be true, possible bug
	   assertTrue(urlVal.isValid("http://amazon.com"));
	   assertTrue(urlVal.isValid("http://espn.go.com"));
	   assertTrue(urlVal.isValid("http://eecs.oregonstate.edu"));
	   assertTrue(urlVal.isValid("http://eecs.oregonstate.edu/students"));
	   assertTrue(urlVal.isValid("http://eecs.oregonstate.edu/current%20students"));
	   assertTrue(urlVal.isValid("http://eecs.oregonstate.edu/index.html"));
	   assertTrue(urlVal.isValid("http://eecs.oregonstate.edu/index.html#calendar"));
	   
	   // Test URL with query
	   System.out.println("URL With Query Test");
	   urlVal = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
	   assertFalse(urlVal.isValid("http://www.foo.gov/somefolder?name=bar"));				//Should be true, possible bug
	   assertFalse(urlVal.isValid("http://www.foo.gov/somefolder?name=bar&name2=bar2"));	//Should be true, possible bug
	   assertFalse(urlVal.isValid("http://www.foo.gov/somefolder?name=bar;name2=bar2"));  	//Should be true, possible bug
	   assertFalse(urlVal.isValid("http://www.foo.gov/somefolder?1=2&2=3"));			  	//Should be true, possible bug
	   assertFalse(urlVal.isValid("http://foo.gov/somefolder?name=bar+name2=bar2"));
	   assertFalse(urlVal.isValid("http://foo.gov/somefolder?name=bar,name2=bar2"));
	   assertFalse(urlVal.isValid("http://foo.gov/somefolder?name=bar?name2=bar2"));
	   assertFalse(urlVal.isValid("http://foo.gov/somefolder??name=bar&name2=bar2"));
	   
	   // Test URL with ports
	   System.out.println("URL With Port Test");
	   urlVal = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
	   assertTrue(urlVal.isValid("http://www.apple.com:80"));
	   assertFalse(urlVal.isValid("http://www.apple.com:35912"));	//Should be true, possible bug
	   assertFalse(urlVal.isValid("http://www.apple.com:ABCD"));
	   assertFalse(urlVal.isValid("http://www.apple.com:?"));
	   assertFalse(urlVal.isValid("http://www.apple.com:/somefolder"));

	   // Test URL with username/password
	   System.out.println("URL With Authentication Token Test");
	   urlVal = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
	   assertFalse(urlVal.isValid("http://user:password@mail.google.com"));

	   // Test URL with IP address
	   System.out.println("URL With IP Address Test");
	   urlVal = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
	   assertTrue(urlVal.isValid("http://5.5.5.5"));
	   assertTrue(urlVal.isValid("http://5.5.5.5:80"));
	   assertFalse(urlVal.isValid("http://5.5.5.5:13000"));						//Should be true, possible bug
	   assertTrue(urlVal.isValid("http://5.5.5.256"));							//Should be false, possible bug
	   assertTrue(urlVal.isValid("http://0.0.0.0"));
	   assertTrue(urlVal.isValid("http://5.5.5.5/folder"));
	   assertTrue(urlVal.isValid("http://5.5.5.5:80/folder"));
	   assertFalse(urlVal.isValid("http://5.5.5.5/folder?name=foo"));			//Should be true, possible bug
	   assertFalse(urlVal.isValid("http://5.5.5.5/folder?name=foo&name2=bar"));	//Should be true, possible bug
	   
	   // Test FTP scheme
	   System.out.println("FTP Scheme Test");
	   urlVal = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
	   assertFalse(urlVal.isValid("ftp://user1:pass@foo.com"));				//Should be true, possible bug
	   assertFalse(urlVal.isValid("ftp://user1@foo.com"));					//Should be true, possible bug
	   assertFalse(urlVal.isValid("ftp://@foo.com"));						//Should be true, possible bug
	   assertTrue(urlVal.isValid("ftp://foo.com"));
	   assertTrue(urlVal.isValid("ftp://foo.com/folder1/folder2/folder3"));
	   assertFalse(urlVal.isValid("ftp://foo.com?name=bar"));
	   assertTrue(urlVal.isValid("ftp://foo.com/folder;type=a"));
	   assertTrue(urlVal.isValid("ftp://foo.com/folder;type=z"));			//Should be false, possible bug
	   assertTrue(urlVal.isValid("ftp://foo.com:20/folder"));				
	   assertFalse(urlVal.isValid("ftp://foo.com:20000/folder"));			//Should be true, possible bug
	   
   }
   
   
   /************************************************
    *       PART 2: INPUT DOMAIN PARTITIONING
    ************************************************/
   
   public void testYourFirstPartition(){
	   System.out.println("Testing partition: full URL pattern");
	   
	   //Test full URLs based on ASCII_PATTERN
	   /*Notes: According to RFC3986 the following ASCII characters are allowed in a URL: 
	    *   Reserved characters - ! # $ % & ' ( ) * + , / : ; = ? @ [ ] 
	    *   Unreserved characters - all alpha, all digits, and - . _ ~
	    *   No other characters are allowed unless they are encoded using %
	    *   Authority further restricts the hostname to alphanumeric with . and - only
	    */
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   //valid, unreserved chars (in authority)
	   String url = "http://www.123-abc.456-xyz.com";	
	   assertTrue(urlVal.isValid(url));
	   //invalid, unreserved chars (in authority)
	   url = "http://www.123_abc~456_xyz.com";	
	   assertFalse(urlVal.isValid(url));
	   //valid, unreserved chars (in path)
	   url = "http://www.oregonstate.edu/~user_first.last-name";	
	   assertTrue(urlVal.isValid(url));
	   //invalid chars
	   url = "http://www<google>com";	
	   assertFalse(urlVal.isValid(url));
	   //invalid chars
	   url = "http://www google com";
	   assertFalse(urlVal.isValid(url));
	   //invalid non-printable chars, 8=backspace, 27=escape
	   url = "http://www" + (char)8 + "google" + (char)27 + "com";	
	   assertFalse(urlVal.isValid(url));
	   //invalid extended ASCII chars (cafe with accent)
	   url = "http://www.caf" + (char)130 + ".com";	
	   assertFalse(urlVal.isValid(url));
	   //encoded characters (in authority)
	   url = "http://www.my%20company.com";	
	   assertFalse(urlVal.isValid(url));
	   //encoded characters (in path), %20=space
	   url = "http://www.mycompany.com/my%20file";	
	   assertTrue(urlVal.isValid(url));
	   //encoded characters (in path), %E9=accented e
	   url = "http://www.mycompany.com/caf%E9";	
	   assertTrue(urlVal.isValid(url));
   	   
	   
	   //TODO: Test full URLs based on URL_PATTERN
	  
   }
   
   public void testYourSecondPartition(){
	   System.out.println("Testing partition: schemes");
	   
	   //Test valid and invalid URL schemes
	   System.out.println("Testing partition: schemes > standard");
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   for (int i = 0; i < testSchemas.length; i++){ 
		   ResultPair url = URLmaker(i,0,0,0,0);
		   assertEquals(url.valid, urlVal.isValid(url.item));
	   }
	   
	   //Test custom schemes supplied in isValid constructor
	   System.out.println("Testing partition: schemes > custom");
	   String[] mySchemes = {"foo", "boo", "moo"};
	   UrlValidator customUrlVal = new UrlValidator(mySchemes);
	   assertTrue(customUrlVal.isValid("foo://www.google.com"));
	   assertTrue(customUrlVal.isValid("boo://www.google.com"));
	   assertTrue(customUrlVal.isValid("moo://www.google.com"));
	   assertFalse(customUrlVal.isValid("zoo://www.google.com"));
	   assertFalse(customUrlVal.isValid("http://www.google.com"));
	   assertFalse(customUrlVal.isValid("https://www.google.com"));
	   assertFalse(customUrlVal.isValid("ftp://www.google.com"));
	   
   }
   
   public void testYourThirdPartition(){
	   System.out.println("Testing partition: authorities");
	   
	   //Test valid and invalid URL hosts
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   System.out.println("Testing partition: authorities > hosts");
	   for (int i = 0; i < testHosts.length; i++){ 
		   ResultPair url = URLmaker(0,i,0,0,0);
		   assertEquals(url.valid, urlVal.isValid(url.item));
	   }
	   
	   //Test valid and invalid URL ports
	   System.out.println("Testing partition: authorities > ports");
	   for (int i = 0; i < testPorts.length; i++){ 
		   ResultPair url = URLmaker(0,0,i,0,0);
		   assertEquals(url.valid, urlVal.isValid(url.item));
	   }
	   
	   //Test no authority when using file: scheme
	   System.out.println("Testing partition: authorities > none with file: scheme");
	   assertTrue(urlVal.isValid("file:///myfile.txt"));
	   assertTrue(urlVal.isValid("file:///folder/myfile.txt"));
	   assertFalse(urlVal.isValid("file://localhost/myfile.txt"));
	   	   	   
	   //Test custom validator
	   //Regex: hostname = 1-5 digits, port = 1-3 letters, separated by :
	   System.out.println("Testing partition: authorities > custom");
	   RegexValidator myAuthorityRegex = new RegexValidator("^[0-9]{1,5}:[a-zA-z]{1,3}$");
	   UrlValidator customUrlVal = new UrlValidator(myAuthorityRegex, UrlValidator.ALLOW_ALL_SCHEMES);
	   assertTrue(customUrlVal.isValid("http://123:abc"));
	   assertTrue(customUrlVal.isValid("http://12345:a"));
	   assertFalse(customUrlVal.isValid("http://123456:a"));
	   assertFalse(customUrlVal.isValid("http://123:abcd"));
	   assertFalse(customUrlVal.isValid("http://123:80"));
	   assertFalse(customUrlVal.isValid("http://abc:a"));
	   assertTrue(customUrlVal.isValid("http://www.google.com"));	//should be false
	   	   
   }
   
   public void testYourFourthPartition(){
	   //Test URL Path
	   System.out.println("Testing partition: paths");
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   for (int i = 0; i < testPaths.length; i++){ 
		   ResultPair url = URLmaker(0,0,0,i,0);
		   assertEquals(url.valid, urlVal.isValid(url.item));
	   }
   }
   
   public void testYourFifthPartition(){
	   //Test URL Query
	   System.out.println("Testing partition: queries");
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   for (int i = 0; i < testQueries.length; i++){ 
		   ResultPair url = URLmaker(0,0,0,0,i);
		   assertEquals(url.valid, urlVal.isValid(url.item));
	   }
   }
   
   
   /************************************************
    *       PART 3: PROGRAMMING-BASED TESTING
    ************************************************/
   
   public void testIsValid()
   {
	   // Exercise isValid using random testing
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   Random ran = new Random();

	   for(int i = 0;i<10000;i++)
	   {	   
			int schemaIndex = ran.nextInt(testSchemas.length);
			int hostIndex = ran.nextInt(testHosts.length);
			int portIndex = ran.nextInt(testPorts.length);
			int pathIndex = ran.nextInt(testPaths.length);
			int queryIndex = ran.nextInt(testQueries.length);
			ResultPair url = URLmaker(schemaIndex, hostIndex, portIndex, pathIndex, queryIndex);
			System.out.println(String.format("Generated url: %s. is valid: %s", url.item, url.valid));
			assertEquals(url.valid, urlVal.isValid(url.item));
		}
   }
   
   public void testAnyOtherUnitTest()
   {
	   
   } 
   
   
   /************************************************
    *       HELPER FUNCTIONS AND RESULT PAIRS
    ************************************************/
   
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
		   new ResultPair("bob://", true),	//should be false
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
		   new ResultPair("256.0.0.1", true),	//Should be false
		   new ResultPair("127", false)
	};
	//Port Numbers
	ResultPair[] testPorts = {
		   new ResultPair("", true),
		   new ResultPair(":80", true),
		   new ResultPair(":8080", false),	//Should be true
		   new ResultPair(":65535", false),   //Should be true
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
		   new ResultPair("?lvalue=rvalue", false),	//Should be true
		   new ResultPair("?lvalue=rvalue&lvalue2=rvalue2", false),	//Should be true
		   new ResultPair("?lvalue=rvalue:lvalue2=rvalue2", false),
		   new ResultPair("?=rvalueonly", false) 
	};   
   

}
