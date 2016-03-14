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
import static org.junit.Assert.assertEquals;
import java.util.Random;
import java.util.regex.Pattern;
import java.lang.reflect.Array;

/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */
public class UrlValidatorTest {
    private Random rnd = new Random();

    private UrlValidator urlVal = new UrlValidator(
        null,
        null,
        UrlValidator.ALLOW_ALL_SCHEMES
    );

    private static final boolean PRINT_ALL = false;
    private static final boolean PRINT_INVALID = true;
    private static final boolean PRINT_PART_DEBUG = false;
    private static final boolean STATISTICS = false;

    private static final String SCHEME_CHARS
        = "abcdefghijklmnopqrstuvwxyz0123456789+.-";

    private static final String AUTHORITY_CHARS
        = "abcdefghijklmnopqrstuvwxyz0123456789-";

    private static final String PATH_CHARS
        = "abcdefghijklmnopqrstuvwxyz0123456789+.-";

    private static final String QUERY_CHARS
        = "abcdefghijklmnopqrstuvwxyz0123456789";

    private static final String FRAGMENT_CHARS
        = "abcdefghijklmnopqrstuvwxyz0123456789-_";

    private static final Pattern SCHEME_PATTERN = Pattern.compile(
        "^[a-z][a-z0-9\\+\\.\\-]*?:\\/\\/$",
        Pattern.CASE_INSENSITIVE
    );
    
    private static final Pattern HOSTNAME_PATTERN = Pattern.compile(
        "^[a-z0-9][a-z0-9-]*(\\.[a-z0-9][a-z0-9-]*){1,}$",
        Pattern.CASE_INSENSITIVE
    );

    private static final Pattern PORT_PATTERN = Pattern.compile(
        "^(?::(?:(?:\\d)|(?:[1-9]\\d{1,4})))?$"
    );

    private static final Pattern PATH_PATTERN = Pattern.compile(
        "^\\/[a-z0-9+\\.\\-\\/]*$",
        Pattern.CASE_INSENSITIVE
    );

    private static final Pattern QUERY_PATTERN = Pattern.compile(
        "^\\??(?:[^=&\\?]+(?:=[^&\\?]+)?(?:&[^=&\\?]+(?:=[^&\\?]+)?)*)?$"
    );

    private static final Pattern FRAGMENT_PATTERN = Pattern.compile(
        "^#[a-z0-9_=,&\\-\\*\\(\\)\\/]*?$",
        Pattern.CASE_INSENSITIVE
    );

    private static final String[] TLDS = { "com", "org", "net", "int", "edu",
        "gov", "mil", "arpa", "ac", "ad", "ae", "af", "ag", "ai", "al", "am",
        "an", "ao", "aq", "ar", "as", "at", "au", "aw", "ax", "az", "ba", "bb",
        "bd", "be", "bf", "bg", "bh", "bi", "bj", "bm", "bn", "bo", "bq", "br",
        "bs", "bt", "bv", "bw", "by", "bz", "ca", "cc", "cd", "cf", "cg", "ch",
        "ci", "ck", "cl", "cm", "cn", "co", "cr", "cu", "cv", "cw", "cx", "cy",
        "cz", "de", "dj", "dk", "dm", "do", "dz", "ec", "ee", "eg", "eh", "er",
        "es", "et", "eu", "fi", "fj", "fk", "fm", "fo", "fr", "ga", "gb", "gd",
        "ge", "gf", "gg", "gh", "gi", "gl", "gm", "gn", "gp", "gq", "gr", "gs",
        "gt", "gu", "gw", "gy", "hk", "hm", "hn", "hr", "ht", "hu", "id", "ie",
        "il", "im", "in", "io", "iq", "ir", "is", "it", "je", "jm", "jo", "jp",
        "ke", "kg", "kh", "ki", "km", "kn", "kp", "kr", "kw", "ky", "kz", "la",
        "lb", "lc", "li", "lk", "lr", "ls", "lt", "lu", "lv", "ly", "ma", "mc",
        "md", "me", "mg", "mh", "mk", "ml", "mm", "mn", "mo", "mp", "mq", "mr",
        "ms", "mt", "mu", "mv", "mw", "mx", "my", "mz", "na", "nc", "ne", "nf",
        "ng", "ni", "nl", "no", "np", "nr", "nu", "nz", "om", "pa", "pe", "pf",
        "pg", "ph", "pk", "pl", "pm", "pn", "pr", "ps", "pt", "pw", "py", "qa",
        "re", "ro", "rs", "ru", "rw", "sa", "sb", "sc", "sd", "se", "sg", "sh",
        "si", "sj", "sk", "sl", "sm", "sn", "so", "sr", "ss", "st", "su", "sv",
        "sx", "sy", "sz", "tc", "td", "tf", "tg", "th", "tj", "tk", "tl", "tm",
        "tn", "to", "tp", "tr", "tt", "tv", "tw", "tz", "ua", "ug", "uk", "us",
        "uy", "uz", "va", "vc", "ve", "vg", "vi", "vn", "vu", "wf", "ws", "ye",
        "yt", "za", "zm", "zw" };

