#include "../Headers/grid2.h"
#include "../Headers/edge.h"
#include "../Headers/claim.h"
#include <algorithm>
#include <list>
//Takes an x and y coordinate as input and creates a grid of that size filled with default nodes
Grid2::Grid2(ProblemObject* problem_object) {
      
      vector<Connection> routes = problem_object->get_connections();//got all routes
      this->num_connections = problem_object->get_connections().size();//how many routes we have
      //vector of structs to keep information.
      for(int i = 0; i < num_connections; ++i)
      {
            grid_helper count;
	    count.source = routes.at(i).source;
	    count.sink = routes.at(i).sink;
	    count.height = problem_object->get_height();
	    count.width = problem_object->get_width();
	    this->all_routes.push_back(count);	    
      }
      vector<Blocker> blockers = problem_object->get_blockers();
      int height = problem_object->get_height();
      int width = problem_object->get_width();
      for(int y = 0; y < height; y++) {//chaging the x and y for blockers
	      vector<Node*> temp_row;
	      for(int x = 0; x < width; x++) {
			 Node* new_node;
	      		 //Check to see if what we want to add falls within a blocker, and if it does than don't add it
	      		 bool add_flag = true;
	      		 for(unsigned i = 0; i < blockers.size(); i++) {
			 	  if(x > blockers.at(i).location.x && x <= blockers.at(i).location.x + blockers.at(i).width &&
				  	y > blockers.at(i).location.y && y <= blockers.at(i).location.y + blockers.at(i).height) {
					add_flag = false;
				  }
			  }

			  //If the add flag is true, the node doesn't lie within a blocker and we can add it to the system
			  if(add_flag) {
				  /* 
				  Note that we add connections west and north because we start building in the upper left
				  corner of the system, so as the system fills it links to all the nodes it can connect to
				  that have already been created. This stops the system from accidentally creating multiple
				  connections between two nodes, which could cause issues when routing
				  */
				  new_node = new Node(x,y);
				  if (x > 0) {
				  	  if(temp_row.at(temp_row.size()-1) != NULL) {
						  Edge* west = new Edge(new_node,temp_row.at(temp_row.size()-1));
						  new_node->add_connection(west);
					  }
				  }
				  if (y > 0) {
				          if(grid2.at(y-1).at(x) != NULL) {
						  Edge* north = new Edge(new_node,grid2.at(y-1).at(x));
						  new_node->add_connection(north);
					  }
				  }
			  }
			  //If the add flag is false, the node shouldn't exist, so we fill its space with a NULL for completeness
			  else {
				new_node = NULL;
			  }
			  temp_row.push_back(new_node);
          }
          this->grid2.push_back(temp_row);
      }
}



//Destructs the grid by deleting each node individually, the node destructors will delete their own set of edges
Grid2::~Grid2() {
      int width = this->get_width();
      int height = this->get_height();
      for(int x = 0; x < width; x++) {
            for(int y = 0; y < height; y++) {//changed to height from width
	    	if(grid2.at(y).at(x) != NULL) {
                  	delete grid2.at(y).at(x);
		  }
            }
      }
}

int Grid2::get_width() {
	//Assumes a perfect rectangle
	return grid2.empty()?0:grid2.at(0).size();
}

int Grid2::get_height() {
	//Assumes a perfect rectangle
	return this->grid2.size();
}

int Grid2::get_num_connections() {
  	return this->num_connections;
}

Node* Grid2::get_node(int x, int y) {
      if(y >= this->grid2.size()) {
        claim("Attemping to access a node outside of the grid's range (y-value out of range)", Utilities::kError);
	    return NULL;
      }
      else if(x >= this->grid2.at(y).size()) {
        claim("Attemping to access a node outside of the grid's range (x-value out of range)", Utilities::kError);
	    return NULL;
      }
      else if(this->grid2.at(y).at(x) != NULL) {
      	    return this->grid2.at(y).at(x);      //at(...) will throw an out of range exception
      }
      else {
	    return NULL;
      }
}

