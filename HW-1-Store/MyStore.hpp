#ifndef MYSTORE_H
#define MYSTORE_H
#pragma once
#include "Stack.hpp"
#include "Queue.hpp"

const int RESTOCK_TIME = 60;
const int RESTOCK_AMOUNT = 100;

struct MyStore : Store {

	ActionHandler *actionHandler = nullptr;

    int banana = 0;
    int schweppes = 0;
    int workers = 0;

    // bool restocking_banana = false;
    // bool restocking_schweppes = false;

    int ordered_banana = 0;
    int ordered_schweppes = 0;

    //int current_time = 0;

    Stack action_list;
    Queue client_queue;

    int client_index = 0;

	void setActionHandler(ActionHandler *handler) override {
		actionHandler = handler;
	}

	void init(int workerCount, int startBanana, int startSchweppes) override {
        workers = workerCount;
        banana = startBanana;
        schweppes = startSchweppes;
        ordered_banana = banana;
        ordered_schweppes = schweppes;
		//current_time = 0;
        client_index = 0;
	}

	void addClients(const Client *clients, int count) override {
		for (int i = 0; i < count; i++) {
            addClient(clients[i]);
        }
	}

	void advanceTo(int minute) override {
        //current_time = minute;
        while (!action_list.empty() && action_list.getTop()->getMinute() <= minute) {
            handleCurrentAction(action_list.getTop());
            action_list.pop();
        }
	}

	virtual int getBanana() const {
		return banana;
	}

	virtual int getSchweppes() const {
		return schweppes;
	}

    void printAllEvents() {
        while (!action_list.empty()) {
            handleCurrentAction(action_list.getTop());
            action_list.pop();
        }  
    }

private:

    void client_leave(int minute) {
        int dif_banana = banana;
        int dif_schweppes = schweppes;
        client_queue.dequeue_check(banana, schweppes, minute, actionHandler);
        dif_banana -= banana;
        dif_schweppes -= schweppes;
        ordered_banana -= dif_banana;
        ordered_schweppes -= dif_schweppes;
    }

    void addClient(const Client& new_client) {
        ClientIndexed cl_indexed(client_index, new_client);
        ClientAction* cl_arrive = new ClientAction(new_client.arriveMinute, ActionType::ClinetArrive, cl_indexed);
        action_list.push_sorted(cl_arrive);
        client_index++;
    }

    void handleCurrentAction(const Action* action) {

        switch (action->getActionType()) {
            case ActionType::WorkerArrive: {
                if (action->getResourceType() == ResourceType::banana) {
                    banana += RESTOCK_AMOUNT;
                    if(actionHandler) actionHandler->onWorkerBack(action->getMinute(), ResourceType::banana);
                    std::cout << "D " << action->getMinute() << " banana\n";
                } else {
                    schweppes += RESTOCK_AMOUNT;
                    if(actionHandler) actionHandler->onWorkerBack(action->getMinute(), ResourceType::schweppes);
                    std::cout << "D " << action->getMinute() << " schweppes\n";
                }
                client_leave(action->getMinute());
                break;
            }

            case ActionType::ClinetArrive: {
                ClientIndexed cl_indexed = action->getClient();
                client_queue.enqueue(cl_indexed);
                int cl_banana = cl_indexed.client_data.banana;
                int cl_schweppes =cl_indexed.client_data.schweppes;
                int task_minute = cl_indexed.client_data.arriveMinute;
                int leave_minute = cl_indexed.leave_time();
                if (cl_banana > banana || cl_schweppes > schweppes) {
                    while (ordered_banana < cl_banana && workers > 0) {
                        WorkerAction* restock_banana = new WorkerAction(task_minute + RESTOCK_TIME ,ActionType::WorkerArrive, ResourceType::banana);
                        action_list.push_sorted(restock_banana);
                        ordered_banana += RESTOCK_AMOUNT;
                        workers--;
                        if(actionHandler) actionHandler->onWorkerSend(task_minute, ResourceType::banana);
                        std::cout << "W " << task_minute << " banana\n";
                    }
                    while (ordered_schweppes < cl_schweppes && workers > 0) {
                        WorkerAction* restock_schweppes = new WorkerAction(task_minute + RESTOCK_TIME ,ActionType::WorkerArrive, ResourceType::schweppes);
                        action_list.push_sorted(restock_schweppes);
                        ordered_schweppes += RESTOCK_AMOUNT;
                        workers--;
                        if(actionHandler) actionHandler->onWorkerSend(task_minute, ResourceType::schweppes);
                        std::cout << "W " << task_minute << " schweppes\n";
                    }
                    ordered_banana -= cl_banana;
                    ordered_schweppes -= cl_schweppes;
                    ClientAction* leave = new ClientAction(leave_minute, ActionType::ClinetLeave, cl_indexed);
                    action_list.push_sorted(leave);

                } else {
                    client_leave(action->getMinute());
                }
                break;
            }

            case ActionType::ClinetLeave: {
                client_leave(action->getMinute());
                break;
            }  
             
        }
        // actionHandler->onWorkerSend(0, ResourceType::banana);
		// actionHandler->onWorkerBack(0, ResourceType::schweppes);
		// actionHandler->onClientDepart(0, 0, 1, 2);
    }
};

#endif