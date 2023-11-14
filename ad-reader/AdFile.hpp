//
//  AdFile.hpp
//  simplfiProject
//
//  Created by Richard Liu on 10/29/23.
//

#ifndef AdFile_hpp
#define AdFile_hpp

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>
#include "AdSpec.hpp"

// ID, Highest bid
typedef std::pair<int,float> AdSearchOutput;

class AdFile {
public:
    AdFile(std::ifstream &input);
    ~AdFile();

    // return ad ID with highest bid
    AdSearchOutput searchAdFile(AdSize size, std::vector<std::string> keywords);
private:
    void parseFile(std::ifstream &input);

    // group by size, then ID
    std::map<AdSize, std::map<float, std::shared_ptr<AdSpec>>> _adMap;
};

#endif /* AdFile_hpp */
