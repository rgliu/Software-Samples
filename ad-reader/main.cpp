//
//  main.cpp
//  simplfiProject
//
//  Created by Richard Liu on 10/29/23.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "AdFile.hpp"
#include "RequestReader.hpp"

int main(int argc, const char * argv[]) {
    if (argc >= 2) {
        std::string adsFileName(argv[1]);
        std::string requestsFileName(argv[2]);

        // read ads.txt
        std::ifstream input1(adsFileName);
        AdFile* file = new AdFile(input1);

        // read request
        std::ifstream input2(requestsFileName);
        RequestReaderFactory* rFactory = new RequestReaderFactory(file, input2);

        delete rFactory;
        delete file;
    } else {
        std::cout << "Please supply arguments";
    }
}
