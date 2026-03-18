#include "graph.h"
#include <stack>
#include <algorithm>
#include <iostream>
#include <utility> 

#include <set>


struct tarajans_control_structure{
    db::Graph* graph;

    std::stack<std::string> stack;
    std::unordered_map<std::string, int> map_index;
    std::unordered_map<std::string, int> map_lowlink;
    std::unordered_map<std::string, bool> map_on_stack;
    int index = 0;

    std::list<std::string> return_list;
};

void strongconnect(std::string node_ptr, tarajans_control_structure& controller);
std::list<std::string> tarjans_algorithm(db::Graph* graph);

// claude generated code for converting .dat file to .dot file.
// convert .dot file to png using "dot -Tpng graph.dot -o graph.png" in linux terminal.
void graphFileToDot(const std::string& inputFile, const std::string& dotFile);


struct rpq_control_structure{
    // only tow paths but i used a matrix because i was lazy.
    // this cold be changed later to tow separate vectors or a different more optimal type.
    std::vector<std::vector<std::string>> paths;
    // because a matrix is used we must store the row that is in use.
    long unsigned int path_index_row = 0;
    long unsigned int path_index_column = 0;


    std::unordered_map<const db::Node*, bool> map_visited;

    db::Node* start_node;
    std::list<std::pair<db::Node*, db::Node*>> return_list;
};

void DFS(const std::vector<db::Node *>& node_list, const db::Node* node_pointer, rpq_control_structure& controller);

std::list<std::string> regular_path_querying(const db::Graph* const graph, std::string file_path);