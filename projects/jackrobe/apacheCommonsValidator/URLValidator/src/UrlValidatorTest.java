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
import java.net.*;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;


/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */
class helperFunctions {

    //Helper functions http://stackoverflow.com/questions/285712/java-reading-a-file-into-an-array
    public String[] readLines(String filename) throws IOException {

        FileReader fileReader = new FileReader(filename);
        BufferedReader bufferedReader = new BufferedReader(fileReader);
        List<String> lines = new ArrayList<String>();
        String line = null;

        while ((line = bufferedReader.readLine()) != null) {
            lines.add(line);
        }

        bufferedReader.close();
        return lines.toArray(new String[lines.size()]);
    }


}


public class UrlValidatorTest extends TestCase {

   private boolean printStatus = false;
   private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.

   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testKnownValid()
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

       //read in Valid urls
       String fileName = "src\\UrlsToVerify.txt";
       helperFunctions h = new helperFunctions();
       int failRate =0;
       List<String> failedUrls = new ArrayList<String>();
       boolean testWhole, testAuth, testPath, testPort, testQu, testScheme ;
       try {
           String[] urls = h.readLines(fileName);

           //pass them to isValid
           for (String url: urls) {
               URL aURL = new URL(url);

               testAuth = urlVal.isValidAuthority(aURL.getAuthority());
               testPath = urlVal.isValidPath(aURL.getPath());
               testQu = urlVal.isValidQuery(aURL.getQuery());
               testScheme = urlVal.isValidScheme(aURL.getProtocol());
               testWhole = urlVal.isValid(url);

               //todo I know this next section needs to be refactored but I have to run and want the thought/idea to be there
               //when I come back Also it's not giving useful information at all, I thought I could add more than one assert to thetest
               // but I guess I'm mistaken

               if (!testAuth) {

                   //assertEquals(true,testAuth);
                   System.out.println("Authority failed ");
               }

               if (!testPath) {

                   //assertEquals(true,testPath);
                   System.out.println("Test Path failed");
               }

               if (!testQu) {

                   System.out.println("Query failed");
               }
               if (!testScheme) {


                   System.out.println("Scheme failed");
               }

               if (!testWhole) {

                   failRate++;
                   failedUrls.add(url);
                   System.out.println("URL: " + url);
               }

               if (failRate > 0) {

                   System.out.println("Failed Testing " + failRate + " test(s) of " + urls.length);
                   System.out.println("The following Urls Failed " + failedUrls);

               }
           }

                   assertEquals(0, failRate);
       }catch(IOException ex){
           System.out.println (ex.toString());
           System.out.println("Could not find file " + fileName);
       }





       //System.out.println(urlVal.isValid("http://www.amazon.com"));


       //print out what didn't pass



   }

    public void knownInvalidTest()
    {
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

        //read in Valid urls

        //pass them to isValid
        System.out.println(urlVal.isValid("http://www.amazon.com"));

        ////print out what did pass

    }
   
   
   public void testAuthority()
   {
	   
   }
   
   public void testPort(){
	   
   }
   
   
   public void testPath()
   {

   }

    public void testQuery()
    {

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
