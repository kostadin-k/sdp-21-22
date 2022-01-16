#ifndef HASH_H
#define HASH_H
#pragma once
#include <string>
#include <set>
#include <iostream>

const size_t HASH_TABLE_SIZE = 10000;

inline size_t hashFun(std::string data) {
	return std::hash<std::string>{}(data) % HASH_TABLE_SIZE;
}

class HashNode {
	std::string data;
	size_t count;
	HashNode* next;
public:
	HashNode(const std::string& data, size_t count)
		:data(data), count(count), next(nullptr) {}
	
	std::string getData() const {return data;}
	size_t getCount() const {return count;}
	HashNode* getNext() const {return next;}
	
	void setCount(size_t new_count) {count = new_count;}
	void setNext(HashNode* new_next) {next = new_next;}
};


class HashTable {
	HashNode** table;
	size_t size = HASH_TABLE_SIZE;
	
	HashNode* find(HashNode* begin, const std::string& data) const;
public:
	HashTable();
	void add(const std::string& data, unsigned int count);
	void remove(const std::string& data, unsigned int count = 0);
	bool check(const std::string& data) const;
	size_t checkWordCount(const std::string& data) const;
	size_t count() const;
	size_t countUnique() const;
	std::multiset<std::string> asMulitset() const;
	~HashTable();
	void print();
};
#endif