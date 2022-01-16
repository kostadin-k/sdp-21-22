#include "interface.h"
#include <vector>
#include <fstream>

void WordsMultiset::add(const std::string& word, size_t times) {
    table.add(word, times);
}

bool WordsMultiset::contains(const std::string& word) const {
    return table.check(word);
}

size_t WordsMultiset::countOf(const std::string& word) const {
    return table.checkWordCount(word);
}

size_t WordsMultiset::countOfUniqueWords() const {
    return table.countUnique();
}

std::multiset<std::string> WordsMultiset::words() const {
    return table.asMulitset();
}

void WordsMultiset::remove(const std::string& data, size_t times) {
    table.remove(data, times);
}

size_t WordsMultiset::countOfWords() const {
    return table.count();
}

void WordsMultiset::print() {
    table.print();
}

ComparisonReport Comparator::compare(std::istream& a, std::istream& b) {
    ComparisonReport repo;
    char sym = 0;
    std::string buffer = "";

    while(a.get(sym)) {
        if(isspace(sym)) {
            if(!buffer.empty()) {
                repo.uniqueWords[0].add(buffer);
                buffer = "";
                std::cout << "Common: ";
                repo.commonWords.print();
                std::cout << "Unique 1: ";
                repo.uniqueWords[0].print();
                std::cout << "Unique 2: ";
                repo.uniqueWords[1].print();
                std::cout << '\n';
            }
            continue;
        }
        buffer += sym;
    
    }

    if(!buffer.empty())repo.uniqueWords[0].add(buffer);
    buffer = "";

    while(b.get(sym)) {
        if(isspace(sym)) {
            if(!buffer.empty()) {
                if(repo.uniqueWords[0].contains(buffer)) {
                    repo.uniqueWords[0].remove(buffer,1);
                    repo.commonWords.add(buffer);
                } else {
                    repo.uniqueWords[1].add(buffer);
                }
                std::cout << "Common: ";
                repo.commonWords.print();
                std::cout << "Unique 1: ";
                repo.uniqueWords[0].print();
                std::cout << "Unique 2: ";
                repo.uniqueWords[1].print();
                std::cout << '\n';
                buffer = "";
            }
            continue;
        }
        buffer += sym;
    
    }

    if (!buffer.empty())
        if (repo.uniqueWords[0].contains(buffer)) {
            repo.uniqueWords[0].remove(buffer, 1);
            repo.commonWords.add(buffer);
        }
        else {
            repo.uniqueWords[1].add(buffer);
        }

    return repo;

}