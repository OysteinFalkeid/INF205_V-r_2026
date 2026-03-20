#include "graph.h"
#include "scc.h"
#include <set>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

void read_query(
    const std::string& filename,
    std::set<std::string>& even_labels,
    std::set<std::string>& odd_labels)
{
    std::ifstream in(filename);
    std::string line;

    // første linje
    if (std::getline(in, line))
    {
        std::istringstream iss(line);
        std::string label;
        while (iss >> label)
        {
            if (!label.empty() && label.back() == '.')
                label.pop_back();
            even_labels.insert(label);
        }
    }

    // andre linje
    if (std::getline(in, line))
    {
        std::istringstream iss(line);
        std::string label;
        while (iss >> label)
        {
            if (!label.empty() && label.back() == '.')
                label.pop_back();
            odd_labels.insert(label);
        }
    }
}

/*
void testoppgave1(){
        std::cout << "Oppgave 1 - testing: \n";
        Graph g;

        g.insert_edge("A", "e1", "B");
        g.insert_edge("A", "e2", "C");
        g.insert_edge("B", "e3", "A");
        g.insert_edge("A", "e4", "A");  // selv-loop

        g.write(std::cout);
        std::cout << "\n";
    }
void testoppgave2(){
    std::cout << "Oppgave 2 - testing: \n";
    Graph g;

    std::ifstream in("input.txt");
    if (!in) { std::cout << "Kunne ikke åpne input.txt\n"; return; }
    g.read(in);
    g.write(std::cout);
    std::cout << "\n";

}

void testoppgave3(){
    std::cout << "Oppgave 3 - testing \n";
    AbstractGraph* ag = new Graph();

    std::ifstream in3("input.txt");

    if (!in3)
    {
        std::cout << "Could not open input.txt\n";
        delete ag;
        return;
    }

    ag->read(in3);

    ag->write(std::cout);

    delete ag;
}

void testoppgave4(){
    std::cout << "Oppgave 4 - testing - Graph Matrix \n";

    AbstractGraph* ag2 = new MatrixGraph();

    std::ifstream in4("input.txt");

    if (!in4)
    {
        std::cout << "Could not open input.txt\n";
        delete ag2;
        return;
    }

    ag2->read(in4);

    ag2->write(std::cout);

    delete ag2;
}

void testoppgave5(){
    std::cout << "Test disconnect og remove_node (Graph)\n";

    AbstractGraph* ag3 = new Graph();
    std::ifstream in5("input.txt");
    ag3->read(in5);

    std::cout << "Før disconnect:\n";
    ag3->write(std::cout);

    ag3->disconnect("A", "B");
    std::cout << "\nEtter disconnect(A, B):\n";
    ag3->write(std::cout);

    ag3->remove_node("A");
    std::cout << "\nEtter remove_node(A):\n";
    ag3->write(std::cout);

    delete ag3;
}

void testoppgave6(){
    std::cout << "Kopikonstruktør\n";
    Graph g1;
    g1.insert_edge("A", "e1", "B");
    Graph g2 = g1;
    g1.insert_edge("B", "e2", "C");
    std::cout << "g1: "; g1.write(std::cout);
    std::cout << "g2: "; g2.write(std::cout); // skal bare ha e1

    std::cout << "Kopieringsoperator\n";
    Graph g3, g4;
    g3.insert_edge("A", "e1", "B");
    g4.insert_edge("X", "e2", "Y");
    g4 = g3;
    std::cout << "g3: "; 
    g3.write(std::cout);
    std::cout << "g4: "; 
    g4.write(std::cout); // skal være lik g3

    std::cout << "Flyttkonstruktør\n";
    Graph g5;
    g5.insert_edge("A", "e1", "B");
    Graph g6 = std::move(g5);
    std::cout << "g5 (skal være tom): \n"; 
    g5.write(std::cout);
    std::cout << "g6:" ; 
    g6.write(std::cout);

    std::cout << "Flyttoperator\n";
    Graph g7, g8;
    g7.insert_edge("A", "e1", "B");
    g8.insert_edge("X", "e2", "Y");
    g8 = std::move(g7);
    std::cout << "g7 (skal være tom): \n"; 
    g7.write(std::cout);
    std::cout << "g8: "; 
    g8.write(std::cout);

}
    */

