#include <iostream>
using namespace std;

int main(){

/* Skriver ut sizeof de ulike datatypene*/

std::cout << "Int: " << sizeof(int) << " bytes" << endl;
std::cout << "Short: " <<sizeof(short) << " bytes" << endl;
std::cout << "Double: " <<sizeof(double) << " bytes" << endl;
std::cout << "Char: " <<sizeof(char) << " bytes" << endl;
std::cout << "Long: " <<sizeof(long) << " bytes" << endl;
std::cout << "Long long: " <<sizeof(long long) << " bytes" << endl;



int x = 10; // Lager en variabel
int* p = &x; // Lager en peker til adressen til x

//Lagrer startadressen til x:
int* start = p;

//Skriver ut startadressen til x:
std::cout << "Adresse før inkrement: " << p << endl;

// Inkrementerer p, p++, så skal vi vise adressen blir flyttet akkurat sizeof(int) i minnet.
p++;

//Skriver ut sluttadressen til x:
std::cout << "Adresse etter inkrement: " << p << endl;


std::cout << "Forskjell i adresse = sizeof(int)" << (char*)p - (char*)start << endl;

}
