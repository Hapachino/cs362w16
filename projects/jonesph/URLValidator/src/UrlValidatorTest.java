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
   }
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
	String port = ":80";
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
		String port = ":80";
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
	String port = ":80";
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
	   
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   String url;
	   //for i in scheme
	   for (int i = 0; i < SCHEME.length; i++){
		   //for j in authority
		   for (int j = 0; j < AUTHORITY.length; j ++){
			   //for k in domain
			   for (int k = 0; k < DOMAINS.length; k++){
				   //for l in port
				   for (int l = 0; l < PORT.length; l++){
					   //for m in path
					   for (int m = 0; m < PATHS.length; m++){
						   //for n in option
						   for (int n = 0; n < OPTION.length; n++){
							   //for o in query
							   for (int o = 0; o < QUERY.length; o++){
								   url = SCHEME[i] + AUTHORITY[j] + DOMAINS[k] + PORT[l] + PATHS[m] + OPTION[n] + QUERY[o];
								   if (!urlVal.isValid(url)){
									   System.out.println(url);
								   }
							   }
						   }
					   }
				   }
			   }	   	
		   }
	   }
   }
   
   /**
    * Create set of tests by taking the testUrlXXX arrays and
    * running through all possible permutations of their combinations.
    *
    * @param testObjects Used to create a url.
    */
   private static final String[] SCHEME = new String[] {
		   "",
		   "https://",
		   "http://"
   };
   private static final String [] AUTHORITY = new String[]{
		   "www.amazon."   
   };
   private static final String[] PORT = new String[]{
		   "",
		   ":80",
		   ":8080",
		   ":65535"	   
   };
   private static final String[] PATHS = new String[] {
		   "",
		   "/valid"
   };
   
   private static final String[] OPTION = new String[] {
		   "",
		   "/option"
   };
   private static final String[] QUERY = new String[] {
		   "",
		   "/?node=5"
   };
   private static final String[] DOMAINS = new String[] {
		   /*
		    "aero",               // air transport industry
	        "asia",               // Pan-Asia/Asia Pacific
	        "biz",                // businesses
	        "cat", */               // Catalan linguistic/cultural community
	        "com"  /*,                // commercial enterprises
	        "coop",               // cooperative associations
	        "info",               // informational sites
	        "jobs",               // Human Resource managers
	        "mobi",               // mobile products and services
	        "museum",             // museums, surprisingly enough
	        "name",               // individuals' sites
	        "net",                // internet support infrastructure/business
	        "org",                // noncommercial organizations
	        "pro",                // credentialed professionals and entities
	        "tel",                // contact data for businesses and individuals
	        "travel",             // entities in the travel industry
	        "gov",                // United States Government
	        "edu",                // accredited postsecondary US education entities
	        "mil",                // United States Military
	        "int",                 // organizations established by international treaty
	        "ac",                 // Ascension Island
   	        "ad",                 // Andorra
   	        "ae",                 // United Arab Emirates
   	        "af",                 // Afghanistan
   	        "ag",                 // Antigua and Barbuda
   	        "ai",                 // Anguilla
   	        "al",                 // Albania
   	        "am",                 // Armenia
   	        "an",                 // Netherlands Antilles
   	        "ao",                 // Angola
   	        "aq",                 // Antarctica
   	        "ar",                 // Argentina
   	        "as",                 // American Samoa
   	        "at",                 // Austria
   	        "au",                 // Australia (includes Ashmore and Cartier Islands and Coral Sea Islands)
   	        "aw",                 // Aruba
   	        "ax",                 // Åland
   	        "az",                 // Azerbaijan
   	        "ba",                 // Bosnia and Herzegovina
   	        "bb",                 // Barbados
   	        "bd",                 // Bangladesh
   	        "be",                 // Belgium
   	        "bf",                 // Burkina Faso
   	        "bg",                 // Bulgaria
   	        "bh",                 // Bahrain
   	        "bi",                 // Burundi
   	        "bj",                 // Benin
   	        "bm",                 // Bermuda
   	        "bn",                 // Brunei Darussalam
   	        "bo",                 // Bolivia
   	        "br",                 // Brazil
   	        "bs",                 // Bahamas
   	        "bt",                 // Bhutan
   	        "bv",                 // Bouvet Island
   	        "bw",                 // Botswana
   	        "by",                 // Belarus
   	        "bz",                 // Belize
   	        "ca",                 // Canada
   	        "cc",                 // Cocos (Keeling) Islands
   	        "cd",                 // Democratic Republic of the Congo (formerly Zaire)
   	        "cf",                 // Central African Republic
   	        "cg",                 // Republic of the Congo
   	        "ch",                 // Switzerland
   	        "ci",                 // Côte d'Ivoire
   	        "ck",                 // Cook Islands
   	        "cl",                 // Chile
   	        "cm",                 // Cameroon
   	        "cn",                 // China, mainland
   	        "co",                 // Colombia
   	        "cr",                 // Costa Rica
   	        "cu",                 // Cuba
   	        "cv",                 // Cape Verde
   	        "cx",                 // Christmas Island
   	        "cy",                 // Cyprus
   	        "cz",                 // Czech Republic
   	        "de",                 // Germany
   	        "dj",                 // Djibouti
   	        "dk",                 // Denmark
   	        "dm",                 // Dominica
   	        "do",                 // Dominican Republic
   	        "dz",                 // Algeria
   	        "ec",                 // Ecuador
   	        "ee",                 // Estonia
   	        "eg",                 // Egypt
   	        "er",                 // Eritrea
   	        "es",                 // Spain
   	        "et",                 // Ethiopia
   	        "eu",                 // European Union
   	        "fi",                 // Finland
   	        "fj",                 // Fiji
   	        "fk",                 // Falkland Islands
   	        "fm",                 // Federated States of Micronesia
   	        "fo",                 // Faroe Islands
   	        "fr",                 // France
   	        "ga",                 // Gabon
   	        "gb",                 // Great Britain (United Kingdom)
   	        "gd",                 // Grenada
   	        "ge",                 // Georgia
   	        "gf",                 // French Guiana
   	        "gg",                 // Guernsey
   	        "gh",                 // Ghana
   	        "gi",                 // Gibraltar
   	        "gl",                 // Greenland
   	        "gm",                 // The Gambia
   	        "gn",                 // Guinea
   	        "gp",                 // Guadeloupe
   	        "gq",                 // Equatorial Guinea
   	        "gr",                 // Greece
   	        "gs",                 // South Georgia and the South Sandwich Islands
   	        "gt",                 // Guatemala
   	        "gu",                 // Guam
   	        "gw",                 // Guinea-Bissau
   	        "gy",                 // Guyana
   	        "hk",                 // Hong Kong
   	        "hm",                 // Heard Island and McDonald Islands
   	        "hn",                 // Honduras
   	        "hr",                 // Croatia (Hrvatska)
   	        "ht",                 // Haiti
   	        "hu",                 // Hungary
   	        "id",                 // Indonesia
   	        "ie",                 // Ireland (Éire)
   	        "il",                 // Israel
   	     
   	        "im",                 // Isle of Man
   	        "in",                 // India
   	        "io",                 // British Indian Ocean Territory
   	        "iq",                 // Iraq
   	        "ir",                 // Iran
   	        "is",                 // Iceland
   	        "it",                 // Italy
   	        "je",                 // Jersey
   	        "jm",                 // Jamaica
   	        "jo",                 // Jordan
   	        "jp",                 // Japan
   	        "ke",                 // Kenya
   	        "kg",                 // Kyrgyzstan
   	        "kh",                 // Cambodia (Khmer)
   	        "ki",                 // Kiribati
   	        "km",                 // Comoros
   	        "kn",                 // Saint Kitts and Nevis
   	        "kp",                 // North Korea
   	        "kr",                 // South Korea
   	        "kw",                 // Kuwait
   	        "ky",                 // Cayman Islands
   	        "kz",                 // Kazakhstan
   	        "la",                 // Laos (currently being marketed as the official domain for Los Angeles)
   	        "lb",                 // Lebanon
   	        "lc",                 // Saint Lucia
   	        "li",                 // Liechtenstein
   	        "lk",                 // Sri Lanka
   	        "lr",                 // Liberia
   	        "ls",                 // Lesotho
   	        "lt",                 // Lithuania
   	        "lu",                 // Luxembourg
   	        "lv",                 // Latvia
   	        "ly",                 // Libya
   	        "ma",                 // Morocco
   	        "mc",                 // Monaco
   	        "md",                 // Moldova
   	        "me",                 // Montenegro
   	        "mg",                 // Madagascar
   	        "mh",                 // Marshall Islands
   	        "mk",                 // Republic of Macedonia
   	        "ml",                 // Mali
   	        "mm",                 // Myanmar
   	        "mn",                 // Mongolia
   	        "mo",                 // Macau
   	        "mp",                 // Northern Mariana Islands
   	        "mq",                 // Martinique
   	        "mr",                 // Mauritania
   	        "ms",                 // Montserrat
   	        "mt",                 // Malta
   	        "mu",                 // Mauritius
   	        "mv",                 // Maldives
   	        "mw",                 // Malawi
   	        "mx",                 // Mexico
   	        "my",                 // Malaysia
   	        "mz",                 // Mozambique
   	        "na",                 // Namibia
   	        "nc",                 // New Caledonia
   	        "ne",                 // Niger
   	        "nf",                 // Norfolk Island
   	        "ng",                 // Nigeria
   	        "ni",                 // Nicaragua
   	        "nl",                 // Netherlands
   	        "no",                 // Norway
   	        "np",                 // Nepal
   	        "nr",                 // Nauru
   	        
   	        "nu",                 // Niue
   	        "nz",                 // New Zealand
   	        "om",                 // Oman
   	        "pa",                 // Panama
   	        "pe",                 // Peru
   	        "pf",                 // French Polynesia With Clipperton Island
   	        "pg",                 // Papua New Guinea
   	        "ph",                 // Philippines
   	        "pk",                 // Pakistan
   	        "pl",                 // Poland
   	        "pm",                 // Saint-Pierre and Miquelon
   	        "pn",                 // Pitcairn Islands
   	        "pr",                 // Puerto Rico
   	        "ps",                 // Palestinian territories (PA-controlled West Bank and Gaza Strip)
   	        "pt",                 // Portugal
   	        "pw",                 // Palau
   	        "py",                 // Paraguay
   	        "qa",                 // Qatar
   	        "re",                 // Réunion
   	        "ro",                 // Romania
   	        "rs",                 // Serbia
   	        "ru",                 // Russia
   	        "rw",                 // Rwanda
   	        "sa",                 // Saudi Arabia
   	        "sb",                 // Solomon Islands
   	        "sc",                 // Seychelles
   	        "sd",                 // Sudan
   	        "se",                 // Sweden
   	        "sg",                 // Singapore
   	        "sh",                 // Saint Helena
   	        "si",                 // Slovenia
   	        "sj",                 // Svalbard and Jan Mayen Islands Not in use (Norwegian dependencies; see .no)
   	        "sk",                 // Slovakia
   	        "sl",                 // Sierra Leone
   	        "sm",                 // San Marino
   	        "sn",                 // Senegal
   	        "so",                 // Somalia
   	        "sr",                 // Suriname
   	        "st",                 // São Tomé and Príncipe
   	        "su",                 // Soviet Union (deprecated)
   	        "sv",                 // El Salvador
   	        "sy",                 // Syria
   	        "sz",                 // Swaziland
   	        "tc",                 // Turks and Caicos Islands
   	        "td",                 // Chad
   	        "tf",                 // French Southern and Antarctic Lands
   	        "tg",                 // Togo
   	        "th",                 // Thailand
   	        "tj",                 // Tajikistan
   	        "tk",                 // Tokelau
   	        "tl",                 // East Timor (deprecated old code)
   	        "tm",                 // Turkmenistan
   	        "tn",                 // Tunisia
   	        "to",                 // Tonga
   	        "tp",                 // East Timor
   	        "tr",                 // Turkey
   	        "tt",                 // Trinidad and Tobago
   	        "tv",                 // Tuvalu
   	        "tw",                 // Taiwan, Republic of China
   	        "tz",                 // Tanzania
   	        "ua",                 // Ukraine
   	        "ug",                 // Uganda
   	        "uk",                 // United Kingdom
   	        "um",                 // United States Minor Outlying Islands
   	        "us",                 // United States of America
   	        "uy",                 // Uruguay
   	        "uz",                 // Uzbekistan
   	        "va",                 // Vatican City State
   	        "vc",                 // Saint Vincent and the Grenadines
   	        "ve",                 // Venezuela
   	        "vg",                 // British Virgin Islands
   	        "vi",                 // U.S. Virgin Islands
   	        "vn",                 // Vietnam
   	        "vu",                 // Vanuatu
   	        "wf",                 // Wallis and Futuna
   	        "ws",                 // Samoa (formerly Western Samoa)
   	        "ye",                 // Yemen
   	        "yt",                 // Mayotte
   	        "yu",                 // Serbia and Montenegro (originally Yugoslavia)
   	        "za",                 // South Africa
   	        "zm",                 // Zambia
   	        "zw",                 // Zimbabwe
   	        */
   	    };

}