#include "Hash.hpp"  

HashNode* HashTable::find(HashNode* begin, const std::string& data) const {
    HashNode* it = begin;
    while (it) {
        if(data == it->getData()) return it;
        it = it->getNext();
    }
    return nullptr;
}

HashTable::HashTable() {
    table = new HashNode*[size];
    for(size_t i = 0; i < size; i++) {
        table[i] = nullptr;
    }
}

void HashTable::add(const std::string& data, unsigned int count) {
    size_t hash_data = hashFun(data);
    HashNode* it = table[hash_data];
    HashNode* buff = nullptr;

    while(it) {
        if(data == it->getData()) {
            it->setNext(it->getNext() + count);
            return;
        }
        buff = it;
        it = it->getNext();
    }

    HashNode* new_node = new HashNode(data,count);

    if(!buff) {
        table[hash_data] = new_node;
    } else {
        buff->setNext(new_node);
    }

}

void HashTable::remove(const std::string& data, unsigned int count) {
    size_t hash_data = hashFun(data);
    HashNode* it = table[hash_data];
    HashNode* buff = nullptr;

    while(it) {
        if(data == it->getData()) {
            if(count && count < it->getCount()) {
                it->setCount(it->getCount() - count);
            } else {
                if(!buff) {
                    table[hash_data] = it->getNext();
                } else {
                    buff->setNext(it->getNext());
                }
                delete it;
            }
            return;
        }
    }
    
}

bool HashTable::check(const std::string& data) const {
    size_t hash_data = hashFun(data);
    return find(table[hash_data], data);
}

size_t HashTable::checkWordCount(const std::string& data) const {
    size_t hash_data = hashFun(data);
    HashNode* node = find(table[hash_data], data);
    if(!node) return 0;
    return node->getCount();
}

size_t HashTable::count() const {
    size_t count = 0;
    for(size_t i = 0; i < size; i++) {
        HashNode* it = table[i];
        while (it) {
            count += it->getCount();
            it = it->getNext();
        }
    }
    return count;
}

size_t HashTable::countUnique() const {
    size_t count = 0;
    for(size_t i = 0; i < size; i++) {
        HashNode* it = table[i];
        while (it) {
            count++;
            it = it->getNext();
        }
    }
    return count;
}

std::multiset<std::string> HashTable::asMulitset() const {
    std::multiset<std::string> mul;
    for(size_t i = 0; i < size; i++) {
        HashNode* it = table[i];
        while (it) {
            while (it->getCount()){
                mul.insert(it->getData());
            }
            it = it->getNext();
        }
    }
    return mul;
}

HashTable::~HashTable() {
    for(size_t i = 0; i < size; i++) {
        HashNode* it = table[i];
        while (it) {
            HashNode* to_delete = it;
            it = it->getNext();
            delete to_delete;
        }
        
    }
	delete[] table;
}

void HashTable::print() {
    HashNode* it = nullptr;
    for(size_t i = 0; i < size; i++) {
        it = table[i];
        if(!it) continue;
        std:: cout << i << "/";
        while (it) {
            std::cout << it->getData() << ":" << it->getCount()<< "; ";
            it = it->getNext();
        }
        std::cout << std::endl;
    }
}