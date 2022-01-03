#include "HierarchyNamed.hpp"  

//HierarchyNamed

HierarchyNamed::HierarchyNamed(HierarchyNamed&& r) noexcept {
    heir = r.heir;
    name = r.name;
    is_saved = r.is_saved;
    r.heir = nullptr;
    r.name.clear();
    r.is_saved = 1;
}
HierarchyNamed::HierarchyNamed(const HierarchyNamed& r)  {
    heir = new Hierarchy(*r.heir);
    name = r.name;
    is_saved = r.is_saved;
}

HierarchyNamed::HierarchyNamed(Hierarchy* r, const string& name = "") {
    heir = r;
    this->name = name;
}

HierarchyNamed::HierarchyNamed(const string& data, const string& name = "") {
    heir = new Hierarchy(data);
    this->name = name;
}

HierarchyNamed::~HierarchyNamed() {
    delete heir;
}

Hierarchy* HierarchyNamed::getHierarchy() {
    return heir;
}

string HierarchyNamed::getName() const {
    return name;
}

bool HierarchyNamed::isSaved() {
    return is_saved;
}

void HierarchyNamed::setName(const string& name) {
    this->name = name;
}
