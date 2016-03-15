/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
import org.junit.Test;
import static org.junit.Assert.assertTrue;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertEquals;
import java.lang.reflect.Array;
import java.util.Random;

/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */
public class UrlValidatorTest {
    private UrlValidator urlVal = new UrlValidator(
        null,
        null,
        UrlValidator.ALLOW_ALL_SCHEMES
    );
    private Random rand = new Random();
    private static final boolean RUN_TESTISVALID = true;
    private static final boolean PRINT_INVALID = false;
    private static final String[] ORIG_TLDS = {
        ".com",
        ".org",
        ".net",
        ".int",
        ".edu",
        ".gov",
        ".mil"
    };
    private static final String[] CC_TLDS = {
        ".ac",
        ".fi",
        ".ke",
        ".pa",
        ".ua",
        ".zw"
    };

    @Test
    public void testManualTest() {
        // ----- Valid URLs -----
        System.out.println("----- Valid URLs -----");
        System.out.printf(
            "pass = %b:\thttp://www.domain.com\n",
            this.urlVal.isValid("http://www.domain.com") == true
        );
        System.out.printf(
            "pass = %b:\tftp://www.domain.com\n",
            this.urlVal.isValid("ftp://www.domain.com") == true
        );
        System.out.printf(
            "pass = %b:\thttp://www.domain.com:80\n",
            this.urlVal.isValid("http://www.domain.com:80") == true
        );
        System.out.printf(
            "pass = %b:\thttp://www.domain.com:30000\n",
            this.urlVal.isValid("http://www.domain.com:30000") == true
        );
        System.out.printf(
            "pass = %b:\thttp://www.domain.us\n",
            this.urlVal.isValid("http://www.domain.us") == true
        );
        System.out.printf(
            "pass = %b:\thttp://domain.com\n",
            this.urlVal.isValid("http://domain.com") == true
        );
        System.out.printf(
            "pass = %b:\thttp://www.domain.com/testpath\n",
            this.urlVal.isValid("http://www.domain.com/testpath") == true
        );
        System.out.printf(
            "pass = %b:\thttp://www.domain.com/testpath/\n",
            this.urlVal.isValid("http://www.domain.com/testpath/") == true
        );
        System.out.printf(
            "pass = %b:\thttp://127.0.0.1\n",
            this.urlVal.isValid("http://127.0.0.1") == true
        );
        System.out.printf(
            "pass = %b:\thttp://www.domain.com/?key=value\n",
            this.urlVal.isValid("http://www.domain.com/?key=value") == true
        );
        System.out.printf(
            "pass = %b:\thttp://www.domain.com/?key=value&key2=value2\n",
            this.urlVal.isValid(
                "http://www.domain.com/?key=value&key2=value2"
            ) == true
        );
        System.out.printf(
            "pass = %b:\thttp://www.domain.com/#fragment\n",
            this.urlVal.isValid("http://www.domain.com/#fragment") == true
        );


        // ----- Invalid URLs -----
        System.out.println("\n----- Invalid URLs -----");
        // Invalid TLD
        System.out.printf(
            "pass = %b:\thttp://www.domain\n",
            this.urlVal.isValid("http://www.domain") == false
        );

        // Incorrect number of forward-slashes after scheme and colon
        System.out.printf(
            "pass = %b:\thttp:/www.domain.com\n",
            this.urlVal.isValid("http:/www.domain.com") == false
        );
        System.out.printf(
            "pass = %b:\thttp:///www.domain.com\n",
            this.urlVal.isValid("http:///www.domain.com") == false
        );

        // Port with too many digits
        System.out.printf(
            "pass = %b:\thttp://www.domain.com:123456\n",
            this.urlVal.isValid("http://www.domain.com:123456") == false
        );

        // Missing scheme
        System.out.printf(
            "pass = %b:\twww.domain.com\n",
            this.urlVal.isValid("www.domain.com") == false
        );

        // IP address including a number that's too large (above 255)
        System.out.printf(
            "pass = %b:\thttp://192.168.1.300\n",
            this.urlVal.isValid("http://192.168.1.300") == false
        );
    }

