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
   
   
   public void testYourFirstPartition()
   {
	   
   }
   
   public void testYourSecondPartition(){
	   
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
