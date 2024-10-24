#include <iostream>
#include <string>
#include "clipp.h"

using namespace clipp;
using std::cout;
using std::string;

// exe /home/lemon/readme.txt --format png -I 20
int main(int argc, char** argv) {
    std::string filename, fmt = "csv";
    bool flag = false;
    int iterations = 10;
    auto cli = (value("input file", filename),
        option("-f", "-F", "--format").set(flag) & value("fmt", fmt),
        option("-i", "-I", "--iterations") & value("iterations", iterations));
    if (parse(argc, const_cast<char**>(argv), cli)) {
        std::cout << "filename: " << filename << "\n"
            << "fmt: " << fmt << "\n"
            << "flag: " << flag << "\n"
            << "iterations: " << iterations << std::endl;
    }
    else {
        std::cerr << make_man_page(cli, argv[0]) << std::endl;
    }
    return 0;
}