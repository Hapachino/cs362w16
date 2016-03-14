// import junit.framework.TestCase;

// import java.io.PrintWriter;
// import java.io.File;
import java.io.*;
import java.util.Random;

public class randomTesting {
	public static void main(String[] args) throws FileNotFoundException {
		// PrintWriter outFile = new PrintWriter("urlResults.txt", "UTF-8");
		// File fName = new File("urlResults.txt");
		// PrintWriter outFile = new PrintWriter(fName);
		PrintWriter outFile = new PrintWriter("urlRandomResults.txt");
		UrlValidator urlVal = new UrlValidator();

		boolean stillRun = true;

		long testSeed = System.currentTimeMillis();

		Random randNums = new Random(testSeed);

		outFile.println("Test Seed: " + testSeed);
		outFile.println();

		while  (stillRun == true) {
			int protVal = randNums.nextInt(protocol.length);
			int subVal = randNums.nextInt(subdomain.length);
			int domVal = randNums.nextInt(domain.length);
			int portVal = randNums.nextInt(port.length);
			int pathVal = randNums.nextInt(path.length);
			int qVal = randNums.nextInt(query.length);
			int fragVal = randNums.nextInt(fragment.length);

			String testURL = protocol[protVal].item;
			testURL += subdomain[subVal].item;
			testURL += domain[domVal].item;
			testURL += port[portVal].item;
			testURL += path[pathVal].item;
			testURL += query[qVal].item;
			testURL += fragment[fragVal].item;
									
			boolean expRes;
			if (protocol[protVal].valid == true && 
				subdomain[subVal].valid == true && 
				domain[domVal].valid == true && 
				port[portVal].valid == true && 
				path[pathVal].valid == true && 
				query[qVal].valid == true &&
				fragment[fragVal].valid == true) {
				expRes = true;
			}
			else {
				expRes = false;
			}

			boolean actRes = urlVal.isValid(testURL);

			if (expRes != actRes) {
				stillRun = false;

				outFile.println("URL: " + testURL);
				outFile.println("Expected Results: " + expRes);
				outFile.println("Actual Results: " + actRes);
				outFile.println("Failed!");
				outFile.println();
			}
		}

		outFile.close();
	}
	
	static ResultPair[] protocol = {
			new ResultPair("", false),
			new ResultPair("https://", true),
			new ResultPair("http://", true),
			new ResultPair("http:////", false),
			new ResultPair("file:///", true),
			new ResultPair("5®67", false),
			new ResultPair("hfjhasfhsdkjhcbksjhdbckhjgfuweerugskjdascjhbasdjhgasjhfbljsdhcbkasdhfcjhsbcljbscjhbsdlbashgflashgfysagdcjhbschbasdfhgasuifgasdjbsdlcblsahgfljsabcljasbcljasfljgaiusefgehgfljsbcljsbdfljhgasdkfjuhaswiufhlskjcbnlsdjdbfljsdahfuysifcbasjchaspiawylafljsabcljasdhdfhgasygasdhcbbcsjhfgljweagfusdgljjhsdbckjhasdfjgsdfugwefhvasdkhfvashkfuyaevfuberyflgbrtuhjbskfhvdkjhikuajelfbhouerygjhbedcvjkhgduvcygdjkhbvfhjksgvuagfbaewfgbuchvsdkjhgfwegfusgdcjhbsdacjhguaedyfrugcjkhsdbckjhsdgfuygtewfytsdchvdsjkhcvsdakjagfuyaewtgfusdgkhsdkcjhvskjdhgfyuwetfrjhsgdfjkhvjkhvdgfyweagtrhbsfchvjkhgwejfgjhsdfjhsdvcjhsdgfywetruygdsfjkhvsdkchjvdkygfrewygfkjsdhvckhjsdgfhgewyruthjksdvcjksdhgfhgewyrgtsjkhdcvskjhdgfkyetwghjcjs://", false)
	};

	static ResultPair[] subdomain = {
		new ResultPair("", true),
		new ResultPair("www.", true),
		new ResultPair("stuff.", true),
		new ResultPair("th¬m.", false),
		new ResultPair("jkfhgsdjuryweiourhljshfljhagerouweytufygasjhdfguyawetruhbsdfjhgasfuygwiufgasdjkhfgiauweyfriawhbfdkjhsdgfjysadfyfrgsdkjhkjsgfjasfuytawfrhgsdjfhgsadkhuytfsfkhsuyteuoakjhgskjjaseruoywefjhgsdjhfgsajkhfguywetruiyshdgfkjhgfaifdbkhasafuekjghnlsdfkjglkfsdnglksrhegtlkjdfhgjbflhuiytrejkfglglkjfdhgluyhretuhfdkjgbfdsljkbrjehtuierytuidshfglkjdfhvbcxmdsfghdjkhgfjhsdgfkjhgsdljfhgsdkjhfljhsckjhgsdafkjhgsdljfhbvkjdshvckjhsdgfjhgsdakjfhgduyhfrgtueywtgruoyertuerutypreuitpriuetypiueryotuyteufiytwelfhsdglfsdhjgfksdgahkfgsdhfvsdmcbvxzmbnvxzcjhcgfskhjfkdjghjkhgkhjgjhkdsgfjhmnbxcbvmhgfdsahfguyertgjnvbfdhgdkjghkjsdhgfaeriuyretuyd.", false)
	};

