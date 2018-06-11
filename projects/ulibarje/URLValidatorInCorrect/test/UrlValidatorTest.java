

import junit.framework.TestCase;
import java.util.Random;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!

public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
	   
	   System.out.println("------------ Beginning Manual Test ----------------");
	   
	   //You can use this function to implement your manual testing
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   try {
		   assertTrue(urlVal.isValid("http://www.google.com"));			// ---> pass, expected = pass
		   assertTrue(urlVal.isValid("http://www.google.com/test"));	// ---> pass, expected = pass
//		   assertTrue(urlVal.isValid("http://www.google.com/file/")); 	// ---> fail, expected = pass
		   
		   assertTrue(urlVal.isValid("http://go.a1a/test"));			// ---> pass, expected = fail
		   
//		   assertTrue(urlVal.isValid("ftp://www.google.com/file")); 	// ---> fail, expected = pass
//		   assertTrue(urlVal.isValid("https://www.google.com/file"));	// ---> fail, expected = pass
		   
		   assertTrue(urlVal.isValid("http://go.au"));					// ---> pass, expected = pass
//		   assertTrue(urlVal.isValid("ftp://go.au"));					// ---> fail, expected = pass
		   
//		   assertTrue(urlVal.isValid("http://www.google.com/test1/file?action=view")); 		 // ---> fail, expected = pass
//		   assertTrue(urlVal.isValid("http://www.google.com:65535/test1/file?action=view")); // ---> fail, expected = pass
//		   assertTrue(urlVal.isValid("ftp://www.google.com:65535/test1/file?action=view"));  // ---> fail, expected = pass
		   
		   assertFalse(urlVal.isValid("file://path:/to?action=view"));	// ---> fail, expected = fail
//		   assertTrue(urlVal.isValid("file://path/to?action=view"));	// ---> fail, expected = pass
		   
	   } catch(ExceptionInInitializerError error) {
		   System.out.println("Caught Error: " + error);
	   } catch(NullPointerException error) {
		   System.out.println("Caught Exception: " + error);
		   System.out.println("");
	   }	   
   }
   
   
   public void testYourFirstPartition()
   {
	   
	   System.out.println("");
	   System.out.println("------------ Beginning Partition 1 Test ----------------");
	   
	   int i = 0;
	   //You can use this function to implement your First Partition testing
	   //The first partition will consist of testing the HTTP protocol 
	 
	   ResultPair[] scheme = {new ResultPair("http://", true)};
	   
	   ResultPair[] authority = {new ResultPair("www.apple.com", true),
			   					new ResultPair("258.243.222.111.", false),
			   					new ResultPair("", false)};
	   
	   ResultPair[] port = {new ResultPair("", true),
			   				new ResultPair(":a12", false),
			   				new ResultPair(":80", true)};
	   
	   ResultPair[] path = {new ResultPair("/test1", true),
			   				new ResultPair("/..", false),
			   				new ResultPair("", true)};
	   
	   ResultPair[] pathOptions = {new ResultPair("/$23", true),
			   						new ResultPair("/....", false),
			   						new ResultPair("", true)};
	   
	   ResultPair[] query = {new ResultPair("?action=view", true),
			   				new ResultPair(">>>???", false),
			   				new ResultPair("", true)};
	   
	   
	   
	   // Create URL Validator Object
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   boolean expected = true;
	   int x;
	   int exceptions = 0;
	   String assertionError = null;
	   Random rand = new Random();
	   String valid = "Valid URL";
	   String invalid = "Invalid URL";
	   
	   // Build 5 URLs
	   for(i = 0; i <50; i++) {
		   StringBuilder testStr = new StringBuilder();
		   
		   // Build A URL string
		   testStr.append(scheme[0].item);
		   expected &= scheme[0].valid;
		   
		   x = rand.nextInt(3) ;
		   testStr.append(authority[x].item);
		   expected &= authority[x].valid;
		   
		   x = rand.nextInt(3) ;
		   testStr.append(port[x].item);
		   expected &= port[x].valid;
		   
		   x = rand.nextInt(3) ;
		   testStr.append(path[x].item);
		   expected &= path[x].valid;
		   
		   x = rand.nextInt(3) ;
		   testStr.append(pathOptions[x].item);
		   expected &= pathOptions[x].valid;
		   
		   x = rand.nextInt(3) ;
		   testStr.append(query[x].item);
		   expected &= query[x].valid;
		   
		   //Print the string
		   System.out.println(testStr);
		   
		   //Convert testStr to a string
		   String url = testStr.toString();
		   
		   //Check if URL is valid
		   boolean testResult = urlVal.isValid(url);
		   
		   //Compare expected result to test result
		   try {
			   assertEquals(url, expected, testResult);
			   
			   if(testResult == true) {
				   if(expected)
					   System.out.println("Expected Result: " + valid);
				   else
					   System.out.println("Expected Result: " + invalid);
				   
				   System.out.println("Test Result: Valid URL\n");
			   }
			   else {
				   if(expected)
					   System.out.println("Expected Result: " + valid);
				   else
					   System.out.println("Expected Result: " + invalid);
				   System.out.println("Test Result: Invalid URL\n");
			   }
		   } catch (AssertionError ae) {
       		assertionError = ae.toString();
       		exceptions++;
       		
       		System.out.println(assertionError);
		   }
	   }
	   System.out.println("Exceptions thrown: " + exceptions);
	    
   } // End first partition
   
   public void testYourSecondPartition(){
	   
	   System.out.println("");
	   System.out.println("------------ Beginning Partition 2 Test ----------------");
	   
	   int i = 0;
	   //You can use this function to implement your First Partition testing
	   //The first partition will consist of testing the HTTP protocol 
	 
	   ResultPair[] scheme = {new ResultPair("ftp://", true)};
	   
	   ResultPair[] authority = {new ResultPair("www.apple.com", true),
			   					new ResultPair("258.243.222.111.", false),
			   					new ResultPair("", false)};
	   
	   ResultPair[] port = {new ResultPair("", true),
			   				new ResultPair(":a12", false),
			   				new ResultPair(":80", true)};
	   
	   ResultPair[] path = {new ResultPair("/test1", true),
			   				new ResultPair("/..", false),
			   				new ResultPair("", true)};
	   
	   ResultPair[] pathOptions = {new ResultPair("/$23", true),
			   						new ResultPair("/....", false),
			   						new ResultPair("", true)};
	   
	   ResultPair[] query = {new ResultPair("?action=view", true),
			   				new ResultPair(">>>???", false),
			   				new ResultPair("", true)};
	   
	   
	   
	   // Create URL Validator Object
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   boolean expected = true;
	   int x;
	   int exceptions = 0;
	   Random rand = new Random();
	   String valid = "Valid URL";
	   String invalid = "Invalid URL";
	   
	   // Build 5 URLs
	   for(i = 0; i <50; i++) {
		   StringBuilder testStr = new StringBuilder();
		   
		   // Build A URL string
		   testStr.append(scheme[0].item);
		   expected &= scheme[0].valid;
		   
		   x = rand.nextInt(3) ;
		   testStr.append(authority[x].item);
		   expected &= authority[x].valid;
		   
		   x = rand.nextInt(3) ;
		   testStr.append(port[x].item);
		   expected &= port[x].valid;
		   
		   x = rand.nextInt(3) ;
		   testStr.append(path[x].item);
		   expected &= path[x].valid;
		   
		   x = rand.nextInt(3) ;
		   testStr.append(pathOptions[x].item);
		   expected &= pathOptions[x].valid;
		   
		   x = rand.nextInt(3) ;
		   testStr.append(query[x].item);
		   expected &= query[x].valid;
		   
		   //Print the string
		   System.out.println(testStr);
		   
		   //Convert testStr to a string
		   String url = testStr.toString();
		   
		   //Check if URL is valid
		   try {
			   boolean testResult = urlVal.isValid(url);
			   
			   if(testResult == true) {
				   if(expected)
					   System.out.println("Expected Result: " + valid);
				   else
					   System.out.println("Expected Result: " + invalid);
				   
				   System.out.println("Test Result: Valid URL\n");
			   }
			   else {
				   if(expected)
					   System.out.println("Expected Result: " + valid);
				   else
					   System.out.println("Expected Result: " + invalid);
				   System.out.println("Test Result: Invalid URL\n");
			   }
			   
		   } catch(NoClassDefFoundError error) {
			   exceptions++;
		   }
		   
		   //Compare expected result to test result
		   //assertEquals(url, expected, testResult);

	   }
	   
	   System.out.println("Exceptions thrown: " + exceptions);
	    
   } // End first partition
   
   public void testIsValid()
   {
	   System.out.println("");
	   System.out.println("------------ Beginning testIsValid Test ----------------");
	   
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

       ResultPair[] scheme = {new ResultPair("http://", true),
               new ResultPair("ftp://", true),
               new ResultPair("h3t://", true),
               new ResultPair("3ht://", false),
               new ResultPair("https:/", false),
               new ResultPair("http:", false),
               new ResultPair("", true)};

       ResultPair[] authority = {new ResultPair("www.google.com", true),
               new ResultPair("go.com", true),
               new ResultPair("go.au", true),
               new ResultPair("0.0.0.0", true),
               new ResultPair("1.2.3.4.5", false),
               new ResultPair("go.a", false),
               new ResultPair("", false)};

       ResultPair[] port = {new ResultPair(":80", true),
               new ResultPair(":65535", true),
               new ResultPair(":0", true),
               new ResultPair("", true),
               new ResultPair(":-1", false),
               new ResultPair(":65636",false),
               new ResultPair(":65a", false)};

       ResultPair[] path = {new ResultPair("/test1", true),
               new ResultPair("/t123", true),
               new ResultPair("/$23", true),
               new ResultPair("/..", false),
               new ResultPair("/../", false),
               new ResultPair("/test1/", true),
               new ResultPair("", true)};

       ResultPair[] pathOptions = {new ResultPair("/test1", true),
               new ResultPair("/t123", true),
               new ResultPair("/$23", true),
               new ResultPair("/..", false),
               new ResultPair("/../", false),
               new ResultPair("/test1/", true),
               new ResultPair("", true)};

       ResultPair[] query = {new ResultPair("?action=view", true),
               new ResultPair("?action=edit&mode=up", true),
               new ResultPair("", true),
               new ResultPair("//***//", false),
               new ResultPair("?action=&&", false),
               new ResultPair("?action=^$#view", false),
               new ResultPair("?????", false)};

      int index, value;
      // There are seven given options for each URL part: scheme, authority, port, path, pathOptions, query
      value = 7;
      int correctOutputs = 0;
      int exceptions = 0;
      String assertionError = null;

      Random randVal  = new Random();

      for(int i = 0; i < 50000; i++) {
        StringBuilder testBuffer = new StringBuilder();
        boolean expected = true;

        index = randVal.nextInt(value);
        testBuffer.append(scheme[index].item);
        expected &= scheme[index].valid;

        index = randVal.nextInt(value);
        testBuffer.append(authority[index].item);
        expected &= authority[index].valid;

        index = randVal.nextInt(value);
        testBuffer.append(port[index].item);
        expected &= port[index].valid;

        index = randVal.nextInt(value);
        testBuffer.append(path[index].item);
        expected &= path[index].valid;

        index = randVal.nextInt(value);
        testBuffer.append(pathOptions[index].item);
        expected &= pathOptions[index].valid;

        index = randVal.nextInt(value);
        testBuffer.append(query[index].item);
        expected &= query[index].valid;

        String url = testBuffer.toString();
//        System.out.println(url);
        try {
        	boolean result = urlVal.isValid(url);
        	
        	try {
        		assertEquals(url, expected, result);
        		correctOutputs++;
        	} catch (AssertionError ae) {
        		assertionError = ae.toString();
        		exceptions++;
        		
        		System.out.println(assertionError);
        	}
        	
        } catch(NoClassDefFoundError error) {
        	exceptions++;
        }
      }
      
      System.out.println("");
      System.out.println("--------------------------------");
      System.out.println("Correct test output: " + correctOutputs);
      System.out.println("Exeptions thrown: " + exceptions);
      int total = correctOutputs + exceptions;
      System.out.println("Total tests: " + total);

   }
   


}
