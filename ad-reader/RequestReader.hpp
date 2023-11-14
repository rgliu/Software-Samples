//
//  RequestReader.hpp
//  simplfiProject
//
//  Created by Richard Liu on 10/30/23.
//

#ifndef RequestReader_hpp
#define RequestReader_hpp

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "AdFile.hpp"
#include "AdSpec.hpp"

class RequestReader;

class RequestReaderFactory {
public:
    enum ReaderType {
        None = -1,
        Exchange1 = 0,
        Exchange2 = 1
    };

    RequestReaderFactory(AdFile* adFile, std::ifstream &input);
    ~RequestReaderFactory();
    void parseFile(std::ifstream &input);
    void setRequestReader(std::string domain);
private:
    std::unordered_map<ReaderType,std::shared_ptr<RequestReader>> _rReaderStore;
    std::shared_ptr<RequestReader> _rReader;
    AdFile* _adFile;
    ReaderType _curReaderType;
};

class RequestReader {
public:
    RequestReader(AdFile* adFile) { _adFile = adFile; };
    virtual ~RequestReader() {
        this->clear();
    };
    virtual void fulfillRequest(std::string request) = 0;
    virtual void parseKeyword(std::string request) = 0;
    virtual void parseSize(std::string request) = 0;

    // Clear group of keywords and size
    // Must be overriden if non-base class members to be cleared
    virtual void clear() {
        _keywords.clear();
        _size = std::make_pair(0,0);
    };

protected:
    AdFile* _adFile;
    std::vector<std::string> _keywords;
    AdSize _size;
};

// Exchange 1 format
// domain is bid.simpli.fi
// kw=keyword1+keyword2+keyword3
// size=100x100 (widthxheight)
class Exchange1_RequestReader : public RequestReader {
public:
    Exchange1_RequestReader(AdFile* adFile) : RequestReader(adFile){};
    ~Exchange1_RequestReader(){};
    void fulfillRequest(std::string request) override;
    void parseKeyword(std::string request) override;
    void parseSize(std::string request) override;
};

// Exchange 2 format
// domain is simpli.fi
// keywords=keyword1+keyword2+keyword3
// ad_width=100&adheight=100
class Exchange2_RequestReader : public RequestReader {
public:
    Exchange2_RequestReader(AdFile* adFile) : RequestReader(adFile){};
    ~Exchange2_RequestReader(){};
    void fulfillRequest(std::string request) override;
    void parseKeyword(std::string request) override;
    void parseSize(std::string request) override;
};

#endif /* RequestReader_hpp */
