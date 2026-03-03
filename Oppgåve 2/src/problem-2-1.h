#include <string>
#include <list>
#include <unordered_map>

class Node{
private:
    /* data */
    std::list<Edge*> edges;
    std::string label;
public:
    Node(std::string node_label);
    ~Node();
    void add_edge(std::string edge_label, Node* node_ptr);
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

class Edge{
private:
    /* data */
    std::string label;
public:
    Edge(std::string label, Node* node_ptr);
    ~Edge();
};

Edge::Edge(std::string edge_label, Node* node_ptr){
    label = edge_label;
}

Edge::~Edge(){
}


class Graph{
private:
    /* data */
    std::unordered_map<std::string, Node*> node_pointer_list;
public:
    Graph(/* args */);
    ~Graph();


    void insert_edge(std::string node_a_label, std::string edge_label, std::string node_b_label);
    void remove_node(std::string node_label);
};

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

}
