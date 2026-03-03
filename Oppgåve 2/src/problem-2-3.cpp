
#include "problem-2-3.h"

int main(int /*argc*/, char** /*argv*/) 
{
    File_parser file_parser;
    file_parser.read_file("problem-2-3.txt");
    file_parser.write_to_file("problem-2-3_out.txt");
    
}