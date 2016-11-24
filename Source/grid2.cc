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
                                                                                                                                                                                                                                   1,16          Top
