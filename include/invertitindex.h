#pragma once

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <thread>
#include <mutex>

#include "converterjson.h"

/*==========================================
== File: InvertitIndex.h                  ==
== Created by RoliMoon.                   ==
== Date: 15/08/2025                       ==
== This class responsible for indexing.   ==
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
    InvertedIndex() = default;
    void update_document_base(vector<string> input_docs);
    vector<Entry> get_word_count(const string& word);
private:
    vector<string> docs;
    std::map<string, vector<Entry>> freq_dictionary;
    std::mutex dictionar_mutex;
};
