#include "defines.h" 
#include <set>  // for std::set
#include <string>  // vi vil konvertere C-strengane til C++-strengar
#include <vector>
#include <unordered_set>

int main(int argc, char** argv)
{
    std::cout << "\nargv[0] er namnet til den køyrbare fila: " << argv[0] << "\n";
    
    std::vector<std::string> args;
    std::unordered_set<std::string> seen;

    for (int i = 0; i < argc; i++) {
        std::string arg = argv[i];

        if (arg[0] == '-') {
            if (seen.insert(arg).second) {
                args.push_back(arg);
                if (argv[i+1][0] != '-'){
                    i++;
                    arg = argv[i];
                    args.push_back(arg);
                }
            }
        }

    }

    for (const auto& arg : args) {
        std::cout << arg << std::endl;
    }
}