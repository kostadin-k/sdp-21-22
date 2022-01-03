#include "HierManager.hpp"  
//HierarchyExtended

HierarchyExtended::HierarchyExtended(HierarchyExtended&& r) noexcept : Hierarchy(r) {
    is_saved = r.is_saved;
    name = r.name;
    r.is_saved = 1;
    r.name = "";
}

HierarchyExtended::HierarchyExtended(const HierarchyExtended& r) : Hierarchy(r) {
    is_saved = r.is_saved;
    name = r.name;
}

HierarchyExtended::HierarchyExtended(const string& data, const string& name) : Hierarchy(data) {
    is_saved = 1;
    this->name = name;
}

HierarchyExtended::HierarchyExtended(const Hierarchy& r, const string& name) : Hierarchy(r) {
    is_saved = 1;
    this->name = name;
}

string HierarchyExtended::getName() const {
    return name;
}

bool HierarchyExtended::isSaved() {
    return is_saved;
}

void HierarchyExtended::setName(const string& name) {
    this->name = name;
}

HierarchyExtended HierarchyExtended::join(const HierarchyExtended& r, const string& name) {
    HierarchyExtended heir_ext(this->join(r, name)) ;
    return heir_ext;
}

//HierManager

void HierManager::add(const HierarchyExtended& hier) {
    HierarchyExtended* h = new HierarchyExtended(hier);
    h_list.push_back(h);
}

HierarchyExtended* HierManager::getAtIndex(size_t index) {
    if(index < h_list.size()) return h_list[index];
    return nullptr;
}

size_t HierManager::getSize() {
    return h_list.size();
}

bool HierManager::isInFile(const string& name, const string& path, size_t& pos) {
    std::ifstream file;
    file.open(path);
    if(!file) throw std::invalid_argument("No file!");
    string str;
    while (file) {
		pos = file.tellg();
        getline(file, str);
		if(str == name) {
			file.close();
			return 1;
		}
    }
	pos = file.tellg();
	file.close();
	return 0;
}

HierarchyExtended* HierManager::findHierarchy(const string& name) {
    for(size_t i = 0; i < h_list.size(); i++) {
        if(h_list[i]->getName() == name) return h_list[i];
    }
    string message = "Couldn't find " + name + "!";
    throw std::invalid_argument(message);
    return nullptr;
}

HierarchyExtended* HierManager::join(const string& heir_1, const string& heir_2, const string& heir_3) {
    HierarchyExtended* hier_1_it = findHierarchy(heir_1);
    HierarchyExtended* hier_2_it = findHierarchy(heir_2);
    // Hierarchy* heir = new Hierarchy((hier_1_it)->join(*hier_2_it->getHierarchy()));
    HierarchyExtended* heir_ext = new HierarchyExtended(hier_1_it->join(*hier_2_it, heir_3));
    h_list.push_back(heir_ext);
    return heir_ext;
}

void HierManager::input(const string& name) {
    string user_input;
    string data;
    bool isInputStopped = 0;
    do {
        std::getline(std::cin, user_input);
        if(user_input != "") data += user_input + '\n';
        //std::cin.ignore();

    } while(!std::cin.eof());
    HierarchyExtended* hier = new HierarchyExtended(data, name);
}

void HierManager::load(const string& name, const string& path) {
    std::ifstream file;
    file.open(path);
    if(!file) throw std::invalid_argument("Couldn't open file!");
    size_t pos = 0;
    if(!isInFile(name, path, pos)) {
        file.close();
        throw std::runtime_error("Couldn't find hierarchy!");
    }
    string buffer, data;
    getline(file, buffer);
    
    while (buffer != "") {
        getline(file, buffer);
        data+=buffer + '\n';
    }
    
    HierarchyExtended* new_hier = new HierarchyExtended(data, name);
    new_hier->setName(name);
    h_list.push_back(new_hier);
}

void HierManager::save(const string& name, const string& path) {
    HierarchyExtended* hier = findHierarchy(name);
    std::ofstream file;
    file.open(path);
    if(!file) throw std::invalid_argument("Couldn't open file!");

    string data = name + '\n' + hier->print() +'\n';
    size_t pos = 0;
    if(!isInFile(name, path, pos)) {
        file.seekp(0,std::ios_base::end);
        file.write(data.c_str(),data.size());
        file.close();
    } else {
        file.close();
        std::fstream temp_file;
        temp_file.open(path + "\\..\\temp.txt", std::ios::out | std::ios::in | std::ios::trunc);
        if(!temp_file) throw std::invalid_argument("Couldn't open temp file!");
        std::ifstream file_r;
        file_r.open(path);
        if(!temp_file) throw std::invalid_argument("Couldn't open file-r file!");
        
       // size_t pos = file_r.tellg();
        string buffer;
        buffer.resize(pos);
        file_r.read(&buffer[0], pos);
        buffer += '\n';
        temp_file.write(&buffer[0], pos+1);

        temp_file.write(data.c_str(),data.size());
        buffer.clear();

        while (buffer[0] == '\n') {
            getline(file_r, buffer);
        }

        file_r.seekg(1, std::ios::cur);
        pos = file_r.tellg();
        file_r.seekg(0, std::ios_base::end);
        size_t size = file_r.tellg();
        file_r.seekg(pos, std::ios_base::beg);


        buffer.clear();
        buffer.resize(size - pos);
        file_r.read(&buffer[0], size - pos);
        temp_file.write(&buffer[0], size - pos);
        file_r.close();

        file.open(path, std::ios::out | std::ios::trunc);
        if(!file) throw std::invalid_argument("Couldn't open file 2!");

        temp_file.seekg(0);
        buffer.clear();
        while (temp_file) {
            getline(temp_file,buffer);
            buffer += '\n';
            file.write(&buffer[0], buffer.size());
        }
        file.close();
        temp_file.close();

        buffer = path + "\\..\\temp.txt";
        remove(buffer.c_str());
    }
}

bool HierManager::areUnsaved() {
    string unsaved = "";
    for(size_t i = 0; i < h_list.size(); i++) {
        if(!h_list[i]->isSaved()) unsaved += h_list[i]->getName() + ' ';
    }
    return unsaved.size();
}