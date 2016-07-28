//Trevor Cargile
//813542789
//rohan# masc0328

import data_structures.*;

public class MazeSolver{
    private MazeGrid grid;
    //variable to store if the grid has been marked.
    private boolean is_marked = false;
    //variable to store the dimension of the maze.
    private int maze_dimension;
    private Stack<GridCell> maze_stack = new Stack<GridCell>();
    private Queue<GridCell> maze_queue = new Queue<GridCell>();

    //The constructor. Takes a single argument, the number of rows and columns in the grid.
    public MazeSolver(int dimension){
        grid = new MazeGrid(this, dimension);
	maze_dimension = dimension;
        }
    //This method runs the breadth first traversal, marks each reachable cell with its distance.
    public void mark(){
	GridCell holder = grid.getCell(0,0);
	
	//set origin distance equal to 0.
	holder.setDistance(0);
	
	//enqueue the gridCell at the origin.
	maze_queue.enqueue(holder);
	
	while(!maze_queue.isEmpty()){
	    holder = maze_queue.dequeue();
	    grid.markDistance(holder);
	    
	    //checks to see if each adjacent gridcell exists, isn't blackened, and hasn't been visited.
	    //If both tests care true, the gridcell will be queued distance will be marked as one higher.
	    if (grid.isValidMove(grid.getCell(holder.getX() + 1, holder.getY())) && 
	    	!grid.getCell(holder.getX() + 1, holder.getY()).wasVisited()){
	    	maze_queue.enqueue(grid.getCell(holder.getX() + 1, holder.getY()));
		grid.getCell(holder.getX() + 1, holder.getY()).setDistance(holder.getDistance() + 1);
	    	}//End of if
	    if (grid.isValidMove(grid.getCell(holder.getX() - 1, holder.getY())) && 
	    	!grid.getCell(holder.getX() - 1, holder.getY()).wasVisited()){
	    	maze_queue.enqueue(grid.getCell(holder.getX() - 1, holder.getY()));
		grid.getCell(holder.getX() - 1, holder.getY()).setDistance(holder.getDistance() + 1);
	    	}//End of if
	    if (grid.isValidMove(grid.getCell(holder.getX(), holder.getY() + 1)) && 
	    	!grid.getCell(holder.getX(), holder.getY() + 1).wasVisited()){
	    	maze_queue.enqueue(grid.getCell(holder.getX(), holder.getY() + 1));
		grid.getCell(holder.getX(), holder.getY() + 1).setDistance(holder.getDistance() + 1);
	    	}//End of if
	    if (grid.isValidMove(grid.getCell(holder.getX(), holder.getY() - 1)) && 
	    	!grid.getCell(holder.getX(), holder.getY() - 1).wasVisited()){
	    	maze_queue.enqueue(grid.getCell(holder.getX(), holder.getY() - 1));
		grid.getCell(holder.getX(), holder.getY() - 1).setDistance(holder.getDistance() + 1);
	    	}//End of if
	    }//End of while
	//grid has been marked
	is_marked = true;	
    	return;
        }//End mark
    //Does part two, indicates in the GUI the shortest path found.
    public boolean move(){
    	//if the grid hasn't been marked, mark it.
    	if (!is_marked)
	    mark();
	
    	GridCell smallest, holder = grid.getCell(maze_dimension - 1, maze_dimension - 1);
	
	smallest = holder;
	
	//if the distance is -1, the maze has no solution
	if (holder.getDistance() == -1) return false;
	maze_stack.push(holder);
	
	//loop until at the beginning of the maze.
	//check each adjacent gridcell to find the lowest distance from start.
	//then store that grid and recheck from the new gridcell, until back at start.
	while(smallest.getDistance() != 0){
	    if (grid.isValidMove(grid.getCell(holder.getX() - 1, holder.getY())) && 
	    	(smallest.getDistance() > grid.getCell(holder.getX() - 1, holder.getY()).getDistance()))
		smallest = grid.getCell(holder.getX() - 1, holder.getY());
	
	    if (grid.isValidMove(grid.getCell(holder.getX() + 1, holder.getY())) && 
	    	(smallest.getDistance() > grid.getCell(holder.getX() + 1, holder.getY()).getDistance()))
		smallest = grid.getCell(holder.getX() + 1, holder.getY());

	    if (grid.isValidMove(grid.getCell(holder.getX(), holder.getY() - 1)) && 
	    	(smallest.getDistance() > grid.getCell(holder.getX(), holder.getY() - 1).getDistance()))
		smallest = grid.getCell(holder.getX(), holder.getY() - 1);
		
	    if (grid.isValidMove(grid.getCell(holder.getX(), holder.getY() + 1)) && 
	    	(smallest.getDistance() > grid.getCell(holder.getX(), holder.getY() + 1).getDistance()))
		smallest = grid.getCell(holder.getX(), holder.getY() + 1);
		
	    maze_stack.push(smallest);
	    holder = smallest;
	    }//End while
	
	//go through the stack and mark each as part of solution, then pop and go to next one.    
	while(!maze_stack.isEmpty())
	    grid.markMove(maze_stack.pop());
	//the maze has a solution    
    	return true;
        }//End of move
    //Reinitializes the puzzle. Clears the stack and queue (calls makeEmpty() ).
    public void reset(){
    	is_marked = false;
        maze_stack.makeEmpty();
	maze_queue.makeEmpty();
        }//End of reset

    public static void main(String []args){
    	new MazeSolver(30);
    	}//End main
    }//End MazeSolver
