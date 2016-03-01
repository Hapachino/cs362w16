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
public class URLValidatorTest extends TestCase {

	   private boolean printStatus = false;
	   private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.

	   public URLValidatorTest(String testName) {
	      super(testName);
	   }
    // manual test array
    public String[] populateTestArray()
    {
    //create array of test strings
    String[] testURLs = new String[20];
    
    testURLs[0]="http://www.amazon.com";
    testURLs[1]="http://www.amazšn.com";
    testURLs[2]="www.amazon.comhttp://";
    testURLs[3]="www.google";
    testURLs[4]="http://www.google.com";
    testURLs[5]="http://www.go.com";
    //TODO add rest of manual tests correct function to accept a integer that is the size of the number of manual tests?
    }
	
   //IsValid tests
   public void testManualTest(String testURL)
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
  	   boolean result;
       //URL Validation
  	   System.out.println("Testing valid URL address:"+testURL);
  	   result= urlVal.isValid(testURL);
  	   if (result)
  	   { 
  		   System.out.println("Valid URL:"+testURL+" Pass");
  	   }
  	   else {
  		   System.out.println("Valid URL:"+testURL+" Fail");
  	   }
 	   System.out.println("Test Completed");
   }

   public void testIsValid(){
	   	int numManualTests=5;//TODO fix
	   	String[] manualTests=populateTestArray();
	   	// Manual IsValid tests
    for(int i=0; i<numManualTests; i++){
        testManualTest(manualTests[i]);
    } 
   }
}
