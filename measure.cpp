#include "measure.h"
#include "scc.h"
#include <chrono>
#include <iostream>

void measure_scc(AbstractGraph* g, int iter)
//tar inn grafen g og iter-hvor mange man kjører algoritmen
{
    //start tid, lagrer starttidspunkt
    auto t0 = std::chrono::high_resolution_clock::now();

    //tarjan algoritmen blir kjørt mange mange ganger
    for (int i = 0; i < iter; i++)
    {
        tarjan_scc(g);
    }

    //slutt tid
    auto t1 = std::chrono::high_resolution_clock::now();

    //forskjellen mellom start og sluttid
    auto delta = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count();

    //gjør om fra mikrosekunder til sekunder
    std::cout << "SCC tid: " << 1.0e-06 * delta << " sek\n";
}

void measure_diamonds(
    AbstractGraph* g,
    std::vector<std::string>& even,
    std::vector<std::string>& odd,
    int iter)
{
    auto t0 = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < iter; i++)
    {
        find_diamonds(g, even, odd);
    }

    auto t1 = std::chrono::high_resolution_clock::now();

    auto delta = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count();

    std::cout << "Diamonds tid: " << 1.0e-06 * delta << " sek\n";
}