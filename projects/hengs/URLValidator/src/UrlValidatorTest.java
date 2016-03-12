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
	   System.out.println(urlVal.isValid("http://www.amazon.com"));
	   
	   
   }
   
   
   public void testYourFirstPartition()
   {
	   
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   System.out.println("\n\nTesting First Partition: Schemes");
	   
	   String[] goodschemes = new String[4];
	   String[] badschemes = new String[5];
	   
	   
	   goodschemes[0] = "http://";
	   goodschemes[1] = "ftp://";
	   goodschemes[2] = "h3t://";
	   goodschemes[3] = "";
	   badschemes[0] = "3ht://";
	   badschemes[1] = "http:/";
	   badschemes[2] = "http:";
	   badschemes[3] = "http/";
	   badschemes[4] = "://";
	   
	   String validAuthority = "www.amazon.com";
	   String validPort = ":80";
	   String validPath = "/test123";
	   String validOption = "/test1/file";
	   String validQuery = "?action=view";
	   
	   System.out.println("\nTesting Expected Good Schemes");
	   for(int i = 0; i < 4; i++){
		   String testUrl = goodschemes[i] + validAuthority + validPort + validPath + validOption + validQuery;
		   if(urlVal.isValid(testUrl)){
			   System.out.println("\nSUCCESS!!! Correct Expecation, URL is valid: " + testUrl);
		   }
		   else{
			   System.out.println("\nFAIL!!! Incorrect Expecation, URL is invalid: " + testUrl);
		   }
	   }
	   System.out.println("\n\nTesting Expected Bad Schemes");
	   for(int i = 0; i < 5; i++){
		   String testUrl = badschemes[i] + validAuthority + validPort + validPath + validOption + validQuery;
		   if(urlVal.isValid(testUrl)){
			   System.out.println("\nFAIL!!! Incorrect Expecation, URL is valid: " + testUrl);
		   }
		   else{
			   System.out.println("\nSUCCESS!!! Correct Expecation, URL is invalid: " + testUrl);
		   }
	   }
	   
   }
   
   public void testYourSecondPartition(){
	   
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   System.out.println("\n\nTesting Second Partition: Authority");
	   
	   String[] goodauthority = new String[7];
	   String[] badauthority = new String[8];
	   
	   
	   goodauthority[0] = "www.google.com";
	   goodauthority[1] = "go.com";
	   goodauthority[2] = "go.au";
	   goodauthority[3] = "0.0.0.0";
	   goodauthority[4] = "255.255.255.255";
	   goodauthority[5] = "255.com";
	   goodauthority[6] = "go.cc";
	   
	   badauthority[0] = "256.256.256.256";
	   badauthority[1] = "1.2.3.4.5";
	   badauthority[2] = ".1.2.3.4";
	   badauthority[3] = "go.a";
	   badauthority[4] = "aaa.";
	   badauthority[5] = ".aaa";
	   badauthority[6] = "aaa";
	   badauthority[7] = "";
	  
	   
	   String validScheme = "http://";
	   String validPort = ":80";
	   String validPath = "/test123";
	   String validOption = "/test1/file";
	   String validQuery = "?action=view";
	   
	   System.out.println("\n\nTesting Expected Good Authority:");
	   for(int i = 0; i < 7; i++){
		   String testUrl = validScheme + goodauthority[i] + validPort + validPath + validOption + validQuery;
		   if(urlVal.isValid(testUrl)){
			   System.out.println("\nSUCCESS!!! Correct Expecation, URL is valid: " + testUrl);
		   }
		   else{
			   System.out.println("\nFAIL!!! Incorrect Expecation, URL is invalid: " + testUrl);
		   }
	   }
	   System.out.println("\n\nTesting Expected Bad Authority");
	   for(int i = 0; i < 8; i++){
		   String testUrl = validScheme + badauthority[i] + validPort + validPath + validOption + validQuery;
		   if(urlVal.isValid(testUrl)){
			   System.out.println("\nFAIL!!! Incorrect Expecation, URL is valid: " + testUrl);
		   }
		   else{
			   System.out.println("\nSUCCESS!!! Correct Expecation, URL is invalid: " + testUrl);
		   }
	   }
	   
   }
   public void testYourThirdPartition(){
	   
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   System.out.println("\n\nTesting Third Partition: Port");
	   
	   String[] goodport = new String[5];
	   String[] badport = new String[5];
	   
	   
	   goodport[0] = ":80";
	   goodport[1] = ":0";
	   goodport[2] = ":65535";
	   goodport[3] = "";
	   goodport[4] = ":65636";
	  
	   
	   
	   badport[0] = ":-1";
	   badport[1] = ":65a";
	   badport[2] = ":a77";
	   badport[3] = ":-a";
	   badport[4] = ":abc";
	   
	  
	   
	   String validScheme = "http://";
	   String validAuthority = "www.amazon.com";
	   //String validPort = ":80";
	   String validPath = "/test123";
	   String validOption = "/test1/file";
	   String validQuery = "?action=view";
	   
	   System.out.println("\n\nTesting Expected Good Port:");
	   for(int i = 0; i < 5; i++){
		   String testUrl = validScheme + validAuthority + goodport[i] + validPath + validOption + validQuery;
		   if(urlVal.isValid(testUrl)){
			   System.out.println("\nSUCCESS!!! Correct Expecation, URL is valid: " + testUrl);
		   }
		   else{
			   System.out.println("\nFAIL!!! Incorrect Expecation, URL is invalid: " + testUrl);
		   }
	   }
	   System.out.println("\n\nTesting Expected Bad Port");
	   for(int i = 0; i < 5; i++){
		   String testUrl = validScheme + validAuthority + badport[i] + validPath + validOption + validQuery;
		   if(urlVal.isValid(testUrl)){
			   System.out.println("\nFAIL!!! Incorrect Expecation, URL is valid: " + testUrl);
		   }
		   else{
			   System.out.println("\nSUCCESS!!! Correct Expecation, URL is invalid: " + testUrl);
		   }
	   }
	   
   }

