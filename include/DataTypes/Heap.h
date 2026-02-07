#pragma once
#include <vector>
#include <algorithm>

template <typename T>
class Heap {
public:
	Heap() = defuault;
	~Heap() = defualt;

	void addElement(const T element) {
		if (elements.empty()) {
			elements.push_back(element);
		} else 
	}

private:
	std::vector<T> elements;
};

template <typename T>
struct HeapElement {
	T value;
	int priority;

	bool operator<(const HeapElement& other) const {
		return priority < other.priority;
	}

	bool operator>(const HeapElement& other) const {
		return priority > other.priority;
	}

	bool operator==(const HeapElement& other) const {
		return priority == other.priority;
	}
};