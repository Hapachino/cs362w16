import java.util.Random;

public class GenerateUrl {
	
	UrlComponents components = new UrlComponents();
	public int[] randArray()
	{
		Random generator = new Random();
		int[] randArr = new int[4];
		randArr[0] = generator.nextInt(components.schemesLength);
		randArr[1] = generator.nextInt(components.authoritiesLength);
		randArr[2] = generator.nextInt(components.pathsLength);
		randArr[3] = generator.nextInt(components.queriesLength);	
		return randArr;
	}
	
	public String[] urlComponentArray(int[] r)
	{
		String[] urlComp = new String[4];
		
		urlComp[0] = (String) UrlComponents.testSchemes[r[0]].item;
		urlComp[1] = UrlComponents.testAuthority.get(r[1]).item;
		urlComp[2] = UrlComponents.testPaths[r[2]].item;	
		urlComp[3] = UrlComponents.testQueryStrings[r[3]].item;	
		return urlComp;
	}
	
	public String createUrl(String[] urlComp)
	{
		StringBuilder URL = new StringBuilder();
		
		for(String comp:urlComp)
		{
			URL.append(comp);
		}
		return URL.toString();		
	}
	
	public boolean[] isValidArray(int[] r)
	{
		boolean[] isValidComponent = new boolean[4]; 
		isValidComponent[0] = UrlComponents.testSchemes[r[0]].valid;
		isValidComponent[1] = UrlComponents.testAuthority.get(r[1]).valid;
		isValidComponent[2] = UrlComponents.testPaths[r[2]].valid;	
		isValidComponent[3] = UrlComponents.testQueryStrings[r[3]].valid;
		return isValidComponent;
	}
	
	public boolean isValid(boolean[] comp)
	{
		boolean isValid = true;
		for(int i = 0; i < comp.length; i++)
		{
			isValid &= comp[i];
		}
		return isValid;
	}
}

