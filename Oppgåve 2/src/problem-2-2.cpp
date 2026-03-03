
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
        //return 1 as error. can be printed in terminal if program has error
        // echo $?
        return 1;
    } 
    // buffering the string.
    std::stringstream buffer_inn;
    buffer_inn << file_stream_inn.rdbuf(); 
    file_stream_inn.close();

    // storing the string stream in a list to show that the proigram is capable of using the values
    std::vector<my_string> list_of_my_string;
    std::string line;
    //unsure why the line ends in . as the newline character separates the comands.
    while (std::getline(buffer_inn, line)) {

        std::stringstream stringstream(line);
        my_string temp_string;
        stringstream >> temp_string.a >> temp_string.b >> temp_string.c;
        //removing "."
        temp_string.c.pop_back();

        list_of_my_string.push_back(temp_string);
    }

    //buffering for output. This cold be an ofstream insted.
    std::stringstream buffer_out;

    for (my_string& item : list_of_my_string){
        buffer_out << item.a << " " << item.b << " " << item.c << "." << std::endl;
        std::cout << item.a << " " << item.b << " " << item.c << "." << std::endl;
    }

    std::ofstream file_stream_out("problem-2-2_out.txt");
    if (!file_stream_inn){
        std::cout << "file not created. \n";
        //return 1 as error. can be printed in terminal if program has error
        // echo $?
        return 1;
    } 
    // writing to file to show that the innput file is written corectly to an output.
    file_stream_out << buffer_out.rdbuf();


}

