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
   private boolean printIndex = false; //print index that indicates current scheme,host,port,path, query test were using.

   public UrlValidatorTest(String testName) {
      super(testName);
   }

   public void testManualTest(String url) {
	   UrlValidator urlVal = new UrlValidator();
	   System.out.println(urlVal.isValid(url));
   }

   //test schemes with bare minimum
   public void testYourFirstPartition()
   {
        System.out.println("\n\nTesting Schemes Partition");
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

        String validPost = "www.google.com";

        String goodSch = "http://" + validPost;
        String badSch = "http:" + validPost;
        String noSch = "" + validPost;

        System.out.println("\nGood scheme: " + goodSch);
        if (!urlVal.isValid(goodSch))
            System.out.println("URL is valid but failed");
        else
        	System.out.println("Url worked");

        System.out.println("\nBad scheme: " + badSch);
        if (urlVal.isValid(badSch))
            System.out.println("URL is invalid but passed");
        else
        	System.out.println("Url worked");

        System.out.println("\nNo scheme: " + noSch);
        if (urlVal.isValid(noSch))
            System.out.println("URL is invalid but passed");
        else
        	System.out.println("Url worked");
   }

   //test authority with bare minimum
   public void testYourSecondPartition(){
        System.out.println("\n\nTesting Authority Partition");
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

        String goodAut = "http://www.google.com";
        String badAut = "http://1.2.3";
        String noAut = "http://";

        System.out.println("\nGood authority: " + goodAut);
        if (!urlVal.isValid(goodAut))
            System.out.println("URL is valid but failed");
        else
        	System.out.println("Url worked");

        System.out.println("\nBad authority: " + badAut);
        if (urlVal.isValid(badAut))
            System.out.println("URL is invalid but passed");
        else
        	System.out.println("Url worked");

        System.out.println("\nNo authority: " + noAut);
        if (urlVal.isValid(noAut))
            System.out.println("URL is invalid but passed");
        else
        	System.out.println("Url worked");
   }

   	//test port with bare minimum
    public void testYourThirdPartition(){
        System.out.println("\n\nTesting Port Partition");
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

        String validPre = "http://www.google.com";

        String goodPort = validPre + ":80";
        String badPort = validPre + ":-1";
        String noPort = validPre + "";

        System.out.println("\nGood port: " + goodPort);
        if (!urlVal.isValid(goodPort))
            System.out.println("URL is valid but failed");
        else
        	System.out.println("Url worked");

        System.out.println("\nBad port: " + badPort);
        if (urlVal.isValid(badPort))
            System.out.println("URL is invalid but passed");
        else
        	System.out.println("Url worked");

        System.out.println("\nNo port: " + noPort);
        if (!urlVal.isValid(noPort))
            System.out.println("URL is valid but failed");
        else
        	System.out.println("Url worked");
   }

    //test path with bare minimum
    public void testYourFourthPartition(){
        System.out.println("\n\nTesting Path Partition");
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

        String validPre = "http://www.google.com";

        String goodPath = validPre + "/test1";
        String badPath = validPre + "/../";
        String noPath = validPre + "";

        System.out.println("\nGood path: " + goodPath);
        if (!urlVal.isValid(goodPath))
            System.out.println("URL is valid but failed");
        else
        	System.out.println("Url worked");

        System.out.println("\nBad path: " + badPath);
        if (urlVal.isValid(badPath))
            System.out.println("URL is invalid but passed");
        else
        	System.out.println("Url worked");

        System.out.println("\nNo path: " + noPath);
        if (!urlVal.isValid(noPath))
            System.out.println("URL is valid but failed");
        else
        	System.out.println("Url worked");
   }

    //test query with bare minimum
    public void testYourFifthPartition(){
        System.out.println("\n\nTesting Query Partition");
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

        String validPre = "http://www.google.com";

        String goodQue = validPre + "?action=view";
        String badQue = validPre + "?action=view?b=2";
        String noQue = validPre + "";

        System.out.println("\nGood query: " + goodQue);
        if (!urlVal.isValid(goodQue))
            System.out.println("URL is valid but failed");
        else
        	System.out.println("Url worked");

        System.out.println("\nBad query: " + badQue);
        if (urlVal.isValid(badQue))
            System.out.println("URL is invalid but passed");
        else
        	System.out.println("Url worked");

        System.out.println("\nNo query: " + noQue);
        if (!urlVal.isValid(noQue))
            System.out.println("URL is valid but failed");
        else
        	System.out.println("Url worked");
   }

    //test all combinations
    public void testYourSixthPartition(){
        System.out.println("\n\nTesting Valid Combination Partition");
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

        String validSch = "http://"; //signified by leading 's'
        String validAut = "www.google.com"; //signified by 'A'
        String validPort = ":80"; //signified by 'Po'
        String validPath = "/test1"; //signified by 'Pa'
        String validQue = "?action=view"; //signified by 'Q'

        String sAPo = validSch + validAut + validPort;
        String sAPa = validSch + validAut + validPath;
        String sAQ = validSch + validAut + validQue;
        String sAPoPa = validSch + validAut + validPort + validPath;
        String sAPoQ = validSch + validAut + validPort + validQue;
        String sAPaQ = validSch + validAut + validPath + validQue;
        String sAPoPaQ = validSch + validAut + validPort + validPath + validQue;


        System.out.println("\nScheme + Authority + Port: " + sAPo);
        if (!urlVal.isValid(sAPo))
            System.out.println("URL is valid but failed");
        else
        	System.out.println("Url worked");

        System.out.println("\nScheme + Authority + Path: " + sAPa);
        if (!urlVal.isValid(sAPa))
            System.out.println("URL is valid but failed");
        else
        	System.out.println("Url worked");

        System.out.println("\nScheme + Authority + Query: " + sAQ);
        if (!urlVal.isValid(sAQ))
            System.out.println("URL is valid but failed");
        else
        	System.out.println("Url worked");

        System.out.println("\nScheme + Authority + Port + Path: " + sAPoPa);
        if (!urlVal.isValid(sAPoPa))
            System.out.println("URL is valid but failed");
        else
        	System.out.println("Url worked");

        System.out.println("\nScheme + Authority + Port + Query: " + sAPoQ);
        if (!urlVal.isValid(sAPoQ))
            System.out.println("URL is valid but failed");
        else
        	System.out.println("Url worked");

        System.out.println("\nScheme + Authority + Port + Query: " + sAPaQ);
        if (!urlVal.isValid(sAPaQ))
            System.out.println("URL is valid but failed");
        else
        	System.out.println("Url worked");

        System.out.println("\nScheme + Authority + Port + Path + Query: " + sAPoPaQ);
        if (!urlVal.isValid(sAPoPaQ))
            System.out.println("URL is valid but failed");
        else
        	System.out.println("Url worked");
   }

    public void testIsValid() {
    	UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

    	String laststr = "", diffstr;
	    do {
	    	StringBuilder testBuffer = new StringBuilder();
	    	boolean expected = true;
	        for (int testPartsIndexIndex = 0; testPartsIndexIndex < testPartsIndex.length; ++testPartsIndexIndex) {
	        	int index = testPartsIndex[testPartsIndexIndex];
	        	ResultPair[] part = (ResultPair[]) testUrlParts[testPartsIndexIndex];
	            testBuffer.append(part[index].item);
	            expected &= part[index].valid;
	        }

	        // run UrlValidator.isValid() method
	        String url = testBuffer.toString();
	        diffstr = "";
			if (laststr == "")
				diffstr = url;
			else {
				int idx = -1, len;
				if (laststr.length() > url.length()) len = url.length();
				else if (laststr.length() < url.length()) len = laststr.length();
				else len = url.length();

				for (int n=0; n<len; ++n)
					if (laststr.charAt(n) != url.charAt(n)) {
						idx = n;
						break;
					}

				if (idx >= 0)
					diffstr = url.substring(idx);
			}
			laststr = url;

			// test isValid (buggy) method
			System.out.println(url);
			boolean result = urlVal.isValid(url);
	        if (result == expected) {
	        	//System.out.println("[Expected] " + expected + "  [Buggy] " + result + "\n");
	        	;
	        }
	        else {
	        	System.out.println("[Expected] " + expected + "  [Buggy] " + result +
	        			"  [Diff Str] " + diffstr + "\n");
	        }
	    } while (incrementTestPartsIndex(testPartsIndex, testUrlParts));

    }

