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
import java.io.File;
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


public class UrlValidatorTest extends TestCase {


    //enum for url parts, used for easier choice of argument for makeInvalidPart()
//    public enum urlPart {
//        protocol(1), host(2), port(3), path(4), query(5), authority(5);
//        private final int value;
//        private urlPart(int value) {
//            this.value = value;
//        }
//        public int get() {
//            return value;
//        }
//    }
    //Simplified because i was unsure  of the former functions utility
    public enum UrlPart {
        protocol, host, port, path, query, authority;
    }


    //Made these Global to the class so that the reporter function works, and enum too
    UrlPart partName;
    UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);


    //Makes part of the URL invalid
    //@param string array of urls that ARE valid
    //@param part (which part you want to make invalid: SEE switch Statement)
    //Returns a List<String> of now BAD urls
    //TODO needs fixin...still not making good-bad URLS'-its set to print during test run
    public List<String> makeInvalidPart(List<String> urls, UrlPart partName) {

        //defines
        URL aURL = null;
        String auth, path, query, protocol, host, portStr, fullUrl = null;
        int port, rand;
        List<String> badUrls = new ArrayList<String>();
        RandomString rnd;

        try {

            for (String url : urls) {

                //Parse the URL
                aURL = new URL(url);

                protocol = aURL.getProtocol();
                auth = aURL.getAuthority();
                host = aURL.getHost();
                port = aURL.getPort();
                path = aURL.getPath();
                query = aURL.getQuery();
                portStr = null;

                /*
                System.out.println("Protocol: " + protocol);
                System.out.println("Authority: " + auth);
                System.out.println("Host: " + host);
                System.out.println("Port: " + port);
                System.out.println("Path: " + path);
                System.out.println("Query: " + query);
                System.out.println();
                */

                //Select which part to change
                switch (partName) {
                    case protocol: //bad protocol
                        rand = ThreadLocalRandom.current().nextInt(1, 5);
                        rnd = new RandomString(rand);
                        protocol = rnd.nextString();
                        break;

                    case host: //bad host
                        rand = ThreadLocalRandom.current().nextInt(1, 4);
                        rnd = new RandomString(rand);
                        host = rnd.nextString();
                        rand = ThreadLocalRandom.current().nextInt(1, 12);
                        rnd = new RandomString(rand);
                        host += "." + rnd.nextString();
                        rand = ThreadLocalRandom.current().nextInt(1, 4);
                        rnd = new RandomString(rand);
                        host += "." + rnd.nextString();
                        break;

                    case port: //bad port
                        rand = ThreadLocalRandom.current().nextInt(1, 5);
                        rnd = new RandomString(rand);
                        portStr = ":" + rnd.nextString();
                        break;

                    case path: //bad path
                        rand = ThreadLocalRandom.current().nextInt(1, 20);
                        rnd = new RandomString(rand);
                        path = "/" + rnd.nextString();
                        break;

                    case query: //bad query
                        rand = ThreadLocalRandom.current().nextInt(1, 20);
                        rnd = new RandomString(rand);
                        query = "?" + rnd.nextString();
                        break;
                    case authority: //bad query
                        //some length 3 some length 2 authorities
                        //todo needs some tweaking to make more halfway plausiable authorities i.e. not all ASCII
                        int half = ThreadLocalRandom.current().nextInt(0, 2);//http://stackoverflow.com/questions/363681/generating-random-integers-in-a-specific-ran

                        if (half == 0) {
                            rnd = new RandomString(3);

                        } else {
                            rnd = new RandomString(2);
                        }

                        auth = "." + rnd.nextString();
                        //badUrls.add(protocol +"://" + host + auth);

                        break;
                }
                //todo figure out if my version of enum can be used like this...ehhh
                if (port == -1 && partName != partName.port) portStr = "";
                if (query == null && partName != partName.query) query = "";
                if (auth != null && partName != partName.authority) auth = "";

                fullUrl = protocol + "://" + host + auth + portStr + path + query;
                badUrls.add(fullUrl);
                //System.out.println(fullUrl);
            }

        } catch (IOException ex) {
            System.out.println(ex.toString());
            System.out.println("Could not find file ");
        }

        return badUrls;
    }

    //Makes a VALID URL
    //@param number of URLS to make
    //Returns a List<String> of GOOD urls
    public List<String> makeValidURL(int n){

        List<String> urls =new ArrayList<String>();
        String builtURL;

        for(int i =0; i < n ; i ++){

            HelpFunctions h = new HelpFunctions();

            builtURL = h.getRandomProtocol()+"://";
            //TODO MAKE THIS PART SWITCH TO GET either an IP or a valid HOST name
            builtURL += h.makeIP();
            //TODO Function to make a valid Host
            builtURL += "/"; // this depending on if there are parts added after the host
            //TODO make this change  sometimes path sometimes query sometimes both
            builtURL += h.makePath();
            builtURL += h.makeQuery();

            urls.add(builtURL);
        }

        return urls;
    }

    public int reporter(List<String> Urls, int passRate, int failRate, int maxTests){
        //pass altered (bad) urls to isValid for testing
        for (String url: Urls) {

            //USE JAVAS OWN URL breakapart function
            //To tell us which part is bad
            URL jurl;
            try {
                jurl = new URL(url);

                if (urlVal.isValid(url)) {
                    passRate++;
                    System.out.println("Passed UrlValidator: " + url);
                } else {
                    failRate++;
                    System.out.println("--Failed UrlValidator: " + url);
                    System.out.print("--Java Says: ");
                    if (urlVal.isValidScheme(jurl.getProtocol())) {
                        System.out.print("Protocol: OK, ");
                    } else {
                        System.out.print("Protocol: FAIL, ");
                    }
                    if (urlVal.isValidAuthority(jurl.getHost())) {
                        System.out.print("Host: OK, ");
                    } else {
                        System.out.print("Host: FAIL, ");
                    }
                    if (urlVal.isValidAuthority(jurl.getAuthority())) {
                        System.out.print("Authority: OK, ");
                    } else {
                        System.out.print("Authority: FAIL, ");
                    }
                    if (urlVal.isValidQuery(jurl.getQuery())) {
                        System.out.print("Query: OK, ");
                    } else {
                        System.out.print("Query: FAIL, "+ jurl.getQuery());
                    }
                    if (urlVal.isValidPath(jurl.getPath())) {
                        System.out.print("Path: OK\n");
                    } else {
                        System.out.print("Path: FAIL\n");
                    }
                }
            }catch (IOException e) {
                System.out.println("FAILED the JAVA URL VALIDATION");
            }

            //limit number of urls for dev testing
            if (passRate + failRate >= maxTests) break;
        }
        System.out.println("Passed " + passRate + "/" + maxTests + " test(s).");
        System.out.println("Failed " + failRate + "/" + maxTests + " test(s).");
        return failRate;
    }

    public UrlValidatorTest(String testName) {
        super(testName);
    }

    //Tests Known Valid URLS, using a text file
    public void testKnownValid()
    {
       HelpFunctions h = new HelpFunctions();
        int failRate=0, passRate=0, maxTests=0;
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        String fileName = "src" + File.separator + "UrlsToVerify.txt";

        System.out.println("--------------------------- TESTING KNOWN GOOD URLS ------------------------------- ");
        //read in Valid urls
        try {
            List<String> urls = h.readLines(fileName);
            maxTests = 1000;	//change to urls.length for full testing

            //pass the lines to isValid parts
            int fails = reporter(urls, passRate, failRate, maxTests );

            assertEquals(0, fails);  // Makes sure

        } catch(IOException ex){
            System.out.println (ex.toString());
            System.out.println("Could not find file " + fileName);
        }

    }

    public void testKnownRandomValid()
    {
       HelpFunctions h = new HelpFunctions();
        int failRate=0, passRate=0, maxTests=0;
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);


        System.out.println("--------------------------- TESTING GOOD RANDOM URLS ------------------------------- ");
        //read in Valid urls

        maxTests = 1000;	//change to urls.length for full testing
        List<String> urls = makeValidURL(maxTests);

        //pass the lines to isValid parts
        int fails = reporter(urls, passRate, failRate, maxTests );

        assertEquals(0, fails);  // Makes sure

    }




    //Takes input from known good URLs, changes one part of the URL, and tests
    public void testKnownBadAuthority() {
       HelpFunctions h = new HelpFunctions();
        int failRate = 0, passRate = 0, maxTests = 0;
        List<String> failedUrls = new ArrayList<String>();
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        String fileName = "src" + File.separator + "UrlsToVerify.txt";

        System.out.println("---------------------------TESTING LIKELY BAD URLS ------------------------------- ");
        //read in Valid urls
        try {
            List<String> urls = h.readLines(fileName);
            maxTests = 1000;    //change to urls.length for full testing
            //change urlPart to either - protocol/host/port/path/query urlPart.protocol.get()
            failedUrls = makeInvalidPart(urls, partName.authority);

            //pass altered (bad) urls to isValid for testing
            //pass the lines to isValid parts
            //TODO add section here
            System.out.println("Section we are testing..." + " -------------------------------");
            reporter(failedUrls, passRate, failRate, maxTests);

            assertEquals(maxTests, failRate);  // Makes sure

        } catch (IOException ex) {
            System.out.println(ex.toString());
            System.out.println("Could not find file " + fileName);
        }

    }


    public void testKnownBadHost()
    {
        HelpFunctions h = new HelpFunctions();
        int failRate=0, passRate=0, maxTests=0;
        List<String> failedUrls = new ArrayList<String>();
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        String fileName = "src" + File.separator + "UrlsToVerify.txt";

        System.out.println("---------------------------TESTING LIKELY BAD URLS ------------------------------- ");
        //read in Valid urls
        try {
            List<String> urls = h.readLines(fileName);
            maxTests = 1000;	//change to urls.length for full testing
            //change urlPart to either - protocol/host/port/path/query urlPart.protocol.get()
            failedUrls = makeInvalidPart(urls, partName.host );

            //pass altered (bad) urls to isValid for testing
            //pass the lines to isValid parts
            //TODO add section here
            System.out.println( "Section we are testing..." + " -------------------------------");
            reporter(failedUrls, passRate, failRate, maxTests );

            assertEquals(maxTests, failRate);  // Makes sure

        }catch(IOException ex){
            System.out.println (ex.toString());
            System.out.println("Could not find file " + fileName);
        }
    }
    public void testThis(){
       HelpFunctions h = new HelpFunctions();
//        System.out.println(h.makeIP(10));
//        System.out.println(h.makePath(10));
//        System.out.println(h.makeQuery(10));
        //System.out.println(makeValidURL(10));




    }
}
