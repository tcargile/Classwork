/*	Trevor Cargile
	masc0328
	813542789	*/

package data_structures;

import java.util.Iterator;
import java.util.NoSuchElementException;
import java.lang.UnsupportedOperationException;

public class Stack<E> extends LinkedListDS<E>{

    // inserts the object obj into the stack
    public void push(E obj){
	addFirst(obj);
	return;
    	}
    
    // pops and returns the element on the top of the stack    
    public E pop(){
    	return removeFirst();
    	}
    
    // returns the number of elements currently in the stack
    public int size(){
    	return super.size();
    	} 
    
    // return true if the stack is empty, otherwise false
    public boolean isEmpty(){
    	return super.isEmpty();
    	}        
    
    // returns but does not remove the element on the top of the stack    
    public E peek(){
    	return peekFirst();
    	} 
     
    // returns true if the object obj is in the stack,
    // otherwise false   
    public boolean contains(E obj){
    	return super.contains(obj);
    	} 
    
    // returns the stack to an empty state    
    public void makeEmpty(){
    	super.makeEmpty();
	return;
	}
    
    // removes the Object obj if it is in the stack and
    // returns true, otherwise returns false.
    public boolean remove(E obj){
    	return super.remove(obj);
    	}    
    
    // returns a iterator of the elements in the stack.  The elements
    // must be in the same sequence as pop() would return them.    
    public Iterator<E> iterator(){
    	return super.iterator();
    	} 
    }