/**Everything below taken from the given tester in part A of assignment**/


    public boolean incrementTestPartsIndex(int[] testPartsIndex, Object[] testParts) {
    	boolean carry = true;  //add 1 to lowest order part.
	    boolean maxIndex = true;
	    for (int testPartsIndexIndex = testPartsIndex.length - 1; testPartsIndexIndex >= 0; --testPartsIndexIndex) {
	    	int index = testPartsIndex[testPartsIndexIndex];
	    	ResultPair[] part = (ResultPair[]) testParts[testPartsIndexIndex];
	        if (carry) {
	        	if (index < part.length - 1) {
	        		index++;
	                testPartsIndex[testPartsIndexIndex] = index;
	                carry = false;
	            }
	        	else {
	        		testPartsIndex[testPartsIndexIndex] = 0;
	                carry = true;
	            }
	        }
	        maxIndex &= (index == (part.length - 1));
	    }
	    return (!maxIndex);
	}


    public void testAnyOtherUnitTest() {
    	return;
    }


   /**
    * Create set of tests by taking the testUrlXXX arrays and
    * running through all possible permutations of their combinations.
    *
    * @param testObjects Used to create a url.
    */


    //-------------------- Test data for creating a composite URL
    /**
     * The data given below approximates the 4 parts of a URL
     * <scheme>://<authority><path>?<query> except that the port number
     * is broken out of authority to increase the number of permutations.
     * A complete URL is composed of a scheme+authority+port+path+query,
     * all of which must be individually valid for the entire URL to be considered
     * valid.
     */
    ResultPair[] testUrlScheme = {new ResultPair("http://", true),
                                new ResultPair("ftp://", true),
                                new ResultPair("h3t://", true),
                                new ResultPair("3ht://", false),
                                new ResultPair("http:/", false),
                                new ResultPair("http:", false),
                                new ResultPair("http/", false),
                                new ResultPair("://", false),
                                new ResultPair("", true)};

    ResultPair[] testUrlAuthority = {new ResultPair("www.google.com", true),
                                   new ResultPair("go.com", true),
                                   new ResultPair("go.au", true),
                                   new ResultPair("0.0.0.0", true),
                                   new ResultPair("255.255.255.255", true),
                                   new ResultPair("256.256.256.256", false),
                                   new ResultPair("255.com", true),
                                   new ResultPair("1.2.3.4.5", false),
                                   new ResultPair("1.2.3.4.", false),
                                   new ResultPair("1.2.3", false),
                                   new ResultPair(".1.2.3.4", false),
                                   new ResultPair("go.a", false),
                                   new ResultPair("go.a1a", false),
                                   new ResultPair("go.cc", true),
                                   new ResultPair("go.1aa", false),
                                   new ResultPair("aaa.", false),
                                   new ResultPair(".aaa", false),
                                   new ResultPair("aaa", false),
                                   new ResultPair("", false)
    };
    ResultPair[] testUrlPort = {new ResultPair(":80", true),
                              new ResultPair(":65535", true),
                              new ResultPair(":0", true),
                              new ResultPair("", true),
                              new ResultPair(":-1", false),
                              new ResultPair(":65636", true),
                              new ResultPair(":65a", false)
    };
    ResultPair[] testPath = {new ResultPair("/test1", true),
                           new ResultPair("/t123", true),
                           new ResultPair("/$23", true),
                           new ResultPair("/..", false),
                           new ResultPair("/../", false),
                           new ResultPair("/test1/", true),
                           new ResultPair("", true),
                           new ResultPair("/test1/file", true),
                           new ResultPair("/..//file", false),
                           new ResultPair("/test1//file", false)
    };
    //Test allow2slash, noFragment
    ResultPair[] testUrlPathOptions = {new ResultPair("/test1", true),
                                     new ResultPair("/t123", true),
                                     new ResultPair("/$23", true),
                                     new ResultPair("/..", false),
                                     new ResultPair("/../", false),
                                     new ResultPair("/test1/", true),
                                     new ResultPair("/#", false),
                                     new ResultPair("", true),
                                     new ResultPair("/test1/file", true),
                                     new ResultPair("/t123/file", true),
                                     new ResultPair("/$23/file", true),
                                     new ResultPair("/../file", false),
                                     new ResultPair("/..//file", false),
                                     new ResultPair("/test1//file", true),
                                     new ResultPair("/#/file", false)
    };

    ResultPair[] testUrlQuery = {new ResultPair("?action=view", true),
                               new ResultPair("?action=edit&mode=up", true),
                               new ResultPair("", true)
    };

    Object[] testUrlParts = {testUrlScheme, testUrlAuthority, testUrlPort, testPath, testUrlQuery};
    Object[] testUrlPartsOptions = {testUrlScheme, testUrlAuthority, testUrlPort, testUrlPathOptions, testUrlQuery};
    int[] testPartsIndex = {0, 0, 0, 0, 0};

    //---------------- Test data for individual url parts ----------------
    ResultPair[] testScheme = {new ResultPair("http", true),
                             new ResultPair("ftp", false),
                             new ResultPair("httpd", false),
                             new ResultPair("telnet", false)};

}
