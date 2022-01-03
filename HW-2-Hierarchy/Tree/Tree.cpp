#include "Tree.hpp"
#include <exception>

//node_t

void node_t::clear() {
    for(size_t i=0; i<children.size(); i++) {
        delete children[i];
    }
}

void node_t::pushSorted(node_t* child) {
    size_t index = 0;

    for(index; index < children.size(); index++) {
        if(child->getData() < children[index]->getData()) break;
    }

    children.insert(children.begin() + index, child);
}

size_t node_t::findChildIndex(const string& data) {
    for(size_t i = 0; i < children.size(); i++) {
        if(children[i]->getData() == data) return i;
    }
    return children.size();
}

void node_t::moveEndChild(size_t index) {
    node_t* buffer = nullptr;
    for(size_t i = index; i < children.size()-1; i++) {
        buffer = children[i];
        children[i] = children[i+1];
        children[i+1] = buffer;
    }
}

node_t::node_t(const string& data) {
    this->data = data;
}

node_t::~node_t() {
    clear();
}

node_t::node_t(const node_t& other) {
    if(this != &other) {
        clear();
        data = other.data;
        parent = other.parent;
        for (size_t i = 0; i < other.childCount(); i++) {
            node_t* node = new node_t(*other.children[i]);
            addChild(node);
        }
    }    
}

// node_t& node_t::operator=(const node_t& other) {
//     copy(other);
//     return *this;
// }

string node_t::getData() const {
    return data;
}

node_t* node_t::getChild(size_t num) const {
    if(num < children.size()) return children[num];
    throw std::range_error("idk");
}

size_t node_t::childCount() const {
    return children.size();
}

node_t* node_t::getParent() const {
    return parent;
}

void node_t::addChild(node_t* child) {
    child->parent = this;
    pushSorted(child);
}

bool node_t::addChild(const string& data) {
    node_t* newChild = new (std::nothrow) node_t(data);
    if(!newChild) return 0;
    addChild(newChild);
    return 1;
}

bool node_t::removeChild(const string& data) {
    size_t index = findChildIndex(data);
    if (index == children.size()) return 0;
    node_t* to_delete = children[index];

    moveEndChild(index);
    children.pop_back();

    if(!to_delete->children.empty()) {
        children.reserve(children.size() + to_delete->children.size());
        for(size_t i = 0; i < to_delete->children.size(); i++) {
            addChild(to_delete->children[i]);
        }    
    }

    to_delete->children.clear();      
    delete to_delete;
    return 1;
}

//Tree

void Tree::clear() {
    if(root) delete root;
}

void Tree::copy(const Tree& other) {
    if(this != &other) {
        /* if(root) */clear();
        root = new node_t(*(other.root));
        size = other.size;
    }
}

vector<vector<string>> Tree::splitString(const string& str) {
    string str_buffer = "";
    vector<string> vec_buffer;
    vector<vector<string>> result;
    for(size_t i = 0; i < str.size(); i++) {
        if(str[i] == ' ') continue;
        
        if(str[i] == '-') {
            vec_buffer.push_back(str_buffer);
            str_buffer.clear();
            continue;
        }

        if(str[i] == '\n') {
            vec_buffer.push_back(str_buffer);
            str_buffer.clear();
            result.push_back(vec_buffer);
            vec_buffer.clear();
            if (i+1 < str.size() && str[i+1] == '\n') i++;
            continue;
        }
        
        str_buffer += str[i];
    }
    return result;
}

Tree::~Tree() {
	clear();
}

Tree::Tree(node_t* node) {
    root = new node_t(*node);
}

Tree::Tree(const string& data) {
    node_t* node = new node_t(BOSS_NAME);
    root = node;
    if(data == "") return;
    vector<vector<string>> entries = splitString(data);
    for(size_t i = 0; i < entries.size(); i++) {
        if(entries[i][0] != node->getData()) {
            node = findNode(entries[i][0]);
            if (!node) {
                string err = "couldn't add node at " + i;
                throw std::runtime_error(err.c_str());
            }
        }
        addChild(node, entries[i][1]);
    }
    // root = new node_t(root_data);
}

Tree::Tree(const Tree& other) {
	copy(other);
}

