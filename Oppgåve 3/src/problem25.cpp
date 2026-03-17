
#include "graph.h"
#include "algorithms.h"
#include <CLI/CLI.hpp> 
#include <iostream>

using namespace db;

int main(int argc, char** argv) 
{
    // Argument parsing
    CLI::App app{"Oppgåve 2.5"};
    bool verbose = false;
    app.add_flag("-v,--verbose", verbose, "Verbose output");
    std::string file = "graph_inn.txt";
    app.add_option("-f,--file", file, "path to inputfile");


    CLI11_PARSE(app, argc, argv);

    db::Graph graph;
    graph.read_file(file);
    graph.disconnect("node_a_label", "node_b_label");
    graph.remove_node("node_d_label");

    graph.write_to_file("graph_1.txt");
}