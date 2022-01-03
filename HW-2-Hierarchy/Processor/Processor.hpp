#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H
#include "Command/Command.hpp"
#include "../HierManager/HierManager.hpp"
#include <iostream>
#include <fstream>
using std::cin;
using std::cout;
using std::endl;
using std::cerr;
/*
	class Processor is the command ui and executes functions at user unput
*/
class Processor {
	HierManager hier_man;
	bool isValidCommand(Command& command);
	bool execute(Command& command);
	std::string help_list[15] = {
		"Command list:",
		"load <object name> [file name]",
		"save <object name> [file name]",
		"find <object name> <employee name>",
		"num_subordinates <object name> <employee name>",
		"manager <object name> <employee name>",
		"num_employees <object name>",
		"overloaded <object name>",
		"join <object name 1> <object name 2> <object name result>",
		"fire <object name> <employee name>",
		"hire <object name> <employee name> <boss name>",
		"salary <object name> <employee name>",
		"incorporate <object name>",
		"modernize <object name>",
		"exit"
		};
	void processFind(bool isHere);
public:
	Processor();
	~Processor();
	void run();
};
#endif