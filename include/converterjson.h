#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "nlohmann/json.hpp"

/*==========================================
== File: ConverterJSON.h                  ==
== Creatit bi RoliMoon.                   ==
== Date: 15/08/2025                       ==
== This cless responsible for json files. ==
==========================================*/

// Maist often uisit elements ainlie.
using std::string;
using std::vector;

struct Configuration {
    string name;
    string version;
    int max_responses;
    vector<string> files;
};

class ConverterJson {
public:
    ConverterJson();
    vector<string> get_text_documents();
    int get_responses_limit();
    vector<string> get_requests();
    void put_answers(vector<vector<std::pair<int, float>>> answers);

private:
    Configuration cfg;
    vector<string> requests;
    const string cpath = "../config/config.json";
    const string rpath = "../config/requests.json";
    const string apath = "../config/answers.json";
};
