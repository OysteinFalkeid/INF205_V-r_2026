#include "journal-article-index.h"
#include "defines.h" 

int main()
{
   litindex::JournalArticleIndex jai_i;
   jai_i.set_bibliographic_data(
      "IEEE_Access", 9, 0, 152333, 152346, 2021, "doi:10.1109/access.2021.3126429"
   );
   jai_i.set_page(152345);
   std::clog << "JournalArticleIndex jai_i:\n" << jai_i << "\n";

   std::clog << "\nWriting jai_i into a string stream.\n";
   std::ofstream of_file("temp.txt");
   //Sjekker om filen ble åpnet riktig:
   if (!of_file) {
      return 1;
   }

   std::ifstream if_file("temp.txt");
   //Sjekker om filen ble åpnet riktig:
   if (!if_file) {
      return 1;
   }

   of_file << jai_i;  // jai_i written into the stream "text"
   std::string text_content;
   text_content.assign(std::istreambuf_iterator<char>(if_file), std::istreambuf_iterator<char>());  // string export of the stream
   std::clog << "Text content of the stream is now as follows:\n" << text_content << "\n";
   
   litindex::JournalArticleIndex jai_j;
   std::clog << "\nReading jai_j from the string stream.\n";

   if_file >> jai_j;   // jai_j read from the stream "text"
   std::clog << "JournalArticleIndex jai_j:\n" << jai_j << "\n";

   of_file.close();
   if_file.close();
}