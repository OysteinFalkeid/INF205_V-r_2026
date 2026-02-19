#include <iostream>
using namespace std;

int main(){
    // Lagrer tallverdier - 12 i ulike datatyper:

    short s = -12;
    int i = -12;
    long l = -12;
    long long ll = -12;

    // Ta adressen til en datatype
    //Tolk den som en char*. Bruker unsigned char for å unngå negative verdier

    unsigned char* p = (unsigned char*)&i;

    //Gå gjennom minnet en byte av gangen
    //Skrive ut hver byte i hex

    for (int j = 0; j < sizeof(i); j++){
        cout << "0x" << hex << (int)p[i] << " ";
    }

}