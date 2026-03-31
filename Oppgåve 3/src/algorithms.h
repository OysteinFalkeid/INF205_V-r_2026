#include "graph.h"
#include <stack>
#include <algorithm>
#include <iostream>
#include <utility> 

#include <set>


// creating a controller insted of a dedicated class
struct tarajans_control_structure{
    db::Node_database_interface* graph;

    std::stack<std::string> stack;
    std::unordered_map<std::string, int> map_index;
    std::unordered_map<std::string, int> map_lowlink;
    std::unordered_map<std::string, bool> map_on_stack;
    int index = 0;

    std::list<std::string> return_list;
};

void strongconnect(std::string node_ptr, tarajans_control_structure& controller);
std::list<std::string> tarjans_algorithm(db::Node_database_interface* graph);

// claude generated code for converting .dat file to .dot file.
// convert .dot file to png using "dot -Tpng graph.dot -o graph.png" in linux terminal.
void graphFileToDot(const std::string& inputFile, const std::string& dotFile);

// creating a controller insted of a dedicated class
struct rpq_control_structure{
    db::Node_database_interface* graph;
    // only tow paths but we use a matrix for possible expansion.
    std::vector<std::vector<std::string>> paths;
    // because a matrix is used we must store the row that is in use.
    long unsigned int path_index_row = 0;
    long unsigned int path_index_column = 0;

    std::unordered_map<std::string, bool> map_visited;
    std::string start_node;
    std::list<std::pair<std::string, std::string>> return_list;
};

void DFS(std::string node, rpq_control_structure& controller);
std::list<std::string> regular_path_querying(db::Node_database_interface* graph, std::string file_path);