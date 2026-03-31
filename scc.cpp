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

// Oppgave 3.1
//Struktur
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
{// tar inn referanse til den delte staten. &betyr at vi jobber på den samme staten

    //index[v] er tidsstempelet. Når ble denne noden besøkt?
    state.index[v] = state.currentIndex; 
    // starter likt, men oppdateres underveis. 
    // Dette er den laveste index-verdien som kan nåes fra noden v i DFS-treet
    // Antar at v ikke kan nå noen tidligere node. -> lowlink = index
    state.lowlink[v] = state.currentIndex; 
    // Teller, som økes rett etter at node v får sin index, og før vi utforsker naboer.
    // Neste node som besøkes skal få et høyere tidsstempel enn node v
    state.currentIndex++; 

    //legger v på stakken - som inneholder alle noder som kan tilhøre en scc som ikke er ferdig enda
    // samle noder som tilhører samme SCC
    state.S.push(v);
    //legger v til onstack settet. rask oppslag
    // et sett for å sjekke raskt om en node er på stakken, fordi det er tregt å søke gjennom en stakk 
    state.onStack.insert(v); 

    // går gjennom alle naboer node(r) w som node v har, og kan nå ut til
    for (auto w : state.graph->get_neighbors(v)) 
    {
        // sjekker om naboen w er besøkt enda
        if (state.index.find(w) == state.index.end()) 
        {
            //kaller rekursivt på den ubesøkte naboen w
            // den holder noden på vent og utforsker alle naboene og naboene til naboene
            // før den vender tilbake og oppdaterer lowlink[v]
            strongconnect(w, state); 
            state.lowlink[v] = std::min(state.lowlink[v], state.lowlink[w]); //oppdaterer lowlink
        }
        else if (state.onStack.count(w)) // w er allerede besøkt?
        {   // hvis w allerede er besøkt så tilhører den en ferdig behandlet scc. 
            // da har den ingenting med å gjøre med de andre nodene vi skal så på, fordi det er ikke koblinger mellom sccer
            state.lowlink[v] = std::min(state.lowlink[v], state.index[w]);
        }
    }

    // v er roten. v kan ikke nå noen node med lavere index enn seg selv
    // v har ikke noe vei tilbake til en tidligere node. 
    // så alt som ligger på stakken over v må tilhøre samme scc som v
    if (state.lowlink[v] == state.index[v]) 
    {
        // oppretter en tom liste som kan samle salle nodene i denne sccen
        std::vector<std::string> scc; 

        while (true)
        {   
            // tar den øverste noden av stakken
            std::string w = state.S.top(); 
             // fortsetter å poppe helt til vi når v
            state.S.pop();
            //fjerner w fra onstack siden den tilhører en bestemt scc
            state.onStack.erase(w); 
            //legger den i den gjeldende scc listen
            scc.push_back(w); 

            //når vi har poppet selve roten v er vi ferdige med denne sccen. 
            // stopper løkken
            if (w == v) break; 
        }
        //legger den ferdige sccen inn i resultat listen. Er ferdige med denne noden
        state.result.push_back(scc); 
    }
}

std::vector<std::vector<std::string>> tarjan_scc(AbstractGraph* graph)
{// Tar en inn peker til en graf og returnerer en liste av scc. Hver scc er en
    //en liste med node-navn vector<string>, returtypen er liste av lister
    // Oppretter struktur
    TarjanState state;
    //Lagrer pekeren til grafen in i state'en
    state.graph = graph;

    //Itererer over alle noder i grafen
    for (auto v : graph->get_nodes()) 
    {   //Sjekker om noden v allerede har fått tildelt en index
        // hvis find() returnerer end() finnes ikke v i index-kartet
        if (state.index.find(v) == state.index.end())
        {   
            // starter DFS fra node v. Vil rekursivt utforske alle noder som er nåbare fra v
            strongconnect(v, state); 
        }
    }
    // underveis fylles denne med ferdige scc'er. så returneres den

    return state.result; 
}

// Oppgave 3.2

std::set<std::string> follow_path(
    AbstractGraph* g,
    const std::string& start,
    const std::vector<std::string>& labels)
{
    // holder alle noder man er på nå
    std::set<std::string> current;
    //legger til startnoden
    current.insert(start);

    //går gjennom en label av gangen
    for (const auto& label : labels)
    {
        //nye noder etter et steg
        std::set<std::string> next;

        // for hver node du er på
        for (const auto& v : current)
        {   // se på alle kanter ut fra node v
            for (auto [w, edge_label] : g->get_labeled_neighbors(v))
            {
                // følg bare kanter med riktig label
                if (edge_label == label)
                {   //legg til neste node
                    next.insert(w);
                }
            }
        }
        //oppdater settet
        current = next;

        //stopp hvis det er tomt
        if (current.empty())
            break;
    }

    return current;
}


std::vector<std::pair<std::string,std::string>>
find_diamonds(
    AbstractGraph* g,
    const std::vector<std::string>& even_labels,
    const std::vector<std::string>& odd_labels)
{
    //vil unngå duplikater, bruker set
    std::set<std::pair<std::string,std::string>> unique;

    //for hver node ni, finn alle noder du kan nå via
    // even-path og odd-path
    for (auto ni : g->get_nodes())
    {
        // finn alle som kan nåes via stien even
        auto R_even = follow_path(g, ni, even_labels);
        // finn alle som kan nåes via stien odd
        auto R_odd  = follow_path(g, ni, odd_labels);

        //tar snittet
        //for hver node du når via even
        for (auto& nj : R_even)
        {
            // sjekk også om du gjør det via odd.
            //unngå "trivial case"
            if (nj != ni && R_odd.count(nj))
            {
                // legg til resultat (startnode, sluttnode)
                unique.insert({ni, nj});
            }
        }
    }
    // returnerer resultatet
    // gjør set om til vektor
    return std::vector<std::pair<std::string,std::string>>(unique.begin(), unique.end());
}

