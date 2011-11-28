#ifndef __CSVPARSER_H__
#define __CSVPARSER_H__

#include <string>
#include <vector>
#include <istream>
#include <iostream>

using std::string;
using std::vector;
using std::istream;
using std::cin;
using std::string;

class CSVParser{
    vector<vector<string> > lines;

public:
    CSVParser();
    bool ParseCSV(istream& inpStr);
    vector<string> GetNextLine();
    bool AtEnd();
    

};

#endif /* __CSVPARSER_H__ */