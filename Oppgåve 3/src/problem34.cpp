
#include "graph.h"
#include "algorithms.h"
#include <CLI/CLI.hpp> 
#include <iostream>
#include <chrono>

using namespace db;

int main(int argc, char** argv) 
{
    // Argument parsing
    CLI::App app{"Oppgåve 3"};
    bool verbose = false;
    app.add_flag("-v,--verbose", verbose, "Verbose output");
    std::string file = "scc-graph-benchmark-data/scc02.dat";
    app.add_option("-f,--file", file, "path to inputfile");
    bool use_tarjans_algorithm = false;
    app.add_flag("--tarjans", use_tarjans_algorithm, "computes tarjans algorithm");
    std::string file_regular_path_querying = "";
    app.add_option("--rpq", file_regular_path_querying, "query file for regular_path_querying");
    int rounds = 10;
    app.add_option("-r, --rounds", rounds, "number of repetitions for generating average time");


    CLI11_PARSE(app, argc, argv);


    Graph graph;
    
    graph.read_file(file);

    std::chrono::_V2::system_clock::time_point start;
    std::chrono::_V2::system_clock::time_point end;
    double total = 0.0;

    for (int i = 0; i < rounds; i++) {
        
        if (use_tarjans_algorithm) {
            start = std::chrono::high_resolution_clock::now();
        
            tarjans_algorithm(&graph);
        
            end = std::chrono::high_resolution_clock::now();
        } else {
            if (file_regular_path_querying != "") {

                start = std::chrono::high_resolution_clock::now();
                
                std::__cxx11::list<std::string> my_list = regular_path_querying(&graph, file_regular_path_querying);

                // std::cout << "paries found: " << my_list.size() << std::endl;
                
            
                end = std::chrono::high_resolution_clock::now();
            }

        }

        std::chrono::duration<double, std::milli> elapsed = end - start;
        total += elapsed.count();
        // if (verbose) {
        //     std::cout << "Round " << i + 1 << ": " << elapsed.count() << " ms\n";
        // }
    }

    if (verbose){
        std::cout << "\nAverage over " << rounds << " rounds: " << total / rounds << " ms\n";
    }

}