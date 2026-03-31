#include "DynamicArray.h"

DynamicArray::DynamicArray()
	:	array(new int[1]), capacity(1), size(0) {
}

DynamicArray::DynamicArray(size_t initialCapacity)
	:	array(new int[initialCapacity]), capacity(initialCapacity), size(0) {
		}

DynamicArray::~DynamicArray(){
	delete[] array;
}