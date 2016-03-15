public class manualTest {
	public static void main (String[] args) {
		int i;
		String testGoodURLS[] = {"www.google.com", "http://google.com/test", "https://amazon.co.uk", "www.oregonstate.edu"};
		String testBadURLS[] = {"httq://www.google.com", "http://google.com/$test", "www.$$$$.com", "www.amazon.com:-1"};
		UrlValidator validator = new UrlValidator();

		for (i = 0; i < 4; i++) {
			System.out.println("Input: " + testGoodURLS[i]);
			System.out.print("Expected Result: Test passed");

			if(validator.isValid(testGoodURLS[i])) {
				System.out.println("Actual Result: Test passed");
			}
			else
				System.out.println("Actual Result: Test failed");
		}

		for (i = 0; i < 4; i++) {
			System.out.println("Input: " + testBadURLS[i]);
			System.out.print("Expected Result: Test failed");

			if(validator.isValid(testBadURLS[i])) {
				System.out.println("Actual Result: Test passed");
			}
			else
				System.out.println("Actual Result: Test failed");
		}

	}
}