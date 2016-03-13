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
	   //Test Allow All Schemes
	   //This is one way we could approach testing manually
	   UrlValidator urlVal = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
	   System.out.println("Schema Test - Allow All Schemes");
	   assertTrue(urlVal.isValid("http://www.amazon.com"));
	   assertTrue(urlVal.isValid("https://www.google.com"));
	   assertTrue(urlVal.isValid("http://ww.google.com"));
	   assertFalse(urlVal.isValid("google"));
	   assertFalse(urlVal.isValid("amazon.com"));
	   assertTrue(urlVal.isValid("http://google.com"));
	   
	   //Using arrays like this is easier. Feel free to add more valid URLs to either.
	   String[] validUrls = {"", 
			   "http://www.amazon.com", 
			   "https://www.google.com", 
			   "http://ww.google.com",
			   "ftp://127.0.0.1", 
			   "https://oregonstate.instructure.com/courses/1568425", 
			   "http://eecs.oregonstate.edu/current%20students",
			   "http://localhost/", 
			   "http://www.amazon.com:80",
			   "https://mail.google.com/mail/u/0/?hl=en&shva=1#inbox",
			   "http://blog.yourwebsite.com"};
	   
	   String[] invalidUrls = {"amazon.com",
			   "google",
			   "http://www.google.com:123r",
			   "htp://google.com",
			   "https:///www.google.com",
			   "http//www.oregonstate.edu",
			   "http:\\www.amazon.com"};
	   
	   int i;
	   boolean isValid;
	   
	   for(i = 0; i < validUrls.length; i++)
	   {
		   System.out.println("Testing URL: " + validUrls[i]);
		   isValid = urlVal.isValid(validUrls[i]);
		   if (isValid)
		   {
			   System.out.println("TEST PASSED");
		   }
		   else
		   {
			   System.out.println("TEST FAILED");
		   }
	   }
	   
	   System.out.println();
	   
	   for(i = 0; i < invalidUrls.length; i++)
	   {
		   System.out.println("Testing invalid URL: " + invalidUrls[i]);
		   isValid = urlVal.isValid(invalidUrls[i]);
		   if (!isValid)
		   {
			   System.out.println("TEST PASSED");
		   }
		   else
		   {
			   System.out.println("TEST FAILED");
		   }
	   }
   }
   
   /******************************************
    * Part 2: Input Partitioning
    ******************************************/
   
   public void testYourFirstPartition()
   {
	   //Testing Schemes
	   
	   UrlValidator urlVal = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   boolean passed = true;
	   
	   String validOne = "http://";
	   String validTwo = "https://";
	   String validThree = "ftp://";
	   
	   String invalidOne = "h3pp://";
	   
	   String urlBig = "www.google.com";
	   
	   String validUrl = validOne + urlBig;
	   String invalidUrl = invalidOne + urlBig;
	   
	   System.out.println("");
	   System.out.println("Testing Schemes");
	   
	   if(!urlVal.isValid(validUrl))
	   {
		   System.out.println("TEST FAILED. Expected valid for URL: " + validUrl);
		   passed = false;
	   }
	   
	   validUrl = validTwo + urlBig;
	   
	   if(!urlVal.isValid(validUrl))
	   {
		   System.out.println("TEST FAILED. Expected valid for URL: " + validUrl);
		   passed = false;
	   }
	   
	   validUrl = validThree + urlBig;
	   
	   if(!urlVal.isValid(validUrl))
	   {
		   System.out.println("TEST FAILED. Expected valid for URL: " + validUrl);
		   passed = false;
	   }
	   
	   if(urlVal.isValid(invalidUrl))
	   {
		   System.out.println("TEST FAILED. Expected invalid for URL: " + invalidUrl);
		   passed = false;
	   }
	   
	   if(passed)
	   {
		   System.out.println("Scheme Test Passed");
	   }
	   else
	   {
		   System.out.println("Scheme Test Failed");
	   }
   }
   
   public void testYourSecondPartition()
   {
	   UrlValidator urlVal = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   System.out.println("");
	   System.out.println("Testing Authority");
	   
	   boolean passed = true;
	   
	   String validOne = "www.google.com";
	   String validTwo = "amazon.com";
	   String validThree = "127.0.0.1";
	   
	   String invalidOne = "google";
	   String invalidTwo = ".google.com";
	   
	   String urlBig = "http://";
	   
	   String validUrl = urlBig + validOne;
	   String invalidUrl = urlBig + invalidOne;
	   
	   if(!urlVal.isValid(validUrl))
	   {
		   System.out.println("TEST FAILED. Expected valid for URL: " + validUrl);
		   passed = false;
	   }
	   
	   validUrl = urlBig + validTwo;
	   
	   if(!urlVal.isValid(validUrl))
	   {
		   System.out.println("TEST FAILED. Expected valid for URL: " + validUrl);
		   passed = false;
	   }
	   
	   validUrl = urlBig + validThree;
	   
	   if(!urlVal.isValid(validUrl))
	   {
		   System.out.println("TEST FAILED. Expected valid for URL: " + validUrl);
		   passed = false;
	   }
	   
	   if(urlVal.isValid(invalidUrl))
	   {
		   System.out.println("TEST FAILED. Expected invalid for URL: " + invalidUrl);
		   passed = false;
	   }
	   
	   invalidUrl = urlBig + invalidTwo;
	   
	   if(urlVal.isValid(invalidUrl))
	   {
		   System.out.println("TEST FAILED. Expected invalid for URL: " + invalidUrl);
		   passed = false;
	   }
	   
	   if(passed)
	   {
		   System.out.println("Authority Test Passed");
	   }
	   else
	   {
		   System.out.println("Authority Test Failed");
	   }
   }
   
   public void testYourThirdPartition()
   {
	   UrlValidator urlVal = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   System.out.println("");
	   System.out.println("Testing Path");
	   
	   boolean passed = true;
	   
	   String validOne = "/test1";
	   String validTwo = "/test1/pics";
	   
	   String invalidOne = "/..";

	   String urlBig = "http://www.google.com";
	   
	   String validUrl = urlBig + validOne;
	   String invalidUrl = urlBig + invalidOne;
	   
	   if(!urlVal.isValid(validUrl))
	   {
		   System.out.println("TEST FAILED. Expected valid for URL: " + validUrl);
		   passed = false;
	   }
	   
	   validUrl = urlBig + validTwo;
	   
	   if(!urlVal.isValid(validUrl))
	   {
		   System.out.println("TEST FAILED. Expected valid for URL: " + validUrl);
		   passed = false;
	   }
	   
	   if(urlVal.isValid(invalidUrl))
	   {
		   System.out.println("TEST FAILED. Expected invalid for URL: " + invalidUrl);
		   passed = false;
	   }
	   
	   if(passed)
	   {
		   System.out.println("Path Test Passed");
	   }
	   else
	   {
		   System.out.println("Path Test Failed");
	   }
   }
   
   public void testYourFourthPartition()
   {
	   UrlValidator urlVal = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   System.out.println("");
	   System.out.println("Testing Query");
	   
	   boolean passed = true;
	   
	   String validOne = "?action=view";
	   String validTwo = "?action=edit&mode=up";

	   String urlBig = "http://www.google.com";
	   
	   String validUrl = urlBig + validOne;
	   
	   if(!urlVal.isValid(validUrl))
	   {
		   System.out.println("TEST FAILED. Expected valid for URL: " + validUrl);
		   passed = false;
	   }
	   
	   validUrl = urlBig + validTwo;
	   
	   if(!urlVal.isValid(validUrl))
	   {
		   System.out.println("TEST FAILED. Expected valid for URL: " + validUrl);
		   passed = false;
	   }
	   
	   if(passed)
	   {
		   System.out.println("Path Test Passed");
	   }
	   else
	   {
		   System.out.println("Query Test Failed");
	   }
   }
   
   
   public void testIsValid()
   {
	   /* To properly construct a programmatic test, we need a substantial set of input parameters. 
	    * We will be segmenting the URL into the following categories:
	    * 	Protocol
	    * 	Domain Name
	    * 	Port
	    * 	Path
	    * 	Parameters
	    * 
	    * Each of these will have their own set of key-pairs that will be mapped to true or false.
	    * When testing, if all key pairs are true, then we expect a true response from isValid(). 
	    * If any of the pairs are all false, then we expect a "false" response from isValid(). 
	    * 
	    * For each of our domain names, we will also be appending a sub-domain (www.), so we 
	    * will be testing with and without the sub-domain.
	    */
	   
	   /* http://www.iana.org/assignments/uri-schemes/uri-schemes.xhtml
	    * Provides a list of valid schemes. We used these in our key-pair map.
	    * Commented out some because it was simply taking too long and crashing Eclipse
	    * You would want to use separate arrays to test each individually if thoroughly looking
	    * for more bugs
	    */
	   ResultPair [] protocolPairs = {
			   /*new ResultPair("aaa://", true),
			   new ResultPair("aaas://", true),
			   new ResultPair("about://", true),
			   new ResultPair("acap://", true),
			   new ResultPair("acct://", true),
			   new ResultPair("cap://", true),
			   new ResultPair("cid://", true),
			   new ResultPair("coap://", true),
			   new ResultPair("coaps://", true),
			   new ResultPair("crid://", true),
			   new ResultPair("data://", true),
			   new ResultPair("dav://", true),
			   new ResultPair("dict://", true),
			   new ResultPair("dns://", true),
			   new ResultPair("example://", true),
			   new ResultPair("file://", true),*/
			   new ResultPair("ftp://", true),
			   new ResultPair("geo://", true),
			   new ResultPair("go://", true),
			   new ResultPair("gopher://", true),
			   new ResultPair("h323://", true),
			   new ResultPair("http://", true),
			   new ResultPair("https://", true),
			   new ResultPair("iax://", true),
			   new ResultPair("icap://", true),
			   new ResultPair("im://", true),
			   new ResultPair("imap://", true),
			   new ResultPair("info://", true),
			   new ResultPair("ipp://", true),
			   new ResultPair("ipps://", true),
			   new ResultPair("iris://", true),/*
			   new ResultPair("iris.beep://", true),
			   new ResultPair("iris.lwz://", true),
			   new ResultPair("iris.xpc://", true),
			   new ResultPair("iris.xpcs://", true),
			   new ResultPair("jabber://", true),
			   new ResultPair("ldap://", true),
			   new ResultPair("mailto://", true),
			   new ResultPair("mid://", true),
			   new ResultPair("msrp://", true),
			   new ResultPair("msrps://", true),
			   new ResultPair("mtqp://", true),
			   new ResultPair("mupdate://", true),
			   new ResultPair("news://", true),
			   new ResultPair("nfs://", true),
			   new ResultPair("ni://", true),
			   new ResultPair("nih://", true),
			   new ResultPair("nntp://", true),
			   new ResultPair("opaquelocktoken://", true),
			   new ResultPair("pkcs11://", true),
			   new ResultPair("pop://", true),
			   new ResultPair("pres://", true),
			   new ResultPair("reload://", true),
			   new ResultPair("rtsp://", true),
			   new ResultPair("rtsps://", true),
			   new ResultPair("rtspu://", true),
			   new ResultPair("service://", true),
			   new ResultPair("session://", true),
			   new ResultPair("shttp://", true),
			   new ResultPair("sieve://", true),
			   new ResultPair("sip://", true),
			   new ResultPair("sips://", true),
			   new ResultPair("sms://", true),
			   new ResultPair("snmp://", true),
			   new ResultPair("soap.beep://", true),
			   new ResultPair("soap.beeps://", true),
			   new ResultPair("stun://", true),
			   new ResultPair("stuns://", true),
			   new ResultPair("tag://", true),
			   new ResultPair("tel://", true),
			   new ResultPair("telnet://", true),
			   new ResultPair("tftp://", true),
			   new ResultPair("thismessage://", true),
			   new ResultPair("tip://", true),
			   new ResultPair("tn3270://", true),
			   new ResultPair("turn://", true),
			   new ResultPair("turns://", true),
			   new ResultPair("tv://", true),
			   new ResultPair("urn://", true),
			   new ResultPair("vemmi://", true),
			   new ResultPair("ws://", true),
			   new ResultPair("wss://", true),
			   new ResultPair("xcon://", true),
			   new ResultPair("xcon-userid://", true),
			   new ResultPair("xmlrpc.beep://", true),
			   new ResultPair("xmlrpc.beeps://", true),
			   new ResultPair("xmpp://", true),
			   new ResultPair("z39.50r://", true),
			   new ResultPair("z39.50s://", true),*/
			   new ResultPair("www?google", false),
			   new ResultPair("w12°", false),
			   new ResultPair(":://", false),
			   new ResultPair("hp://www.bitup.org/\"", false),
			   new ResultPair("12www://", false),
			   new ResultPair("", false),
			   new ResultPair("feelin://Burn://", false),
			   new ResultPair("ls-qp://", false),
			   new ResultPair("asdfni:\\", false)
	   };		   
	   
	   /* https://en.wikipedia.org/wiki/List_of_Internet_top-level_domains
	    * Provides a list of valid TOLD. We used these in our key-pair map.
	    * Commented out some because it was taking too long and crashing Eclipse.
	    * Might want a separate array if doing thorough testing to find all bugs
	    * not just 3
	    */
	   ResultPair [] domainPairs = {
			   new ResultPair("bread.com", true),
			   new ResultPair("bagels.org", true),
			   new ResultPair("google.net", true),
			   new ResultPair("drought.int", true),
			   new ResultPair("buckets.edu", true),
			   new ResultPair("draft.gov", true),
			   new ResultPair("skiiiiiilllllzzzz.mil", true),
			   new ResultPair("www.bread.ac", true),
			   new ResultPair("www.bagels.ad", true),
			   new ResultPair("www.google.ae", true),
			   new ResultPair("www.drought.af", true),
			   new ResultPair("www.buckets.ag", true),
			   new ResultPair("www.draft.ai", true),
			   new ResultPair("bread.al", true),
			   new ResultPair("bagels.am", true),
			   new ResultPair("google.an", true),
			   new ResultPair("drought.ao", true),
			   new ResultPair("buckets.aq", true),
			   new ResultPair("draft.ar", true),
			   new ResultPair("skiiiiiilllllzzzz.as", true),
			   new ResultPair("www.bread.at", true),
			   new ResultPair("www.bagels.au", true),
			   new ResultPair("www.google.aw", true),
			   new ResultPair("www.drought.ax", true),
			   new ResultPair("www.buckets.az", true),
			   new ResultPair("www.draft.ba", true),
			   new ResultPair("www.skiiiiiilllllzzzz.bb", true),
			   new ResultPair("bread.bd", true),
			   new ResultPair("bagels.be", true),
			   new ResultPair("google.bf", true),
			   new ResultPair("drought.bg", true),
			   new ResultPair("buckets.bh", true),
			   new ResultPair("draft.bi", true),/*
			   new ResultPair("skiiiiiilllllzzzz.bj", true),
			   new ResultPair("www.bread.bm", true),
			   new ResultPair("www.bagels.bn", true),
			   new ResultPair("www.google.bo", true),
			   new ResultPair("www.drought.bq", true),
			   new ResultPair("www.buckets.br", true),
			   new ResultPair("www.draft.bs", true),
			   new ResultPair("bread.bt", true),
			   new ResultPair("bagels.bv", true),
			   new ResultPair("google.bw", true),
			   new ResultPair("drought.by", true),
			   new ResultPair("buckets.bz", true),
			   new ResultPair("draft.ca", true),
			   new ResultPair("skiiiiiilllllzzzz.cc", true),
			   new ResultPair("www.bread.cd", true),
			   new ResultPair("www.bagels.cf", true),
			   new ResultPair("www.google.cg", true),
			   new ResultPair("www.drought.ch", true),
			   new ResultPair("www.buckets.ci", true),
			   new ResultPair("www.draft.ck", true),
			   new ResultPair("www.skiiiiiilllllzzzz.cl", true),
			   new ResultPair("bread.cm", true),
			   new ResultPair("bagels.cn", true),
			   new ResultPair("google.co", true),
			   new ResultPair("drought.cr", true),
			   new ResultPair("buckets.cu", true),
			   new ResultPair("draft.cv", true),
			   new ResultPair("skiiiiiilllllzzzz.cw", true),
			   new ResultPair("www.bread.cx", true),
			   new ResultPair("www.bagels.cy", true),
			   new ResultPair("www.google.cz", true),
			   new ResultPair("www.drought.de", true),
			   new ResultPair("www.buckets.dj", true),
			   new ResultPair("www.draft.dk", true),
			   new ResultPair("bread.dm", true),
			   new ResultPair("bagels.do", true),
			   new ResultPair("google.dz", true),
			   new ResultPair("drought.ec", true),
			   new ResultPair("buckets.ee", true),
			   new ResultPair("draft.eg", true),
			   new ResultPair("skiiiiiilllllzzzz.eh", true),
			   new ResultPair("www.bread.er", true),
			   new ResultPair("www.bagels.es", true),
			   new ResultPair("www.google.et", true),
			   new ResultPair("www.drought.eu", true),
			   new ResultPair("www.buckets.fi", true),
			   new ResultPair("www.draft.fj", true),
			   new ResultPair("www.skiiiiiilllllzzzz.fk", true),
			   new ResultPair("bread.fm", true),
			   new ResultPair("bagels.fo", true),
			   new ResultPair("google.fr", true),
			   new ResultPair("drought.ga", true),
			   new ResultPair("buckets.gb", true),
			   new ResultPair("draft.gd", true),
			   new ResultPair("skiiiiiilllllzzzz.ge", true),
			   new ResultPair("www.bread.gf", true),
			   new ResultPair("www.bagels.gg", true),
			   new ResultPair("www.google.gh", true),
			   new ResultPair("www.drought.gi", true),
			   new ResultPair("www.buckets.gl", true),
			   new ResultPair("www.draft.gm", true),
			   new ResultPair("bread.gn", true),
			   new ResultPair("bagels.gp", true),
			   new ResultPair("google.gq", true),
			   new ResultPair("drought.gr", true),
			   new ResultPair("buckets.gs", true),
			   new ResultPair("draft.gt", true),
			   new ResultPair("skiiiiiilllllzzzz.gu", true),
			   new ResultPair("www.bread.gw", true),
			   new ResultPair("www.bagels.gy", true),
			   new ResultPair("www.google.hk", true),
			   new ResultPair("www.drought.hm", true),
			   new ResultPair("www.buckets.hn", true),
			   new ResultPair("www.draft.hr", true),
			   new ResultPair("www.skiiiiiilllllzzzz.ht", true),
			   new ResultPair("bread.hu", true),
			   new ResultPair("bagels.id", true),
			   new ResultPair("google.ie", true),
			   new ResultPair("drought.il", true),
			   new ResultPair("buckets.im", true),
			   new ResultPair("draft.in", true),
			   new ResultPair("skiiiiiilllllzzzz.io", true),
			   new ResultPair("www.bread.iq", true),
			   new ResultPair("www.bagels.ir", true),
			   new ResultPair("www.google.is", true),
			   new ResultPair("www.drought.it", true),*/
			   new ResultPair("www.buckets.je", true),
			   new ResultPair("www.draft.jm", true),
			   new ResultPair("bread.jo", true),
			   new ResultPair("bagels.jp", true),
			   new ResultPair("google.ke", true),
			   new ResultPair("drought.kg", true),
			   new ResultPair("buckets.kh", true),
			   new ResultPair("draft.ki", true),
			   new ResultPair("skiiiiiilllllzzzz.km", true),
			   new ResultPair("www.bread.kn", true),
			   new ResultPair("www.bagels.kp", true),
			   new ResultPair("www.google.kr", true),
			   new ResultPair("www.drought.kw", true),
			   new ResultPair("www.buckets.ky", true),
			   new ResultPair("www.draft.kz", true),
			   new ResultPair("www.skiiiiiilllllzzzz.la", true),
			   new ResultPair("bread.lb", true),
			   new ResultPair("bagels.lc", true),
			   new ResultPair("google.li", true),
			   new ResultPair("drought.lk", true),
			   new ResultPair("buckets.lr", true),
			   new ResultPair("draft.ls", true),
			   new ResultPair("skiiiiiilllllzzzz.lt", true),
			   new ResultPair("www.bread.lu", true),
			   new ResultPair("www.bagels.lv", true),
			   new ResultPair("www.google.ly", true),
			   new ResultPair("www.drought.ma", true),
			   new ResultPair("www.buckets.mc", true),
			   new ResultPair("www.draft.md", true),
			   new ResultPair("bread.me", true),
			   new ResultPair("bagels.mg", true),
			   new ResultPair("google.mh", true),
			   new ResultPair("drought.mk", true),
			   new ResultPair("buckets.ml", true),
			   new ResultPair("draft.mm", true),
			   new ResultPair("skiiiiiilllllzzzz.mn", true),
			   new ResultPair("www.bread.mo", true),
			   new ResultPair("www.bagels.mp", true),
			   new ResultPair("www.google.mq", true),
			   new ResultPair("www.drought.mr", true),
			   new ResultPair("www.buckets.ms", true),
			   new ResultPair("www.draft.mt", true),
			   new ResultPair("www.skiiiiiilllllzzzz.mu", true),
			   new ResultPair("bread.mv", true),
			   new ResultPair("bagels.mw", true),
			   new ResultPair("google.mx", true),
			   new ResultPair("drought.my", true),
			   new ResultPair("buckets.mz", true),
			   new ResultPair("draft.na", true),
			   new ResultPair("skiiiiiilllllzzzz.nc", true),
			   new ResultPair("www.bread.ne", true),
			   new ResultPair("www.bagels.nf", true),
			   new ResultPair("www.google.ng", true),
			   new ResultPair("www.drought.ni", true),
			   new ResultPair("www.buckets.nl", true),
			   new ResultPair("www.draft.no", true),
			   new ResultPair("bread.np", true),
			   new ResultPair("bagels.nr", true),
			   new ResultPair("google.nu", true),
			   new ResultPair("drought.nz", true),
			   new ResultPair("buckets.om", true),
			   new ResultPair("draft.pa", true),
			   new ResultPair("skiiiiiilllllzzzz.pe", true),
			   new ResultPair("www.bread.pf", true),
			   new ResultPair("www.bagels.pg", true),
			   new ResultPair("www.google.ph", true),
			   new ResultPair("www.drought.pk", true),
			   new ResultPair("www.buckets.pl", true),
			   new ResultPair("www.draft.pm", true),
			   new ResultPair("www.skiiiiiilllllzzzz.pn", true),
			   new ResultPair("bread.pr", true),
			   new ResultPair("bagels.ps", true),
			   new ResultPair("google.pt", true),
			   new ResultPair("drought.pw", true),
			   new ResultPair("buckets.py", true),
			   new ResultPair("draft.qa", true),
			   new ResultPair("skiiiiiilllllzzzz.re", true),
			   new ResultPair("www.bread.ro", true),
			   new ResultPair("www.bagels.rs", true),
			   new ResultPair("www.google.ru", true),
			   new ResultPair("www.drought.rw", true),
			   new ResultPair("www.buckets.sa", true),
			   new ResultPair("www.draft.sb", true),
			   new ResultPair("bread.sc", true),
			   new ResultPair("bagels.sd", true),
			   new ResultPair("google.se", true),
			   new ResultPair("drought.sg", true),
			   new ResultPair("buckets.sh", true),
			   new ResultPair("draft.si", true),
			   new ResultPair("skiiiiiilllllzzzz.sj", true),
			   new ResultPair("www.bread.sk", true),
			   new ResultPair("www.bagels.sl", true),
			   new ResultPair("www.google.sm", true),
			   new ResultPair("www.drought.sn", true),
			   new ResultPair("www.buckets.so", true),
			   new ResultPair("www.draft.sr", true),
			   new ResultPair("www.skiiiiiilllllzzzz.ss", true),
			   new ResultPair("bread.st", true),
			   new ResultPair("bagels.su", true),
			   new ResultPair("google.sv", true),
			   new ResultPair("drought.sx", true),
			   new ResultPair("buckets.sy", true),
			   new ResultPair("draft.sz", true),
			   new ResultPair("skiiiiiilllllzzzz.tc", true),
			   new ResultPair("www.bread.td", true),
			   new ResultPair("www.bagels.tf", true),
			   new ResultPair("www.google.tg", true),
			   new ResultPair("www.drought.th", true),
			   new ResultPair("www.buckets.tj", true),
			   new ResultPair("www.draft.tk", true),
			   new ResultPair("bread.tl", true),
			   new ResultPair("bagels.tm", true),
			   new ResultPair("google.tn", true),
			   new ResultPair("drought.to", true),
			   new ResultPair("buckets.tp", true),
			   new ResultPair("draft.tr", true),
			   new ResultPair("skiiiiiilllllzzzz.tt", true),
			   new ResultPair("www.bread.tv", true),
			   new ResultPair("www.bagels.tw", true),
			   new ResultPair("www.google.tz", true),
			   new ResultPair("www.drought.ua", true),
			   new ResultPair("www.buckets.ug", true),
			   new ResultPair("www.draft.uk", true),
			   new ResultPair("www.skiiiiiilllllzzzz.us", true),
			   new ResultPair("bread.uy", true),
			   new ResultPair("bagels.uz", true),
			   new ResultPair("google.va", true),
			   new ResultPair("drought.vc", true),
			   new ResultPair("buckets.ve", true),
			   new ResultPair("draft.vg", true),
			   new ResultPair("skiiiiiilllllzzzz.vi", true),
			   new ResultPair("www.bread.vn", true),
			   new ResultPair("www.bagels.vu", true),
			   new ResultPair("www.google.wf", true),
			   new ResultPair("www.drought.ws", true),
			   new ResultPair("www.buckets.ye", true),
			   new ResultPair("www.draft.yt", true),
			   new ResultPair("bread.za", true),
			   new ResultPair("bagels.zm", true),
			   new ResultPair("google.zw", true),
			   new ResultPair("Thisisaverylongsentencethatshouldabsolutelybreakthesystembecauseitshouldntallowthislongofastringforadomainlikethisisjustcrazyhowwouldanyonetypethisinatallitisjustcrazylong.com", false),
			   new ResultPair("www.open.bad!", false),
			   new ResultPair("blue.123", false),
			   new ResultPair("www.reddit.$*#", false),
			   new ResultPair("483.25939.2939", false),
			   new ResultPair("255.255.255.255", true),
               new ResultPair("256.256.256.256", false)
	   };
	   
	   /* 
	    * Port numbers should not have special characters, or be just letters
	    */
	   ResultPair [] portPairs = {
			   new ResultPair(":5000", true),
			   new ResultPair(":20", true),
			   new ResultPair(":8483", true),
			   new ResultPair(":#$*#", false),
			   new ResultPair(":--2349", false),
			   new ResultPair(":asdfasdf", false),
			   new ResultPair(":", false),
			   new ResultPair("", true)
	   };
	   
	   /* Paths shouldn't have double slashes, or .. */
	   ResultPair [] pathPairs = {
			   new ResultPair("/somepath1", true),
               new ResultPair("/somepath/path2/path3", true),
               new ResultPair("/sd$_asd", true),
               new ResultPair("/..", false),
               new ResultPair("/../", false),
               new ResultPair("../", false),
               new ResultPair("", true),
               new ResultPair("/..//file", false),
               new ResultPair("/test1//file", false)
	   };
	   
	   /* No special characters int eh wrong place, and should have proper pairs */
	   ResultPair [] parameterPairs = {
			   new ResultPair("?request=answer", true),
               new ResultPair("?one=ten&two=eleven", true),
               new ResultPair("", true),
               new ResultPair("?", true),
               new ResultPair("?###new=&&LUE", false),
               new ResultPair("asdf=dfdd", false),
               new ResultPair("?=red", false),
               new ResultPair("=red", false)
	   };

	   /* Intro text before running the programmatic testing */
	   System.out.println("Programmatic testing of URLs commencing: Passed tests will not be reported (over 7 million combinations)");
	   System.out.println("Lines starting with 'TEST FAILED X:' indicates a test that has failed");
	   
	   // Create variables to hold iterators, the number of tests, and the failed tests
	   int v;
	   int w;
	   int x;
	   int y;
	   int z;
	   int itrNum = 0;
	   int testFails = 0;
	   // Create an instance for our UrlValidator
	   UrlValidator urlVal = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   // For loops to loop through all possible combinations
	   for(v = 0; v < protocolPairs.length; v++)
	   {
		   for(w = 0; w < domainPairs.length; w++) 
		   {
			   for(x = 0; x < portPairs.length; x++) 
			   {
				   for(y = 0; y < pathPairs.length; y++) 
				   {
					   for(z = 0; z < parameterPairs.length; z++) 
					   {
						   // Bools to store results, and iterate count of tests performed 
						   boolean inputValid;
						   boolean testValid;
						   itrNum++;
						   // Create the URL that will be tested
						   String url = protocolPairs[v].item + domainPairs[w].item + portPairs[x].item + pathPairs[y].item + parameterPairs[z].item;
						   
						   // Check to see if a valid URL was generated by our programmatic tester
						   if (protocolPairs[v].valid && domainPairs[w].valid && portPairs[x].valid && pathPairs[y].valid && parameterPairs[z].valid) {
							   inputValid = true; 
						   } else {
							   inputValid = false;
						   }
						   
						   // Get result from isValid method
						   testValid = urlVal.isValid(url);
						   
						   // Check to see if they agree
						   if (inputValid == testValid) {
							   // Do nothing because the test was successful
						   } else {
							   // Increment the count of failed tests. Print out error results to console
							   testFails++;
							   System.out.println("TEST FAILED " + itrNum + ": URL: " + url + " Expected: " + inputValid + " Result: " + testValid);
						   }
					   }
				   }
			   }
		   }  
	   }
	   // Print out aggregate results of the test to the console (good summary at the end)
	   double d = ((double)testFails)  / ((int)itrNum);
	   System.out.println("TESTS RUN: " + itrNum + " TESTS FAILED: " + testFails + " Percentage: " + d);
   }

}
