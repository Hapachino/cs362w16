/* Licensed to the Apache Software Foundation (ASF) under one or more
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

  public UrlValidatorTest(String testName) {
    super(testName);
  }

  public void testManualTest()
  {
	/**********************************************************************************
	 * TEST 1: ALLOW ALL SCHEMES  
	 *********************************************************************************/
    UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

    System.out.println("=================================== \n");
    System.out.println("MANUAL TESTING:Allowing all schemes \n");
    System.out.println("=================================== \n");
    
    // ------------------scheme----------------------------------
    System.out.println("----------SCHEME----------------------------------------------");
    System.out.println("Should Validate");
    // test http://
    System.out.println("http://www.google.com" + "\t\t\t\tResult: " + urlVal.isValid("http://www.google.com"));
    
    // test no http://
    System.out.println("www.google.com" + "\t\t\t\t\tResult: " + urlVal.isValid("www.google.com"));
    
    // test h3tp://
    System.out.println("h3tp://www.google.com" + "\t\t\t\tResult: " + urlVal.isValid("h3tp://www.google.com"));
    
    System.out.println("\nShould Not Validate");
    // test :/
    System.out.println(":/www.google.com" + "\t\t\t\tResult: " + urlVal.isValid(":/www.google.com"));
    
    // test ://
    System.out.println("://www.google.com" + "\t\t\t\tResult: " + urlVal.isValid("://www.google.com"));

    // ------------------authority----------------------------------
    System.out.println("\n----------AUTHORITY-------------------------------------------");
    System.out.println("Should Validate");
    // test .au
    System.out.println("http://www.google.au" + "\t\t\t\tResult: " + urlVal.isValid("http://www.google.au"));
    
    System.out.println("\nShould Not Validate");
    // test illegal character
    System.out.println("http://www.google~.com" + "\t\t\t\tResult: " + urlVal.isValid("http://www.google~.com"));
    
    // test missing .com
    System.out.println("http://www.google" + "\t\t\t\tResult: " + urlVal.isValid("http://www.google"));
    
    // test made up url
    System.out.println("http://my.hostname.com" + "\t\t\t\tResult: " + urlVal.isValid("http://my.hostname.com"));
    
    // test numbers
    System.out.println("http://1.2.3" + "\t\t\t\t\tResult: " + urlVal.isValid("http://1.2.3"));
    
    // test blank
    System.out.println("http://<blank>" + "\t\t\t\t\tResult: " + urlVal.isValid("http:// "));
    
    // ------------------port----------------------------------
    System.out.println("\n----------PORT------------------------------------------------");
    System.out.println("Should Validate");
    // test valid port 80
    System.out.println("http://www.google.com:80" + "\t\t\tResult: " + urlVal.isValid("http://www.google.com:80"));
    
    // test 3 digit port
    System.out.println("http://www.google.com:800" + "\t\t\tResult: " + urlVal.isValid("http://www.google.com:800"));
    
    // test 4 digit port
    System.out.println("http://www.google.com:8000" + "\t\t\tResult: " + urlVal.isValid("http://www.google.com:8000"));
    
    // test 5 digit port
    System.out.println("http://www.google.com:80000" + "\t\t\tResult: " + urlVal.isValid("http://www.google.com:80000"));
    
    System.out.println("\nShould Not Validate:");
    // test : missing port number
    System.out.println("http://www.google.com:" + "\t\t\t\tResult: " + urlVal.isValid("http://www.google.com:"));
    
    // test negative port number
    System.out.println("http://www.google.com:-80" + "\t\t\tResult: " + urlVal.isValid("http://www.google.com:-80"));
    
    // test alphanumeric port number
    System.out.println("http://www.google.com:80a" + "\t\t\tResult: " + urlVal.isValid("http://www.google.com:80a"));
    
    // ------------------path----------------------------------
    System.out.println("\n----------PATH------------------------------------------------");
    System.out.println("Should Validate: ");
    // test root path test
    System.out.println("http://www.google.com/test" + "\t\t\tResult: " + urlVal.isValid("http://www.google.com/test"));
    
    // test path with only /
    System.out.println("http://www.google.com/" + "\t\t\t\tResult: " + urlVal.isValid("http://www.google.com/"));
    
    System.out.println("\nShould Not Validate: ");
    // test missing / on path
    System.out.println("http://www.google.comtest" + "\t\t\tResult: " + urlVal.isValid("http://www.google.comtest"));
    
    // test // on path
    System.out.println("http://www.google.com//test" + "\t\t\tResult: " + urlVal.isValid("http://www.google.com//test"));
    
    // test illegal character on path
    System.out.println("http://www.google.com/.." + "\t\t\tResult: " + urlVal.isValid("http://www.google.com/.."));
    
    // test 2 level deep path with illegal characters
    System.out.println("http://www.google.com/../" + "\t\t\tResult: " + urlVal.isValid("http://www.google.com/../"));
    
    // test spaces in path
    System.out.println("http://www.google.com       /" + "\t\t\tResult: " + urlVal.isValid("http://www.google.com         /"));
    

    // ------------------option----------------------------------
    System.out.println("\n----------PATH OPTIONS---------------------------------------");
    System.out.println("Should Validate: ");
    // test valid two level deep path
    System.out.println("http://www.google.com/test/test" + "\t\t\tResult: " + urlVal.isValid("http://www.google.com/test/test"));
    
    // test trailing / on path
    System.out.println("http://www.google.com/test/" + "\t\t\tResult: " + urlVal.isValid("http://www.google.com/test/"));
    
    // test missing / on two level deep path
    System.out.println("http://www.google.com/testtest" + "\t\t\tResult: " + urlVal.isValid("http://www.google.com/testtest"));
    
    System.out.println("\nShould Not Validate: ");
    // test missing / on two level deep path
    System.out.println("http://www.google.comtesttest" + "\t\t\tResult: " + urlVal.isValid("http://www.google.comtesttest"));
    
    // test // on two level deep path
    System.out.println("http://www.google.com/test//test" + "\t\tResult: " + urlVal.isValid("http://www.google.com/test//test"));

    // ------------------queries----------------------------------
    System.out.println("\n----------QUERIES--------------------------------------------");
    System.out.println("Should Validate:");
    // test valid query
    System.out.println("http://www.google.com?query=test" + "\t\tResult: " + urlVal.isValid("http://www.google.com?query=test"));
    
    //test query with & added
    System.out.println("http://www.google.com?query=test&hi=hello" + "\tResult: " + urlVal.isValid("http://www.google.com?query=test&hi=hello"));
    
    System.out.println("\nShould Not Validate: ");
    // test missing test
    System.out.println("http://www.google.com?query=" + "\t\t\tResult: " + urlVal.isValid("http://www.google.com?query="));
    
    // test missing ?query
    System.out.println("http://www.google.com=test" + "\t\t\tResult: " + urlVal.isValid("http://www.google.com=test"));
    
    // test ??
    System.out.println("http://www.google.com??query=test" + "\t\tResult: " + urlVal.isValid("http://www.google.com??query=test"));

    
    /**********************************************************************************
	 * TEST 2: NO FRAGMENTS  
	 *********************************************************************************/
    UrlValidator urlVal2 = new UrlValidator(null, null, UrlValidator.NO_FRAGMENTS);
    System.out.println("\n==================================== \n");
    System.out.println("MANUAL TESTING:Allowing No Fragments \n");
    System.out.println("==================================== \n");
    
    System.out.println("----------SCHEME----------------------------------------------");
    System.out.println("Should Validate");
    // test http://
    System.out.println("http://www.google.com" + "\t\t\t\tResult: " + urlVal2.isValid("http://www.google.com"));
    
    // test no http://
    System.out.println("www.google.com" + "\t\t\t\t\tResult: " + urlVal2.isValid("www.google.com"));
    
    // test h3tp://
    System.out.println("h3tp://www.google.com" + "\t\t\t\tResult: " + urlVal2.isValid("h3tp://www.google.com"));
    
    System.out.println("\nShould Not Validate");
    // test :/
    System.out.println(":/www.google.com" + "\t\t\t\tResult: " + urlVal2.isValid(":/www.google.com"));
    
    // test ://
    System.out.println("://www.google.com" + "\t\t\t\tResult: " + urlVal2.isValid("://www.google.com"));

    // ------------------authority----------------------------------
    System.out.println("\n----------AUTHORITY-------------------------------------------");
    System.out.println("Should Validate");
    // test .au
    System.out.println("http://www.google.au" + "\t\t\t\tResult: " + urlVal2.isValid("http://www.google.au"));
    
    System.out.println("\nShould Not Validate");
    // test illegal character
    System.out.println("http://www.google~.com" + "\t\t\t\tResult: " + urlVal2.isValid("http://www.google~.com"));
    
    // test missing .com
    System.out.println("http://www.google" + "\t\t\t\tResult: " + urlVal2.isValid("http://www.google"));
    
    // test made up url
    System.out.println("http://my.hostname.com" + "\t\t\t\tResult: " + urlVal2.isValid("http://my.hostname.com"));
    
    // test numbers
    System.out.println("http://1.2.3" + "\t\t\t\t\tResult: " + urlVal2.isValid("http://1.2.3"));
    
    // test blank
    System.out.println("http://<blank>" + "\t\t\t\t\tResult: " + urlVal2.isValid("http:// "));
    
    // ------------------port----------------------------------
    System.out.println("\n----------PORT------------------------------------------------");
    System.out.println("Should Validate");
    // test valid port 80
    System.out.println("http://www.google.com:80" + "\t\t\tResult: " + urlVal2.isValid("http://www.google.com:80"));
    
    // test 3 digit port
    System.out.println("http://www.google.com:800" + "\t\t\tResult: " + urlVal2.isValid("http://www.google.com:800"));
    
    // test 4 digit port
    System.out.println("http://www.google.com:8000" + "\t\t\tResult: " + urlVal2.isValid("http://www.google.com:8000"));
    
    // test 5 digit port
    System.out.println("http://www.google.com:80000" + "\t\t\tResult: " + urlVal2.isValid("http://www.google.com:80000"));
    
    System.out.println("\nShould Not Validate:");
    // test : missing port number
    System.out.println("http://www.google.com:" + "\t\t\t\tResult: " + urlVal2.isValid("http://www.google.com:"));
    
    // test negative port number
    System.out.println("http://www.google.com:-80" + "\t\t\tResult: " + urlVal2.isValid("http://www.google.com:-80"));
    
    // test alphanumeric port number
    System.out.println("http://www.google.com:80a" + "\t\t\tResult: " + urlVal2.isValid("http://www.google.com:80a"));

    // ------------------path----------------------------------
    System.out.println("\n----------PATH------------------------------------------------");
    System.out.println("Should Validate: ");
    // test root path test
    System.out.println("http://www.google.com/test" + "\t\t\tResult: " + urlVal2.isValid("http://www.google.com/test"));
    
    // test path with only /
    System.out.println("http://www.google.com/" + "\t\t\t\tResult: " + urlVal2.isValid("http://www.google.com/"));
    
    System.out.println("\nShould Not Validate: ");
    // test missing / on path
    System.out.println("http://www.google.comtest" + "\t\t\tResult: " + urlVal2.isValid("http://www.google.comtest"));
    
    // test // on path
    System.out.println("http://www.google.com//test" + "\t\t\tResult: " + urlVal2.isValid("http://www.google.com//test"));
    
    // test illegal character on path
    System.out.println("http://www.google.com/.." + "\t\t\tResult: " + urlVal2.isValid("http://www.google.com/.."));
    
    // test 2 level deep path with illegal characters
    System.out.println("http://www.google.com/../" + "\t\t\tResult: " + urlVal2.isValid("http://www.google.com/../"));
    
    // test spaces in path
    System.out.println("http://www.google.com       /" + "\t\t\tResult: " + urlVal2.isValid("http://www.google.com         /"));

    // ------------------option----------------------------------
    System.out.println("\n----------PATH OPTIONS---------------------------------------");
    System.out.println("Should Validate: ");
    // test valid two level deep path
    System.out.println("http://www.google.com/test/test" + "\t\t\tResult: " + urlVal2.isValid("http://www.google.com/test/test"));
    
    // test trailing / on path
    System.out.println("http://www.google.com/test/" + "\t\t\tResult: " + urlVal2.isValid("http://www.google.com/test/"));
    
    // test missing / on two level deep path
    System.out.println("http://www.google.com/testtest" + "\t\t\tResult: " + urlVal2.isValid("http://www.google.com/testtest"));
    
    System.out.println("\nShould Not Validate: ");
    // test missing / on two level deep path
    System.out.println("http://www.google.comtesttest" + "\t\t\tResult: " + urlVal2.isValid("http://www.google.comtesttest"));
    
    // test // on two level deep path
    System.out.println("http://www.google.com/test//test" + "\t\tResult: " + urlVal2.isValid("http://www.google.com/test//test"));

    // ------------------queries----------------------------------
    System.out.println("\n----------QUERIES--------------------------------------------");
    System.out.println("Should Validate:");
    // test valid query
    System.out.println("http://www.google.com?query=test" + "\t\tResult: " + urlVal2.isValid("http://www.google.com?query=test"));
    
    //test query with & added
    System.out.println("http://www.google.com?query=test&hi=hello" + "\tResult: " + urlVal2.isValid("http://www.google.com?query=test&hi=hello"));
    
    System.out.println("\nShould Not Validate: ");
    // test missing test
    System.out.println("http://www.google.com?query=" + "\t\t\tResult: " + urlVal2.isValid("http://www.google.com?query="));
    
    // test missing ?query
    System.out.println("http://www.google.com=test" + "\t\t\tResult: " + urlVal2.isValid("http://www.google.com=test"));
    
    // test ??
    System.out.println("http://www.google.com??query=test" + "\t\tResult: " + urlVal2.isValid("http://www.google.com??query=test"));

    /**********************************************************************************
	 * TEST 3: ALLOW LOCAL URLS  
	 *********************************************************************************/
    UrlValidator urlVal3 = new UrlValidator(UrlValidator.ALLOW_LOCAL_URLS);
    System.out.println("\n=================================== \n");
    System.out.println("MANUAL TESTING:Allowing Local URLs \n");
    System.out.println("=================================== \n");

    // ------------------scheme----------------------------------
    System.out.println("----------SCHEME----------------------------------------------");
    System.out.println("Should Validate");
    // test http://
    System.out.println("http://www.google.com" + "\t\t\t\tResult: " + urlVal3.isValid("http://www.google.com"));
    
    // test no http://
    System.out.println("www.google.com" + "\t\t\t\t\tResult: " + urlVal3.isValid("www.google.com"));
    
    // test h3tp://
    System.out.println("h3tp://www.google.com" + "\t\t\t\tResult: " + urlVal3.isValid("h3tp://www.google.com"));
    
    System.out.println("\nShould Not Validate");
    // test :/
    System.out.println(":/www.google.com" + "\t\t\t\tResult: " + urlVal3.isValid(":/www.google.com"));
    
    // test ://
    System.out.println("://www.google.com" + "\t\t\t\tResult: " + urlVal3.isValid("://www.google.com"));

    // ------------------authority----------------------------------
    System.out.println("\n----------AUTHORITY-------------------------------------------");
    System.out.println("Should Validate");
    // test .au
    System.out.println("http://www.google.au" + "\t\t\t\tResult: " + urlVal3.isValid("http://www.google.au"));
    
    // special, SHOULD allow local
    System.out.println("http://hostname" + "\t\t\t\t\tResult: " + urlVal3.isValid("http://hostname"));
    
    System.out.println("\nShould Not Validate");
    // test illegal character
    System.out.println("http://www.google~.com" + "\t\t\t\tResult: " + urlVal3.isValid("http://www.google~.com"));
    
    // test missing .com
    System.out.println("http://www.google" + "\t\t\t\tResult: " + urlVal3.isValid("http://www.google"));
    
    // test made up url
    System.out.println("http://my.hostname.com" + "\t\t\t\tResult: " + urlVal3.isValid("http://my.hostname.com"));
    
    // test numbers
    System.out.println("http://1.2.3" + "\t\t\t\t\tResult: " + urlVal3.isValid("http://1.2.3"));
    
    // test blank
    System.out.println("http://<blank>" + "\t\t\t\t\tResult: " + urlVal3.isValid("http:// "));

    // ------------------port----------------------------------
    System.out.println("\n----------PORT------------------------------------------------");
    System.out.println("Should Validate");
    // test valid port 80
    System.out.println("http://www.google.com:80" + "\t\t\tResult: " + urlVal3.isValid("http://www.google.com:80"));
    
    // test 3 digit port
    System.out.println("http://www.google.com:800" + "\t\t\tResult: " + urlVal3.isValid("http://www.google.com:800"));
    
    // test 4 digit port
    System.out.println("http://www.google.com:8000" + "\t\t\tResult: " + urlVal3.isValid("http://www.google.com:8000"));
    
    // test 5 digit port
    System.out.println("http://www.google.com:80000" + "\t\t\tResult: " + urlVal3.isValid("http://www.google.com:80000"));
    
    System.out.println("\nShould Not Validate:");
    // test : missing port number
    System.out.println("http://www.google.com:" + "\t\t\t\tResult: " + urlVal3.isValid("http://www.google.com:"));
    
    // test negative port number
    System.out.println("http://www.google.com:-80" + "\t\t\tResult: " + urlVal3.isValid("http://www.google.com:-80"));
    
    // test alphanumeric port number
    System.out.println("http://www.google.com:80a" + "\t\t\tResult: " + urlVal3.isValid("http://www.google.com:80a"));

    // ------------------path----------------------------------
    System.out.println("\n----------PATH------------------------------------------------");
    System.out.println("Should Validate: ");
    // test root path test
    System.out.println("http://www.google.com/test" + "\t\t\tResult: " + urlVal3.isValid("http://www.google.com/test"));
    
    // test path with only /
    System.out.println("http://www.google.com/" + "\t\t\t\tResult: " + urlVal3.isValid("http://www.google.com/"));
    
    System.out.println("\nShould Not Validate: ");
    // test missing / on path
    System.out.println("http://www.google.comtest" + "\t\t\tResult: " + urlVal3.isValid("http://www.google.comtest"));
    
    // test // on path
    System.out.println("http://www.google.com//test" + "\t\t\tResult: " + urlVal3.isValid("http://www.google.com//test"));
    
    // test illegal character on path
    System.out.println("http://www.google.com/.." + "\t\t\tResult: " + urlVal3.isValid("http://www.google.com/.."));
    
    // test 2 level deep path with illegal characters
    System.out.println("http://www.google.com/../" + "\t\t\tResult: " + urlVal3.isValid("http://www.google.com/../"));
    
    // test spaces in path
    System.out.println("http://www.google.com       /" + "\t\t\tResult: " + urlVal3.isValid("http://www.google.com         /"));

    // ------------------option----------------------------------
    System.out.println("\n----------PATH OPTIONS---------------------------------------");
    System.out.println("Should Validate: ");
    // test valid two level deep path
    System.out.println("http://www.google.com/test/test" + "\t\t\tResult: " + urlVal3.isValid("http://www.google.com/test/test"));
    
    // test trailing / on path
    System.out.println("http://www.google.com/test/" + "\t\t\tResult: " + urlVal3.isValid("http://www.google.com/test/"));
    
    // test missing / on two level deep path
    System.out.println("http://www.google.com/testtest" + "\t\t\tResult: " + urlVal3.isValid("http://www.google.com/testtest"));
    
    System.out.println("\nShould Not Validate: ");
    // test missing / on two level deep path
    System.out.println("http://www.google.comtesttest" + "\t\t\tResult: " + urlVal3.isValid("http://www.google.comtesttest"));
    
    // test // on two level deep path
    System.out.println("http://www.google.com/test//test" + "\t\tResult: " + urlVal3.isValid("http://www.google.com/test//test"));

    // ------------------queries----------------------------------
    System.out.println("\n----------QUERIES--------------------------------------------");
    System.out.println("Should Validate:");
    // test valid query
    System.out.println("http://www.google.com?query=test" + "\t\tResult: " + urlVal3.isValid("http://www.google.com?query=test"));
    
    //test query with & added
    System.out.println("http://www.google.com?query=test&hi=hello" + "\tResult: " + urlVal3.isValid("http://www.google.com?query=test&hi=hello"));
    
    System.out.println("\nShould Not Validate: ");
    // test missing test
    System.out.println("http://www.google.com?query=" + "\t\t\tResult: " + urlVal3.isValid("http://www.google.com?query="));
    
    // test missing ?query
    System.out.println("http://www.google.com=test" + "\t\t\tResult: " + urlVal3.isValid("http://www.google.com=test"));
    
    // test ??
    System.out.println("http://www.google.com??query=test" + "\t\tResult: " + urlVal3.isValid("http://www.google.com??query=test"));
    
    /**********************************************************************************
	 * TEST 4: DEFAULT VALIDATOR  
	 *********************************************************************************/
    UrlValidator urlVal4 = new UrlValidator(0);
    System.out.println("\n=================================== \n");
    System.out.println("MANUAL TESTING:Default \n");
    System.out.println("=================================== \n");

    // ------------------scheme----------------------------------
    System.out.println("----------SCHEME----------------------------------------------");
    System.out.println("Should Validate");
    // test http://
    System.out.println("http://www.google.com" + "\t\t\t\tResult: " + urlVal4.isValid("http://www.google.com"));
    
    // test no http://
    System.out.println("www.google.com" + "\t\t\t\t\tResult: " + urlVal4.isValid("www.google.com"));
    
    // test h3tp://
    System.out.println("h3tp://www.google.com" + "\t\t\t\tResult: " + urlVal4.isValid("h3tp://www.google.com"));
    
    System.out.println("\nShould Not Validate");
    // test :/
    System.out.println(":/www.google.com" + "\t\t\t\tResult: " + urlVal4.isValid(":/www.google.com"));
    
    // test ://
    System.out.println("://www.google.com" + "\t\t\t\tResult: " + urlVal4.isValid("://www.google.com"));

    // ------------------authority----------------------------------
    System.out.println("\n----------AUTHORITY-------------------------------------------");
    System.out.println("Should Validate");
    // test .au
    System.out.println("http://www.google.au" + "\t\t\t\tResult: " + urlVal4.isValid("http://www.google.au"));
    
    System.out.println("\nShould Not Validate");
    // test illegal character
    System.out.println("http://www.google~.com" + "\t\t\t\tResult: " + urlVal4.isValid("http://www.google~.com"));
    
    // test missing .com
    System.out.println("http://www.google" + "\t\t\t\tResult: " + urlVal4.isValid("http://www.google"));
    
    // test made up url
    System.out.println("http://my.hostname.com" + "\t\t\t\tResult: " + urlVal4.isValid("http://my.hostname.com"));
    
    // test numbers
    System.out.println("http://1.2.3" + "\t\t\t\t\tResult: " + urlVal4.isValid("http://1.2.3"));
    
    // test blank
    System.out.println("http://<blank>" + "\t\t\t\t\tResult: " + urlVal4.isValid("http:// "));
    
    // special, should NOT allow at default
    System.out.println("http://hostname" + "\t\t\t\t\tResult: " + urlVal4.isValid("http://hostname"));

    // ------------------port----------------------------------
    System.out.println("\n----------PORT------------------------------------------------");
    System.out.println("Should Validate");
    // test valid port 80
    System.out.println("http://www.google.com:80" + "\t\t\tResult: " + urlVal4.isValid("http://www.google.com:80"));
    
    // test 3 digit port
    System.out.println("http://www.google.com:800" + "\t\t\tResult: " + urlVal4.isValid("http://www.google.com:800"));
    
    // test 4 digit port
    System.out.println("http://www.google.com:8000" + "\t\t\tResult: " + urlVal4.isValid("http://www.google.com:8000"));
    
    // test 5 digit port
    System.out.println("http://www.google.com:80000" + "\t\t\tResult: " + urlVal4.isValid("http://www.google.com:80000"));
    
    System.out.println("\nShould Not Validate:");
    // test : missing port number
    System.out.println("http://www.google.com:" + "\t\t\t\tResult: " + urlVal4.isValid("http://www.google.com:"));
    
    // test negative port number
    System.out.println("http://www.google.com:-80" + "\t\t\tResult: " + urlVal4.isValid("http://www.google.com:-80"));
    
    // test alphanumeric port number
    System.out.println("http://www.google.com:80a" + "\t\t\tResult: " + urlVal4.isValid("http://www.google.com:80a"));

    // ------------------path----------------------------------
    System.out.println("\n----------PATH------------------------------------------------");
    System.out.println("Should Validate: ");
    // test root path test
    System.out.println("http://www.google.com/test" + "\t\t\tResult: " + urlVal4.isValid("http://www.google.com/test"));
    
    // test path with only /
    System.out.println("http://www.google.com/" + "\t\t\t\tResult: " + urlVal4.isValid("http://www.google.com/"));
    
    System.out.println("\nShould Not Validate: ");
    // test missing / on path
    System.out.println("http://www.google.comtest" + "\t\t\tResult: " + urlVal4.isValid("http://www.google.comtest"));
    
    // test // on path
    System.out.println("http://www.google.com//test" + "\t\t\tResult: " + urlVal4.isValid("http://www.google.com//test"));
    
    // test illegal character on path
    System.out.println("http://www.google.com/.." + "\t\t\tResult: " + urlVal4.isValid("http://www.google.com/.."));
    
    // test 2 level deep path with illegal characters
    System.out.println("http://www.google.com/../" + "\t\t\tResult: " + urlVal4.isValid("http://www.google.com/../"));
    
    // test spaces in path
    System.out.println("http://www.google.com       /" + "\t\t\tResult: " + urlVal4.isValid("http://www.google.com         /"));

    // ------------------option----------------------------------
    System.out.println("\n----------PATH OPTIONS---------------------------------------");
    System.out.println("Should Validate: ");
    // test valid two level deep path
    System.out.println("http://www.google.com/test/test" + "\t\t\tResult: " + urlVal4.isValid("http://www.google.com/test/test"));
    
    // test trailing / on path
    System.out.println("http://www.google.com/test/" + "\t\t\tResult: " + urlVal4.isValid("http://www.google.com/test/"));
    
    // test missing / on two level deep path
    System.out.println("http://www.google.com/testtest" + "\t\t\tResult: " + urlVal4.isValid("http://www.google.com/testtest"));
    
    System.out.println("\nShould Not Validate: ");
    // test missing / on two level deep path
    System.out.println("http://www.google.comtesttest" + "\t\t\tResult: " + urlVal4.isValid("http://www.google.comtesttest"));
    
    // test // on two level deep path
    System.out.println("http://www.google.com/test//test" + "\t\tResult: " + urlVal4.isValid("http://www.google.com/test//test"));

    // ------------------queries----------------------------------
    System.out.println("\n----------QUERIES--------------------------------------------");
    System.out.println("Should Validate:");
    // test valid query
    System.out.println("http://www.google.com?query=test" + "\t\tResult: " + urlVal4.isValid("http://www.google.com?query=test"));
    
    //test query with & added
    System.out.println("http://www.google.com?query=test&hi=hello" + "\tResult: " + urlVal4.isValid("http://www.google.com?query=test&hi=hello"));
    
    System.out.println("\nShould Not Validate: ");
    // test missing test
    System.out.println("http://www.google.com?query=" + "\t\t\tResult: " + urlVal4.isValid("http://www.google.com?query="));
    
    // test missing ?query
    System.out.println("http://www.google.com=test" + "\t\t\tResult: " + urlVal4.isValid("http://www.google.com=test"));
    
    // test ??
    System.out.println("http://www.google.com??query=test" + "\t\tResult: " + urlVal4.isValid("http://www.google.com??query=test"));

  }

