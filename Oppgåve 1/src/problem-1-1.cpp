#include "defines.h" 


int main(int /*argc*/, char** /*argv*/) 
{
    /* Skriver ut sizeof de ulike datatypene*/
    short a;
    std::cout << "The sizeof a short is " << sizeof(a) << "\n";
    int b;
    std::cout << "The sizeof a int is " << sizeof(b) << "\n";
    long c;
    std::cout << "The sizeof a long is " << sizeof(c) << "\n";
    long long d;
    std::cout << "The sizeof a long long is " << sizeof(d) << "\n";
    bool e;
    std::cout << "The sizeof a bool is " << sizeof(e) << "\n";
    char f;
    std::cout << "The sizeof a char is " << sizeof(f) << "\n";
    void* g;
    std::cout << "The sizeof a void pointer is " << sizeof(g) << "\n";
    double h;
    std::cout << "The sizeof a double is " << sizeof(h) << "\n";

    // Lager en peker til adressen til b
    int* ptr_b = &b;

    // adressen til b og &b+1
    // for å sbrive ut differansen i antall byte og ikke antall int konverterer vi til uint8_t
    std::cout << "\n";
    std::cout << "minneadressen til en tillfeldig int er " << ptr_b << "\n" 
        << "minneadressen med incrementering er " << ptr_b + 1 << "\n"
        << "differansen er " << (uint8_t*)(ptr_b + 1) - (uint8_t*)ptr_b << "\n";
}