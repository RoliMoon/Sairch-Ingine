#pragma once

#include <string>
#include <vector>
#include <set>

#include "invertitindex.h"
#include "converterjson.h"

/*==========================================
== File: SairchServer.h                   ==
== Created by RoliMoon.                   ==
== Date: 15/08/2025                       ==
== This class responsible for search      ==
== processing.                            ==
==========================================*/

// Most often used elements only.
using std::string;
using std::vector;
using std::set;

struct RelativeIndex {
    size_t doc_id;
    float rank;
    bool operator == (const RelativeIndex& other) const {
        return (doc_id == other.doc_id && rank == other.rank);
    }
};

class SearchServer {
public:
    SearchServer(InvertedIndex& idx) : iiclass(idx){ };
    vector<vector<RelativeIndex>> search(const vector<string>& queries_input);
    set<string> parse_query(const string& query);
    float calculate_rank(size_t doc_id, const set<string>& words);
private:
    //RelativeIndex relative_index;
    InvertedIndex iiclass;

};
