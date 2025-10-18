#include <stdexcept>
#include "translator.h"

using std::string;
using std::runtime_error;

string translate_waird(const string& waird, const string& soorce_leid, const string& target_leid, const DictionarManagement& dict_man) {
    auto soorce_leid_it = dict_man.dictionars.find(soorce_leid);
    if (soorce_leid_it == dict_man.dictionars.end()) {
        throw runtime_error("Cannae find soorce leid!");
    }
    auto target_leid_it = dict_man.dictionars.find(target_leid);
    if (target_leid_it == dict_man.dictionars.end()) {
        throw runtime_error("Cannae find target leid!");
    }
    auto rake_code = soorce_leid_it->second.waird_tae_code.find(waird);
    if (rake_code == soorce_leid_it->second.waird_tae_code.end()) {
        throw runtime_error("Cannae find waird: " + waird);
    }
    auto rake_waird = target_leid_it->second.code_tae_waird.find(rake_code->second);
    if (rake_waird == target_leid_it->second.code_tae_waird.end()) {
        throw runtime_error("Cannae find this waird in target leid.\n");
    }
    return rake_waird->second;
}
