import java.util.Random;

/**
 * Created by Robert on 3/10/2016.
 * adapted / stolen from http://stackoverflow.com/questions/41107/how-to-generate-a-random-alpha-numeric-string
 */
public class RandomString {

    private static final char[] symbols;
    private static final char[] unresSymbols;
    private static final char[] aSymbols;

    //ASCII
    static {
        StringBuilder tmp = new StringBuilder();
        for (char ch = '0'; ch <= '9'; ++ch)
            tmp.append(ch);
        for (char ch = 'a'; ch <= 'z'; ++ch)
            tmp.append(ch);

        char[] chars = "/{}\\!@#$%^&*()-+=~`;':\"|,.<>/?".toCharArray();
        tmp.append(chars);

        symbols = tmp.toString().toCharArray();
    }


    //Path subset
    static {
        StringBuilder tmp = new StringBuilder();
        for (char ch = '0'; ch <= '9'; ++ch)
            tmp.append(ch);
        for (char ch = 'a'; ch <= 'z'; ++ch)
            tmp.append(ch);

        //UNreserved PATH characters only (i.e. those not requiring escaping)
        char[] chars = "-~_".toCharArray();
        tmp.append(chars);

        unresSymbols = tmp.toString().toCharArray();
    }

    //Query subset
    static {
        StringBuilder tmp = new StringBuilder();
        for (char ch = '0'; ch <= '9'; ++ch)
            tmp.append(ch);
        for (char ch = 'a'; ch <= 'z'; ++ch)
            tmp.append(ch);

        aSymbols = tmp.toString().toCharArray();
    }


    private final Random random = new Random();

    private final char[] buf;

    public RandomString(int length) {
        if (length < 1)
            throw new IllegalArgumentException("length < 1: " + length);
        buf = new char[length];
    }

    public String nextString() {
        for (int idx = 0; idx < buf.length; ++idx)
            buf[idx] = symbols[random.nextInt(symbols.length)];
        return new String(buf);
    }

    public String unresString() {
        for (int idx = 0; idx < buf.length; ++idx)
            buf[idx] = unresSymbols[random.nextInt(unresSymbols.length)];
        return new String(buf);
    }

    public String aString() {
        for (int idx = 0; idx < buf.length; ++idx)
            buf[idx] = aSymbols[random.nextInt(aSymbols.length)];
        return new String(buf);
    }

}