    /**
     * Generate a random scheme that's potentially valid or invalid.
     * A scheme is described as "a sequence of characters beginning with a
     * letter and followed by any combination of letters, digits, plus (+),
     * period (.), or hyphen (-)."
     * @return a ResultPair object, including the scheme and validity
     */
    private ResultPair generateRandomScheme() {
        StringBuilder schemeBuild = new StringBuilder();

        // 98% chance having a scheme
        int length = 0;
        if (this.rnd.nextInt(50) > 0) {
            length = this.rnd.nextInt(15) + 1;
        }

        if (length > 0) {
            // 98% chance of starting the scheme with a letter
            if (this.rnd.nextInt(50) > 0) {
                schemeBuild.append(SCHEME_CHARS.charAt(
                    this.rnd.nextInt(26)
                ));
            }
        }

        for (int i = 1; i < length; i++) {
            // Randomly populate the scheme with valid characters
            schemeBuild.append(SCHEME_CHARS.charAt(
                this.rnd.nextInt(SCHEME_CHARS.length())
            ));
        }

        // 98% chance of adding a trailing colon to the scheme
        if (this.rnd.nextInt(50) > 0) {
            schemeBuild.append(":");
        }
        
        // 98% chance of appending trailing slashes
        if (this.rnd.nextInt(50) > 0) {
            schemeBuild.append("//");
        }

        // Return ResultPair for scheme
        String schemeStr = schemeBuild.toString();
        return new ResultPair(
            schemeStr,
            SCHEME_PATTERN.matcher(schemeStr).matches()
        );
    }

    private ResultPair generateRandomAuthority() {
        StringBuilder authorityBuild = new StringBuilder();
        boolean validity = true;
        boolean hostname = false;

        // 98% chance having an authority
        int length = 0;
        if (this.rnd.nextInt(50) > 0) {
            length = this.rnd.nextInt(25) + 1;
        }

        // 66% chance of generating a host name
        if (this.rnd.nextInt(3) > 0) {
            hostname = true;

            for (int i = 0; i < length; ++i) {
                // 5% chance of adding a dot (creating sub-domains, etc.)
                if (this.rnd.nextInt(20) > 0) {
                 // Randomly populate the scheme with valid characters
                    authorityBuild.append(AUTHORITY_CHARS.charAt(
                        this.rnd.nextInt(AUTHORITY_CHARS.length())
                    ));
                } else {
                    authorityBuild.append(".");
                }
            }

            // 95% chance of using a valid TLD (vs. something random)
            authorityBuild.append(".");
            if (this.rnd.nextInt(20) > 0) {
                // Add a random TLD from the TLDS array
                authorityBuild.append(
                    TLDS[this.rnd.nextInt(Array.getLength(TLDS))]
                );
            } else {
                // Create a random, probably invalid TLD
                for (int i = 0, tldLn = this.rnd.nextInt(3); i < tldLn; ++i) {
                    authorityBuild.append(AUTHORITY_CHARS.charAt(
                        this.rnd.nextInt(AUTHORITY_CHARS.length())
                    ));
                }
                validity = false;   // Assume the generated TLD's invalid
            }
        } else {
            // 98% chance of generating a valid IP address
            if (this.rnd.nextInt(50) > 0) {
                for (int i = 0; i < 4; ++i) {
                    if (i != 0) {
                        authorityBuild.append(".");
                    }

                    authorityBuild.append(
                        Integer.toString(this.rnd.nextInt(256))
                    );
                }
            } else {
                // Create a random, likely invalid, IP address
                for (int i = 0; i < length; ++i) {
                    // 75% chance of adding a digit
                    if (this.rnd.nextInt(10) > 0) {
                        authorityBuild.append(
                            Integer.toString(this.rnd.nextInt(10))
                        );
                    } else {
                        // Add a dot
                        authorityBuild.append(".");
                    }
                }
                validity = false;
            }
        }
        
        String authorityStr = authorityBuild.toString();
        if (validity == true) {
            // Check if the authority contains double dots
            validity &= !authorityStr.matches(".*\\.\\..*");
            
            if (hostname) {
                validity &= UrlValidatorTest.HOSTNAME_PATTERN
                    .matcher(authorityStr).matches();
            }
        }

        return new ResultPair(authorityStr, validity);
    }

