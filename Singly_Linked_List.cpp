#include "Singly_Linked_List.h"

//definitions of functions declared in SinglyLinkedList.h

//constuction of the list
SinglyLinkedList::SinglyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

//destruction of the list, we need to free memory for each Node in the List, otherwise we would have a memory leak
SinglyLinkedList::~SinglyLinkedList() {
    Node* current = head;
    while (current) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
}

void SinglyLinkedList::print_array() {
    Node* current = head;
    while (current) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}

size_t SinglyLinkedList::get_size(void) const {
    return size;
}

int SinglyLinkedList::get_component(size_t index) const {
    if (index >= size)
    {
        std::cout << "\nIndex is out of range.\n";
        return 0;
    }

    Node* current = head;
    for (size_t i = 0; i < index; i++)
        current = current->next;

    return current->data;
}

void SinglyLinkedList::push_front(int value) {
    Node* newNode = new Node(value);

    //if the list is empty (tail=nullptr) then the new node becomes the tail as well as head,
    // otherwise the new node should point to the old head and become the new head
    if (!tail) {
        tail = newNode;
    }
    else
    {
        newNode->next = head;
        head = newNode;
    }

    size++;
}

void SinglyLinkedList::push_back(int value) {
    Node* newNode = new Node(value);

    //if the list is empty (head=nullptr) then the new node becomes the head as well as tail,
    // otherwise the old tail should point to the new node and the new node becomes the new tail
    if (!head) {
        head = newNode;
    }
    else {
        Node* current = head;
        while (current->next)
            current = current->next;

        current->next = newNode;
    }

    size++;
}

void SinglyLinkedList::push_at(int value, size_t index) {
    if (index == 0) {
        push_front(value);
        return;
    }

    if (index > size)
        throw std::out_of_range("Index");

    Node* current = head;
    for (size_t i = 0; i < index - 1; i++)
        current = current->next;

    Node* newNode = new Node(value);
    newNode->next = current->next;
    current->next = newNode;

    size++;
}