	static ResultPair[] domain = {
		new ResultPair("", false),
		new ResultPair("google.com", true),
		new ResultPair("google", false),
		new ResultPair("google com", false),
		new ResultPair("google.com", true),
		new ResultPair("apple-things.com", true),
		new ResultPair("apple!.com", false),
		new ResultPair("pickle@home.com", false),
		new ResultPair("http://", false),
		new ResultPair("localhost", false),
		new ResultPair("172.16.254.1", true),
		new ResultPair("172.16.254.1", true),
		new ResultPair("172.16.255.1", true),
		new ResultPair("172.16.900.1", false),
		new ResultPair("aplace.org", true),
		new ResultPair("µ¶the±.com", false),
		new ResultPair("fjhsdgfkjhsdkjfhvsdkjhfgkjhsdgfkhbsdkjcbsdjkhbfjksdgfkjhgsdkjhcbsdkjhfvkjhdgsfkjsdahgfljhdbsfljkbhsdajlcvbdlfbvlkjfdhglkjbfvlvkbdhvlkjdglkjvljbfdljbvhkdfhbkgvhfdgureytuiyreoituyerpterquypiueyroeruyijhdgfkjhdgfdjskhgfkdshlfdashljfglhdsgafljdfhglkjsfdhglhfiuadyouiyterquwotruoiewyupiorewyrweiotuerpiotudfjghdjkgfasdnhbvmbnxzvcmbnvcmbnvcbxmxmznbvxjhfgdkfjghdalkahureytuioyretiuoyrewuithgrewjgkfdshgfdioauysjegrtkyoyuipuiyy.net", false)
	};

	static ResultPair[] port = {
		new ResultPair("", true),
		new ResultPair(":80", true),
		new ResultPair(":443", true),
		new ResultPair("2:43", false),
		new ResultPair(":1090", true),
		new ResultPair(":65535", true),
		new ResultPair("http://", false),
		new ResultPair(":bill", false),
		new ResultPair(":£¤¥", false),
		new ResultPair(":1234567891234890", false) /* Will it be false? */
	};

	static ResultPair[] path = {
		new ResultPair("", true),
		new ResultPair("/yes/alsoyes/", true),
		new ResultPair("/okay/sure", true),
		new ResultPair("http://", false),
		new ResultPair("\\okay\\sure", false),
		new ResultPair("/¦§¨«", false),
		new ResultPair("/sdhfkjsdahfk/asdjkfhaskdjfhkajsfh/fkjhasdkfjhasdkfjh/kjsdhfkajsdhfkjasdf/lkadsfkasdfkjsdahf/lkasdflkjasdfkjasdh/ouerotiueroiu/sdkfhkasdhfkjasdfh/lksdfjlkjsdhafkjasdh/kjasdflksdahfkjhasdkj/lksdhjflkasdjflkasjdf/ksdjhflkasdjflksdja/kjasjflksdjflkdsjaf/ikjdsflkasdjfioujasdkflj/klsdjflksdjfldkasf/", false)
	};

	static ResultPair[] query = {
		new ResultPair("", true),
		new ResultPair("?a=yes", true),
		new ResultPair("?number=5&word=okay", true),
		new ResultPair("http://", false),
		new ResultPair("?:£¤¥=/¦§¨«", false),
		new ResultPair("?a=yes&b=75&stuff=some+text+here&hfgasdkjfghasdkjfhkasdjhfuierihwfdkjsdahfiusdhafjkasdhfkjsdh=sdjkfhasdkjfhksdjhfuiweyriuhsdkjfhasdkjfhaskdjhfkjasdbfkjbsdcjkhfjkdhsjkfh&iruweqioruyweiuryqiuweryioertuioweurioertuiuerytuiywertiuyweroitueroituieruytiureytiuy=oierutioweurehfkjsdahfkjhsdiufhyouiertiojergtkjhsdfkjhsdfiugeroitujkehdfkjhsgfdkjghiutryiowtyoihdsfkjghkjfdghiouwertioh", false)
	};

	static ResultPair[] fragment = {
		new ResultPair("", true),
		new ResultPair("#something", true),
		new ResultPair("#a1s2d3f4g5hj", true),
		new ResultPair("http://", false),
		new ResultPair("#5®67", false),
		new ResultPair("#sjdhfkasjdhfiueyroihdfjkhasuryeofhjsdhfguiaeyfojhasdfkjhaewiurhlkasjfhiuawehfkjahfuaweifhasdufhiaweuhfaswhfrwertoiuyalfjhasdfhaoeiuytoajsdhljirufhlfyiukfhakdsjfhoaweytoiuweyfrkjsadhlkjfhskfeiusdjfaldjiurjhflksdhkahfyjhsdafkjhasdkfjlhauyeruthsdkljfhasiurehlkjdsahfiuyertioyituyewouiyroiyriutyeoterpoeriyweiuryweiutyerjhgfdskjgfkjhgfjhgsdkfhgsdjhkfgsdjkhgfksdgbvmnvbxcmnbvnbvmnbvmnbvmnbvmnbvmnbvczxmnvcmnbxcvmnzxcbvxmnbcvmznxbvcmznbcvhdsgfhsdgfsafgeuyrteriewyrteiruyjhdgfksdhjfgkyityur", false)
	};
}