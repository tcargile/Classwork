/*	Trevor Cargile
	masc0328
	813542789	*/

import java.util.Iterator;
import data_structures.*;

public class StockItem implements Comparable<StockItem> {
    String SKU;
    String description;
    String vendor;
    float cost;
    float retail;
   
    //Constructor. Creates a new StockItem instance.  
    public StockItem(String oSKU, String oDescription, String oVendor, float oCost, float oRetail){
    	SKU = oSKU;
	description = oDescription;
	vendor = oVendor;
	cost = oCost;
	retail = oRetail;
	}		   
    
    //Follows the specifications of the Comparable Interface.
    //The SKU is always used for comparisons, in dictionary order.  
    public int compareTo(StockItem n){
    	return (((Comparable<String>)SKU).compareTo(n.SKU));
	}
       
    //Returns an int representing the hashCode of the SKU.
    public int hashCode(){
    	return SKU.hashCode();
	}   
       
    //Returns the description of the StockItem.
    public String getDescription(){
    	return description;
	} 
    
    //Returns the vendor of the StockItem.
    public String getVendor(){
    	return vendor;
	}
    
    //Returns the cost of the StockItem.
    public float getCost(){
    	return cost;
	}
    
    //Returns the retail of the StockItem.
    public float getRetail(){
    	return retail;
	}
        
    //All fields in one line, in order   
    public String toString(){
    	return SKU + " | " + description + " | " + vendor + " | " + cost + " | " + retail;
	}
    }
