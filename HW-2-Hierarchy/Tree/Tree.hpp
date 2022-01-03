#ifndef TREE_H
#define TREE_H
#pragma once
#include <vector>
#include <string>
#include <exception>
#include <iostream>
#include <queue>
using std::string;
using std::vector;

const string BOSS_NAME = "Uspeshnia";

class node_t {
	string data = "";
	node_t* parent = nullptr;
	vector<node_t*> children;

	void clear();

	void moveEndChild(size_t index);
	void pushSorted(node_t* child);

	size_t findChildIndex(const string& data);
public:
	node_t() = default;
	~node_t();
	node_t(const string& data);
	node_t(const node_t& other);

	string getData() const;
	node_t* getChild(size_t num) const;
	size_t childCount() const;
	node_t* getParent() const;

	bool addChild(const string& data);
	bool removeChild(const string& data);
	void addChild(node_t* child);
};

class Tree {
	node_t* root = nullptr;
	int size = 0;

	void clear();
	void copy(const Tree& other);
	//void updateDepth();

	vector<vector<string>> splitString(const string& str);

	node_t* findNode(node_t* node, const string& node_data) const;
	void stringifyDFS(node_t* node, string& buffer);

	bool addChild(node_t* parent, const string& data);
	bool removeChild(node_t* parent, node_t* &to_remove);

	void getDepth(node_t* node, int level , int& max_level) const;
	void getNumDecendants(node_t* node, int& count) const;
	void getOverloaded(node_t* node, int limit, int& count) const;
public:
	//Tree() = default;
	~Tree();
	Tree(node_t* node);
	Tree(const string& root_data);
	Tree(const Tree& other);

	Tree& operator=(const Tree& other);

	node_t* findNode(const string& node) const;

	string stringifyDFS();
	string stringifyBFS();

	int getSize() const;
	int getDepth() const;
	int getNumDecendants(node_t* node) const;
	unsigned long getSalary(const string& node) const;
	int getOverloaded(int limit) const; 

	bool addNode(const string& node, const string& parent);
	bool removeNode(const string& node);

	Tree merge(const Tree& other);
	void incorporate();
    void modernize();
};
#endif