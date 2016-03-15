import junit.framework.TestCase;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;


public class randomized extends TestCase{
	static public void testURLs(){
		int totalUrls = 0;
		int goodUrls = 0;
		int badUrls = 0;
	    UrlValidator urlVal2 = new UrlValidator(null, null, UrlValidator.NO_FRAGMENTS);
	    System.out.println("\n==================================== \n");
	    System.out.println("Testing good URLs \n");
	    System.out.println("==================================== \n");
	    //5000 URLs generated and scraped from randomwebsite.com, stored in validURLs.txt
	    BufferedReader in = null;
		try {
			in = new BufferedReader(new FileReader("urls2.txt"));
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
        String str;

        List<String> list = new ArrayList<String>();
        try {
			while((str = in.readLine()) != null){
			    list.add(str);
			    //System.out.println(str);
			}
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

        @SuppressWarnings("unused")
		String[] stringArr = list.toArray(new String[0]);
        totalUrls = stringArr.length;
        for(int i = 0;i< stringArr.length;i++){
        	
        	boolean validFlag = urlVal2.isValid(stringArr[i]);
        	if(validFlag){
        		//System.out.format("%s ... valid\n",stringArr[i]);
        		goodUrls++;
        	}
        	else{
        		System.out.format("%s ... invalid\n",stringArr[i]);
        		badUrls++;
        	}
        }
        System.out.format("%d of %d total are valid\n", goodUrls,totalUrls);
        //next we add a forbidden character randomly to our random URLs and repeat the process
        System.out.println("\n==================================== \n");
	    System.out.println("Inserting bad URLs: invalid character \n");
	    System.out.println("==================================== \n");
        
        Random randomGenerator = new Random();
        for (int idx = 0; idx <= 20; ++idx){
            int randomInt = randomGenerator.nextInt(800);
            String randomUrl = stringArr[randomInt];
            //System.out.println(randomUrl);
            int strLen = randomUrl.length();
            char[] charUrl = randomUrl.toCharArray();
            int smallRandom = randomGenerator.nextInt(strLen);
            charUrl[smallRandom] = '>';
            randomUrl = String.valueOf(charUrl);
            System.out.println(randomUrl);
            stringArr[randomInt] = randomUrl;
            
          }
      //next we add double slashes randomly to our random URLs and repeat the process
        System.out.println("\n==================================== \n");
	    System.out.println("Inserting bad URLs: double slash \n");
	    System.out.println("==================================== \n");
        
        for (int idx = 0; idx <= 20; ++idx){
            int randomInt = randomGenerator.nextInt(200);
            String randomUrl = stringArr[randomInt];
            //System.out.println(randomUrl);
            int strLen = randomUrl.length();
            char[] charUrl = randomUrl.toCharArray();
            int smallRandom = randomGenerator.nextInt(strLen);
            charUrl[smallRandom] = '/';
            if (smallRandom < strLen-1){
            	charUrl[smallRandom] = '/';
            }
            randomUrl = String.valueOf(charUrl);
            System.out.println(randomUrl);
            stringArr[randomInt] = randomUrl;
            
          }
        //next we nuke top level domains from another 20
        System.out.println("\n==================================== \n");
	    System.out.println("Inserting bad URLs: removing random TLDs\n");
	    System.out.println("==================================== \n");
        
        for (int idx = 0; idx <= 20; ++idx){
            int randomInt = randomGenerator.nextInt(200);
            String randomUrl = stringArr[randomInt];
            //System.out.println(randomUrl);
           
            randomUrl = randomUrl.replace(".com", "");
            randomUrl = randomUrl.replace(".org", "");
            randomUrl = randomUrl.replace(".net", "");
            randomUrl = randomUrl.replace(".edu", "");
            System.out.println(randomUrl);
         
            stringArr[randomInt] = randomUrl;
            
          }
        System.out.println("\n==================================== \n");
	    System.out.println("Retesting total URLs \n");
	    System.out.println("==================================== \n");
        badUrls = 0;
        goodUrls =0;
        for(int i = 0;i< stringArr.length;i++){
        	
        	boolean validFlag = urlVal2.isValid(stringArr[i]);
        	if(validFlag){
        		//System.out.format("%s ... valid\n",stringArr[i]);
        		goodUrls++;
        	}
        	else{
        		System.out.format("%s ... invalid\n",stringArr[i]);
        		badUrls++;
        	}
        }
        System.out.format("%d of %d total are valid\n", goodUrls,totalUrls);
        
        
        //next we chop up and remix some URLs
        
	   
	  
	}
	public static void main(String[] argv){
		testURLs();
	}
}
