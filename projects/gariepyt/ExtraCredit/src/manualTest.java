public class manualTest {
	public static void main(String[] args) {
		if (args.length > 0) {
			String input = args[0];
			String[] schemes = {"http", "gopher"};
      		//UrlValidator urlVal = new UrlValidator(schemes,false,false,false);
      		UrlValidator urlVal = new UrlValidator();
      		boolean result = urlVal.isValid(input);
      		if (result == true) {
      			System.out.println("True");
      		}
      		else {
      			System.out.println("false");
      		}
		}
	}
}