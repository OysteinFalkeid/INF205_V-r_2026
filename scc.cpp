#include "scc.h"
#include <iostream>
#include <unordered_map>
#include <map>
#include <set>
#include <stack>
#include <functional>
#include <algorithm>

struct TarjanState {
    AbstractGraph* graph;

    std::map<std::string,int> index;
    std::map<std::string,int> lowlink;
    std::stack<std::string> S;
    std::set<std::string> onStack;

    int currentIndex = 0;

    std::vector<std::vector<std::string>> result;
};

void strongconnect(const std::string& v, TarjanState& state)
{
    state.index[v] = state.currentIndex;
    state.lowlink[v] = state.currentIndex;
    state.currentIndex++;

    state.S.push(v);
    state.onStack.insert(v);

    for (auto w : state.graph->get_neighbors(v))
    {
        if (state.index.find(w) == state.index.end())
        {
            strongconnect(w, state);
            state.lowlink[v] = std::min(state.lowlink[v], state.lowlink[w]);
        }
        else if (state.onStack.count(w))
        {
            state.lowlink[v] = std::min(state.lowlink[v], state.index[w]);
        }
    }

    if (state.lowlink[v] == state.index[v])
    {
        std::vector<std::string> scc;

        while (true)
        {
            std::string w = state.S.top();
            state.S.pop();
            state.onStack.erase(w);
            scc.push_back(w);

            if (w == v) break;
        }

        state.result.push_back(scc);
    }
}

std::vector<std::vector<std::string>> tarjan_scc(AbstractGraph* graph)
{
    TarjanState state;
    state.graph = graph;

    for (auto v : graph->get_nodes())
    {
        if (state.index.find(v) == state.index.end())
        {
            strongconnect(v, state);
        }
    }

    return state.result;
}