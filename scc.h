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


