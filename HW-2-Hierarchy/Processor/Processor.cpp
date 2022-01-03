#include "Processor.hpp"

bool isEqualString(std::string str_1, std::string str_2) {
    if (str_1 == str_2) return true;
    if (str_1.size() != str_2.size()) return false;
    size_t len = str_1.size();
    const char* ch_1 = str_1.c_str();
    const char* ch_2 = str_2.c_str();
    for (size_t i = 0; i < len; i++) {
        if (std::toupper(ch_1[i]) != std::toupper(ch_2[i])) return false;
    } 
    return true;
}

void Processor::processFind(bool isHere) {
    if (!isHere) cout <<"n't";
}

Processor::Processor() {

};

Processor::~Processor() {

};

// Processor::Processor(std::string path) {

// }

void Processor::run() {
    std::string input;
    bool active = true;
    do {
        std::getline(std::cin, input);
        Command command(input);
        if(!isValidCommand(command)) {
            if (command.getString() == "") {
                std::cin.ignore();
            }
            continue;
        }
        active = execute(command);

    } while (active);
}

bool Processor::isValidCommand(Command& command) {       
    if (isEqualString(command[0], "load")) {
        if (command.size() < 2) {
            std::cerr << "Usage: "<< help_list[1] << "\n";
            return false;
        }
        return true;

    } else if (isEqualString(command[0], "save")) {
        if (command.size() < 2) {
            std::cerr << "Usage: "<< help_list[2] << "\n";
            return false;
        }
        return true;

    } else if (isEqualString(command[0], "find")) {
        if (command.size() < 3) {
            std::cerr << "Usage: "<< help_list[3] << "\n";
            return false;            
        }
        return true;

    } else if (isEqualString(command[0], "num_subordinates")) {
        if (command.size() < 3) {
            std::cerr << "Usage: "<< help_list[4] << "\n";
            return false;            
        }
        return true;

    } else if (isEqualString(command[0], "manager")) {
        if (command.size() < 3) {
            std::cerr << "Usage: "<< help_list[5] << "\n";
            return false;            
        }
        return true;
        
    } else if (isEqualString(command[0], "num_employees")) {
        if (command.size() < 2) {
            std::cerr << "Usage: "<< help_list[6] << "\n";
            return false;            
        }
        return true;

    } else if (isEqualString(command[0], "overloaded")) {
        if (command.size() < 2) {
            std::cerr << "Usage: "<< help_list[7] << "\n";
            return false;            
        }
        return true;

    } else if (isEqualString(command[0], "join")) {
        if (command.size() < 4) {
            std::cerr << "Usage: "<< help_list[8] << "\n";
            return false;            
        }
        return true;

    } else if (isEqualString(command[0], "fire")) {
        if (command.size() < 3) {
            std::cerr << "Usage: "<< help_list[9] << "\n";
            return false;            
        }
        return true;

    } else if (isEqualString(command[0], "hire")) {
        if (command.size() < 4) {
            std::cerr << "Usage: "<< help_list[10] << "\n";
            return false;            
        }
        return true;

    } else if (isEqualString(command[0], "salary")) {
        if (command.size() < 3) {
            std::cerr << "Usage: "<< help_list[11] << "\n";
            return false;            
        }
        return true;

    } else if (isEqualString(command[0], "incorporate")) {
        if (command.size() < 2) {
            std::cerr << "Usage: "<< help_list[12] << "\n";
            return false;            
        }
        return true;

    } else if (isEqualString(command[0], "modernize")) {
        if (command.size() < 2) {
            std::cerr << "Usage: "<< help_list[13] << "\n";
            return false;            
        }
        return true;

    } else {
        std::cerr << "Unknown command!\n";
        return false;
    }
}

bool Processor::execute(Command& command) {
    if (isEqualString(command[0], "exit")) {
        std::cout << "Exiting program...";
        return 0;
    }

    try {
        if (isEqualString(command[0], "load")) {
            if (command.size() == 2) {
                hier_man.input(command[1]);
            } else {
                hier_man.load(command[1], command[2]);
            }

        } else if (isEqualString(command[0], "save")) {
            if (command.size() == 2) {
                std::cout << hier_man.findHierarchy(command[1])->print();
            } else {
                hier_man.load(command[1], command[2]);
            }

        } else if (isEqualString(command[0], "find")) {
            bool isEmplyeeHere = hier_man.findHierarchy(command[1])->find(command[2]);
            cout << command[2] << " is "; processFind(isEmplyeeHere); cout<<" employed in " << command[1] << ".\n";

        } else if (isEqualString(command[0], "num_subordinates")) {
            int subs = hier_man.findHierarchy(command[1])->num_subordinates(command[2]);
            cout << command[2] << " has "<< subs <<" subordinates" << ".\n";

        } else if (isEqualString(command[0], "manager")) {
            string manager = hier_man.findHierarchy(command[1])->manager(command[2]);
            cout << "The manager of " << command[2] << " is " << manager << ".\n";
            
        } else if (isEqualString(command[0], "num_employees")) {
            int employee_number = hier_man.findHierarchy(command[1])->num_employees();
            cout << "There are " << employee_number << " employees in " << command[1] << ".\n";

        } else if (isEqualString(command[0], "overloaded")) {
            int empl_overloaded = hier_man.findHierarchy(command[1])->num_overloaded();
            cout << empl_overloaded << " overloaded employees in Lozenec.\n";

        } else if (isEqualString(command[0], "join")) {
            hier_man.join(command[1], command[2], command[3]);
            cout << command[3] << " has been created" << ".\n";

        } else if (isEqualString(command[0], "fire")) {
            bool fired = hier_man.findHierarchy(command[1])->fire(command[2]);
            cout << command[1] << " has been fired" << ".\n";

        } else if (isEqualString(command[0], "hire")) {
            bool hired = hier_man.findHierarchy(command[1])->hire(command[2], command[3]);
            cout << command[1] << " has been hired" << ".\n";

        } else if (isEqualString(command[0], "salary")) {
            unsigned long salary = hier_man.findHierarchy(command[1])->getSalary(command[2]);
            cout << command[2] << "'s salary is " << salary << ".\n";

        } else if (isEqualString(command[0], "incorporate")) {
            hier_man.findHierarchy(command[1])->incorporate();
            cout << command[1] << "has been incorporated" << ".\n";

        } else if (isEqualString(command[0], "modernize")) {
            hier_man.findHierarchy(command[1])->modernize();
            cout << command[1] << "has been modernized" << ".\n";

        } else if (isEqualString(command[0], "help")) {
            for (int i = 0; i < 14; i++) {
                cout << help_list[i] << '\n';
            }
        } else {
            cerr << "Invalid input!\n";
        }

    } catch(std::exception &e) {
        cerr << e.what() <<'\n';
    }

    return 1;
}