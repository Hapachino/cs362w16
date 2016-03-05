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

import java.io.BufferedReader;
import java.io.Console;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Random;
import java.util.Scanner;

import junit.framework.TestCase;

/**
 * Performs Validation Test for url validations.
 * 
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May
 *          2011) $
 */
public class UrlValidatorTest extends TestCase {

	private boolean printStatus = false;
	private boolean printIndex = false; // print index that indicates current scheme, host, port, path, query test we're using.

	enum TestParam { Good, Bad, Empty };
	
	public class TestResult {
		String url;
		boolean valid;

		public TestResult(String u, boolean v) {
			url = u;
			valid = v;
		}
	}

	public UrlValidatorTest(String testName) {
		super(testName);
	}
	
	public void testManualTest() {
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

        System.out.println(urlVal.isValid("##://www.foo.com"));
        System.out.println(urlVal.isValid("ftp://!!!.###.com"));
        System.out.println(urlVal.isValid("://www.foo.com"));
        System.out.println(urlVal.isValid("http://.foo.com"));
        System.out.println(urlVal.isValid("\\10.1.1.1"));	
        System.out.println(urlVal.isValid("http://massive.tv/")); 
        System.out.println(urlVal.isValid("http://www.yahoo.co.jp"));    
        System.out.println(urlVal.isValid("a://www.foo.com"));	   
        System.out.println(urlVal.isValid("ftp://ftp.somed0main.com"));
        System.out.println(urlVal.isValid("http://www.normalurl.com"));
        System.out.println(urlVal.isValid("https://google.com"));
        System.out.println(urlVal.isValid("ssh://onid.orst.edu"));
        System.out.println(urlVal.isValid("http://www.1.com"));
        System.out.println(urlVal.isValid("google.com"));
        System.out.println(urlVal.isValid("www.google.com"));
        System.out.println(urlVal.isValid("http://74.125.224.72/"));
        System.out.println(urlVal.isValid("http://74.125.224.72:8080"));
        System.out.println(urlVal.isValid("https://www.yahoo.com:493"));
        System.out.println(urlVal.isValid("http://www.yahoo.com:8000"));
        System.out.println(urlVal.isValid("http://www.yahoo.com:80"));
        System.out.println(urlVal.isValid("http://www.yahoo.com:abc"));
        System.out.println(urlVal.isValid("a://www.foo./"));
        System.out.println(urlVal.isValid("a:www.foo.com"));
        System.out.println(urlVal.isValid("http://www.1.com/subPage/main.html"));
        System.out.println(urlVal.isValid("http://www. .com"));
        System.out.println(urlVal.isValid("http://www.yahoo.com:0"));
        System.out.println(urlVal.isValid("http://www.yahoo.com:65535"));
        System.out.println(urlVal.isValid("http://www.yahoo.com:65536"));
        
		Scanner s = new Scanner(System.in);
		String testUrl;
		while (true) {
			System.out.print("Enter test URL:\t");
			testUrl = s.nextLine();
			if (testUrl.isEmpty())
				break;
			System.out.println(urlVal.isValid(testUrl));
		}
		s.close();
	}

	public void testManual() {
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        ArrayList<String> inputUrl = new ArrayList<String>();
        
        inputUrl.add("##://www.foo.com");
        inputUrl.add("ftp://!!!.###.com");
        inputUrl.add("://www.foo.com");
        inputUrl.add("http://.foo.com");
        inputUrl.add("\\10.1.1.1");	
        inputUrl.add("http://massive.tv/"); 
        inputUrl.add("http://www.yahoo.co.jp");
        inputUrl.add("http://www.yahoo.co.fj");
        inputUrl.add("a://www.foo.com");	   
        inputUrl.add("ftp://ftp.somed0main.com");
        inputUrl.add("http://www.normalurl.com");
        inputUrl.add("https://google.com");
        inputUrl.add("ssh://onid.orst.edu");
        inputUrl.add("http://www.1.com");
        inputUrl.add("google.com");
        inputUrl.add("www.google.com");
        inputUrl.add("http://74.125.224.72/");
        inputUrl.add("http://74.125.224.72:8080");
        inputUrl.add("https://www.yahoo.com:493");
        inputUrl.add("http://www.yahoo.com:8000");
        inputUrl.add("http://www.yahoo.com:80");
        inputUrl.add("http://www.yahoo.com:abc");
        inputUrl.add("a://www.foo./");
        inputUrl.add("a:www.foo.com");
        inputUrl.add("http://www.1.com/subPage/main.html");
        inputUrl.add("http://www. .com");
        inputUrl.add("http://www.yahoo.com:0");
        inputUrl.add("http://www.yahoo.com:65535");
        inputUrl.add("http://www.yahoo.com:65536");
        
        for(String s : inputUrl)
        {
        	System.out.println(urlVal.isValid(s) + "\t" + s);
        }
		
	}
	
