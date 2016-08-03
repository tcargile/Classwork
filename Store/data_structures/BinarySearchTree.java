/*	Trevor Cargile
	masc0328
	813542789	*/

package data_structures;

import java.util.Iterator;
import java.util.NoSuchElementException;
import java.util.ConcurrentModificationException;

public class BinarySearchTree<K,V> implements DictionaryADT<K,V>{

    private int currentSize, modificationCounter;
    private K foundKey;

    //Tree node has a key and value, and left and right.
    class TreeNode<K,V> implements Comparable<TreeNode<K,V>>{
    	K key;
	V value;
	TreeNode<K,V> left;
	TreeNode<K,V> right;
	public TreeNode(K k, V v){
	    key = k;
	    value = v;
	    left = right = null;
	    }
	//Method to compare two keys.
	public int compareTo(TreeNode<K,V> node){
	    return ((Comparable<K>)key).compareTo((K)node.key);
	    }
    	}
	
    private TreeNode<K,V> root;
      
    //Private class to help the key search method. Has to traverse
    //the whole list because the tree is sorted by key.
    private void valueFinder(TreeNode<K,V> n, V value){
    	if (n == null || foundKey != null) return;
	if (((Comparable<V>)value).compareTo(n.value) == 0){
	    foundKey = n.key;
	    return;
	    }
	valueFinder(n.left,value);
	valueFinder(n.right,value);
    	}

    //Super class for the Key and Value Iterators.	
    abstract class IteratorHelper<E> implements Iterator<E>{
    	protected TreeNode<K,V> [] nodes;
	protected int index, modCheck, j;
	
