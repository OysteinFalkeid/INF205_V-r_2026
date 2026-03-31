#include "graph.h"
#include "scc.h"
#include "measure.h"
#include <set>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

/*
// Innlevering 2 - Oppgave 1 -> 6
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

    //Innlevering 3
    
    //Oppgave 1

    void test_scc() {
    std::cout << "\nSCC test:\n";

    Graph g;
    std::ifstream in("scc02.dat");
    g.read(in);

    auto sccs = tarjan_scc(&g);

    for (auto& comp : sccs) {
        std::cout << "{ ";
        for (auto& n : comp)
            std::cout << n << " ";
        std::cout << "}\n";
    }
}

//Oppgave 3

void demo_pro22()
    {
        std::cout << "Demo 2.2 (read/write):\n";

        Graph g;
        std::ifstream in("input.txt");

        if (!in) {
            std::cout << "Kunne ikke åpne input.txt\n";
            return;
        }

        g.read(in);
        g.write(std::cout);
    }

void demo_pro25(bool verbose, bool use_matrix)
{
    std::cout << "Demo 2.5 (disconnect/remove_node):\n";

    AbstractGraph* g;

    if (use_matrix)
        g = new MatrixGraph();
    else
        g = new Graph();

    g->insert_edge("A","e1","B");
    g->insert_edge("A","e2","C");
    g->insert_edge("B","e3","A");
    g->insert_edge("B","e4","C");

    std::cout << "Før:\n";
    g->write(std::cout);

    g->disconnect("A","B");

    std::cout << "\nEtter disconnect(A,B):\n";
    g->write(std::cout);

    g->remove_node("A");

    std::cout << "\nEtter remove_node(A):\n";
    g->write(std::cout);

    delete g;
}

void read_query(
    std::istream& in,
    std::vector<std::string>& even_labels,
    std::vector<std::string>& odd_labels)
{
    even_labels.clear();
    odd_labels.clear();

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
            even_labels.push_back(label);
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
            odd_labels.push_back(label);
        }
    }
}

void demo_pro31(bool verbose, bool use_matrix, const std::string& filename)
{
    if (verbose)
        std::cout << "Demo 3.1 (SCC):\n";

    AbstractGraph* g;

    if (use_matrix)
        g = new MatrixGraph();
    else
        g = new Graph();

    std::ifstream in(filename);
    if (!in) {
        std::cout << "Kunne ikke åpne " << filename << "\n";
        delete g;
        return;
    }

    g->read(in);

    auto sccs = tarjan_scc(g);

    for (auto& comp : sccs)
    {
        std::cout << "{ ";
        for (auto& n : comp)
            std::cout << n << " ";
        std::cout << "}\n";
    }

    delete g;
}

void demo_pro32(bool verbose, bool use_matrix,
                const std::string& graphfile,
                const std::string& queryfile)
{
    if (verbose)
        std::cout << "Demo 3.2 (Diamonds):\n";

    AbstractGraph* g;

    if (use_matrix)
        g = new MatrixGraph();
    else
        g = new Graph();

    std::ifstream gin(graphfile);
    if (!gin) {
        std::cout << "Kunne ikke åpne" << graphfile << "\n";
        delete g;
        return;
    }

    g->read(gin);

    std::ifstream qin(queryfile);
    if (!qin) {
        std::cout << "Kunne ikke åpne " << queryfile << "\n";
        delete g;
        return;
    }

    std::vector<std::string> even_labels;
    std::vector<std::string> odd_labels;

    read_query(qin, even_labels, odd_labels);

    auto diamonds = find_diamonds(g, even_labels, odd_labels);

    for (auto& [a,b] : diamonds)
    {
        std::cout << "(" << a << ", " << b << ")\n";
    }

    delete g;
}

int main(int argc, char** argv)

{
    bool verbose = true;
    bool use_matrix = false;

    for (int i = 1; i < argc; i++)
    {
        std::string arg = argv[i];

        if (arg == "--silent" || arg == "-s")
            verbose = false;
        else if (arg == "--verbose" || arg == "-v")
            verbose = true;
        else if (arg == "--matrix" || arg == "-m")
            use_matrix = true;
    }

    // Test av oppgave 3.4

    if (argc >= 3 && std::string(argv[1]) == "--measure-scc")
{
    std::string graphfile = argv[2];

    AbstractGraph* g = use_matrix
        ? static_cast<AbstractGraph*>(new MatrixGraph())
        : static_cast<AbstractGraph*>(new Graph());

    std::ifstream in(graphfile);
    if (!in)
    {
        std::cout << "Kunne ikkje opne " << graphfile << "\n";
        return 1;
    }

    g->read(in);

    measure_scc(g, 100);

    delete g;
    return 0;
}

if (argc >= 4 && std::string(argv[1]) == "--measure-diamonds")
{
    std::string graphfile = argv[2];
    std::string queryfile = argv[3];

    AbstractGraph* g = use_matrix
        ? static_cast<AbstractGraph*>(new MatrixGraph())
        : static_cast<AbstractGraph*>(new Graph());

    std::ifstream in(graphfile);
    if (!in)
    {
        std::cout << "Kunne ikke åpne " << graphfile << "\n";
        return 1;
    }

    g->read(in);

    std::ifstream qin(queryfile);
    std::vector<std::string> even, odd;
    read_query(qin, even, odd);

    measure_diamonds(g, even, odd, 100);

    delete g;
    return 0;
}


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
    

    // Innlevering 3

    // Test av oppgave 1
    test_scc();
    */

    // Test av oppgave 3
    if (argc < 2)
    {
        std::cout << "Bruk:\n";
        std::cout << "./main pro22\n";
        std::cout << "./main pro25\n";
        std::cout << "./main pro31\n";
        std::cout << "./main pro32\n";
        return 1;
    }

    std::string cmd = argv[1];

    if (cmd == "pro22")
        demo_pro22();
    else if (cmd == "pro25")
        demo_pro25(verbose, use_matrix);
    else if (cmd == "pro31")
        {
        if (argc < 3) {
            std::cout << "Bruk: pro31 <fil>\n";
            return 1;
        }
        demo_pro31(verbose, use_matrix, argv[2]);
        }
    else if (cmd == "pro32")
        {
        if (argc < 4) {
            std::cout << "Bruk: pro32 <graf> <query>\n";
            return 1;
        }
        demo_pro32(verbose, use_matrix, argv[2], argv[3]);
    }
    else
        std::cout << "Ukjent kommando\n";

    
    return 0;
}