	// generateRandomValidString: generate a random string of letters, numbers
	// and valid substrings
	// int length: how many characters
	public String generateRandomValidString(int length, ArrayList<String> validSubstrings) {
		Random r = new Random();
		java.lang.StringBuffer sb = new StringBuffer();
		for (int i = 0; i < length; i++) {
			if(!validSubstrings.isEmpty() && r.nextInt(5) == 0) {
				sb.append( validSubstrings.get( r.nextInt( validSubstrings.size() ) ) );
			}
			else {
				int rInt = (int) 'a' + r.nextInt(36);
				if (rInt > (int) 'z') {
					rInt -= 75; // if number is past 'z', use a digit instead
				}
				sb.append((char) rInt);
			}
		}
		return sb.toString();
	}
	
	// generateRandomString: generate a random string of characters with at least one non-alphaNum
	// int length: how many characters
	public String generateRandomString(int length) {
		if(length < 1) {
			return "";
		}
		Random r = new Random();
		java.lang.StringBuffer sb = new StringBuffer();
		boolean aNumOnly = true;
		for (int i = 0; i < length; i++) {
			int rInt = (int) ' ' + r.nextInt(94);
			if( !(
					(rInt >= (int)'0' && rInt <= (int)'9') || 
					(rInt >= (int)'A' && rInt <= (int)'Z') || 
					(rInt >= (int)'a' && rInt <= (int)'z')
			) ) {
				aNumOnly = false;
			}
			sb.append((char) rInt);
		}
		if(aNumOnly) {
			sb.setCharAt( r.nextInt( sb.length() ), (char)((int)' ' + r.nextInt(15)) );
		}
		return sb.toString();
	}	

	// return all lines from FileReader f
	public ArrayList<String> getLines(FileReader f) {
		ArrayList<String> lines = new ArrayList<String>();
		BufferedReader inStream = new BufferedReader(f);
		try 
		{
			String line;
			while( (line = inStream.readLine()) != null ) {
				lines.add(line.toLowerCase());
			}
			inStream.close();
			return lines;
		} 
		catch (IOException e) 
		{
			e.printStackTrace();
			return null;
		} 		
	}
	


	
	
/* ******************************************************************************************************************************
 * testRandom
 * 
 * generates and tests a URL with randomly generated components. URL components may be Good, Bad, or Empty depending on the 
 * component. These values are enum TestParam {Good, Bad, Empty}
 * 
 * parameters:
 * 				numTests				int 			how many tests to run
 * 				scheme, separator		TestParam		{ Good, Bad, Empty }
 * 				authority, sld, tld		TestParam		{ Good, Bad, Empty }
 * 				port, path, query		TestParam		{ Good, Bad, Empty }
 *
 * Recent changes: 
 * 			
 * 			all components can be empty.
 * 
 * 			testRandom takes new parameter:		TestParam separator		can be valid, which right now is :// or invalid, which 
 * 																		is a random string, or empty
 * 
 * 			for bad ports, now using only random numbers outside allowable range. (Not specifically testing 0, this can be a
 * 			manual test or we can add it to the randomizer.)
 * 
 * 			now using an extra param for generateValidString: ArrayList<String> containing additional substrings besides alphanum
 * 			which should be considered valid. This is empty except for path and query. (Not sure about whether path should be.)
 *
 *******************************************************************************************************************************/

