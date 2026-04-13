#include "Singly_Linked_List.h"

//definitions of functions declared in SinglyLinkedList.h

//constuction of the list
SinglyLinkedList::SinglyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

//destroying all nodes to free occupied memory
SinglyLinkedList::~SinglyLinkedList() {
    Node* current = head;
    while (current) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
}

//iterating through the list and printing the value of each node
void SinglyLinkedList::print() {
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
        head = tail = newNode;
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
        head = tail = head = newNode;
    }
    else {
        tail->next = newNode;
        tail = newNode;
    }
    size++;
}

void SinglyLinkedList::push_at(size_t index, int data) {
    if (index == 0) {
        push_front(data);
        return;
    }

    if (index > size)
    {
        std::cout << "\nIndex is out of range.\n";
        return;
    }

    //we need to find the node at index-1, then we can insert the new node after it
    Node* current = head;
    for (size_t i = 0; i < index - 1; i++)
        current = current->next;

    Node* newNode = new Node(data);
    newNode->next = current->next;
    current->next = newNode;

    size++;
}

void SinglyLinkedList::pop_front() {
    if (!head) {
        std::cout << "\nThere is nothing to remove.\n";
        return;
    }

    //deleting the head node and making the next node the new head
    Node* temp = head;
    head = head->next;
    delete temp;

    size--;
}

void SinglyLinkedList::pop_back() {
    if (!head) {
        std::cout << "\nThere is nothing to remove.\n";
        return;
    }

    //if there is only one node in the list, we can simply call pop_front
    if (!head->next) {
        pop_front();
        return;
    }

	//we need to find the node before the tail, then we can delete the tail and make the found node the new tail
    Node* current = head;
    while (current->next->next)
        current = current->next;

	//current is now the node before the tail, we can delete the tail and make current the new tail
    delete current->next;
    current->next = nullptr;
    tail = current;

    size--;
}

void SinglyLinkedList::pop_at(size_t index) {
    if (index >= size)
    {
        std::cout << "\nThere is nothing to remove.\n";
        return;
    };

    if (index == 0)
    {
        pop_front();
        return;
    }

    Node* current = head;
    for (size_t i = 0; i < index - 1; i++)
        current = current->next;

    Node* temp = current->next;
    
    if (temp == tail) {
        tail = current;
    }

    current->next = temp->next;
    delete temp;

    size--;
}

bool SinglyLinkedList::search(int value) {
    Node* current = head;

    // checking each node in the list until we find the value or reach the end of the list
    while (current) {
        if (current->data == value)
            return true;
        current = current->next;
    }
    return false;
}