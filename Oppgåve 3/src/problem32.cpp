
#include "graph.h"
#include "algorithms.h"
#include <CLI/CLI.hpp> 
#include <iostream>

using namespace db;

int main(int argc, char** argv) 
{
    // Argument parsing
    CLI::App app{"Oppgåve 3.2"};
    bool verbose = false;
    app.add_flag("-v,--verbose", verbose, "Verbose output");
    std::string file = "knowledge-graph-benchmark-data/kb04a.dat";
    app.add_option("-f,--file", file, "path to inputfile");
    std::string file_regular_path_querying;
    app.add_option("--rpq", file_regular_path_querying, "query file for regular_path_querying");


    CLI11_PARSE(app, argc, argv);

    Graph graph;
    graph.read_file(file);

    if (file_regular_path_querying != ""){
        std::list<std::string> list_of_string = regular_path_querying(&graph, file_regular_path_querying);
        for (auto& string : list_of_string){
            std::cout << string << std::endl;
        }
    }



}