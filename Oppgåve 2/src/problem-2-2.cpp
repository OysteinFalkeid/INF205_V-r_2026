
#include "problem-2-2.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <list>
#include <vector>

struct my_string{
    std::string a;
    std::string b;
    std::string c;
};

int main(int /*argc*/, char** /*argv*/) 
{
    // setting upp an inn stream to read from the file.
    std::ifstream file_stream_inn("problem-2-2.txt");
    if (!file_stream_inn){
        std::cout << "file not found. \n";
        return 1;
    } 

    std::vector<my_string> list_of_my_string;
    std::string line;
    while (std::getline(file_stream_inn, line)) {

        std::stringstream stringstream(line);
        my_string temp_string;
        stringstream >> temp_string.a >> temp_string.b >> temp_string.c;
        temp_string.c.pop_back();

        list_of_my_string.push_back(temp_string);
    }

    file_stream_inn.close();

    for (int i=0; i<3; i++){
        std::cout << list_of_my_string[i].a << list_of_my_string[i].b << list_of_my_string[i].c << std::endl;
    }

}

