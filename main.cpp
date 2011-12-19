#include "main.h"

struct fieldPattern{
    unsigned int number;
    FuzzyLib* matcher;
};

int main (int argc, char** argv) { 
    if (argc == 1) return 0;
    CSVParser parser;
    unsigned int numberOfPatterns;
    vector<fieldPattern> patterns;
    unsigned int paramPos = 1;
    if (string(argv[1]) == string("-f")){
        ifstream input(argv[2] , ifstream::in);
        paramPos = 3;
        if (string(argv[paramPos]) == string("-t")){
            parser.TokenizeText(input);
            ++paramPos;
        }else{
            parser.ParseCSV(input);
        }
    }else{
        if (string(argv[paramPos]) == string("-t")){
            parser.TokenizeText(cin);
            ++paramPos;
        }else{
            parser.ParseCSV(cin);
        }
    }
    
    numberOfPatterns = atoi(argv[paramPos]);


    void *lib_handle;
    lib_handle = dlopen("./levenshtein_automata.so", RTLD_NOW);
    LevenshteinAutomata* (*Create)();
    Create = (LevenshteinAutomata*(*)()) dlsym(lib_handle, "Create");

    for (unsigned int i = paramPos + 1; i <= paramPos + numberOfPatterns * 3; i += 3){
        fieldPattern pt;
        pt.number =  atoi(argv[i]);
        string pattern = string(argv[i+1]);
        unsigned int distance = atoi(argv[i+2]);
        LevenshteinAutomata* alg = Create();
        pt.matcher = new FuzzyLib(alg);
        pt.matcher->SetPattern(pattern,distance);
        patterns.push_back(pt);
    }

    while (! parser.AtEnd()){
        vector<string> line = parser.GetNextLine();
        bool matched = true;
        for (unsigned int i = 0; i < patterns.size(); ++i){
            unsigned int fieldNum = patterns[i].number;
            if (! patterns[i].matcher->Match(line[fieldNum]))
                matched = false;
        }
        if (matched){
            for (unsigned int j = 0; j < line.size() - 1; ++j){
                cout<< line[j] << ",";
            }
            cout<< line[line.size() - 1] << endl;
        }
    }

    return 0;
}
