
#include "graph.h"
#include "algorithms.h"
#include <CLI/CLI.hpp> 
#include <iostream>

using namespace db;

int main(int argc, char** argv) 
{
    // Argument parsing
    CLI::App app{"Oppgåve 3.1"};
    bool verbose = false;
    app.add_flag("-v,--verbose", verbose, "Verbose output");
    std::string file = "scc-graph-benchmark-data/scc02.dat";
    app.add_option("-f,--file", file, "path to inputfile");


    CLI11_PARSE(app, argc, argv);

    Graph graph;
    graph.read_file(file);
    std::list<std::string> strong_connections = tarjans_algorithm(&graph);

    for(auto& string : strong_connections){
        std::cout << string << std::endl;
    }


}