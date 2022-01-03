#include "interface.h"

Hierarchy::Hierarchy(Hierarchy&& r) noexcept {
    tree = r.tree;
    node_t* boss = new node_t(BOSS_NAME);
    r.tree = new Tree(boss);
}

Hierarchy::Hierarchy(const Hierarchy& r) {
    tree = new Tree(*r.tree);
}

Hierarchy::Hierarchy(const string& data) {
    tree = new Tree(data);
}

Hierarchy::~Hierarchy() noexcept {
    delete tree;
}

string Hierarchy::print() const {
    return tree->stringifyBFS();
}

int Hierarchy::longest_chain() const {
    return tree->getDepth();
}

bool Hierarchy::find(const string& name) const {
    return tree->findNode(name);
}

int Hierarchy::num_employees() const {
    return tree->getSize();
}

int Hierarchy::num_overloaded(int level) const {
    return tree->getOverloaded(level);
}

string Hierarchy::manager(const string& name) const {
    node_t* employee = tree->findNode(name);
    if (!employee) throw std::invalid_argument(name + " doesn't work here!");
    if (!employee->getParent()) throw std::invalid_argument(name + " is the manager!");
    return employee->getParent()->getData();
}

int Hierarchy::num_subordinates(const string& name) const {
    node_t* employee = tree->findNode(name);
    if(!employee) throw std::invalid_argument(name + " not found!");
    return employee->childCount(); 
}

unsigned long Hierarchy::getSalary(const string& who) const {
    return tree->getSalary(who);
}

bool Hierarchy::fire(const string& who) {
    return tree->removeNode(who);
}

bool Hierarchy::hire(const string& who, const string& boss) {
    return tree->addNode(who,boss);
}

void Hierarchy::incorporate() {
    tree->incorporate();
}

void Hierarchy::modernize() {
    tree->modernize();
}

Hierarchy Hierarchy::join(const Hierarchy& right) const {
    Hierarchy hier(tree->merge(*(right.tree)));
    return hier;
}

Hierarchy::Hierarchy(const Tree& t) {
    tree = new Tree(t);
}