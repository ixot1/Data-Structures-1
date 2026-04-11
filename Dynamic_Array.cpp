#include "Dynamic_Array.h"
#include <iostream>

DynamicArray::DynamicArray() : size(0), capacity(2) {
    array = new int[capacity];
}

DynamicArray::DynamicArray(size_t init_capacity) : size(0), capacity(init_capacity) {
    // capacity should never be 0, it can cause problems with resizing strategy (capacity *= 2)
    if (init_capacity < 1) {
        capacity = 1;
    }

    array = new int[capacity];
}

DynamicArray::~DynamicArray() {
    delete[] array;
}

void DynamicArray::resize(size_t new_capacity) {
    // creating a new array with the new capacity
    int* new_array = new int[new_capacity];
    
    // copying data from the old array to the new one
    std::memcpy(new_array, array, size * sizeof(int));

    delete[] array; //freeing memory used by old array
    array = new_array;
    capacity = new_capacity;
}

void DynamicArray::print_array(void) {

    for (size_t i = 0; i < size; i++) {
        std::cout << array[i]<< " " ;
    }
}

size_t DynamicArray::get_size(void) const {
    return size;
}

int DynamicArray::get_component(size_t index) const {
    if (index >= size) {
            std::cout << "\nIndex is out of range.\n";
            return 0;
    }
    return array[index];
}

void DynamicArray::push_back(int value) {
    // if we are at the limit of capacity, we need to double the capacity to accomodate more elements
    if (size == capacity) {
        resize(capacity * 2);
    }

    array[size] = value;
    size++;
}

void DynamicArray::push_front(int value) {
    if (size == capacity) {
        resize(capacity * 2);
    }

    // moving all of data one place to the right and overwriting array[0]
    for (size_t i = size; i > 0; i--) {
        array[i] = array[i - 1];
    }

    array[0] = value;
    size++;
}

void DynamicArray::push_at(int value, size_t index) {
    //using similar logic as in push_front and push_back
    if (index > size && index) {
        std::cout << "\nIndex is out of range\n";
        return;
    }

    if (size == capacity) {
        resize(capacity * 2);
    }

    for (size_t i = size; i > index; i--) {
        array[i] = array[i - 1];
    }

    array[index] = value;
    size++;
}

void DynamicArray::pop_front(void) {
    if (!size) {
        std::cout << "There are no elements to remove.\n";
    }

    for (size_t i = 0; i < size; i++) {
        array[i] = array[i + 1];
    }

    size--;
}

void DynamicArray::pop_back(void) {
    if (!size) {
        std::cout << "There are no elements to remove.\n";
    }

    size--;
}

void DynamicArray::pop_at(size_t index) {
    if (!size) {
        std::cout << "There are no elements to remove.\n";
    }

    if (index >= size) {
        std::cout << "\nIndex is out of range\n";
    }

    for (size_t i = index; i < size; i++) {
        array[i] = array[i + 1];
    }

    size--;
}

bool DynamicArray::search(int value) {
    for (size_t i = 0; i < size; i++)
        if (array[i] == value)
            return true;

    return false;
}