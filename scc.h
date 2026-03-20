#pragma once
#include "graph.h"

#include <set>
#include <vector>
#include <string>
#include <unordered_map>
#include <stack>
#include <functional>
#include <algorithm>

std::vector<std::vector<std::string>> tarjan_scc(AbstractGraph* graph);

std::vector<std::pair<std::string,std::string>>
find_diamonds(
    AbstractGraph* g,
    const std::set<std::string>& even_labels,
    const std::set<std::string>& odd_labels);
