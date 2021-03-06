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
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
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
	String randomBadTestResultsPath = "randomBadTestResults.txt";
	
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
        inputUrl.add("http://0.0.0.0");
        inputUrl.add("http://-1.0.0.0");
        inputUrl.add("http://256.66.32.1");
        inputUrl.add("http://174.80.32.4352");
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
        inputUrl.add("https://www.yahoo.com:443");
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
        inputUrl.add("https://www.yahoo.com:443");
        inputUrl.add("ftp://www.yahoo.com:20");
        inputUrl.add("ftp://www.yahoo.com:21");
        inputUrl.add("pop3://www.yahoo.com:110");
        inputUrl.add("custprot://www.yahoo.com:7020");
        inputUrl.add("http://www.oregonstate.edu/~somestudent");
        inputUrl.add("http://www.yahoo.com:999");
        inputUrl.add("http://www.yahoo.com:1000");
        inputUrl.add("http:///www.yahoo.com");
        inputUrl.add("http://www.yahoo.com//foobar");
        
        for(String s : inputUrl)
        {
        	System.out.println(urlVal.isValid(s) + "\t" + s);
        }
		
	}
	
	public int getPortForScheme(String scheme){
		Boolean use2ndPort = (new Random()).nextInt(2) == 1 ? true : false;
		int port;
		
		switch (scheme){
			case "FTP": port = use2ndPort ? 21 : 20; break;
			case "TFTP": port = 69; break;
			case "NFS": port = 111; break;
			case "SNMP": port = use2ndPort ? 162 : 161; break;
			case "SMTP": port = use2ndPort ? 587 : 25; break;
			case "HTTP": port = 80; break;
			case "HTTPS": port = 443; break;
			case "BOOTP": port = 68; break;
			case "DHCP": port = use2ndPort ? 68 : 67; break;
			case "BGP": port = 179; break;
			case "EGP": port = 8; break;
			case "IGP": port = 9; break;
			case "RIP": port = 520; break;
			case "OSPF": port = use2ndPort ? 89 : 88; break;
			case "POP2": port = 109; break;
			case "POP3": port = 110; break;
			case "IMAP": port = 143; break;
			case "Telnet": port = 23; break;
			case "TCP": port = 6; break;
			case "UDP": port = use2ndPort ? 21 : 20; break;
			case "ICMP": port = 1; break;
			case "CBT": port = 6; break;
			default: port = 0; break;
		}
		
		return port;
	}
	
	// Schemes/protocols can be any string of any length that begins with a letter
	// and has no special characters. If 'true' is passed for the 'valid' param,
	// this method generates a string that matches the criteria. If 'false' is passed,
	// the method ensures that an invalid scheme is generated.
	public String generateRandomScheme(Boolean valid, int length){
		Random r = new Random();
		String retStr = "0";
		
		if (valid){
			// Do a coin flip to decide whether to return one of the establish TCP/IP Networking Protocols.
			// If we don't use one the established ones, we generate a valid one so simulate a real-world 
			// scenario where a user creates their own. The coin flip is biased (66.6% chance) toward using
			// an established protocol such as http, udp, dns, etc....
			Boolean useCommonScheme = (r.nextInt(3) < 2) ? true : false;
			
			if (useCommonScheme){
				// Return a randomly selected scheme from the common scheme list
				return schemeList.get((r.nextInt(schemeList.size() - 1)));
			}
			
			// If not using a common scheme, generate a valid string.
			// Keep generating random strings until we get one without a number at the beginning, 
			// because valid schemes must begin with a letter and can't have special characters.
			while (!Character.isLetter(retStr.charAt(0))) {
				retStr = generateRandomString(length, false, false);
			}
		} else {
			// Randomly decide whether or not to use white space
			Boolean useWhiteSpace = (r.nextInt(2) == 0) ? true : false;
			// Ensure we get an invalid scheme by sticking a special char in it
			retStr += "" + "#$%^&".charAt(r.nextInt(5));
			retStr += generateRandomString(length, true, useWhiteSpace);
		}
		
		return retStr;
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
	
	// This overload of generateRandomString() guarantees the string returned will contain at least one of the characters in the 
	// string specialChars
	public String generateRandomString(int length, String specialChars) {
		if(length == 0) {
			return "";
		}
		StringBuffer randomStringBuffer = new StringBuffer();
		Random r = new Random();
		String alphaNumericChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ123456890";
		String numbers = "123456890";
		boolean includesSpecialChars = false;
		for(int i = 0; i < length; i++) 
		{
			if(r.nextInt() % 3 == 0) {
				randomStringBuffer.append( specialChars.charAt( r.nextInt( specialChars.length() ) ) );
				includesSpecialChars = true;
			}
			else if(r.nextInt() % 5 == 0) {
				randomStringBuffer.append( numbers.charAt( r.nextInt( numbers.length() ) ) );
			}
			else {
				randomStringBuffer.append( alphaNumericChars.charAt(r.nextInt( alphaNumericChars.length() ) ) );
			}
		}
		if(!includesSpecialChars) {
			randomStringBuffer.setCharAt( 
					r.nextInt( randomStringBuffer.length() ), 
					specialChars.charAt( r.nextInt( specialChars.length() ) ) 
			);
		}
		return randomStringBuffer.toString();
	}
	
	public String generateRandomString(int length, Boolean useSpecialChars, Boolean useWhiteSpace) {
		String retStr = "";
		if(length == 0) {
			return retStr;
		}
		Random r = new Random();
		String alphaNumericChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ123456890";
		String numbers = "123456890";
		String specialChars = "~`!@#$%^&*()_+-={}|[]:;'<>?,./'; +";
		
		// Treat lengths of 1 slightly differently
		if (length == 1) {
			int randomRes = r.nextInt(3);
			
			if (randomRes == 0 && useWhiteSpace)
				return " ";
			else if (randomRes == 1 && useSpecialChars)
				return "" + specialChars.charAt(r.nextInt(specialChars.length()));	
			else
				return "" + numbers.charAt(r.nextInt(numbers.length()));
		}
		
		if (useSpecialChars){
			while (retStr.length() < length){			
				// Flip coin for whether to the next char will be alphanumeric or special
				if (r.nextInt(432) % 2 == 0)
					retStr += alphaNumericChars.charAt(r.nextInt(alphaNumericChars.length()));
				else
					retStr += specialChars.charAt(r.nextInt(specialChars.length()));
			}
		} else {
			// Keep adding random alphanumeric chars until the desired length is reached
			 while (retStr.length() < length)
				 retStr += alphaNumericChars.charAt(r.nextInt(alphaNumericChars.length()));
		}
		
		if (useWhiteSpace){
			// Choose a random spot in the string to add white space
			/*
			String charToReplace = "" + retStr.charAt(r.nextInt(retStr.length()));
			retStr = retStr.replaceFirst(charToReplace, " ");
			*/
			StringBuffer rsb = new StringBuffer();
			rsb.append(retStr);
			rsb.setCharAt(r.nextInt(rsb.length()), ' ');
			retStr = rsb.toString();
		}
		
		return retStr;
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
 *			When generating a scheme, we now call some new methods specifically design to handle schemes. You can pass true/false
 *			for the 'valid' param, which will result in a valid/invalid scheme string. That method also makes use of commonly used
 *			known good schemes such as ftp, dns, https, etc...
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
		
		String badChars = " %\\";
		
		for (int i = 0; i < numTests; i++) 
		{
			java.lang.StringBuffer urlSb = new StringBuffer();
			String schemeStr = "";
			
			// generate random scheme
			StringBuffer sb = new StringBuffer();
			if(scheme == TestParam.Good) {
				//sb.append((char) ('a' + r.nextInt(26)));
				String rString = schemeStr = generateRandomScheme(true, 1 + r.nextInt(5)); //generateRandomValidString(r.nextInt(5), new ArrayList<String>());
				sb.append(rString);
			} else if(scheme == TestParam.Bad) {
				String rString = generateRandomScheme(false, r.nextInt(5) ); //generateRandomString(r.nextInt(5));
				if (rString.length() > 0) {
					sb.append(rString);
				}
			}	
			
			if(separator == TestParam.Good) {
				sb.append("://");
			} else if(separator == TestParam.Bad) {
				String s;
				do {
					s = generateRandomString(1 + r.nextInt(4), badChars);
				} while("://" == s);
				sb.append(s);
			}			
			urlSb.append(sb);
			
			// generate random authority
			if(authority == TestParam.Good) {
				urlSb.append(generateRandomString(1 + r.nextInt(3), false, false) + "."); //urlSb.append( generateRandomValidString( 1 + r.nextInt( 3 ), new ArrayList<String>() ) + "." );
			}
			else if(authority == TestParam.Bad) {
				urlSb.append(generateRandomString(1 + r.nextInt(3), true, true) + "."); //urlSb.append( generateRandomString( 1 + r.nextInt( 3 ) ) + "." );
			}					

			// generate random second-level domain
			// According to O'Reilly (http://archive.oreilly.com/pub/post/the_worlds_longest_domain_name.html)
			// the longest legal domain name is 63 characters starting with a letter or number.
			// That is why the length is set to a max of 63 (64 - 1) in the Good sld case.
			for(int j = 0; j < 1 + r.nextInt(5); j++) 
			{
				if(sld == TestParam.Good) {
					urlSb.append(generateRandomString(1 + r.nextInt(64), false, false) + "."); //urlSb.append( generateRandomValidString( 1 + r.nextInt( 100 ), new ArrayList<String>() ) + "." );
				} else if (sld == TestParam.Bad) {
					urlSb.append(generateRandomString(1 + r.nextInt(100), true, true) + "."); //urlSb.append( generateRandomString( 1 + r.nextInt( 100 ) ) + "." );
				} 
			}

			// use a top-level domain from list
			if(tld == TestParam.Good) {
				urlSb.append(tldList.get(testCount % tldList.size()));
			} else if(tld == TestParam.Bad) {
				if(r.nextInt(2) == 0) {
					urlSb.append( generateRandomString( 1 + r.nextInt(5), badChars ) );
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
			// attaching a port only makes sense to the validator if the correct port is used
			// for the given scheme. 
			/*if(port == TestParam.Good) {
				int portNum = 1 + r.nextInt(65535);
				urlSb.append(":" + portNum); */
			if (port != TestParam.Empty) {
				int portNum = 0;
				
				if (port == TestParam.Good && schemeList.contains(schemeStr)) {
					portNum = getPortForScheme(schemeStr);
				} else if(port == TestParam.Bad) {
					portNum = 65536 + r.nextInt(Integer.MAX_VALUE - 65536);
					if(testCount % 10 == 0) {
						portNum = 0 - r.nextInt();
					}
				}
				
				urlSb.append( ":" + portNum );
			}
		 	
			
			// generate a random path, or none
			if(path == TestParam.Good) {	
					//String pathString = generateRandomValidString(1 + r.nextInt(10), urlEncodeList);
					
					// Start with some randomly generated alphanumeric string
					String pathString = generateRandomString(1 + r.nextInt(10), false, false);
					
					if(pathString.length() > 0) {
						urlSb.append("/");
						
						if(r.nextInt(5) == 0) {
							String unreservedSet = "-_.!~*'()";
							urlSb.append(r.nextInt(unreservedSet.length()));
						}
						
						urlSb.append(pathString);
					}
			} else if(path == TestParam.Bad) {
				for(int j = 0; j < 1 + r.nextInt(3); j++) 
				{
					//String pathString = generateRandomString(1 + r.nextInt(10));					
					Boolean useWhiteSpace = r.nextInt(7) == 0; 
					String pathString = generateRandomString(1 + r.nextInt(10), false, useWhiteSpace);
					if(pathString.length() > 0) {
						urlSb.append("/" + pathString);
					}
				}
			}
			
			// generate a random query, or none
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
					// Valid parameter names do not have encoded chars, do not have special chars, and begin with a letter
					// (the naming convention follows C-based programming language conventions because they are normally 
					// consumed by C-based languages.
					String letters = "abcdefghijklmnopqrstuvwxyz";
					queryString = "" + letters.charAt(r.nextInt(letters.length())); 
					queryString += generateRandomString(1 + r.nextInt(10), false, false);
				} else {
					queryString = generateRandomString(1 + r.nextInt(10), badChars);
				}
				
				urlSb.append(queryString + "=");
				
				// Two random string generator methods are used below to ensure variety of characters. generateRandomString is 
				// a little better at returning special characters.
				if(query == TestParam.Good) {
					// Valid value portions of the query strings cannot have = signs because that is used to 
					// signify the value of a parameter.
					String valueStr = generateRandomValidString(1 + r.nextInt(10), urlEncodeList) + generateRandomString(1 + r.nextInt(5), true, false);
					valueStr = valueStr.replace("=", "");
					queryString = valueStr;
				} else {
					queryString = generateRandomString(1 + r.nextInt(10), badChars) + generateRandomString(1 + r.nextInt(5), true, false);
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
		
		try{
			FileWriter fw = new FileWriter(randomBadTestResultsPath, false);
			fw.close();
		}
		catch(IOException e) {
			System.out.println("Error resetting random bad test result file.");
			return;
		}
		
		int numTests = 1000;
		int scheme, sep, auth, sld, tld, port, path, query;
		ArrayList<TestParam> params = new ArrayList<TestParam>();
		params.add(0, TestParam.Good);
		params.add(1, TestParam.Bad);
		params.add(2, TestParam.Empty);
		
		for (scheme = 0; scheme < 3; scheme++) {
			for (sep = 0; sep < 3; sep++) {
				for (auth = 0; auth < 3; auth++) {
					for (sld = 0; sld < 3; sld++) {
						for (tld = 0; tld < 3; tld++) {
							for (port = 0; port < 3; port++) {
								for (path = 0; path < 3; path++) {
									for (query = 0; query < 3; query++) {
										if(scheme+sep+auth+sld+tld == 0 && port != 1 && path != 1 && query != 1) {
												continue;																						
										} else {
											String header = 
													"scheme: " + scheme +
													"\tseparator: " + sep + 
													"\tauthority: " + auth + 
													"\tSLD: " + sld +
													"\tTLD: " + tld +
													"\tport: " + port +
													"\tpath: " + path +
													"\tquery: " + query;
											System.out.println("Testing " + header);
											ArrayList<TestResult> tResults = testRandom (
													numTests, TestParam.Bad, params.get(sep), params.get(auth),
													params.get(sld), params.get(tld), params.get(port), 
													params.get(path), params.get(query)
											);											
											logResults( randomBadTestResultsPath, header, tResults, numTests, false);
										}
										
									
		}}}}}}}}
	}
	
	/*
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
	*/
	
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
				//System.out.println(t.valid + "\t" + t.url);
				if(t.valid == false) {		// all should be valid
					failedTests++;
					System.out.println(t.valid + "\t" + t.url);
				}	
			}
			//System.out.println(numTests + " tests\n" + failedTests + " failures.");
		}
		//Test result should be invalid
		if (flag == 1) {
			for (TestResult t: res) {
				//System.out.println(t.valid + "\t" + t.url);
				if(t.valid != false) {		// all should be valid
					failedTests++;
					System.out.println(t.valid + "\t" + t.url);
				}	
			}
			//System.out.println(numTests + " tests\n" + failedTests + " failures.");
		}
		
		if (failedTests > 0)
			System.out.println(numTests + " tests\n" + failedTests + " failures.");
	}
	
	public void logResults(String path, String header, ArrayList<TestResult> res, int numTests, boolean flag) {
		FileWriter fw = null;
		PrintWriter pw = null;
		try {
			if(null != (fw = new FileWriter(path,true) )) {
				pw = new PrintWriter(fw);
			}
		} catch (IOException e) {
			e.printStackTrace();
			return;
		}		
		pw.println("\n\t**********\t" + header + "\t**********");
		int failCount = 0, testCount = 0;
		for(TestResult t : res) 
		{
			testCount++;
			if(t.valid != flag) {
				pw.print("FAIL:\t" + t.valid + "\t" + t.url + "\n");
				failCount++;
			}		
		}
		pw.println("\t" + testCount + " tests");
		if(failCount > 0) {
			pw.println("\t" + failCount + " failures");
		}
		if(pw != null) {
			pw.close();
		}
	}
	
	ArrayList<String> tldList =   new ArrayList<>(Arrays.asList("ac", "ad", "ae", "aero", "af", "ag", "ai", "al", "am", "an", "ao", "aq", "ar", "arpa", "as", "asia", "at", "au", "aw", "ax", "az", "ba", "bb", "bd", "be", "bf", "bg", "bh", "bi", "biz", "bj", "bm", "bn", "bo", "br", "bs", "bt", "bv", "bw", "by", "bz", "ca", "cat", "cc", "cd", "cf", "cg", "ch", "ci", "ck", "cl", "cm", "cn", "co", "com", "coop", "cr", "cu", "cv", "cx", "cy", "cz", "de", "dj", "dk", "dm", "do", "dz", "ec", "edu", "ee", "eg", "er", "es", "et", "eu", "fi", "fj", "fk", "fm", "fo", "fr", "ga", "gb", "gd", "ge", "gf", "gg", "gh", "gi", "gl", "gm", "gn", "gov", "gp", "gq", "gr", "gs", "gt", "gu", "gw", "gy", "hk", "hm", "hn", "hr", "ht", "hu", "id", "ie", "il", "im", "in", "info", "int", "io", "iq", "ir", "is", "it", "je", "jm", "jo", "jobs", "jp", "ke", "kg", "kh", "ki", "km", "kn", "kp", "kr", "kw", "ky", "kz", "la", "lb", "lc", "li", "lk", "lr", "ls", "lt", "lu", "lv", "ly", "ma", "mc", "md", "me", "mg", "mh", "mil", "mk", "ml", "mm", "mn", "mo", "mobi", "mp", "mq", "mr", "ms", "mt", "mu", "museum", "mv", "mw", "mx", "my", "mz", "na", "name", "nc", "ne", "net", "nf", "ng", "ni", "nl", "no", "np", "nr", "nu", "nz", "om", "org", "pa", "pe", "pf", "pg", "ph", "pk", "pl", "pm", "pn", "pr", "pro", "ps", "pt", "pw", "py", "qa", "re", "ro", "root", "rs", "ru", "rw", "sa", "sb", "sc", "sd", "se", "sg", "sh", "si", "sj", "sk", "sl", "sm", "sn", "so", "sr", "st", "su", "sv", "sy", "sz", "tc", "td", "tel", "tf", "tg", "th", "tj", "tk", "tl", "tm", "tn", "to", "tp", "tr", "travel", "tt", "tv", "tw", "tz", "ua", "ug", "uk", "um", "us", "uy", "uz", "va", "vc", "ve", "vg", "vi", "vn", "vu", "wf", "ws", "ye", "yt", "yu", "za", "zm", "zw" ));
	ArrayList<String> urlEncodeList = new ArrayList<>(Arrays.asList("%20", "%20", "%21", "%21", "%22", "%22", "%23", "%23", "%24", "%24", "%", "%25", "%25", "%26", "%26", "%27", "%27", "%28", "%28", "%29", "%29", "%2A", "%2A", "%2B", "%2B", "%2C", "%2C", "%2D", "%2D", "%2E", "%2E", "%2F", "%2F", "%30", "%30", "%31", "%31", "%32", "%32", "%33", "%33", "%34", "%34", "%35", "%35", "%36", "%36", "%37", "%37", "%38", "%38", "%39", "%39", "%3A", "%3A", "%3B", "%3B", "%3C", "%3C", "%3D", "%3D", "%3E", "%3E", "%3F", "%3F", "%40", "%40", "%41", "%41", "%42", "%42", "%43", "%43", "%44", "%44", "%45", "%45", "%46", "%46", "%47", "%47", "%48", "%48", "%49", "%49", "%4A", "%4A", "%4B", "%4B", "%4C", "%4C", "%4D", "%4D", "%4E", "%4E", "%4F", "%4F", "%50", "%50", "%51", "%51", "%52", "%52", "%53", "%53", "%54", "%54", "%55", "%55", "%56", "%56", "%57", "%57", "%58", "%58", "%59", "%59", "%5A", "%5A", "%5B", "%5B", "%5C", "%5C", "%5D", "%5D", "%5E", "%5E", "%5F", "%5F", "%60", "%60", "%61", "%61", "%62", "%62", "%63", "%63", "%64", "%64", "%65", "%65", "%66", "%66", "%67", "%67", "%68", "%68", "%69", "%69", "%6A", "%6A", "%6B", "%6B", "%6C", "%6C", "%6D", "%6D", "%6E", "%6E", "%6F", "%6F", "%70", "%70", "%71", "%71", "%72", "%72", "%73", "%73", "%74", "%74", "%75", "%75", "%76", "%76", "%77", "%77", "%78", "%78", "%79", "%79", "%7A", "%7A", "%7B", "%7B", "%7C", "%7C", "%7D", "%7D", "%7E", "%7E", "%7F", "%7F", "%80", "%E2%82%AC", "%81", "%81", "%82", "%E2%80%9A", "%83", "%C6%92", "%84", "%E2%80%9E", "%85", "%E2%80%A6", "%86", "%E2%80%A0", "%87", "%E2%80%A1", "%88", "%CB%86", "%89", "%E2%80%B0", "%8A", "%C5%A0", "%8B", "%E2%80%B9", "%8C", "%C5%92", "%8D", "%C5%8D", "%8E", "%C5%BD", "%8F", "%8F", "%90", "%C2%90", "%91", "%E2%80%98", "%92", "%E2%80%99", "%93", "%E2%80%9C", "%94", "%E2%80%9D", "%95", "%E2%80%A2", "%96", "%E2%80%93", "%97", "%E2%80%94", "%98", "%CB%9C", "%99", "%E2%84", "%9A", "%C5%A1", "%9B", "%E2%80", "%9C", "%C5%93", "%9D", "%9D", "%9E", "%C5%BE", "%9F", "%C5%B8", "%A0", "%C2%A0", "%A1", "%C2%A1", "%A2", "%C2%A2", "%A3", "%C2%A3", "%A4", "%C2%A4", "%A5", "%C2%A5", "%A6", "%C2%A6", "%A7", "%C2%A7", "%A8", "%C2%A8", "%A9", "%C2%A9", "%AA", "%C2%AA", "%AB", "%C2%AB", "%AC", "%C2%AC", "%AD", "%C2%AD", "%AE", "%C2%AE", "%AF", "%C2%AF", "%B0", "%C2%B0", "%B1", "%C2%B1", "%B2", "%C2%B2", "%B3", "%C2%B3", "%B4", "%C2%B4", "%B5", "%C2%B5", "%B6", "%C2%B6", "%B7", "%C2%B7", "%B8", "%C2%B8", "%B9", "%C2%B9", "%BA", "%C2%BA", "%BB", "%C2%BB", "%BC", "%C2%BC", "%BD", "%C2%BD", "%BE", "%C2%BE", "%BF", "%C2%BF", "%C0", "%C3%80", "%C1", "%C3%81", "%C2", "%C3%82", "%C3", "%C3%83", "%C4", "%C3%84", "%C5", "%C3%85", "%C6", "%C3%86", "%C7", "%C3%87", "%C8", "%C3%88", "%C9", "%C3%89", "%CA", "%C3%8A", "%CB", "%C3%8B", "%CC", "%C3%8C", "%CD", "%C3%8D", "%CE", "%C3%8E", "%CF", "%C3%8F", "%D0", "%C3%90", "%D1", "%C3%91", "%D2", "%C3%92", "%D3", "%C3%93", "%D4", "%C3%94", "%D5", "%C3%95", "%D6", "%C3%96", "%D7", "%C3%97", "%D8", "%C3%98", "%D9", "%C3%99", "%DA", "%C3%9A", "%DB", "%C3%9B", "%DC", "%C3%9C", "%DD", "%C3%9D", "%DE", "%C3%9E", "%DF", "%C3%9F", "%E0", "%C3%A0", "%E1", "%C3%A1", "%E2", "%C3%A2", "%E3", "%C3%A3", "%E4", "%C3%A4", "%E5", "%C3%A5", "%E6", "%C3%A6", "%E7", "%C3%A7", "%E8", "%C3%A8", "%E9", "%C3%A9", "%EA", "%C3%AA", "%EB", "%C3%AB", "%EC", "%C3%AC", "%ED", "%C3%AD", "%EE", "%C3%AE", "%EF", "%C3%AF", "%F0", "%C3%B0", "%F1", "%C3%B1", "%F2", "%C3%B2", "%F3", "%C3%B3", "%F4", "%C3%B4", "%F5", "%C3%B5", "%F6", "%C3%B6", "%F7", "%C3%B7", "%F8", "%C3%B8", "%F9", "%C3%B9", "%FA", "%C3%BA", "%FB", "%C3%BB", "%FC", "%C3%BC", "%FD", "%C3%BD", "%FE", "%C3%BE", "%FF", "%C3%BF"));
	ArrayList<String> schemeList =   new ArrayList<>(Arrays.asList("FTP", "TFTP", "NFS", "SNMP", "SMTP", "HTTP", "HTTPS", "BOOTP", "DHCP", "BGP", "EGP", "IGP", "RIP", "OSPF", "POP3", "IMAP", "Telnet", "POP2", "TCP", "UDP", "ICMP"));
}
	