	public ArrayList<TestResult> testRandom(
			int numTests,
			TestParam scheme, TestParam separator, TestParam authority, TestParam sld, TestParam tld, 	
			TestParam port, TestParam path, TestParam query) {	
		
		Random r = new Random();
		UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		ArrayList<String> tldList;
		ArrayList<String> urlEncodeList;
		try {
			FileReader f = new FileReader("src/tldList.txt");
			tldList = getLines(f);
			f.close();
			f = new FileReader("src/urlEncodeList.txt");
			urlEncodeList = getLines(f);
		} 
		catch (Exception e) {
			e.printStackTrace();
			return null;
		}	
		
		ArrayList<TestResult> results = new ArrayList<TestResult>();
		String testUrl;
		int testCount = 0;
		
		for (int i = 0; i < numTests; i++) 
		{
			java.lang.StringBuffer urlSb = new StringBuffer();

			// generate random scheme
			StringBuffer sb = new StringBuffer();
			if(scheme == TestParam.Good) {
				sb.append((char) ('a' + r.nextInt(26)));
				String rString = generateRandomValidString(r.nextInt(5), new ArrayList<String>());
				sb.append(rString);
			} else if(scheme == TestParam.Bad) {
				String rString = generateRandomString(r.nextInt(5));
				if (rString.length() > 0) {
					sb.append(rString);
				}
			}			
			if(separator == TestParam.Good) {
				sb.append("://");
			} else if(separator == TestParam.Bad) {
				String s;
				do {
					s = generateRandomString(1 + r.nextInt(4));
				} while("://" == s);
				sb.append(s);
			}			
			urlSb.append(sb);
			
			// generate random authority
			if(authority == TestParam.Good) {
				urlSb.append( generateRandomValidString( 1 + r.nextInt( 3 ), new ArrayList<String>() ) + "." );
			}
			else if(authority == TestParam.Bad) {
				urlSb.append( generateRandomString( 1 + r.nextInt( 3 ) ) + "." );
			}					

			// generate random second-level domain
			for(int j = 0; j < 1 + r.nextInt(5); j++) 
			{
				if(sld == TestParam.Good) {
					urlSb.append( generateRandomValidString( 1 + r.nextInt( 100 ), new ArrayList<String>() ) + "." );
				} else if (sld == TestParam.Bad) {
					urlSb.append( generateRandomString( 1 + r.nextInt( 100 ) ) + "." );
				} 
			}

			// use a top-level domain from list
			if(tld == TestParam.Good) {
				//urlSb.append(tldList[testCount % tldList.length]);
				urlSb.append(tldList.get(testCount % tldList.size()));
			} else if(tld == TestParam.Bad) {
				if(r.nextInt(2) == 0) {
					urlSb.append( generateRandomString( 1 + r.nextInt(5) ) );
				} 
				else {
					String s;
					do {
						s = generateRandomValidString( 1 + r.nextInt(5), urlEncodeList );						
					} while(tldList.contains(s));
					urlSb.append(s);
				}
			} else {
				if(urlSb.charAt( urlSb.length() - 1) == '.' ) {
					urlSb.deleteCharAt(urlSb.length() - 1);		// if authority or sld but no tld, remove the last period
				}
			}			
					
			// generate a random port number, or no port number
			if(port == TestParam.Good) {
				int portNum = 1 + r.nextInt(65535);
				urlSb.append(":" + portNum);
			} else if(port == TestParam.Bad) {
				int portNum = 65536 + r.nextInt(Integer.MAX_VALUE - 65536);
				if(testCount % 10 == 0) {
					portNum = 0 - r.nextInt();
				}
				urlSb.append( ":" + portNum );
			}
			
			// generate a random path, or none
			if(path == TestParam.Good) {	
				for(int j = 0; j < 1 + r.nextInt(3); j++) 
				{
					String pathString = generateRandomValidString(1 + r.nextInt(10), urlEncodeList);
					if(pathString.length() > 0) {
						urlSb.append("/");
						if(r.nextInt(5) == 0) {
							urlSb.append("~");
						}
						urlSb.append(pathString);
					}
				}
			} else if(path == TestParam.Bad) {
				for(int j = 0; j < 1 + r.nextInt(3); j++) 
				{
					String pathString = generateRandomString(1 + r.nextInt(10));
					if(pathString.length() > 0) {
						urlSb.append("/" + pathString);
					}
				}
			}
			
			// generate a random query, or none
			
			// ****** NEED TO ADD testing for allowed "special" characters:
			//		$	-	+	!	*	'	()	;	@
			
			// How about these?
			//		<	>	#	%	|	\	^	[	]	`
			
			int numPairs;
			if(query != TestParam.Empty) {
				numPairs = r.nextInt(5);
			}
			else {
				numPairs = 0;
			}
			if(numPairs > 0) {
				urlSb.append("?");
			}
			for(int j = 1; j <= numPairs; j++) 
			{
				String queryString;
				if(query == TestParam.Good) {
					queryString = generateRandomValidString(1 + r.nextInt(10), urlEncodeList);
				} else {
					queryString = generateRandomString(1 + r.nextInt(10));
				}
				urlSb.append(queryString + "=");
				if(query == TestParam.Good) {
					queryString = generateRandomValidString(1 + r.nextInt(10), urlEncodeList);
				} else {
					queryString = generateRandomString(1 + r.nextInt(10));
				}
				urlSb.append(queryString);
				if(j < numPairs) {
					urlSb.append("&");
				}
			}
			testUrl = urlSb.toString();
			results.add(new TestResult(testUrl, urlVal.isValid(testUrl)));
			testCount++;
		}
		if(testCount != numTests) {
			System.out.println("Error! testRandom() did not execute the requested number of tests.");
			System.out.println("Expected " + numTests + ", got " + testCount);	
		}
		return results;
	}
	
	
	
/* ******************************************************************************************************************************
 * Example test: All URLs in the form
 * 
 * {AlphaFirstString}://{AlphaNumString}.{AlphaNumString}.{tldString}:{int16}/{AlphaNumString}?{AlphaNumString}={AlphaNumString}
 * 
 * should be valid,
 * 
 * where 	AlphaNumString : string of letters/numbers
 * 			AlphaFirstString : AlphaNumString starting with a letter
 * 			tldString : one of accepted top-level domains
 *
 * and everything after TLD is optional, the path may have more than one string, and the query may have more than one parameter
 * 
 *******************************************************************************************************************************/
		