/**********************************************************************************
*   PARTITION TESTING  
*********************************************************************************/
  // scheme partition
  public void testYourFirstPartition() {
	  
	System.out.println("\n==========Testing Schemes:=====================================\n");

    String[] testSchemes = {"http://", "Htp://", "h3tp://", ":/", "://", " "};
    UrlValidator schemeVal = new UrlValidator(testSchemes, 0);
    for (int i = 0; i < testSchemes.length; i++) {
      String curScheme = testSchemes[i];
      System.out.print("\nTesting " + curScheme);
      boolean valid = schemeVal.isValidScheme(curScheme);
      if (valid == false && i == 0 || valid == true && i == 1 || valid == false && i == 2 || valid == true && i == 3 || valid == true && i == 4 || valid == false && i == 5) {
        System.out.println("\t\t\tResult: FAILED, invalid scheme");
      } else {
    	System.out.println("\t\t\tResult: PASSED");
      }
    }
  }

  // authority partition
  public void testYourSecondPartition() {
    System.out.println("\n==========Testing Authority:==================================\n");

    String[] testAuthority = {"www.google.com", "www.google~.com", "www.google", "my.hostname.com", " "};
    UrlValidator authVal = new UrlValidator(testAuthority, 0);
    for (int i = 0; i < testAuthority.length; i++) {
      String curAuth = testAuthority[i];
      System.out.print("\nTesting " + curAuth);
      boolean valid = authVal.isValidAuthority(curAuth);
      if (valid == false && i == 0 || valid == true && i == 1 || valid == true && i == 2 || valid == true && i == 3 || valid == false && i == 4) {
        if(i == 4){
        	System.out.println("\t\t\tResult: FAILED, invalid authority");
        } else
    	  System.out.println("\t\tResult: FAILED, invalid authority");
      } else {
    	  if(i == 4){
    		  System.out.println("\t\t\tResult: PASSED");
    	  } else
    	System.out.println("\t\tResult: PASSED");
      }
    }
  }

  // port partition - Done with the isValidAuthority(String authority) function
  public void testYourThirdPartition() {
    System.out.println("\n=================================== \n");
    System.out.println("       PARTITION TESTING \n");
    System.out.println("=================================== \n");
	  
	System.out.println("\n==========Testing Port:=======================================\n");

    String[] testPort = {"www.google.com:80", "www.google.com:800", "www.google.com:8000", "www.google.com:80000", "www.google.com:", "www.google.com:-80", "www.google.com:80a"};
    UrlValidator portVal = new UrlValidator(testPort, 0);
    for (int i = 0; i < testPort.length; i++) {
      String curPort = testPort[i];
      System.out.print("\nTesting " + curPort);
      boolean valid = portVal.isValidAuthority(curPort);
      if (valid == false && i == 0 || valid == false && i == 1 || valid == false && i == 2 || valid == false && i == 3 || valid == true && i == 4 || valid == true && i == 5 || valid == true && i == 6) {
       if( i == 4){
    	   System.out.println("\t\tResult: FAILED, invalid port");
       } else
    	  System.out.println("\tResult: FAILED, invalid port");
      } else {
    	  if( i == 4){
    		  System.out.println("\t\tResult: PASSED"); 
    	  } else
    	System.out.println("\tResult: PASSED");
      }
    }
  }

  // path Partition
  public void testYourFourthPartition(){
    System.out.println("\n==========Testing Path:======================================\n");

    String[] testPath = {"/test", "/", "test", "//test" , " //test", ".."};
    UrlValidator pathVal = new UrlValidator(testPath, 0);
    for (int i = 0; i < testPath.length; i++) {
      String curPath = testPath[i];
      System.out.print("\nTesting " + curPath);
      boolean valid = pathVal.isValidPath(curPath);
      if (valid == false && i == 0 || valid == false && i == 1 || valid == false && i == 2 || valid == false && i == 3 || valid == false && i == 4 || valid == true && i == 5) {
        System.out.println("\t\t\tResult: FAILED, invalid path");
      } else {
    	System.out.println("\t\t\tResult: PASSED");
      }
    }
  }


  // query Partition
  public void testYourFifthPartition() {
    System.out.println("\n==========Testing Queries:===================================\n");

    String[] testQueries = {"/?query=test", "?query=test", "?query=", "=test", "??query=test"};
    UrlValidator pathQuery = new UrlValidator(testQueries, 0);
    for (int i = 0; i < testQueries.length; i++) {
      String curQuery = testQueries[i];
      System.out.print("\nTesting " + curQuery);
      boolean valid = pathQuery.isValidQuery(curQuery);
      if(valid == false && i == 0 || valid == true && i == 1 || valid == true && i == 2 || valid == true && i == 3 || valid == true && i == 4) {
        if(i == 2 || i== 3){
        	System.out.println("\t\t\tResult: FAILED, invalid Query");
        } else
    	  System.out.println("\t\tResult: FAILED, invalid Query");
      } else {
    	  if(i == 2 || i== 3){
    		  System.out.println("\t\t\tResult: PASSED");
    	  } else
    	System.out.println("\t\tResult: PASSED");
      }
    }
  }

