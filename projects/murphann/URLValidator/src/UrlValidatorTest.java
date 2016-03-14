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

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;




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

   public List<ResultPair> createResultPairs(String filename) throws IOException{
	  List<ResultPair> urls = new ArrayList<ResultPair>();
	   BufferedReader br = null;
	   String line = "";
	   String splitBy = ",";
	   boolean valid = false;
	   try {
		   br = new BufferedReader(new FileReader(filename));
		   while ((line = br.readLine()) != null){
			   String[] url = line.split(splitBy);
			   if (url[1].equals("valid")){
				   valid = true;
			   }
			   else {
				   valid = false;
			   }
			   urls.add(new ResultPair(url[0],valid));
			   
		   }
	   } finally {
		   if (br != null){
				br.close();	
		   }
	   }
	   return urls;
   }
   public void printManualTests() throws IOException{
	   List<ResultPair> urls;
	   urls = createResultPairs(System.getProperty("user.dir") + "/src/urls.csv");
	   System.out.println("---------------------");
	   System.out.println("File Result Pairs");
	   System.out.println("---------------------");
	   for(ResultPair url : urls){
		   System.out.println(url.item + "," + url.valid);
	   }
	   System.out.println("---------------------");
   }
   public List<String> getStuff(String filename) throws IOException {
	   List<String> scheme = new ArrayList<String>();
	   BufferedReader br = null;
	   String line = "";
	   try {
		   br = new BufferedReader(new FileReader(filename));
		   while ((line = br.readLine()) != null){
			   scheme.add(line);
			   
		   }
	   } finally {
		   if (br != null){
				br.close();	
		   }
	   }
	   return scheme;
	   
	   
   }
   public void testManualTest() throws IOException
   {
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   //System.out.println(urlVal.isValid("http://www.amazon.com"));
        
        System.out.println("Beginning manual tests\n");
        List<ResultPair> urls = createResultPairs(System.getProperty("user.dir") + "/src/urls.csv");
        for(ResultPair url : urls){
           if (urlVal.isValid(url.item) == true && url.valid == true)
           {
               System.out.println("PASS: " + url.valid + " -- " + url.item);
           }
           else if (urlVal.isValid(url.item) == false && url.valid == false)
           {
        	   System.out.println("PASS: " + url.valid + " -- " + url.item);
           }
           else {
        	   System.out.println("-> FAIL: " + url.valid + " -- " + url.item);
           }
 	   }
        /*----- VALID TEST CASES -----*/
        System.out.println("Valid URLs:\n");
        ResultPair[] validUrls = {new ResultPair("www.google.com", true),
                                  new ResultPair("http://www.google.com", true),
                                  new ResultPair("google.com", true),
                                  new ResultPair("http://www.google.com/", true),
                                  new ResultPair("https://google.com/", true),
                                  new ResultPair("http://www.google.com:65636", true),
                                  new ResultPair("h3t://www.google.com/", true),
                                  new ResultPair("http://google.com/test1/file", true)};

        int i;
        int numTests = validUrls.length;
        for (i = 0; i < numTests; i++)
        {
            // Test passes (EXPECTED)
            if (urlVal.isValid(validUrls[i].item) == true)
            {
                System.out.println(validUrls[i].item + "passed\n");
            }
            // Test fails (BUG!)
            else if (urlVal.isValid(validUrls[i].item) == false)
            {
                System.out.println("ERROR: " + validUrls[i].item + "failed\n");
            }
        }
	   
        /*----- INVALID TEST CASES -----*/
        System.out.println("Invalid URLs:\n");
        ResultPair[] invalidUrls = {new ResultPair("httpgoogle", false),
                                    new ResultPair("www.google.com.www", false),
                                    new ResultPair("file:///c:\\", false),
                                    new ResultPair("google.com//", false),
                                    new ResultPair("http:/google.com", false),
                                    new ResultPair("http://google.com:-1", false),
                                    new ResultPair("http://google.com/test1//file", false),
                                    new ResultPair("", false)};

        numTests = invalidUrls.length;
        for (i = 0; i < numTests; i++)
        {
            // Test passes (BUG!)
            if (urlVal.isValid(invalidUrls[i].item) == true)
            {
                System.out.println("ERROR: " + invalidUrls[i].item + "passed\n");
            }
            // Test fails (EXPECTED)
            else if (urlVal.isValid(invalidUrls[i].item) == false)
            {
                System.out.println(invalidUrls[i].item + "failed\n");
            }
        }
	   
   }
   