Node* Grid2::get_node(Point coord) {
      return this->get_node(coord.x, coord.y);
}

vector<Path*> Grid2::get_paths() {
      return this->paths;
}

Path* Grid2::get_path(int i) {
      if(i >= paths.size()) {
            claim("Attempting to access a path outside of the path list's range", Utilities::kError);
      }
      return this->paths.at(i);           //at(...) will throw an out of range exception
}

/*
Since each node has an x/y coordinate, if you pass a Node* into replace node, it will take the node at the passed in
Nodes location, delete it, and then place the passed in node into the grid at its proper location.
*/
void Grid2::replace_node(Node* replacement_node) {
      delete this->grid2.at(replacement_node->get_y()).at(replacement_node->get_x());
      this->grid2.at(replacement_node->get_y()).at(replacement_node->get_x()) = replacement_node;
}

void Grid2::set_paths(vector<Path*> paths) {
      this->paths = paths;
}

void Grid2::add_path(Path* path) {
      this->paths.push_back(path);
}

void Grid2::replace_path(int i, Path* path) {
      if(i >= this->paths.size()) {
            claim("Attemping to replace path outside of the path list's range", Utilities::kError);
      }
      paths.at(i) = path;
}

void Grid2::remove_path(int i) {
      if(i >= paths.size()) {
      	claim("Attempting to remove a path outside of the path list's range", Utilities::kError);
      }
      vector<Path*>::iterator it = this->paths.begin();
      it += i;
      paths.erase(it);
}


void Grid2::print_grid2(int i)
{

for(int c = 0; c < grid2.size(); ++c)
{
	//cout << height << width  << endl;
	for(int r = 0; r < grid2.at(0).size(); ++r)
	{
		if(grid2.at(c).at(r) == NULL){
		std::cout << "X ";
		}
		else{
		    std::cout << "O ";
	}
	}
	std::cout << endl;
}
}


void Grid2::print_cost_grid2(int i)
{
for(int c = 0; c < grid2.size(); ++c)
{
	for(int r = 0; r < grid2.at(0).size(); ++r)
	{
		if(grid2.at(c).at(r) != NULL){
		int temp = grid2.at(c).at(r)->get_cost();
		if(temp == -1){temp = 0;}
		std::cout << temp << " ";
		}
		else{
		    std::cout << "X ";
		}
	}
	std::cout << endl;
}
}

void Grid2::reset_costs(int i){
for(int c = 0; c < grid2.size(); ++c)
{
	for(int r = 0; r < grid2.at(0).size(); ++r)
	{
		if(grid2.at(c).at(r) != NULL){
		grid2.at(c).at(r)->set_cost(0);
		}
	}
}
}


