
#include "graph.h"

int main(int /*argc*/, char** /*argv*/) 
{

    // 1 Normal constructor
    //MyArray a();

    // 2 Copy constructor
    //MyArray b = a;

    // 3 Copy assignment
    //MyArray c();
    //c = a;

    // 4 Move constructor
    //MyArray d = createArray();

    // 5 Move assignment
    //MyArray e(2);
    //e = createArray();

    {

        db::Graph my_graph;
        if (!my_graph.read_file("graph_inn.txt")){
            return 1;
        }
        if (!my_graph.write_to_file("graph_0.txt")){
            return 1;
        }
    }

    {
        db::Graph my_graph;
        
        my_graph.insert_edge("node_a_label", "edge_label", "node_b_label");
        my_graph.insert_edge("node_a_label", "edge_label", "node_c_label");
        my_graph.insert_edge("node_a_label", "edge_label", "node_d_label");
    
        
        my_graph.insert_edge("node_b_label", "edge_label", "node_c_label");
        my_graph.insert_edge("node_b_label", "edge_label", "node_e_label");
        my_graph.insert_edge("node_b_label", "edge_label", "node_f_label");
        
        std::cout << "Printing graph\n";
        std::cout << my_graph << std::endl;
    
        my_graph.disconnect("node_b_label", "node_c_label");
        
        std::cout << "Printing graph after removing edge\n";
        std::cout << my_graph << std::endl;
    
        if (!my_graph.write_to_file("graph_1.txt")){
            return 1;
        }
    }

    {
        db::Graph my_graph;
        
        my_graph.insert_edge("node_a_label", "edge_label", "node_a_label");
        my_graph.insert_edge("node_a_label", "edge_label", "node_g_label");
        my_graph.insert_edge("node_a_label", "edge_label", "node_h_label");
    
        
        my_graph.insert_edge("node_b_label", "edge_label", "node_c_label");
        my_graph.insert_edge("node_b_label", "edge_label", "node_e_label");
        my_graph.insert_edge("node_b_label", "edge_label", "node_f_label");

        my_graph.remove_node("node_c_label");
        my_graph.remove_node("node_e_label");
        my_graph.remove_node("node_f_label");
        
        std::cout << "printing after making b floating" << std::endl;
        std::cout << my_graph << std::endl;
    }

    {
        db::Matrix my_matrix;
        // my_matrix.insert_edge("node_a_label", "edge_label", "node_b_label");
        // my_matrix.insert_edge("node_c_label", "edge_label", "node_d_label");
        if (!my_matrix.read_file("graph_inn.txt")){
            return 1;
        }
        // for (auto& string : my_matrix.nodes){
        //     std::cout << string;
        // }
        std::cout << "printing content of matrix" << std::endl;
        std::cout << my_matrix;
    }
    

}