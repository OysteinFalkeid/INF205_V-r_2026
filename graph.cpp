#include "graph.h"
#include <ostream>
#include <iostream>


Node::Node(const std::string& l)
    : label(l)
{
}

Edge::Edge(const std::string& l, Node* f, Node* t)
    : label(l), from(f), to(t)
{
}


Node* Graph::find_node(const std::string& label)
{
    for (auto n : nodes)
    {
        if (n->label == label)
            return n;
    }
    return nullptr;
}

void Graph::insert_edge(std::string node_a_label,
                        std::string edge_label,
                        std::string node_b_label)
{
    Node* a = find_node(node_a_label);
    if (!a)
    {
        a = new Node(node_a_label);
        nodes.push_back(a);
    }

    Node* b = find_node(node_b_label);
    if (!b)
    {
        b = new Node(node_b_label);
        nodes.push_back(b);
    }

    Edge* e = new Edge(edge_label, a, b);
    edges.push_back(e);

    a->incidences.push_back(e);
    b->incidences.push_back(e);
}

Graph::~Graph()
{
    for (auto e : edges)
        delete e;

    for (auto n : nodes)
        delete n;
}

void Graph::clear()
{
    for (auto e : edges)
        delete e;

    for (auto n : nodes)
        delete n;

    edges.clear();
    nodes.clear();
}

std::istream& operator>>(std::istream& is, Graph& g)
{
    g.clear();

    std::string a, e, b;

    while (is >> a >> e >> b)
    {
        if (!b.empty() && b.back() == '.')
            b.pop_back();

        g.insert_edge(a, e, b);
    }

    return is;
}
/* Oppgave 2 

std::ostream& operator<<(std::ostream& os, const Graph& g)
{
    for (auto e : g.edges)
    {
        os << e->from->label << " "
           << e->label << " "
           << e->to->label << "\n";
    }

    return os;
}

*/

//Oppgave 3

void Graph::read(std::istream& is)
{
    clear();

    std::string a, e, b;

    while (is >> a >> e >> b)
    {
        if (!b.empty() && b.back() == '.')
            b.pop_back();

        insert_edge(a, e, b);
    }
}

void Graph::write(std::ostream& os) const
{
    for (auto e : edges)
    {
        os << e->from->label << " "
           << e->label << " "
           << e->to->label << ".\n";
    }
}
