import static org.junit.Assert.*;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

public class manualTest01 {

	@Before
	public void setUp() throws Exception {
	}

	@After
	public void tearDown() throws Exception {
	}

	@Test
	public void manualTest() {
		UrlValidator manTest = new UrlValidator();
		
		String urlIn = "http://www.google.com";
		boolean result = manTest.isValid(urlIn);
		if(!result){System.out.print("\n"+urlIn);}
		
		urlIn = "http://www.google.com/";
		result = manTest.isValid(urlIn);
		if(!result){System.out.print("\n"+urlIn);}
		
		urlIn = "www.google.com";
		result = manTest.isValid(urlIn);
		if(!result){System.out.print("\n"+urlIn);}
		
		urlIn = "google.com";
		result = manTest.isValid(urlIn);
		if(!result){System.out.print("\n"+urlIn);}
		
		urlIn = "http://google.com/";
		result = manTest.isValid(urlIn);
		if(!result){System.out.print("\n"+urlIn);}
		
		urlIn = "http://";
		result = manTest.isValid(urlIn);
		if(!result){System.out.print("\n"+urlIn);}
		
		urlIn = "https://www.google.com/webhp?sourceid=chrome-instant&ion=1&espv=2&ie=UTF-8#q=cat%20videos";
		result = manTest.isValid(urlIn);
		if(!result){System.out.print("\n"+urlIn);}
		
		urlIn = "https://www.reddit.com/r/catvideos";
		result = manTest.isValid(urlIn);
		if(!result){System.out.print("\n"+urlIn);}
		
		urlIn = "https://www.youtube.com/watch?v=4T4_8LnvXw8&feature=youtu.be";
		result = manTest.isValid(urlIn);
		if(!result){System.out.print("\n"+urlIn);}
		
		urlIn = "http://www.wired.com/2012/08/ff_cats/";
		result = manTest.isValid(urlIn);
		if(!result){System.out.print("\n"+urlIn);}
		
		urlIn = "http://www.hawkforum.co.uk/viewforum.php?f=10&sid=9afa07a83d1ecef9b55eba8115c9a4c2";
		result = manTest.isValid(urlIn);
		if(!result){System.out.print("\n"+urlIn);}
		
		urlIn = "http://web.engr.oregonstate.edu/~loomisc/";
		result = manTest.isValid(urlIn);
		if(!result){System.out.print("\n"+urlIn);}
		
		urlIn = "https://www.google.com/?q=ha";
		result = manTest.isValid(urlIn);
		if(!result){System.out.print("\n"+urlIn);}
		
		urlIn = "http://www.google.com?action=view";
		result = manTest.isValid(urlIn);
		if(!result){System.out.print("\n"+urlIn);}
		
		urlIn = "http://www.google.com/$23";
		result = manTest.isValid(urlIn);
		if(!result){System.out.print("\n"+urlIn);}
		
		urlIn = "http://www.google.com/?23";
		result = manTest.isValid(urlIn);
		if(!result){System.out.print("\n"+urlIn);}
	}

}
