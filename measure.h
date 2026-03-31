#pragma once
#include "graph.h"
#include <set>
#include <string>

void measure_scc(AbstractGraph* g, int iter);

void measure_diamonds(
    AbstractGraph* g,
    std::vector<std::string>& even,
    std::vector<std::string>& odd,
    int iter);