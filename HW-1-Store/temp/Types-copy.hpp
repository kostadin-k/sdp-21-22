#ifndef TYPES_H
#define TYPES_H
#pragma once
#include <iostream>	
#include <string>
#include "../interface.h"

struct ClientOrder {
	int id = -1;
	Client client_data{};

	//ClientOrder() : id(-1), arrive_time(0), bananas(0), schweppes(0), wait_time(0) {}
	ClientOrder() = default;

	ClientOrder(int id, int arrive_minute, int banana, int schweppes, int max_wait_time);
	ClientOrder(int id, const Client& new_client_data);
	int leave_time() ;

	ClientOrder& operator=(const ClientOrder& other);
};


enum class ActionType {
	WorkerArrive, // 1
	ClinetLeave, //  2
	ClinetArrive//   3 
};


class Action {

	int minute = 0;
	ActionType action_type{};

	std::string typeToStr(ActionType& action_type);
	
public:
	Action() = default;

	Action(int minute, ActionType action_type);

	Action& operator=(const Action& other);

	const int getMinute() const;
	const ActionType getActionType() const;
	virtual ResourceType getResourceType();
	//virtual ClientOrder* getClient() {return nullptr;}
	virtual int getClientId();
	virtual int getClientArrival();
	virtual int getClientBanana();
	virtual int getClientSchweppes();
	virtual int getClientMaxWaitTime();

	virtual void print();
};

class WorkerAction : public Action {
	ResourceType resource_type = ResourceType::banana;
public:
	WorkerAction() = default;
	WorkerAction(int minute, ActionType action_type, ResourceType resource_type);
	
	ResourceType getResourceType() override;

	void print() override;
};

class ClientAction  : public Action {
	ClientOrder* client = nullptr;
public:
	ClientAction() = default;
	ClientAction(int minute, ActionType action_type, ClientOrder* client);
	
	int getClientId() override;
	int getClientArrival() override;
	int getClientBanana() override;
	int getClientSchweppes() override;
	int getClientMaxWaitTime() override;

	void print() override;
};
#endif