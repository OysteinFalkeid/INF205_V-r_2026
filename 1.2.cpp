#include <iostream>
using namespace std;

void print_s(short value){
    unsigned char* p = (unsigned char*)&value;

    std::cout << "short " << value << " , size = " << sizeof(value) << " bytes" << "\n";
    //Gå gjennom minnet en byte av gangen
    //Skrive ut hver byte i hex
    for (int j = 0; j < sizeof(value); j++){
        std::cout << "0x" << hex << (int)p[j] << " ";
    }
    cout << dec << "\n\n";
}

void print_i(int value){
    unsigned char* p = (unsigned char*)&value;

    std::cout << "int " << value << " , size = " << sizeof(value) << " bytes" << "\n";
    //Gå gjennom minnet en byte av gangen
    //Skrive ut hver byte i hex
    for (int j = 0; j < sizeof(value); j++){
        std::cout << "0x" << hex << (int)p[j] << " ";
    }
    cout << dec << "\n\n";
}

void print_l(long value){
    unsigned char* p = (unsigned char*)&value;

    std::cout << "long " << value << " , size = " << sizeof(value) << " bytes" << "\n";
    //Gå gjennom minnet en byte av gangen
    //Skrive ut hver byte i hex
    for (int j = 0; j < sizeof(value); j++){
        std::cout << "0x" << hex << (int)p[j] << " ";
    }
    cout << dec << "\n\n";
}

void print_ll(long long value){
    unsigned char* p = (unsigned char*)&value;

    std::cout << "long long " << value << " , size = " << sizeof(value) << " bytes" << "\n";
    //Gå gjennom minnet en byte av gangen
    //Skrive ut hver byte i hex
    for (int j = 0; j < sizeof(value); j++){
        std::cout << "0x" << hex << (int)p[j] << " ";
    }
    cout << hex << "\n\n";
}
int main(){
    // Lagrer tallverdier - 12 i ulike datatyper:

    short s = -12;
    int i = -12;
    long l = -12;
    long long ll = -12;

    // Ta adressen til en datatype
    //Tolk den som en char*. Bruker unsigned char for å unngå negative verdier

    print_s(s);
    print_i(i);
    print_l(l);
    print_ll(ll);

}
