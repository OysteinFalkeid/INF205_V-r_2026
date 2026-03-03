#include <string>
#include <list>
#include <unordered_map>
#include <map>
#include <iostream>

class Node;
class Graph;
class Edge;

std::ostream& operator<<(std::ostream&, const Graph&);
std::ostream& operator<<(std::ostream&, const Node*);
std::ostream& operator<<(std::ostream&, const Edge*);

class Node{
    private:
    /* data */
    public:
    Node(std::string node_label);
    ~Node();
    
    std::string label;
    std::list<Edge*> edges;

    void add_edge(std::string edge_label, Node* node_ptr);
};

class Edge{
    private:
    /* data */
    public:
    Edge(std::string label, Node* node_ptr);
    ~Edge();
    
    Node* pointing_to_node;
    std::string label;
};

class Graph{
    private:
    /* data */
    public:

    Graph(/* args */);
    ~Graph();
    
    std::map<std::string, Node*> node_pointer_list;
    
    void insert_edge(std::string node_a_label, std::string edge_label, std::string node_b_label);
    void remove_node(std::string node_label);
};

Node::Node(std::string node_label){
    label = node_label;
}

Node::~Node(){
    for (auto& item : edges){
        delete item;
    }
}

void Node::add_edge(std::string edge_label, Node* node_ptr){
    Edge* edge_ptr = new Edge(edge_label, node_ptr);
    edges.push_back(edge_ptr);
}

Edge::Edge(std::string edge_label, Node* node_ptr){
    label = edge_label;
    pointing_to_node = node_ptr;
}

Edge::~Edge(){
}


Graph::Graph(/* args */){
    
}

Graph::~Graph(){
    for(auto& pair : node_pointer_list){
        delete pair.second;
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
    delete node_pointer_list[node_label];
    node_pointer_list.erase(node_label);
}







std::ostream& operator<<(std::ostream& os, const Graph& graph) {
    for(auto& pair : graph.node_pointer_list){
        os << pair.second << std::endl;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const Node* node) {
    if (node){
        os << node->label << ":" << std::endl;
        for(auto& item : node->edges){
            os << node->label << " -> " << item;
        }
    } else {
        os << "nullptr";
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const Edge* edge) {
    if (edge){
        os << edge->label << " -> ";
        if(edge->pointing_to_node){
            os << edge->pointing_to_node->label;
        } else {
         os << "nullptr";
        }
    } else{
        os << "nullptr";
    }
    os  << std::endl;   
    return os;
}
