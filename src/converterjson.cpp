#include <fstream>
#include <iomanip>
//#include <string>
//#include <sstream>

#include "converterjson.h"

/*==========================================
== File: ConverterJSON.cpp                ==
== Creatit bi RoliMoon.                   ==
== Date: 15/08/2025                       ==
== This class responsible for json files. ==
==========================================*/

// Most often used elements only.
using std::cout;
using std::endl;
using std::cerr;
using std::ifstream;

// A dinnae ken for whit it's daein, bit a can suppose, it's need for a licht an fest switches o variables in a code...

// Get documents
const string CONFIG_CLASS = "config";
const string CONFIG_KEY_NAME = "name";
const string CONFIG_KEY_VERSION = "version";
const string CONFIG_KEY_RESPONSES = "max responses";
const string CONFIG_KEY_FILES = "files";

// Get requests
const string REQUESTS_KEY = "requests";

// Put answers
const string ANSWERS_KEY_RESULT = "result";

ConverterJson::ConverterJson() {}

vector<string> ConverterJson::get_text_documents() {
    vector<string> contents;
    try {
        ifstream read_json_here(cpath);
      // Try to open config.json, and if it cannot opened successfully - return empty array instead of that.
        if (!read_json_here.is_open()) {
            cerr << "Cannae open config.json.\n";
            return {};
        } else {
            nlohmann::json config_dictionary;
            read_json_here >> config_dictionary;
          // Check for all necessary fields.
            if (config_dictionary.find(CONFIG_CLASS) == config_dictionary.end()) {
                throw std::runtime_error("Missing ''config'' object in ''config.json''.\n");
            }
            const auto& config = config_dictionary["config"];

            if (!(config.find(CONFIG_KEY_NAME) != config.end() &&
                config[CONFIG_KEY_NAME].is_string() &&
                config.find(CONFIG_KEY_VERSION) != config.end() &&
                config[CONFIG_KEY_VERSION].is_string() &&
                config.find(CONFIG_KEY_RESPONSES) != config.end() &&
                config[CONFIG_KEY_RESPONSES].is_number())) {
                throw std::runtime_error("Missing necessary fields in ''config.json''.\n");
            }
            if (config_dictionary.find(CONFIG_KEY_FILES) == config_dictionary.end() ||
                !config_dictionary[CONFIG_KEY_FILES].is_array()) {
                throw std::runtime_error("Missing or invalid ''files'' array.\n");
            }

          // Fillin o the configuration structure.
            cfg.name = config[CONFIG_KEY_NAME];
            cfg.version = config[CONFIG_KEY_VERSION];
            cfg.max_responses = config[CONFIG_KEY_RESPONSES];
            for (const auto& file : config_dictionary[CONFIG_KEY_FILES]) {
                if (file.is_string()) {
                    cfg.files.push_back(file.get<string>());
                } else {
                    cerr << "Invalid file entry in ''config''!\n";
                }
            }
        
        for (const string& file_path : cfg.files) {
            ifstream file_stream(file_path);
            if (file_stream.is_open()) {
                std::stringstream string_buffer;
                string_buffer << file_stream.rdbuf();
                contents.push_back(string_buffer.str());
                file_stream.close();
            } else {
                cerr << "Warning! Could nae open a document file " << file_path << endl;
                contents.push_back("");
            }
        }

          // Ootput.
            cout << cfg.name << " version: " << cfg.version << endl;
            cout << "Welcome, dear user!\n";
            cout << "Limit o responses per one request: " << cfg.max_responses << endl;
            cout << "Foond files: " << cfg.files.size() << endl;
            read_json_here.close();
        }
  // Processin o file gettin exceptions.
    } catch (nlohmann::json::exception& jex) {
        cerr << "JSON exception: " << jex.what();
    } catch (std::exception& cex) {
        cerr << "Common exception:" << cex.what();
    }
  // Returnin file contents.
    return contents;
}

int ConverterJson::get_responses_limit() {
    return cfg.max_responses;
}

vector<string> ConverterJson::get_requests() {
    try {
        ifstream read_json_here(rpath);
      // Try tae open requests.json, an if it cannot opened successfully - return empty array instead of that.
        if (!read_json_here.is_open()) {
            cerr << "Cannae open requests.json.\n";
            return {};
        } else {
            nlohmann::json requests_reg;
            read_json_here >> requests_reg;
            if (!(requests_reg.find(REQUESTS_KEY) != requests_reg.end() &&
                requests_reg[REQUESTS_KEY].is_array())) {
            throw std::runtime_error("Missing necessary fields in requests.json\n");
            }
          // Fillin a requests array.
            for (const auto& request : requests_reg[REQUESTS_KEY]) {
                if (request.is_string()) {
                    requests.push_back(request.get<string>());
                } else {
                    cerr << "Incorrect structure of requests!\n";
                }
            }
            read_json_here.close();
        }
  // Processin o gettin requests exceptions.
    } catch (nlohmann::json::exception& jex) {
        cerr << "JSON exception: " << jex.what();
    } catch (std::exception& cex) {
            cerr << "Common exception:" << cex.what();
    }
  // Returnin requests array.
    return requests;
}

void ConverterJson::put_answers(vector<vector<std::pair<int, float>>> answers) {
    try {
        if (answers.empty()) {
            cerr << "Haven't answers to write.\n";
            return;
        }

        std::ofstream write_data_there(apath, std::ios::trunc);
        nlohmann::json answers_data;

        if (!write_data_there.is_open()) {
            cerr << "Cannae open answers.json.\n";
            return;
        }

        for (size_t request_id = 0; request_id < answers.size(); request_id++) {
            std::stringstream id_stream;
            id_stream << "request" << std::setw(3) << std::setfill('0') << (request_id + 1);
            auto& request_data = answers_data["answers"][id_stream.str()];

            if (answers[request_id].empty()) {
                request_data[ANSWERS_KEY_RESULT] = false;
                continue;
            }

            request_data[ANSWERS_KEY_RESULT] = true;

            nlohmann::json relevance_array = nlohmann::json::array();

            for (const auto& result : answers[request_id]) {
                nlohmann::json relevance_item;
                relevance_item["docid"] = result.first;
                relevance_item["rank"] = result.second;
                relevance_array.push_back(relevance_item);
            }
            request_data["relevance"] = relevance_array;
        }
        write_data_there << std::setw(4) << answers_data << endl;
        cout << "Answers successfully writed in file.\n";
  // Processin o answers scrivin exceptions.
    } catch (nlohmann::json::exception& jex) {
        cerr << "JSON exception: " << jex.what();
    } catch (std::exception& cex) {
        cerr << "Common exception:" << cex.what();
    }
}
