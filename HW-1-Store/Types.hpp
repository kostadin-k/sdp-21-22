#ifndef TYPES_H
#define TYPES_H
#pragma once
#include <iostream>	
#include <string>
#include "interface.h"

struct ClientIndexed {
	int id = -1;
	Client client_data{};

	//ClientIndexed() : id(-1), arrive_time(0), bananas(0), schweppes(0), wait_time(0) {}
	ClientIndexed() = default;

	ClientIndexed(int id, int arrive_minute, int banana, int schweppes, int max_wait_time) {
		this->id = id;
		client_data.arriveMinute = arrive_minute;
		client_data.banana = banana;
		client_data.schweppes = schweppes;
		client_data.maxWaitTime = max_wait_time;
		
	}
	ClientIndexed(int id, const Client& new_client) {
		this->id = id;
		client_data.arriveMinute = new_client.arriveMinute;
		client_data.banana = new_client.banana;
		client_data.schweppes = new_client.schweppes;
		client_data.maxWaitTime = new_client.maxWaitTime;
		
	}
	int leave_time() {
		return client_data.arriveMinute + client_data.maxWaitTime;
	}

	ClientIndexed& operator=(const ClientIndexed& other) {
		if(this != &other) {
			id = other.id;
			client_data.arriveMinute = other.client_data.arriveMinute;
			client_data.banana = other.client_data.banana;
			client_data.schweppes = other.client_data.schweppes;
			client_data.maxWaitTime = other.client_data.maxWaitTime;
		}
		return *this;
	}

	void print() {
		std::cout << '#' << id;
		std::cout << ", Arrive Minute: " << client_data.arriveMinute;
		std::cout << ", Bananas: " << client_data.banana;
		std::cout << ", Schweppes: " << client_data.schweppes;
		std::cout << ", MaxWaitTime: " << client_data.maxWaitTime;
	}

	//~ClientIndexed() {if (client_data) delete client_data;}
};


enum class ActionType {
	WorkerArrive, // 1
	ClinetLeave, //  2
	ClinetArrive//   3 
};


class Action {

	int minute = 0;
	ActionType action_type{};

	std::string aTypeToStr(ActionType& action_type) {
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
		}
    	return output;
	}
	void copy(const Action& other) {
		if(this != &other) {
			minute = other.minute;
			action_type = other.action_type;
		}
	}
public:
	Action() = default;

	Action(int minute, ActionType action_type) {
		if (minute < 0) {throw std::out_of_range("");}
		this->minute = minute;
		this->action_type = action_type;
	}

	Action(const Action& other) {
		copy(other);
	}

	Action& operator=(const Action& other) {
		copy(other);
		return *this;
	}

	const int getMinute() const {return minute;}
	const ActionType getActionType() const {return action_type;}
	virtual const ResourceType getResourceType() const {return ResourceType::banana;}
	virtual const ClientIndexed getClient() const {return ClientIndexed{};}
	virtual const int getClientId() const {return 0;}
	virtual const int getClientArrival() const {return 0;}
	virtual const int getClientBanana() const {return 0;}
	virtual const int getClientSchweppes() const {return 0;}
	virtual const int getClientMaxWaitTime() const {return 0;}

	virtual void print() {
		std::cout << "Action - ";
		std::cout << "Minute: ";
		std::cout << minute;
		std::cout << ", Task: ";
		std::cout << aTypeToStr(action_type);
	}
};

class WorkerAction : public Action {
	ResourceType resource_type = ResourceType::banana;

	std::string rTypeToStr(ResourceType& action_type) {
		std::string output;
		switch (action_type) {
			case ResourceType::banana: {
				output = "banana";
				break;
			}
				
			case ResourceType::schweppes: {
				output = "schweppes";
				break;
			}
		}
		return output;
	}
public:
	WorkerAction() = default;
	WorkerAction(int minute, ActionType action_type, ResourceType resource_type)
		 : Action(minute, action_type), resource_type(resource_type) {}

	WorkerAction(const WorkerAction& other) : Action(other) {
		resource_type = other.resource_type;
	}

	WorkerAction& operator=(const WorkerAction& other) {
		Action::operator=(other);
		resource_type = other.resource_type;
		return *this;
	}
	
	ResourceType const getResourceType() const override {return resource_type;}

	void print() override {
		std::cout << "Worker ";
		Action::print();
		std::cout << rTypeToStr(resource_type);
	}
};

class ClientAction  : public Action {
	ClientIndexed client{};
public:
	ClientAction() = default;
	ClientAction(int minute, ActionType action_type, ClientIndexed client)
		 : Action(minute, action_type) {this->client = client;}

	ClientAction(const ClientAction& other) : Action(other) {
		client = other.client;
	}
	
	ClientAction& operator=(const ClientAction& other) {
		Action::operator=(other);
		client = other.client;
		return *this;
	}

	const ClientIndexed getClient() const override {return client;}
	const int getClientId() const override {return client.id;}
	const int getClientArrival() const override {return client.client_data.arriveMinute;}
	const int getClientBanana() const override {return client.client_data.banana;}
	const int getClientSchweppes() const override {return client.client_data.schweppes;}
	const int getClientMaxWaitTime() const override {return client.client_data.maxWaitTime;}

	void print() override {
		std::cout << "Client ";
		Action::print();
		client.print();
	}
	//~ClientAction() {if (client) delete client;}
};
#endif