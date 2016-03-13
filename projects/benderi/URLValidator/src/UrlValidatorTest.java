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
    //@param string array of urls that ARE valid
    //@param part (which part you want to make invalid: SEE switch Statement)
    //Returns a List<String> of now BAD urls

    //TODO needs fixin...still not making good-bad URLS'-its set to print during test run
    public List<String> makeInvalidPart(String[] urls, int part){

        //defines
        URL aURL = null;
        String auth, path, query, protocol, host, portStr, fullUrl = null;
        int port, rand;
        List<String> badUrls = new ArrayList<String>();
        RandomString rnd;

        try {
        	
            for (String url: urls) {

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
                switch (part){
                    case 1: //bad protocol
                    	rand = ThreadLocalRandom.current().nextInt(1,5);
                    	rnd = new RandomString(rand);
                    	protocol = rnd.nextString();
                        break;
                        
                    case 2: //bad host
                    	rand = ThreadLocalRandom.current().nextInt(1,4);
                    	rnd = new RandomString(rand);
                    	host = rnd.nextString();
                    	rand = ThreadLocalRandom.current().nextInt(1,12);
                    	rnd = new RandomString(rand);
                    	host += "." + rnd.nextString();
                    	rand = ThreadLocalRandom.current().nextInt(1,4);
                    	rnd = new RandomString(rand);
                    	host += "." + rnd.nextString();
                        break;
                    	
                    case 3: //bad port
                    	rand = ThreadLocalRandom.current().nextInt(1,5);
                    	rnd = new RandomString(rand);
                    	portStr = ":" + rnd.nextString();
                        break;
                        
                    case 4: //bad path
                    	rand = ThreadLocalRandom.current().nextInt(1,20);
                    	rnd = new RandomString(rand);
                    	path = "/" + rnd.nextString();
                        break;
                        
                    case 5: //bad query
                    	rand = ThreadLocalRandom.current().nextInt(1,20);
                    	rnd = new RandomString(rand);
                    	query = "?" + rnd.nextString();
                        break;
                }

                if (port == -1 && part != 3) portStr = "";
                if (query == null && part != 5) query = "";
                
                fullUrl = protocol + "://" + host + portStr + path + query;
                badUrls.add(fullUrl);
            	//System.out.println(fullUrl);
            }

        }catch(IOException ex){
            System.out.println (ex.toString());
            System.out.println("Could not find file " );
        }

        return badUrls;
    }
   
}


public class UrlValidatorTest extends TestCase {
	
	//enum for url parts, used for easier choice of argument for makeInvalidPart()
	public enum urlPart {
		protocol(1), host(2), port(3), path(4), query(5);
		private final int value;
		private urlPart(int value) {
			this.value = value;
		}
		public int get() {
			return value;
		}
	}
	

	public UrlValidatorTest(String testName) {
		super(testName);
	}

    //Tests Known Valid URLS, using a text file
   public void testKnownValid()
   {
       helperFunctions h = new helperFunctions();
       int failRate=0, passRate=0, maxTests=0;
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
       String fileName = "src" + File.separator + "UrlsToVerify.txt";
       
       System.out.println("TESTING KNOWN GOOD URLS ------------------------------- ");
       //read in Valid urls   
       try {
           String[] urls = h.readLines(fileName);
           maxTests = 1000;	//change to urls.length for full testing

           //pass the lines to isValid parts
           for (String url: urls) {

               if (urlVal.isValid(url)) {
            	   passRate++;              
            	   System.out.println("Passed UrlValidator: " + url);
               } else {
            	   failRate++;
            	   System.out.println("--Failed UrlValidator: " + url);
               }
               
               //limit number of urls for dev testing
               if (passRate + failRate >= maxTests) break; 
           }
           
           System.out.println("Passed " + passRate + "/" + maxTests + " test(s).");
           System.out.println("Failed " + failRate + "/" + maxTests + " test(s).");

           assertEquals(0, failRate);  // Makes sure

       } catch(IOException ex){
           System.out.println (ex.toString());
           System.out.println("Could not find file " + fileName);
       }
       
       assertEquals(0, failRate);
   }


    //Takes input from known good URLs, randomly changes one part of the URL, and tests
    public void testPRINTBAD()
    {
    	helperFunctions h = new helperFunctions();
        int failRate=0, passRate=0, maxTests=0;
        List<String> failedUrls = new ArrayList<String>();
 	    UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        String fileName = "src" + File.separator + "UrlsToVerify.txt";
        
        System.out.println("TESTING LIKELY BAD URLS ------------------------------- ");
        //read in Valid urls   
        try {
            String[] urls = h.readLines(fileName);
            maxTests = 1000;	//change to urls.length for full testing
            //change urlPart to either - protocol/host/port/path/query
            failedUrls = h.makeInvalidPart(urls, urlPart.protocol.get());
            
            //pass altered (bad) urls to isValid for testing
            for (String url: failedUrls) {

                if (urlVal.isValid(url)) {
             	   passRate++;              
             	   System.out.println("Passed UrlValidator: " + url);
                } else {
             	   failRate++;
             	   System.out.println("--Failed UrlValidator: " + url);
                }
                
                //limit number of urls for dev testing
                if (passRate + failRate >= maxTests) break; 
            }
            
            System.out.println("Passed " + passRate + "/" + maxTests + " test(s).");
            System.out.println("Failed " + failRate + "/" + maxTests + " test(s).");

            assertEquals(maxTests, failRate);  // Makes sure

        }catch(IOException ex){
            System.out.println (ex.toString());
            System.out.println("Could not find file " + fileName);
        }
    }

}