		public void testRandomAllPartsValid()
		{
			int numTests = 100;
			int failedTests = 0;
			ArrayList<TestResult> results = testRandom(
				numTests, TestParam.Good, TestParam.Good, TestParam.Good, TestParam.Good, 
				TestParam.Good, TestParam.Good, TestParam.Good, TestParam.Good
			);
			for(TestResult t : results) 
			{
				if(t.valid == false) {		// all should be valid
					failedTests++;
					System.out.println(t.valid + "\t" + t.url);
				}		
			}
			System.out.println(numTests + " tests\n" + failedTests + " failures.");
		}
		
		
		
/* ******************************************************************************************************************************
 * Example test: All URLs in the form
 * 
 * {AlphaFirstString}://{String}.{AlphaNumString}.{tldString}:{int16}/{AlphaNumString}?{AlphaNumString}={AlphaNumString}
 * 
 * should be invalid,
 * 
 * where	String : string with non-alphaNum chars
 * 		 	AlphaNumString : string of letters/numbers
 * 			AlphaFirstString : AlphaNumString starting with a letter
 * 			tldString : one of accepted top-level domains
 * 
 *******************************************************************************************************************************/
		
		public void testRandomBadScheme()
		{
			int numTests = 100;
			int failedTests = 0;
			ArrayList<TestResult> results = testRandom(
				numTests, TestParam.Bad, TestParam.Good, TestParam.Good, TestParam.Good, 
				TestParam.Good, TestParam.Good, TestParam.Good, TestParam.Good
			);
			for(TestResult t : results) 
			{
				System.out.println(t.valid + "\t" + t.url);
				if(t.valid == true) {		// all should be invalid
					failedTests++;					
				}		
			}
			System.out.println(numTests + " tests\n" + failedTests + " failures.");
		}
		
		
		
/* ******************************************************************************************************************************
 * Example test: All URLs in the form
 * 
 * {AlphaFirstString}://{AlphaNumString}.{AlphaNumString}.{tldString}
 * 
 * should be valid,
 * 
 * where 	AlphaNumString : string of letters/numbers
 * 			AlphaFirstString : AlphaNumString starting with a letter
 * 			tldString : one of accepted top-level domains
 * 
 *******************************************************************************************************************************/
		
