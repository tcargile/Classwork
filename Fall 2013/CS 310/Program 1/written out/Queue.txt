/*	Trevor Cargile
	masc0328
	813542789	*/

package data_structures;

import java.util.Iterator;
import java.util.NoSuchElementException;
import java.lang.UnsupportedOperationException;

public class Queue<E> extends LinkedListDS<E>{

    // inserts the object obj into the queue
    public void enqueue(E obj){
    	addLast(obj);
	return;
    	} 
     
    // removes and returns the object at the front of the queue   
    public E dequeue(){
    	return removeFirst();
    	} 
    
    // returns the number of objects currently in the queue    
    public int size(){
    	return super.size();
    	} 
    
    // returns true if the queue is empty, otherwise false   
    public boolean isEmpty(){
    	return super.isEmpty();
    	} 
    
    // returns but does not remove the object at the front of the queue   
    public E peek(){
    	return peekFirst();
    	} 
    
    // returns true if the Object obj is in the queue    
    public boolean contains(E obj){
    	return super.contains(obj);
    	} 
     
    // returns the queue to an empty state  
    public void makeEmpty(){
    	super.makeEmpty();
	return;
    	} 
    
    // removes the Object obj if it is in the queue and
    // returns true, otherwise returns false.
    public boolean remove(E obj){
    	return super.remove(obj);
    	}
    
    // returns an iterator of the elements in the queue.  The elements
    // must be in the same sequence as dequeue would return them.    
    public Iterator<E> iterator(){
    	return super.iterator();
    	}
    }
