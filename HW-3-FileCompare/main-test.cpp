#include <iostream>
#include <fstream>
#include <vector>
#include <string>
//#include "Hash/Hash.hpp"
#include "interface.h"
#include <sstream>
using namespace std;

std::vector<std::string> readStream(std::istream& istr) {
    std::vector<std::string> words;
    char sym = 0;
    std::string buffer = "";

    while(istr.get(sym)) {
        if(isspace(sym)) {
            if(!buffer.empty()) {
                words.push_back(buffer);
                buffer = "";
            }
            continue;
        }
        buffer += sym;
    }
    if(!buffer.empty()) words.push_back(buffer);
    return words;
}

int main() {
    /*Comparator c;
    std::stringstream a("one");
    std::stringstream b;
    ComparisonReport rep = c.compare(a, b);
    rep.commonWords.print();
    rep.uniqueWords[0].print();
    rep.uniqueWords[1].print();*/
    
    /*size_t test;
    test = std::hash<std::string>{}("test");
    cout << test*/;
    std::stringstream a("one");
    std::stringstream b;
    WordsMultiset test;
    std::vector<std::string> words = readStream(a);
    for(size_t i = 0; i < words.size(); i++) {
        test.add(words[i]);
    }
    test.print();

    WordsMultiset test2;
    std::vector<std::string> words2 = readStream(b);
    for(size_t i = 0; i < words2.size(); i++) {
        test2.add(words2[i]);
    }
    test2.print();
    return 0;
}