//
//  AdFile.cpp
//  simplfiProject
//
//  Created by Richard Liu on 10/29/23.
//

#include "AdFile.hpp"

constexpr auto max_size = std::numeric_limits<std::streamsize>::max();

// 1234,    320,    250,    1.0,            ["mazda", 0.0, "cars", 0.5, "mazda3", 1.5]
// ad id,   width,  height, default bid,    [keyword, bid]
// if bid to keyword is 0.0m then default bid is to be used

AdFile::AdFile(std::ifstream &input)
{
    parseFile(input);
}

AdFile::~AdFile()
{
    _adMap.clear();
}


AdSearchOutput AdFile::searchAdFile(AdSize size, std::vector<std::string> keywords) {
    // AdSearchOutput - (ID, highestBid)
    AdSearchOutput out = std::make_pair(0,0.0);

    // Find all ads of provided size
    auto it1 = _adMap.find(size);
    if (it1 == _adMap.end()) {
        // Size not found
        std::cout << "Ad size not found\n";
        return out;
    }

    // Iterate through all IDs of provided size looking for keyword
    // Save ID and largest bid found
    for (auto it2 = it1->second.begin(); it2 != it1->second.end(); it2++) {
        float tmpBid = it2->second->searchAd(keywords);
        if (tmpBid > out.second) {
            out.first = it2->first;
            out.second = tmpBid;
            tmpBid = -1;
        }
    }

    // No ID assigned
    if (out.first == 0) {
        std::cout << "Ad keyword not found\n";
    }

    return out;
}

void AdFile::parseFile(std::ifstream &input) {
    std::string line;
    while (std::getline(input, line)) {
        std::istringstream iss(line);
        //std::cout << line << "\n";

        // Ad ID
        int aID;
        iss >> aID;
        if (iss.peek() == ',') {
            iss.ignore();
        } else {
            std::cout << "[ERROR] 1 Parsing unsuccessful, check file\n";
            break;
        }

        // Ad Dimensions
        AdSize size;
        iss >> size.first;
        if (iss.peek() == ',') {
            iss.ignore();
        } else {
            std::cout << "[ERROR] 2 Parsing unsuccessful, check file\n";
            break;
        }
        iss >> size.second;
        if (iss.peek() == ',') {
            iss.ignore();
        } else {
            std::cout << "[ERROR] 3 Parsing unsuccessful, check file\n";
            break;
        }

        // Ad Default Bid
        float defaultBid;
        iss >> defaultBid;
        if (iss.peek() == ',') {
            iss.ignore();
        } else {
            std::cout << "[ERROR] 4 Parsing unsuccessful, check file\n";
            break;
        }

        // Keywords/Bids
        iss.ignore(max_size, '[');

        char ch;
        std::unordered_map<std::string, float> kwMap;
        while(iss >> ch) {
            if (ch == '"') { // Start of keyword
                std::string kw;
                float bid;
                std::getline( iss, kw, '"' ); // get until end of keyword

                if (iss.peek() == ',') {
                    iss.ignore();
                } else {
                    std::cout << "[ERROR] 6 Parsing unsuccessful, check file\n";
                    break;
                }

                iss >> bid;
                if (iss.peek() == ',') {
                    iss.ignore();
                } else if (iss.peek() == ']') {
                    //std::cout << "[DEBUG] reached end of keywords\n";
                    iss.ignore();
                } else {
                    std::cout << "[ERROR] 7 Parsing unsuccessful, check file\n";
                    break;
                }

                // if bid is 0.0, assign to default bid
                bid = (bid == 0.0) ? defaultBid : bid;
                kwMap.insert({kw, bid});
            }
        }
        //_adMap
        std::shared_ptr<AdSpec> spec = std::make_shared<AdSpec>(aID, size, defaultBid, kwMap);
        std::pair<float, std::shared_ptr<AdSpec>> idPair = std::make_pair(aID, spec);
        auto it = _adMap.find(size);
        if (it == _adMap.end()) { // first entry of this size
            std::map<float, std::shared_ptr<AdSpec>> idMap;
            idMap.insert(idPair);
            _adMap.insert(std::make_pair(size, idMap));
        } else {
            it->second.insert(idPair);
        }
    }

    // Print
    for(auto it = _adMap.cbegin(); it != _adMap.cend(); ++it) {
        std::cout << "Size:" << it->first.first << "x" << it->first.second << "\n";
        int adCount = 0;
        for(auto it2 = it->second.cbegin(); it2 != it->second.cend(); ++it2) {
            adCount++;
            std::cout << "\t[id:" << it2->first << " ";
            it2->second->print();
        }
        std::cout << "Count:" << adCount << "\n\n";
    }
}
