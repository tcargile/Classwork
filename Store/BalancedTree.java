/*	Trevor Cargile
	masc0328
	813542789	*/

package data_structures;

import java.util.Iterator;
import java.util.NoSuchElementException;
import java.util.ConcurrentModificationException;
import java.util.TreeMap;
import java.util.Map;
import java.util.Map.Entry;

public class BalancedTree<K,V> implements DictionaryADT<K,V>{

    private int currentSize, modificationCounter;
    private TreeMap<K,V> tree = new TreeMap<K,V>();

    //Super class for the Key and Value Iterators.	
    abstract class IteratorHelper<E> implements Iterator<E>{
    	protected Entry<K,V> [] nodes;
	protected int index, modCheck, j;
	
	//Creates an array of Map.Entry and sorts them naturally through the
	//entry.set method of tree.
	public IteratorHelper(){
	    nodes = new Entry[currentSize];
	    index = 0;
	    j = 0;
	    modCheck = modificationCounter;
	    for (Map.Entry<K,V> test : tree.entrySet()){
	    	nodes[j] = test;
		j++;
		}
	    }
	
	//Checks to see if there is another element in the list.
	public boolean hasNext(){
	    if(modCheck != modificationCounter)
	    	throw new ConcurrentModificationException();
	    return index < currentSize;
	    }
	
	public abstract E next();
	
	public void remove() {
	    throw new UnsupportedOperationException();
	    }
	}

    //Inner class that the key iterators use to send the key values back
    //to the array to be sorted. Other than the next, everything else
    //is inherited by the IteratorHelper class.
    class KeyIteratorHelper<K> extends IteratorHelper<K>{
    	public KeyIteratorHelper(){
	    super();
	    }
	public K next(){
	    return (K) nodes[index++].getKey();
	    }
	}
	
    //Inner class that the value iterators use to send the value back to
    //the array in order to be sorted. It inherits everything else from
    //the IteratorHelper class besides the next class.
    class ValueIteratorHelper<V> extends IteratorHelper<V>{
    	public ValueIteratorHelper(){
	    super();
	    }
	public V next(){
	    return (V) nodes[index++].getValue();
	    }
	}

    //Call the containsKey method to check to see if the key exists. This is
    //logn behavior.
    public boolean contains(K key){
    	return tree.containsKey(key);
	}
	
    //Call the containsKey method to check if the value is already in the list
    //and if it isn't put it in there. Return false if both methods fail.
    public boolean insert(K key, V value){
    	if (tree.containsKey(key) || tree.put(key,value) != null)
	    return false;
	currentSize++;
	modificationCounter++;
	return true;
    	}
	
    //Call the remove method for tree and if it returns null then it
    //either failed or it didn't exist.
    public boolean remove(K key){
    	if (tree.remove(key) == null)
	    return false;
	currentSize--;
	modificationCounter++;
	return true;
    	}
	
    //Call the get method which will return the value or null
    //depending on if the key was found or not.
    public V getValue(K key){
    	return tree.get(key);
    	}

    //Have to traverse through every Map.Entry in the tree because it is
    //sorted by key and not value. If found return the key, otherwise null.
    public K getKey(V value){
    	for(Map.Entry<K,V> test : tree.entrySet()){
	    if (((Comparable<V>)value).compareTo(test.getValue()) == 0)
	    	return test.getKey();
	    }
    	return null;
    	}

    //Return the size of the tree.	
    public int size(){
    	return tree.size();
    	}

    //Since a tree is never full, return false.
    public boolean isFull(){
    	return false;
    	}

    //If the currentSize is 0, return true, otherwise false. Could
    //also call size method of tree and check that with 0.
    public boolean isEmpty(){
    	return currentSize == 0;
    	}

    //Set your own currentSize/modificationCounter to 0 and then use
    //the clear method of the tree.
    public void clear(){
    	currentSize = modificationCounter = 0;
    	tree.clear();
    	}
	
    public Iterator<K> keys(){
    	return new KeyIteratorHelper();
	}

    public Iterator<V> values(){
    	return new ValueIteratorHelper();
    	}
    }
