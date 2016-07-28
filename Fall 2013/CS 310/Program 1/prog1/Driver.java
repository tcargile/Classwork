import java.util.Iterator;
import data_structures.*;

public class Driver{
    public static void main(String [] args){
    	ListADT<String> list = new LinkedListDS<String>();
	ListADT<Integer> list2 = new LinkedListDS<Integer>();
	list.addFirst("Hello");
	list.addFirst("World");
	list.addLast("ending");
	list.addLast("ending2");
	list.addFirst("Hello2");
	list.addFirst("World2");
	list.addLast("ending3");
	list.addLast("ending4");
	for (String s : list){
	    System.out.println(s);
	}
	System.out.println(".................");
	System.out.println(list.peekLast());
	list.remove("ending4");
	System.out.println(list.peekLast());
	list.remove("ending2");
	System.out.println(list.peekLast());
	list.remove("Hello2");
	System.out.println(list.peekFirst());
	list.remove("World2");
	System.out.println(list.peekFirst());
	System.out.println(".................");
	for (String s : list){
	    System.out.println(s);
	}
	System.out.println(".................");
	System.out.println(list.peekFirst());
	System.out.println(list.peekLast());
	System.out.println(".................");
	list.removeFirst();
	list.removeLast();
	for (String s : list){
	    System.out.println(s);
	}
	System.out.println(".................");
	System.out.println(list.find("ending"));
	System.out.println(list.find("never"));
	System.out.println(".................");
	System.out.println(list.remove("Hello"));
	System.out.println(list.remove("never"));
	System.out.println(".................");
	list.addFirst("tree");
	list.addFirst("forest");
	list.addLast("jungle");
	for (String s : list){
	    System.out.println(s);
	}	
	System.out.println(".................");
	list.makeEmpty();
	for (String s : list){
	    System.out.println(s);
	System.out.println(list.isEmpty());
	System.out.println(list.isFull());
	}
	System.out.println(".................");
	list.addFirst("tree");
	list.addFirst("forest");
	list.addLast("jungle");
	list.addFirst("frog");
	list.addFirst("bunny");
	list.addLast("cat");
	System.out.println(".................");
	System.out.println(list.isEmpty());
	System.out.println(list.isFull());
	System.out.println(".................");
	System.out.println(list.contains("frog"));
	System.out.println(list.contains("froglet"));
	System.out.println(".................");
	System.out.println(list.size());
	System.out.println(".................");
	System.out.println(list.remove("frog"));
	System.out.println(list.remove("cat"));
	System.out.println(list.peekLast());
	System.out.println(".................");
	System.out.println(list.size());
	System.out.println(".................");
	int i = 0;
	list2.makeEmpty();
	for (i = 0; i<1000; i++){
	    if ((i / 2) == 0)
	    	list2.addFirst(i);
	    else
	    	list2.addLast(i);
	    }
	int a = 100, b = 100;
	int c = 1000, d = 1000;
	System.out.println(a == b);
	System.out.println(c == d);
	for (i = 0; i<1000; i++){
	    list2.remove(i);
	    }
	System.out.println(list2.size());
	System.out.println(".................");	
		
	return;
    }	
}