	//Sets up the array to be displayed.
	public IteratorHelper(){
	    nodes = new TreeNode[currentSize];
	    index = 0;
	    j = 0;
	    modCheck = modificationCounter;
	    sorter(root);
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
	
	//Generic sorting. Go to each left and then right and recursively
	//calls itself.    
	public void sorter(TreeNode<K,V> node){
	    if (node == null) return;
	    sorter(node.left);
	    nodes[j] = node;
	    j++;
	    sorter(node.right);
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

    //Looks for a node that contains the key given and returns true if it was
    //found and false otherwise.    
    public boolean contains(K key){
    	TreeNode<K,V> holder = root;
	//Traverse through logn comparing keys being greater than or smaller than
	//and go right or left until you find it.
	while (holder != null){
	    int compare = ((Comparable<K>)key).compareTo(holder.key);
	    if (compare == 0) 
	    	return true;
	    else if (compare < 0) 
	    	holder = holder.left;
	    else 
	    	holder = holder.right;
	    }
	//If out of loop, it wasn't found.
	return false;
    	}

    //Inserts a node with the given key and value. Returns true if it was
    //successful or false if there already exists a node with that key.
    public boolean insert(K key, V value){
    	TreeNode<K,V> parent = null, holder = root;
	boolean wentLeft = true;
	//If the tree is empty, set the root to a new Node with the given key/value.
	if (holder == null){
	    root = new TreeNode<K,V>(key, value);
	    currentSize++;
	    modificationCounter++;
	    return true;
	    }
	//Until you find the end of the tree, keep going.
	while (holder != null){
	    //Traverse through logn by comparing the key. Greater than - go right,
	    //otherwise go left. If you find the node itself return false because
	    //there can't be duplicates.
	    int compare = ((Comparable<K>)key).compareTo(holder.key);
	    if (compare == 0) 
	    	return false;
	    else if (compare < 0){
	    	parent = holder; 
	    	holder = holder.left;
		wentLeft = true;
		}
	    else{
	    	parent = holder; 
	    	holder = holder.right;
		wentLeft = false;
		}
	    }
	//If you went left that's the parent's new left, otherwise it is
	//the parent's new right.
	if (wentLeft)
	    parent.left = new TreeNode<K,V>(key, value);
	else
	    parent.right = new TreeNode<K,V>(key, value);
	currentSize++;
	modificationCounter++;
	return true;  
	}

    //Removes a node based on the key given.
    public boolean remove(K key){
    	TreeNode<K,V> parent = null, holder = root;
	//value to keep track of if we are deleting a parent's right or left node.
	boolean wentLeft = true;
	//Traverse the tree until you find the node you are looking for.
	while (holder != null){
	    int compare = ((Comparable<K>)key).compareTo(holder.key);
	    if (compare == 0) 
	    	break;
	    else if (compare < 0){
	    	parent = holder; 
	    	holder = holder.left;
		wentLeft = true;
		}
	    else{
	    	parent = holder; 
	    	holder = holder.right;
		wentLeft = false;
		}
	    }
	//Couldn't find the node, so return false.
    	if (holder == null) return false;
	//Node has no children. Set it's parent's left or right to null.
	if (holder.right == null && holder.left == null){
	    if (holder == root)
	    	root = null;
	    else if (wentLeft) 
	    	parent.left = null;
	    else 
	    	parent.right = null;
	    }
	//The node has two children here..
	else if (holder.right != null && holder.left != null){
	    //Algorithm used: Successor - go right then go left until null.
	    TreeNode<K,V> succParent = holder, successor = holder;
	    successor = successor.right;
	    int flag = 0;
	    //The algorithm step. The flag is used to keep track whether we went
	    //left at all after we went right once. This loop find the node to
	    //replace the node and also its parent.
	    while (successor.left != null){
	    	succParent = successor;
		successor = successor.left;
		flag = -1;
		}
	    //If the node is the root replace with successor.
	    if (holder == root){
	    	//We went right and then left, so take into account both sides.
	    	if (flag == -1){
		    succParent.left = successor.right;
		    successor.left = root.left;
		    successor.right = root.right;
		    root = successor;
		    }
		//Root's right only has one child. Inherit left and replace.
		else{
		    successor.left = root.left;
		    root = successor;
		    }
		}
	    //Node is just an ordinary node.
	    else{ 
	    	//If we went right and then left, set the parent's left to the
		//successor's right. Then check to see if the node we are deleting
		//is on the parent's left or right and replace accordingly.
	    	if (flag == -1){
		    succParent.left = successor.right;
		    if (wentLeft){
		    	successor.left = parent.left.left;
		    	successor.right = parent.left.right;
			parent.left = successor;
		    	}
		    else{
		    	successor.left = parent.right.left;
			successor.right = parent.right.right;
			parent.right = successor;
			}
		    }
		//If we just went right, then check to see if we went left or right
		//and replace the parent's side with the appropriate value.
	    	else{
		    if (wentLeft){
		    	successor.left = parent.left.left;
		    	parent.left = successor;
			}
		    else{
		    	successor.left = parent.right.left;
		    	parent.right = successor;
			}
		    }
		}
	    }
	//The node in question has one child.
	else{
	    //If it's the root, make whatever child it has the new one.
    	    if (holder == root){
	    	if (holder.right != null)
	    	    root = root.right;
	    	else
	    	    root = root.left;
	    	}
	    //If you went left then set the parent's left to its one child.
	    else if (wentLeft){
	    	if (holder.right != null)
	    	    parent.left = holder.right;
	    	else
		    parent.left = holder.left;
	    	}
	    //Otherwise, set the parent's right to its one child.
	    else{
	    	if (holder.right != null)
		    parent.right = holder.right;
	    	else
		    parent.right = holder.left;
	        }
    	    }
	
	currentSize--;
	modificationCounter++;
	return true;
    	}   

    //Traverse through the tree by following a logn path. Once the node is
    //found, return it, or return null.
    public V getValue(K key){
    	TreeNode<K,V> holder = root;
	//If less than, go to the left, else go to the right.
	while(holder != null){
	    int compare = ((Comparable<K>)key).compareTo(holder.key);
	    if (compare == 0)
	    	return holder.value;
	    else if (compare < 0)
	    	holder = holder.left;
	    else
	    	holder = holder.right;
	    }
	return null;
    	}

    //Call valueFinder to continuously loop through the tree to find the key.
    public K getKey(V value){
    	foundKey = null;
	valueFinder(root,value);
    	return foundKey;
    	}

    //Return the currentSize of the tree.
    public int size(){
    	return currentSize;
    	}

    //Since a tree can never be full, return null.
    public boolean isFull(){
    	return false;
    	}

    //If the root is null, then the tree is empty.
    public boolean isEmpty(){
    	return root == null;
    	}
 
    //Clears the tree.
    public void clear(){
    	root = null;
	currentSize = 0;
	modificationCounter = 0;
    	}

    public Iterator<K> keys(){
    	return new KeyIteratorHelper();
    	}

    public Iterator<V> values(){
    	return new ValueIteratorHelper();
    	}	
    }
