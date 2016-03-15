
import junit.framework.TestCase;
import java.util.ArrayList;
public class UrlValidatorTesting extends TestCase{

    public UrlValidatorTesting(String testName)
    {
        super(testName);
    }

    public void testIsValid()
    {

        boolean printFails = false;
        boolean printPasses = false;

        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

        ArrayList<UrlComponent> protocols = new ArrayList<UrlComponent>();
        ArrayList<Host> hosts = new ArrayList<Host>();
        ArrayList<UrlComponent> ports = new ArrayList<UrlComponent>();
        ArrayList<UrlComponent> paths = new ArrayList<UrlComponent>();
        ArrayList<UrlComponent> parameters = new ArrayList<UrlComponent>();
        buildComponents(protocols, hosts, ports, paths, parameters);

        TestURL test;
        System.out.println(urlVal.isValid("h3t://www.com.com"));
        System.out.println(urlVal.isValid("http://video.espn.co.uk:80"));
        System.out.println(urlVal.isValid("http://video.espn.co.uk:80/test1"));
        System.out.println(urlVal.isValid("http://video.espn.co.uk:80/test1?action=view"));
        int failcount = 0;
        int passcount = 0;
        boolean loop = true;
        if(loop)
        {
            System.out.println("starting Loop");
            for(UrlComponent protocol : protocols)
                for(Host host : hosts)
                    for(UrlComponent port : ports)
                        for(UrlComponent path : paths)
                            for(UrlComponent parameter : parameters)
                            {
                                test = new TestURL(protocol, host, port, path, parameter);

                                if(urlVal.isValid(test.toString()) == test.isValid())
                                {
                                    passcount++;
                                    if(printPasses) 
                                    {
                                        System.out.print(passcount + " " +test + "("+test.isValid()+")");
                                        System.out.println("--- passed");
                                    }
                                }
                                else 
                                {
                                    failcount++;
                                    if (printFails)
                                    {
                                        System.out.print(failcount + " " +test + "("+test.isValid()+")");
                                        System.out.println("==============================FAIL");

                                    }
                                }
                                //assertEquals(urlVal.isValid(test.toString()), test.isValid());
                                //System.out.println("-- passed");
                            }
            System.out.println("Testing complete: " + passcount + " tests passed,  " + failcount + " tests failed.");
        }

    }

    private void buildComponents( ArrayList<UrlComponent> protocols,  ArrayList<Host> hosts,
    ArrayList<UrlComponent> ports,  ArrayList<UrlComponent> paths,
    ArrayList<UrlComponent> parameters)
    {
        boolean noisyTest = true;
        protocols.add(new UrlComponent("http://", true));
        protocols.add(new UrlComponent("ftp://", true));
        protocols.add(new UrlComponent("h3t://", true));
        protocols.add(new UrlComponent("3ht://", false));
        protocols.add(new UrlComponent("http:/", false));
        protocols.add(new UrlComponent("http:", false));
        protocols.add(new UrlComponent("http/", false));
        protocols.add(new UrlComponent("://", false));
        protocols.add(new UrlComponent("", false));

        ArrayList<UrlComponent> topDomain = new ArrayList<UrlComponent>();
        ArrayList<UrlComponent> secondDomain = new ArrayList<UrlComponent>();
        ArrayList<UrlComponent> subDomain = new ArrayList<UrlComponent>();

        topDomain.add( new UrlComponent("com", true));
        topDomain.add( new UrlComponent("co.uk", true));
        topDomain.add( new UrlComponent("edu", true));
        topDomain.add( new UrlComponent("gov", true));
        topDomain.add( new UrlComponent("hello", false));
        topDomain.add( new UrlComponent("", false));

        secondDomain.add( new UrlComponent("espn", true));
        secondDomain.add( new UrlComponent("google", true));
        secondDomain.add( new UrlComponent("com", true));
        secondDomain.add( new UrlComponent("***", false));
        secondDomain.add( new UrlComponent("", false));

        subDomain.add(new UrlComponent("video", true));
        subDomain.add(new UrlComponent("", true));
        subDomain.add(new UrlComponent("www", true));
        subDomain.add(new UrlComponent("go", true));
        subDomain.add(new UrlComponent("***", false));

        for(UrlComponent top : topDomain)
            for(UrlComponent second : secondDomain)
                for(UrlComponent sub : subDomain)
                    hosts.add(new Host(top, second, sub));

        /*
        hosts.add(new UrlComponent("www.google.com", true));
        hosts.add(new UrlComponent("go.com", true));
        hosts.add(new UrlComponent("go.au", true));
        hosts.add(new UrlComponent("0.0.0.0", true));
        hosts.add(new UrlComponent("255.255.255.255", true));
        hosts.add(new UrlComponent("256.256.256.256", false));
        hosts.add(new UrlComponent("255.com", true));
        hosts.add(new UrlComponent("1.2.3.4.5", false));
        hosts.add(new UrlComponent("1.2.3.4.", false));
        hosts.add(new UrlComponent("1.2.3", false));
        hosts.add(new UrlComponent(".1.2.3.4", false));
        hosts.add(new UrlComponent("go.a", false));
        hosts.add(new UrlComponent("go.a1a", false));
        hosts.add(new UrlComponent("go.cc", true));
        hosts.add(new UrlComponent("go.1aa", false));
        hosts.add(new UrlComponent("aaa.", false));
        hosts.add(new UrlComponent(".aaa", false));
        hosts.add(new UrlComponent("aaa", false));
        hosts.add(new UrlComponent("", false));
         */
        ports.add(new UrlComponent(":80", true));
        ports.add(new UrlComponent(":65535", true));
        ports.add(new UrlComponent(":0", true));
        ports.add(new UrlComponent("", true));
        ports.add(new UrlComponent(":65636", true));
        ports.add(new UrlComponent(":65a", false));

        paths.add(new UrlComponent("/test1", true));
        paths.add(new UrlComponent("/t123", true));
        paths.add(new UrlComponent("/$23", true));
        paths.add(new UrlComponent("/..", false));
        paths.add(new UrlComponent("/../", false));
        paths.add(new UrlComponent("/test1/", true));
        paths.add(new UrlComponent("", true));
        paths.add(new UrlComponent("/test1/file", true));
        paths.add(new UrlComponent("/..//file", false));
        paths.add(new UrlComponent("/test1//file", false));

        parameters.add(new UrlComponent("?action=view", true));
        parameters.add(new UrlComponent("?action=edit&mode=up", true));
        parameters.add(new UrlComponent("", true));
    }
}