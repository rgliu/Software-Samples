//
//  RequestReader.cpp
//  simplfiProject
//
//  Created by Richard Liu on 10/30/23.
//

#include "RequestReader.hpp"

RequestReaderFactory::RequestReaderFactory(AdFile* adFile, std::ifstream &input) {
    _adFile = adFile;
    _rReader = NULL;
    _curReaderType = ReaderType::None;
    parseFile(input);
};

RequestReaderFactory::~RequestReaderFactory() {
    _rReader.reset(); // first ref count
    _rReaderStore.clear(); // second ref count
};

void RequestReaderFactory::parseFile(std::ifstream &input) {
    std::string line;
    while (std::getline(input, line)) {
        // Extract domain ie. http ://this.is.mydomain/
        size_t domainStart = line.find_first_of(":") + 3; // + 3 because of "//"
        size_t domainEnd = line.find("/", domainStart); // find the next "/" after http(s)://
        std::string domain = line.substr(domainStart, domainEnd - domainStart);
        std::cout << "Domain found: " << domain << "\n";

        // Set strategy (which exchange submitted the request)
        setRequestReader(domain);

        // Parse line for keyword and size
        // Fulfill request
        _rReader->fulfillRequest(line);
    }
}

void RequestReaderFactory::setRequestReader(std::string domain) {
    // Clear saved keywords and size
    if (_rReader != NULL) {
        _rReader->clear();
    }

    // Determine exchange based off of domain
    // Pick strategy based off of exchange
    if (domain == "bid.simpli.fi") {
        _curReaderType = ReaderType::Exchange1;
        // if currently does not exist
        if (_rReaderStore.find(_curReaderType) == _rReaderStore.end()) {
            _rReaderStore.insert({ReaderType::Exchange1, std::make_shared<Exchange1_RequestReader>(_adFile)});
        }
        _rReader = _rReaderStore[_curReaderType];
    } else if (domain == "simpli.fi") {
        _curReaderType = ReaderType::Exchange2;
        // if currently does not exist
        if (_rReaderStore.find(_curReaderType) == _rReaderStore.end()) {
            _rReaderStore.insert({ReaderType::Exchange2, std::make_shared<Exchange2_RequestReader>(_adFile)});
        }
        _rReader = std::make_unique<Exchange2_RequestReader>(_adFile);
    } else {
        std::cout << "[ERROR] Domain not found in available readers\n";
    }
}

// Exchange 1 format
// domain is bid.simpli.fi
// kw=keyword1+keyword2+keyword3
// size=100x100 (widthxheight)
void Exchange1_RequestReader::parseKeyword(std::string request) {
    // Extract keyword snippet ie. keyword1+keyword2+keyword3
    std::string kwToFind = "kw=";
    size_t kwFound = request.find(kwToFind);
    size_t kwEndFound = request.find("&", kwFound+kwToFind.size());
    std::string kwSnippet = request.substr(kwFound+kwToFind.size(), kwEndFound - (kwFound+kwToFind.size()));

    // parse keywords using "+" as deliminator
    std::string kw;
    for (int i = 0; i < kwSnippet.size(); i++) {
        if (kwSnippet[i] != '+') {
            kw += kwSnippet[i];
        } else {
            _keywords.push_back(kw);
            kw.clear();
        }
    }
    // last word doesn't end with "+" so pushback one more
    _keywords.push_back(kw);
}

void Exchange1_RequestReader::parseSize(std::string request) {
    // Extract size snippet ie. widthxheight
    std::string sizeToFind = "size=";
    size_t sizeFound = request.find(sizeToFind);
    size_t sizeEndFound = request.find("&", sizeFound+sizeToFind.size());
    std::string sizeSnippet = request.substr(sizeFound+sizeToFind.size(), sizeEndFound - (sizeFound+sizeToFind.size()));

    // Split into width and height using "x" as deliminator
    std::string sizeTmp;
    for (int i = 0; i < sizeSnippet.size(); i++) {
        if (sizeSnippet[i] != 'x') {
            sizeTmp += sizeSnippet[i];
        } else {
            // width
            _size.first = std::stoi(sizeTmp);
            sizeTmp.clear();
        }
    }
    // height
    _size.second = std::stoi(sizeTmp);
}

void Exchange1_RequestReader::fulfillRequest(std::string request) {
    // Extract and save size and keywords
    parseSize(request);
    parseKeyword(request);

    // Print
    std::cout << "Size: " << _size.first << "x" << _size.second << "\n";
    for (int i = 0; i < _keywords.size(); i++) {
        std::cout << "Keyword: " << _keywords[i] << "\n";
    }
    std::cout << "\n";

    // Search input Ad File for size and keyword match
    AdSearchOutput out = _adFile->searchAdFile(_size, _keywords);
    std::cout << "RESULT - ID:" << out.first << " Bid:" << out.second << "\n\n";
}

// Exchange 2 format
// domain is simpli.fi
// keywords=keyword1+keyword2+keyword3
// ad_width=100&adheight=100
void Exchange2_RequestReader::parseKeyword(std::string request) {
    // Extract keyword snippet ie. keyword1+keyword2+keyword3
    std::string kwToFind = "keywords=";
    size_t kwFound = request.find(kwToFind);
    size_t kwEndFound = request.find("&", kwFound+kwToFind.size());
    std::string kwSnippet = request.substr(kwFound+kwToFind.size(), kwEndFound - (kwFound+kwToFind.size()));

    // parse keywords using "+" as deliminator
    std::string kw;
    for (int i = 0; i < kwSnippet.size(); i++) {
        if (kwSnippet[i] != '+') {
            kw += kwSnippet[i];
        } else {
            _keywords.push_back(kw);
            kw.clear();
        }
    }
    // last word doesn't end with "+" so pushback one more
    _keywords.push_back(kw);
}

void Exchange2_RequestReader::parseSize(std::string request) {
    // Extract size snippet
    // First Width ie. ad_width=100
    std::string adWidthToFind = "ad_width=";
    size_t adWidthFound = request.find(adWidthToFind);
    size_t adWidthEndFound = request.find("&", adWidthFound+adWidthToFind.size());
    std::string adWidthSnippet = request.substr(adWidthFound+adWidthToFind.size(), adWidthEndFound - (adWidthFound+adWidthToFind.size()));
    _size.first = std::stoi(adWidthSnippet);

    // Then Height ie. ad_height=100
    std::string adHeightToFind = "ad_height=";
    size_t adHeightFound = request.find(adHeightToFind);
    size_t adHeightEndFound = request.find("&", adHeightFound+adHeightToFind.size());
    std::string adHeightSnippet = request.substr(adHeightFound+adHeightToFind.size(), adHeightEndFound - (adHeightFound+adHeightToFind.size()));
    _size.second = std::stoi(adHeightSnippet);
}

void Exchange2_RequestReader::fulfillRequest(std::string request) {
    // Extract and save size and keywords
    parseSize(request);
    parseKeyword(request);

    // Print
    std::cout << "Size: " << _size.first << "x" << _size.second << "\n";
    for (int i = 0; i < _keywords.size(); i++) {
        std::cout << "Keyword: " << _keywords[i] << "\n";
    }
    std::cout << "\n";

    // Search input Ad File for size and keyword match
    AdSearchOutput out = _adFile->searchAdFile(_size, _keywords);
    std::cout << "RESULT - ID:" << out.first << " Bid:" << out.second << "\n\n";
}
