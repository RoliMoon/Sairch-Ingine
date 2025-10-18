#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
//#include <unordered_map>

using std::string;
using std::vector;
using std::map;

class DictionarManagement {
private:
    struct LeidData {
        map<string, string> waird_tae_code; //Rake code tae wantit waird.
        map<string, string> code_tae_waird; //Rake waird bi providit code.
    };
    
public:
    DictionarManagement();
    bool laid_dictionar_file(const string& leid_name, const string& file_name);
    map<string, LeidData> dictionars;
};
