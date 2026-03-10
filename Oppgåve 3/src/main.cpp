
#include "graph.h"
#include <CLI/CLI.hpp> 
#include <iostream>

int main(int argc, char** argv) 
{
    // Argument parsing
    CLI::App app{"Oppgåve 3"};
    bool verbose = false;
    app.add_flag("-v,--verbose", verbose, "Verbose output");
    CLI11_PARSE(app, argc, argv);

    //

}