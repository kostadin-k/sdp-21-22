#ifndef STACK_H
#define STACK_H
#pragma once
#include <iostream>
#include <exception>
#include "Types.hpp"

class Stack {
	struct node_s {
		Action* data = nullptr;
		node_s* next = nullptr;
		node_s() = default;
		node_s(Action* data, node_s* next = nullptr) : next(next) {this->data = data;}
		~node_s() {if(data) delete data;}
	};
	
	node_s* top;
	std::size_t size;

	void clear() {
		while (top) pop();
	}

public:
	Stack() : top(nullptr), size(0) {};
	~Stack() {clear();}

	void push_sorted(Action* data) {
		node_s* new_node = new node_s(data,top);

		if (!top) {
			new_node->next = top;
			top = new_node;
			size++;
			return;
		}
		
		node_s* it = top;

		while (it->next) {
			if (it->next->data->getMinute() > data->getMinute()) {
				new_node->next = it->next;
				it->next = new_node;
				size++;
				return;
			}

			if (it->next->data->getMinute() == data->getMinute()) {
				if (it->next->data->getActionType() >= data->getActionType()) {
					new_node->next = it->next;
					it->next = new_node;
					size++;
					return;
				}
			}
			it = it->next;
		}

		if (!it->next) {
			new_node->next = nullptr;
			it->next = new_node;
			size++;
		}
	}

	void pop() {
		//if (!top) throw std::out_of_range("Stack empty! Unable to pop!");
		if (!top) return;
		node_s* new_top = top->next;
		delete top;
		top = new_top;
		size--;
}

	const Action* getTop() const {
		if (top) return top->data;
		throw std::invalid_argument("Stack empty! Unable to get top!");
	}
	
	bool empty() {
		return !top;
	}

	std::size_t getSize() {
		return size;
	}

	void print() {
		if (!top) {
			std::cout << "Stack empty!\n";
			return;
		} 
		node_s* current_node = top;

		while (current_node) {
			current_node->data->print();
			std::cout << '\n';
			current_node = current_node->next;
		}
	}
};
#endif