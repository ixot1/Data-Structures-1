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

    virtual void pop_front(void) override;
    virtual void pop_back(void) override;
    virtual void pop_at(size_t index) override;

    virtual void push_back(int data) override;
    virtual void push_front(int data) override;
    virtual void push_at(int data, size_t index) override;

    DynamicArray();
    DynamicArray(size_t initialCapacity);
    ~DynamicArray();
};