#include "algorithms.h"





void strongconnect(const db::Node* const node_ptr, tarajans_control_structure& controller){
    controller.map_index[node_ptr] = controller.index;
    controller.map_lowlink[node_ptr] = controller.index;
    controller.index++;
    controller.stack.push(node_ptr);
    controller.map_on_stack[node_ptr] = true;

    for (const auto& edge : node_ptr->edges){
        if (controller.map_index.find(edge->pointing_to_node) == controller.map_index.end()){
            strongconnect(edge->pointing_to_node, controller);
            controller.map_lowlink[node_ptr] = std::min(controller.map_lowlink[node_ptr], controller.map_lowlink [edge->pointing_to_node]);
        } else if (controller.map_on_stack.find(edge->pointing_to_node) != controller.map_on_stack.end()){
            if (controller.map_on_stack[edge->pointing_to_node]){
                controller.map_lowlink[node_ptr] = std::min(controller.map_lowlink[node_ptr], controller.map_index[edge->pointing_to_node]);
            }
        }
    }

    if (controller.map_lowlink[node_ptr] == controller.map_index[node_ptr]){
        std::string return_string;
        while(true){
            const db::Node *node_ptr_in_stack = controller.stack.top();
            controller.stack.pop();
            controller.map_on_stack.erase(node_ptr_in_stack);

            return_string += node_ptr_in_stack->label + " ";

            if (node_ptr == node_ptr_in_stack){
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
std::list<std::string> tarjans_algorithm(const db::Graph* const graph){
    tarajans_control_structure controller;

    for (const auto& node_ptr : graph->get_node_list()){
        if (controller.map_index.find(node_ptr) == controller.map_index.end()){
            strongconnect(node_ptr, controller);
        }
    }

    return controller.return_list;
}