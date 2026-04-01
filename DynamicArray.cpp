#include "DynamicArray.h"
#include <iostream>

DynamicArray::DynamicArray()
	:	array(new int[1]), capacity(1), size(0) {
}

DynamicArray::DynamicArray(size_t initialCapacity)
	:	array(new int[initialCapacity]), capacity(initialCapacity), size(0) {
		}

DynamicArray::~DynamicArray(){
	delete[] array;
}

void DynamicArray::print_array() {
	for (int i = 0; i < size; i++) {
		std::cout << array[i] << " ";
	}
}

void DynamicArray::check_capacity() {
	//with single element additions size can't be more than capacity, >= condition is for safety measure if we wanted to add more than one element at once
	if (size >= capacity) {
		size_t newCapacity = capacity * 2;
		int* newArray = new int[newCapacity];
		for (int i = 0; i < size; i++) {
			newArray[i] = array[i];
		}
		delete[] array;

		array = newArray;
		capacity = newCapacity;
	}
}

void DynamicArray::push_back(int data){
	check_capacity();
	array[size] = data;
	size++;
}

void DynamicArray::push_front(int data) {
}

void DynamicArray::push_at(int data, size_t index) {
}

void DynamicArray::pop_back() {
}

void DynamicArray::pop_front() {
}

void DynamicArray::pop_at(size_t index) {
}