		public void testRandomValidNoPPQ() {
			int numTests = 1000;
			int failedTests = 0;
			ArrayList<TestResult> results = testRandom(
				numTests, TestParam.Good, TestParam.Good, TestParam.Good, TestParam.Good, 
				TestParam.Good, TestParam.Empty, TestParam.Empty, TestParam.Empty
			);
			for(TestResult t : results) 
			{
				System.out.println(t.valid + "\t" + t.url);
				if(t.valid == false) {		// all should be valid
					failedTests++;
					//System.out.println(t.valid + "\t" + t.url);
				}		
			}
			System.out.println(numTests + " tests\n" + failedTests + " failures.");
		}


		
	public void testYourFirstPartition() {

	}
		
	public void testYourSecondPartition() {

	}

	public void testIsValid() {
		for (int i = 0; i < 10000; i++) {

		}
	}

	public void testAnyOtherUnitTest() {

	}
	/**
	 * Create set of tests by taking the testUrlXXX arrays and running through
	 * all possible permutations of their combinations.
	 * 
	 * @param testObjects
	 *            Used to create a url.
	 */

	
	/* ******************************************************************************************************************************
	 * testValidPartitions: Runs tests for all possible combinations of components that make up a valid URL
	 * 
	 * {AlphaFirstString}://{AlphaNumString}.{AlphaNumString}.{tldString}:{int16}/{AlphaNumString}?{AlphaNumString}={AlphaNumString}
	 * {scheme}			 ://{authority}	    .{sld}		     .{tld}      :{port} /{path}	      ?{query}
	 * 
	 * should be valid,
	 * 
	 * where 	AlphaNumString : string of letters/numbers
	 * 			AlphaFirstString : AlphaNumString starting with a letter
	 * 			tldString : one of accepted top-level domains
	 * 			sld, port, path, and query are all optional (e.g. can be valid or empty)
	 * 			
	 * 
	 *******************************************************************************************************************************/
	public void testValidPartitions() {
		int numTests = 100;
		
		//All components are valid
		ArrayList<TestResult> r1 = testRandom(
				numTests, TestParam.Good, TestParam.Good, TestParam.Good, TestParam.Good,
				TestParam.Good, TestParam.Good, TestParam.Good, TestParam.Good);
		printResults(r1, numTests, 0);
		
		//No query
		ArrayList<TestResult> r2 = testRandom(
				numTests, TestParam.Good, TestParam.Good, TestParam.Good, TestParam.Good,
				TestParam.Good, TestParam.Good, TestParam.Good, TestParam.Empty);
		printResults(r2, numTests, 0);

		//No path
		ArrayList<TestResult> r3 = testRandom(
				numTests, TestParam.Good, TestParam.Good, TestParam.Good, TestParam.Good,
				TestParam.Good, TestParam.Good, TestParam.Empty, TestParam.Good);
		printResults(r3, numTests, 0);

		//No port
		ArrayList<TestResult> r4 = testRandom(
				numTests, TestParam.Good, TestParam.Good, TestParam.Good, TestParam.Good,
				TestParam.Good, TestParam.Empty, TestParam.Good, TestParam.Good);
		printResults(r4, numTests, 0);

		//No query or path
		ArrayList<TestResult> r5 = testRandom(
				numTests, TestParam.Good, TestParam.Good, TestParam.Good, TestParam.Good,
				TestParam.Good, TestParam.Good, TestParam.Empty, TestParam.Empty);
		printResults(r5, numTests, 0);

		//No query or port
		ArrayList<TestResult> r6 = testRandom(
				numTests, TestParam.Good, TestParam.Good, TestParam.Good, TestParam.Good,
				TestParam.Good, TestParam.Empty, TestParam.Good, TestParam.Empty);
		printResults(r6, numTests, 0);

		//No path or port
		ArrayList<TestResult> r7 = testRandom(
				numTests, TestParam.Good, TestParam.Good, TestParam.Good, TestParam.Good,
				TestParam.Good, TestParam.Empty, TestParam.Empty, TestParam.Good);
		printResults(r7, numTests, 0);
		
		//No query, path or port
		ArrayList<TestResult> r8 = testRandom(
				numTests, TestParam.Good, TestParam.Good, TestParam.Good, TestParam.Good,
				TestParam.Good, TestParam.Empty, TestParam.Empty, TestParam.Empty);
		printResults(r8, numTests, 0);
	}
	
