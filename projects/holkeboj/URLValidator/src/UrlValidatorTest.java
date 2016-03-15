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
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May
 *          2011) $
 */
public class UrlValidatorTest extends TestCase {
	private static final String URL_REGEX = "^(([^:/?#]+):)?(//([^/?#]*))?([^?#]*)(\\?([^#]*))?(#(.*))?";
	private static final Pattern URL_PATTERN = Pattern.compile(URL_REGEX);
	private static final String LEGAL_ASCII_REGEX = "^\\p{ASCII}+$";
	private static final Pattern ASCII_PATTERN = Pattern.compile(LEGAL_ASCII_REGEX);

	public UrlValidatorTest(String testName) {
		super(testName);
	}

	public void testManualTest() {
		   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_LOCAL_URLS);
		   System.out.println("Should Return True:");
		   System.out.println(urlVal.isValid("http://www.amazon.com"));
		   System.out.println(urlVal.isValid("http://www.google.com/valid/"));
		   System.out.println(urlVal.isValid("http://stuff.amazon.com/231?get=h/"));
		   System.out.println(urlVal.isValid("http://www.amazon.com/test1?action=view/"));
		   System.out.println(urlVal.isValid("http://www.msn.com//valid?valid"));
		   System.out.println(urlVal.isValid("http://www.msn.com/valid=valid"));
		   System.out.println(urlVal.isValid("http://www.msn.com/$23"));
		   System.out.println(urlVal.isValid("http://www.msn.com/t123?action=view"));
		   System.out.println(urlVal.isValid("http://www.msn.com/?/"));
		   System.out.println(urlVal.isValid("http://www.msn.com/$/"));
		   System.out.println(urlVal.isValid("http://www.amazon.com"));
		   System.out.println(urlVal.isValid("http://www.yahoo.com"));
		   System.out.println(urlVal.isValid("http://www.paypal.com"));
		   System.out.println(urlVal.isValid("http://www.blazersedge.com"));
		   System.out.println(urlVal.isValid("http://www.amazon.com/1/2/3/4/5/6/7/8/9/10/11/12/13/14/15/16"));
		   System.out.println(urlVal.isValid("http://www.amazon.com/zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz/"));
		   
