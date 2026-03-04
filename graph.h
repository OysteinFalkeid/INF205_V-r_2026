#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <ostream>
#include <istream>

class Edge;   // forward declaration

class AbstractGraph {
public:
    virtual ~AbstractGraph() {}   // viktig!

    virtual void insert_edge(
        std::string node_a_label,
        std::string edge_label,
        std::string node_b_label
    ) = 0;

    virtual void clear() = 0;

    virtual void read(std::istream& is) = 0;
    virtual void write(std::ostream& os) const = 0;
};


class Node {
public:
    std::string label;
    std::vector<Edge*> incidences;

    Node(const std::string& l);
};

class Edge {
public:
    std::string label;
    Node* from;
    Node* to;

    Edge(const std::string& l, Node* f, Node* t);
};

class Graph : public AbstractGraph {
private:
    std::vector<Node*> nodes;
    std::vector<Edge*> edges;

    Node* find_node(const std::string& label);

public:
    ~Graph();

    void clear() override;
    
    /* oppgave 2
    friend std::istream& operator>>(std::istream& is, Graph& g);
    friend std::ostream& operator<<(std::ostream& os, const Graph& g);
    */

    void insert_edge(std::string node_a_label,
                     std::string edge_label,
                     std::string node_b_label) override;
    
    void read(std::istream& is) override;
    void write(std::ostream& os) const override;
    
};

#endif