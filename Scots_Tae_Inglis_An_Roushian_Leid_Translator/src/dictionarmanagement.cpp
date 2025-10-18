#include <fstream>
#include <sstream>
#include "dictionarmanagement.h"

using std::cin;
using std::cout;
using std::cerr;
using std::endl;

DictionarManagement::DictionarManagement() {}

bool DictionarManagement::laid_dictionar_file(const string& leid_name, const string& file_name) {
    std::ifstream leid_dictionar(file_name);
    if (!leid_dictionar.is_open()) {
        cerr << "Eeror o openin file: " << file_name << endl;
        return false;
    }

    LeidData data_base;
    string line;

    while (std::getline(leid_dictionar, line)) {
        line.erase(line.find_last_not_of(" \n\r\t") + 1);
        line.erase(0, line.find_first_not_of(" \n\r\t"));

        if (line.empty()) continue;
        size_t poseetion = line.find(" = ");
        if (poseetion != string::npos) {
            string key = line.substr(0, poseetion);
            string value = line.substr(poseetion + 3);

            data_base.waird_tae_code[key] = value;
            data_base.code_tae_waird[value] = key;
        }
    }
    dictionars[leid_name] = data_base;
    return true;
}