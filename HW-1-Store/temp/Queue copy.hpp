#ifndef QUEUE_H
#define QUEUE_H
#pragma once
#include <iostream>
#include <exception>

template <class T>
struct ClientOrder {
	long id;

	T data{};

	ClientOrder() = default;

	ClientOrder(long id, T data) {
		this->id = id;
		this->data = data;
	}

	ClientOrder& operator=(const ClientOrder& other) {
		if(this != &other) {
			id = other.id
			data = other.data;
		}
		return *this;
	}
};
template <class T>
class Queue {
	private:
	struct node_q {
		ClientOrder<T> data{};
		node_q* next = nullptr;
		node_q() = default;
		node_q(ClientOrder<T> data, node_q* next = nullptr) : data(data), next(next) {};
	};
	
	node_q* begin;
	node_q* end;
	std::size_t size;

	public:
		Queue() : size(0), begin(nullptr), end(nullptr) {};
		~Queue() {while (begin) pop();}

		void push(const ClientOrder<T>& data) {
			node_q* new_node = new node_q(data);
			if(!begin) {
				begin = new_node;
			} else {
				end->next = new_node;
			}
			end = new_node;
			size++;
		}
		void pop() {
			node_q* new_begin = begin->next;
			delete begin;
			begin = new_begin;
			size--;
		}
		
		const ClientOrder<T>& getFirst() const {
			if (begin) return begin->data;
			throw std::invalid_argument("Stack empty! Unable to get first!");
		}

		bool isEmpty() {
			return !begin;
		}

};
#endif