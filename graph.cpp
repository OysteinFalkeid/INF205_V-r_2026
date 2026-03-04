#include "graph.h"
#include <ostream>
#include <iostream>

// Node kontruktøren

Node::Node(const std::string& l)
    : label(l)
{
}

// Edge konstruktøren

Edge::Edge(const std::string& l, Node* f, Node* t)
    : label(l), from(f), to(t)
{
}

// Funksjon som går gjennom alle nodene i nodes-vektoren. Finner den riktig node returnerer den en peker til noden
// Hvis ikke returnerer den nullptr

Node* Graph::find_node(const std::string& label)
{
    for (auto n : nodes)
    {
        if (n->label == label)
            return n;
    }
    return nullptr;
}

// Finner node A og B som opprettes hvis ikke de finnes og blir lagt til i nodes vektoren
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

    // Oppretter en ny kant og legger til i edges vektoren
    Edge* e = new Edge(edge_label, a, b);
    edges.push_back(e);

    a->incidences.push_back(e);
    b->incidences.push_back(e);
}

// Destruktør som går gjennom edges og sletter de før han går gjennom nodes og sletter de. Edge slettes før node
Graph::~Graph()
{
    for (auto e : edges)
        delete e;

    for (auto n : nodes)
        delete n;
}

// Tømmer grafen for edges og nodes men objektet graph eksisterer
void Graph::clear()
{
    for (auto e : edges)
        delete e;

    for (auto n : nodes)
        delete n;

    edges.clear();
    nodes.clear();
}

/* Oppgave 2 

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
    clear(); // tømmer grafen

    std::string a, e, b;

    while (is >> a >> e >> b) // leser inn tre ord om gangen
    {
        if (!b.empty() && b.back() == '.')
            b.pop_back();

        insert_edge(a, e, b);
    }
}

void Graph::write(std::ostream& os) const
{
    for (auto e : edges) // går gjennom alle kanter og skriver de ut
    {
        os << e->from->label << " "
           << e->label << " "
           << e->to->label << ".\n";
    }
}

//Oppgave 4

//Tom destruktør fordi vektor og list rydder opp selv
MatrixGraph::~MatrixGraph(){

}

//Går gjennom nodes vektoren og returnerer indeksen. hvis ikke returnerer -1 
int MatrixGraph::find_node(const std::string& label) const{
    for(int i = 0; i < (int)nodes.size(); i++){
        if(nodes[i] == label)
            return i;
    }
    return -1;
}

void MatrixGraph::add_node(const std::string& label){
    //Legg til en ny kolonne i alle eksisterende rader
    for (auto&row : matrix){
        row.push_back(std::list<std::string>());
    }

    //Legg til en ny rad for den nye noden
    int new_row = nodes.size() + 1;
    matrix.push_back(std::vector<std::list<std::string>>(new_row));

    // Legg til noden i lista
    nodes.push_back(label);
}

void MatrixGraph::insert_edge(std::string node_a_label, std::string edge_label, std::string node_b_label){

    //Finn eller opprett node A
    if(find_node(node_a_label) == -1)
        add_node(node_a_label);

    //Finn eller opprett node B
    if(find_node(node_b_label) == -1)
        add_node(node_b_label);
    
    //Hent indeksene til nodene:
    int i = find_node(node_a_label);
    int j = find_node(node_b_label);

    //Legg til kanten i matrisen
    matrix[i][j].push_back(edge_label);

}

void MatrixGraph::clear(){
    //Tøm vektorene:
    nodes.clear();
    matrix.clear();
}

void MatrixGraph::read(std::istream& is)
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


void MatrixGraph::write(std::ostream& os) const
{
    //Ytre forløkke, går gjennom alle rader:
    for(int i = 0; i < (int)nodes.size(); i++){
        //Midtre forløkke, går gjennom kolonner:
        for(int j = 0; j < (int)nodes.size(); j++){
            //Går gjennom edges:
            for(auto& edge_label : matrix[i][j]){
                os << nodes[i] << " "
                << edge_label << " "
                << nodes[j] << ".\n";
            }
        }
    }

}
