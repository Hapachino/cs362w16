/*
CS 362 - Winter 2016
Final Project - Extra credit part
Random tester for URL Validator valid() method


It generates a set of input urls by combining the sample url elements provided by commons apache.
Each sample url element is associated with a boolean value of valid or invalid.
In combining the elements, the code constructs a sample url along with its boolean value of valid or invalid.
For each sample url it is also used as an input for the buggy isValid() method.
Since the input url's value is predetermined, we can compare whether the isValid() method returns the expected value.
If there is discrepancy between expected and isValid() result values, 
the code records those values as well as any sub string that was added from the previous input.


Place "UrlValidatorRandomTester.java" in ...\URLValidator\src  folder.


Usage:

...\URLValidator\src>javac UrlValidatorRandomTester.java

...\URLValidator\src>java UrlValidatorRandomTester > output.txt

*/


public class UrlValidatorRandomTester {
	
	public static void main(String[] args) {
		UrlValidatorRandomTester urlValidatorRandomTester = new UrlValidatorRandomTester();
		urlValidatorRandomTester.testIsValid();
	}
	
	
	// source: UrlValidatorTest.java (apache commons)
	public void testIsValid() {
		///////////////// set the number of iteration here /////////////////////
		int numOfIteration = 10000;
		////////////////////////////////////////////////////////////////////////
		
		
		String[] arrInputUrl = new String[numOfIteration];
		StringBuilder sb;
		int randomIndex;
		boolean expected;
		
		for (int cnt=0; cnt<numOfIteration; ++cnt) {
			sb = new StringBuilder();
			expected = true;
			
			for (int testPartsIndexIndex=0; testPartsIndexIndex<testUrlParts.length; ++testPartsIndexIndex) {
				ResultPair[] part = (ResultPair[])testUrlParts[testPartsIndexIndex];
				if (testPartsIndexIndex > 0) randomIndex = (int)(Math.random()*part.length);
				else randomIndex = (int)(Math.random()*part.length-1); // prevent testUrlScheme from being a blank
	            sb.append(part[randomIndex].item);
	            expected &= part[randomIndex].valid;
	        }
			
			if (expected) sb.append(1); // true -> append "1"
			else sb.append(0); // false -> append "0"
			
			arrInputUrl[cnt] = sb.toString();
		}
		
		// sort the input urls
		java.util.Arrays.sort(arrInputUrl);
		
		
		UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	    String url, laststr = "", diffstr;
	    
	    for (int cnt=0; cnt<numOfIteration; ++cnt) {
	    	int len = arrInputUrl[cnt].length();
	    	url = arrInputUrl[cnt].substring(0, len-1);
	    	if (arrInputUrl[cnt].charAt(len-1) == '1') expected = true;
	    	else expected = false;
	    	
	        diffstr = "";
			if (laststr != "") {
				int idx = -1;
				if (laststr.length() > url.length()) len = url.length();
				else if (laststr.length() < url.length()) len = laststr.length();
				else len = url.length();
				
				for (int n=0; n<len; ++n)
					if (laststr.charAt(n) != url.charAt(n)) {
						idx = n;
						break;
					}
				
				if (idx >= 0) 
					diffstr = url.substring(idx);
			}
			else diffstr = url;
			laststr = url;
			
			// test isValid (buggy) method
			System.out.println(url);
			boolean result = urlVal.isValid(url);
	        if (result == expected) {
	        	//System.out.println("[Expected] " + expected + "  [Buggy] " + result + "\n");
	        	;
	        }
	        else {
	        	System.out.println("[Expected] " + expected + "  [Buggy] " + result + 
	        			"  [Diff Str] " + diffstr + "\n");
	        	//System.out.println("[Expected] " + expected + "  [Buggy] " + result + "\n");
	        }
	    }
	}
	
	
	//---------------- Test data for individual url parts ----------------
	ResultPair[] testUrlScheme = {new ResultPair("http://", true),
								new ResultPair("ftp://", true),
								new ResultPair("h3t://", true),
								new ResultPair("3ht://", false),
								new ResultPair("http:/", false),
								new ResultPair("http:", false),
								new ResultPair("http/", false),
								new ResultPair("://", false),
								new ResultPair("", true)};
	
	ResultPair[] testUrlAuthority = {new ResultPair("www.google.com", true),
								new ResultPair("go.com", true),
								new ResultPair("go.au", true),
								new ResultPair("0.0.0.0", true),
								new ResultPair("255.255.255.255", true),
								new ResultPair("256.256.256.256", false),
								new ResultPair("255.com", true),
								new ResultPair("1.2.3.4.5", false),
								new ResultPair("1.2.3.4.", false),
								new ResultPair("1.2.3", false),
								new ResultPair(".1.2.3.4", false),
								new ResultPair("go.a", false),
								new ResultPair("go.a1a", false),
								new ResultPair("go.cc", true),
								new ResultPair("go.1aa", false),
								new ResultPair("aaa.", false),
								new ResultPair(".aaa", false),
								new ResultPair("aaa", false),
								new ResultPair("", false)};
	
	ResultPair[] testUrlPort = {new ResultPair(":80", true),
								new ResultPair(":65535", true),
								new ResultPair(":0", true),
								new ResultPair("", true),
								new ResultPair(":-1", false),
								new ResultPair(":65636", true),
								new ResultPair(":65a", false)};
	
	ResultPair[] testPath = {new ResultPair("/test1", true),
								new ResultPair("/t123", true),
								new ResultPair("/$23", true),
								new ResultPair("/..", false),
								new ResultPair("/../", false),
								new ResultPair("/test1/", true),
								new ResultPair("", true),
								new ResultPair("/test1/file", true),
								new ResultPair("/..//file", false),
								new ResultPair("/test1//file", false)};
	
	ResultPair[] testUrlQuery = {new ResultPair("?action=view", true),
								new ResultPair("?action=edit&mode=up", true),
								new ResultPair("", true)};

	Object[] testUrlParts = {testUrlScheme, testUrlAuthority, testUrlPort, testPath, testUrlQuery};
	
} // end of class
