#pragma once
#include "Structure.h"
#include <cstring> // memcpy

class DynamicArray : public Structure{
private:
    size_t size;
    size_t capacity;
    int* array;
    void resize(size_t new_capacity);

public:
    virtual void print_array(void) override;
    virtual size_t get_size(void) const override;
    virtual int get_component(size_t index) const override;
    virtual bool search(int value) override;
    //virtual int* searchAll(int value, int& count) override;

    virtual int pop_front(void) override;
    virtual int pop_back(void) override;
    virtual int pop_at(size_t index) override;

    void push_back(int data) override;
    void push_front(int data) override;
    void push_at(int data, size_t index) override;

    void check_capacity(void);

    DynamicArray();
    DynamicArray(size_t initialCapacity);
    ~DynamicArray();
};