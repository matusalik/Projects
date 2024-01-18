#pragma once
#include <iostream>
#include"ListElement.h"
namespace ms {
	template<typename T>
	class TWList {
	private:
		//head ------ data ------- tail
		ListElement<T>* head;
		ListElement<T>* tail;
	public:
		TWList() : head(nullptr), tail(nullptr) {}
		~TWList() {
			while (head != nullptr) {
				ListElement<T>* temp = head;
				head = head->next;
				delete temp;
			}
		}
		void push_back(const T& data) {
			ListElement<T>* newElement = new ListElement<T>(data);
			if (tail == nullptr) {
				head = tail = newElement;
			}
			else {
				newElement->prev = tail;
				tail->next = newElement;
				tail = newElement;
			}		
		}
		void push_front(const T& data) {
			ListElement<T>* newElement = new ListElement<T>(data);
			if (head == nullptr) {
				head = tail = newElement;
			}
			else {
				newElement->next = head;
				head->prev = newElement;
				head = newElement;
			}
		}
		void display() {
			ListElement<T>* current = head;
			while (current != nullptr) {
				std::cout << current->data << " ";
				current = current->next;
			}
			std::cout << std::endl;
		}
	};
}