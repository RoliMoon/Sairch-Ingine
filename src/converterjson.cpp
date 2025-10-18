#include <fstream>
#include <iomanip>

#include "converterjson.h"

/*==========================================
== File: ConverterJSON.cpp                ==
== Creatit bi RoliMoon.                   ==
== Date: 15/08/2025                       ==
== This cless responsible for json files. ==
==========================================*/

// Maist often uisit elements ainlie.
using std::cout;
using std::endl;
using std::cerr;
using std::ifstream;

// Paths initialisin.
ConverterJson::ConverterJson() {}

vector<string> ConverterJson::get_text_documents() {
    try {
    ifstream read_json_here(cpath);
  // Try tae open config.json, an if it cannae openit successfully - return empty array in place o that.
    if (!read_json_here.is_open()) {
        cerr << "Cannae open config.json.\n";
        return {};
    }
        nlohmann::json config_dictionar;
        read_json_here >> config_dictionar;
      // Check for aa necessary fields.
        if (config_dictionar.find("config") == config_dictionar.end()) {
            throw std::runtime_error("Missin ''config'' object in ''config.json''.\n");
        }
        const auto& config = config_dictionar["config"];

        if (!(config.find("name") != config.end() &&
            config["name"].is_string() &&
            config.find("version") != config.end() &&
            config["version"].is_string() &&
            config.find("max_responses") != config.end() &&
            config["max_responses"].is_number())) {
            throw std::runtime_error("Missin necessary fields in ''config.json''.\n");
        }
        if (config_dictionar.find("files") == config_dictionar.end() ||
            !config_dictionar["files"].is_array()) {
            throw std::runtime_error("Missin or invalid ''files'' array.\n");
        }
      // Fill the configuration structur.
        cfg.name = config["name"];
        cfg.version = config["version"];
        cfg.max_responses = config["max_responses"];
        for (const auto& file : config_dictionar["files"]) {
            if (file.is_string()) {
                cfg.files.push_back(file.get<string>());
            } else {
                cerr << "Invalid file entry in ''config''!\n";
            }
        }
    
      // Ootput.
        cout << cfg.name << " version: " << cfg.version << endl;
        cout << "Walcome, dear uiser!\n";
        cout << "Limit o responses per ain request: " << cfg.max_responses << endl;
        cout << "Foond files: " << cfg.files.size() << endl;
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
  // Try tae open requests.json, an if it cannae openit successfully - return empty array in place o that.
    if (!read_json_here.is_open()) {
        cerr << "Cannae open requests.json.\n";
        return {};
    }
        nlohmann::json requests_reg;
        read_json_here >> requests_reg;
        if (!(requests_reg.find("requests") != requests_reg.end() &&
            requests_reg["requests"].is_array())) {
        throw std::runtime_error("Missin necessary fields in requests.json\n");
        }
      // Fill a requests array.
        for (const auto& request : requests_reg["requests"]) {
            if (request.is_string()) {
                requests.push_back(request.get<string>());
            } else {
                cerr << "Incorrect structur o requests!\n";
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
            cerr << "Hanae answers tae scrive.\n";
            return;
        }

        std::ofstream scrive_data_thare(apath, std::ios::trunc);
        nlohmann::json answers_data;

        if (!scrive_data_thare.is_open()) {
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
        scrive_data_thare << std::setw(4) << answers_data << endl;
        cout << "Answers successfully scrivin tae file.\n";

    } catch (nlohmann::json::exception& jex) {
        cerr << "JSON exception: " << jex.what();
    } catch (std::exception& cex) {
        cerr << "Common exception:" << cex.what();
    }
}