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


import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Random;

import junit.framework.TestCase;





/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */
public class UrlValidatorTest extends TestCase {
   
	// test object is used to store the different parts of our test urls and their validity/description
   private class testObj {
	   public testObj(boolean valid, String val, String desc) {
		   isValid = valid; 
		   value = val; 
		   description = desc; 
	   }
	   public boolean isValid;
	   public String description; 
	   public String value; 
   }
   
   
   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   System.out.println(urlVal.isValid("http://www.amazon.com"));
	   
	   
   }
   
   
   public void testYourFirstPartition()
   {
	   
   }
   
   public void testYourSecondPartition(){
	   
   }
   
   /* random tester that loops 1000 times creating "random" combinations of our different test cases that are outlined
    in fillTestArrays. It prints the test url and expected result plus keeps track of the count for the amount of errors 
    for the different test parts */ 
   public void testIsValid()
   {
	   // create the url validator
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   // used for random number generation 
	   Random randNumGen = new Random(); 
	   
	   // create and fill our test part arrays
	   List<testObj> test_protocols = new ArrayList<testObj>(); 
	   List<testObj> test_mains = new ArrayList<testObj>(); 
	   List<testObj> test_paths = new ArrayList<testObj>(); 
	   fillTestArrays(test_protocols, test_mains, test_paths);
	   
	   // used to store our random numbers that are genarated
	   int randomNum1 = 0; 
	   int randomNum2 = 0; 
	   int randomNum3 = 0; 
	   
	   // stores the size of our arrays to be used as the upper limit for rand num generation
	   int protsSize = test_protocols.size(); 
	   int mainsSize = test_mains.size(); 
	   int pathsSize = test_paths.size();
	   
	   // the individual test objects 
	   testObj testProt = null;
	   testObj testMain = null; 
	   testObj testPath = null;
	   
	   // used for our expected and actual return values from url validator 
	   boolean expected = false; 
	   boolean actual = false; 
	   
	   String testUrl = ""; 
	   
	   // hash map is used to keep track of the count of the errors for different url parts 
	   Map<String, Integer> resultMap = new HashMap<String,Integer>(1000); 
	   
	   for(int i = 0;i<1000;i++)
	   {
		   // generate three random nums from 0 to size of the particular test lists - 1
		   randomNum1 = randNumGen.nextInt(protsSize);
		   randomNum2 = randNumGen.nextInt(mainsSize); 
		   randomNum3 = randNumGen.nextInt(pathsSize); 
		   
		   // get the test part that lives at the random number genearated position in the list 
		   testProt = test_protocols.get(randomNum1);
		   testMain = test_mains.get(randomNum2);
		   testPath = test_paths.get(randomNum3); 
		   
		   // create the test url 
		   testUrl = testProt.value + testMain.value + testPath.value; 
		   
		   // calculate the expected result
		  if(testProt.isValid)
		  {
			  if (testMain.isValid)
			  {
				  if(testPath.isValid)
				  {
					  expected = true; 
				  }
				  else
				  {
					  expected = false; 
				  }
			  }
			  else
			  {
				  expected = false; 
			  }
		  }
		  else 
		  {
			  expected = false; 
		  }
		   
		  // run test url through validator 
		   actual = urlVal.isValid(testUrl); 
		   
		   // if the results do not match
		   if(actual != expected)
		   {
			   // get the description 
			   String description = testProt.value + testMain.value + testPath.value;
			   
			   // print expected, actual, and description 
			   System.out.println("Expected:" + expected + " Actual: " + actual);
			   System.out.println("Items tested: " + description);
			   
			   // if the map already has our test protocol string present inc the value
			   if(resultMap.containsKey(testProt.value))
			   {
				   Integer count = resultMap.get(testProt.value); 
				   count++; 
				   resultMap.put(testProt.value, count); 
			   }
			   // else add it to the map with a value of 1 
			   else
			   {
				   resultMap.put(testProt.value, 1); 
			   }
			   
			   // repeat process for test main 
			   if(resultMap.containsKey(testMain.value))
			   {
				   Integer count = resultMap.get(testMain.value); 
				   count++; 
				   resultMap.put(testMain.value, count); 
			   }
			   else
			   {
				   resultMap.put(testMain.value, 0); 
			   }
			   
			   // repeat process for test path 
			   if(resultMap.containsKey(testPath.value))
			   {
				   Integer count = resultMap.get(testPath.value); 
				   count++; 
				   resultMap.put(testPath.value, count); 
			   }
			   else
			   {
				   resultMap.put(testPath.value, 0); 
			   }
		   }
	   }
	   
	   // print total error counts 
	   System.out.println("Total error counts are as follows.");
	   
	   // print map adapted from http://stackoverflow.com/questions/18280373/iterate-dictionary-in-java
	   for (Map.Entry<String, Integer> entry : resultMap.entrySet()) {
		   testUrl = entry.getKey(); 
		   Integer count = entry.getValue(); 
		   
		   System.out.println(testUrl + " " + count + " times"); 
	   }
   }
   
   // fill the test lists of test testObjs, which are test url pieces 
   // to add more test cases simply add more testobjs and add them to their respective lists 
   public void fillTestArrays(List<testObj> test_protocols, List<testObj> test_mains,
		List<testObj> test_paths) {
	   
	   testObj prot1 = new testObj (true, "http://", "Simple http ");
	   testObj prot2 = new testObj(true, "", "Protocol: Empty "); 
	   testObj prot3 = new testObj(false, "htp", "Protocol: Deformed http "); 
	   testObj prot4 = new testObj(true, "ftp://", "Protocol: File transfer protocol "); 
	   
	   test_protocols.add(prot1); 
	   test_protocols.add(prot2); 
	   test_protocols.add(prot3); 
	   test_protocols.add(prot4); 
	   
	   testObj main1 = new testObj(true, "www.google.com", "Main: .com Host with WWW ");
	   testObj main2 = new testObj(true, "google.com", "Main: .com Host with no WWW "); 
	   testObj main3 = new testObj(true, "oregonstate.edu", "Main: .edu Host with no WWW ");
	   testObj main4 = new testObj(true, "www.oregonstate.edu", "Main: .edu host with WWW "); 
	   testObj main5 = new testObj(true, "www.w3.org", "Main: .org host with WWW ");
	   testObj main6 = new testObj(false, "w.w3.org", "Main: .org host with Malformed WWW ");
	   testObj main7 = new testObj(false, "www.google.coom", "Main: malformed .com with WWW ");
	   
	   test_mains.add(main1); 
	   test_mains.add(main2); 
	   test_mains.add(main3);
	   test_mains.add(main4);
	   test_mains.add(main5);
	   test_mains.add(main6);
	   test_mains.add(main7);
	   
	   testObj path1 = new testObj(true, ":80", "Path: only a port number of 2 digits");
	   testObj path2 = new testObj(true, ":50034", "Path: only a port number of 5 digits");
	   testObj path3 = new testObj(false, ":5555555", "Path: only a port number of 7 digits");
	   testObj path4 = new testObj(true, "/?action=something", "Path: 1 query string param");
	   testObj path5 = new testObj(true, "/?action=something&action2=somethingelse", "Path: 2 query string param");
	   testObj path6 = new testObj(true, "/hello/there.html", "Path: two location specifiers and html extension");
	   testObj path7 = new testObj(true, "/hello?action=something", "Path: one location and a query string");
	   testObj path8 = new testObj(false, "/hello//", "Path: two slashes adjacent");
	   testObj path9 = new testObj(false, "??action=hello", "Path: query string with two question marks");
	   
	   test_paths.add(path1);
	   test_paths.add(path2);
	   test_paths.add(path3);
	   test_paths.add(path4);
	   test_paths.add(path5);
	   test_paths.add(path6);
	   test_paths.add(path7);
	   test_paths.add(path8);
	   test_paths.add(path9);
	   
	}

}
