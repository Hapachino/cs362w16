

public class UnitTest {
	
	public static void testIsValid() {
		
		
		UrlValidator URLtester = new UrlValidator();
		String[] validURLs = {  "www.google.com",
								"http://www.google.com",
								"google.com",
								"http://google.com",
								"https://google.com",
								"http://google.com:80",
								"http://google.com/test1/file",
								"h3t://google.com"};

		String[] invalidURLs = {"httpgoogle",
								"www.google.com.www",
								"file:///c:\\",
								"",
								"google.com//",
								"http://google.com:-1",
								"http:\\google.com/test1/file",
								"http://googlecom"};
					
		System.out.println("TESTING VALID URLs \n");
	
		for (String url: validURLs) {
			boolean result = URLtester.isValid(url);
			
			if (!result)
				System.out.println("Failed: "+ url);
			
		}
		
		System.out.println("\nTESTING INVALID URLs \n");
		
		for (String url: invalidURLs) {
			boolean result = URLtester.isValid(url);
			
			if (result)
				System.out.println("Passed: "+url);
			
		}
		
	}
	
	public static void main(String args[]) {
		
		testIsValid();
		
		
	}

}