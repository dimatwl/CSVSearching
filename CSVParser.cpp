#include "CSVParser.h"

CSVParser::CSVParser(){}

bool CSVParser::ParseCSV(istream& inpStr){
    int result(0);

    bool inQuote(false);
    bool newLine(false);
    string field;
    this->lines.clear();
    vector<string> line;
    string csv = "";
    string cell;
    while(std::getline(inpStr,cell)){
        csv += cell + "\n";
    }
    string::const_iterator aChar = csv.begin();
    while (aChar != csv.end()){
        switch (*aChar){
            case '"':
                newLine = false;
                inQuote = !inQuote;
                field += *aChar;
            break;

            case ',':
                newLine = false;
                if (inQuote == true)
                    field += *aChar;
                else{
                    line.push_back(field);
                    field.clear();
                }
            break;

            case '\n':
            case '\r':
                if (inQuote == true)
                    field += *aChar;
                else{
                    if (newLine == false){
                        line.push_back(field);
                        this->lines.push_back(line);
                        field.clear();
                        line.clear();
                        newLine = true;
                    }
                }
            break;

            default:
                newLine = false;
                field.push_back(*aChar);
                break;
        }
        aChar++;
    }

    if (line.size()){
        if (field.size())
        line.push_back(field);

        lines.push_back(line);
    }

    return result;
}

bool CSVParser::TokenizeText(istream& inpStr){
    int result(0);

    string field;
    this->lines.clear();
    vector<string> line;
    string csv = "";
    string cell;
    while(std::getline(inpStr,cell)){
        csv += cell + "\n";
    }
    string::const_iterator aChar = csv.begin();
    while (aChar != csv.end()){
        if (isspace(*aChar) || ispunct(*aChar)){
            if (field.size() > 0){
                line.push_back(field);
                this->lines.push_back(line);
                field.clear();
                line.clear();
            }
        } else{
            field.push_back(*aChar);
        }
        aChar++;
    }
}

vector<string> CSVParser::GetNextLine(){
    vector<string> tmp = this->lines.back();
    this->lines.pop_back();
    return tmp;
}

bool CSVParser::AtEnd(){
    return this->lines.empty();
}