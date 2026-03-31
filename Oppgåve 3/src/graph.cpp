#include "graph.h"


// adding a namespace containing all graph classes
namespace db{

    // virtual destructor
    Node_database_interface::~Node_database_interface(){
        clear();
    }

    // method to ensure all children handel memory
    void Node_database_interface::clear(){

    }

    // overloader for all children
    std::ostream& operator<<(std::ostream& os, const db::Node_database_interface& node_database_interface) {
        node_database_interface.print(os);
        return os;
    }    

    // constructor
    Node_database_interface::Node_database_interface(/* args */){

    }

    // constructor with variable
    Node_database_interface::Node_database_interface(std::string file_path){
        std::cout << "virtual Method " << file_path;
    }

    // method used by stream overloader
    void Node_database_interface::print(std::ostream& os) const {
        os << "This is an abstract class";
    }

    // virtual method for setting upp a graph from a file
    bool Node_database_interface::read_file(std::string file_path){
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

    // virtual method for writing graph data to file
    bool Node_database_interface::write_to_file(std::string file_path){
        std::ofstream file_out(file_path);
        if (!file_out){
            return false;
        }

        file_out << *this << std::endl;
        file_out.close();

        return true;
    }

    // #### <Node> ############################################################

    // constructor with label
    Node::Node(std::string node_label){
        label = node_label;
    }

    // destructor not inherited but following same structure
    Node::~Node(){
        clear();
    }
    
    // stream operator overloader
    std::ostream& operator<<(std::ostream& os, const db::Node& node) {
        node.print(os);
        return os;
    }  
    
    // printing node to string stream
    void Node::print(std::ostream& os) const{
        for(auto& item : edges){
            os << label << " " << *item;
        }
    }

    // method for memory handling upon delete
    void Node::clear(){
        for (auto& item : edges){
            delete item;
        }
        edges.clear();
    }

    // adding an edge to the node
    void Node::add_edge(std::string edge_label, Node* node_ptr){
        Edge* edge_ptr = new Edge(edge_label, node_ptr);
        edges.push_back(edge_ptr);
    }

    // removing an edge from the node 
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

    // constructor for setting up an edge with label and pointer
    Edge::Edge(std::string edge_label, Node* node_ptr){
        label = edge_label;
        pointing_to_node = node_ptr;
    }

    // destructor 
    Edge::~Edge(){
        clear();
    }

    // stream operator overloader
    std::ostream& operator<<(std::ostream& os, const db::Edge& edge) {
        edge.print(os);
        return os;
    }  

    // printing node to string stream
    void Edge::print(std::ostream& os) const{
        os << label << " ";
        if(pointing_to_node){
            os << pointing_to_node->label;
        }
        os  << "." << std::endl;
    }

    // method for memory handling upon delete
    void Edge::clear() {

    }




    // #### <Graph> ############################################################

    // Copy constructor 
    Graph::Graph(const Graph& other): Node_database_interface(){
        for (auto& pair : other.node_pointer_list){
            for (auto& item : pair.second->edges){
                insert_edge(pair.second->label, item->label, item->pointing_to_node->label);
            }
        }
    }

    // Copy asignment opperator
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
    
    // Move constructor
    Graph::Graph(Graph&& other){
        node_pointer_list = other.node_pointer_list;
        other.node_pointer_list.clear();
        
    }
    
    // Move assignment opperator
    Graph& Graph::operator=(Graph&& other){
        clear();
        node_pointer_list = other.node_pointer_list;
        other.node_pointer_list.clear();
        return *this;
    }
    
    // printing node to string stream
    void Graph::print(std::ostream& os) const{
        for(auto& pair : node_pointer_list){
            os << *pair.second;
        }
    }

    // method for memory handling upon delete
    void Graph::clear(){
        for(auto& pair : node_pointer_list){
            delete pair.second;
        }
        node_pointer_list.clear();
    }
    
    // remove unconected nodes
    void Graph::cleanup(){
        bool flag = 0;
        // iterate over every node
        for (auto& pair_i : node_pointer_list){
            // if node has no edges
            if (pair_i.second->edges.size() == 0){
                // iterate over every node again
                for(auto& pair_j : node_pointer_list){
                    // iterator over every edge in second node iteration
                    for (auto& item : pair_j.second->edges){
                        // if the node is pointed to 
                        if (item->pointing_to_node == pair_i.second){
                            flag = true;
                            break;
                        }
                    }
                }
                // the flag is false the node has no edges and is not pointed to.
                if (!flag){
                    remove_node(pair_i.second->label);
                }
                flag = false;
            }
        }
    }

    // adding edge from one node to another
    void Graph::insert_edge(std::string node_a_label, std::string edge_label, std::string node_b_label){
        // add node a if it dose not exist
        if (node_pointer_list[node_a_label] == nullptr) {
            node_pointer_list[node_a_label] = new Node(node_a_label);
        }
        // add node b if it dose not exist
        if (node_pointer_list[node_b_label] == nullptr) {
            node_pointer_list[node_b_label] = new Node(node_b_label);
        }
        // add edge from node a to node b
        node_pointer_list[node_a_label]->add_edge(edge_label, node_pointer_list[node_b_label]);

    }

    // deleta a node and edges to and from the node based on node label
    void Graph::remove_node(std::string node_label){
        // returns the pointer from a map
        Node* target = node_pointer_list[node_label];

        // search all nodes in the graph
        for (auto& pair : node_pointer_list){
            // iterate over all nodes to delete edges pointing to node to be deleted
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
        // delete the node
        delete node_pointer_list[node_label];
        node_pointer_list.erase(node_label);
    }

    // delete all edges from one node to another
    void Graph::disconnect(std::string node_a_label, std::string node_b_label){
        if (node_pointer_list[node_a_label] && node_pointer_list[node_b_label]) {
            node_pointer_list[node_a_label]->remove_edge(node_pointer_list[node_b_label]);
        }
    }


    // constructing a graph from the buffer.
    // genneral method for converting string to graph
    void Graph::parse_buffer(){
        std::string line;
        std::string connection;
        // reading line by line from the buffer.
        while (std::getline(buffer, line)) {
            for (char c : line){
                // using "." as end of line command
                if (c == '.'){
                    std::stringstream stringstream(connection);
                    connection.clear();
                    std::string node_label_a, edge_label, node_label_b;
                    stringstream >> node_label_a >> edge_label >> node_label_b;
                    
                    // inserting the edge ensures both nodes are generated
                    insert_edge(node_label_a, edge_label, node_label_b);
                } else {
                    connection += c;
                }
            }
            connection += " ";
        }
    }

    // returns a list of node labels
    std::list<std::string> Graph::get_nodes(){
        std::list<std::string> return_list;
        // converting pointer to label
        for (auto& node : node_pointer_list){
            return_list.push_back(node.first);
        }
        return return_list;
    }

    // returns a list of edge pairs from the node
    std::list<std::pair<std::string, std::string>> Graph::get_node_edges(std::string node_label){
        std::list<std::pair<std::string, std::string>> return_list;
        // if node exist
        if (node_pointer_list.find(node_label) != node_pointer_list.end()){
            // converting edge object to pair
            for (auto& edge : node_pointer_list[node_label]->edges){
                return_list.push_back({edge->label, edge->pointing_to_node->label});
            }
        }
        return return_list; // list with format [(label, node pointer)]
    }


    // #### <Matrix> ############################################################


    // printing node to string stream
    void Matrix::print(std::ostream& os) const{
        for (std::size_t i=0; i<nodes.size(); i++){
            if (matrix.size() <= i){
                break;
            }
            for (std::size_t j=0; j<nodes.size(); j++){
                if (matrix[i].size() <= j) {
                    break;
                }
                for (auto& string : matrix[i][j]){
                    os << nodes[i] << " " << string << " " << nodes[j] << "." << std::endl;
                }
            }
        }
    }

    // constructing a graph from the buffer.
    // genneral method for converting string to graph
    void Matrix::parse_buffer(){
        std::string line;
        std::string connection;
        // reading line by line from the buffer.
        while (std::getline(buffer, line)) {
            for (char c : line){
                // using "." as end of line command
                if (c == '.'){
                    std::stringstream stringstream(connection);
                    connection.clear();
                    std::string node_label_a, edge_label, node_label_b;
                    stringstream >> node_label_a >> edge_label >> node_label_b;
                    
                    // inserting the edge ensures both nodes are generated
                    insert_edge(node_label_a, edge_label, node_label_b);
                } else {
                    connection += c;
                }
            }
            connection += " ";
        }
    }

    // method for memory handling upon delete
    void Matrix::clear(){

    }


    // adding edge from one node to another
    void Matrix::insert_edge(std::string node_a_label, std::string edge_label, std::string node_b_label){
        // add nodes if list is empty
        if (nodes.size() == 0){
            nodes.push_back(node_a_label);
            nodes.push_back(node_b_label);
        }

        // add node a if it dose not exist
        if (std::find(nodes.begin(), nodes.end(), node_a_label) == nodes.end()) {
            nodes.push_back(node_a_label);
        }
        // add node b if it dose not exist
        if (std::find(nodes.begin(), nodes.end(), node_b_label) == nodes.end()) {
            nodes.push_back(node_b_label);
        }
        
        // uppdate matrix shape and add edge label
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
                        // edge from node i to node j
                        matrix[i][j].push_back(edge_label);
                    }
                }
            }
        }
    }

    // deleta a node and edges to and from the node based on node label
    void Matrix::remove_node(std::string node_label){
        for (long unsigned int i=0; i<nodes.size(); i++){
            if (nodes[i] == node_label){

                // delete edges from the node
                for (auto& row : matrix)
                {
                    if (i < row.size())
                        row.erase(row.begin() + i);
                }

                // delete edges to the node
                matrix.erase(matrix.begin() + i);

                // delete the node
                nodes.erase(nodes.begin() + i);
            }
        }
    }

    // remove all edges from one node to another
    void Matrix::disconnect(std::string node_a_label, std::string node_b_label){
        // iterator over every node
        for (long unsigned int i=0; i<nodes.size(); i++){
            if (nodes[i] == node_a_label){
                // iterator over every node again
                for (long unsigned int j=0; j<nodes.size(); j++){
                    // delete the edges from node i to node j
                    if (nodes[j] == node_b_label){
                        matrix[i][j].clear();
                    }
                }
            }
        }
    }

    // returns a list of node labels
    std::list<std::string> Matrix::get_nodes(){
        std::list<std::string> return_list;
        // copy vector to list
        for (auto& node : nodes){
            return_list.push_back(node);
        }
        return return_list;
    }

    // returns a list of edge pairs from the node
    std::list<std::pair<std::string, std::string>> Matrix::get_node_edges(std::string node_label){
        std::list<std::pair<std::string, std::string>> return_list;

        // find the node iterator
        auto it = std::find(nodes.begin(), nodes.end(), node_label);

        if (it != nodes.end()) {
            // Calculate index using std::distance
            int index = std::distance(nodes.begin(), it);
            // convert matrix to list of pair
            for (long unsigned int i = 0; i < matrix[index].size(); ++i) {
                for (auto& edge : matrix[index][i]){
                    return_list.push_back({edge, nodes[i]});
                }
            }
            return return_list;
        } else {
            return return_list;
        }

    }

}
