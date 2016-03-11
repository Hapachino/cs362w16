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
//TODO make the system out put to a file for use, not just screen output

import junit.framework.TestCase;
import java.net.*;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.concurrent.ThreadLocalRandom;


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

    //Makes part of the URL invalid
    //@ param string array of urls that ARE valid
    //@param part (which part you want to make invalid: SEE switch Statement)
    //Returns  a List<String> of now BAD urls

    //TODO needs fixin...still not making good-bad URLS'-its set to print during test run
    public List<String> makeInvalidPart(String[] urls, int part){

        //defines
        URL aURL = null;
        String auth, path, query, protocol, host;
        List<String> badUrls = new ArrayList<String>();
        RandomString rnd, rnd1, rnd2, rnd3;

        try {

            for (String url: urls) {

                //Parse the URL
                aURL = new URL(url);

                auth = aURL.getAuthority();
                path = aURL.getPath();
                query = aURL.getQuery();
                host = aURL.getHost();
                protocol = aURL.getProtocol();


                //Select which part to change
                //Todo I'm missing one section of the URL the main part HOST, and... ports?
                switch (part){
                    case 1: //BAD AUTHORITY

                        //some length 3 some length 2 authorities
                        //todo needs some tweaking to make more halfway plausiable authorities i.e. not all ASCII
                        int half = ThreadLocalRandom.current().nextInt(0, 2);//http://stackoverflow.com/questions/363681/generating-random-integers-in-a-specific-ran

                        if (half == 0 ) {
                             rnd = new RandomString(3);

                        }else{
                             rnd = new RandomString(2);
                        }

                        auth = "." + rnd.nextString();
                        badUrls.add(protocol +"://" + host + auth);

                        break;

                    case 2: //BAD PATH

                        rnd1 = new RandomString(ThreadLocalRandom.current().nextInt(1, 50));

                        path = "/" + rnd1.nextString() ;
                        badUrls.add(protocol +"://" + host + path);
                        break;

                    case 3: //BAD query

                        //TODO finish query
                        query = aURL.getQuery();

                        break;

                    case 4: //BAD Protocol

                        rnd2 =  new RandomString(ThreadLocalRandom.current().nextInt(2, 5));
                        protocol = rnd2.nextString() + "://";

                        badUrls.add(protocol + host);
                    case 5: //BAD ...

                        break;
                }



            }

        }catch(IOException ex){
            System.out.println (ex.toString());
            System.out.println("Could not find file " );
        }

        return badUrls;
    }


    // Runs the test on the section specified by int
    //Returns the failrate for that test
    //prints out the fails
    public int sectionTest(int test){

        //define some stuff
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        helperFunctions h = new helperFunctions();
        List<String> failedUrls = new ArrayList<String>();
        List<String> badUrls = new ArrayList<String>();

        String fileName = "src\\UrlsToVerify.txt";
        String[] urls = null;

        int failRate =0;
        boolean testWhole, testAuth, testPath, testPort, testQu, testScheme ;

        URL aURL = null;


        //read in Valid urls
        try{
            urls = h.readLines(fileName);
        }catch(IOException ex){
            System.out.println (ex.toString());
            System.out.println("Could not find file " + fileName);
        };

        badUrls = h.makeInvalidPart(urls, test);

        //Mostly the same as the KnownValid except looking for passing b/c it should be failing in these cases
        //todo possibly refactor if we make more
        //pass them to isValid

        for (String url: badUrls) {
            try {
                aURL = new URL(url);

            }catch(IOException ex) {

                //System.out.println (ex.toString());
                //System.out.println("URL didn't work " + fileName);
            }

            testWhole = urlVal.isValid(url);

            if (testWhole) {

                failRate++;
                failedUrls.add(url);
                System.out.println("URL: " + url);
            }
        }

        if (failRate > 0) {

            System.out.println("Failed Testing " + failRate + " test(s) of " + urls.length);
            System.out.println("The following Urls Passed But MAYBE should not have " + failedUrls);

        }else{
            System.out.println("Passed"+ urls.length+ " test(s)");
        }

        return failRate;

    }
}


public class UrlValidatorTest extends TestCase {

   private boolean printStatus = false;
   private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.

