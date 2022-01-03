#ifndef HIERMANAGER_H
#define HIERMANAGER_H
#pragma once
#include "../interface.h"
#include "fstream"

class HierarchyExtended : public Hierarchy {
	string name = "";
	bool is_saved = 1;
public:
    HierarchyExtended(HierarchyExtended&& r) noexcept;
    HierarchyExtended(const HierarchyExtended& r);
    HierarchyExtended(const string& data, const string& name);
	HierarchyExtended(const Hierarchy& r, const string& name);
    //~HierarchyExtended() noexcept;
    void operator=(const HierarchyExtended&) = delete;

	string getName() const;
	void setName(const string& name);
	bool isSaved();

	HierarchyExtended join(const HierarchyExtended& r, const string& name);
};

class HierManager {
	vector<HierarchyExtended*> h_list;
	bool isInFile(const string& name, const string& path, size_t& pos);
public:
	HierManager() = default;
	void add(const HierarchyExtended& hier);
	HierarchyExtended* getAtIndex(size_t index);
	size_t getSize();
	HierarchyExtended* findHierarchy(const string& name);
	HierarchyExtended* join(const string& heir_1, const string& heir_2, const string& heir_3);
	void input(const string& name);
	void load(const string& name, const string& path);
	void save(const string& name, const string& path);
	bool areUnsaved();
};

#endif