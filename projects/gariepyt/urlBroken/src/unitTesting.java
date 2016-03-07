// import junit.framework.TestCase;

// import java.io.PrintWriter;
// import java.io.File;
import java.io.*;

public class unitTesting {
	public static void main(String[] args) throws FileNotFoundException {
		// PrintWriter outFile = new PrintWriter("urlResults.txt", "UTF-8");
		// File fName = new File("urlResults.txt");
		// PrintWriter outFile = new PrintWriter(fName);
		PrintWriter outFile = new PrintWriter("urlResults.txt");
		UrlValidator urlVal = new UrlValidator();

		for (int protVal = 0; protVal < protocol.length; protVal++) {
			for (int subVal = 0; subVal < subdomain.length; subVal++) {
				for (int domVal = 0; domVal < domain.length; domVal++) {
					for (int portVal = 0; portVal < port.length; portVal++) {
						for (int pathVal = 0; pathVal < path.length; pathVal++) {
							for (int qVal = 0; qVal < query.length; qVal++) {
								for (int fragVal = 0; fragVal < fragment.length; fragVal++) {
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

									outFile.println("URL: " + testURL);
									outFile.println("Expected Results: " + expRes);
									outFile.println("Actual Results: " + actRes);

									if (expRes == actRes) {
										outFile.println("Success!");
									}
									else {
										outFile.println("Failed!");
									}

									outFile.println();
								}
							}
						}
					}
				}
			}
		}

		outFile.close();
	}
	
	static ResultPair[] protocol = {
			new ResultPair("", false),
			new ResultPair("https://", true),
			new ResultPair("http://", true),
			new ResultPair("5®67", false),
			new ResultPair("hfjhasfhsdkjhcbksjhdbckhjgfuweerugskjdascjhbasdjhgasjhfbljsdhcbkasdhfcjhsbcljbscjhbsdlbashgflashgfysagdcjhbschbasdfhgasuifgasdjbsdlcblsahgfljsabcljasbcljasfljgaiusefgehgfljsbcljsbdfljhgasdkfjuhaswiufhlskjcbnlsdjdbfljsdahfuysifcbasjchaspiawylafljsabcljasdhdfhgasygasdhcbbcsjhfgljweagfusdgljjhsdbckjhasdfjgsdfugwefhvasdkhfvashkfuyaevfuberyflgbrtuhjbskfhvdkjhikuajelfbhouerygjhbedcvjkhgduvcygdjkhbvfhjksgvuagfbaewfgbuchvsdkjhgfwegfusgdcjhbsdacjhguaedyfrugcjkhsdbckjhsdgfuygtewfytsdchvdsjkhcvsdakjagfuyaewtgfusdgkhsdkcjhvskjdhgfyuwetfrjhsgdfjkhvjkhvdgfyweagtrhbsfchvjkhgwejfgjhsdfjhsdvcjhsdgfywetruygdsfjkhvsdkchjvdkygfrewygfkjsdhvckhjsdgfhgewyruthjksdvcjksdhgfhgewyrgtsjkhdcvskjhdgfkyetwghjcjs://", false)
	};

	static ResultPair[] subdomain = {
		new ResultPair("", true),
		new ResultPair("www.", true),
		new ResultPair("stuff.", true),
		new ResultPair("th¬m.", false),
		new ResultPair("jkfhgsdjuryweiourhljshfljhagerouweytufygasjhdfguyawetruhbsdfjhgasfuygwiufgasdjkhfgiauweyfriawhbfdkjhsdgfjysadfyfrgsdkjhkjsgfjasfuytawfrhgsdjfhgsadkhuytfsfkhsuyteuoakjhgskjjaseruoywefjhgsdjhfgsajkhfguywetruiyshdgfkjhgfaifdbkhasafuekjghnlsdfkjglkfsdnglksrhegtlkjdfhgjbflhuiytrejkfglglkjfdhgluyhretuhfdkjgbfdsljkbrjehtuierytuidshfglkjdfhvbcxmdsfghdjkhgfjhsdgfkjhgsdljfhgsdkjhfljhsckjhgsdafkjhgsdljfhbvkjdshvckjhsdgfjhgsdakjfhgduyhfrgtueywtgruoyertuerutypreuitpriuetypiueryotuyteufiytwelfhsdglfsdhjgfksdgahkfgsdhfvsdmcbvxzmbnvxzcjhcgfskhjfkdjghjkhgkhjgjhkdsgfjhmnbxcbvmhgfdsahfguyertgjnvbfdhgdkjghkjsdhgfaeriuyretuyd.", true)
	};

