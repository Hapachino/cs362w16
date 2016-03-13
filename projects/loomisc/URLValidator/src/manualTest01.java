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
	public void manualTest01() {
		UrlValidator manTest = new UrlValidator();
		
		String urlIn = "http://www.google.com";
		boolean result = manTest.isValid(urlIn);
		if(!result){System.out.print("\n"+urlIn);}
		assertTrue(result);
	}
	
	@Test
	public void manualTest02() {
		UrlValidator manTest = new UrlValidator();
			
		String urlIn = "http://www.google.com/";
		boolean result = manTest.isValid(urlIn);
		if(!result){System.out.print("\n"+urlIn);}
		assertTrue(result);
	}
	
	@Test
	public void manualTest03() {
		UrlValidator manTest = new UrlValidator();
			
		String urlIn = "www.google.com";
		boolean result = manTest.isValid(urlIn);
		if(!result){System.out.print("\n"+urlIn);}
		assertTrue(result);
	}
	
	@Test
	public void manualTest04() {
		UrlValidator manTest = new UrlValidator();
		
		String urlIn = "google.com";
		boolean result = manTest.isValid(urlIn);
		if(!result){System.out.print("\n"+urlIn);}
		assertTrue(result);
	}
	
	@Test
	public void manualTest05() {
		UrlValidator manTest = new UrlValidator();
		
		String urlIn = "http://google.com/";
		boolean result = manTest.isValid(urlIn);
		if(!result){System.out.print("\n"+urlIn);}
		assertTrue(result);
	}
	
	@Test
	public void manualTest06() {
		UrlValidator manTest = new UrlValidator();
		
		String urlIn = "http://";
		boolean result = manTest.isValid(urlIn);
		if(!result){System.out.print("\n"+urlIn);}
		assertTrue(result);
	}	
	
	@Test
	public void manualTest07() {
		UrlValidator manTest = new UrlValidator();

		String urlIn = "https://www.google.com/webhp?sourceid=chrome-instant&ion=1&espv=2&ie=UTF-8#q=cat%20videos";
		boolean result = manTest.isValid(urlIn);
		if(!result){System.out.print("\n"+urlIn);}
		assertTrue(result);
	}
	
	@Test
	public void manualTest08() {
		UrlValidator manTest = new UrlValidator();
		
		String urlIn = "https://www.reddit.com/r/catvideos";
		boolean result = manTest.isValid(urlIn);
		if(!result){System.out.print("\n"+urlIn);}
		assertTrue(result);
	}
	
	@Test
	public void manualTest09() {
		UrlValidator manTest = new UrlValidator();
		
		String urlIn = "https://www.youtube.com/watch?v=4T4_8LnvXw8&feature=youtu.be";
		boolean result = manTest.isValid(urlIn);
		if(!result){System.out.print("\n"+urlIn);}
		assertTrue(result);
	}
	
	@Test
	public void manualTest10() {
		UrlValidator manTest = new UrlValidator();
		
		String urlIn = "http://www.wired.com/2012/08/ff_cats/";
		boolean result = manTest.isValid(urlIn);
		if(!result){System.out.print("\n"+urlIn);}
		assertTrue(result);
	}
	
	@Test
	public void manualTest11() {
		UrlValidator manTest = new UrlValidator();

		String urlIn = "http://www.hawkforum.co.uk/viewforum.php?f=10&sid=9afa07a83d1ecef9b55eba8115c9a4c2";
		boolean result = manTest.isValid(urlIn);
		if(!result){System.out.print("\n"+urlIn);}
		assertTrue(result);
	}
	
	@Test
	public void manualTest12() {
		UrlValidator manTest = new UrlValidator();
		
		String urlIn = "http://web.engr.oregonstate.edu/~loomisc/";
		boolean result = manTest.isValid(urlIn);
		if(!result){System.out.print("\n"+urlIn);}
		assertTrue(result);
	}
	
	@Test
	public void manualTest13() {
		UrlValidator manTest = new UrlValidator();
		
		String urlIn = "https://www.google.com/?q=ha";
		boolean result = manTest.isValid(urlIn);
		if(!result){System.out.print("\n"+urlIn);}
		assertTrue(result);
	}
	
	@Test
	public void manualTest14() {
		UrlValidator manTest = new UrlValidator();
		
		String urlIn = "http://www.google.com?action=view";
		boolean result = manTest.isValid(urlIn);
		if(!result){System.out.print("\n"+urlIn);}
		assertTrue(result);
	}
	
	@Test
	public void manualTest15() {
		UrlValidator manTest = new UrlValidator();
		
		String urlIn = "http://www.google.com/$23";
		boolean result = manTest.isValid(urlIn);
		if(!result){System.out.print("\n"+urlIn);}
		assertTrue(result);
	}
	
	@Test
	public void manualTest16() {
		UrlValidator manTest = new UrlValidator();
		
		String urlIn = "http://www.google.com/?23";
		boolean result = manTest.isValid(urlIn);
		if(!result){System.out.print("\n"+urlIn);}
		assertTrue(result);
	}

}
