#ifndef QUEUE_H
#define QUEUE_H
#pragma once
#include <iostream>
#include <exception>
#include "Types.hpp"

class Queue {
	private:
	struct node_q {
		ClientIndexed data{};
		node_q* next = nullptr;
		node_q() = default;
		node_q(ClientIndexed data, node_q* next = nullptr) : data(data), next(next) {};
	};
	
	node_q* begin;
	node_q* end;
	std::size_t size;

	void dequeue() {
		if(!begin) return;
		node_q* new_begin = begin->next;
		delete begin;
		begin = new_begin;
		size--;
	}

	enum class Position {
		Begin, Middle
	};
		
	bool wasRemoved(node_q* &cl, int time, int& banana, int& schweppes, Position position, ActionHandler* act_hndlr = nullptr) {
		node_q* to_remove = nullptr;

		//int leaveTime = cl->data.leave_time();
		node_q* it = position == Position::Middle ? it = cl->next : cl;

		int cl_banana = it->data.client_data.banana; 
		int cl_schweppes = it->data.client_data.schweppes;

		if (it->data.leave_time() > time) {

			if (it->data.client_data.arriveMinute <= time
				&& banana >= cl_banana
				&& schweppes >= cl_schweppes) {

					banana -= cl_banana;
					schweppes -= cl_schweppes;

					switch (position) {

						case Queue::Position::Begin: {
							if (act_hndlr) 
								act_hndlr->onClientDepart(it->data.id, time, cl_banana, cl_schweppes);
							std::cout << it->data.id << ' ' << time << ' ' << cl_banana << ' ' << cl_schweppes << '\n';
							dequeue();
							cl = begin;
							break;
						}
						
						case Queue::Position::Middle: {
							if (act_hndlr) 
								act_hndlr->onClientDepart(it->data.id, time, cl_banana, cl_schweppes);
							std::cout << it->data.id << ' ' << time << ' ' << cl_banana << ' ' << cl_schweppes << '\n';
							to_remove = cl->next;
							cl->next = cl->next->next;
							delete to_remove;
							break;
						}
						
						/*case Queue::Position::End: {
							delete cl;
							break;
						}*/
					}
					size--;
					return true;
			}
			else {
				//if (position == Position::Begin) cl = cl->next;
				return false;
			}
				
		} else {

			if (banana <= cl_banana) {
				cl_banana = banana;
				banana = 0;
			} else {
				banana -= cl_banana;
			}

			if (schweppes <= cl_schweppes) {
				cl_schweppes = schweppes;
				schweppes = 0;
			} else {
				schweppes -= cl_schweppes;
			}

			switch (position) {
				case Queue::Position::Begin: {

					if (act_hndlr) 
						act_hndlr->onClientDepart(it->data.id, time, cl_banana, cl_schweppes);
					std::cout << it->data.id << ' ' << time << ' ' << cl_banana << ' ' << cl_schweppes << '\n';
					dequeue();
					cl = begin;

					break;
				}

				case Queue::Position::Middle: {
					if (act_hndlr) 
						act_hndlr->onClientDepart(it->data.id, time, cl_banana, cl_schweppes);
					std::cout << it->data.id << ' ' << time << ' ' << cl_banana << ' ' << cl_schweppes << '\n';
					to_remove = cl->next;
					cl->next = cl->next->next;
					delete to_remove;

					break;
				}

				/*case Queue::Position::End: {
					delete cl;
					break;
				}*/
			}
			size--;
			return true;
		}
	}

	public:
		Queue() : size(0), begin(nullptr), end(nullptr) {};
		~Queue() {while (begin) dequeue();}

		void enqueue(const ClientIndexed& data) {
			node_q* new_node = new node_q(data);
			if(!begin) {
				begin = new_node;
			} else {
				end->next = new_node;
			}
			end = new_node;
			size++;
		}
		void dequeue_check(int& banana, int& schweppes, int time, ActionHandler* act_hndlr = nullptr) {
			if(!begin) return;
			node_q* it = begin;
			//node_q* before_end = nullptr;	

			while (it == begin && it) {
				if (!wasRemoved(it, time, banana, schweppes, Position::Begin, act_hndlr)) break;
			}

			if (!it) return;

			while (it->next) {
				if(!wasRemoved(it, time, banana, schweppes, Position::Middle, act_hndlr)) it = it->next;
				//if(it->next = end) before_end = it;
				
			}

			/*int past_size = size;
			remove(end, time, banana, schweppes, Position::End);
			if (size != past_size) before_end->next = nullptr;*/
		}

		
		
		const ClientIndexed& getFirst() const {
			if (begin) return begin->data;
			throw std::invalid_argument("Queue empty! Unable to get first!");
		}

		bool isEmpty() {
			return !begin;
		}

		void print() {
			if(!begin) {
				std::cout << "Queue empty!\n";
				return;
			}
			node_q* current_node = begin;
			while (current_node) {
				current_node->data.print();
				std::cout << std::endl;
				current_node = current_node->next;
			}
			
		}

};
#endif