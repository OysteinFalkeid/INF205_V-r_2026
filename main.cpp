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

    // Bruker baseklasse-peker
    AbstractGraph* ag = new Graph();

    std::ifstream in("input.txt");

    if (!in)
    {
        std::cout << "Could not open input.txt\n";
        delete ag;
        return 1;
    }

    ag->read(in);

    std::cout << "Graph content:\n";
    ag->write(std::cout);

    delete ag;

    return 0;
}