   public UrlValidatorTest(String testName) {
      super(testName);
   }


    //Tests Known Valid URLS, using a text file
    public void testKnownValid()
   {

       System.out.println("TESTING KNOWN GOOD URLS ------------------------------- ");
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

       //read in Valid urls
       String fileName = "src\\UrlsToVerify.txt";
       helperFunctions h = new helperFunctions();
       int failRate =0;
       List<String> failedUrls = new ArrayList<String>();
       boolean testWhole, testAuth, testPath, testHost, testQuery, testProtocol ;

       try {

           String[] urls = h.readLines(fileName);

           //pass the lines to isValid parts
           for (String url: urls) {

               URL aURL = new URL(url);
               //TODO make it test the host too!
               //todo make sure I'm hitting all the parts

               testAuth = urlVal.isValidAuthority(aURL.getAuthority());
               testPath = urlVal.isValidPath(aURL.getPath());
               testQuery = urlVal.isValidQuery(aURL.getQuery());
               testProtocol = urlVal.isValidScheme(aURL.getProtocol());
               testWhole = urlVal.isValid(url);

               if (!testAuth) {

                   //assertEquals(true,testAuth);
                   System.out.println(" Authority failed");
               }

               else if (!testPath) {

                   //assertEquals(true,testPath);
                   System.out.println(" Test Path failed");
               }

               else if (!testQuery) {

                   System.out.println(" Query failed");
               }

               else if (!testProtocol) {


                   System.out.println(" Scheme failed");
               }


               if (!testWhole) {

                   failRate++;
                   failedUrls.add(url);
                   System.out.print(" URL: " + url);
               }

           }

            if(failRate > 0) {
                System.out.println("Failed Testing " + failRate + " test(s) of " + urls.length);
                System.out.println("The following Urls Failed " + failedUrls);
            }else{
                System.out.println("Passed"+ urls.length+ " test(s)");
            }

           assertEquals(0, failRate);  // Makes sure

       }catch(IOException ex){
           System.out.println (ex.toString());
           System.out.println("Could not find file " + fileName);
       }


   }

   public void testPort(){
       //todo add code similar to others
       //todo first verify that the testSection is dealing with the port
   }

   public void testPath()
   {
       System.out.println("TESTING PATHS ------------------------------- ");
       helperFunctions h = new helperFunctions();
       int fails;
       fails = h.sectionTest(2);
       assertEquals(0,fails);
   }
    public void testHost()
    {
        //todo add code similar to others
        //todo first verify that the testSection is doing this correctly
    }
    public void testQuery()
    {
        //todo add code similar others
    }
    public void testProtocol()
    {
        System.out.println("TESTING PROTOCOL ------------------------------- ");
        helperFunctions h = new helperFunctions();
        int fails;
        fails = h.sectionTest(4);
        assertEquals(0,fails);
    }
    public void testBadAuthority() {

        System.out.println("TESTING AUTHORITY ------------------------------- ");
        helperFunctions h = new helperFunctions();
        int fails;
        fails = h.sectionTest(1);
        assertEquals(0,fails);

    }

    //This is a not a test so much as usfule for checking the output of the
    //function that generates bad URL's
    public void testPRINTBAD()
    {
        //define some stuff
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        helperFunctions h = new helperFunctions();
        List<String> failedUrls = new ArrayList<String>();
        List<String> badAutho = new ArrayList<String>();
        List<String> badPath = new ArrayList<String>();
        List<String> badProto = new ArrayList<String>();


        String fileName = "src\\UrlsToVerify.txt";
        String[] urls = null;

        boolean testWhole, testAuth, testPath, testPort, testQu, testScheme ;

        URL aURL = null;

        //read in Valid urls
        try{
            urls = h.readLines(fileName);

        }catch(IOException ex){
            System.out.println (ex.toString());
            System.out.println("Could not find file " + fileName);
        };


        badAutho = h.makeInvalidPart(urls, 1);
        badPath = h.makeInvalidPart(urls, 2);
        badProto = h.makeInvalidPart(urls, 4);
        System.out.println("BAD AUTHORITY URLS: " + badAutho);
        System.out.println("BAD Path URLS: " + badPath);
        System.out.println("BAD Proto URLS: " + badProto);


    }


}
