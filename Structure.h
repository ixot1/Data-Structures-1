#pragma once
#include <iostream>
#include <cstddef> //for size_t


// a base class for all the structures used in the code, an abstract class
class Structure {
public:
    virtual void print_array(void) = 0;                      // display values inside of a chosen structure
    virtual size_t get_size(void) const = 0;                 // returns size value
    virtual int get_component(size_t index) const = 0;       // returns a number on the given index
    virtual bool search(int value) = 0;                      // checks if the specified value is in the structure (true or false)
   // virtual int* searchAll(int value, int& count) = 0;       // returns all indexes where the specified value is located and the number of occurrences (count)

    virtual int pop_front(void) = 0;                         // removes item from the beggining
    virtual int pop_back(void) = 0;                          // removes item from the end
    virtual int pop_at(size_t index) = 0;			         // removes item from the specified index

	virtual void push_back(int data) = 0;                    // adds item at the end
    virtual void push_front(int data) = 0;                   // adds item at the beginning
	virtual void push_at(int data, size_t index)=0;            // adds item at the specified index
   
    virtual ~Structure() {}
};
