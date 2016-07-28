/*	Trevor Cargile
	masc0328
	813542789	*/

package data_structures;

import java.util.Iterator;
import java.util.NoSuchElementException;
import java.util.ConcurrentModificationException;

public class Hashtable<K,V> implements DictionaryADT<K,V> {

    private int tableSize, maxSize, currentSize;
    private int modificationCounter;
    private LinkedListDS<DictionaryNode<K,V>> [] list;

    //The wrapper class that instantiates the original Node. Has a key
    //and value and what DictionaryNode is next in the list.
    class DictionaryNode<K,V> implements Comparable<DictionaryNode<K,V>>{
    	K key;
	V value;
	DictionaryNode<K,V> next;
	public DictionaryNode(K k, V v){
	    key = k;
	    value = v;
	    next = null;
	    }
	//Method to compare two keys.
	public int compareTo(DictionaryNode<K,V> node){
	    return ((Comparable<K>)key).compareTo((K)node.key);
	    }
	}
	
    //Constructor for hashtable. Establishes the tableSize being 1.3 times
    //larger than the maxSize. CurrentSize and modificationCounter are set
    //to 0. Then, the array of linked lists are created and each element
    //receives a new linked list.	
    public Hashtable(int n){
    	maxSize = n;
    	tableSize = (int) (maxSize * 1.3f);
	currentSize = modificationCounter = 0;
    	list = new LinkedListDS[tableSize];
	for (int i = 0; i < tableSize; i++)
	    list[i] = new LinkedListDS<DictionaryNode<K,V>>();
	}
	
    //Creates a hash code in the range of the tableSize for the key.
    private int getIndex(K key) {
	return (key.hashCode() & 0x7FFFFFFF) % tableSize;
	}
	
    //Super class for the Key and Value Iterators.	
    abstract class IteratorHelper<E> implements Iterator<E>{
    	protected DictionaryNode<K,V> [] nodes;
	protected int index, modCheck;
	
	//Sets the array up of elements in the hashtable to be displayed.
	public IteratorHelper(){
	    nodes = new DictionaryNode[currentSize];
	    index = 0;
	    int j = 0;
	    modCheck = modificationCounter;
	    for(int i = 0; i < tableSize; i++)
	    	for(DictionaryNode<K,V> n : list[i])
		    nodes[j++] = n;
	    sorter();
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
	    
	public void sorter(){
	    //Two indexes to look at for sorting.
	    int take, give;
	    DictionaryNode<K,V> holder;
	    //Incrementer to figure out the gaps.
	    int h = 1;
	    //Max gap size is calculated here.
	    while (h <= currentSize / 3)
	    	h = h * 3 + 1;
	    //Continue until the gap size reaches 0.
	    while (h > 0){
	    	for (give = h; give < currentSize; give++){
		    //Supply the holder with the DictionaryNode being tested.
		    holder = nodes[give];
		    take = give;
		    //If the value in the array is greater than the previous one, swap them.
		    while (take > h - 1 && ((Comparable<K>)nodes[take - h].key).compareTo(holder.key) > 0){
		    	nodes[take] = nodes[take - h];
			take -= h;
			}
		    nodes[take] = holder;
		    }
		//Common shell short algorithm to find the next value of h.    
		h = (h - 1) / 3;
	    	}
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
	    return (K) nodes[index++].key;
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
	    return (V) nodes[index++].value;
	    }
	}

    //Gets the index of the key and checks to see
    //if there exists one with the key given.	
    public boolean contains(K key){
    	return list[getIndex(key)].contains(new DictionaryNode<K,V>(key,null));
    	}

    //Checks to see if the index already contains the DictionaryNode or
    //if the size of the hashtable is full. If so, return false, otherwise
    //add the new DictionaryNode to the end of the list at the index.
    public boolean insert(K key, V value){
    	if (isFull() || (list[getIndex(key)].contains(new DictionaryNode<K,V>(key, null))))
	    return false;
	list[getIndex(key)].addLast(new DictionaryNode<K,V>(key,value));
	currentSize++;
	modificationCounter++;
	return true;
	}

    //Instantly goes to the list at the index from the given key and looks for the node
    //to remove. If it is found, it is removed, but if it isn't a null is returned.
    public boolean remove(K key){
    	if (list[getIndex(key)].remove(new DictionaryNode<K,V>(key,null))){
	    currentSize--;
	    modificationCounter++;
	    return true;
	    }
	return false;
    	}

    //Traverses the list at the index from the given key. If the particular key is found, then its
    //value is returned, otherwise null.
    public V getValue(K key){
    	DictionaryNode<K,V> holder = list[getIndex(key)].find(new DictionaryNode<K,V>(key,null));
	if (holder == null) return null;
	return holder.value;
	}

    //Because the compareTo method that is established in the DictionaryNode class, finding a
    //value without a key can only be done by looking at the whole hash table. This method
    //looks through everything and if the value is found, the key is returned. Otherwise null.
    public K getKey(V value){
    	for(int i = 0; i < tableSize; i++){
	    for(DictionaryNode<K,V> n : list[i]){
	    	if (((Comparable<V>)n.value).compareTo(value) == 0)
		    return n.key;
		}
	    }
	return null;
	}

    //Returns the currentSize of the hash table.
    public int size(){
    	return currentSize;
    	}

    //If the maxSize and currentSize are the same value, then it is full.
    public boolean isFull(){
    	return maxSize == currentSize;
    	}
	
    //If the currentSize is equal to 0, then the hashtable is empty, otherwise it isn't.
    public boolean isEmpty(){
    	return currentSize == 0;
    	}

    //Clears the currentSize as well as the maxSize, which will be determined once the
    //hashtable is remade. Then, every linked list is erased from the array.
    public void clear(){
    	currentSize = 0;
	for (int i = 0; i < tableSize; i++)
	    list[i].makeEmpty();
    	}
	
    //Creates a new iterator for the keys to be analyzed.
    public Iterator<K> keys(){
    	return new KeyIteratorHelper();
	}

    //Creates a new iterator for the values to be analyzed.
    public Iterator<V> values(){
    	return new ValueIteratorHelper();
    	}		    
	
    }