    @Test
    public void testSchemePartition() {
        // Valid schemes
        assertTrue(this.urlVal.isValid("http://www.domain.com"));
        assertTrue(this.urlVal.isValid("https://www.domain.com"));
        assertTrue(this.urlVal.isValid("ftp://www.domain.com"));
        assertTrue(this.urlVal.isValid("mailto://www.domain.com"));
        assertTrue(this.urlVal.isValid("abc123://www.domain.com"));
        assertTrue(this.urlVal.isValid("a1b2c://www.domain.com"));
        assertTrue(this.urlVal.isValid("a-c://www.domain.com"));
        assertTrue(this.urlVal.isValid("a.c://www.domain.com"));
        assertTrue(this.urlVal.isValid("a+c://www.domain.com"));

        // Invalid schemes
        assertFalse(this.urlVal.isValid("www.domain.com"));
        assertFalse(this.urlVal.isValid("http:/www.domain.com"));
        assertFalse(this.urlVal.isValid("http/www.domain.com"));
        assertFalse(this.urlVal.isValid("http//www.domain.com"));
        assertFalse(this.urlVal.isValid("http:///www.domain.com"));
        assertFalse(this.urlVal.isValid("://www.domain.com"));
        assertFalse(this.urlVal.isValid(":/www.domain.com"));
        assertFalse(this.urlVal.isValid(":www.domain.com"));
        assertFalse(this.urlVal.isValid("//www.domain.com"));
        assertFalse(this.urlVal.isValid("/www.domain.com"));
        assertFalse(this.urlVal.isValid("http:www.domain.com"));
        assertFalse(this.urlVal.isValid("1abc://www.domain.com"));
    }

    @Test
    public void testAuthorityPartition() {
        // Valid authorities
        assertTrue(this.urlVal.isValid("http://www.domain.com"));
        assertTrue(this.urlVal.isValid("http://domain.com"));
        assertTrue(this.urlVal.isValid("http://www.domain.org"));
        assertTrue(this.urlVal.isValid("http://www.domain.net"));
        assertTrue(this.urlVal.isValid("http://www.domain.name"));
        assertTrue(this.urlVal.isValid("http://www.domain.ac"));
        assertTrue(this.urlVal.isValid("http://www.domain.fi"));
        assertTrue(this.urlVal.isValid("http://www.domain.ke"));
        assertTrue(this.urlVal.isValid("http://www.domain.pa"));
        assertTrue(this.urlVal.isValid("http://www.domain.ua"));
        assertTrue(this.urlVal.isValid("http://www.domain.zw"));
        assertTrue(this.urlVal.isValid("http://127.0.0.1"));
        assertTrue(this.urlVal.isValid("http://0.0.0.0"));
        assertTrue(this.urlVal.isValid("http://255.255.255.255"));

        // Invalid authorities
        assertFalse(this.urlVal.isValid("http://www.domain.asdfghjkl"));
        assertFalse(this.urlVal.isValid("http://.com"));
        assertFalse(this.urlVal.isValid("http://com."));
        assertFalse(this.urlVal.isValid("http://com"));
        assertFalse(this.urlVal.isValid("http://0"));
        assertFalse(this.urlVal.isValid("http://0.0"));
        assertFalse(this.urlVal.isValid("http://0.0.0"));
        assertFalse(this.urlVal.isValid("http://0.0.0.300"));
        assertFalse(this.urlVal.isValid("http://.0.0.0.0"));
        assertFalse(this.urlVal.isValid("http://0.0.0.0."));
        assertFalse(this.urlVal.isValid("http://0.0.0.0.0"));
    }

    @Test
    public void testPortPartition() {
        // Valid ports
        assertTrue(this.urlVal.isValid("http://www.domain.com"));
        assertTrue(this.urlVal.isValid("http://www.domain.com:0"));
        assertTrue(this.urlVal.isValid("http://www.domain.com:80"));
        assertTrue(this.urlVal.isValid("http://www.domain.com:123"));
        assertTrue(this.urlVal.isValid("http://www.domain.com:1234"));
        assertTrue(this.urlVal.isValid("http://www.domain.com:12345"));
        assertTrue(this.urlVal.isValid("http://www.domain.com:65535"));

        // Invalid ports
        assertFalse(this.urlVal.isValid("http://www.domain.com:-1"));
        assertFalse(this.urlVal.isValid("http://www.domain.com:65536"));
        assertFalse(this.urlVal.isValid("http://www.domain.com:123456"));
        assertFalse(this.urlVal.isValid("http://www.domain.com:a1"));
        assertFalse(this.urlVal.isValid("http://www.domain.com:1a"));
    }

