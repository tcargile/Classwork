import java.util.Iterator;
import data_structures.*;

public class Driver2{
    public static void main(String [] args){
    	Queue<String> list2 = new Queue<String>();
	Stack<String> list = new Stack<String>();
	
	list.push("Hello");
	list.push("World");
	list.push("Hi");
	list.push("What");
	list.push("Why");
	for( String s : list)
	    System.out.println(s);
	System.out.println(list.size());
	System.out.println("----------------------");
	System.out.println(list.pop());
	System.out.println(list.pop());
	System.out.println("----------------------");
	System.out.println(list.size());
	System.out.println("----------------------");
	System.out.println(list.isEmpty());
	System.out.println("----------------------");
	System.out.println(list.peek());
	System.out.println("----------------------");
	System.out.println(list.contains("Hello"));
	System.out.println(list.contains("What"));
	System.out.println(list.contains("Why"));
	System.out.println("----------------------");
	list.makeEmpty();
	System.out.println(list.size());
	System.out.println("----------------------");
	list.push("Hello");
	list.push("World");
	list.push("Hi");
	list.push("What");
	list.push("Why");
	for( String s : list)
	    System.out.println(s);
	System.out.println(list.size());	
	System.out.println("----------------------");
	System.out.println(list.remove("Hi"));
	System.out.println(list.remove("Where"));
	System.out.println(list.remove("Why"));
	System.out.println(list.remove("Hello"));
	System.out.println("----------------------");
		
	return;
    }	
}
