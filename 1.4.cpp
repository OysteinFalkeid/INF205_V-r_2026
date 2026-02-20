#include "book-index.h"
#include <iostream>
#include <fstream>
#include <vector>

namespace
{
   void start_chapter(litindex::BookIndex b)
   {
      std::cout << "start_chapter(litindex::BookIndex b)\n";

      b.next_chapter();
      b.out();  // print status
   }
}

int main()
{
   //Åpner fila for lesing
   std::ifstream infile("Bookindex.txt");

   //Sjekker om fila eksisterer, gir feilmelding ellers
   if (!infile){
    std::cout << "Kan ikke åpne filen for lesing" << "\n";
    return 1;
   }

   // leser inn første taller, n er første tallet i fila
   int n;
   infile >> n;

   //Oppretter en tom vektor som kan lagre objektene
   std::vector<litindex::BookIndex> books;

   for (int i = 0; i < n; i++){
      //Leser en linje fra fila
      int c,s,p;
      infile >> c >> s >> p;
      //Lager objektet og kaller på konstruktøren
      litindex::BookIndex b(c,s,p);
      books.push_back(b); //Legger til bakerst i vektoren. 
      //Så den første som blir bakerst havner først når løkka er ferdig
    }

   std::cout << "\nObjekter lest fra fil:\n";
   // Går gjennom hvert element i vektoren og skriver ut. Kaller på out funksjonen i h-fila
   for (const auto& b : books) {
    b.out();
   }
}
