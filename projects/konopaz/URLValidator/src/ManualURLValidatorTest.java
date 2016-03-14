import java.io.IOException;
import java.util.Arrays;
import java.util.Collection;

import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;


@RunWith(Parameterized.class)
public class ManualURLValidatorTest {
  private UrlValidator urlVal;
  private String urlToTest;
  private boolean expectedResult;

  @Parameterized.Parameters
  public static Collection<Object[]> getUrls() throws IOException {
    
    return Arrays.asList(new Object[][] { 
        {"https://amazon.com", true},
        {"https://www.amazon.com", true}, 
        {"http://www.amazon.com:80", true},
        {"https://www.amazon.com:80", true}, 
        {"http://www.amazon.com:443", true},
        {"https://www.amazon.com:443", true}, 
        {"http://www.amazon.com/help", true},
        {"https://www.amazon.com/help", true}, 
        {"http://www.amazon.com:80/help", true},
        {"https://www.amazon.com:80/help", true}, 
        {"http://www.amazon.com:443/help", true},
        {"https://www.amazon.com:443/help", true}, 
        {"http://www.amazon.com:123/help", true},
        {"https://www.amazon.com:123/help", true}, 
        {"http://www.amazon.com:12/help", true},
        {"https://www.amazon.com:12/help", true}, 
        {"https//www.amazon.com:12/help", false}, 
        {"https:amazon.com", false},
        {"https:/amazon.com", false},
        {"https://com", false},
        {"https://.amazon.com", false},
        /*
        {"gronk://www.amazon.com/", false},
        {"http://www.amazon.com:69648", true},
        {"https://www.amazon.com:69648", true}, 
        {"http://www.amazon.com:69648", true},
        {"https://www.amazon.com:69648", true}, 
        {"http://www.amazon.com:69648/help", true},
        {"https://www.amazon.com:69648/help", true}, 
        {"http://www.amazon.com:696483/help", true},
        {"https://www.amazon.com:696483/help", true}
        */
    });
  }

  @Before
  public void before() {
    urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
  }

  public ManualURLValidatorTest(final String urlToTest, final boolean expectedResult) {
    this.urlToTest = urlToTest;
    this.expectedResult = expectedResult;
  }

  @Test
  public void testManualTest() {
    Assert.assertEquals(urlToTest, expectedResult, urlVal.isValid(urlToTest));
  }
}
