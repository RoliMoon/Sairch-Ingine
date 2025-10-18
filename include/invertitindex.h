#pragma once

#include <string>
#include <vector>
#include <map>

#include "converterjson.h"

/*==========================================
== File: InvertitIndex.h                  ==
== Creatit bi RoliMoon.                   ==
== Date: 15/08/2025                       ==
== This cless responsible for indexin.    ==
==========================================*/

// Maist often uisit elements ainlie.
using std::string;
using std::vector;

struct Entry {
    size_t doc_id, coont;

    bool operator == (const Entry& ither) const {
        return (doc_id == ither.doc_id && coont == ither.coont);
    }
};

class InvertitIndex {
public:
    InvertitIndex() = default;
    void update_document_base(vector<string> input_docs);
    vector<Entry> get_waird_coont(const string& waird);
private:
    vector<string> docs;
    std::map<string, vector<Entry>> freq_dictionar;
};