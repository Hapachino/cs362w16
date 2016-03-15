import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ThreadLocalRandom;

/**
 * Created by Robert on 3/12/2016.
 */
public class HelpFunctions {

        //Helper functions http://stackoverflow.com/questions/285712/java-reading-a-file-into-an-array
        public List<String> readLines(String filename) throws IOException {

            FileReader fileReader = new FileReader(filename);
            BufferedReader bufferedReader = new BufferedReader(fileReader);
            List<String> lines = new ArrayList<String>();
            String line = null;

            while ((line = bufferedReader.readLine()) != null) {
                lines.add(line);
            }

            bufferedReader.close();
            //return lines.toArray(new String[lines.size()]);
            return lines;
        }

        public List<String> makeIP(int n){

            List<String> ipList = new ArrayList<String>();

            for(int j = 0; j < n; j++){
                String ip =null;

                for (int i = 0; i < 4; i++) {

                    int rand = ThreadLocalRandom.current().nextInt(0, 254);
                    if (ip == null) {
                        ip = String.valueOf(rand);
                    } else if (ip != null) {
                        ip += "." + String.valueOf(rand) ;
                    }
                }

                ipList.add(ip);
            }

            return ipList;
        };

    public String makeIP(){

            String ip =null;

            for (int i = 0; i < 4; i++) {

                int rand = ThreadLocalRandom.current().nextInt(0, 254);
                if (ip == null) {
                    ip = String.valueOf(rand);
                } else if (ip != null) {
                    ip += "." + String.valueOf(rand);
                }
            }

            return ip;
        }


        //generates a path using unreserver characters (i.e. those not requiring escaping)
        //@param n (how many to make)
        public List<String> makePath(int n){

            List<String> pathList = new ArrayList<String>();
            RandomString rnd;

            for(int j = 0; j < n; j++){
                String path = null;
                int rand =0;

                //vary the length of the path
                int plength = ThreadLocalRandom.current().nextInt(1, 5);
                for(int i = 0 ; i < plength; i++) {

                    //vary the length of the part
                    rand = ThreadLocalRandom.current().nextInt(1, 10); // 1- 10 characters long
                    rnd = new RandomString(rand);

                    //construct the path
                    if (path == null) {
                        path = String.valueOf(rnd.unresString());

                    } else  {
                        path += "/" + String.valueOf(rnd.unresString());
                    }
                }

                //sometimes add a file name
                if (rand%2 == 1){
                    rnd = new RandomString(2);
                    path += "/SomeFileName." + rnd.unresString();

                }
                //sometimes add a trailing slash
                if (rand%2 == 0){

                    path += "/";
                }
                pathList.add(path);
            }

            return pathList;
        };


        //generates a path using unreserver characters (i.e. those not requiring escaping)
        //@param n (how many to make)
        public String makePath(){

            RandomString rnd;

            String path = null;
            int rand =0;

            //vary the length of the path
            int plength = ThreadLocalRandom.current().nextInt(1, 5);
            for(int i = 0 ; i < plength; i++) {

                //vary the length of the part
                rand = ThreadLocalRandom.current().nextInt(1, 10); // 1- 10 characters long
                rnd = new RandomString(rand);

                //construct the path
                if (path == null) {
                    path = String.valueOf(rnd.unresString());

                } else  {
                    path += "/" + String.valueOf(rnd.unresString());
                }
            }


            //sometimes add a file name
            if (rand%2 == 1){
                rnd = new RandomString(2);
                path += "/SomeFileName." + rnd.unresString();

            }
            //sometimes add a trailing slash
            if (rand%2 == 0){

                path += "/";
            }

            return path;
        };


