#pragma once
#include "Structure.h"

class DynamicArray : public Structure{
private:
    size_t size;
    size_t capacity;
    int* array;
    void resize(size_t new_capacity);

public:
    virtual void print() override;
    virtual size_t get_size() const override;
    virtual int get_component(size_t index) const override;
    virtual bool search(int value) override;

    virtual void pop_front() override;
    virtual void pop_back() override;
    virtual void pop_at(size_t index) override;

    virtual void push_back(int data) override;
    virtual void push_front(int data) override;
    virtual void push_at(size_t index, int data) override;

    DynamicArray();
    DynamicArray(size_t initialCapacity);
    ~DynamicArray();
};