    @Test
    public void testPathPartition() {
        // Valid paths
        assertTrue(this.urlVal.isValid("http://www.domain.com"));
        assertTrue(this.urlVal.isValid("http://www.domain.com/"));
        assertTrue(this.urlVal.isValid("http://www.domain.com/test"));
        assertTrue(this.urlVal.isValid("http://www.domain.com/test/"));
        assertTrue(this.urlVal.isValid("http://www.domain.com/1test"));
        assertTrue(this.urlVal.isValid("http://www.domain.com/test1"));
        assertTrue(this.urlVal.isValid("http://www.domain.com/1test1"));
        assertTrue(this.urlVal.isValid("http://www.domain.com/1test1"));
        assertTrue(this.urlVal.isValid("http://www.domain.com/~"));
        assertTrue(this.urlVal.isValid("http://www.domain.com/."));
        assertTrue(this.urlVal.isValid("http://www.domain.com/~/test2"));
        assertTrue(this.urlVal.isValid("http://www.domain.com/test/test2"));
        assertTrue(this.urlVal.isValid("http://www.domain.com/test/test2/"));
        assertTrue(this.urlVal.isValid(
            "http://www.domain.com/test/test2/test3"
        ));
        assertTrue(this.urlVal.isValid(
            "http://www.domain.com/test/test2/test3/"
        ));

        // Invalid paths
        assertFalse(this.urlVal.isValid("http://www.domain.com/.."));
        assertFalse(this.urlVal.isValid("http://www.domain.com//"));
        assertFalse(this.urlVal.isValid("http://www.domain.com/../test"));
        assertFalse(this.urlVal.isValid("http://www.domain.com//test"));
        assertFalse(this.urlVal.isValid("http://www.domain.com//test/"));
        assertFalse(this.urlVal.isValid("http://www.domain.com/test//"));
        assertFalse(this.urlVal.isValid("http://www.domain.com/test/.."));
        assertFalse(this.urlVal.isValid("http://www.domain.com/test//test2"));
    }

    @Test
    public void testQueryPartition() {
        // Valid queries
        assertTrue(this.urlVal.isValid("http://www.domain.com"));
        assertTrue(this.urlVal.isValid("http://www.domain.com/?"));
        assertTrue(this.urlVal.isValid("http://www.domain.com/?key"));
        assertTrue(this.urlVal.isValid("http://www.domain.com/?key=value"));
        assertTrue(this.urlVal.isValid(
            "http://www.domain.com/?key=value&key2=value2"
        ));
        assertTrue(this.urlVal.isValid("http://www.domain.com/test?key=value"));
        assertTrue(this.urlVal.isValid(
            "http://www.domain.com/test/?key=value"
        ));
        assertTrue(this.urlVal.isValid(
            "http://www.domain.com/test?key=value&key2=value2"
        ));
        assertTrue(this.urlVal.isValid(
            "http://www.domain.com/test/?key=value&key2=value2"
        ));
    }

    @Test
    public void testFragmentPartition() {
        // Valid fragments
        assertTrue(this.urlVal.isValid("http://www.domain.com"));
        assertTrue(this.urlVal.isValid("http://www.domain.com/#"));
        assertTrue(this.urlVal.isValid("http://www.domain.com/#test"));
        assertTrue(this.urlVal.isValid("http://www.domain.com/test#test"));
        assertTrue(this.urlVal.isValid("http://www.domain.com/test/#test"));
        assertTrue(this.urlVal.isValid(
            "http://www.domain.com/test/test2#test"
        ));
    }

