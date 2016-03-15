 



public class UrlComponent 
{
    private String component;
    private boolean valid;

    //constructor for UrlComponent Object
    public UrlComponent(String c, boolean v)
    {
        this.component = c;
        this.valid = v;
    }

    //accessor methods
    public String getComponent() {return component;}

    public boolean isValid() {return valid;}

}


