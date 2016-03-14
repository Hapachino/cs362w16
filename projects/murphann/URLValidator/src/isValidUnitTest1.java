import junit.framework.TestCase;
import java.util.Scanner;



public class isValidUnitTest1 extends TestCase{

	public static void main(String args[]) {
	
		
		
		Scanner keyboard = new Scanner(System.in);
		
		UrlValidator URLtester = new UrlValidator();
		
		for(int i=0; i < 5; i++){
			System.out.println("Enter URL to chcek: ");
			String testURL = keyboard.nextLine();
			System.out.println(URLtester.isValid(testURL));
		}
		keyboard.close();
		
			
	}
	
}