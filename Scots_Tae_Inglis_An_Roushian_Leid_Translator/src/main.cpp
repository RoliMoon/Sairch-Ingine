#include <iostream>
#include <string>

#include "dictionarmanagement.h"
#include "translator.h"

using std::string;
using std::cout;
using std::cin;

int main() {
    DictionarManagement dict_man;
    
    //Laid leid dictonars.
    dict_man.laid_dictionar_file("scots", "leids/scots_leid_dictionar.txt");
    dict_man.laid_dictionar_file("inglis", "leids/inglis_leid_dictionar.txt");
    dict_man.laid_dictionar_file("roushian", "leids/roushian_leid_dictionar.txt");

    string input;
    string soorce_leid;
    string target_leid;

    cout << "Walcome, dear uiser!\n Tae uise translator, enter a name o soorce an target leids.\n";
    cout << "Soorce leid. Enter ''scots'', ''inglis'' or ''roushian'' \nfor define soorce leid. >> ";
    cin >> soorce_leid;
    cout << "Target leid. Enter ''scots'', ''inglis'' or ''roushian'' \nfor define target leid. >> ";
    cin >> target_leid;

    cout << "Enter yer wantit waird here: >> ";
    cin >> input;
    string translation = translate_waird(input, soorce_leid, target_leid, dict_man);
    cout << "Yer waird in target leid: >> " << translation << std::endl;

    return 0;
}