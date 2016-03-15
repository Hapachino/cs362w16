 



public class Host
{

    private String topLevel;
    private String secondLevel;
    private String subDomain;
    private boolean valid;
    private String ip;
    
    //constructor for UrlComponent Object
    public Host(UrlComponent top, UrlComponent second, UrlComponent sub)
    {
        this.topLevel = top.getComponent();
        this.secondLevel = second.getComponent();
        this.subDomain = sub.getComponent();
       
        this.valid = top.isValid() && second.isValid() && sub.isValid();
        
    }
    
    public Host (UrlComponent ipAddress)
    {
        this.ip = ipAddress.getComponent();
        valid = ipAddress.isValid();
    }

    //accessor methods
    public String getHost() 
    {
        if(ip == null)
        {
            if(subDomain.equals(""))
                return secondLevel+"."+topLevel;
            return subDomain+"."+secondLevel+"."+topLevel;
        }
        return ip;
    }

    public boolean isValid() {return valid;}
    
}
