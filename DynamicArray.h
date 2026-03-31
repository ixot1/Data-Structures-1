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
};