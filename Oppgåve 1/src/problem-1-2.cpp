#include "defines.h" 

void print_hex(unsigned char* char_ptr, size_t array_size);

int main(int /*argc*/, char** /*argv*/) 
{
    // Problem_2
    short a_short = -12;
    int a_int = -12;
    long a_long = -12;
    long long a_long_long = -12;
    // unsigned char* char_ptr = (unsigned char*)&a_short;
    
    std::cout << "The values stored in the short variable is \n" ;
    print_hex((unsigned char*)&a_short, sizeof(a_short));
    std::cout << "\n";
    
    std::cout << "The values stored in the int variable is \n" ;
    print_hex((unsigned char*)&a_int, sizeof(a_int));
    std::cout << "\n";
    
    std::cout << "The values stored in the long variable is \n" ;
    print_hex((unsigned char*)&a_long, sizeof(a_long));
    std::cout << "\n";
    
    std::cout << "The values stored in the long long variable is \n" ;
    print_hex((unsigned char*)&a_long_long, sizeof(a_long_long));
    std::cout << "\n";
    
}

void print_hex(unsigned char* char_ptr, size_t array_size)
{
    std::cout << std::hex << std::uppercase << "0x" ;
    for (size_t i = 0; i < array_size; i++)
    {
        std::cout << (int)char_ptr[i];
    }
    
    std::cout << "\n" << std::dec << std::nouppercase;
}