/* Partition Setup:
 * The partitions are based on the different components of a URL, where an equivalence class is defined on valid and invalid substrings. For example, a generic URL has the form:
 * scheme + authority + port + path + query
 * This function returns a string with the desired invalid (0) and valid (1)components. */
    private String partitionString(int scheme, int authority,
        int port, int path, int query)
    {
    	//List<String> schemes = getStuff(System.getProperty("user.dir") + "/src/paths.csv");
        String[] schemes = {"http:/", "http://"};
        String[] authorities = {"", "www.google.com"};
        String[] ports = {":-1", ":65535"};
        String[] paths = {"/..", "/test1"};
        String[] queries = {"action=view", "?action=view"};

        String url = schemes[scheme] + authorities[authority] + ports[port] + paths[path] + queries[query];

        return url; 
    }

/* Partition1:
 * invalid scheme + valid authority + valid port + valid path + valid query
 */
    public void testYourFirstPartition()
    {
    	UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        System.out.println("Testing first partition:\n");

        String url = partitionString(0, 1, 1, 1, 1);
        boolean valid = urlVal.isValid(url);
        if (valid)
        {
            System.out.println("ERROR: " + url + " passed with invalid scheme.\n");
        }
        else
        {
            System.out.println(url + " failed with invalid scheme.\n");
        }
    }
   
/* Partition2:
 * valid scheme + invalid authority + valid port + valid path + valid query
 */
    public void testYourSecondPartition()
    {
    	UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        System.out.println("Testing second partition:\n");

        String url = partitionString(1, 0, 1, 1, 1);
        boolean valid = urlVal.isValid(url);
        if (valid)
        {
            System.out.println("ERROR: " + url + " passed with invalid authority.\n");
        }
        else
        {
            System.out.println(url + " failed with invalid authority.\n");
        }
    }
   
/* Partition3:
 * valid scheme + invalid authority + valid port + valid path + valid query
 */
    public void testYourThirdPartition()
    {
    	UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        System.out.println("Testing third partition:\n");

        String url = partitionString(1, 1, 0, 1, 1);
        boolean valid = urlVal.isValid(url);
        if (valid)
        {
            System.out.println("ERROR: " + url + " passed with invalid port.\n");
        }
        else
        {
            System.out.println(url + " failed with invalid port.\n");
        }
    }
   
/* Partition4:
 * valid scheme + invalid authority + valid port + valid path + valid query
 */
    public void testYourFourthPartition()
    {
    	UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        System.out.println("Testing fourth partition:\n");

        String url = partitionString(1, 1, 1, 0, 1);
        boolean valid = urlVal.isValid(url);
        if (valid)
        {
            System.out.println("ERROR: " + url + " passed with invalid path.\n");
        }
        else
        {
            System.out.println(url + " failed with invalid path.\n");
        }
    }
   
/* Partition5:
 * valid scheme + invalid authority + valid port + valid path + valid query
 */
    public void testYourFifthPartition()
    {
    	UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        System.out.println("Testing fifth partition:\n");

        String url = partitionString(1, 1, 1, 1, 0);
        boolean valid = urlVal.isValid(url);
        if (valid)
        {
            System.out.println("ERROR: " + url + " passed with invalid query.\n");
        }
        else
        {
            System.out.println(url + " failed with invalid query.\n");
        }
    }
   
