#pragma once
#include <string>
#include <vector>
#include <list>
#include <ostream>
#include <istream>
#include <unordered_map>

class Edge;   // forward declaration av Edge. Edge finnes, men kommer etter Node. Node bruker edge

//Et grensesnitt abstrakt klasse, som Graph og MatrixGraph arver fra
class AbstractGraph {
public:
    virtual ~AbstractGraph() {}   // virtuell destruktør

    //Rene virtuelle funksjoner som gjør klassen abstrakt

    virtual void insert_edge(
        std::string node_a_label,
        std::string edge_label,
        std::string node_b_label
    ) = 0;

    virtual void clear() = 0;

    virtual void read(std::istream& is) = 0;
    virtual void write(std::ostream& os) const = 0;

    //Oppgave 5
    virtual void disconnect(std::string node_a_label, std::string node_b_label) = 0;
    virtual void remove_node(std::string node_label) = 0;

    // Oppgave 3.1

    virtual std::vector<std::string> get_nodes() const = 0;
    virtual std::vector<std::string> get_neighbors(std::string node_label) const = 0;

    // Oppgave 3.2

    virtual std::vector<std::pair<std::string,std::string>>
    get_labeled_neighbors(std::string node_label) const = 0;
};


class Node {
public:

    //unike identifikatoren til noden
    std::string label;
    //alle edges denne noden er incident til. 
    //kanter som går ut fra noden og som går inn til node
    std::vector<Edge*> incidences;

    //Konstruktøren 
    Node(const std::string& l);
};

class Edge {
public:

    //Navnet på edgen
    std::string label;

    //Peker til opprinnelsesnoden
    Node* from;
    //Peker til endenoden?
    Node* to;

    //Konstruktøren
    Edge(const std::string& l, Node* f, Node* t);
};

//peker basert graf
class Graph : public AbstractGraph {
private:
    //Liste over alle noder i grafen
    std::unordered_map<std::string, Node*> node_map;
    //Liste over alle edges i grafen
    std::vector<Edge*> edges;

    //Hjelpefunksjon som skal søke gjennom nodes mapen etter en node med bestemt navn ´label´
    Node* find_node(const std::string& label) const;

public:

    //Destruktøren
    ~Graph();

    //Tømmer grafen
    void clear() override;
    
    /* oppgave 2
    friend std::istream& operator>>(std::istream& is, Graph& g);
    friend std::ostream& operator<<(std::ostream& os, const Graph& g);
    */

    //Lgger til kant i grafen og oppretter noder hvis de ikke eksisterer fra før av
    void insert_edge(std::string node_a_label,
                     std::string edge_label,
                     std::string node_b_label) override;
    
    void read(std::istream& is) override;
    void write(std::ostream& os) const override;

    // Oppgave 5
    void disconnect(std::string node_a_label, std::string node_b_label) override;
    void remove_node(std::string node_label) override;

    //Oppgave 6
    Graph(const Graph& orig); //Kopikontruktør
    Graph(){}
    Graph& operator=(const Graph& rhs); //Kopioperator
    Graph(Graph&& old); //Flyttekonstruktør
    Graph& operator=(Graph&& old); //Flytteoperator

    //Oppgave 3.1
    std::vector<std::string> get_nodes() const override;
    std::vector<std::string> get_neighbors(std::string node_label) const override;

    //Oppgave 3.2
    std::vector<std::pair<std::string,std::string>>
    get_labeled_neighbors(std::string node_label) const override;


};

//matrise-basert
class MatrixGraph : public AbstractGraph{
    private:
        //Hva noden kallen
        std::vector<std::string> nodes;
        //adjancency matrix med edge labels
        //Matrise matrix[i][j] alle edges fra node i til node j
        std::vector<std::vector<std::list<std::string>>> matrix;

        //Søker gjennom nodes vektoren etter en node med et bestemt navn og returnerer indeksen:
        int find_node(const std::string& label) const;

        //Legger til ny node og utvider matrisen. nå skal vi endre på matrisen og derfor er det ik const på slutten:
        void add_node(const std::string& label);
    public:
        ~MatrixGraph(); // destruktør

        void clear() override;
        void insert_edge(std::string node_a_label,
                     std::string edge_label,
                     std::string node_b_label) override;

        void read(std::istream& is) override;
        void write(std::ostream& os) const override;

        // Oppgave 5
        void disconnect(std::string node_a_label, std::string node_b_label) override;
        void remove_node(std::string node_label) override;

        // Oppgave 3-1
        std::vector<std::string> get_nodes() const override;
        std::vector<std::string> get_neighbors(std::string node_label) const override;

        //Oppgave 3-2

        std::vector<std::pair<std::string,std::string>>
        get_labeled_neighbors(std::string node_label) const override;

};
