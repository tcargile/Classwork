/*	Trevor Cargile
	masc0328
	813542789	*/

import data_structures.*;
import java.util.Iterator;

public class ProductLookup {

    private DictionaryADT<String,StockItem> data;
  
    //Constructor.  There is no argument-less constructor, or default size.
    //Multiple instances are commented out to be able to change.
    public ProductLookup(int maxSize){
    	data = new Hashtable<String,StockItem>(maxSize);
	//data = new BinarySearchTree<String,StockItem>();
	//data = new BalancedTree<String,StockItem>();
    	}
       
    //Adds a new StockItem to the dictionary
    public void addItem(String SKU, StockItem item){
    	data.insert(SKU,item);
    	}
           
    //Returns the StockItem associated with the given SKU, if it is
    //in the ProductLookup, null if it is not.
    public StockItem getItem(String SKU){
    	return data.getValue(SKU);
    	}
       
    //Returns the retail price associated with the given SKU value.
    //-.01 if the item is not in the dictionary
    public float getRetail(String SKU){
    	if (data.getValue(SKU) == null) return -.01f;
	return data.getValue(SKU).getRetail();
    	} 
    
    //Returns the cost price associated with the given SKU value.
    //-.01 if the item is not in the dictionary
    public float getCost(String SKU){
    	if (data.getValue(SKU) == null) return -.01f;
	return data.getValue(SKU).getCost();
	}  
    
    //Returns the description of the item, null if not in the dictionary.
    public String getDescription(String SKU){
    	if (data.getValue(SKU) == null) return null;
	return data.getValue(SKU).getDescription();
	}          
       
    //Deletes the StockItem associated with the SKU if it is
    //in the ProductLookup.  Returns true if it was found and
    //deleted, otherwise false.  
    public boolean deleteItem(String SKU){
    	return data.remove(SKU);
	}
       
    //Prints a directory of all StockItems with their associated
    //price, in sorted order (ordered by SKU).
    public void printAll(){
    	//Create an iterator and traverse it, print each one.
	Iterator<StockItem> values = data.values();
	while(values.hasNext())
            System.out.println(values.next().toString());
        } 
    
    //Prints a directory of all StockItems from the given vendor, 
    //in sorted order (ordered by SKU).
    public void print(String vendor){
    	//Create an iterator and traverse it, and if it matches - print.
    	Iterator<String> key = data.keys();
	while(key.hasNext()){
	    String test = key.next();
	    if (((Comparable<String>)vendor).compareTo(data.getValue(test).getVendor()) == 0)
	    	System.out.println(data.getValue(test).toString());
	    }
	}
    
    //An iterator of the SKU keys.
    public Iterator<String> keys(){
    	return data.keys();
	}
    
    //An iterator of the StockItem values.    
    public Iterator<StockItem> values(){
    	return data.values();
	}
    }
