#pragma once
#include "Structure.h"

class DoublyLinkedList : public Structure {
private:
    struct Node {
        int data;
        Node* prev;
        Node* next;
        Node(int value) : prev(nullptr), data(value), next(nullptr) {}
    };

    size_t size;
    Node* head;
    Node* tail;

public:
    virtual void print(void) override;
    virtual size_t get_size(void) const override;
    virtual int get_component(size_t index) const override;
    virtual bool search(int value) override;

    virtual void pop_front(void) override;
    virtual void pop_back(void) override;
    virtual void pop_at(size_t index) override;

    virtual void push_back(int data) override;
    virtual void push_front(int data) override;
    virtual void push_at(size_t index, int data) override;


    DoublyLinkedList();
    ~DoublyLinkedList();
};