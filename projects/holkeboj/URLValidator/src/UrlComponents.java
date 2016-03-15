import java.util.ArrayList;

public class UrlComponents {
	
	int schemesLength;
	int authoritiesLength;
	int pathsLength;
	int queriesLength;
	int maxLength;
	
	// Test Schemes
	static ResultPair[] testSchemes = {
			new ResultPair("", true),
			new ResultPair("http://", true),
			new ResultPair("ftp://", true),
			new ResultPair("h3t://", true),
			new ResultPair("htpp://", false),
			new ResultPair("http", false),
			new ResultPair("http:/", false),
			new ResultPair("ftp:", false),
			new ResultPair("h3tt://", false),
			new ResultPair("fft:", false),
			new ResultPair(":/", false),
			new ResultPair("://", false),
	};

	// Test addresses
	static ResultPair[] testAddresses = {
			new ResultPair("yahoo.com", true),
			new ResultPair("www.yahoo.com", true),
			new ResultPair("www.yahoo.com.au", true),
			new ResultPair(".yahoo.com", false),
			new ResultPair("192.168.0.110", true),
			new ResultPair("300.168.0.110", false),
			new ResultPair("google.kjfwoei", false),
			new ResultPair("google.", false),
			new ResultPair("0.0.0.0", true),
			new ResultPair("12345.com", true),
			new ResultPair("255.255.255.255", true),
			new ResultPair("255.256.255.255", false),
			new ResultPair("256.255.255.255", false),
			new ResultPair("255.255.256.255", false),
			new ResultPair("255.255.255.256", false),
			new ResultPair("192.24.2.1.2", false),
			new ResultPair("192.168.0.500", false),
			new ResultPair("google", false),
			new ResultPair(".google", false),
			new ResultPair("", false)	
	};

	static ResultPair[] testPorts = {
			new ResultPair("", true),
			new ResultPair(":80", true),
			new ResultPair(":0", true),
			new ResultPair(":-1", false),
			new ResultPair(":oisd", false),
			new ResultPair(":44isd", false),
			new ResultPair(":24ois67", false),
			new ResultPair(":66849", false),
			new ResultPair(":65635", true)
	};

	static ResultPair[] testPaths = {
			new ResultPair("/testpath", true),
			new ResultPair("/i12iro3i", true),
			new ResultPair("/testpath/", true),
			new ResultPair("/$owie", true),
			new ResultPair("/..", false),
			new ResultPair("/#", false),
			new ResultPair("/#/testpath", false),
			new ResultPair("", true),
			new ResultPair("/testpath1/testpath2", true),
			new ResultPair("testpath1//testpath2", false),
			new ResultPair("/testpath1//testpath2", false),
			new ResultPair("", true),
			new ResultPair("1path/path2", false),
			new ResultPair("/1path/path2", true)
	};

	static ResultPair[] testQueryStrings = {
			new ResultPair("?query=this", true),
			new ResultPair("?query=this&query2=that", true),
			new ResultPair("?query=this&amp;query2=that", true),
			new ResultPair("?query=this and that", false),
			new ResultPair("", true),
	};
	
	public static ArrayList<ResultPair> makeList(ResultPair[] testAddresses, ResultPair[] testPorts)
	{
		int addressLength = testAddresses.length;
		int portLength = testPorts.length;
		ArrayList<ResultPair> list = new ArrayList<ResultPair>();
		int k = 0;
		
		for(int i = 0; i < addressLength; i++)
		{
			for(int j = 0; j < portLength; j++)
			{
				String authorityString = testAddresses[i].item+testPorts[j].item;
				boolean authorityBoolean = testAddresses[i].valid && testPorts[j].valid;
				ResultPair authority = new ResultPair(authorityString,authorityBoolean);
				list.add(authority);
			}
		}	
		return list;
	}
	
	static ArrayList<ResultPair> testAuthority = makeList(testAddresses, testPorts);
	
	public UrlComponents()
	{
		this.schemesLength=testSchemes.length;
		this.authoritiesLength=testAuthority.size();
		this.queriesLength=testQueryStrings.length;
		this.pathsLength=testPaths.length;
		this.maxLength = Math.max(Math.max(schemesLength, authoritiesLength),Math.max(queriesLength, pathsLength));
	}
}
