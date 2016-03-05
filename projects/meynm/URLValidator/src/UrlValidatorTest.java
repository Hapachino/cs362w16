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

}

	