//Traceback algoritm, gets our source, sink, height/width, and lees num
//add a segment to our path if it fits lees num
//return path*
Path* Grid2::traceback(int lees_num, bool intersections, int source_x, int source_y, int sink_x, int sink_y, int height, int width){
bool intersection = intersections;

//keeps the direction we have, lets us know if prev != curr then we change directions
int prev_dir = 0;
int curr_dir = 0;
//lets us know when we're done
bool source_found = false;


int curr_lees = lees_num + 1;

//create new path
//set the sink and source
//we'll print out the path in reverse 
Path* new_path = new Path();			//we'll use this for our path
int curr_x = sink_x;
int curr_y = sink_y;
int target_x = source_x;
int target_y = source_y;


//we know that the sink is -1 so special identifier
//5 directions
//       3(up)
//1(left) 0() 2(right)
//      4(down)


while(source_found == false)//break when we find our source
{
    --curr_lees;
    bool added = false;		//this will only let us add one node
    
    if(intersection == false)
    {
	//makes node NULL if we visit it
	grid2.at(curr_y).at(curr_x) = NULL;	
    }
    //left check
    if(added == false){
    if((curr_x - 1 == target_x)&& //checking for sink
    (curr_y == target_y)){
	    Point head(curr_x, curr_y);
	    Point tail(curr_x-1, curr_y);
	    prev_dir = curr_dir;
	    curr_dir = 1;
	    if((curr_dir != prev_dir) && (prev_dir != 0)){
		Point top(-10, -10);
		Point bottom(-10, -10);
            	PathSegment* spec_seg = new PathSegment(top, bottom);
            	new_path->add_segment(spec_seg);
	    }
            PathSegment* new_segment = new PathSegment(head,tail);
            new_path->add_segment(new_segment);
	    added = true;
	    source_found = true;
	    if(intersection == false){
	        grid2.at(curr_y).at(curr_x - 1) = NULL;
	    }
	    break;
    }
    if((curr_x - 1 > -1) && (curr_y < height) && (curr_y > -1)){//inside the grid
	if((grid2.at(curr_y).at(curr_x - 1) != NULL)&& //grid is valid to left
    	(grid2.at(curr_y).at(curr_x - 1)->get_cost() == curr_lees)){ //checks that cost is one less
	    Point head(curr_x, curr_y);
	    Point tail(curr_x-1, curr_y);
	    prev_dir = curr_dir;
	    curr_dir = 1;
	    if((curr_dir != prev_dir) && (prev_dir != 0)){
		Point top(-10, -10);
		Point bottom(-10, -10);
            	PathSegment* spec_seg = new PathSegment(top,bottom);
            	new_path->add_segment(spec_seg);
	    }
            PathSegment* new_segment = new PathSegment(head,tail);
            new_path->add_segment(new_segment);
	    added = true;
    	}
    }
    if(added == true){
    	--curr_x;
    }
    }
    //right check
    if(added == false){
    if((curr_x + 1 == target_x)&& //checking for sink
    (curr_y == target_y)){
	    Point head(curr_x, curr_y);
	    Point tail(curr_x + 1, curr_y);
	    prev_dir = curr_dir;
	    curr_dir = 2;
	    if((curr_dir != prev_dir) && (prev_dir != 0)){
		Point top(-10, -10);
		Point bottom(-10, -10);
            	PathSegment* spec_seg = new PathSegment(top, bottom);
            	new_path->add_segment(spec_seg);
	    }
            PathSegment* new_segment = new PathSegment(head,tail);
            new_path->add_segment(new_segment);
	    added = true;
	    source_found = true;
	    if(intersection == false){
                 grid2.at(curr_y).at(curr_x + 1) = NULL;
	    }
	    break;
    }
    if((curr_x + 1 < width) && (curr_y < height) && (curr_y > -1)){//inside the grid
	if((grid2.at(curr_y).at(curr_x + 1) != NULL)&& //grid is valid to right
    	(grid2.at(curr_y).at(curr_x + 1)->get_cost() == curr_lees)){ //checks that cost is one less
	    Point head(curr_x, curr_y);
	    Point tail(curr_x + 1, curr_y);
	    prev_dir = curr_dir;
	    curr_dir = 2;
	    if((curr_dir != prev_dir) && (prev_dir != 0)){
		Point top(-10, -10);
		Point bottom(-10, -10);
            	PathSegment* spec_seg = new PathSegment(top, bottom);
            	new_path->add_segment(spec_seg);
	    }
            PathSegment* new_segment = new PathSegment(head,tail);
            new_path->add_segment(new_segment);
	    added = true;
    	}
    }
    if(added == true){
        ++curr_x; 
    }
    }
    

    
    //up check
    if(added == false){
    if((curr_x == target_x)&& //checking for sink
    (curr_y - 1 == target_y)){
	    Point head(curr_x, curr_y);
	    Point tail(curr_x, curr_y - 1);
	    prev_dir = curr_dir;
	    curr_dir = 3;
	    if((curr_dir != prev_dir) && (prev_dir != 0)){
		Point top(-10, -10);
		Point bottom(-10, -10);
            	PathSegment* spec_seg = new PathSegment(top, bottom);
            	new_path->add_segment(spec_seg);
	    }
            PathSegment* new_segment = new PathSegment(head,tail);
            new_path->add_segment(new_segment);
	    added = true;
	    source_found = true;
	    if(intersection == false){
	        grid2.at(curr_y - 1).at(curr_x) = NULL;
	    }
	    break;
    }

    if((curr_x > -1) && (curr_y - 1 < height) && (curr_y - 1 > -1)){//inside the grid
	if((grid2.at(curr_y - 1).at(curr_x) != NULL)&& //grid is valid to up
   	(grid2.at(curr_y - 1).at(curr_x)->get_cost() == curr_lees)){ //checks that cost is one less

	    Point head(curr_x, curr_y);
	    Point tail(curr_x, curr_y - 1);
	    prev_dir = curr_dir;
	    curr_dir = 3;
	    if((curr_dir != prev_dir) && (prev_dir != 0)){
		Point top(-10, -10);
		Point bottom(-10, -10);
            	PathSegment* spec_seg = new PathSegment(top, bottom);
            	new_path->add_segment(spec_seg);
	    }
            PathSegment* new_segment = new PathSegment(head,tail);
            new_path->add_segment(new_segment);
	    added = true;
    	}
    }
    if(added == true){
    --curr_y; 
    }
    }
    
    
    //down check
    if(added == false){
    if((curr_x == target_x)&& //checking for sink
    (curr_y + 1 == target_y)){
	    Point head(curr_x, curr_y);
	    Point tail(curr_x, curr_y + 1);
	    prev_dir = curr_dir;
	    curr_dir = 3;
	    if((curr_dir != prev_dir) && (prev_dir != 0)){
		Point top(-10, -10);
		Point bottom(-10, -10);
            	PathSegment* spec_seg = new PathSegment(top, bottom);
            	new_path->add_segment(spec_seg);
	    }
            PathSegment* new_segment = new PathSegment(head,tail);
            new_path->add_segment(new_segment);
	    added = true;
	    source_found = true;
	    if(intersection == false){
	    	grid2.at(curr_y + 1).at(curr_x) = NULL;
	    }
	    break;
    }
    if((curr_x > -1) && (curr_y + 1 < height) && (curr_y + 1 > -1)){//inside the grid
	if((grid2.at(curr_y + 1).at(curr_x) != NULL)&& //grid is valid to down
    	(grid2.at(curr_y + 1).at(curr_x)->get_cost() == curr_lees)){ //checks that cost is one less
	    Point head(curr_x, curr_y);
	    Point tail(curr_x, curr_y + 1);
	    prev_dir = curr_dir;
	    curr_dir = 4;	    
	    if((curr_dir != prev_dir) && (prev_dir != 0)){
		Point top(-10, -10);
		Point bottom(-10, -10);
            	PathSegment* spec_seg = new PathSegment(top, bottom);
            	new_path->add_segment(spec_seg);
	    }
            PathSegment* new_segment = new PathSegment(head,tail);
            new_path->add_segment(new_segment);
	    added = true;
    	}
    }
    if(added == true){
        ++curr_y; 
    }
    }

}



return new_path;
}


