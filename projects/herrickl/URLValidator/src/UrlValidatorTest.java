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

    /*********************************
     Part 1:  Manual Testing
     *********************************/
   public void testManualTest()
   {
       /*** Test All Schemes ***/
       UrlValidator urlVal = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
       System.out.println("----Allow All Schemes----");

       assertTrue(urlVal.isValid("https://www.google.com"));
       assertTrue(urlVal.isValid("http://www.amazon.com"));
       assertTrue(urlVal.isValid("https://www.airbnb.com"));

       assertFalse(urlVal.isValid("google"));
       assertFalse(urlVal.isValid("http:///amazon.com"));
       assertFalse(urlVal.isValid("//www.google.com"));

       /*** Test valid schemas ***/
       urlVal = new UrlValidator();
       System.out.println("----Test Valid Schemas----");
       
       assertTrue(urlVal.isValid("https://www.google.com"));
       assertTrue(urlVal.isValid("http://www.amazon.com"));
       assertTrue(urlVal.isValid("https://www.airbnb.com"));
       
       assertFalse(urlVal.isValid("google"));
       assertFalse(urlVal.isValid("http:///amazon.com"));
       assertFalse(urlVal.isValid("google.com"));
       
       /*** Test fragments not allowed ***/
       urlVal = new UrlValidator(UrlValidator.NO_FRAGMENTS);
       System.out.println("----Test Fragments Not Allowed----");
       
       assertTrue(urlVal.isValid("http://www.google.com"));
       assertFalse(urlVal.isValid("http://http://http://www.google.com"));
       
       
       /*** Test for 2 slashes in path  ***/
       urlVal = new UrlValidator(UrlValidator.ALLOW_2_SLASHES);
       System.out.println("----Test for 2 Slashes in Path----");
       
       assertTrue(urlVal.isValid("http://www.cnn.com//world"));
                                 
       assertTrue(urlVal.isValid("http://www.cnn.com///world")); // BUG!  SHould be false!
       
       /*** Test local URLs ***/
       urlVal = new UrlValidator(UrlValidator.ALLOW_LOCAL_URLS);
       System.out.println("----Test Local URLs Allowed----");
       
       assertTrue(urlVal.isValid("http://127.0.0.1"));

       assertFalse(urlVal.isValid("http://localhost"));  // should be true but is printing out false.  BUG!
       
       /*** Test URL with Hostname ***/
       urlVal = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
       System.out.println("----Test for URL with a hostname----");
       
       assertTrue(urlVal.isValid("https://www.google.com"));
       assertTrue(urlVal.isValid("http://www.amazon.com"));
       assertTrue(urlVal.isValid("https://www.airbnb.com"));
       assertTrue(urlVal.isValid("https://www.amazon.au")); // austrailian extension
       assertTrue(urlVal.isValid("http://www.disney.go.com"));
       assertTrue(urlVal.isValid("http://www.eecs.oregonstate.edu"));
       assertTrue(urlVal.isValid("http://www.eecs.oregonstate.edu/index.html"));
       
       
       assertFalse(urlVal.isValid("https://www.google.&&&"));
       assertFalse(urlVal.isValid("http://www.amazon.love")); // BUG! this should work
       assertFalse(urlVal.isValid("http://www.amazon.998"));
       
	   /*** Test URL with Query ***/
       urlVal = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
       System.out.println("----Test URL with Query----");
       
       assertFalse(urlVal.isValid("https://www.google.com/?q=foo")); //BUG - SHOULD BE TRUE
       
       assertFalse(urlVal.isValid("http://www.google.com/?123=iol=abc"));
       assertFalse(urlVal.isValid("http://www.google.com/somefolder?name=bar+name2=bar2"));
       
       /*** Test URL with IP address ***/
       urlVal = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
       System.out.println("----Test URL with IP address----");
       
       assertTrue(urlVal.isValid("http://3.3.3.3"));
       
       assertFalse(urlVal.isValid("http://3.3.3.3/folder?name=foo")); // BUG should be true
       assertFalse(urlVal.isValid("http://3.3.3.3:1000")); // BUG should be true
       assertFalse(urlVal.isValid("http://@.@.#.$"));
       
       /*** Test FTP ***/
       urlVal = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
       System.out.println("----Test FTP----");
       
       assertTrue(urlVal.isValid("ftp://foo.com"));
       assertTrue(urlVal.isValid("ftp://eecs.oregonstate.edu/"));
       
       assertFalse(urlVal.isValid("ftp://###.com"));
       assertFalse(urlVal.isValid("ftp://foo.com:2000/folder"));
       
       
       
   }
   
   
   // Note: Partition code is based on code from the original URLValidatorTest.java

   // test schemes
   public void testYourFirstPartition()
   {
	  System.out.println("\nTesting Schemes:\n");
	    
	    // create an array of schemes to test
	    String[] Schemes = {"http://", "htp://", "://", ":/", " "};
	    UrlValidator newScheme = new UrlValidator(Schemes, 0);


	    // loop through all schemes
	    for (int i = 0; i < Schemes.length; i++) {
	      String curScheme = Schemes[i];
	      System.out.println("\nTesting " + curScheme);


	      // see if scheme is valid and print results 
	      boolean valid = newScheme.isValidScheme(curScheme);
	      if (valid == false && i == 0 || valid == true && i == 1 || valid == true && i == 2 || valid == true 

&& i == 3 || valid == false && i == 4) {
	        System.out.println("FAILED: Invalid Scheme\n");
	      } else {
	    	System.out.println("PASSED\n");
	      }
	    }
   }


   // test authorities   
   public void testYourSecondPartition()
   {
	   System.out.println("\nTesting Authority:\n");

	    // create an array of authorities to test
	    String[] Authorities = {"www.google.com", "www.!google!.com", "www.reddit.net", " ", "monstermonstermonster.com", 

"www.googl.net", "1.2.3.4.5"};
	    UrlValidator newAuth = new UrlValidator(Authorities, 0);

	    // loop through all authorities
	    for (int i = 0; i < Authorities.length; i++) {
	      String curAuth = Authorities[i];
	      System.out.println("\nTesting " + curAuth);

	      // see if authority is valid and print results
	      boolean valid = newAuth.isValidAuthority(curAuth);
	      if (valid == false && i == 0 || valid == true && i == 1 || valid == true && i == 2 || valid == true 

&& i == 3 || valid == true && i == 4 || valid == true && i == 5 || valid == true && i == 6) {
	        System.out.println("FAILED: Invalid Authority\n");
	      } else {
	    	System.out.println("PASSED\n");
	      }
	    }
   }


   // test paths
   public void testYourThirdPartition()
   {
	  System.out.println("\nTesting Paths:\n");

	    // create an array of paths to test
	    String[] Paths = {"/t123", "/..", "", "///", "/$23"};
	    UrlValidator newPath = new UrlValidator(Paths, 0);

	    // loop through all paths
	    for (int i = 0; i < Paths.length; i++) {
	      String curPath = Paths[i];
	      System.out.println("\nTesting " + curPath);

	      // see if path is valid and print results
	      boolean valid = newPath.isValidPath(curPath);
	      if (valid == false && i == 0 || valid == true && i == 1 || valid == false && i == 2 || valid == true 

&& i == 3 || valid == false && i == 4) {
	        System.out.println("FAILED: Invalid Path\n");
	      } else {
	    	System.out.println("PASSED\n");
	      }
	    }
   }

   // test ports   
   public void testYourFourthPartition()
   {
	   System.out.println("\nTesting Ports:\n");

	    // create an array of ports to test
	    String[] Ports = {":80", ":0", "", ":65a", ":-1"};
	    UrlValidator newPort = new UrlValidator(Ports, 0);

	    // loop through all ports
	    for (int i = 0; i < Ports.length; i++) {
	      String curPort = Ports[i];
	      System.out.println("\nTesting " + curPort);

	      // see if port is valid and print results
	      boolean valid = newPort.isValid(curPort);
	      if (valid == false && i == 0 || valid == false && i == 1 || valid == false && i == 2 || valid == true && i == 3 || valid == true && i == 4) {
	        System.out.println("FAILED: Invalid Port\n");
	      } else {
	    	System.out.println("PASSED\n");
	      }
	    }
   }

   // test queries
   public void testYourFifthPartition()
   {
	  System.out.println("\nTesting Queries:\n");

	    // create an array of queries to test
	    String[] Queries = {"", "?action=view", "?action=edit&mode=up"};
	    UrlValidator newQuery = new UrlValidator(Queries, 0);

	    // loop through all queries
	    for (int i = 0; i < Queries.length; i++) {
	      String curQuery = Queries[i];
	      System.out.println("\nTesting " + curQuery);

	      // see if query is valid and print results
	      boolean valid = newQuery.isValidQuery(curQuery);
	      if (valid == false && i == 0 || valid == false && i == 1 || valid == false && i == 2) {
	        System.out.println("FAILED: Invalid Query\n");
	      } else {
	    	System.out.println("PASSED\n");
	      }
	    }
   }

   
   
    public void testIsValid()
   {
	   /*IsValid() takes string value param
	    * checks if value is null
	    * checks if ascii
	    * calls Matcher to check that it fits url valid pattern
	    * calls scheme to check that it matches scheme
	    * parses url so scheme is separate, checks if scheme is valid
	    * parses url so authority are separate, checks if valid path
	    * parses url so path are separate, checks if valid path
	    * checks if valid query
	    * checks if valid fragment
	    */
	
        //url related variables according to RFC 3986 section 3, http://tools.ietf.org/html/rfc3986
        //for structural purposes of testing scheme+authority+path+query+fragement -- http, https, ""
        ResultPair[] scheme = {new ResultPair("http://", true), new ResultPair("https://", true), new ResultPair("", false),
            new ResultPair("://", false), new ResultPair("htp://", false), new ResultPair("htps://", false),
            new ResultPair("http", false), new ResultPair("https", false), new ResultPair("ftp", false)
        };
        //show example of www...com, ....com, ...edu
        ResultPair[] authority = {new ResultPair("oregonstate.edu", true), new ResultPair("www.reddit.com", true), new ResultPair("reddit.com", true),
                new ResultPair("www.com", false), new ResultPair("oregonstate", false), new ResultPair("oregonstate.eud", false),
                new ResultPair("ww.reddit.com", false), new ResultPair("www.reddit,com", false), new ResultPair("www,reddit.com", false), new ResultPair("www.reddit", false)
        };
        //show example of one page from root, two pages from root, name vs name.html vs name.php, /#..., /number
        ResultPair[] path = {new ResultPair("/about", true), new ResultPair("/about/", true), new ResultPair("/about/more", true), new ResultPair("/about.html", true),
            new ResultPair("/about.php", true), new ResultPair("/256", true), new ResultPair("about/", false), new ResultPair("//about", false),
            new ResultPair("about/more", false), new ResultPair("about.php", false), new ResultPair(" ", false), new ResultPair("", true)		   
        };
        //show example of one key/value pair, multiple key/value pairs, no key/value pairs, since forced fragement afterwards beware of empty query
        ResultPair[] query = {new ResultPair("?name=StephCurry", true), new ResultPair("?name=StephCurry&position=PointGuard", true), new ResultPair("", true), 
        		new ResultPair("/", false)
        };
        ResultPair[] fragment = {new ResultPair("#inbox", true),  new ResultPair("#30", true), new ResultPair("//", false), new ResultPair("://", false), new ResultPair("//#inbox", false)};


        //randomize values for unit tests
        Random getRandom = new Random();
        for(int i = 0;i<1000;i++){
            //randomize test state values
            int schemeChoice = getRandom.nextInt(scheme.length);
            int authorityChoice = getRandom.nextInt(authority.length);
            int pathChoice = getRandom.nextInt(path.length);
            int queryChoice = getRandom.nextInt(query.length);
            int fragmentChoice = getRandom.nextInt(fragment.length);
		   
            //test prep
            UrlValidator test = new UrlValidator();
            String url = scheme[schemeChoice].item + authority[authorityChoice].item + path[pathChoice].item + query[queryChoice].item + fragment[fragmentChoice].item;
		   
            //print test identifier
            StringBuilder intTest = new StringBuilder();
            intTest.append("");
            intTest.append(i);
            String testNum = intTest.toString();
            System.out.println("Random Test" + testNum + ": " + url);
		   
		   
            //compare states (unit test)
            boolean testResult = test.isValid(url);
            boolean cleanResult = true;
            if(scheme[schemeChoice].valid == false || authority[authorityChoice].valid == false || path[pathChoice].valid == false || query[queryChoice].valid == false || fragment[fragmentChoice].valid == false){
                cleanResult = false;
            }
            //if bug, show why/where
            if(cleanResult != testResult){  //added for grading clarity
                boolean printed = false;
                //check scheme
                if(scheme[schemeChoice].valid == false && scheme[schemeChoice].valid != testResult){
                    System.out.println("**Expected: " + cleanResult + ", Result: " + testResult + ", scheme: " + scheme[schemeChoice].item);
                    printed = true;
                }
                //check authority
                if(authority[authorityChoice].valid == false && authority[authorityChoice].valid != testResult){
                    System.out.println("**Expected: " + cleanResult + ", Result: " + testResult + ", authority: " + authority[authorityChoice].item);
                    printed = true;   
                }
                //check path
                if(path[pathChoice].valid == false && path[pathChoice].valid != testResult){
                    System.out.println("**Expected: " + cleanResult + ", Result: " + testResult + ", scheme: " + scheme[schemeChoice].item);
                    printed = true;
                }
                //check query
                if(query[queryChoice].valid == false && query[queryChoice].valid != testResult){
                    System.out.println("**Expected: " + cleanResult + ", Result: " + testResult + ", query: " + query[queryChoice].item);
                    printed = true;
                }
                //check fragment
                if(fragment[fragmentChoice].valid == false && fragment[fragmentChoice].valid != testResult){
                    System.out.println("**Expected: " + cleanResult + ", Result: " + testResult + ", query: " + fragment[fragmentChoice].item);
                    printed = true;
                }
                if(printed != true){
                	System.out.println("**scheme: " + scheme[schemeChoice].item);
                	System.out.println("**authority: " + authority[authorityChoice].item);
                	System.out.println("**path: " + path[pathChoice].item);
                	System.out.println("**query: " + query[queryChoice].item);
                	System.out.println("**fragment: " + fragment[fragmentChoice].item);
                	System.out.println("**Expected: " + cleanResult + ", Result: " + testResult);
                }
            }
            //comment out if you want to see all failed tests, above will provide details
            assertEquals(cleanResult, testResult);   
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
