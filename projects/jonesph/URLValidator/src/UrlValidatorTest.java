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
	   UrlValidator url = new UrlValidator();
	   // System.out.println(url.isValid("http://www.amazon.com"));
	   UrlValidator urlAAS = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);


	   System.out.println("--- Manual Tests ---");
	   
	   // scheme
	   System.out.println("");
	   System.out.println("Scheme isValid expect 'true':");
	   System.out.print("   http://www.amazon.com  =  ");
	   System.out.println(url.isValid("http://www.amazon.com"));
	   System.out.print("   www.amazon.com  =  ");
	   // System.out.println(url.isValid("www.amazon.com"));
	   System.out.println(urlAAS.isValid("www.amazon.com"));
	   System.out.println("");
	   System.out.println("Scheme isValid expect 'false':");
	   System.out.print("   http:/www.amazon.com  =  ");
	   System.out.println(url.isValid("http:/www.amazon.com"));
	   System.out.print("   http//www.amazon.com  =  ");
	   System.out.println(url.isValid("http//www.amazon.com"));
	   System.out.print("   htp://www.amazon.com  =  ");
	   System.out.println(url.isValid("htp://www.amazon.com"));

	   // authority
	   System.out.println("");
	   System.out.println("Authority isValid expect 'true':");
	   System.out.print("   http://www.amazon.com  =  ");
	   System.out.println(url.isValid("http://www.amazon.com"));
	   System.out.print("   http://54.239.25.208  =  ");
	   System.out.println(url.isValid("http://54.239.25.208"));
	   System.out.print("   http://www.amazon.co.it  =  ");
	   System.out.println(url.isValid("http://www.amazon.co.it"));
	   System.out.print("   http://www.amazon.co.uk  =  ");
	   System.out.println(url.isValid("http://www.amazon.co.uk"));
	   System.out.println("");
	   System.out.println("Authority isValid expect 'false':");
	   System.out.print("   http://www.amazon.com!  =  ");
	   System.out.println(url.isValid("http://www.amazon.com!"));
	   System.out.print("   http://www.amazon  =  ");
	   System.out.println(url.isValid("http://www.amazon"));
	   System.out.print("   http://54.239.25  =  ");
	   System.out.println(url.isValid("http://54.239.25"));
	   System.out.print("   http:// www.amazon.com  =  ");
	   System.out.println(url.isValid("http:// www.amazon.com"));

	   // port
	   System.out.println("");
	   System.out.println("Port isValid expect 'true':");
	   System.out.print("   http://www.amazon.com:80  =  ");
	   System.out.println(url.isValid("http://www.amazon.com:80"));  // std http port
	   System.out.print("   http://www.amazon.com:8080  =  ");
	   System.out.println(url.isValid("http://www.amazon.com:8080"));  // std tomcat
	   System.out.print("   http://www.amazon.com:65535  =  ");
	   System.out.println(url.isValid("http://www.amazon.com:65535"));  // max port
	   System.out.println("");
	   System.out.println("Port isValid expect 'false':");
	   System.out.print("   http://www.amazon.com:  =  ");
	   System.out.println(url.isValid("http://www.amazon.com:"));
	   System.out.print("   http://www.amazon.com:80a  =  ");
	   System.out.println(url.isValid("http://www.amazon.com:80a"));
	   System.out.print("   http://www.amazon.com:80 80  =  ");
	   System.out.println(url.isValid("http://www.amazon.com:80 80"));
	   System.out.print("   http://www.amazon.com:65536  =  ");
	   System.out.println(url.isValid("http://www.amazon.com:65536"));  // 65536 > max 65535
	   
	   // path
	   System.out.println("");
	   System.out.println("Path isValid expect 'true':");
	   System.out.print("   http://www.amazon.com/  =  ");
	   System.out.println(url.isValid("http://www.amazon.com/"));
	   System.out.print("   http://www.amazon.com/valid  =  ");
	   System.out.println(url.isValid("http://www.amazon.com/valid"));
	   System.out.println("");
	   System.out.println("Path isValid expect 'false':");
	   System.out.print("   http://www.amazon.cominvalid  =  ");
	   System.out.println(url.isValid("http://www.amazon.cominvalid"));
	   System.out.print("   http://www.amazon.com//invalid  =  ");
	   System.out.println(url.isValid("http://www.amazon.com//invalid"));
	   System.out.print("   http://www.amazon.com/ invalid  =  ");
	   System.out.println(url.isValid("http://www.amazon.com/ invalid"));
	   System.out.print("   http://www.amazon.com/in valid  =  ");
	   System.out.println(url.isValid("http://www.amazon.com/in valid"));

	   // option
	   System.out.println("");
	   System.out.println("Option isValid expect 'true':");
	   System.out.print("   http://www.amazon.com/valid/option  =  ");
	   System.out.println(url.isValid("http://www.amazon.com/valid/option"));
	   System.out.print("   http://www.amazon.com/validoption/  =  ");
	   System.out.println(url.isValid("http://www.amazon.com/validoption/"));
	   System.out.print("   http://www.amazon.com/validoption  =  ");
	   System.out.println(url.isValid("http://www.amazon.com/validoption"));
	   System.out.println("");
	   System.out.println("Option isValid expect 'false':");
	   System.out.print("   http://www.amazon.cominvalidoption  =  ");
	   System.out.println(url.isValid("http://www.amazon.cominvalidoption"));
	   System.out.print("   http://www.amazon.com/invalid//option  =  ");
	   System.out.println(url.isValid("http://www.amazon.com/invalid//option"));
	   System.out.print("   http://www.amazon.com/invalid option  =  ");
	   System.out.println(url.isValid("http://www.amazon.com/invalid option"));

	   // query
	   System.out.println("");
	   System.out.println("Query isValid expect 'true':");
	   System.out.print("   http://www.amazon.com/?node=5  =  ");
	   System.out.println(url.isValid("http://www.amazon.com/?node=5"));
	   System.out.print("   http://www.amazon.com/b/?node=5  =  ");
	   System.out.println(url.isValid("http://www.amazon.com/b/?node=5"));
	   System.out.println("");
	   System.out.println("Query isValid expect 'false':");
	   System.out.print("   http://www.amazon.com/b/?node  =  ");
	   System.out.println(url.isValid("http://www.amazon.com/b/?node"));
	   System.out.print("   http://www.amazon.com/b/?node=  =  ");
	   System.out.println(url.isValid("http://www.amazon.com/b/?node="));
	   System.out.print("   http://www.amazon.com/b/? node=5  =  ");
	   System.out.println(url.isValid("http://www.amazon.com/b/? node=5"));
	   System.out.print("   http://www.amazon.com/b/?node = 5  =  ");
	   System.out.println(url.isValid("http://www.amazon.com/b/?node = 5"));

   }
 
