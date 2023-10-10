#include "testlib.h"

#include <iostream>
#include <iomanip>
#include <map>
#include <functional>

class TheProc {
public:
    TheProc(std::string _name, std::string _key, std::string _region)
        : name(_name)
        , key(_key)
        , region(_region)
        , pid(generateProcID(_name))
    {
        // debug
        // std::cout << "CONSTRUCTOR - id: " << pid << " name:" << name << " keyword:" << key << " region:" << region << "\n";
    }

    ~TheProc()
    {
        // debug
        // std::cout << "DESTRUCTOR - id: " << pid << " name:" << name << " keyword:" << key << " region:" << region << "\n";
    }

    int Run(int length) {
        std::cout << "Running with ID " << pid << " length:" << length << std::setfill('.') << std::setw(length) << "" << std::endl;
        return static_cast<int>(length + key.length() + region.length());
    }

    std::string getName() {
        return name;
    }

    std::string getKey() {
        return key;
    }

    std::string getRegion() {
        return region;
    }

    std::size_t getID() {
        return pid;
    }

private:
    std::string name;
    std::string key;
    std::string region;
    std::size_t pid;

    std::size_t generateProcID(const std::string &name) {
        // Create unique ID using std::hash function
        std::hash<std::string>str_hash;
        std::size_t procID = static_cast<std::size_t>(str_hash(name));
        return procID;
    }
};


namespace {
    std::map<std::size_t, TheProc*> proc_map;
}


extern "C"
std::size_t CreateProc(const char *name, const char *key, const char *region) {
    TheProc* tmpProc = new TheProc(name, key, region);
    std::size_t tmpProcID = tmpProc->getID();

    // Check whether ID has already been used (same proc names)
    auto inserted = proc_map.insert(std::pair<std::size_t, TheProc*>(tmpProcID, tmpProc));
    if (inserted.second == true) {
        std::cout << "Created PROC - id:" << tmpProcID << " name:" << name << " keyword:" << key << " region:" << region << "\n";
    } else {
        std::cout << "ERROR: Name already exists! To overwrite, destroy proc id " << tmpProcID << " and try again\n";
        // Object won't be used, release now
        delete tmpProc;
    }

    return tmpProcID;
}

extern "C"
int RunProc(std::size_t pid, int process_length) {
    auto result = proc_map.find(pid);
    if (result != proc_map.end()) {
        result->second->Run(process_length);
    } else {
        std::cout << "ERROR: PROC_ID " << pid << " not found!\n";
    }
    return 0;
}

extern "C"
int GetProcName(std::size_t pid) {
    auto result = proc_map.find(pid);
    if (result != proc_map.end()) {
        std::cout << "Printing PROC - id:" << pid << " name:" << result->second->getName() << "\n";
    } else {
        std::cout << "ERROR: PROC_ID " << pid << " not found!\n";
    }
    return 0;
}

extern "C"
int DestroyProc(std::size_t pid) {
    auto result = proc_map.find(pid);
    if (result != proc_map.end()) {
        std::cout << "Released PROC - id:" << pid << " name:" << result->second->getName() << " keyword:" << result->second->getKey() << " region:" << result->second->getRegion() << "\n";
        delete result->second;
        proc_map.erase(result);
    } else {
        std::cout << "ERROR: PROC_ID " << pid << " not found!\n";
    }
    return 0;
}
