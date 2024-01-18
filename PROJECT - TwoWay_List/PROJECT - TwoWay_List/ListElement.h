#pragma once
namespace ms {
	template<typename T>
	struct ListElement {
		T data;
		ListElement* next;
		ListElement* prev;
		ListElement(const T& data) : data(data), next(nullptr), prev(nullptr) {}
	};
}