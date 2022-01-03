#ifndef TYPES_H
#define TYPES_H
#pragma once
#include <iostream>	
#include <string>
#include "interface.h"

struct ClientIndexed {
	int id = -1;
	Client* client_data = nullptr;

	//ClientIndexed() : id(-1), arrive_time(0), bananas(0), schweppes(0), wait_time(0) {}
	ClientIndexed() = default;

	ClientIndexed(int id, int arrive_minute, int banana, int schweppes, int max_wait_time) {
		this->id = id;
		client_data = new Client{arrive_minute, banana, schweppes, max_wait_time};
		
	}
	ClientIndexed(int id, const Client& new_client) {
		this->id = id;
		client_data = new Client{new_client.arriveMinute, new_client.banana, new_client.schweppes, new_client.maxWaitTime};
		
	}
	int leave_time() {
		return client_data->arriveMinute + client_data->maxWaitTime;
	}

	ClientIndexed& operator=(const ClientIndexed& other) {
		if(this != &other) {
			id = other.id;
			client_data->arriveMinute = other.client_data->arriveMinute;
			client_data->banana = other.client_data->banana;
			client_data->schweppes = other.client_data->schweppes;
			client_data->maxWaitTime = other.client_data->maxWaitTime;
		}
		return *this;
	}

	void print() {
		std::cout << '#' << id;
		std::cout << ", Arrive Minute: " << client_data->arriveMinute;
		std::cout << ", Bananas: " << client_data->banana;
		std::cout << ", Schweppes: " << client_data->schweppes;
		std::cout << ", MaxWaitTime: " << client_data->maxWaitTime;
	}

	~ClientIndexed() {if (client_data) delete client_data;}
};


enum class ActionType {
	WorkerArrive, // 1
	ClinetLeave, //  2
	ClinetArrive//   3 
};


class Action {

	int minute = 0;
	ActionType action_type{};

	std::string typeToStr(ActionType& action_type) {
    	std::string output;
		switch (action_type) {
			case ActionType::WorkerArrive: {
				output = "WorkerArrive";
				break;
			}
				
			case ActionType::ClinetLeave: {
				output = "ClinetLeave";
				break;
			}

			case ActionType::ClinetArrive: {
				output = "ClinetArrive";
				break;
			}
			
			default: {
				output = "undefined";
				break;
			}
		}
    	return output;
	}
	
public:
	Action() = default;

	Action(int minute, ActionType action_type) {
		if (minute < 0) {throw std::out_of_range("");}
		this->minute = minute;
		this->action_type = action_type;
	}

	Action& operator=(const Action& other) {
		if(this != &other) {
			minute = other.minute;
			action_type = other.action_type;
		}
		return *this;
	}

	const int getMinute() const {return minute;}
	const ActionType getActionType() const {return action_type;}
	virtual const ResourceType getResourceType() const {return ResourceType::banana;}
	//virtual ClientIndexed* getClient() {return nullptr;}
	virtual const int getClientId() const {return 0;}
	virtual const int getClientArrival() const {return 0;}
	virtual const int getClientBanana() const {return 0;}
	virtual const int getClientSchweppes() const {return 0;}
	virtual const int getClientMaxWaitTime() const {return 0;}

	void print()  {
		std::cout << "Action - ";
		std::cout << "Minute: ";
		std::cout << minute;
		std::cout << ", Task: ";
		std::cout << typeToStr(action_type);
	}
};

class WorkerAction : public Action {
	ResourceType resource_type = ResourceType::banana;
public:
	WorkerAction() = default;
	WorkerAction(int minute, ActionType action_type, ResourceType resource_type)
		 : Action(minute, action_type), resource_type(resource_type) {}
	
	ResourceType const getResourceType() const override {return resource_type;}

	void print() {
		std::cout << "Worker ";
		Action::print();
	}
};

class ClientAction  : public Action {
	ClientIndexed* client = nullptr;
public:
	ClientAction() = default;
	ClientAction(int minute, ActionType action_type, ClientIndexed* client)
		 : Action(minute, action_type), client(client) {}
	
	const int getClientId() const override {return (*client).id;}
	const int getClientArrival() const override {return (*client).client_data->arriveMinute;}
	const int getClientBanana() const override {return (*client).client_data->banana;}
	const int getClientSchweppes() const override {return (*client).client_data->schweppes;}
	const int getClientMaxWaitTime() const override {return (*client).client_data->maxWaitTime;}

	void print() {
		std::cout << "Client ";
		Action::print();
	}
	~ClientAction() {if (client) delete client;}
};
#endif