	static ResultPair[] domain = {
		new ResultPair("", false),
		new ResultPair("google.com", true),
		new ResultPair("aplace.org", true),
		new ResultPair("µ¶the±.com", false),
		new ResultPair("fjhsdgfkjhsdkjfhvsdkjhfgkjhsdgfkhbsdkjcbsdjkhbfjksdgfkjhgsdkjhcbsdkjhfvkjhdgsfkjsdahgfljhdbsfljkbhsdajlcvbdlfbvlkjfdhglkjbfvlvkbdhvlkjdglkjvljbfdljbvhkdfhbkgvhfdgureytuiyreoituyerpterquypiueyroeruyijhdgfkjhdgfdjskhgfkdshlfdashljfglhdsgafljdfhglkjsfdhglhfiuadyouiyterquwotruoiewyupiorewyrweiotuerpiotudfjghdjkgfasdnhbvmbnxzvcmbnvcmbnvcbxmxmznbvxjhfgdkfjghdalkahureytuioyretiuoyrewuithgrewjgkfdshgfdioauysjegrtkyoyuipuiyy.net", true)
	};

	static ResultPair[] port = {
		new ResultPair("", true),
		new ResultPair(":80", true),
		new ResultPair(":443", true),
		new ResultPair(":£¤¥", false),
		new ResultPair(":1234567891234890", false) /* Will it be false? */
	};

	static ResultPair[] path = {
		new ResultPair("", true),
		new ResultPair("/yes/alsoyes/", true),
		new ResultPair("/okay/sure", true),
		new ResultPair("/¦§¨«", false),
		new ResultPair("/sdhfkjsdahfk/asdjkfhaskdjfhkajsfh/fkjhasdkfjhasdkfjh/kjsdhfkajsdhfkjasdf/lkadsfkasdfkjsdahf/lkasdflkjasdfkjasdh/ouerotiueroiu/sdkfhkasdhfkjasdfh/lksdfjlkjsdhafkjasdh/kjasdflksdahfkjhasdkj/lksdhjflkasdjflkasjdf/ksdjhflkasdjflksdja/kjasjflksdjflkdsjaf/ikjdsflkasdjfioujasdkflj/klsdjflksdjfldkasf/", true)
	};

	static ResultPair[] query = {
		new ResultPair("", true),
		new ResultPair("?a=yes", true),
		new ResultPair("?number=5&word=okay", true),
		new ResultPair("?:£¤¥=/¦§¨«", false),
		new ResultPair("?a=yes&b=75&stuff=some+text+here&hfgasdkjfghasdkjfhkasdjhfuierihwfdkjsdahfiusdhafjkasdhfkjsdh=sdjkfhasdkjfhksdjhfuiweyriuhsdkjfhasdkjfhaskdjhfkjasdbfkjbsdcjkhfjkdhsjkfh&iruweqioruyweiuryqiuweryioertuioweurioertuiuerytuiywertiuyweroitueroituieruytiureytiuy=oierutioweurehfkjsdahfkjhsdiufhyouiertiojergtkjhsdfkjhsdfiugeroitujkehdfkjhsgfdkjghiutryiowtyoihdsfkjghkjfdghiouwertioh", true)
	};

	static ResultPair[] fragment = {
		new ResultPair("", true),
		new ResultPair("#something", true),
		new ResultPair("#a1s2d3f4g5hj", true),
		new ResultPair("#5®67", false),
		new ResultPair("#sjdhfkasjdhfiueyroihdfjkhasuryeofhjsdhfguiaeyfojhasdfkjhaewiurhlkasjfhiuawehfkjahfuaweifhasdufhiaweuhfaswhfrwertoiuyalfjhasdfhaoeiuytoajsdhljirufhlfyiukfhakdsjfhoaweytoiuweyfrkjsadhlkjfhskfeiusdjfaldjiurjhflksdhkahfyjhsdafkjhasdkfjlhauyeruthsdkljfhasiurehlkjdsahfiuyertioyituyewouiyroiyriutyeoterpoeriyweiuryweiutyerjhgfdskjgfkjhgfjhgsdkfhgsdjhkfgsdjkhgfksdgbvmnvbxcmnbvnbvmnbvmnbvmnbvmnbvmnbvczxmnvcmnbxcvmnzxcbvxmnbcvmznxbvcmznbcvhdsgfhsdgfsafgeuyrteriewyrteiruyjhdgfksdhjfgkyityur", true)
	};
}