 


import java.util.ArrayList;

public class TestURL
{

    private String protocol;
    private String host;       //do we want this split by subdomain / domain?
    private String port;      
    private String path;
    private String parameters;  //might have more than one
    private boolean valid;

    public TestURL(UrlComponent p, Host h, UrlComponent po, UrlComponent pa,
    UrlComponent params)
    {
        boolean tempValid = true;
        
        this.protocol = p.getComponent();
        tempValid &= p.isValid();
        
        this.host = h.getHost();
        tempValid &= h.isValid();
        
        this.port = po.getComponent();
        tempValid &= po.isValid();
        
        this.path = pa.getComponent();
        tempValid &= pa.isValid();
        
        this.parameters = params.getComponent();
        tempValid &= params.isValid();
        
        this.valid = tempValid;
    }

    
    public String toString()
    {
        return protocol + host + port + path + parameters;
    }
    
    public boolean isValid() 
    {
        return valid;
    }
}