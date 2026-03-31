#include "algorithms.h"

// recursive strong connnection algorithm. 
// The algorithom runs recursively until every edge in a strong connection is tested. 
// Then the algorithm stores these nodes as visited and return a list of nodes.
void strongconnect(std::string node, tarajans_control_structure& controller){
    // uppdate the index of the node
    controller.map_index[node] = controller.index;
    // uppdate the lowlink of the node.
    // lowlink is the same number for every strongly connected node.
    controller.map_lowlink[node] = controller.index;
    // incrementing the controller
    controller.index++;
    // add node to first in last out stack
    controller.stack.push(node);
    // store node as visited
    controller.map_on_stack[node] = true;

    // search all edges from the node
    for (const auto& edge : controller.graph->get_node_edges(node)){
        // test if the next node is on stack
        if (controller.map_index.find(edge.second) == controller.map_index.end()){
            // run strong connect algorithm on the next node
            strongconnect(edge.second, controller);
            // update lowlink based on next node if strong connect
            controller.map_lowlink[node] = std::min(controller.map_lowlink[node], controller.map_lowlink [edge.second]);
        } 
        // update low link if next node is on stack
        else if (controller.map_on_stack[edge.second]){
            controller.map_lowlink[node] = std::min(controller.map_lowlink[node], controller.map_index[edge.second]);
        }
    }

    // gennerate list of strong connections after recurtion ends.
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
        // remove last " " from string
        return_string.pop_back();
        // add end comand char "."
        return_string += ".";
        controller.return_list.push_back(return_string);
    }
}

// using pas by pointer to reduse copy.
std::list<std::string> tarjans_algorithm( db::Node_database_interface* graph){
    // setting upp a controller
    tarajans_control_structure controller;
    // adding graph pointer to controller
    controller.graph = graph;

    // itterating over every node in graph
    for (auto& node : graph->get_nodes()){
        // testing if node has been visited.
        if (controller.map_index.find(node) == controller.map_index.end()){
            // passing node label and controller to run recursive algorithm.
            strongconnect(node, controller);
        }
    }

    // returns a list of string containing " " sepparated node labels
    // every strong connection ends in a "."
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
// the recursive algorithm for regular path is based on depth first.
// the algorithm filters edges based on a predefined path.
void DFS(std::string node, rpq_control_structure& controller){
    // setting node as visited to remove possibilities of searching in circles.
    controller.map_visited[node] = true;
    // storing the index for this recursion in case of backtracking.
    unsigned long column_index = controller.path_index_column;

    for (auto& edge : controller.graph->get_node_edges(node)){
        // overwriting index in case of backtracking
        controller.path_index_column = column_index;
        // is the nex node new in this serch?
        if (controller.map_visited.find(edge.second) == controller.map_visited.end()){
            // is the label of the edge correct?
            if (controller.paths[controller.path_index_row][column_index] == edge.first){
                //incrementing the index to the next edge label.
                controller.path_index_column++;

                // if the path is complete add the nodes to the list
                if (controller.paths[controller.path_index_row].size() <= controller.path_index_column){
                    controller.return_list.push_back({controller.start_node, edge.second});
                }
                // recursively calling for depth first.
                DFS(edge.second, controller);
            }
        }
    }
}

// sourced https://en.wikipedia.org/wiki/Regular_path_query
// The algorithm extracts tow paths from a path file.
// These are used as filters for the search.
std::list<std::string> regular_path_querying(db::Node_database_interface* graph, std::string file_path){
    // setting upp a controller
    rpq_control_structure controller;
    // adding graph to the controller
    controller.graph = graph;

    // reading path from file
    std::ifstream in_file(file_path);
    std::string line;
    std::string connection;
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
    
    // read nodes from the graph
    std::list<std::string> node_list = graph->get_nodes();
    // list of string to be returned
    std::list<std::string> return_list;
    // nodes found using path a
    std::list<std::pair<std::string, std::string>> nodes_found_a;
    // nodes found using path b
    std::list<std::pair<std::string, std::string>> nodes_found_b;

    // querry path a for node pairs
    for (const auto& node : node_list){
        controller.path_index_column = 0;
        controller.map_visited.clear();
        controller.start_node = node;
        DFS(node, controller);
    }
    nodes_found_a = controller.return_list;

    // querry path b for node pairs
    controller.path_index_row = 1;
    controller.return_list.clear();
    for (const auto& node_ptr : node_list){
        controller.path_index_column = 0;
        controller.map_visited.clear();
        controller.start_node = node_ptr;
        DFS(node_ptr, controller);
    }
    nodes_found_b = controller.return_list;
    
    std::list<std::pair<std::string, std::string>> intersection;

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
        return_list.push_back(pair.first + " " + pair.second);
    }

    return return_list;
}