		   System.out.println("Should Return False:");
		   System.out.println(urlVal.isValid("http://www.msn.com/valid123//"));
		   System.out.println(urlVal.isValid("http//www.amazon.com"));
		   System.out.println(urlVal.isValid("a://www.msn.com"));
		   System.out.println(urlVal.isValid("ab://www.msn.com"));
		   System.out.println(urlVal.isValid("abc://www.msn.com"));
		   System.out.println(urlVal.isValid("abcd://www.msn.com"));
		   System.out.println(urlVal.isValid("abcde://www.msn.com"));
		   System.out.println(urlVal.isValid("abcdef://www.msn.com"));
		   System.out.println(urlVal.isValid("abcdefg://www.msn.com"));
		   System.out.println(urlVal.isValid("abcdefgh://www.msn.com"));
		   System.out.println(urlVal.isValid("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa://www.msn.com"));
		   System.out.println(urlVal.isValid("htp://www.amazon.com"));
		   System.out.println(urlVal.isValid("www.amazon.com"));
		   System.out.println(urlVal.isValid(""));
		   System.out.println(urlVal.isValid("yo"));
		   System.out.println(urlVal.isValid("false://www.amazon.com"));
		   System.out.println(urlVal.isValid("4://www.msn.com"));
		   System.out.println(urlVal.isValid("91872398u8r9jiej"));
		   System.out.println(urlVal.isValid("18://444.23145.9804"));
		   System.out.println(urlVal.isValid("http:/www.amazon.com"));
		   System.out.println(urlVal.isValid("http://256.256.256.256"));
		   System.out.println(urlVal.isValid("http://google.kjfwoei"));
		   System.out.println(urlVal.isValid("http://google.BLAHBLAH"));
	}
	
	
	public void testYourFirstPartition(){
		int testsFailed = 0;
		int testCount = 10000;

		UrlComponents components = new UrlComponents();

		int[] schemeErrors = new int[components.schemesLength];
		int[] authorityErrors = new int[components.authoritiesLength];
		int[] pathErrors = new int[components.pathsLength];
		int[] queryErrors = new int[components.queriesLength];

		GenerateUrl gen = new GenerateUrl();
		UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_LOCAL_URLS);

		for (int i = 0; i < testCount; i++) {

			int[] randArr = gen.randArray(); // Random array for initialization
												// of url components

			String[] comp = gen.urlComponentArray(randArr); // URL Component
															// array
			String URL = gen.createUrl(comp); // Actual URL

			boolean[] bcomp = gen.isValidArray(randArr); // Boolean component of
															// respective url
															// Components
			boolean expectedValid = gen.isValid(bcomp); // Expected boolean of
														// test case
			boolean actualValid = urlVal.isValid(URL); // Actual boolean
														// produced

			if (actualValid != expectedValid) {
				Matcher urlMatcher = URL_PATTERN.matcher(URL);
				urlMatcher.matches();
				System.out.format("\nMISMATCH DETECTED! Test URL is %s\n", URL);
				System.out.format("Expected Result: %b Actual Result: %b\n", expectedValid, actualValid);
				for (int j = 0; j <= 4; j++) {
					switch (j) {
					case 0:
						String scheme = urlMatcher.group(2);
						// System.out.format("Scheme is %s %d\n", scheme,j);
						boolean validScheme = urlVal.isValidScheme(scheme);
						if (bcomp[j] != validScheme) {
							schemeErrors[randArr[0]] += 1;
							System.out.format("Scheme error detected for %s Expected: %b Actual: %b\n", comp[j],
									bcomp[j], validScheme);
						}
						break;
					case 1:
						String authority = urlMatcher.group(4);
						boolean validAuthority = urlVal.isValidAuthority(authority);
						if (bcomp[j] != validAuthority) {
							authorityErrors[randArr[1]] += 1;
							System.out.format("Authority error detected for %s Expected: %b Actual: %b\n", comp[j],
									bcomp[j], validAuthority);
						}
						break;
					case 2:
						String path = urlMatcher.group(5);
						boolean validPath = urlVal.isValidPath(path);
						if (bcomp[j] != validPath) {
							pathErrors[randArr[2]] += 1;
							System.out.format("Path error detected for %s Expected: %b Actual %b\n", comp[j], bcomp[j],
									validPath);
						}
						break;
					case 3:
						String query = urlMatcher.group(7);
						boolean validQuery = urlVal.isValid(query);
						if (bcomp[j] != validQuery) {
							queryErrors[randArr[3]] += 1;
							System.out.format("Querry error detected for %s Expected %b Actual %b\n", comp[j], bcomp[j],
									validQuery);
						}
						break;
					}
				}
				testsFailed++;
			}

		}
		System.out.print("\n");
		System.out.format("Failed %d out of %d tests (%.3f%%).\n\n", testsFailed,testCount, ((double)testsFailed/(double)testCount)*100);

		for (int j = 0; j < schemeErrors.length; j++) {
			if (schemeErrors[j] > 0)
				System.out.format("Scheme %s failed\n", components.testSchemes[j].item);
		}
		System.out.print("\n");
		for (int j = 0; j < authorityErrors.length; j++) {
			if (authorityErrors[j] > 0)
				System.out.format("Authority %s failed\n", components.testAuthority.get(j).item);
		}
		System.out.print("\n");
		for (int j = 0; j < pathErrors.length; j++) {
			if (pathErrors[j] > 0)
				System.out.format("Path %s failed\n", components.testPaths[j].item);
		}
		System.out.print("\n");
		for (int j = 0; j < queryErrors.length; j++) {
			if (queryErrors[j] > 0)
				System.out.format("query %s failed\n", components.testQueryStrings[j].item, queryErrors[j]);
		}
	}

	public void testIsValid() {
		   // Construct sets of ResultPairs that will be randomly chosen from
		   // These arrays represent the different parts of a URL:
		   	// Scheme (e.g. http, ftp, etc)
		   	// Address (e.g. yahoo.com, www.google.com, bbc.co.uk, etc)
		   	// Port (e.g. no port, :80, :63353, etc)
		   	// Path (e.g. /path, /path1/path2/file.txt, etc)
		   	// Query String (e.g. ?value=1)
		   // The only URL part that must be present is the address. 
		   // Each other part can have the value of a blank string and boolean true.
		   
		   
		   // Test Schemes
		   ResultPair[] testSchemes = {
				   new ResultPair("", true),
				   new ResultPair("http://", true),
				   new ResultPair("ftp://", true),
				   new ResultPair("h3t://", true),
				   new ResultPair("htpp://", false),
				   new ResultPair("http", false),
				   new ResultPair("http:/", false),
				   new ResultPair("ftp:", false),
				   new ResultPair("h3tt://", false),
				   new ResultPair("fft:", false),
				   new ResultPair(":/", false),
				   new ResultPair("://", false),
		   };
		   
		   // Test addresses
		   ResultPair[] testAddresses = {
				   new ResultPair("yahoo.com", true),
				   new ResultPair("www.yahoo.com", true),
				   new ResultPair("www.yahoo.com.au", true),
				   new ResultPair(".yahoo.com", false),
				   new ResultPair("192.168.0.110", true),
				   new ResultPair("300.168.0.110", false),
				   new ResultPair("google.kjfwoei", false),
				   new ResultPair("google.", false),
				   new ResultPair("0.0.0.0", true),
				   new ResultPair("12345.com", true),
				   new ResultPair("255.255.255.255", true),
				   new ResultPair("255.256.255.255", false),
				   new ResultPair("256.255.255.255", false),
				   new ResultPair("255.255.256.255", false),
				   new ResultPair("255.255.255.256", false),
				   new ResultPair("192.24.2.1.2", false),
				   new ResultPair("192.168.0.500", false),
				   new ResultPair("google", false),
				   new ResultPair(".google", false),
				   new ResultPair("", false)	
		   };
		   
		   ResultPair[] testPorts = {
				   new ResultPair("", true),
				   new ResultPair(":80", true),
				   new ResultPair(":0", true),
				   new ResultPair(":-1", false),
				   new ResultPair(":oisd", false),
				   new ResultPair(":44isd", false),
				   new ResultPair(":24ois67", false),
				   new ResultPair(":66849", false),
				   new ResultPair(":65635", true)
		   };
		   
		   ResultPair[] testPaths = {
				   new ResultPair("/testpath", true),
				   new ResultPair("/i12iro3i", true),
				   new ResultPair("/testpath/", true),
				   new ResultPair("/$owie", true),
				   new ResultPair("/..", false),
				   new ResultPair("/#", false),
				   new ResultPair("/#/testpath", false),
				   new ResultPair("", true),
				   new ResultPair("/testpath1/testpath2", true),
				   new ResultPair("testpath1//testpath2", false),
				   new ResultPair("/testpath1//testpath2", false),
				   new ResultPair("", true),
				   new ResultPair("1path/path2", false),
				   new ResultPair("/1path/path2", true)
		   };
		   
		   ResultPair[] testQueryStrings = {
				   new ResultPair("?query=this", true),
				   new ResultPair("?query=this&query2=that", true),
				   new ResultPair("?query=this&amp;query2=that", true),
				   new ResultPair("?query=this and that", false),
				   new ResultPair("", true),
		   };
		   
		   // Each ResultPair has a boolean value.
		   // We construct a test case by concatenating the strings in each URL part
		   // And then doing an AND on all the boolean values
		   int testsFailed = 0;
		   int numberOfTests = 10000;
		   Random generator = new Random();
		   for(int i = 0;i<numberOfTests;i++)
		   {
			   // get random scheme
			   int randomSchemeIndex = generator.nextInt(testSchemes.length);
			   String scheme = testSchemes[randomSchemeIndex].item;
			   Boolean schemeValidity = testSchemes[randomSchemeIndex].valid;
			   
			   // get random address
			   int randomAddressIndex = generator.nextInt(testAddresses.length);
			   String address = testAddresses[randomAddressIndex].item;
			   Boolean addressValidity = testAddresses[randomAddressIndex].valid;	
			   
			   // get random port
			   int randomPortIndex = generator.nextInt(testPorts.length);
			   String port = testPorts[randomPortIndex].item;
			   Boolean portValidity = testPorts[randomPortIndex].valid;
			   
			   // get random path
			   int randomPathIndex = generator.nextInt(testPaths.length);
			   String path = testPaths[randomPathIndex].item;
			   Boolean pathValidity = testPaths[randomPathIndex].valid;	
			   
			   // get random query string
			   int randomQueryStringIndex = generator.nextInt(testQueryStrings.length);
			   String queryString = testQueryStrings[randomQueryStringIndex].item;
			   Boolean queryStringValidity = testQueryStrings[randomQueryStringIndex].valid;
			   
			   // build test case
			   String testURL = scheme + address + port + path + queryString;
			   Boolean testURLValidity = schemeValidity && addressValidity && portValidity
					   && pathValidity && queryStringValidity;
			   
			   // test the test case
			   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_LOCAL_URLS);
			   boolean result = urlVal.isValid(testURL);
			   if (result != testURLValidity) {
				   System.out.format("Failed for URL %s\n", testURL);
				   testsFailed += 1;
			   }
		   }
		   System.out.format("Failed %d out of %d tests.\n", testsFailed, numberOfTests);
	}

	public void testAnyOtherUnitTest() {

	}
}
