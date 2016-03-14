   public void testManualTest()
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
       
       System.out.println("http://www.facebook.com is valid? " + urlVal.isValid("http://www.facebook.com"));
       assertTrue(urlVal.isValid("http://www.facebook.com"));
       
       System.out.println("http://www.123456.com is valid? " + urlVal.isValid("http://www.123456.com"));
       assertTrue(urlVal.isValid("http://www.123456.com"));
       
       System.out.println("http://www.website.com/inner is valid? " + urlVal.isValid("http://www.website.com/inner"));
       assertTrue(urlVal.isValid("http://www.website.com/inner"));
       
       System.out.println("http://www.www.com is valid? " + urlVal.isValid("http://www.www.com"));
       assertTrue(urlVal.isValid("http://www.www.com"));
       
       //this should be true
       System.out.println("http://www.website.com/inner?name=Ted is valid? " + urlVal.isValid("http://www.website.com/inner?name=Ted"));
       assertTrue(urlVal.isValid("http://www.website.com/inner?name=Ted"));
       
       System.out.println("https://www.secure.com is valid? " + urlVal.isValid("https://www.secure.com"));
       assertTrue(urlVal.isValid("https://www.secure.com"));
       
       //this should be true
       System.out.println("http://join.me is valid? " + urlVal.isValid("http://join.me"));
       assertTrue(urlVal.isValid("http://join.me"));
       
       System.out.println("asdf://www.sdfgsdfg.me is valid? " + urlVal.isValid("asdf://www.sdfgsdfg.me"));
       assertFalse(urlVal.isValid("asdf://www.sdfgsdfg.me"));
       
          
   }
   

   
   /*
   URL will be grouped into schemes, host, subdomain, top-level domain,
   second-level domain, port, URL-path, and URL-parameters partitions. One property
   from each partition will be tested.

   Default URL for testing:
   http://www.google.com

   URL = {set of all strings}
   */
   
   public void testYourFirstPartition()
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   //URL1(Schemes) = {ftp, http, gopher, mailto, news, nntp, telnet, wais, file, prospero ...}
	   assertTrue("http://www.google.com - Should be TRUE",
			   urlVal.isValid("http://www.google.com"));
	   assertFalse("*fds3://www.google.com - Should be FALSE",
			   urlVal.isValid("*fds3://www.google.com"));
   }
   
   public void testYourSecondPartition(){
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   //URL2(Host) = {http://www.espn.com, http://www.ign.com, http://www.google.com, http://www.foxnews.com, http://www.cnn.com, http://www.cat.com ...}
	   assertTrue("http://www.espn.com - Should be TRUE",
			   urlVal.isValid("http://www.espn.com"));
	   assertFalse("http://www.?.com - Should be FALSE",
			   urlVal.isValid("http://www.?.com"));
   }
   
   public void testYourThirdPartition(){
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   //URL3(Subdomain) = {http://go.espn.com, http://mail.google.com, http://youtube.google.com, http://cats.foxnews.com, http://dogs.cnn.com ...}
	   assertTrue("http://mail.google.com - Should be TRUE",
			   urlVal.isValid("http://mail.google.com"));
	   assertFalse("http://?.google.com - Should be FALSE",
			   urlVal.isValid("http://?.google.com"));
   }
   
   public void testYourFourthPartition(){
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   //URL4(Top-level Domain) = {http://go.espn.biz, http://www.google.me, http://youtube.google.xyz, http://cats.foxnews.football, http://dogs.cnn.fitness ...}
	   assertTrue("http://www.google.me - Should be TRUE",
			   urlVal.isValid("http://www.google.me"));
	   assertFalse("http://www.google.? - Should be FALSE",
			   urlVal.isValid("http://www.google.?"));
   }
   
   public void testYourFifthPartition(){
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   //URL5(Second-level Domain) = {http://go.espn.biz.uk, http://www.google.com.su, http://youtube.google.xyz.eu, http://cats.foxnews.football.ac, http://dogs.cnn.fitness.at ...}
	   assertTrue("http://www.google.com.su - Should be TRUE",
			   urlVal.isValid("http://www.google.com.su"));
	   assertFalse("http://www.google.?.su - Should be FALSE",
			   urlVal.isValid("http://www.google.?.su"));
   }
   
   public void testYourSixthPartition(){
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   //URL6(Port) = {http://www.google.com:1, http://www.google.com:10, http://www.google.com:100 ...}
	   assertTrue("http://www.google.com:10 - Should be TRUE",
			   urlVal.isValid("http://www.google.com:10"));
	   assertFalse("http://www.google.com:^ - Should be FALSE",
			   urlVal.isValid("http://www.google.com:^"));
   }
   
   public void testYourSeventhPartition(){
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   //URL7(URL-Path) = {http://www.google.com/test1, http://www.google.com/test2, http://www.google.com/test3 ...}
	   assertTrue("http://www.google.com/test1 - Should be TRUE",
			   urlVal.isValid("http://www.google.com/test1"));
	   assertFalse("http://www.google.com/*&^% - Should be FALSE",
			   urlVal.isValid("http://www.google.com/*&^%"));
   }
   
   public void testYourEighthPartition(){
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   //URL8(URL-Parameters) = {http://www.google.com/test1?t=one, http://www.google.com/test2?t=two, http://www.google.com/test3?t=three ...}
	   assertTrue("http://www.google.com/test1?t=one - Should be TRUE",
			   urlVal.isValid("http://www.google.com/test1?t=one"));
	   assertFalse("http://www.google.com/test1?t=@@@@@@ - Should be FALSE",
			   urlVal.isValid("http://www.google.com/test1?t=@@@@@@"));
   }