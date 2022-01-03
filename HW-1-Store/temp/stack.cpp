#include "./Stack.hpp"

// std::string Action::typeToStr(ActionType& type) {
//     std::string output;
//     switch (type) {
//         case ActionType::WorkerArrive: {
//             output = "WorkerArrive";
//             break;
//         }
            
//         case ActionType::ClinetLeave: {
//             output = "ClinetLeave";
//             break;
//         }

//         case ActionType::ClinetArrive: {
//             output = "ClinetArrive";
//             break;
//         }
        
//         default: {
//             output = "undefined";
//             break;
//         }
//     }
//     return output;
// }

// Action::Action(long minute, ActionType type) {
//     if (minute < 0) {throw std::out_of_range("");}
//     this->minute = minute;
//     this->type = type;
// }

// Action& Action::operator=(const Action& other) {
//     if(this != &other) {
//         minute = other.minute;
//         type = other.type;
//     }
//     return *this;
// }

// const long Action::getMinute() const {return minute;}
// const ActionType Action::getActionType() const {return type;}

// void Action::print() {
//     std::cout << "Action - ";
//     std::cout << "Minute: ";
//     std::cout << minute;
//     std::cout << ", Task: ";
//     std::cout << typeToStr(type);
// }





	


// void Stack::clear() {
//     while(top) pop();
// }

// Stack::Stack() : top(nullptr), size(0) {};
// Stack::~Stack() {clear();}

// void Stack::push_sorted(const Action& data) {
//     node_s* new_item = new node_s(data,top);

//     if (!top) {
//         new_item->next = top;
//         top = new_item;
//         return;
//     }
    
//     node_s* new_pos = top;

//     while (new_pos->next) {
//         if (new_pos->next->data.getMinute() > data.getMinute()) {
//             new_item->next = new_pos->next;
//             new_pos->next = new_item;
//             return;
//         }

//         if (new_pos->next->data.getMinute() == data.getMinute()) {
//             if (new_pos->next->data.getActionType() >= data.getActionType()) {
//                 new_item->next = new_pos->next;
//                 new_pos->next = new_item;
//                 return;
//             }
//         }
//         new_pos = new_pos->next;
//     }

//     if(!new_pos->next) {
//         new_item->next = nullptr;
//         new_pos->next = new_item;
//     }

// }

// void Stack::pop() {
//     if (!top) throw std::out_of_range("Stack empty! Unable to pop!");
//     node_s* newTop = top->next;
//     delete top;
//     top = top->next;
// }

// const Action& Stack::getTop() const {
//     if (!top) throw std::invalid_argument("Stack empty! Unable to top!");
//     return top->data;
// }

// void Stack::print() {
//     if (!top) {
//         std::cout << "Stack empty!\n";
//         return;
//     } 
//     node_s* current_item = top;

//     while (current_item) {
//         current_item->data.print();
//         std::cout << '\n';
//         current_item = current_item->next;
//     }
// }