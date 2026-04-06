#pragma once
#include <iostream>
#include "Structure.h"

class SinglyLinkedList : public Structure {
private:
    struct Node {
        int data;
        Node* next;
        Node(int value) : data(value), next(nullptr) {}
    };

    size_t size;
    Node* head;
    Node* tail;

public:
    virtual void print_array(void) override;
    virtual size_t get_size(void) const override;
    virtual int get_component(size_t index) const override;
    virtual bool search(int value) override;
    virtual int* searchAll(int value, int& count) override;

    virtual int pop_front(void) override;
    virtual int pop_back(void) override;
    void pop_at(size_t index) override;

    void push_back(int data) override;
    void push_front(int data) override;
    void push_at(int data, size_t index) override;

    SinglyLinkedList();
    ~SinglyLinkedList();
};