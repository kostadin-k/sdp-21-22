#include "Types-copy.hpp"

ClientOrder::ClientOrder(int id, int arrive_minute, int banana, int schweppes, int max_wait_time) {
    this->id = id;
    client_data.arriveMinute = arrive_minute;
    client_data.banana = banana;
    client_data.schweppes = schweppes;
    client_data.maxWaitTime = max_wait_time;
}

ClientOrder::ClientOrder(int id, const Client& new_client_data) {
    this->id = id;
    client_data.arriveMinute = new_client_data.arriveMinute;
    client_data.banana = new_client_data.banana;
    client_data.schweppes = new_client_data.schweppes;
    client_data.maxWaitTime = new_client_data.maxWaitTime;
    
}
int ClientOrder::leave_time() {
    return client_data.arriveMinute + client_data.maxWaitTime;
}

ClientOrder& ClientOrder::operator=(const ClientOrder& other) {
    if(this != &other) {
        id = other.id;
        client_data.arriveMinute = other.client_data.arriveMinute;
        client_data.banana = other.client_data.banana;
        client_data.schweppes = other.client_data.schweppes;
        client_data.maxWaitTime = other.client_data.maxWaitTime;
    }
    return *this;
}

std::string Action::typeToStr(ActionType& action_type) {
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
	
	//Action::Action() = default;

	Action::Action(int minute, ActionType action_type) {
		if (minute < 0) {throw std::out_of_range("");}
		this->minute = minute;
		this->action_type = action_type;
	}

	Action& Action::operator=(const Action& other) {
		if(this != &other) {
			minute = other.minute;
			action_type = other.action_type;
		}
		return *this;
	}

	const int Action::getMinute() const {return minute;}
	const ActionType Action::getActionType() const {return action_type;}
	ResourceType Action::getResourceType() {return ResourceType::banana;}
	int Action::getClientId() {return 0;}
	int Action::getClientArrival() {return 0;}
	int Action::getClientBanana() {return 0;}
	int Action::getClientSchweppes() {return 0;}
	int Action::getClientMaxWaitTime() {return 0;}

	void Action::print()  {
		std::cout << "Action - ";
		std::cout << "Minute: ";
		std::cout << minute;
		std::cout << ", Task: ";
		std::cout << typeToStr(action_type);
	}

    WorkerAction::WorkerAction(int minute, ActionType action_type, ResourceType resource_type)
		 : Action(minute, action_type), resource_type(resource_type) {}
	
	ResourceType WorkerAction::getResourceType()  {return resource_type;}

	void WorkerAction::print() {
		std::cout << "Worker ";
		Action::print();
	}

	ClientAction::ClientAction(int minute, ActionType action_type, ClientOrder* client)
		 : Action(minute, action_type), client(client) {}
	
	int ClientAction::getClientId()  {return (*client).id;}
	int ClientAction::getClientArrival()  {return (*client).client_data.arriveMinute;}
	int ClientAction::getClientBanana()  {return (*client).client_data.banana;}
	int ClientAction::getClientSchweppes()  {return (*client).client_data.schweppes;}
	int ClientAction::getClientMaxWaitTime()  {return (*client).client_data.maxWaitTime;}

	void ClientAction::print() {
		std::cout << "Client ";
		Action::print();
	}