    private ResultPair makeScheme(boolean valid) {
        int selector = 0;
        int invalidCase = 4;
        int numCases = 8;
        StringBuilder scheme = new StringBuilder("http:");

        // Select a rule based on provided validity
        if (valid) {
            selector = this.rand.nextInt(invalidCase);
        } else {
            selector = this.rand.nextInt(numCases - invalidCase) + invalidCase;
        }

        switch (selector) {
        case 0:
            // Normal, valid scheme
            return new ResultPair(scheme.toString(), true);
        case 1:
            // Insert number/+/./- within scheme name (not at start or end)
            int offset = this.rand.nextInt(3) + 1;
            scheme.insert(
                offset,
                "0123456789+.-".charAt(this.rand.nextInt(13))
            );
            return new ResultPair(scheme.toString(), true);
        case 2:
            // Decrease length of scheme
            int end = this.rand.nextInt(2);
            scheme.delete(0, end);
            return new ResultPair(scheme.toString(), true);
        case 3:
            // Increase length of scheme (with letters)
            scheme.insert(0, "abcdefghij".substring(this.rand.nextInt(10)));
            return new ResultPair(scheme.toString(), true);
        case 4:
            // Insert number/+/./- at start of scheme name
            scheme.insert(0, "0123456789+.-".charAt(this.rand.nextInt(13)));
            return new ResultPair(scheme.toString(), false);
        case 5:
            // Remove colon
            scheme.deleteCharAt(4);
            return new ResultPair(scheme.toString(), false);
        case 6:
            // Remove scheme name (only a colon)
            scheme.delete(0, 4);
            return new ResultPair(scheme.toString(), false);
        case 7:
            // Fall through to the default (empty scheme)
        default:
            return new ResultPair("", false);
        }
    }

    private ResultPair makeSlashes(boolean valid) {
        int selector = 0;
        int invalidCase = 1;
        int numCases = 4;
        StringBuilder slashes = new StringBuilder("//");

        // Select a rule based on provided validity
        if (valid) {
            selector = this.rand.nextInt(invalidCase);
        } else {
            selector = this.rand.nextInt(numCases - invalidCase) + invalidCase;
        }

        switch (selector) {
        case 0:
            return new ResultPair(slashes.toString(), true);
        case 1:
            // Add a forward slash
            slashes.append("/");
            return new ResultPair(slashes.toString(), false);
        case 2:
            // Remove a forward slash
            slashes.deleteCharAt(slashes.length() - 1);
            return new ResultPair(slashes.toString(), false);
        case 3:
            // Fall through to the default (no slashes)
        default:
            return new ResultPair("", false);
        }
    }

    private ResultPair makeAuthority(boolean valid) {
        int selector = 0;
        int invalidCase = 6;
        int numCases = 11;
        int num = 0;
        boolean b = false;
        StringBuilder hostname = new StringBuilder("domain.com");
        StringBuilder address = new StringBuilder();

        // Select a rule based on provided validity
        if (valid) {
            selector = this.rand.nextInt(invalidCase);
        } else {
            selector = this.rand.nextInt(numCases - invalidCase) + invalidCase;
        }

        switch (selector) {
        case 0:
            // Normal, valid hostname
            return new ResultPair(hostname.toString(), true);
        case 1:
            // Normal, valid hostname, with subdomain
            hostname.insert(0, "www.");
            return new ResultPair(hostname.toString(), true);
        case 2:
            // Hostname with one of the original TLDs
            num = this.rand.nextInt(
                Array.getLength(UrlValidatorTest.ORIG_TLDS)
            );
            hostname.replace(6, 10, UrlValidatorTest.ORIG_TLDS[num]);
            return new ResultPair(hostname.toString(), true);
        case 3:
            // Hostname with one of the valid country code TLDs
            num = this.rand.nextInt(
                Array.getLength(UrlValidatorTest.CC_TLDS)
            );
            hostname.replace(6, 10, UrlValidatorTest.CC_TLDS[num]);
            return new ResultPair(hostname.toString(), true);
        case 4:
            // Prepend username and password for authentication
            hostname.insert(0, "username:password@");
            return new ResultPair(hostname.toString(), true);
        case 5:
            // Create a valid IP address
            for (int i = 0; i < 4; ++i) {
                if (i > 0) {
                    address.append(".");
                }
                address.append(Integer.toString(this.rand.nextInt(256)));
            }
            return new ResultPair(address.toString(), true);
        case 6:
            // Remove hostname (leave only TLD)
            hostname.delete(0, 6);
            return new ResultPair(hostname.toString(), false);
        case 7:
            // Remove TLD
            hostname.delete(6, 10);
            return new ResultPair(hostname.toString(), false);
        case 8:
            // IP address with byte segment(s) above 255
            for (int i = 0; i < 4; ++i) {
                if (i > 0) {
                    address.append(".");
                }

                if (
                    (this.rand.nextInt(4) == 0)
                    || ((i == 3) && (b == false))
                ) {
                    address.append(
                        Integer.toString(this.rand.nextInt(743) + 256)
                    );
                    b = true;
                } else {
                    address.append(Integer.toString(this.rand.nextInt(256)));
                }
            }

            return new ResultPair(address.toString(), false);
        case 9:
            // IP address with wrong number of byte segments
            if (this.rand.nextInt(2) > 0) {
                num = this.rand.nextInt(4);         // Too few
            } else {
                num = this.rand.nextInt(4) + 4;     // Too many
            }

            for (int i = 0; i < num; ++i) {
                if (i > 0) {
                    address.append(".");
                }
                address.append(Integer.toString(this.rand.nextInt(256)));
            }

            return new ResultPair(address.toString(), false);
        case 10:
            // Fall through to the default (no authority)
        default:
            return new ResultPair("", false);
        }
    }