int main(int argc, char** argv)
{
     /*
    // Test av oppgave 1:

    testoppgave1();

    // Test av oppgave 2:

    testoppgave2();
    
    // Test av oppgave 3

    testoppgave3();

    // Test av oppgave 4
    
    testoppgave4();
    
    
    // Testing oppgave 5

    testoppgave5();

    //Test av oppgave 6
    
    testoppgave6();

*/
    

    /*
    g.insert_edge("A","e1","B");
    g.insert_edge("A","e2","C");

    for (auto n : g.get_nodes()) {
        std::cout << "Node: " << n << "\n";
        for (auto nb : g.get_neighbors(n)) {
            std::cout << "  -> " << nb << "\n";
        }
    }

   

    g.insert_edge("A","e1","B");
    g.insert_edge("B","e2","C");
    g.insert_edge("C","e3","A"); // cycle

    g.insert_edge("D","e4","E");

    auto sccs = tarjan_scc(&g);

    for (auto& comp : sccs) {
        std::cout << "SCC: ";
        for (auto& node : comp) {
            std::cout << node << " ";
        }
        std::cout << "\n";
    }

    */

    // --- Standard ---
    bool verbose    = true;
    bool use_matrix = false;

    // 🔥 NY struktur (oppgave 2)
    std::string graphfile = "";
    std::string queryfile = "";

    // --- Argument parsing ---
    for (int i = 1; i < argc; i++)
    {
        std::string arg = argv[i];

        if (arg == "--silent" || arg == "-s")
            verbose = false;
        else if (arg == "--verbose" || arg == "-v")
            verbose = true;
        else if (arg == "--matrix" || arg == "-m")
            use_matrix = true;
        else if (graphfile.empty())
            graphfile = arg;
        else
            queryfile = arg;
    }

    // --- Validering ---
    if (graphfile.empty())
    {
        std::cerr << "Bruk: " << argv[0]
                  << " [--silent | --verbose] [--matrix] <grafil> [queryfil]\n";
        return 1;
    }

    // --- Les graf ---
    std::ifstream in(graphfile);
    if (!in)
    {
        std::cerr << "Kunne ikkje opne graf-fil: " << graphfile << "\n";
        return 1;
    }

    // --- Vel graf ---
    AbstractGraph* g = use_matrix
        ? static_cast<AbstractGraph*>(new MatrixGraph())
        : static_cast<AbstractGraph*>(new Graph());

    if (verbose)
    {
        std::cout << "Graftype: "
                  << (use_matrix ? "MatrixGraph" : "Graph") << "\n";
        std::cout << "Fil: " << graphfile << "\n\n";
    }

    g->read(in);

    // DEBUG: skriv ut grafen
    g->write(std::cout);
    std::cout << "\n";

    // ======================
    // SCC (oppgave 3.1)
    // ======================
    auto sccs = tarjan_scc(g);

    if (verbose)
    {
        for (auto& comp : sccs)
        {
            std::cout << "SCC: ";
            for (auto& node : comp)
                std::cout << node << " ";
            std::cout << "\n";
        }
    }

    std::cout << "Antall SCC: " << sccs.size() << "\n";

    // ======================
    //Diamonds (oppgave 3.2)
    // ======================
    if (!queryfile.empty())
    {
        std::set<std::string> even_labels, odd_labels;

        read_query(queryfile, even_labels, odd_labels);

        auto diamonds = find_diamonds(g, even_labels, odd_labels);

        if (verbose)
        {
            for (auto& [a, b] : diamonds)
            {
                std::cout << "Diamond: " << a << " -> " << b << "\n";
            }
        }

        std::cout << "Antall diamonds: " << diamonds.size() << "\n";
    }

    delete g;
    return 0;
}
