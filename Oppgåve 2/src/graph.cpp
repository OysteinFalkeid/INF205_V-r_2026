#include "graph.h"

namespace db{


    Node_controller::Node_controller(/* args */){
        
    }

    Node_controller::Node_controller(std::string file_path){
        read_file(file_path);
    }

    
    Node_controller::~Node_controller(){
        clear();
    }

    bool Node_controller::read_file(std::string file_path){
        std::ifstream file_inn(file_path);
        if (!file_inn){
            return false;
        }
    
        buffer.str("");
        buffer.clear();
        buffer << file_inn.rdbuf();
        file_inn.close();
    
        parse_buffer();
    
        return true;
    }
    
    bool Node_controller::write_to_file(std::string file_path){
        std::ofstream file_out(file_path);
        if (!file_out){
            return false;
        }
    
        file_out << *this << std::endl;
        file_out.close();
    
        return true;
    }

    // #### <Node> ############################################################
    
    Node::Node(std::string node_label){
        label = node_label;
    }
    
    Node::~Node(){
        clear();
    }

    void Node::clear(){
        for (auto& item : edges){
            delete item;
        }
        edges.clear();
    }
    
    void Node::add_edge(std::string edge_label, Node* node_ptr){
        Edge* edge_ptr = new Edge(edge_label, node_ptr);
        edges.push_back(edge_ptr);
    }
    
    void Node::remove_edge(Node* node_ptr)
    {
        // edges is a linked list
        //assigning an iterator to read out values from the list
        auto it = edges.begin();
        // running a while loop over every element.
        //this loop runs until the iterator has the value of the end ellement in the list
        while (it != edges.end())
        {
            // extracting the pointer from the list using the iterator.
            Edge* current_edge = *it;
            
            //testing if the edge is pointing to the specified node
            if (current_edge->pointing_to_node == node_ptr)
            {
                // deleting the edge. The edge is responsible for cleanup in the node that is pointed to.
                delete current_edge;
                // deletes the element the iterator is pointing at. 
                // if there are multiple pointers to the same edge this ensures only the specified element is deleted.
                // this also increments the iterator to ensure the iterator points to a valid element in the list.
                it = edges.erase(it);
            } else {
                //if the edge is not pointing to the node specified the iterator is incremented.
                ++it;
            }
        }
    }
    
    
    
    
    
    // #### <Edge> ############################################################
    
    Edge::Edge(std::string edge_label, Node* node_ptr){
        label = edge_label;
        pointing_to_node = node_ptr;
    }
    
    Edge::~Edge(){
    }
    
    
    
    
    
    
    
    // #### <Graph> ############################################################


    Graph::Graph(const Graph& other){
        for (auto& pair : other.node_pointer_list){
            for (auto& item : pair.second->edges){
                insert_edge(pair.second->label, item->label, item->pointing_to_node->label);
            }
        }
    }

    Graph& Graph::operator=(const Graph& other){
        if (this == &other){
            return *this;
        }

        clear();
        for (auto& pair : other.node_pointer_list){
            for (auto& item : pair.second->edges){
                insert_edge(pair.second->label, item->label, item->pointing_to_node->label);
            }
        }

        return *this;
    }

    Graph::Graph(Graph&& other){
        node_pointer_list = other.node_pointer_list;
        other.node_pointer_list.clear();

    }

    Graph& Graph::operator=(Graph&& other){
        clear();
        node_pointer_list = other.node_pointer_list;
        other.node_pointer_list.clear();
        return *this;
    }

    void Graph::clear(){
        for(auto& pair : node_pointer_list){
            delete pair.second;
        }
        node_pointer_list.clear();
    }
    
    
    void Graph::insert_edge(std::string node_a_label, std::string edge_label, std::string node_b_label){
        if (node_pointer_list[node_a_label] == nullptr) {
            node_pointer_list[node_a_label] = new Node(node_a_label);
        }
        if (node_pointer_list[node_b_label] == nullptr) {
            node_pointer_list[node_b_label] = new Node(node_b_label);
        }
    
        node_pointer_list[node_a_label]->add_edge(edge_label, node_pointer_list[node_b_label]);
    
    }
    
    void Graph::remove_node(std::string node_label){
        delete node_pointer_list[node_label];
        node_pointer_list.erase(node_label);
    }
    
    void Graph::disconnect(std::string node_a_label, std::string node_b_label){
        if (node_pointer_list[node_a_label] && node_pointer_list[node_b_label]) {
            node_pointer_list[node_a_label]->remove_edge(node_pointer_list[node_b_label]);
        }
    }
    

    
    void Graph::parse_buffer(){
    
        std::string line;
        while (std::getline(buffer, line)) {
            
            std::stringstream stringstream(line);
            std::string node_label_a;
            std::string edge_label;
            std::string node_label_b;
    
            stringstream >> node_label_a >> edge_label >> node_label_b;
            node_label_b.pop_back();
    
            this->insert_edge(node_label_a, edge_label, node_label_b);
    
        }
    }
    
    
    
    // #### <Matrix> ############################################################
    // TODO

    // TODO
    void Matrix::parse_buffer(){
        std::string line;
        while (std::getline(buffer, line)) {
            
            std::stringstream stringstream(line);
            std::string node_label_a;
            std::string edge_label;
            std::string node_label_b;
    
            stringstream >> node_label_a >> edge_label >> node_label_b;
            node_label_b.pop_back();
    
            this->insert_edge(node_label_a, edge_label, node_label_b);
        }
    }
    
    // TODO
    void Matrix::clear(){

    }

    // TODO
    void Matrix::insert_edge(std::string node_a_label, std::string edge_label, std::string node_b_label){
        for (auto node : nodes){
            if (node == node_a_label){
                
            }
        }
    }

    // TODO
    void Matrix::remove_node(std::string node_label){

    }

    // TODO
    void Matrix::disconnect(std::string node_a_label, std::string node_b_label){

    }
    
    
    // #### <overloaders> ############################################################
    
    std::ostream& operator<<(std::ostream& os, const Graph& graph) {
        for(auto& pair : graph.node_pointer_list){
            os << pair.second;
        }
        return os;
    }

    // TODO
    std::ostream& operator<<(std::ostream& os, const Matrix& graph) {
        return os;
    }
    
    std::ostream& operator<<(std::ostream& os, const Node* node) {
        if (node){
            // os << node->label << ":" << std::endl;
            for(auto& item : node->edges){
                os << node->label << " " << item;
            }
        } else {
            os << "nullptr";
        }
        return os;
    }
    
    std::ostream& operator<<(std::ostream& os, const Edge* edge) {
        if (edge){
            os << edge->label << " ";
            if(edge->pointing_to_node){
                os << edge->pointing_to_node->label;
            } else {
             os << "nullptr";
            }
        } else{
            os << "nullptr";
        }
        os  << "." << std::endl;   
        return os;
    }
}