    private ResultPair makePort(boolean valid) {
        int selector = 0;
        int invalidCase = 6;
        int numCases = 10;
        StringBuilder port = new StringBuilder(":");

        // Select a rule based on provided validity
        if (valid) {
            selector = this.rand.nextInt(invalidCase);
        } else {
            selector = this.rand.nextInt(numCases - invalidCase) + invalidCase;
        }

        switch (selector) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            // Port with 1-5 digits that's in range (<= 65535)
            port.append(Integer.toString(this.rand.nextInt(65536)));
            return new ResultPair(port.toString(), true);
        case 5:
            // Use the default (no port)
            return new ResultPair("", true);
        case 6:
            // Port with 5 digits that's out of range (> 65535)
            port.append(Integer.toString(
                this.rand.nextInt(34463) + 65536
            ));
            return new ResultPair(port.toString(), false);
        case 7:
            // Port with 6-9 digits
            port.append(Integer.toString(
                this.rand.nextInt(999899999) + 100000
            ));
            return new ResultPair(port.toString(), false);
        case 8:
            // Negative port number
            port.append(Integer.toString(-this.rand.nextInt(65536)));
            return new ResultPair(port.toString(), false);
        case 9:
            // Port containing letters
            port.append(Integer.toString(this.rand.nextInt(65536)));
            port.insert(this.rand.nextInt(port.length()), "a");
            return new ResultPair(port.toString(), false);
        default:
            return new ResultPair("", true);
        }
    }

    private ResultPair makePath(boolean valid) {
        int selector = 0;
        int invalidCase = 4;
        int numCases = 6;
        StringBuilder path = new StringBuilder("/");

        // Select a rule based on provided validity
        if (valid) {
            selector = this.rand.nextInt(invalidCase);
        } else {
            selector = this.rand.nextInt(numCases - invalidCase) + invalidCase;
        }

        switch (selector) {
        case 0:
            // Path with just a slash
            return new ResultPair(path.toString(), true);
        case 1:
            // Path with one directory
            path.append("asdfgjkl");

            if (this.rand.nextInt(2) > 0) {
                path.append("/");
            }

            return new ResultPair(path.toString(), true);
        case 2:
            // Path with more than one directory and one file
            path.append("asdfghjkl/qwertyuiop");

            if (this.rand.nextInt(2) > 0) {
                path.append("/");
            }

            return new ResultPair(path.toString(), true);
        case 3:
            // Use the default (no path)
            return new ResultPair("/", true);
        case 4:
            // Append an additional leading forward slash
            path.append("/asdfgjkl");
            return new ResultPair(path.toString(), false);
        case 5:
            // Path with multiple directories and a double forward slash within
            path.append("asdfghjkl//qwertyuiop/zxcvbnm");
            return new ResultPair(path.toString(), false);
        default:
            return new ResultPair("/", true);
        }
    }

    private ResultPair makeQuery(boolean valid) {
        int selector = 0;
        int numCases = 4;
        StringBuilder query = new StringBuilder("?");

        // Note: All cases are currently valid, so we just randomly select one
        selector = this.rand.nextInt(numCases);

        switch (selector) {
        case 0:
            // Query without any key/value pairs
            return new ResultPair(query.toString(), true);
        case 1:
            // Query with one key and, maybe, a value
            query.append("key");

            if (this.rand.nextInt(2) > 0) {
                query.append("=value");
            }

            return new ResultPair(query.toString(), true);
        case 2:
            // Query with more than one keys and, maybe, values
            for (int i = 1, len = (this.rand.nextInt(3) + 2); i <= len; ++i) {
                if (i > 1) {
                    query.append("&");
                }
                query.append("key" + Integer.toString(i));

                if (this.rand.nextInt(2) > 0) {
                    query.append("=value" + Integer.toString(i));
                }

                return new ResultPair(query.toString(), true);
            }
        case 3:
            // Fall through to the default (no query)
        default:
            return new ResultPair("", true);
        }
    }

    private ResultPair makeFragment(boolean valid) {
        int selector = 0;
        int numCases = 3;
        StringBuilder fragment = new StringBuilder("#");

        // Note: All cases are currently valid, so we just randomly select one
        selector = this.rand.nextInt(numCases);

        switch (selector) {
        case 0:
            // Fragment with only a hash mark
            return new ResultPair(fragment.toString(), true);
        case 1:
            // Fragment with a hash mark and fragment name
            fragment.append("test");
            return new ResultPair(fragment.toString(), true);
        case 2:
            // Fall through to the default (no fragment)
        default:
            return new ResultPair("", true);
        }
    }

    /**
     * Create a URL using randomly-selected rules for each URL part.
     * @return ResultPair of created URL or empty string (no more URLs)
     */
    private ResultPair makeUrl() {
        // Determine whether to make a valid or invalid URL
        boolean valid = this.rand.nextInt(2) == 0;

        // Make the various URL parts (either definitely valid or 90% invalid)
        ResultPair scheme = makeScheme(
            (valid) ? true : (this.rand.nextInt(3) == 0)
        );
        ResultPair slashes = makeSlashes(
            (valid) ? true : (this.rand.nextInt(3) == 0)
        );
        ResultPair authority = makeAuthority(
            (valid) ? true : (this.rand.nextInt(3) == 0)
        );
        ResultPair port = makePort(
            (valid) ? true : (this.rand.nextInt(3) == 0)
        );
        ResultPair path = makePath(
            (valid) ? true : (this.rand.nextInt(3) == 0)
        );
        ResultPair query = makeQuery(
            (valid) ? true : (this.rand.nextInt(3) == 0)
        );
        ResultPair fragment = makeFragment(
            (valid) ? true : (this.rand.nextInt(3) == 0)
        );


        // Make the URL string from the parts
        String url = scheme.item + slashes.item + authority.item + port.item
            + path.item + query.item + fragment.item;

        if (!valid) {
            // Compute if an invalid URL is actually invalid based on the parts
            valid = scheme.valid && slashes.valid && authority.valid
                && port.valid && path.valid && query.valid && fragment.valid;
        }

        return new ResultPair(url, valid);
    }

    @Test
    public void testIsValid() {
        if (!UrlValidatorTest.RUN_TESTISVALID) {
            return;     // Skip the test if the RUN_TESTISVALID flag is false
        }

        boolean result;
        ResultPair url;

        // Test created URLs
        for (int i = 0; i < 10000; ++i) {
            url = makeUrl();    // Create the URL to test

            // Test validity of URL and compare to expected result
            result = this.urlVal.isValid(url.item);

            if (UrlValidatorTest.PRINT_INVALID) {
                // Print URL and expected/observed validity for bad URLs
                if (result != url.valid) {
                    System.out.printf(
                        "expected: %b\tobserved: %b\t\t%s\n",
                        url.valid,
                        result,
                        url.item
                    );
                }
            } else {
                // Ensure the expected/observed validity matches
                assertEquals(result, url.valid);
            }
        }
    }
}
