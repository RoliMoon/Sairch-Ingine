#pragma once

#include <string>
#include <vector>
#include <map>

#include "converterjson.h"

/*==========================================
== File: InvertitIndex.h                  ==
== Creatit bi RoliMoon.                   ==
== Date: 15/08/2025                       ==
== This class responsible for indexin.    ==
==========================================*/

// Most often used elements only.
using std::string;
using std::vector;

struct Entry {
    size_t doc_id, count;

    bool operator == (const Entry& other) const {
        return (doc_id == other.doc_id && count == other.count);
    }
};

class InvertedIndex {
public:
    InvertitIndex() = default;
    void update_document_base(vector<string> input_docs);
    vector<Entry> get_word_coont(const string& word);
private:
    vector<string> docs;
    std::map<string, vector<Entry>> freq_dictionary;

};