/* Partition6: (no optional components)
 * (no scheme) + valid authority + (no port) + (no path) + (no query)
 */
    public void testYourSixthPartition()
    {
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        System.out.println("Testing fifth partition:\n");

        String url = partitionString(1, 1, 1, 1, 0);
        boolean valid = urlVal.isValid(url);
        if (valid)
        {
            System.out.println(url + " passed with valid authority and no optional components.\n");
        }
        else
        {
            System.out.println("ERROR: " + url + " failed with valid authority and no optional components.\n");
        }
    }

// For this test, consider different *specific* tests to isValidScheme, isValidAuthority, isValidPath, isValidQuery, and isValidFragment
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
    
    /* Test different permutations of valid URL components. */
    public void permTest() {
        String url;
        String[] schemes = {"http://", "h3t://", ""};
        String[] authorities = {"google.com", "www.amazon.com", "255.255.255.255"};
        String[] ports = {"", ":80", ":65636"};
        String[] paths = {"", "/test1", "/test1/file"};
        String[] queries = {"", "?action=view"};
        
        for (s = 0; s < schemes.length; s++) {
            for (a = 0; a < authorities.length; a++) {
                for (po = 0; po < ports.length; po++) {
                    for (pa = 0; pa < paths.length; pa++) {
                        for (q = 0; q < queries.length; q++) {
                            url = schemes[s] + authorities[a] + ports[po] + paths[pa] + queries[q];
                            if (isValid(url)) {
                                System.out.println("OK: " url + " passed.\n");
                            }
                            else {
                                System.out.println("ERROR: " + url + " failed.\n");
                            }
                        }
                    }
                }
            }
        }
    }

/* Some very basic unit tests to tease out the bugs from isValid() method */
    public void testIsValidScheme() {
        // Test a valid scheme
        String validScheme = "http://";
        if (!isValidScheme(validScheme)) {
            System.out.println("ERROR: " + validScheme + " failed with valid scheme.\n");
        }
        else {
            System.out.println(validScheme + " passed with valid scheme.\n");
        }
        
        // Test an invalid scheme
        String invalidScheme = "3ht://";
        if (isValidScheme(invalidScheme) {
            System.out.println("ERROR: " + invalidScheme + " passed with invalid scheme.\n");
        }
        else {
            System.out.println(invalidScheme + " failed with invalid scheme.\n");
        }
    }

    public void testIsValidAuthority() {
        // Test a valid authority
        String validAuthority = "www.google.com:65535";
        if (!isValidAuthority(validAuthority)) {
            System.out.println("ERROR: " + validAuthority + " failed with valid authority.\n");
        }
        else {
            System.out.println(validAuthority + " passed with valid authority.\n");
        }
        
        // Test an invalid authority
        String invalidAuthority = "256.256.256.256";
        if (isValidAuthority(invalidAuthority) {
            System.out.println("ERROR: " + invalidAuthority + " passed with invalid authority.\n");
        }
        else {
            System.out.println(invalidScheme + " failed with invalid authority.\n");
        }
    }

    public void testIsValidPath() {
        // Test a valid path
        String validPath = "/test1";
        if (!isValidPath(validPath)) {
            System.out.println("ERROR: " + validPath + " failed with valid path.\n");
        }
        else {
            System.out.println(validPath + " passed with valid path.\n");
        }
        
        // Test an invalid path
        String invalidPath = "/..//file";
        if (isValidPath(invalidPath) {
            System.out.println("ERROR: " + invalidPath + " passed with invalid path.\n");
        }
        else {
            System.out.println(invalidPath + " failed with invalid path.\n");
        }
    }

    public void testIsValidQuery() {
        // Test a valid query
        String validQuery = "?action=view";
        if (!isValidQuery(validQuery)) {
            System.out.println("ERROR: " + validQuery + " failed with valid query.\n");
        }
        else {
            System.out.println(validQuery + " passed with valid query.\n");
        }
        
        // Test an invalid query
        String invalidQuery = "action=view";
        if (isValidQuery(invalidQuery) {
            System.out.println("ERROR: " + invalidQuery + " passed with invalid query.\n");
        }
        else {
            System.out.println(invalidQuery + " failed with invalid query.\n");
        }
    }

}
