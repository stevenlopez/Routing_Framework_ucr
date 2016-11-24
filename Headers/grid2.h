#ifndef _GRID2_BASE_H_
#define _GRID2_BASE_H_

#include "node.h"
#include "path.h"
#include "problem_object.h"
#include <vector>

using std::cerr;
using std::endl;
using std::string;
using Utilities::Node;
using Utilities::Edge;
using Utilities::Path;
using Utilities::ProblemObject;


struct grid_helper{
	int height;
	int width;
	Point source;
	Point sink;
};

class Grid2 {
	private:
	    vector<vector<Node*> > grid2;
	    int num_connections;
	    vector<Path*> paths;
	    vector <grid_helper> all_routes;
	public:
	    /* Constructors/Destructors */
	    Grid2(ProblemObject* problem_object);
	    ~Grid2();

	    /* Accessors */
	    int get_width();
	    int get_height();
	    int get_num_connections();
	    Node* get_node(int x, int y);
	    Node* get_node(Point coord);
	    vector<Path*> get_paths();
	    Path* get_path(int i);

	    /* Mutators */
	    void replace_node(Node* replacement_node);
	    void set_paths(vector<Path*> paths);
	    void add_path(Path* path);
	    void replace_path(int i, Path* path);
	    void remove_path(int i);
	    void print_grid2(int i);
	    void print_cost_grid2(int i);
	    void reset_costs(int i);
	    /* Algorithms */
	    Path* traceback(int lees_num, bool intersection, int x_start, int y_start, int x_end, int y_end, int height, int width);

	    vector<Path*> test_algorithm(bool intersection);

};

#endif  //_GRID2_BASE_H_

