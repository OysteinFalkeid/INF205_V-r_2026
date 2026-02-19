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
   std::ifstream infile("Bookindex.txt");

   if (!infile){
    std::cout << "Kan ikke åpne filen for lesing" << "\n";
    return 1;
   }

   int n;
   infile >> n;

   std::vector<litindex::BookIndex> books;

   for (int i = 0; i < n; i++){
    int c,s,p;
    infile >> c >> s >> p;
    litindex::BookIndex b(c,s,p);
    books.push_back(b);
    }

   std::cout << "\nBookIndex example:\n";
   litindex::BookIndex idx(1, 11, 24);
   
   
   
   idx.out();  // print status
   start_chapter(idx);
   idx.out();  // print status
}
