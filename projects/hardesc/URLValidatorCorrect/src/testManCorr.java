

public class testManCorr {

   
   public static void main(String[] args) {
      UrlValidator uv = new UrlValidator();
      if (args.length != 1) {
         System.out.println("ERROR: invalid number of arguments");
      }
      System.out.println(uv.isValid(args[0]));
   }

}
