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

// Oppgave 5

void Graph::disconnect(std::string node_a_label, std::string node_b_label){

    // Finner nodene a og b, returnerer hvis de ikke eksisterer

    Node* a = find_node(node_a_label);
    Node* b = find_node(node_b_label);

    if (a == nullptr || b == nullptr){
        return;
    }

    // Går gjennom alle edges i "edges". For hver edge, sjekke om den går fra node A til B

    auto k = edges.begin();
    while (k != edges.end()) // Kjør på så lenge vi ikke er på enden av vektoren
    {
        Edge* e = *k;
        if (e->from == a && e->to == b)
        {
            //Fjerne kanten fra lista til node a, bruker remove siden vi har incidences i vektor
            //std::remove sletter e, mens erase gir oss den vektoren som inneholder alt annet enn det vi fjernet. altså fjerner tomrommet
            a->incidences.erase(
                std::remove(a->incidences.begin(), a->incidences.end(), e), a->incidences.end()
            );
            //Fjerne kanten fra lista til node b
            b->incidences.erase(
                std::remove(b->incidences.begin(), b->incidences.end(), e), b->incidences.end()
            );
            //Slette kanten
            delete e;
            // Fjerne kanten fra edges
            k = edges.erase(k); //slett kanten
        } else{
            ++k;
        }
    }

    //Fjerne evt isolerte noder
    auto in = nodes.begin(); //iterator som starter på det første elementet i nodes vektoren
    while (in != nodes.end())
    {
        Node* n = *in;
        if (n->incidences.empty()){ //returnerer true hvis den er isolert
            delete n; //sletter node og frigjør minnet
            in = nodes.erase(in); //fjerner noden fra vektoren
        }else{
            ++in; // hvis noden ikke er isolert så går den videre til neste node
        }
    }
}

void Graph::remove_node(std::string node_label){
    //Finn noden, hvis den ikke finnes returner

    Node* m = find_node(node_label);
    if (m == nullptr){
        return;
    }

    auto k = edges.begin();
    while (k != edges.end()) // Kjør på så lenge vi ikke er på enden av vektoren
    {
        Edge* e = *k;
        if (e->from == m || e->to == m)
        {
            //A - > e1 -> B, må fjerne edge fra A og fra B
            //Fjerne edge fra "from"
            e->from->incidences.erase(std::remove(e->from->incidences.begin(), e->from->incidences.end(), e), e->from->incidences.end());

            //Fjerne edge fra "to"
            e->to->incidences.erase(std::remove(e->to->incidences.begin(), e->to->incidences.end(), e), e->to->incidences.end());

            //Slette kanten
            delete e;
            // Fjerne kanten fra edges
            k = edges.erase(k); //slett kanten

        }else{
            ++k;
        }
    }

    //Slett noden
    nodes.erase(std::remove(nodes.begin(), nodes.end(), m), nodes.end()); //frigjør pekeren fra vektoren
    delete m; // frigjør else node i minnet

    //Fjerne evt isolerte noder
    auto in = nodes.begin(); //iterator som starter på det første elementet i nodes vektoren
    while (in != nodes.end())
    {
        Node* n = *in;
        if (n->incidences.empty()){ //returnerer true hvis den er isolert
            delete n; //sletter node og frigjør minnet
            in = nodes.erase(in); //fjerner noden fra vektoren
        }else{
            ++in; // hvis noden ikke er isolert så går den videre til neste node
        }
    }
}

void MatrixGraph::disconnect(std::string node_a_label, std::string node_b_label)
{

}

void MatrixGraph::remove_node(std::string node_label)
{

}
