/******************************************************************************
**  smd - A small example of a command-line tool                             **
**                                                                           **
**  Copyright (C) 2023 Sogrey, sogrey_0423@gmail.com                         **
**                                                                           **
**  Example How to Develop an Efficient Command Line Tool.                   **
******************************************************************************/

#include <iostream>
#include <stdlib.h>
#include <string.h>

void usage(){
    std::cout << "Usage: " << std::endl;
    std::cout << "   smd <input> [-d]" << std::endl << std::endl;
    std::cout << "   input      input something." << std::endl;
    std::cout << "   -d         optional, debug." << std::endl << std::endl;;
    std::cout << "   -h         optional, help info." << std::endl;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        usage();
        return 1;
    }
	
	bool debug = false;
	
	for (int i= 1; i < argc; ++i){
        std::string param = argv[i];
        if (false && i == (argc - 1) ){ // 仅一个参数
            std::cout << "Last param: " << param << std::endl;
        } else {
            if (param.at(0) == '-') {
                if (param.at(1) == 'h'){
					std::cout << "Param h(help): " << std::endl;
					usage();
                } else if (tolower(param.at(1)) == 'd'){
                    debug = true;
					std::cout << "Param d(debug): " << debug << std::endl;
                } else if (tolower(param.at(1)) == 'i'){
					std::string inoutParam = argv[++i];
					std::cout << "Input param i(input): " << inoutParam << std::endl;
                } else {
                    std::cout << "Invalid param: " << param << std::endl;
                }
            } else{
                std::cout << "Param: " << param << std::endl;
			}
        }
    }

}