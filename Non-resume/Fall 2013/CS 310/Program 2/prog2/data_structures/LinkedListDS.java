/*	Trevor Cargile
	masc0328
	813542789	*/

package data_structures;

import java.util.Iterator;
import java.util.NoSuchElementException;
import java.lang.UnsupportedOperationException;

public class LinkedListDS<E> implements ListADT<E>{
    
    class Node<T>{
    	T data;
	Node<T> next;
	public Node(T obj){
	    data = obj;
	    next = null;
	    }
	}

    private Node<E> head, tail;
    private int currentSize;

//  Adds the Object obj to the beginning of the list
    public void addFirst(E obj){
    	Node<E> newNode = new Node<E>(obj);
	
	//if list is empty, make head/tail point to new node.
	if (head == null)
	    head = tail = newNode;
	//else make the newNode point to the first in list, head is newNode.
	else{
	    newNode.next = head;
	    head = newNode;
	    }
	
	currentSize++;
    	return;
	}

//  Adds the Object obj to the end of the list
    public void addLast(E o){
    	//create new node with the o passed.
        Node<E> newNode2 = new Node<E>(o);
	
	//if the list is empty, make head/tail point to it.
	if (head == null)
	    head = tail = newNode2;
	//make tail's next point to new node, then make tail point to new node.
	else{
	    tail.next = newNode2;
	    tail = newNode2;
	    }
	
	currentSize++;
    	return;
	}

//  Removes the first Object in the list and returns it.
//  Returns null if the list is empty.
    public E removeFirst(){
    	//if list is empty, return null.
    	if (head == null)
	    return null;
	//if there is only one node, make list empty and return node.
	else if (head == tail){
	    Node<E> holder = head;
	    head = tail = null;
	    currentSize--;
	    return holder.data;
	    }
	//make the head point to the first node's next.
	else{
	    Node<E> holder = head;
	    head = head.next;
	    currentSize--;
	    return holder.data;
	    }
	}

//  Removes the last Object in the list and returns it.
//  Returns null if the list is empty.
    public E removeLast(){
    	//if list is empty, return null.
    	if (head == null)
	    return null;
	//if there is only one node, make empty and return it.
	else if (head == tail){
	    Node<E> holder = head;
	    head = tail = null;
	    currentSize--;
	    return holder.data;
	    }
	//must keep track of previous node, make tail = previous from current.
	else{
	    Node<E> holder = null, current = head;
	    while (current != tail){
	    	holder = current;
		current = current.next;
		}
	    holder.next = null;
	    tail = holder;
	    
	    currentSize--;
	    return current.data;
	    }
	}

//  Returns the first Object in the list, but does not remove it.
//  Returns null if the list is empty.
    public E peekFirst(){
    	if (head == null)
	    return null;
	else
	    return head.data;
	}

//  Returns the last Object in the list, but does not remove it.
//  Returns null if the list is empty.
    public E peekLast(){
    	if (head == null)
    	    return null;
	else
	    return tail.data;
	}
    
//  Finds and returns the Object obj if it is in the list, otherwise
//  returns null.  Does not modify the list in any way
    public E find(E obj){
    	//calls contains to save from writing same code.
    	if (contains(obj))
	    return obj;
	else
	    return null;
	}

//  Removes the first instance of thespecific Object obj from the list, if it exists.
//  Returns true if the Object obj was found and removed, otherwise false
    public boolean remove(E obj){

	Node<E> holder = null, current = head;
	while (((Comparable<E>)obj).compareTo(current.data) != 0){
	    //if the current node is at the tail it isn't in there.
	    if(current == tail)
		return false;
	    //keep track of previous node and current node.
	    holder = current;
	    current = current.next;
	    }
	//if the current node is in front, removeFirst
	if (current == head)
	    removeFirst();
	//if the current node is at the end, removeLast
	else if(current == tail)
	    removeLast();
	//the node must be in the middle, make previous point to current's next.
	else{
	    holder.next = current.next;
	    currentSize--;	    	
	    }
	//only can get to this point if it is in the list.
	return true;	    
	}

//  The list is returned to an empty state.
    public void makeEmpty(){
    	//remove all nodes by pointing both head/tail to null & reset size.
    	head = tail = null;
	currentSize = 0;
    	return;
	}

//  Returns true if the list contains the Object obj, otherwise false
    public boolean contains(E obj){
    	Node<E> tmp = head;
	//stop when tmp hits null, which is end of list.
	while (tmp != null){
	    //Compare both obj and current node.data and return true if equal.
	    if(((Comparable<E>)obj).compareTo(tmp.data) == 0)
	    	return true;
	    tmp = tmp.next;
	    }
	//if the while loop is broken, it isn't in the list.
	return false;
	}

//  Returns true if the list is empty, otherwise false
    public boolean isEmpty(){
    	return head == null;
	}

//  Returns true if the list is full, otherwise false
    public boolean isFull(){
    	return false;
	}

//  Returns the number of Objects currently in the list.
    public int size(){
    	return currentSize;
	}

//  Returns an Iterator of the values in the list, presented in
//  the same order as the list.
    public Iterator<E> iterator(){
    	return new Iteratorhelper();
	}


    class Iteratorhelper implements Iterator<E>{
    	Node<E> itrPtr;
	
	public Iteratorhelper(){
	    //start at the head.
	    itrPtr = head;
	    }
	    
	public E next(){
	    if (!hasNext()) throw new NoSuchElementException();
	    //move to the next node in the list.
	    E temp = itrPtr.data;
	    itrPtr = itrPtr.next;
	    return temp;
	    }
	
	public Iterator<E> iterator(){
	    return new Iteratorhelper();
	    }
	
	public boolean hasNext(){
	    //if itrPtr is null, there is nothing left in the list.
	    return itrPtr != null;
	    }
	
	public void remove(){
	    throw new UnsupportedOperationException();
	    }
	}
}
