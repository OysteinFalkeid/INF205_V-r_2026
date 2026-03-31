
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
    bool visualize = false;
    app.add_flag("-g,--to_graph", visualize, "generates a .dot file from the input file and renders a graph");
    std::string file = "scc-graph-benchmark-data/scc02.dat";
    app.add_option("-f,--file", file, "path to inputfile");
    bool use_tarjans_algorithm = false;
    app.add_flag("--tarjans", use_tarjans_algorithm, "computes tarjans algorithm");
    std::string file_regular_path_querying;
    app.add_option("--rpq", file_regular_path_querying, "query file for regular_path_querying");


    CLI11_PARSE(app, argc, argv);

    
    if (visualize){
        graphFileToDot(file, "graph.dot");
        std::system("dot -Tpng graph.dot -o graph.png");
    }

    db::Graph graph;
    if (!graph.read_file(file)){
        return 1;
    }
    if (verbose) {
        std::cout << graph << std::endl;
    }

    if (use_tarjans_algorithm){
        std::list<std::string> strong_connections = tarjans_algorithm(&graph);
        if (verbose) {
            for (auto& string : strong_connections){
                std::cout << string << std::endl;
            }
        }
        std::ofstream connections_to_file("connections.txt");
        for (auto& string : strong_connections){
            connections_to_file << string << std::endl;
        }
        connections_to_file.close();
    }


    if (file_regular_path_querying != ""){
        std::list<std::string> list_of_string = regular_path_querying(&graph, file_regular_path_querying);
        if (verbose){
            for (auto& string : list_of_string){
                std::cout << string << std::endl;
            }
        }
    }


    if (!graph.write_to_file("graph_1.txt")){
        return 1;
    }

}