/***************************************************************************  
//Partition testing: test each section, or partition, of the code at a time.
****************************************************************************/

//	Scheme Partitioning
   public void testYourFirstPartition()
   {
	System.out.println("Testing First Partition: Schemes");
	UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	
	String authority = "www.amazon.com";
	String port = ":80";
	String path = "/valid";
	String option = "/option";
	String query = "?node=5";

	String goodScheme = "http://";
	String badScheme = "http/";
	String noScheme = "";

	String good = goodScheme + authority + port + path + option + query;
	String bad = badScheme + authority + port + path + option + query;
	String none = noScheme + authority + port + path + option + query;

	if (urlVal.isValid(good))
	{System.out.println("URL is good: " + good);}
	else
	{System.out.println("URL should be valid but failed: " + good);}

	if (urlVal.isValid(bad))
	{System.out.println("URL should be bad but passed: " + bad);}
	else
	{System.out.println("URL is bad: " + bad);}

	if (urlVal.isValid(none))
	{System.out.println("URL is good: " + none);}
	else
	{System.out.println("URL should be valid but failed: " + none);}
   }
 
//	Authority Partitioning  
   public void testYourSecondPartition()
	{
	System.out.println("Testing Second Partition: Authority");
	UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	
	String scheme = "http://";
	String port = ":80";
	String path = "/valid";
	String option = "/option";
	String query = "?node=5";

	String goodAuthority = "www.amazon.com";
	String badAuthority = "www.amazon";
	String noAuthority = "";

	String good = scheme + goodAuthority + port + path + option + query;
	String bad = scheme + badAuthority + port + path + option + query;
	String none = scheme + noAuthority + port + path + option + query;

	if (urlVal.isValid(good))
	{System.out.println("URL is good: " + good);}
	else
	{System.out.println("URL should be valid but failed: " + good);}

	if (urlVal.isValid(bad))
	{System.out.println("URL should be bad but passed: " + bad);}
	else
	{System.out.println("URL is bad: " + bad);}

	if (urlVal.isValid(none))
	{System.out.println("URL should be bad but passed: " + bad);}
	else
	{System.out.println("URL is bad: " + bad);}

//	Port Partitioning
   public void testYourThirdPartition()
   {
	System.out.println("Testing Third Partition: Ports");
	UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	
	String scheme = "http://";
	String authority = "www.amazon.com";
	String path = "/valid";
	String option = "/option";
	String query = "?node=5";

	String goodPort = ":80";
	String badPort = ":80abc";
	String noPort = "";

	String good = scheme + authority + goodPort + path + option + query;
	String bad = scheme + authority + badPort + path + option + query;
	String none = scheme + authority + noPort + path + option + query;

	if (urlVal.isValid(good))
	{System.out.println("URL is good: " + good);}
	else
	{System.out.println("URL should be valid but failed: " + good);}

	if (urlVal.isValid(bad))
	{System.out.println("URL should be bad but passed: " + bad);}
	else
	{System.out.println("URL is bad: " + bad);}

	if (urlVal.isValid(none))
	{System.out.println("URL is good: " + none);}
	else
	{System.out.println("URL should be valid but failed: " + none);}   
   }
 
//	Path Partitioning  
   public void testYourFourthPartition()
	{
	System.out.println("Testing Fourth Partition: Paths");
	UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	
	String scheme = "http://";
	String authority = "www.amazon.com";
	String port = ":80"
	String option = "/option";
	String query = "?node=5";

	String goodPath = "/valid";
	String badPath = "invalid";
	String noPath = "";

	String good = scheme + authority + port + goodPath + option + query;
	String bad = scheme + authority + port + badPath + option + query;
	String none = scheme + authority + port + noPath + option + query;

	if (urlVal.isValid(good))
	{System.out.println("URL is good: " + good);}
	else
	{System.out.println("URL should be valid but failed: " + good);}

	if (urlVal.isValid(bad))
	{System.out.println("URL should be bad but passed: " + bad);}
	else
	{System.out.println("URL is bad: " + bad);}

	if (urlVal.isValid(none))
	{System.out.println("URL is good: " + none);}
	else
	{System.out.println("URL should be valid but failed: " + none);}  
	}

//	Option Partitioning
   public void testYourFifthPartition()
   {
	System.out.println("Testing Fifth Partition: Options");
	UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	
	String scheme = "http://";
	String authority = "www.amazon.com";
	String port = ":80"
	String path = "/valid";
	String query = "?node=5";

	String goodOption = "/validOption";
	String badOption = "invalidOption";
	String noOption = "";

	String good = scheme + authority + port + path + goodOption + query;
	String bad = scheme + authority + port + path + badOption + query;
	String none = scheme + authority + port + path + noOption + query;

	if (urlVal.isValid(good))
	{System.out.println("URL is good: " + good);}
	else
	{System.out.println("URL should be valid but failed: " + good);}

	if (urlVal.isValid(bad))
	{System.out.println("URL should be bad but passed: " + bad);}
	else
	{System.out.println("URL is bad: " + bad);}

	if (urlVal.isValid(none))
	{System.out.println("URL is good: " + none);}
	else
	{System.out.println("URL should be valid but failed: " + none);}   
   }
 
//	Query Partitioning  
   public void testYourSixthPartition()
	{
	System.out.println("Testing Sixth Partition: Queries");
	UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	
	String scheme = "http://";
	String authority = "www.amazon.com";
	String port = ":80"
	String path = "/valid";
	String option = "/option";

	String goodQuery = "?node=5";
	String badQuery = "/b/?node=";
	String noQuery = "";

	String good = scheme + authority + port + path + option + goodQuery;
	String bad = scheme + authority + port + path + option + badQuery;
	String none = scheme + authority + port + path + option + noQuery;

	if (urlVal.isValid(good))
	{System.out.println("URL is good: " + good);}
	else
	{System.out.println("URL should be valid but failed: " + good);}

	if (urlVal.isValid(bad))
	{System.out.println("URL should be bad but passed: " + bad);}
	else
	{System.out.println("URL is bad: " + bad);}

	if (urlVal.isValid(none))
	{System.out.println("URL is good: " + none);}
	else
	{System.out.println("URL should be valid but failed: " + none);}   
	}
   
   
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
   

}
