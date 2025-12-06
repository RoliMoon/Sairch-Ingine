#include <sstream>
#include <algorithm>
#include <iomanip>
#include <map>
#include <cctype>
#include <iterator>

#include "invertitindex.h"

/*==========================================
== File: InvertitIndex.cpp                ==
== Creatit bi RoliMoon.                   ==
== Date: 15/08/2025                       ==
== This class responsible for indexing.   ==
==========================================*/

// Most often used elements only.
using std::transform;
using std::thread;
using std::map;
using std::cout;
using std::endl;

void InvertedIndex::update_document_base(vector<string> input_docs) {
    /*if (!input_docs.empty()) {
        //input_docs.clear();
        freq_dictionary.clear();
        docs.reserve(input_docs.size());
    }*/
    freq_dictionary.clear();

    vector<thread> thread_pool;
    size_t num_threads = thread::hardware_concurrency();
    if (num_threads == 0) num_threads = 1;

  // Vector o frequency dictionars for single documents.
    vector<map<string, vector<Entry>>> all_perdoc_freq_dictionaries(num_threads); 
    size_t docs_per_thread = input_docs.size() / num_threads;

    auto process_range = [&](size_t thread_id, size_t doc_id_begin, size_t doc_id_final) {
        map<string, vector<Entry>> perdoc_freq_dictionary;

        for (size_t doc_id = doc_id_begin; doc_id < doc_id_final;  doc_id++) {
          // Separating documents until single words.
            std::istringstream words_stream(input_docs[doc_id]);
            string word;

            while (words_stream >> word) {
              // Changing register from large to wee letters - ("WaiRd" -> "waird").
                transform(word.begin(), word.end(), word.begin(), tolower);
                word.erase(std::remove_if(word.begin(), word.end(), ispunct), word.end());
                if (!word.empty()) {
                    auto& entries = perdoc_freq_dictionary[word];
                    if (!entries.empty() && entries.back().doc_id == doc_id) {
                        entries.back().count++;
                    } else {
                        entries.push_back({doc_id, 1});
                    }
                }
            }
        }
        all_perdoc_freq_dictionaries[thread_id] = std::move(perdoc_freq_dictionary);
      // *** LOGGIN O INFORMATION FOR DEBUG. ***
        //std::cout << "DEBUG: Indexit wairds coont: " << all_perdoc_freq_dictionaries[thread_id].size() << std::endl;
    };
    
  // Launchin threads
    for (size_t i = 0; i < num_threads; i++) {
        size_t begin = i * docs_per_thread;
        size_t final = (i == num_threads - 1) ? input_docs.size() : ((i + 1) * docs_per_thread);
        if (begin < final) {
            thread_pool.emplace_back(process_range, i, begin, final);
        }
    }

  // Closing threads
    for (auto& thread : thread_pool) {
        if (thread.joinable()) {
            thread.join();
        }
    }

  // Connecting threads
    std::lock_guard<std::mutex> lock(dictionar_mutex);
    for (const auto& local_dictionary : all_perdoc_freq_dictionaries) {
        for (const auto& dict_pair : local_dictionary) {
            const string& word = dict_pair.first;
            const vector<Entry>& entries = dict_pair.second;
            freq_dictionary[word].insert(freq_dictionary[word].end(), entries.begin(), entries.end());
        }
    }

  // *** LOGGING O INFORMATION FOR DEBUG. ***
  // A desidit add a logging tae find a problem.
    /*
    cout << "Debug index final frequency dictionar wairds: ";
    for (const auto pair : freq_dictionary) {
        cout << pair.first << "(" << pair.second.size() << " entries) ";
    }
    cout << std::endl;*/

  // *** END O OOTPUTTIN O DEBUG INFORMATION BLOCK. ***

    docs = std::move(input_docs);
    //docs = input_docs;
}

vector<Entry> InvertedIndex::get_word_count(const string& word) {
    string low_reg_word = word;
    std::transform(low_reg_word.begin(), low_reg_word.end(), low_reg_word.begin(), tolower);
    
    std::lock_guard<std::mutex> lock(dictionar_mutex);
    auto it = freq_dictionary.find(low_reg_word);
    if (it != freq_dictionary.end()) {
        return it->second;
    }
    return {};
}


