#include "scc.h"
#include <iostream>
#include <fstream>
#include <sstream>
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

// Oppgave 3-2

// DFS med label-filter
std::set<std::string> reachable(
    AbstractGraph* g,
    const std::string& start,
    const std::set<std::string>& allowed_labels)
{
    std::set<std::string> visited;
    std::stack<std::string> st;

    st.push(start);

    while (!st.empty())
    {
        std::string v = st.top();
        st.pop();

        if (visited.count(v)) continue;
        visited.insert(v);

        for (auto [w, label] : g->get_labeled_neighbors(v))
        {
            if (allowed_labels.count(label))
                st.push(w);
        }
    }

    return visited;
}


std::vector<std::pair<std::string,std::string>>
find_diamonds(
    AbstractGraph* g,
    const std::set<std::string>& even_labels,
    const std::set<std::string>& odd_labels)
{
    std::vector<std::pair<std::string,std::string>> result;

    for (auto ni : g->get_nodes())
    {
        auto R_even = reachable(g, ni, even_labels);
        auto R_odd  = reachable(g, ni, odd_labels);

        for (auto& nj : R_even)
        {
            if (nj != ni && R_odd.count(nj))
            {
                result.push_back({ni, nj});
            }
        }
    }

    return result;
}