    private ResultPair generateRandomPort() {
        StringBuilder portBuild = new StringBuilder();
        boolean validity = true;

        // 98% chance having a port
        int length = 0;
        if (this.rnd.nextInt(50) > 0) {
            // 95% chance of generating a port of length 6 or less
            if (this.rnd.nextInt(20) > 0) {
                length = this.rnd.nextInt(6) + 1;
            } else {
                length = this.rnd.nextInt(8) + 1;
            }
        }

        // Generate the port number (if any)
        for (int i = 0; i < length; ++i) {
            // 2% chance of starting the port with zero
            if ((i == 0) && (this.rnd.nextInt(50) == 0)) {
                portBuild.append("0");
            } else {
                portBuild.append(
                    Integer.toString(this.rnd.nextInt(10))
                );
            }
        }

        // Check if the port is in range (where appropriate)
        if ((length > 1)) {
            int portInt = Integer.parseInt(portBuild.toString());
            validity &= (portInt >= 0) && (portInt <= 65535);
        }

        // 98% chance of adding a leading colon
        if (this.rnd.nextInt(50) > 0) {
            portBuild.insert(0, ":");
        }

        // Return ResultPair for scheme
        String portStr = portBuild.toString();
        return new ResultPair(
            portStr,
            PORT_PATTERN.matcher(portStr).matches()
                && validity
        );
    }

    private ResultPair generateRandomPath() {
        StringBuilder pathBuild = new StringBuilder();
        boolean validity = true;

        // 95% chance having path text
        int length = 0;
        if (this.rnd.nextInt(50) > 0) {
            length = this.rnd.nextInt(30) + 1;
        }

        // 98% chance of adding a leading forward slash
        if (this.rnd.nextInt(50) > 0) {
            pathBuild.append("/");
        }

        // Populate path with directory/file names
        for (int i = 0; i < length; ++i) {
            // 95% chance of appending a letter
            if (this.rnd.nextInt(20) > 0) {
                pathBuild.append(PATH_CHARS.charAt(
                    this.rnd.nextInt(PATH_CHARS.length())
                ));
            } else {
                // Append a forward slash
                pathBuild.append("/");
            }
        }

        // 10% chance of adding a trailing forward slash
        if (this.rnd.nextInt(10) == 0) {
            pathBuild.append("/");
        }

        String pathStr = pathBuild.toString();
        if (pathStr.length() > 0) {
            validity &= PATH_PATTERN.matcher(pathStr).matches()
                && !pathStr.matches(".*\\/\\/.*");
        }

        return new ResultPair(pathStr, validity);
    }

    private ResultPair generateRandomQuery() {
        StringBuilder queryBuild = new StringBuilder();

        // 95% chance of having more than one key/value pair
        int numParts = 0;
        if (this.rnd.nextInt(20) > 0) {
            numParts = this.rnd.nextInt(5) + 1;
        }

        // 98% chance of adding a leading question mark
        if (this.rnd.nextInt(50) > 0) {
            queryBuild.append("?");
        }

        for (int i = 0; i < numParts; ++i) {
            // > 95% chance of adding an ampersand between key/value pairs
            if ((i > 0) && (this.rnd.nextInt(25) > 0)) {
                queryBuild.append("&");
            }

            // Generate a random key
            int strLength = this.rnd.nextInt(10) + 1;
            for (int j = 0; j < strLength; ++j) {
                queryBuild.append(QUERY_CHARS.charAt(
                    this.rnd.nextInt(QUERY_CHARS.length())
                ));
            }

            // 75% chance of having a value
            if (this.rnd.nextInt(4) > 0) {
                queryBuild.append("=");

                strLength = this.rnd.nextInt(15) + 1;
                for (int j = 0; j < strLength; ++j) {
                    queryBuild.append(QUERY_CHARS.charAt(
                        this.rnd.nextInt(QUERY_CHARS.length())
                    ));
                }
            }
        }

        String queryStr = queryBuild.toString();
        return new ResultPair(
            queryStr,
            QUERY_PATTERN.matcher(queryStr).matches()
        );
    }