	/* ******************************************************************************************************************************
	 * testInvalidPartitions: Runs tests for all "bad" and "empty" case for all mandatotry components of a URL
	 * 
	 * {AlphaFirstString}://{AlphaNumString}.{AlphaNumString}.{tldString}:{int16}/{AlphaNumString}?{AlphaNumString}={AlphaNumString}
	 * {scheme}			 ://{authority}	    .{sld}		     .{tld}      :{port} /{path}	      ?{query}
	 * 
	 * should be invalid,
	 * 
	 * where 	AlphaNumString : string of letters/numbers
	 * 			AlphaFirstString : AlphaNumString starting with a letter
	 * 			tldString : one of accepted top-level domains
	 * 			sld, port, path, and query are all optional (e.g. can be invalid or empty)
	 * 			
	 * 
	 *******************************************************************************************************************************/
	public void testInvalidPartitions() {
		int numTests = 100;
		int scheme, sep, auth, sld, tld, port, path, query;
		ArrayList<TestParam> params = new ArrayList<TestParam>();
		params.add(0, TestParam.Good);
		params.add(1, TestParam.Bad);
		params.add(2, TestParam.Empty);
		
		//Generate tests for every possible combination with specified component being bad or empty
		//Bad scheme
		for (sep = 0; sep < 3; sep++) {
			for (auth = 0; auth < 3; auth++) {
				for (sld = 0; sld < 3; sld++) {
					for (tld = 0; tld < 3; tld++) {
						for (port = 0; port < 3; port++) {
							for (path = 0; path < 3; path++) {
								for (query = 0; query < 3; query++) {
									ArrayList<TestResult> badScheme = testRandom (
											numTests, TestParam.Bad, params.get(sep), params.get(auth),
											params.get(sld), params.get(tld), params.get(port), 
											params.get(path), params.get(query)
											);
									printResults(badScheme, numTests, 1);
								}}}}}}}
		
		//Empty scheme
		for (sep = 0; sep < 3; sep++) {
			for (auth = 0; auth < 3; auth++) {
				for (sld = 0; sld < 3; sld++) {
					for (tld = 0; tld < 3; tld++) {
						for (port = 0; port < 3; port++) {
							for (path = 0; path < 3; path++) {
								for (query = 0; query < 3; query++) {
									ArrayList<TestResult> noScheme = testRandom (
											numTests, TestParam.Empty, params.get(sep), params.get(auth),
											params.get(sld), params.get(tld), params.get(port), 
											params.get(path), params.get(query)
											);
									printResults(noScheme, numTests, 1);
								}}}}}}}
	
		//Bad separator
		for (scheme = 0; scheme < 3; scheme++) {
			for (auth = 0; auth < 3; auth++) {
				for (sld = 0; sld < 3; sld++) {
					for (tld = 0; tld < 3; tld++) {
						for (port = 0; port < 3; port++) {
							for (path = 0; path < 3; path++) {
								for (query = 0; query < 3; query++) {
									ArrayList<TestResult> badSep = testRandom (
											numTests, params.get(scheme), TestParam.Bad, params.get(auth),
											params.get(sld), params.get(tld), params.get(port), 
											params.get(path), params.get(query)
											);
									printResults(badSep, numTests, 1);
								}}}}}}}
		
		//Empty separator
		for (scheme = 0; scheme < 3; scheme++) {
			for (auth = 0; auth < 3; auth++) {
				for (sld = 0; sld < 3; sld++) {
					for (tld = 0; tld < 3; tld++) {
						for (port = 0; port < 3; port++) {
							for (path = 0; path < 3; path++) {
								for (query = 0; query < 3; query++) {
									ArrayList<TestResult> noSep = testRandom (
											numTests, params.get(scheme), TestParam.Empty, params.get(auth),
											params.get(sld), params.get(tld), params.get(port), 
											params.get(path), params.get(query)
											);
									printResults(noSep, numTests, 1);
								}}}}}}}
		
		;
		//Bad authority
		for (scheme = 0; scheme < 3; scheme++) {
			for (sep = 0; sep < 3; sep++) {
				for (sld = 0; sld < 3; sld++) {
					for (tld = 0; tld < 3; tld++) {
						for (port = 0; port < 3; port++) {
							for (path = 0; path < 3; path++) {
								for (query = 0; query < 3; query++) {
									ArrayList<TestResult> badAuth = testRandom (
											numTests, params.get(scheme), params.get(sep), TestParam.Bad,
											params.get(sld), params.get(tld), params.get(port), 
											params.get(path), params.get(query)
											);
									printResults(badAuth, numTests, 1);
								}}}}}}}
		
		//Empty authority
		for (scheme = 0; scheme < 3; scheme++) {
			for (sep = 0; sep < 3; sep++) {
				for (sld = 0; sld < 3; sld++) {
					for (tld = 0; tld < 3; tld++) {
						for (port = 0; port < 3; port++) {
							for (path = 0; path < 3; path++) {
								for (query = 0; query < 3; query++) {
									ArrayList<TestResult> noAuth = testRandom (
											numTests, params.get(scheme), params.get(sep), TestParam.Empty,
											params.get(sld), params.get(tld), params.get(port), 
											params.get(path), params.get(query)
											);
									printResults(noAuth, numTests, 1);
								}}}}}}}
		
		//Bad second level domain
		for (scheme = 0; scheme < 3; scheme++) {
			for (sep = 0; sep < 3; sep++) {
				for (auth = 0; auth < 3; auth++) {
					for (tld = 0; tld < 3; tld++) {
						for (port = 0; port < 3; port++) {
							for (path = 0; path < 3; path++) {
								for (query = 0; query < 3; query++) {
									ArrayList<TestResult> badSld = testRandom (
											numTests, params.get(scheme), params.get(sep), params.get(auth),
											TestParam.Bad, params.get(tld), params.get(port), 
											params.get(path), params.get(query)
											);
									printResults(badSld, numTests, 1);
								}}}}}}}
		
		//Empty second level domain
		for (scheme = 0; scheme < 3; scheme++) {
			for (sep = 0; sep < 3; sep++) {
				for (auth = 0; auth < 3; auth++) {
					for (tld = 0; tld < 3; tld++) {
						for (port = 0; port < 3; port++) {
							for (path = 0; path < 3; path++) {
								for (query = 0; query < 3; query++) {
									ArrayList<TestResult> noSld = testRandom (
											numTests, params.get(scheme), params.get(sep), params.get(auth),
											TestParam.Empty, params.get(tld), params.get(port), 
											params.get(path), params.get(query)
											);
									printResults(noSld, numTests, 1);
								}}}}}}}
		//Bad top level domain
		for (scheme = 0; scheme < 3; scheme++) {
			for (sep = 0; sep < 3; sep++) {
				for (auth = 0; auth < 3; auth++) {
					for (sld = 0; sld < 3; sld++) {
						for (port = 0; port < 3; port++) {
							for (path = 0; path < 3; path++) {
								for (query = 0; query < 3; query++) {
									ArrayList<TestResult> badTld = testRandom (
											numTests, params.get(scheme), params.get(sep), params.get(auth),
											params.get(sld), TestParam.Bad, params.get(port), 
											params.get(path), params.get(query)
											);
									printResults(badTld, numTests, 1);
								}}}}}}}
		
		//Empty top level domain
		for (scheme = 0; scheme < 3; scheme++) {
			for (sep = 0; sep < 3; sep++) {
				for (auth = 0; auth < 3; auth++) {
					for (sld = 0; sld < 3; sld++) {
						for (port = 0; port < 3; port++) {
							for (path = 0; path < 3; path++) {
								for (query = 0; query < 3; query++) {
									ArrayList<TestResult> noTld = testRandom (
											numTests, params.get(scheme), params.get(sep), params.get(auth),
											params.get(sld), TestParam.Empty, params.get(port), 
											params.get(path), params.get(query)
											);
									printResults(noTld, numTests, 1);
								}}}}}}}	
		
		//Bad port
				for (scheme = 0; scheme < 3; scheme++) {
					for (sep = 0; sep < 3; sep++) {
						for (auth = 0; auth < 3; auth++) {
							for (sld = 0; sld < 3; sld++) {
								for (tld = 0; tld < 3; tld++) {
									for (path = 0; path < 3; path++) {
										for (query = 0; query < 3; query++) {
											ArrayList<TestResult> badPort = testRandom (
													numTests, params.get(scheme), params.get(sep), params.get(auth),
													params.get(sld), params.get(tld), TestParam.Bad, 
													params.get(path), params.get(query)
													);
											printResults(badPort, numTests, 1);
										}}}}}}}	
				
				//Bad path
				for (scheme = 0; scheme < 3; scheme++) {
					for (sep = 0; sep < 3; sep++) {
						for (auth = 0; auth < 3; auth++) {
							for (sld = 0; sld < 3; sld++) {
								for (tld = 0; tld < 3; tld++) {
									for (port = 0; port < 3; port++) {
										for (query = 0; query < 3; query++) {
											ArrayList<TestResult> badPath = testRandom (
													numTests, params.get(scheme), params.get(sep), params.get(auth),
													params.get(sld), params.get(tld), params.get(port), 
													TestParam.Bad, params.get(query)
													);
											printResults(badPath, numTests, 1);
										}}}}}}}	
				
				//Bad query
				for (scheme = 0; scheme < 3; scheme++) {
					for (sep = 0; sep < 3; sep++) {
						for (auth = 0; auth < 3; auth++) {
							for (sld = 0; sld < 3; sld++) {
								for (tld = 0; tld < 3; tld++) {
									for (port = 0; port < 3; port++) {
										for (path = 0; path < 3; path++) {
											ArrayList<TestResult> badQuery = testRandom (
													numTests, params.get(scheme), params.get(sep), params.get(auth),
													params.get(sld), params.get(tld), params.get(port), 
													params.get(path), TestParam.Bad
													);
											printResults(badQuery, numTests, 1);
										}}}}}}}	
	}
	
