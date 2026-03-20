#include "graph.h"
#include <iostream>
#include <fstream>

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
int main()
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

    // --- Standard verdiar ---
    bool verbose    = true;
    bool use_matrix = false;
    std::string filename = "";
 
    // --- Les flagg og filnamn frå kommandolinja ---
    for (int i = 1; i < argc; i++)
    {
        std::string arg = argv[i];
 
        if (arg == "--silent" || arg == "-s")
            verbose = false;
        else if (arg == "--verbose" || arg == "-v")
            verbose = true;
        else if (arg == "--matrix" || arg == "-m")
            use_matrix = true;
        else
            filename = arg;   // første ukjente argument = grafil
    }
 
    // --- Validering ---
    if (filename.empty())
    {
        std::cerr << "Bruk: " << argv[0]
                  << " [--silent | --verbose] [--matrix] <grafil>\n";
        return 1;
    }
 
    // --- Opne fil ---
    std::ifstream in(filename);
    if (!in)
    {
        std::cerr << "Kunne ikkje opne fil: " << filename << "\n";
        return 1;
    }
 
    // --- Vel graftype via AbstractGraph-peikar ---
    AbstractGraph* g = use_matrix
                       ? static_cast<AbstractGraph*>(new MatrixGraph())
                       : static_cast<AbstractGraph*>(new Graph());
 
    if (verbose)
        std::cout << "Graftype: " << (use_matrix ? "MatrixGraph" : "Graph") << "\n"
                  << "Fil: " << filename << "\n\n";
 
    // --- Les inn grafen ---
    g->read(in);
 
    // --- Køyr Tarjan ---
    auto sccs = tarjan_scc(g);
 
    // --- Skriv ut resultat ---
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

    return 0;
}
