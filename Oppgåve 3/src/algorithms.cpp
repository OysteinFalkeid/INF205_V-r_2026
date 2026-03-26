#include "algorithms.h"





void strongconnect(std::string node, tarajans_control_structure& controller){
    controller.map_index[node] = controller.index;
    controller.map_lowlink[node] = controller.index;
    controller.index++;
    controller.stack.push(node);
    controller.map_on_stack[node] = true;
    // std::cout << node << " at start: index " << controller.map_index[node] << " lowlink " << controller.map_lowlink[node] << std::endl; 

    for (const auto& edge : controller.graph->get_node_edges(node)){
        if (controller.map_index.find(edge.second) == controller.map_index.end()){
            // std::cout << "recurtion" << std::endl;
            strongconnect(edge.second, controller);
            controller.map_lowlink[node] = std::min(controller.map_lowlink[node], controller.map_lowlink [edge.second]);
        } else if (controller.map_on_stack[edge.second]){
            // std::cout << "found tail " << controller.map_on_stack[edge.second] << " " << edge.second << std::endl;
            controller.map_lowlink[node] = std::min(controller.map_lowlink[node], controller.map_index[edge.second]);
        }
        // std::cout << node << " : index " << controller.map_index[node] << " lowlink " << controller.map_lowlink[node] << std::endl; 
    }

    if (controller.map_lowlink[node] == controller.map_index[node]){
        std::string return_string;
        while(true){
            std::string node_in_stack = controller.stack.top();
            controller.stack.pop();
            controller.map_on_stack[node_in_stack] = false;


            // std::cout << node_in_stack << " on stack : index " << controller.map_index[node_in_stack] << " lowlink " << controller.map_lowlink[node_in_stack] << " : " << node << std::endl; 

            return_string += node_in_stack + " ";

            if (node == node_in_stack){
                break;
            }
        }
        return_string.pop_back();
        return_string += ".";
        controller.return_list.push_back(return_string);
    }
}

//using pass by pointer with const to ensure the object is not changed.
//this displays to the user that the graph is not copied but passed using pointer.
std::list<std::string> tarjans_algorithm( db::Graph* graph){
    tarajans_control_structure controller;
    controller.graph = graph;

    for (auto& node : graph->get_nodes()){
        if (controller.map_index.find(node) == controller.map_index.end()){
            strongconnect(node, controller);
        }
    }

    return controller.return_list;
}




// claude generated code for converting .dat file to .dot file.
// convert .dot file to png using "dot -Tpng graph.dot -o graph.png" in linux terminal.
void graphFileToDot(const std::string& inputFile, const std::string& dotFile) {
    // these comments are added my humans for better understanding the code
    // defines an inputfile and an outputfile
    std::ifstream in(inputFile);
    std::ofstream out(dotFile);

    // The .dot file format starts with a header describing the graph structure and shape.
    out << "digraph G {\n";
    out << "    node [shape=circle];\n";

    // using lineskip insted of "." this might cause issues if lineskip is missing.
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        if (!line.empty() && line.back() == '.') line.pop_back();

        // defining 3 string variables in one line.
        std::string from, rel, to;
        //converting the string line to a string stream.
        std::istringstream ss(line);
        ss >> from >> rel >> to;

        // testing if the nodes exist and rewriting them with different syntax
        if (!from.empty() && !to.empty()) {
            // different style for self pointers
            if (from == to)
                out << "    " << from << " -> " << to << " [label=\"" << rel << "\" style=dashed];\n";
            else
                out << "    " << from << " -> " << to << " [label=\"" << rel << "\"];\n";
        }
    }

    out << "}\n";
}

// sourced https://en.wikipedia.org/wiki/Depth-first_search 
void DFS(const db::Node* node_pointer, rpq_control_structure& controller){
    // setting node as visited to remove possibilities of searching in circles.
    controller.map_visited[node_pointer] = true;
    // storing the index for this recursion in case of backtracking.
    unsigned long column_index = controller.path_index_column;

    for (const auto& edge : node_pointer->edges){
        // overwriting index in case of backtracking
        controller.path_index_column = column_index;
        // is the nex node new in this serch?
        if (controller.map_visited.find(edge->pointing_to_node) == controller.map_visited.end()){
            // is the label of the edge corect?
            if (controller.paths[controller.path_index_row][column_index] == edge->label){
                // debugging
                // std::cout << controller.paths[controller.path_index_row][0] << " " << controller.paths[controller.path_index_row][1] << " - " << edge->label << std::endl;
                // std::cout << controller.start_node->label << " " << node_pointer->label << " " << edge->pointing_to_node->label << std::endl;
                // ----
                
                //incrementing the index to the next edge label.
                controller.path_index_column++;

                // if the path is complete add the nodes to the list
                if (controller.paths[controller.path_index_row].size() <= controller.path_index_column){
                    controller.path_index_column = 0;
                    controller.return_list.push_back({controller.start_node, edge->pointing_to_node});
                }

                DFS(edge->pointing_to_node, controller);
            }
        }
    }
}

// sourced https://en.wikipedia.org/wiki/Regular_path_query
std::list<std::string> regular_path_querying(const db::Graph* const graph, std::string file_path){

    rpq_control_structure controller;

    std::ifstream in_file(file_path);
    std::vector<db::Node *> node_list = graph->get_node_list();


    std::string line;
    std::string connection;
    // reading from file
    while (std::getline(in_file, line)) {
        for (char c : line){
            if (c == '.'){
                std::stringstream stringstream(connection);
                connection.erase();
                std::string edge_label;
                std::vector<std::string> temp_string;
                while (stringstream >> edge_label){
                    temp_string.push_back(edge_label);
                    edge_label.erase();
                }
                controller.paths.push_back(temp_string);
                // controller.path_index_row++;

            } else {
                connection += c;
            }
        }
        connection += " ";
    }

    std::list<std::string> return_list;
    std::list<std::pair<db::Node*, db::Node*>> nodes_found_a;
    std::list<std::pair<db::Node*, db::Node*>> nodes_found_b;

    // making a list of all the first paths
    for (const auto& node_ptr : node_list){
        controller.path_index_column = 0;
        controller.map_visited.clear();
        controller.start_node = node_ptr;
        DFS(node_ptr, controller);
    }
    nodes_found_a = controller.return_list;

    // resetting and making a list of all the second paths
    controller.path_index_row = 1;
    controller.return_list.clear();
    for (const auto& node_ptr : node_list){
        controller.path_index_column = 0;
        controller.map_visited.clear();
        controller.start_node = node_ptr;
        DFS(node_ptr, controller);
    }
    nodes_found_b = controller.return_list;
    
    std::list<std::pair<db::Node*, db::Node*>> intersection;

    // comparing the list and finding diamonds
    for (auto& pair_a : nodes_found_a){
        for (auto& pair_b : nodes_found_b){
            if ((pair_a.first == pair_b.first) && (pair_a.second == pair_b.second)){
                intersection.push_back(pair_a);
            }
        }

    }

    // converting pointer to string labels
    for (auto& pair : intersection){
        return_list.push_back(pair.first->label + " " + pair.second->label);
    }

    
    return return_list;
}

