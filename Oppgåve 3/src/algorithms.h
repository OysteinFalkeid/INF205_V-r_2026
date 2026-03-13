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