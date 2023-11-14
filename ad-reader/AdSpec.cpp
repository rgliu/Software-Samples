//
//  AdSpec.cpp
//  simplfiProject
//
//  Created by Richard Liu on 10/29/23.
//

#include "AdSpec.hpp"

AdSpec::AdSpec(int aID, AdSize size, float defaultBid, std::unordered_map<std::string, float> kwMap)
    : _aID(aID)
    , _size(size)
    , _defaultBid(defaultBid)
    , _kwMap(kwMap) {}

void AdSpec::print() {
    std::cout << "aID:" << _aID << " size:" << _size.first << "x" << _size.second << " defaultBid:" << _defaultBid << " [";

    for (auto itr = _kwMap.begin(); itr != _kwMap.end(); itr++) {
        std::cout << "(kw:" << itr->first
             << " bid:" << itr->second << ")";
    }

    std::cout << "]\n";
}

float AdSpec::searchAd(std::vector<std::string> keywords) {
    float largestBid = 0;
    for (int i = 0; i < keywords.size(); i++) {
        auto itr = _kwMap.find(keywords[i]);
        if (itr != _kwMap.end() && itr->second > largestBid) {
            std::cout << "KeywordFound:" << itr->first << "\n";
            largestBid = itr->second;
        }
    }
    return largestBid;
}
