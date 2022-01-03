#ifndef HIERARCHYNAMED_H
#define HIERARCHYNAMED_H
#pragma once
#include "../../interface.h"

class HierarchyNamed {
	Hierarchy* heir = nullptr;
	string name = "";
	bool is_saved = 1;
public:
    HierarchyNamed(HierarchyNamed&& r) noexcept;
	HierarchyNamed(const HierarchyNamed& r);
    HierarchyNamed(Hierarchy* r, const string& name = "");
    HierarchyNamed(const string& data, const string& name = "");
    ~HierarchyNamed() noexcept;

    void operator=(const HierarchyNamed&) = delete;

	Hierarchy* getHierarchy();
	string getName() const;
	void setName(const string& name);
	bool isSaved();
};
#endif