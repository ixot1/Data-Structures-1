#pragma once
#include <iostream>

class Structure {
public:
    virtual void print_array(void) = 0;                      // display values inside of a chosen structure
    virtual size_t get_size(void) const = 0;                 // returns size value
    virtual int get_component(size_t index) const = 0;       // returns a number on the given index
    virtual bool search(int value) = 0;                      // checks if the specified value is in the structure

    virtual int pop_front(void) = 0;                         // removes item from the beggining
    virtual int pop_back(void) = 0;                          // removes item from the end
    void pop_at(size_t index) = 0;							 // removes item from the specified index

    void push_back(int data) = 0;
    void push_front(int data) = 0;
    void push_at(int data, size_t index) = 0;                //są nam potrzebne oba push i pull?

    virtual int remove(size_t index) = 0;                    // removes item from the specified index

    virtual void append(int value) = 0;                      // add item at the end
    virtual void prepend(int value) = 0;                     // add item at the beginning
    virtual void insert(int value, size_t index) = 0;        // add item at the specified position


    virtual ~Structure() {}
};
