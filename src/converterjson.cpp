#include <fstream>
#include <iomanip>

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

vector<string> ConverterJson::get_text_documents() {
    try {
    ifstream read_json_here(cpath);
  // Try to open config.json, and if it cannot opened successfully - return empty array instead of that.
    if (!read_json_here.is_open()) {
        cerr << "Cannae open config.json.\n";
        return {};
    }
        nlohmann::json config_dictionary;
        read_json_here >> config_dictionary;
      // Check for all necessary fields.
        if (config_dictionary.find("config") == config_dictionary.end()) {
            throw std::runtime_error("Missing ''config'' object in ''config.json''.\n");
        }
        const auto& config = config_dictionary["config"];

        if (!(config.find("name") != config.end() &&
            config["name"].is_string() &&
            config.find("version") != config.end() &&
            config["version"].is_string() &&
            config.find("max_responses") != config.end() &&
            config["max_responses"].is_number())) {
            throw std::runtime_error("Missing necessary fields in ''config.json''.\n");
        }
        if (config_dictionary.find("files") == config_dictionary.end() ||
            !config_dictionary["files"].is_array()) {
            throw std::runtime_error("Missing or invalid ''files'' array.\n");
        }
      // Fill the configuration structure.
        cfg.name = config["name"];
        cfg.version = config["version"];
        cfg.max_responses = config["max_responses"];
        for (const auto& file : config_dictionary["files"]) {
            if (file.is_string()) {
                cfg.files.push_back(file.get<string>());
            } else {
                cerr << "Invalid file entry in ''config''!\n";
            }
        }
    
      // Ootput.
        cout << cfg.name << " version: " << cfg.version << endl;
        cout << "Welcome, dear user!\n";
        cout << "Limit o responses per one request: " << cfg.max_responses << endl;
        cout << "Found files: " << cfg.files.size() << endl;
        read_json_here.close();

    } catch (nlohmann::json::exception& jex) {
        cerr << "JSON exception: " << jex.what();
    } catch (std::exception& cex) {
        cerr << "Common exception:" << cex.what();
    }
  // Return files array.
    
    return cfg.files;
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
    }
        nlohmann::json requests_reg;
        read_json_here >> requests_reg;
        if (!(requests_reg.find("requests") != requests_reg.end() &&
            requests_reg["requests"].is_array())) {
        throw std::runtime_error("Missing necessary fields in requests.json\n");
        }
      // Fill a requests array.
        for (const auto& request : requests_reg["requests"]) {
            if (request.is_string()) {
                requests.push_back(request.get<string>());
            } else {
                cerr << "Incorrect structure of requests!\n";
            }
        }

        read_json_here.close();
        
    } catch (nlohmann::json::exception& jex) {
        cerr << "JSON exception: " << jex.what();
    } catch (std::exception& cex) {
        cerr << "Common exception:" << cex.what();
    }
  // Return requests array.
    
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
                request_data["result"] = false;
                continue;
            }

            request_data["result"] = true;

            if (answers[request_id].size() == 1) {
                const auto& result = answers[request_id][0];
                request_data;
            }
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

    } catch (nlohmann::json::exception& jex) {
        cerr << "JSON exception: " << jex.what();
    } catch (std::exception& cex) {
        cerr << "Common exception:" << cex.what();
    }
}
