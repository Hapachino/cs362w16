import static org.junit.Assert.*;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

public class portTest01 {

	@Before
	public void setUp() throws Exception {
	}

	@After
	public void tearDown() throws Exception {
	}

	@Test
	public void portLen0() {
		UrlValidator manTest = new UrlValidator();
		
		String urlIn = "http://www.google.com";
		boolean result = manTest.isValid(urlIn);
		if(!result){System.out.print("\n"+urlIn);}
		assertTrue(result);
	}
	
	@Test
	public void portLen1() {
		UrlValidator manTest = new UrlValidator();
		
		String urlIn = "http://www.google.com:0";
		boolean result = manTest.isValid(urlIn);
		if(!result){System.out.print("\n"+urlIn);}
		assertTrue(result);
	}
	
	@Test
	public void portLen2() {
		UrlValidator manTest = new UrlValidator();
		
		String urlIn = "http://www.google.com:00";
		boolean result = manTest.isValid(urlIn);
		if(!result){System.out.print("\n"+urlIn);}
		assertTrue(result);
	}
	
	@Test
	public void portLen3() {
		UrlValidator manTest = new UrlValidator();
		
		String urlIn = "http://www.google.com:000";
		boolean result = manTest.isValid(urlIn);
		if(!result){System.out.print("\n"+urlIn);}
		assertTrue(result);
	}
	
	@Test
	public void portLen4() {
		UrlValidator manTest = new UrlValidator();
		
		String urlIn = "http://www.google.com:0000";
		boolean result = manTest.isValid(urlIn);
		if(!result){System.out.print("\n"+urlIn);}
		assertTrue(result);
	}
	
	@Test
	public void portLen5() {
		UrlValidator manTest = new UrlValidator();
		
		String urlIn = "http://www.google.com:00000";
		boolean result = manTest.isValid(urlIn);
		if(!result){System.out.print("\n"+urlIn);}
		assertTrue(result);
	}
	
	@Test
	public void portLen6() {
		UrlValidator manTest = new UrlValidator();
		
		String urlIn = "http://www.google.com:000000";
		boolean result = manTest.isValid(urlIn);
		if(!result){System.out.print("\n"+urlIn);}
		assertTrue(result);
	}

}
