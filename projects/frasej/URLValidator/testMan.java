

public class testMan {

   
   public static void main(String[] args) {
      UrlValidatorTest uvt = new UrlValidatorTest("testy");
      if (args.length != 1) {
         System.out.println("ERROR: invalid number of arguments");
      }
      uvt.testManualTest(args[0]);
   }

}
