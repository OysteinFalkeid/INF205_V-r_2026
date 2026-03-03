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

class File_parser
{
private:
    /* data */
    std::stringstream buffer;
    void parse_buffer();
public:
    File_parser(/* args */);
    ~File_parser();

    std::list<my_string> list_of_my_string;

    int read_file(std::string file_path);
    int write_to_file(std::string file_path);
};

File_parser::File_parser(/* args */)
{
}

File_parser::~File_parser()
{
}

int File_parser::read_file(std::string file_path){
    std::ifstream file_inn(file_path);
    if (!file_inn){
        return 1;
    }

    buffer.str("");
    buffer.clear();
    buffer << file_inn.rdbuf();
    file_inn.close();

    parse_buffer();

    return 0;
}

void File_parser::parse_buffer(){
    std::string line;
    while (std::getline(buffer, line)) {
        
        std::stringstream stringstream(line);
        my_string temp_string;
        stringstream >> temp_string.a >> temp_string.b >> temp_string.c;
        temp_string.c.pop_back();
        
        list_of_my_string.push_back(temp_string);
    }
}

int File_parser::write_to_file(std::string file_path){
    std::ofstream file_out(file_path);
    if (!file_out){
        return 1;
    }
    for (my_string& item : list_of_my_string){
        file_out << item.a << " " << item.b << " " << item.c << "." << std::endl;
    }
    file_out.close();
    return 0;
}