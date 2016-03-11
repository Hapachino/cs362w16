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

  ResultPair[] schemeParts = {new ResultPair("http://", true)};

  ResultPair[] authorityParts = {new ResultPair("www.google.com", true)};

  ResultPair[] portParts = {new ResultPair(":80", true)};

  ResultPair[] pathParts = {new ResultPair("/test", true)};

  ResultPair[] queryParts = {new ResultPair("?test=true", true)};



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

  public void testAllPartsCombinations()
  {
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

              if (result) {
                //assertTrue();
              } else {
                //assertFalse();
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
