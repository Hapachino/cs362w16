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

import java.awt.List;
import java.io.BufferedReader;
import java.io.Console;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
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
	
	ArrayList<String> tldList =   new ArrayList<>(Arrays.asList("ac", "ad", "ae", "aero", "af", "ag", "ai", "al", "am", "an", "ao", "aq", "ar", "arpa", "as", "asia", "at", "au", "aw", "ax", "az", "ba", "bb", "bd", "be", "bf", "bg", "bh", "bi", "biz", "bj", "bm", "bn", "bo", "br", "bs", "bt", "bv", "bw", "by", "bz", "ca", "cat", "cc", "cd", "cf", "cg", "ch", "ci", "ck", "cl", "cm", "cn", "co", "com", "coop", "cr", "cu", "cv", "cx", "cy", "cz", "de", "dj", "dk", "dm", "do", "dz", "ec", "edu", "ee", "eg", "er", "es", "et", "eu", "fi", "fj", "fk", "fm", "fo", "fr", "ga", "gb", "gd", "ge", "gf", "gg", "gh", "gi", "gl", "gm", "gn", "gov", "gp", "gq", "gr", "gs", "gt", "gu", "gw", "gy", "hk", "hm", "hn", "hr", "ht", "hu", "id", "ie", "il", "im", "in", "info", "int", "io", "iq", "ir", "is", "it", "je", "jm", "jo", "jobs", "jp", "ke", "kg", "kh", "ki", "km", "kn", "kp", "kr", "kw", "ky", "kz", "la", "lb", "lc", "li", "lk", "lr", "ls", "lt", "lu", "lv", "ly", "ma", "mc", "md", "me", "mg", "mh", "mil", "mk", "ml", "mm", "mn", "mo", "mobi", "mp", "mq", "mr", "ms", "mt", "mu", "museum", "mv", "mw", "mx", "my", "mz", "na", "name", "nc", "ne", "net", "nf", "ng", "ni", "nl", "no", "np", "nr", "nu", "nz", "om", "org", "pa", "pe", "pf", "pg", "ph", "pk", "pl", "pm", "pn", "pr", "pro", "ps", "pt", "pw", "py", "qa", "re", "ro", "root", "rs", "ru", "rw", "sa", "sb", "sc", "sd", "se", "sg", "sh", "si", "sj", "sk", "sl", "sm", "sn", "so", "sr", "st", "su", "sv", "sy", "sz", "tc", "td", "tel", "tf", "tg", "th", "tj", "tk", "tl", "tm", "tn", "to", "tp", "tr", "travel", "tt", "tv", "tw", "tz", "ua", "ug", "uk", "um", "us", "uy", "uz", "va", "vc", "ve", "vg", "vi", "vn", "vu", "wf", "ws", "ye", "yt", "yu", "za", "zm", "zw" ));
	ArrayList<String> urlEncodeList = new ArrayList<>(Arrays.asList("%20", "%20", "%21", "%21", "%22", "%22", "%23", "%23", "%24", "%24", "%", "%25", "%25", "%26", "%26", "%27", "%27", "%28", "%28", "%29", "%29", "%2A", "%2A", "%2B", "%2B", "%2C", "%2C", "%2D", "%2D", "%2E", "%2E", "%2F", "%2F", "%30", "%30", "%31", "%31", "%32", "%32", "%33", "%33", "%34", "%34", "%35", "%35", "%36", "%36", "%37", "%37", "%38", "%38", "%39", "%39", "%3A", "%3A", "%3B", "%3B", "%3C", "%3C", "%3D", "%3D", "%3E", "%3E", "%3F", "%3F", "%40", "%40", "%41", "%41", "%42", "%42", "%43", "%43", "%44", "%44", "%45", "%45", "%46", "%46", "%47", "%47", "%48", "%48", "%49", "%49", "%4A", "%4A", "%4B", "%4B", "%4C", "%4C", "%4D", "%4D", "%4E", "%4E", "%4F", "%4F", "%50", "%50", "%51", "%51", "%52", "%52", "%53", "%53", "%54", "%54", "%55", "%55", "%56", "%56", "%57", "%57", "%58", "%58", "%59", "%59", "%5A", "%5A", "%5B", "%5B", "%5C", "%5C", "%5D", "%5D", "%5E", "%5E", "%5F", "%5F", "%60", "%60", "%61", "%61", "%62", "%62", "%63", "%63", "%64", "%64", "%65", "%65", "%66", "%66", "%67", "%67", "%68", "%68", "%69", "%69", "%6A", "%6A", "%6B", "%6B", "%6C", "%6C", "%6D", "%6D", "%6E", "%6E", "%6F", "%6F", "%70", "%70", "%71", "%71", "%72", "%72", "%73", "%73", "%74", "%74", "%75", "%75", "%76", "%76", "%77", "%77", "%78", "%78", "%79", "%79", "%7A", "%7A", "%7B", "%7B", "%7C", "%7C", "%7D", "%7D", "%7E", "%7E", "%7F", "%7F", "%80", "%E2%82%AC", "%81", "%81", "%82", "%E2%80%9A", "%83", "%C6%92", "%84", "%E2%80%9E", "%85", "%E2%80%A6", "%86", "%E2%80%A0", "%87", "%E2%80%A1", "%88", "%CB%86", "%89", "%E2%80%B0", "%8A", "%C5%A0", "%8B", "%E2%80%B9", "%8C", "%C5%92", "%8D", "%C5%8D", "%8E", "%C5%BD", "%8F", "%8F", "%90", "%C2%90", "%91", "%E2%80%98", "%92", "%E2%80%99", "%93", "%E2%80%9C", "%94", "%E2%80%9D", "%95", "%E2%80%A2", "%96", "%E2%80%93", "%97", "%E2%80%94", "%98", "%CB%9C", "%99", "%E2%84", "%9A", "%C5%A1", "%9B", "%E2%80", "%9C", "%C5%93", "%9D", "%9D", "%9E", "%C5%BE", "%9F", "%C5%B8", "%A0", "%C2%A0", "%A1", "%C2%A1", "%A2", "%C2%A2", "%A3", "%C2%A3", "%A4", "%C2%A4", "%A5", "%C2%A5", "%A6", "%C2%A6", "%A7", "%C2%A7", "%A8", "%C2%A8", "%A9", "%C2%A9", "%AA", "%C2%AA", "%AB", "%C2%AB", "%AC", "%C2%AC", "%AD", "%C2%AD", "%AE", "%C2%AE", "%AF", "%C2%AF", "%B0", "%C2%B0", "%B1", "%C2%B1", "%B2", "%C2%B2", "%B3", "%C2%B3", "%B4", "%C2%B4", "%B5", "%C2%B5", "%B6", "%C2%B6", "%B7", "%C2%B7", "%B8", "%C2%B8", "%B9", "%C2%B9", "%BA", "%C2%BA", "%BB", "%C2%BB", "%BC", "%C2%BC", "%BD", "%C2%BD", "%BE", "%C2%BE", "%BF", "%C2%BF", "%C0", "%C3%80", "%C1", "%C3%81", "%C2", "%C3%82", "%C3", "%C3%83", "%C4", "%C3%84", "%C5", "%C3%85", "%C6", "%C3%86", "%C7", "%C3%87", "%C8", "%C3%88", "%C9", "%C3%89", "%CA", "%C3%8A", "%CB", "%C3%8B", "%CC", "%C3%8C", "%CD", "%C3%8D", "%CE", "%C3%8E", "%CF", "%C3%8F", "%D0", "%C3%90", "%D1", "%C3%91", "%D2", "%C3%92", "%D3", "%C3%93", "%D4", "%C3%94", "%D5", "%C3%95", "%D6", "%C3%96", "%D7", "%C3%97", "%D8", "%C3%98", "%D9", "%C3%99", "%DA", "%C3%9A", "%DB", "%C3%9B", "%DC", "%C3%9C", "%DD", "%C3%9D", "%DE", "%C3%9E", "%DF", "%C3%9F", "%E0", "%C3%A0", "%E1", "%C3%A1", "%E2", "%C3%A2", "%E3", "%C3%A3", "%E4", "%C3%A4", "%E5", "%C3%A5", "%E6", "%C3%A6", "%E7", "%C3%A7", "%E8", "%C3%A8", "%E9", "%C3%A9", "%EA", "%C3%AA", "%EB", "%C3%AB", "%EC", "%C3%AC", "%ED", "%C3%AD", "%EE", "%C3%AE", "%EF", "%C3%AF", "%F0", "%C3%B0", "%F1", "%C3%B1", "%F2", "%C3%B2", "%F3", "%C3%B3", "%F4", "%C3%B4", "%F5", "%C3%B5", "%F6", "%C3%B6", "%F7", "%C3%B7", "%F8", "%C3%B8", "%F9", "%C3%B9", "%FA", "%C3%BA", "%FB", "%C3%BB", "%FC", "%C3%BC", "%FD", "%C3%BD", "%FE", "%C3%BE", "%FF", "%C3%BF"));
}
	

