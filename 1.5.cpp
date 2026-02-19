#include <iostream>
#include <set>
#include <vector>
#include <string>

int main(int argc, char** argv)
{
   std::cout << "\nargv[0] er namnet til den køyrbare fila: "
             << argv[0] << "\n";

   std::set<std::string> sett;          // for å sjekke duplikat
   std::vector<std::string> rekkefolge; // for å bevare rekkefølge

      // Går gjennom alle argumentene
   for (int i = 0; i < argc; i++)
   {
      std::string arg = argv[i]; // gjør om til std::string

      if (sett.insert(arg).second)  // true hvis ikke sett før
      {
         rekkefolge.push_back(arg);
      }
   }

   // printer elementene i samme rekkefølge som de ble skrevet inn i
   for (const auto& s : rekkefolge)
      std::cout << "\targument: \"" << s << "\"\n";
}