    private ResultPair generateRandomFragment() {
        int length = this.rnd.nextInt(15);
        StringBuilder fragmentBuild = new StringBuilder();
        boolean validity = true;

        // 95% chance of adding a leading octothorpe
        if (this.rnd.nextInt(20) > 0) {
            fragmentBuild.append("#");
        }

        // Create the fragment text
        for (int i = 0; i < length; ++i) {
            fragmentBuild.append(FRAGMENT_CHARS.charAt(
                this.rnd.nextInt(FRAGMENT_CHARS.length())
            ));
        }

        String fragmentStr = fragmentBuild.toString();
        // NOTE: It's probably safe to just assume that the fragment is valid
        // if (fragmentStr.length() > 0) {
        //     // Verify the fragment if it's not empty
        //     validity &= FRAGMENT_PATTERN.matcher(fragmentStr).matches();
        // }

        return new ResultPair(fragmentStr, validity);
    }

    /**
     * Generate a URL using randomly-generated parts.
     * @return ResultPair object including the URL and validity
     */
    private ResultPair generateRandomUrl() {
        StringBuilder urlBuild = new StringBuilder();
        boolean validity = true;

        // Generate the random URL parts
        ResultPair scheme = generateRandomScheme();
        ResultPair authority = generateRandomAuthority();
        ResultPair port = generateRandomPort();
        ResultPair path = generateRandomPath();
        ResultPair query = generateRandomQuery();
        ResultPair fragment = generateRandomFragment();

        // Build the URL from the generated parts
        urlBuild.append(scheme.item)
            .append(authority.item)
            .append(port.item)
            .append(path.item)
            .append(query.item)
            .append(fragment.item);

        // Calculate the validity of the URL from the parts
        validity &= scheme.valid
            & authority.valid
            & port.valid
            & path.valid
            & query.valid
            & fragment.valid;

        if (UrlValidatorTest.PRINT_PART_DEBUG && validity == false) {
            System.out.printf(
                "s:%b a:%b po:%b pa:%b q:%b f:%b\n",
                scheme.valid,
                authority.valid,
                port.valid,
                path.valid,
                query.valid,
                fragment.valid
            );
        }

        return new ResultPair(urlBuild.toString(), validity);
    }

    @Test
    public void randomTestIsValid() {
        boolean result;
        int tt = 0;
        int tf = 0;
        int ft = 0;
        int ff = 0;

        // Test URLs composed of randomly generated parts
        for (int i = 0; i < 1000; ++i) {
            // Create the URL of randomly-generated parts
            ResultPair url = generateRandomUrl();

            // Test the validity of the generated URL
            result = this.urlVal.isValid(url.item);

            // Collect expected vs. observed statistics, if desired
            if (UrlValidatorTest.STATISTICS) {
                if (url.valid == true && result == true) {
                    tt += 1;
                } else if (url.valid == true && result == false) {
                    tf += 1;
                } else if (url.valid == false && result == true) {
                    ft += 1;
                } else if (url.valid == false && result == false) {
                    ff += 1;
                }
            }

            // Output the result or assert
            if (
                UrlValidatorTest.PRINT_ALL
                || (UrlValidatorTest.PRINT_INVALID && (result != url.valid))
            ) {
                System.out.printf(
                    "expected: %b\tobserved: %b\t\t%s\n",
                    url.valid,
                    result,
                    url.item
                );
                continue;
            } else {
                // Ensure the expected/observed validity matches
                assertEquals(result, url.valid);
            }
        }

        // Print the collected expected vs. observed statistics, if desired
        if (UrlValidatorTest.STATISTICS) {
            System.out.printf(
                "\nTT: %d\tTF: %d\tFT: %d\tFF: %d\n",
                tt, tf, ft, ff
            );
        }
    }
}
