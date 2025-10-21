#include <sstream>
#include <set>
#include <algorithm>

#include "sairchserver.h"

/*==========================================
== File: SairchServer.cpp                 ==
== Creatit bi RoliMoon.                   ==
== Date: 15/08/2025                       ==
== This class responsible for sairch      ==
== processing.                             ==
==========================================*/

// Most often used elements only.
using std::transform;
using std::set;

vector<vector<RelativeIndex>> SairchServer::search(const vector<string>& queries_input) {
    vector<vector<RelativeIndex>> results;

	for (const auto& query : queries_input) {
        vector<RelativeIndex> query_results;
        set<string> words = parse_query(query);

        for (const auto& word : words) {
            auto word_entries = iiclass.get_word_count(word);

            for (const auto& entry : word_entries) {
                float rank = calculate_rank(entry.doc_id, words);
                query_results.emplace_back(RelativeIndex{entry.doc_id, rank});
            }
			std::sort(query_results.begin(), query_results.end(), [](const RelativeIndex& left_side, const RelativeIndex& richt_side) {
				return left_side.rank < richt_side.rank;
				});
        }
        results.push_back(query_results);
    }
    return results;
}

set<string> SairchServer::parse_query(const string& query) {
    set<string> words;
    string word;
    std::istringstream word_stream(query);

    while (word_stream >> word) {
        transform(word.begin(), word.end(), word.begin(), tolower);
        word.erase(std::remove_if(word.begin(), word.end(), ispunct), word.end());
        if (!word.empty()) {
            words.insert(word);
        }
    }
    return words;
}

float SairchServer::calculate_rank(size_t doc_id, const set<string>& words) {
    float base_rank = 1.0f;

    for (const auto& word : words) {
        auto entries = iiclass.get_word_count(word);

        for (const auto& entry : entries) {
            if (entry.doc_id == doc_id) {
                base_rank *= entry.count;
                break;
            }
        }
    }
    base_rank /= words.size();
    return base_rank;

}