vector<Path*> Grid2::test_algorithm(bool intersections) {
    bool intersection = intersections;//checks if you can intersect or not
    int num_routes = all_routes.size();
    vector<Path*> paths; //this will hold all our paths
    for(int current_route = 0; current_route < num_routes; ++current_route)
    {
 
    bool found = false;  
    int height = all_routes.at(current_route).height;
    int width = all_routes.at(current_route).width;
    int ending_x = all_routes.at(current_route).sink.x;
    int ending_y = all_routes.at(current_route).sink.y;
    int starting_x = all_routes.at(current_route).source.x;
    int starting_y = all_routes.at(current_route).source.y;

    //Only output, helps so you don't have to look at test files
    std::cout << "PATH " << current_route << ": ";
    std::cout << "(" << starting_x << "," << starting_y << ")";
    std::cout << " -> ";
    std::cout << "(" << ending_x << "," << ending_y << ")" << endl;

    //node is in blocker or out of grid
    if(grid2.at(starting_y).at(starting_x) == NULL)
    {
	std::cout << "adding empty path source" << endl;
	Path* curr_path = new Path();
	paths.push_back(curr_path);
	found = true;
	
    }
    else{
         grid2.at(starting_y).at(starting_x)->set_cost(-1);//sets the first node to be the source
     
    std::list<Node*> node_q; //keeps track of nodes we need to visit
    int lees_num = -1;
    
    
    Node* current_node;
    node_q.push_back(this->get_node(starting_x, starting_y));//currently only the source for our route is in the queue   
    while(!node_q.empty()){
    current_node = node_q.front();
    node_q.pop_front();
    int curr_x = current_node->get_x();
    int curr_y = current_node->get_y();




    //left check
    lees_num = grid2.at(curr_y).at( curr_x)->get_cost() + 1;
    if(lees_num == 0){
	    lees_num = 1;
    }
    
    if(!found){
    if((curr_x - 1 == ending_x)&& //checking for sink
    (curr_y == ending_y)){
	    found = true;
    	    break;
    }

    if((curr_x - 1 > -1) && (curr_y < height) && (curr_y > -1)){
    	if((grid2.at(curr_y).at(curr_x - 1) != NULL)&& //grid is valid to left
    	(grid2.at(curr_y).at(curr_x - 1)->get_cost() == 0)){ //checks that cost is 0
    		grid2.at(curr_y).at(curr_x - 1)->set_cost(lees_num); //sets a cost
		node_q.push_back(this->get_node(curr_x - 1, curr_y));
    	}
    }
    }
    //right check
    if(!found){
    if((curr_x + 1 == ending_x)&& //checking for sink
    (curr_y == ending_y)){
	    found = true;
    	    break;
    }
    if((curr_x + 1 < width) && (curr_y < height) && (curr_y > -1)){
    	if((grid2.at(curr_y).at(curr_x + 1) != NULL)&& //grid is valid to left
    	(grid2.at(curr_y).at(curr_x + 1)->get_cost() == 0)){ //checks that cost is 0
    		grid2.at(curr_y).at(curr_x + 1)->set_cost(lees_num); //sets a cost
		node_q.push_back(this->get_node(curr_x + 1, curr_y));
    	}
    }
    }
    
    //up check
    if(!found){ 
    if((curr_x == ending_x)&& //checking for sink
    (curr_y - 1 == ending_y)){
	    found = true;
//	    std::cout << "found up:" << endl;  
    	    break;
    }
    if((curr_x  > -1) && (curr_x < width) && (curr_y - 1 > -1)){
    	if((grid2.at(curr_y - 1).at(curr_x) != NULL)&& //grid is valid to left
    	(grid2.at(curr_y - 1).at(curr_x)->get_cost() == 0)){ //checks that cost is 0
    		grid2.at(curr_y - 1).at(curr_x)->set_cost(lees_num); //sets a cost
		node_q.push_back(this->get_node(curr_x, curr_y - 1));
    	}
    }
    }
    //down check
    if(!found){
    if((curr_x == ending_x)&& //checking for sink
    (curr_y + 1 == ending_y)){
	    found = true;
    	    break;
    }
    if((curr_x > -1) && (curr_x < width) && (curr_y + 1 < height)){
    	if((grid2.at(curr_y + 1).at(curr_x) != NULL)&& //grid is valid to left
    	(grid2.at(curr_y + 1).at(curr_x)->get_cost() == 0)){ //checks that cost is 0
    		grid2.at(curr_y + 1).at(curr_x)->set_cost(lees_num); //sets a cost
		node_q.push_back(this->get_node(curr_x, curr_y + 1));
    	}
    } 
    }
}



    if(found == true){//if we found the sink then we can add a path otherwise add empty path
	Path* curr_path = traceback(lees_num, intersection, starting_x, starting_y, ending_x, ending_y, height, width);
	paths.push_back(curr_path);
    }
    else{
	std::cout << "adding empty path" << endl;
	Path* curr_path = new Path();
	paths.push_back(curr_path);
    }
    reset_costs(0);
    }
}
    

    return paths;
}









