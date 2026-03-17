#include "graph.h"
#include <stack>
#include <algorithm>


struct tarajans_control_structure{
    std::stack<const db::Node*> stack;
    std::unordered_map<const db::Node*, int> map_index;
    std::unordered_map<const db::Node*, int> map_lowlink;
    std::unordered_map<const db::Node*, bool> map_on_stack;
    int index = 0;

    std::list<std::string> return_list;
};

void strongconnect(const db::Node* const node_ptr, tarajans_control_structure& controller);
std::list<std::string> tarjans_algorithm(const db::Graph* const graph);

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

    std::string return_string;
    std::list<std::string> return_list;
};

void DFS(const std::vector<db::Node *>& node_list, const db::Node* node_pointer, rpq_control_structure& controller);

std::list<std::string> regular_path_querying(const db::Graph* const graph, std::string file_path);