/*
 * Example to show the contrast between C and C++ strings:
 * 
 * C strings are of type char*, they are character arrays;
 * since arrays are pointers, they are always passed by reference.
 * It is impossible to pass them by value.
 * 
 * C++ strings are of type std::string and can be passed by value.
 */

#include <iostream>
#include <array>

namespace
{
    // Send ved verdi. Kopi lages, endringen skjer bare inne i funksjonen, orginalen forblir lik
   void increment_value(int p, std::array<char,7> arr)
   {
      std::cout << "increment_value:\n";
      arr[p]++;
      std::cout << "Inside by_value: " << arr.data() << "\n";
   }

   // Send ved referanse. Samme objekt brukes. Originalen endres
   void increment_reference(int p, std::array<char,7>& arr)
   {
      std::cout << "increment_reference: \n";
      arr[p]++;   
      std::cout << "Inside by_reference: " << arr.data() << "\n";
   }
}

int main()
{
   std::array<char,7> arr = {'I','N','F','2','0','5','\0'};

   increment_value(5, arr);
   std::cout << "After value call: " << arr.data() << "\n";
   
   
   increment_reference(5, arr);
   std::cout << "After reference call: " << arr.data() << "\n";
}