/**********************************************************************************
	 * PROGRAMMING TESTS  
*********************************************************************************/
  public void testIsValid() {

    int bugCount = 0;
    int length = 10;    // change as needed for loop count
    int k = 0;

    // set up valid parts
    String[] badUrls = new String[length];
    String[] trueSchemes = {"http://", "", "h3tp://"};
    String[] trueAuthority = {"www.google.com", "google.com"};
    String[] truePort = {":80", ":9", ":100"};
    String[] truePath = {"/test", "/"};
    String[] trueQueries = {"?query=test", " "};


    // randomize valid each round and loop through "length" times
	System.out.println("----------------------------------- ");
	System.out.println("UNIT TESTING:Full URL Strings");
	System.out.println("----------------------------------- ");

    for(int i = 0; i < length; i++) {
      // randomize
      int schemeInt = (int) (Math.random() * 3);
      int authorityInt = (int) (Math.random() * 2);
      int portInt = (int) (Math.random() * 3);
      int pathInt = (int) (Math.random() * 2);
      int queriesInt = (int) (Math.random() *2);

      // make string of valid parts in valid order
      String url = trueSchemes[schemeInt] + trueAuthority[authorityInt] + truePort[portInt] + truePath[pathInt] + trueQueries[queriesInt];
      UrlValidator validator = new UrlValidator();

      // check if it was marked valid
      boolean valid = validator.isValid(url);

      // if not valid, increase bug count and store url
      if(valid == false) {
        bugCount++;
        badUrls[k] = url;
        k++;
      }
    }
    // print results
    System.out.println("Bad URLs:");
    for (int j = 0; j < badUrls.length; j++) {
      if(badUrls[j] != null){
    	System.out.println(badUrls[j]);
      }
    }
    System.out.println("\n Total Bug Count: " + bugCount);
  }

  public void testIsValidQueryUnitTest()
  {
	  UrlValidator val = new UrlValidator();
	  System.out.println("-----------------------------------");
	  System.out.println("UNIT TESTING:isValidQuery");
	  System.out.println("-----------------------------------");
	  System.out.print("Testing query ?action=view ");
	  System.out.println("\tResult: " + val.isValidQuery("?action=view"));
	  System.out.print("Testing query null ");
	  System.out.println("\t\tResult: " + val.isValidQuery(""));
	  System.out.print("Testing query ?page=1&test=0 ");
	  System.out.println("\tResult: " + val.isValidQuery("?page=1&test=0"));
  }
  
  public void testIsValidSchemeUnitTest()
  {
	  System.out.println("\n=================================== \n");
	  System.out.println("      PROGRAMMING TESTING:");
	  System.out.println("=================================== \n");
	  
	  UrlValidator val = new UrlValidator();
	  System.out.println("----------------------------------- ");
	  System.out.println("UNIT TESTING:isValidScheme");
	  System.out.println("----------------------------------- ");
	  System.out.print("Testing scheme http ");
	  System.out.println("\tResult: " + val.isValidScheme("http"));
	  System.out.print("Testing scheme https ");
	  System.out.println("\tResult: " + val.isValidScheme("https"));
	  System.out.print("Testing scheme aaa ");
	  System.out.println("\tResult: " + val.isValidScheme("aaa"));
	  System.out.print("Testing scheme ftp ");
	  System.out.println("\tResult: " + val.isValidScheme("ftp"));
	  
  }


  public void testIsValidAuthorityUnitTest()
  {
      System.out.println("\n=================================== \n");
      System.out.println("      PROGRAMMING TESTING:");
      System.out.println("=================================== \n");

      String[] Auth = {"docs.oracle.com","www.violinworks.net","mail.google.com","example.com:80","some_user:some_path@blah.com","docs//.oracle","www.violinworks.net//?","http//:google.com","example com","///"};
      int badCount = 0;
      int validCount = 0;

    System.out.println("----------------------------------- ");
      System.out.println("UNIT TESTING:isValidAuthority");
      System.out.println("----------------------------------- ");
      UrlValidator val = new UrlValidator();
      for (int i = 0;i<10;i++){
          String currAuth = Auth[i];
          System.out.println("Testing authority " + currAuth);
          System.out.println("\tResult: " + val.isValidScheme(currAuth));
          if (val.isValidScheme(currAuth) == false){
              badCount++;
          }
          else{
              validCount++;
          }
      }
       System.out.println("in testIsValidAuthorityUnitTest() test expected 5 bad, returned " + badCount + " bad");
       System.out.println("expected 5  valid, returned " + validCount + " valid");
      
  }

  public void testIsValidPathUnitTest()
  {
      System.out.println("\n=================================== \n");
      System.out.println("      PROGRAMMING TESTING:");
      System.out.println("=================================== \n");

      String[] PathTests = {"/is/valid/path.htm",".htm","something.html","1/2/3.jpg","xxx/x/a/a/b.txt","docs?oracle","?","/docs/?.htm","?path/to/file.htm ","//<>//"};
      int badCount = 0;
      int validCount = 0;

    System.out.println("----------------------------------- ");
      System.out.println("UNIT TESTING:isValidPath");
      System.out.println("----------------------------------- ");
      UrlValidator val = new UrlValidator();
      for (int i = 0;i<10;i++){
          String currPath = PathTests[i];
          System.out.println("Testing authority " + currPath);
          System.out.println("\tResult: " + val.isValidPath(currPath));
          if (val.isValidPath(currPath) == false){
              badCount++;
          }
          else{
              validCount++;
          }
      }
       System.out.println("testIsValidPathUnitTest expected 5 bad, returned " + badCount + " bad");
       System.out.println("expected 5  valid, returned " + validCount + " valid");
      
  }


    public void testIsValidPortUnitTest()
  {
      System.out.println("\n=================================== \n");
      System.out.println("      PROGRAMMING TESTING:");
      System.out.println("=================================== \n");

      String[] PortTests = {"google.com:80","google.com:80000","google.com:  ","google.com:1","google.com:xyz","docs.oracle?:80"};
      int badCount = 0;
      int validCount = 0;

    System.out.println("----------------------------------- ");
      System.out.println("UNIT TESTING: Port validity with isValidAuthority");
      System.out.println("----------------------------------- ");
      UrlValidator val = new UrlValidator();
      for (int i = 0;i<6;i++){
          String currPort = PortTests[i];
          System.out.println("Testing port " + currPort);
          System.out.println("\tResult: " + val.isValidAuthority(currPort));
          if (val.isValidAuthority(currPort) == false){
              badCount++;
          }
          else{
              validCount++;
          }
      }
       System.out.println("port validity expected 3 bad, returned " + badCount + " bad");
       System.out.println("expected 3  valid, returned " + validCount + " valid");
      
  }
  /**
  * Create set of tests by taking the testUrlXXX arrays and
  * running through all possible permutations of their combinations.
  *
  * @param testObjects Used to create a url.
  */

}