Tree& Tree::operator=(const Tree& other) {
    copy(other);
    return *this;
}

node_t* Tree::findNode(node_t* node, const string& node_data) const {
    if(node->getData() == node_data) return node;
    node_t* test_node = nullptr;

    for(size_t i=0; i<node->childCount(); i++) {
        test_node = findNode(node->getChild(i), node_data);
        if (test_node) return test_node;
    }
    return test_node;
}

node_t* Tree::findNode(const string& node) const {
    if(!root) return nullptr;
    return findNode(root, node);
}

void Tree::stringifyDFS(node_t* node, string& buffer) {
    for(size_t i = 0; i < node->childCount(); i++) {
        buffer += node->getData() + '-' + node->getChild(i)->getData() +'\n';
    }

    for(size_t i = 0; i < node->childCount(); i++) {
        stringifyDFS(node->getChild(i), buffer);
    }
}

    string Tree::stringifyDFS() {
        string buffer = "";
        if(!root) return buffer;
        stringifyDFS(root, buffer);
        return buffer;
    }

string Tree::stringifyBFS() {
    if(!root) return "";
    string buffer;
    std::queue<node_t*> node_queue;
    node_queue.push(root);
    node_t* current = nullptr;

    while (!node_queue.empty()) {
        current = node_queue.front();
        for(size_t i = 0; i < current->childCount(); i++) {
            buffer += current->getData() + '-' + current->getChild(i)->getData() + '\n';
            node_queue.push(current->getChild(i));
        }
        node_queue.pop();
    }
    
    return buffer;
}



int Tree::getSize() const {
    return size;
}

void Tree::getDepth(node_t* node, int level , int& max_level) const {
    if(level > max_level) {
        max_level = level;
    }

    for(size_t i = 0; i < node->childCount(); i++) {
        getDepth(node->getChild(i), level+1, max_level);
    }
}

int Tree::getDepth() const {
    int max_level = 0;
    getDepth(root,0,max_level);
    return max_level;
}

bool Tree::addChild(node_t* parent, const string& data) {
    bool isAdded = parent->addChild(data);
    if(isAdded) size++;
    return isAdded;
}

bool Tree::addNode(const string& parent_data, const string& node_data) {
    if(findNode(node_data)) return 0;
    node_t* parent = findNode(parent_data);
    if(!parent) return 0;
    return addChild(parent, node_data);;
}

bool Tree::removeChild(node_t* parent, node_t* &to_remove) {
    bool isRemoved = parent->removeChild(to_remove->getData());
    if(isRemoved) size--;
    return isRemoved;
}

bool Tree::removeNode(const string& node) {
    if(root->getData() == node) return 0;
    node_t* to_remove = findNode(node);
    if(!to_remove) return 0;
    return removeChild(to_remove->getParent(), to_remove);;
}

void Tree::getNumDecendants(node_t* node, int& count) const {
    count++;
    for(size_t i = 0; i < node->childCount(); i++) {
        getNumDecendants(node->getChild(i), count);
    }
}

int Tree::getNumDecendants(node_t* node) const {
    int decendants = 0;
    getNumDecendants(node, decendants);
    return decendants;
}

unsigned long Tree::getSalary(const string& node) const {
    node_t* employee = findNode(node);
    if(!employee) throw std::invalid_argument("");
    return 500*employee->childCount() + 50*(getNumDecendants(employee)-employee->childCount());
}

void Tree::getOverloaded(node_t* node, int limit, int& count) const {
    if(node->childCount() >= limit || getNumDecendants(node) >= limit) count++;
    else return;

    for(size_t i = 0; i < node->childCount(); i++) {
        getOverloaded(node->getChild(i), limit, count);
    }
}

int Tree::getOverloaded(int limit) const {
    int count = 0;
    for(size_t i = 0; i < root->childCount(); i++) {
        getOverloaded(root->getChild(i), limit, count);
    }
    return count;
}

Tree Tree::merge(const Tree& other) {
    std::queue<node_t*> node_queue;
    node_queue.push(root);
    node_t* current = nullptr;
    Tree trees(current);
    return trees;
}

void Tree::incorporate() {

}

void Tree::modernize() {
    
}