	public ArrayList<TestParam> randParams() {
		ArrayList<TestParam> params = new ArrayList<TestParam>();
		Random r = new Random();
		for (int i = 0; i < 8; i++) {
			int randInt = r.nextInt(3);
			if (randInt == 0) {
				params.add(i, TestParam.Good);
			}
			else if (randInt == 1) {
				params.add(i, TestParam.Bad);
			}
			else {
				params.add(i, TestParam.Empty);
			}
		}
		return params;
	}
	
	public void printResults(ArrayList<TestResult> res, int numTests, int flag) {
		int failedTests = 0;
		
		//Test result should be valid
		if (flag == 0) {
			for (TestResult t: res) {
				System.out.println(t.valid + "\t" + t.url);
				if(t.valid == false) {		// all should be valid
					failedTests++;
					//System.out.println(t.valid + "\t" + t.url);
				}	
			}
			System.out.println(numTests + " tests\n" + failedTests + " failures.");
		}
		//Test result should be invalid
		if (flag == 1) {
			for (TestResult t: res) {
				System.out.println(t.valid + "\t" + t.url);
				if(t.valid != false) {		// all should be valid
					failedTests++;
					//System.out.println(t.valid + "\t" + t.url);
				}	
			}
			System.out.println(numTests + " tests\n" + failedTests + " failures.");
		}
	}
}
	

