#include <sstream>
#include <set>
#include <algorithm>

#include "sairchserver.h"

/*==========================================
== File: SairchServer.cpp                 ==
== Creatit bi RoliMoon.                   ==
== Date: 15/08/2025                       ==
== This class responsible for sairch      ==
== processing.                            ==
==========================================*/

// Most often used elements only.
using std::transform;
using std::set;
using std::cout;

vector<vector<RelativeIndex>> SearchServer::search(const vector<string>& queries_input) {
    vector<vector<RelativeIndex>> results;

	for (const auto& query : queries_input) {
      // Here vi collects aa waird entries for every document.
        std::map<size_t, float> document_total_counts;
        set<string> words = parse_query(query);

      // *** LOGGING O INFORMATION FOR DEBUG. ***
      // A desidit add a logging tae find a problem.
        /*
        cout << "Debug sairch: querie ''" << query << "'' parsit intae wairds: ";
        for (const auto wrd : words) {
            cout << "''" << wrd << "''";
        }
        cout << std::endl;
        */
      // *** END O OOTPUTTIN O DEBUG INFORMATION BLOCK. ***

        for (const auto& word : words) {
            auto word_entries = iiclass.get_word_count(word);

            for (const auto& entry : word_entries) {
              // Summation o waird entries in common coont o document
                document_total_counts[entry.doc_id] += entry.count;
                
                // document_total_counts[entry.doc_id] += calculate_rank(entry.doc_id, words); -> Deletit
            }
        }
        vector<RelativeIndex> query_results;
        float maximal_rank = 0.0f;

        for (const auto& pair : document_total_counts) {
            query_results.emplace_back(RelativeIndex{pair.first, pair.second});
            if (pair.second > maximal_rank) {
                maximal_rank = pair.second;
            }
        }
        
        if (maximal_rank > 0.0f) {
            for (auto& result : query_results) {
				result.rank /= maximal_rank;
			}
        }
      // Sortin o queries bi rank
        std::sort(query_results.begin(), query_results.end(), [](const RelativeIndex& left_side, const RelativeIndex& richt_side) {
			if (abs(left_side.rank - richt_side.rank) > 0.0001f) {
				return left_side.rank > richt_side.rank;
			}
			return left_side.doc_id < richt_side.doc_id;
		});
        results.push_back(query_results);
    }
    return results;
}

set<string> SearchServer::parse_query(const string& query) {
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
