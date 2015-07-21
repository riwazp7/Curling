/*
 *-tailBreaker.java
 *-(c) 2015 Riwaz Poudyal
 *-parse sequences to keys
 *-[tailBreaker] [-h] for help
 */
import java.util.ArrayList;
import java.util.Scanner;
import java.util.LinkedHashMap;
import java.io.File;
import java.io.FileNotFoundException;

public class tailBreaker {
    
    public tailBreaker(String fileName, String seq, int st){

	LinkedHashMap <String, String> dict = makeMap(fileName);

	//List of keys in order to compare with
	ArrayList <String>  keyList = new ArrayList <String> ();
	keyList.addAll(dict.keySet());

	//Parse from front
	if (st == -1) System.out.println(front (seq, keyList, dict));

	//Parse from middle
	else System.out.println(mid(seq, keyList, dict, st));
	
    }

    protected String mid (String seq, ArrayList <String> keyList, LinkedHashMap <String, String> dict, int st){
	
	int strlen = seq.length();

	//if st==0, look for 323 from the exact middle
	if (st == 0) st = strlen/2;

	//Else look for 323 to the right of given st
	int point = seq.indexOf("323", st);

	//If no 323 found, look to the left of st/from the start of the string
	if (point == -1) {

	    point = seq.lastIndexOf("323", st );

	    if (point == -1) point = seq.indexOf("323");
	}

	point+=2;
	System.out.println("Parse from: " + point);

	//Front half to be parsed from the back
	String pre = seq.substring(0, point);

	//End half to be parsed from the front
	String post = front (seq.substring(point), keyList, dict);

	//Parse from back
	while (point>= 0) {

	    boolean flag = false;

	    //Check if a given substring matches a key in the list (In order)
	    for (String key: keyList) {
		
		int keyLen = key.length(); //?

		if (point-keyLen >= 0 && pre.substring(point-keyLen, point).equals(key)) {

		    pre = pre.substring(0, point-keyLen) + dict.get(key) + pre.substring(point);
		    flag = true;
		    point-=(keyLen);
		    break;
		}
	    }

	    //No match. Ignore the character
	    if (!flag) point--;
	}

	//Parsed String
	return pre +"|" + post;
		
    }

    //Parse from the front
    protected String front (String seq, ArrayList <String> keyList, LinkedHashMap <String, String> dict){

	int point = 0;	
	int strlen = seq.length();
	
	while (point <= strlen-1){

	    boolean flag = false;
	    
	    for (String key: keyList){
		
		int keyLen = key.length();
		
		if (point+keyLen <= seq.length() && seq.substring(point, point + keyLen).equals(key)) {
		    String value = dict.get(key);
		    seq = seq.substring(0, point) + value + seq.substring(point+keyLen);
		    flag = true;
		    point+=value.length();
		    break;
		}				
	    }

	    //No match
	    if (!flag) point++;
	}

	return seq;
		
    }

    //Make a LinkedHashMap out of the dictionary file
    protected LinkedHashMap <String, String> makeMap (String fileName){
 
	LinkedHashMap <String, String> dict = new LinkedHashMap <String, String> ();

	try {
	    Scanner sc = new Scanner (new File (fileName));
	    while (sc.hasNextLine()){

		String line = sc.nextLine();
		if (line.startsWith("#")) continue; //Comment
	    
		int col = line.indexOf(":");
		dict.put(line.substring(col+1), line.substring(0, col));	    
	    }
	    
	} catch (FileNotFoundException e){

	    throw new RuntimeException("Invalid File");
	}
	
	return dict;	
    }

    //Call constructor with appropriate value/ print help
    public static void main (String[] args) throws FileNotFoundException{
	
	Scanner sc = new Scanner(System.in);
	
	if (args.length == 1 )   {

	    if (args[0].equals("-h")){

		System.out.println("tailBreaker.java" );
		System.out.println("Help : tailBreaker -h");		    
		System.out.println("Usage: tailBreaker [dictionary file].txt");
		System.out.println("       tailBreaker [dictionary file].txt -m <Optional:index>");
		System.out.println("         -m: start parsing from the 1st occurance of \"232\"\n             from the middle of sequence or from the given index");
		System.out.println("\nTakes dictionary file to parse the input sequence" );
		System.out.println("Dictionary syntax:");
		System.out.println("--comments start with '#'\n--<key>:<value> in each line\n--multiple character keys accepted normal mode only\n");

	    } else {
		
		while (sc.hasNextLine()){
		    
		    //Parse from the front
		    new tailBreaker(args[0], sc.next(), -1);
		}
	    }
	    
	} else if (args.length == 2 && args[1].equals("-m")) {

	    //parse from middle
	    new tailBreaker(args[0], sc.next(), 0);
	    	    
	} else if (args.length == 3 && args[1].equals("-m")){

	    //Parse from the given int value
	    new tailBreaker(args[0], sc.next(), Integer.parseInt(args[2]));	    
	    
	}else System.out.println( "\t¯\\_(ツ)_/¯\nHelp: [tailBreaker] [-h]" );
	
    }
	      
}
