#include "graph.h"

namespace db{


    Node_controller::Node_controller(/* args */){

    }

    Node_controller::Node_controller(std::string file_path){
        std::cout << "virtual Method " << file_path;
    }


    bool Node_controller::read_file(std::string file_path){
        std::cout <<"1";
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

    Graph::~Graph(){
        clear();
    }

    Graph::Graph(const Graph& other): Node_controller(){
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

    void Graph::cleanup(){
        bool flag = 0;
        for (auto& pair_i : node_pointer_list){
            if (pair_i.second->edges.size() == 0){
                for(auto& pair_j : node_pointer_list){
                    for (auto& item : pair_j.second->edges){
                        if (item->pointing_to_node == pair_i.second){
                            break;
                            flag = true;
                        }
                    }
                }
                if (!flag){
                    remove_node(pair_i.second->label);
                }
                flag = false;
            }
        }
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
        Node* target = node_pointer_list[node_label];

        for (auto& pair : node_pointer_list){
            
            auto it = pair.second->edges.begin();
            while (it != pair.second->edges.end()){
                if ((*it)->pointing_to_node == target){
                    delete *it; 
                    it = pair.second->edges.erase(it); 
                } else{
                    ++it;
                }
            }
        }

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

            insert_edge(node_label_a, edge_label, node_label_b);

        }
    }

    bool Graph::read_file(std::string file_path){
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

    bool Graph::write_to_file(std::string file_path){
        std::ofstream file_out(file_path);
        if (!file_out){
            return false;
        }

        file_out << *this << std::endl;
        file_out.close();

        return true;
    }


    // #### <Matrix> ############################################################

    Matrix::~Matrix(){
        clear();
    }

    void Matrix::parse_buffer(){
        std::string line;
        while (std::getline(buffer, line)) {

            std::stringstream stringstream(line);
            std::string node_label_a;
            std::string edge_label;
            std::string node_label_b;

            stringstream >> node_label_a >> edge_label >> node_label_b;
            node_label_b.pop_back();

            insert_edge(node_label_a, edge_label, node_label_b);
        }
    }

    void Matrix::clear(){

    }

    void Matrix::insert_edge(std::string node_a_label, std::string edge_label, std::string node_b_label){
        // std::cout << node_a_label;
        if (nodes.size() == 0){
            nodes.push_back(node_a_label);
            nodes.push_back(node_b_label);
        }

        if (std::find(nodes.begin(), nodes.end(), node_a_label) == nodes.end()) {
            nodes.push_back(node_a_label);
        }

        if (std::find(nodes.begin(), nodes.end(), node_b_label) == nodes.end()) {
            nodes.push_back(node_b_label);
        }

        for (std::size_t i=0; i<nodes.size(); i++){

            if (nodes[i] == node_a_label){
                for (std::size_t j=0; j<nodes.size(); j++){
                    if (nodes[j] == node_b_label){
                        
                        if (matrix.size() <= i) {
                            matrix.resize(i+1);
                        }
                        if (matrix[i].size() <= j) {
                            matrix[i].resize(j+1);
                        }
                        matrix[i][j].push_back(edge_label);
                    }
                }
            }
        }
    }


    void Matrix::remove_node(std::string node_label){

        for (long unsigned int i=0; i<nodes.size(); i++){
            if (nodes[i] == node_label){

                for (auto& row : matrix)
                {
                    if (i < row.size())
                        row.erase(row.begin() + i);
                }


                matrix.erase(matrix.begin() + i);

                nodes.erase(nodes.begin() + i);
            }
        }
    }

    void Matrix::disconnect(std::string node_a_label, std::string node_b_label){
        for (long unsigned int i=0; i<nodes.size(); i++){
            if (nodes[i] == node_a_label){
                for (long unsigned int j=0; j<nodes.size(); j++){
                    if (nodes[j] == node_b_label){
                        matrix[i][j].clear();
                    }
                }
            }
        }
    }

    bool Matrix::read_file(std::string file_path){
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

    bool Matrix::write_to_file(std::string file_path){
        std::ofstream file_out(file_path);
        if (!file_out){
            return false;
        }

        file_out << *this << std::endl;
        file_out.close();

        return true;
    }


}


// #### <overloaders> ############################################################

std::ostream& operator<<(std::ostream& os, const db::Node_controller& node_controller) {
    os << &node_controller;
    return os;
}

std::ostream& operator<<(std::ostream& os, const db::Graph& graph) {
    for(auto& pair : graph.node_pointer_list){
        os << pair.second;
    }
    return os;
}


std::ostream& operator<<(std::ostream& os, const db::Matrix& matrix) {
    for (std::size_t i=0; i<matrix.nodes.size(); i++){
        if (matrix.matrix.size() <= i){
            break;
        }
        for (std::size_t j=0; j<matrix.nodes.size(); j++){
            if (matrix.matrix[i].size() <= j) {
                break;
            }
            for (auto& string : matrix.matrix[i][j]){
                os << matrix.nodes[i] << " " << string << " " << matrix.nodes[j] << "." << std::endl;
            }
        }
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const db::Node* node) {
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

std::ostream& operator<<(std::ostream& os, const db::Edge* edge) {
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
