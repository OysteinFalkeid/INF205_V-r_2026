
#include "problem-2-1.h"

int main(int /*argc*/, char** /*argv*/) 
{
    Graph my_graph;
    my_graph.insert_edge("node_a_label", "edge_label", "node_b_label");
    my_graph.insert_edge("node_a_label", "edge_label", "node_c_label");
    my_graph.insert_edge("node_a_label", "edge_label", "node_d_label");

    
    my_graph.insert_edge("node_b_label", "edge_label", "node_c_label");
    my_graph.insert_edge("node_b_label", "edge_label", "node_e_label");
    my_graph.insert_edge("node_b_label", "edge_label", "node_f_label");

    std::cout << my_graph << std::endl;
    

}