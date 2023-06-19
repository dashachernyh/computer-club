#include <iostream>
#include "work.h"

int main(int argc, char** argv) {

    if (argc != 2) {
        std::cerr << "Wrong parameters in command line! Excpect : *.exe *.txt\n";
        return -1;
    }
    std::string file_name (argv[1]);
    work_in_club(file_name);
    return 0;
}