import java.util.Random;

public class testIsValid {
	public static void main(String[] args) {
		int testNumber, randScheme, randAuthority, randPort, randPath;
		boolean isValid;
		String testURL;
		Random rand = new Random();
		String[] urlScheme = {"http://", "https://", "http://www.", "https://www.", "//"};
		String[] urlAuthority = {"google.com", "yahoo.com", "reddit.com", "google.co.uk", "oregonstate.edu"};
		String[] urlPort = {":80", ""};
		String[] urlPath = {"/test", "/test/", "/test/file", ""};
		String[] badUrlScheme = {"::", "wcw.", "httq://www.", "", "/"};
		String[] badUrlAuthority = {"@#$!@.com", "#@$#!$.gov", ".com", "$$.co.uk", "2$2.edu"};
		String[] badUrlPort = {":$%", ":-1"};
		String[] badUrlPath = {"//test", "/test//", "/#/file", "/test/--file"};

		for(testNumber = 0; testNumber < 2000; testNumber++) {
			randScheme = rand.nextInt(5);
			randAuthority = rand.nextInt(5);
			randPort = rand.nextInt(2);
			randPath = rand.nextInt(4);
			isValid = rand.nextBoolean();

			if (isValid == true) {
				testURL = urlScheme[randScheme] + urlAuthority[randAuthority] + urlPort[randPort] + urlPath[randPath];
			}
			else {
				testURL = badUrlScheme[randScheme] + badUrlAuthority[randAuthority] + badUrlPort[randPort] + badUrlPath[randPath];
			}

			testOracle(testURL, isValid);
		}

	}

	public static void testOracle(String testURL, boolean isValid) {
		UrlValidator validator = new UrlValidator();
		boolean result = validator.isValid(testURL);

		if (result == isValid) {
			System.out.println("Test Passed%n");
		}
		else
			System.out.println("Test failed%n");

		System.out.println("The URL passed was: " + testURL + "%n");
		System.out.println("Expected Result: " + isValid + "%n");
		System.out.println("Actual Result: " + result + "%n");
	}
}