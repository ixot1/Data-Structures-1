#pragma once

class DynamicArray {
private:
	int* array;
	size_t size;
	size_t capacity;

public:
	DynamicArray();
	DynamicArray(size_t initialCapacity);
	~DynamicArray();

	void print_array();
	void check_capacity();
	
	void push_back(int data);
	void push_front(int data);
	void push_at(int data, size_t index);

	void pop_back();
	void pop_front();
	void pop_at(size_t index); //są nam potrzebne oba push i pull?

	void append();
	void prepend();
	void insert();
	void remove();

};