public void testYourFourthPartition(){
	   
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   System.out.println("\n\nTesting Fourth Partition: Path");
	   
	   String[] goodpath = new String[6];
	   String[] badpath = new String[4];
	   
	   
	   goodpath[0] = "/test1";
	   goodpath[1] = "/t123";
	   goodpath[2] = "/$23";
	   goodpath[3] = "";
	   goodpath[4] = "/test1/";
	   goodpath[5] = "/test1/file";
	  
	   badpath[0] = "/..";
	   badpath[1] = "/../";
	   badpath[2] = "/..//file";
	   badpath[3] = "/test1//file";
	   
	   
	  
	   
	   String validScheme = "http://";
	   String validAuthority = "www.amazon.com";
	   String validPort = ":80";
	   //String validPath = "/test123";
	   String validOption = "/test1/file";
	   String validQuery = "?action=view";
	   
	   System.out.println("\n\nTesting Expected Good Path:");
	   for(int i = 0; i < 6; i++){
		   String testUrl = validScheme + validAuthority + validPort + goodpath[i] + validOption + validQuery;
		   if(urlVal.isValid(testUrl)){
			   System.out.println("\nSUCCESS!!! Correct Expecation, URL is valid: " + testUrl);
		   }
		   else{
			   System.out.println("\nFAIL!!! Incorrect Expecation, URL is invalid: " + testUrl);
		   }
	   }
	   System.out.println("\n\nTesting Expected Bad Path");
	   for(int i = 0; i < 4; i++){
		   String testUrl = validScheme + validAuthority + validPort + badpath[i] + validOption + validQuery;
		   if(urlVal.isValid(testUrl)){
			   System.out.println("\nFAIL!!! Incorrect Expecation, URL is valid: " + testUrl);
		   }
		   else{
			   System.out.println("\nSUCCESS!!! Correct Expecation, URL is invalid: " + testUrl);
		   }
	   }
	   
}
   
	public void testYourFifthPartition(){
	   
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   System.out.println("\n\nTesting Fifth Partition: Options");
	   
	   String[] goodoption = new String[9];
	   String[] badoption = new String[7];
	   	   
	   goodoption[0] = "/test1";
	   goodoption[1] = "/t123";
	   goodoption[2] = "/$23";
	   goodoption[3] = "";
	   goodoption[4] = "/test1/";
	   goodoption[5] = "/test1/file";
	   goodoption[6] = "/t123/file";
	   goodoption[7] = "/$23/file";
	   goodoption[8] = "/test1//file";
	  
	   badoption[0] = "/..";
	   badoption[1] = "/../";
	   badoption[2] = "/..//file";
	   badoption[3] = "/test1//file";
	   badoption[4] = "/#/file";
	   badoption[5] = "/#";
	   badoption[6] = "/../file";
	   
	   String validScheme = "http://";
	   String validAuthority = "www.amazon.com";
	   String validPort = ":80";
	   String validPath = "/test123";
	   //String validOption = "/test1/file";
	   String validQuery = "?action=view";
	   
	   System.out.println("\n\nTesting Expected Good Option:");
	   for(int i = 0; i < 9; i++){
		   String testUrl = validScheme + validAuthority + validPort + validPath + goodoption[i] + validQuery;
		   if(urlVal.isValid(testUrl)){
			   System.out.println("\nSUCCESS!!! Correct Expecation, URL is valid: " + testUrl);
		   }
		   else{
			   System.out.println("\nFAIL!!! Incorrect Expecation, URL is invalid: " + testUrl);
		   }
	   }
	   System.out.println("\n\nTesting Expected Bad Option");
	   for(int i = 0; i < 7; i++){
		   String testUrl = validScheme + validAuthority + validPort + validPath + badoption[i] + validQuery;
		   if(urlVal.isValid(testUrl)){
			   System.out.println("\nFAIL!!! Incorrect Expecation, URL is valid: " + testUrl);
		   }
		   else{
			   System.out.println("\nSUCCESS!!! Correct Expecation, URL is invalid: " + testUrl);
		   }
	   }
	   
}
   
	public void testYourSixthPartition(){
		   
		   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
		   System.out.println("\n\nTesting Sixth Partition: Query");
		   
		   String[] goodquery = new String[3];
		   String[] badquery = new String[2];
		   	   
		   goodquery[0] = "?action=view";
		   goodquery[1] = "?action=edit&mode=up";
		   goodquery[2] = "";
		  
		   badquery[0] = "/dog/?action=";
		   badquery[1] = "justquerying";
		      
		   String validScheme = "http://";
		   String validAuthority = "www.amazon.com";
		   String validPort = ":80";
		   String validPath = "/test123";
		   String validOption = "/test1/file";
		   //String validQuery = "?action=view";
		   
		   System.out.println("\n\nTesting Expected Good Query:");
		   for(int i = 0; i < 3; i++){
			   String testUrl = validScheme + validAuthority + validPort + validPath + validOption + goodquery[i];
			   if(urlVal.isValid(testUrl)){
				   System.out.println("\nSUCCESS!!! Correct Expecation, URL is valid: " + testUrl);
			   }
			   else{
				   System.out.println("\nFAIL!!! Incorrect Expecation, URL is invalid: " + testUrl);
			   }
		   }
		   System.out.println("\n\nTesting Expected Bad Query");
		   for(int i = 0; i < 2; i++){
			   String testUrl = validScheme + validAuthority + validPort + validPath + validOption + badquery[i];
			   if(urlVal.isValid(testUrl)){
				   System.out.println("\nFAIL!!! Incorrect Expecation, URL is valid: " + testUrl);
			   }
			   else{
				   System.out.println("\nSUCCESS!!! Correct Expecation, URL is invalid: " + testUrl);
			   }
		   }
		   
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
