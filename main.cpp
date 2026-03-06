#include "graph.h"
#include <iostream>
#include <fstream>

int main()
{
    Graph g;

    /* testing av oppgave 1
    g.insert_edge("A", "e1", "B");
    g.insert_edge("A", "e2", "C");
    g.insert_edge("B", "e3", "A");
    g.insert_edge("A", "e4", "A");  // selv-loop
    */

    /* testing oppgave 2
    std::ifstream in("input.txt");

    if (!in)
    {
        std::cout << "Kunne ikke åpne input.txt\n";
        return 1;
    }

    in >> g;

    std::cout << g;
    */

    // Testing oppgave 3

    /*
    std::cout << "Graph insidens liste \n";

    AbstractGraph* ag = new Graph();

    std::ifstream in3("input.txt");

    if (!in3)
    {
        std::cout << "Could not open input.txt\n";
        delete ag;
        return 1;
    }

    ag->read(in3);

    ag->write(std::cout);

    delete ag;
    */

    // Testing oppgave 4
    /*
    std::cout << "Graph Matrix \n";

    AbstractGraph* ag2 = new MatrixGraph();

    std::ifstream in4("input.txt");

    if (!in4)
    {
        std::cout << "Could not open input.txt\n";
        delete ag;
        delete ag2;
        return 1;
    }

    ag2->read(in4);

    ag2->write(std::cout);

    delete ag2;
    */

    // Testing oppgave 5

    // Testing oppgave 5 - Graph
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

    return 0;
}
