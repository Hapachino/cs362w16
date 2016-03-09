
public class debug {
	public static void main(String[] args) {
		UrlValidator urlVal = new UrlValidator();
		boolean expRes = true;
		boolean actRes = urlVal.isValid("https://google.com?a=yes");
	}
}
