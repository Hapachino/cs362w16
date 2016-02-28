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

import java.io.Console;
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
	private boolean printIndex = false; // print index that indicates current
										// scheme,host,port,path, query test
										// were using.

	public UrlValidatorTest(String testName) {
		super(testName);
	}

	public void testManualTest() {
		UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
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

	public String generateRandomAlphaNumString(int length) {
		Random r = new Random();
		java.lang.StringBuffer sb = new StringBuffer();
		for (int i = 0; i < length; i++) {
			int rInt = (int) 'a' + r.nextInt(36);
			if (rInt > (int) 'z') {
				rInt -= 75; // if number is past 'z', use a digit instead
			}
			sb.append((char) rInt);
		}
		return sb.toString();
	}

	public void testYourFirstPartition() {
		Random r = new Random();
		UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		String testUrl;
		int testCount = 0;
		int failCount = 0;
		for (int i = 0; i < 1000; i++) {
			java.lang.StringBuffer urlSb = new StringBuffer();

			// generate random scheme
			StringBuffer sb = new StringBuffer();
			sb.append((char) ('a' + r.nextInt(26)));
			String rString = generateRandomAlphaNumString(r.nextInt(5));
			if (rString.length() > 0) {
				sb.append(rString);
			}
			sb.append("://");
			urlSb.append(sb);
			
			// generate random authority
			String auth = generateRandomAlphaNumString(1 + r.nextInt(3));
			urlSb.append(auth);
			urlSb.append(".");

			auth = generateRandomAlphaNumString(1 + r.nextInt(100));
			urlSb.append(auth);
			urlSb.append(".");

			auth = generateRandomAlphaNumString(1 + r.nextInt(3));			
			urlSb.append(auth);			
			urlSb.append("/");

			testUrl = urlSb.toString();
			if (!urlVal.isValid(testUrl)) {
				System.out.println("FAIL. Returned not valid:\t" + urlSb);
				failCount++;
			} else {
				System.out.println("pass. Returned valid:\t" + urlSb);
			}
			testCount++;
		}
		System.out.print("\n" + testCount + " tests\n" + failCount + " failures\n");
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
