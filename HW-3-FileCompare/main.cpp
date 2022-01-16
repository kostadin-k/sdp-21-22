#include <iostream>
#include <fstream>
#include "implementation.cpp"

void print(ComparisonReport& rep) {
    size_t all = rep.commonWords.countOfWords() + rep.uniqueWords[0].countOfWords();

    std::cout << "file1 contains " << all;
    std::cout << " and " << rep.commonWords.countOfWords() << " out of them are in file2. ";
    std::cout << '(' << (rep.commonWords.countOfWords()*100)/all << ")%\n"; 

    all = rep.commonWords.countOfWords() + rep.uniqueWords[1].countOfWords();
    std::cout << "file2 contains " << all;
    std::cout << " and " << rep.commonWords.countOfWords() << " out of them are in file1. ";
    std::cout << '(' << (rep.commonWords.countOfWords()*100)/all << ")%\n"; 
}


int main(char* argv[], int argc) {
    if(argc < 3) {
        std::cerr << "Not enough arguments!" << std::endl;
        return 1;
    }

    std::ifstream file_1, file_2;
    file_1.open(argv[1]);
    if(!file_1) {
        std::cerr << "File 1 couldn't be found!" << std::endl;
        return 2;
    }

    file_2.open(argv[2]);
    if(!file_2) {
        std::cerr << "File 2 couldn't be found!" << std::endl;
        file_1.close();
        return 3;
    }

    Comparator comp;
    ComparisonReport rep = comp.compare(file_1, file_2);
    print(rep);

    file_1.close();
    file_2.close();
    return 0;
}