        //generates a path using unreserver characters (i.e. those not requiring escaping)
        //@param n (how many to make)
        public List<String> makeQuery(int n){

            List<String> queryList = new ArrayList<String>();
            RandomString rnd, rndd;

            for(int j = 0; j < n; j++){
                String q = null;
                int rand =0;
                int rand2 =0;

                //vary the length of the query
                int qlength = ThreadLocalRandom.current().nextInt(1, 5);
                for(int i = 0 ; i < qlength; i++) {

                    //vary the length of the part
                    rand = ThreadLocalRandom.current().nextInt(1, 10); // 1- 10 characters long
                    rand2 = ThreadLocalRandom.current().nextInt(1, 10); // 1- 10 characters long
                    rnd = new RandomString(rand);
                    rndd = new RandomString(rand2); //different length variable value pairs

                    //construct the path
                    if (q == null) {
                        q = String.valueOf(rnd.aString()) + "=" + String.valueOf(rndd.aString());

                    } else  {
                        q += "&"+ String.valueOf(rnd.aString()) + "=" + String.valueOf(rndd.aString());
                    }

                }
                queryList.add(q);

            }

            return queryList;
        };

        //generates a path using unreserver characters (i.e. those not requiring escaping)
        //@param n (how many to make)
        public String makeQuery(){

            RandomString rnd, rndd;

            String q = null;
            int rand =0;
            int rand2 =0;

            //vary the length of the query
            int qlength = ThreadLocalRandom.current().nextInt(1, 5);
            for(int i = 0 ; i < qlength; i++) {

                //vary the length of the part
                rand = ThreadLocalRandom.current().nextInt(1, 10); // 1- 10 characters long
                rand2 = ThreadLocalRandom.current().nextInt(1, 10); // 1- 10 characters long
                rnd = new RandomString(rand);
                rndd = new RandomString(rand2); //different length variable value pairs

                //construct the path
                if (q == null) {
                    q = String.valueOf(rnd.aString()) + "=" + String.valueOf(rndd.aString());

                } else  {
                    q += "&"+ String.valueOf(rnd.aString()) + "=" + String.valueOf(rndd.aString());
                }

            }

            return q;
        }


        //Gets a Random Protocol from a List
        //@param n (how many to make)
        public String getRandomProtocol(){

            List<String>  protocolList =  new ArrayList<String>();

            String protocol = null;

            //loads a list of valid Authorities from RFC http://www.iana.org/assignments/uri-schemes/uri-schemes.xhtml
            String fileName = "src" + File.separator + "validProtocols.txt";
            try {

                protocolList = this.readLines(fileName);

                //convert to Array for random Access
                String[] protocolArray = protocolList.toArray(new String[protocolList.size()]);

                //picks one at random
                int randNum = ThreadLocalRandom.current().nextInt(0, protocolList.size()-1);
                return protocolArray[randNum];

            }catch(IOException ex){
                System.out.println (ex.toString());
                System.out.println("Could not find file " + fileName);
                return null;
            }


        };

    public String makeValidDomain(){
        List<String>  domainList =  new ArrayList<String>();

        String tld = null;
        String domain;


        //loads a list of valid Authorities from RFC http://www.iana.org/assignments/uri-schemes/uri-schemes.xhtml
        String domainFile = "src" + File.separator + "validTLDs.txt";

        try {

            domainList = this.readLines(domainFile);

            //convert to Array for random Access
            String[] domainArray = domainList.toArray(new String[domainList.size()]);

            //picks one at random
            int randNum = ThreadLocalRandom.current().nextInt(0, domainList.size()-1);

            //ToDo Add possibility of sub domains and localhost/localdomain

            return domainArray[randNum];

        }catch(IOException ex){
            System.out.println (ex.toString());
            System.out.println("Could not find file " );
            return null;
        }


    }
    //SAME as above only returns a list
    public List<String> makeValidTLDList(){
        List<String>  domainList =  new ArrayList<String>();

        String tld = null;
        String domain;


        //loads a list of valid Authorities from RFC http://www.iana.org/assignments/uri-schemes/uri-schemes.xhtml
        String domainFile = "src" + File.separator + "validTLDs.txt";

        try {

             domainList = this.readLines(domainFile);


        }catch(IOException ex){
            System.out.println (ex.toString());
            System.out.println("Could not find file " );
            return null;
        }
        return domainList;

    }

}
