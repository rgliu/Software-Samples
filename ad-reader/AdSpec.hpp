//
//  AdSpec.hpp
//  simplfiProject
//
//  Created by Richard Liu on 10/29/23.
//

#ifndef AdSpec_hpp
#define AdSpec_hpp

#include <stdio.h>
#include <iostream>

// 1234,    320,    250,    1.0,            ["mazda", 0.0, "cars", 0.5, "mazda3", 1.5]
// ad id,   width,  height, default bid,    [keyword, bid]
// if bid to keyword is 0.0m then default bid is to be used

typedef std::pair<int,int> AdSize;

class AdSpec {
public:
    AdSpec(int aID, AdSize size, float defaultBid, std::unordered_map<std::string, float> kwMap);

    void print();

    // Return largest bid found, -1 if no keywords found
    float searchAd(std::vector<std::string> keywords);

private:
    int _aID;
    AdSize _size;
    float _defaultBid;
    std::unordered_map<std::string, float> _kwMap;
};
#endif /* AdSpec_hpp */
