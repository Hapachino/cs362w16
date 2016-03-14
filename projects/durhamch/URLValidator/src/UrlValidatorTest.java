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
   private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.
   
   public UrlValidatorTest(String testName) {
	
      super(testName);
   
   }

   
   
   public void testManualTest()
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	// scheme
	    System.out.println("\nShould Validate:");
	    System.out.println("http://www.google.com");
	    System.out.println(urlVal.isValid("http://www.google.com"));
	    System.out.println("www.google.com");
	    System.out.println(urlVal.isValid("www.google.com"));
	    System.out.println("h3tp://www.google.com");
	    System.out.println(urlVal.isValid("h3tp://www.google.com"));
	    System.out.println("\nShould Not Validate:");
	    System.out.println("http:/www.google.com");
	    System.out.println(urlVal.isValid("://www.google.com"));
	    System.out.println("://www.google.com");
	    System.out.println(urlVal.isValid("://www.google.com"));

	    // authority
	    System.out.println("\nShould Validate:");
	    System.out.println("http://www.google.com");
	    System.out.println(urlVal.isValid("http://www.google.com"));
	    System.out.println("http://www.google.au");
	    System.out.println(urlVal.isValid("http://www.google.au"));
	    System.out.println("\nShould Not Validate:");
	    System.out.println("http://www.google~.com");
	    System.out.println(urlVal.isValid("http://www.google~.com"));
	    System.out.println("http://www.google");
	    System.out.println(urlVal.isValid("http://www.google"));
	    System.out.println("http://broke.hostname.com");
	    System.out.println(urlVal.isValid("http://broke.hostname.com"));
	    System.out.println("http://1.2.3");
	    System.out.println(urlVal.isValid("http://1.2.3"));
	    System.out.println("http://<blank>");
	    System.out.println(urlVal.isValid("http:// "));
	    

	    // port
	    System.out.println("\nShould Validate:");
	    System.out.println("http://www.google.com:80");
	    System.out.println(urlVal.isValid("http://www.google.com:80"));
	    System.out.println("http://www.google.com:300");
	    System.out.println(urlVal.isValid("http://www.google.com:300"));
	    System.out.println("http://www.google.com:3000");
	    System.out.println(urlVal.isValid("http://www.google.com:3000"));
	    System.out.println("http://www.google.com:30000");
	    System.out.println(urlVal.isValid("http://www.google.com:30000"));
	    System.out.println("\nShould Not Validate:");
	    System.out.println("http://www.google.com:");
	    System.out.println(urlVal.isValid("http://www.google.com:"));
	    System.out.println("http://www.google.com:-80");
	    System.out.println(urlVal.isValid("http://www.google.com:-80a"));
	    System.out.println("http://www.google.com:80");
	    System.out.println(urlVal.isValid("http://www.google.com:80a"));

	    // path
	    System.out.println("\nShould Validate: ");
	    System.out.println("http://www.google.com/test1");
	    System.out.println(urlVal.isValid("http://www.google.com/test1"));
	    System.out.println("http://www.google.com/");
	    System.out.println(urlVal.isValid("http://www.google.com/"));
	    System.out.println("\nShould Not Validate: ");
	    System.out.println("http://www.google.comtest1");
	    System.out.println(urlVal.isValid("http://www.google.comtest1"));
	    System.out.println("http://www.google.com//test1");
	    System.out.println(urlVal.isValid("http://www.google.com//test1"));
	    System.out.println("http://www.google.com/..");
	    System.out.println(urlVal.isValid("http://www.google.com/.."));
	    System.out.println("http://www.google.com/../");
	    System.out.println(urlVal.isValid("http://www.google.com/../"));
	    System.out.println("http://www.google.com       /");
	    System.out.println(urlVal.isValid("http://www.google.com         /"));
	    

	    // option
	    System.out.println("\nShould Validate: ");
	    System.out.println("http://www.google.com/test1/test1");
	    System.out.println(urlVal.isValid("http://www.google.com/test1/test1"));
	    System.out.println("http://www.google.com/test1/");
	    System.out.println(urlVal.isValid("http://www.google.com/test1/"));
	    System.out.println("http://www.google.com/test1test1");
	    System.out.println(urlVal.isValid("http://www.google.com/test1test1"));
	    System.out.println("\nShould Not Validate: ");
	    System.out.println("http://www.google.comtest1test1");
	    System.out.println(urlVal.isValid("http://www.google.comtest1test1"));
	    System.out.println("http://www.google.com/test1//test1");
	    System.out.println(urlVal.isValid("http://www.google.com/test1//test1"));

	    // queries
	    System.out.println("\nShould Validate:");
	    System.out.println("http://www.google.com?action=view");
	    System.out.println(urlVal.isValid("http://www.google.com?action=view"));
	    System.out.println("http://www.google.com?action=view&hi=hello");
	    System.out.println(urlVal.isValid("http://www.google.com?action=view&hi=hello"));
	    System.out.println("\nShould Not Validate: ");
	    System.out.println("http://www.google.com?action");
	    System.out.println(urlVal.isValid("http://www.google.com?action="));
	    System.out.println("http://www.google.com=view");
	    System.out.println(urlVal.isValid("http://www.google.comaction=view"));
	    System.out.println("http://www.google.com??action=view");
	    System.out.println(urlVal.isValid("http://www.google.com??action=view"));

	    UrlValidator urlVal2 = new UrlValidator(null, null, UrlValidator.NO_FRAGMENTS);
	    System.out.println("\nAllowing No Fragments: \n");
	    // scheme
	    System.out.println("\nShould Validate:");
	    System.out.println("http://www.google.com");
	    System.out.println(urlVal2.isValid("http://www.google.com"));
	    System.out.println("www.google.com");
	    System.out.println(urlVal2.isValid("www.google.com"));
	    System.out.println("h3tp://www.google.com");
	    System.out.println(urlVal2.isValid("h3tp://www.google.com"));
	    System.out.println("\nShould Not Validate:");
	    System.out.println("http:/www.google.com");
	    System.out.println(urlVal2.isValid("://www.google.com"));
	    System.out.println("://www.google.com");
	    System.out.println(urlVal2.isValid("://www.google.com"));

	    // authority
	    System.out.println("\nShould Validate:");
	    System.out.println("http://www.google.com");
	    System.out.println(urlVal2.isValid("http://www.google.com"));
	    System.out.println("http://www.google.au");
	    System.out.println(urlVal2.isValid("http://www.google.au"));
	    System.out.println("\nShould Not Validate:");
	    System.out.println("http://www.google~.com");
	    System.out.println(urlVal2.isValid("http://www.google~.com"));
	    System.out.println("http://www.google");
	    System.out.println(urlVal2.isValid("http://www.google"));
	    System.out.println("http://broke.hostname.com");
	    System.out.println(urlVal2.isValid("http://broke.hostname.com"));
	    System.out.println("http://1.2.3");
	    System.out.println(urlVal2.isValid("http://1.2.3"));
	    System.out.println("http://<blank>");
	    System.out.println(urlVal2.isValid("http:// "));

	    // port
	    System.out.println("\nShould Validate:");
	    System.out.println("http://www.google.com:80");
	    System.out.println(urlVal2.isValid("http://www.google.com:80"));
	    System.out.println("http://www.google.com:300");
	    System.out.println(urlVal2.isValid("http://www.google.com:300"));
	    System.out.println("http://www.google.com:3000");
	    System.out.println(urlVal2.isValid("http://www.google.com:3000"));
	    System.out.println("http://www.google.com:30000");
	    System.out.println(urlVal2.isValid("http://www.google.com:30000"));
	    System.out.println("\nShould Not Validate:");
	    System.out.println("http://www.google.com:");
	    System.out.println(urlVal2.isValid("http://www.google.com:"));
	    System.out.println("http://www.google.com:-80");
	    System.out.println(urlVal2.isValid("http://www.google.com:-80a"));
	    System.out.println("http://www.google.com:80");
	    System.out.println(urlVal2.isValid("http://www.google.com:80a"));

	    // path
	    System.out.println("\nShould Validate: ");
	    System.out.println("http://www.google.com/test1");
	    System.out.println(urlVal2.isValid("http://www.google.com/test1"));
	    System.out.println("http://www.google.com/");
	    System.out.println(urlVal2.isValid("http://www.google.com/"));
	    System.out.println("\nShould Not Validate: ");
	    System.out.println("http://www.google.comtest1");
	    System.out.println(urlVal2.isValid("http://www.google.comtest1"));
	    System.out.println("http://www.google.com//test1");
	    System.out.println(urlVal2.isValid("http://www.google.com//test1"));
	    System.out.println("http://www.google.com/..");
	    System.out.println(urlVal2.isValid("http://www.google.com/.."));
	    System.out.println("http://www.google.com/../");
	    System.out.println(urlVal2.isValid("http://www.google.com/../"));

	    // option
	    System.out.println("\nShould Validate: ");
	    System.out.println("http://www.google.com/test1/test1");
	    System.out.println(urlVal2.isValid("http://www.google.com/test1/test1"));
	    System.out.println("http://www.google.com/test1/");
	    System.out.println(urlVal2.isValid("http://www.google.com/test1/"));
	    System.out.println("http://www.google.com/test1test1");
	    System.out.println(urlVal2.isValid("http://www.google.com/test1test1"));
	    System.out.println("\nShould Not Validate: ");
	    System.out.println("http://www.google.comtest1test1");
	    System.out.println(urlVal2.isValid("http://www.google.comtest1test1"));
	    System.out.println("http://www.google.com/test1//test1");
	    System.out.println(urlVal2.isValid("http://www.google.com/test1//test1"));

	    // queries
	    System.out.println("\nShould Validate:");
	    System.out.println("http://www.google.com?action=view");
	    System.out.println(urlVal2.isValid("http://www.google.com?action=view"));
	    System.out.println("http://www.google.com?action=view&hi=hello");
	    System.out.println(urlVal2.isValid("http://www.google.com?action=view&hi=hello"));
	    System.out.println("\nShould Not Validate: ");
	    System.out.println("http://www.google.com?action");
	    System.out.println(urlVal2.isValid("http://www.google.com?action="));
	    System.out.println("http://www.google.com=view");
	    System.out.println(urlVal2.isValid("http://www.google.comaction=view"));
	    System.out.println("http://www.google.com??action=view");
	    System.out.println(urlVal2.isValid("http://www.google.com??action=view"));

	    UrlValidator urlVal3 = new UrlValidator(UrlValidator.ALLOW_LOCAL_URLS);
	    System.out.println("\nAllowing local urls: \n");
	    // scheme
	    System.out.println("\nShould Validate:");
	    System.out.println("http://www.google.com");
	    System.out.println(urlVal3.isValid("http://www.google.com"));
	    System.out.println("www.google.com");
	    System.out.println(urlVal3.isValid("www.google.com"));
	    System.out.println("h3tp://www.google.com");
	    System.out.println(urlVal3.isValid("h3tp://www.google.com"));
	    System.out.println("\nShould Not Validate:");
	    System.out.println("http:/www.google.com");
	    System.out.println(urlVal3.isValid("://www.google.com"));
	    System.out.println("://www.google.com");
	    System.out.println(urlVal3.isValid("://www.google.com"));

	    // authority
	    System.out.println("\nShould Validate:");
	    System.out.println("http://www.google.com");
	    System.out.println(urlVal3.isValid("http://www.google.com"));
	    System.out.println("http://www.google.au");
	    System.out.println(urlVal3.isValid("http://www.google.au"));
	    
	    // special, SHOULD allow at allow local
	    System.out.println("http://hostname");
	    System.out.println(urlVal3.isValid("http://hostname"));
	    System.out.println("\nShould Not Validate:");
	    System.out.println("http://www.google~.com");
	    System.out.println(urlVal3.isValid("http://www.google~.com"));
	    System.out.println("http://www.google");
	    System.out.println(urlVal3.isValid("http://www.google"));
	    System.out.println("http://broke.hostname.com");
	    System.out.println(urlVal3.isValid("http://broke.hostname.com"));
	    System.out.println("http://1.2.3");
	    System.out.println(urlVal3.isValid("http://1.2.3"));
	    System.out.println("http://<blank>");
	    System.out.println(urlVal3.isValid("http:// "));

	    // port
	    System.out.println("\nShould Validate:");
	    System.out.println("http://www.google.com:80");
	    System.out.println(urlVal3.isValid("http://www.google.com:80"));
	    System.out.println("http://www.google.com:300");
	    System.out.println(urlVal3.isValid("http://www.google.com:300"));
	    System.out.println("http://www.google.com:3000");
	    System.out.println(urlVal3.isValid("http://www.google.com:3000"));
	    System.out.println("http://www.google.com:30000");
	    System.out.println(urlVal3.isValid("http://www.google.com:30000"));
	    System.out.println("\nShould Not Validate:");
	    System.out.println("http://www.google.com:");
	    System.out.println(urlVal3.isValid("http://www.google.com:"));
	    System.out.println("http://www.google.com:-80");
	    System.out.println(urlVal3.isValid("http://www.google.com:-80a"));
	    System.out.println("http://www.google.com:80");
	    System.out.println(urlVal3.isValid("http://www.google.com:80a"));

	    // path
	    System.out.println("\nShould Validate: ");
	    System.out.println("http://www.google.com/test1");
	    System.out.println(urlVal3.isValid("http://www.google.com/test1"));
	    System.out.println("http://www.google.com/");
	    System.out.println(urlVal3.isValid("http://www.google.com/"));
	    System.out.println("\nShould Not Validate: ");
	    System.out.println("http://www.google.comtest1");
	    System.out.println(urlVal3.isValid("http://www.google.comtest1"));
	    System.out.println("http://www.google.com//test1");
	    System.out.println(urlVal3.isValid("http://www.google.com//test1"));
	    System.out.println("http://www.google.com/..");
	    System.out.println(urlVal3.isValid("http://www.google.com/.."));
	    System.out.println("http://www.google.com/../");
	    System.out.println(urlVal3.isValid("http://www.google.com/../"));

	    // option
	    System.out.println("\nShould Validate: ");
	    System.out.println("http://www.google.com/test1/test1");
	    System.out.println(urlVal3.isValid("http://www.google.com/test1/test1"));
	    System.out.println("http://www.google.com/test1/");
	    System.out.println(urlVal3.isValid("http://www.google.com/test1/"));
	    System.out.println("http://www.google.com/test1test1");
	    System.out.println(urlVal3.isValid("http://www.google.com/test1test1"));
	    System.out.println("\nShould Not Validate: ");
	    System.out.println("http://www.google.comtest1test1");
	    System.out.println(urlVal3.isValid("http://www.google.comtest1test1"));
	    System.out.println("http://www.google.com/test1//test1");
	    System.out.println(urlVal3.isValid("http://www.google.com/test1//test1"));

	    // queries
	    System.out.println("\nShould Validate:");
	    System.out.println("http://www.google.com?action=view");
	    System.out.println(urlVal3.isValid("http://www.google.com?action=view"));
	    System.out.println("http://www.google.com?action=view&hi=hello");
	    System.out.println(urlVal3.isValid("http://www.google.com?action=view&hi=hello"));
	    System.out.println("\nShould Not Validate: ");
	    System.out.println("http://www.google.com?action");
	    System.out.println(urlVal3.isValid("http://www.google.com?action="));
	    System.out.println("http://www.google.com=view");
	    System.out.println(urlVal3.isValid("http://www.google.comaction=view"));
	    System.out.println("http://www.google.com??action=view");
	    System.out.println(urlVal3.isValid("http://www.google.com??action=view"));

	    UrlValidator urlVal4 = new UrlValidator(0);
	    System.out.println("\nDefault: \n");
	    // scheme
	    System.out.println("\nShould Validate:");
	    System.out.println("http://www.google.com");
	    System.out.println(urlVal4.isValid("http://www.google.com"));
	    System.out.println("www.google.com");
	    System.out.println(urlVal4.isValid("www.google.com"));
	    System.out.println("h3tp://www.google.com");
	    System.out.println(urlVal4.isValid("h3tp://www.google.com"));
	    System.out.println("\nShould Not Validate:");
	    System.out.println("http:/www.google.com");
	    System.out.println(urlVal4.isValid("://www.google.com"));
	    System.out.println("://www.google.com");
	    System.out.println(urlVal4.isValid("://www.google.com"));

	    // authority
	    System.out.println("\nShould Validate:");
	    System.out.println("http://www.google.com");
	    System.out.println(urlVal4.isValid("http://www.google.com"));
	    System.out.println("http://www.google.au");
	    System.out.println(urlVal4.isValid("http://www.google.au"));
	    System.out.println("\nShould Not Validate:");
	    System.out.println("http://www.google~.com");
	    System.out.println(urlVal4.isValid("http://www.google~.com"));
	    System.out.println("http://www.google");
	    System.out.println(urlVal4.isValid("http://www.google"));
	    System.out.println("http://broke.hostname.com");
	    System.out.println(urlVal4.isValid("http://broke.hostname.com"));
	    System.out.println("http://1.2.3");
	    System.out.println(urlVal4.isValid("http://1.2.3"));
	    System.out.println("http://<blank>");
	    System.out.println(urlVal4.isValid("http:// "));
	    // special, should NOT allow at default
	    System.out.println("http://hostname");
	    System.out.println(urlVal4.isValid("http://hostname"));

	    // port
	    System.out.println("\nShould Validate:");
	    System.out.println("http://www.google.com:80");
	    System.out.println(urlVal4.isValid("http://www.google.com:80"));
	    System.out.println("http://www.google.com:300");
	    System.out.println(urlVal4.isValid("http://www.google.com:300"));
	    System.out.println("http://www.google.com:3000");
	    System.out.println(urlVal4.isValid("http://www.google.com:3000"));
	    System.out.println("http://www.google.com:30000");
	    System.out.println(urlVal4.isValid("http://www.google.com:30000"));
	    System.out.println("\nShould Not Validate:");
	    System.out.println("http://www.google.com:");
	    System.out.println(urlVal4.isValid("http://www.google.com:"));
	    System.out.println("http://www.google.com:-80");
	    System.out.println(urlVal4.isValid("http://www.google.com:-80a"));
	    System.out.println("http://www.google.com:80");
	    System.out.println(urlVal4.isValid("http://www.google.com:80a"));

	    // path
	    System.out.println("\nShould Validate: ");
	    System.out.println("http://www.google.com/test1");
	    System.out.println(urlVal4.isValid("http://www.google.com/test1"));
	    System.out.println("http://www.google.com/");
	    System.out.println(urlVal4.isValid("http://www.google.com/"));
	    System.out.println("\nShould Not Validate: ");
	    System.out.println("http://www.google.comtest1");
	    System.out.println(urlVal4.isValid("http://www.google.comtest1"));
	    System.out.println("http://www.google.com//test1");
	    System.out.println(urlVal4.isValid("http://www.google.com//test1"));
	    System.out.println("http://www.google.com/..");
	    System.out.println(urlVal4.isValid("http://www.google.com/.."));
	    System.out.println("http://www.google.com/../");
	    System.out.println(urlVal4.isValid("http://www.google.com/../"));

	    // option
	    System.out.println("\nShould Validate: ");
	    System.out.println("http://www.google.com/test1/test1");
	    System.out.println(urlVal4.isValid("http://www.google.com/test1/test1"));
	    System.out.println("http://www.google.com/test1/");
	    System.out.println(urlVal4.isValid("http://www.google.com/test1/"));
	    System.out.println("http://www.google.com/test1test1");
	    System.out.println(urlVal4.isValid("http://www.google.com/test1test1"));
	    System.out.println("\nShould Not Validate: ");
	    System.out.println("http://www.google.comtest1test1");
	    System.out.println(urlVal4.isValid("http://www.google.comtest1test1"));
	    System.out.println("http://www.google.com/test1//test1");
	    System.out.println(urlVal4.isValid("http://www.google.com/test1//test1"));

	    // queries
	    System.out.println("\nShould Validate:");
	    System.out.println("http://www.google.com?action=view");
	    System.out.println(urlVal4.isValid("http://www.google.com?action=view"));
	    System.out.println("http://www.google.com?action=view&hi=hello");
	    System.out.println(urlVal4.isValid("http://www.google.com?action=view&hi=hello"));
	    System.out.println("\nShould Not Validate: ");
	    System.out.println("http://www.google.com?action");
	    System.out.println(urlVal4.isValid("http://www.google.com?action="));
	    System.out.println("http://www.google.com=view");
	    System.out.println(urlVal4.isValid("http://www.google.comaction=view"));
	    System.out.println("http://www.google.com??action=view");
	    System.out.println(urlVal4.isValid("http://www.google.com??action=view"));
   }
   
   
  public void testYourFirstPartition()
   {
	  System.out.println("\nTesting Schemes:\n");

	    String[] ourSchemes = {"http://", "h3tp://", "://", ":/", " "};
	    UrlValidator schemeVal = new UrlValidator(ourSchemes, 0);
	    for (int i = 0; i < ourSchemes.length; i++) {
	      String curScheme = ourSchemes[i];
	      System.out.println("\nTesting " + curScheme);
	      boolean valid = schemeVal.isValidScheme(curScheme);
	      if (valid == false && i == 0 || valid == false && i == 1 || valid == true && i == 2 || valid == true && i == 3 || valid == false && i == 4) {
	        System.out.println("FAILED, invalid scheme\n");
	      } else {
	    	System.out.println("PASSED\n");
	      }
	    }
   }
   
   public void testYourSecondPartition(){
	   System.out.println("\nTesting Authority:\n");

	    String[] ourAuthority = {"www.google.com", "www.google~.com", "www.google", " ", "broke.hostname.com"};
	    UrlValidator authVal = new UrlValidator(ourAuthority, 0);
	    for (int i = 0; i < ourAuthority.length; i++) {
	      String curAuth = ourAuthority[i];
	      System.out.println("\nTesting " + curAuth);
	      boolean valid = authVal.isValidAuthority(curAuth);
	      if (valid == false && i == 0 || valid == true && i == 1 || valid == true && i == 2 || valid == true && i == 3 || valid == true && i == 4) {
	        System.out.println("FAILED, invalid authority\n");
	      } else {
	    	System.out.println("PASSED\n");
	      }
	    }
   }
   public void testIsValid() throws Exception {
       testIsValid(testUrlParts, UrlValidator.ALLOW_ALL_SCHEMES);
       setUp();
       
  }
   
   public void testIsValid(Object[] testObjects, long options)
   {
	   UrlValidator urlVal = new UrlValidator(null, null, options);
	   StringBuffer testBuffer = new StringBuffer();

	  
	   int index1 = 0;
	   int index2 = 0;
	   int index3 = 0;
	   int index4 = 0;
	   int index5 = 0;
	   int testsFailed = 0;

	   //iterate for the number of possible URLs
	   for(int i = 0; i < 35910; i++){
		   
		   boolean expectedResult = true;
		   
		   //choose the scheme, append to test URL, calculate expected result
		   ResultPair[] part = (ResultPair[]) testObjects[0];
	       testBuffer.append(part[index1].item);
	       expectedResult &= part[index1].valid;
	 
	       //if end of scheme list is reached, reset index and move to the next index for the remaining URL parts
	       if(index1 == 8){
	    	   index1 = 0;
	    	   index2++;
	    	   index3++;
	    	   index4++;
	    	   index5++;
	       }
	       
	       //otherwise, just increment the scheme index
	       else{
	    	   index1++;
	       }
	       
	       //choose the authority, append to test URL, calculate expected result
	       ResultPair[] part2 = (ResultPair[]) testObjects[1];
	       testBuffer.append(part2[index2].item);
	       expectedResult &= part2[index2].valid;
	
	       //if end of authority list reached, reset index
	       if(index2 == 18){
		    	  index2 = 0;
		    }
		    
	       //choose the port, append to test URL, calculate expected result
	       ResultPair[] part3 = (ResultPair[]) testObjects[2];
	       testBuffer.append(part3[index3].item);
	       expectedResult &= part3[index3].valid;
	     
	       //if end of port list reached, reset index
	       if(index3 == 6){
		    	  index3 = 0;
		    }   
	    	   
	       //choose the path, append to testURL, calculate expected result
	       ResultPair[] part4 = (ResultPair[]) testObjects[3];
	       testBuffer.append(part4[index4].item);
	       expectedResult &= part4[index4].valid;
	  
	       //if end of path list reached, reset index
	       if(index4 == 9){
		    	  index4 = 0;
		    }    
	       
	       //choose the query, append to test URL, calculate the expected result
	       ResultPair[] part5 = (ResultPair[]) testObjects[4];
	       testBuffer.append(part5[index5].item);
	       expectedResult &= part5[index5].valid;
	       
	       //if end of query list reached, reset the index
	       if(index5 == 2){
		    	  index5 = 0;
		    }  
	       
	       //test the URL via isValid()
	       boolean testResult = urlVal.isValid(testBuffer.toString());
	   
	       //if expected result does not match actual result
	       if(expectedResult != testResult){
	           //print failure messages and increment number of failed tests
	    	   System.out.println("Test failed: "+ testBuffer.toString() );
	    	   System.out.println("Expected: "+ expectedResult + ", Actual: "+ testResult);
	    	   System.out.println("\n");
	    	   testsFailed++;
	       }
	       
	       //reset test URL buffer
	       testBuffer.setLength(0);
	       
		   
	   }
	   //print number of failed tests
	   System.out.println("Tests Failed: " + testsFailed +"/35910");

	  
   }
   
   public static void main(String[] argv) throws Exception {
	   	  //run testIsValid()	
	      UrlValidatorTest test = new UrlValidatorTest("test");
	      test.setUp();
	      test.testIsValid();
	    
	   }
   
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
