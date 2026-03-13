
#include "graph.h"
#include "algorithms.h"
#include <CLI/CLI.hpp> 
#include <iostream>

using namespace db;

int main(int argc, char** argv) 
{
    // Argument parsing
    CLI::App app{"Oppgåve 3"};
    bool verbose = false;
    app.add_flag("-v,--verbose", verbose, "Verbose output");
    std::string file = "scc-graph-benchmark-data/scc02.dat";
    app.add_option("-f,--file", file, "path to inputfile");
    CLI11_PARSE(app, argc, argv);

    //

    db::Graph graph;
    if (!graph.read_file(file)){
        return 1;
    }

    std::list<std::string> strong_connections = tarjans_algorithm(&graph);


    if (verbose) {
        for (auto& string : strong_connections){
            std::cout << string << std::endl;
        }
    
        std::cout << graph << std::endl;
    }

    std::ofstream connections_to_file("connections.txt");
    for (auto& string : strong_connections){
        connections_to_file << string << std::endl;
    }

    if (!graph.write_to_file("graph_1.txt")){
        return 1;
    }

}


