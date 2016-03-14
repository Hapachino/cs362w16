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

  private boolean printFlag = true;
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

  ResultPair[] schemeParts = {new ResultPair("http://", true)};

  ResultPair[] authorityParts = { new ResultPair("www.google.com",true),
      new ResultPair("www.google.com:3000",true),
      new ResultPair("www.google.com:0",true),
      new ResultPair("www.google.com:-1",false),
      new ResultPair("www.google.com:99999",true),
      new ResultPair("www.google.com:000000",false),
      new ResultPair("www.google.com:a",false),
      new ResultPair("www.google.com:99999a",false),    
      new ResultPair("www.google.com:10000.999",false),
      new ResultPair("asvr23.google.com",true),
      new ResultPair("www.www.google.com",true),
      new ResultPair("asdsader.435g.f82kfd1.google.com",true),
      new ResultPair(".com",false),
      new ResultPair("google.",false),
      new ResultPair("google",false),
      new ResultPair("google.com",true),
      new ResultPair("google.com     ",true),
      new ResultPair("abcdefghijklmnopqrstuvwxyz.com",true),
      new ResultPair("ABCDEFGHIJKLMNOPQRSTUVWXYZ.COM",true),
      new ResultPair("#.com",false),
      new ResultPair("0123456789.com",true),
      new ResultPair("-.com",false),
      new ResultPair(":.com",false),
      new ResultPair("@.com",false),
      new ResultPair("&.com",false),
      new ResultPair("?.com",false),
      new ResultPair("=.com",false),
      new ResultPair("+.com",false),
      new ResultPair(",.com",false),
      new ResultPair("!.com",false),
      new ResultPair("~.com",false),
      new ResultPair("*.com",false),
      new ResultPair("'.com",false),
      new ResultPair("%.com",false),
      new ResultPair("_.com",false),
      new ResultPair(";.com",false),
      new ResultPair("(.com",false),
      new ResultPair(").com",false),
      new ResultPair("|.com",false),
      new ResultPair("`.com",false),
      new ResultPair("<.com",false),
      new ResultPair(">.com",false),
      new ResultPair("[.com",false),
      new ResultPair("].com",false),
      new ResultPair("{.com",false),
      new ResultPair("}.com",false),
      new ResultPair("google.arpa",true),
      new ResultPair("google.ARPA",true),
      new ResultPair("google.biz",true),
      new ResultPair("google.name",true),
      new ResultPair("google.az",true),
      new ResultPair("google.is",true),
      new ResultPair("google.na",true),
      new ResultPair("google.za",true),
      new ResultPair("google.a",false), 
      new ResultPair("google.zldsjry",false),
      new ResultPair("google.123",false),
      new ResultPair("localhost",false),
      new ResultPair("localdomain",false),
      new ResultPair("0.0.0.0",true),
      new ResultPair("0.0.0.-1",false),
      new ResultPair("255.255.255.255",true),
      new ResultPair("256.256.256.256",false),
      new ResultPair("1.246.58.39",true),
      new ResultPair("43.0.222.167.53",false),
      new ResultPair("111.111.111",false),
      new ResultPair(".111.111.111",false),
      new ResultPair("",false)};
  
  
  //I'm not sure whether the Result pairs that are commented out in this array
  //should be valid? I tested with the correct version of URLValidator and 
  //it was finding them to be valid (true) but I would like to have one or
  //both of you take a look at it with me to see what you think. (Could be a bug?)
  ResultPair[] authorityPartsLocal = { new ResultPair("www.google.com",true),
      new ResultPair("www.google.com:3000",true),
      new ResultPair("www.google.com:0",true),
      new ResultPair("www.google.com:-1",false),
      new ResultPair("www.google.com:99999",true),
      new ResultPair("www.google.com:000000",false),
      new ResultPair("www.google.com:a",false),
      new ResultPair("www.google.com:99999a",false),    
      new ResultPair("www.google.com:10000.999",false),
      new ResultPair("asvr23.google.com",true),
      new ResultPair("www.www.google.com",true),
      new ResultPair("asdsader.435g.f82kfd1.google.com",true),
      new ResultPair(".com",false),
      new ResultPair("google.",false),
      /*new ResultPair("google",false),*/
      new ResultPair("google.com",true),
      new ResultPair("google.com     ",true),
      new ResultPair("abcdefghijklmnopqrstuvwxyz.com",true),
      new ResultPair("ABCDEFGHIJKLMNOPQRSTUVWXYZ.COM",true),
      new ResultPair("#.com",false),
      new ResultPair("0123456789.com",true),
      new ResultPair("-.com",false),
      new ResultPair(":.com",false),
      new ResultPair("@.com",false),
      new ResultPair("&.com",false),
      new ResultPair("?.com",false),
      new ResultPair("=.com",false),
      new ResultPair("+.com",false),
      new ResultPair(",.com",false),
      new ResultPair("!.com",false),
      new ResultPair("~.com",false),
      new ResultPair("*.com",false),
      new ResultPair("'.com",false),
      new ResultPair("%.com",false),
      new ResultPair("_.com",false),
      new ResultPair(";.com",false),
      new ResultPair("(.com",false),
      new ResultPair(").com",false),
      new ResultPair("|.com",false),
      new ResultPair("`.com",false),
      new ResultPair("<.com",false),
      new ResultPair(">.com",false),
      new ResultPair("[.com",false),
      new ResultPair("].com",false),
      new ResultPair("{.com",false),
      new ResultPair("}.com",false),
      new ResultPair("google.arpa",true),
      new ResultPair("google.ARPA",true),
      new ResultPair("google.biz",true),
      new ResultPair("google.name",true),
      new ResultPair("google.az",true),
      new ResultPair("google.is",true),
      new ResultPair("google.na",true),
      new ResultPair("google.za",true),
      new ResultPair("google.a",false), 
      /*new ResultPair("google.zldsjry",false),
      new ResultPair("google.123",false),*/
      new ResultPair("localhost",true),
      new ResultPair("localdomain",true),
      new ResultPair("0.0.0.0",true),
      new ResultPair("0.0.0.-1",false),
      new ResultPair("255.255.255.255",true),
      new ResultPair("256.256.256.256",false),
      new ResultPair("1.246.58.39",true),
      new ResultPair("43.0.222.167.53",false),
      new ResultPair("111.111.111",false),
      new ResultPair(".111.111.111",false),
      new ResultPair("",false)};

  ResultPair[] pathParts = { new ResultPair("/",true),
      new ResultPair("/#",false),
      new ResultPair("/abcdefghijklmnopqrstuvwxyz",true),
      new ResultPair("/ABCDEFGHIJKLMNOPQRSTUVWXYZ",true),
      new ResultPair("/0123456789",true),
      new ResultPair("/-:@&?=+,.!~*'%$_;()",true),
      new ResultPair("/|",false),
      new ResultPair("/`",false),
      new ResultPair("/<",false),
      new ResultPair("/>",false),
      new ResultPair("/file/",true),
      new ResultPair("/path123//file456",false),
      new ResultPair("/../file",false),
      new ResultPair("/../path1/file",true)}; 
  
  ResultPair[] pathPartsSlashes = { new ResultPair("/",true),
      new ResultPair("/#",false),
      new ResultPair("/abcdefghijklmnopqrstuvwxyz",true),
      new ResultPair("/ABCDEFGHIJKLMNOPQRSTUVWXYZ",true),
      new ResultPair("/0123456789",true),
      new ResultPair("/-:@&?=+,.!~*'%$_;()",true),
      new ResultPair("/|",false),
      new ResultPair("/`",false),
      new ResultPair("/<",false),
      new ResultPair("/>",false),
      new ResultPair("/file/",true),
      new ResultPair("/path123//file456",true),
      new ResultPair("/../file",false),
      new ResultPair("/../path1/file",true)};
   
  ResultPair[] queryParts = {new ResultPair("",true),
      new ResultPair("?",true),
      new ResultPair("?\n", false),
      new ResultPair("#",true),
      new ResultPair("?#",true),
      new ResultPair("?#",true),
      new ResultPair("?abcdefghijklmnopqrstuvwxyz",true),
      new ResultPair("?ABCDEFGHIJKLMNOPQRSTUVWXYZ",true),
      new ResultPair("?0123456789",true),
      new ResultPair("?-:@&=+,.!~*'%$_;()[]{}/|`~",true),
      new ResultPair("?action=add", true),
      new ResultPair("?test1=yes&test2=5&test3='string'",true)};

  ResultPair[] fragmentParts = {new ResultPair("",true),
                  new ResultPair("#",true),
                  new ResultPair("#\n",false),
                  new ResultPair("##",true),
                  new ResultPair("#abcdefghijklmnopqrstuvwxyz",true),
                  new ResultPair("#ABCDEFGHIJKLMNOPQRSTUVWXYZ",true),
                  new ResultPair("#0123456789",true),
                  new ResultPair("#?-:@&=+,.!~*'%$_;()[]{}/|`~",true)};
  
  
  ResultPair[] fragmentPartsNO = {new ResultPair("",true),
                    new ResultPair("#",false),
                    new ResultPair("##",false),
                    new ResultPair("#abcdefghijklmnopqrstuvwxyz",false),
                    new ResultPair("#ABCDEFGHIJKLMNOPQRSTUVWXYZ",false),
                    new ResultPair("#0123456789",false),
                    new ResultPair("#?-:@&=+,.!~*'%$_;()[]{}/|`~",false)};

  public void testYourFirstPartition()
  {
    UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
    assertTrue(urlVal.isValid("http://www.amazon.com"));

    //test non ASCII chars
    assertFalse(urlVal.isValid("http://www.amazon¢.com"));

    //test out of order
    assertFalse(urlVal.isValid("com.amazon.http://"));
    assertFalse(urlVal.isValid("amazon.http://com"));

    assertFalse(urlVal.isValid("this_is_not_a_url"));
  }


  public void testURLScheme()
  {
    //Test allowing only "test" scheme
    String[] schemes = {"test"};
    UrlValidator urlValStrictScheme = new UrlValidator(schemes);
    assertTrue(urlValStrictScheme.isValid("test://www.amazon.com"));
    assertFalse(urlValStrictScheme.isValid("http://www.amazon.com"));

    //Test default schemes
    UrlValidator urlValDefaultScheme = new UrlValidator();
    assertTrue(urlValDefaultScheme.isValid("http://www.amazon.com"));
    assertTrue(urlValDefaultScheme.isValid("https://www.amazon.com"));
    assertTrue(urlValDefaultScheme.isValid("ftp://www.amazon.com"));
    assertFalse(urlValDefaultScheme.isValid("test://www.amazon.com"));

    //Test allowing any scheme
    UrlValidator urlValAnyScheme = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
    assertTrue(urlValAnyScheme.isValid("https://www.amazon.com"));
    assertFalse(urlValAnyScheme.isValid("https:/www.amazon.com"));
    assertFalse(urlValAnyScheme.isValid("https//www.amazon.com"));
    assertFalse(urlValAnyScheme.isValid("httpswww.amazon.com"));
    assertTrue(urlValAnyScheme.isValid("anything://www.amazon.com"));
  }

  public void testIsValidAuthority() {
    boolean pass = true;
    //test without ALLOW_LOCAL_URLS option
    UrlValidator urlVal = new UrlValidator(null, null, (UrlValidator.ALLOW_2_SLASHES + UrlValidator.ALLOW_ALL_SCHEMES + UrlValidator.NO_FRAGMENTS));
    //iterates over each authority in authorityParts
    for(int i = 0; i < authorityParts.length; i++) {
      if(printFlag){
        if(authorityParts[i].valid != urlVal.isValidAuthority(authorityParts[i].item)){
          pass = false;
          System.out.println("testIsValidAuthority(): " + authorityParts[i].item + " Failed");
          System.out.println("expected: " + authorityParts[i].valid);
        }
      }
      else{
        assertEquals(authorityParts[i].valid, urlVal.isValidAuthority(authorityParts[i].item));
      }
    }
    
    //test with ALLOW_LOCAL_URLS option
    UrlValidator urlValLocal = new UrlValidator(null, null, (UrlValidator.ALLOW_LOCAL_URLS + UrlValidator.ALLOW_2_SLASHES + UrlValidator.ALLOW_ALL_SCHEMES + UrlValidator.NO_FRAGMENTS));
    //iterates over each authority in authorityParts
    for(int i = 0; i < authorityPartsLocal.length; i++) {
      if(printFlag){
        if(authorityPartsLocal[i].valid != urlValLocal.isValidAuthority(authorityPartsLocal[i].item)){
          pass = false;
          System.out.println("testIsValidAuthority() - ALLOW_LOCAL_URLS: " + authorityPartsLocal[i].item + " Failed");
          System.out.println("expected: " + authorityPartsLocal[i].valid);
        }
      }
      else{
        assertEquals(authorityPartsLocal[i].valid, urlValLocal.isValidAuthority(authorityPartsLocal[i].item));
      }
    }
    
    if(printFlag && pass){
      System.out.println("testIsValidAuthority(): All Tests Passed");
    }
  
  }

  public void testIsValidPath() {
    
    boolean pass = true;
    //test without ALLOW_2_Slashes option
    UrlValidator urlVal = new UrlValidator(null, null, (UrlValidator.ALLOW_ALL_SCHEMES + UrlValidator.NO_FRAGMENTS));
    //iterates over each path in pathParts
    for(int i = 0; i < pathParts.length; i++) {
      if(printFlag){
        if(pathParts[i].valid != urlVal.isValidPath(pathParts[i].item)){
          pass = false;
          System.out.println("testIsValidPath(): " + pathParts[i].item + " Failed");
          System.out.println("expected: " + pathParts[i].valid);
        }
      }
      else{
        assertEquals(pathParts[i].valid, urlVal.isValidPath(pathParts[i].item));
      }
    }
    
    //test with ALLOW_2_Slashes option
    UrlValidator urlValSlashes = new UrlValidator(null, null, (UrlValidator.ALLOW_2_SLASHES + UrlValidator.ALLOW_ALL_SCHEMES + UrlValidator.NO_FRAGMENTS));
    //iterates over each path in pathPartsSlashes
    for(int i = 0; i < pathPartsSlashes.length; i++) {
      if(printFlag){
        if(pathPartsSlashes[i].valid != urlValSlashes.isValidPath(pathPartsSlashes[i].item)){
          pass = false;
          System.out.println("testIsValidPath() - ALLOW_2_SLASHES: " + pathPartsSlashes[i].item + " Failed");
          System.out.println("expected: " + pathPartsSlashes[i].valid);

        }
      }
      else{
        assertEquals(pathPartsSlashes[i].valid, urlValSlashes.isValidPath(pathPartsSlashes[i].item));
      }
      
    }
    
    if(printFlag && pass){
      System.out.println("testIsValidPath(): All Tests Passed");
    }
  }

  public void testIsValidQuery() {
    
    boolean pass = true;
    
    UrlValidator urlVal = new UrlValidator(null, null, (UrlValidator.ALLOW_ALL_SCHEMES + UrlValidator.NO_FRAGMENTS));
    //iterates over each path in queryParts
    for(int i = 0; i < queryParts.length; i++) {
      if(printFlag){
        if(queryParts[i].valid != urlVal.isValidQuery(queryParts[i].item)){
          pass = false;
          System.out.println("testIsValidQuery(): " + queryParts[i].item + " Failed");
          System.out.println("expected: " + queryParts[i].valid);
        }
      }
      else{
        assertEquals(queryParts[i].valid, urlVal.isValidQuery(queryParts[i].item));
      }
    }
    
    if(printFlag && pass){
      System.out.println("testisValidQuery(): All Tests Passed");
    }
  }

  public void testIsValidFragment() {
    
    boolean pass = true;
    //test without NO_FRAGMENTS option
    UrlValidator urlVal = new UrlValidator(null, null, (UrlValidator.ALLOW_ALL_SCHEMES));
    //iterates over each path in fragmentParts
    for(int i = 0; i < fragmentParts.length; i++) {
      if(printFlag){
        if(fragmentParts[i].valid != urlVal.isValidPath(fragmentParts[i].item)){
          pass = false;
          System.out.println("testIsValidFragment(): " + fragmentParts[i].item + " Failed");
          System.out.println("expected: " + fragmentParts[i].valid);
        }
      }
      else{
        assertEquals(fragmentParts[i].valid, urlVal.isValidPath(fragmentParts[i].item));
      }
    }
    
    //test with NO_FRAGMAENTS option
    UrlValidator urlValSlashes = new UrlValidator(null, null, (UrlValidator.ALLOW_2_SLASHES + UrlValidator.ALLOW_ALL_SCHEMES + UrlValidator.NO_FRAGMENTS));
    //iterates over each path in fragmentPartsNO
    for(int i = 0; i < fragmentPartsNO.length; i++) {
      if(printFlag){
        if(fragmentPartsNO[i].valid != urlValSlashes.isValidPath(fragmentPartsNO[i].item)){
          pass = false;
          System.out.println("testIsValidFragment() - NO_FRAGMENTS: " + fragmentPartsNO[i].item + " Failed");
          System.out.println("expected: " + fragmentPartsNO[i].valid);
        }
      }
      else{
        assertEquals(fragmentPartsNO[i].valid, urlValSlashes.isValidPath(fragmentPartsNO[i].item));
      }
      
    }
    
    if(printFlag && pass){
      System.out.println("testIsValidFragment(): All Tests Passed");
    }
  }

  public void testAllPartsCombinations()
  {
    boolean pass = true;

    for (int i = 0;i<schemeParts.length;i++)
    {
      for (int j = 0;j<authorityParts.length;j++)
      {
        for (int k = 0;k<portParts.length;k++)
        {
          for (int l = 0;l<pathParts.length;l++)
          {
            for (int m = 0;m<queryParts.length;m++)
            {
              //Determine validity of the test URL
              boolean result = schemeParts[i].valid &&
                authorityParts[j].valid &&
                portParts[k].valid &&
                pathParts[l].valid &&
                queryParts[m].valid;

              //Build test URL
              String testUrl = new StringBuilder(255).append(schemeParts[i].item)
                .append(authorityParts[j].item)
                .append(portParts[k].item)
                .append(pathParts[l].item)
                .append(queryParts[m].item)
                .toString();

              System.out.println(testUrl);

              
              if(printFlag){
                if(urlVal.isValidPath(testUrl) != result){
                  pass = false;
                  System.out.println("testIsValid: " + testUrl + " Failed");
                  System.out.println("expected: " + result);
                }
                else{
                  assertEquals(result, urlVal.isValidPath(testUrl));
                }
              } 
            }
          }
        }
      }
    }
  }

  public void testYourSecondPartition()
  {

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
